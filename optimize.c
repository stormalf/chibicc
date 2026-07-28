#include "chibicc.h"


// Check if Tail Call Optimization can be applied to the function.
// TCO is disabled if any local variable has its address taken or is volatile.
bool can_apply_tco_scope(Scope *sc) {
  for (Obj *var = sc->locals; var; var = var->next) {
    if (var->is_address_used || is_volatile(var->ty))
      return false;
  }
  for (Scope *child = sc->children; child; child = child->sibling_next) {
    if (!can_apply_tco_scope(child))
      return false;
  }
  return true;
}

//implementing tail call optimization. Marking tails calls.
void mark_tail_calls(Node *node, Obj *fn) {
  if (!node)
    return;

  switch (node->kind) {
  case ND_BLOCK:
    if (!node->body)
      return;
    Node *last = node->body;
    while (last->next)
      last = last->next;
    mark_tail_calls(last, fn);
    break;
  case ND_IF:
    mark_tail_calls(node->then, fn);
    mark_tail_calls(node->els, fn);
    break;
  case ND_RETURN:
    mark_tail_calls(node->lhs, fn);
    break;
  case ND_EXPR_STMT:
    // Allow sibling-call optimization only when reaching the end of a
    // non-main void function (so that main's implicit return 0 is preserved).
    if (!fn || strcmp(fn->name, "main") == 0)
      break;
    if (!fn->ty || !fn->ty->return_ty || fn->ty->return_ty->kind != TY_VOID)
      break;
    mark_tail_calls(node->lhs, fn);
    break;
  case ND_CAST:
    mark_tail_calls(node->lhs, fn);
    break;
  case ND_COMMA:
    mark_tail_calls(node->rhs, fn);
    break;
  case ND_FUNCALL:
    node->is_tail = true;
    break;
  default:
    break;
  }
}

void mark_live(Obj *var)
{
  if (!var->is_function || var->is_live)
    return;

  var->is_live = true;

  for (int i = 0; i < var->refs.len; i++)
  {
    Obj *fn = find_func(var->refs.data[i]);
    if (fn)
      mark_live(fn);
  }
}

static void mark_liveness_on_node(Node *node, bool is_lhs) {
  if (!node) return;

  switch (node->kind) {
  case ND_VAR:
    if (!node->var || node->var->is_function)
      return;
    node->var->is_read = true;
    if (is_lhs)
      node->var->is_written = true;
    return;
  case ND_MEMBER:
    mark_liveness_on_node(node->lhs, is_lhs);
    return;
  case ND_DEREF:
    mark_liveness_on_node(node->lhs, false);
    return;
  case ND_ASSIGN:
    mark_liveness_on_node(node->rhs, false);
    mark_liveness_on_node(node->lhs, true);
    return;
  case ND_ADDR:
    mark_var_address_taken(node->lhs);
    mark_liveness_on_node(node->lhs, false);
    return;
  case ND_FUNCALL:
    mark_liveness_on_node(node->lhs, false);
    for (Node *a = node->args; a; a = a->next)
      mark_liveness_on_node(a, false);
    if (node->ret_buffer)
      node->ret_buffer->is_written = true;
    return;
  case ND_RETURN:
    mark_liveness_on_node(node->lhs, false);
    return;
  case ND_COND:
    mark_liveness_on_node(node->cond, false);
    mark_liveness_on_node(node->then, false);
    mark_liveness_on_node(node->els, false);
    return;
  case ND_BLOCK:
  case ND_STMT_EXPR:
    for (Node *n = node->body; n; n = n->next)
      mark_liveness_on_node(n, false);
    return;
  case ND_IF:
    mark_liveness_on_node(node->cond, false);
    mark_liveness_on_node(node->then, false);
    mark_liveness_on_node(node->els, false);
    return;
  case ND_FOR:
    mark_liveness_on_node(node->init, false);
    mark_liveness_on_node(node->cond, false);
    mark_liveness_on_node(node->inc, false);
    mark_liveness_on_node(node->then, false);
    return;
  case ND_DO:
    mark_liveness_on_node(node->then, false);
    mark_liveness_on_node(node->cond, false);
    return;
  case ND_SWITCH:
    mark_liveness_on_node(node->cond, false);
    mark_liveness_on_node(node->then, false);
    return;
  case ND_CASE:
  case ND_LABEL:
    mark_liveness_on_node(node->lhs, false);
    return;
  case ND_EXPR_STMT:
    mark_liveness_on_node(node->lhs, false);
    return;
  case ND_COMMA:
    mark_liveness_on_node(node->lhs, false);
    mark_liveness_on_node(node->rhs, false);
    return;
  case ND_CAST:
    mark_liveness_on_node(node->lhs, false);
    return;
  case ND_GOTO:
  case ND_GOTO_EXPR:
  case ND_LABEL_VAL:
  case ND_NULL_EXPR:
  case ND_NUM:
    return;
  case ND_VLA_PTR:
    if (node->var && !node->var->is_function)
      node->var->is_read = true;
    return;
  case ND_MEMZERO:
    if (node->var)
      node->var->is_written = true;
    return;
  case ND_ASM:
    return;
  case ND_FPCLASSIFY:
    if (node->fpc && node->fpc->node)
      mark_liveness_on_node(node->fpc->node, false);
    return;
  default:
    if (node->lhs)
      mark_liveness_on_node(node->lhs, false);
    if (node->rhs)
      mark_liveness_on_node(node->rhs, false);
    for (int i = 0; i < MAX_BUILTIN_ARGS; i++)
      if (node->builtin_args[i])
        mark_liveness_on_node(node->builtin_args[i], false);
    if (node->builtin_dest)
      mark_liveness_on_node(node->builtin_dest, false);
    if (node->builtin_src)
      mark_liveness_on_node(node->builtin_src, false);
    if (node->builtin_size)
      mark_liveness_on_node(node->builtin_size, false);
    if (node->builtin_val)
      mark_liveness_on_node(node->builtin_val, false);
    if (node->cas_addr)
      mark_liveness_on_node(node->cas_addr, false);
    if (node->cas_old)
      mark_liveness_on_node(node->cas_old, false);
    if (node->cas_new)
      mark_liveness_on_node(node->cas_new, false);
    if (node->cas_ptr)
      mark_liveness_on_node(node->cas_ptr, false);
    if (node->cas_expected)
      mark_liveness_on_node(node->cas_expected, false);
    if (node->cas_desired)
      mark_liveness_on_node(node->cas_desired, false);
    if (node->cas_weak)
      mark_liveness_on_node(node->cas_weak, false);
    if (node->cas_success)
      mark_liveness_on_node(node->cas_success, false);
    if (node->cas_failure)
      mark_liveness_on_node(node->cas_failure, false);
    if (node->atomic_addr && !node->atomic_addr->is_function)
      node->atomic_addr->is_address_used = true;
    if (node->atomic_addr && !node->atomic_addr->is_function) {
      node->atomic_addr->is_read = true;
      node->atomic_addr->is_written = true;
    }
    if (node->atomic_expr)
      mark_liveness_on_node(node->atomic_expr, false);
    break;
  }
}

