#include "chibicc.h"

//
// Basic block construction
// Builds a control-flow graph (CFG) from the AST.
//

typedef struct {
  BasicBlock *from;
  char *label;
} DeferredGoto;

typedef struct {
  BasicBlock *head;
  BasicBlock *tail;
  HashMap label_map;
  DeferredGoto *pending;
  int pending_len;
  int pending_cap;
} BBState;

typedef struct {
  BasicBlock *bb;
  bool terminated;
} BBWalkResult;

static BasicBlock *basicblock_alloc(BBState *s) {
  BasicBlock *bb = calloc(1, sizeof(BasicBlock));
  bb->id = s->tail ? s->tail->id + 1 : 0;
  if (s->tail) {
    s->tail->chain = bb;
    bb->chain_prev = s->tail;
  } else {
    s->head = bb;
  }
  s->tail = bb;
  return bb;
}

static void basicblock_add_edge(BasicBlock *from, BasicBlock *to) {
  if (from->next.len == from->next.cap) {
    from->next.cap = from->next.cap ? from->next.cap * 2 : 4;
    from->next.data = realloc(from->next.data, from->next.cap * sizeof(BasicBlock *));
  }
  from->next.data[from->next.len++] = to;
  if (to->prev.len == to->prev.cap) {
    to->prev.cap = to->prev.cap ? to->prev.cap * 2 : 4;
    to->prev.data = realloc(to->prev.data, to->prev.cap * sizeof(BasicBlock *));
  }
  to->prev.data[to->prev.len++] = from;
}

static void add_pending_goto(BBState *s, BasicBlock *from, char *label) {
  if (s->pending_len == s->pending_cap) {
    s->pending_cap = s->pending_cap ? s->pending_cap * 2 : 16;
    s->pending = realloc(s->pending, s->pending_cap * sizeof(DeferredGoto));
  }
  s->pending[s->pending_len++] = (DeferredGoto){from, label};
}

static BBWalkResult basicblock_walk_stmts(BBState *s, Node *node, BasicBlock *cur);
static BBWalkResult basicblock_walk_body(BBState *s, Node *node, BasicBlock *cur);

static BBWalkResult basicblock_walk_body(BBState *s, Node *node, BasicBlock *cur) {
  if (!node)
    return (BBWalkResult){cur, false};
  if (node->kind == ND_BLOCK)
    return basicblock_walk_stmts(s, node->body, cur);
  return basicblock_walk_stmts(s, node, cur);
}

static BBWalkResult basicblock_walk_stmts(BBState *s, Node *node, BasicBlock *cur) {
  bool terminated = false;
  while (node) {
    switch (node->kind) {
    case ND_NULL_EXPR:
      terminated = false;
      node = node->next;
      continue;

    case ND_BLOCK: {
      BBWalkResult r = basicblock_walk_stmts(s, node->body, cur);
      cur = r.bb;
      terminated = r.terminated;
      node = node->next;
      continue;
    }

    case ND_LABEL:
      if (cur->has_stmt) {
        BasicBlock *prev_bb = cur;
        cur = basicblock_alloc(s);
        if (prev_bb->next.len == 0)
          basicblock_add_edge(prev_bb, cur);
      }
      hashmap_put(&s->label_map, node->unique_label, cur);
      cur->label = node->unique_label;
      terminated = false;
      if (node->lhs) {
        BBWalkResult r = basicblock_walk_body(s, node->lhs, cur);
        cur = r.bb;
        terminated = r.terminated;
      }
      node = node->next;
      continue;

    case ND_CASE:
      if (cur->has_stmt) {
        BasicBlock *prev_bb = cur;
        cur = basicblock_alloc(s);
        if (prev_bb->next.len == 0)
          basicblock_add_edge(prev_bb, cur);
      }
      if (node->label)
        hashmap_put(&s->label_map, node->label, cur);
      terminated = false;
      if (node->lhs) {
        BBWalkResult r = basicblock_walk_body(s, node->lhs, cur);
        cur = r.bb;
        terminated = r.terminated;
      }
      node = node->next;
      continue;

    case ND_IF: {
      cur->has_stmt = true;
      BasicBlock *after = basicblock_alloc(s);
      BasicBlock *then_bb = basicblock_alloc(s);
      basicblock_add_edge(cur, then_bb);
      BBWalkResult then_r = basicblock_walk_body(s, node->then, then_bb);
      if (!then_r.terminated)
        basicblock_add_edge(then_r.bb, after);
      if (node->els) {
        BasicBlock *else_bb = basicblock_alloc(s);
        basicblock_add_edge(cur, else_bb);
        BBWalkResult else_r = basicblock_walk_body(s, node->els, else_bb);
        if (!else_r.terminated)
          basicblock_add_edge(else_r.bb, after);
      } else {
        basicblock_add_edge(cur, after);
      }
      cur = after;
      terminated = false;
      node = node->next;
      continue;
    }

    case ND_FOR: {
      cur->has_stmt = true;
      if (node->init) {
        BBWalkResult r = basicblock_walk_stmts(s, node->init, cur);
        cur = r.bb;
      }
      BasicBlock *cond_bb = basicblock_alloc(s);
      BasicBlock *body_bb = basicblock_alloc(s);
      BasicBlock *inc_bb = basicblock_alloc(s);
      BasicBlock *after = basicblock_alloc(s);
      basicblock_add_edge(cur, cond_bb);
      if (node->cond)
        basicblock_walk_stmts(s, node->cond, cond_bb);
      basicblock_add_edge(cond_bb, body_bb);
      basicblock_add_edge(cond_bb, after);
      if (node->brk_label)
        hashmap_put(&s->label_map, node->brk_label, after);
      if (node->cont_label)
        hashmap_put(&s->label_map, node->cont_label, inc_bb);
      BBWalkResult body_r = basicblock_walk_body(s, node->then, body_bb);
      if (!body_r.terminated)
        basicblock_add_edge(body_r.bb, inc_bb);
      if (node->inc)
        basicblock_walk_stmts(s, node->inc, inc_bb);
      basicblock_add_edge(inc_bb, cond_bb);
      cur = after;
      terminated = false;
      node = node->next;
      continue;
    }

    case ND_DO: {
      cur->has_stmt = true;
      BasicBlock *body_bb = basicblock_alloc(s);
      BasicBlock *cond_bb = basicblock_alloc(s);
      BasicBlock *after = basicblock_alloc(s);
      basicblock_add_edge(cur, body_bb);
      if (node->brk_label)
        hashmap_put(&s->label_map, node->brk_label, after);
      if (node->cont_label)
        hashmap_put(&s->label_map, node->cont_label, cond_bb);
      BBWalkResult body_r = basicblock_walk_body(s, node->then, body_bb);
      if (!body_r.terminated)
        basicblock_add_edge(body_r.bb, cond_bb);
      if (node->cond)
        basicblock_walk_stmts(s, node->cond, cond_bb);
      basicblock_add_edge(cond_bb, body_bb);
      basicblock_add_edge(cond_bb, after);
      cur = after;
      terminated = false;
      node = node->next;
      continue;
    }

    case ND_SWITCH: {
      cur->has_stmt = true;
      BasicBlock *after = basicblock_alloc(s);
      if (node->brk_label)
        hashmap_put(&s->label_map, node->brk_label, after);
      basicblock_walk_body(s, node->then, cur);
      cur = after;
      terminated = false;
      node = node->next;
      continue;
    }

    case ND_GOTO:
      cur->has_stmt = true;
      terminated = true;
      {
        BasicBlock *target = hashmap_get(&s->label_map, node->unique_label);
        if (target)
          basicblock_add_edge(cur, target);
        else
          add_pending_goto(s, cur, node->unique_label);
      }
      cur = basicblock_alloc(s);
      node = node->next;
      continue;

    case ND_GOTO_EXPR:
      cur->has_stmt = true;
      terminated = true;
      cur = basicblock_alloc(s);
      node = node->next;
      continue;

    case ND_RETURN:
      cur->has_stmt = true;
      terminated = true;
      cur = basicblock_alloc(s);
      node = node->next;
      continue;

    default:
      cur->has_stmt = true;
      terminated = false;
      node = node->next;
      continue;
    }
  }
  return (BBWalkResult){cur, terminated};
}

