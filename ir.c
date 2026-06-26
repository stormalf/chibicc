#include "chibicc.h"

static FILE *output_file;
static int ir_reg;

static void emit(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(output_file, fmt, ap);
  va_end(ap);
}

static const char *new_reg(void)
{
  return format("%%_%d", ir_reg++);
}

static void emit_indent(int indent)
{
  for (int i = 0; i < indent; i++)
    emit(" ");
}

static void emit_type_str(Type *ty)
{
  switch (ty->kind)
  {
  case TY_VOID:
    emit("void");
    return;
  case TY_BOOL:
    emit("i1");
    return;
  case TY_CHAR:
    emit("i8");
    return;
  case TY_SHORT:
    emit("i16");
    return;
  case TY_INT:
    emit("i32");
    return;
  case TY_LONG:
    emit("i64");
    return;
  case TY_LLONG:
    emit("i64");
    return;
  case TY_FLOAT:
    emit("float");
    return;
  case TY_DOUBLE:
    emit("double");
    return;
  case TY_PTR:
    emit("ptr");
    return;
  case TY_ARRAY:
    emit("ptr");
    return;
  case TY_STRUCT:
    emit("ptr");
    return;
  case TY_FUNC:
    emit("ptr");
    return;
  case TY_ENUM:
    emit("i32");
    return;
  case TY_VLA:
    emit("ptr");
    return;
  case TY_UNION:
    emit("ptr");
    return;
  case TY_LDOUBLE:
    emit("x86_fp80");
    return;
  case TY_VECTOR:
    emit("<%d x ", ty->vector_size);
    emit_type_str(ty->base);
    emit(">");
    return;
  case TY_INT128:
    emit("i128");
    return;
  default:
    error("emit_type: unknown type kind %d", ty->kind);
  }
}

static void emit_escaped_string(const char *data, int size)
{
  for (int i = 0; i < size; i++)
  {
    unsigned char c = (unsigned char)data[i];
    if (c == '\\')
      emit("\\\\");
    else if (c == '"')
      emit("\\22");
    else if (c == '\n')
      emit("\\0a");
    else if (c == '\r')
      emit("\\0d");
    else if (c == '\t')
      emit("\\09");
    else if (c >= 32 && c < 127)
      emit("%c", c);
    else
      emit("\\%02x", c);
  }
}

static void emit_global(Obj *var)
{
  if (var->alias_name)
    return;
  if (var->is_function || !var->is_definition)
    return;

  emit("@%s = ", var->name);
  if (var->is_tls)
    emit("thread_local ");
  if (var->is_static)
    emit("internal ");
  else
    emit("global ");

  if (var->init_data && !var->rel)
    emit("[%d x i8]", var->ty->size);
  else
    emit_type_str(var->ty);

  if (var->init_data && !var->rel)
  {
    emit(" c\"");
    emit_escaped_string(var->init_data, var->ty->size);
    emit("\"");
  }
  else
  {
    emit(" zeroinitializer");
  }

  emit("\n");
}

static const char *emit_expr(Node *node, int indent);

static const char *var_ptr(Obj *var)
{
  if (var->is_local)
  {
    if (!var->name || !var->name[0])
    {
      static int anon_id = 0;
      char buf[64];
      snprintf(buf, sizeof(buf), ".L.anon.%d", anon_id++);
      var->name = strdup(buf);
    }
    return format("%%_%s.addr", var->name);
  }
  else
  {
    if (var->name)
      return format("@%s", var->name);
    return "@<anon>";
  }
}

static const char *emit_lval(Node *node, int indent)
{
  switch (node->kind)
  {
  case ND_VAR:
  {
    Obj *var = node->var;
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = load ", r);
    emit_type_str(var->ty);
    emit(", ptr %s\n", var_ptr(var));
    return r;
  }
  case ND_DEREF:
  {
    const char *addr = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = load ", r);
    emit_type_str(node->ty);
    emit(", ptr %s\n", addr);
    return r;
  }
  default:
    error_tok(node->tok, "emit_lval: unexpected node kind %d", node->kind);
    return NULL;
  }
}

