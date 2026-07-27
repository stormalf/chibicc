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
  }
}
