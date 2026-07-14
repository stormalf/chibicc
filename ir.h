#ifndef CHIBICC_IR_H
#define CHIBICC_IR_H

#include "chibicc.h"

// Shared state for the LLVM IR backend (defined in ir.c).
extern FILE *output_file;
extern int ir_reg;
extern const char *current_block;
extern const char *sret_reg;
extern bool is_terminated;
FILE *output_file;
int ir_reg;
const char *current_block;
const char *sret_reg;
bool is_terminated;
static Obj *current_fn;

// Debug-info (DWARF) state.  When -g is given we emit minimal LLVM debug
// metadata: a DICompileUnit plus one DISubprogram per emitted function.  This
// is enough for llc to produce a .debug_line table and a DW_AT_stmt_list.
#define IR_DBG_MAX 8192
#define IR_DBG_SP_BASE 6
static int dbg_sp_cnt;
static const char *dbg_sp_name[IR_DBG_MAX];
static int dbg_sp_line[IR_DBG_MAX];
static Obj **obj_map;
static int obj_map_count;
static int obj_map_cap;


// Declarations shared between ir.c and ir_builtin.c.

void asm_llvm_ty(Type *ty, char *buf, size_t sz);
const char *atomic_int_to_float_val(const char *reg, Type *ty, int indent);
const char *bitcast_to_intrinsic_vec(const char *src, Type *ty, int elem, int indent);
const char *cast_uint_width(const char *reg, int src_bits, int dst_bits, int indent);
char *convert_asm_template(const char *tmpl, int noutputs, AsmOperand *outputs, AsmOperand *inputs, int ninputs);
void emit(const char *fmt, ...);
void emit_atomic_type_str(Type *ty);
const char *emit_expr(Node *node, int indent);
void emit_float_const(const char *reg, Node *node);
void emit_indent(int indent);
void emit_label(const char *label);
const char *emit_lval_ptr(Node *node, int indent);
const char *emit_reinterpret_via_mem_ty(const char *val, Type *src_ty, Type *dst_ty, int indent);
void emit_stmt(Node *node, int indent, bool *terminated);
const char *emit_to_bool(const char *val, Type *ty, int indent);
void emit_type_str(Type *ty);
void emit_vec_type_str(int n, Type *elem);
char *escape_ir_asm(const char *s);
const char *gen_ir_abort(Node *node, int indent);
const char *gen_ir_add(Node *node, int indent);
const char *gen_ir_add_and_fetch(Node *node, int indent);
const char *gen_ir_addfetch(Node *node, int indent);
const char *gen_ir_addr(Node *node, int indent);
const char *gen_ir_addsub(Node *node, int indent);
const char *gen_ir_alloc(Node *node, int indent);
const char *gen_ir_andfetch(Node *node, int indent);
const char *gen_ir_assign(Node *node, int indent);
const char *gen_ir_atomic_is_lock_free(Node *node, int indent);
const char *gen_ir_bextr(Node *node, int indent);
const char *gen_ir_bitcast_vec_to_elem(const char *v, Type *ty, int ebits, int indent);
const char *gen_ir_bitnot(Node *node, int indent);
const char *gen_ir_blend(Node *node, int indent);
const char *gen_ir_bool_cas(Node *node, int indent);
const char *gen_ir_builtin_add_overflow(Node *node, int indent);
const char *gen_ir_builtin_bswap16(Node *node, int indent);
const char *gen_ir_builtin_bswap32(Node *node, int indent);
const char *gen_ir_builtin_bswap64(Node *node, int indent);
const char *gen_ir_builtin_clz(Node *node, int indent);
const char *gen_ir_builtin_clzl(Node *node, int indent);
const char *gen_ir_builtin_ctz(Node *node, int indent);
const char *gen_ir_builtin_ctzl(Node *node, int indent);
const char *gen_ir_builtin_frame_address(Node *node, int indent);
const char *gen_ir_float_const_builtin(Node *node, int indent);
const char *gen_ir_builtin_isnan(Node *node, int indent);
const char *gen_ir_builtin_memcpy(Node *node, int indent);
const char *gen_ir_builtin_memset(Node *node, int indent);
const char *gen_ir_builtin_mul_overflow(Node *node, int indent);
const char *gen_ir_builtin_sub_overflow(Node *node, int indent);
const char *gen_ir_cas(Node *node, int indent);
const char *gen_ir_cas_n(Node *node, int indent);
const char *gen_ir_cast(Node *node, int indent);
const char *gen_ir_clear(Node *node, int indent);
const char *gen_ir_clflush(Node *node, int indent);
const char *gen_ir_cmpxchg(Node *node, int indent);
const char *gen_ir_cmpxchg_n(Node *node, int indent);
const char *gen_ir_comi(Node *node, int indent);
const char *gen_ir_comma(Node *node, int indent);
const char *gen_ir_cond(Node *node, int indent);
const char *gen_ir_crc32(Node *node, int indent);
const char *gen_ir_cvtpi2ps(Node *node, int indent);
const char *gen_ir_default(Node *node, int indent);
const char *gen_ir_deref(Node *node, int indent);
const char *gen_ir_dpp(Node *node, int indent);
const char *gen_ir_eq(Node *node, int indent);
const char *gen_ir_exch(Node *node, int indent);
const char *gen_ir_exch_n(Node *node, int indent);
const char *gen_ir_expect(Node *node, int indent);
const char *gen_ir_fetchadd(Node *node, int indent);
const char *gen_ir_fetchand(Node *node, int indent);
const char *gen_ir_fetchnand(Node *node, int indent);
const char *gen_ir_fetchor(Node *node, int indent);
const char *gen_ir_fetchsub(Node *node, int indent);
const char *gen_ir_fetchxor(Node *node, int indent);
const char *gen_ir_fpclassify(Node *node, int indent);
const char *gen_ir_funcall(Node *node, int indent);
const char *gen_ir_hadd_hsub(Node *node, int indent);
const char *gen_ir_horizontal(Node *node, int indent, int ebits, bool sub, bool sat);
const char *gen_ir_insertps(Node *node, int indent);
const char *gen_ir_int_vec_binop(Node *node, int indent);
const char *gen_ir_int_vec_unary(Node *node, int indent);
const char *gen_ir_isunordered(Node *node, int indent);
const char *gen_ir_label_val(Node *node, int indent);
const char *gen_ir_load(Node *node, int indent);
const char *gen_ir_load_eightbyte(const char *addr, int off, const char *llty, int indent);
const char *gen_ir_load_n(Node *node, int indent);
const char *gen_ir_logand(Node *node, int indent);
const char *gen_ir_maskmov(Node *node, int indent);
const char *gen_ir_membarrier(Node *node, int indent);
const char *gen_ir_memzero(Node *node, int indent);
const char *gen_ir_movmsk(Node *node, int indent);
const char *gen_ir_movnt_vec_store(Node *node, int indent);
const char *gen_ir_movntdqa_load(Node *node, int indent);
const char *gen_ir_movnti_store(Node *node, int indent);
const char *gen_ir_movq128(Node *node, int indent);
const char *gen_ir_mpsadbw(Node *node, int indent);
const char *gen_ir_nandfetch(Node *node, int indent);
const char *gen_ir_neg(Node *node, int indent);
const char *gen_ir_not(Node *node, int indent);
const char *gen_ir_null_expr(Node *node, int indent);
const char *gen_ir_num(Node *node, int indent);
const char *gen_ir_orfetch(Node *node, int indent);
const char *gen_ir_overflow_arith(Node *node, int indent, const char *op);
const char *gen_ir_pack(Node *node, int indent);
const char *gen_ir_pack_sat(const char *src, const char *vsrc, int na, int deb, bool is_unsigned, 
    const char *lo_splat, const char *hi_splat, int indent);
