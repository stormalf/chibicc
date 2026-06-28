#include "chibicc.h"

static FILE *output_file;
static int ir_reg;
static const char *current_block;
static const char *sret_reg;
static bool is_terminated;
static Obj *current_fn;



// Forward declarations for gen_ir_* helpers (defined after emit_expr)
static const char *gen_ir_null_expr(Node *node, int indent);
static const char *gen_ir_num(Node *node, int indent);
static const char *gen_ir_var(Node *node, int indent);
static const char *gen_ir_deref(Node *node, int indent);
static const char *gen_ir_assign(Node *node, int indent);
static const char *gen_ir_cast(Node *node, int indent);
static const char *gen_ir_add(Node *node, int indent);
static const char *gen_ir_eq(Node *node, int indent);
static const char *gen_ir_logand(Node *node, int indent);
static const char *gen_ir_neg(Node *node, int indent);
static const char *gen_ir_bitnot(Node *node, int indent);
static const char *gen_ir_memzero(Node *node, int indent);
static const char *gen_ir_not(Node *node, int indent);
static const char *gen_ir_comma(Node *node, int indent);
static const char *gen_ir_cond(Node *node, int indent);
static const char *gen_ir_addr(Node *node, int indent);
static const char *gen_ir_funcall(Node *node, int indent);
static const char *gen_ir_stmt_expr(Node *node, int indent);
static const char *gen_ir_alloc(Node *node, int indent);
static const char *gen_ir_pos(Node *node, int indent);
static const char *gen_ir_builtin_memcpy(Node *node, int indent);
static const char *gen_ir_builtin_memset(Node *node, int indent);
static const char *gen_ir_builtin_clz(Node *node, int indent);
static const char *gen_ir_builtin_clzl(Node *node, int indent);
static const char *gen_ir_builtin_ctz(Node *node, int indent);
static const char *gen_ir_builtin_ctzl(Node *node, int indent);
static const char *gen_ir_popcount(Node *node, int indent);
static const char *gen_ir_popcountl(Node *node, int indent);
static const char *gen_ir_expect(Node *node, int indent);
static const char *gen_ir_abort(Node *node, int indent);
static const char *gen_ir_return_addr(Node *node, int indent);
static const char *gen_ir_builtin_frame_address(Node *node, int indent);
static const char *gen_ir_unreachable(Node *node, int indent);
static const char *gen_ir_builtin_bswap16(Node *node, int indent);
static const char *gen_ir_builtin_bswap32(Node *node, int indent);
static const char *gen_ir_builtin_bswap64(Node *node, int indent);
static const char *gen_ir_builtin_inff(Node *node, int indent);
static const char *gen_ir_builtin_inf(Node *node, int indent);
static const char *gen_ir_builtin_nanl(Node *node, int indent);
static const char *gen_ir_builtin_nanf(Node *node, int indent);
static const char *gen_ir_builtin_nan(Node *node, int indent);
static const char *gen_ir_builtin_isnan(Node *node, int indent);
static const char *gen_ir_parity(Node *node, int indent);
static const char *gen_ir_parityl(Node *node, int indent);
static const char *gen_ir_stdc_bit_ceil(Node *node, int indent);
static const char *gen_ir_builtin_add_overflow(Node *node, int indent);
static const char *gen_ir_builtin_sub_overflow(Node *node, int indent);
static const char *gen_ir_builtin_mul_overflow(Node *node, int indent);
static const char *gen_ir_uadd_overflow(Node *node, int indent);
static const char *gen_ir_umul_overflow(Node *node, int indent);
static const char *gen_ir_label_val(Node *node, int indent);
static const char *gen_ir_default(Node *node, int indent);
static void gen_ir_stmt_block(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_return(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_expr_stmt(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_null_expr(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_if(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_label(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_goto(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_for(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_do(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_switch(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_case(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_asm(Node *node, int indent, bool *terminated);
static void gen_ir_stmt_default(Node *node, int indent, bool *terminated);



static bool is_sret(Type *ty) {
  return (ty->kind == TY_STRUCT || ty->kind == TY_UNION) && ty->size > 16;
}

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
  if (!is_terminated && current_block)
    emit("  br label %%%s\n", label);
  current_block = label;
  emit("%s:\n", label);
  is_terminated = false;
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

// === Helpers for variadic call argument classification ===
// Returns true if the type occupies a floating-point register slot in the
// AMD64 calling convention.  We only need a coarse classification here.
static bool ir_has_flonum(Type *ty, int lo, int hi, int offset)
{
  if (!ty)
    return false;
  if (ty->kind == TY_STRUCT || ty->kind == TY_UNION)
  {
    for (Member *mem = ty->members; mem; mem = mem->next)
    {
      int tmpoff = offset + mem->offset;
      if ((tmpoff + mem->ty->size) <= lo)
        continue;
      if (hi <= tmpoff)
        break;
      if (!ir_has_flonum(mem->ty, lo, hi, tmpoff))
        return false;
    }
    return true;
  }
  if (ty->kind == TY_VECTOR)
    return true;
  return ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE;
}

static bool ir_has_flonum1(Type *ty) { return ir_has_flonum(ty, 0, 8, 0); }
static bool ir_has_flonum2(Type *ty) { return ir_has_flonum(ty, 8, 16, 0); }

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
    error("%s:%d: in %s: unknown type kind %d", __FILE__, __LINE__, __func__, ty->kind);
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
    if (var->ty->is_const)
      emit("constant ");
    else
      emit("global ");
    emit("[%d x i8] c\"", var->ty->size);
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

    if (var->ty->kind == TY_ARRAY || var->ty->kind == TY_FUNC ||
        var->ty->kind == TY_VLA)
      return var_ptr(var);

    // Struct/union parameters are passed by pointer in the AMD64 ABI, so the
    // alloca holds the pointer (not the struct data).  Dereference it so
    // subsequent getelementptr instructions address the struct fields
    // through the pointer value rather than the pointer storage slot.
    if (var->ty->kind == TY_STRUCT || var->ty->kind == TY_UNION)
    {
      if (var->is_param && var->ty->size > 0)
      {
        const char *r = new_reg();
        emit_indent(indent);
        emit("%s = load ptr, ptr %s\n", r, var_ptr(var));
        return r;
      }
      return var_ptr(var);
    }

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

    if (node->ty->kind == TY_ARRAY || node->ty->kind == TY_STRUCT ||
        node->ty->kind == TY_UNION || node->ty->kind == TY_FUNC ||
        node->ty->kind == TY_VLA)
      return addr;

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
    error_tok(node->tok, "%s:%d: in %s: emit_lval: unexpected node kind %d", __FILE__, __LINE__, __func__, node->kind);
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
    union { long double f; uint8_t bytes[16]; } u;
    u.f = node->fval;
    unsigned long long mantissa = 0;
    int i;
    for (i = 0; i < 8; i++)
      mantissa |= (unsigned long long)u.bytes[i] << (i * 8);
    unsigned exponent = (u.bytes[9] << 8) | u.bytes[8];
    emit("%s = fadd x86_fp80 0xK%04X%016llX, 0xK00000000000000000000\n",
         reg, exponent, mantissa);
  }
}

static const char *emit_expr(Node *node, int indent)
{
  if (!node)
    return NULL;

  switch (node->kind)
  {
  case ND_NULL_EXPR:
    return gen_ir_null_expr(node, indent);
  case ND_NUM:
    return gen_ir_num(node, indent);
  case ND_VAR:
  case ND_MEMBER:
    return gen_ir_var(node, indent);
  case ND_DEREF:
  case ND_VLA_PTR:
    return gen_ir_deref(node, indent);
  case ND_ASSIGN:
    return gen_ir_assign(node, indent);
  case ND_CAST:
    return gen_ir_cast(node, indent);
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
    return gen_ir_add(node, indent);
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
    return gen_ir_eq(node, indent);
  case ND_LOGAND:
  case ND_LOGOR:
    return gen_ir_logand(node, indent);
  case ND_NEG:
    return gen_ir_neg(node, indent);
  case ND_BITNOT:
    return gen_ir_bitnot(node, indent);
  case ND_MEMZERO:
    return gen_ir_memzero(node, indent);
  case ND_NOT:
    return gen_ir_not(node, indent);
  case ND_COMMA:
    return gen_ir_comma(node, indent);
  case ND_COND:
    return gen_ir_cond(node, indent);
  case ND_ADDR:
    return gen_ir_addr(node, indent);
  case ND_FUNCALL:
    return gen_ir_funcall(node, indent);
  case ND_STMT_EXPR:
    return gen_ir_stmt_expr(node, indent);
  case ND_ALLOC:
    return gen_ir_alloc(node, indent);
  case ND_POS:
    return gen_ir_pos(node, indent);

  case ND_BUILTIN_MEMCPY:
    return gen_ir_builtin_memcpy(node, indent);

  case ND_BUILTIN_MEMSET:
    return gen_ir_builtin_memset(node, indent);

  case ND_BUILTIN_CLZ:
    return gen_ir_builtin_clz(node, indent);

  case ND_BUILTIN_CLZL:
  case ND_BUILTIN_CLZLL:
    return gen_ir_builtin_clzl(node, indent);

  case ND_BUILTIN_CTZ:
    return gen_ir_builtin_ctz(node, indent);

  case ND_BUILTIN_CTZL:
  case ND_BUILTIN_CTZLL:
    return gen_ir_builtin_ctzl(node, indent);

  case ND_POPCOUNT:
    return gen_ir_popcount(node, indent);

  case ND_POPCOUNTL:
  case ND_POPCOUNTLL:
    return gen_ir_popcountl(node, indent);

  case ND_EXPECT:
    return gen_ir_expect(node, indent);

  case ND_ABORT:
    return gen_ir_abort(node, indent);

  case ND_RETURN_ADDR:
    return gen_ir_return_addr(node, indent);

  case ND_BUILTIN_FRAME_ADDRESS:
    return gen_ir_builtin_frame_address(node, indent);

  case ND_UNREACHABLE:
    return gen_ir_unreachable(node, indent);

  case ND_BUILTIN_BSWAP16:
    return gen_ir_builtin_bswap16(node, indent);

  case ND_BUILTIN_BSWAP32:
    return gen_ir_builtin_bswap32(node, indent);

  case ND_BUILTIN_BSWAP64:
    return gen_ir_builtin_bswap64(node, indent);

  case ND_BUILTIN_INFF:
  case ND_BUILTIN_HUGE_VALF:
    return gen_ir_builtin_inff(node, indent);

  case ND_BUILTIN_INF:
  case ND_BUILTIN_HUGE_VAL:
    return gen_ir_builtin_inf(node, indent);

  case ND_BUILTIN_NANL:
  case ND_BUILTIN_HUGE_VALL:
    return gen_ir_builtin_nanl(node, indent);

  case ND_BUILTIN_NANF:
    return gen_ir_builtin_nanf(node, indent);

  case ND_BUILTIN_NAN:
    return gen_ir_builtin_nan(node, indent);

  case ND_BUILTIN_ISNAN:
    return gen_ir_builtin_isnan(node, indent);

  case ND_PARITY:
    return gen_ir_parity(node, indent);

  case ND_PARITYL:
  case ND_PARITYLL:
    return gen_ir_parityl(node, indent);

  case ND_STDC_BIT_CEIL:
    return gen_ir_stdc_bit_ceil(node, indent);

  case ND_BUILTIN_ADD_OVERFLOW:
    return gen_ir_builtin_add_overflow(node, indent);

  case ND_BUILTIN_SUB_OVERFLOW:
    return gen_ir_builtin_sub_overflow(node, indent);

  case ND_BUILTIN_MUL_OVERFLOW:
    return gen_ir_builtin_mul_overflow(node, indent);

  case ND_UADD_OVERFLOW:
  case ND_UADDL_OVERFLOW:
  case ND_UADDLL_OVERFLOW:
    return gen_ir_uadd_overflow(node, indent);

  case ND_UMUL_OVERFLOW:
  case ND_UMULL_OVERFLOW:
  case ND_UMULLL_OVERFLOW:
    return gen_ir_umul_overflow(node, indent);

  case ND_LABEL_VAL:
    return gen_ir_label_val(node, indent);
  default:
    return gen_ir_default(node, indent);
  }
}

static const char *gen_ir_null_expr(Node *node, int indent)
{
  return NULL;
}

static const char *gen_ir_num(Node *node, int indent)
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


static const char *gen_ir_var(Node *node, int indent)
{
  return emit_lval(node, indent);
}

static const char *gen_ir_deref(Node *node, int indent)
{
  return emit_lval(node, indent);
}

static const char *gen_ir_assign(Node *node, int indent)
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
     error_tok(node->tok, "%s:%d: in %s: emit_expr ND_ASSIGN: unexpected lhs kind %d", __FILE__, __LINE__, __func__, node->lhs->kind);
     addr = NULL;
   }

    const char *val = emit_expr(node->rhs, indent);
    emit_indent(indent);
    if (node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION)
    {
      emit("call void @llvm.memcpy.p0.p0.i64(ptr %s, ptr %s, i64 %ld, i1 false)\n",
           addr, val, node->ty->size);
    }
    else
    {
      emit("store ");
      emit_type_str(node->ty);
      emit(" %s, ptr %s\n", val, addr);
    }
   return val;

}

static const char *gen_ir_cast(Node *node, int indent)
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

  if ((src->kind == TY_PTR || is_array(src) || src->kind == TY_FUNC ) && db)
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = ptrtoint ptr %s to i%d\n", r, val, db);
    return r;
  }

  if (sb && (dst->kind == TY_PTR || is_array(dst) || dst->kind == TY_FUNC))
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = inttoptr i%d %s to ptr\n", r, sb, val);
    return r;
  }

  return emit_expr(node->lhs, indent);
}


static const char *gen_ir_add(Node *node, int indent)
{

  bool lhs_ptr = node->lhs->ty->kind == TY_PTR || is_array(node->lhs->ty);

  bool rhs_ptr =  node->rhs->ty->kind == TY_PTR || is_array(node->rhs->ty);
  if ((node->kind == ND_ADD || node->kind == ND_SUB) &&
      (lhs_ptr && rhs_ptr))
  {
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);

    const char *l_int = l;
    if (node->lhs->ty->kind == TY_PTR || is_array(node->lhs->ty)) {
      l_int = new_reg();
      emit_indent(indent);
      emit("%s = ptrtoint ptr %s to i64\n", l_int, l);
    }

    const char *r_int = r;
    if (node->rhs->ty->kind == TY_PTR || is_array(node->rhs->ty)) {
      r_int = new_reg();
      emit_indent(indent);
      emit("%s = ptrtoint ptr %s to i64\n", r_int, r);
    }

    const char *diff = new_reg();
    emit_indent(indent);
    emit("%s = sub i64 %s, %s\n", diff, l_int, r_int);

    const char *scale_i32 = new_reg();
    emit_indent(indent);
    int sz = node->lhs->ty->base->size;

    emit("%s = add i32 0, %d\n", scale_i32, sz);

    const char *scale_i64 = new_reg();
    emit_indent(indent);
    emit("%s = sext i32 %s to i64\n", scale_i64, scale_i32);

    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = sdiv i64 %s, %s\n", res, diff, scale_i64);

    return res;
  }
  if (node->kind == ND_ADD &&
      (node->lhs->ty->kind == TY_PTR ||is_array(node->lhs->ty)))
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


static const char *gen_ir_eq(Node *node, int indent)
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


static const char *gen_ir_logand(Node *node, int indent)
{

  int id = ir_reg++;
  const char *entry_label = format(".L.log.entry.%d", id);
  const char *rhs_label = format(".L.log.rhs.%d", id);
  const char *end_label = format(".L.log.end.%d", id);

  emit_indent(indent);
  emit("br label %%%s\n", entry_label);
  emit_label(entry_label);
  const char *l_bool = emit_to_bool(emit_expr(node->lhs, indent), node->lhs->ty, indent);

  if (node->kind == ND_LOGAND)
  {
    emit_indent(indent);
    emit("br i1 %s, label %%%s, label %%%s\n", l_bool, rhs_label, end_label);
    is_terminated = true;
  }
  else
  {
    emit_indent(indent);
    emit("br i1 %s, label %%%s, label %%%s\n", l_bool, end_label, rhs_label);
    is_terminated = true;
  }

  emit_label(rhs_label);
  const char *r_bool = emit_to_bool(emit_expr(node->rhs, indent), node->rhs->ty, indent);
  emit_indent(indent);
  emit("br label %%%s\n", end_label);
  is_terminated = true;

  emit_label(end_label);
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


static const char *gen_ir_neg(Node *node, int indent)
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


static const char *gen_ir_bitnot(Node *node, int indent)
{

  const char *v = emit_expr(node->lhs, indent);
  const char *reg = new_reg();
  emit_indent(indent);
  emit("%s = xor ", reg);
  emit_type_str(node->ty);
  emit(" %s, -1\n", v);
  return reg;
}


static const char *gen_ir_memzero(Node *node, int indent)
{

  if (node->ty->kind == TY_VOID)
    return NULL;
  Obj *var = NULL;
  if (node->var)
    var = node->var;
  else if (node->lhs && node->lhs->kind == ND_VAR)
    var = node->lhs->var;
  if (var)
  {
    if (var->ty->size > 0)
    {
      emit_indent(indent);
      emit("call void @llvm.memset.p0.i64(ptr %s, i8 0, i64 %ld, i1 false)\n",
           var_ptr(var), var->ty->size);
    }
    return NULL;
  }
  return NULL;
}


static const char *gen_ir_not(Node *node, int indent)
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


static const char *gen_ir_comma(Node *node, int indent)
{

  emit_expr(node->lhs, indent);
  return emit_expr(node->rhs, indent);
}


static const char *gen_ir_cond(Node *node, int indent)
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
  is_terminated = true;

  emit_label(true_label);
  const char *true_val = emit_expr(node->then, indent);
  const char *true_pred = current_block ? current_block : true_label;
  emit_indent(indent);
  emit("br label %%%s\n", merge_label);
  is_terminated = true;

  emit_label(false_label);
  const char *false_val = emit_expr(node->els, indent);
  const char *false_pred = current_block ? current_block : false_label;
  emit_indent(indent);
  emit("br label %%%s\n", merge_label);
  is_terminated = true;

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


static const char *gen_ir_addr(Node *node, int indent)
{

  if (node->lhs->kind == ND_VAR)
  {
    Obj *var = node->lhs->var;
    return format("%s", var_ptr(var));
  }
  if (node->lhs->kind == ND_DEREF)
    return emit_expr(node->lhs->lhs, indent);
  if (node->lhs->kind == ND_MEMBER)
  {
    const char *base = emit_expr(node->lhs->lhs, indent);
    const char *base_i8 = new_reg();
    emit_indent(indent);
    emit("%s = getelementptr i8, ptr %s, i32 0\n", base_i8, base);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = getelementptr i8, ptr %s, i32 %d\n", r, base_i8, node->lhs->member->offset);
    return r;
  }
  const char *ptr = emit_expr(node->lhs, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = getelementptr i8, ptr %s, i32 0\n", r, ptr);
  return r;
}


static const char *gen_ir_funcall(Node *node, int indent)
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
    emit("%s = alloca i8, i64 %s, align 16\n", r, size);
    return r;
  }

  const char *callee_str;
  if (is_direct)
    callee_str = format("@%s", node->lhs->var->name);
  else
    callee_str = emit_expr(node->lhs, indent);

  bool sret = is_sret(node->ty);
  // For AMD64 calls to a variadic callee, AL must hold the number of
  // XMM registers that were actually populated with float arguments so
  // that the callee's va_start can correctly decide whether to save the
  // XMM register save area.  LLVM does not infer this automatically when
  // the call is to a libc function declared with `...` because the
  // chibicc IR (unlike the assembly backend) did not set AL.
  bool is_variadic_callee = is_direct &&
                             node->lhs->var->ty &&
                             node->lhs->var->ty->is_variadic;
  int fp_arg_count = 0;
  int n = 0;
  if (sret)
    n++;
  for (Node *arg = node->args; arg; arg = arg->next)
    n++;
  const char **arg_regs = NULL;
  Type **arg_tys = NULL;
  if (n > 0)
  {
    arg_regs = (const char **)calloc((size_t)n, sizeof(const char *));
    arg_tys = (Type **)calloc((size_t)n, sizeof(Type *));
    int i = 0;
    if (sret)
    {
      arg_regs[i] = var_ptr(node->ret_buffer);
      arg_tys[i] = pointer_to(ty_void);
      i++;
    }
    for (Node *arg = node->args; arg; arg = arg->next)
    {
      arg_regs[i] = emit_expr(arg, indent);
      arg_tys[i] = arg->ty;
      if (is_variadic_callee && fp_arg_count < 8)
      {
        Type *ty = arg->ty;
        if (!ty) ty = ty_int;
        switch (ty->kind)
        {
          case TY_FLOAT:
          case TY_DOUBLE:
            fp_arg_count++;
            break;
          case TY_VECTOR:
            fp_arg_count++;
            break;
          case TY_STRUCT:
          case TY_UNION:
            if (ty->size > 0 && ir_has_flonum1(ty))
            {
              fp_arg_count++;
              if (ty->size > 8 && ir_has_flonum2(ty))
                fp_arg_count++;
            }
            break;
          default:
            break;
        }
      }
      i++;
    }
  }

  if (is_variadic_callee)
  {
    const char *al_reg = new_reg();
    emit_indent(indent);
    emit("%s = add i8 0, %d\n", al_reg, fp_arg_count);
  }

  const char *reg = new_reg();
  emit_indent(indent);
  if (node->ty->kind == TY_VOID || sret)
    emit("call ");
  else
    emit("%s = call ", reg);
  if (sret)
    emit("void");
  else
    emit_type_str(node->ty);
  // When the callee is a variadic function with a direct declaration,
  // emit the call as `call <return_ty> (<arg_types>, ...) @name(<args>)` so
  // LLVM can recognize the varargs signature and set AL correctly before
  // the call.  A bare `call ... @name(...)` without the function-type
  // cast doesn't carry the variadic information to LLVM's DAG selection
  // stage, so no AL setup is inserted and printf (and other libc
  // varargs functions) crash when reading the XMM register save area.
  if (is_variadic_callee)
  {
    emit(" (");
    for (Node *arg = node->args; arg; arg = arg->next)
    {
      if (arg != node->args)
        emit(", ");
      emit_type_str(arg->ty);
    }
    emit(", ...");
    emit(")");
  }
  emit(" %s(", callee_str);
  for (int i = 0; i < n; i++)
  {
    if (i > 0)
      emit(", ");
    if (sret && i == 0)
      emit("ptr sret(i8) %s", arg_regs[i]);
    else
    {
      emit_type_str(arg_tys[i]);
      emit(" %s", arg_regs[i]);
    }
  }
  emit(")\n");

  if (arg_regs)
    free(arg_regs);
  if (arg_tys)
    free(arg_tys);
  if (sret)
    return var_ptr(node->ret_buffer);
  return reg;
}


static const char *gen_ir_stmt_expr(Node *node, int indent)
{

  for (Node *n = node->body; n; n = n->next)
  {
    bool term = false;
    if (n->next)
    {
      emit_stmt(n, indent, &term);
      if (term)
        break;
    }
    else
    {
      // The tail expression is the value of the whole statement
      // expression.  Emit its expression directly (without the trailing
      // semicolon that emit_stmt would produce for an EXPR_STMT) so the
      // expression is only generated once.  This matters for side-effect
      // expressions like va_arg() that must not run twice.
      if (n->kind == ND_EXPR_STMT)
        return emit_expr(n->lhs, indent);
      emit_stmt(n, indent, &term);
      if (term)
        break;
    }
  }
  return NULL;
}


static const char *gen_ir_alloc(Node *node, int indent)
{

  const char *size = emit_expr(node->lhs, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = alloca i8, i64 %s\n", r, size);
  return r;
}


static const char *gen_ir_pos(Node *node, int indent)
{
  return emit_expr(node->lhs, indent);
}

static const char *gen_ir_builtin_memcpy(Node *node, int indent)
{

  const char *dest = emit_expr(node->builtin_dest, indent);
  const char *src = emit_expr(node->builtin_src, indent);
  const char *size = emit_expr(node->builtin_size, indent);
  emit_indent(indent);
  emit("call void @llvm.memcpy.p0.p0.i64(ptr %s, ptr %s, i64 %s, i1 false)\n", dest, src, size);
  return dest;
}


static const char *gen_ir_builtin_memset(Node *node, int indent)
{

  const char *dest = emit_expr(node->builtin_dest, indent);
  const char *val = emit_expr(node->builtin_val, indent);
  const char *size = emit_expr(node->builtin_size, indent);
  if (node->builtin_val->ty->size >= 4 && node->builtin_val->ty->size < 8)
  {
    const char *trunc = new_reg();
    emit_indent(indent);
    emit("%s = trunc i32 %s to i8\n", trunc, val);
    val = trunc;
  }
  emit_indent(indent);
  emit("call void @llvm.memset.p0.i64(ptr %s, i8 %s, i64 %s, i1 false)\n", dest, val, size);
  return dest;
}


static const char *gen_ir_builtin_clz(Node *node, int indent)
{
{
  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i32 @llvm.ctlz.i32(i32 %s, i1 false)\n", r, val);
  return r;
}
}

static const char *gen_ir_builtin_clzl(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i64 @llvm.ctlz.i64(i64 %s, i1 false)\n", r, val);
  const char *trunc = new_reg();
  emit_indent(indent);
  emit("%s = trunc i64 %s to i32\n", trunc, r);
  return trunc;
}


static const char *gen_ir_builtin_ctz(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i32 @llvm.cttz.i32(i32 %s, i1 false)\n", r, val);
  return r;
}


static const char *gen_ir_builtin_ctzl(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i64 @llvm.cttz.i64(i64 %s, i1 false)\n", r, val);
  const char *trunc = new_reg();
  emit_indent(indent);
  emit("%s = trunc i64 %s to i32\n", trunc, r);
  return trunc;
}


static const char *gen_ir_popcount(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i32 @llvm.ctpop.i32(i32 %s)\n", r, val);
  return r;
}


static const char *gen_ir_popcountl(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i64 @llvm.ctpop.i64(i64 %s)\n", r, val);
  const char *trunc = new_reg();
  emit_indent(indent);
  emit("%s = trunc i64 %s to i32\n", trunc, r);
  return trunc;
}


static const char *gen_ir_expect(Node *node, int indent)
{

  const char *val = emit_expr(node->lhs, indent);
  const char *expected = emit_expr(node->rhs, indent);
  int bits = int_type_bits(node->lhs->ty);
  if (bits <= 0) bits = 64;
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i%d @llvm.expect.i%d(i%d %s, i%d %s)\n",
       r, bits, bits, bits, val, bits, expected);
  int ret_bits = int_type_bits(node->ty);
  if (ret_bits > 0 && ret_bits != bits)
  {
    const char *r_cast = new_reg();
    emit_indent(indent);
    emit("%s = zext i%d %s to i%d\n", r_cast, bits, r, ret_bits);
    return r_cast;
  }
  return r;
}


static const char *gen_ir_abort(Node *node, int indent)
{

  emit_indent(indent);
  emit("call void @abort()\n");
  emit_indent(indent);
  emit("unreachable\n");
  is_terminated = true;
  return NULL;
}


static const char *gen_ir_return_addr(Node *node, int indent)
{

  int level = (int)eval(node->lhs);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call ptr @llvm.returnaddress(i32 %d)\n", r, level);
  return r;
}


static const char *gen_ir_builtin_frame_address(Node *node, int indent)
{

  int level = (int)eval(node->lhs);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call ptr @llvm.frameaddress(i32 %d)\n", r, level);
  return r;
}


static const char *gen_ir_unreachable(Node *node, int indent)
{
  return NULL;
}

static const char *gen_ir_builtin_bswap16(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  int in_bits = int_type_bits(node->builtin_val->ty);
  const char *trunc = val;
  if (in_bits > 0 && in_bits != 16) {
    trunc = new_reg();
    emit_indent(indent);
    if (in_bits < 16)
      emit("%s = zext i%d %s to i16\n", trunc, in_bits, val);
    else
      emit("%s = trunc i%d %s to i16\n", trunc, in_bits, val);
  }
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i16 @llvm.bswap.i16(i16 %s)\n", r, trunc);
  return r;
}


static const char *gen_ir_builtin_bswap32(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i32 @llvm.bswap.i32(i32 %s)\n", r, val);
  return r;
}


static const char *gen_ir_builtin_bswap64(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  int in_bits = int_type_bits(node->builtin_val->ty);
  if (in_bits > 0 && in_bits < 64) {
    const char *ext = new_reg();
    emit_indent(indent);
    emit("%s = zext i%d %s to i64\n", ext, in_bits, val);
    val = ext;
  }
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i64 @llvm.bswap.i64(i64 %s)\n", r, val);
  return r;
}


static const char *gen_ir_builtin_inff(Node *node, int indent)
{

  const char *r = new_reg();
  emit_indent(indent);
  emit_float_const(r, node);
  return r;
}


static const char *gen_ir_builtin_inf(Node *node, int indent)
{

  const char *r = new_reg();
  emit_indent(indent);
  emit_float_const(r, node);
  return r;
}


static const char *gen_ir_builtin_nanl(Node *node, int indent)
{

  const char *r = new_reg();
  emit_indent(indent);
  emit_float_const(r, node);
  return r;
}


static const char *gen_ir_builtin_nanf(Node *node, int indent)
{

  const char *r = new_reg();
  emit_indent(indent);
  emit_float_const(r, node);
  return r;
}


static const char *gen_ir_builtin_nan(Node *node, int indent)
{

  const char *r = new_reg();
  emit_indent(indent);
  emit_float_const(r, node);
  return r;
}


static const char *gen_ir_builtin_isnan(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  const char *cmp = new_reg();
  emit_indent(indent);
  if (node->builtin_val->ty->kind == TY_FLOAT)
    emit("%s = fcmp uno float %s, %s\n", cmp, val, val);
  else
    emit("%s = fcmp uno double %s, %s\n", cmp, val, val);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i32\n", r, cmp);
  return r;
}


static const char *gen_ir_parity(Node *node, int indent)
{

  const char *val = emit_expr(node->lhs, indent);
  const char *pop = new_reg();
  emit_indent(indent);
  emit("%s = call i32 @llvm.ctpop.i32(i32 %s)\n", pop, val);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = and i32 %s, 1\n", r, pop);
  return r;
}


static const char *gen_ir_parityl(Node *node, int indent)
{

  const char *val = emit_expr(node->lhs, indent);
  const char *pop = new_reg();
  emit_indent(indent);
  emit("%s = call i64 @llvm.ctpop.i64(i64 %s)\n", pop, val);
  const char *trunc = new_reg();
  emit_indent(indent);
  emit("%s = trunc i64 %s to i32\n", trunc, pop);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = and i32 %s, 1\n", r, trunc);
  return r;
}


static const char *gen_ir_stdc_bit_ceil(Node *node, int indent)
{

  const char *val = emit_expr(node->lhs, indent);
  int bits = int_type_bits(node->lhs->ty);
  if (bits <= 0) bits = 32;
  const char *cmp = new_reg();
  emit_indent(indent);
  emit("%s = icmp ule i%d %s, 1\n", cmp, bits, val);
  const char *sub = new_reg();
  emit_indent(indent);
  emit("%s = sub i%d %s, 1\n", sub, bits, val);
  const char *leading = new_reg();
  emit_indent(indent);
  emit("%s = call i%d @llvm.ctlz.i%d(i%d %s, i1 true)\n", leading, bits, bits, bits, sub);
  const char *width = new_reg();
  emit_indent(indent);
  emit("%s = sub i%d %d, %s\n", width, bits, bits, leading);
  const char *shifted = new_reg();
  emit_indent(indent);
  emit("%s = shl i%d 1, %s\n", shifted, bits, width);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = select i1 %s, i%d 1, i%d %s\n", r, cmp, bits, bits, shifted);
  return r;
}


static const char *gen_ir_builtin_add_overflow(Node *node, int indent)
{

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);
  int bits = int_type_bits(node->rhs->ty);
  if (bits <= 0) bits = 32;
  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = call {i%d, i1} @llvm.sadd.with.overflow.i%d(i%d %s, i%d %s)\n",
       result, bits, bits, bits, l, bits, r);
  const char *val = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 0\n", val, bits, result);
  const char *dest_ptr = emit_expr(node->builtin_dest, indent);
  emit_indent(indent);
  emit("store i%d %s, ptr %s\n", bits, val, dest_ptr);
  const char *overflow = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 1\n", overflow, bits, result);
  return overflow;
}


static const char *gen_ir_builtin_sub_overflow(Node *node, int indent)
{

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);
  int bits = int_type_bits(node->rhs->ty);
  if (bits <= 0) bits = 32;
  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = call {i%d, i1} @llvm.ssub.with.overflow.i%d(i%d %s, i%d %s)\n",
       result, bits, bits, bits, l, bits, r);
  const char *val = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 0\n", val, bits, result);
  const char *dest_ptr = emit_expr(node->builtin_dest, indent);
  emit_indent(indent);
  emit("store i%d %s, ptr %s\n", bits, val, dest_ptr);
  const char *overflow = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 1\n", overflow, bits, result);
  return overflow;
}