void mark_liveness_on_locals(Obj *prog) {
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    mark_liveness_on_node(fn->body, false);

    emit_unused_warnings(fn);

    if (fn->alloca_bottom) {
      fn->alloca_bottom->is_read = true;
      fn->alloca_bottom->is_written = true;
    }
    if (fn->va_area) {
      fn->va_area->is_read = true;
      fn->va_area->is_written = true;
    }

    for (Obj *p = fn->params; p; p = p->next) {
      p->is_read = true;
      if (!p->ty->is_const)
        p->is_written = true;
    }
  }
}

Node *constant_folding(int kind, Node *lhs, Node *rhs, Token *tok)
{
  add_type(lhs);
  add_type(rhs);

  if (lhs->kind != ND_NUM || rhs->kind != ND_NUM)
    return NULL;

  Node *node;
  bool is_float = is_flonum(lhs->ty) || is_flonum(rhs->ty);

  if (is_float) {
    double a = is_flonum(lhs->ty) ? lhs->fval : lhs->val;
    double b = is_flonum(rhs->ty) ? rhs->fval : rhs->val;

    switch (kind) {
    case ND_ADD: node = new_double(a + b, tok); break;
    case ND_SUB: node = new_double(a - b, tok); break;
    case ND_MUL: node = new_double(a * b, tok); break;
    case ND_DIV:
      node = new_double(a / b, tok);
      break;
    default: return NULL;
    }
  } else {
    bool is_unsigned = lhs->ty->is_unsigned || rhs->ty->is_unsigned;

    uint64_t u_a = lhs->val;
    uint64_t u_b = rhs->val;

    int64_t s_a = lhs->val;
    int64_t s_b = rhs->val;

    switch (kind) {
    case ND_ADD: node = new_num(is_unsigned ? (u_a + u_b) : (s_a + s_b), tok); break;
    case ND_SUB: node = new_num(is_unsigned ? (u_a - u_b) : (s_a - s_b), tok); break;
    case ND_MUL: node = new_num(is_unsigned ? (u_a * u_b) : (s_a * s_b), tok); break;
    case ND_DIV:
      if (is_unsigned ? (u_b == 0) : (s_b == 0))
        return NULL;
      node = new_num(is_unsigned ? (u_a / u_b) : (s_a / s_b), tok);
      break;
    case ND_MOD:
      if (is_unsigned ? (u_b == 0) : (s_b == 0))
        return NULL;
      node = new_num(is_unsigned ? (u_a % u_b) : (s_a % s_b), tok);
      break;
    default: return NULL;
    }
  }

  Node dummy = {kind, .lhs = lhs, .rhs = rhs, .tok = tok};
  add_type(&dummy);
  node->ty = dummy.ty;

  if (!is_float)
    node->val = eval_sign_extend(node->ty, node->val);
  else if (node->ty->kind == TY_FLOAT)
    node->fval = (float)node->fval;

  return node;
}
