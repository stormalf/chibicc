#include "chibicc.h"

static Node *copy_node(Node *node) {
  if (!node) return NULL;
  Node *n = calloc(1, sizeof(Node));
  *n = *node;
  n->next = copy_node(node->next);
  n->goto_next = NULL;
  n->case_next = NULL;
  n->lhs = copy_node(node->lhs);
  n->rhs = copy_node(node->rhs);
  n->cond = copy_node(node->cond);
  n->then = copy_node(node->then);
  n->els = copy_node(node->els);
  n->init = copy_node(node->init);
  n->inc = copy_node(node->inc);
  n->body = copy_node(node->body);
  n->args = copy_node(node->args);
  n->builtin_dest = copy_node(node->builtin_dest);
  n->builtin_src = copy_node(node->builtin_src);
  n->builtin_size = copy_node(node->builtin_size);
  n->builtin_val = copy_node(node->builtin_val);
  for (int i = 0; i < MAX_BUILTIN_ARGS; i++)
    n->builtin_args[i] = copy_node(node->builtin_args[i]);
  n->cas_addr = copy_node(node->cas_addr);
  n->cas_old = copy_node(node->cas_old);
  n->cas_new = copy_node(node->cas_new);
  return n;
}

static Node *subst_params(Node *node, Obj *fn, Node *args) {
  if (!node) return NULL;
  if (node->kind == ND_VAR && node->var->is_param) {
    Node *arg = args;
    for (Obj *p = fn->params; p; p = p->next, arg = arg->next) {
      if (p == node->var)
        return copy_node(arg);
    }
  }
  node->lhs = subst_params(node->lhs, fn, args);
  node->rhs = subst_params(node->rhs, fn, args);
  node->cond = subst_params(node->cond, fn, args);
  node->then = subst_params(node->then, fn, args);
  node->els = subst_params(node->els, fn, args);
  node->init = subst_params(node->init, fn, args);
  node->inc = subst_params(node->inc, fn, args);
  node->body = subst_params(node->body, fn, args);
  node->args = subst_params(node->args, fn, args);
  node->builtin_dest = subst_params(node->builtin_dest, fn, args);
  node->builtin_src = subst_params(node->builtin_src, fn, args);
  node->builtin_size = subst_params(node->builtin_size, fn, args);
  node->builtin_val = subst_params(node->builtin_val, fn, args);
  for (int i = 0; i < MAX_BUILTIN_ARGS; i++)
    node->builtin_args[i] = subst_params(node->builtin_args[i], fn, args);
  node->cas_addr = subst_params(node->cas_addr, fn, args);
  node->cas_old = subst_params(node->cas_old, fn, args);
  node->cas_new = subst_params(node->cas_new, fn, args);
  return node;
}

//basic inlining restricted to only simple case to manage for now
static bool can_inline(Obj *fn) {
  if (!fn->is_inline)
    return false;
  if (!fn->ty)
    return false;
  if (fn->is_extern)
    return false;
  if (fn->ty->is_variadic)
    return false;
  if (!fn->is_definition)
    return false;
  if (fn->is_noinline)
    return false;
  if (!fn->body || fn->body->kind != ND_BLOCK)
    return false;
  Node *stmt = fn->body->body;
  if (!stmt || stmt->next)
    return false;
  if (stmt->kind != ND_RETURN || !stmt->lhs)
    return false;
  for (Obj *var = fn->locals; var; var = var->next)
    if (!var->is_param)
      return false;
  return true;
}

static Node *inline_funcall(Node *call, Obj *callee) {
  Node *ret = callee->body->body;
  Node *expr = copy_node(ret->lhs);
  expr = subst_params(expr, callee, call->args);
  add_type(expr);
  return expr;
}

static Node *inline_in_stmt(Node *node, Obj *current_fn) {
  if (!node) return NULL;
  if (node->kind == ND_FUNCALL) {
    if (node->lhs && node->lhs->kind == ND_VAR && node->lhs->var->is_function) {
      Obj *callee = node->lhs->var;
      if (callee != current_fn && can_inline(callee)) {
        Node *result = inline_funcall(node, callee);
        return inline_in_stmt(result, current_fn);
      }
    }
  }
  node->next = inline_in_stmt(node->next, current_fn);
  node->lhs = inline_in_stmt(node->lhs, current_fn);
  node->rhs = inline_in_stmt(node->rhs, current_fn);
  node->cond = inline_in_stmt(node->cond, current_fn);
  node->then = inline_in_stmt(node->then, current_fn);
  node->els = inline_in_stmt(node->els, current_fn);
  node->init = inline_in_stmt(node->init, current_fn);
  node->inc = inline_in_stmt(node->inc, current_fn);
  node->body = inline_in_stmt(node->body, current_fn);
  node->args = inline_in_stmt(node->args, current_fn);
  node->builtin_dest = inline_in_stmt(node->builtin_dest, current_fn);
  node->builtin_src = inline_in_stmt(node->builtin_src, current_fn);
  node->builtin_size = inline_in_stmt(node->builtin_size, current_fn);
  node->builtin_val = inline_in_stmt(node->builtin_val, current_fn);
  for (int i = 0; i < MAX_BUILTIN_ARGS; i++)
    node->builtin_args[i] = inline_in_stmt(node->builtin_args[i], current_fn);
  node->cas_addr = inline_in_stmt(node->cas_addr, current_fn);
  node->cas_old = inline_in_stmt(node->cas_old, current_fn);
  node->cas_new = inline_in_stmt(node->cas_new, current_fn);
  return node;
}

void inline_function_bodies(Obj *prog) {
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    fn->body = inline_in_stmt(fn->body, fn);
  }
}