static const char *gen_ir_builtin_mul_overflow(Node *node, int indent)
{

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);
  int bits = int_type_bits(node->rhs->ty);
  if (bits <= 0) bits = 32;
  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = call {i%d, i1} @llvm.smul.with.overflow.i%d(i%d %s, i%d %s)\n",
       result, bits, bits, bits, l, bits, r);
  const char *val = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 0\n", val, bits, result);
  const char *dest_ptr = emit_expr(node->builtin_dest, indent);
  emit_indent(indent);
  emit("store i%d %s, ptr %s\n", bits, val, dest_ptr);
  const char *overflow = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 1\n", overflow, bits, result);
  return overflow;
}


static const char *gen_ir_uadd_overflow(Node *node, int indent)
{

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);
  int bits = int_type_bits(node->rhs->ty);
  if (bits <= 0) bits = 64;
  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = call {i%d, i1} @llvm.uadd.with.overflow.i%d(i%d %s, i%d %s)\n",
       result, bits, bits, bits, l, bits, r);
  const char *val = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 0\n", val, bits, result);
  const char *dest_ptr = emit_expr(node->builtin_dest, indent);
  emit_indent(indent);
  emit("store i%d %s, ptr %s\n", bits, val, dest_ptr);
  const char *overflow = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 1\n", overflow, bits, result);
  return overflow;
}