void build_bbs(Obj *prog) {
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    if (!fn->body)
      continue;
    BBState s = {0};
    BasicBlock *entry = basicblock_alloc(&s);
    if (fn->body->kind == ND_BLOCK)
      basicblock_walk_stmts(&s, fn->body->body, entry);
    else
      basicblock_walk_stmts(&s, fn->body, entry);
    for (int i = 0; i < s.pending_len; i++)
      basicblock_add_edge(s.pending[i].from,
                   hashmap_get(&s.label_map, s.pending[i].label));
    fn->bbs = s.head;
  }
}

//
// Liveness analysis
//

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
    analyze_operand(node->then, LV_READ, pos);
    break;
  case ND_DO:
    analyze_operand(node->cond, LV_READ, pos);
    analyze_operand(node->then, LV_READ, pos);
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
    analyze_operand(node->builtin_dest, LV_READ, pos);
    analyze_operand(node->builtin_src, LV_READ, pos);
    analyze_operand(node->builtin_size, LV_READ, pos);
    analyze_operand(node->builtin_val, LV_READ, pos);
    for (int i = 0; i < node->builtin_nargs; i++)
      analyze_operand(node->builtin_args[i], LV_READ, pos);
    analyze_operand(node->cas_addr, LV_READ, pos);
    analyze_operand(node->cas_old, LV_READ, pos);
    analyze_operand(node->cas_new, LV_READ, pos);
    analyze_operand(node->cas_ptr, LV_READ, pos);
    analyze_operand(node->cas_expected, LV_READ, pos);
    analyze_operand(node->cas_desired, LV_READ, pos);
    analyze_operand(node->cas_weak, LV_READ, pos);
    analyze_operand(node->cas_success, LV_READ, pos);
    analyze_operand(node->cas_failure, LV_READ, pos);
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
  if (!sc)
    return;
  for (Scope *child = sc->children; child; child = child->sibling_next)
    scope_warn_unused(child);
  for (Obj *var = sc->locals; var; var = var->next) {
    if (var->first_use >= 0)
      continue;
    if (!var->name || !var->name[0] || var->name[0] == '.')
      continue;
    if (var->is_param)
      continue;
    //stack corruption when variable in macro
    if (var->tok && !var->tok->origin && !(var->tok->file && var->tok->file->is_system_header))
      warn_tok(var->tok, "%s:%d: in %s: unused variable '%s'", __FILE__, __LINE__, __func__, var->name);

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
    //stack corruption when variable in macro
    if (var->tok && !var->tok->origin && !(var->tok->file && var->tok->file->is_system_header))
      warn_tok(var->tok, "%s:%d: in %s: unused parameter '%s'", __FILE__, __LINE__, __func__, var->name);
    
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
  build_bbs(prog);
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    analyze_function(fn);
  }
}