static int int_type_bits(Type *ty)
{
  switch (ty->kind)
  {
  case TY_BOOL: return 1;
  case TY_CHAR: return 8;
  case TY_SHORT: return 16;
  case TY_INT: case TY_ENUM: return 32;
  case TY_LONG: case TY_LLONG: return 64;
  case TY_INT128: return 128;
  default: return 0;
  }
}

static bool is_float_type(Type *ty)
{
  return ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE || ty->kind == TY_LDOUBLE;
}

static void emit_float_const(const char *reg, Node *node)
{
  if (node->ty->kind == TY_FLOAT)
  {
    union { float f; uint32_t i; } u = { (float)node->fval };
    emit("%s = bitcast i32 %u to float\n", reg, u.i);
  }
  else if (node->ty->kind == TY_DOUBLE)
  {
    union { double f; uint64_t i; } u = { (double)node->fval };
    emit("%s = bitcast i64 %lu to double\n", reg, u.i);
  }
  else
  {
    emit("%s = fadd x86_fp80 0xK3FFF8000000000000000, 0xK3FFF8000000000000000\n", reg);
  }
}

static const char *emit_expr(Node *node, int indent)
{
  if (!node)
    return NULL;

  switch (node->kind)
  {
  case ND_NULL_EXPR:
    return NULL;
  case ND_NUM:
  {
    const char *r = new_reg();
    emit_indent(indent);
    if (node->ty->kind == TY_FLOAT || node->ty->kind == TY_DOUBLE || node->ty->kind == TY_LDOUBLE)
      emit_float_const(r, node);
    else if (node->ty->kind == TY_INT || node->ty->kind == TY_CHAR ||
             node->ty->kind == TY_SHORT || node->ty->kind == TY_BOOL)
      emit("%s = add i32 0, %d", r, (int)node->val);
    else
      emit("%s = add i64 0, %ld", r, node->val);
    emit("\n");
    return r;
  }
  case ND_VAR:
    return emit_lval(node, indent);
case ND_DEREF:
     return emit_lval(node, indent);
   case ND_ASSIGN:
   {
     const char *addr;
     switch (node->lhs->kind)
     {
     case ND_VAR:
     {
       Obj *var = node->lhs->var;
       addr = var_ptr(var);
       break;
     }
     case ND_DEREF:
     {
       addr = emit_expr(node->lhs->lhs, indent);
       break;
     }
     case ND_MEMBER:
     {
       const char *base_ptr = emit_expr(node->lhs->lhs, indent);
       // Convert base_ptr to i8* pointer
       const char *base_ptr_i8 = new_reg();
       emit_indent(indent);
       emit("%s = getelementptr i8, ptr %s, i32 0\n", base_ptr_i8, base_ptr);
       // Now compute the address of the member: base_ptr_i8 + offset
       const char *addr_tmp = new_reg();
       emit_indent(indent);
       emit("%s = getelementptr i8, ptr %s, i32 %d\n", addr_tmp, base_ptr_i8, node->lhs->member->offset);
       addr = addr_tmp;
       break;
     }
     default:
       error_tok(node->tok, "emit_expr ND_ASSIGN: unexpected lhs kind %d", node->lhs->kind);
       addr = NULL;
     }

     const char *val = emit_expr(node->rhs, indent);
     emit_indent(indent);
     emit("store ");
     emit_type_str(node->ty);
     emit(" %s, ptr %s\n", val, addr);
     return val;
   }
  case ND_CAST:
  {
    Type *src = node->lhs->ty;
    Type *dst = node->ty;

    if (dst->kind == TY_VOID)
    {
      emit_expr(node->lhs, indent);
      return NULL;
    }

    if (src == dst)
      return emit_expr(node->lhs, indent);

    int sb = int_type_bits(src);
    int db = int_type_bits(dst);

    if (sb && db)
    {
      const char *val = emit_expr(node->lhs, indent);
      if (sb == db)
        return val;
      const char *r = new_reg();
      emit_indent(indent);
      if (sb < db)
        emit("%s = %s i%d %s to i%d\n", r, src->is_unsigned ? "zext" : "sext", sb, val, db);
      else if (db == 1)
        emit("%s = icmp ne i%d %s, 0\n", r, sb, val);
      else
        emit("%s = trunc i%d %s to i%d\n", r, sb, val, db);
      return r;
    }

    if (sb && is_float_type(dst))
    {
      const char *val = emit_expr(node->lhs, indent);
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = %s i%d %s to ", r, src->is_unsigned ? "uitofp" : "sitofp", sb, val);
      emit_type_str(dst);
      emit("\n");
      return r;
    }

    if (is_float_type(src) && db)
    {
      const char *val = emit_expr(node->lhs, indent);
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = %s ", r, dst->is_unsigned ? "fptoui" : "fptosi");
      emit_type_str(src);
      emit(" %s to i%d\n", val, db);
      return r;
    }

    if (is_float_type(src) && is_float_type(dst))
    {
      const char *val = emit_expr(node->lhs, indent);
      if (src->size == dst->size)
        return val;
      const char *r = new_reg();
      emit_indent(indent);
      if (src->size < dst->size)
      {
        emit("%s = fpext ", r);
        emit_type_str(src);
        emit(" %s to ", val);
      }
      else
      {
        emit("%s = fptrunc ", r);
        emit_type_str(src);
        emit(" %s to ", val);
      }
      emit_type_str(dst);
      emit("\n");
      return r;
    }

    if ((src->kind == TY_PTR || src->kind == TY_ARRAY || src->kind == TY_FUNC || src->kind == TY_VLA) && db)
    {
      const char *val = emit_expr(node->lhs, indent);
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = ptrtoint %s to i%d\n", r, val, db);
      return r;
    }

    if (sb && (dst->kind == TY_PTR || dst->kind == TY_ARRAY || dst->kind == TY_FUNC))
    {
      const char *val = emit_expr(node->lhs, indent);
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = inttoptr i%d %s to ptr\n", r, sb, val);
      return r;
    }

    return emit_expr(node->lhs, indent);
  }
  case ND_ADD:
  case ND_SUB:
  case ND_MUL:
  case ND_DIV:
  case ND_MOD:
  case ND_BITAND:
  case ND_BITOR:
  case ND_BITXOR:
  case ND_SHL:
  case ND_SHR:
  {
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);
    const char *reg = new_reg();
    const char *op;
    switch (node->kind)
    {
    case ND_ADD: op = "add"; break;
    case ND_SUB: op = "sub"; break;
    case ND_MUL: op = "mul"; break;
    case ND_DIV: op = node->ty->is_unsigned ? "udiv" : "sdiv"; break;
    case ND_MOD: op = node->ty->is_unsigned ? "urem" : "srem"; break;
    case ND_BITAND: op = "and"; break;
    case ND_BITOR: op = "or"; break;
    case ND_BITXOR: op = "xor"; break;
    case ND_SHL: op = "shl"; break;
    case ND_SHR: op = node->ty->is_unsigned ? "lshr" : "ashr"; break;
    default: op = "???"; break;
    }
    emit_indent(indent);
    emit("%s = %s ", reg, op);
    emit_type_str(node->ty);
    emit(" %s, %s\n", l, r);
    return reg;
  }
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
  {
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);
    const char *cond;
    switch (node->kind)
    {
    case ND_EQ: cond = "eq"; break;
    case ND_NE: cond = "ne"; break;
    case ND_LT: cond = node->ty->is_unsigned ? "ult" : "slt"; break;
    case ND_LE: cond = node->ty->is_unsigned ? "ule" : "sle"; break;
    default: cond = "???"; break;
    }
    const char *tmp = new_reg();
    emit_indent(indent);
    emit("%s = icmp %s ", tmp, cond);
    emit_type_str(node->lhs->ty);
    emit(" %s, %s\n", l, r);
    const char *reg = new_reg();
    emit_indent(indent);
    emit("%s = zext i1 %s to i32\n", reg, tmp);
    return reg;
  }
  case ND_NEG:
  {
    const char *v = emit_expr(node->lhs, indent);
    const char *reg = new_reg();
    emit_indent(indent);
    emit("%s = sub ", reg);
    emit_type_str(node->ty);
    emit(" 0, %s\n", v);
    return reg;
  }
  case ND_BITNOT:
  {
    const char *v = emit_expr(node->lhs, indent);
    const char *reg = new_reg();
    emit_indent(indent);
    emit("%s = xor ", reg);
    emit_type_str(node->ty);
    emit(" %s, -1\n", v);
    return reg;
  }
  case ND_MEMZERO:
  {
    if (node->lhs && node->lhs->kind == ND_VAR)
    {
      Obj *var = node->lhs->var;
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = add i32 0, 0\n", r);
      emit_indent(indent);
      emit("store i32 0, ptr %s\n", var_ptr(var));
      return r;
    }
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = add i32 0, 0\n", r);
    return r;
  }
  case ND_NOT:
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *zero = new_reg();
    emit_indent(indent);
    emit("%s = icmp eq i32 %s, 0\n", zero, val);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = zext i1 %s to i32\n", r, zero);
    return r;
  }
  case ND_COMMA:
  {
    emit_expr(node->lhs, indent);
    return emit_expr(node->rhs, indent);
  }
  case ND_COND:
  {
    const char *cond_val = emit_expr(node->cond, indent);
    const char *cond_bool;
    if (node->cond->ty->kind == TY_BOOL || node->cond->ty->kind == TY_PTR)
      cond_bool = cond_val;
    else
    {
      cond_bool = new_reg();
      emit_indent(indent);
      emit("%s = icmp ne i32 %s, 0\n", cond_bool, cond_val);
    }

    const char *true_label = format(".L.cond.true.%d", ir_reg++);
    const char *false_label = format(".L.cond.false.%d", ir_reg++);
    const char *merge_label = format(".L.cond.merge.%d", ir_reg++);

    emit_indent(indent);
    emit("br i1 %s, label %%%s, label %%%s\n", cond_bool, true_label, false_label);

    emit("%s:\n", true_label);
    const char *true_val = emit_expr(node->then, indent);
    emit_indent(indent);
    emit("br label %%%s\n", merge_label);

    emit("%s:\n", false_label);
    const char *false_val = emit_expr(node->els, indent);
    emit_indent(indent);
    emit("br label %%%s\n", merge_label);

    emit("%s:\n", merge_label);
    const char *reg = new_reg();
    emit_indent(indent);
    emit("%s = phi ", reg);
    emit_type_str(node->ty);
    emit(" [%s, %%%s], [%s, %%%s]\n", true_val, true_label, false_val, false_label);
    return reg;
  }
  case ND_ADDR:
  {
    if (node->lhs->kind == ND_VAR)
    {
      Obj *var = node->lhs->var;
      return format("%s", var_ptr(var));
    }
    if (node->lhs->kind == ND_DEREF)
      return emit_expr(node->lhs->lhs, indent);
    const char *ptr = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = getelementptr i8, ptr %s, i32 0\n", r, ptr);
    return r;
  }
  case ND_FUNCALL:
  {
    emit_indent(indent);
    const char *reg = new_reg();
    emit("%s = call ", reg);
    emit_type_str(node->ty);
    emit(" @%s(", node->func_ty->name);
    for (Node *arg = node->args; arg; arg = arg->next)
    {
      if (arg != node->args)
        emit(", ");
      const char *v = emit_expr(arg, indent);
      emit_type_str(arg->ty);
      emit(" %s", v);
    }
    emit(")\n");
    return reg;
  }
  case ND_LABEL_VAL:
  {
    error_tok(node->tok, "emit_expr: ND_LABEL_VAL not supported");
    return NULL;
  }
  default:
  {
    emit_indent(indent);
    emit("; UNSUPPORTED: node kind %d\n", node->kind);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = add i32 0, 0\n", r);
    return r;
  }
  }
}