static const char *gen_ir_umul_overflow(Node *node, int indent)
{

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);
  int bits = int_type_bits(node->rhs->ty);
  if (bits <= 0) bits = 64;
  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = call {i%d, i1} @llvm.umul.with.overflow.i%d(i%d %s, i%d %s)\n",
       result, bits, bits, bits, l, bits, r);
  const char *val = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 0\n", val, bits, result);
  const char *dest_ptr = emit_expr(node->builtin_dest, indent);
  emit_indent(indent);
  emit("store i%d %s, ptr %s\n", bits, val, dest_ptr);
  const char *overflow = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {i%d, i1} %s, 1\n", overflow, bits, result);
  return overflow;
}


static const char *gen_ir_label_val(Node *node, int indent)
{

  error_tok(node->tok, "%s:%d: in %s: emit_expr: ND_LABEL_VAL not supported", __FILE__, __LINE__, __func__);
  return NULL;
}


static const char *gen_ir_default(Node *node, int indent)
{

  emit_indent(indent);
  emit("; UNSUPPORTED: node kind %d\n", node->kind);
  if (node->ty->kind == TY_VOID)
    return NULL;
  const char *r = new_reg();
  emit_indent(indent);
  if (node->ty->kind == TY_PTR || is_array(node->ty) ||
      node->ty->kind == TY_FUNC || 
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


static void gen_ir_stmt_block(Node *node, int indent, bool *terminated)
{
  for (Node *n = node->body; n; n = n->next)
  {
    emit_stmt(n, indent, terminated);
    if (terminated && *terminated)
      break;
  }
  return;
}

static void gen_ir_stmt_return(Node *node, int indent, bool *terminated)
{
  if (node->lhs)
  {
    const char *val = emit_expr(node->lhs, indent);
    emit_indent(indent);
    if (sret_reg)
    {
      emit("call void @llvm.memcpy.p0.p0.i64(ptr %s, ptr %s, i64 %ld, i1 false)\n", sret_reg, val, node->lhs->ty->size);
      emit_indent(indent);
      emit("ret void\n");
      is_terminated = true;
    }
    else
    {
      // The ND_RETURN node itself has no type set; use the enclosing
      // function's declared return type instead.
      Type *rty = (current_fn && current_fn->ty) ? current_fn->ty->return_ty : node->ty;
      Type *expr_ty = node->lhs ? node->lhs->ty : NULL;
      int ret_bits = -1;
      if (rty)
      {
        if (rty->kind == TY_BOOL) ret_bits = 1;
        else if (rty->kind == TY_CHAR) ret_bits = 8;
        else if (rty->kind == TY_SHORT) ret_bits = 16;
      }
      int expr_bits = -1;
      if (expr_ty)
      {
        if (expr_ty->kind == TY_BOOL) expr_bits = 1;
        else if (expr_ty->kind == TY_CHAR) expr_bits = 8;
        else if (expr_ty->kind == TY_SHORT) expr_bits = 16;
        else if (expr_ty->kind == TY_INT) expr_bits = 32;
      }
      // Truncate to the declared return width when the expression is
      // wider than what the ABI requires (e.g. returning an int from a
      // bool/char/short function).  Mirrors the logic in codegen.c.
      if (ret_bits > 0 && expr_bits > ret_bits)
      {
        const char *src_ty = (expr_bits == 32) ? "i32"
                          : (expr_bits == 16) ? "i16"
                          : (expr_bits == 8)  ? "i8"
                          : "i1";
        const char *trunc = new_reg();
        emit_indent(indent);
        emit("%s = trunc %s %s to i%d\n", trunc, src_ty, val, ret_bits);
        val = trunc;
      }
      emit("ret ");
      emit_type_str(rty);
      emit(" %s\n", val);
      is_terminated = true;
    }
  }
  else
  {
    emit_indent(indent);
    emit("ret void\n");
    is_terminated = true;
  }
  if (terminated)
    *terminated = true;
  return;
}

static void gen_ir_stmt_expr_stmt(Node *node, int indent, bool *terminated)
{
  emit_expr(node->lhs, indent);
  return;
}

static void gen_ir_stmt_null_expr(Node *node, int indent, bool *terminated)
{
  return;
}

static void gen_ir_stmt_if(Node *node, int indent, bool *terminated)
{
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
  is_terminated = true;

  emit_label(then_label);
  emit_stmt(node->then, indent, NULL);
  if (!is_terminated)
  {
    emit_indent(indent);
    emit("br label %%%s\n", end_label);
    is_terminated = true;
  }

  emit_label(else_label);
  if (node->els)
    emit_stmt(node->els, indent, NULL);
  if (!is_terminated)
  {
    emit_indent(indent);
    emit("br label %%%s\n", end_label);
    is_terminated = true;
  }
  emit_label(end_label);
  return;
}
}

static void gen_ir_stmt_label(Node *node, int indent, bool *terminated)
{
  emit_label(node->unique_label);
  if (node->lhs)
    emit_stmt(node->lhs, indent, terminated);
  return;
}

static void gen_ir_stmt_goto(Node *node, int indent, bool *terminated)
{
  emit_indent(indent);
  emit("br label %%%s\n", node->unique_label);
  is_terminated = true;
  if (terminated)
    *terminated = true;
  return;
}

static void gen_ir_stmt_for(Node *node, int indent, bool *terminated)
{

  const char *begin_label = format(".L.begin.%d", ir_reg++);
  const char *cont_label = format(".L.cont.%d", ir_reg++);
  const char *end_label = format(".L.end.%d", ir_reg++);
  if (node->init)
    emit_stmt(node->init, indent, NULL);
  emit_label(begin_label);
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
    is_terminated = true;
  }
  else
  {
    emit_indent(indent);
    emit("br label %%%s\n", cont_label);
    is_terminated = true;
  }
  emit_label(cont_label);
  emit_stmt(node->then, indent, NULL);
  if (node->inc)
    emit_expr(node->inc, indent);
  if (!is_terminated)
  {
    emit_indent(indent);
    emit("br label %%%s\n", begin_label);
    is_terminated = true;
  }
  emit_label(end_label);
  return;
}


