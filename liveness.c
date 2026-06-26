#include "chibicc.h"

typedef enum {
  LV_READ,
  LV_WRITE,
  LV_ADDR,
} LvContext;

static void analyze_node(Node *node, LvContext ctx, int *pos);

static LvContext context_for_child(LvContext ctx, NodeKind kind) {
  switch (kind) {
  case ND_MEMBER:
    return ctx;
  case ND_DEREF:
    return LV_READ;
  case ND_ADDR:
    return LV_ADDR;
  default:
    return (ctx == LV_ADDR) ? LV_READ : ctx;
  }
}

static void analyze_operand(Node *node, LvContext ctx, int *pos) {
  if (!node) return;
  LvContext child_ctx = context_for_child(ctx, node->kind);
  analyze_node(node, child_ctx, pos);
}

static void analyze_node(Node *node, LvContext ctx, int *pos) {
  if (!node) return;

  if (node->kind == ND_VAR && node->var && node->var->is_local) {
    Obj *var = node->var;
    (*pos)++;
    if (var->first_use < 0) var->first_use = *pos;
    var->last_use = *pos;
    switch (ctx) {
    case LV_READ:
      var->is_read = true;
      break;
    case LV_WRITE:
      var->is_written = true;
      break;
    case LV_ADDR:
      break;
    }
    return;
  }

  switch (node->kind) {
  case ND_ASSIGN:
    analyze_operand(node->lhs, LV_WRITE, pos);
    analyze_operand(node->rhs, LV_READ, pos);
    break;
  case ND_ADDR:
    analyze_operand(node->lhs, LV_ADDR, pos);
    break;
  case ND_DEREF:
    analyze_operand(node->lhs, LV_READ, pos);
    break;
  case ND_MEMBER:
    analyze_operand(node->lhs, ctx, pos);
    break;
  case ND_FUNCALL:
    analyze_operand(node->lhs, LV_READ, pos);
    for (Node *a = node->args; a; a = a->next)
      analyze_operand(a, LV_READ, pos);
    break;
  case ND_RETURN:
    analyze_operand(node->lhs, LV_READ, pos);
    break;
  case ND_IF:
    analyze_operand(node->cond, LV_READ, pos);
    analyze_operand(node->then, LV_READ, pos);
    analyze_operand(node->els, LV_READ, pos);
    break;
  case ND_FOR:
    analyze_operand(node->init, LV_READ, pos);
    analyze_operand(node->cond, LV_READ, pos);
    analyze_operand(node->inc, LV_READ, pos);
    analyze_operand(node->body, LV_READ, pos);
    break;
  case ND_DO:
    analyze_operand(node->cond, LV_READ, pos);
    analyze_operand(node->body, LV_READ, pos);
    break;
  case ND_SWITCH:
    analyze_operand(node->cond, LV_READ, pos);
    analyze_operand(node->then, LV_READ, pos);
    break;
  case ND_CASE:
    analyze_operand(node->lhs, LV_READ, pos);
    analyze_operand(node->rhs, LV_READ, pos);
    analyze_operand(node->then, LV_READ, pos);
    break;
  case ND_BLOCK:
  case ND_STMT_EXPR:
    for (Node *n = node->body; n; n = n->next)
      analyze_operand(n, LV_READ, pos);
    break;
  case ND_EXPR_STMT:
  case ND_LABEL:
    analyze_operand(node->lhs, LV_READ, pos);
    break;
  case ND_LABEL_VAL:
    break;
  case ND_GOTO:
  case ND_GOTO_EXPR:
    break;
  case ND_NULL_EXPR:
    break;
  default:
    analyze_operand(node->lhs, LV_READ, pos);
    analyze_operand(node->rhs, LV_READ, pos);
    analyze_operand(node->cond, LV_READ, pos);
    analyze_operand(node->then, LV_READ, pos);
    analyze_operand(node->els, LV_READ, pos);
    analyze_operand(node->init, LV_READ, pos);
    analyze_operand(node->inc, LV_READ, pos);
    if (node->body) {
      for (Node *n = node->body; n; n = n->next)
        analyze_operand(n, LV_READ, pos);
    }
    if (node->args) {
      for (Node *a = node->args; a; a = a->next)
        analyze_operand(a, LV_READ, pos);
    }
    break;
  }
}

static void scope_init_liveness(Scope *sc) {
  for (Scope *child = sc->children; child; child = child->sibling_next)
    scope_init_liveness(child);
  for (Obj *var = sc->locals; var; var = var->next) {
    var->first_use = -1;
    var->last_use = -1;
    var->is_read = false;
    var->is_written = false;
  }
}

static void scope_warn_unused(Scope *sc) {
  for (Scope *child = sc->children; child; child = child->sibling_next)
    scope_warn_unused(child);
  for (Obj *var = sc->locals; var; var = var->next) {
    if (var->first_use >= 0)
      continue;
    if (!var->name || !var->name[0] || var->name[0] == '.')
      continue;
    if (var->is_param)
      continue;
    if (var->tok)
      warn_tok(var->tok, "unused variable '%s'", var->name);
    else
      fprintf(stderr, "warning: unused variable '%s'\n", var->name);
  }
}

static void fn_warn_unused_params(Obj *fn) {
  if (!opt_unused_param_warn)
    return;
  for (Obj *var = fn->params; var; var = var->next) {
    if (var->first_use >= 0)
      continue;
    if (!var->name || !var->name[0])
      continue;
    if (var->tok)
      warn_tok(var->tok, "unused parameter '%s'", var->name);
    else
      fprintf(stderr, "warning: unused parameter '%s'\n", var->name);
  }
}

static void analyze_function(Obj *fn) {
  if (!fn->ty->scopes)
    return;
  scope_init_liveness(fn->ty->scopes);
  int pos = 0;
  if (fn->body)
    analyze_node(fn->body, LV_READ, &pos);
  if (opt_unused_warn)
    scope_warn_unused(fn->ty->scopes);
  fn_warn_unused_params(fn);
}

void analyze_liveness(Obj *prog) {
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    analyze_function(fn);
  }
}