static void emit_stmt(Node *node, int indent, bool *terminated)
{
  if (!node)
    return;

  switch (node->kind)
  {
  case ND_BLOCK:
    for (Node *n = node->body; n; n = n->next)
    {
      emit_stmt(n, indent, terminated);
      if (terminated && *terminated)
        break;
    }
    return;
  case ND_RETURN:
    if (node->lhs)
    {
      const char *val = emit_expr(node->lhs, indent);
      emit_indent(indent);
      emit("ret ");
      emit_type_str(node->lhs->ty);
      emit(" %s\n", val);
    }
    else
    {
      emit_indent(indent);
      emit("ret void\n");
    }
    if (terminated)
      *terminated = true;
    return;
  case ND_EXPR_STMT:
    emit_expr(node->lhs, indent);
    return;
  case ND_NULL_EXPR:
    return;
  case ND_IF:
  {
    const char *cond_val = emit_expr(node->cond, indent);
    const char *cond_bool = new_reg();
    emit_indent(indent);
    emit("%s = icmp ne i32 %s, 0\n", cond_bool, cond_val);
    const char *then_label = format(".L.then.%d", ir_reg++);
    const char *else_label = format(".L.else.%d", ir_reg++);
    const char *end_label = format(".L.end.%d", ir_reg++);
    emit_indent(indent);
    emit("br i1 %s, label %%%s, label %%%s\n", cond_bool, then_label, else_label);
    emit("%s:\n", then_label);
    bool then_terminated = false;
    emit_stmt(node->then, indent, &then_terminated);
    if (!then_terminated)
    {
      emit_indent(indent);
      emit("br label %%%s\n", end_label);
    }
    emit("%s:\n", else_label);
    bool else_terminated = false;
    if (node->els)
      emit_stmt(node->els, indent, &else_terminated);
    if (!else_terminated)
    {
      emit_indent(indent);
      emit("br label %%%s\n", end_label);
    }
    if (!then_terminated || !else_terminated)
      emit("%s:\n", end_label);
    return;
  }
  case ND_LABEL:
    emit("%s:\n", node->unique_label);
    if (node->lhs)
      emit_stmt(node->lhs, indent, terminated);
    return;
  case ND_GOTO:
    emit_indent(indent);
    emit("br label %%%s\n", node->unique_label);
    if (terminated)
      *terminated = true;
    return;
  case ND_FOR:
  {
    const char *begin_label = format(".L.begin.%d", ir_reg++);
    const char *cont_label = format(".L.cont.%d", ir_reg++);
    const char *end_label = format(".L.end.%d", ir_reg++);
    if (node->init)
    {
      bool init_terminated = false;
      emit_stmt(node->init, indent, &init_terminated);
      if (!init_terminated)
      {
        emit_indent(indent);
        emit("br label %%%s\n", begin_label);
      }
    }
    emit("%s:\n", begin_label);
    if (node->cond)
    {
      const char *cond_val = emit_expr(node->cond, indent);
      const char *cond_bool = new_reg();
      emit_indent(indent);
      emit("%s = icmp ne i32 %s, 0\n", cond_bool, cond_val);
      emit_indent(indent);
      emit("br i1 %s, label %%%s, label %%%s\n", cond_bool, cont_label, end_label);
    }
    else
    {
      emit_indent(indent);
      emit("br label %%%s\n", cont_label);
    }
    emit("%s:\n", cont_label);
    bool body_terminated = false;
    emit_stmt(node->then, indent, &body_terminated);
    if (node->inc)
      emit_expr(node->inc, indent);
    if (!body_terminated)
    {
      emit_indent(indent);
      emit("br label %%%s\n", begin_label);
    }
    emit("%s:\n", end_label);
    return;
  }
  case ND_DO:
  {
    const char *begin_label = format(".L.begin.%d", ir_reg++);
    const char *cont_label = format(".L.cont.%d", ir_reg++);
    const char *end_label = format(".L.end.%d", ir_reg++);
    emit("%s:\n", begin_label);
    bool body_terminated = false;
    emit_stmt(node->then, indent, &body_terminated);
    if (body_terminated)
      return;
    emit("%s:\n", cont_label);
    {
      const char *cond_val = emit_expr(node->cond, indent);
      const char *cond_bool = new_reg();
      emit_indent(indent);
      emit("%s = icmp ne i32 %s, 0\n", cond_bool, cond_val);
      emit_indent(indent);
      emit("br i1 %s, label %%%s, label %%%s\n", cond_bool, begin_label, end_label);
    }
    emit("%s:\n", end_label);
    return;
  }
  case ND_SWITCH:
  {
    emit_expr(node->cond, indent);
    for (Node *n = node->case_next; n; n = n->case_next)
    {
      emit_indent(indent);
      emit("; case %ld\n", n->begin);
    }
    if (node->default_case)
    {
      emit_indent(indent);
      emit("; default case at %s\n", node->default_case->label);
    }
    emit_indent(indent);
    emit("br label %%%s\n", node->brk_label);
    emit_stmt(node->then, indent, NULL);
    emit("%s:\n", node->brk_label);
    return;
  }
  case ND_CASE:
    emit("%s:\n", node->label);
    if (node->lhs)
      emit_stmt(node->lhs, indent, terminated);
    return;
  default:
    emit_indent(indent);
    emit("; UNSUPPORTED stmt: node kind %d\n", node->kind);
    return;
  }
}

