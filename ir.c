#include "chibicc.h"
#include "ir.h"

static bool is_terminated;

static int llvm_obj_id(Obj *var)
{
  for (int i = 0; i < obj_map_count; i++)
    if (obj_map[i] == var)
      return i;
  if (obj_map_count == obj_map_cap) {
    obj_map_cap = obj_map_cap ? obj_map_cap * 2 : 4096;
    obj_map = realloc(obj_map, (size_t)obj_map_cap * sizeof(Obj *));
  }
  obj_map[obj_map_count++] = var;
  return obj_map_count - 1;
}

void emit(const char *fmt, ...)
{
  if (is_terminated)
    return;
  va_list ap;
  va_start(ap, fmt);
  vfprintf(output_file, fmt, ap);
  va_end(ap);
}

// Returns true if the LLVM identifier 'name' must be quoted (i.e. contains
// characters outside [-a-zA-Z$._0-9]).
static bool needs_llvm_quoting(const char *name)
{
  if (!name || !name[0])
    return false;
  for (const char *p = name; *p; p++) {
    unsigned char c = (unsigned char)*p;
    if (c >= 128)
      return true; // non-ASCII (e.g. UTF-8)
    if (c == '-' || c == '$' || c == '.' || c == '_' ||
        (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
      continue;
    return true;
  }
  return false;
}

static const char *format_llvm_name(const char *name)
{
  if (needs_llvm_quoting(name))
    return format("@\"%s\"", name);
  return format("@%s", name);
}

static void emit_llvm_name(const char *name)
{
  emit("%s", format_llvm_name(name));
}

static const char *format_llvm_local(const char *name, int id)
{
  if (needs_llvm_quoting(name))
    return format("%%\"_%s.addr_%d\"", name, id);
  return format("%%_%s.addr_%d", name, id);
}

void emit_label(const char *label)
{
  if (!is_terminated && current_block)
    emit("  br label %%%s\n", label);
  current_block = label;
  // A label always opens a fresh, reachable block: branch targets must be
  // emitted even when the previous block was terminated by an `unreachable`
  // (e.g. after a noreturn call), so emit it directly rather than through
  // emit() (which swallows output once a block is terminated).
  fprintf(output_file, "%s:\n", label);
  is_terminated = false;
}

const char *new_reg(void)
{
  return format("%%_%d", ir_reg++);
}

void emit_indent(int indent)
{
  for (int i = 0; i < indent; i++)
    emit(" ");
}


// Classify a struct/union type for the AMD64 SysV calling convention when it
// is passed *by value* to an external (non-chibicc) function.  Aggregates of
// at most 16 bytes are split into one or two eightbyte scalar slots; returns
// the number of eightbytes (1 or 2) and fills `eb_ty` with their LLVM types
// ("i32"/"i64"/"float"/"double").  Larger aggregates are MEMORY class and are
// returned as 0 so the caller uses a `byval` pointer instead.
static int ir_sysv_agg_eightbytes(Type *t, const char *eb_ty[2])
{
  if (!t || (t->kind != TY_STRUCT && t->kind != TY_UNION))
    return 0;
  if (t->size <= 0 || t->size > 16)
    return 0;
  int ne = (t->size + 7) / 8;
  if (ne > 2)
    ne = 2;
  for (int e = 0; e < ne; e++)
  {
    int ebsize = t->size - e * 8;
    if (ebsize > 8)
      ebsize = 8;
    bool sse = (e == 0) ? has_flonum1(t) : has_flonum2(t);
    if (sse)
      eb_ty[e] = (ebsize <= 4) ? "float" : "double";
    else
      eb_ty[e] = (ebsize <= 4) ? "i32" : "i64";
  }
  return ne;
}

static bool ir_is_system_func(Obj *var)
{
  return var && var->tok && var->tok->file && var->tok->file->is_system_header;
}

void emit_type_str(Type *ty)
{

  if (ty->kind <= TY_LLONG && simple[ty->kind]) {
    emit("%s", simple[ty->kind]);
    return;
  }
  if (ty->kind == TY_VECTOR)

    {
      int count = ty->array_len;
      if (count <= 0 && ty->vector_size > 0 && ty->base && ty->base->size > 0)
        count = ty->vector_size / ty->base->size;
      if (count <= 0)
        count = 1;

      if (count == 1 && ty->base &&
          (ty->base->kind == TY_LONG || ty->base->kind == TY_LLONG)) {
        emit("<2 x i32>");
        return;
      }
      emit("<%d x ", count);
    }
    emit_type_str(ty->base);
    emit(">");
    return;
}

// Emit an LLVM aggregate (struct/union/array) type suitable for the `byval`
// attribute.  Scalar members fall back to emit_type_str.  Bit-field members
// are emitted as an integer of their declared width so the in-memory layout
// and ABI register class match the source type.
static void emit_llvm_aggr_type(Type *ty)
{
  switch (ty->kind)
  {
  case TY_UNION:
    emit("[%ld x i8]", ty->size);
    return;
  case TY_STRUCT:
  {
    emit("{ ");
    bool first = true;
    for (Member *mem = ty->members; mem; mem = mem->next)
    {
      if (!first)
        emit(", ");
      if (mem->is_bitfield)
      {
        // Consecutive bit-field members that share the same byte offset are
        // packed by the C layout into a single storage unit of the
        // underlying integer type.  Emit one integer field for the whole
        // unit (not one field per bit-field) so the LLVM aggregate type
        // matches the in-memory layout used by every GEP.  Otherwise a
        // struct holding bit-fields (e.g. a global table initialised
        // with designated initialisers) would be mis-packed and its
        // later members read from the wrong offset.
        emit("i%d", mem->ty->size * 8);
        first = false;
        while (mem->next && mem->next->is_bitfield &&
               mem->next->offset == mem->offset)
          mem = mem->next;
        continue;
      }
      emit_llvm_aggr_type(mem->ty);
      first = false;
    }
    emit(" }");
    return;
  }
  case TY_ARRAY:
    emit("[%ld x ", ty->array_len);
    emit_llvm_aggr_type(ty->base);
    emit("]");
    return;
  default:
    emit_type_str(ty);
    return;
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

// Find a relocation whose byte offset matches `offset`.
static Relocation *ir_find_rel(Relocation *rel, long offset)
{
  for (; rel; rel = rel->next)
    if (rel->offset == offset)
      return rel;
  return NULL;
}

// Emit the real LLVM type of a global. 
static int union_member_rank(Member *m)
{
  if (is_integer(m->ty))
    return 4;
  if (m->ty->kind == TY_FLOAT || m->ty->kind == TY_DOUBLE ||
      m->ty->kind == TY_LDOUBLE)
    return 3;
  if (m->ty->kind == TY_VECTOR)
    return 2;
  if (m->ty->kind == TY_PTR || m->ty->kind == TY_FUNC)
    return 1;
  return 0;
}

// Choose the union member used to represent the whole union. 
static Member *union_repr_member(Type *ty)
{
  Member *best = NULL;
  for (Member *m = ty->members; m; m = m->next)
  {
    if (!best)
      best = m;
    else if (m->ty->size > best->ty->size ||
             (m->ty->size == best->ty->size &&
              union_member_rank(m) > union_member_rank(best)))
      best = m;
  }
  return best;
}

static void emit_global_type(Type *ty)
{
  switch (ty->kind)
  {
  case TY_STRUCT:
  {
    emit("{ ");
    bool first = true;
    for (Member *m = ty->members; m; m = m->next)
    {
      if (!first)
        emit(", ");
      first = false;
      if (m->is_bitfield)
      {

        emit("i%d", m->ty->size * 8);
        while (m->next && m->next->is_bitfield &&
               m->next->offset == m->offset)
          m = m->next;
        continue;
      }
      emit_global_type(m->ty);
    }
    emit(" }");
    return;
  }
  case TY_UNION:
    // Represent the union with one of its members (preferring an integer or
    // pointer member) so pointer/integer initializers are representable.  All
    // members overlap at offset 0 and the chosen member spans the whole union,
    // so the LLVM type keeps the correct size.
    emit_global_type(union_repr_member(ty)->ty);
    return;
  case TY_ARRAY:
    emit("[%ld x ", ty->array_len);
    emit_global_type(ty->base);
    emit("]");
    return;
  case TY_VECTOR:
  {
    int count = ty->array_len > 0 ? ty->array_len : 1;
    emit("<%d x ", count);
    emit_global_type(ty->base);
    emit(">");
    return;
  }
  default:
    emit_type_str(ty);
    return;
  }
}

// Emit only the scalar integer literal (no type prefix) read from `data`.
static void emit_int_const_from_data(Type *ty, unsigned char *data, long base)
{
  switch (ty->size)
  {
  case 1: { int8_t v; memcpy(&v, data + base, 1); emit("%d", (int)v); return; }
  case 2: { int16_t v; memcpy(&v, data + base, 2); emit("%d", (int)v); return; }
  case 4: { int32_t v; memcpy(&v, data + base, 4); emit("%d", (int)v); return; }
  case 8: { int64_t v; memcpy(&v, data + base, 8); emit("%ld", (long)v); return; }
  case 16:
  {
    uint64_t lo, hi;
    memcpy(&lo, data + base, 8);
    memcpy(&hi, data + base + 8, 8);
    emit("0x%016llX%016llX", (unsigned long long)hi, (unsigned long long)lo);
    return;
  }
  default:
    emit("0");
    return;
  }
}

// Emit the scalar floating-point zero literal (typed) for `ty`.
// Used where the type is NOT already declared by the surrounding context
// (e.g. a `ret` value or a global initializer), so the type prefix is needed.
static void emit_float_zero_const(Type *ty)
{
  if (ty->kind == TY_FLOAT)
    emit("float 0.0");
  else if (ty->kind == TY_LDOUBLE)
    emit("x86_fp80 0xK00000000000000000000");
  else
    emit("double 0.0");
}

// Emit the scalar floating-point zero literal (untyped) for `ty`.
// Used as an instruction operand (e.g. fcmp's second operand), where the type
// is already declared by the instruction. LLVM's IR parser rejects a typed
// decimal literal (e.g. "double 0.0") as fcmp's second operand, so the
// scientific form "0.0e+00" (or x86_fp80's 0xK... form) is required.
static void emit_float_zero_const_untyped(Type *ty)
{
  if (ty->kind == TY_LDOUBLE)
    emit("0xK00000000000000000000");
  else
    emit("0.0e+00");
}

// Emit only the scalar floating-point literal read from `data`.
// Must be a typed literal (e.g. `double 0x3FF...`) because this is only used
// for global initializers, where `bitcast` constant expressions are rejected
// inside aggregate (struct/array) constants by llc.
static void emit_float_const_from_data(Type *ty, unsigned char *data, long base)
{
  if (ty->kind == TY_FLOAT)
  {
    uint32_t i; memcpy(&i, data + base, 4);
    emit("float 0x%08X", i);
  }
  else if (ty->kind == TY_DOUBLE)
  {
    uint64_t i; memcpy(&i, data + base, 8);
    emit("double 0x%016llX", (unsigned long long)i);
  }
  else
  {
    union { long double f; uint8_t bytes[16]; } u;
    memcpy(u.bytes, data + base, 16);
    unsigned long long mantissa = 0;
    for (int i = 0; i < 8; i++)
      mantissa |= (unsigned long long)u.bytes[i] << (i * 8);
    unsigned exponent = (u.bytes[9] << 8) | u.bytes[8];
    emit("x86_fp80 0xK%04X%016llX", exponent, mantissa);
  }
}

// Emit an LLVM constant initializer for `ty`, reading non-relocation bytes from
// `data` (absolute byte offset `base`) and honoring relocations from `rel`.
// The function walks the type recursively so aggregates carrying several
// pointer relocations are emitted correctly (the previous code dropped every
// global with more than one relocation to `zeroinitializer`).  Each value is
// prefixed with its LLVM type, as required for aggregate constants.
static void emit_typed_const(Type *ty, unsigned char *data, long base, Relocation *rel)
{
  switch (ty->kind)
  {
  case TY_PTR:
  case TY_FUNC:
  {
    emit_type_str(ty);
    emit(" ");
    Relocation *r = ir_find_rel(rel, base);
    if (r)
    {
      if (r->is_label)
      {
        // A basic-block label (&&label) is not a global symbol; it must be
        // emitted as an LLVM blockaddress referencing its function.
        emit("blockaddress(");
        emit_llvm_name(r->func_name);
        emit(", %%%s)", *r->label);
      }
      else if (r->addend != 0)
      {
        emit("getelementptr inbounds (i8, ptr ");
        emit_llvm_name(*r->label);
        emit(", i32 %ld)", r->addend);
      }
      else
        emit_llvm_name(*r->label);
    }
    else
      emit("null");
    return;
  }
  case TY_BOOL:
  case TY_CHAR:
  case TY_SHORT:
  case TY_INT:
  case TY_LONG:
  case TY_ENUM:
  case TY_LLONG:
  {
    emit_type_str(ty);
    emit(" ");
    Relocation *r = ir_find_rel(rel, base);
    if (r)
    {
      emit("add (");
      emit_type_str(ty);
      emit(" ptrtoint (ptr ");
      emit_llvm_name(*r->label);
      emit(" to ");
      emit_type_str(ty);
      emit("), ");
      emit_type_str(ty);
      emit(" %ld)", r->addend);
    }
    else if (data)
      emit_int_const_from_data(ty, data, base);
    else
      emit("0");
    return;
  }
  case TY_INT128:
  {
    emit("i128 ");
    Relocation *r = ir_find_rel(rel, base);
    if (r)
    {
      emit("add (i128 ptrtoint (ptr ");
      emit_llvm_name(*r->label);
      emit(" to i128), i128 %ld)", r->addend);
    }
    else if (data)
      emit_int_const_from_data(ty, data, base);
    else
      emit("0");
    return;
  }
  case TY_FLOAT:
  case TY_DOUBLE:
  case TY_LDOUBLE:
    if (data)
      emit_float_const_from_data(ty, data, base);
    else
      emit_float_zero_const(ty);
    return;
  case TY_STRUCT:
  {
    emit_global_type(ty);
    emit(" { ");
    bool first = true;
    for (Member *m = ty->members; m; m = m->next)
    {
      if (!first)
        emit(", ");
      first = false;
      if (m->is_bitfield)
      {
        // A run of bit-fields sharing one storage unit is emitted as a
        // single integer constant: the initializer buffer already holds
        // the packed value at `m->offset`.  Emitting one value per
        // bit-field would disagree with the (now packed) global type.
        // The integer width must match emit_global_type, which uses the
        // member's storage size in bits (so a `_Bool` bit-field is `i8`,
        // not `i1`).  Use that width here so the value type agrees with
        // the struct's declared element type.
        emit("i%d ", (int)m->ty->size * 8);
        Relocation *r = ir_find_rel(rel, base + m->offset);
        if (r)
        {
          emit("add (i%d ptrtoint (ptr ", (int)m->ty->size * 8,
               *r->label);
          emit(" to i%d), i%d %ld)", (int)m->ty->size * 8,
               (int)m->ty->size * 8, r->addend);
        }
        else if (data)
          emit_int_const_from_data(m->ty, data, base + m->offset);
        else
          emit("0");
        while (m->next && m->next->is_bitfield &&
               m->next->offset == m->offset)
          m = m->next;
        continue;
      }
      emit_typed_const(m->ty, data, base + m->offset, rel);
    }
    emit(" }");
    return;
  }
  case TY_UNION:
  {
    // All members overlap at offset 0; emit the initializer of the chosen
    // representative member so pointer/integer union values (and their
    // relocations) are preserved instead of being zeroed.  The representative
    // spans the whole union, so the emitted value has the correct size.
    Member *m = union_repr_member(ty);
    emit_typed_const(m->ty, data, base, rel);
    return;
  }
  case TY_ARRAY:
  case TY_VECTOR:
  {
    emit("[%ld x ", ty->array_len);
    emit_global_type(ty->base);
    emit("] [ ");
    bool first = true;
    long stride = ty->base->size;
    for (int i = 0; i < ty->array_len; i++)
    {
      if (!first)
        emit(", ");
      first = false;
      emit_typed_const(ty->base, data, base + (long)i * stride, rel);
    }
    emit(" ]");
    return;
  }
  default:
    error("%s:%d: in %s: unsupported global init type kind %d",
          __FILE__, __LINE__, __func__, ty->kind);
  }
}

static void emit_global(Obj *var)
{
  if (var->alias_name && !var->is_function)
  {
    emit_llvm_name(ir_sym(var));
    emit(" = ");
    if (var->is_weak)
      emit("weak ");
    emit("alias ");
    emit_type_str(var->ty);
    emit(", ptr ");
    emit_llvm_name(var->alias_name);
    emit("\n");
    return;
  }

  if (var->is_function)
    return;

  if (!var->is_definition) {
    emit_llvm_name(ir_sym(var));
    emit(" = ");
    if (var->is_weak)
      emit("extern_weak ");
    else
      emit("external ");
    if (var->is_static)
      emit("internal ");
    if (var->is_tls)
      emit("thread_local ");

    int gsize = var->ty->size > 0 ? var->ty->size : 0;
    emit("global [%d x i8]", gsize);
    if (var->align > 0)
      emit(", align %d", var->align);
    emit("\n");
    return;
  }

  emit_llvm_name(ir_sym(var));
  emit(" = ");
  if (var->is_static)
    emit("internal ");
  else if (var->is_weak)
    emit("weak ");
  if (var->is_tls)
    emit("thread_local ");

  if (var->init_data && !var->rel)
  {
    if (var->ty->is_const)
      emit("constant ");
    else
      emit("global ");
    emit("[%d x i8] c\"", var->ty->size);
    emit_escaped_string(var->init_data, var->ty->size);
    emit("\"");
    if (var->align > 0)
      emit(", align %d", var->align);
  }
  else if (var->rel)
    {
        if (var->ty->is_const)
          emit("constant ");
        else
          emit("global ");
        emit_typed_const(var->ty, (unsigned char *)var->init_data, 0, var->rel);
        if (var->align > 0)
          emit(", align %d", var->align);
    }
  else
  {

    emit("global ");
    emit("[%ld x i8]", var->ty->size);
    emit(" zeroinitializer");
    if (var->align > 0)
      emit(", align %d", var->align);
  }

  emit("\n");
}


const char *emit_reinterpret_via_mem_ty(const char *val,
                                                Type *src_ty, Type *dst_ty,
                                                int indent)
{
  int size = src_ty->size > dst_ty->size ? src_ty->size : dst_ty->size;
  int align = src_ty->align > dst_ty->align ? src_ty->align : dst_ty->align;
  const char *ptr = new_reg();
  emit_indent(indent);
  emit("%s = alloca i8, i64 %d, align %d\n", ptr, size, align);
  // When the destination is wider than the source, zero the backing store
  // first so the bytes beyond the source value are well-defined (zero),
  // matching the zero-extension semantics of e.g. movq/movd reinterprets.
  if (dst_ty->size > src_ty->size)
  {
    emit_indent(indent);
    emit("call void @llvm.memset.p0.i64(ptr %s, i8 0, i64 %d, i1 false)\n",
         ptr, size);
  }
  emit_indent(indent);
  emit("store ");
  emit_type_str(src_ty);
  emit(" %s, ptr %s, align %d\n", val, ptr, src_ty->align);
  return ir_load(dst_ty, ptr, dst_ty->align, indent);
}

const char *ir_sym(Obj *var)
{
  return var->asmname ? var->asmname : var->name;
}

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
    return format_llvm_local(var->name, llvm_obj_id(var));
  }
  else
  {
    if (var->name)
      return format_llvm_name(ir_sym(var));
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

// Returns the store address (always a ptr) for an lvalue node.
// Unlike emit_lval, this never loads the value of a scalar variable.
const char *emit_lval_ptr(Node *node, int indent)
{
  switch (node->kind)
  {
  case ND_VAR:
    return var_ptr(node->var);
  case ND_DEREF:
    return emit_expr(node->lhs, indent);
  case ND_VLA_PTR:
    return var_ptr(node->var);
  case ND_CAST:
    return emit_lval_ptr(node->lhs, indent);
  case ND_COMMA:
    // Evaluate lhs for side effects, then yield the store address of the rhs.
    emit_expr(node->lhs, indent);
    return emit_lval_ptr(node->rhs, indent);
  case ND_MEMBER:
  {
    const char *base = emit_expr(node->lhs, indent);
    return ir_gep_i8(base, node->member->offset, indent);
  }
  default:
    error_tok(node->tok, "%s:%d: in %s: emit_lval_ptr: unexpected node kind %d",
              __FILE__, __LINE__, __func__, node->kind);
    return NULL;
  }
}

static const char *emit_lval(Node *node, int indent)
{
  switch (node->kind)
  {
  case ND_VAR:
  {
    Obj *var = node->var;

    // A variable-length array is realized as a hidden pointer (the parser
    // lowers it to an alloca of vla_size whose address is stored in the
    // variable's slot).  Its lvalue is the loaded pointer, not the slot
    // holding it, otherwise address arithmetic (e.g. &a[0]) would address
    // the slot rather than the array data.
    if (var->ty->kind == TY_VLA)
    {
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = load ptr, ptr %s\n", r, var_ptr(var));
      return r;
    }

    if (is_array(var->ty) || var->ty->kind == TY_FUNC ||
        is_vector(var->ty))
      return var_ptr(var);

    // Struct/union parameters are copied by value into their alloca slot at
    // function entry (see the memcpy in emit_func), so the slot itself holds
    // the struct data and its address is the struct's address.  Treating it
    // identically to a local struct variable keeps `&param` and field writes
    // consistent and avoids the load-ptr-then-gep pattern that llc miscompiles
    // for by-value struct parameters whose address is also taken.
    if (var->ty->kind == TY_STRUCT || var->ty->kind == TY_UNION)
      return var_ptr(var);

    return ir_load(var->ty, var_ptr(var), 0, indent);
  }
  case ND_DEREF:
  {
    const char *addr = emit_expr(node->lhs, indent);

    if (is_array(node->ty) || node->ty->kind == TY_STRUCT ||
        node->ty->kind == TY_UNION || node->ty->kind == TY_FUNC ||
        is_vector(node->ty))
      return addr;

    return ir_load(node->ty, addr, 0, indent);
  }
  case ND_MEMBER:
  {
    const char *base = emit_expr(node->lhs, indent);
    const char *addr = ir_gep_i8(base, node->member->offset, indent);

    if (is_array(node->ty) || node->ty->kind == TY_STRUCT ||
        node->ty->kind == TY_UNION || node->ty->kind == TY_FUNC ||
        is_vector(node->ty))
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
      r = ir_load(node->ty, addr, 0, indent);
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
   case ND_CAST:
     // A cast does not change the address of an lvalue.
     return emit_lval(node->lhs, indent);
   case ND_COMMA:
     // Evaluate the lhs for side effects, then yield the address of the rhs lvalue.
     emit_expr(node->lhs, indent);
     return emit_lval(node->rhs, indent);
   default:
     error_tok(node->tok, "%s:%d: in %s: emit_lval: unexpected node kind %d", __FILE__, __LINE__, __func__, node->kind);
     return NULL;
  }
}

int int_type_bits(Type *ty)
{
  if (!ty)
    return 0;
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

// Width (in bits) of the integer used for an atomic access of `ty`, matching
// the type emitted by emit_atomic_type_str: floats use their natural width,
// booleans are widened to i8, and everything else uses its integer width
// (minimum 8 bits, as LLVM requires for atomic accesses).
static int atomic_ir_width(Type *ty)
{
  if (is_flonum(ty))
    return ty->size * 8;
  int b = int_type_bits(ty);
  if (b <= 0)
    b = ty->size > 0 ? ty->size * 8 : 32;
  return b < 8 ? 8 : b;
}

// Emit the LLVM IR type string to use for atomic operations on the given
// type.  LLVM's cmpxchg (and most atomicrmw ops) only accept integer types,
// so for floating-point types we emit the equivalent-width integer type.
void emit_atomic_type_str(Type *ty)
{
  if (is_flonum(ty))
    emit("i%d", ty->size * 8);
  else
    emit_type_str(ty);
}

// Convert a floating-point value (in an LLVM register) to the equivalent-width
// integer type used for atomic operations.  For float/double (same size as i32/i64)
// we can bitcast directly; for long double (80-bit x86_fp80 -> 128-bit i128) we
// must go through memory because the sizes differ.  No-op for non-float types.
static const char *float_val_to_atomic_int(const char *reg, Type *ty, int indent)
{
  if (!is_flonum(ty))
    return reg;
  if (ty->kind == TY_FLOAT)
  {
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = bitcast float %s to i32\n", r, reg);
    return r;
  }
  if (ty->kind == TY_DOUBLE)
  {
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = bitcast double %s to i64\n", r, reg);
    return r;
  }
  // TY_LDOUBLE: x86_fp80 is 80 bits but i128 is 128 bits.  Go through memory
  // to get the full 128-bit representation including padding bytes.
  const char *tmp = new_reg();
  emit_indent(indent);
  emit("%s = alloca i8, i64 16\n", tmp);
  emit_indent(indent);
  emit("store x86_fp80 %s, ptr %s\n", reg, tmp);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = load i128, ptr %s\n", r, tmp);
  return r;
}

// Convert an integer value (from emit_expr) to the equivalent-width integer
// type used for atomic operations.  No-op for float types or when the width
// already matches.  Uses zext/sext/trunc as needed based on signedness.
const char *int_val_to_atomic_int(const char *reg, Type *val_ty, Type *ty, int indent)
{
  if (is_flonum(ty))
    return float_val_to_atomic_int(reg, ty, indent);
  if (!val_ty || !is_integer(val_ty))
    return reg;
  int src_bits = int_type_bits(val_ty);
  if (src_bits <= 0) src_bits = val_ty->size * 8;
  int dst_bits = int_type_bits(ty);
  if (dst_bits <= 0) dst_bits = ty->size * 8;
  if (src_bits > 0 && dst_bits > 0 && src_bits != dst_bits)
  {
    const char *r = new_reg();
    emit_indent(indent);
    if (src_bits < dst_bits)
      emit("%s = %s i%d %s to i%d\n", r, val_ty->is_unsigned ? "zext" : "sext", src_bits, reg, dst_bits);
    else
      emit("%s = trunc i%d %s to i%d\n", r, src_bits, reg, dst_bits);
    return r;
  }
  return reg;
}

// Convert a value back from the atomic integer type to its original floating-point
// type.  No-op for non-float types.
const char *atomic_int_to_float_val(const char *reg, Type *ty, int indent)
{
  if (!is_flonum(ty))
    return reg;
  if (ty->kind == TY_FLOAT)
  {
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = bitcast i32 %s to float\n", r, reg);
    return r;
  }
  if (ty->kind == TY_DOUBLE)
  {
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = bitcast i64 %s to double\n", r, reg);
    return r;
  }
  // TY_LDOUBLE: go through memory (i128 -> x86_fp80).
  const char *tmp = new_reg();
  emit_indent(indent);
  emit("%s = alloca i8, i64 16\n", tmp);
  emit_indent(indent);
  emit("store i128 %s, ptr %s\n", reg, tmp);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = load x86_fp80, ptr %s\n", r, tmp);
  return r;
}

// === Atomic helpers ===
// Map a chibicc __ATOMIC_* memory order constant to the LLVM atomic
// ordering keyword (monotonic/acquire/release/acq_rel/seq_cst).  chibicc
// uses the same 0..5 numbering as the C11/_Atomic header file.
const char *ir_atomic_ordering(int memorder)
{
  switch (memorder)
  {
  case 0: return "monotonic";
  case 1: return "monotonic";
  case 2: return "acquire";
  case 3: return "release";
  case 4: return "acq_rel";
  case 5: return "seq_cst";
  default: return "seq_cst";
  }
}

// A store cannot use Acquire ordering (Acquire is load-only).  Like GCC/clang,
// drop an invalid acquire store ordering to relaxed (monotonic) so the IR stays
// valid.
const char *ir_atomic_store_ordering(int memorder)
{
  if (memorder == 2)  // __ATOMIC_ACQUIRE
    return "monotonic";
  return ir_atomic_ordering(memorder);
}

// A load cannot use Release ordering (Release is store-only).  Drop an invalid
// release load ordering to relaxed (monotonic).
const char *ir_atomic_load_ordering(int memorder)
{
  if (memorder == 3)  // __ATOMIC_RELEASE
    return "monotonic";
  return ir_atomic_ordering(memorder);
}

// Emit an atomic load with the requested ordering.  Pointers and
// floating-point values are loaded with their real LLVM type (so e.g. a
// `char *` atom loads as `ptr` and not as `i64`, which would break callers
// expecting a pointer), while integer/boolean values keep the existing
// widening/narrowing behaviour.
 const char *ir_emit_atomic_load(const char *ptr, Type *ty, int memorder, int indent)
 {
   if (ty->kind == TY_STRUCT || ty->kind == TY_UNION)
   {
     // Aggregates are passed by address in this backend.  Load the atomic
     // location as an integer of the same width, then copy it into a fresh
     // aggregate slot and return that slot's address as the loaded value.
     int bits = ty->size * 8;
     const char *loaded = new_reg();
     emit_indent(indent);
     emit("%s = load atomic i%d, ptr %s %s, align %d\n", loaded, bits, ptr,
          ir_atomic_load_ordering(memorder), ty->align);
     const char *tmp = new_reg();
     emit_indent(indent);
     emit("%s = alloca i8, i64 %d, align %d\n", tmp, ty->size, ty->align);
     emit_indent(indent);
     emit("store i%d %s, ptr %s, align %d\n", bits, loaded, tmp, ty->align);
     return tmp;
   }

   if (is_pointer(ty) || ty->kind == TY_FUNC || is_array(ty) || is_vector(ty))
   {
     const char *r = new_reg();
     emit_indent(indent);
     emit("%s = load atomic ptr, ptr %s %s, align %d\n",
          r, ptr, ir_atomic_load_ordering(memorder), ty->align);
     return r;
   }


  if (is_flonum(ty))
  {
    // Atomic accesses must be power-of-two sized; x86_fp80 (80 bits) is not,
    // so load the value in its equivalent-width integer form and convert it
    // back to the floating-point register type expected by callers.
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = load atomic i%d, ptr %s %s, align %d\n",
         r, ty->size * 8, ptr, ir_atomic_load_ordering(memorder), ty->align);
    return atomic_int_to_float_val(r, ty, indent);
  }

  int bits = int_type_bits(ty);
  if (bits <= 0) bits = (ty->size > 0) ? ty->size * 8 : 32;
  // LLVM requires atomic memory accesses to be at least one byte wide;
  // TY_BOOL (i1) must be widened to i8 for the load instruction.
  int load_bits = bits < 8 ? 8 : bits;
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = load atomic i%d, ptr %s %s, align %d\n",
       r, load_bits, ptr, ir_atomic_load_ordering(memorder), ty->align);
  // Narrow the i8 result back to i1 for boolean types.
  if (bits == 1)
  {
    const char *trunc = new_reg();
    emit_indent(indent);
    emit("%s = trunc i8 %s to i1\n", trunc, r);
    return trunc;
  }
  return r;
}

// Emit an atomic store with the requested ordering.  Pointers and
// floating-point values are stored with their real LLVM type (so a `char *`
// atom stores as `ptr`, not as `i64`), while integer/boolean values keep the
// existing widening/narrowing behaviour.  `val_bits` is the IR bit-width of
// the incoming `val` register (0 = unknown, assume i32).
 void ir_emit_atomic_store(const char *val, const char *ptr, Type *ty,
                                  int memorder, int indent, int val_bits)
 {
   if (ty->kind == TY_STRUCT || ty->kind == TY_UNION)
   {
     // Aggregates are passed by address in this backend.  Bitcast the source
     // location to an integer of the same width and load it, since LLVM
     // cannot atomically store aggregate types directly.  Opaque pointers let
     // us load/store the integer directly without an explicit bitcast.
     int bits = ty->size * 8;
     const char *loaded = new_reg();
     emit_indent(indent);
     emit("%s = load i%d, ptr %s, align %d\n", loaded, bits, val, ty->align);
     emit_indent(indent);
     emit("store atomic i%d %s, ptr %s %s, align %d\n", bits, loaded, ptr,
          ir_atomic_store_ordering(memorder), ty->align);
     return;
   }

   if (is_pointer(ty) || ty->kind == TY_FUNC || is_array(ty) || is_vector(ty))
   {
     emit_indent(indent);
     emit("store atomic ptr %s, ptr %s %s, align %d\n",
          val, ptr, ir_atomic_store_ordering(memorder), ty->align);
     return;
   }


  if (is_flonum(ty))
  {
    // As for loads, atomic stores must use a power-of-two width, so convert
    // the floating-point value to its equivalent-width integer form first.
    const char *v = float_val_to_atomic_int(val, ty, indent);
    emit_indent(indent);
    emit("store atomic i%d %s, ptr %s %s, align %d\n",
         ty->size * 8, v, ptr, ir_atomic_store_ordering(memorder), ty->align);
    return;
  }

  int bits = int_type_bits(ty);
  if (bits <= 0) bits = (ty->size > 0) ? ty->size * 8 : 32;
  // LLVM requires atomic memory accesses to be at least one byte wide;
  // widen i1 to i8 before storing.
  int store_bits = bits < 8 ? 8 : bits;
  const char *store_val = val;
  if (val_bits <= 0)
    val_bits = 32;
  if (bits == 1)
  {
    // Coerce the value to i1 first (it may arrive wider, e.g. an `i32`
    // holding a boolean), then widen i1 -> i8 for the atomic store.
    const char *b = new_reg();
    emit_indent(indent);
    if (val_bits == 1)
      b = val;
    else
      emit("%s = trunc i%d %s to i1\n", b, val_bits, val);
    store_val = new_reg();
    emit_indent(indent);
    emit("%s = zext i1 %s to i8\n", store_val, b);
  }
  else if (val_bits != store_bits)
  {
    // Normalise the value to the atomic access width (handles e.g. an i32
    // constant being stored into an i64/i8 atomic location).
    const char *cv = new_reg();
    emit_indent(indent);
    if (val_bits > store_bits)
      emit("%s = trunc i%d %s to i%d\n", cv, val_bits, val, store_bits);
    else
      emit("%s = %s i%d %s to i%d\n", cv, ty->is_unsigned ? "zext" : "sext",
           val_bits, val, store_bits);
    store_val = cv;
  }
  emit_indent(indent);
  emit("store atomic i%d %s, ptr %s %s, align %d\n",
       store_bits, store_val, ptr, ir_atomic_store_ordering(memorder), ty->align);
}

// Emit an atomicrmw read-modify-write with the requested LLVM opcode and
// return the register holding the old value.
// val_bits is the IR bit-width of the incoming `val` register (0 = unknown/i32).
const char *ir_emit_atomicrmw(const char *op, const char *ptr, const char *val,
                                     Type *ty, int memorder, int indent, int val_bits)
{
  // Pointers (and func/array/vector) atomics exchange their real LLVM type
  // (so a `T *` atom does `atomicrmw xchg ptr ..., ptr ...`, not an
  // integer access that would try to zext a pointer value).
  if (is_pointer(ty) || ty->kind == TY_FUNC || is_array(ty) || is_vector(ty))
  {
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = atomicrmw %s ptr %s, ptr %s %s\n",
         r, op, ptr, val, ir_atomic_ordering(memorder));
    return r;
  }

  int orig_bits = int_type_bits(ty);
  if (orig_bits <= 0) orig_bits = (ty->size > 0) ? ty->size * 8 : 32;
  int bits = orig_bits;
  // LLVM requires atomic memory accesses to be at least one byte wide;
  // TY_BOOL (i1) must be widened to i8 for atomicrmw/load/store.
  if (bits < 8)
    bits = 8;
  // Normalise val_bits: 0 means caller doesn't know, assume i32 (constant literal).
  if (val_bits <= 0)
    val_bits = 32;
  // Ensure the incoming val register has exactly i{bits} width.
  // This handles: bool widening (i1->i8), small types (i8/i16 from i32 constants),
  // and large types (i32 val fed into an i64 atomicrmw for `long`).
  if (val_bits != bits)
  {
    const char *casted = new_reg();
    emit_indent(indent);
    if (val_bits > bits)
      emit("%s = trunc i%d %s to i%d\n", casted, val_bits, val, bits);
    else
      emit("%s = %s i%d %s to i%d\n", casted, ty->is_unsigned ? "zext" : "sext", val_bits, val, bits);
    val = casted;
  }
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = atomicrmw %s ptr %s, i%d %s %s\n",
       r, op, ptr, bits, val, ir_atomic_ordering(memorder));
  // Narrow the i8 result back to i1 for boolean types so callers see
  // the original width.
  if (orig_bits == 1)
  {
    const char *trunc = new_reg();
    emit_indent(indent);
    emit("%s = trunc i8 %s to i1\n", trunc, r);
    return trunc;
  }
  return r;
}

const char *emit_to_bool(const char *val, Type *ty, int indent)
{
  if (ty->kind == TY_BOOL)
    return val;
  const char *r = new_reg();
  emit_indent(indent);
  if (is_flonum(ty))
  {
    emit("%s = fcmp une ", r);
    emit_type_str(ty);
    emit(" %s, ", val);
    emit_float_zero_const_untyped(ty);
    emit("\n");
  }
  else
  {
    emit("%s = icmp ne ", r);
    emit_type_str(ty);
    emit(" %s, %s\n", val, is_pointer(ty) ? "null" : "0");
  }
  return r;
}

void emit_float_const(const char *reg, Node *node)
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

const char *gen_ir_shuffle_blend(Node *node, int indent)
{
  switch (node->kind) {
  case ND_BLENDPS: case ND_BLENDPD:
  case ND_BLENDPS256: case ND_BLENDPD256:
  case ND_BLENDVPS: case ND_BLENDVPD:
    return gen_ir_blend(node, indent);
  case ND_PBLENDVB128: case ND_PBLENDVB256:
  case ND_PBLENDW128: case ND_PBLENDD256:
    return gen_ir_pblend(node, indent);
  case ND_INSERTPS128:
    return gen_ir_insertps(node, indent);
  case ND_DPPS: case ND_DPPD: case ND_DPPS256:
    return gen_ir_dpp(node, indent);
  case ND_PALIGNR: case ND_PALIGNR128: case ND_PALIGNR256:
    return gen_ir_palignr(node, indent, node->kind == ND_PALIGNR256);
  case ND_PERMDI256:
    return gen_ir_permdi256(node, indent);
  case ND_MPSADBW128: case ND_MPSADBW256:
    return gen_ir_mpsadbw(node, indent);
  case ND_PSHUFB: case ND_PSHUFB128: case ND_PSHUFB256:
    return gen_ir_pshufb(node, indent);
  case ND_PSHUFD: case ND_PSHUFW:
    return gen_ir_pshuf(node, indent, 0);
  case ND_PSHUFHW:
    return gen_ir_pshuf(node, indent, 1);
  case ND_PSHUFLW:
    return gen_ir_pshuf(node, indent, 2);
  default:
    return gen_ir_sse_binop(node, indent);
  }
}

const char *gen_ir_vpermil_group(Node *node, int indent)
{
  switch (node->kind) {
  case ND_VPERMILPD: case ND_VPERMILPS:
  case ND_VPERMILPD256: case ND_VPERMILPS256:
    return gen_ir_vpermil(node, indent);
  case ND_VEXTRACTF128_PD256: case ND_VEXTRACTF128_PS256:
  case ND_VEXTRACTF128_SI256:
    return gen_ir_vextractf128(node, indent);
  case ND_VINSERTF128_PD256: case ND_VINSERTF128_PS256:
  case ND_VINSERTF128_SI256:
    return gen_ir_vinsertf128(node, indent);
  case ND_VPERM2F128_PD256: case ND_VPERM2F128_PS256:
    return gen_ir_vperm2f128(node, indent);
  case ND_VPERM2I128_SI256:
    return gen_ir_vperm2i128(node, indent);
  case ND_SI256_SI: case ND_SI_SI256:
    return gen_ir_vec_cast_extract(node, indent);
  case ND_PCMPGTB256_MASK:
    return gen_ir_pcmpgtb256_mask(node, indent);
  default:
    return gen_ir_int_vec_binop(node, indent);
  }
}

const char *emit_expr(Node *node, int indent)
{
  if (!node)
    return NULL;

  switch (node->kind)
  {
  case ND_NULL_EXPR: return gen_ir_null_expr(node, indent);
  case ND_NUM:  return gen_ir_num(node, indent);
  case ND_VAR: case ND_MEMBER: return gen_ir_var(node, indent);
  case ND_DEREF: case ND_VLA_PTR: return gen_ir_deref(node, indent);
  case ND_ASSIGN: return gen_ir_assign(node, indent);
  case ND_CAST: return gen_ir_cast(node, indent);
  case ND_ADD: case ND_SUB: case ND_MUL: case ND_DIV: case ND_MOD: case ND_BITAND: case ND_BITOR: 
  case ND_BITXOR: case ND_SHL: case ND_SHR:  return gen_ir_add(node, indent);
  case ND_EQ: case ND_NE: case ND_LT: case ND_LE: return gen_ir_eq(node, indent);
  case ND_LOGAND: case ND_LOGOR: return gen_ir_logand(node, indent);
  case ND_NEG: return gen_ir_neg(node, indent);
  case ND_BITNOT: return gen_ir_bitnot(node, indent);
  case ND_MEMZERO: return gen_ir_memzero(node, indent);
  case ND_NOT: return gen_ir_not(node, indent);
  case ND_COMMA: return gen_ir_comma(node, indent);
  case ND_COND: return gen_ir_cond(node, indent);
  case ND_ADDR: return gen_ir_addr(node, indent);
  case ND_FUNCALL: return gen_ir_funcall(node, indent);
  case ND_STMT_EXPR: return gen_ir_stmt_expr(node, indent);
  case ND_ALLOC: return gen_ir_alloc(node, indent);
  case ND_POS: return gen_ir_pos(node, indent);
  case ND_BUILTIN_MEMCPY: return gen_ir_builtin_memcpy(node, indent);
  case ND_BUILTIN_MEMSET: return gen_ir_builtin_memset(node, indent);
  case ND_BUILTIN_CLZ: return gen_ir_builtin_clz(node, indent);
  case ND_BUILTIN_CLZL: case ND_BUILTIN_CLZLL: return gen_ir_builtin_clzl(node, indent);
  case ND_BUILTIN_CTZ: return gen_ir_builtin_ctz(node, indent);
  case ND_BUILTIN_CTZL: case ND_BUILTIN_CTZLL: return gen_ir_builtin_ctzl(node, indent);
  case ND_POPCOUNT: return gen_ir_popcount(node, indent);
  case ND_POPCOUNTL: case ND_POPCOUNTLL: return gen_ir_popcountl(node, indent);
  case ND_EXPECT: return gen_ir_expect(node, indent);
  case ND_ABORT:  return gen_ir_abort(node, indent);
  case ND_RETURN_ADDR: return gen_ir_return_addr(node, indent);
  case ND_BUILTIN_FRAME_ADDRESS: return gen_ir_builtin_frame_address(node, indent);
  case ND_UNREACHABLE: return gen_ir_unreachable(node, indent);
  case ND_BUILTIN_BSWAP16: return gen_ir_builtin_bswap16(node, indent);
  case ND_BUILTIN_BSWAP32: return gen_ir_builtin_bswap32(node, indent);
  case ND_BUILTIN_BSWAP64: return gen_ir_builtin_bswap64(node, indent);
  case ND_BUILTIN_INFF: case ND_BUILTIN_HUGE_VALF: case ND_BUILTIN_INF: case ND_BUILTIN_HUGE_VAL:
  case ND_BUILTIN_NANL: case ND_BUILTIN_HUGE_VALL: case ND_BUILTIN_NANF:
  case ND_BUILTIN_NAN: return gen_ir_float_const_builtin(node, indent);
  case ND_BUILTIN_ISNAN: return gen_ir_builtin_isnan(node, indent);
  case ND_PARITY: return gen_ir_parity(node, indent);
  case ND_PARITYL: case ND_PARITYLL: return gen_ir_parityl(node, indent);
  case ND_STDC_BIT_CEIL: return gen_ir_stdc_bit_ceil(node, indent);
  case ND_BUILTIN_ADD_OVERFLOW: return gen_ir_builtin_add_overflow(node, indent);
  case ND_BUILTIN_SUB_OVERFLOW: return gen_ir_builtin_sub_overflow(node, indent);
  case ND_BUILTIN_MUL_OVERFLOW: return gen_ir_builtin_mul_overflow(node, indent);
  case ND_UADD_OVERFLOW: case ND_UADDL_OVERFLOW: case ND_UADDLL_OVERFLOW: return gen_ir_uadd_overflow(node, indent);
  case ND_UMUL_OVERFLOW: case ND_UMULL_OVERFLOW: case ND_UMULLL_OVERFLOW: return gen_ir_umul_overflow(node, indent);
  case ND_LABEL_VAL: return gen_ir_label_val(node, indent);
  case ND_CAS: return gen_ir_cas(node, indent);
  case ND_CAS_N: return gen_ir_cas_n(node, indent);
  case ND_EXCH: return gen_ir_exch(node, indent);
  case ND_EXCH_N: return gen_ir_exch_n(node, indent);
  case ND_CMPEXCH: return gen_ir_cmpxchg(node, indent);
  case ND_CMPEXCH_N: return gen_ir_cmpxchg_n(node, indent);
  case ND_BOOL_CAS: return gen_ir_bool_cas(node, indent);
  case ND_LOAD: return gen_ir_load(node, indent);
  case ND_LOAD_N: return gen_ir_load_n(node, indent);
  case ND_STORE: return gen_ir_store(node, indent);
  case ND_STORE_N: return gen_ir_store_n(node, indent);
  case ND_CLEAR: return gen_ir_clear(node, indent);
  case ND_RELEASE: return gen_ir_release(node, indent);
  case ND_TESTANDSET: return gen_ir_testandset(node, indent);
  case ND_TESTANDSETA: return gen_ir_testandseta(node, indent);
  case ND_FETCHADD: return gen_ir_fetchadd(node, indent);
  case ND_FETCHSUB: return gen_ir_fetchsub(node, indent);
  case ND_ADDFETCH: return gen_ir_addfetch(node, indent);
  case ND_SUBFETCH: return gen_ir_subfetch(node, indent);
  case ND_ORFETCH: return gen_ir_orfetch(node, indent);
  case ND_ANDFETCH: return gen_ir_andfetch(node, indent);
  case ND_XORFETCH: return gen_ir_xorfetch(node, indent);
  case ND_FETCHAND: return gen_ir_fetchand(node, indent);
  case ND_FETCHOR: return gen_ir_fetchor(node, indent);
  case ND_FETCHXOR: return gen_ir_fetchxor(node, indent);
  case ND_FETCHNAND: return gen_ir_fetchnand(node, indent);
  case ND_NANDFETCH: return gen_ir_nandfetch(node, indent);
  case ND_ADD_AND_FETCH: return gen_ir_add_and_fetch(node, indent);
  case ND_SUB_AND_FETCH: return gen_ir_sub_and_fetch(node, indent);
  case ND_SYNC: return gen_ir_sync(node, indent);
  case ND_MEMBARRIER: return gen_ir_membarrier(node, indent);
  case ND_ATOMIC_IS_LOCK_FREE: return gen_ir_atomic_is_lock_free(node, indent);
  case ND_ADDSS: case ND_ADDSD:  case ND_SUBSS: case ND_SUBSD:  case ND_MULSS: case ND_MULSD:
  case ND_DIVSS: case ND_DIVSD:  case ND_CMPEQSS: case ND_CMPEQSD: case ND_CMPEQPS: case ND_CMPEQPD:
  case ND_CMPLTSS: case ND_CMPLTSD: case ND_CMPLTPS: case ND_CMPLTPD: case ND_CMPLESS: case ND_CMPLESD: 
  case ND_CMPLEPS: case ND_CMPLEPD: case ND_CMPNEQSS: case ND_CMPNEQSD: case ND_CMPNEQPS: case ND_CMPNEQPD:
  case ND_CMPNLESS: case ND_CMPNLESD: case ND_CMPNLEPS: case ND_CMPNLEPD: case ND_CMPNLTSS: case ND_CMPNLTSD: 
  case ND_CMPNLTPS: case ND_CMPNLTPD: case ND_CMPNGTPD: case ND_CMPNGTPS: case ND_CMPNGEPD: case ND_CMPNGEPS:
  case ND_CMPORDSS: case ND_CMPORDSD: case ND_CMPORDPS: case ND_CMPORDPD: case ND_CMPUNORDSS: case ND_CMPUNORDSD: 
  case ND_CMPUNORDPS: case ND_CMPUNORDPD: case ND_CMPGTPD: case ND_CMPGTPS: case ND_CMPGEPD: case ND_CMPGEPS:
  case ND_CMPPD: case ND_CMPPS: case ND_CMPPD256: case ND_CMPPS256: case ND_CMPSS: case ND_CMPSD:  
  case ND_ANDPS: case ND_ANDNPS: case ND_ORPS: case ND_XORPS: case ND_ANDPD: case ND_ANDNPD: case ND_ORPD: 
  case ND_XORPD: return gen_ir_sse_binop(node, indent);
  case ND_MOVSS: case ND_MOVSD: return gen_ir_sse_movss_sd(node, indent);
  case ND_MOVLHPS: case ND_MOVHLPS: return gen_ir_sse_movlhmh(node, indent);
   case ND_UNPCKHPS: case ND_UNPCKLPS: case ND_UNPCKHPD: case ND_UNPCKLPD: return gen_ir_unpck(node, indent);
  case ND_ADDSUBPS: case ND_ADDSUBPD: return gen_ir_addsub(node, indent);
  case ND_HADDPS: case ND_HADDPD: case ND_HSUBPS: case ND_HSUBPD: return gen_ir_hadd_hsub(node, indent);
  case ND_PACKSSWB: case ND_PACKSSWB128: case ND_PACKSSDW: case ND_PACKSSDW128:
  case ND_PACKUSWB: case ND_PACKUSWB128: case ND_PACKUSDW128: return gen_ir_pack(node, indent);
  case ND_PSADBW: case ND_PSADBW128: return gen_ir_psadbw(node, indent);
  case ND_PCMPEQB: case ND_PCMPEQW: case ND_PCMPEQD: case ND_PCMPGTB: case ND_PCMPGTW: case ND_PCMPGTD:
  case ND_PMINSB128: case ND_PMAXSB128: case ND_PMINSW: case ND_PMINSW128: case ND_PMAXSW: case ND_PMAXSW128:
  case ND_PMINUB: case ND_PMINUB128: case ND_PMAXUB: case ND_PMAXUB128: case ND_PMINUW128: case ND_PMAXUW128:
  case ND_PMINSD128: case ND_PMAXSD128: case ND_PMINUD128: case ND_PMAXUD128: case ND_PADDSB: case ND_PADDSB128: 
  case ND_PADDSW: case ND_PADDSW128: case ND_PADDUSB: case ND_PADDUSB128: case ND_PADDUSW: case ND_PADDUSW128:
  case ND_PSUBSB: case ND_PSUBSB128: case ND_PSUBSW: case ND_PSUBSW128: case ND_PSUBUSB: case ND_PSUBUSB128: 
  case ND_PSUBUSW: case ND_PSUBUSW128: case ND_PMADDUBSW: case ND_PMADDUBSW128: case ND_PMULHRSW: case ND_PMULHRSW128:
  case ND_PMULHW: case ND_PMULHW128: case ND_PMULLW: case ND_PMULUDQ: case ND_PMULUDQ128: case ND_PMADDWD128:
  case ND_PAVGB: case ND_PAVGB128: case ND_PAVGW: case ND_PAVGW128: case ND_PHADDW: case ND_PHADDD: case ND_PHADDSW:
  case ND_PHADDW128: case ND_PHADDD128: case ND_PHADDSW128: case ND_PHSUBW: case ND_PHSUBD: case ND_PHSUBSW:
  case ND_PHSUBW128: case ND_PHSUBD128: case ND_PHSUBSW128: case ND_PSIGNB: case ND_PSIGNB128: case ND_PSIGNW: 
  case ND_PSIGNW128: case ND_PSIGND: case ND_PSIGND128: return gen_ir_sse_binop(node, indent);
  case ND_PADDB: case ND_PADDW: case ND_PADDD: case ND_PADDQ: case ND_PSUBB: case ND_PSUBW: case ND_PSUBD: 
  case ND_PSUBQ: case ND_PAND: case ND_PANDN: case ND_PANDN128: case ND_POR: case ND_PXOR:
  case ND_ANDNOTSI256: return gen_ir_sse_binop(node, indent);
  case ND_PSLLWI: case ND_PSLLWI128: case ND_PSLLDI: case ND_PSLLDI128: case ND_PSLLDI256:
  case ND_PSLLQI: case ND_PSLLQI128: case ND_PSLLQI256: case ND_PSLLW: case ND_PSLLW128:
  case ND_PSLLD: case ND_PSLLD128: case ND_PSLLQ: case ND_PSLLQ128: case ND_PSRAWI: case ND_PSRAWI128:
  case ND_PSRADI: case ND_PSRADI128: case ND_PSRADI256: case ND_PSRAW: case ND_PSRAW128:
  case ND_PSRAD: case ND_PSRAD128: case ND_PSRLWI: case ND_PSRLWI128: case ND_PSRLDI: case ND_PSRLDI128: 
  case ND_PSRLDI256: case ND_PSRLQI: case ND_PSRLQI128: case ND_PSRLQI256: case ND_PSRLW: case ND_PSRLW128:
  case ND_PSRLD: case ND_PSRLD128: case ND_PSRLQ: case ND_PSRLQ128: case ND_PSLLDQI128: case ND_PSLLDQI256:
  case ND_PSRLDQI128: case ND_PSRLDQI256: return gen_ir_psll_imm(node, indent);
  case ND_PABSB: case ND_PABSB128: case ND_PABSW: case ND_PABSW128: case ND_PABSD: 
  case ND_PABSD128: return gen_ir_int_vec_unary(node, indent);
  case ND_COMIEQ: case ND_COMILT: case ND_COMILE: case ND_COMIGT: case ND_COMIGE: case ND_COMINEQ:
  case ND_UCOMIEQ: case ND_UCOMILT: case ND_UCOMILE: case ND_UCOMIGT: case ND_UCOMIGE: case ND_UCOMINEQ:
  case ND_COMISDEQ: case ND_COMISDLT: case ND_COMISDLE: case ND_COMISDGT: case ND_COMISDGE: case ND_COMISDNEQ:
  case ND_UCOMISDEQ: case ND_UCOMISDLT: case ND_UCOMISDLE: case ND_UCOMISDGT: case ND_UCOMISDGE: 
  case ND_UCOMISDNEQ: return gen_ir_comi(node, indent);
  case ND_SQRTSS: case ND_SQRTPS: case ND_SQRTPD: case ND_SQRTSD: case ND_RCPSS: case ND_RCPPS:
  case ND_RSQRTSS: case ND_RSQRTPS: case ND_ROUNDSS: case ND_ROUNDPS: case ND_ROUNDPD: case ND_ROUNDSD:
  case ND_CVTSS2SI: case ND_CVTSS2SI64: case ND_CVTTSS2SI: case ND_CVTTSS2SI64: case ND_CVTSD2SI: case ND_CVTSD2SI64:
  case ND_CVTTSD2SI: case ND_CVTTSD2SI64: case ND_CVTSS2SD: case ND_CVTSD2SS: case ND_CVTPD2PS: case ND_CVTPS2PD:
  case ND_CVTDQ2PD: case ND_CVTDQ2PS: case ND_CVTPD2DQ: case ND_CVTTPD2DQ: case ND_CVTPS2DQ: case ND_CVTTPS2DQ:
  case ND_CVTPI2PD: case ND_CVTSI2SS: case ND_CVTSI642SS: case ND_CVTSI2SD: case ND_CVTSI642SD: case ND_CVTPS2PI: 
  case ND_CVTTPS2PI: case ND_CVTPD2PI: case ND_CVTTPD2PI: return gen_ir_unary_float(node, indent);
  case ND_CVTPI2PS: return gen_ir_cvtpi2ps(node, indent);
  case ND_MOVMSKPS: case ND_MOVMSKPD: return gen_ir_movmsk(node, indent);
  case ND_PMOVMSKB: case ND_PMOVMSKB128: return gen_ir_pmovmskb(node, indent);
  case ND_PMOVSXBD128: case ND_PMOVSXBW128: case ND_PMOVSXBQ128: case ND_PMOVSXDQ128: case ND_PMOVSXWD128: 
  case ND_PMOVSXWQ128: case ND_PMOVZXBD128: case ND_PMOVZXBW128: case ND_PMOVZXBQ128: case ND_PMOVZXDQ128: 
  case ND_PMOVZXWD128: case ND_PMOVZXWQ128: return gen_ir_pmov_sx_zx(node, indent);
  case ND_MINSS: case ND_MINPS: case ND_MINSD: case ND_MINPD: case ND_MAXSS: case ND_MAXPS: case ND_MAXSD: 
  case ND_MAXPD: return gen_ir_sse_binop(node, indent);
  case ND_PMADDWD: case ND_PMULHUW: case ND_PMULHUW128: case ND_PMULHUW256:
  case ND_PMULDQ128: return gen_ir_sse_binop(node, indent);
  case ND_PHMINPOSUW128: return gen_ir_sse_binop(node, indent);
  case ND_SHUFPS: case ND_SHUFPS256: case ND_SHUFPD: case ND_SHUFPD256: return gen_ir_shufp(node, indent);
  case ND_SHUFFLE: return gen_ir_shuffle(node, indent);
  case ND_PSHUFD: case ND_PSHUFHW: case ND_PSHUFLW: case ND_PSHUFW: case ND_PSHUFB: case ND_PSHUFB128: 
  case ND_PSHUFB256: case ND_PALIGNR: case ND_PALIGNR128: case ND_PALIGNR256: case ND_PERMDI256:
  case ND_MOVSHDUP: case ND_MOVSLDUP: case ND_LDDQU: case ND_PBLENDVB128: case ND_PBLENDVB256: case ND_PBLENDW128: 
  case ND_PBLENDD256: case ND_BLENDPS: case ND_BLENDPD: case ND_BLENDPS256: case ND_BLENDPD256: case ND_BLENDVPS: 
  case ND_BLENDVPD: case ND_INSERTPS128: case ND_MPSADBW128: case ND_MPSADBW256: case ND_DPPS: case ND_DPPD: 
  case ND_DPPS256: return gen_ir_shuffle_blend(node, indent);
  case ND_PTESTZ128: case ND_PTESTC128: case ND_PTESTNZC128: return gen_ir_ptest(node, indent);
  case ND_PCLMULQDQ128: case ND_VPCLMULQDQ_V4DI: case ND_VPCLMULQDQ_V8DI: return gen_ir_sse_binop(node, indent);
  case ND_MOVNTI: case ND_MOVNTI64: case ND_MOVNTQ: return gen_ir_movnti_store(node, indent);
  case ND_MOVNTDQ: case ND_MOVNTPD: case ND_MOVNTPS: return gen_ir_movnt_vec_store(node, indent);
  case ND_MOVNTDQA: return gen_ir_movntdqa_load(node, indent);
  case ND_MASKMOVDQU: case ND_MASKMOVQ: return gen_ir_maskmov(node, indent);
  case ND_MOVQ128: return gen_ir_movq128(node, indent);
  case ND_STOREHPS: case ND_STORELPS: return gen_ir_sse_store(node, indent);
  case ND_LOADHPS: case ND_LOADHPD: case ND_LOADLPS: case ND_LOADLPD: return gen_ir_sse_load(node, indent);
  case ND_CLFLUSH: return gen_ir_clflush(node, indent);
  case ND_SFENCE: case ND_LFENCE: case ND_MFENCE: case ND_PAUSE: case ND_LDMXCSR: 
  case ND_STMXCSR: return gen_ir_stmxcsr(node, indent);
  case ND_FPCLASSIFY: return gen_ir_fpclassify(node, indent);
  case ND_ISUNORDERED: return gen_ir_isunordered(node, indent);
  case ND_SIGNBIT: case ND_SIGNBITF: case ND_SIGNBITL: return gen_ir_signbit(node, indent);
  case ND_RDPID: return gen_ir_x86_rdpid(node, indent);
  case ND_RDFSBASE32: case ND_RDFSBASE64: return gen_ir_x86_rdfsbase(node, indent);
  case ND_RDGSBASE32: case ND_RDGSBASE64: return gen_ir_x86_rdgsbase(node, indent);
  case ND_PREFETCH: return gen_ir_prefetch(node, indent);
  case ND_EMMS: case ND_FEMMS: case ND_MWAIT: case ND_MONITOR: case ND_RDPKRU: return gen_ir_default(node, indent);
  case ND_RDTSC: return gen_ir_x86_rdtsc(node, indent);
  case ND_RDTSCP: return gen_ir_x86_rdtscp(node, indent);
  case ND_RDPMC: return gen_ir_x86_rdpmc(node, indent);
  case ND_READEFLAGS_U64: return gen_ir_x86_readeflags(node, indent);
  case ND_WRITEEFLAGS_U64: return gen_ir_x86_writeeflags(node, indent);
  case ND_RDSSPQ: return gen_ir_x86_rdsspq(node, indent);
  case ND_BSRSI: return gen_ir_x86_bsrsi(node, indent);
  case ND_BSRDI: return gen_ir_x86_bsrdi(node, indent);
  case ND_SBB_U32: return gen_ir_x86_sbb_u32(node, indent);
  case ND_SBB_U64: return gen_ir_x86_sbb_u64(node, indent);
  case ND_ADDCARRYX_U32: return gen_ir_x86_addcarryx_u32(node, indent);
  case ND_ADDCARRYX_U64: return gen_ir_x86_addcarryx_u64(node, indent);
  case ND_TZCNT_U16: return gen_ir_x86_tzcnt_u16(node, indent);
  case ND_CRC32QI: case ND_CRC32HI: case ND_CRC32SI: case ND_CRC32DI: return gen_ir_crc32(node, indent);
  case ND_BEXTR_U32: case ND_BEXTR_U64: return gen_ir_bextr(node, indent);
  case ND_ROLQI: case ND_ROLHI: case ND_RORQI: case ND_RORHI: case ND_XABORT: case ND_XBEGIN: case ND_XEND:
  case ND_SERIALIZE: case ND_XSUSLDTRK: case ND_XRESLDTRK: case ND_CLUI: case ND_STUI: case ND_TESTUI:
  case ND_WBINVD: case ND_WBNOINVD: case ND_XTEST: case ND_INCSSPQ: case ND_RSTORSSP: case ND_SAVEPREVSSP: 
  case ND_SETSSBSY: case ND_SLWPCB: case ND_WRSSD: case ND_WRSSQ: case ND_WRUSSD: case ND_WRUSSQ: 
  case ND_CLRSSBSY: case ND_VZEROALL: case ND_VZEROUPPER: case ND_PSUBUSB256: case ND_PCMPGTB256_MASK:
  case ND_SI256_SI: case ND_SI_SI256: case ND_VINSERTF128_SI256: case ND_VEXTRACTF128_SI256:
  case ND_VINSERTF128_PD256: case ND_VINSERTF128_PS256: case ND_VEXTRACTF128_PD256: case ND_VEXTRACTF128_PS256:
  case ND_VPERM2I128_SI256:  case ND_VPERM2F128_PD256: case ND_VPERM2F128_PS256: case ND_VPERM2F128_SI256:
  case ND_VPERMILPD: case ND_VPERMILPS: case ND_VPERMILPD256: 
  case ND_VPERMILPS256: return gen_ir_vpermil_group(node, indent);
  case ND_PD256_PD: case ND_PS256_PS: return gen_ir_vec_cast_extract(node, indent);
  case ND_EXP2PD_MASK: case ND_EXP2PS_MASK: case ND_RCP28PD_MASK: case ND_RCP28PS_MASK:
  case ND_RCP28SD_ROUND: case ND_RCP28SS_ROUND: case ND_RSQRT28PD_MASK: case ND_RSQRT28PS_MASK:
  case ND_RSQRT28SD_ROUND: case ND_RSQRT28SS_ROUND: case ND_GATHERPFDPD: case ND_GATHERPFDPS:
  case ND_GATHERPFQPD: case ND_GATHERPFQPS: case ND_SCATTERPFDPD: case ND_SCATTERPFDPS:
  case ND_SCATTERPFQPD: case ND_SCATTERPFQPS: case ND_VPSHLD_V32HI: case ND_VPSHLD_V16SI: case ND_VPSHLD_V8DI:
  case ND_VPSHLD_V16SI_MASK: case ND_VPSHLD_V8DI_MASK: case ND_VPSHRD_V32HI: case ND_VPSHRD_V16SI: case ND_VPSHRD_V8DI:
  case ND_VPSHRD_V16SI_MASK: case ND_VPSHRD_V8DI_MASK: return gen_ir_int_vec_binop(node, indent);
  case ND_PCMPISTRM128: case ND_PCMPISTRI128: case ND_PCMPISTRIA128: case ND_PCMPISTRIC128:
  case ND_PCMPISTRIO128: case ND_PCMPISTRIS128: case ND_PCMPISTRIZ128: case ND_PCMPESTRM128: case ND_PCMPESTRI128:
  case ND_PCMPESTRIA128: case ND_PCMPESTRIC128: case ND_PCMPESTRIO128: case ND_PCMPESTRIS128: 
  case ND_PCMPESTRIZ128: return gen_ir_pcmpistr(node, indent);
  case ND_PUNPCKHBW: case ND_PUNPCKHWD: case ND_PUNPCKHDQ: case ND_PUNPCKLBW: case ND_PUNPCKLWD: case ND_PUNPCKLDQ:
  case ND_PUNPCKHBW128: case ND_PUNPCKHWD128: case ND_PUNPCKHDQ128: case ND_PUNPCKHQDQ128: case ND_PUNPCKLBW128: 
  case ND_PUNPCKLWD128: case ND_PUNPCKLDQ128: case ND_PUNPCKLQDQ128: return gen_ir_punpck(node, indent);
  case ND_VECEXTV2SI: case ND_VECEXTV4SI: case ND_VECEXTV4SF: case ND_VECEXTV16QI: case ND_VECEXTV8HI: case ND_VECEXTV2DI:
  case ND_VECEXTV4HI: return gen_ir_vec_ext(node, indent);
  case ND_VECSETV4HI: case ND_VECSETV8HI: case ND_VECSETV16QI: case ND_VECSETV4SI: 
  case ND_VECSETV2DI: return gen_ir_vec_set(node, indent);
  case ND_VECINITV2SI: case ND_VECINITV4HI: case ND_VECINITV8QI: return gen_ir_vec_init(node, indent);
  default:
    return gen_ir_int_vec_binop(node, indent);
  }
}

const char *gen_ir_null_expr(Node *node, int indent)
{
  return NULL;
}

const char *gen_ir_num(Node *node, int indent)
{

  const char *r = new_reg();
  emit_indent(indent);
  if (node->ty->kind == TY_FLOAT || node->ty->kind == TY_DOUBLE || node->ty->kind == TY_LDOUBLE)
    emit_float_const(r, node);
  else if (node->ty->kind == TY_INT || node->ty->kind == TY_CHAR ||
           node->ty->kind == TY_SHORT || node->ty->kind == TY_BOOL ||
           node->ty->kind == TY_LONG) {
    int bits = node->ty->size * 8;
    if (node->ty->kind == TY_BOOL) bits = 1;
    if (bits == 64)
      emit("%s = add i64 0, %ld", r, (long)node->val);
    else
      emit("%s = add i%d 0, %d", r, bits, (int)node->val);
  }
  else if (node->ty->kind == TY_INT128)
    emit("%s = add i128 0, %ld", r, (long)node->val);
  else if (is_vector(node->ty))
  {
    Type *elem = node->ty->base;
    if (elem->kind == TY_FLOAT || elem->kind == TY_DOUBLE || elem->kind == TY_LDOUBLE)
      emit("%s = fadd ", r);
    else
      emit("%s = add ", r);
    emit_type_str(node->ty);
    emit(" zeroinitializer, zeroinitializer");
  }
  else
    emit("%s = add i64 0, %ld", r, node->val);
  emit("\n");
  return r;
}


static int ir_align_of(Type *ty)
{
  return (ty && ty->align > 0) ? ty->align : 1;
}

// Emit byte-offset pointer arithmetic `base + off` as two chained
// `getelementptr i8` instructions (the inbounds i32 0 index is required by
// LLVM before the byte offset).  Returns the resulting address register.
const char *ir_gep_i8(const char *base, long off, int indent)
{
  const char *base_i8 = new_reg();
  emit_indent(indent);
  emit("%s = getelementptr i8, ptr %s, i32 0\n", base_i8, base);
  const char *addr = new_reg();
  emit_indent(indent);
  emit("%s = getelementptr i8, ptr %s, i32 %ld\n", addr, base_i8, off);
  return addr;
}

// Emit `reg = load ty, ptr addr` with an optional alignment clause (the
// `align` clause is omitted when `align <= 0`).  Returns the destination
// register.
const char *ir_load(Type *ty, const char *addr, int align, int indent)
{
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = load ", r);
  emit_type_str(ty);
  if (align > 0)
    emit(", ptr %s, align %d\n", addr, align);
  else
    emit(", ptr %s\n", addr);
  return r;
}

const char *gen_ir_var(Node *node, int indent)
{
  const char *addr = emit_lval(node, indent);
  if (is_vector(node->ty))
    return ir_load(node->ty, addr, ir_align_of(node->ty), indent);
  return addr;
}

const char *gen_ir_deref(Node *node, int indent)
{
  const char *addr = emit_lval(node, indent);
  if (is_vector(node->ty))
    return ir_load(node->ty, addr, ir_align_of(node->ty), indent);
  return addr;
}

const char *gen_ir_assign(Node *node, int indent)
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
     case ND_CAST:
     {
       addr = emit_lval(node->lhs, indent);
       break;
     }
     case ND_COMMA:
     {
       addr = emit_lval_ptr(node->lhs, indent);
       break;
     }
     case ND_MEMBER:
    {
       Member *lhs_mem = node->lhs->member;
       const char *base_ptr = emit_expr(node->lhs->lhs, indent);
       addr = ir_gep_i8(base_ptr, node->lhs->member->offset, indent);

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
          emit(" %s, ptr %s, align %d\n", new_container, addr, ir_align_of(node->ty));
        }
        // The result of a bitfield assignment is the stored (truncated and
        // sign/zero-extended) field value, not the raw RHS.  _Bool bitfields
        // keep the previous behaviour (their extracted value is already i1).
        const char *result = (lhs_mem->ty->kind == TY_BOOL)
          ? val_trunc
          : emit_extract_bitfield(new_container, lhs_mem, load_bits, indent);
        int assign_bits = int_type_bits(node->ty);
        if (assign_bits > 0 && assign_bits != load_bits)
        {
          const char *conv = new_reg();
          emit_indent(indent);
          if (assign_bits > load_bits)
          {
            if (node->ty->is_unsigned || lhs_mem->ty->is_unsigned)
              emit("%s = zext i%d %s to i%d\n", conv, load_bits, result, assign_bits);
            else
              emit("%s = sext i%d %s to i%d\n", conv, load_bits, result, assign_bits);
          }
          else
            emit("%s = trunc i%d %s to i%d\n", conv, load_bits, result, assign_bits);
          result = conv;
        }
        return result;
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
      emit(" %s, ptr %s, align %d\n", val, addr, ir_align_of(node->ty));
    }
   return val;

}

const char *gen_ir_cast(Node *node, int indent)
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

  if (sb && is_flonum(dst))
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = %s i%d %s to ", r, src->is_unsigned ? "uitofp" : "sitofp", sb, val);
    emit_type_str(dst);
    emit("\n");
    return r;
  }

  if (is_flonum(src) && db)
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    // bool: a float casts to 1 if non-zero (ordered not-equal to 0.0),
    // not via fptosi which would truncate 0.1 to 0.
    if (db == 1) {
      emit("%s = fcmp une ", r);
      emit_type_str(src);
      emit(" %s, ", val);
      emit_float_zero_const_untyped(src);
      emit("\n");
    } else {
      emit("%s = %s ", r, dst->is_unsigned ? "fptoui" : "fptosi");
      emit_type_str(src);
      emit(" %s to i%d\n", val, db);
    }
    return r;
  }

  if (is_flonum(src) && is_flonum(dst))
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

  if ((is_pointer(src) || is_array(src) || src->kind == TY_FUNC ) && db)
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    if (db == 1)
    {
      // pointer -> bool: compare against null. Using ptrtoint to i1 would
      // take the low bit of the pointer, which is 0 for aligned
      // (non-null) pointers and would wrongly yield false.
      emit("%s = icmp ne ptr %s, null\n", r, val);
    }
    else
    {
      emit("%s = ptrtoint ptr %s to i%d\n", r, val, db);
    }
    return r;
  }

  if (sb && (is_pointer(dst) || is_array(dst) || dst->kind == TY_FUNC))
  {
    const char *val = emit_expr(node->lhs, indent);
    // LLVM `inttoptr` from a narrower integer zero-extends to the pointer
    // width, so an `i32 -1` would become 0x00000000FFFFFFFF instead of the
    // correct 0xFFFFFFFFFFFFFFFF.  Widen the integer to the pointer's integer
    // width first, sign-extending for signed sources (so `(void *)-1` yields
    // a full-width -1) and zero-extending for unsigned ones.
    if (sb < 64)
    {
      const char *ext = new_reg();
      emit_indent(indent);
      if (node->lhs->ty && node->lhs->ty->is_unsigned)
        emit("%s = zext i%d %s to i64\n", ext, sb, val);
      else
        emit("%s = sext i%d %s to i64\n", ext, sb, val);
      val = ext;
      sb = 64;
    }
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = inttoptr i%d %s to ptr\n", r, sb, val);
    return r;
  }

  if (is_vector(src) && is_pointer(dst))
    return emit_lval(node->lhs, indent);

  // Scalar to vector: convert the scalar to the element type (when the
  // widths differ) and splat it into every lane via insertelement +
  // shufflevector.  The previous code stored only the scalar's bytes into a
  // vector-sized slot and loaded the whole vector back, leaving the other
  // lanes (and high bits of lane 0) uninitialized.  Only applies when the
  // source is a scalar; vector->vector casts fall through to bitcast below.
  if (is_vector(dst) && dst->base && src->kind != TY_VECTOR) {
    // A same-size scalar -> vector conversion is a bit reinterpret (matching
    // GCC and the default x86 backend), not a splat.  This is required for the
    // __m64 <-> vector reintercasts used by the MMX/SSE builtins, where the
    // scalar only ever holds the raw vector bytes.
    if (src->size == dst->size) {
      const char *val = emit_expr(node->lhs, indent);
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = bitcast ", r);
      emit_type_str(src);
      emit(" %s to ", val);
      emit_type_str(dst);
      emit("\n");
      return r;
    }

    Type *ety = dst->base;
    int nelem = dst->array_len;
    if (nelem <= 0)
      nelem = 1;

    const char *val = emit_expr(node->lhs, indent);

    // Convert the scalar to the vector element type when needed.
    if (is_flonum(src) && !is_flonum(ety)) {
      const char *cv = new_reg();
      emit_indent(indent);
      emit("%s = %s ", cv, ety->is_unsigned ? "fptoui" : "fptosi");
      emit_type_str(src);
      emit(" %s to ", val);
      emit_type_str(ety);
      emit("\n");
      val = cv;
    } else if (!is_flonum(src) && is_flonum(ety)) {
      const char *cv = new_reg();
      emit_indent(indent);
      emit("%s = %s i%d %s to ", cv,
           src->is_unsigned ? "uitofp" : "sitofp", sb, val);
      emit_type_str(ety);
      emit("\n");
      val = cv;
    } else if (!is_flonum(src) && !is_flonum(ety)) {
      int eb = int_type_bits(ety);
      if (eb > 0 && eb != sb) {
        const char *cv = new_reg();
        emit_indent(indent);
        if (sb < eb)
          emit("%s = %s i%d %s to i%d\n", cv,
               src->is_unsigned ? "zext" : "sext", sb, val, eb);
        else
          emit("%s = trunc i%d %s to i%d\n", cv, sb, val, eb);
        val = cv;
      }
    }

    const char *ins = new_reg();
    emit_indent(indent);
    emit("%s = insertelement ", ins);
    emit_type_str(dst);
    emit(" undef, ");
    emit_type_str(ety);
    emit(" %s, i32 0\n", val);
    const char *spl = new_reg();
    emit_indent(indent);
    emit("%s = shufflevector ", spl);
    emit_type_str(dst);
    emit(" %s, ", ins);
    emit_type_str(dst);
    emit(" undef, <%d x i32> <", nelem);
    for (int i = 0; i < nelem; i++) {
      if (i) emit(", ");
      emit("i32 0");
    }
    emit(">\n");
    return spl;
  }

  if (is_vector(src) && db > 0)
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    if (src->size == (size_t)db / 8) {
      emit("%s = bitcast ", r);
      emit_type_str(src);
      emit(" %s to i%d\n", val, db);
    } else {
      int dsize = db / 8;
      int size = src->size > dsize ? src->size : dsize;
      int align = dsize > src->align ? dsize : src->align;
      const char *tmp = new_reg();
      emit("%s = alloca i8, i64 %d, align %d\n", tmp, size, align);
      emit_indent(indent);
      emit("store ");
      emit_type_str(src);
      emit(" %s, ptr %s, align %d\n", val, tmp, src->align);
      emit_indent(indent);
      r = new_reg();
      emit("%s = load i%d, ptr %s, align %d\n", r, db, tmp, dsize);
    }
    return r;
  }

  if (is_vector(src) && is_vector(dst))
  {
    const char *val = emit_expr(node->lhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    if (src->size == dst->size) {
      emit("%s = bitcast ", r);
      emit_type_str(src);
      emit(" %s to ", val);
      emit_type_str(dst);
      emit("\n");
    } else {
      r = emit_reinterpret_via_mem_ty(val, src, dst, indent);
    }
    return r;
  }

  return emit_expr(node->lhs, indent);
}


const char *gen_ir_add(Node *node, int indent)
{

  bool lhs_ptr = is_pointer(node->lhs->ty) || is_array(node->lhs->ty);

  bool rhs_ptr =  is_pointer(node->rhs->ty) || is_array(node->rhs->ty);
  if (node->kind == ND_ADD && lhs_ptr && rhs_ptr)
  {
    const char *l = emit_expr(node->lhs, indent);
    const char *r_tmp = emit_expr(node->rhs, indent);
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = ptrtoint ptr %s to i64\n", r, r_tmp);
    const char *reg = new_reg();
    emit_indent(indent);
    emit("%s = getelementptr i8, ptr %s, i64 %s\n", reg, l, r);
    return reg;
  }
  if ((node->kind == ND_SUB) &&
      (lhs_ptr && rhs_ptr))
  {
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);

    const char *l_int = l;
    if (is_pointer(node->lhs->ty) || is_array(node->lhs->ty)) {
      l_int = new_reg();
      emit_indent(indent);
      emit("%s = ptrtoint ptr %s to i64\n", l_int, l);
    }

    const char *r_int = r;
    if (is_pointer(node->rhs->ty) || is_array(node->rhs->ty)) {
      r_int = new_reg();
      emit_indent(indent);
      emit("%s = ptrtoint ptr %s to i64\n", r_int, r);
    }

    // Emit the raw byte difference. The element-size division is already
    // expressed by the parser as an enclosing ND_DIV node (see new_sub in
    // parse.c), so dividing here again would scale the result twice.
    const char *diff = new_reg();
    emit_indent(indent);
    emit("%s = sub i64 %s, %s\n", diff, l_int, r_int);

    return diff;
  }
  if (node->kind == ND_SUB &&
      (is_pointer(node->lhs->ty) || is_array(node->lhs->ty)))
  {
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);
    int rbits = int_type_bits(node->rhs->ty);
    const char *r_neg = new_reg();
    emit_indent(indent);
    emit("%s = sub i%d 0, %s\n", r_neg, rbits, r);
    const char *reg = new_reg();
    emit_indent(indent);
    // `node->rhs` is already byte-scaled by new_add (rhs * sizeof(elem)),
    // so the GEP must use an i8 (byte) element type to avoid scaling twice.
    emit("%s = getelementptr i8, ptr %s, i%d %s\n", reg, l, rbits, r_neg);
    return reg;
  }
  if (node->kind == ND_ADD &&
      (is_pointer(node->lhs->ty) || is_array(node->lhs->ty)))
  {
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);
    int rbits = int_type_bits(node->rhs->ty);
    const char *reg = new_reg();
    emit_indent(indent);
    // `node->rhs` is already byte-scaled by new_add (rhs * sizeof(elem)),
    // so the GEP must use an i8 (byte) element type to avoid scaling twice.
    emit("%s = getelementptr i8, ptr %s, i%d %s\n", reg, l, rbits, r);
    return reg;
  }
  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);
  // Emit a helper: splat a scalar value into a vector.
  // If the result type is a vector and one operand is scalar, splat it.
  if (is_vector(node->ty) && node->ty->base) {
    Type *ety = node->ty->base;
    int nelem = node->ty->array_len;
    bool l_is_scalar = node->lhs->ty->kind != TY_VECTOR;
    bool r_is_scalar = node->rhs->ty->kind != TY_VECTOR;
    if (l_is_scalar) {
      const char *ins = new_reg();
      emit_indent(indent);
      emit("%s = insertelement ", ins);
      emit_type_str(node->ty);
      emit(" undef, ");
      emit_type_str(ety);
      emit(" %s, i32 0\n", l);
      const char *spl = new_reg();
      emit_indent(indent);
      emit("%s = shufflevector ", spl);
      emit_type_str(node->ty);
      emit(" %s, ", ins);
      emit_type_str(node->ty);
      emit(" undef, <");
      for (int i = 0; i < nelem; i++) { if (i) emit(", "); emit("i32 0"); }
      emit(">\n");
      l = spl;
    }
    if (r_is_scalar) {
      const char *ins = new_reg();
      emit_indent(indent);
      emit("%s = insertelement ", ins);
      emit_type_str(node->ty);
      emit(" undef, ");
      emit_type_str(ety);
      emit(" %s, i32 0\n", r);
      const char *spl = new_reg();
      emit_indent(indent);
      emit("%s = shufflevector ", spl);
      emit_type_str(node->ty);
      emit(" %s, ", ins);
      emit_type_str(node->ty);
      emit(" undef, <");
      for (int i = 0; i < nelem; i++) { if (i) emit(", "); emit("i32 0"); }
      emit(">\n");
      r = spl;
    }
  }

  const char *reg = new_reg();
  emit_indent(indent);
  bool is_vec_float = (is_vector(node->ty)) &&
                      (node->ty->base &&
                       (node->ty->base->kind == TY_FLOAT ||
                        node->ty->base->kind == TY_DOUBLE ||
                        node->ty->base->kind == TY_LDOUBLE));
  if (is_flonum(node->ty) || is_vec_float)
  {
    // Scalar float/double division must use the x86 divss/divsd
    // instructions (via their LLVM intrinsics) so the NaN sign bit matches
    // the native backend and hardware.  Generic LLVM `fdiv` yields a positive
    // QNaN for 0.0/0.0 whereas x86 divss/divsd yield a negative QNaN, which
    // is what signbit and related tests rely on.
    if (node->kind == ND_DIV && !is_vec_float && node->ty->kind != TY_LDOUBLE)
    {
      const char *res = new_reg();
      if (node->ty->kind == TY_FLOAT)
      {
        const char *av = new_reg();
        emit_indent(indent);
        emit("%s = insertelement <4 x float> undef, float %s, i32 0\n", av, l);
        const char *bv = new_reg();
        emit_indent(indent);
        emit("%s = insertelement <4 x float> undef, float %s, i32 0\n", bv, r);
        const char *rv = new_reg();
        emit_indent(indent);
        emit("%s = call <4 x float> @llvm.x86.sse.div.ss(<4 x float> %s, <4 x float> %s)\n",
             rv, av, bv);
        emit_indent(indent);
        emit("%s = extractelement <4 x float> %s, i32 0\n", res, rv);
      }
      else
      {
        const char *av = new_reg();
        emit_indent(indent);
        emit("%s = insertelement <2 x double> undef, double %s, i32 0\n", av, l);
        const char *bv = new_reg();
        emit_indent(indent);
        emit("%s = insertelement <2 x double> undef, double %s, i32 0\n", bv, r);
        const char *rv = new_reg();
        emit_indent(indent);
        emit("%s = call <2 x double> @llvm.x86.sse2.div.sd(<2 x double> %s, <2 x double> %s)\n",
             rv, av, bv);
        emit_indent(indent);
        emit("%s = extractelement <2 x double> %s, i32 0\n", res, rv);
      }
      return res;
    }

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


const char *gen_ir_eq(Node *node, int indent)
{

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);
  const char *tmp = new_reg();
  emit_indent(indent);
  if (is_flonum(node->lhs->ty))
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
    case ND_LT: cond = node->lhs->ty->is_unsigned ||
                      is_pointer(node->lhs->ty) || is_array(node->lhs->ty) ||
                      is_pointer(node->rhs->ty) || is_array(node->rhs->ty)
                      ? "ult" : "slt"; break;
    case ND_LE: cond = node->lhs->ty->is_unsigned ||
                      is_pointer(node->lhs->ty) || is_array(node->lhs->ty) ||
                      is_pointer(node->rhs->ty) || is_array(node->rhs->ty)
                      ? "ule" : "sle"; break;
    default: cond = "???"; break;
    }
    emit("%s = icmp %s ", tmp, cond);
    emit_type_str(node->lhs->ty);
    emit(" %s, %s\n", l, r);
  }
  const char *reg = new_reg();
  emit_indent(indent);
  if (is_vector(node->lhs->ty)) {
    emit("%s = sext <%d x i1> %s to ", reg, node->lhs->ty->array_len, tmp);
    emit_type_str(node->ty);
    emit("\n");
  } else {
    emit("%s = zext i1 %s to i32\n", reg, tmp);
  }
  return reg;
}


const char *gen_ir_logand(Node *node, int indent)
{

  int id = ir_reg++;
  const char *entry_label = format(".L.log.entry.%d", id);
  const char *rhs_label = format(".L.log.rhs.%d", id);
  const char *end_label = format(".L.log.end.%d", id);

  emit_indent(indent);
  emit("br label %%%s\n", entry_label);
  is_terminated = true;
  emit_label(entry_label);
  const char *l_bool = emit_to_bool(emit_expr(node->lhs, indent), node->lhs->ty, indent);

  // Capture the block that the LHS expression actually ended in.
  // The LHS may span multiple basic blocks (e.g. nested &&/|| or ternary),
  // so current_block after emit_expr is the real predecessor of end_label,
  // not entry_label which was set before the LHS was evaluated.
  const char *lhs_block = current_block;
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
  // Capture the block the RHS actually ended in (may differ from rhs_label
  // if the RHS expression itself generated multiple basic blocks).
  const char *rhs_block = current_block;
  emit_indent(indent);
  emit("br label %%%s\n", end_label);
  is_terminated = true;

  emit_label(end_label);
  const char *result = new_reg();
  emit_indent(indent);
  const char *entry_result = (node->kind == ND_LOGAND) ? "false" : "true";
  emit("%s = phi i1 [ %s, %%%s ], [ %s, %%%s ]\n",
       result, entry_result, lhs_block, r_bool, rhs_block);

  const char *final = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i32\n", final, result);
  return final;
}


const char *gen_ir_neg(Node *node, int indent)
{

  const char *v = emit_expr(node->lhs, indent);
  const char *reg = new_reg();
  emit_indent(indent);
  bool is_vec_fp = (is_vector(node->ty)) &&
                    node->ty->base &&
                    is_flonum(node->ty->base);
  if (is_flonum(node->ty) || is_vec_fp)
  {
    emit("%s = fneg ", reg);
    emit_type_str(node->ty);
    emit(" %s\n", v);
  }
  else if (is_vector(node->ty))
  {
    emit("%s = sub ", reg);
    emit_type_str(node->ty);
    emit(" zeroinitializer, %s\n", v);
  }
  else
  {
    emit("%s = sub ", reg);
    emit_type_str(node->ty);
    emit(" 0, %s\n", v);
  }
  return reg;
}


const char *gen_ir_bitnot(Node *node, int indent)
{

  const char *v = emit_expr(node->lhs, indent);
  const char *reg = new_reg();
  emit_indent(indent);
  if (is_vector(node->ty))
  {
    Type *ety = node->ty->base;
    int bits = int_type_bits(ety);
    if (bits <= 0) bits = ety->size * 8;
    int count = node->ty->array_len;
    if (count <= 0) count = 1;
    emit("%s = xor ", reg);
    emit_type_str(node->ty);
    emit(" %s, <", v);
    for (int i = 0; i < count; i++)
    {
      if (i) emit(", ");
      emit("i%d -1", bits);
    }
    emit(">\n");
  }
  else
  {
    emit("%s = xor ", reg);
    emit_type_str(node->ty);
    emit(" %s, -1\n", v);
  }
  return reg;
}


const char *gen_ir_memzero(Node *node, int indent)
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


const char *gen_ir_not(Node *node, int indent)
{

  const char *val = emit_expr(node->lhs, indent);
  const char *zero = new_reg();
  emit_indent(indent);
  if (is_flonum(node->lhs->ty))
  {
    emit("%s = fcmp oeq ", zero);
    emit_type_str(node->lhs->ty);
    emit(" %s, ", val);
    emit_float_zero_const_untyped(node->lhs->ty);
    emit("\n");
  }
  else
  {
    emit("%s = icmp eq ", zero);
    emit_type_str(node->lhs->ty);
    emit(" %s, %s\n", val, is_pointer(node->lhs->ty) ? "null" : "0");
  }
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i32\n", r, zero);
  return r;
}


const char *gen_ir_comma(Node *node, int indent)
{

  emit_expr(node->lhs, indent);
  return emit_expr(node->rhs, indent);
}


const char *gen_ir_cond(Node *node, int indent)
{
  if (is_const_expr(node->cond)) {
    Node *n = eval(node->cond) ? node->then : node->els;
    if (n)
      return emit_expr(n, indent);
    return NULL;
  }

  const char *cond_val = emit_expr(node->cond, indent);
  const char *cond_bool;
  if (node->cond->ty->kind == TY_BOOL || is_pointer(node->cond->ty))
    cond_bool = cond_val;
  else
    cond_bool = emit_to_bool(cond_val, node->cond->ty, indent);

  const char *true_label = format(".L.cond.true.%d", ir_reg++);
  const char *false_label = format(".L.cond.false.%d", ir_reg++);
  const char *merge_label = format(".L.cond.merge.%d", ir_reg++);

  emit_indent(indent);
  emit("br i1 %s, label %%%s, label %%%s\n", cond_bool, true_label, false_label);
  is_terminated = true;

  emit_label(true_label);
  const char *true_val = emit_expr(node->then, indent);
  bool true_reaches = !is_terminated;
  const char *true_pred = current_block ? current_block : true_label;
  if (true_reaches) {
    emit_indent(indent);
    emit("br label %%%s\n", merge_label);
    is_terminated = true;
  }

  emit_label(false_label);
  const char *false_val = emit_expr(node->els, indent);
  bool false_reaches = !is_terminated;
  const char *false_pred = current_block ? current_block : false_label;
  if (false_reaches) {
    emit_indent(indent);
    emit("br label %%%s\n", merge_label);
    is_terminated = true;
  }

  if (node->ty->kind == TY_VOID) {
    if (true_reaches || false_reaches)
      emit_label(merge_label);
    return NULL;
  }

  emit_label(merge_label);

  if (!true_reaches && !false_reaches)
    return "0"; // unreachable anyway

  const char *reg = new_reg();
  emit_indent(indent);
  emit("%s = phi ", reg);
  emit_type_str(node->ty);

  if (true_reaches && false_reaches) {
    emit(" [%s, %%%s], [%s, %%%s]\n",
         true_val ? true_val : "0", true_pred,
         false_val ? false_val : "0", false_pred);
  } else if (true_reaches) {
    emit(" [%s, %%%s]\n", true_val ? true_val : "0", true_pred);
  } else {
    emit(" [%s, %%%s]\n", false_val ? false_val : "0", false_pred);
  }
  return reg;
}


const char *gen_ir_addr(Node *node, int indent)
{

  if (node->lhs->kind == ND_VAR)
  {
    Obj *var = node->lhs->var;
    // A VLA variable holds its array pointer in a hidden slot; the address
    // of the array is the loaded pointer, not the slot itself.
    if (var->ty->kind == TY_VLA)
    {
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = load ptr, ptr %s\n", r, var_ptr(var));
      return r;
    }
    return format("%s", var_ptr(var));
  }
  if (node->lhs->kind == ND_DEREF)
    return emit_expr(node->lhs->lhs, indent);
  if (node->lhs->kind == ND_MEMBER)
  {
    const char *base = emit_expr(node->lhs->lhs, indent);
    return ir_gep_i8(base, node->lhs->member->offset, indent);
  }
  const char *ptr = emit_lval_ptr(node->lhs, indent);
  return ir_gep_i8(ptr, 0, indent);
}


// A node is "pure" when evaluating it has no observable side effects, so its
// value can be recomputed at any program point that dominates its use.  This
// is used to re-materialize call arguments that were emitted in a basic block
// that does not dominate the call (see gen_ir_funcall).
static bool ir_node_is_pure(Node *n)
{
  if (!n)
    return true;
  switch (n->kind)
  {
    case ND_NUM:
    case ND_NULL_EXPR:
    case ND_VAR:
    case ND_MEMBER:
    case ND_ADDR:
    case ND_CAST:
    case ND_BITNOT:
    case ND_NEG:
    case ND_NOT:
    case ND_POS:
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
    case ND_EQ:
    case ND_NE:
    case ND_LT:
    case ND_LE:
      return ir_node_is_pure(n->lhs) && ir_node_is_pure(n->rhs);
    default:
      return false;
  }
}

// Load one SysV eightbyte (a scalar chunk of an aggregate passed by value in
// a register) from `addr + off` as the given LLVM scalar type.
const char *gen_ir_load_eightbyte(const char *addr, int off,
                                         const char *llty, int indent)
{
  const char *p = addr;
  if (off)
  {
    const char *gep = new_reg();
    emit_indent(indent);
    emit("%s = getelementptr i8, ptr %s, i64 %d\n", gep, addr, off);
    p = gep;
  }
  const char *v = new_reg();
  emit_indent(indent);
  emit("%s = load %s, ptr %s\n", v, llty, p);
  return v;
}

const char *gen_ir_funcall(Node *node, int indent)
{

  bool is_direct = (node->lhs && node->lhs->kind == ND_VAR && node->lhs->var &&
                    node->lhs->var->ty->kind == TY_FUNC);

  if (is_direct && (!strcmp(node->lhs->var->name, "alloca") ||
                    !strcmp(node->lhs->var->name, "__builtin_alloca")))
  {
    Node *arg = node->args;
    const char *size = emit_expr(arg, indent);
    // The alloca size operand must be i64 on x86-64.  Widen sub-64-bit
    // integer arguments (e.g. int/i32) so llc does not reject the IR.
    if (arg->ty->size < 8) {
      const char *size64 = new_reg();
      emit_indent(indent);
      emit("%s = %s i%d %s to i64\n", size64,
           arg->ty->is_unsigned ? "zext" : "sext",
           arg->ty->size * 8, size);
      size = size64;
    }
    const char *r = new_reg();
    emit_indent(indent);
    // Honor the requested alignment (set by the VLA lowering / __builtin_alloca
    // to MAX(16, _Alignas(N))) so over-aligned VLAs keep their alignment.
    int al = node->val > 0 ? (int)node->val : 16;
    emit("%s = alloca i8, i64 %s, align %d\n", r, size, al);
    return r;
  }

  const char *callee_str;
  const char *callee_def_block = NULL;
    if (is_direct)
      callee_str = format_llvm_name(ir_sym(node->lhs->var));
  else
  {
    callee_str = emit_expr(node->lhs, indent);
    callee_def_block = current_block;
  }

  bool sret = is_sret(node->ty);

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
  Node **arg_nodes = NULL;
  const char **arg_def_block = NULL;
  if (n > 0)
  {
    arg_regs = (const char **)calloc((size_t)n, sizeof(const char *));
    arg_tys = (Type **)calloc((size_t)n, sizeof(Type *));
    arg_nodes = (Node **)calloc((size_t)n, sizeof(Node *));
    arg_def_block = (const char **)calloc((size_t)n, sizeof(const char *));
    int i = 0;
    if (sret)
    {
      arg_regs[i] = var_ptr(node->ret_buffer);
      arg_tys[i] = pointer_to(ty_void);
      i++;
    }
    for (Node *arg = node->args; arg; arg = arg->next)
    {
      arg_nodes[i] = arg;
      arg_regs[i] = emit_expr(arg, indent);
      arg_def_block[i] = current_block;
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
            if (ty->size > 0 && has_flonum1(ty))
            {
              fp_arg_count++;
              if (ty->size > 8 && has_flonum2(ty))
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


  {
    const char *call_block = current_block;
    if (call_block)
    {
      for (int i = 0; i < n; i++)
      {
        if (arg_def_block[i] && strcmp(arg_def_block[i], call_block) != 0 &&
            ir_node_is_pure(arg_nodes[i]))
          arg_regs[i] = emit_expr(arg_nodes[i], indent);
      }
      if (callee_def_block && strcmp(callee_def_block, call_block) != 0 &&
          ir_node_is_pure(node->lhs))
        callee_str = emit_expr(node->lhs, indent);
    }
  }

  // chibicc-compiled functions (those that have a body in this link,
  // i.e. `is_definition`) always receive struct/union arguments as a byval
  // (hidden) pointer, never by value in registers.  Keep the argument as its
  // address so it is emitted as a `ptr` below, matching the callee's
  // parameter convention (the LLVM stdarg setup reads such variadic struct
  // args from the stack, not from registers).
  //
  // Genuine *external* libc functions that we only declare (no definition in
  // this link) follow the AMD64 SysV ABI instead: a small aggregate (<= 16
  // bytes) is classified into one or two eightbytes and passed *by value* in
  // registers, while larger aggregates stay MEMORY class and are passed as a
  // `byval` pointer.  Lower such arguments accordingly here, matching clang,
  // so e.g. `sigqueue(pid, sig, union sigval)` delivers the right value.
  int *agg_ne = (int *)calloc((size_t)(n > 0 ? n : 1), sizeof(int));
  const char *agg_val[2 * 64];
  const char *agg_ty[2 * 64];
  memset(agg_val, 0, sizeof(agg_val));
   memset(agg_ty, 0, sizeof(agg_ty));
   // External calls (direct, no definition in this link) keep chibicc's
   // internal byval-pointer convention *unless* they are genuine libc
   // functions (prototype declared in a system header), which must obey the
   // AMD64 SysV ABI: a small aggregate (<= 16 bytes) is passed by value as one
   // or two eightbyte scalar slots, while larger aggregates are MEMORY class
   // and passed as a `byval` pointer.  This matches real libc, e.g.
   // `sigqueue(pid, sig, union sigval)` from util-linux.
   bool is_external_call =
       is_direct && node->lhs->var && !node->lhs->var->is_definition;
   bool is_libc = is_external_call && ir_is_system_func(node->lhs->var);
   if (is_libc)
   {
     bool is_var = node->lhs->var->ty->is_variadic;
     int fixed_params = 0;
     for (Type *t = node->lhs->var->ty->params; t; t = t->next)
       fixed_params++;
     int sret_off = sret ? 1 : 0;
     for (int i = 0; i < n && i < 64; i++)
     {
       // Only variadic trailing arguments travel through `...`; fixed
       // parameters are classified from their declared (SysV) type.
       if (is_var && i - sret_off < fixed_params)
         continue;
       Type *t = arg_tys[i];
       if (!t || (t->kind != TY_STRUCT && t->kind != TY_UNION))
         continue;
       const char *eb_ty[2] = {NULL, NULL};
       int ne = ir_sysv_agg_eightbytes(t, eb_ty);
       if (ne == 0)
         continue;
       for (int e = 0; e < ne; e++)
       {
         agg_ty[i * 2 + e] = eb_ty[e];
         agg_val[i * 2 + e] =
             gen_ir_load_eightbyte(arg_regs[i], e * 8, eb_ty[e], indent);
       }
       agg_ne[i] = ne;
     }
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

  if (is_variadic_callee)
  {
    emit(" (");
    bool first = true;
    int ai = sret ? 1 : 0;
    if (sret)
    {
      emit("ptr");
      first = false;
    }
    for (Node *arg = node->args; arg; arg = arg->next)
    {
      if (!first)
        emit(", ");
      // `byval` is an argument attribute and may not appear in the callee
      // function-type list, so emit a plain pointer type here.  Small
      // aggregates passed by value expand into their scalar eightbyte types.
      if (ai < 64 && agg_ne[ai])
      {
        for (int e = 0; e < agg_ne[ai]; e++)
        {
          if (e)
            emit(", ");
          emit("%s", agg_ty[ai * 2 + e]);
        }
      }
      else if (arg->ty->kind == TY_STRUCT || arg->ty->kind == TY_UNION)
      {
        emit("ptr");
      }
      else
        emit_type_str(arg->ty);
      first = false;
      ai++;
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
    else if (arg_tys[i]->kind == TY_STRUCT || arg_tys[i]->kind == TY_UNION)
    {
      if (is_libc && i < 64 && agg_ne[i])
      {
        for (int e = 0; e < agg_ne[i]; e++)
        {
          if (e)
            emit(", ");
          emit("%s %s", agg_ty[i * 2 + e], agg_val[i * 2 + e]);
        }
      }
      else if (is_libc)
      {
        int al = ir_type_align(arg_tys[i]);
        emit("ptr byval(");
        emit_llvm_aggr_type(arg_tys[i]);
        emit(")");
        if (al > 16)
          emit(" align %d", al);
        emit(" %s", arg_regs[i]);
      }
      else if (is_variadic_callee)
      {
        // chibicc-compiled variadic functions receive struct/union arguments
        // as a hidden byval pointer, matching their definition (see the
        // parameter emission in emit_ir), so the LLVM stdarg machinery can
        // read them from the stack.
        int al = ir_type_align(arg_tys[i]);
        emit("ptr byval(");
        emit_llvm_aggr_type(arg_tys[i]);
        emit(")");
        if (al > 16)
          emit(" align %d", al);
        emit(" %s", arg_regs[i]);
      }
       else
       {
         emit("ptr %s", arg_regs[i]);
       }
    }
    else
    {
      emit_type_str(arg_tys[i]);
      emit(" %s", arg_regs[i]);
    }
  }
  emit(")\n");

  // A call to a __attribute__((noreturn)) function never returns, so the
  // current block has no implicit terminator.  Emit an `unreachable`
  // instruction (and mark the block terminated) so the IR stays valid;
  // otherwise llc rejects the enclosing function with "expected instruction
  // opcode" on the closing brace.
  bool callee_noreturn = false;
  if (is_direct && node->lhs->var)
    callee_noreturn = node->lhs->var->is_noreturn;
  if (callee_noreturn)
  {
    emit_indent(indent);
    emit("unreachable\n");
    is_terminated = true;
  }

  if (arg_regs)
    free(arg_regs);
  if (arg_tys)
    free(arg_tys);
  free(agg_ne);
  if (sret)
    return var_ptr(node->ret_buffer);
  return reg;
}


const char *gen_ir_stmt_expr(Node *node, int indent)
{

  for (Node *n = node->body; n; n = n->next)
  {
    if (n->next)
    {
      emit_stmt(n, indent, NULL);
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
      emit_stmt(n, indent, NULL);
    }
  }
  return NULL;
}


const char *gen_ir_alloc(Node *node, int indent)
{

  const char *size = emit_expr(node->lhs, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = alloca i8, i64 %s\n", r, size);
  return r;
}


const char *gen_ir_pos(Node *node, int indent)
{
  return emit_expr(node->lhs, indent);
}

const char *gen_ir_builtin_memcpy(Node *node, int indent)
{

  const char *dest = emit_expr(node->builtin_dest, indent);
  const char *src = emit_expr(node->builtin_src, indent);
  const char *size = emit_expr(node->builtin_size, indent);
  emit_indent(indent);
  emit("call void @llvm.memcpy.p0.p0.i64(ptr %s, ptr %s, i64 %s, i1 false)\n", dest, src, size);
  return dest;
}


const char *gen_ir_builtin_memset(Node *node, int indent)
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


// Truncate a 64-bit value to 32 bits (used after the 64-bit builtins whose
// result must be returned as an int).
static const char *trunc_to_i32(const char *reg, int indent)
{
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = trunc i64 %s to i32\n", r, reg);
  return r;
}

// __builtin_clz / __builtin_clzl.  LLVM's ctlz returns N for a zero input,
// but GCC's builtins (implemented via `bsr; xor $(N-1)`) yield N-1 for zero.
// Subtract one when the input is zero to match GCC's behaviour.  The 64-bit
// variant additionally truncates the result back to i32.
static const char *gen_ir_ctlz(Node *node, int indent, int bits)
{
  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i%d @llvm.ctlz.i%d(i%d %s, i1 false)\n", r, bits, bits, bits, val);
  const char *iszero = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq i%d %s, 0\n", iszero, bits, val);
  const char *dec = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i%d\n", dec, iszero, bits);
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = sub i%d %s, %s\n", res, bits, r, dec);
  return bits == 32 ? res : trunc_to_i32(res, indent);
}

const char *gen_ir_builtin_clz(Node *node, int indent)
{
  return gen_ir_ctlz(node, indent, 32);
}

const char *gen_ir_builtin_clzl(Node *node, int indent)
{
  return gen_ir_ctlz(node, indent, 64);
}


static const char *gen_ir_cttz(Node *node, int indent, int bits)
{
  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i%d @llvm.cttz.i%d(i%d %s, i1 false)\n", r, bits, bits, bits, val);
  return bits == 32 ? r : trunc_to_i32(r, indent);
}

const char *gen_ir_builtin_ctz(Node *node, int indent)
{
  return gen_ir_cttz(node, indent, 32);
}

const char *gen_ir_builtin_ctzl(Node *node, int indent)
{
  return gen_ir_cttz(node, indent, 64);
}


static const char *gen_ir_ctpop(Node *node, int indent, int bits)
{
  const char *val = emit_expr(node->builtin_val, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i%d @llvm.ctpop.i%d(i%d %s)\n", r, bits, bits, bits, val);
  return bits == 32 ? r : trunc_to_i32(r, indent);
}

const char *gen_ir_popcount(Node *node, int indent)
{
  return gen_ir_ctpop(node, indent, 32);
}

const char *gen_ir_popcountl(Node *node, int indent)
{
  return gen_ir_ctpop(node, indent, 64);
}


const char *gen_ir_expect(Node *node, int indent)
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


const char *gen_ir_abort(Node *node, int indent)
{

  emit_indent(indent);
  emit("call void @abort()\n");
  emit_indent(indent);
  emit("unreachable\n");
  is_terminated = true;
  return NULL;
}


const char *gen_ir_return_addr(Node *node, int indent)
{

  int level = (int)eval(node->lhs);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call ptr @llvm.returnaddress(i32 %d)\n", r, level);
  return r;
}


const char *gen_ir_builtin_frame_address(Node *node, int indent)
{

  int level = (int)eval(node->lhs);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call ptr @llvm.frameaddress(i32 %d)\n", r, level);
  return r;
}


const char *gen_ir_unreachable(Node *node, int indent)
{
  return NULL;
}

const char *gen_ir_builtin_bswap16(Node *node, int indent)
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


const char *gen_ir_builtin_bswap32(Node *node, int indent)
{

  const char *val = emit_expr(node->builtin_val, indent);
  int in_bits = int_type_bits(node->builtin_val->ty);
  if (in_bits > 0 && in_bits != 32) {
    const char *adj = new_reg();
    emit_indent(indent);
    if (in_bits < 32)
      emit("%s = zext i%d %s to i32\n", adj, in_bits, val);
    else
      emit("%s = trunc i%d %s to i32\n", adj, in_bits, val);
    val = adj;
  }
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i32 @llvm.bswap.i32(i32 %s)\n", r, val);
  return r;
}


const char *gen_ir_builtin_bswap64(Node *node, int indent)
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


const char *gen_ir_x86_rdpid(Node *node, int indent)
{
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i32 asm \".byte 0xf3, 0x0f, 0xc7, 0xf8\", \"={eax}\"()\n", r);
  return r;
}

// BEXTR_u32/u64 (software implementation, mirroring gen_bextr_u32/64 in
// builtin.c).  ctrl encodes (len << 8) | start, both 8-bit fields.
//   len   = (ctrl >> 8) & 0xFF
//   start = ctrl & 0xFF
//   if len == 0 or start >= bits: result = 0
//   else: eff_len = min(len, bits - start)
//         result   = (src >> start) & ((1 << eff_len) - 1)
//         (when eff_len == bits the mask is all ones, so result = src >> start)
const char *gen_ir_bextr(Node *node, int indent)
{
  int bits = node->ty->size * 8;

  const char *src;
  const char *ctrl;
  if (node->builtin_nargs >= 2)
  {
    src = emit_expr(node->builtin_args[0], indent);
    ctrl = emit_expr(node->builtin_args[1], indent);
  }
  else
  {
    src = emit_expr(node->lhs, indent);
    ctrl = emit_expr(node->rhs, indent);
  }

  const char *start = new_reg();
  emit_indent(indent);
  emit("%s = and i%d %s, %d\n", start, bits, ctrl, 0xFF);
  const char *len_shift = new_reg();
  emit_indent(indent);
  emit("%s = lshr i%d %s, 8\n", len_shift, bits, ctrl);
  const char *len = new_reg();
  emit_indent(indent);
  emit("%s = and i%d %s, %d\n", len, bits, len_shift, 0xFF);

  const char *len_zero = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq i%d %s, 0\n", len_zero, bits, len);
  const char *start_big = new_reg();
  emit_indent(indent);
  emit("%s = icmp uge i%d %s, %d\n", start_big, bits, start, bits);
  const char *is_zero = new_reg();
  emit_indent(indent);
  emit("%s = or i1 %s, %s\n", is_zero, len_zero, start_big);

  const char *zero_label = format(".L.bextr0.%d", ir_reg++);
  const char *cont_label = format(".L.bextr1.%d", ir_reg++);
  const char *end_label = format(".L.bextr2.%d", ir_reg++);
  emit_indent(indent);
  emit("br i1 %s, label %%%s, label %%%s\n", is_zero, zero_label, cont_label);
  is_terminated = true;

  emit_label(zero_label);
  const char *zero_val = new_reg();
  emit_indent(indent);
  emit("%s = add i%d 0, 0\n", zero_val, bits);
  emit_indent(indent);
  emit("br label %%%s\n", end_label);
  is_terminated = true;

  emit_label(cont_label);
  const char *max_len = new_reg();
  emit_indent(indent);
  emit("%s = sub i%d %d, %s\n", max_len, bits, bits, start);
  const char *max_cmp = new_reg();
  emit_indent(indent);
  emit("%s = icmp ule i%d %s, %s\n", max_cmp, bits, len, max_len);
  const char *eff_len = new_reg();
  emit_indent(indent);
  emit("%s = select i1 %s, i%d %s, i%d %s\n",
       eff_len, max_cmp, bits, len, bits, max_len);
  const char *shifted = new_reg();
  emit_indent(indent);
  emit("%s = lshr i%d %s, %s\n", shifted, bits, src, start);
  const char *eff_is_full = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq i%d %s, %d\n", eff_is_full, bits, eff_len, bits);
  const char *mask_label = format(".L.bextr3.%d", ir_reg++);
  const char *cont2_label = format(".L.bextr4.%d", ir_reg++);
  emit_indent(indent);
  emit("br i1 %s, label %%%s, label %%%s\n", eff_is_full, cont2_label, mask_label);
  is_terminated = true;

  emit_label(mask_label);
  const char *mask = new_reg();
  emit_indent(indent);
  emit("%s = shl i%d 1, %s\n", mask, bits, eff_len);
  const char *maskm1 = new_reg();
  emit_indent(indent);
  emit("%s = sub i%d %s, 1\n", maskm1, bits, mask);
  const char *masked = new_reg();
  emit_indent(indent);
  emit("%s = and i%d %s, %s\n", masked, bits, shifted, maskm1);
  emit_indent(indent);
  emit("br label %%%s\n", cont2_label);
  is_terminated = true;

  emit_label(cont2_label);
  const char *cont_res = new_reg();
  emit_indent(indent);
  emit("%s = phi i%d [ %s, %%%s ], [ %s, %%%s ]\n",
       cont_res, bits, shifted, cont_label, masked, mask_label);
  emit_indent(indent);
  emit("br label %%%s\n", end_label);
  is_terminated = true;

  emit_label(end_label);
  const char *final = new_reg();
  emit_indent(indent);
  emit("%s = phi i%d [ %s, %%%s ], [ %s, %%%s ]\n",
       final, bits, zero_val, zero_label, cont_res, cont2_label);
  return final;
}

// zext/trunc an integer register to a target bit width (unsigned semantics).
const char *cast_uint_width(const char *reg, int src_bits,
                                  int dst_bits, int indent)
{
  if (src_bits <= 0 || src_bits == dst_bits)
    return reg;
  const char *r = new_reg();
  emit_indent(indent);
  if (src_bits < dst_bits)
    emit("%s = zext i%d %s to i%d\n", r, src_bits, reg, dst_bits);
  else
    emit("%s = trunc i%d %s to i%d\n", r, src_bits, reg, dst_bits);
  return r;
}

// CRC32 (SSE4.2 crc32b/w/d/q).  LLVM's @llvm.x86.sse42.crc32.*
// intrinsics are not selectable on this LLVM, so emit the matching x86
// `crc32` asm instruction directly.  crc32 reads/writes the crc in
// eax/rax (tied input/output) and folds in the value operand.
const char *gen_ir_crc32(Node *node, int indent)
{
  Node *oper_crc = node->lhs ? node->lhs : node->builtin_args[0];
  Node *oper_val = node->lhs ? node->rhs : node->builtin_args[1];
  if (!oper_crc || !oper_val)
    return gen_ir_default(node, indent);
  const char *crc = emit_expr(oper_crc, indent);
  const char *val = emit_expr(oper_val, indent);

  int crc_bits = int_type_bits(oper_crc->ty);
  if (crc_bits <= 0) crc_bits = oper_crc->ty->size * 8;
  int val_bits = int_type_bits(oper_val->ty);
  if (val_bits <= 0) val_bits = oper_val->ty->size * 8;

  int crc_w, val_w, res_w;
  const char *suffix;
  switch (node->kind)
  {
  case ND_CRC32QI: crc_w = 32; val_w = 8;  res_w = 32; suffix = "b"; break;
  case ND_CRC32HI: crc_w = 32; val_w = 16; res_w = 32; suffix = "w"; break;
  case ND_CRC32SI: crc_w = 32; val_w = 32; res_w = 32; suffix = "l"; break;
  case ND_CRC32DI: crc_w = 64; val_w = 64; res_w = 64; suffix = "q"; break;
  default: return gen_ir_default(node, indent);
  }

  crc = cast_uint_width(crc, crc_bits, crc_w, indent);
  val = cast_uint_width(val, val_bits, val_w, indent);

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = call i%d asm \"crc32%s $2, $0\", "
       "\"=r,0,r,~{dirflag},~{fpsr},~{flags}\"(i%d %s, i%d %s)\n",
       res, res_w, suffix, crc_w, crc, val_w, val);
  return res;
}

// cvtpi2ps: convert the two 32-bit ints of an __m64 (MMX) into the low
// two floats of a __m128, preserving the upper two floats of the __m128.
const char *gen_ir_cvtpi2ps(Node *node, int indent)
{
  Node *oper_a = node->lhs ? node->lhs : node->builtin_args[0];
  Node *oper_b = node->lhs ? node->rhs : node->builtin_args[1];
  if (!oper_a || !oper_b)
    return gen_ir_default(node, indent);
  const char *a = emit_expr(oper_a, indent);
  const char *b = emit_expr(oper_b, indent);
  Type *a_ty = oper_a->ty;
  Type *b_ty = oper_b->ty;

  const char *a_bc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", a_bc);
  emit_type_str(a_ty);
  emit(" %s to <4 x float>\n", a);

  const char *b_bc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", b_bc);
  emit_type_str(b_ty);
  emit(" %s to <2 x i32>\n", b);

  // Convert the two 32-bit integers of b to float and insert them into the
  // low two lanes of a, preserving a's upper two lanes.  (The
  // @llvm.x86.sse2.cvtpi2ps intrinsic is unavailable, so we expand it
  // manually.)
  const char *b0 = new_reg();
  emit_indent(indent);
  emit("%s = extractelement <2 x i32> %s, i32 0\n", b0, b_bc);
  const char *b1 = new_reg();
  emit_indent(indent);
  emit("%s = extractelement <2 x i32> %s, i32 1\n", b1, b_bc);
  const char *f0 = new_reg();
  emit_indent(indent);
  emit("%s = sitofp i32 %s to float\n", f0, b0);
  const char *f1 = new_reg();
  emit_indent(indent);
  emit("%s = sitofp i32 %s to float\n", f1, b1);
  const char *r1 = new_reg();
  emit_indent(indent);
  emit("%s = insertelement <4 x float> %s, float %s, i32 0\n", r1, a_bc, f0);
  const char *r2 = new_reg();
  emit_indent(indent);
  emit("%s = insertelement <4 x float> %s, float %s, i32 1\n", r2, r1, f1);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast <4 x float> %s to ", out, r2);
  emit_type_str(node->ty);
  emit("\n");
  return out;
}


const char *gen_ir_x86_rdfsbase(Node *node, int indent)
{
  int bits = (node->kind == ND_RDFSBASE64) ? 64 : 32;
  const char *r = new_reg();
  emit_indent(indent);
  if (bits == 64)
    emit("%s = call i64 asm \".byte 0xf3, 0x48, 0x0f, 0xae, 0xc0\", \"={rax}\"()\n", r);
  else
    emit("%s = call i32 asm \".byte 0xf3, 0x0f, 0xae, 0xc0\", \"={eax}\"()\n", r);
  return r;
}


const char *gen_ir_x86_rdgsbase(Node *node, int indent)
{
  int bits = (node->kind == ND_RDGSBASE64) ? 64 : 32;
  const char *r = new_reg();
  emit_indent(indent);
  if (bits == 64)
    emit("%s = call i64 asm \".byte 0xf3, 0x48, 0x0f, 0xae, 0xc8\", \"={rax}\"()\n", r);
  else
    emit("%s = call i32 asm \".byte 0xf3, 0x0f, 0xae, 0xc8\", \"={eax}\"()\n", r);
  return r;
}

// === x86 system/intrinsic builtins missing from the LLVM backend ===

const char *gen_ir_x86_rdtsc(Node *node, int indent)
{
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i64 @llvm.readcyclecounter()\n", r);
  return r;
}

const char *gen_ir_zext_to_i64(const char *v, Type *ty, int indent)
{
  int bits = ty ? int_type_bits(ty) : 64;
  if (bits >= 64)
    return v;
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = zext i%d %s to i64\n", r, bits, v);
  return r;
}

static const char *gen_ir_zext_to_bits(const char *v, Type *ty, int dst_bits, int indent)
{
  int bits = ty ? int_type_bits(ty) : dst_bits;
  if (bits >= dst_bits)
    return v;
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = zext i%d %s to i%d\n", r, bits, v, dst_bits);
  return r;
}

const char *gen_ir_x86_rdpmc(Node *node, int indent)
{
  const char *in = emit_expr(node->lhs, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call { i32, i32 } asm sideeffect \"rdpmc\", \"={eax},={edx},{ecx}\"(i32 %s)\n",
       r, in);
  const char *lo = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue { i32, i32 } %s, 0\n", lo, r);
  const char *hi = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue { i32, i32 } %s, 1\n", hi, r);
  return lo;
}

const char *gen_ir_x86_rdtscp(Node *node, int indent)
{
  const char *auxptr = emit_expr(node->lhs, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call { i32, i32, i32 } asm sideeffect \"rdtscp\", \"={eax},={edx},={ecx}\"()\n",
       r);
  const char *lo = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue { i32, i32, i32 } %s, 0\n", lo, r);
  const char *hi = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue { i32, i32, i32 } %s, 1\n", hi, r);
  const char *auxv = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue { i32, i32, i32 } %s, 2\n", auxv, r);
  emit_indent(indent);
  emit("store i32 %s, ptr %s\n", auxv, auxptr);
  return lo;
}

const char *gen_ir_x86_readeflags(Node *node, int indent)
{
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i64 asm sideeffect \"pushfq\\0Apopq $0\", \"=r\"()\n", r);
  return r;
}

const char *gen_ir_x86_writeeflags(Node *node, int indent)
{
  const char *val = emit_expr(node->lhs, indent);
  const char *v64;
  if (node->lhs->ty->size >= 8)
    v64 = val;
  else
  {
    v64 = new_reg();
    emit_indent(indent);
    emit("%s = zext i32 %s to i64\n", v64, val);
  }
  emit_indent(indent);
  emit("call void asm sideeffect \"pushq $0\\0Apopfq\", \"{rax}\"(i64 %s)\n", v64);
  return NULL;
}

const char *gen_ir_x86_rdsspq(Node *node, int indent)
{
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i64 asm sideeffect \"rdsspq $0\", \"=r\"()\n", r);
  return r;
}

const char *gen_ir_x86_bsrsi(Node *node, int indent)
{
  const char *v = emit_expr(node->lhs, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i32 asm sideeffect \"bsrl $1, $0\", \"=r,r\"(i32 %s)\n", r, v);
  return r;
}

const char *gen_ir_x86_bsrdi(Node *node, int indent)
{
  const char *v = emit_expr(node->lhs, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i64 asm sideeffect \"bsrq $1, $0\", \"=r,r\"(i64 %s)\n", r, v);
  return r;
}

const char *gen_ir_x86_tzcnt_u16(Node *node, int indent)
{
  const char *v = emit_expr(node->lhs, indent);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = call i16 @llvm.cttz.i16(i16 %s, i1 false)\n", r, v);
  return r;
}

const char *gen_ir_x86_sbb_u32(Node *node, int indent)
{
  const char *bin = gen_ir_zext_to_bits(emit_expr(node->builtin_args[0], indent),
                                        node->builtin_args[0]->ty, 32, indent);
  const char *a = emit_expr(node->builtin_args[1], indent);
  const char *b = emit_expr(node->builtin_args[2], indent);
  const char *outptr = emit_expr(node->builtin_args[3], indent);

  const char *tmp = new_reg();
  emit_indent(indent);
  emit("%s = sub i32 %s, %s\n", tmp, a, b);
  const char *borrow1 = new_reg();
  emit_indent(indent);
  emit("%s = icmp ult i32 %s, %s\n", borrow1, a, b);
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = sub i32 %s, %s\n", res, tmp, bin);
  const char *borrow2 = new_reg();
  emit_indent(indent);
  emit("%s = icmp ult i32 %s, %s\n", borrow2, tmp, bin);
  const char *borrow = new_reg();
  emit_indent(indent);
  emit("%s = or i1 %s, %s\n", borrow, borrow1, borrow2);
  const char *bw = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i32\n", bw, borrow);
  emit_indent(indent);
  emit("store i32 %s, ptr %s\n", bw, outptr);
  return res;
}

const char *gen_ir_x86_sbb_u64(Node *node, int indent)
{
  const char *bin = gen_ir_zext_to_i64(emit_expr(node->builtin_args[0], indent),
                                       node->builtin_args[0]->ty, indent);
  const char *a = gen_ir_zext_to_i64(emit_expr(node->builtin_args[1], indent),
                                     node->builtin_args[1]->ty, indent);
  const char *b = gen_ir_zext_to_i64(emit_expr(node->builtin_args[2], indent),
                                     node->builtin_args[2]->ty, indent);
  const char *outptr = emit_expr(node->builtin_args[3], indent);

  const char *tmp = new_reg();
  emit_indent(indent);
  emit("%s = sub i64 %s, %s\n", tmp, a, b);
  const char *borrow1 = new_reg();
  emit_indent(indent);
  emit("%s = icmp ult i64 %s, %s\n", borrow1, a, b);
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = sub i64 %s, %s\n", res, tmp, bin);
  emit_indent(indent);
  emit("store i64 %s, ptr %s\n", res, outptr);
  const char *borrow2 = new_reg();
  emit_indent(indent);
  emit("%s = icmp ult i64 %s, %s\n", borrow2, tmp, bin);
  const char *borrow = new_reg();
  emit_indent(indent);
  emit("%s = or i1 %s, %s\n", borrow, borrow1, borrow2);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i8\n", r, borrow);
  return r;
}

static const char *gen_ir_x86_addcarryx(Node *node, int indent, int bits)
{
  const char *cin = emit_expr(node->builtin_args[0], indent);
  const char *x = emit_expr(node->builtin_args[1], indent);
  const char *y = emit_expr(node->builtin_args[2], indent);
  const char *outptr = emit_expr(node->builtin_args[3], indent);
  if (bits == 64) {
    cin = gen_ir_zext_to_i64(cin, node->builtin_args[0]->ty, indent);
    x = gen_ir_zext_to_i64(x, node->builtin_args[1]->ty, indent);
    y = gen_ir_zext_to_i64(y, node->builtin_args[2]->ty, indent);
  } else {
    cin = gen_ir_zext_to_bits(cin, node->builtin_args[0]->ty, bits, indent);
  }

  const char *sum = new_reg();
  emit_indent(indent);
  emit("%s = add i%d %s, %s\n", sum, bits, x, y);
  const char *sum2 = new_reg();
  emit_indent(indent);
  emit("%s = add i%d %s, %s\n", sum2, bits, sum, cin);
  emit_indent(indent);
  emit("store i%d %s, ptr %s\n", bits, sum2, outptr);
  const char *carry1 = new_reg();
  emit_indent(indent);
  emit("%s = icmp ult i%d %s, %s\n", carry1, bits, sum, x);
  const char *carry2 = new_reg();
  emit_indent(indent);
  emit("%s = icmp ult i%d %s, %s\n", carry2, bits, sum2, cin);
  const char *carry = new_reg();
  emit_indent(indent);
  emit("%s = or i1 %s, %s\n", carry, carry1, carry2);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i8\n", r, carry);
  return r;
}

const char *gen_ir_x86_addcarryx_u32(Node *node, int indent)
{
  return gen_ir_x86_addcarryx(node, indent, 32);
}

const char *gen_ir_x86_addcarryx_u64(Node *node, int indent)
{
  return gen_ir_x86_addcarryx(node, indent, 64);
}

const char *gen_ir_float_const_builtin(Node *node, int indent)
{
  const char *r = new_reg();
  emit_indent(indent);
  emit_float_const(r, node);
  return r;
}


const char *gen_ir_builtin_isnan(Node *node, int indent)
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

// __builtin_fpclassify(nan, inf, normal, subnormal, zero, x): return the
// integer constant matching x's floating-point class.  Implemented portably
// by inspecting the integer bit pattern of the value (exponent/mantissa
// fields) rather than via fcmp, which avoids target-specific intrinsics and a
// miscompilation of paired fcwrites on the same operand seen in this LLVM.
//   exp == all-ones : inf (mantissa 0) or nan (mantissa != 0)
//   exp == 0        : zero (mantissa 0) or subnormal (mantissa != 0)
//   otherwise       : normal
const char *gen_ir_fpclassify(Node *node, int indent)
{
  const char *x = emit_expr(node->fpc->node, indent);
  Type *ty = node->fpc->node->ty;

  const char *tystr, *intstr;
  int exp_shift, exp_mask;
  unsigned long mant_mask;
  if (ty->kind == TY_FLOAT) {
    tystr = "float"; intstr = "i32";
    exp_shift = 23; exp_mask = 0xFF; mant_mask = 0x7FFFFFUL;
  } else if (ty->kind == TY_LDOUBLE) {
    tystr = "x86_fp80"; intstr = "i80";
    exp_shift = 64; exp_mask = 0x7FFF; mant_mask = 0xFFFFFFFFFFFFFFFFUL;
  } else {
    tystr = "double"; intstr = "i64";
    exp_shift = 52; exp_mask = 0x7FF; mant_mask = 0xFFFFFFFFFFFFFUL;
  }

  const char *bits = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to %s\n", bits, tystr, x, intstr);

  const char *exp = new_reg();
  emit_indent(indent);
  emit("%s = lshr %s %s, %d\n", exp, intstr, bits, exp_shift);
  const char *expm = new_reg();
  emit_indent(indent);
  emit("%s = and %s %s, %d\n", expm, intstr, exp, exp_mask);

  const char *mant = new_reg();
  emit_indent(indent);
  emit("%s = and %s %s, %lu\n", mant, intstr, bits, mant_mask);

  const char *is_zeroexp = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq %s %s, 0\n", is_zeroexp, intstr, expm);
  const char *is_maxexp = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq %s %s, %d\n", is_maxexp, intstr, expm, exp_mask);

  const char *is_zeromant = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq %s %s, 0\n", is_zeromant, intstr, mant);
  const char *is_nonzeromant = new_reg();
  emit_indent(indent);
  emit("%s = icmp ne %s %s, 0\n", is_nonzeromant, intstr, mant);

  const char *zero_or_sub = new_reg();
  emit_indent(indent);
  emit("%s = select i1 %s, i32 %d, i32 %d\n", zero_or_sub, is_zeromant,
       node->fpc->args[4], node->fpc->args[3]);
  const char *inf_or_nan = new_reg();
  emit_indent(indent);
  emit("%s = select i1 %s, i32 %d, i32 %d\n", inf_or_nan, is_nonzeromant,
       node->fpc->args[0], node->fpc->args[1]);
  const char *special = new_reg();
  emit_indent(indent);
  emit("%s = select i1 %s, i32 %s, i32 %d\n", special, is_maxexp,
       inf_or_nan, node->fpc->args[2]);
  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = select i1 %s, i32 %s, i32 %s\n", result, is_zeroexp,
       zero_or_sub, special);
  return result;
}

// __builtin_isunordered(a, b): true iff a or b is NaN.  fcmp uno yields an
// i1 which we zero-extend to the chibicc i32 convention.
const char *gen_ir_isunordered(Node *node, int indent)
{
  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);
  Type *ty = node->lhs->ty;
  const char *cmp = new_reg();
  emit_indent(indent);
  if (ty->kind == TY_FLOAT)
    emit("%s = fcmp uno float %s, %s\n", cmp, a, b);
  else if (ty->kind == TY_LDOUBLE)
    emit("%s = fcmp uno x86_fp80 %s, %s\n", cmp, a, b);
  else
    emit("%s = fcmp uno double %s, %s\n", cmp, a, b);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i32\n", r, cmp);
  return r;
}


const char *gen_ir_parity(Node *node, int indent)
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


const char *gen_ir_parityl(Node *node, int indent)
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


const char *gen_ir_stdc_bit_ceil(Node *node, int indent)
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


const char *gen_ir_overflow_arith(Node *node, int indent, const char *op)
{
  Type *dest_ty = node->builtin_dest->ty->base;
  int dest_bits = int_type_bits(dest_ty);
  if (dest_bits <= 0) dest_bits = 32;

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);

  int lhs_bits = int_type_bits(node->lhs->ty);
  int rhs_bits = int_type_bits(node->rhs->ty);
  if (lhs_bits <= 0) lhs_bits = 32;
  if (rhs_bits <= 0) rhs_bits = 32;

  int wide_bits;
  if (dest_bits >= 128 || lhs_bits > 128 || rhs_bits > 128)
    wide_bits = 256;
  else if (dest_bits >= 64 || lhs_bits > 64 || rhs_bits > 64)
    wide_bits = 128;
  else
    wide_bits = 64;

  const char *l_ext = l;
  if (lhs_bits < wide_bits) {
    l_ext = new_reg();
    emit_indent(indent);
    emit("%s = %s i%d %s to i%d\n", l_ext,
         node->lhs->ty->is_unsigned ? "zext" : "sext", lhs_bits, l, wide_bits);
  }
  const char *r_ext = r;
  if (rhs_bits < wide_bits) {
    r_ext = new_reg();
    emit_indent(indent);
    emit("%s = %s i%d %s to i%d\n", r_ext,
         node->rhs->ty->is_unsigned ? "zext" : "sext", rhs_bits, r, wide_bits);
  }

  const char *result = new_reg();
  emit_indent(indent);
  emit("%s = %s i%d %s, %s\n", result, op, wide_bits, l_ext, r_ext);

  const char *val = new_reg();
  emit_indent(indent);
  emit("%s = trunc i%d %s to i%d\n", val, wide_bits, result, dest_bits);
  const char *dest_ptr = emit_expr(node->builtin_dest, indent);
  emit_indent(indent);
  emit("store i%d %s, ptr %s\n", dest_bits, val, dest_ptr);

  const char *val_ext = new_reg();
  emit_indent(indent);
  emit("%s = %s i%d %s to i%d\n", val_ext,
       dest_ty->is_unsigned ? "zext" : "sext", dest_bits, val, wide_bits);

  const char *overflow = new_reg();
  emit_indent(indent);
  emit("%s = icmp ne i%d %s, %s\n", overflow, wide_bits, result, val_ext);
  return overflow;
}


const char *gen_ir_builtin_add_overflow(Node *node, int indent)
{
  return gen_ir_overflow_arith(node, indent, "add");
}


const char *gen_ir_builtin_sub_overflow(Node *node, int indent)
{
  return gen_ir_overflow_arith(node, indent, "sub");
}


const char *gen_ir_builtin_mul_overflow(Node *node, int indent)
{
  return gen_ir_overflow_arith(node, indent, "mul");
}


const char *gen_ir_uadd_overflow(Node *node, int indent)
{
  return gen_ir_overflow_arith(node, indent, "add");
}


const char *gen_ir_umul_overflow(Node *node, int indent)
{
  return gen_ir_overflow_arith(node, indent, "mul");
}


// Computed-goto (&&label / goto *p) support.  An LLVM `indirectbr` must
// enumerate every basic block that can be reached through a blockaddress
// taken in the current function, otherwise the IR is invalid and the
// optimizer may delete the targets (causing a crash).  We collect the
// labels referenced by ND_LABEL_VAL nodes as we emit them.
static char **label_addr_list = NULL;
static int label_addr_count = 0;
static int label_addr_cap = 0;

void register_label_addr(const char *label)
{
  for (int i = 0; i < label_addr_count; i++)
    if (strcmp(label_addr_list[i], label) == 0)
      return;
  if (label_addr_count >= label_addr_cap)
  {
    label_addr_cap = label_addr_cap ? label_addr_cap * 2 : 8;
    label_addr_list = realloc(label_addr_list, (size_t)label_addr_cap * sizeof(char *));
  }
  label_addr_list[label_addr_count++] = strdup(label);
}

static void reset_label_addrs(void)
{
  label_addr_count = 0;
}

// Collect every basic-block label (ND_LABEL) reachable from `n` so that
// `indirectbr` can enumerate all possible computed-goto targets, including
// labels only referenced from static array initializers (e.g. `p[] =
// {&&v1, &&v2}`).  Walking the whole function body is safe: LLVM allows the
// destination list to contain labels that are never actually targeted.
static void collect_labels(Node *n)
{
  if (!n)
    return;
  if (n->kind == ND_LABEL && n->unique_label)
    register_label_addr(n->unique_label);
  collect_labels(n->next);
  collect_labels(n->lhs);
  collect_labels(n->rhs);
  collect_labels(n->cond);
  collect_labels(n->then);
  collect_labels(n->els);
  collect_labels(n->init);
  collect_labels(n->body);
  collect_labels(n->args);
  for (int i = 0; i < MAX_BUILTIN_ARGS; i++)
    collect_labels(n->builtin_args[i]);
}

const char *gen_ir_label_val(Node *node, int indent)
{
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = getelementptr i8, ptr blockaddress(@%s, %%%s), i64 0\n",
       r, current_fn->name, node->unique_label);
  register_label_addr(node->unique_label);
  return r;
}


// === Atomic operations ===
//
// All atomic node helpers below emit the corresponding LLVM IR
// (atomicrmw, cmpxchg, load/store atomic, fence).  Each helper returns
// the LLVM register that holds the result, or NULL for void operations
// such as stores, clears, and fences.

const char *gen_ir_cas(Node *node, int indent)
{
  // For ND_CAS (legacy sync-style "compare and swap"), cas_old is a
  // POINTER to the expected value (the parser wraps it with ND_ADDR).
  // We dereference it before passing the value to LLVM's cmpxchg.
  Type *ty = (node->cas_addr && node->cas_addr->ty->base)
             ? node->cas_addr->ty->base : node->ty;
  const char *addr = emit_expr(node->cas_addr, indent);
  const char *cnew = emit_expr(node->cas_new, indent);
  const char *cold = emit_expr(node->cas_old, indent);
  int ordering = node->memorder ? node->memorder : 5;
  const char *old_val = ir_emit_atomic_load(cold, ty, 5, indent);
  old_val = float_val_to_atomic_int(old_val, ty, indent);
  const char *cnew_i = int_val_to_atomic_int(cnew, node->cas_new->ty, ty, indent);
  const char *pair = new_reg();
  emit_indent(indent);
  emit("%s = cmpxchg ptr %s, ", pair, addr);
  emit_atomic_type_str(ty);
  emit(" %s, ", old_val);
  emit_atomic_type_str(ty);
  emit(" %s %s %s\n",
       cnew_i, ir_atomic_ordering(ordering), ir_atomic_ordering(ordering));
  // C11 __atomic_compare_exchange semantics: on failure the actual memory
  // value must be written back to *expected (harmless on success since the
  // old value equals the expected one in that case).  Matches gen_cas in
  // builtin.c which stores the real memory value back to *expected.
  const char *old_mem = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {", old_mem);
  emit_atomic_type_str(ty);
  emit(", i1} %s, 0\n", pair);
  old_mem = atomic_int_to_float_val(old_mem, ty, indent);
  ir_emit_atomic_store(old_mem, cold, ty, ordering, indent, atomic_ir_width(ty));
  // Return the success flag (i1); downstream ND_CAST converts to the
  // user-visible type.
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {", r);
  emit_atomic_type_str(ty);
  emit(", i1} %s, 1\n", pair);
  return r;
}


const char *gen_ir_cas_n(Node *node, int indent)
{
  // For ND_CAS_N (the legacy "__sync_val_compare_and_swap" builtin),
  // cas_old is the expected VALUE (not a pointer).  gen_cas_n in
  // codegen.c likewise treats it as a value (loaded into rax and used
  // directly by `lock cmpxchg`) and returns the OLD value in rax.
  // The node has no usable ty of its own, so we read the memory width
  // from cas_addr->ty->base.
  Type *ty = (node->cas_addr && node->cas_addr->ty->base)
             ? node->cas_addr->ty->base : node->ty;
  const char *addr = emit_expr(node->cas_addr, indent);
  const char *cnew = emit_expr(node->cas_new, indent);
  const char *old_val = emit_expr(node->cas_old, indent);
  int ordering = node->memorder ? node->memorder : 5;
  const char *old_val_i = int_val_to_atomic_int(old_val, node->cas_old->ty, ty, indent);
  const char *cnew_i = int_val_to_atomic_int(cnew, node->cas_new->ty, ty, indent);
  const char *pair = new_reg();
  emit_indent(indent);
  emit("%s = cmpxchg ptr %s, ", pair, addr);
  emit_atomic_type_str(ty);
  emit(" %s, ", old_val_i);
  emit_atomic_type_str(ty);
  emit(" %s %s %s\n",
       cnew_i, ir_atomic_ordering(ordering), ir_atomic_ordering(ordering));
  // Return the OLD value (extractvalue index 0).  Matches gen_cas_n
  // in codegen.c which leaves the previous value of *p in rax after
  // `lock cmpxchg`.
  const char *r_int = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {", r_int);
  emit_atomic_type_str(ty);
  emit(", i1} %s, 0\n", pair);
  const char *r = atomic_int_to_float_val(r_int, ty, indent);
  return r;
}


const char *gen_ir_exch(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  const char *val = emit_expr(node->rhs, indent);
  int vbits = (node->rhs && node->rhs->ty) ? int_type_bits(node->rhs->ty) : 0;
  return ir_emit_atomicrmw("xchg", addr, val, ty,
                           node->memorder ? node->memorder : 5, indent, vbits);
}


const char *gen_ir_exch_n(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  const char *val = emit_expr(node->rhs, indent);
  int vbits = (node->rhs && node->rhs->ty) ? int_type_bits(node->rhs->ty) : 0;
  return ir_emit_atomicrmw("xchg", addr, val, ty,
                           node->memorder ? node->memorder : 5, indent, vbits);
}


const char *gen_ir_cmpxchg(Node *node, int indent)
{
  // For ND_CMPEXCH (from __atomic_compare_exchange), cas_expected is
  // a POINTER to the expected value.  We dereference it before cmpxchg.
  // On failure, the actual memory value must be written back to *expected.
  int succ = node->cas_success ? node->cas_success->val : 5;
  int fail = node->cas_failure ? node->cas_failure->val : 5;
  Type *ty = (node->cas_ptr && node->cas_ptr->ty->base)
             ? node->cas_ptr->ty->base : node->ty;
  const char *ptr = emit_expr(node->cas_ptr, indent);
  const char *expected_ptr = emit_expr(node->cas_expected, indent);
  const char *expected = ir_emit_atomic_load(expected_ptr, ty, 5, indent);
  expected = float_val_to_atomic_int(expected, ty, indent);
  // cas_desired is a pointer (caller passes &desired), so load the value through it.
  const char *desired_ptr = emit_expr(node->cas_desired, indent);
  const char *desired = ir_emit_atomic_load(desired_ptr, ty, 5, indent);
  desired = float_val_to_atomic_int(desired, ty, indent);
  const char *pair = new_reg();
  emit_indent(indent);
  emit("%s = cmpxchg ptr %s, ", pair, ptr);
  emit_atomic_type_str(ty);
  emit(" %s, ", expected);
  emit_atomic_type_str(ty);
  emit(" %s %s %s\n",
       desired, ir_atomic_ordering(succ), ir_atomic_ordering(fail));
  // Extract the old value and write it back to *expected (required by C spec
  // on failure, harmless on success since old==expected in that case).
  const char *old_val = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {", old_val);
  emit_atomic_type_str(ty);
  emit(", i1} %s, 0\n", pair);
  old_val = atomic_int_to_float_val(old_val, ty, indent);
  ir_emit_atomic_store(old_val, expected_ptr, ty, fail, indent,
                        (int_type_bits(ty) > 0 ? int_type_bits(ty)
                         : (ty->size > 0 ? ty->size * 8 : 32)));
  // Return the success flag (index 1).
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {", r);
  emit_atomic_type_str(ty);
  emit(", i1} %s, 1\n", pair);
  return r;
}


const char *gen_ir_cmpxchg_n(Node *node, int indent)
{
  // For ND_CMPEXCH_N (from __atomic_compare_exchange_n), cas_expected
  // is a POINTER to the expected value (matches gen_cmpxchgn in
  // codegen.c, which dereferences it before cmpxchg).  The function
  // returns the bool success flag.  On failure, the actual memory value
  // must be written back to *expected (C11 __atomic_compare_exchange_n spec).
  int succ = node->cas_success ? node->cas_success->val : 5;
  int fail = node->cas_failure ? node->cas_failure->val : 5;
  Type *ty = (node->cas_ptr && node->cas_ptr->ty->base)
             ? node->cas_ptr->ty->base : node->ty;
  const char *ptr = emit_expr(node->cas_ptr, indent);
  const char *expected_ptr = emit_expr(node->cas_expected, indent);
  const char *expected = ir_emit_atomic_load(expected_ptr, ty, 5, indent);
  expected = float_val_to_atomic_int(expected, ty, indent);
  const char *desired = emit_expr(node->cas_desired, indent);
  const char *desired_i = int_val_to_atomic_int(desired, node->cas_desired->ty, ty, indent);
  const char *pair = new_reg();
  emit_indent(indent);
  emit("%s = cmpxchg ptr %s, ", pair, ptr);
  emit_atomic_type_str(ty);
  emit(" %s, ", expected);
  emit_atomic_type_str(ty);
  emit(" %s %s %s\n",
       desired_i, ir_atomic_ordering(succ), ir_atomic_ordering(fail));
  // Extract the old value and write it back to *expected (harmless on success).
  const char *old_val = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {", old_val);
  emit_atomic_type_str(ty);
  emit(", i1} %s, 0\n", pair);
  old_val = atomic_int_to_float_val(old_val, ty, indent);
  ir_emit_atomic_store(old_val, expected_ptr, ty, fail, indent,
                        (int_type_bits(ty) > 0 ? int_type_bits(ty)
                         : (ty->size > 0 ? ty->size * 8 : 32)));
  // Return the success flag (index 1).
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {", r);
  emit_atomic_type_str(ty);
  emit(", i1} %s, 1\n", pair);
  return r;
}


const char *gen_ir_bool_cas(Node *node, int indent)
{
  // For ND_BOOL_CAS (from __sync_bool_compare_and_swap), cas_expected
  // is the expected VALUE (not a pointer).  This matches gen_bool_cas
  // in codegen.c, which uses it directly without dereferencing.
  Type *ty = (node->cas_ptr && node->cas_ptr->ty->base)
             ? node->cas_ptr->ty->base : node->ty;
  const char *ptr = emit_expr(node->cas_ptr, indent);
  const char *expected = emit_expr(node->cas_expected, indent);
  const char *desired = emit_expr(node->cas_desired, indent);
  const char *expected_i = int_val_to_atomic_int(expected, node->cas_expected->ty, ty, indent);
  const char *desired_i = int_val_to_atomic_int(desired, node->cas_desired->ty, ty, indent);
  const char *pair = new_reg();
  emit_indent(indent);
  emit("%s = cmpxchg ptr %s, ", pair, ptr);
  emit_atomic_type_str(ty);
  emit(" %s, ", expected_i);
  emit_atomic_type_str(ty);
  emit(" %s seq_cst seq_cst\n", desired_i);
  const char *r = new_reg();
  emit_indent(indent);
  emit("%s = extractvalue {", r);
  emit_atomic_type_str(ty);
  emit(", i1} %s, 1\n", pair);
  return r;
}


const char *gen_ir_load(Node *node, int indent)
{
  // For ND_LOAD (generic __atomic_load), rhs is a pointer to the destination.
  // We load from lhs and store the result through rhs.
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  const char *val = ir_emit_atomic_load(addr, ty, node->memorder ? node->memorder : 5, indent);
  if (node->rhs && node->rhs->ty && node->rhs->ty->base)
  {
    const char *dst_ptr = emit_expr(node->rhs, indent);
    ir_emit_atomic_store(val, dst_ptr, ty, 5, indent,
                         int_type_bits(ty) == 1 ? 1 : atomic_ir_width(ty));
  }
  return val;
}


const char *gen_ir_load_n(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  return ir_emit_atomic_load(addr, ty, node->memorder ? node->memorder : 5, indent);
}


const char *gen_ir_store(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  const char *val;
  int store_val_bits;
  // For ND_STORE (generic __atomic_store), rhs is a pointer to the value.
  if (node->rhs && node->rhs->ty && node->rhs->ty->base)
  {
    val = ir_emit_atomic_load(emit_expr(node->rhs, indent), ty, 5, indent);
    store_val_bits = int_type_bits(ty) == 1 ? 1 : atomic_ir_width(ty);
  }
  else
  {
    val = emit_expr(node->rhs, indent);
    int rb = node->rhs ? int_type_bits(node->rhs->ty) : 0;
    store_val_bits = rb > 0 ? rb
                    : (node->rhs && node->rhs->ty->size > 0
                         ? node->rhs->ty->size * 8 : 32);
  }
  ir_emit_atomic_store(val, addr, ty,
                       node->memorder ? node->memorder : 5, indent, store_val_bits);
  return NULL;
}


const char *gen_ir_store_n(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  const char *val = emit_expr(node->rhs, indent);
  int rb = node->rhs ? int_type_bits(node->rhs->ty) : 0;
  int store_val_bits = rb > 0 ? rb
                       : (node->rhs && node->rhs->ty->size > 0
                            ? node->rhs->ty->size * 8 : 32);
  ir_emit_atomic_store(val, addr, ty,
                       node->memorder ? node->memorder : 5, indent, store_val_bits);
  return NULL;
}


const char *gen_ir_clear(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  int bits = int_type_bits(ty);
  if (bits <= 0) bits = (ty->size > 0) ? ty->size * 8 : 32;
  const char *zero = new_reg();
  emit_indent(indent);
  emit("%s = add i%d 0, 0\n", zero, bits);
  ir_emit_atomic_store(zero, addr, ty,
                       node->memorder ? node->memorder : 5, indent, bits);
  return NULL;
}


const char *gen_ir_release(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  int bits = int_type_bits(ty);
  if (bits <= 0) bits = (ty->size > 0) ? ty->size * 8 : 32;
  const char *zero = new_reg();
  emit_indent(indent);
  emit("%s = add i%d 0, 0\n", zero, bits);
  ir_emit_atomic_store(zero, addr, ty, 3, indent, bits);  // release semantics
  return NULL;
}


const char *gen_ir_testandset(Node *node, int indent)
{
  // __sync_lock_test_and_set(ptr, val): atomically store val, return old.
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  const char *val = emit_expr(node->rhs, indent);
  int vbits = (node->rhs && node->rhs->ty) ? int_type_bits(node->rhs->ty) : 0;
  return ir_emit_atomicrmw("xchg", addr, val, ty, 5, indent, vbits);
}


const char *gen_ir_testandseta(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  int bits = int_type_bits(ty);
  if (bits <= 0) bits = (ty->size > 0) ? ty->size * 8 : 32;
  const char *one = new_reg();
  emit_indent(indent);
  if (bits == 1)
    emit("%s = add i8 0, 1\n", one);
  else
    emit("%s = add i%d 0, 1\n", one, bits);
  // `one` was generated with i{bits} width (or i8 for bool widened to 8)
  int one_bits = bits < 8 ? 8 : bits;
  return ir_emit_atomicrmw("xchg", addr, one, ty,
                           node->memorder ? node->memorder : 5, indent, one_bits);
}


// Generic helper for atomic read-modify-write returning the old value.
const char *gen_ir_rmw_old(Node *node, int indent, const char *op)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  const char *val = emit_expr(node->rhs, indent);
  int vbits = (node->rhs && node->rhs->ty) ? int_type_bits(node->rhs->ty) : 0;
  return ir_emit_atomicrmw(op, addr, val, ty,
                           node->memorder ? node->memorder : 5, indent, vbits);
}


// Generic helper for atomic read-modify-write returning the new value.
// Emits "old = atomicrmw op; new = old + val;"  (or xor/and/or/nand).
const char *gen_ir_rmw_new(Node *node, int indent, const char *op)
{
  Type *ty = (node->lhs && node->lhs->ty->base) ? node->lhs->ty->base : node->ty;
  const char *addr = emit_expr(node->lhs, indent);
  const char *val = emit_expr(node->rhs, indent);
  int vbits = (node->rhs && node->rhs->ty) ? int_type_bits(node->rhs->ty) : 0;
  const char *old = ir_emit_atomicrmw(op, addr, val, ty,
                                      node->memorder ? node->memorder : 5, indent, vbits);
  // LLVM's atomicrmw always returns the old value.  Compute the new
  // value with the same arithmetic the C abstract machine describes.
  const char *r = new_reg();
  emit_indent(indent);
  if (!strcmp(op, "add") || !strcmp(op, "sub") ||
      !strcmp(op, "or")  || !strcmp(op, "xor") ||
      !strcmp(op, "and") || !strcmp(op, "nand"))
  {
    int bits = int_type_bits(ty);
    if (bits <= 0) bits = (ty->size > 0) ? ty->size * 8 : 32;
    const char *val_ext = val;
    // LLVM requires both operands of an integer binop to be the same
    // width.  If the value has been narrowed by the parser (e.g. when
    // storing into a smaller type), extend it back to the type of the
    // memory location.
    int val_bits = (node->rhs && node->rhs->ty) ? int_type_bits(node->rhs->ty) : bits;
    if (val_bits > 0 && val_bits != bits)
    {
      val_ext = new_reg();
      emit_indent(indent);
      emit("%s = %s i%d %s to i%d\n",
           val_ext, val_bits < bits ? "zext" : "trunc", val_bits, val, bits);
    }
    if (!strcmp(op, "add"))
      emit("%s = add i%d %s, %s\n", r, bits, old, val_ext);
    else if (!strcmp(op, "sub"))
      emit("%s = sub i%d %s, %s\n", r, bits, old, val_ext);
    else if (!strcmp(op, "or"))
      emit("%s = or i%d %s, %s\n", r, bits, old, val_ext);
    else if (!strcmp(op, "xor"))
      emit("%s = xor i%d %s, %s\n", r, bits, old, val_ext);
    else if (!strcmp(op, "and"))
      emit("%s = and i%d %s, %s\n", r, bits, old, val_ext);
    else  // nand: ~(old & val)
    {
      const char *and_r = new_reg();
      emit_indent(indent);
      emit("%s = and i%d %s, %s\n", and_r, bits, old, val_ext);
      emit_indent(indent);
      emit("%s = xor i%d %s, -1\n", r, bits, and_r);
    }
  }
  else
  {
    emit("%s = %s ", r, op);
    emit_type_str(ty);
    emit(" %s, %s\n", old, val);
  }
  return r;
}


const char *gen_ir_fetchadd(Node *node, int indent)
{
  return gen_ir_rmw_old(node, indent, "add");
}


const char *gen_ir_fetchsub(Node *node, int indent)
{
  return gen_ir_rmw_old(node, indent, "sub");
}


const char *gen_ir_addfetch(Node *node, int indent)
{
  return gen_ir_rmw_new(node, indent, "add");
}


const char *gen_ir_subfetch(Node *node, int indent)
{
  return gen_ir_rmw_new(node, indent, "sub");
}


const char *gen_ir_orfetch(Node *node, int indent)
{
  return gen_ir_rmw_new(node, indent, "or");
}


const char *gen_ir_andfetch(Node *node, int indent)
{
  return gen_ir_rmw_new(node, indent, "and");
}


const char *gen_ir_xorfetch(Node *node, int indent)
{
  return gen_ir_rmw_new(node, indent, "xor");
}


const char *gen_ir_fetchand(Node *node, int indent)
{
  return gen_ir_rmw_old(node, indent, "and");
}


const char *gen_ir_fetchor(Node *node, int indent)
{
  return gen_ir_rmw_old(node, indent, "or");
}


const char *gen_ir_fetchxor(Node *node, int indent)
{
  return gen_ir_rmw_old(node, indent, "xor");
}


const char *gen_ir_fetchnand(Node *node, int indent)
{
  return gen_ir_rmw_old(node, indent, "nand");
}


const char *gen_ir_nandfetch(Node *node, int indent)
{
  return gen_ir_rmw_new(node, indent, "nand");
}


const char *gen_ir_add_and_fetch(Node *node, int indent)
{
  return gen_ir_rmw_new(node, indent, "add");
}


const char *gen_ir_sub_and_fetch(Node *node, int indent)
{
  return gen_ir_rmw_new(node, indent, "sub");
}


const char *gen_ir_sync(Node *node, int indent)
{
  emit_indent(indent);
  emit("fence seq_cst\n");
  return NULL;
}


const char *gen_ir_membarrier(Node *node, int indent)
{
  int ordering = (node->lhs && node->ty && node->ty->kind != TY_VOID)
                 ? (int)node->lhs->val : 5;
  emit_indent(indent);
  emit("fence %s\n", ir_atomic_ordering(ordering));
  return NULL;
}


const char *gen_ir_atomic_is_lock_free(Node *node, int indent)
{
  // For x86-64 the lock-free limit is 8 bytes, the size of a register.
  // We compute this dynamically by comparing the size argument against 8.
  int bits = int_type_bits(node->lhs->ty);
  if (bits <= 0) bits = 32;
  const char *size = emit_expr(node->lhs, indent);
  const char *cmp = new_reg();
  emit_indent(indent);
  emit("%s = icmp ule i%d %s, 8\n", cmp, bits, size);
  // The second argument is the optional pointer argument; we ignore it
  // because lock-freeness in chibicc depends only on the requested size.
  if (node->rhs)
    emit_expr(node->rhs, indent);
  // Return the i1 comparison; downstream ND_CAST or implicit promotion
  // converts it to the user-visible type.
  return cmp;
}


// === Universal SSE/AVX binop dispatcher ===
//
// Maps node->kind to a LLVM IR opcode for the floating-point binops that
// codegen.c dispatches via gen_sse_binop{1,2,3}.  Returns 1 (handled) or
// 0 (this node kind is not covered by the universal handler).
bool ir_universal_fbinop_op(Node *node, const char **out_op)
{
  switch (node->kind)
  {
  // Generic + SSE-specific float arithmetic.
  case ND_ADD: case ND_ADDSS: case ND_ADDSD:
    *out_op = "fadd"; return true;
  case ND_SUB: case ND_SUBSS: case ND_SUBSD:
    *out_op = "fsub"; return true;
  case ND_MUL: case ND_MULSS: case ND_MULSD:
    *out_op = "fmul"; return true;
  case ND_DIV: case ND_DIVSS: case ND_DIVSD:
    *out_op = "fdiv"; return true;
  case ND_BITAND:              *out_op = "and";  return true;
  case ND_BITOR:               *out_op = "or";   return true;
  case ND_BITXOR:              *out_op = "xor";  return true;
  case ND_ANDNPS: case ND_ANDNPD: *out_op = "andnot"; return true;
  // Comparisons.
  case ND_CMPEQSS: case ND_CMPEQSD: case ND_CMPEQPS: case ND_CMPEQPD:
  case ND_CMPPD: case ND_CMPPS: case ND_CMPPD256: case ND_CMPPS256:
  case ND_CMPSS: case ND_CMPSD:
    *out_op = "oeq"; return true;
  case ND_CMPLTSS: case ND_CMPLTSD: case ND_CMPLTPS: case ND_CMPLTPD:
    *out_op = "olt"; return true;
  case ND_CMPGTPD: case ND_CMPGTPS:
    *out_op = "ugt"; return true;
  case ND_CMPLESS: case ND_CMPLESD: case ND_CMPLEPS: case ND_CMPLEPD:
    *out_op = "ole"; return true;
  case ND_CMPNEQSS: case ND_CMPNEQSD: case ND_CMPNEQPS: case ND_CMPNEQPD:
    *out_op = "une"; return true;
  case ND_CMPNLTSS: case ND_CMPNLTSD: case ND_CMPNLTPS: case ND_CMPNLTPD:
  case ND_CMPGEPD: case ND_CMPGEPS:
    *out_op = "uge"; return true;
  case ND_CMPNLESS: case ND_CMPNLESD: case ND_CMPNLEPS: case ND_CMPNLEPD:
    *out_op = "ugt"; return true;
  case ND_CMPNGTPD: case ND_CMPNGTPS:
    *out_op = "ole"; return true;
  case ND_CMPNGEPD: case ND_CMPNGEPS:
    *out_op = "olt"; return true;
  case ND_CMPORDSS: case ND_CMPORDSD: case ND_CMPORDPS: case ND_CMPORDPD:
    *out_op = "ord"; return true;
  case ND_CMPUNORDSS: case ND_CMPUNORDSD: case ND_CMPUNORDPS: case ND_CMPUNORDPD:
    *out_op = "uno"; return true;

  // Basic integer vector arithmetic: PADDB/PADDW/PADDD/PADDQ and PSUBB/PSUBW/PSUBD/PSUBQ.
  // These are simple vector adds/subs expressible in LLVM IR without intrinsics.
  case ND_PADDB: case ND_PADDW: case ND_PADDD: case ND_PADDQ:
    *out_op = "add"; return true;
  case ND_PSUBB: case ND_PSUBW: case ND_PSUBD: case ND_PSUBQ:
    *out_op = "sub"; return true;

  // Integer vector bitwise ops.
  case ND_PAND:  *out_op = "and"; return true;
  case ND_PANDN: case ND_PANDN128:
  case ND_ANDNOTSI256: *out_op = "andnot"; return true;
  case ND_POR:   *out_op = "or";  return true;
  case ND_PXOR:  *out_op = "xor"; return true;

  // Float vector bitwise ops (bitcast to integer vector, op, bitcast back).
  case ND_ANDPS: *out_op = "and"; return true;
  case ND_ORPS:  case ND_ORPD:  *out_op = "or";  return true;
  case ND_XORPS: case ND_XORPD: *out_op = "xor"; return true;

  // Float min/max (emulated via fcmp + select in gen_ir_sse_binop).
  case ND_MINSS: case ND_MINSD:
  case ND_MINPS: case ND_MINPD:
  case ND_MAXSS: case ND_MAXSD:
  case ND_MAXPS: case ND_MAXPD:
    *out_op = (node->kind == ND_MINSS || node->kind == ND_MINSD ||
               node->kind == ND_MINPS || node->kind == ND_MINPD)
                  ? "min" : "max";
    return true;

  default:
    return false;
  }
}

// SS/SD arithmetic (addss/addsd/subss/...) only computes on element 0
// and preserves the upper elements from the first operand.
bool is_scalar_sse_arith(Node *node)
{
  switch (node->kind)
  {
  case ND_ADDSS: case ND_ADDSD:
  case ND_SUBSS: case ND_SUBSD:
  case ND_MULSS: case ND_MULSD:
  case ND_DIVSS: case ND_DIVSD:
    return true;
  default:
    return false;
  }
}

// SS/SD comparisons only operate on element 0 and preserve upper elements.
bool is_scalar_sse_cmp(Node *node)
{
  switch (node->kind)
  {
  case ND_CMPEQSS: case ND_CMPEQSD:
  case ND_CMPLTSS: case ND_CMPLTSD:
  case ND_CMPLESS: case ND_CMPLESD:
  case ND_CMPNEQSS: case ND_CMPNEQSD:
  case ND_CMPNLTSS: case ND_CMPNLTSD:
  case ND_CMPNLESS: case ND_CMPNLESD:
  case ND_CMPORDSS: case ND_CMPORDSD:
  case ND_CMPUNORDSS: case ND_CMPUNORDSD:
  case ND_CMPSS: case ND_CMPSD:
    return true;
  default:
    return false;
  }
}

const char *gen_ir_sse_load(Node *node, int indent)
{
  Type *ty = node->ty;
  const char *vec = emit_expr(node->lhs, indent);
  const char *ptr = emit_expr(node->rhs, indent);

  bool is_dbl = (node->kind == ND_LOADHPD || node->kind == ND_LOADLPD);
  bool is_high = (node->kind == ND_LOADHPD || node->kind == ND_LOADHPS);

  const char *loaded = new_reg();
  emit_indent(indent);
  emit("%s = load ", loaded);
  if (is_dbl)
    emit("double, ptr %s\n", ptr);
  else
    emit("<2 x float>, ptr %s\n", ptr);

  const char *cur = vec;
  if (is_dbl)
  {
    int idx = is_high ? 1 : 0;
    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = insertelement ", res);
    emit_type_str(ty);
    emit(" %s, double %s, i32 %d\n", cur, loaded, idx);
    cur = res;
  }
  else
  {
    for (int i = 0; i < 2; i++)
    {
      int idx = (is_high ? 2 : 0) + i;
      const char *elt = new_reg();
      emit_indent(indent);
      emit("%s = extractelement <2 x float> %s, i32 %d\n", elt, loaded, i);
      const char *res = new_reg();
      emit_indent(indent);
      emit("%s = insertelement ", res);
      emit_type_str(ty);
      emit(" %s, float %s, i32 %d\n", cur, elt, idx);
      cur = res;
    }
  }
  return cur;
}

// Emit the LLVM IR spelling of a vector type with `n` elements of `elem`.
void emit_vec_type_str(int n, Type *elem)
{
  emit("<%d x ", n);
  switch (elem->kind)
  {
  case TY_FLOAT:  emit("float");  break;
  case TY_DOUBLE: emit("double"); break;
  case TY_LDOUBLE: emit("x86_fp80"); break;
  case TY_BOOL:   emit("i1");     break;
  case TY_CHAR:   emit("i8");     break;
  case TY_SHORT:  emit("i16");    break;
  case TY_INT:    emit("i32");    break;
  case TY_LONG:
  case TY_LLONG:  emit("i64");    break;
  default:        emit("i%d", elem->size * 8); break;
  }
  emit(">");
}

// __builtin_ia32_unpckhps/lps/hpd/lpd(a, b): interleave the high/low halves
// of two vectors.  Low:  result = {a[0], b[0], a[1], b[1], ...}.
// High: result = {a[n/2], b[n/2], a[n/2+1], b[n/2+1], ...}.
const char *gen_ir_unpck(Node *node, int indent)
{
  Type *ty = node->ty;
  int n = ty->array_len;
  if (n <= 0)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);

  bool high = (node->kind == ND_UNPCKHPS || node->kind == ND_UNPCKHPD);
  int base = high ? n / 2 : 0;

  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int i = 0; i < n / 2; i++)
  {
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d, i32 %d",
                    (i > 0) ? "," : "", base + i, base + i + n);
  }
  off += snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", b, mask);
  return res;
}

// __builtin_ia32_storehps/lps(ptr, vec): store the high (storehps) or low
// (storelps) 64 bits of the vector to memory.  The result is discarded.
const char *gen_ir_sse_store(Node *node, int indent)
{
  Type *ty = node->rhs->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
  {
    emit_expr(node->lhs, indent);
    emit_expr(node->rhs, indent);
    return gen_ir_sse_unsupported(node, indent);
  }

  const char *ptr = emit_expr(node->lhs, indent);
  const char *vec = emit_expr(node->rhs, indent);

  bool high = (node->kind == ND_STOREHPS);
  int base = high ? n / 2 : 0;
  int m = n / 2;

  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", m);
  for (int i = 0; i < m; i++)
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (i > 0) ? "," : "", base + i);
  off += snprintf(mask + off, sizeof(mask) - off, ">");

  const char *sub = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", sub);
  emit_type_str(ty);
  emit(" %s, ", vec);
  emit_type_str(ty);
  emit(" %s, %s\n", vec, mask);

  emit_indent(indent);
  emit("store ");
  emit_vec_type_str(m, ty->base);
  emit(" %s, ptr %s\n", sub, ptr);
  return NULL;
}

// __builtin_ia32_movss(a, b): result = {b[0], a[1], a[2], a[3]}.
// __builtin_ia32_movsd(a, b): result = {b[0], a[1]}.
// The low element comes from the second operand; the upper elements are
// preserved from the first operand.  Both are pure shuffles.
const char *gen_ir_sse_movss_sd(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);

  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int i = 0; i < n; i++)
  {
    // element 0 comes from b (index n), the rest from a (index i).
    int idx = (i == 0) ? n : i;
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (i > 0) ? "," : "", idx);
  }
  off += snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", b, mask);
  return res;
}

// __builtin_ia32_addsubps/pd(a, b): even lanes = a - b, odd lanes = a + b.
const char *gen_ir_addsub(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);

  const char *sub = new_reg();
  emit_indent(indent);
  emit("%s = fsub ", sub);
  emit_type_str(ty);
  emit(" %s, %s\n", a, b);

  const char *add = new_reg();
  emit_indent(indent);
  emit("%s = fadd ", add);
  emit_type_str(ty);
  emit(" %s, %s\n", a, b);

  // Combine: even lanes from sub, odd lanes from add.
  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int i = 0; i < n; i++)
  {
    int idx = (i % 2 == 0) ? i : (n + i);
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (i > 0) ? "," : "", idx);
  }
  off += snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", sub);
  emit_type_str(ty);
  emit(" %s, %s\n", add, mask);
  return res;
}

// __builtin_ia32_haddps/pd and hsubps/pd: horizontal add/sub of adjacent
// pairs.  For n lanes the result is
//   { a0(+/-)a1, a2(+/-)a3, ..., b0(+/-)b1, b2(+/-)b3, ... }.
const char *gen_ir_hadd_hsub(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  bool is_sub = (node->kind == ND_HSUBPS || node->kind == ND_HSUBPD);

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);

  // Build the "even" (first of each pair) and "odd" (second of each pair)
  // vectors as shuffles over the concatenation (a, b).
  char even_mask[256], odd_mask[256];
  int eo = 0, oo = 0;
  eo += snprintf(even_mask + eo, sizeof(even_mask) - eo, "<%d x i32> <", n);
  oo += snprintf(odd_mask + oo, sizeof(odd_mask) - oo, "<%d x i32> <", n);
  for (int j = 0; j < n; j++)
  {
    int base, p;
    if (j < n / 2) { base = 0; p = j; }
    else           { base = n; p = j - n / 2; }
    int even_idx = base + 2 * p;
    int odd_idx = base + 2 * p + 1;
    eo += snprintf(even_mask + eo, sizeof(even_mask) - eo, "%s i32 %d",
                   (j > 0) ? "," : "", even_idx);
    oo += snprintf(odd_mask + oo, sizeof(odd_mask) - oo, "%s i32 %d",
                   (j > 0) ? "," : "", odd_idx);
  }
  snprintf(even_mask + eo, sizeof(even_mask) - eo, ">");
  snprintf(odd_mask + oo, sizeof(odd_mask) - oo, ">");

  const char *evens = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", evens);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", b, even_mask);

  const char *odds = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", odds);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", b, odd_mask);

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = %s ", res, is_sub ? "fsub" : "fadd");
  emit_type_str(ty);
  emit(" %s, %s\n", evens, odds);
  return res;
}

// __builtin_ia32_dpps/dppd(a, b, imm) and dpps256: dot product.  The high
// nibble of imm selects which element products are summed; the low nibble
// selects which result lanes receive the (broadcast) sum.  For the 256-bit
// form the mask is applied independently to each 128-bit lane.
const char *gen_ir_dpp(Node *node, int indent)
{
  Type *ty = (node->builtin_args[0] && node->builtin_args[0]->ty)
                 ? node->builtin_args[0]->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  Type *elem_ty = ty->base;
  int elem_bits = elem_ty->size * 8;

  // Elements per 128-bit lane and number of independent lanes.
  int group = 128 / elem_bits;
  if (group <= 0) group = n;
  int num_groups = n / group;
  if (num_groups <= 0) num_groups = 1;

  int imm = eval(node->builtin_args[2]);

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[1], indent);

  const char *prod = new_reg();
  emit_indent(indent);
  emit("%s = fmul ", prod);
  emit_type_str(ty);
  emit(" %s, %s\n", a, b);

  const char *cur = "zeroinitializer";
  bool any_lane = false;

  for (int g = 0; g < num_groups; g++)
  {
    int lbase = g * group;
    // Accumulate the selected lane products into a scalar sum for this lane.
    const char *acc = NULL;
    for (int i = 0; i < group; i++)
    {
      if (!((imm >> (4 + i)) & 1))
        continue;
      const char *e = new_reg();
      emit_indent(indent);
      emit("%s = extractelement ", e);
      emit_type_str(ty);
      emit(" %s, i32 %d\n", prod, lbase + i);
      if (!acc)
        acc = e;
      else
      {
        const char *s = new_reg();
        emit_indent(indent);
        emit("%s = fadd ", s);
        emit_type_str(elem_ty);
        emit(" %s, %s\n", acc, e);
        acc = s;
      }
    }
    if (!acc)
      acc = "0.0";

    // Broadcast the sum into the selected result lanes of this group.
    for (int j = 0; j < group; j++)
    {
      if (!((imm >> j) & 1))
        continue;
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = insertelement ", r);
      emit_type_str(ty);
      emit(" %s, ", cur);
      emit_type_str(elem_ty);
      emit(" %s, i32 %d\n", acc, lbase + j);
      cur = r;
      any_lane = true;
    }
  }

  if (!any_lane)
  {
    // No result lane selected: materialize a zero vector.
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = fadd ", r);
    emit_type_str(ty);
    emit(" zeroinitializer, zeroinitializer\n");
    return r;
  }
  return cur;
}

// __builtin_ia32_insertps128(d, s, imm):
//   src  = s[(imm>>6)&3]; dst_lane = (imm>>4)&3;
//   result = d with lane dst_lane replaced by src, then each lane j whose
//   zero-mask bit (imm>>j)&1 is set forced to 0.
const char *gen_ir_insertps(Node *node, int indent)
{
  Type *ty = (node->builtin_args[0] && node->builtin_args[0]->ty)
                 ? node->builtin_args[0]->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  Type *elem_ty = ty->base;

  int imm = eval(node->builtin_args[2]);
  int src_sel = (imm >> 6) & 3;
  int dst_sel = (imm >> 4) & 3;

  const char *d = emit_expr(node->builtin_args[0], indent);
  const char *s = emit_expr(node->builtin_args[1], indent);

  const char *src = new_reg();
  emit_indent(indent);
  emit("%s = extractelement ", src);
  emit_type_str(ty);
  emit(" %s, i32 %d\n", s, src_sel);

  const char *cur = new_reg();
  emit_indent(indent);
  emit("%s = insertelement ", cur);
  emit_type_str(ty);
  emit(" %s, ", d);
  emit_type_str(elem_ty);
  emit(" %s, i32 %d\n", src, dst_sel);

  for (int j = 0; j < n; j++)
  {
    if (!((imm >> j) & 1))
      continue;
    const char *r = new_reg();
    emit_indent(indent);
    emit("%s = insertelement ", r);
    emit_type_str(ty);
    emit(" %s, ", cur);
    emit_type_str(elem_ty);
    emit(" 0.0, i32 %d\n", j);
    cur = r;
  }
  return cur;
}

// __builtin_ia32_movq128(a): keep the low 64 bits of a.  The node's type is
// <1 x i64>; when the result is assigned to a 128-bit lvalue the upper half
// is zero-filled by the surrounding store, matching the movq semantics.
const char *gen_ir_movq128(Node *node, int indent)
{
  Type *in_ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  const char *a = emit_expr(node->lhs, indent);

  int in_bits = in_ty->size * 8;
  int k = in_bits / 64;
  if (k < 1) k = 1;

  const char *ac = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", ac);
  emit_type_str(in_ty);
  emit(" %s to <%d x i64>\n", a, k);

  const char *lo = new_reg();
  emit_indent(indent);
  emit("%s = extractelement <%d x i64> %s, i32 0\n", lo, k, ac);

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = insertelement <1 x i64> zeroinitializer, i64 %s, i32 0\n",
       res, lo);

  // The node's declared type is a 64-bit vector (e.g. <1 x i64> or <2 x i32>);
  // reinterpret the low-64-bit result to that shape so the surrounding store
  // sees a matching type.
  Type *out_ty = (is_vector(node->ty)) ? node->ty : in_ty;
  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast <1 x i64> %s to ", out, res);
  emit_type_str(out_ty);
  emit("\n");
  return out;
}

// __builtin_ia32_shufps/shufpd and their 256-bit variants: immediate
// controlled shuffle over two vectors, applied per 128-bit lane.
const char *gen_ir_shufp(Node *node, int indent)
{
  Node *an, *bn;
  int imm;
  if (node->builtin_nargs >= 3)
  {
    an = node->builtin_args[0];
    bn = node->builtin_args[1];
    imm = eval(node->builtin_args[2]);
  }
  else
  {
    an = node->lhs;
    bn = node->rhs;
    imm = (int)node->rhs->val;
  }

  Type *ty = an->ty ? an->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  bool is_pd = (node->kind == ND_SHUFPD || node->kind == ND_SHUFPD256);

  const char *a = emit_expr(an, indent);
  const char *b = emit_expr(bn, indent);

  int lane_elems = is_pd ? 2 : 4;

  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int j = 0; j < n; j++)
  {
    int lane = j / lane_elems;
    int within = j % lane_elems;
    int base = lane * lane_elems;
    int idx;
    if (is_pd)
    {
      int bit = (imm >> j) & 1;
      // even element from a, odd element from b.
      idx = (within == 0) ? (base + bit) : (n + base + bit);
    }
    else
    {
      int sel = (imm >> (2 * within)) & 3;
      // first two elements from a, last two from b.
      idx = (within < 2) ? (base + sel) : (n + base + sel);
    }
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (j > 0) ? "," : "", idx);
  }
  snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", b, mask);
  return gen_ir_reinterpret_vec(res, ty, node->ty, indent);
}

const char *gen_ir_pack_sat(const char *src, const char *vsrc,
                                    int na, int deb, bool is_unsigned,
                                    const char *lo_splat, const char *hi_splat,
                                    int indent)
{
  char vw[32], vdst[32];
  snprintf(vw, sizeof vw, "<%d x i64>", na);
  snprintf(vdst, sizeof vdst, "<%d x i%d>", na, deb);

  const char *w = new_reg();
  emit_indent(indent);
  emit("%s = sext %s %s to %s\n", w, vsrc, src, vw);

  const char *clamped;
  if (is_unsigned) {
    // Unsigned saturation clamps a (signed) source to [0, hi]: negative
    // values become 0, overflowing positives become hi.  Use signed
    // extension + signed min/max (lo = 0) so negatives saturate to 0.
    const char *mx = new_reg();
    char smaxn[64];
    snprintf(smaxn, sizeof smaxn, "llvm.smax.v%di64", na);
    emit_indent(indent);
    emit("%s = call %s @%s(%s %s, %s)\n", mx, vw, smaxn,
         vw, w, lo_splat);
    const char *mn = new_reg();
    char sminn[64];
    snprintf(sminn, sizeof sminn, "llvm.smin.v%di64", na);
    emit_indent(indent);
    emit("%s = call %s @%s(%s %s, %s)\n", mn, vw, sminn,
         vw, mx, hi_splat);
    clamped = mn;
  } else {
    const char *mx = new_reg();
    char smaxn[64];
    snprintf(smaxn, sizeof smaxn, "llvm.smax.v%di64", na);
    emit_indent(indent);
    emit("%s = call %s @%s(%s %s, %s)\n", mx, vw, smaxn,
         vw, w, lo_splat);
    const char *mn = new_reg();
    char sminn[64];
    snprintf(sminn, sizeof sminn, "llvm.smin.v%di64", na);
    emit_indent(indent);
    emit("%s = call %s @%s(%s %s, %s)\n", mn, vw, sminn,
         vw, mx, hi_splat);
    clamped = mn;
  }

  const char *dst = new_reg();
  emit_indent(indent);
  emit("%s = trunc %s %s to %s\n", dst, vw, clamped, vdst);
  return dst;
}

const char *gen_ir_pack(Node *node, int indent)
{
  // pack*wd/wb: saturate each element of a and b to the destination width and
  // interleave them (a's elements first, then b's).  Portable lowering via
  // sign/zero extension, clamp with llvm.smin/smax/umin, truncate, then a
  // shufflevector interleave.
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int na = ty->array_len;
  if (na <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  bool is_unsigned = (node->kind == ND_PACKUSWB ||
                      node->kind == ND_PACKUSWB128 ||
                      node->kind == ND_PACKUSDW128);
  int seb = int_type_bits(ty->base);
  Type *dty = (is_vector(node->ty)) ? node->ty : ty;
  int deb = int_type_bits(dty->base);

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);

  char vsrc[32];
  snprintf(vsrc, sizeof vsrc, "<%d x i%d>", na, seb);

  const char *av = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", av); emit_type_str(ty);
  emit(" %s to %s\n", a, vsrc);
  const char *bv = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", bv); emit_type_str(ty);
  emit(" %s to %s\n", b, vsrc);

  long long lo = is_unsigned ? 0 : -(1LL << (deb - 1));
  long long hi = is_unsigned ? ((1LL << deb) - 1)
                             : ((1LL << (deb - 1)) - 1);

  char lo_splat[256], hi_splat[256];
  int o = snprintf(lo_splat, sizeof lo_splat, "<%d x i64> <", na);
  for (int i = 0; i < na; i++)
    o += snprintf(lo_splat + o, sizeof lo_splat - o, "%s i64 %lld",
                  (i ? "," : ""), lo);
  snprintf(lo_splat + o, sizeof lo_splat - o, ">");
  o = snprintf(hi_splat, sizeof hi_splat, "<%d x i64> <", na);
  for (int i = 0; i < na; i++)
    o += snprintf(hi_splat + o, sizeof hi_splat - o, "%s i64 %lld",
                  (i ? "," : ""), hi);
  snprintf(hi_splat + o, sizeof hi_splat - o, ">");

  const char *resa = gen_ir_pack_sat(av, vsrc, na, deb, is_unsigned,
                                     lo_splat, hi_splat, indent);
  const char *resb = gen_ir_pack_sat(bv, vsrc, na, deb, is_unsigned,
                                     lo_splat, hi_splat, indent);

  int n2 = na * 2;
  char vres[32], vdst[32];
  snprintf(vres, sizeof vres, "<%d x i%d>", n2, deb);
  snprintf(vdst, sizeof vdst, "<%d x i%d>", na, deb);

  char mask[256];
  o = snprintf(mask, sizeof mask, "<%d x i32> <", n2);
  for (int i = 0; i < n2; i++)
    o += snprintf(mask + o, sizeof mask - o, "%s i32 %d", (i ? "," : ""), i);
  snprintf(mask + o, sizeof mask - o, ">");

  const char *inter = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s %s, %s\n", inter, vdst, resa,
       vdst, resb, mask);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, vres, inter);
  emit_type_str(dty);
  emit("\n");
  return out;
}

const char *gen_ir_psadbw(Node *node, int indent)
{
  // __builtin_ia32_psadbw(a, b): for every 8-byte block, store the sum of
  // absolute byte differences at the block's low lane; other lanes are 0.
  // Portable lowering: compute each block sum with scalar abs-diff over the
  // 8 bytes, then assemble the result vector.
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  // n is the byte count of the vector (== ty->size); the operands are
  // reinterpreted as a flat byte vector by bitcast_to_intrinsic_vec.
  int n = ty->size;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);
  const char *ac = bitcast_to_intrinsic_vec(a, ty, 8, indent);
  const char *bc = bitcast_to_intrinsic_vec(b, ty, 8, indent);

  int nb = n / 8;
  char vres[32];
  snprintf(vres, sizeof vres, "<%d x i64>", nb);

  const char *resv = new_reg();
  for (int k = 0; k < nb; k++) {
    const char *sum = new_reg();
    emit_indent(indent);
    emit("%s = add i64 0, 0\n", sum);
    for (int i = 0; i < 8; i++) {
      int idx = 8 * k + i;
      const char *ai = new_reg();
      const char *bi = new_reg();
      emit_indent(indent);
      emit("%s = extractelement <%d x i8> %s, i32 %d\n", ai, n, ac, idx);
      emit_indent(indent);
      emit("%s = extractelement <%d x i8> %s, i32 %d\n", bi, n, bc, idx);
      const char *ad = new_reg(), *bd = new_reg();
      emit_indent(indent);
      emit("%s = zext i8 %s to i32\n", ad, ai);
      emit_indent(indent);
      emit("%s = zext i8 %s to i32\n", bd, bi);
      const char *diff = new_reg();
      emit_indent(indent);
      emit("%s = sub i32 %s, %s\n", diff, ad, bd);
      const char *neg = new_reg();
      emit_indent(indent);
      emit("%s = icmp slt i32 %s, 0\n", neg, diff);
      const char *absd = new_reg();
      emit_indent(indent);
      emit("%s = sub i32 0, %s\n", absd, diff);
      const char *sel = new_reg();
      emit_indent(indent);
      emit("%s = select i1 %s, i32 %s, i32 %s\n", sel, neg, absd, diff);
      const char *ext = new_reg();
      emit_indent(indent);
      emit("%s = zext i32 %s to i64\n", ext, sel);
      const char *nsum = new_reg();
      emit_indent(indent);
      emit("%s = add i64 %s, %s\n", nsum, sum, ext);
      sum = nsum;
    }
    if (k == 0) {
      emit_indent(indent);
      emit("%s = insertelement %s poison, i64 %s, i32 0\n", resv, vres, sum);
    } else {
      const char *nres = new_reg();
      emit_indent(indent);
      emit("%s = insertelement %s %s, i64 %s, i32 %d\n",
           nres, vres, resv, sum, k);
      resv = nres;
    }
  }

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, vres, resv);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

const char *gen_ir_mpsadbw(Node *node, int indent)
{
  // __builtin_ia32_mpsadbw128/256(a, b, imm): multiple sums of absolute byte
  // differences.  Lowered through the stable sse41/avx2 mpsadbw intrinsics
  // (which take the immediate as an immarg constant).
  Type *ty = (node->builtin_args[0] && node->builtin_args[0]->ty)
                 ? node->builtin_args[0]->ty : node->ty;
  // n is the byte count of the vector (== ty->size); the intrinsic operates on
  // the vector reinterpreted as a flat byte vector, matching bitcast_to_intrinsic_vec.
  int n = ty->size;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[1], indent);
  const char *ac = bitcast_to_intrinsic_vec(a, ty, 8, indent);
  const char *bc = bitcast_to_intrinsic_vec(b, ty, 8, indent);

  int imm = eval(node->builtin_args[2]);

  const char *intrinsic;
  int retn;
  if (n == 32) {
    intrinsic = "llvm.x86.avx2.mpsadbw";
    retn = 16;
  } else {
    intrinsic = "llvm.x86.sse41.mpsadbw";
    retn = 8;
  }

  char vret[32];
  snprintf(vret, sizeof vret, "<%d x i16>", retn);

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = call %s @%s(<%d x i8> %s, <%d x i8> %s, i8 %d)\n",
       res, vret, intrinsic, n, ac, n, bc, imm);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, vret, res);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

const char *gen_ir_pshuf(Node *node, int indent, int hi_low)
{
  // hi_low: 0 = full vector shuffle (pshufd/pshufw, groups of 4 elements),
  // hi_low: 0 = full vector shuffle (pshufd/pshufw, groups of 4 elements),
  //         1 = pshufhw (only the high 4 words are permuted),
  //         2 = pshuflw (only the low 4 words are permuted).
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  int imm = eval(node->rhs);

  const char *a = emit_expr(node->lhs, indent);

  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int j = 0; j < n; j++) {
    int src;
    int half = n / 2;
    if (hi_low == 1) {
      // pshufhw: low half unchanged, high half permuted by imm.
      if (j < half) src = j;
      else {
        int within = j - half;
        src = half + ((imm >> (2 * within)) & 3);
      }
    } else if (hi_low == 2) {
      // pshuflw: low half permuted by imm, high half unchanged.
      if (j >= half) src = j;
      else {
        int within = j;
        src = (imm >> (2 * within)) & 3;
      }
    } else {
      // Full shuffle in groups of 4 elements (pshufd/pshufw).
      int within = j % 4;
      int group = j - within;
      src = group + ((imm >> (2 * within)) & 3);
    }
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (j > 0) ? "," : "", src);
  }
  snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", a, mask);
  return gen_ir_reinterpret_vec(res, ty, node->ty, indent);
}

const char *gen_ir_pshufb(Node *node, int indent)
{
  // __builtin_ia32_pshufb(a, m): for each byte i, if m[i] & 0x80 the result
  // byte is 0, otherwise result[i] = a[base + (m[i] & mask_low)] where the
  // gather is confined to the current 16-byte lane (per-lane for 256-bit) so
  // the index never crosses into another lane.
  //
  // Portable lowering (no x86-specific intrinsic): store the source bytes to a
  // stack slot, then for each lane gather a[base + (m[i] & mask_low)] (a
  // dynamic index is not expressible with extractelement/shufflevector, so we
  // go through memory) and zero the lane when the high bit of m[i] is set.
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  // n is the byte count of the vector (== ty->size); for the byte-permute
  // intrinsics the vector is always a flat byte vector, so byte count equals
  // element count here and matches bitcast_to_intrinsic_vec.
  int n = ty->size;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  int mask_low = (n == 8) ? 7 : 15;
  int lane = (n >= 32) ? 16 : n;

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);

  const char *ac = bitcast_to_intrinsic_vec(a, ty, 8, indent);
  const char *bc = bitcast_to_intrinsic_vec(b, ty, 8, indent);

  const char *slot = new_reg();
  emit_indent(indent);
  emit("%s = alloca i8, i64 %d, align 1\n", slot, n);
  emit_indent(indent);
  emit("store <%d x i8> %s, ptr %s, align 1\n", n, ac, slot);

  const char *mb = new_reg();
  const char *lo = new_reg();
  const char *hi = new_reg();

  const char *res = new_reg();
  for (int i = 0; i < n; i++) {
    const char *mbi = (i == 0) ? mb : new_reg();
    const char *loi = (i == 0) ? lo : new_reg();
    const char *hii = (i == 0) ? hi : new_reg();
    const char *loi32 = new_reg();
    const char *addri = new_reg();
    const char *vali = new_reg();
    const char *zcondi = new_reg();
    const char *outbi = new_reg();

    int base = (n >= 32) ? (i / lane) * lane : 0;

    emit_indent(indent);
    emit("%s = extractelement <%d x i8> %s, i32 %d\n", mbi, n, bc, i);
    emit_indent(indent);
    emit("%s = and i8 %s, %d\n", loi, mbi, mask_low);
    emit_indent(indent);
    if (base != 0) {
      emit("%s = zext i8 %s to i32\n", loi32, loi);
      const char *loi_base = new_reg();
      emit_indent(indent);
      emit("%s = add i32 %s, %d\n", loi_base, loi32, base);
      loi32 = loi_base;
    } else {
      emit("%s = zext i8 %s to i32\n", loi32, loi);
    }
    emit_indent(indent);
    emit("%s = and i8 %s, -128\n", hii, mbi);
    emit_indent(indent);
    emit("%s = getelementptr inbounds [%d x i8], ptr %s, i32 0, i32 %s\n",
         addri, n, slot, loi32);
    emit_indent(indent);
    emit("%s = load i8, ptr %s, align 1\n", vali, addri);
    emit_indent(indent);
    emit("%s = icmp ne i8 %s, 0\n", zcondi, hii);
    emit_indent(indent);
    emit("%s = select i1 %s, i8 0, i8 %s\n", outbi, zcondi, vali);
    const char *nres = new_reg();
    if (i == 0) {
      emit_indent(indent);
      emit("%s = insertelement <%d x i8> poison, i8 %s, i32 0\n",
           res, n, outbi);
    } else {
      emit_indent(indent);
      emit("%s = insertelement <%d x i8> %s, i8 %s, i32 %d\n",
           nres, n, res, outbi, i);
      res = nres;
    }
  }

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast <%d x i8> %s to ", out, n, res);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

// __builtin_ia32_vpermilpd/ps and their 256-bit variants: in-lane permute of
// a single vector controlled by an immediate.
const char *gen_ir_vpermil(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  int imm = eval(node->rhs);

  bool is_pd = (node->kind == ND_VPERMILPD || node->kind == ND_VPERMILPD256);
  int lane_elems = is_pd ? 2 : 4;

  const char *a = emit_expr(node->lhs, indent);

  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int j = 0; j < n; j++)
  {
    int lane = j / lane_elems;
    int within = j % lane_elems;
    int base = lane * lane_elems;
    int idx;
    if (is_pd)
      idx = base + ((imm >> j) & 1);
    else
      idx = base + ((imm >> (2 * within)) & 3);
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (j > 0) ? "," : "", idx);
  }
  snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" poison, %s\n", mask);
  return gen_ir_reinterpret_vec(res, ty, node->ty, indent);
}

// __builtin_ia32_vextractf128_pd256/ps256/si256: extract a 128-bit half.
const char *gen_ir_vextractf128(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  int imm = eval(node->rhs);

  int half = n / 2;
  int base = (imm & 1) * half;

  const char *a = emit_expr(node->lhs, indent);

  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", half);
  for (int j = 0; j < half; j++)
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (j > 0) ? "," : "", base + j);
  snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" poison, %s\n", mask);

  // The shuffle result is <half x base> (mask length), but the node's declared
  // type (node->ty) may reinterp the same-sized bytes (e.g. the _si256
  // variants expose <16 x i8> or <4 x i64>). Reinterpret so downstream
  // casts/bitcasts see a consistent LLVM type.
  Type *res_ty = vector_of(ty->base, half);
  return gen_ir_reinterpret_vec(res, res_ty, node->ty, indent);
}

// __builtin_ia32_vinsertf128_pd256/ps256/si256: insert a 128-bit vector into
// one of the two 128-bit halves of a 256-bit vector.
const char *gen_ir_vinsertf128(Node *node, int indent)
{
  Type *ty = (node->builtin_args[0] && node->builtin_args[0]->ty)
                 ? node->builtin_args[0]->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  Type *half_ty = node->builtin_args[1]->ty;
  int half = n / 2;
  int imm = eval(node->builtin_args[2]);

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *ins = emit_expr(node->builtin_args[1], indent);

  // Widen the 128-bit insert operand to the full 256-bit width so it can be
  // shuffled together with the destination.
  char wmask[128];
  int wo = 0;
  wo += snprintf(wmask + wo, sizeof(wmask) - wo, "<%d x i32> <", n);
  for (int j = 0; j < n; j++)
    wo += snprintf(wmask + wo, sizeof(wmask) - wo, "%s i32 %d",
                   (j > 0) ? "," : "", (j < half) ? j : 0);
  snprintf(wmask + wo, sizeof(wmask) - wo, ">");

  const char *insw = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", insw);
  emit_type_str(half_ty);
  emit(" %s, ", ins);
  emit_type_str(half_ty);
  emit(" poison, %s\n", wmask);

  // Select: lane in the target half comes from the widened insert (indices
  // n..2n-1), the other half comes from a (indices 0..n-1).
  int ins_half = imm & 1;
  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int j = 0; j < n; j++)
  {
    int lane = j / half;
    int idx = (lane == ins_half) ? (n + (j % half)) : j;
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (j > 0) ? "," : "", idx);
  }
  snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", insw, mask);

  // The shuffle result uses the input operand's element type, but the node's
  // declared type (node->ty) may reinterp the same-sized bytes (e.g. the
  // _si256 variants expose <16 x i8> or <4 x i64>). Bitcast the result so
  // downstream casts/bitcasts see a consistent LLVM type.
  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", out);
  emit_type_str(ty);
  emit(" %s to ", res);
  emit_type_str(node->ty);
  emit("\n");
  return out;
}

// __builtin_ia32_vperm2f128_pd256/ps256/si256: permute the 128-bit halves of
// two 256-bit vectors.  imm[1:0] selects the source for the low half, imm[5:4]
// for the high half (0/1 = halves of a, 2/3 = halves of b); imm[3]/imm[7]
// force the corresponding output half to zero.
const char *gen_ir_vperm2f128(Node *node, int indent)
{
  Type *ty = (node->builtin_args[0] && node->builtin_args[0]->ty)
                 ? node->builtin_args[0]->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  int half = n / 2;
  int imm = eval(node->builtin_args[2]);

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[1], indent);

  int low_sel = imm & 3;
  int high_sel = (imm >> 4) & 3;
  // Concat index of the first element of a selected 128-bit source.
  int low_base = (low_sel < 2) ? (low_sel * half) : (n + (low_sel - 2) * half);
  int high_base = (high_sel < 2) ? (high_sel * half) : (n + (high_sel - 2) * half);

  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int j = 0; j < n; j++)
  {
    int idx;
    if (j < half)
      idx = low_base + j;
    else
      idx = high_base + (j - half);
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (j > 0) ? "," : "", idx);
  }
  snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", b, mask);

  // Apply the zeroing bits, if any.
  if ((imm & 0x8) || (imm & 0x80))
  {
    const char *cur = res;
    for (int j = 0; j < n; j++)
    {
      bool zero = (j < half) ? (imm & 0x8) : (imm & 0x80);
      if (!zero)
        continue;
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = insertelement ", r);
      emit_type_str(ty);
      emit(" %s, ", cur);
      emit_type_str(ty->base);
      emit(" 0.0, i32 %d\n", j);
      cur = r;
    }
    return cur;
  }
  return res;
}

// __builtin_ia32_palignr128 / palignr256 / palignr: PALIGNR byte-shift.
// The 3rd argument is a BIT count; the hardware shifts by imm/8 bytes.
// Semantics (Intel PALIGNR): concatenate the two 128-bit operands (the first
// node argument is the HIGH part, the second is the LOW part) into a 2x width
// value, shift it right by imm bytes, and keep the low width bytes.  The 256-bit
// form repeats this independently on each 128-bit lane pair.
const char *gen_ir_palignr(Node *node, int indent, bool is256)
{
  Type *ty = node->builtin_args[0]->ty;
  const char *a = emit_expr(node->builtin_args[0], indent); // high part
  const char *b = emit_expr(node->builtin_args[1], indent); // low part
  int64_t imm_bytes = eval(node->builtin_args[2]) / 8;
  if (imm_bytes < 0) imm_bytes = 0;

  int total = ty->size; // 8 (MMX), 16 (128-bit), 32 (256-bit)
  int lane_size = (total < 16) ? total : 16; // 64-bit or 128-bit lanes

  char vb[32];
  snprintf(vb, sizeof vb, "<%d x i8>", total);

  const char *ab = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", ab);
  emit_type_str(ty);
  emit(" %s to %s\n", a, vb);

  const char *bb = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", bb);
  emit_type_str(ty);
  emit(" %s to %s\n", b, vb);

  char mask[512];
  int off = snprintf(mask, sizeof mask, "<%d x i32> <", total);
  for (int i = 0; i < total; i++) {
    // VPALIGNR concatenates {dst_operand, src_operand} and extracts
    // bytes [imm, imm+lanes-1].  For 256-bit this is lane-wise (lanes of
    // 16 bytes); for smaller vectors the full vector is one lane.
    int lane = is256 ? (i / lane_size) : 0;
    int p = i % lane_size;
    int pos = p + (int)imm_bytes;
    int idx;
    if (pos >= lane_size) {
      idx = total + lane * lane_size + pos - lane_size;
    } else {
      idx = lane * lane_size + pos;
    }
    if (idx >= 2 * total)
      idx = 2 * total;
    off += snprintf(mask + off, sizeof mask - off, "%s i32 %d",
                    (i > 0) ? "," : "", idx);
  }
  snprintf(mask + off, sizeof mask - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s %s, %s\n", res, vb, bb, vb, ab, mask);

  return gen_ir_reinterpret_vec(res, vector_of(ty_char, total), node->ty,
                                indent);
}

// __builtin_ia32_permdi256(a, imm): vpermq — permute the four 64-bit lanes of
// a 256-bit vector according to the 2-bit fields of the immediate.
const char *gen_ir_permdi256(Node *node, int indent)
{
  Type *ty = node->lhs->ty;
  const char *a = emit_expr(node->lhs, indent);
  int imm = (int)eval(node->rhs);

  char mask[64];
  int off = snprintf(mask, sizeof mask, "<4 x i32> <");
  for (int i = 0; i < 4; i++) {
    int src = (imm >> (2 * i)) & 3;
    off += snprintf(mask + off, sizeof mask - off, "%s i32 %d",
                    (i > 0) ? "," : "", src);
  }
  snprintf(mask + off, sizeof mask - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" poison, %s\n", mask);

  return gen_ir_reinterpret_vec(res, ty, node->ty, indent);
}

// __builtin_ia32_permti256(a, b, imm): vperm2i128 — permute the 128-bit lanes
// of two 256-bit vectors.  imm[1:0] selects the source for the low 128-bit
// result lane (0/1 = a's halves, 2/3 = b's halves); imm[5:4] does the same for
// the high lane; imm[3]/imm[7] zero the low/high result lane.
const char *gen_ir_vperm2i128(Node *node, int indent)
{
  Type *ty = node->builtin_args[0]->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  int half = n / 2;
  int imm = (int)eval(node->builtin_args[2]);

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[1], indent);

  int low_sel = imm & 3;
  int high_sel = (imm >> 4) & 3;
  int low_base = (low_sel < 2) ? (low_sel * half) : (n + (low_sel - 2) * half);
  int high_base = (high_sel < 2) ? (high_sel * half)
                                 : (n + (high_sel - 2) * half);

  char mask[256];
  int off = snprintf(mask, sizeof mask, "<%d x i32> <", n);
  for (int j = 0; j < n; j++) {
    int idx = (j < half) ? (low_base + j) : (high_base + (j - half));
    off += snprintf(mask + off, sizeof mask - off, "%s i32 %d",
                    (j > 0) ? "," : "", idx);
  }
  snprintf(mask + off, sizeof mask - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", b, mask);

  if (imm & 0x8 || imm & 0x80) {
    const char *cur = res;
    for (int j = 0; j < n; j++) {
      bool zero = (j < half) ? (imm & 0x8) : (imm & 0x80);
      if (!zero)
        continue;
      const char *r = new_reg();
      emit_indent(indent);
      emit("%s = insertelement ", r);
      emit_type_str(ty);
      emit(" %s, ", cur);
      emit_type_str(ty->base);
      emit(" 0, i32 %d\n", j);
      cur = r;
    }
    res = cur;
  }

  return gen_ir_reinterpret_vec(res, ty, node->ty, indent);
}

// __builtin_ia32_si_si256 / si256_si / pd_pd256 / ps_ps256: these are pure
// reinterpreting casts with no instruction.  si_si256 extracts the low 128 bits
// of a 256-bit vector; si256_si zero-extends the high 128 bits; pd/ps_pd256
// promote a 128-bit float vector to 256 bits (upper lanes undefined).
const char *gen_ir_vec_cast_extract(Node *node, int indent)
{
  const char *a = emit_expr(node->lhs, indent);
  Type *ty = node->lhs->ty;
  Type *dst = node->ty;
  int n = ty->array_len;
  int dn = dst->array_len;
  if (n <= 0 || dn <= 0)
    return gen_ir_sse_unsupported(node, indent);

  // These builtins are pure reinterprets between vector representations of
  // the same total width (bitcast), zero-extending when the destination is
  // wider (e.g. _mm256_castsi128_si256) or truncating when it is narrower
  // (e.g. _mm256_castsi256_si128).  gen_ir_reinterpret_vec already handles
  // both cases correctly (bitcast for equal sizes, memory round-trip for
  // differing sizes), so delegate rather than hand-rolling shufflevectors
  // whose operand types must agree.
  return gen_ir_reinterpret_vec(a, ty, dst, indent);
}

// __builtin_ia32_pcmpgtb256_mask(a, b, mask): vpcmpgtb over 32 bytes followed
// by a vpmovmskb to produce a 32-bit mask, ANDed with the writemask argument.
const char *gen_ir_pcmpgtb256_mask(Node *node, int indent)
{
  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[1], indent);

  const char *ac = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", ac);
  emit_type_str(node->builtin_args[0]->ty);
  emit(" %s to <32 x i8>\n", a);

  const char *bc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", bc);
  emit_type_str(node->builtin_args[1]->ty);
  emit(" %s to <32 x i8>\n", b);

  const char *cmp = new_reg();
  emit_indent(indent);
  emit("%s = icmp sgt <32 x i8> %s, %s\n", cmp, ac, bc);

  // llvm.x86.avx2.pmovmskb.256 was removed in recent LLVM; compute the mask
  // portably: the mask bit i is the sign bit of byte lane i.  SEXT the i1
  // comparison to i32 (0 or 1), shift each lane into its bit position, then
  // OR-reduce into a scalar i32.
  const char *bits = new_reg();
  emit_indent(indent);
  emit("%s = sext <32 x i1> %s to <32 x i32>\n", bits, cmp);

  const char *shamt_reg = new_reg();
  char shamt_init[512];
  {
    int off = snprintf(shamt_init, sizeof shamt_init, "< i32 0");
    for (int i = 1; i < 32; i++)
      off += snprintf(shamt_init + off, sizeof shamt_init - off, ", i32 %d", i);
    snprintf(shamt_init + off, sizeof shamt_init - off, ">");
  }
  emit_indent(indent);
  emit("%s = or <32 x i32> zeroinitializer, %s\n", shamt_reg, shamt_init);

  const char *sh = new_reg();
  emit_indent(indent);
  emit("%s = shl <32 x i32> %s, %s\n", sh, bits, shamt_reg);

  const char *msk = new_reg();
  emit_indent(indent);
  emit("%s = call i32 @llvm.vector.reduce.or.v32i32(<32 x i32> %s)\n", msk, sh);

  const char *wr = emit_expr(node->builtin_args[2], indent);
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = and i32 %s, %s\n", res, msk, wr);

  return gen_ir_reinterpret_vec(res, ty_int, node->ty, indent);
}

// __builtin_ia32_prefetch(addr, rw, locality[, hint]): pure no-op for
// correctness (the hardware prefetch has no observable effect); we only need to
// evaluate the arguments so their side effects (e.g. rw++, ++locality) run.
const char *gen_ir_prefetch(Node *node, int indent)
{
  for (int i = 0; i < node->builtin_nargs; i++)
    emit_expr(node->builtin_args[i], indent);
  return NULL;
}

// __builtin_ia32_pcmpistr* / pcmpestr*: string compare.  The index (pcmpistri)
// and byte mask (pcmpistrm) are produced by inline assembly because LLVM 18
// no longer supports the @llvm.x86.sse41.pcmpi* intrinsics; the flag variants
// (a/c/o/s/z) are derived from IntRes2 bits:
//   CF = IntRes2[0], OF = IntRes2[5], SF = IntRes2[7], ZF = IntRes2[6].
const char *gen_ir_pcmpistr(Node *node, int indent)
{
  bool explicit_len = (node->builtin_nargs == 5);
  int imm = (int)eval(explicit_len ? node->builtin_args[4]
                                    : node->builtin_args[2]);

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[explicit_len ? 2 : 1],
                            indent);

  const char *ac = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", ac);
  emit_type_str(node->builtin_args[0]->ty);
  emit(" %s to <16 x i8>\n", a);

  const char *bc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", bc);
  emit_type_str(node->builtin_args[explicit_len ? 2 : 1]->ty);
  emit(" %s to <16 x i8>\n", b);

  switch (node->kind) {
  case ND_PCMPISTRI128:
  case ND_PCMPESTRI128: {
    const char *res = new_reg();
    emit_indent(indent);
    if (explicit_len) {
      const char *la = emit_expr(node->builtin_args[1], indent);
      const char *lb = emit_expr(node->builtin_args[3], indent);
      emit("%s = call i32 asm \"pcmpestri $5, $3, $1\", "
           "\"={ecx},x,{eax},x,{edx},N,~{dirflag},~{fpsr},~{flags}\""
           "(<16 x i8> %s, i32 %s, <16 x i8> %s, i32 %s, i8 %d)\n",
           res, ac, la, bc, lb, imm);
    } else {
      emit("%s = call i32 asm \"pcmpistri $3, $2, $1\", "
           "\"={ecx},x,x,N,~{dirflag},~{fpsr},~{flags}\""
           "(<16 x i8> %s, <16 x i8> %s, i8 %d)\n",
           res, ac, bc, imm);
    }
    return gen_ir_reinterpret_vec(res, ty_int, node->ty, indent);
  }
    default: {
    // Flag variants (a/c/o/s/z) are derived from EFLAGS via setcc, not from
    // the mask.  GCC implements them with a single pcmpistri followed by the
    // appropriate setcc instruction (not by extracting bits from the mask).
    const char *setcc = NULL;
    switch (node->kind) {
    case ND_PCMPISTRIA128:
    case ND_PCMPESTRIA128: setcc = "seta"; break;  // above: CF=0 AND ZF=0
    case ND_PCMPISTRIC128:
    case ND_PCMPESTRIC128: setcc = "setb"; break;  // below: CF=1
    case ND_PCMPISTRIO128:
    case ND_PCMPESTRIO128: setcc = "seto"; break;  // overflow: OF=1
    case ND_PCMPISTRIS128:
    case ND_PCMPESTRIS128: setcc = "sets"; break;  // sign: SF=1
    case ND_PCMPISTRIZ128:
    case ND_PCMPESTRIZ128: setcc = "sete"; break;  // equal/zero: ZF=1
    default: break;
    }

    if (setcc) {
      const char *res = new_reg();
      emit_indent(indent);
      if (explicit_len) {
        const char *la = emit_expr(node->builtin_args[1], indent);
        const char *lb = emit_expr(node->builtin_args[3], indent);
        emit("%s = call i32 asm \"xor ${0:k}, ${0:k}; pcmpestri $5, $3, $1; %s ${0:b}\", "
             "\"=r,x,{eax},x,{edx},N,~{ecx},~{dirflag},~{fpsr},~{flags}\""
             "(<16 x i8> %s, i32 %s, <16 x i8> %s, i32 %s, i8 %d)\n",
             res, setcc, ac, la, bc, lb, imm);
      } else {
        emit("%s = call i32 asm \"xor ${0:k}, ${0:k}; pcmpistri $3, $2, $1; %s ${0:b}\", "
             "\"=r,x,x,N,~{ecx},~{dirflag},~{fpsr},~{flags}\""
             "(<16 x i8> %s, <16 x i8> %s, i8 %d)\n",
             res, setcc, ac, bc, imm);
      }
      return gen_ir_reinterpret_vec(res, ty_int, node->ty, indent);
    }

    // Fall through: pcmpistrm / pcmpestrm – return the mask vector.
    const char *mask = new_reg();
    emit_indent(indent);
    if (explicit_len) {
      const char *la = emit_expr(node->builtin_args[1], indent);
      const char *lb = emit_expr(node->builtin_args[3], indent);
      emit("%s = call <16 x i8> asm \"pcmpestrm $5, $3, $1\", "
           "\"=x,0,{eax},x,{edx},N,~{dirflag},~{fpsr},~{flags}\""
           "(<16 x i8> %s, i32 %s, <16 x i8> %s, i32 %s, i8 %d)\n",
           mask, ac, la, bc, lb, imm);
    } else {
      emit("%s = call <16 x i8> asm \"pcmpistrm $3, $2, $1\", "
           "\"=x,0,x,N,~{dirflag},~{fpsr},~{flags}\""
           "(<16 x i8> %s, <16 x i8> %s, i8 %d)\n",
           mask, ac, bc, imm);
    }

    // The mask is returned as a __m128i/__m128i-equivalent vector.
    Type *rt = node->ty;
    return gen_ir_reinterpret_vec(mask, vector_of(ty_char, 16), rt, indent);
  }
  }
}

// __builtin_ia32_movlhps(a, b): result = {a[0], a[1], b[0], b[1]}.
// __builtin_ia32_movhlps(a, b): result = {a[0], a[1], b[2], b[3]}.
// Both are pure shuffles of the two input vectors.
const char *gen_ir_sse_movlhmh(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0 || ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);

  bool high = (node->kind == ND_MOVHLPS);
  char mask[256];
  int off = 0;
  off += snprintf(mask + off, sizeof(mask) - off, "<%d x i32> <", n);
  for (int i = 0; i < n; i++)
  {
    // movlhps: {a0, a1, b0, b1}; movhlps: {b2, b3, a2, a3}.
    int idx;
    if (high)
      idx = (i < 2) ? (n + i + 2) : i;   // b[2],b[3] then a[2],a[3]
    else
      idx = (i < 2) ? i : (n + i - 2);   // a[0],a[1] then b[0],b[1]
    off += snprintf(mask + off, sizeof(mask) - off, "%s i32 %d",
                    (i > 0) ? "," : "", idx);
  }
  off += snprintf(mask + off, sizeof(mask) - off, ">");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, %s\n", b, mask);
  return res;
}

// Non-temporal scalar stores: movnti(&x, v) / movnti64 / movntq.
// The non-temporal hint is irrelevant to the computed value, so a plain
// store is sufficient for correctness.
const char *gen_ir_movnti_store(Node *node, int indent)
{
  const char *ptr = emit_expr(node->lhs, indent);
  const char *val = emit_expr(node->rhs, indent);

  emit_indent(indent);
  emit("store ");
  emit_type_str(node->rhs->ty);
  emit(" %s, ptr %s\n", val, ptr);
  return NULL;
}

// Non-temporal vector stores: movntdq(&m, v) / movntpd.
const char *gen_ir_movnt_vec_store(Node *node, int indent)
{
  const char *ptr = emit_expr(node->lhs, indent);
  const char *val = emit_expr(node->rhs, indent);

  emit_indent(indent);
  emit("store ");
  emit_type_str(node->rhs->ty);
  emit(" %s, ptr %s\n", val, ptr);
  return NULL;
}

// __builtin_ia32_movntdqa(&src): aligned non-temporal load of a 128-bit
// vector.  A plain aligned load reproduces the observable value.
const char *gen_ir_movntdqa_load(Node *node, int indent)
{
  const char *ptr = emit_expr(node->lhs, indent);
  return ir_load(node->ty, ptr, 0, indent);
}

// __builtin_ia32_maskmovdqu(src, mask, dest) / maskmovq: conditionally
// store the bytes of src into memory at dest where the high bit (0x80) of
// the corresponding mask byte is set; unselected bytes are left untouched.
// Emitted portably as a per-byte select between the current memory contents
// and the source, selected by (mask[i] & 0x80).
const char *gen_ir_maskmov(Node *node, int indent)
{
  if (node->builtin_nargs != 3)
    return gen_ir_sse_unsupported(node, indent);

  int n = node->builtin_args[0]->ty->size;
  if (n <= 0)
    return gen_ir_sse_unsupported(node, indent);

  const char *ptr = emit_expr(node->builtin_args[2], indent);
  const char *src = emit_expr(node->builtin_args[0], indent);
  const char *mask = emit_expr(node->builtin_args[1], indent);

  const char *cur = new_reg();
  emit_indent(indent);
  emit("%s = load <%d x i8>, ptr %s\n", cur, n, ptr);

  const char *src_b = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", src_b);
  emit_type_str(node->builtin_args[0]->ty);
  emit(" %s to <%d x i8>\n", src, n);

  const char *mask_b = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", mask_b);
  emit_type_str(node->builtin_args[1]->ty);
  emit(" %s to <%d x i8>\n", mask, n);

  const char *res = cur;
  for (int i = 0; i < n; i++)
  {
    const char *m = new_reg();
    emit_indent(indent);
    emit("%s = extractelement <%d x i8> %s, i32 %d\n", m, n, mask_b, i);
    const char *mb = new_reg();
    emit_indent(indent);
    emit("%s = and i8 %s, 128\n", mb, m);
    const char *sel = new_reg();
    emit_indent(indent);
    emit("%s = icmp ne i8 %s, 0\n", sel, mb);

    const char *sv = new_reg();
    emit_indent(indent);
    emit("%s = extractelement <%d x i8> %s, i32 %d\n", sv, n, src_b, i);
    const char *cv = new_reg();
    emit_indent(indent);
    emit("%s = extractelement <%d x i8> %s, i32 %d\n", cv, n, cur, i);

    const char *ch = new_reg();
    emit_indent(indent);
    emit("%s = select i1 %s, i8 %s, i8 %s\n", ch, sel, sv, cv);

    const char *ins = new_reg();
    emit_indent(indent);
    emit("%s = insertelement <%d x i8> %s, i8 %s, i32 %d\n", ins, n, res, ch, i);
    res = ins;
  }

  emit_indent(indent);
  emit("store <%d x i8> %s, ptr %s\n", n, res, ptr);
  return NULL;
}

// __builtin_ia32_stmxcsr/ldmxcsr(ptr): read/write the MXCSR control/status
// register.  With no pointer argument, stmxcsr spills the value to a stack
// slot and returns it as an i32.
// __builtin_ia32_clflush(p): flush the cache line containing p.  This does
// not affect the observable value of memory, so it is emitted as the
// dedicated x86 clflush intrinsic (which takes the pointer and returns void).
const char *gen_ir_clflush(Node *node, int indent)
{
  if (!node->lhs)
    return NULL;
  const char *ptr = emit_expr(node->lhs, indent);
  emit_indent(indent);
  emit("call void @llvm.x86.sse2.clflush(ptr %s)\n", ptr);
  return NULL;
}

const char *gen_ir_stmxcsr(Node *node, int indent)
{
  if (!node->lhs)
  {
    const char *slot = new_reg();
    emit_indent(indent);
    emit("%s = alloca i8, i64 4, align 4\n", slot);
    emit_indent(indent);
    emit("call void @llvm.x86.sse.stmxcsr(ptr %s)\n", slot);
    const char *val = new_reg();
    emit_indent(indent);
    emit("%s = load i32, ptr %s\n", val, slot);
    return val;
  }

  if (node->kind == ND_LDMXCSR)
  {
    // __builtin_ia32_ldmxcsr takes an int value; spill it to a 4-byte stack
    // slot and pass the resulting pointer to the intrinsic.
    const char *val = emit_expr(node->lhs, indent);
    const char *slot = new_reg();
    emit_indent(indent);
    emit("%s = alloca i8, i64 4, align 4\n", slot);
    emit_indent(indent);
    emit("store i32 %s, ptr %s\n", val, slot);
    emit_indent(indent);
    emit("call void @llvm.x86.sse.ldmxcsr(ptr %s)\n", slot);
  }
  else
  {
    const char *ptr = emit_expr(node->lhs, indent);
    emit_indent(indent);
    emit("call void @llvm.x86.sse.stmxcsr(ptr %s)\n", ptr);
  }
  return NULL;
}

const char *gen_ir_blend(Node *node, int indent)
{
  // blendps/pd(a, b, imm): per-lane select of b where the imm bit is set,
  // else a.  blendvps/vpd(a, b, m): per-lane select of b where the sign bit
  // of m is set (negative), else a.
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[1], indent);

  // Build the <N x i1> selection mask as either an inline constant (immediate
  // controlled blendps/pd) or a register (sign-bit derived blendvps/vpd).
  const char *mask_reg = NULL;
  char mask_const[256];

  if (node->kind == ND_BLENDVPS || node->kind == ND_BLENDVPD)
  {
    int bits = ty->base->size * 8;
    const char *m = emit_expr(node->builtin_args[2], indent);
    const char *mc = new_reg();
    emit_indent(indent);
    emit("%s = bitcast ", mc);
    emit_type_str(ty);
    emit(" %s to <%d x i%d>\n", m, n, bits);
    mask_reg = new_reg();
    emit_indent(indent);
    emit("%s = icmp slt <%d x i%d> %s, zeroinitializer\n",
         mask_reg, n, bits, mc);
  }
  else
  {
    int imm = eval(node->builtin_args[2]);
    if (imm < 0 || imm > 255)
      error_tok(node->builtin_args[2]->tok,
                "%s:%d: in %s: immediate out of range %d",
                __FILE__, __LINE__, __func__, imm);
    int off = 0;
    off += snprintf(mask_const + off, sizeof(mask_const) - off, "<%d x i1> <", n);
    for (int i = 0; i < n; i++)
    {
      off += snprintf(mask_const + off, sizeof(mask_const) - off,
                      "%s i1 %d", (i > 0) ? "," : "", (imm >> i) & 1);
    }
    off += snprintf(mask_const + off, sizeof(mask_const) - off, ">");
  }

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = select ", res);
  if (mask_reg)
    emit("<%d x i1> %s, ", n, mask_reg);
  else
    emit("%s, ", mask_const);
  emit_type_str(ty);
  emit(" %s, ", b);
  emit_type_str(ty);
  emit(" %s\n", a);
  return res;
}

const char *gen_ir_pblend(Node *node, int indent)
{
  // Integer blends.  chibicc represents integer vectors as <N x i64>, so we
  // derive the natural element width / lane count from the specific
  // instruction rather than node->ty:
  //   pblendvb128/vb256 : per-byte, mask via MSB of each byte (sign bit)
  //   pblendw128        : per-16-bit word, controlled by an 8-bit immediate
  //   pblendd256        : per-32-bit dword, controlled by an 8-bit immediate
  int ebits, n;
  bool sign_mask;
  switch (node->kind) {
  case ND_PBLENDVB128: ebits = 8;  n = 16; sign_mask = true;  break;
  case ND_PBLENDVB256: ebits = 8;  n = 32; sign_mask = true;  break;
  case ND_PBLENDW128:  ebits = 16; n = 8;  sign_mask = false; break;
  case ND_PBLENDD256:  ebits = 32; n = 8;  sign_mask = false; break;
  default: return gen_ir_sse_unsupported(node, indent);
  }

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[1], indent);

  char vstr[32];
  snprintf(vstr, sizeof vstr, "<%d x i%d>", n, ebits);

  const char *ac = bitcast_to_intrinsic_vec(a, node->builtin_args[0]->ty, ebits, indent);
  const char *bc = bitcast_to_intrinsic_vec(b, node->builtin_args[1]->ty, ebits, indent);
  char mconst[256];
  const char *mask;
  if (sign_mask) {
    const char *m = emit_expr(node->builtin_args[2], indent);
    const char *mc = bitcast_to_intrinsic_vec(m, node->builtin_args[2]->ty, ebits, indent);
    mask = new_reg();
    emit_indent(indent);
    emit("%s = icmp slt %s %s, zeroinitializer\n", mask, vstr, mc);
  } else {
    int imm = eval(node->builtin_args[2]);
    if (imm < 0 || imm > 255)
      error_tok(node->builtin_args[2]->tok,
                "%s:%d: in %s: immediate out of range %d",
                __FILE__, __LINE__, __func__, imm);

    int off = 0;
    off += snprintf(mconst + off, sizeof mconst - off, "<");
    for (int i = 0; i < n; i++)
      off += snprintf(mconst + off, sizeof mconst - off,
                      "%s i1 %d", (i > 0) ? "," : "", (imm >> i) & 1);
    off += snprintf(mconst + off, sizeof mconst - off, ">");
    mask = mconst;
  }

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = select <%d x i1> %s, %s %s, %s %s\n",
       res, n, mask, vstr, bc, vstr, ac);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, vstr, res);
  emit_type_str(node->ty);
  emit("\n");
  return out;
}

// PTEST family (ptestz/ptestc/ptestnzc): logically AND the two 128-bit vector
// operands and return the resulting x86 flag as a C int.
//   ptestz128   -> ZF = ((a & b) == 0)
//   ptestc128   -> CF = ((~a & b) == 0)
//   ptestnzc128 -> (ZF == 0 && CF == 0)
// The operands are treated as a raw 128-bit bag of bits (bitcast to i128).
const char *gen_ir_ptest(Node *node, int indent)
{
  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);

  const char *li = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", li);
  emit_type_str(node->lhs->ty);
  emit(" %s to i128\n", l);

  const char *ri = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", ri);
  emit_type_str(node->rhs->ty);
  emit(" %s to i128\n", r);

  // ZF = (a & b) == 0
  const char *andv = new_reg();
  emit_indent(indent);
  emit("%s = and i128 %s, %s\n", andv, li, ri);
  const char *zf = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq i128 %s, 0\n", zf, andv);

  if (node->kind == ND_PTESTZ128) {
    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = zext i1 %s to i32\n", res, zf);
    return res;
  }

  // CF = (~a & b) == 0
  const char *notl = new_reg();
  emit_indent(indent);
  emit("%s = xor i128 %s, -1\n", notl, li);
  const char *andc = new_reg();
  emit_indent(indent);
  emit("%s = and i128 %s, %s\n", andc, notl, ri);
  const char *cf = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq i128 %s, 0\n", cf, andc);

  if (node->kind == ND_PTESTC128) {
    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = zext i1 %s to i32\n", res, cf);
    return res;
  }

  // ptestnzc128: result = (ZF == 0) && (CF == 0)
  const char *nzf = new_reg();
  emit_indent(indent);
  emit("%s = xor i1 %s, true\n", nzf, zf);
  const char *ncf = new_reg();
  emit_indent(indent);
  emit("%s = xor i1 %s, true\n", ncf, cf);
  const char *both = new_reg();
  emit_indent(indent);
  emit("%s = and i1 %s, %s\n", both, nzf, ncf);
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i32\n", res, both);
  return res;
}

const char *gen_ir_sse_binop(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  const char *op = NULL;
  if (!ir_universal_fbinop_op(node, &op))
    // No generic LLVM opcode for this binop (e.g. saturating arithmetic
    // like psubsb/paddusb/...).  Route through gen_ir_int_vec_binop, which
    // maps these to the matching x86 intrinsics; nodes it can't handle are
    // still emitted as unsupported placeholders.
    return gen_ir_int_vec_binop(node, indent);

  // LLVM operates on raw float bit patterns; an i<N x float> is bitcasted
  // to i<N x i<bits>> for and/or/xor and back.  For fadd/fsub/fmul/fdiv
  // LLVM accepts <N x float> directly.
  const char *l, *r;
  if (node->builtin_nargs >= 2)
  {
    l = emit_expr(node->builtin_args[0], indent);
    r = emit_expr(node->builtin_args[1], indent);
  }
  else
  {
    l = emit_expr(node->lhs, indent);
    r = NULL;
    if (node->rhs)
      r = emit_expr(node->rhs, indent);
  }

  Type *elem_ty = (is_vector(ty)) ? ty->base : ty;
  bool is_fp = is_flonum(elem_ty);
  bool is_intv = (is_vector(ty)) &&
                 (ty->base->kind == TY_INT || ty->base->kind == TY_CHAR  ||
                  ty->base->kind == TY_SHORT || ty->base->kind == TY_LONG ||
                  ty->base->kind == TY_LLONG || ty->base->kind == TY_BOOL);

  const char *r_use = r;
  const char *r_orig = r;

  if (!is_fp && !is_intv)
    return gen_ir_sse_unsupported(node, indent);

  if (is_intv)
  {
    // Integer vectors: LLVM uses i<N x elt> directly for add/sub/xor.
    // For and/or/xor the result type is the same as the operands.
    const char *r2 = new_reg();
    emit_indent(indent);
    if (!strcmp(op, "andnot"))
    {
      // ~a & b  implemented as  xor(a, all-ones); and(result, b)
      int bits = int_type_bits(ty->base);
      if (bits <= 0) bits = 32;
      int count = ty->array_len;
      if (count <= 0) count = 1;
      const char *neg = new_reg();
      emit_indent(indent);
      emit("%s = xor ", neg);
      emit_type_str(ty);
      emit(" %s, <", l);
      for (int i = 0; i < count; i++)
      {
        if (i > 0) emit(", ");
        emit("i%d -1", bits);
      }
      emit(">\n");
      emit("%s = and ", r2);
      emit_type_str(ty);
      emit(" %s, %s\n", neg, r_use);
    }
    else if (!strcmp(op, "and") || !strcmp(op, "or") || !strcmp(op, "xor") ||
        !strcmp(op, "add") || !strcmp(op, "sub"))
    {
      emit("%s = %s ", r2, op);
      emit_type_str(ty);
      emit(" %s, %s\n", l, r_use);
    }
    else
    {
      // Treat the integer vector binop as a float vector of same width for
      // paddusb/paddsb etc.: routes through gen_ir_int_vec_binop.
      (void)r_orig;
      return gen_ir_int_vec_binop(node, indent);
    }
    return r2;
  }

  // Bitwise ops need bitcasts on float vectors.
  if (!strcmp(op, "andnot") || !strcmp(op, "and") || !strcmp(op, "or") ||
      !strcmp(op, "xor"))
  {
    if (ty->kind != TY_VECTOR)
      return gen_ir_sse_unsupported(node, indent);
    int bits = elem_ty->size * 8;
    const char *l_i = new_reg();
    emit_indent(indent);
    emit("%s = bitcast <%d x %s> %s to <%d x i%d>\n",
         l_i, ty->array_len, ty->base->kind == TY_FLOAT ? "float" : "double",
         l, ty->array_len, bits);
    const char *r_i = new_reg();
    emit_indent(indent);
    emit("%s = bitcast <%d x %s> %s to <%d x i%d>\n",
         r_i, ty->array_len, ty->base->kind == TY_FLOAT ? "float" : "double",
         r, ty->array_len, bits);
    const char *res_i = new_reg();
    emit_indent(indent);
    if (!strcmp(op, "andnot"))
    {
      const char *neg = new_reg();
      emit_indent(indent);
      emit("%s = xor <%d x i%d> %s, <", neg, ty->array_len, bits, l_i);
      for (int i = 0; i < ty->array_len; i++)
      {
        if (i > 0) emit(", ");
        emit("i%d -1", bits);
      }
      emit(">\n");
      emit("%s = and <%d x i%d> %s, %s\n", res_i, ty->array_len, bits, neg, r_i);
    }
    else
    {
      emit("%s = %s <%d x i%d> %s, %s\n",
           res_i, op, ty->array_len, bits, l_i, r_i);
    }
    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = bitcast <%d x i%d> %s to <%d x %s>\n",
         res, ty->array_len, bits, res_i,
         ty->array_len, ty->base->kind == TY_FLOAT ? "float" : "double");
    return res;
  }

  // fcmp produces i1 (or <N x i1>).
  // For scalar: zext to i32 (chibicc convention for scalar compare results).
  // For vector: sext to <N x i{elem_bits}> (to get all-1s/all-0s), then
  // bitcast back to the original float vector type (e.g. <2 x double>).
  bool is_fcmp = (op[0] == 'o' || op[0] == 'u') && op[1] != '\0';
  if (is_fcmp)
  {
    const char *cmp = new_reg();
    emit_indent(indent);
    emit("%s = fcmp %s ", cmp, op);
    emit_type_str(ty);
    emit(" %s, %s\n", l, r_use);
    const char *r2 = new_reg();
    emit_indent(indent);
    if (is_vector(ty))
    {
      int bits = elem_ty->size * 8;
      if (is_scalar_sse_cmp(node))
      {
        // SS/SD: compare only element 0, preserve upper elements from lhs
        const char *l0 = new_reg();
        emit("%s = extractelement ", l0);
        emit_type_str(ty);
        emit(" %s, i32 0\n", l);
        const char *r0 = new_reg();
        emit("%s = extractelement ", r0);
        emit_type_str(ty);
        emit(" %s, i32 0\n", r_use);
        const char *cmp_s = new_reg();
        emit("%s = fcmp %s ", cmp_s, op);
        emit_type_str(elem_ty);
        emit(" %s, %s\n", l0, r0);
        const char *sext_val = new_reg();
        emit("%s = sext i1 %s to i%d\n", sext_val, cmp_s, bits);
        const char *res_elt = new_reg();
        emit("%s = bitcast i%d %s to ", res_elt, bits, sext_val);
        emit_type_str(elem_ty);
        emit("\n");
        emit("%s = insertelement ", r2);
        emit_type_str(ty);
        emit(" %s, ", l);
        emit_type_str(elem_ty);
        emit(" %s, i32 0\n", res_elt);
      }
      else
      {
        const char *int_cmp = new_reg();
        emit("%s = sext <%d x i1> %s to <%d x i%d>\n",
             int_cmp, ty->array_len, cmp, ty->array_len, bits);
        emit("%s = bitcast <%d x i%d> %s to ", r2, ty->array_len, bits, int_cmp);
        emit_type_str(ty);
        emit("\n");
      }
    }
    else
    {
      emit("%s = zext i1 %s to i32\n", r2, cmp);
    }
    return r2;
  }

  // For unsorted compares reorder: olt -> olt, ole -> ole, etc.

  // Float min/max: use the portable llvm.minnum/maxnum intrinsics.
  // Scalar SS/SD variants compute only element 0 and preserve the upper
  // lanes from the first operand (matching the x86 scalar semantics).
  if (is_fp && (op[0] == 'm') && (op[1] == 'i' || op[1] == 'a'))
  {
    bool scalar = (node->kind == ND_MINSS || node->kind == ND_MAXSS ||
                   node->kind == ND_MINSD || node->kind == ND_MAXSD);
    if (scalar)
    {
      const char *l0 = new_reg();
      emit_indent(indent);
      emit("%s = extractelement ", l0);
      emit_type_str(ty);
      emit(" %s, i32 0\n", l);
      const char *r0 = new_reg();
      emit_indent(indent);
      emit("%s = extractelement ", r0);
      emit_type_str(ty);
      emit(" %s, i32 0\n", r_use);
      int elem_bits = elem_ty->size * 8;
      const char *res0 = new_reg();
      emit_indent(indent);
      emit("%s = call ", res0);
      emit_type_str(elem_ty);
      emit(" @llvm.%snum.f%d(", op, elem_bits);
      emit_type_str(elem_ty);
      emit(" %s, ", l0);
      emit_type_str(elem_ty);
      emit(" %s)\n", r0);
      const char *r2 = new_reg();
      emit_indent(indent);
      emit("%s = insertelement ", r2);
      emit_type_str(ty);
      emit(" %s, ", l);
      emit_type_str(elem_ty);
      emit(" %s, i32 0\n", res0);
      return r2;
    }
    int elem_bits = elem_ty->size * 8;
    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = call ", res);
    emit_type_str(ty);
    emit(" @llvm.%snum.", op);
    if (is_vector(ty))
      emit("v%d", ty->array_len);
    emit("f%d(", elem_bits);
    emit_type_str(ty);
    emit(" %s, ", l);
    emit_type_str(ty);
    emit(" %s)\n", r_use);
    return res;
  }

  // SS/SD scalar arithmetic: only element 0 is computed, the upper
  // elements are preserved from the first operand (lhs).
  if (is_scalar_sse_arith(node))
  {
    const char *l0 = new_reg();
    emit_indent(indent);
    emit("%s = extractelement ", l0);
    emit_type_str(ty);
    emit(" %s, i32 0\n", l);
    const char *r0 = new_reg();
    emit_indent(indent);
    emit("%s = extractelement ", r0);
    emit_type_str(ty);
    emit(" %s, i32 0\n", r_use);
    const char *res0 = new_reg();
    emit_indent(indent);
    emit("%s = %s ", res0, op);
    emit_type_str(elem_ty);
    emit(" %s, %s\n", l0, r0);
    const char *r2 = new_reg();
    emit_indent(indent);
    emit("%s = insertelement ", r2);
    emit_type_str(ty);
    emit(" %s, ", l);
    emit_type_str(elem_ty);
    emit(" %s, i32 0\n", res0);
    return r2;
  }

  const char *r2 = new_reg();
  emit_indent(indent);
  emit("%s = %s ", r2, op);
  emit_type_str(ty);
  emit(" %s, %s\n", l, r_use);
  return r2;
}

// Bitcast a vector register (widened as <N x i64> in chibicc's IR)
// to the canonical <count x i<elem>> shape expected by the matching
// x86 intrinsic, and return the new register.
const char *bitcast_to_intrinsic_vec(const char *src, Type *ty,
                                            int elem, int indent)
{
  int total = ty->size * 8;
  int n = total / elem;
  if (n <= 0) n = 1;
  const char *bc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", bc);
  emit_type_str(ty);
  emit(" %s to <%d x i%d>\n", src, n, elem);
  return bc;
}

const char *vec_elem_llvm_str(int bits)
{
  if (bits >= 64) return "i64";
  if (bits >= 32) return "i32";
  if (bits >= 16) return "i16";
  return "i8";
}

// __builtin_ia32_vec_ext_*: extract a single lane of a vector as a scalar.
// The vector operand (node->lhs) is a real LLVM vector; the lane index
// Reinterpret a vector value `val` (of type `from`) to the canonical
// element-width vector type `to`.  Emits a bitcast only when the shapes
// actually differ; if they are identical the value is returned unchanged.
const char *gen_ir_reinterpret_vec(const char *val, Type *from,
                                          Type *to, int indent)
{
  if (!from || !to || from == to)
    return val;
  if (from->kind != TY_VECTOR || to->kind != TY_VECTOR)
    return val;
  if (from->array_len == to->array_len &&
      from->base->kind == to->base->kind &&
      int_type_bits(from->base) == int_type_bits(to->base))
    return val;
  // LLVM bitcast requires the source and destination to have the same total
  // bit width.  When the vector kinds differ only by element width but keep
  // the same lane count (e.g. <4 x i32> vs <4 x i64>, as produced by
  // _mm256_castsi128_si256) the bitcast is illegal.  Route the reinterpret
  // through memory, which zero-extends when the destination is wider and
  // truncates when it is narrower -- always valid IR.
  if (from->size != to->size)
    return emit_reinterpret_via_mem_ty(val, from, to, indent);
  const char *bc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", bc);
  emit_type_str(from);
  emit(" %s to ", val);
  emit_type_str(to);
  emit("\n");
  return bc;
}

// __builtin_ia32_vec_ext_*: extract a single lane of a vector as a scalar.
// The vector operand (node->lhs) is a real LLVM vector; the lane index
// (node->rhs) is an integer.  The x86 backend zero-extends byte lanes
// (movzbl) and sign-extends word lanes (movswl); mirror that here.  The
// operand may be a differently-typed vector (e.g. __m128i = <2 x i64>) that
// was implicitly cast to the builtin's element shape, so reinterpret it to
// the canonical element-width vector before extractelement.
const char *gen_ir_vec_ext(Node *node, int indent)
{
  const char *vec = emit_expr(node->lhs, indent);
  const char *idx = emit_expr(node->rhs, indent);
  Type *rty = node->ty;

  int count, ebits;
  bool is_float = false;
  switch (node->kind) {
  case ND_VECEXTV16QI: count = 16; ebits = 8;  break;
  case ND_VECEXTV8HI:  count = 8;  ebits = 16; break;
  case ND_VECEXTV4HI:  count = 4;  ebits = 16; break;
  case ND_VECEXTV4SI:  count = 4;  ebits = 32; break;
  case ND_VECEXTV2SI:  count = 2;  ebits = 32; break;
  case ND_VECEXTV2DI:  count = 2;  ebits = 64; break;
  case ND_VECEXTV4SF:  count = 4;  ebits = 32; is_float = true; break;
  default:              count = 0;  ebits = 0;  break;
  }
  if (count == 0)
    return gen_ir_sse_unsupported(node, indent);

  const char *elem_str = is_float ? "float" : vec_elem_llvm_str(ebits);
  char vbuf[32];
  snprintf(vbuf, sizeof(vbuf), "<%d x %s>", count, elem_str);

  const char *bc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", bc);
  emit_type_str(node->lhs->ty);
  emit(" %s to %s\n", vec, vbuf);

  const char *ext = new_reg();
  emit_indent(indent);
  emit("%s = extractelement %s %s, i32 %s\n", ext, vbuf, bc, idx);

  if (is_float)
    return ext;

  int rbits = int_type_bits(rty);
  if (ebits <= 0 || rbits <= 0 || ebits == rbits)
    return ext;

  const char *conv = new_reg();
  emit_indent(indent);
  if (ebits < 32) {
    const char *op = (ebits == 8) ? "zext" : "sext";
    emit("%s = %s i%d %s to %s\n", conv, op, ebits, ext,
         vec_elem_llvm_str(rbits));
  } else {
    emit("%s = trunc i%d %s to %s\n", conv, ebits, ext,
         vec_elem_llvm_str(rbits));
  }
  return conv;
}

// __builtin_ia32_vec_set_*: insert a scalar into a given lane, returning the
// updated vector.  The scalar value (builtin_args[1]) is widened; truncate it
// to the vector element width before insertelement.  Like vec_ext, the
// operand vector may arrive in a differently-typed shape, so reinterpret it.
const char *gen_ir_vec_set(Node *node, int indent)
{
  const char *vec = emit_expr(node->builtin_args[0], indent);
  const char *val = emit_expr(node->builtin_args[1], indent);
  const char *idx = emit_expr(node->builtin_args[2], indent);
  Type *vty = node->ty;
  Type *ety = vty->base;
  int ebits = int_type_bits(ety);
  int vbits = int_type_bits(node->builtin_args[1]->ty);
  const char *elem_str = vec_elem_llvm_str(ebits);

  vec = gen_ir_reinterpret_vec(vec, node->builtin_args[0]->ty, vty, indent);

  const char *ve = val;
  if (ebits < vbits) {
    const char *t = new_reg();
    emit_indent(indent);
    emit("%s = trunc %s %s to %s\n", t, vec_elem_llvm_str(vbits), val, elem_str);
    ve = t;
  }

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = insertelement ", res);
  emit_type_str(vty);
  emit(" %s, %s %s, i32 %s\n", vec, elem_str, ve, idx);
  return res;
}

// __builtin_ia32_vec_init_*: build a vector from scalar lane values.
// Depending on the arity the parser stores the operands either in
// builtin_args (>=3 args) or in lhs/rhs (2-arg forms such as vec_init_v2si).
const char *gen_ir_vec_init(Node *node, int indent)
{
  Type *vty = node->ty;
  Type *ety = vty->base;
  int ebits = int_type_bits(ety);
  const char *elem_str = vec_elem_llvm_str(ebits);

  int nargs = node->builtin_nargs;
  if (nargs <= 0)
    nargs = 2;

  const char *cur = NULL;
  for (int i = 0; i < nargs; i++) {
    Node *arg = (node->builtin_nargs > 0) ? node->builtin_args[i]
                                          : (i == 0 ? node->lhs : node->rhs);
    const char *v = emit_expr(arg, indent);
    const char *ve = v;
    int vbits = int_type_bits(arg->ty);
    if (ebits < vbits) {
      const char *t = new_reg();
      emit_indent(indent);
      emit("%s = trunc %s %s to %s\n", t, vec_elem_llvm_str(vbits), v, elem_str);
      ve = t;
    }
    const char *res = new_reg();
    emit_indent(indent);
    if (i == 0) {
      emit("%s = insertelement ", res);
      emit_type_str(vty);
      emit(" undef, %s %s, i32 0\n", elem_str, ve);
    } else {
      emit("%s = insertelement ", res);
      emit_type_str(vty);
      emit(" %s, %s %s, i32 %d\n", cur, elem_str, ve, i);
    }
    cur = res;
  }

  if (!cur) {
    const char *z = new_reg();
    emit_indent(indent);
    emit("%s = add ", z);
    emit_type_str(vty);
    emit(" zeroinitializer, zeroinitializer\n");
    return z;
  }
  return cur;
}

// Bitcast a vector value `v` (of LLVM shape `emit_type_str(ty)`) to the
// canonical element-width vector `<N x i{ebits}>`.  `ty` is the operand's
// chibicc vector type; N = ty->size*8 / ebits.
const char *gen_ir_bitcast_vec_to_elem(const char *v, Type *ty,
                                              int ebits, int indent)
{
  int total = ty->size * 8;
  int n = total / ebits;
  if (n <= 0) n = 1;
  char vstr[32];
  snprintf(vstr, sizeof vstr, "<%d x i%d>", n, ebits);
  const char *bc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", bc);
  emit_type_str(ty);
  emit(" %s to %s\n", v, vstr);
  return bc;
}

// Horizontal packed add/sub (PHADD*/PHSUB*): concatenate the two source
// vectors into one 2N-lane vector, then combine adjacent lanes
// (result[i] = concat[2i] +/- concat[2i+1]).  `sat` selects signed
// saturating arithmetic (PHADDsw/PHSUBsw) via the portable llvm sadd/ssub
// intrinsics.
const char *gen_ir_horizontal(Node *node, int indent, int ebits,
                                     bool sub, bool sat)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);

  int total = ty->size * 8;
  int N = total / ebits;
  if (N <= 0) N = 1;
  int M = 2 * N;
  char vN[32], vM[32];
  snprintf(vN, sizeof vN, "<%d x i%d>", N, ebits);
  snprintf(vM, sizeof vM, "<%d x i%d>", M, ebits);

  const char *lc = gen_ir_bitcast_vec_to_elem(l, ty, ebits, indent);
  const char *rc = gen_ir_bitcast_vec_to_elem(r, ty, ebits, indent);

  const char *concat = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s %s, <%d x i32> <",
       concat, vN, lc, vN, rc, M);
  for (int i = 0; i < M; i++) {
    if (i) emit(", ");
    emit("i32 %d", i);
  }
  emit(">\n");

  const char *ev = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s undef, <%d x i32> <",
       ev, vM, concat, vM, N);
  for (int i = 0; i < N; i++) {
    if (i) emit(", ");
    emit("i32 %d", 2 * i);
  }
  emit(">\n");

  const char *od = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s undef, <%d x i32> <",
       od, vM, concat, vM, N);
  for (int i = 0; i < N; i++) {
    if (i) emit(", ");
    emit("i32 %d", 2 * i + 1);
  }
  emit(">\n");

  const char *res = new_reg();
  emit_indent(indent);
  if (sat) {
    const char *satop = sub ? "ssub.sat" : "sadd.sat";
    char iname[48];
    snprintf(iname, sizeof iname, "llvm.%s.v%di%d", satop, N, ebits);
    emit("%s = call %s @%s(%s %s, %s %s)\n",
         res, vN, iname, vN, ev, vN, od);
  } else {
    emit("%s = %s %s %s, %s\n", res, sub ? "sub" : "add", vN, ev, od);
  }

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, vN, res);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

// PMADDWD: multiply adjacent signed 16-bit words of a and b, then
// horizontally add each pair of products to a 32-bit dword.
const char *gen_ir_pmaddwd(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);

  int total = ty->size * 8;
  int N = total / 16;
  if (N <= 0) N = 1;
  int N2 = N / 2;
  char vw[32], vw32[32], vd[32];
  snprintf(vw, sizeof vw, "<%d x i16>", N);
  snprintf(vw32, sizeof vw32, "<%d x i32>", N);
  snprintf(vd, sizeof vd, "<%d x i32>", N2);

  const char *lc = gen_ir_bitcast_vec_to_elem(l, ty, 16, indent);
  const char *rc = gen_ir_bitcast_vec_to_elem(r, ty, 16, indent);

  const char *le = new_reg();
  emit_indent(indent);
  emit("%s = sext %s %s to %s\n", le, vw, lc, vw32);
  const char *re = new_reg();
  emit_indent(indent);
  emit("%s = sext %s %s to %s\n", re, vw, rc, vw32);

  const char *p = new_reg();
  emit_indent(indent);
  emit("%s = mul %s %s, %s\n", p, vw32, le, re);

  const char *ev = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s undef, <%d x i32> <",
       ev, vw32, p, vw32, N2);
  for (int i = 0; i < N2; i++) {
    if (i) emit(", ");
    emit("i32 %d", 2 * i);
  }
  emit(">\n");

  const char *od = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s undef, <%d x i32> <",
       od, vw32, p, vw32, N2);
  for (int i = 0; i < N2; i++) {
    if (i) emit(", ");
    emit("i32 %d", 2 * i + 1);
  }
  emit(">\n");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = add %s %s, %s\n", res, vd, ev, od);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, vd, res);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

// PMADDUBSW: multiply unsigned byte a by signed byte b, sum adjacent pairs
// and saturate to a signed 16-bit word.
const char *gen_ir_pmaddubsw(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);

  int total = ty->size * 8;
  int N = total / 8;
  if (N <= 0) N = 1;
  int N2 = N / 2;
  char vb[32], vw[32], vw2[32];
  snprintf(vb, sizeof vb, "<%d x i8>", N);
  snprintf(vw, sizeof vw, "<%d x i16>", N);
  snprintf(vw2, sizeof vw2, "<%d x i16>", N2);

  const char *lc = gen_ir_bitcast_vec_to_elem(l, ty, 8, indent);
  const char *rc = gen_ir_bitcast_vec_to_elem(r, ty, 8, indent);

  const char *le = new_reg();
  emit_indent(indent);
  emit("%s = zext %s %s to %s\n", le, vb, lc, vw);
  const char *re = new_reg();
  emit_indent(indent);
  emit("%s = sext %s %s to %s\n", re, vb, rc, vw);

  const char *p = new_reg();
  emit_indent(indent);
  emit("%s = mul %s %s, %s\n", p, vw, le, re);

  const char *ev = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s undef, <%d x i32> <",
       ev, vw, p, vw, N2);
  for (int i = 0; i < N2; i++) {
    if (i) emit(", ");
    emit("i32 %d", 2 * i);
  }
  emit(">\n");

  const char *od = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s undef, <%d x i32> <",
       od, vw, p, vw, N2);
  for (int i = 0; i < N2; i++) {
    if (i) emit(", ");
    emit("i32 %d", 2 * i + 1);
  }
  emit(">\n");

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = call %s @llvm.sadd.sat.v%di16(%s %s, %s %s)\n",
       res, vw2, N2, vw2, ev, vw2, od);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, vw2, res);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

// PHMINPOSUW: find the first (lowest-index) unsigned 16-bit word minimum of
// a 128-bit vector and return [min, index, 0, 0, 0, 0, 0, 0].
const char *gen_ir_phminposuw(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  const char *a = emit_expr(node->lhs, indent);
  const char *av = gen_ir_bitcast_vec_to_elem(a, ty, 16, indent);

  // Parallel unsigned-min reduction over the 8 lanes (tree of umin).
  const char *h = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector <8 x i16> %s, <8 x i16> %s, "
       "<8 x i32> <i32 4, i32 5, i32 6, i32 7, "
       "i32 undef, i32 undef, i32 undef, i32 undef>\n",
       h, av, av);
  const char *m1 = new_reg();
  emit_indent(indent);
  emit("%s = call <8 x i16> @llvm.umin.v8i16(<8 x i16> %s, <8 x i16> %s)\n",
       m1, av, h);
  const char *h2 = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector <8 x i16> %s, <8 x i16> %s, "
       "<8 x i32> <i32 2, i32 3, i32 undef, i32 undef, "
       "i32 undef, i32 undef, i32 undef, i32 undef>\n",
       h2, m1, m1);
  const char *m2 = new_reg();
  emit_indent(indent);
  emit("%s = call <8 x i16> @llvm.umin.v8i16(<8 x i16> %s, <8 x i16> %s)\n",
       m2, m1, h2);
  const char *h3 = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector <8 x i16> %s, <8 x i16> %s, "
       "<8 x i32> <i32 1, i32 undef, i32 undef, i32 undef, "
       "i32 undef, i32 undef, i32 undef, i32 undef>\n",
       h3, m2, m2);
  const char *m3 = new_reg();
  emit_indent(indent);
  emit("%s = call <8 x i16> @llvm.umin.v8i16(<8 x i16> %s, <8 x i16> %s)\n",
       m3, m2, h3);

  // Broadcast the minimum to all lanes for the equality comparison.
  const char *minb = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector <8 x i16> %s, <8 x i16> %s, "
       "<8 x i32> <i32 0, i32 0, i32 0, i32 0, "
       "i32 0, i32 0, i32 0, i32 0>\n",
       minb, m3, m3);

  const char *eq = new_reg();
  emit_indent(indent);
  emit("%s = icmp eq <8 x i16> %s, %s\n", eq, av, minb);

  // For each lane, keep its index if it equals the min, else a large value;
  // the (unique) first matching index is the unsigned minimum of those.
  const char *sel = new_reg();
  emit_indent(indent);
  emit("%s = select <8 x i1> %s, <8 x i32> <i32 0, i32 1, i32 2, i32 3, "
       "i32 4, i32 5, i32 6, i32 7>, "
       "<8 x i32> <i32 255, i32 255, i32 255, i32 255, "
       "i32 255, i32 255, i32 255, i32 255>\n",
       sel, eq);

  const char *s1 = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector <8 x i32> %s, <8 x i32> %s, "
       "<8 x i32> <i32 4, i32 5, i32 6, i32 7, "
       "i32 undef, i32 undef, i32 undef, i32 undef>\n",
       s1, sel, sel);
  const char *r1 = new_reg();
  emit_indent(indent);
  emit("%s = call <8 x i32> @llvm.umin.v8i32(<8 x i32> %s, <8 x i32> %s)\n",
       r1, sel, s1);
  const char *s2 = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector <8 x i32> %s, <8 x i32> %s, "
       "<8 x i32> <i32 2, i32 3, i32 undef, i32 undef, "
       "i32 undef, i32 undef, i32 undef, i32 undef>\n",
       s2, r1, r1);
  const char *r2 = new_reg();
  emit_indent(indent);
  emit("%s = call <8 x i32> @llvm.umin.v8i32(<8 x i32> %s, <8 x i32> %s)\n",
       r2, r1, s2);
  const char *s3 = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector <8 x i32> %s, <8 x i32> %s, "
       "<8 x i32> <i32 1, i32 undef, i32 undef, i32 undef, "
       "i32 undef, i32 undef, i32 undef, i32 undef>\n",
       s3, r2, r2);
  const char *idx = new_reg();
  emit_indent(indent);
  emit("%s = call <8 x i32> @llvm.umin.v8i32(<8 x i32> %s, <8 x i32> %s)\n",
       idx, r2, s3);

  // Build [min, index, 0, 0, 0, 0, 0, 0].
  const char *minv = new_reg();
  emit_indent(indent);
  emit("%s = extractelement <8 x i16> %s, i32 0\n", minv, minb);
  const char *idxv = new_reg();
  emit_indent(indent);
  emit("%s = extractelement <8 x i32> %s, i32 0\n", idxv, idx);
  const char *idx16 = new_reg();
  emit_indent(indent);
  emit("%s = trunc i32 %s to i16\n", idx16, idxv);

  const char *zero = new_reg();
  emit_indent(indent);
  emit("%s = add <8 x i16> zeroinitializer, zeroinitializer\n", zero);
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = insertelement <8 x i16> %s, i16 %s, i32 0\n", res, zero, minv);
  const char *res2 = new_reg();
  emit_indent(indent);
  emit("%s = insertelement <8 x i16> %s, i16 %s, i32 1\n", res2, res, idx16);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast <8 x i16> %s to ", out, res2);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

// __builtin_shuffle(a, mask) / __builtin_shuffle(a, b, mask): per-lane
// selection from the concatenation (a, b) using the runtime integer mask.
// Built with extractelement/select/insertelement so it works for non-constant
// masks as well (LLVM's shufflevector requires a constant mask).
const char *gen_ir_shuffle(Node *node, int indent)
{
  Type *ty = node->ty;
  if (ty->kind != TY_VECTOR)
    return gen_ir_sse_unsupported(node, indent);
  int n = ty->array_len;
  if (n <= 0)
    return gen_ir_sse_unsupported(node, indent);

  Type *m_ty = node->builtin_args[2]->ty;
  int mn = m_ty->array_len;
  if (mn <= 0)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->builtin_args[0], indent);
  const char *b = emit_expr(node->builtin_args[1], indent);
  const char *m = emit_expr(node->builtin_args[2], indent);

  const char *res = NULL;
  for (int i = 0; i < n; i++) {
    const char *idx = new_reg();
    emit_indent(indent);
    emit("%s = extractelement ", idx);
    emit_type_str(m_ty);
    emit(" %s, i32 %d\n", m, i);

    // The shuffle index must be an i32 (the lane index width used by
    // extractelement/icmp/sub).  Normalize a wider mask element
    // (e.g. <2 x i64>) down to i32 first.
    int mb = int_type_bits(m_ty->base);
    if (mb != 32) {
      const char *idx32 = new_reg();
      emit_indent(indent);
      emit("%s = %s i%d %s to i32\n", idx32,
           (mb > 32) ? "trunc" : "zext", mb, idx);
      idx = idx32;
    }

    const char *is_b = new_reg();
    emit_indent(indent);
    emit("%s = icmp uge i32 %s, %d\n", is_b, idx, n);

    const char *b_idx = new_reg();
    emit_indent(indent);
    emit("%s = sub i32 %s, %d\n", b_idx, idx, n);

    const char *elem_a = new_reg();
    emit_indent(indent);
    emit("%s = extractelement ", elem_a);
    emit_type_str(ty);
    emit(" %s, i32 %s\n", a, idx);

    const char *elem_b = new_reg();
    emit_indent(indent);
    emit("%s = extractelement ", elem_b);
    emit_type_str(ty);
    emit(" %s, i32 %s\n", b, b_idx);

    const char *elem = new_reg();
    emit_indent(indent);
    emit("%s = select i1 %s, ", elem, is_b);
    emit_type_str(ty->base);
    emit(" %s, ", elem_b);
    emit_type_str(ty->base);
    emit(" %s\n", elem_a);

    const char *next = new_reg();
    emit_indent(indent);
    if (i == 0) {
      emit("%s = insertelement ", next);
      emit_type_str(ty);
      emit(" undef, ");
      emit_type_str(ty->base);
      emit(" %s, i32 0\n", elem);
    } else {
      emit("%s = insertelement ", next);
      emit_type_str(ty);
      emit(" %s, ", res);
      emit_type_str(ty->base);
      emit(" %s, i32 %d\n", elem, i);
    }
    res = next;
  }

  return res;
}

const char *gen_ir_int_vec_binop(Node *node, int indent)
{
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;

  // --- Horizontal add/sub and multiply-add builtins (SSSE3/SSE2). ---
  switch (node->kind) {
  case ND_PHADDW:  case ND_PHADDW128:
    return gen_ir_horizontal(node, indent, 16, false, false);
  case ND_PHADDD:  case ND_PHADDD128:
    return gen_ir_horizontal(node, indent, 32, false, false);
  case ND_PHADDSW: case ND_PHADDSW128:
    return gen_ir_horizontal(node, indent, 16, false, true);
  case ND_PHSUBW:  case ND_PHSUBW128:
    return gen_ir_horizontal(node, indent, 16, true, false);
  case ND_PHSUBD:  case ND_PHSUBD128:
    return gen_ir_horizontal(node, indent, 32, true, false);
  case ND_PHSUBSW: case ND_PHSUBSW128:
    return gen_ir_horizontal(node, indent, 16, true, true);
  case ND_PMADDWD: case ND_PMADDWD128:
    return gen_ir_pmaddwd(node, indent);
  case ND_PMADDUBSW: case ND_PMADDUBSW128:
    return gen_ir_pmaddubsw(node, indent);
  case ND_PHMINPOSUW128:
    return gen_ir_phminposuw(node, indent);
  default: break;
  }

  // --- Portable packed integer vector binops (no x86-specific intrinsics). ---
  // Saturating add/sub lower via LLVM's sadd.sat/ssub.sat/uadd.sat/usub.sat
  // and the packed multiplies lower via plain vector arithmetic, so they are
  // robust across LLVM versions and avoid the MMX (x86_mmx) type-width
  // mismatch that makes the matching x86 intrinsics unlinkable.
  enum {
    OP_NONE, OP_SADD, OP_SSUB, OP_UADD, OP_USUB,
    OP_MULLOW, OP_MULHWS, OP_MULHWU, OP_MULHRSW,
    OP_MULDQ_S, OP_MULDQ_U, OP_PAVG, OP_PCMPEQ, OP_PCMPGT,
    OP_SMIN, OP_SMAX, OP_UMIN, OP_UMAX, OP_PSIGN
  } op = OP_NONE;
  int ebits = 0;

  switch (node->kind) {
  case ND_PSIGNB:  case ND_PSIGNB128:  ebits = 8;  op = OP_PSIGN; break;
  case ND_PSIGNW:  case ND_PSIGNW128:  ebits = 16; op = OP_PSIGN; break;
  case ND_PSIGND:  case ND_PSIGND128:  ebits = 32; op = OP_PSIGN; break;
  case ND_PADDSB:  case ND_PADDSB128:   ebits = 8;  op = OP_SADD; break;
  case ND_PADDSW:  case ND_PADDSW128:   ebits = 16; op = OP_SADD; break;
  case ND_PADDUSB: case ND_PADDUSB128:  ebits = 8;  op = OP_UADD; break;
  case ND_PADDUSW: case ND_PADDUSW128:  ebits = 16; op = OP_UADD; break;
  case ND_PSUBSB:  case ND_PSUBSB128:   ebits = 8;  op = OP_SSUB; break;
  case ND_PSUBSW:  case ND_PSUBSW128:   ebits = 16; op = OP_SSUB; break;
  case ND_PSUBUSB: case ND_PSUBUSB128: case ND_PSUBUSB256:
    ebits = 8;  op = OP_USUB; break;
  case ND_PSUBUSW: case ND_PSUBUSW128:  ebits = 16; op = OP_USUB; break;

  case ND_PMULLW:                         ebits = 16; op = OP_MULLOW; break;
  case ND_PMULHW:  case ND_PMULHW128:     ebits = 16; op = OP_MULHWS; break;
  case ND_PMULHUW: case ND_PMULHUW128: case ND_PMULHUW256:
    ebits = 16; op = OP_MULHWU; break;
  case ND_PMULHRSW: case ND_PMULHRSW128:  ebits = 16; op = OP_MULHRSW; break;

  case ND_PMULDQ128:  ebits = 32; op = OP_MULDQ_S; break;
  case ND_PMULUDQ:  ebits = 32; op = OP_MULDQ_U; break;
  case ND_PMULUDQ128: ebits = 32; op = OP_MULDQ_U; break;

  case ND_PAVGB:  case ND_PAVGB128:  ebits = 8;  op = OP_PAVG; break;
  case ND_PAVGW:  case ND_PAVGW128:  ebits = 16; op = OP_PAVG; break;
  case ND_PCMPEQB: ebits = 8;  op = OP_PCMPEQ; break;
  case ND_PCMPEQW: ebits = 16; op = OP_PCMPEQ; break;
  case ND_PCMPEQD: ebits = 32; op = OP_PCMPEQ; break;
  case ND_PCMPGTB: ebits = 8;  op = OP_PCMPGT; break;
  case ND_PCMPGTW: ebits = 16; op = OP_PCMPGT; break;
  case ND_PCMPGTD: ebits = 32; op = OP_PCMPGT; break;

  // Packed integer min/max (lower via the portable llvm.smin/smax/umin/umax
  // intrinsics, matching the per-lane signed/unsigned semantics of the x86
  // pmin*/pmax* instructions).
  case ND_PMINSW:  case ND_PMINSW128:  ebits = 16; op = OP_SMIN; break;
  case ND_PMAXSW:  case ND_PMAXSW128:  ebits = 16; op = OP_SMAX; break;
  case ND_PMINUB:  case ND_PMINUB128:  ebits = 8;  op = OP_UMIN; break;
  case ND_PMAXUB:  case ND_PMAXUB128:  ebits = 8;  op = OP_UMAX; break;
  case ND_PMINSB128: ebits = 8;  op = OP_SMIN; break;
  case ND_PMAXSB128: ebits = 8;  op = OP_SMAX; break;
  case ND_PMINUW128: ebits = 16; op = OP_UMIN; break;
  case ND_PMAXUW128: ebits = 16; op = OP_UMAX; break;
  case ND_PMINSD128: ebits = 32; op = OP_SMIN; break;
  case ND_PMAXSD128: ebits = 32; op = OP_SMAX; break;
  case ND_PMINUD128: ebits = 32; op = OP_UMIN; break;
  case ND_PMAXUD128: ebits = 32; op = OP_UMAX; break;
  default: break;
  }

  if (op != OP_NONE) {
    const char *l = emit_expr(node->lhs, indent);
    const char *r = emit_expr(node->rhs, indent);

    int total = ty->size * 8;
    int n = total / ebits;
    if (n <= 0) n = 1;
    char vstr[32];
    snprintf(vstr, sizeof vstr, "<%d x i%d>", n, ebits);

    const char *lc = new_reg();
    emit_indent(indent);
    emit("%s = bitcast ", lc); emit_type_str(ty); emit(" %s to %s\n", l, vstr);
    const char *rc = new_reg();
    emit_indent(indent);
    emit("%s = bitcast ", rc); emit_type_str(ty); emit(" %s to %s\n", r, vstr);

    const char *res = new_reg();

    switch (op) {
    case OP_SADD: case OP_SSUB: case OP_UADD: case OP_USUB: {
      const char *sat = (op == OP_SADD) ? "sadd.sat" :
                        (op == OP_SSUB) ? "ssub.sat" :
                        (op == OP_UADD) ? "uadd.sat" : "usub.sat";
      char iname[48];
      snprintf(iname, sizeof iname, "llvm.%s.v%di%d", sat, n, ebits);
      emit_indent(indent);
      emit("%s = call %s @%s(%s %s, %s %s)\n",
           res, vstr, iname, vstr, lc, vstr, rc);
      break;
    }
    case OP_MULLOW:
      emit_indent(indent);
      emit("%s = mul %s %s, %s\n", res, vstr, lc, rc);
      break;
    case OP_MULHWS: case OP_MULHWU: {
      char w32[32];
      snprintf(w32, sizeof w32, "<%d x i32>", n);
      const char *le = new_reg();
      emit_indent(indent);
      emit("%s = %s %s %s to %s\n", le,
           (op == OP_MULHWS) ? "sext" : "zext", vstr, lc, w32);
      const char *re = new_reg();
      emit_indent(indent);
      emit("%s = %s %s %s to %s\n", re,
           (op == OP_MULHWS) ? "sext" : "zext", vstr, rc, w32);
      const char *p = new_reg();
      emit_indent(indent);
      emit("%s = mul %s %s, %s\n", p, w32, le, re);
      const char *sh = new_reg();
      emit_indent(indent);
      emit("%s = %s %s %s, <", sh,
           (op == OP_MULHWS) ? "ashr" : "lshr", w32, p);
      for (int i = 0; i < n; i++) {
        if (i) emit(", ");
        emit("i32 16");
      }
      emit(">\n");
      emit_indent(indent);
      emit("%s = trunc %s %s to %s\n", res, w32, sh, vstr);
      break;
    }
    case OP_MULHRSW: {
      char w32[32];
      snprintf(w32, sizeof w32, "<%d x i32>", n);
      const char *le = new_reg();
      emit_indent(indent);
      emit("%s = sext %s %s to %s\n", le, vstr, lc, w32);
      const char *re = new_reg();
      emit_indent(indent);
      emit("%s = sext %s %s to %s\n", re, vstr, rc, w32);
      const char *p = new_reg();
      emit_indent(indent);
      emit("%s = mul %s %s, %s\n", p, w32, le, re);
      const char *c = new_reg();
      emit_indent(indent);
      emit("%s = add %s %s, <", c, w32, p);
      for (int i = 0; i < n; i++) {
        if (i) emit(", ");
        emit("i32 16384");
      }
      emit(">\n");
      const char *sh = new_reg();
      emit_indent(indent);
      emit("%s = ashr %s %s, <", sh, w32, c);
      for (int i = 0; i < n; i++) {
        if (i) emit(", ");
        emit("i32 15");
      }
      emit(">\n");
      emit_indent(indent);
      emit("%s = trunc %s %s to %s\n", res, w32, sh, vstr);
      break;
    }
    case OP_MULDQ_S: case OP_MULDQ_U: {
      // Multiply the even 32-bit lanes to 64-bit results.  Reinterpret the
      // operands as <k x i32> (k = total/32; k=4 for 128-bit, k=2 for 64-bit
      // MMX), gather the even lanes {0,2,...} via shufflevector, extend to
      // i64 (sext for signed, zext for unsigned) and multiply.  This is
      // portable and avoids the (unlinkable) x86 pmuldq/pmuludq intrinsics.
      int k = total / 32;
      if (k <= 0) k = 1;
      char vin[32];
      snprintf(vin, sizeof vin, "<%d x i32>", k);
      const char *li = new_reg();
      emit_indent(indent);
      emit("%s = bitcast ", li); emit_type_str(ty);
      emit(" %s to %s\n", l, vin);
      const char *ri = new_reg();
      emit_indent(indent);
      emit("%s = bitcast ", ri); emit_type_str(ty);
      emit(" %s to %s\n", r, vin);

      char vshuf[32];
      snprintf(vshuf, sizeof vshuf, "<%d x i32>", k / 2);
      const char *la = new_reg();
      emit_indent(indent);
      emit("%s = shufflevector %s %s, %s zeroinitializer, <%d x i32> <",
           la, vin, li, vin, k / 2);
      for (int i = 0; i < k / 2; i++) {
        if (i) emit(", ");
        emit("i32 %d", 2 * i);
      }
      emit(">\n");
      const char *lb = new_reg();
      emit_indent(indent);
      emit("%s = shufflevector %s %s, %s zeroinitializer, <%d x i32> <",
           lb, vin, ri, vin, k / 2);
      for (int i = 0; i < k / 2; i++) {
        if (i) emit(", ");
        emit("i32 %d", 2 * i);
      }
      emit(">\n");

      char vout[32];
      snprintf(vout, sizeof vout, "<%d x i64>", k / 2);
      const char *la64 = new_reg();
      emit_indent(indent);
      emit("%s = %s %s %s to %s\n", la64,
           (op == OP_MULDQ_S) ? "sext" : "zext", vshuf, la, vout);
      const char *lb64 = new_reg();
      emit_indent(indent);
      emit("%s = %s %s %s to %s\n", lb64,
           (op == OP_MULDQ_S) ? "sext" : "zext", vshuf, lb, vout);

      emit_indent(indent);
      emit("%s = mul %s %s, %s\n", res, vout, la64, lb64);

      const char *out = new_reg();
      emit_indent(indent);
      emit("%s = bitcast %s %s to ", out, vout, res);
      emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

    case OP_PAVG: {
      // (a + b + 1) >> 1, computed in a widened (unsigned) type.
      int wide = ebits * 2;
      char w[32];
      snprintf(w, sizeof w, "<%d x i%d>", n, wide);
      const char *le = new_reg();
      emit_indent(indent);
      emit("%s = zext %s %s to %s\n", le, vstr, lc, w);
      const char *re = new_reg();
      emit_indent(indent);
      emit("%s = zext %s %s to %s\n", re, vstr, rc, w);
      const char *s = new_reg();
      emit_indent(indent);
      emit("%s = add %s %s, %s\n", s, w, le, re);
      const char *s1 = new_reg();
      emit_indent(indent);
      emit("%s = add %s %s, <", s1, w, s);
      for (int i = 0; i < n; i++) {
        if (i) emit(", ");
        emit("i%d 1", wide);
      }
      emit(">\n");
      const char *avg = new_reg();
      emit_indent(indent);
      emit("%s = lshr %s %s, <", avg, w, s1);
      for (int i = 0; i < n; i++) {
        if (i) emit(", ");
        emit("i%d 1", wide);
      }
      emit(">\n");
      emit_indent(indent);
      emit("%s = trunc %s %s to %s\n", res, w, avg, vstr);
      break;
    }
    case OP_PCMPEQ: case OP_PCMPGT: {
      // icmp over the logical element type, then sext the i1 mask to the
      // element width so each lane is 0 or all-ones (matching x86 semantics).
      const char *cmp = new_reg();
      emit_indent(indent);
      emit("%s = icmp %s %s %s, %s\n", cmp,
           (op == OP_PCMPEQ) ? "eq" : "sgt", vstr, lc, rc);
      emit_indent(indent);
      emit("%s = sext <%d x i1> %s to %s\n", res, n, cmp, vstr);
      break;
    }
    case OP_SMIN: case OP_SMAX: case OP_UMIN: case OP_UMAX: {
      // Per-lane min/max via the portable LLVM intrinsics.
      const char *minmax = (op == OP_SMIN) ? "smin" :
                           (op == OP_SMAX) ? "smax" :
                           (op == OP_UMIN) ? "umin" : "umax";
      char iname[48];
      snprintf(iname, sizeof iname, "llvm.%s.v%di%d", minmax, n, ebits);
      emit_indent(indent);
      emit("%s = call %s @%s(%s %s, %s %s)\n",
           res, vstr, iname, vstr, lc, vstr, rc);
      break;
    }
    case OP_PSIGN: {
      // r[i] = a[i] * sign(b[i]);  sign(b) in {-1, 0, +1}.
      // sign = (b > 0 ? 1 : 0) + (b < 0 ? -1 : 0), computed as
      // sext(icmp sgt b, 0) + sext(icmp slt b, 0).
      const char *gt = new_reg();
      emit_indent(indent);
      emit("%s = icmp sgt %s %s, zeroinitializer\n", gt, vstr, rc);
      const char *lt = new_reg();
      emit_indent(indent);
      emit("%s = icmp slt %s %s, zeroinitializer\n", lt, vstr, rc);
      const char *gtx = new_reg();
      emit_indent(indent);
      emit("%s = zext <%d x i1> %s to %s\n", gtx, n, gt, vstr);
      const char *ltx = new_reg();
      emit_indent(indent);
      emit("%s = zext <%d x i1> %s to %s\n", ltx, n, lt, vstr);
      const char *sign = new_reg();
      emit_indent(indent);
      // sign = (b > 0) - (b < 0), giving +1, -1 or 0 per lane.
      emit("%s = sub %s %s, %s\n", sign, vstr, gtx, ltx);
      emit_indent(indent);
      emit("%s = mul %s %s, %s\n", res, vstr, lc, sign);
      break;
    }
    default: break;
    }

    const char *out = new_reg();
    emit_indent(indent);
    emit("%s = bitcast %s %s to ", out, vstr, res);
    emit_type_str((is_vector(node->ty)) ? node->ty : ty);
    emit("\n");
    return out;
  }

  // --- Legacy x86-intrinsic path (pmadd/psadbw only; the rest are emitted
  //     portably above). ---
  const char *intrinsic;
  switch (node->kind) {
  case ND_PSADBW: case ND_PSADBW128: intrinsic = "llvm.x86.sse2.psad.bw"; break;
  case ND_PMADDWD: case ND_PMADDWD128: intrinsic = "llvm.x86.sse2.pmadd.wd"; break;
  case ND_PMADDUBSW: case ND_PMADDUBSW128:
    intrinsic = "llvm.x86.ssse3.pmadd.ub.sw"; break;
  default:
    return gen_ir_sse_unsupported(node, indent);
  }

  // pmadd/psad have a different result width than their inputs, so leave
  // them on the unsupported (valid-placeholder) path for now.
  if (strstr(intrinsic, "pmadd") || strstr(intrinsic, "psad"))
    return gen_ir_sse_unsupported(node, indent);

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);

  // The chibicc LLVM type for an integer vector is <N x i64> (the
  // element size is widened), but the x86 intrinsics expect the
  // natural element width.  Bitcast the operands to the intrinsic's
  // canonical shape, call it, then bitcast the result back.
  int elem = 8;
  if (strstr(intrinsic, ".q")) elem = 64;
  else if (strstr(intrinsic, ".d")) elem = 32;
  else if (strstr(intrinsic, ".w")) elem = 16;

  Type *ty2 = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int total = ty2->size * 8;
  int n = total / elem;
  if (n <= 0) n = 1;

  const char *lc = bitcast_to_intrinsic_vec(l, ty2, elem, indent);
  const char *rc = bitcast_to_intrinsic_vec(r, ty2, elem, indent);

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = call <%d x i%d> @%s(<%d x i%d> %s, <%d x i%d> %s)\n",
       res, n, elem, intrinsic, n, elem, lc, n, elem, rc);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast <%d x i%d> %s to ", out, n, elem, res);
  // Bitcast the intrinsic result back to the builtin's declared return
  // type (node->ty).  The operands were bitcast using node->lhs->ty, which
  // may be a different element-width vector of the same total size (e.g.
  // __v32qi vs __m256i).  Using node->ty keeps the emitted value type in
  // agreement with the type assigned in type.c.
  emit_type_str((is_vector(node->ty)) ? node->ty : ty2);
  emit("\n");
  return out;
}

bool is_punpck_high(Node *node)
{
  switch (node->kind)
  {
  case ND_PUNPCKHBW: case ND_PUNPCKHWD: case ND_PUNPCKHDQ:
  case ND_PUNPCKHBW128: case ND_PUNPCKHWD128: case ND_PUNPCKHDQ128:
  case ND_PUNPCKHQDQ128:
    return true;
  default:
    return false;
  }
}

const char *gen_ir_punpck(Node *node, int indent)
{
  // PUNPCKxx interleaves the low (l) or high (h) halves of two equal-length
  // vectors: for each i in [0, N/2) the result holds (a[base+i], b[base+i]).
  // This is a pure shuffle, emitted as an LLVM shufflevector over the
  // concatenated (a, b) vector.  Mask index convention for shufflevector:
  // element k of the first operand is at index k, element k of the second at
  // index N + k.
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int n = ty->array_len;
  if (n <= 0)
    return gen_ir_sse_unsupported(node, indent);

  const char *a = emit_expr(node->lhs, indent);
  const char *b = emit_expr(node->rhs, indent);

  int base = is_punpck_high(node) ? n / 2 : 0;

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector ", res);
  emit_type_str(ty);
  emit(" %s, ", a);
  emit_type_str(ty);
  emit(" %s, <%d x i32> <", b, n);
  for (int i = 0; i < n / 2; i++)
  {
    if (i > 0) emit(", ");
    emit("i32 %d, i32 %d", base + i, n + base + i);
  }
  emit(">\n");

  // The shuffle is performed at the operand's element granularity (the
  // intrinsic header casts the inputs to the right vector type, e.g.
  // (__v2di) for punpckhqdq), so its result type is `ty`.  The builtin
  // node itself, however, is typed as the canonical __m128i/__m256i
  // representation (node->ty), which may use a different element type for
  // the same byte width.  Reinterpret the result to node->ty so callers
  // that wrap it in a (__m128i)/(__m256i) cast emit a consistent bitcast.
  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", out);
  emit_type_str(ty);
  emit(" %s to ", res);
  emit_type_str(node->ty);
  emit("\n");
  return out;
}

const char *gen_ir_int_vec_unary(Node *node, int indent)
{
  // Packed integer vector unary: pabsb/pabsw/pabsd.
  const char *l = emit_expr(node->lhs, indent);
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  int bits = int_type_bits(ty->base);
  if (bits <= 0) bits = 32;

  // abs(x) = (x ^ (x >> (W-1))) - (x >> (W-1))
  // LLVM requires the shift amount to be a vector of the same length.
  const char *mask = new_reg();
  emit_indent(indent);
  const char *op = ty->base->is_unsigned ? "lshr" : "ashr";
  emit("%s = %s <%d x i%d> %s, <", mask, op, ty->array_len, bits, l);
  for (int i = 0; i < ty->array_len; i++)
  {
    if (i > 0) emit(", ");
    emit("i%d %d", bits, bits - 1);
  }
  emit(">\n");
  const char *xor_r = new_reg();
  emit_indent(indent);
  emit("%s = xor <%d x i%d> %s, %s\n",
       xor_r, ty->array_len, bits, l, mask);
  const char *sub_r = new_reg();
  emit_indent(indent);
  emit("%s = sub <%d x i%d> %s, %s\n",
       sub_r, ty->array_len, bits, xor_r, mask);
  return sub_r;
}

const char *gen_ir_comi(Node *node, int indent)
{
  // COMIxx and UCOMIxx: comparison that produces a scalar int (0/1).
  // Only the low element (index 0) of each vector operand is compared.
  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);
  const char *cond;
  bool unordered = false;
  switch (node->kind)
  {
  case ND_COMIEQ:  case ND_COMISDEQ:  cond = "oeq"; unordered = false; break;
  case ND_COMINEQ: case ND_COMISDNEQ: cond = "une"; unordered = false; break;
  case ND_COMILT:  case ND_COMISDLT:  cond = "olt"; unordered = false; break;
  case ND_COMILE:  case ND_COMISDLE:  cond = "ole"; unordered = false; break;
  case ND_COMIGT:  case ND_COMISDGT:  cond = "ogt"; unordered = false; break;
  case ND_COMIGE:  case ND_COMISDGE:  cond = "oge"; unordered = false; break;
  case ND_UCOMIEQ:  case ND_UCOMISDEQ:  cond = "oeq"; unordered = true; break;
  case ND_UCOMINEQ: case ND_UCOMISDNEQ: cond = "une"; unordered = true; break;
  case ND_UCOMILT:  case ND_UCOMISDLT:  cond = "olt"; unordered = true; break;
  case ND_UCOMILE:  case ND_UCOMISDLE:  cond = "ole"; unordered = true; break;
  case ND_UCOMIGT:  case ND_UCOMISDGT:  cond = "ogt"; unordered = true; break;
  case ND_UCOMIGE:  case ND_UCOMISDGE:  cond = "oge"; unordered = true; break;
  default: return gen_ir_default(node, indent);
  }
  (void)unordered;
  const char *l0 = new_reg();
  emit_indent(indent);
  emit("%s = extractelement ", l0);
  emit_type_str(node->lhs->ty);
  emit(" %s, i32 0\n", l);
  const char *r0 = new_reg();
  emit_indent(indent);
  emit("%s = extractelement ", r0);
  emit_type_str(node->lhs->ty);
  emit(" %s, i32 0\n", r);
  const char *cmp = new_reg();
  emit_indent(indent);
  emit("%s = fcmp %s ", cmp, cond);
  emit_type_str(node->lhs->ty->base);
  emit(" %s, %s\n", l0, r0);
  const char *r2 = new_reg();
  emit_indent(indent);
  emit("%s = zext i1 %s to i32\n", r2, cmp);
  return r2;
}

const char *gen_ir_unary_float(Node *node, int indent)
{
  // Unary float conversions and square roots.  CVT* and SQRT*.
  const char *l = emit_expr(node->lhs, indent);
  Type *ty = (node->lhs && node->lhs->ty) ? node->lhs->ty : node->ty;
  Type *dst_ty = node->ty ? node->ty : ty;
  const char *r = NULL;
  if (node->rhs)
    r = emit_expr(node->rhs, indent);

  // --- MMX (64-bit) packed float<->int conversions.  The MMX result is
  //     represented as a plain 64-bit vector (<2 x i32>), so emulate it from
  //     the 128-bit SSE cvt intrinsics (which respect the MXCSR rounding
  //     mode) instead of the x86_mmx MMX intrinsics, avoiding MMX selection
  //     issues.  cvt* round to nearest (MXCSR default); cvtt* truncate.
  switch (node->kind) {
  case ND_CVTPI2PD: {
    const char *ext = new_reg();
    emit_indent(indent);
    emit("%s = shufflevector <2 x i32> %s, <2 x i32> zeroinitializer, <4 x i32> <i32 0, i32 1, i32 2, i32 3>\n", ext, l, l);
    const char *r2 = new_reg();
    emit_indent(indent);
    emit("%s = call <2 x double> @llvm.x86.sse2.cvtdq2pd(<4 x i32> %s)\n", r2, ext);
    return r2;
  }
  case ND_CVTPD2PI: {
    const char *dq = new_reg();
    emit_indent(indent);
    emit("%s = call <4 x i32> @llvm.x86.sse2.cvtpd2dq(<2 x double> %s)\n", dq, l);
    const char *r2 = new_reg();
    emit_indent(indent);
    emit("%s = shufflevector <4 x i32> %s, <4 x i32> zeroinitializer, <2 x i32> <i32 0, i32 1>\n", r2, dq, dq);
    return r2;
  }
  case ND_CVTTPD2PI: {
    const char *dq = new_reg();
    emit_indent(indent);
    emit("%s = call <4 x i32> @llvm.x86.sse2.cvttpd2dq(<2 x double> %s)\n", dq, l);
    const char *r2 = new_reg();
    emit_indent(indent);
    emit("%s = shufflevector <4 x i32> %s, <4 x i32> zeroinitializer, <2 x i32> <i32 0, i32 1>\n", r2, dq, dq);
    return r2;
  }
  case ND_CVTPS2PI: {
    const char *dq = new_reg();
    emit_indent(indent);
    emit("%s = call <4 x i32> @llvm.x86.sse2.cvtps2dq(<4 x float> %s)\n", dq, l);
    const char *r2 = new_reg();
    emit_indent(indent);
    emit("%s = shufflevector <4 x i32> %s, <4 x i32> zeroinitializer, <2 x i32> <i32 0, i32 1>\n", r2, dq, dq);
    return r2;
  }
  case ND_CVTTPS2PI: {
    const char *dq = new_reg();
    emit_indent(indent);
    emit("%s = call <4 x i32> @llvm.x86.sse2.cvttps2dq(<4 x float> %s)\n", dq, l);
    const char *r2 = new_reg();
    emit_indent(indent);
    emit("%s = shufflevector <4 x i32> %s, <4 x i32> zeroinitializer, <2 x i32> <i32 0, i32 1>\n", r2, dq, dq);
    return r2;
  }
  default: break;
  }

  const char *intrinsic = NULL;
  // Conversions: source type comes from lhs, destination from node->ty.
  switch (node->kind)
  {
  case ND_SQRTSS: intrinsic = "llvm.x86.sse.sqrt.ss"; break;
  case ND_SQRTPS: intrinsic = "llvm.x86.sse.sqrt.ps"; break;
  case ND_SQRTPD: intrinsic = "llvm.x86.sse2.sqrt.pd"; break;
  case ND_SQRTSD: intrinsic = "llvm.x86.sse2.sqrt.sd"; break;
  case ND_RCPSS:  intrinsic = "llvm.x86.sse.rcp.ss"; break;
  case ND_RCPPS:  intrinsic = "llvm.x86.sse.rcp.ps"; break;
  case ND_RSQRTSS: intrinsic = "llvm.x86.sse.rsqrt.ss"; break;
  case ND_RSQRTPS: intrinsic = "llvm.x86.sse.rsqrt.ps"; break;
  case ND_ROUNDSS: intrinsic = "llvm.x86.sse41.round.ss"; break;
  case ND_ROUNDPS: intrinsic = "llvm.x86.sse41.round.ps"; break;
  case ND_ROUNDPD: intrinsic = "llvm.x86.sse41.round.pd"; break;
  case ND_ROUNDSD: intrinsic = "llvm.x86.sse41.round.sd"; break;
  case ND_MOVMSKPS: intrinsic = "llvm.x86.sse.movmsk.ps"; break;
  case ND_MOVMSKPD: intrinsic = "llvm.x86.sse2.movmsk.pd"; break;
  case ND_CVTSS2SI: intrinsic = "llvm.x86.sse.cvtss2si"; break;
  case ND_CVTSS2SI64: intrinsic = "llvm.x86.sse.cvtss2si64"; break;
  case ND_CVTTSS2SI: intrinsic = "llvm.x86.sse.cvttss2si"; break;
  case ND_CVTTSS2SI64: intrinsic = "llvm.x86.sse.cvttss2si64"; break;
  case ND_CVTSD2SI: intrinsic = "llvm.x86.sse2.cvtsd2si"; break;
  case ND_CVTSD2SI64: intrinsic = "llvm.x86.sse2.cvtsd2si64"; break;
  case ND_CVTTSD2SI: intrinsic = "llvm.x86.sse2.cvttsd2si"; break;
  case ND_CVTTSD2SI64: intrinsic = "llvm.x86.sse2.cvttsd2si64"; break;
  case ND_CVTSD2SS: intrinsic = "llvm.x86.sse2.cvtsd2ss"; break;
  case ND_CVTSS2SD: intrinsic = "llvm.x86.sse2.cvtss2sd"; break;
  case ND_CVTPD2DQ: intrinsic = "llvm.x86.sse2.cvtpd2dq"; break;
  case ND_CVTTPD2DQ: intrinsic = "llvm.x86.sse2.cvttpd2dq"; break;
  case ND_CVTPS2DQ: intrinsic = "llvm.x86.sse2.cvtps2dq"; break;
  case ND_CVTTPS2DQ: intrinsic = "llvm.x86.sse2.cvttps2dq"; break;
  case ND_CVTDQ2PD: intrinsic = "llvm.x86.sse2.cvtdq2pd"; break;
  case ND_CVTDQ2PS: intrinsic = "llvm.x86.sse2.cvtdq2ps"; break;
  case ND_CVTPD2PS: intrinsic = "llvm.x86.sse2.cvtpd2ps"; break;
  case ND_CVTPS2PD: intrinsic = "llvm.x86.sse2.cvtps2pd"; break;
  case ND_CVTSI2SS: intrinsic = "llvm.x86.sse.cvtsi2ss"; break;
  case ND_CVTSI642SS: intrinsic = "llvm.x86.sse.cvtsi642ss"; break;
  case ND_CVTSI2SD: intrinsic = "llvm.x86.sse2.cvtsi2sd"; break;
  case ND_CVTSI642SD: intrinsic = "llvm.x86.sse2.cvtsi642sd"; break;
  case ND_VECEXTV2SI: case ND_VECEXTV4SI: case ND_VECEXTV4SF:
  case ND_VECEXTV16QI: case ND_VECEXTV8HI: case ND_VECEXTV2DI: case ND_VECEXTV4HI:
    // Skip; not handled here, route elsewhere.
    intrinsic = NULL;
    break;
  default:
    intrinsic = NULL;
    break;
  }
  (void)r;

  if (intrinsic == NULL)
  {
    // For node kinds not represented by an intrinsic, fall through to
    // either a portable float conversion (sitofp/fptosi) or to the
    // default unsupported emitter.
    if (is_flonum(dst_ty) && ty && int_type_bits(ty) > 0)
    {
      const char *r2 = new_reg();
      emit_indent(indent);
      emit("%s = sitofp ", r2);
      emit_type_str(ty);
      emit(" %s to ", l);
      emit_type_str(dst_ty);
      emit("\n");
      return r2;
    }
    if (int_type_bits(dst_ty) > 0 && ty && is_flonum(ty))
    {
      const char *r2 = new_reg();
      emit_indent(indent);
      emit("%s = fptosi ", r2);
      emit_type_str(ty);
      emit(" %s to ", l);
      emit_type_str(dst_ty);
      emit("\n");
      return r2;
    }
    return gen_ir_sse_unsupported(node, indent);
  }

  // ROUNDSS/ROUNDSD have irregular args (builtin_args, not node->lhs/node->rhs)
  // so emit them before the call text begins.
  if (node->kind == ND_ROUNDSS || node->kind == ND_ROUNDSD)
  {
    const char *dst = emit_expr(node->builtin_args[0], indent);
    const char *src = emit_expr(node->builtin_args[1], indent);
    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = call ", res);
    emit_type_str(dst_ty);
    emit(" @%s(", intrinsic);
    emit_type_str(node->builtin_args[0]->ty);
    emit(" %s, ", dst);
    emit_type_str(node->builtin_args[1]->ty);
    emit(" %s, i32 %ld)\n", src, eval(node->builtin_args[2]));
    return res;
  }

  // Insert conversions: scalar-int inserted into the low lane of a vector
  // (cvtsi2ss / cvtsi2sd).  These take two operands: the destination vector
  // and the scalar integer source.
  bool is_insert = (node->kind == ND_CVTSI2SS || node->kind == ND_CVTSI642SS ||
                    node->kind == ND_CVTSI2SD || node->kind == ND_CVTSI642SD);
  // Two-vector conversions (cvtsd2ss / cvtss2sd): low element of the second
  // vector is converted and inserted into the low lane of the first.
  bool is_vec2 = (node->kind == ND_CVTSD2SS || node->kind == ND_CVTSS2SD);

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = call ", res);
  emit_type_str(dst_ty);
  emit(" @%s(", intrinsic);

  if (is_insert || is_vec2)
  {
    emit_type_str(node->lhs->ty);
    emit(" %s, ", l);
    emit_type_str(node->rhs->ty);
    emit(" %s)\n", r);
  }
  else if (node->kind == ND_ROUNDPS || node->kind == ND_ROUNDPD)
  {
    emit_type_str(node->lhs->ty);
    emit(" %s, i32 %ld)\n", l, (long)node->rhs->val);
  }
  else
  {
    emit_type_str(node->lhs->ty);
    emit(" %s)\n", l);
  }
  return res;
}

const char *gen_ir_movmsk(Node *node, int indent)
{
  const char *l = emit_expr(node->lhs, indent);
  Type *ty = node->lhs->ty;
  if (ty->kind != TY_VECTOR)
    return gen_ir_default(node, indent);
  // Use the same intrinsic dispatch as gen_ir_unary_float.
  const char *intrinsic = (ty->base->kind == TY_FLOAT)
                           ? "llvm.x86.sse.movmsk.ps"
                           : "llvm.x86.sse2.movmsk.pd";
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = call i32 @%s(<%d x %s> %s)\n",
       res, intrinsic, ty->array_len,
       ty->base->kind == TY_FLOAT ? "float" : "double", l);
  return res;
}

// __builtin_ia32_pmovmskb[128]: extract the most significant bit of each byte
// of the integer vector into a scalar i32 mask.  LLVM 18 no longer selects the
// @llvm.x86.mmx.pmovmskb intrinsic, so lower it portably: shift each byte right
// by 7 (yielding 0 or 1), zext to i32, shift each lane into its bit position,
// then OR-reduce into a scalar i32.  This matches the x86 pmovmskb convention
// (bit i = MSB of byte lane i) for both the 64-bit (MMX) and 128-bit (SSE2)
// variants.
const char *gen_ir_pmovmskb(Node *node, int indent)
{
  const char *l = emit_expr(node->lhs, indent);
  Type *ty = node->lhs->ty;
  const char *res = new_reg();

  int n = ty->size; // bytes: 8 (MMX) or 16 (SSE2)

  const char *lc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", lc);
  emit_type_str(ty);
  emit(" %s to <%d x i8>\n", l, n);

  const char *shr = new_reg();
  emit_indent(indent);
  emit("%s = lshr <%d x i8> %s, <", shr, n, lc);
  for (int i = 0; i < n; i++) { if (i) emit(", "); emit("i8 7"); }
  emit(">\n");

  const char *ext = new_reg();
  emit_indent(indent);
  emit("%s = zext <%d x i8> %s to <%d x i32>\n", ext, n, shr, n);

  const char *shamt = new_reg();
  emit_indent(indent);
  emit("%s = or <%d x i32> zeroinitializer, <", shamt, n);
  for (int i = 0; i < n; i++) { if (i) emit(", "); emit("i32 %d", i); }
  emit(">\n");

  const char *sh = new_reg();
  emit_indent(indent);
  emit("%s = shl <%d x i32> %s, %s\n", sh, n, ext, shamt);

  emit_indent(indent);
  emit("%s = call i32 @llvm.vector.reduce.or.v%di32(<%d x i32> %s)\n",
       res, n, n, sh);
  return res;
}

// __builtin_ia32_pmovsxXX128 / pmovzxXX128: sign/zero extend the low lanes of
// an integer vector to wider elements.  These lower to the SSE4.1 pmovsx /
// pmovzx intrinsics; the operand is reinterpreted at its natural (narrow)
// element width and the result is bitcast back to the builtin's return type.
const char *gen_ir_pmov_sx_zx(Node *node, int indent)
{
  const char *base = NULL;
  int in_elem = 0, out_elem = 0;
  switch (node->kind)
  {
  case ND_PMOVSXBD128: base = "pmovsx"; in_elem = 8;  out_elem = 32; break;
  case ND_PMOVSXBW128: base = "pmovsx"; in_elem = 8;  out_elem = 16; break;
  case ND_PMOVSXBQ128: base = "pmovsx"; in_elem = 8;  out_elem = 64; break;
  case ND_PMOVSXDQ128: base = "pmovsx"; in_elem = 32; out_elem = 64; break;
  case ND_PMOVSXWD128: base = "pmovsx"; in_elem = 16; out_elem = 32; break;
  case ND_PMOVSXWQ128: base = "pmovsx"; in_elem = 16; out_elem = 64; break;
  case ND_PMOVZXBD128: base = "pmovzx"; in_elem = 8;  out_elem = 32; break;
  case ND_PMOVZXBW128: base = "pmovzx"; in_elem = 8;  out_elem = 16; break;
  case ND_PMOVZXBQ128: base = "pmovzx"; in_elem = 8;  out_elem = 64; break;
  case ND_PMOVZXDQ128: base = "pmovzx"; in_elem = 32; out_elem = 64; break;
  case ND_PMOVZXWD128: base = "pmovzx"; in_elem = 16; out_elem = 32; break;
  case ND_PMOVZXWQ128: base = "pmovzx"; in_elem = 16; out_elem = 64; break;
  default: return gen_ir_sse_unsupported(node, indent);
  }

  const char *letter = (in_elem == 8) ? "b" :
                       (in_elem == 16) ? "w" :
                       (in_elem == 32) ? "d" : "q";
  const char *letter_out = (out_elem == 16) ? "w" :
                           (out_elem == 32) ? "d" : "q";

  const char *l = emit_expr(node->lhs, indent);
  Type *ty = node->lhs->ty;

  int n_in = ty->size * 8 / in_elem;
  int n_out = ty->size * 8 / out_elem;
  if (n_in <= 0) n_in = 1;
  if (n_out <= 0) n_out = 1;

  char in_vt[32];
  snprintf(in_vt, sizeof in_vt, "<%d x i%d>", n_in, in_elem);
  char out_vt[32];
  snprintf(out_vt, sizeof out_vt, "<%d x i%d>", n_out, out_elem);

  const char *lc = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", lc);
  emit_type_str(ty);
  emit(" %s to %s\n", l, in_vt);

  char intr[64];
  snprintf(intr, sizeof intr, "llvm.x86.sse41.%s.%s%s.128",
           base, letter, letter_out);

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = call %s @%s(%s %s)\n", res, out_vt, intr, in_vt, lc);

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, out_vt, res);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

// __builtin_signbit / signbitf / signbitl: extract the top (sign) bit of the
// floating-point value by reinterpreting its bits as an integer and shifting
// the sign bit down to bit 0.  Returns the int 0 (positive/zero) or 1 (negative)
// so it is compatible with the C signbit semantics used by the test suite.
const char *gen_ir_signbit(Node *node, int indent)
{
  const char *v = emit_expr(node->lhs, indent);
  Type *ty = node->lhs->ty;
  const char *bits = new_reg();
  emit_indent(indent);
  switch (ty->kind)
  {
  case TY_FLOAT:
    emit("%s = bitcast float %s to i32\n", bits, v);
    break;
  case TY_DOUBLE:
    emit("%s = bitcast double %s to i64\n", bits, v);
    break;
  case TY_LDOUBLE:
    emit("%s = bitcast x86_fp80 %s to i80\n", bits, v);
    break;
  default:
    error_tok(node->tok,
              "%s:%d: in %s: signbit expects a floating-point operand",
              __FILE__, __LINE__, __func__);
    return NULL;
  }

  int shift = (ty->kind == TY_FLOAT) ? 31 : (ty->kind == TY_DOUBLE) ? 63 : 79;
  const char *shifted = new_reg();
  emit_indent(indent);
  if (ty->kind == TY_FLOAT)
    emit("%s = lshr i32 %s, %d\n", shifted, bits, shift);
  else if (ty->kind == TY_DOUBLE)
    emit("%s = lshr i64 %s, %d\n", shifted, bits, shift);
  else
    emit("%s = lshr i80 %s, %d\n", shifted, bits, shift);

  // The float case already yields i32 (matching the node's int type); only
  // the wider double/long-double results need truncating down to i32.
  if (ty->kind == TY_FLOAT)
    return shifted;

  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = trunc %s %s to i32\n", res,
       ty->kind == TY_DOUBLE ? "i64" : "i80", shifted);
  return res;
}

bool is_pshift_dq(NodeKind k) {
  return k == ND_PSLLDQI128 || k == ND_PSLLDQI256 ||
         k == ND_PSRLDQI128 || k == ND_PSRLDQI256;
}

// Variable-count packed shifts (psllw/pslld/psllq, psraw/psrad,
// psrlw/psrld/psrlq and their 128/256-bit variants).  The hardware reads the
// shift count from the count operand in a way that is NOT a per-element shift,
// so we emit the matching x86 intrinsic (which lowers to the real instruction)
// instead of a generic per-lane shl/lshr/ashr.
const char *gen_ir_pshift_intrinsic(Node *node, int indent)
{
  Type *ty = node->lhs->ty;
  const char *op;
  int elem;
  switch (node->kind) {
  case ND_PSLLW: case ND_PSLLW128: case ND_PSLLWI: case ND_PSLLWI128:
    op = "psll"; elem = 16; break;
  case ND_PSLLD: case ND_PSLLD128: case ND_PSLLDI: case ND_PSLLDI128:
  case ND_PSLLDI256:
    op = "psll"; elem = 32; break;
  case ND_PSLLQ: case ND_PSLLQ128: case ND_PSLLQI: case ND_PSLLQI128:
  case ND_PSLLQI256:
    op = "psll"; elem = 64; break;
  case ND_PSRAW: case ND_PSRAW128: case ND_PSRAWI: case ND_PSRAWI128:
    op = "psra"; elem = 16; break;
  case ND_PSRAD: case ND_PSRAD128: case ND_PSRADI: case ND_PSRADI128:
  case ND_PSRADI256:
    op = "psra"; elem = 32; break;
  case ND_PSRLW: case ND_PSRLW128: case ND_PSRLWI: case ND_PSRLWI128:
    op = "psrl"; elem = 16; break;
  case ND_PSRLD: case ND_PSRLD128: case ND_PSRLDI: case ND_PSRLDI128:
  case ND_PSRLDI256:
    op = "psrl"; elem = 32; break;
  case ND_PSRLQ: case ND_PSRLQ128: case ND_PSRLQI: case ND_PSRLQI128:
  case ND_PSRLQI256:
    op = "psrl"; elem = 64; break;
  default:
    return gen_ir_sse_unsupported(node, indent);
  }

  const char *arch;
  if (ty->size == 8) arch = "mmx";
  else if (ty->size == 16) arch = "sse2";
  else arch = "avx2";

  const char *l = emit_expr(node->lhs, indent);
  const char *r = emit_expr(node->rhs, indent);

  // The MMX (64-bit) intrinsics require x86_mmx operands and the +mmx
  // target feature (enabled for the LLVM backend build).
  const char *lc = l, *rc = r;
  if (ty->size == 8) {
    lc = new_reg();
    emit_indent(indent);
    emit("%s = bitcast ", lc);
    emit_type_str(ty);
    emit(" %s to x86_mmx\n", l);
    rc = new_reg();
    emit_indent(indent);
    emit("%s = bitcast ", rc);
    emit_type_str(node->rhs->ty);
    emit(" %s to x86_mmx\n", r);
  }

  char intrinsic[64];
  snprintf(intrinsic, sizeof(intrinsic), "llvm.x86.%s.%s.%s",
           arch, op, elem == 16 ? "w" : (elem == 32 ? "d" : "q"));

  if (ty->size == 8) {
    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = call x86_mmx @%s(x86_mmx %s, x86_mmx %s)\n",
         res, intrinsic, lc, rc);
    const char *out = new_reg();
    emit_indent(indent);
    emit("%s = bitcast x86_mmx %s to ", out, res);
    emit_type_str(ty);
    emit("\n");
    return out;
  }

  // sse2 / avx2: operands are already in their natural vector shapes and the
  // count operand keeps its own (128-bit for avx2) width.
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = call ", res);
  emit_type_str(ty);
  emit(" @%s(", intrinsic);
  emit_type_str(ty);
  emit(" %s, ", l);
  emit_type_str(node->rhs->ty);
  emit(" %s)\n", r);
  return res;
}

// PSLLDQ/PSRLDQ: shift the whole XMM/YMM register left/right by an immediate
// number of bytes.  Modeled as a byte-granular shuffle over a <N x i8> view of
// the register: concatenate the source with a zero vector and select the
// offset window (zeros fill the lanes shifted in).
const char *gen_ir_pshift_dq(Node *node, int indent)
{
  Type *ty = node->lhs->ty;
  const char *l = emit_expr(node->lhs, indent);

  int total = (int)ty->size;
  if (total <= 0) total = 16;

  // The GCC builtin ABI expresses the immediate count in BITS; convert it to a
  // byte count.  PSLLDQ/PSRLDQ shift each 128-bit lane INDEPENDENTLY, so the
  // 256-bit (AVX2) form is two independent 16-byte shifts, not a single
  // contiguous 32-byte shift.
  int amt = 0;
  if (node->rhs)
    amt = (int)eval(node->rhs) / 8;
  if (amt < 0) amt = 0;
  if (amt > 16) amt = 16;

  char vb[32];
  snprintf(vb, sizeof vb, "<%d x i8>", total);

  const char *src = new_reg();
  emit_indent(indent);
  emit("%s = bitcast ", src);
  emit_type_str(ty);
  emit(" %s to %s\n", l, vb);

  // Shift each 16-byte lane left/right by `amt` bytes: select a byte window
  // from (src, zero) where bytes shifted in come from the zero vector.  Zero
  // bytes are taken from the second shuffle operand (index == total).
  bool left = (node->kind == ND_PSLLDQI128 || node->kind == ND_PSLLDQI256);
  const char *res = new_reg();
  emit_indent(indent);
  emit("%s = shufflevector %s %s, %s zeroinitializer, <%d x i32> <",
       res, vb, src, vb, total);
  for (int i = 0; i < total; i++) {
    if (i) emit(", ");
    int lane_base = (i / 16) * 16;
    int off = i % 16;
    int srcoff = left ? off - amt : off + amt;
    if (srcoff >= 0 && srcoff < 16)
      emit("i32 %d", lane_base + srcoff);
    else
      emit("i32 %d", total);
  }
  emit(">\n");

  const char *out = new_reg();
  emit_indent(indent);
  emit("%s = bitcast %s %s to ", out, vb, res);
  emit_type_str((is_vector(node->ty)) ? node->ty : ty);
  emit("\n");
  return out;
}

const char *gen_ir_psll_imm(Node *node, int indent)
{
  // Packed integer vector shifts with an immediate amount encoded in
  // node->rhs->val (or node->val for some nodes).
  const char *l = emit_expr(node->lhs, indent);
  Type *ty = node->lhs->ty;
  int bits = int_type_bits(ty->base);
  if (bits <= 0) bits = 32;

  // PSLLDQ/PSRLDQ shift the WHOLE 128/256-bit register left/right by an
  // immediate number of BYTES (not per-element bits).  Implement as a
  // byte-granular shuffle: concatenate the source with a zero vector and
  // select the appropriately offset window.
  if (is_pshift_dq(node->kind))
    return gen_ir_pshift_dq(node, indent);

  // __m64 is a single 64-bit MMX value internally represented as a 1-element
  // i64 vector (<1 x i64>), which is not a legal/selectable LLVM type.  Treat
  // the shift as a scalar i64 operation and repack to the canonical __m64
  // shape (<2 x i32>), which is what the public header uses.  Only the
  // <1 x i64> (i64-element) 64-bit vector is MMX; other 8-byte vectors such as
  // <2 x i32> are regular per-lane vector shifts and must not take this path.
  if (ty->size == 8 && ty->base &&
      (ty->base->kind == TY_LONG || ty->base->kind == TY_LLONG)) {
    const char *v = new_reg();
    emit_indent(indent);
    emit("%s = bitcast ", v);
    emit_type_str(ty);
    emit(" %s to i64\n", l);

    const char *cnt;
    if (is_vector(node->rhs->ty)) {
      const char *ec = emit_expr(node->rhs, indent);
      cnt = new_reg();
      emit_indent(indent);
      emit("%s = bitcast ", cnt);
      emit_type_str(node->rhs->ty);
      emit(" %s to i64\n", ec);
    } else {
      cnt = emit_expr(node->rhs, indent);
      if (int_type_bits(node->rhs->ty) < 64) {
        const char *z = new_reg();
        emit_indent(indent);
        emit("%s = zext %s %s to i64\n", z,
             vec_elem_llvm_str(int_type_bits(node->rhs->ty)), cnt);
        cnt = z;
      }
    }

    const char *op;
    switch (node->kind) {
    case ND_PSLLW: case ND_PSLLD: case ND_PSLLQ:
    case ND_PSLLW128: case ND_PSLLD128: case ND_PSLLQ128:
    case ND_PSLLWI: case ND_PSLLDI: case ND_PSLLQI:
    case ND_PSLLWI128: case ND_PSLLDI128: case ND_PSLLQI128:
     case ND_PSLLQI256: case ND_PSLLDI256:
       op = "shl"; break;
     case ND_PSRAW: case ND_PSRAD:
     case ND_PSRAW128: case ND_PSRAD128:
     case ND_PSRAWI: case ND_PSRADI:
     case ND_PSRAWI128: case ND_PSRADI128: case ND_PSRADI256:
       op = ty->base->is_unsigned ? "lshr" : "ashr"; break;
    case ND_PSRLW: case ND_PSRLD: case ND_PSRLQ:
    case ND_PSRLW128: case ND_PSRLD128: case ND_PSRLQ128:
    case ND_PSRLWI: case ND_PSRLDI: case ND_PSRLQI:
    case ND_PSRLWI128: case ND_PSRLDI128: case ND_PSRLQI128:
    case ND_PSRLQI256: case ND_PSRLDI256:
      op = "lshr"; break;
    default:
      return gen_ir_sse_unsupported(node, indent);
    }

    const char *res = new_reg();
    emit_indent(indent);
    emit("%s = %s i64 %s, %s\n", res, op, v, cnt);
    const char *out = new_reg();
    emit_indent(indent);
    emit("%s = bitcast i64 %s to ", out, res);
    emit_type_str(ty);
    emit("\n");
    return out;
  }

  int amt = 0;
  if (node->rhs && node->rhs->kind == ND_NUM)
    amt = (int)node->rhs->val;
  else if (node->rhs)
  {
    // Variable-count element shifts must go through the x86 target
    // intrinsics (the hardware shift count is not per-element).
    if (is_vector(node->rhs->ty) &&
        !is_pshift_dq(node->kind))
      return gen_ir_pshift_intrinsic(node, indent);

    const char *r = emit_expr(node->rhs, indent);
    const char *r_use = r;
    const char *r_ext = NULL;
    if (is_vector(node->rhs->ty))
    {
      // rhs is already a vector; use it directly
      r_use = r;
    }
    else
    {
      // rhs is scalar (i32 from C int): convert to element type, then
      // broadcast to vector via insertelement + shufflevector.
      const char *scaled = r;
      if (bits != 32)
      {
        const char *conv = new_reg();
        emit_indent(indent);
        if (bits < 32)
          emit("%s = trunc i32 %s to i%d\n", conv, r, bits);
        else
          emit("%s = zext i32 %s to i%d\n", conv, r, bits);
        scaled = conv;
      }
      const char *ins = new_reg();
      emit_indent(indent);
      emit("%s = insertelement <%d x i%d> zeroinitializer, i%d %s, i32 0\n",
           ins, ty->array_len, bits, bits, scaled);
      r_ext = new_reg();
      emit_indent(indent);
      emit("%s = shufflevector <%d x i%d> %s, <%d x i%d> undef, <%d x i32> <",
           r_ext, ty->array_len, bits, ins, ty->array_len, bits, ty->array_len);
      for (int i = 0; i < ty->array_len; i++)
      {
        if (i > 0) emit(", ");
        emit("i32 %d", 0);
      }
      emit(">\n");
      r_use = r_ext;
    }
    const char *res = new_reg();
    emit_indent(indent);
    const char *op;
    switch (node->kind)
    {
    case ND_PSLLW: case ND_PSLLD: case ND_PSLLQ:
    case ND_PSLLW128: case ND_PSLLD128: case ND_PSLLQ128:
    case ND_PSLLWI: case ND_PSLLDI: case ND_PSLLQI:
    case ND_PSLLWI128: case ND_PSLLDI128: case ND_PSLLQI128:
    case ND_PSLLQI256: case ND_PSLLDI256:
       op = "shl";  break;
     case ND_PSRAW: case ND_PSRAD:
     case ND_PSRAW128: case ND_PSRAD128:
     case ND_PSRAWI: case ND_PSRADI:
     case ND_PSRAWI128: case ND_PSRADI128: case ND_PSRADI256:
       op = ty->base->is_unsigned ? "lshr" : "ashr"; break;
    case ND_PSRLW: case ND_PSRLD: case ND_PSRLQ:
    case ND_PSRLW128: case ND_PSRLD128: case ND_PSRLQ128:
    case ND_PSRLWI: case ND_PSRLDI: case ND_PSRLQI:
    case ND_PSRLWI128: case ND_PSRLDI128: case ND_PSRLQI128:
    case ND_PSRLQI256: case ND_PSRLDI256:
      op = "lshr"; break;
    default:
      return gen_ir_sse_unsupported(node, indent);
    }
    emit("%s = %s <%d x i%d> %s, %s\n",
         res, op, ty->array_len, bits, l, r_use);
    return res;
  }
  const char *r2 = new_reg();
  emit_indent(indent);
  const char *op;
  switch (node->kind)
  {
    case ND_PSLLW: case ND_PSLLD: case ND_PSLLQ:
    case ND_PSLLW128: case ND_PSLLD128: case ND_PSLLQ128:
    case ND_PSLLWI: case ND_PSLLDI: case ND_PSLLQI:
    case ND_PSLLWI128: case ND_PSLLDI128: case ND_PSLLQI128:
    case ND_PSLLQI256: case ND_PSLLDI256:
    op = "shl"; break;
  case ND_PSRAW: case ND_PSRAD:
  case ND_PSRAW128: case ND_PSRAD128:
  case ND_PSRAWI: case ND_PSRADI:
  case ND_PSRAWI128: case ND_PSRADI128: case ND_PSRADI256:
    op = ty->base->is_unsigned ? "lshr" : "ashr"; break;
    case ND_PSRLW: case ND_PSRLD: case ND_PSRLQ:
    case ND_PSRLW128: case ND_PSRLD128: case ND_PSRLQ128:
    case ND_PSRLWI: case ND_PSRLDI: case ND_PSRLQI:
    case ND_PSRLWI128: case ND_PSRLDI128: case ND_PSRLQI128:
    case ND_PSRLQI256: case ND_PSRLDI256:
    op = "lshr"; break;
  default:
    return gen_ir_sse_unsupported(node, indent);
  }
  emit("%s = %s <%d x i%d> %s, <", r2, op, ty->array_len, bits, l);
  for (int i = 0; i < ty->array_len; i++)
  {
    if (i > 0) emit(", ");
    emit("i%d %d", bits, amt);
  }
  emit(">\n");
  return r2;
}

const char *gen_ir_sse_unsupported(Node *node, int indent)
{
  return gen_ir_default(node, indent);
}

const char *gen_ir_default(Node *node, int indent)
{
  emit_indent(indent);
  emit("; UNSUPPORTED: node kind %d\n", node->kind);
  if (node->ty->kind == TY_VOID)
    return NULL;
  const char *r = new_reg();
  emit_indent(indent);
  if (is_pointer(node->ty) || is_array(node->ty) ||
      node->ty->kind == TY_FUNC || 
      node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION)
  {
    emit("%s = inttoptr i32 0 to ", r);
    emit_type_str(node->ty);
    emit("\n");
  }
  else if (is_vector(node->ty))
  {
    Type *elem = node->ty->base;
    if (elem->kind == TY_FLOAT || elem->kind == TY_DOUBLE || elem->kind == TY_LDOUBLE)
      emit("%s = fadd ", r);
    else
      emit("%s = add ", r);
    emit_type_str(node->ty);
    emit(" zeroinitializer, zeroinitializer\n");
  }
  else
  {
    emit("%s = %s ", r, is_flonum(node->ty) ? "fadd" : "add");
    emit_type_str(node->ty);
    if (is_flonum(node->ty))
      emit(" 0.0, 0.0");
    else
      emit(" 0, 0");
    emit("\n");
  }
  return r;
}


void gen_ir_stmt_block(Node *node, int indent, bool *terminated)
{
  for (Node *n = node->body; n; n = n->next)
  {
    // Once the current block is terminated (by a noreturn call that emitted
    // `unreachable`, or by return/goto/break/continue), every following
    // statement is unreachable.  Skip it unless it defines a label (or
    // contains one transitively) -- such a label is still a potential
    // branch target and must be emitted (emit_label resets the terminated
    // state and starts a fresh block).  Note: dead code that appears *inside*
    // the same statement (e.g. the store of `tab[i] = (abort(), x)`) is
    // handled by emit(), which swallows output while the block is
    // terminated.
    if (is_terminated && !contains_label(n))
      continue;
    emit_stmt(n, indent, terminated);
  }
  return;
}

void gen_ir_stmt_return(Node *node, int indent, bool *terminated)
{
  if (node->lhs)
  {
    const char *val = emit_expr(node->lhs, indent);
    emit_indent(indent);
    if (sret_reg)
    {
      emit_indent(indent);
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
      // When the function returns an integer type but the expression
      // produced a pointer (e.g. returning 0 cast to a pointer type in a
      // function declared to return int), emit a ptrtoint to coerce the
      // pointer value back to the required integer width.
      int rty_bits = int_type_bits(rty);
      bool expr_is_ptr = expr_ty &&
                         (is_pointer(expr_ty) || is_array(expr_ty) ||
                          expr_ty->kind == TY_FUNC);
      if (rty_bits > 0 && expr_is_ptr)
      {
        const char *coerced = new_reg();
        emit_indent(indent);
        emit("%s = ptrtoint ptr %s to i%d\n", coerced, val, rty_bits);
        val = coerced;
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

void gen_ir_stmt_expr_stmt(Node *node, int indent, bool *terminated)
{
  emit_expr(node->lhs, indent);
  return;
}

void gen_ir_stmt_null_expr(Node *node, int indent, bool *terminated)
{
  return;
}

void gen_ir_stmt_if(Node *node, int indent, bool *terminated)
{
{
  const char *cond_val = emit_expr(node->cond, indent);
  const char *cond_bool = emit_to_bool(cond_val, node->cond->ty, indent);
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

void gen_ir_stmt_label(Node *node, int indent, bool *terminated)
{
  emit_label(node->unique_label);
  // A label starts a fresh, unterminated block.  If a preceding statement
  // (e.g. an early `return;`) left *terminated true, reset it so the
  // following block is treated as open; otherwise the function epilogue
  // would skip emitting its terminator (e.g. `ret void`), leaving an
  // invalid block that llc rejects with "expected instruction opcode".
  if (terminated)
    *terminated = false;
  if (node->lhs)
    emit_stmt(node->lhs, indent, terminated);
  return;
}

void gen_ir_stmt_goto(Node *node, int indent, bool *terminated)
{
  emit_indent(indent);
  emit("br label %%%s\n", node->unique_label);
  is_terminated = true;
  if (terminated)
    *terminated = true;
  return;
}

void gen_ir_stmt_for(Node *node, int indent, bool *terminated)
{

  const char *begin_label = format(".L.begin.%d", ir_reg++);
  const char *body_label = format(".L.body.%d", ir_reg++);
  if (node->init)
    emit_stmt(node->init, indent, NULL);
  emit_label(begin_label);
  if (node->cond)
  {
    const char *cond_val = emit_expr(node->cond, indent);
    const char *cond_bool = emit_to_bool(cond_val, node->cond->ty, indent);
    emit_indent(indent);
    emit("br i1 %s, label %%%s, label %%%s\n", cond_bool, body_label, node->brk_label);
    is_terminated = true;
  }
  else
  {
    emit_indent(indent);
    emit("br label %%%s\n", body_label);
    is_terminated = true;
  }
  emit_label(body_label);
  emit_stmt(node->then, indent, NULL);
  if (!is_terminated)
  {
    emit_indent(indent);
    emit("br label %%%s\n", node->cont_label);
    is_terminated = true;
  }
  emit_label(node->cont_label);
  if (node->inc)
    emit_expr(node->inc, indent);
  emit_indent(indent);
  emit("br label %%%s\n", begin_label);
  is_terminated = true;
  emit_label(node->brk_label);
  return;
}


void gen_ir_stmt_do(Node *node, int indent, bool *terminated)
{

  const char *begin_label = format(".L.begin.%d", ir_reg++);
  emit_label(begin_label);
  emit_stmt(node->then, indent, NULL);
  if (!is_terminated)
  {
    emit_indent(indent);
    emit("br label %%%s\n", node->cont_label);
    is_terminated = true;
  }
  emit_label(node->cont_label);
  {
    const char *cond_val = emit_expr(node->cond, indent);
    const char *cond_bool = emit_to_bool(cond_val, node->cond->ty, indent);
    emit_indent(indent);
    emit("br i1 %s, label %%%s, label %%%s\n", cond_bool, begin_label, node->brk_label);
    is_terminated = true;
  }
  emit_label(node->brk_label);
  return;
}


void gen_ir_stmt_switch(Node *node, int indent, bool *terminated)
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


void gen_ir_stmt_case(Node *node, int indent, bool *terminated)
{
  emit_label(node->label);
  if (node->lhs)
    emit_stmt(node->lhs, indent, terminated);
  return;
}

char *escape_ir_asm(const char *s)
{
  int len = strlen(s);
  int cnt = 0;
  for (int i = 0; s[i]; i++)
    if (s[i] == '$')
      cnt++;
  if (cnt == 0)
    return (char *)s;
  char *buf = calloc(1, len + cnt + 1);
  int j = 0;
  for (int i = 0; s[i]; i++) {
    if (s[i] == '$')
      buf[j++] = '$';
    buf[j++] = s[i];
  }
  buf[j] = '\0';
  return buf;
}

void gen_ir_stmt_goto_expr(Node *node, int indent, bool *terminated)
{
  const char *addr = emit_expr(node->lhs, indent);
  const char *ptr = addr;
  if (node->lhs->ty->kind != TY_PTR) {
    ptr = new_reg();
    emit_indent(indent);
    emit("%s = inttoptr i64 %s to ptr\n", ptr, addr);
  }
  emit_indent(indent);
  emit("indirectbr ptr %s, [", ptr);
  for (int i = 0; i < label_addr_count; i++)
    emit("%s label %%%s", i ? "," : "", label_addr_list[i]);
  emit(" ]\n");
  is_terminated = true;
  if (terminated) *terminated = true;
}

// Convert GCC asm template to LLVM IR format:
//   %N  -> $N      (operand references)
//   %%  -> %        (literal percent)
//   %=  -> <unique> (unique number)
//   %[name] -> $N   (named operand -> operand index)
char *convert_asm_template(const char *tmpl, int noutputs,
                                   AsmOperand *outputs, AsmOperand *inputs,
                                   int ninputs)
{
  // Build a name -> index mapping for named operands
  // Maximum 20 operands (10+10), reasonable limit
  struct { char *name; int idx; } named[20];
  int nnamed = 0;

  for (int i = 0; i < noutputs; i++) {
    if (outputs[i].name)
      { named[nnamed].name = outputs[i].name; named[nnamed].idx = i; nnamed++; }
  }
  for (int i = 0; i < ninputs; i++) {
    if (inputs[i].name)
      { named[nnamed].name = inputs[i].name; named[nnamed].idx = noutputs + i; nnamed++; }
  }

  int len = strlen(tmpl);
  // Result buffer, generously sized
  char *res = calloc(1, len * 2 + 256);
  if (!res)
    error("%s:%d: error: in %s: out of memory", __FILE__, __LINE__, __func__);

  // Pre-pass: flatten Clang dialect alternatives {att|intel} -> att.
  // AVX masking like {%k1} (no '|') is preserved verbatim.
  char *flat = calloc(1, len * 2 + 256);
  if (!flat)
    error("%s:%d: error: in %s: out of memory", __FILE__, __LINE__, __func__);
  {
    int f = 0;
    for (int i = 0; tmpl[i]; ) {
      if (tmpl[i] == '{') {
        int bar = -1, end = i + 1;
        while (tmpl[end] && tmpl[end] != '}') {
          if (tmpl[end] == '|' && bar < 0) bar = end;
          end++;
        }
        if (bar >= 0 && tmpl[end] == '}') {
          // dialect: keep the AT&T side (before '|')
          for (int m = i + 1; m < bar; m++) flat[f++] = tmpl[m];
          i = end + 1; // skip past '}'
        } else if (tmpl[end] == '}') {
          // AVX masking {%k1}: keep the '{' and continue normally
          flat[f++] = '{';
          i++;
        } else {
          // stray '{' with no closing '}': drop it
          i++;
        }
      } else {
        flat[f++] = tmpl[i];
        i++;
      }
    }
    flat[f] = '\0';
    tmpl = flat;
  }

  int j = 0;
  for (int i = 0; tmpl[i]; i++) {
    if (tmpl[i] == '%' && tmpl[i + 1] == '%') {
      // %% -> %
      res[j++] = '%';
      i++;
    } else if (tmpl[i] == '%' && tmpl[i + 1] == '=') {
      // %= -> unique number
      static int unique_id = 0;
      j += snprintf(res + j, 100, "%d", unique_id++);
      i++;
    } else if (tmpl[i] == '%' && tmpl[i + 1] == '[') {
      // %[name] -> $N
      char close = ']';
      int start = i + 2;
      int end = start;
      while (tmpl[end] && tmpl[end] != close) end++;
      if (tmpl[end] != close)
        error("%s:%d: in %s: unterminated %%[name] in asm template", __FILE__, __LINE__, __func__);
      int nlen = end - start;
      int found = -1;
      for (int k = 0; k < nnamed; k++) {
        if ((int)strlen(named[k].name) == nlen &&
            !strncmp(named[k].name, tmpl + start, nlen)) {
          found = named[k].idx;
          break;
        }
      }
      if (found < 0)
        error("%s:%d: in %s: unknown named operand %.*s in asm template",
              __FILE__, __LINE__, __func__, nlen, tmpl + start);
      j += snprintf(res + j, 50, "$%d", found);
      i = end; // skip past ]
    } else if (tmpl[i] == '%' && (isalpha((unsigned char)tmpl[i+1]) || tmpl[i+1] == '*')) {
      // %N (operand) possibly with GCC size modifiers (b,h,w,k,q,l,...).
      // GCC: %b1  -> byte version of operand 1.  LLVM: $1b (modifier after number).
      const char *mods = "bhwkqlcnpeLHatxyz";
      int k = i + 1;
      int mstart = k;
      while (tmpl[k] && strchr(mods, tmpl[k])) k++;
      int mlen = k - mstart;  // length of modifier letters (before digits)
      if (tmpl[k] >= '0' && tmpl[k] <= '9') {
        int n = 0;
        while (tmpl[k] >= '0' && tmpl[k] <= '9')
          n = n * 10 + (tmpl[k++] - '0');
        // LLVM uses ${N:mod} for operand modifiers (e.g. ${1:b}).
        j += snprintf(res + j, 64, "${%d:", n);
        for (int m = 0; m < mlen; m++) res[j++] = tmpl[mstart + m];
        res[j++] = '}';
        i = k - 1;
      } else {
        // Not an operand with modifiers: copy the '%' and let the
        // following register name be copied verbatim (e.g. %fs, %eax).
        res[j++] = '%';
      }
    } else if (tmpl[i] == '%' && tmpl[i + 1] >= '0' && tmpl[i + 1] <= '9') {
      // %N -> $N
      int n = 0;
      while (tmpl[i + 1] >= '0' && tmpl[i + 1] <= '9')
        n = n * 10 + (tmpl[++i] - '0');
      j += snprintf(res + j, 50, "$%d", n);
    } else if (tmpl[i] == '{') {
      // Dialect alternative: {att|intel}. Select the AT&T side and strip
      // the {, |, } characters.  AVX masking like {%k1} has no '|', so keep
      // it verbatim.
      int end = i + 1;
      int bar = -1;
      while (tmpl[end] && tmpl[end] != '}') {
        if (tmpl[end] == '|' && bar < 0) bar = end;
        end++;
      }
      if (bar >= 0 && tmpl[end] == '}') {
        // dialect: copy AT&T part (between '{' and '|'), skip to after '}'
        for (int m = i + 1; m < bar; m++) res[j++] = tmpl[m];
        i = end; // skip '}'
      } else {
        // No '|': keep the '{' and continue verbatim (AVX mask, or a stray
        // '{' which we drop).
        if (tmpl[end] == '}') {
          res[j++] = '{'; // keep, let normal loop handle the rest
        } else {
          i++; // drop the stray '{'
        }
      }
    } else if (tmpl[i] == '$') {
      // LLVM uses $ for operand refs; a literal $ must be $$
      res[j++] = '$';
      res[j++] = '$';
    } else {
      res[j++] = tmpl[i];
    }
  }
  res[j] = '\0';
  free(flat);
  return res;
}

// Map a single GCC x86 register constraint letter to its LLVM brace form,
// or NULL if `c` is not one of a/b/c/d/S/D.
static const char *llvm_x86_reg_char(char c) {
  switch (c) {
  case 'a': return "{ax}";
  case 'b': return "{bx}";
  case 'c': return "{cx}";
  case 'd': return "{dx}";
  case 'S': return "{si}";
  case 'D': return "{di}";
  }
  return NULL;
}

// Convert a full GCC x86 inline-asm constraint string into the LLVM form.
// Each register letter (a/b/c/d/S/D) is rewritten to its brace form so that
// LLVM can allocate it; other constraint letters (e.g. N, i, m, r) are kept
// verbatim.  Multi-letter alternative constraints such as "dN" become
// "{dx}N", which lets LLVM pick the immediate 'N' alternative when a constant
// is supplied and the explicit {dx} register otherwise.  Output/mode prefixes
// ('=', '+', '&') are skipped; the caller is responsible for re-adding them.
void llvm_x86_constraint(const char *c, char *out, size_t sz) {
  while (*c == '=' || *c == '+' || *c == '&') c++;
  int pos = 0;
  for (; *c && pos < (int)sz - 1; c++) {
    const char *reg = llvm_x86_reg_char(*c);
    if (reg)
      pos += snprintf(out + pos, sz - pos, "%s", reg);
    else
      out[pos++] = *c;
  }
  out[pos] = '\0';
}

// Map a chibicc Type to an LLVM IR type string for inline asm operands.
void asm_llvm_ty(Type *ty, char *buf, size_t sz) {
  switch (ty->kind) {
    case TY_VOID:   snprintf(buf, sz, "void"); break;
    case TY_CHAR:   snprintf(buf, sz, "i8"); break;
    case TY_SHORT:  snprintf(buf, sz, "i16"); break;
    case TY_INT:    snprintf(buf, sz, "i%d", (int)(ty->size * 8)); break;
    case TY_LONG:
    case TY_LLONG:  snprintf(buf, sz, "i64"); break;
    case TY_FLOAT:  snprintf(buf, sz, "float"); break;
    case TY_DOUBLE: snprintf(buf, sz, "double"); break;
    case TY_PTR:
    case TY_FUNC:   snprintf(buf, sz, "ptr"); break;
    case TY_BOOL:   snprintf(buf, sz, "i8"); break;
    case TY_ENUM:   snprintf(buf, sz, "i%d", (int)(ty->size * 8)); break;
    default:        snprintf(buf, sz, "i%d", (int)(ty->size * 8)); break;
  }
}

void gen_ir_stmt_asm(Node *node, int indent, bool *terminated)
{
  // Old path: flat x86 string (from extended_asm.c)
  if (node->asm_str) {
    char *s = subst_fp_placeholder(node->asm_str, "%rbp");
    s = escape_ir_asm(s);
    emit_indent(indent);
    emit("call void asm sideeffect \"%s\", \"\"()\n", s);
    return;
  }

  int nout = node->asm_noutputs;
  int nin = node->asm_ninputs;
  int nclob = node->asm_nclobbers;

  // --- 1. Convert template ---
  char *template = convert_asm_template(node->asm_template,
                                         nout,
                                         node->asm_outputs,
                                         node->asm_inputs,
                                         nin);

  // --- 2. Classify operands ---
  // For each output i:
  //   is_mem[i]    : memory operand (constraint contains 'm')
  //   is_rw[i]     : read-write ('+' prefix)
  //   reg_idx[i]   : index in the struct return, or -1 if memory
  bool *is_mem = calloc(nout + nin, 1);
  bool *is_rw  = calloc(nout, 1);
  if (!is_mem || !is_rw)
    error("%s:%d: in %s: out of memory", __FILE__, __LINE__, __func__);

  for (int i = 0; i < nout; i++) {
    const char *c = node->asm_outputs[i].constraint;
    if (strchr(c, 'm')) is_mem[i] = true;
    if (c[0] == '+') is_rw[i] = true;
  }
  for (int i = 0; i < nin; i++) {
    const char *c = node->asm_inputs[i].constraint;
    if (strchr(c, 'm')) is_mem[nout + i] = true;
  }

  // --- 3. Build constraint string and argument list together ---
  // Operand order: [outputs] [regular inputs] [read-write read-parts]
  char constraints[4096];
  constraints[0] = '\0';
  int cpos = 0;

  typedef struct {
    char type[32];
    const char *reg;
    bool has_elem;
    char elem[32];
  } AsmArg;
  AsmArg args[40];
  int nargs = 0;

  // Outputs
  for (int i = 0; i < nout; i++) {
    const char *c = node->asm_outputs[i].constraint;
    char llvm_c[72];
    if (is_mem[i]) {
      // Memory output: "=*m" (covers both =m and =*m, and +m/+*m)
      if (c[0] == '&' || (c[0] == '+' && c[1] == '&'))
        snprintf(llvm_c, sizeof(llvm_c), "=&*m");
      else
        snprintf(llvm_c, sizeof(llvm_c), "=*m");
    } else {
      int earlyclob = (c[0] == '&' || (c[0] == '+' && c[1] == '&')) ? 1 : 0;
      char regstr[64];
      llvm_x86_constraint(c, regstr, sizeof(regstr));
      snprintf(llvm_c, sizeof(llvm_c), "%s%s", earlyclob ? "=&" : "=", regstr);
    }
    cpos += snprintf(constraints + cpos, sizeof(constraints) - cpos, "%s,", llvm_c);

    if (is_mem[i]) {
      // Memory output: pass pointer; elementtype is the accessed type.
      const char *p = (c[1] == '*') ? emit_expr(node->asm_outputs[i].expr, indent)
                                     : emit_lval_ptr(node->asm_outputs[i].expr, indent);
      char et[32];
      asm_llvm_ty(node->asm_outputs[i].expr->ty, et, sizeof(et));
      strcpy(args[nargs].type, "ptr");
      args[nargs].reg = p;
      args[nargs].has_elem = true;
      strcpy(args[nargs].elem, et);
      nargs++;
    }
  }

  // Regular inputs
  for (int i = 0; i < nin; i++) {
    const char *c = node->asm_inputs[i].constraint;
    char llvm_c[64];
    if (c[0] >= '0' && c[0] <= '9' && c[1] == '\0') {
      // matching constraint (e.g. "0")
      snprintf(llvm_c, sizeof(llvm_c), "%s", c);
    } else if (is_mem[nout + i]) {
      snprintf(llvm_c, sizeof(llvm_c), "*m");
    } else if (strcmp(c, "g") == 0) {
      // general-purpose: immediate | memory | register
      snprintf(llvm_c, sizeof(llvm_c), "imr");
    } else if (strcmp(c, "i") == 0) {
      // immediate
      snprintf(llvm_c, sizeof(llvm_c), "i");
    } else {
      char regstr[64];
      llvm_x86_constraint(c, regstr, sizeof(regstr));
      snprintf(llvm_c, sizeof(llvm_c), "%s", regstr);
    }
    cpos += snprintf(constraints + cpos, sizeof(constraints) - cpos, "%s,", llvm_c);

    if (is_mem[nout + i]) {
      const char *p = (c[0] == '*') ? emit_expr(node->asm_inputs[i].expr, indent)
                                     : emit_lval_ptr(node->asm_inputs[i].expr, indent);
      char et[32];
      asm_llvm_ty(node->asm_inputs[i].expr->ty, et, sizeof(et));
      strcpy(args[nargs].type, "ptr");
      args[nargs].reg = p;
      args[nargs].has_elem = true;
      strcpy(args[nargs].elem, et);
      nargs++;
    } else {
      const char *v = emit_expr(node->asm_inputs[i].expr, indent);
      char t[32];
      asm_llvm_ty(node->asm_inputs[i].expr->ty, t, sizeof(t));
      strcpy(args[nargs].type, t);
      args[nargs].reg = v;
      args[nargs].has_elem = false;
      nargs++;
    }
  }

  // Read-write read-parts (in output order)
  for (int i = 0; i < nout; i++) {
    if (!is_rw[i]) continue;
    if (is_mem[i]) {
      // Memory read-write: re-reference the same memory as "*m"
      cpos += snprintf(constraints + cpos, sizeof(constraints) - cpos, "*m,");
      const char *p = (node->asm_outputs[i].constraint[1] == '*')
                           ? emit_expr(node->asm_outputs[i].expr, indent)
                           : emit_lval_ptr(node->asm_outputs[i].expr, indent);
      char et[32];
      asm_llvm_ty(node->asm_outputs[i].expr->ty, et, sizeof(et));
      strcpy(args[nargs].type, "ptr");
      args[nargs].reg = p;
      args[nargs].has_elem = true;
      strcpy(args[nargs].elem, et);
      nargs++;
    } else {
      // Register read-write: matching constraint tied to output i
      cpos += snprintf(constraints + cpos, sizeof(constraints) - cpos, "%d,", i);
      const char *v = emit_expr(node->asm_outputs[i].expr, indent);
      char t[32];
      asm_llvm_ty(node->asm_outputs[i].expr->ty, t, sizeof(t));
      strcpy(args[nargs].type, t);
      args[nargs].reg = v;
      args[nargs].has_elem = false;
      nargs++;
    }
  }

  // Clobbers
  for (int i = 0; i < nclob; i++) {
    const char *cl = node->asm_clobbers[i];
    // Register clobbers are stored with a leading '%' (e.g. "%ebx") to match
    // GCC syntax. LLVM expects a single-braced name without the '%', so strip
    // it. Special clobbers "memory"/"cc" are modeled by the 'sideeffect'
    // attribute already, so they are not emitted as register clobbers.
    if (cl[0] == '%')
      cl++;
    if (strcmp(cl, "memory") == 0 || strcmp(cl, "cc") == 0)
      continue;
    cpos += snprintf(constraints + cpos, sizeof(constraints) - cpos,
                     "~{%s},", cl);
  }
  if (cpos > 0) constraints[cpos - 1] = '\0';

  // --- 4. Build argument string ---
  char arg_str[4096];
  int apos = 0;
  for (int i = 0; i < nargs; i++) {
    if (args[i].has_elem)
      apos += snprintf(arg_str + apos, sizeof(arg_str) - apos,
                       "%s elementtype(%s) %s, ", args[i].type, args[i].elem, args[i].reg);
    else
      apos += snprintf(arg_str + apos, sizeof(arg_str) - apos,
                       "%s %s, ", args[i].type, args[i].reg);
  }
  if (apos > 2) arg_str[apos - 2] = '\0';
  else arg_str[0] = '\0';

  // --- 5. Count register outputs and build return type ---
  int nreg = 0;
  int reg_idx[20];
  for (int i = 0; i < nout; i++) {
    if (!is_mem[i]) reg_idx[i] = nreg++;
    else reg_idx[i] = -1;
  }

  char rettype[256];
  if (nreg == 0) {
    strcpy(rettype, "void");
  } else if (nreg == 1) {
    for (int i = 0; i < nout; i++) {
      if (!is_mem[i]) {
        asm_llvm_ty(node->asm_outputs[i].expr->ty, rettype, sizeof(rettype));
        break;
      }
    }
  } else {
    char buf[256] = "{ ";
    int bpos = 2;
    for (int i = 0; i < nout; i++) {
      if (!is_mem[i]) {
        char ts[32];
        asm_llvm_ty(node->asm_outputs[i].expr->ty, ts, sizeof(ts));
        bpos += snprintf(buf + bpos, sizeof(buf) - bpos, "%s, ", ts);
      }
    }
    if (bpos > 2) {
      buf[bpos - 2] = ' ';
      buf[bpos - 1] = '}';
      buf[bpos] = '\0';
    }
    snprintf(rettype, sizeof(rettype), "%s", buf);
  }

  // --- 6. Emit the call ---
  const char *vol = node->asm_is_volatile ? " sideeffect" : "";
  const char *call_result_reg = NULL;
  if (nreg > 0)
    call_result_reg = new_reg();

  emit_indent(indent);
  if (call_result_reg) {
    emit("%s = call %s asm%s \"%s\", \"%s\"(%s)\n",
         call_result_reg, rettype, vol, template, constraints, arg_str);
  } else {
    emit("call %s asm%s \"%s\", \"%s\"(%s)\n",
         rettype, vol, template, constraints, arg_str);
  }

  // --- 7. Store register outputs back ---
  if (nreg == 1) {
    for (int i = 0; i < nout; i++) {
      if (!is_mem[i]) {
        const char *addr = emit_lval_ptr(node->asm_outputs[i].expr, indent);
        emit_indent(indent);
        emit("store %s %s, ptr %s\n", rettype, call_result_reg, addr);
        break;
      }
    }
  } else if (nreg > 1) {
    for (int i = 0; i < nout; i++) {
      if (is_mem[i]) continue;
      char ts[32];
      asm_llvm_ty(node->asm_outputs[i].expr->ty, ts, sizeof(ts));
      const char *ext = new_reg();
      emit_indent(indent);
      emit("%s = extractvalue %s %s, %d\n",
           ext, rettype, call_result_reg, reg_idx[i]);
      const char *addr = emit_lval_ptr(node->asm_outputs[i].expr, indent);
      emit_indent(indent);
      emit("store %s %s, ptr %s\n", ts, ext, addr);
    }
  }

  free(is_mem);
  free(is_rw);
  free(template);
  return;
}


void gen_ir_stmt_default(Node *node, int indent, bool *terminated)
{
  emit_indent(indent);
  emit("; UNSUPPORTED stmt: node kind %d\n", node->kind);
  return;
}


void emit_stmt(Node *node, int indent, bool *terminated)
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
  case ND_GOTO_EXPR:
    gen_ir_stmt_goto_expr(node, indent, terminated);
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

// Like codegen.c's get_align, but also guarantees a 16-byte alignment for
// large local arrays/structs/unions so that address calculations relying on
// natural 16-byte stack alignment behave identically to the x86 backend.
static int ir_get_align(Obj *var)
{
  int align = var->align > 0 ? var->align : 1;
  if (is_vector(var->ty) || var->ty->kind == TY_INT128 ||
      ((var->ty->kind == TY_ARRAY || var->ty->kind == TY_STRUCT ||
        var->ty->kind == TY_UNION) && var->ty->size >= 16))
    align = align > 16 ? align : 16;
  return align;
}

// Aggregates (struct/union/array) and function parameters are represented as
// a `ptr` value in the LLVM IR (see emit_type_str), so the parameter slot must
// be large enough to hold the pointer (8 bytes, 8-byte aligned), not the
// aggregate itself.  Otherwise the 8-byte `store ptr` overflows the slot and
// corrupts adjacent parameters on the stack.
static long ir_param_slot_size(Type *ty)
{
  if (ty->kind == TY_ARRAY || ty->kind == TY_FUNC || ty->kind == TY_VLA)
    return 8;
  if (ty->kind == TY_STRUCT || ty->kind == TY_UNION)
  {
    // Struct/union parameters are copied by value into their slot (see the
    // memcpy in emit_func), so the slot must hold the whole aggregate, not
    // just a pointer to it.
    return ty->size > 0 ? ty->size : 1;
  }
  return ty->size;
}

static int ir_param_slot_align(Type *ty)
{
  if (ty->kind == TY_ARRAY || ty->kind == TY_FUNC || ty->kind == TY_VLA)
  {
    // The slot holds a pointer (8-byte minimum alignment).
    return 8;
  }
  if (ty->kind == TY_STRUCT || ty->kind == TY_UNION)
  {
    // The slot holds the aggregate itself, so it must be aligned to the
    // aggregate's declared/natural alignment so that the address of a
    // by-value struct parameter (`&param`) keeps its alignment
    // (e.g. aligned(16)/aligned(4096) parameters).
    return ir_align_of(ty);
  }
  int align = ty->align > 0 ? ty->align : 1;
  if (ty->size >= 16)
    align = align > 16 ? align : 16;
  return align;
}

// Alignment of a type, used for the `byval` attribute on variadic calls where
// over-aligned aggregates (e.g. `_Alignas(32)`) must keep their alignment so
// the callee's va_arg can locate them on the stack.
static int ir_type_align(Type *ty)
{
  int align = ty->align > 0 ? ty->align : 1;
  if (ty->kind == TY_STRUCT || ty->kind == TY_UNION || ty->kind == TY_ARRAY)
  {
    if (align < 8)
      align = 8;
  }
  return align;
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
     if (var->ty->kind == TY_VLA)
     {
        emit("%s = alloca i8, i64 8, align %d\n", var_ptr(var), ir_get_align(var));
      }
     else
        emit("%s = alloca i8, i64 %ld, align %d\n", var_ptr(var), var->ty->size, ir_get_align(var));
    }
}

// Write a buffered function body to the real output, appending ", !dbg !<loc>"
// to every call instruction so the module satisfies the LLVM verifier's
// requirement that inlinable calls in a function with debug info carry a debug
// location.  A "logical line" is a full instruction: newlines that appear
// inside a "..." string literal (e.g. a multi-line inline-asm template) do not
// terminate it, so the !dbg suffix is only ever appended after the complete
// instruction and never in the middle of an asm string.
static void ir_dbg_flush_func(const char *buf, int locid)
{
  const char *line_start = buf;
  const char *p = buf;
  bool in_str = false;
  bool has_call = false;
  while (*p)
  {
    char c = *p;
    if (in_str)
    {
      if (c == '\\' && p[1])
      {
        p += 2;
        continue;
      }
      if (c == '"')
        in_str = false;
      p++;
      continue;
    }
    if (c == '"')
    {
      in_str = true;
      p++;
      continue;
    }
    if (c == '\n')
    {
      fwrite(line_start, 1, (size_t)(p - line_start), output_file);
      if (has_call)
        fprintf(output_file, ", !dbg !%d", locid);
      fputc('\n', output_file);
      p++;
      line_start = p;
      has_call = false;
      continue;
    }
    if (!has_call && c == ' ' && strncmp(p, " call ", 6) == 0)
      has_call = true;
    p++;
  }
  if (p != line_start)
  {
    fwrite(line_start, 1, (size_t)(p - line_start), output_file);
    if (has_call)
      fprintf(output_file, ", !dbg !%d", locid);
  }
}

static void emit_func(Obj *fn)
{
  ir_reg = 1;
  sret_reg = NULL;
  is_terminated = false;
  current_block = NULL;
  current_fn = fn;

  reset_label_addrs();
  collect_labels(fn->body);

  if (!fn->is_live)
    return;

  // When emitting debug info, buffer the whole function body so we can append
  // a !dbg location to every call instruction (the LLVM verifier requires
  // inlinable calls in a function with debug info to carry a !dbg location).
  FILE *dbg_saved_out = NULL;
  char *dbg_buf = NULL;
  size_t dbg_buf_sz = 0;
  int dbg_func_idx = -1;
  if (opt_g && dbg_sp_cnt < IR_DBG_MAX)
  {
    FILE *mem = open_memstream(&dbg_buf, &dbg_buf_sz);
    if (mem)
    {
      dbg_saved_out = output_file;
      output_file = mem;
      dbg_func_idx = dbg_sp_cnt; // index this function will claim below
    }
  }

  bool sret = is_sret(fn->ty->return_ty);
  emit("define ");
  if (fn->is_static)
    emit("internal ");
  else if (fn->is_weak)
    emit("weak ");

  if (sret)
    emit("void");
  else
    emit_type_str(fn->ty->return_ty);
  emit(" ");
  emit_llvm_name(ir_sym(fn));
  emit("(");

  if (sret)
  {
    // The aggregate return value is passed through a hidden sret pointer
    // argument.  For large structs (size > 16) the parser has already
    // prepended such a parameter (with an empty name) to fn->params; we
    // reuse it so the signature matches the call sites.  For small
    // structs the parser does not add the parameter, so we synthesize the
    // sret argument here.  Either way the returned value is copied into
    // this buffer by gen_ir_stmt_return.
    if (fn->params && (!fn->params->name || !fn->params->name[0]))
    {
      const char *pname = fn->params->name && fn->params->name[0]
                              ? fn->params->name
                              : format("_p%d", llvm_obj_id(fn->params));
      sret_reg = format("%%%s", pname);
      emit("ptr sret(i8) %%%s", pname);
    }
    else
    {
      sret_reg = "%_agg_result";
      emit("ptr sret(i8) %s", sret_reg);
    }
  }


  bool first_param = true;
  Obj *param;
  for (param = fn->params; param; param = param->next)
  {
    if (sret && first_param && (!param->name || !param->name[0]))
      continue;
    if (sret || !first_param)
      emit(", ");
    first_param = false;

    if (fn->ty->is_variadic && (param->ty->kind == TY_STRUCT || param->ty->kind == TY_UNION))
    {
      int al = ir_type_align(param->ty);
      emit("ptr byval(");
      emit_llvm_aggr_type(param->ty);
      emit(")");
      if (al > 16)
        emit(" align %d", al);
    }
    else
      emit_type_str(param->ty);
    const char *pname = param->name && param->name[0] ? param->name : format("_p%d", llvm_obj_id(param));
    emit(" %%%s", pname);
  }
  if (fn->ty->is_variadic)
  {
    if (fn->params)
      emit(", ");
    emit("...");
  }
  if (opt_g && dbg_sp_cnt < IR_DBG_MAX)
  {
    int idx = dbg_sp_cnt++;
    dbg_sp_name[idx] = fn->name ? fn->name : ir_sym(fn);
    dbg_sp_line[idx] = fn->tok ? fn->tok->line_no : 1;
    // Subprogram id = IR_DBG_SP_BASE + 2*idx, its DILocation = +1.
    emit(") !dbg !%d {\n", IR_DBG_SP_BASE + 2 * idx);
  }
  else
    emit(") {\n");
  emit_label(".L.entry");

  emit_scope_allocas(fn->ty->scopes, fn->params, 2);

  for (param = fn->params; param; param = param->next)
  {
    if (!param->name || !param->name[0])
      continue;
    emit("  %s = alloca i8, i64 %ld, align %d\n", var_ptr(param),
         ir_param_slot_size(param->ty), ir_param_slot_align(param->ty));
  }


  if (fn->ty->is_variadic && fn->va_area)
    emit("  call void @llvm.va_start(ptr %s)\n", var_ptr(fn->va_area));

  for (param = fn->params; param; param = param->next)
  {
    if (!param->name || !param->name[0])
      continue;
    const char *pname = param->name && param->name[0] ? param->name : format("_p%d", llvm_obj_id(param));
    if (param->ty->kind == TY_STRUCT || param->ty->kind == TY_UNION)
    {
      // Struct/union parameters arrive as a hidden `ptr` (the AMD64 SysV
      // by-value ABI) but we want the parameter slot to hold the struct
      // itself, like a local variable.  Copy it in at entry so field access
      // and `&param` address the slot directly (no load-ptr-then-gep, which
      // llc miscompiles when the parameter's address is also taken).
      emit("  call void @llvm.memcpy.p0.p0.i64(ptr %s, ptr %%%s, i64 %ld, i1 false)\n",
           var_ptr(param), pname, param->ty->size);
    }
    else
    {
      emit("  store ");
      emit_type_str(param->ty);
      emit(" %%%s, ptr %s\n", pname, var_ptr(param));
    }
  }

  bool terminated = false;
  emit_stmt(fn->body, 2, &terminated);
  if (!terminated)
  {

    if (fn->ty->return_ty->kind == TY_VOID || sret)
      emit("  ret void\n");
    else if (strcmp(fn->name, "main") == 0)
      emit("  ret i32 0\n");
    else
    {
      Type *rty = fn->ty->return_ty;
      emit("  ret ");
      if (rty->kind == TY_FLOAT || rty->kind == TY_DOUBLE ||
          rty->kind == TY_LDOUBLE)
      {
        // The typed zero literal already carries the type (e.g.
        // "x86_fp80 0xK..."); emitting emit_type_str too would duplicate it.
        emit_float_zero_const(rty);
        emit("\n");
      }
      else
      {
        emit_type_str(rty);
        emit(" ");
        if (is_pointer(rty))
          emit("null\n");
        else if (is_integer(rty))
          emit("0\n");
        else
          emit("zeroinitializer\n");
      }
    }
  }
  // Always close the function, even if its body ended in a noreturn call
  // that left the current block terminated (emit() swallows trailing
  // output in that case).  The closing brace is pure syntax and required.
  is_terminated = false;
  emit("}\n\n");

  if (dbg_saved_out)
  {
    fclose(output_file);
    output_file = dbg_saved_out;
    int locid = IR_DBG_SP_BASE + 2 * dbg_func_idx + 1;
    ir_dbg_flush_func(dbg_buf, locid);
    free(dbg_buf);
  }
}

// Emit @llvm.global_ctors / @llvm.global_dtors for functions marked with
// __attribute__((constructor)) / __attribute__((destructor)).  LLVM calls the
// referenced functions in ascending order of the i32 priority field, matching
// the .init_array/.fini_array ordering used by the native backend.
static int ctor_priority(int a, int b)
{
  int priority = a > b ? a : b;
  if (priority < 0 || priority > 65535)
    priority = 65535;
  return priority;
}

static void emit_ir_ctor_dtor(Obj *prog, bool ctor)
{
  int cnt = 0;
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    if (ctor && (fn->is_constructor || fn->ty->is_constructor))
      cnt++;
    if (!ctor && (fn->is_destructor || fn->ty->is_destructor))
      cnt++;
  }
  if (cnt == 0)
    return;

  emit("@llvm.global_%s = appending global [%d x { i32, ptr, ptr }] [",
       ctor ? "ctors" : "dtors", cnt);
  int i = 0;
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    int priority;
    if (ctor) {
      if (!(fn->is_constructor || fn->ty->is_constructor))
        continue;
      priority = ctor_priority(fn->constructor_priority,
                               fn->ty->constructor_priority);
    } else {
      if (!(fn->is_destructor || fn->ty->is_destructor))
        continue;
      priority = ctor_priority(fn->destructor_priority,
                               fn->ty->destructor_priority);
    }
    if (i)
      emit(", ");
    emit("{ i32, ptr, ptr } { i32 %d, ptr ", priority);
    emit_llvm_name(ir_sym(fn));
    emit(", ptr null }");
    i++;
  }
  emit("]\n");
}

// Emit the module-level debug metadata block for the DISubprograms collected
// during function emission.  Only a compile unit, file, subroutine type and
// one subprogram per function are produced; this suffices for llc to generate
// a .debug_line section and a zero DW_AT_stmt_list offset.
static void emit_ir_debug_info(void)
{
  if (!opt_g || dbg_sp_cnt == 0)
    return;
  const char *file = base_file ? base_file : "chibicc.c";
  emit("\n");
  emit("!llvm.dbg.cu = !{!0}\n");
  emit("!llvm.module.flags = !{!4, !5}\n");
  emit("!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, "
       "producer: \"chibicc\", isOptimized: false, runtimeVersion: 0, "
       "emissionKind: FullDebug, splitDebugInlining: false)\n");
  emit("!1 = !DIFile(filename: \"%s\", directory: \".\")\n", file);
  emit("!2 = !DISubroutineType(types: !3)\n");
  emit("!3 = !{null}\n");
  emit("!4 = !{i32 7, !\"Dwarf Version\", i32 4}\n");
  emit("!5 = !{i32 2, !\"Debug Info Version\", i32 3}\n");
  for (int i = 0; i < dbg_sp_cnt; i++)
  {
    int spid = IR_DBG_SP_BASE + 2 * i;
    emit("!%d = distinct !DISubprogram(name: \"%s\", scope: !1, file: !1, "
         "line: %d, type: !2, scopeLine: %d, unit: !0)\n",
         spid, dbg_sp_name[i], dbg_sp_line[i], dbg_sp_line[i]);
    emit("!%d = !DILocation(line: %d, column: 1, scope: !%d)\n",
         spid + 1, dbg_sp_line[i], spid);
  }
}

// True if a non-function symbol with the same IR name appears before `stop`
// in the program list.  Used to skip a duplicate tentative declaration for a
// symbol declared more than once.
static bool ir_sym_seen_before(Obj *prog, Obj *stop)
{
  for (Obj *v = prog; v != stop; v = v->next)
    if (!v->is_function && !strcmp(ir_sym(v), ir_sym(stop)))
      return true;
  return false;
}

// True if a real definition (or alias) of the same symbol appears after
// `self` in the program list, so a tentative declaration is not needed.
static bool ir_sym_has_definition(Obj *self)
{
  for (Obj *v = self->next; v; v = v->next)
    if ((v->is_definition || v->alias_name) && !strcmp(ir_sym(v), ir_sym(self)))
      return true;
  return false;
}

void emit_ir(Obj *prog, FILE *out)
{
  output_file = out;

  emit("; ModuleID = '" PRODUCT "'\n");
  emit("target datalayout = \"%s\"\n", opt_datalayout);
  emit("target triple = \"%s\"\n", opt_target_triple);
  emit("\n");

  for (Obj *var = prog; var; var = var->next) {
    if (var->is_function) continue;
    if (var->is_definition || var->alias_name)
      emit_global(var);
  }
  for (Obj *var = prog; var; var = var->next) {
    if (var->is_function || var->alias_name) continue;
    if (!var->is_definition) {
      if (ir_sym_seen_before(prog, var)) continue;
      if (!ir_sym_has_definition(var)) emit_global(var);
    }
  }

  emit("\n");

  emit("\n");

  bool has_abort_decl = false;
  for (Obj *fn = prog; fn; fn = fn->next)
    if (fn->is_function && !fn->is_definition && fn->name &&
        strcmp(fn->name, "abort") == 0) {
      has_abort_decl = true;
      break;
    }
  if (!has_abort_decl)
    emit("declare void @abort()\n");
    

  for (Obj *fn = prog; fn; fn = fn->next)
  {
    if (!fn->is_function || !fn->is_definition || !fn->ty || fn->ty->kind != TY_FUNC)
      continue;
    emit_func(fn);
  }

  // Emit function aliases (e.g., weak alias).
  for (Obj *fn = prog; fn; fn = fn->next)
  {
    if (!fn->is_function || !fn->alias_name || !fn->ty || fn->ty->kind != TY_FUNC)
      continue;
    emit_llvm_name(ir_sym(fn));
    emit(" = ");
    if (fn->is_weak)
      emit("weak ");
    emit("alias ");
    bool sret = is_sret(fn->ty->return_ty);
    if (sret)
      emit("void (ptr");
    else
    {
      emit_type_str(fn->ty->return_ty);
      emit(" (");
    }
    int n = 0;
    for (Type *t = fn->ty->params; t; t = t->next)
    {
      if (n) emit(", ");
      emit_type_str(t);
      n++;
    }
    if (fn->ty->is_variadic)
    {
      if (n) emit(", ");
      emit("...");
    }
    emit(")");
    if (sret)
      emit(", void (ptr");
    else
    {
      emit(", ");
      emit_type_str(fn->ty->return_ty);
      emit(" (");
    }
    n = 0;
    for (Type *t = fn->ty->params; t; t = t->next)
    {
      if (n) emit(", ");
      emit_type_str(t);
      n++;
    }
    if (fn->ty->is_variadic)
    {
      if (n) emit(", ");
      emit("...");
    }
    emit(")* ");
    emit_llvm_name(fn->alias_name);
    emit("\n");
  }

  for (Obj *fn = prog; fn; fn = fn->next)
  {
    if (!fn->is_function || fn->is_definition || fn->alias_name || !fn->ty || fn->ty->kind != TY_FUNC)
      continue;
    bool emitted = false;
    for (Obj *f = prog; f != fn; f = f->next) {
      if (f->is_function && !f->is_definition && !f->alias_name && !strcmp(ir_sym(f), ir_sym(fn))) {
        emitted = true;
        break;
      }
    }
    if (emitted) continue;
    // Check if a definition with the same LLVM name exists (forward or backward).
    bool has_def = false;
    for (Obj *f = prog; f; f = f->next) {
      if (f != fn && f->is_function && f->is_definition && !strcmp(ir_sym(f), ir_sym(fn))) {
        has_def = true;
        break;
      }
    }
    if (has_def) continue;
    emit("declare");
    if (fn->is_weak)
      emit(" extern_weak");
    emit(" ");
    bool sret = is_sret(fn->ty->return_ty);
    if (sret)
      emit("void");
    else
      emit_type_str(fn->ty->return_ty);
    emit(" ");
    emit_llvm_name(ir_sym(fn));
    emit("(");

    if (sret)
      emit("ptr sret(i8)");

     Type *ptype = fn->ty->params;
     for (Type *t = ptype; t; t = t->next)
     {
        if (sret || t != ptype)
          emit(", ");
        // Genuine libc functions (prototype in a system header) obey the
        // AMD64 SysV ABI: a small aggregate (<= 16 bytes) is passed by value
        // as one or two eightbyte scalar slots, while larger aggregates are
        // MEMORY class and passed as a `byval` pointer.  Declare the parameter
        // this way so the signature matches the call sites (which lower
        // struct/union arguments the same way) and the real libc implementation
        // is called correctly, e.g. `sigqueue(pid_t, int, union sigval)`.
        // chibicc-compiled functions (including those defined in another
        // translation unit) keep the internal convention instead: a plain
        // `ptr` for non-variadic parameters and a `byval` pointer for variadic
        // ones, matching their definitions.
        if (t->kind == TY_STRUCT || t->kind == TY_UNION)
        {
          if (ir_is_system_func(fn))
          {
            const char *eb_ty[2] = {NULL, NULL};
            int ne = ir_sysv_agg_eightbytes(t, eb_ty);
            if (ne == 0)
            {
              int al = ir_type_align(t);
              emit("ptr byval(");
              emit_llvm_aggr_type(t);
              emit(")");
              if (al > 16)
                emit(" align %d", al);
            }
            else
            {
              for (int e = 0; e < ne; e++)
              {
                if (e)
                  emit(", ");
                emit("%s", eb_ty[e]);
              }
            }
          }
          else if (fn->ty->is_variadic)
          {
            int al = ir_type_align(t);
            emit("ptr byval(");
            emit_llvm_aggr_type(t);
            emit(")");
            if (al > 16)
              emit(" align %d", al);
          }
          else
            emit("ptr");
        }
        else
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

  emit_ir_ctor_dtor(prog, true);
  emit_ir_ctor_dtor(prog, false);
  emit_ir_debug_info();
}