const char *gen_ir_palignr(Node *node, int indent, bool is256);
const char *gen_ir_parity(Node *node, int indent);
const char *gen_ir_parityl(Node *node, int indent);
const char *gen_ir_pblend(Node *node, int indent);
const char *gen_ir_pcmpgtb256_mask(Node *node, int indent);
const char *gen_ir_pcmpistr(Node *node, int indent);
const char *gen_ir_permdi256(Node *node, int indent);
const char *gen_ir_phminposuw(Node *node, int indent);
const char *gen_ir_pmaddubsw(Node *node, int indent);
const char *gen_ir_pmaddwd(Node *node, int indent);
const char *gen_ir_pmov_sx_zx(Node *node, int indent);
const char *gen_ir_pmovmskb(Node *node, int indent);
const char *gen_ir_popcount(Node *node, int indent);
const char *gen_ir_popcountl(Node *node, int indent);
const char *gen_ir_pos(Node *node, int indent);
const char *gen_ir_prefetch(Node *node, int indent);
const char *gen_ir_psadbw(Node *node, int indent);
const char *gen_ir_pshift_dq(Node *node, int indent);
const char *gen_ir_pshift_intrinsic(Node *node, int indent);
const char *gen_ir_pshuf(Node *node, int indent, int hi_low);
const char *gen_ir_pshufb(Node *node, int indent);
const char *gen_ir_psll_imm(Node *node, int indent);
const char *gen_ir_ptest(Node *node, int indent);
const char *gen_ir_punpck(Node *node, int indent);
const char *gen_ir_reinterpret_vec(const char *val, Type *from, Type *to, int indent);
const char *gen_ir_release(Node *node, int indent);
const char *gen_ir_return_addr(Node *node, int indent);
const char *gen_ir_rmw_new(Node *node, int indent, const char *op);
const char *gen_ir_rmw_old(Node *node, int indent, const char *op);
const char *gen_ir_shuffle(Node *node, int indent);
const char *gen_ir_shuffle_blend(Node *node, int indent);
const char *gen_ir_shufp(Node *node, int indent);
const char *gen_ir_signbit(Node *node, int indent);
const char *gen_ir_sse_binop(Node *node, int indent);
const char *gen_ir_sse_load(Node *node, int indent);
const char *gen_ir_sse_movlhmh(Node *node, int indent);
const char *gen_ir_sse_movss_sd(Node *node, int indent);
const char *gen_ir_sse_store(Node *node, int indent);
const char *gen_ir_sse_unsupported(Node *node, int indent);
const char *gen_ir_stdc_bit_ceil(Node *node, int indent);
void gen_ir_stmt_asm(Node *node, int indent, bool *terminated);
void gen_ir_stmt_block(Node *node, int indent, bool *terminated);
void gen_ir_stmt_case(Node *node, int indent, bool *terminated);
void gen_ir_stmt_default(Node *node, int indent, bool *terminated);
void gen_ir_stmt_do(Node *node, int indent, bool *terminated);
const char *gen_ir_stmt_expr(Node *node, int indent);
void gen_ir_stmt_expr_stmt(Node *node, int indent, bool *terminated);
void gen_ir_stmt_for(Node *node, int indent, bool *terminated);
void gen_ir_stmt_goto(Node *node, int indent, bool *terminated);
void gen_ir_stmt_goto_expr(Node *node, int indent, bool *terminated);
void gen_ir_stmt_if(Node *node, int indent, bool *terminated);
void gen_ir_stmt_label(Node *node, int indent, bool *terminated);
void gen_ir_stmt_null_expr(Node *node, int indent, bool *terminated);
void gen_ir_stmt_return(Node *node, int indent, bool *terminated);
void gen_ir_stmt_switch(Node *node, int indent, bool *terminated);
const char *gen_ir_stmxcsr(Node *node, int indent);
const char *gen_ir_store(Node *node, int indent);
const char *gen_ir_store_n(Node *node, int indent);
const char *gen_ir_sub_and_fetch(Node *node, int indent);
const char *gen_ir_subfetch(Node *node, int indent);
const char *gen_ir_sync(Node *node, int indent);
const char *gen_ir_testandset(Node *node, int indent);
const char *gen_ir_testandseta(Node *node, int indent);
const char *gen_ir_uadd_overflow(Node *node, int indent);
const char *gen_ir_umul_overflow(Node *node, int indent);
const char *gen_ir_unary_float(Node *node, int indent);
const char *gen_ir_unpck(Node *node, int indent);
const char *gen_ir_unreachable(Node *node, int indent);
const char *gen_ir_var(Node *node, int indent);
const char *gen_ir_vec_cast_extract(Node *node, int indent);
const char *gen_ir_vec_ext(Node *node, int indent);
const char *gen_ir_vec_init(Node *node, int indent);
const char *gen_ir_vec_set(Node *node, int indent);
const char *gen_ir_vextractf128(Node *node, int indent);
const char *gen_ir_vinsertf128(Node *node, int indent);
const char *gen_ir_vperm2f128(Node *node, int indent);
const char *gen_ir_vperm2i128(Node *node, int indent);
const char *gen_ir_vpermil(Node *node, int indent);
const char *gen_ir_vpermil_group(Node *node, int indent);
const char *gen_ir_x86_addcarryx_u32(Node *node, int indent);
const char *gen_ir_x86_addcarryx_u64(Node *node, int indent);
const char *gen_ir_x86_bsrdi(Node *node, int indent);
const char *gen_ir_x86_bsrsi(Node *node, int indent);
const char *gen_ir_x86_rdfsbase(Node *node, int indent);
const char *gen_ir_x86_rdgsbase(Node *node, int indent);
const char *gen_ir_x86_rdpid(Node *node, int indent);
const char *gen_ir_x86_rdpmc(Node *node, int indent);
const char *gen_ir_x86_rdsspq(Node *node, int indent);
const char *gen_ir_x86_rdtsc(Node *node, int indent);
const char *gen_ir_x86_rdtscp(Node *node, int indent);
const char *gen_ir_x86_readeflags(Node *node, int indent);
const char *gen_ir_x86_sbb_u32(Node *node, int indent);
const char *gen_ir_x86_sbb_u64(Node *node, int indent);
const char *gen_ir_x86_tzcnt_u16(Node *node, int indent);
const char *gen_ir_x86_writeeflags(Node *node, int indent);
const char *gen_ir_xorfetch(Node *node, int indent);
const char *gen_ir_zext_to_i64(const char *v, Type *ty, int indent);
int int_type_bits(Type *ty);
const char *int_val_to_atomic_int(const char *reg, Type *val_ty, Type *ty, int indent);
const char *ir_atomic_ordering(int memorder);
const char *ir_emit_atomic_load(const char *ptr, Type *ty, int memorder, int indent);
void ir_emit_atomic_store(const char *val, const char *ptr, Type *ty, int memorder, int indent, int val_bits);
const char *ir_emit_atomicrmw(const char *op, const char *ptr, const char *val,  Type *ty, int memorder, int indent, int val_bits);
const char *ir_gep_i8(const char *base, long off, int indent);
const char *ir_load(Type *ty, const char *addr, int align, int indent);
const char *ir_sym(Obj *var);
bool ir_universal_fbinop_op(Node *node, const char **out_op);
bool is_float_type(Type *ty);
bool is_pshift_dq(NodeKind k);
bool is_punpck_high(Node *node);
bool is_scalar_sse_arith(Node *node);
bool is_scalar_sse_cmp(Node *node);
void llvm_x86_constraint(const char *c, char *out, size_t sz);
const char *new_reg(void);
void register_label_addr(const char *label);
const char *vec_elem_llvm_str(int bits);

static int ir_type_align(Type *ty);


  static const char *const simple[] = {
    [TY_VOID]    = "void",
    [TY_BOOL]    = "i1",
    [TY_CHAR]    = "i8",
    [TY_SHORT]   = "i16",
    [TY_INT]     = "i32",
    [TY_LONG]    = "i64",
    [TY_LLONG]   = "i64",
    [TY_FLOAT]   = "float",
    [TY_DOUBLE]  = "double",
    [TY_LDOUBLE] = "x86_fp80",
    [TY_ENUM]    = "i32",
    [TY_PTR]     = "ptr",
    [TY_FUNC]    = "ptr",
    [TY_ARRAY]   = "ptr",
    [TY_VLA]     = "ptr",
    [TY_STRUCT]  = "ptr",
    [TY_UNION]   = "ptr",
    [TY_INT128]  = "i128",
  };

#endif // CHIBICC_IR_H