static bool is_in_param_list(Obj *var, Obj *params)
{
  for (Obj *p = params; p; p = p->next)
    if (p == var)
      return true;
  return false;
}

static void emit_scope_allocas(Scope *sc, Obj *params, int indent)
{
  if (!sc)
    return;
  for (Scope *child = sc->children; child; child = child->sibling_next)
    emit_scope_allocas(child, params, indent);
  for (Obj *var = sc->locals; var; var = var->next)
  {
    if (var->is_function)
      continue;
    if (is_in_param_list(var, params))
      continue;
    emit_indent(indent);
    emit("%s = alloca ", var_ptr(var));
    emit_type_str(var->ty);
    emit("\n");
  }
}

static void emit_func(Obj *fn)
{
  ir_reg = 1;

  if (!fn->is_live)
    return;

  emit("define ");
  emit_type_str(fn->ty->return_ty);
  emit(" @%s(", fn->name);

  Obj *param;
  for (param = fn->params; param; param = param->next)
  {
    if (param != fn->params)
      emit(", ");
    emit_type_str(param->ty);
    emit(" %%%s", param->name);
  }
  emit(") {\n");

  emit_scope_allocas(fn->ty->scopes, fn->params, 2);

  for (param = fn->params; param; param = param->next)
  {
    emit("  %s = alloca ", var_ptr(param));
    emit_type_str(param->ty);
    emit("\n");
  }

  for (param = fn->params; param; param = param->next)
  {
    emit("  store ");
    emit_type_str(param->ty);
    emit(" %%%s, ptr %s\n", param->name, var_ptr(param));
  }

  bool terminated = false;
  emit_stmt(fn->body, 2, &terminated);
  emit("}\n\n");
}

void emit_ir(Obj *prog, FILE *out)
{
  output_file = out;

  emit("; ModuleID = '" PRODUCT "'\n");
  emit("target datalayout = \"" TARGET_DATALAYOUT "\"\n");
  emit("target triple = \"" TARGET_TRIPLE "\"\n");
  emit("\n");

  for (Obj *var = prog; var; var = var->next)
    emit_global(var);

  emit("\n");

  for (Obj *fn = prog; fn; fn = fn->next)
  {
    if (fn->is_function && fn->is_definition)
      emit_func(fn);
  }
}
