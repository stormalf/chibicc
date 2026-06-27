#include "chibicc.h"

static FILE *output_file;
static int ir_reg;
static const char *current_block;

static void emit_stmt(Node *node, int indent, bool *terminated);

#define MAX_OBJ_MAP 4096
static Obj *obj_map[MAX_OBJ_MAP];
static int obj_map_count;

static int obj_id(Obj *var)
{
  for (int i = 0; i < obj_map_count; i++)
    if (obj_map[i] == var)
      return i;
  assert(obj_map_count < MAX_OBJ_MAP);
  obj_map[obj_map_count++] = var;
  return obj_map_count - 1;
}

static void emit(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(output_file, fmt, ap);
  va_end(ap);
}

static void emit_label(const char *label)
{
  current_block = label;
  emit("%s:\n", label);
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

  if (var->init_data && !var->rel)
  {
    emit("constant [%d x i8]", var->ty->size);
    emit(" c\"");
    emit_escaped_string(var->init_data, var->ty->size);
    emit("\"");
  }
  else
  {
    emit("global ");
    emit_type_str(var->ty);
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
    return format("%%_%s.addr_%d", var->name, obj_id(var));
  }
  else
  {
    if (var->name)
      return format("@%s", var->name);
    return "@<anon>";
  }
}

static int load_bits_for_member(Member *mem)
{
  if (mem->ty->kind == TY_BOOL)
    return 8;
  return mem->ty->size * 8;
}

static const char *emit_extract_bitfield(const char *val, Member *mem, int load_bits, int indent)
{
  if (mem->ty->kind == TY_BOOL)
  {
    const char *shifted = new_reg();
    emit_indent(indent);
    emit("%s = lshr i%d %s, %d\n", shifted, load_bits, val, mem->bit_offset);
    const char *masked = new_reg();
    emit_indent(indent);
    emit("%s = and i%d %s, 1\n", masked, load_bits, shifted);
    const char *trunc = new_reg();
    emit_indent(indent);
    emit("%s = trunc i%d %s to i1\n", trunc, load_bits, masked);
    return trunc;
  }

  const char *shifted = new_reg();
  emit_indent(indent);
  emit("%s = lshr i%d %s, %d\n", shifted, load_bits, val, mem->bit_offset);

  uint64_t mask = (mem->bit_width >= 64) ? ~0ULL : ((1ULL << mem->bit_width) - 1);
  const char *masked = new_reg();
  emit_indent(indent);
  emit("%s = and i%d %s, %lu\n", masked, load_bits, shifted, mask);

  if (mem->ty->is_unsigned)
    return masked;

  int shift_amt = load_bits - mem->bit_width;
  const char *shifted_left = new_reg();
  emit_indent(indent);
  emit("%s = shl i%d %s, %d\n", shifted_left, load_bits, masked, shift_amt);
  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = ashr i%d %s, %d\n", result, load_bits, shifted_left, shift_amt);
  return result;
}

static const char *emit_insert_bitfield(const char *container, const char *val, Member *mem, int load_bits, int indent)
{
  uint64_t all_ones = (load_bits == 64) ? ~0ULL : ((1ULL << load_bits) - 1);
  uint64_t width_mask = (mem->bit_width >= 64) ? ~0ULL : ((1ULL << mem->bit_width) - 1);

  const char *val_masked = new_reg();
  emit_indent(indent);
  emit("%s = and i%d %s, %lu\n", val_masked, load_bits, val, width_mask);

  const char *val_shifted = new_reg();
  emit_indent(indent);
  emit("%s = shl i%d %s, %d\n", val_shifted, load_bits, val_masked, mem->bit_offset);

  uint64_t clear_mask = width_mask << mem->bit_offset;
  uint64_t inv_clear_mask = all_ones ^ clear_mask;
  const char *container_cleared = new_reg();
  emit_indent(indent);
  emit("%s = and i%d %s, %lu\n", container_cleared, load_bits, container, inv_clear_mask);

  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = or i%d %s, %s\n", result, load_bits, container_cleared, val_shifted);
  return result;
}