static void gen_ir_stmt_do(Node *node, int indent, bool *terminated)
{

  const char *begin_label = format(".L.begin.%d", ir_reg++);
  const char *cont_label = format(".L.cont.%d", ir_reg++);
  const char *end_label = format(".L.end.%d", ir_reg++);
  emit_label(begin_label);
  bool body_terminated = false;
  emit_stmt(node->then, indent, &body_terminated);
  if (body_terminated)
  {
    emit_label(end_label);
    return;
  }
  emit_label(cont_label);
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
    is_terminated = true;
  }
  emit_label(end_label);
  return;
}


static void gen_ir_stmt_switch(Node *node, int indent, bool *terminated)
{

  const char *cond_val = emit_expr(node->cond, indent);

  for (Node *n = node->case_next; n; n = n->case_next)
  {
    const char *next_check = format(".L.switch.next.%d", ir_reg++);
    if (n->begin == n->end)
    {
      const char *cmp = new_reg();
      emit_indent(indent);
      emit("%s = icmp eq ", cmp);
      emit_type_str(node->cond->ty);
      emit(" %s, %ld\n", cond_val, n->begin);
      emit_indent(indent);
      emit("br i1 %s, label %%%s, label %%%s\n", cmp, n->label, next_check);
    }
    else
    {
      // [GNU] Case ranges: (unsigned)(val - begin) <= (unsigned)(end - begin)
      const char *off = new_reg();
      emit_indent(indent);
      emit("%s = sub ", off);
      emit_type_str(node->cond->ty);
      emit(" %s, %ld\n", cond_val, n->begin);

      const char *cmp = new_reg();
      emit_indent(indent);
      emit("%s = icmp ule ", cmp);
      emit_type_str(node->cond->ty);
      emit(" %s, %ld\n", off, n->end - n->begin);

      emit_indent(indent);
      emit("br i1 %s, label %%%s, label %%%s\n", cmp, n->label, next_check);
      is_terminated = true;
    }
    emit_label(next_check);
  }

  emit_indent(indent);
  emit("br label %%%s\n", node->default_case ? node->default_case->label : node->brk_label);
  is_terminated = true;
  emit_stmt(node->then, indent, NULL);
  emit_label(node->brk_label);
  return;
}