static const char *emit_lval(Node *node, int indent)
{
  switch (node->kind)
  {
  case ND_VAR:
  {
    Obj *var = node->var;

    if (var->ty->kind == TY_ARRAY || var->ty->kind == TY_STRUCT ||
        var->ty->kind == TY_UNION || var->ty->kind == TY_FUNC ||
        var->ty->kind == TY_VLA)
      return var_ptr(var);

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
  case ND_MEMBER:
  {
    const char *base = emit_expr(node->lhs, indent);
    const char *base_i8 = new_reg();
    emit_indent(indent);
    emit("%s = getelementptr i8, ptr %s, i32 0\n", base_i8, base);
    const char *addr = new_reg();
    emit_indent(indent);
    emit("%s = getelementptr i8, ptr %s, i32 %d\n", addr, base_i8, node->member->offset);

    if (node->ty->kind == TY_ARRAY || node->ty->kind == TY_STRUCT ||
        node->ty->kind == TY_UNION || node->ty->kind == TY_FUNC ||
        node->ty->kind == TY_VLA)
      return addr;

    Member *mem = node->member;
    int load_bits = load_bits_for_member(mem);
    const char *r = new_reg();
    if (mem->is_bitfield && mem->ty->kind == TY_BOOL)
    {
      emit_indent(indent);
      emit("%s = load i8, ptr %s\n", r, addr);
    }
    else
    {
      emit_indent(indent);
      emit("%s = load ", r);
      emit_type_str(node->ty);
      emit(", ptr %s\n", addr);
    }

    if (mem->is_bitfield)
      return emit_extract_bitfield(r, mem, load_bits, indent);
    return r;
  }
  case ND_VLA_PTR:
  {
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = load ptr, ptr %s\n", r, var_ptr(node->var));
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

static const char *emit_to_bool(const char *val, Type *ty, int indent)
{
  if (ty->kind == TY_BOOL)
    return val;
  const char *r = new_reg();
  emit_indent(indent);
  if (is_float_type(ty))
  {
    emit("%s = fcmp une ", r);
    emit_type_str(ty);
    emit(" %s, 0.0\n", val);
  }
  else
  {
    emit("%s = icmp ne ", r);
    emit_type_str(ty);
    emit(" %s, 0\n", val);
  }
  return r;
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
    else if (node->ty->kind == TY_INT128)
      emit("%s = add i128 0, %ld", r, (long)node->val);
    else
      emit("%s = add i64 0, %ld", r, node->val);
    emit("\n");
    return r;
  }
  case ND_VAR:
  case ND_MEMBER:
    return emit_lval(node, indent);
  case ND_DEREF:
  case ND_VLA_PTR:
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
      case ND_VLA_PTR:
      {
        addr = var_ptr(node->lhs->var);
        break;
      }
      case ND_MEMBER:
      {
        Member *lhs_mem = node->lhs->member;
        const char *base_ptr = emit_expr(node->lhs->lhs, indent);
        const char *base_ptr_i8 = new_reg();
        emit_indent(indent);
        emit("%s = getelementptr i8, ptr %s, i32 0\n", base_ptr_i8, base_ptr);
        const char *addr_tmp = new_reg();
        emit_indent(indent);
        emit("%s = getelementptr i8, ptr %s, i32 %d\n", addr_tmp, base_ptr_i8, node->lhs->member->offset);
        addr = addr_tmp;

        if (lhs_mem->is_bitfield)
        {
          int load_bits = load_bits_for_member(lhs_mem);
          const char *val = emit_expr(node->rhs, indent);
          int val_bits = int_type_bits(node->rhs->ty);
          const char *val_trunc = val;
          if (val_bits > 0 && val_bits != load_bits)
          {
            val_trunc = new_reg();
            emit_indent(indent);
            if (val_bits > load_bits)
              emit("%s = trunc i%d %s to i%d\n", val_trunc, val_bits, val, load_bits);
            else
              emit("%s = zext i%d %s to i%d\n", val_trunc, val_bits, val, load_bits);
          }
          const char *container;
          if (lhs_mem->ty->kind == TY_BOOL)
          {
            container = new_reg();
            emit_indent(indent);
            emit("%s = load i8, ptr %s\n", container, addr);
          }
          else
          {
            container = new_reg();
            emit_indent(indent);
            emit("%s = load ", container);
            emit_type_str(node->ty);
            emit(", ptr %s\n", addr);
          }
          const char *new_container = emit_insert_bitfield(container, val_trunc, lhs_mem, load_bits, indent);
          emit_indent(indent);
          if (lhs_mem->ty->kind == TY_BOOL)
            emit("store i8 %s, ptr %s\n", new_container, addr);
          else
          {
            emit("store ");
            emit_type_str(node->ty);
            emit(" %s, ptr %s\n", new_container, addr);
          }
          return val;
        }
        break;
      }
     default:
       error_tok(node->tok, "emit_expr ND_ASSIGN: unexpected lhs kind %d", node->lhs->kind);
       addr = NULL;
     }

      const char *val = emit_expr(node->rhs, indent);
      emit_indent(indent);
      if (addr && strstr(addr, "L.anon.28"))
        fprintf(stderr, "DEBUG_STORE: val=%s addr=%s ty_kind=%d lhs_kind=%d rhs_kind=%d rhs_is_var=%d rhs_var_name=%s\n", val, addr, node->ty->kind, node->lhs->kind, node->rhs ? node->rhs->kind : -1, node->rhs && node->rhs->kind == ND_VAR && node->rhs->var ? 1 : 0, node->rhs && node->rhs->kind == ND_VAR && node->rhs->var ? (node->rhs->var->name ? node->rhs->var->name : "null") : "n/a");
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
      emit("%s = ptrtoint ptr %s to i%d\n", r, val, db);
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
    if ((node->kind == ND_ADD || node->kind == ND_SUB) &&
        (node->ty->kind == TY_PTR || node->ty->kind == TY_VLA))
    {
      const char *l = emit_expr(node->lhs, indent);
      const char *r = emit_expr(node->rhs, indent);
      const char *r_int = r;
      if (node->rhs->ty->kind == TY_PTR || node->rhs->ty->kind == TY_VLA ||
          node->rhs->ty->kind == TY_ARRAY)
      {
        r_int = new_reg();
        emit_indent(indent);
        emit("%s = ptrtoint ptr %s to i64\n", r_int, r);
      }
      const char *reg = new_reg();
      emit_indent(indent);
      emit("%s = getelementptr i8, ptr %s, i64 %s%s\n",
           reg, l, node->kind == ND_SUB ? "-" : "", r_int);
      return reg;
    }
    if (node->kind == ND_ADD &&
        (node->lhs->ty->kind == TY_PTR || node->lhs->ty->kind == TY_VLA))
    {
      const char *l = emit_expr(node->lhs, indent);
      const char *r = emit_expr(node->rhs, indent);
      const char *reg = new_reg();
      emit_indent(indent);
      emit("%s = getelementptr i8, ptr %s, i64 %s\n", reg, l, r);
      return reg;
    }
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);
    const char *reg = new_reg();
    emit_indent(indent);
    if (is_float_type(node->ty))
    {
      const char *op;
      switch (node->kind)
      {
      case ND_ADD: op = "fadd"; break;
      case ND_SUB: op = "fsub"; break;
      case ND_MUL: op = "fmul"; break;
      case ND_DIV: op = "fdiv"; break;
      default: op = "???"; break;
      }
      emit("%s = %s ", reg, op);
      emit_type_str(node->ty);
      emit(" %s, %s\n", l, r);
    }
    else
    {
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
      const char *r_op = r;
      if (node->kind == ND_SHL || node->kind == ND_SHR)
      {
        int lhs_bits = int_type_bits(node->lhs->ty);
        int rhs_bits = int_type_bits(node->rhs->ty);
        if (lhs_bits > 0 && rhs_bits > 0 && lhs_bits != rhs_bits)
        {
          const char *r_ext = new_reg();
          emit_indent(indent);
          if (rhs_bits < lhs_bits)
            emit("%s = zext i%d %s to i%d\n", r_ext, rhs_bits, r, lhs_bits);
          else
            emit("%s = trunc i%d %s to i%d\n", r_ext, rhs_bits, r, lhs_bits);
          r_op = r_ext;
        }
      }
      emit("%s = %s ", reg, op);
      emit_type_str(node->ty);
      emit(" %s, %s\n", l, r_op);
    }
    return reg;
  }
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
  {
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);
    const char *tmp = new_reg();
    emit_indent(indent);
    if (is_float_type(node->lhs->ty))
    {
      const char *cond;
      switch (node->kind)
      {
      case ND_EQ: cond = "oeq"; break;
      case ND_NE: cond = "une"; break;
      case ND_LT: cond = "olt"; break;
      case ND_LE: cond = "ole"; break;
      default: cond = "???"; break;
      }
      emit("%s = fcmp %s ", tmp, cond);
      emit_type_str(node->lhs->ty);
      emit(" %s, %s\n", l, r);
    }
    else
    {
      const char *cond;
      switch (node->kind)
      {
      case ND_EQ: cond = "eq"; break;
      case ND_NE: cond = "ne"; break;
      case ND_LT: cond = node->ty->is_unsigned ? "ult" : "slt"; break;
      case ND_LE: cond = node->ty->is_unsigned ? "ule" : "sle"; break;
      default: cond = "???"; break;
      }
      emit("%s = icmp %s ", tmp, cond);
      emit_type_str(node->lhs->ty);
      emit(" %s, %s\n", l, r);
    }
    const char *reg = new_reg();
    emit_indent(indent);
    emit("%s = zext i1 %s to i32\n", reg, tmp);
    return reg;
  }
  case ND_LOGAND:
  case ND_LOGOR:
  {
    int id = ir_reg++;
    const char *entry_label = format(".L.log.entry.%d", id);
    const char *rhs_label = format(".L.log.rhs.%d", id);
    const char *end_label = format(".L.log.end.%d", id);

    emit_indent(indent);
    emit("br label %%%s\n", entry_label);
    emit("%s:\n", entry_label);
    const char *l_bool = emit_to_bool(emit_expr(node->lhs, indent), node->lhs->ty, indent);

    if (node->kind == ND_LOGAND)
    {
      emit_indent(indent);
      emit("br i1 %s, label %%%s, label %%%s\n", l_bool, rhs_label, end_label);
    }
    else
    {
      emit_indent(indent);
      emit("br i1 %s, label %%%s, label %%%s\n", l_bool, end_label, rhs_label);
    }

    emit("%s:\n", rhs_label);
    const char *r_bool = emit_to_bool(emit_expr(node->rhs, indent), node->rhs->ty, indent);
    emit_indent(indent);
    emit("br label %%%s\n", end_label);

    emit("%s:\n", end_label);
    const char *result = new_reg();
    emit_indent(indent);
    const char *entry_result = (node->kind == ND_LOGAND) ? "false" : "true";
    emit("%s = phi i1 [ %s, %%%s ], [ %s, %%%s ]\n",
         result, entry_result, entry_label, r_bool, rhs_label);

    const char *final = new_reg();
    emit_indent(indent);
    emit("%s = zext i1 %s to i32\n", final, result);
    return final;
  }
  case ND_NEG:
  {
    const char *v = emit_expr(node->lhs, indent);
    const char *reg = new_reg();
    emit_indent(indent);
    if (is_float_type(node->ty))
      emit("%s = fneg ", reg);
    else
      emit("%s = sub ", reg);
    emit_type_str(node->ty);
    if (is_float_type(node->ty))
      emit(" %s\n", v);
    else
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
    if (node->ty->kind == TY_VOID)
      return NULL;
    if (node->lhs && node->lhs->kind == ND_VAR)
    {
      Obj *var = node->lhs->var;
      const char *r = new_reg();
      emit_indent(indent);
      if (node->ty->kind == TY_PTR || node->ty->kind == TY_ARRAY ||
          node->ty->kind == TY_FUNC || node->ty->kind == TY_VLA ||
          node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION)
      {
        emit("%s = inttoptr i32 0 to ", r);
        emit_type_str(node->ty);
        emit("\n");
      }
      else
      {
        emit("%s = %s ", r, is_float_type(node->ty) ? "fadd" : "add");
        emit_type_str(node->ty);
        if (is_float_type(node->ty))
          emit(" 0.0, 0.0");
        else
          emit(" 0, 0");
        emit("\n");
      }
      emit_indent(indent);
      emit("store i32 0, ptr %s\n", var_ptr(var));
      return r;
    }
    const char *r = new_reg();
    emit_indent(indent);
    if (node->ty->kind == TY_PTR || node->ty->kind == TY_ARRAY ||
        node->ty->kind == TY_FUNC || node->ty->kind == TY_VLA ||
        node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION)
    {
      emit("%s = inttoptr i32 0 to ", r);
      emit_type_str(node->ty);
      emit("\n");
    }
    else
    {
      emit("%s = %s ", r, is_float_type(node->ty) ? "fadd" : "add");
      emit_type_str(node->ty);
      if (is_float_type(node->ty))
        emit(" 0.0, 0.0");
      else
        emit(" 0, 0");
      emit("\n");
    }
    return r;
  }
  case ND_NOT:
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *zero = new_reg();
    emit_indent(indent);
    if (is_float_type(node->lhs->ty))
    {
      emit("%s = fcmp oeq ", zero);
      emit_type_str(node->lhs->ty);
      emit(" %s, 0.0\n", val);
    }
    else
    {
      emit("%s = icmp eq ", zero);
      emit_type_str(node->lhs->ty);
      emit(" %s, 0\n", val);
    }
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

    emit_label(true_label);
    const char *true_val = emit_expr(node->then, indent);
    const char *true_pred = current_block ? current_block : true_label;
    emit_indent(indent);
    emit("br label %%%s\n", merge_label);
    current_block = NULL;

    emit_label(false_label);
    const char *false_val = emit_expr(node->els, indent);
    const char *false_pred = current_block ? current_block : false_label;
    emit_indent(indent);
    emit("br label %%%s\n", merge_label);
    current_block = NULL;

    if (node->ty->kind == TY_VOID)
      return NULL;

    emit_label(merge_label);
    const char *reg = new_reg();
    emit_indent(indent);
    emit("%s = phi ", reg);
    emit_type_str(node->ty);
    emit(" [%s, %%%s], [%s, %%%s]\n",
         true_val ? true_val : "0", true_pred,
         false_val ? false_val : "0", false_pred);
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
    bool is_direct = (node->lhs && node->lhs->kind == ND_VAR && node->lhs->var &&
                      node->lhs->var->ty->kind == TY_FUNC);

    if (is_direct && (!strcmp(node->lhs->var->name, "alloca") ||
                      !strcmp(node->lhs->var->name, "__builtin_alloca")))
    {
      Node *arg = node->args;
      const char *size = emit_expr(arg, indent);
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = alloca i8, i64 %s\n", r, size);
      return r;
    }

    const char *callee_str;
    if (is_direct)
      callee_str = format("@%s", node->lhs->var->name);
    else
      callee_str = emit_expr(node->lhs, indent);

    int n = 0;
    for (Node *arg = node->args; arg; arg = arg->next)
      n++;
    const char **arg_regs = NULL;
    Type **arg_tys = NULL;
    if (n > 0)
    {
      arg_regs = (const char **)calloc((size_t)n, sizeof(const char *));
      arg_tys = (Type **)calloc((size_t)n, sizeof(Type *));
      int i = 0;
      for (Node *arg = node->args; arg; arg = arg->next)
      {
        arg_regs[i] = emit_expr(arg, indent);
        arg_tys[i] = arg->ty;
        i++;
      }
    }

    const char *reg = new_reg();
    emit_indent(indent);
    if (node->ty->kind == TY_VOID)
      emit("call ");
    else
      emit("%s = call ", reg);
    emit_type_str(node->ty);
    emit(" %s(", callee_str);
    for (int i = 0; i < n; i++)
    {
      if (i > 0)
        emit(", ");
      emit_type_str(arg_tys[i]);
      emit(" %s", arg_regs[i]);
    }
    emit(")\n");

    if (arg_regs)
      free(arg_regs);
    if (arg_tys)
      free(arg_tys);
    return reg;
  }
  case ND_STMT_EXPR:
  {
    Node *last = NULL;
    for (Node *n = node->body; n; n = n->next)
    {
      if (!n->next)
        last = n;
      bool term = false;
      emit_stmt(n, indent, &term);
      if (term)
        break;
    }
    if (last && last->kind == ND_EXPR_STMT)
      return emit_expr(last->lhs, indent);
    return NULL;
  }
  case ND_ALLOC:
  {
    const char *size = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = alloca i8, i64 %s\n", r, size);
    return r;
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
    if (node->ty->kind == TY_VOID)
      return NULL;
    const char *r = new_reg();
    emit_indent(indent);
    if (node->ty->kind == TY_PTR || node->ty->kind == TY_ARRAY ||
        node->ty->kind == TY_FUNC || node->ty->kind == TY_VLA ||
        node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION)
    {
      emit("%s = inttoptr i32 0 to ", r);
      emit_type_str(node->ty);
      emit("\n");
    }
    else
    {
      emit("%s = %s ", r, is_float_type(node->ty) ? "fadd" : "add");
      emit_type_str(node->ty);
      if (is_float_type(node->ty))
        emit(" 0.0, 0.0");
      else
        emit(" 0, 0");
      emit("\n");
    }
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
    const char *cond_bool;
    if (node->cond->ty->kind == TY_BOOL)
      cond_bool = cond_val;
    else
    {
      cond_bool = new_reg();
      emit_indent(indent);
      emit("%s = icmp ne i32 %s, 0\n", cond_bool, cond_val);
    }
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
      const char *cond_bool;
      if (node->cond->ty->kind == TY_BOOL)
        cond_bool = cond_val;
      else
      {
        cond_bool = new_reg();
        emit_indent(indent);
        emit("%s = icmp ne i32 %s, 0\n", cond_bool, cond_val);
      }
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
      const char *cond_bool;
      if (node->cond->ty->kind == TY_BOOL)
        cond_bool = cond_val;
      else
      {
        cond_bool = new_reg();
        emit_indent(indent);
        emit("%s = icmp ne i32 %s, 0\n", cond_bool, cond_val);
      }
      emit_indent(indent);
      emit("br i1 %s, label %%%s, label %%%s\n", cond_bool, begin_label, end_label);
    }
    emit("%s:\n", end_label);
    return;
  }
  case ND_SWITCH:
  {
    const char *cond_val = emit_expr(node->cond, indent);
    emit_indent(indent);
    if (node->default_case)
      emit("switch i32 %s, label %%%s [\n", cond_val, node->default_case->label);
    else
      emit("switch i32 %s, label %%%s [\n", cond_val, node->brk_label);
    for (Node *n = node->case_next; n; n = n->case_next)
    {
      emit_indent(indent + 2);
      for (long v = n->begin; v <= n->end; v++)
        emit("    i32 %ld, label %%%s\n", v, n->label);
    }
    emit_indent(indent);
    emit("  ]\n");
    emit_stmt(node->then, indent, NULL);
    emit("%s:\n", node->brk_label);
    emit_indent(indent);
    emit("unreachable\n");
    return;
  }
  case ND_CASE:
    emit("%s:\n", node->label);
    if (node->lhs)
      emit_stmt(node->lhs, indent, terminated);
    return;
  case ND_ASM:
  {
    char *s = subst_fp_placeholder(node->asm_str, "%rbp");
    emit_indent(indent);
    emit("call void asm sideeffect \"%s\", \"\"()\n", s);
    return;
  }
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
    const char *pname = param->name && param->name[0] ? param->name : format("_p%d", obj_id(param));
    emit(" %%%s", pname);
  }
  emit(") {\n");

  emit_scope_allocas(fn->ty->scopes, fn->params, 2);

  for (param = fn->params; param; param = param->next)
  {
    if (!param->name || !param->name[0])
      continue;
    emit("  %s = alloca ", var_ptr(param));
    emit_type_str(param->ty);
    emit("\n");
  }

  for (param = fn->params; param; param = param->next)
  {
    if (!param->name || !param->name[0])
      continue;
    emit("  store ");
    emit_type_str(param->ty);
    const char *pname = param->name && param->name[0] ? param->name : format("_p%d", obj_id(param));
    emit(" %%%s, ptr %s\n", pname, var_ptr(param));
  }

  bool terminated = false;
  emit_stmt(fn->body, 2, &terminated);
  if (!terminated)
  {
    if (fn->ty->return_ty->kind == TY_VOID)
      emit("ret void\n");
    else
      emit("unreachable\n");
  }
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
    if (fn->is_function)
    {
      if (!fn->is_definition && fn->ty && fn->ty->kind == TY_FUNC)
      {
        emit("declare ");
        emit_type_str(fn->ty->return_ty);
        emit(" @%s(", fn->name);
        Obj *param;
        for (param = fn->params; param; param = param->next)
        {
          if (param != fn->params)
            emit(", ");
          emit_type_str(param->ty);
        }
        if (fn->ty->is_variadic)
        {
          if (fn->params)
            emit(", ");
          emit("...");
        }
        emit(")\n");
      }
      else if (fn->is_definition)
        emit_func(fn);
    }
  }
}