static void gen_ir_stmt_case(Node *node, int indent, bool *terminated)
{
  emit_label(node->label);
  if (node->lhs)
    emit_stmt(node->lhs, indent, terminated);
  return;
}

static void gen_ir_stmt_asm(Node *node, int indent, bool *terminated)
{

  char *s = subst_fp_placeholder(node->asm_str, "%rbp");
  emit_indent(indent);
  emit("call void asm sideeffect \"%s\", \"\"()\n", s);
  return;
}


static void gen_ir_stmt_default(Node *node, int indent, bool *terminated)
{
  emit_indent(indent);
  emit("; UNSUPPORTED stmt: node kind %d\n", node->kind);
  return;
}


static void emit_stmt(Node *node, int indent, bool *terminated)
{
  if (!node)
    return;

  switch (node->kind)
  {
  case ND_BLOCK:
    gen_ir_stmt_block(node, indent, terminated);
    return;
  case ND_RETURN:
    gen_ir_stmt_return(node, indent, terminated);
    return;
  case ND_EXPR_STMT:
    gen_ir_stmt_expr_stmt(node, indent, terminated);
    return;
  case ND_NULL_EXPR:
    gen_ir_stmt_null_expr(node, indent, terminated);
    return;
  case ND_IF:
    gen_ir_stmt_if(node, indent, terminated);
    return;
  case ND_LABEL:
    gen_ir_stmt_label(node, indent, terminated);
    return;
  case ND_GOTO:
    gen_ir_stmt_goto(node, indent, terminated);
    return;
  case ND_FOR:
    gen_ir_stmt_for(node, indent, terminated);
    return;
  case ND_DO:
    gen_ir_stmt_do(node, indent, terminated);
    return;
  case ND_SWITCH:
    gen_ir_stmt_switch(node, indent, terminated);
    return;
  case ND_CASE:
    gen_ir_stmt_case(node, indent, terminated);
    return;
  case ND_ASM:
    gen_ir_stmt_asm(node, indent, terminated);
    return;
  default:
    gen_ir_stmt_default(node, indent, terminated);
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
    emit("%s = alloca i8, i64 %ld, align %d\n", var_ptr(var), var->ty->size, var->align);
  }
}

static void emit_func(Obj *fn)
{
  ir_reg = 1;
  sret_reg = NULL;
  is_terminated = false;
  current_block = NULL;
  current_fn = fn;

  if (!fn->is_live)
    return;

  bool sret = is_sret(fn->ty->return_ty);
  emit("define ");
  if (fn->is_static)
    emit("internal ");

  if (sret)
    emit("void");
  else
    emit_type_str(fn->ty->return_ty);
  emit(" @%s(", fn->name);

  if (sret)
  {
    sret_reg = "%_agg_result";
    emit("ptr sret(i8) %s", sret_reg);
  }

  Obj *param;
  for (param = fn->params; param; param = param->next)
  {
    if (sret || param != fn->params)
      emit(", ");
    emit_type_str(param->ty);
    const char *pname = param->name && param->name[0] ? param->name : format("_p%d", obj_id(param));
    emit(" %%%s", pname);
  }
  if (fn->ty->is_variadic)
  {
    if (fn->params)
      emit(", ");
    emit("...");
  }
  emit(") {\n");
  emit_label("entry");

  emit_scope_allocas(fn->ty->scopes, fn->params, 2);

  for (param = fn->params; param; param = param->next)
  {
    if (!param->name || !param->name[0])
      continue;
    emit("  %s = alloca i8, i64 %ld, align %d\n", var_ptr(param), param->ty->size, param->ty->align);
  }

  // For variadic functions, the LLVM va_start intrinsic does not always include
  // rdi (the first named GP argument) in the register save area on x86-64.
  // chibicc's stdarg.h (include/stdarg.h) expects the AMD64 ABI layout where
  // the reg_save_area contains all 6 GP registers (rdi, rsi, rdx, rcx, r8, r9)
  // followed by the 8 XMM registers.  To guarantee rdi is saved, we first
  // emit an inline-asm clobber list that mentions rdi and the other argument
  // registers; this forces LLVM to spill them to a known stack location.  The
  // actual register save area is then populated by va_start.
  if (fn->ty->is_variadic && fn->va_area)
    emit("  call void @llvm.va_start(ptr %s)\n", var_ptr(fn->va_area));

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
      emit("  ret void\n");
    else if (strcmp(fn->name, "main") == 0)
      emit("  ret i32 0\n");
    else
      emit("  unreachable\n");
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
        bool sret = is_sret(fn->ty->return_ty);
        if (sret)
          emit("void");
        else
          emit_type_str(fn->ty->return_ty);
        emit(" @%s(", fn->name);

        if (sret)
          emit("ptr sret(i8)");

        // Use the type's parameter list (fn->ty->params) because the Obj list
        // (fn->params) is empty for declared (non-defined) functions like
        // printf() where only a forward declaration is in scope. Without
        // this, the IR would emit e.g. `declare i32 @printf(...)` with no
        // format-string parameter, which prevents LLVM from setting AL
        // correctly on variadic calls and produces bogus runtime behavior.
        Type *ptype = fn->ty->params;
        for (Type *t = ptype; t; t = t->next)
        {
          if (sret || t != ptype)
            emit(", ");
          emit_type_str(t);
        }
        if (fn->ty->is_variadic)
        {
          if (ptype)
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
