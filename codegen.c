#include "chibicc.h"
#define CODEGEN_C "codegen.c"


#define REDZONE(X)  \
  "sub\t$16,%rsp\n" \
  "\t" X "\n"       \
  "\tadd\t$16,%rsp"


#define GP_MAX 6
#define FP_MAX 8

static FILE *output_file;
static int depth;
static char *argreg8[] = {"%dil", "%sil", "%dl", "%cl", "%r8b", "%r9b"};
static char *argreg16[] = {"%di", "%si", "%dx", "%cx", "%r8w", "%r9w"};
static char *argreg32[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};
static char *argreg64[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};


static char *newargreg8[] =   {"%cl",   "%bl",  "%dl",  "%al",  "%dil", "%r8b", "%r9b", "r10b", "r11b"};
static char *newargreg16[] =  {"%cx",   "%bx",  "%dx",  "%ax",  "%di",  "%r8w", "%r9w", "r10w", "r11w" };
static char *newargreg32[] =  {"%ecx",  "%ebx", "%edx", "%eax", "%edi", "%r8d", "%r9d", "r10d", "r11d" };
static char *newargreg64[] =  {"%rcx",  "%rbx", "%rdx", "%rax", "%rdi", "%r8",  "%r9",  "r10",  "r11" };
static char *registerUsed[] = {"free",  "free", "free", "free", "free", "free", "free", "free", "free"};

static int last_loc_line = 0;

extern int64_t eval(Node *node);

static Obj *current_fn;

static void gen_expr(Node *node);
static void gen_stmt(Node *node);
static void print_offset(Obj *prog);
static void pushx(void);
static void popx(int reg);
void push2(void);
void pop2(char *a, char *b);


__attribute__((format(printf, 1, 2))) void println(char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(output_file, fmt, ap);
  va_end(ap);
  fprintf(output_file, "\n");
}

static int count(void)
{
  static int i = 1;
  return i++;
}

static void push(void)
{
  println("  push %%rax");
  depth++;
}

static void pop(char *arg)
{
  println("  pop %s", arg);
  depth--;
}


static void pushf(Type *ty) {

  switch (ty->vector_size) {
    case 16:  // 128-bit vectors
      pushx();
      break;

    default:
      println("  push %%rax");
      println("  movsd %%xmm0, (%%rsp)");
      depth++;
      break;
  }
}

static void popf(Type *ty, int reg) {
  switch (ty->vector_size) {
    case 16:  // 128-bit vectors
      popx(reg);
      break;

    default:
      println("  movsd (%%rsp), %%xmm%d", reg);
      println("  add $8, %%rsp");
      depth--;
      break;
  }
}


// Round up `n` to the nearest multiple of `align`. For instance,
// align_to(5, 8) returns 8 and align_to(11, 8) returns 16.
int align_to(int n, int align)
{
  //return (n + align - 1) / align * align;
  return ((n + align - 1) / align) * align;
}

char *reg_dx(int sz)
{
  switch (sz)
  {
  case 1:
    return "%dl";
  case 2:
    return "%dx";
  case 4:
    return "%edx";
  case 8:
    return "%rdx";
  case 16:
    return "%rdx";
  }
  unreachable();
}


char *reg_di(int sz)
{
  switch (sz)
  {
  case 1:
    return "%dil";
  case 2:
    return "%di";
  case 4:
    return "%edi";
  case 8:
    return "%rdi";
  case 16:
    return "%rdi";
  }
  unreachable();
}

char *reg_si(int sz)
{
  switch (sz)
  {
  case 1:
    return "%sil";
  case 2:
    return "%si";
  case 4:
    return "%esi";
  case 8:
    return "%rsi";
  case 16:
    return "%rsi";
  }
  unreachable();
}


char *reg_r8w(int sz)
{
  switch (sz)
  {
  case 1:
    return "%r8b";
  case 2:
    return "%r8w";
  case 4:
    return "%r8d";
  case 8:
    return "%r8";
  case 16:
    return "%r8";
  }
  unreachable();
}

char *reg_r9w(int sz)
{
  switch (sz)
  {
  case 1:
    return "%r9b";
  case 2:
    return "%r9w";
  case 4:
    return "%r9d";
  case 8:
    return "%r9";
  case 16:
    return "%r9";
  }
  unreachable();
}


char *reg_r10w(int sz)
{
  switch (sz)
  {
  case 1:
    return "%r10b";
  case 2:
    return "%r10w";
  case 4:
    return "%r10d";
  case 8:
    return "%r10";
  case 16:
    return "%r10";
  }
  unreachable();
}

char *reg_r11w(int sz)
{
  switch (sz)
  {
  case 1:
    return "%r11b";
  case 2:
    return "%r11w";
  case 4:
    return "%r11d";
  case 8:
    return "%r11";
  case 16:
    return "%r11";
  }
  unreachable();
}


char *reg_bx(int sz)
{
  switch (sz)
  {
  case 1:
    return "%bl";
  case 2:
    return "%bx";
  case 4:
    return "%ebx";
  case 8:
    return "%rbx";
  case 16:
    return "%rbx";
  }
  unreachable();
}

char *reg_cx(int sz)
{
  switch (sz)
  {
  case 1:
    return "%cl";
  case 2:
    return "%cx";
  case 4:
    return "%ecx";
  case 8:
    return "%rcx";
  case 16:
    return "%rcx";
  }
  unreachable();
}

char *reg_ax(int sz)
{

  switch (sz)
  {
  case 1:
    return "%al";
  case 2:
    return "%ax";
  case 4:
    return "%eax";
  case 8:
    return "%rax";
  case 16:
    return "%rax";
  }
  unreachable();
}

// Compute the absolute address of a given node.
// It's an error if a given node does not reside in memory.
static void gen_addr(Node *node)
{
  switch (node->kind)
  {
  case ND_VAR:
    

    // Variable-length array, which is always local.
    if (node->var->ty->kind == TY_VLA)
    {
      println("  mov %d(%%rbp), %%rax", node->var->offset);
      return;
    }

    // Local variable
    if (node->var->is_local)
    {
      println("  lea %d(%%rbp), %%rax", node->var->offset);
      return;
    }


    if (opt_fpic)
    {
      // Thread-local variable
      if (node->var->is_tls)
      {
        println("  data16 lea \"%s\"@tlsgd(%%rip), %%rdi", node->var->name);
        println("  .value 0x6666");
        println("  rex64");
        println("  call __tls_get_addr@PLT");
        return;
      }

      // Function or global variable
      println("  mov \"%s\"@GOTPCREL(%%rip), %%rax", node->var->name);
      return;
    }

    // Thread-local variable
    if (node->var->is_tls)
    {
      println("  mov %%fs:0, %%rax");
      println("  add $\"%s\"@tpoff, %%rax", node->var->name);
      return;
    }

    // Here, we generate an absolute address of a function or a global
    // variable. Even though they exist at a certain address at runtime,
    // their addresses are not known at link-time for the following
    // two reasons.
    //
    //  - Address randomization: Executables are loaded to memory as a
    //    whole but it is not known what address they are loaded to.
    //    Therefore, at link-time, relative address in the same
    //    exectuable (i.e. the distance between two functions in the
    //    same executable) is known, but the absolute address is not
    //    known.
    //
    //  - Dynamic linking: Dynamic shared objects (DSOs) or .so files
    //    are loaded to memory alongside an executable at runtime and
    //    linked by the runtime loader in memory. We know nothing
    //    about addresses of global stuff that may be defined by DSOs
    //    until the runtime relocation is complete.
    //
    // In order to deal with the former case, we use RIP-relative
    // addressing, denoted by `(%rip)`. For the latter, we obtain an
    // address of a stuff that may be in a shared object file from the
    // Global Offset Table using `@GOTPCREL(%rip)` notation.

    // Function
    if (node->ty->kind == TY_FUNC)
    {
      if (node->var->is_definition)
        println("  lea \"%s\"(%%rip), %%rax", node->var->name);
      else
        println("  mov \"%s\"@GOTPCREL(%%rip), %%rax", node->var->name);
      return;
    }


    // Global variable
    println("  lea \"%s\"(%%rip), %%rax", node->var->name);
    return;
  case ND_DEREF:
    gen_expr(node->lhs);
    return;
  case ND_COMMA:
    gen_expr(node->lhs);
    gen_addr(node->rhs);
    return;
  case ND_MEMBER:
    // gen_addr(node->lhs);
    // println("  add $%d, %%rax", node->member->offset);
    // return;
    //fix from @fuhsnn on some issues with members
    switch(node->lhs->kind) {
      case ND_FUNCALL:
        if (!node->lhs->ret_buffer)
          break;
      case ND_ASSIGN:
      case ND_COND:
      case ND_STMT_EXPR:
        if (node->lhs->ty->kind != TY_STRUCT && node->lhs->ty->kind != TY_UNION)
          break;
        gen_expr(node->lhs);
        println("  add $%d, %%rax", node->member->offset);
        return;
      default:
        gen_addr(node->lhs);
        println("  add $%d, %%rax", node->member->offset);
        return;
      }    
  case ND_FUNCALL:
    if (node->ret_buffer)
    {
      gen_expr(node);
      return;
    }
    break;
  case ND_ASSIGN:
  case ND_COND:
    if (node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION)
    {
      gen_expr(node);
      return;
    }
    break;
  case ND_VLA_PTR:
    println("  lea %d(%%rbp), %%rax", node->var->offset);
    return;
  }

  error_tok(node->tok, "%s:%d not an lvalue %d", CODEGEN_C, __LINE__, node->kind);
}


// Load a value from where %rax is pointing to.
static void load(Type *ty)
{
  switch (ty->kind)
  {
  case TY_ARRAY:
  case TY_STRUCT:
  case TY_UNION:
  case TY_FUNC:
  case TY_VLA:
      // Do not load arrays, structs, unions, functions, or VLAs into registers.
    return;

  case TY_FLOAT:
      println("  movss (%%rax), %%xmm0");  // Default case if vector_size is not specified
    return;

  case TY_DOUBLE:
    println("  movsd (%%rax), %%xmm0");
    return;

  case TY_LDOUBLE:
      println("  fldt (%%rax)");  // Load long double
    return;

    case TY_INT128:
      println("  mov 8(%%rax), %%rdx");  // Load upper 64 bits into RDX
      println("  mov (%%rax), %%rax");  // Load lower 64 bits into RAX
      return;

    default:
      if (ty->size == 1) {
        if (ty->is_unsigned) {
          println("  movzb (%%rax), %%eax");  // Zero-extend byte to 32-bit for unsigned
        } else {
          println("  movsbl (%%rax), %%eax");  // Sign-extend byte to 32-bit for signed
        }
      } else if (ty->size == 2) {
        if (ty->is_unsigned) {
          println("  movzwl (%%rax), %%eax");  // Zero-extend word to 32-bit for unsigned
        } else {
          println("  movswl (%%rax), %%eax");  // Sign-extend word to 32-bit for signed
        }
      } else if (ty->size == 4) {
        println("  mov (%%rax), %%eax");  // Load 32-bit value
      } else if (ty->size == 8) {
        println("  mov (%%rax), %%rax");  // Load 64-bit value
      } else if (ty->size == 16) {
        // Load 128-bit value: first lower 64 bits, then upper 64 bits
        println("  mov (%%rax), %%rax");  // Load lower 64 bits into RAX
        println("  mov 8(%%rax), %%rdx"); // Load upper 64 bits into RDX
      }
      return;
  }
}


// Store %rax to an address that the stack top is pointing to.
static void store(Type *ty)
{
  pop("%rdi");

  switch (ty->kind)
  {
  case TY_STRUCT:
  case TY_UNION:
    for (int i = 0; i < ty->size; i++)
    {
      println("  mov %d(%%rax), %%r8b", i);
      println("  mov %%r8b, %d(%%rdi)", i);
    }
    return;

  case TY_FLOAT:
      // Default case for unspecified vector size
    println("  movss %%xmm0, (%%rdi)");
    return;

  case TY_DOUBLE:
      // Default case for unspecified vector size
    println("  movsd %%xmm0, (%%rdi)");
    return;

  case TY_LDOUBLE:
    println("  fstpt (%%rdi)");
    return;

    case TY_INT128:
      println("  mov %%rax, (%%rdi)");
      println("  mov %%rdx, 8(%%rdi)");
      return;

    default:
      if (ty->size == 1) {
    println("  mov %%al, (%%rdi)");
      } else if (ty->size == 2) {
    println("  mov %%ax, (%%rdi)");
      } else if (ty->size == 4) {
    println("  mov %%eax, (%%rdi)");
      } else if (ty->size == 8) {
    println("  mov %%rax, (%%rdi)");
      } else if (ty->size == 16) {
        // For 128-bit values (size == 16)
        println("  mov %%rax, (%%rdi)");
        println("  mov %%rdx, 8(%%rdi)");
      }
      return;
  }
}


static void cmp_zero(Type *ty)
{
  switch (ty->kind)
  {
  case TY_FLOAT:
    println("  xorps %%xmm1, %%xmm1");
    println("  ucomiss %%xmm1, %%xmm0");
    return;
  case TY_DOUBLE:
    println("  xorpd %%xmm1, %%xmm1");
    println("  ucomisd %%xmm1, %%xmm0");
    return;
  case TY_LDOUBLE:
    println("  fldz");
    println("  fucomip");
    println("  fstp %%st(0)");
    return;
  case TY_INT128:
    println("  mov %%rax, %%r11");
    println("  or  %%rdx, %%r11");
    return;
  }

  if (is_integer(ty) && ty->size <= 4)
    println("  cmp $0, %%eax");
  else
    println("  cmp $0, %%rax");
}


#define i8i128  "movsbq\t%al,%rax\n\tcqto"
#define i16i128 "movswq\t%ax,%rax\n\tcqto"
#define i32i128 "cltq\n\tcqto"
#define i64i128 "cqto"
#define u8i128  "movzbq\t%al,%rax\n\txor\t%edx,%edx"
#define u16i128 "movzwq\t%ax,%rax\n\txor\t%edx,%edx"
#define u32i128 "cltq\n\txor\t%edx,%edx"
#define u64i128 "xor\t%edx,%edx"
#define i128f32 "mov\t%rax,%rdi\n\tmov\t%rdx,%rsi\n\tcall\t__floattisf"
#define i128f64 "mov\t%rax,%rdi\n\tmov\t%rdx,%rsi\n\tcall\t__floattidf"
#define i128f80 "mov\t%rax,%rdi\n\tmov\t%rdx,%rsi\n\tcall\t__floattixf"
#define u128f32 "mov\t%rax,%rdi\n\tmov\t%rdx,%rsi\n\tcall\t__floatuntisf"
#define u128f64 "mov\t%rax,%rdi\n\tmov\t%rdx,%rsi\n\tcall\t__floatuntidf"
#define u128f80 "mov\t%rax,%rdi\n\tmov\t%rdx,%rsi\n\tcall\t__floatuntixf"
#define f32i128 "call\t__fixsfti"
#define f64i128 "call\t__fixdfti"
#define f80i128 REDZONE("fstpt\t(%rsp)\n\tcall\t__fixxfti")
#define f32u128 "call\t__fixunssfti"
#define f64u128 "call\t__fixunsdfti"
#define f80u128 REDZONE("fstpt\t(%rsp)\n\tcall\t__fixunsxfti")


enum
{
  I8,
  I16,
  I32,
  I64,
  U8,
  U16,
  U32,
  U64,
  F32,
  F64,
  F80,
  I128,
  U128
};

static int getTypeId(Type *ty)
{
  if (!ty)
    return I32;
  switch (ty->kind)
  {
  case TY_CHAR:
    return ty->is_unsigned ? U8 : I8;
  case TY_SHORT:
    return ty->is_unsigned ? U16 : I16;
  case TY_INT:
    return ty->is_unsigned ? U32 : I32;
  case TY_LONG:
    return ty->is_unsigned ? U64 : I64;
  case TY_INT128:
    return ty->is_unsigned ? U128 : I128;  
  case TY_FLOAT:
    return F32;
  case TY_DOUBLE:
    return F64;
  case TY_LDOUBLE:
    return F80;
  }
  return U64;
}

// The table for type casts
static char i32i8[] = "movsbl %al, %eax";
static char i32u8[] = "movzbl %al, %eax";
static char i32i16[] = "movswl %ax, %eax";
static char i32u16[] = "movzwl %ax, %eax";
static char i32f32[] = "cvtsi2ssl %eax, %xmm0";
static char i32i64[] = "movsxd %eax, %rax";
static char i32f64[] = "cvtsi2sdl %eax, %xmm0";
static char i32f80[] = "mov %eax, -4(%rsp); fildl -4(%rsp)";

static char u32f32[] = "mov %eax, %eax; cvtsi2ssq %rax, %xmm0";
static char u32i64[] = "mov %eax, %eax";
static char u32f64[] = "mov %eax, %eax; cvtsi2sdq %rax, %xmm0";
static char u32f80[] = "mov %eax, %eax; mov %rax, -8(%rsp); fildll -8(%rsp)";

static char i64f32[] = "cvtsi2ssq %rax, %xmm0";
static char i64f64[] = "cvtsi2sdq %rax, %xmm0";
static char i64f80[] = "movq %rax, -8(%rsp); fildll -8(%rsp)";

static char u64f32[] = "cvtsi2ssq %rax, %xmm0";
static char u64f64[] =
    "test %rax,%rax; js 1f; pxor %xmm0,%xmm0; cvtsi2sd %rax,%xmm0; jmp 2f; "
    "1: mov %rax,%rdi; and $1,%eax; pxor %xmm0,%xmm0; shr %rdi; "
    "or %rax,%rdi; cvtsi2sd %rdi,%xmm0; addsd %xmm0,%xmm0; 2:";
static char u64f80[] =
    "mov %rax, -8(%rsp); fildq -8(%rsp); test %rax, %rax; jns 1f;"
    "mov $1602224128, %eax; mov %eax, -4(%rsp); fadds -4(%rsp); 1:";

static char f32i8[] = "cvttss2sil %xmm0, %eax; movsbl %al, %eax";
static char f32u8[] = "cvttss2sil %xmm0, %eax; movzbl %al, %eax";
static char f32i16[] = "cvttss2sil %xmm0, %eax; movswl %ax, %eax";
static char f32u16[] = "cvttss2sil %xmm0, %eax; movzwl %ax, %eax";
static char f32i32[] = "cvttss2sil %xmm0, %eax";
static char f32u32[] = "cvttss2siq %xmm0, %rax";
static char f32i64[] = "cvttss2siq %xmm0, %rax";
static char f32u64[] = "cvttss2siq %xmm0, %rax";
static char f32f64[] = "cvtss2sd %xmm0, %xmm0";
static char f32f80[] = "movss %xmm0, -4(%rsp); flds -4(%rsp)";

static char f64i8[] = "cvttsd2sil %xmm0, %eax; movsbl %al, %eax";
static char f64u8[] = "cvttsd2sil %xmm0, %eax; movzbl %al, %eax";
static char f64i16[] = "cvttsd2sil %xmm0, %eax; movswl %ax, %eax";
static char f64u16[] = "cvttsd2sil %xmm0, %eax; movzwl %ax, %eax";
static char f64i32[] = "cvttsd2sil %xmm0, %eax";
static char f64u32[] = "cvttsd2siq %xmm0, %rax";
static char f64i64[] = "cvttsd2siq %xmm0, %rax";
static char f64u64[] = "cvttsd2siq %xmm0, %rax";
static char f64f32[] = "cvtsd2ss %xmm0, %xmm0";
static char f64f80[] = "movsd %xmm0, -8(%rsp); fldl -8(%rsp)";

#define FROM_F80_1                                          \
  "fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; " \
  "mov %ax, -12(%rsp); fldcw -12(%rsp); "

#define FROM_F80_2 " -24(%rsp); fldcw -10(%rsp); "

static char f80i8[] = FROM_F80_1 "fistps" FROM_F80_2 "movsbl -24(%rsp), %eax";
static char f80u8[] = FROM_F80_1 "fistps" FROM_F80_2 "movzbl -24(%rsp), %eax";
static char f80i16[] = FROM_F80_1 "fistps" FROM_F80_2 "movzbl -24(%rsp), %eax";
static char f80u16[] = FROM_F80_1 "fistpl" FROM_F80_2 "movswl -24(%rsp), %eax";
static char f80i32[] = FROM_F80_1 "fistpl" FROM_F80_2 "mov -24(%rsp), %eax";
static char f80u32[] = FROM_F80_1 "fistpl" FROM_F80_2 "mov -24(%rsp), %eax";
static char f80i64[] = FROM_F80_1 "fistpq" FROM_F80_2 "mov -24(%rsp), %rax";
static char f80u64[] = FROM_F80_1 "fistpq" FROM_F80_2 "mov -24(%rsp), %rax";
static char f80f32[] = "fstps -8(%rsp); movss -8(%rsp), %xmm0";
static char f80f64[] = "fstpl -8(%rsp); movsd -8(%rsp), %xmm0";

// static char *cast_table[][11] = {
//     // i8   i16     i32     i64     u8     u16     u32     u64     f32     f64     f80
//     {NULL, NULL, NULL, i32i64, i32u8, i32u16, NULL, i32i64, i32f32, i32f64, i32f80},    // i8
//     {i32i8, NULL, NULL, i32i64, i32u8, i32u16, NULL, i32i64, i32f32, i32f64, i32f80},   // i16
//     {i32i8, i32i16, NULL, i32i64, i32u8, i32u16, NULL, i32i64, i32f32, i32f64, i32f80}, // i32
//     {i32i8, i32i16, NULL, NULL, i32u8, i32u16, NULL, NULL, i64f32, i64f64, i64f80},     // i64

//     {i32i8, NULL, NULL, i32i64, NULL, NULL, NULL, i32i64, i32f32, i32f64, i32f80},      // u8
//     {i32i8, i32i16, NULL, i32i64, i32u8, NULL, NULL, i32i64, i32f32, i32f64, i32f80},   // u16
//     {i32i8, i32i16, NULL, u32i64, i32u8, i32u16, NULL, u32i64, u32f32, u32f64, u32f80}, // u32
//     {i32i8, i32i16, NULL, NULL, i32u8, i32u16, NULL, NULL, u64f32, u64f64, u64f80},     // u64

//     {f32i8, f32i16, f32i32, f32i64, f32u8, f32u16, f32u32, f32u64, NULL, f32f64, f32f80}, // f32
//     {f64i8, f64i16, f64i32, f64i64, f64u8, f64u16, f64u32, f64u64, f64f32, NULL, f64f80}, // f64
//     {f80i8, f80i16, f80i32, f80i64, f80u8, f80u16, f80u32, f80u64, f80f32, f80f64, NULL}, // f80
// };

static const char *const cast_table[13][13] = /* clang-format off */ {
  // i8    i16      i32      i64      u8      u16      u32      u64      f32      f64      f80      i128      u128
  {NULL,   NULL,    NULL,    i32i64,  i32u8,  i32u16,  NULL,    i32i64,  i32f32,  i32f64,  i32f80,  i32i128, i32i128}, // i8
  {i32i8,  NULL,    NULL,    i32i64,  i32u8,  i32u16,  NULL,    i32i64,  i32f32,  i32f64,  i32f80,  i32i128, i32i128}, // i16
  {i32i8,  i32i16,  NULL,    i32i64,  i32u8,  i32u16,  NULL,    i32i64,  i32f32,  i32f64,  i32f80,  i32i128, i32i128}, // i32
  {i32i8,  i32i16,  NULL,    NULL,    i32u8,  i32u16,  NULL,    NULL,    i64f32,  i64f64,  i64f80,  i64i128, i64i128}, // i64
  {i32i8,  NULL,    NULL,    i32i64,  NULL,   NULL,    NULL,    i32i64,  i32f32,  i32f64,  i32f80,  i32i128, i32i128}, // u8
  {i32i8,  i32i16,  NULL,    i32i64,  i32u8,  NULL,    NULL,    i32i64,  i32f32,  i32f64,  i32f80,  i32i128, i32i128}, // u16
  {i32i8,  i32i16,  NULL,    u32i64,  i32u8,  i32u16,  NULL,    u32i64,  u32f32,  u32f64,  u32f80,  u32i128, i32i128}, // u32
  {i32i8,  i32i16,  NULL,    NULL,    i32u8,  i32u16,  NULL,    NULL,    u64f32,  u64f64,  u64f80,  u64i128, u64i128}, // u64
  {f32i8,  f32i16,  f32i32,  f32i64,  f32u8,  f32u16,  f32u32,  f32u64,  NULL,    f32f64,  f32f80,  f32i128, f32u128}, // f32
  {f64i8,  f64i16,  f64i32,  f64i64,  f64u8,  f64u16,  f64u32,  f64u64,  f64f32,  NULL,    f64f80,  f64i128, f64u128}, // f64
  {f80i8,  f80i16,  f80i32,  f80i64,  f80u8,  f80u16,  f80u32,  f80u64,  f80f32,  f80f64,  NULL,    f80i128, f80u128}, // f80
  {i32i8,  i32i16,  NULL,    NULL,    i32u8,  i32u16,  NULL,    NULL,    i128f32, i128f64, i128f80, NULL,    NULL   }, // i128
  {i32i8,  i32i16,  NULL,    NULL,    i32u8,  i32u16,  NULL,    NULL,    u128f32, u128f64, u128f80, NULL,    NULL   }, // u128
} /* clang-format on */;

static void cast(Type *from, Type *to)
{
  if (to->kind == TY_VOID)
    return;

  if (to->kind == TY_BOOL)
  {
    cmp_zero(from);
    println("  setne %%al");
    println("  movzx %%al, %%eax");
    return;
  }

  int t1 = getTypeId(from);
  int t2 = getTypeId(to);

  if (cast_table[t1][t2])
    println("  %s", cast_table[t1][t2]);
}

// Structs or unions equal or smaller than 16 bytes are passed
// using up to two registers.
//
// If the first 8 bytes contains only floating-point type members,
// they are passed in an XMM register. Otherwise, they are passed
// in a general-purpose register.
//
// If a struct/union is larger than 8 bytes, the same rule is
// applied to the the next 8 byte chunk.
//
// This function returns true if `ty` has only floating-point
// members in its byte range [lo, hi).
static bool has_flonum(Type *ty, int lo, int hi, int offset)
{


  if (ty->kind == TY_STRUCT || ty->kind == TY_UNION)
  {
    for (Member *mem = ty->members; mem; mem = mem->next)
      if (!has_flonum(mem->ty, lo, hi, offset + mem->offset))
        return false;
    return true;
  }

  if (ty->kind == TY_ARRAY)
  {
    for (int i = 0; i < ty->array_len; i++)
      if (!has_flonum(ty->base, lo, hi, offset + ty->base->size * i))
        return false;
    return true;
  }

  return offset < lo || hi <= offset || ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE;
}

static bool has_flonum1(Type *ty)
{
  return has_flonum(ty, 0, 8, 0);
}

static bool has_flonum2(Type *ty)
{
  return has_flonum(ty, 8, 16, 0);
}


// static void push_struct(Type *ty) {
//     // Align the size of the structure to the maximum of 8 or its alignment
//     int sz = align_to(ty->size, MAX(8, ty->align));
//     println("  sub $%d, %%rsp", sz);
//     depth += sz / 8;
//     // Copy the structure data from the source address (in rax) to the stack
//     // Copy 8 bytes at a time, if possible
//     for (int i = 0; i < ty->size; i += 8) {
//         if (ty->size - i >= 8) {
//             // Copy 8 bytes
//             println("  mov %d(%%rax), %%r10", i);
//             println("  mov %%r10, %d(%%rsp)", i);
//         } else {
//             // If the remaining bytes are less than 8, copy them byte by byte
//             for (int j = 0; j < ty->size - i; j++) {
//                 println("  mov %d(%%rax), %%r10b", i + j);
//                 println("  mov %%r10b, %d(%%rsp)", i + j);
//             }
//         }
//   }
// }

static bool pass_by_reg(Type *ty, int gp, int fp) {
  if (ty->size > 16)
    return false;

  int fp_inc = has_flonum1(ty) + (ty->size > 8 && has_flonum2(ty));
  int gp_inc = !has_flonum1(ty) + (ty->size > 8 && !has_flonum2(ty));

  if (fp_inc && (fp + fp_inc > FP_MAX))
    return false;
  if (gp_inc && (gp + gp_inc > GP_MAX))
    return false;

  return true;
}

static void push_struct(Type *ty) {
  int sz = align_to(ty->size, 8);
  println("  sub $%d, %%rsp", sz);
  depth += sz / 8;

  for (int i = 0; i < ty->size; i++) {
    println("  mov %d(%%rax), %%r10b", i);
    println("  mov %%r10b, %d(%%rsp)", i);
  }
}


static void push_args2(Node *args, bool first_pass)
{
  if (!args)
    return;
  push_args2(args->next, first_pass);

  // if ((first_pass && !args->pass_by_stack) || (!first_pass && args->pass_by_stack))
  if (first_pass != args->pass_by_stack)
    return;

  gen_expr(args);

  switch (args->ty->kind)
  {

  case TY_STRUCT:
  case TY_UNION:
    push_struct(args->ty);
    break;
  case TY_FLOAT:
  case TY_DOUBLE:
    pushf(args->ty);
    break;
  case TY_LDOUBLE:
    println("  sub $16, %%rsp");
    println("  fstpt (%%rsp)");
    depth += 2;
    break;
  case TY_INT128:
    push2();
    // Handle 128-bit integer arguments
    // println("  sub $16, %%rsp");  // Allocate 16 bytes on the stack
    // println("  mov %%rax, (%%rsp)");  // Store lower 64 bits
    // println("  mov %%rdx, 8(%%rsp)"); // Store upper 64 bits
    // depth += 2;      
    break;
  default:
    push();
  }
  if (args->realign_stack) {
    pushreg("rbx");
  }

    //   if (args->realign_stack) {
    //     // Save the current stack pointer and align it
    //     //pushreg("rbx");                  // Save current stack pointer
    //     println("  mov %%rsp, %%rbx");   // Save the current stack pointer in RBX
    //     println("  and $-16, %%rsp");     // Align the stack pointer to a 16-byte boundary
    //     println("  sub $16, %%rsp");      // Allocate space for local variables
    // }
}

// Load function call arguments. Arguments are already evaluated and
// stored to the stack as local variables. What we need to do in this
// function is to load them to registers or push them to the stack as
// specified by the x86-64 psABI. Here is what the spec says:
//
// - Up to 6 arguments of integral type are passed using RDI, RSI,
//   RDX, RCX, R8 and R9.
//
// - Up to 8 arguments of floating-point type are passed using XMM0 to
//   XMM7.
//
// - If all registers of an appropriate type are already used, push an
//   argument to the stack in the right-to-left order.
//
// - Each argument passed on the stack takes 8 bytes, and the end of
//   the argument area must be aligned to a 16 byte boundary.
//
// - If a function is variadic, set the number of floating-point type
//   arguments to RAX.
static int push_args(Node *node)
{
  int stack = 0, gp = 0, fp = 0;

  // If the return type is a large struct/union, the caller passes
  // a pointer to a buffer as if it were the first argument.
  if (node->ret_buffer && node->ty->size > 16 )
    gp++;

  
  // Load as many arguments to the registers as possible.
  for (Node *arg = node->args; arg; arg = arg->next)
  {
    Type *ty = arg->ty;

    switch (ty->kind)
    {
    case TY_STRUCT:
    case TY_UNION:
      if (pass_by_reg(ty, gp, fp)) {
          fp += has_flonum1(ty) + (ty->size > 8 && has_flonum2(ty));
          gp += !has_flonum1(ty) + (ty->size > 8 && !has_flonum2(ty));
        } else {
          arg->pass_by_stack = true;
          stack += align_to(ty->size, 8) / 8;
        }
        break;    
      // if (ty->size > 16)
      // {
      //   arg->pass_by_stack = true;
      //   stack += align_to(ty->size, 8) / 8;
      // }
      // else
      // {
      //   bool fp1 = has_flonum1(ty);
      //   bool fp2 = has_flonum2(ty);

      //   if (fp + fp1 + fp2 < FP_MAX && gp + !fp1 + !fp2 < GP_MAX)
      //   {
      //     fp = fp + fp1 + fp2;
      //     gp = gp + !fp1 + !fp2;
      //   }
      //   else
      //   {
      //     arg->pass_by_stack = true;
      //     stack += align_to(ty->size, 8) / 8;
      //   }
      // }

      // break;
    
    case TY_FLOAT:
    case TY_DOUBLE:
      if (fp++ >= FP_MAX)
      {
        arg->pass_by_stack = true;
        stack++;
      }
      break;
    case TY_LDOUBLE:
      arg->pass_by_stack = true;
      stack += 2;
      break;
    case TY_INT128:
      if (gp + 1 >= GP_MAX) {
        if (stack & 1) {
          arg->realign_stack = true;
          ++stack;
        }
        arg->pass_by_stack = true;
        stack += 2;
      } else {
        gp += 2;
      }
      break;
    default:
      if (gp++ >= GP_MAX)
      {
        arg->pass_by_stack = true;
        stack++;
      }
    }
  }
  
  if ((depth + stack) % 2 == 1)
  {
    println("  sub $8, %%rsp");
    depth++;
    stack++;
  }

  push_args2(node->args, true);
  push_args2(node->args, false);

  // If the return type is a large struct/union, the caller passes
  // a pointer to a buffer as if it were the first argument.
  if (node->ret_buffer && node->ty->size > 16)
  {
    println("  lea %d(%%rbp), %%rax", node->ret_buffer->offset);
    push();
  }

  return stack;
}


// static void copy_ret_buffer(Obj *var)
// {
//   Type *ty = var->ty;
//   int gp = 0, fp = 0;

//   if (has_flonum1(ty))
//   {
//     assert(ty->size == 4 || ty->size == 8);
//     if (ty->size == 4)
//             println("  movss %%xmm0, %d(%%rbp)", var->offset);  // Handle float (4 bytes)
//     else
//             println("  movsd %%xmm0, %d(%%rbp)", var->offset);  // Handle double (8 bytes)
//     fp++;
//   }
//   else
//   {
//         // **Change 1: Handle the first 8 bytes for integer types (up to 64 bits)**
//     for (int i = 0; i < MIN(8, ty->size); i++)
//     {
//       println("  mov %%al, %d(%%rbp)", var->offset + i);
//       println("  shr $8, %%rax");
//     }
//     gp++;
//   }

//     // **Change 2: Handle the remaining bytes (for __int128, this covers bytes 9-16)**
//   if (ty->size > 8)
//   {
//     if (has_flonum2(ty))
//     {
//       assert(ty->size == 12 || ty->size == 16);
//       if (ty->size == 12)
//                 println("  movss %%xmm%d, %d(%%rbp)", fp, var->offset + 8);  // Handle 12 bytes floating-point case
//       else
//                 println("  movsd %%xmm%d, %d(%%rbp)", fp, var->offset + 8);  // Handle 16 bytes floating-point case
//     }
//     else
//     {
//             // **Change 3: Use %dl and %rdx for the second 8 bytes (bytes 9-16)**
//       char *reg1 = (gp == 0) ? "%al" : "%dl";
//       char *reg2 = (gp == 0) ? "%rax" : "%rdx";

//       for (int i = 8; i < MIN(16, ty->size); i++)
//       {
//         println("  mov %s, %d(%%rbp)", reg1, var->offset + i);
//         println("  shr $8, %s", reg2);
//       }
//     }
//   }
// }

static void copy_ret_buffer(Obj *var)
{
    Type *ty = var->ty;
    int gp = 0, fp = 0;

    if (has_flonum1(ty)) {

        // Allow sizes 4, 8, 12, and 16 for floating-point types
        assert(ty->size == 4 || ty->size == 8 || ty->size == 12 || ty->size == 16);

        if (ty->size == 4) {
            println("  movss %%xmm0, %d(%%rbp)", var->offset);  // Handle float (4 bytes)
        } else if (ty->size == 8) {
            println("  movsd %%xmm0, %d(%%rbp)", var->offset);  // Handle double (8 bytes)
        } else if (ty->size == 12 || ty->size == 16) {
            // Split the 12 or 16 bytes into two parts, handle the first 8 bytes
            println("  movsd %%xmm0, %d(%%rbp)", var->offset);  // Handle first 8 bytes
            // Handle the remaining bytes (4 or 8 bytes)
            if (ty->size == 12) {
                println("  movss %%xmm1, %d(%%rbp)", var->offset + 8);  // Handle the remaining 4 bytes
            } else if (ty->size == 16) {
                println("  movsd %%xmm1, %d(%%rbp)", var->offset + 8);  // Handle the remaining 8 bytes
            }
        }
        fp++;
    } else {
        // **Change 1: Handle the first 8 bytes for integer types (up to 64 bits)**
        for (int i = 0; i < MIN(8, ty->size); i++) {
            println("  mov %%al, %d(%%rbp)", var->offset + i);
            println("  shr $8, %%rax");
        }
        gp++;
    }

    // **Change 2: Handle the remaining bytes (for __int128, this covers bytes 9-16)**
    if (ty->size > 8) {
        if (has_flonum2(ty)) {
            assert(ty->size == 12 || ty->size == 16);
            if (ty->size == 12) {
                println("  movss %%xmm%d, %d(%%rbp)", fp, var->offset + 8);  // Handle 12 bytes floating-point case
            } else {
                println("  movsd %%xmm%d, %d(%%rbp)", fp, var->offset + 8);  // Handle 16 bytes floating-point case
            }
        } else {
            // **Change 3: Use %dl and %rdx for the second 8 bytes (bytes 9-16)**
            char *reg1 = (gp == 0) ? "%al" : "%dl";
            char *reg2 = (gp == 0) ? "%rax" : "%rdx";

            for (int i = 8; i < MIN(16, ty->size); i++) {
                println("  mov %s, %d(%%rbp)", reg1, var->offset + i);
                println("  shr $8, %s", reg2);
            }
        }
    }
}


static void copy_struct_reg(void)
{
  Type *ty = current_fn->ty->return_ty;
  int gp = 0, fp = 0;

  println("  mov %%rax, %%rdi");

  if (has_flonum(ty, 0, 8, 0))
  {
    assert(ty->size == 4 || 8 <= ty->size);
    if (ty->size == 4)
      println("  movss (%%rdi), %%xmm0");
    else
      println("  movsd (%%rdi), %%xmm0");
    fp++;
  }
  else
  {
    println("  mov $0, %%rax");
    for (int i = MIN(8, ty->size) - 1; i >= 0; i--)
    {
      println("  shl $8, %%rax");
      println("  mov %d(%%rdi), %%al", i);
    }
    gp++;
  }

  if (ty->size > 8)
  {
    if (has_flonum(ty, 8, 16, 0))
    {
      assert(ty->size == 12 || ty->size == 16);
      if (ty->size == 12)
        println("  movss 8(%%rdi), %%xmm%d", fp);
      else
        println("  movsd 8(%%rdi), %%xmm%d", fp);
    }
    else
    {
      char *reg1 = (gp == 0) ? "%al" : "%dl";
      char *reg2 = (gp == 0) ? "%rax" : "%rdx";
      println("  mov $0, %s", reg2);
      for (int i = MIN(16, ty->size) - 1; i >= 8; i--)
      {
        println("  shl $8, %s", reg2);
        println("  mov %d(%%rdi), %s", i, reg1);
      }
    }
  }
}

static void copy_struct_mem(void)
{
  Type *ty = current_fn->ty->return_ty;
  Obj *var = current_fn->params;

  println("  mov %d(%%rbp), %%rdi", var->offset);

  for (int i = 0; i < ty->size; i++)
  {
    println("  mov %d(%%rax), %%dl", i);
    println("  mov %%dl, %d(%%rdi)", i);
  }
  //from @fuhsnn Copy returned-by-stack aggregate's pointer to rax
  println("  mov %%rdi, %%rax");
}

static void builtin_alloca(void)
{
  // Align size to 16 bytes.
  println("  add $15, %%rdi");
  println("  and $0xfffffff0, %%edi");

  // Shift the temporary area by %rdi.
  println("  mov %d(%%rbp), %%rcx", current_fn->alloca_bottom->offset);
  println("  sub %%rsp, %%rcx");
  println("  mov %%rsp, %%rax");
  println("  sub %%rdi, %%rsp");
  println("  mov %%rsp, %%rdx");
  println("1:");
  println("  cmp $0, %%rcx");
  println("  je 2f");
  println("  mov (%%rax), %%r8b");
  println("  mov %%r8b, (%%rdx)");
  println("  inc %%rdx");
  println("  inc %%rax");
  println("  dec %%rcx");
  println("  jmp 1b");
  println("2:");

  // Move alloca_bottom pointer.
  println("  mov %d(%%rbp), %%rax", current_fn->alloca_bottom->offset);
  println("  sub %%rdi, %%rax");
  println("  mov %%rax, %d(%%rbp)", current_fn->alloca_bottom->offset);
}


//from cosmopolitan
static void HandleAtomicArithmetic(Node *node, const char *op) {
  gen_expr(node->lhs);
  push();
  gen_expr(node->rhs);
  pop("%r9");
  println("\tmov\t%s,%s", reg_ax(node->ty->size), reg_si(node->ty->size));
  println("\tmov\t(%%r9),%s", reg_ax(node->ty->size));
  println("1:\tmov\t%s,%s", reg_ax(node->ty->size), reg_dx(node->ty->size));
  println("\tmov\t%s,%s", reg_ax(node->ty->size), reg_di(node->ty->size));
  println("\t%s\t%s,%s", op, reg_si(node->ty->size), reg_dx(node->ty->size));
  println("\tlock cmpxchg\t%s,(%%r9)", reg_dx(node->ty->size));
  println("\tjnz\t1b");
  println("\tmov\t%s,%s", reg_di(node->ty->size), reg_ax(node->ty->size));
}


// Generate code for a given node.
static void gen_expr(Node *node)
{
  if (node->tok->line_no != last_loc_line) {
        println("  .loc %d %u", node->tok->file->file_no, node->tok->line_no);
        last_loc_line = node->tok->line_no;
    }

  //println("  .loc %d %u", node->tok->file->file_no, node->tok->line_no);

  switch (node->kind)
  {
  case ND_NULL_EXPR:
    return;
  case ND_NUM:
  {
    switch (node->ty->kind)
    {

    case TY_INT128:
    {
        // Extract the 128-bit integer value into high and low 64-bit parts
        __int128 val = node->val;

        uint64_t low = (uint64_t)val;
        uint64_t high = (uint64_t)(val >> 64);
        println("  mov $%lu, %%rax  # low 64 bits", low);
        println("  mov $%lu, %%rdx  # high 64 bits", high);

        return;
    }
    case TY_FLOAT:
    {
      union
      {
        float f32;
        uint32_t u32;
      } u = {node->fval};
      println("  mov $%u, %%eax  # float %Lf", u.u32, node->fval);
      println("  movq %%rax, %%xmm0");
      return;
    }
    case TY_DOUBLE:
    {
      union
      {
        double f64;
        uint64_t u64;
      } u = {node->fval};
      println("  mov $%lu, %%rax  # double %Lf", u.u64, node->fval);
      println("  movq %%rax, %%xmm0");
      return;
    }
    case TY_LDOUBLE:
    {
      union
      {
        long double f80;
        uint64_t u64[2];
      } u;
      memset(&u, 0, sizeof(u));
      u.f80 = node->fval;
      println("  mov $%lu, %%rax  # long double %Lf", u.u64[0], node->fval);
      println("  mov %%rax, -16(%%rsp)");
      println("  mov $%lu, %%rax", u.u64[1]);
      println("  mov %%rax, -8(%%rsp)");
      println("  fldt -16(%%rsp)");
      return;
    }
    }

    println("  mov $%ld, %%rax", node->val);
    return;
  }
  case ND_NEG:
    gen_expr(node->lhs);

    switch (node->ty->kind)
    {
    case TY_FLOAT:
      println("  mov $1, %%rax");
      println("  shl $31, %%rax");
      println("  movq %%rax, %%xmm1");
      if (node->ty->vector_size == 16) {
        println("  pshufd $0, %%xmm1");
      }
      println("  xorps %%xmm1, %%xmm0");
      return;
    case TY_DOUBLE:
      println("  mov $1, %%rax");
      println("  shl $63, %%rax");
      println("  movq %%rax, %%xmm1");
      if (node->ty->vector_size == 16) {
        println("  pshufd $0b01000100, %%xmm1");
      }      
      println("  xorpd %%xmm1, %%xmm0");
      return;
//  switch (node->ty->kind) {
//     case TY_FLOAT:
//       println("  mov $1, %%rax");
//       println("  shl $31, %%rax");
//       println("  movq %%rax, %%xmm1");

//       // Handle different vector sizes
//       switch (node->ty->vector_size) {
//         case 2:  // 16-bit vectors (2 elements)
//           println("  pshuflw $0, %%xmm1, %%xmm1");
//       println("  xorps %%xmm1, %%xmm0");
//           break;

//         case 4:  // 32-bit vectors (4 elements)
//           println("  pshufd $0, %%xmm1, %%xmm1");
//           println("  xorps %%xmm1, %%xmm0");
//           break;

//         case 8:  // 64-bit vectors (8 elements)
//           println("  movaps %%xmm1, %%xmm2");
//           println("  punpckldq %%xmm1, %%xmm2");
//           println("  xorps %%xmm2, %%xmm0");
//           break;

//         case 16: // 128-bit vectors (4 elements, similar to 32-bit vectors)
//           println("  pshufd $0, %%xmm1, %%xmm1");
//           println("  xorps %%xmm1, %%xmm0");
//           break;

//         default: // Scalar float
//           println("  xorps %%xmm1, %%xmm0");
//           break;
//       }
//       return;

    // case TY_DOUBLE:
    //   println("  mov $1, %%rax");
    //   println("  shl $63, %%rax");
    //   println("  movq %%rax, %%xmm1");

    //   // Handle different vector sizes
    //   switch (node->ty->vector_size) {
    //     case 2:  // 16-bit vectors (2 elements)
    //       println("  punpcklqdq %%xmm1, %%xmm1");
    //   println("  xorpd %%xmm1, %%xmm0");
    //       break;

    //     case 4:  // 32-bit vectors (4 elements)
    //       println("  pshufd $0b01000100, %%xmm1, %%xmm1");
    //       println("  xorpd %%xmm1, %%xmm0");
    //       break;

    //     case 8:  // 64-bit vectors (2 elements, similar to 128-bit vectors but only 2 elements)
    //       println("  punpcklqdq %%xmm1, %%xmm1");
    //       println("  xorpd %%xmm1, %%xmm0");
    //       break;

    //     case 16: // 128-bit vectors (2 elements, similar to 64-bit vectors)
    //       println("  pshufd $0b01000100, %%xmm1, %%xmm1");
    //       println("  xorpd %%xmm1, %%xmm0");
    //       break;

    //     default: // Scalar double
    //       println("  xorpd %%xmm1, %%xmm0");
    //       break;
    //   }
    //   return;

    case TY_LDOUBLE:
      println("  fchs");
      return;
    case TY_INT128:
      println("  neg %%rax");
      println("  adc $0, %%rdx");
      println("  neg %%rdx");
      return;
    }

    println("  neg %%rax");
    return;
  case ND_VAR:
    gen_addr(node);
    load(node->ty);
    return;
  case ND_MEMBER:
  {
    gen_addr(node);
    load(node->ty);

    Member *mem = node->member;
    if (mem->is_bitfield)
    {
      //from @fuhsnn bitfield boolean returned -1 instead of 1
      if (mem->ty->kind == TY_BOOL) {
        println("  shr $%d, %%rax", mem->bit_offset);
        println("  and $1, %%eax");
        return;
      }
      println("  shl $%d, %%rax", 64 - mem->bit_width - mem->bit_offset);
      if (mem->ty->is_unsigned)
        println("  shr $%d, %%rax", 64 - mem->bit_width);
      else
        println("  sar $%d, %%rax", 64 - mem->bit_width);
    }
    return;
  }
  case ND_DEREF:
    gen_expr(node->lhs);
    load(node->ty);
    return;
  case ND_ADDR:
    gen_addr(node->lhs);
    return;
  case ND_ASSIGN:
    gen_addr(node->lhs);
    push();
    gen_expr(node->rhs);

    if (node->lhs->kind == ND_MEMBER && node->lhs->member->is_bitfield)
    {
      println("  mov %%rax, %%r8");

      // If the lhs is a bitfield, we need to read the current value
      // from memory and merge it with a new value.
      Member *mem = node->lhs->member;
      println("  mov %%rax, %%rdi");
      if (mem->bit_width >= 32)
      {
        println("  mov $%ld, %%rax", (1L << mem->bit_width) - 1);
        println("  and %%rax, %%rdi");
      }
      else
      {
        println("  and $%ld, %%rdi", (1L << mem->bit_width) - 1);
      }
      // println("  and $%ld, %%rdi", (1L << mem->bit_width) - 1);
      println("  shl $%d, %%rdi", mem->bit_offset);

      println("  mov (%%rsp), %%rax");
      load(mem->ty);

      long mask = ((1L << mem->bit_width) - 1) << mem->bit_offset;
      println("  mov $%ld, %%r9", ~mask);
      println("  and %%r9, %%rax");
      println("  or %%rdi, %%rax");
      store(node->ty);
      println("  mov %%r8, %%rax");
      return;
    }


    store(node->ty);
    return;
  case ND_STMT_EXPR:
    for (Node *n = node->body; n; n = n->next)
      gen_stmt(n);
    return;
  case ND_COMMA:
    gen_expr(node->lhs);
    gen_expr(node->rhs);
    return;
  case ND_CAST:
    gen_expr(node->lhs);
    cast(node->lhs->ty, node->ty);
    return;
  case ND_MEMZERO:
    // `rep stosb` is equivalent to `memset(%rdi, %al, %rcx)`.
    println("  mov $%d, %%rcx", node->var->ty->size);
    println("  lea %d(%%rbp), %%rdi", node->var->offset);
    println("  mov $0, %%al");
    println("  rep stosb");
    return;
  case ND_COND:
  {
    int c = count();
    gen_expr(node->cond);
    cmp_zero(node->cond->ty);
    println("  je .L.else.%d", c);
    gen_expr(node->then);
    println("  jmp .L.end.%d", c);
    println(".L.else.%d:", c);
    gen_expr(node->els);
    println(".L.end.%d:", c);
    return;
  }
  case ND_NOT:
    gen_expr(node->lhs);
    cmp_zero(node->lhs->ty);
    println("  sete %%al");
    println("  movzx %%al, %%rax");
    return;
  // case ND_BITNOT:
  //   gen_expr(node->lhs);
  //     if (node->lhs->ty->kind == TY_INT128) {
  //       println("  not %%rax");
  //       println("  not %%rdx");
  //     } else if (node->lhs->ty->vector_size == 16) {
  //       println("  pcmpeqd %%xmm1, %%xmm1");
  //       println("  pxor %%xmm1, %%xmm0");
  //     } else {
  //       println("  not %%rax");
  //     }
  //   return;
  case ND_BITNOT:
    gen_expr(node->lhs);

  if (node->lhs->ty->kind == TY_INT128) {
    // Handle 128-bit integers
    println("  not %%rax");
    println("  not %%rdx");
  } else {
    // Handle scalar integers (non-vector, non-INT128)
    println("  not %%rax");
  }
    return;


  case ND_LOGAND:
  {
    int c = count();
    gen_expr(node->lhs);
    cmp_zero(node->lhs->ty);
    println("  je .L.false.%d", c);
    gen_expr(node->rhs);
    cmp_zero(node->rhs->ty);
    println("  je .L.false.%d", c);
    println("  mov $1, %%rax");
    println("  jmp .L.end.%d", c);
    println(".L.false.%d:", c);
    println("  mov $0, %%rax");
    println(".L.end.%d:", c);
    return;
  }
  case ND_LOGOR:
  {
    int c = count();
    gen_expr(node->lhs);
    cmp_zero(node->lhs->ty);
    println("  jne .L.true.%d", c);
    gen_expr(node->rhs);
    cmp_zero(node->rhs->ty);
    println("  jne .L.true.%d", c);
    println("  mov $0, %%rax");
    println("  jmp .L.end.%d", c);
    println(".L.true.%d:", c);
    println("  mov $1, %%rax");
    println(".L.end.%d:", c);
    return;
  }
  case ND_FUNCALL:
  {
    if (node->lhs->kind == ND_VAR && !strcmp(node->lhs->var->name, "alloca"))
    {
      gen_expr(node->args);
      println("  mov %%rax, %%rdi");
      builtin_alloca();
      return;
    }

    int stack_args = push_args(node);
    gen_expr(node->lhs);

    int gp = 0, fp = 0;

    // If the return type is a large struct/union, the caller passes
    // a pointer to a buffer as if it were the first argument.
    if (node->ret_buffer && node->ty->size > 16)
      pop(argreg64[gp++]);

    for (Node *arg = node->args; arg; arg = arg->next)
    {
      Type *ty = arg->ty;

      switch (ty->kind)
      {
      case TY_STRUCT:
      case TY_UNION:
          if (!pass_by_reg(ty, gp, fp))
          continue;

        if (has_flonum1(ty))
          popf(ty, fp++);
        else
          pop(argreg64[gp++]);

        if (ty->size > 8) {
          if (has_flonum2(ty))
            popf(ty, fp++);
          else
            pop(argreg64[gp++]);
        }
        break;
        // if (ty->size > 16)
        //   continue;

        // bool fp1 = has_flonum1(ty);
        // bool fp2 = has_flonum2(ty);

        // if (fp + fp1 + fp2 < FP_MAX && gp + !fp1 + !fp2 < GP_MAX)
        // {
        //   if (fp1)
        //     popf(ty, fp++);
        //   else
        //     pop(argreg64[gp++]);

        //   if (ty->size > 8)
        //   {
        //     if (fp2)
        //       popf(ty, fp++);
        //     else
        //       pop(argreg64[gp++]);
        //   }
        // }
        // break;
      case TY_FLOAT:
      case TY_DOUBLE:
        if (fp < FP_MAX)
          popf(ty, fp++);
        break;
      case TY_LDOUBLE:
        break;
      case TY_INT128:
        if (gp + 1 < GP_MAX) {
          int a = gp++;
          int b = gp++;
          pop2(argreg64[a], argreg64[b]);
        }
        break;
      default:
        if (gp < GP_MAX)
          pop(argreg64[gp++]);
      }
    }



    // Function call
    println("  mov %%rax, %%r10");
    println("  mov $%d, %%rax", fp);
    println("  call *%%r10");
    println("  add $%d, %%rsp", stack_args * 8);

    depth -= stack_args;

    // It looks like the most significant 48 or 56 bits in RAX may
    // contain garbage if a function return type is short or bool/char,
    // respectively. We clear the upper bits here.
    switch (node->ty->kind)
    {
    case TY_BOOL:
      println("  movzx %%al, %%eax");
      return;
    case TY_CHAR:
      if (node->ty->is_unsigned)
        println("  movzbl %%al, %%eax");
      else
        println("  movsbl %%al, %%eax");
      return;
    case TY_SHORT:
      if (node->ty->is_unsigned)
        println("  movzwl %%ax, %%eax");
      else
        println("  movswl %%ax, %%eax");
      return;
    }

    // If the return type is a small struct, a value is returned
    // using up to two registers.
    if (node->ret_buffer && node->ty->size <= 16)
    {
      copy_ret_buffer(node->ret_buffer);
      println("  lea %d(%%rbp), %%rax", node->ret_buffer->offset);
    }

    return;
  }
  case ND_LABEL_VAL:
    println("  lea %s(%%rip), %%rax", node->unique_label);
    return;
  case ND_CAS:
  {
    gen_expr(node->cas_addr);
    push();
    gen_expr(node->cas_new);
    push();
    gen_expr(node->cas_old);
    println("  mov %%rax, %%r8");
    load(node->cas_old->ty->base);
    pop("%rdx"); // new
    pop("%rdi"); // addr

    int sz = node->cas_addr->ty->base->size;
    println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));
    println("  sete %%cl");
    println("  je 1f");
    println("  mov %s, (%%r8)", reg_ax(sz));
    println("1:");
    println("  movzbl %%cl, %%eax");
    return;
  }
  case ND_CAS_N: {
    // Generate code to evaluate and push the address
    gen_expr(node->cas_addr); // Address
    push();
    
    // Generate code to evaluate and push the new value
    gen_expr(node->cas_new);  // New value
    push();
    
    // Generate code to evaluate and push the old value
    gen_expr(node->cas_old);  // Old value

    // Move the old value to r8 to preserve it
    println("  mov %%rax, %%r8"); 

    // Pop the new value and address from the stack
    pop("%rdx"); // New value in rdx
    pop("%rdi"); // Address in rdi

    // Determine the size of the data type
    int sz = node->cas_addr->ty->base->size;

    // Perform the atomic compare-and-swap operation
    println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz)); 

    // After cmpxchg, rax contains the old value (before the swap)
    // Restore the preserved old value to rax
    println("  mov %%r8, %%rax"); 

    return;
  }
  case ND_SYNC: {
    println("  mfence"); // x86-64 instruction for full memory barrier
    return;
  }
  case ND_BUILTIN_MEMCPY: {
    if (opt_fbuiltin) {
      // Generate code to evaluate the destination address
      gen_expr(node->builtin_dest);
      push();
      println("  mov %%rax, %%rdi"); // Destination in RDI

      // Generate code to evaluate the source address
      gen_expr(node->builtin_src);
      push();
      println("  mov %%rax, %%rsi"); // Source in RSI
      // Generate code to evaluate the size
      gen_expr(node->builtin_size);
      push();
      println("  mov %%rax, %%rcx"); // Size in RCX

      // Call the memcpy function
      println("  rep movsb");
      // Pop the stack to balance pushes
      pop("%rcx");
      pop("%rsi");
      pop("%rdi");
    }
    else {
      // Handle the case when built-in functions are disabled
      // You might want to call an external `memcpy` function here
    // Generate code for destination pointer
    gen_expr(node->builtin_dest); 
    push();
    
    // Generate code for source pointer
    gen_expr(node->builtin_src);  
    push();
    
    // Generate code for size
    gen_expr(node->builtin_size); 
    push();

    // Make the call to memcpy
    println("  call memcpy");

    // Restore the stack
    pop("%rdx"); // size
    pop("%rsi"); // source
    pop("%rdi"); // destination
    
    }
    return;   
  }

  case ND_BUILTIN_MEMSET: {
    // Generate code for destination, value, and size
    gen_expr(node->builtin_dest);
    push();
    gen_expr(node->builtin_val);
    push();
    gen_expr(node->builtin_size);
    push();

    // Move the arguments to the appropriate registers
    pop("%rcx");  // size
    pop("%rsi");  // value
    pop("%rdi");  // destination

    // Move the value to the lower 8-bit register
    println("  mov %%sil, %%al");  // Move the lower 8 bits of RSI to AL
    println("  rep stosb");        // Use REP STOSB to set memory

    return;
  }
  case ND_BUILTIN_CLZ: {
    gen_expr(node->builtin_val); // Generate code for the expression
    println("  bsr %%eax, %%eax"); // Bit Scan Reverse to find the highest set bit
    println("  xor $31, %%eax"); // Count leading zeros
    return;
  }
  case ND_BUILTIN_CLZLL:
  case ND_BUILTIN_CLZL: {
    gen_expr(node->builtin_val); // Generate code for the expression
    println("  bsr %%rax, %%rax");       // Calculate number of leading zeros for 64-bit
    println("  xor $63, %%eax");       // Special handling if input was -1

    return;
  }
  case ND_BUILTIN_CTZ: {
    gen_expr(node->builtin_val); // Generate code for the expression
    println("  bsf %%eax, %%eax"); // Bit Scan Forward to find the lowest set bit
    return;
  }
  case ND_BUILTIN_CTZLL:
  case ND_BUILTIN_CTZL: {
    gen_expr(node->builtin_val); // Generate code for the expression
    println("  bsf %%rax, %%rax"); // Bit Scan Forward to find the lowest set bit
    return;
  }

  case ND_BUILTIN_BSWAP16: {
      gen_expr(node->builtin_val);  // Generate code for the expression
      println("  mov %%ax, %%dx");  // Move the lower 16 bits of the result into dx
      println("  rol $8, %%dx");    // Rotate the bits in dx by 8 bits to the left
      println("  mov %%dx, %%ax");  // Move the result back into ax
      return;
  }

  case ND_BUILTIN_BSWAP32: {
      gen_expr(node->builtin_val);  // Generate code for the expression
      println("  bswap %%eax");     // Reverse the byte order of the 32-bit value in eax
      return;
  }

  case ND_BUILTIN_BSWAP64: {
      gen_expr(node->builtin_val);  // Generate code for the expression
      println("  bswap %%rax");     // Reverse the byte order of the 64-bit value in rax
      return;
  }  

  case ND_BUILTIN_INFF:
  case ND_BUILTIN_HUGE_VALF: {
      // Loading the bit pattern for positive infinity in 32-bit single precision (float)
      println("  mov $0x7f800000, %%eax");  // Load the bit pattern 0x7f800000 into eax (single precision positive infinity)
      println("  movd %%eax, %%xmm0"); 
      return;
  }

  // For __builtin_huge_val
  case ND_BUILTIN_HUGE_VAL: {
      // Loading the bit pattern for positive infinity in 64-bit double precision
      println("  mov $0x7ff0000000000000, %%rax");  
      println("  movq %%rax, %%xmm0");      
      return;
  }

  // For __builtin_huge_vall
  case ND_BUILTIN_HUGE_VALL: {
    println("  push $0x7f800000"); 
    println("  flds (%%rsp)"); 
    println("  pop %%rax"); 
    return;
  }

  // For __builtin_frame_address
  case ND_BUILTIN_FRAME_ADDRESS: {
    int c = count();  // Unique label counter
    // Get the level argument from the stack
    println("  mov %%rdi, %%rax"); // Move the level argument into rax
    
    // Check if level is 0
    println("  cmp $0, %%rax");
    println("  je .Lframe_address_%d", c);
    
    // For level > 0, we need to follow the frame pointers
    // We will need to move up the stack `level` times
    // Note: The actual implementation depends on how you manage stack frames
    println("  mov %%rbp, %%rcx"); // Move current frame pointer to rcx
    println("  sub $1, %%rax");   // Decrement level (level - 1)
    println(".Lframe_address_loop%d:", c);
    println("  test %%rax, %%rax"); // Check if level == 0
    println("  jz .Lframe_address_done%d", c);
    println("  mov (%%rcx), %%rcx"); // Move up one frame
    println("  sub $1, %%rax"); // Decrement level
    println("  jmp .Lframe_address_loop%d", c);
    println(".Lframe_address_done%d:", c);
    println("  mov %%rcx, %%rax"); // Return the frame pointer

    println(".Lframe_address_%d:", c);
    println("  mov %%rbp, %%rax"); // Return the current frame pointer
    return;
  }

  case ND_POPCOUNT:
    gen_expr(node->builtin_val); // Generate code for the expression
    println("  popcnt %%rax, %%rax"); // Count the number of set bits
    return;

  case ND_EXPECT: {
    // Generate code for the expression we are expecting
    gen_expr(node->lhs); // Generate code for the condition
    push(); // Save the condition result on stack
    gen_expr(node->rhs); // Generate code for the expected value
    pop("%rdi"); // Restore the condition result from stack into %rdi
    // Compare the condition result with the expected value
    println("  cmp %%rax, %%rdi");
    // Move the condition result back to %rax for use in further code
    println("  mov %%rdi, %%rax");
    return;
  }   
  case ND_ABORT: {
    println("  call abort"); 
    return;
  }
  case ND_RETURN_ADDR: {
    // Generate code to get the frame pointer of the current function
    println("  mov %%rbp, %%rax");
    
    // Get the depth of the return address
    int tmpdepth = eval(node->lhs);
    
    // Walk up the stack frames to the correct depth
    for (int i = 0; i < tmpdepth; i++) {
      println("  mov (%%rax), %%rax");
    }
    
    // Load the return address from the frame pointer
    println("  mov 8(%%rax), %%rax");
    return;
  }
  case ND_BUILTIN_ADD_OVERFLOW: {
   int c = count();  // Unique label counter
    Type *ty = node->builtin_dest->ty;  // Get the type of the operands
    if (ty->base)
      ty = ty->base;

    // Evaluate left-hand side and right-hand side expressions
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    push();
    gen_expr(node->builtin_dest);
    push();

    // Load values into registers and perform addition
    pop("%rdx");  // Load address of result variable
    pop("%rsi");  // Load rhs
    pop("%rdi");  // Load lhs

    if (ty->size == 1) {
        println("  mov %%dil, %%al");
        println("  add %%sil, %%al");
        println("  mov %%al, (%%rdx)");
    } else if (ty->size == 2) {
        println("  mov %%di, %%ax");
        println("  add %%si, %%ax");
        println("  mov %%ax, (%%rdx)");
    } else if (ty->size == 4) {
        println("  mov %%edi, %%eax");
        println("  add %%esi, %%eax");
        println("  mov %%eax, (%%rdx)");
    } else {
        println("  mov %%rdi, %%rax");
        println("  add %%rsi, %%rax");
        println("  mov %%rax, (%%rdx)");
    }

    // Check for overflow
    println("  seto %%al");          // Set AL if overflow occurred
    println("  movzx %%al, %%eax");  // Zero-extend AL to EAX

    // Return 0 if no overflow, 1 if overflow
    println("  cmp $0, %%eax");
    println("  jne .Loverflowa%d", c);
    println("  mov $0, %%eax");
    println("  jmp .Lenda%d", c);
    println(".Loverflowa%d:", c);
    println("  mov $1, %%eax");
    println(".Lenda%d:", c);
    return;
  }
  case ND_BUILTIN_SUB_OVERFLOW: {
    int c = count();  // Unique label counter
    Type *ty = node->builtin_dest->ty;  // Get the type of the operands
    if (ty->base)
      ty = ty->base;
    // Evaluate left-hand side and right-hand side expressions
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    push();
    gen_expr(node->builtin_dest);
    push();

    // Load values into registers and perform subtraction
    pop("%rdx");  // Load address of result variable
    pop("%rsi");  // Load rhs
    pop("%rdi");  // Load lhs

    if (ty->size == 1) {
        println("  mov %%dil, %%al");
        println("  sub %%sil, %%al");
        println("  mov %%al, (%%rdx)");
    } else if (ty->size == 2) {
        println("  mov %%di, %%ax");
        println("  sub %%si, %%ax");
        println("  mov %%ax, (%%rdx)");
    } else if (ty->size == 4) {
        println("  mov %%edi, %%eax");
        println("  sub %%esi, %%eax");
        println("  mov %%eax, (%%rdx)");
    } else {
        println("  mov %%rdi, %%rax");
        println("  sub %%rsi, %%rax");
        println("  mov %%rax, (%%rdx)");
    }

    // Check for overflow
    println("  seto %%al");          // Set AL if overflow occurred
    println("  movzx %%al, %%eax");  // Zero-extend AL to EAX

    // Return 0 if no overflow, 1 if overflow
    println("  cmp $0, %%eax");
    println("  jne .Loverflows%d", c);
    println("  mov $0, %%eax");
    println("  jmp .Lends%d", c);
    println(".Loverflows%d:", c);
    println("  mov $1, %%eax");
    println(".Lends%d:", c);
    return;
  }
  case ND_BUILTIN_MUL_OVERFLOW: {
    int c = count();  // Unique label counter
    Type *ty = node->lhs->ty;  // Get the type of the operands
    if (ty->base)
      ty = ty->base;
    int size = ty->size;
    // Evaluate left-hand side and right-hand side expressions
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    push();
    gen_expr(node->builtin_dest);
    push();

    // Load values into registers and perform multiplication
    pop("%rdx");  // Load address of result variable
    pop("%rsi");  // Load rhs
    pop("%rdi");  // Load lhs

    // Determine the suffix and size for the operations
    if (size == 1) {
        // For 8-bit values (char)
        println("  movzbl %%di, %%eax");  // Zero-extend to 32-bit
        println("  movzbl %%si, %%ebx");  // Zero-extend to 32-bit
        println("  imul %%ebx, %%eax");   // Perform 32-bit multiplication
        println("  jo .L.overflowm%d", c);  // Jump if overflow
        println("  mov %%al, (%%rdx)");    // Store result (8-bit)
        println("  mov $0, %%al");       
        println("  jmp .L.donem%d", c);    // Jump to done
    } else if (size == 2) {
        // For 16-bit values (short)
        println("  movzwl %%di, %%eax");  // Zero-extend to 32-bit
        println("  movzwl %%si, %%ebx");  // Zero-extend to 32-bit
        println("  imul %%ebx, %%eax");   // Perform 32-bit multiplication
        println("  jo .L.overflowm%d", c);  // Jump if overflow
        println("  mov %%ax, (%%rdx)");    // Store result (16-bit)
        println("  mov $0, %%ax");       
        println("  jmp .L.donem%d", c);    // Jump to done
    } else if (size == 4) {
        // For 32-bit values (int)
        println("  mov %%edi, %%eax");    // Move to 32-bit
        println("  imul %%esi, %%eax");   // Perform 32-bit multiplication
        println("  jo .L.overflowm%d", c);  // Jump if overflow
        println("  mov %%eax, (%%rdx)");    // Store result (32-bit)
        println("  mov $0, %%eax");       
        println("  jmp .L.donem%d", c);    // Jump to done
    } else if (size == 8) {
        // For 64-bit values (long long)
        println("  mov %%rdi, %%rax");    // Move to 64-bit
        println("  imul %%rsi, %%rax");   // Perform 64-bit multiplication
        println("  jo .L.overflowm%d", c);  // Jump if overflow
        println("  mov %%rax, (%%rdx)");    // Store result (64-bit)
        println("  mov $0, %%rax");       
        println("  jmp .L.donem%d", c);    // Jump to done
    }

    // Overflow handling
    println(".L.overflowm%d:", c);
    println("  mov %%al, (%%rdx)");        // Store result
    println("  mov $1, %%rax");            // Set return value to 1 (overflow detected)
    println(".L.donem%d:", c);

    return;
  }
  case ND_UNREACHABLE:
    println("  // __builtin_unreachable: no code generation needed");
    return;
  
  case ND_BUILTIN_ISNAN: {
    gen_expr(node->builtin_val);  // Generate code for the expression
    if (node->builtin_val->ty->kind == TY_FLOAT) {
        // Use movss to move the float value and then compare
        println("  movss %%xmm0, %%xmm1");
        println("  ucomiss %%xmm1, %%xmm1");
    } else {
        // Use ucomisd for double
        println("  ucomisd %%xmm0, %%xmm0");
    }

    println("  setp %%al");
    println("  movzx %%al, %%eax");
    return;
  }

  
  case ND_EXCH:
  {
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    pop("%rdi");

    int sz = node->lhs->ty->base->size;
    println("  xchg %s, (%%rdi)", reg_ax(sz));
    return;
  }
  case ND_EXCH_N:
  case ND_TESTANDSET: {
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    pop("%rdi");
    println("\txchg\t%s,(%%rdi)", reg_ax(node->ty->size));
    return;
  }
  case ND_TESTANDSETA: {
    gen_expr(node->lhs);
    push();
    println("\tmov\t$1,%%eax");
    pop("%rdi");
    println("\txchg\t%s,(%%rdi)", reg_ax(node->ty->size));
    return;
  }
  case ND_LOAD: {
    gen_expr(node->rhs);
    push();
    gen_expr(node->lhs);
    println("\tmov\t(%%rax),%s", reg_ax(node->ty->size));
    pop("%rdi");
    println("\tmov\t%s,(%%rdi)", reg_ax(node->ty->size));
    return;
  }
  case ND_LOAD_N: {
    gen_expr(node->lhs);
    println("\tmov\t(%%rax),%s", reg_ax(node->ty->size));
    return;
  }
  case ND_STORE: {
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    pop("%rdi");
    println("\tmov\t(%%rax),%s", reg_ax(node->ty->size));
    println("\tmov\t%s,(%%rdi)", reg_ax(node->ty->size));
    if (node->memorder) {
      println("\tmfence");
    }
    return;
  }
  case ND_STORE_N:
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    pop("%rdi");
    println("\tmov\t%s,(%%rdi)", reg_ax(node->ty->size));
    if (node->memorder) {
      println("\tmfence");
    }
    return;
  case ND_CLEAR:
    gen_expr(node->lhs);
    println("\tmov\t%%rax,%%rdi");
    println("\txor\t%%eax,%%eax");
    println("\tmov\t%s,(%%rdi)", reg_ax(node->ty->size));
    if (node->memorder) {
      println("\tmfence");
    }
    return;
  case ND_FETCHADD:
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    pop("%rdi");
    println("\txadd\t%s,(%%rdi)", reg_ax(node->ty->size));
    return;
  case ND_FETCHSUB:
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    pop("%rdi");
    println("\tneg\t%s", reg_ax(node->ty->size));
    println("\txadd\t%s,(%%rdi)", reg_ax(node->ty->size));
    return;
  case ND_FETCHXOR:
    HandleAtomicArithmetic(node, "xor");
    return;
  case ND_FETCHAND:
    HandleAtomicArithmetic(node, "and");
    return;
  case ND_FETCHOR:
    HandleAtomicArithmetic(node, "or");
    return;
  case ND_SUBFETCH:
    gen_expr(node->lhs);
    push();
    gen_expr(node->rhs);
    pop("%rdi");
    push();
    println("\tneg\t%s", reg_ax(node->ty->size));
    println("\txadd\t%s,(%%rdi)", reg_ax(node->ty->size));
    pop("%rdi");
    println("\tsub\t%s,%s", reg_di(node->ty->size), reg_ax(node->ty->size));
    return;
  case ND_RELEASE:
    gen_expr(node->lhs);
    push();
    pop("%rdi");
    println("\txor\t%%eax,%%eax");
    println("\tmov\t%s,(%%rdi)", reg_ax(node->ty->size));
    return;
  case ND_ALLOC:
    // Evaluate the size expression and store the result in RAX
    gen_expr(node->lhs); // Assume size to allocate is in RAX
    // Allocate space on the stack
    println("  mov %%rax, %%rdi"); // Move size to RDI (or appropriate register)
    println("  sub %%rdi, %%rsp"); // Allocate space on the stack
    println("  mov %%rsp, %%rax"); // Store the new stack pointer (allocated memory address) in RAX
    return;
  
  }

  // switch (node->lhs->ty->kind)
  // {
  // case TY_FLOAT:
  // case TY_DOUBLE:
  // {
  //   gen_expr(node->rhs);
  //   pushf(node->rhs->ty);
  //   gen_expr(node->lhs);
  //   popf(node->rhs->ty, 1);

  //   char sz = (node->lhs->ty->kind == TY_FLOAT) ? 's' : 'd';
  //   char ps = (node->lhs->ty->vector_size == 16) ? 'p' : 's';

  //   switch (node->kind)
  //   {
  //   case ND_ADD:
  //     println("  add%c%c %%xmm1, %%xmm0", ps, sz);
  //     return;
  //   case ND_SUB:
  //     println("  sub%c%c %%xmm1, %%xmm0", ps, sz);
  //     return;
  //   case ND_MUL:
  //     println("  mul%c%c %%xmm1, %%xmm0", ps, sz);
  //     return;
  //   case ND_DIV:
  //     println("  div%c%c %%xmm1, %%xmm0", ps, sz);
  //     return;
  //   case ND_EQ:
  //   case ND_NE:
  //   case ND_LT:
  //   case ND_LE:
  //     println("  ucomis%c %%xmm0, %%xmm1", sz);

  //     if (node->kind == ND_EQ)
  //     {
  //       println("  sete %%al");
  //       println("  setnp %%dl");
  //       println("  and %%dl, %%al");
  //     }
  //     else if (node->kind == ND_NE)
  //     {
  //       println("  setne %%al");
  //       println("  setp %%dl");
  //       println("  or %%dl, %%al");
  //     }
  //     else if (node->kind == ND_LT)
  //     {
  //       println("  seta %%al");
  //     }
  //     else
  //     {
  //       println("  setae %%al");
  //     }

  //     println("  and $1, %%al");
  //     println("  movzb %%al, %%rax");
  //     return;
  //   }

  //   error_tok(node->tok, "%s invalid expression", CODEGEN_C);
  // }
  switch (node->lhs->ty->kind) {
  case TY_FLOAT:
  case TY_DOUBLE: {
    gen_expr(node->rhs);
    pushf(node->rhs->ty);
    gen_expr(node->lhs);
    popf(node->rhs->ty, 1);

    char sz = (node->lhs->ty->kind == TY_FLOAT) ? 's' : 'd';
    char ps = 's';

    switch (node->lhs->ty->vector_size) {
      case 2:  // 16-bit vectors
        ps = 'l';  // Use the low-order variant for 16-bit vectors
        break;
      case 4:  // 32-bit vectors
        ps = 's';  // Standard operation for 32-bit vectors
        break;
      case 8:  // 64-bit vectors
        ps = 'q';  // Use quadword operations for 64-bit vectors
        break;
      case 16: // 128-bit vectors
        ps = 'p';  // Packed operations for 128-bit vectors
        break;
    }

    switch (node->kind) {
    case ND_ADD:
        println("  add%c%c %%xmm1, %%xmm0", ps, sz);
      return;
    case ND_SUB:
        println("  sub%c%c %%xmm1, %%xmm0", ps, sz);
      return;
    case ND_MUL:
        println("  mul%c%c %%xmm1, %%xmm0", ps, sz);
      return;
    case ND_DIV:
        println("  div%c%c %%xmm1, %%xmm0", ps, sz);
      return;
    case ND_EQ:
    case ND_NE:
    case ND_LT:
    case ND_LE:
        println("  ucomis%c %%xmm0, %%xmm1", sz);

        if (node->kind == ND_EQ) {
        println("  sete %%al");
        println("  setnp %%dl");
        println("  and %%dl, %%al");
        } else if (node->kind == ND_NE) {
        println("  setne %%al");
        println("  setp %%dl");
        println("  or %%dl, %%al");
        } else if (node->kind == ND_LT) {
        println("  seta %%al");
        } else {
        println("  setae %%al");
      }

      println("  and $1, %%al");
      println("  movzb %%al, %%rax");
      return;
    }

    error_tok(node->tok, "%s invalid expression", CODEGEN_C);
  }

  case TY_LDOUBLE:
  {
    gen_expr(node->lhs);
    gen_expr(node->rhs);

    switch (node->kind)
    {
    case ND_ADD:
      println("  faddp");
      return;
    case ND_SUB:
      println("  fsubrp");
      return;
    case ND_MUL:
      println("  fmulp");
      return;
    case ND_DIV:
      println("  fdivrp");
      return;
    case ND_EQ:
    case ND_NE:
    case ND_LT:
    case ND_LE:
      println("  fcomip");
      println("  fstp %%st(0)");

      if (node->kind == ND_EQ)
        println("  sete %%al");
      else if (node->kind == ND_NE)
        println("  setne %%al");
      else if (node->kind == ND_LT)
        println("  seta %%al");
      else
        println("  setae %%al");

      println("  movzb %%al, %%rax");
      return;
    }

    error_tok(node->tok, "%s invalid expression", CODEGEN_C);
  }
  }

if (node->rhs->ty->kind == TY_INT128) {
    gen_expr(node->rhs);
    push2();
    gen_expr(node->lhs);
    pop2("%rdi", "%rsi");
  
  } else {
    gen_expr(node->rhs);
    push();
    gen_expr(node->lhs);
    pop("%rdi");
  }


  char *ax, *di, *dx;

  if (node->lhs->ty->kind == TY_LONG || node->lhs->ty->base)
  {
    ax = "%rax";
    di = "%rdi";
    dx = "%rdx";
  }
  else
  {
    ax = "%eax";
    di = "%edi";
    dx = "%edx";
  }

  switch (node->kind)
  {
  case ND_ADD:
    if (node->lhs->ty->kind == TY_INT128) {
      println("  add %%rdi, %%rax");
      println("  adc %%rsi, %%rdx");

    } else {
    println("  add %s, %s", di, ax);
    }
    return;
  case ND_SUB:
      if (node->lhs->ty->kind == TY_INT128) {
        println("  sub %%rdi, %%rax");
        println("  sbb %%rsi, %%rdx");
      }  else {
    println("  sub %s, %s", di, ax);
      }
    return;
  case ND_MUL:
  if (node->lhs->ty->kind == TY_INT128) {
    println("  imul %%rdi, %%rdx");
    println("  imul %%rax, %%rsi");
    println("  add %%rdx, %%rsi");
    println("  mul %%rdi");
    println("  add %%rsi, %%rdx");
  } else {
    println("  imul %s, %s", di, ax);
  }
    return;
  case ND_DIV:
  case ND_MOD:
  if (node->lhs->ty->kind == TY_INT128) {
    bool skew;
    if ((skew = (depth & 1))) {
      println("  sub $8, %%rsp");
      depth++;
    }
    println("  mov %%rsi, %%rcx");
    println("  mov %%rdx, %%rsi");
    println("  mov %%rdi, %%rdx");
    println("  mov %%rax, %%rdi");

    if (node->kind == ND_DIV) {
      if (node->ty->is_unsigned) {
        println("  call __udivti3");
      } else {
        println("  call __divti3");
      }
    } else {
      if (node->ty->is_unsigned) {
        println("  call __umodti3");
      } else {
        println("  call __modti3");
      }
    }
    if (skew) {
      println("  add $8, %%rsp");
      depth--;
    }
  } else {
    // Handle standard integer division or modulus
    if (node->ty->is_unsigned) {
      println("  mov $0, %s", dx);
      println("  div %s", di);
    }
    else
    {
      if (node->lhs->ty->size == 8)
        println("  cqo");
      else
        println("  cdq");
      println("  idiv %s", di);
    }

    if (node->kind == ND_MOD)
      println("  mov %%rdx, %%rax");
  }
    return;
  case ND_BITAND:
    if (node->lhs->ty->kind == TY_INT128) {
        println("  and %%rdi, %%rax");
        println("  and %%rsi, %%rdx");
      } else {
    println("  and %s, %s", di, ax);
      }
    return;
  case ND_BITOR:
    if (node->lhs->ty->kind == TY_INT128) {
        println("  or %%rdi, %%rax");
        println("  or %%rsi, %%rdx");
      }  else {
    println("  or %s, %s", di, ax);
      }
    return;
  case ND_BITXOR:
    if (node->lhs->ty->kind == TY_INT128) {
        println("  xor %%rdi, %%rax");
        println("  xor %%rsi, %%rdx");
      } else {
    println("  xor %s, %s", di, ax);
      }
    return;
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
    if (node->lhs->ty->kind == TY_INT128) {
        switch (node->kind) {
          case ND_EQ:
            println("  mov %%rax, %%r8"); // Move lower 64 bits of lhs to r8
            println("  mov %%rdx, %%r9"); // Move upper 64 bits of lhs to r9
            println("  xor %%r8, %%rdi"); // Compare lower 64 bits of lhs and rhs
            println("  xor %%r9, %%rsi"); // Compare upper 64 bits of lhs and rhs
            println("  or %%rsi, %%rdi"); // Combine the results
            println("  sete %%al");       // Set AL if the result is zero (equal)
            println("  movzx %%al, %%eax"); // Zero extend AL to EAX            
            return;
          case ND_NE:
            println("  xor %%rax, %%rdi");
            println("  xor %%rdx, %%rsi");
            println("  or %%rsi, %%rdi");
            println("  setne %%al");
            println("  movzb %%al, %%rax");  // Zero-extend al to rax to ensure the whole rax is correctly set
            return;
          case ND_LT:
            if (node->lhs->ty->is_unsigned) {
              println("  cmp %%rdi, %%rax");
              println("  mov %%rdx, %%rax");
              println("  sbb %%rsi, %%rax");
              println("  setc %%al");
              println("  movzb %%al, %%rax");  // Zero-extend al to rax to ensure the whole rax is correctly set
            } else {
              println("  cmp %%rdi, %%rax");
              println("  mov %%rdx, %%rax");
              println("  sbb %%rsi, %%rax");
              println("  setl %%al");
              println("  movzb %%al, %%rax");  // Zero-extend al to rax to ensure the whole rax is correctly set
            }
            return;
          case ND_LE:
            if (node->lhs->ty->is_unsigned) {
              println("  cmp %%rax, %%rdi");
              println("  sbb %%rdx, %%rsi");
              println("  setnc %%al");
              println("  movzb %%al, %%rax");  // Zero-extend al to rax to ensure the whole rax is correctly set
            } else {
              println("  cmp %%rax, %%rdi");
              println("  sbb %%rdx, %%rsi");
              println("  setge %%al");
              println("  movzb %%al, %%rax");  // Zero-extend al to rax to ensure the whole rax is correctly set
            }
            return;
        }
      } else {
        println("  cmp %s,%s", di, ax);
        if (node->kind == ND_EQ) {
      println("  sete %%al");
        } else if (node->kind == ND_NE) {
      println("  setne %%al");
        } else if (node->kind == ND_LT) {
          if (node->lhs->ty->is_unsigned) {
        println("  setb %%al");
          } else {
        println("  setl %%al");
    }
        } else if (node->kind == ND_LE) {
          if (node->lhs->ty->is_unsigned) {
        println("  setbe %%al");
          } else {
        println("  setle %%al");
          }
        }
    }

    println("  movzb %%al, %%rax");
    return;
  case ND_SHL:

    println("  mov %%rdi, %%rcx");
    if (node->lhs->ty->kind == TY_INT128) {
        println("  shld %%cl, %%rax, %%rdx");
        println("  shl %%cl, %%rax");
        println("  xor %%edi, %%edi");
        println("  and $64, %%cl");
        println("  cmovne %%rax, %%rdx");
        println("  cmovne %%rdi, %%rax");
    } else {
      // Handle scalar shift left
    println("  shl %%cl, %s", ax);
    }
    return;
  case ND_SHR: {
    int c = count();
    // Move shift amount to CL register
    println("  mov %%rdi, %%rcx");
    if (node->lhs->ty->kind == TY_INT128) {
      // Handle 128-bit shifts
      if (node->lhs->ty->is_unsigned) {
        // Handle unsigned 128-bit shift right
        println("  cmp $64, %%rcx");
        println("  ja .Lshift_gt64_unsigned_%d", c);

        // Common shift logic for shifts within 64 bits
        println("  shrd %%cl, %%rdx, %%rax");  // Shift right double
        println("  shr %%cl, %%rdx");          // Logical shift of upper 64 bits
        println("  jmp .Lshift_done_%d", c);

        // Handle shifts greater than 63 bits
        println(".Lshift_gt64_unsigned_%d:", c);
        println("  sub $64, %%rcx");           // Adjust shift amount
        println("  mov %%rdx, %%rax");         // Move high bits to low
        println("  shr %%cl, %%rax");          // Logical shift remaining bits in %%rax
        println("  xor %%rdx, %%rdx");         // Clear %%rdx (upper 64 bits)
      } else {
        // Handle signed 128-bit shift right (arithmetic)
        println("  cmp $64, %%rcx");
        println("  ja .Lshift_gt64_signed_%d", c);

        // Common shift logic for shifts within 64 bits
        println("  shrd %%cl, %%rdx, %%rax");  // Shift right double
        println("  sar %%cl, %%rdx");          // Arithmetic shift of upper 64 bits
        println("  jmp .Lshift_done_%d", c);

        // Handle shifts greater than 63 bits
        println(".Lshift_gt64_signed_%d:", c);
        println("  sub $64, %%rcx");           // Adjust shift amount
        println("  mov %%rdx, %%rax");         // Move high bits to low
        println("  sar %%cl, %%rax");          // Arithmetic shift remaining bits in %%rax
        println("  sar $63, %%rdx");           // Sign extend %%rdx to fill with sign bit
      }

    println(".Lshift_done_%d:", c);

    } else {
      // Handle scalar values
      if (node->lhs->ty->is_unsigned) {
        println("  shr %%cl, %s", ax);  // Logical shift for unsigned
      } else {
        println("  sar %%cl, %s", ax);  // Arithmetic shift for signed
      }
    }

    return;
    }
  }

  error_tok(node->tok, "%s invalid expression", CODEGEN_C);
}

static void gen_stmt(Node *node)
{
  if (node->tok->line_no != last_loc_line) {
        println("  .loc %d %u", node->tok->file->file_no, node->tok->line_no);
        last_loc_line = node->tok->line_no;
  }
  //println("  .loc %d %u", node->tok->file->file_no, node->tok->line_no);

  switch (node->kind)
  {
  case ND_IF:
  {
    int c = count();
    gen_expr(node->cond);
    cmp_zero(node->cond->ty);
    println("  je  .L.else.%d", c);
    gen_stmt(node->then);
    println("  jmp .L.end.%d", c);
    println(".L.else.%d:", c);
    if (node->els)
      gen_stmt(node->els);
    println(".L.end.%d:", c);
    return;
  }
  case ND_FOR:
  {
    int c = count();
    if (node->init)
      gen_stmt(node->init);
    println(".L.begin.%d:", c);
    if (node->cond)
    {
      gen_expr(node->cond);
      cmp_zero(node->cond->ty);
      println("  je %s", node->brk_label);
    }
    gen_stmt(node->then);
    println("%s:", node->cont_label);
    if (node->inc)
      gen_expr(node->inc);
    println("  jmp .L.begin.%d", c);
    println("%s:", node->brk_label);
    return;
  }
  case ND_DO:
  {
    int c = count();
    println(".L.begin.%d:", c);
    gen_stmt(node->then);
    println("%s:", node->cont_label);
    gen_expr(node->cond);
    cmp_zero(node->cond->ty);
    println("  jne .L.begin.%d", c);
    println("%s:", node->brk_label);
    return;
  }
  case ND_SWITCH:
    gen_expr(node->cond);

    for (Node *n = node->case_next; n; n = n->case_next)
    {
      char *ax = (node->cond->ty->size == 8) ? "%rax" : "%eax";
      char *di = (node->cond->ty->size == 8) ? "%rdi" : "%edi";

      if (n->begin == n->end)
      {
        println("  cmp $%ld, %s", n->begin, ax);
        println("  je %s", n->label);
        continue;
      }

      // [GNU] Case ranges
      println("  mov %s, %s", ax, di);
      println("  sub $%ld, %s", n->begin, di);
      println("  cmp $%ld, %s", n->end - n->begin, di);
      println("  jbe %s", n->label);
    }

    if (node->default_case)
      println("  jmp %s", node->default_case->label);

    println("  jmp %s", node->brk_label);
    gen_stmt(node->then);
    println("%s:", node->brk_label);
    return;
  case ND_CASE:
    println("%s:", node->label);
    gen_stmt(node->lhs);
    return;
  case ND_BLOCK:
    for (Node *n = node->body; n; n = n->next)
      gen_stmt(n);
    return;
  case ND_GOTO:
    println("  jmp %s", node->unique_label);
    return;
  case ND_GOTO_EXPR:
    gen_expr(node->lhs);
    println("  jmp *%%rax");
    return;
  case ND_LABEL:
    println("%s:", node->unique_label);
    gen_stmt(node->lhs);
    return;
  case ND_RETURN:
    if (node->lhs)
    {
      gen_expr(node->lhs);
      Type *ty = node->lhs->ty;

      switch (ty->kind)
      {
      case TY_STRUCT:
      case TY_UNION:
        if (ty->size <= 16)
          copy_struct_reg();
        else
          copy_struct_mem();
        break;
      }
    }

    println("  jmp .L.return.%s", current_fn->name);
    return;
  case ND_EXPR_STMT:
    gen_expr(node->lhs);
    return;
  case ND_ASM:
    println("  %s", node->asm_str);
    return;
  }

  error_tok(node->tok, "%s invalid statement", CODEGEN_C);
}


static void emit_data(Obj *prog)
{
  for (Obj *var = prog; var; var = var->next)
  {
    //issue 35 about array not initialized completely.
    println("  .zero %d", var->ty->size);
    if (var->alias_name)
      println("  .set \"%s\", %s", var->name, var->alias_name);

    if (var->is_function || !var->is_definition)
      continue;

    if (var->is_static)
      println("  .local %s", var->name);
    else if (var->ty->is_weak)
      println("  .weak \"%s\"", var->name);
    else
      println("  .globl %s", var->name);

     // Adjust alignment for TY_ARRAY with size >= 16, TY_INT128, and vector size 16
        int align = var->align;
        if ((var->ty->kind == TY_ARRAY && var->ty->size >= 16) ||
            var->ty->kind == TY_INT128 ||
            (var->ty->vector_size == 16)) {
            align = MAX(16, var->align);
        }


    // Common symbol
    if (opt_fcommon && var->is_tentative)
    {
      //from @fuhsnn incomplete array assuming to have one element
      if (var->ty->kind == TY_ARRAY && var->ty->size < 0)
        var->ty->size = var->ty->base->size;
      println("  .comm %s, %d, %d", var->name, var->ty->size, align);
      continue;
    }
    // .data or .tdata
    if (var->init_data)
    {
      if (var->is_tls)
        println("  .section .tdata,\"awT\",@progbits");
      else
        println("  .section .data,\"aw\",@progbits");
        //println("  .data");

      println("  .type %s, @object", var->name);
      println("  .size %s, %d", var->name, var->ty->size);
      //println("  .align %d", align);
      if (align > 1) println("  .align %d", align);
      println("%s:", var->name);

      Relocation *rel = var->rel;
      int unit_size = (var->ty->kind == TY_ARRAY) ? var->ty->base->size : var->ty->size;
      int pos = 0;
      while (pos < var->ty->size)
      {
        if (rel && rel->offset == pos)
        {
          println("  .quad %s%+ld", *rel->label, rel->addend);
          rel = rel->next;
          pos += 8;
        }
        else 
        {
          
          //from @enh (Elliott Hughes) Use .byte/.short/.long/.quad as appropriate.
          //println("  .byte %d", var->init_data[pos++]);
          if (unit_size == 8) {
            long v = *(long*) &var->init_data[pos];
            println("  .quad %ld  # %#lx", v, v);
            pos += 8;
          } else if (unit_size == 4) {
            int v = *(int*) &var->init_data[pos];
            println("  .long %d  # %#x", v, v);
            pos += 4;
          } else if (unit_size == 2) {
            int v = *(short*) &var->init_data[pos] & 0xffff;
            println("  .short %d  # %#x", v, v);
            pos += 2;
          } else {
            int v = var->init_data[pos] & 0xff;
            println("  .byte %d  # %#x", v, v);
            pos += 1;
          }

        }
      }
      println("  .size %s, %d", var->name, var->ty->size);
      continue;
    }

    // .bss or .tbss
    if (var->is_tls)
      println("  .section .tbss,\"awT\",@nobits");
    else
      println("  .section .bss,\"aw\",@nobits");
      //println("  .bss");

    //println("  .align %d", align);
    if (align > 1) println("  .align %d", align);
    println("%s:", var->name);
    println("  .zero %d", var->ty->size);
  }
}

static void store_fp(int r, int offset, int sz)
{
  switch (sz) {
  case 2:
    // movw is used for 2-byte (16-bit) words
    println("  movw %%xmm%d, %d(%%rbp)", r, offset);
    return;
  case 4:
    println("  movss %%xmm%d, %d(%%rbp)", r, offset);
    return;
  case 8:
    println("  movsd %%xmm%d, %d(%%rbp)", r, offset);
    return;
  case 16:
    println("  movaps %%xmm%d, %d(%%rbp)", r, offset); // movaps for 16-byte (128-bit) vector
    return;
  }
  printf("===== r=%d offset=%d sz=%d\n", r, offset, sz);
  unreachable();
}



static void store_gp(int r, int offset, int sz) {
  switch (sz) {
  case 1:
    println("  mov %s, %d(%%rbp)", argreg8[r], offset);
    return;
  case 2:
    println("  mov %s, %d(%%rbp)", argreg16[r], offset);
    return;
  case 4:
    println("  mov %s, %d(%%rbp)", argreg32[r], offset);
    return;
  case 8:
    println("  mov %s, %d(%%rbp)", argreg64[r], offset);
    return;
  case 16:
    // Assuming we can use xmm registers to store 128 bits
    println("  movdqu %%xmm%d, %d(%%rbp)", r, offset);
    return;
  default:
    for (int i = 0; i < sz; i++) {
      println("  mov %s, %d(%%rbp)", argreg8[r], offset + i);
      println("  shr $8, %s", argreg64[r]);
    }
    return;
  }
}


static void emit_text(Obj *prog)
{
  

  for (Obj *fn = prog; fn; fn = fn->next)
  {
    // Emit alias if fn->alias_name is set
    if (fn->alias_name) {
      // Handle weak alias
      println("  .weak %s", fn->name);                 // Mark the function as weak
      println("  .set %s, %s", fn->name, fn->alias_name);  // Define alias
    }

    if (!fn->is_function || !fn->is_definition)
      continue;

    // No code is emitted for "static inline" functions
    // if no one is referencing them.
    if (!fn->is_live)
      continue;

    // if (fn->is_static)
    //   println("  .local %s", fn->name);
    // else 
    //   println("  .globl %s", fn->name);


    // println("  .text");
    println("\n  .section .text,\"ax\",@progbits");
    println("  .%s %s", fn->is_static ? "local" : "global", fn->name);    
    println("  .type %s, @function", fn->name);
    println("%s:", fn->name);

    
    current_fn = fn;

    // Prologue
    println("  push %%rbp");
    println("  mov %%rsp, %%rbp");
    println("  sub $%d, %%rsp", fn->stack_size);
    println("  mov %%rsp, %d(%%rbp)", fn->alloca_bottom->offset);

    // Save arg registers if function is variadic
    if (fn->va_area)
    {
      int gp = 0, fp = 0;
      for (Obj *var = fn->params; var; var = var->next)
      {
        if (is_flonum(var->ty))
          fp++;
        else
          gp++;
      }

      int off = fn->va_area->offset;

      // va_elem
      println("  movl $%d, %d(%%rbp)", gp * 8, off);          // gp_offset
      println("  movl $%d, %d(%%rbp)", fp * 8 + 48, off + 4); // fp_offset
      println("  movq %%rbp, %d(%%rbp)", off + 8);            // overflow_arg_area
      println("  addq $16, %d(%%rbp)", off + 8);
      println("  movq %%rbp, %d(%%rbp)", off + 16); // reg_save_area
      println("  addq $%d, %d(%%rbp)", off + 24, off + 16);

      // __reg_save_area__
      println("  movq %%rdi, %d(%%rbp)", off + 24);
      println("  movq %%rsi, %d(%%rbp)", off + 32);
      println("  movq %%rdx, %d(%%rbp)", off + 40);
      println("  movq %%rcx, %d(%%rbp)", off + 48);
      println("  movq %%r8, %d(%%rbp)", off + 56);
      println("  movq %%r9, %d(%%rbp)", off + 64);
      println("  movsd %%xmm0, %d(%%rbp)", off + 72);
      println("  movsd %%xmm1, %d(%%rbp)", off + 80);
      println("  movsd %%xmm2, %d(%%rbp)", off + 88);
      println("  movsd %%xmm3, %d(%%rbp)", off + 96);
      println("  movsd %%xmm4, %d(%%rbp)", off + 104);
      println("  movsd %%xmm5, %d(%%rbp)", off + 112);
      println("  movsd %%xmm6, %d(%%rbp)", off + 120);
      println("  movsd %%xmm7, %d(%%rbp)", off + 128);
    }

    // Save passed-by-register arguments to the stack
    int gp = 0, fp = 0;
    for (Obj *var = fn->params; var; var = var->next)
    {

      if (var->offset > 0)
        continue;

      Type *ty = var->ty;

      switch (ty->kind)
      {
      case TY_STRUCT:
      case TY_UNION:
        assert(ty->size <= 16);
        if (has_flonum(ty, 0, 8, 0))
          store_fp(fp++, var->offset, MIN(8, ty->size));
        else
          store_gp(gp++, var->offset, MIN(8, ty->size));

        if (ty->size > 8)
        {
          if (has_flonum(ty, 8, 16, 0))
            store_fp(fp++, var->offset + 8, ty->size - 8);
          else
            store_gp(gp++, var->offset + 8, ty->size - 8);
        }
        break;
      case TY_FLOAT:
      case TY_DOUBLE:
        store_fp(fp++, var->offset, ty->size);
        break;
      case TY_INT128:
        store_gp(gp++, var->offset + 0, 8);
        store_gp(gp++, var->offset + 8, 8);
        break;
      default:
        store_gp(gp++, var->offset, ty->size);
      }
    }



    // Emit code
    gen_stmt(fn->body);

    assert(depth == 0);




    // [https://www.sigbus.info/n1570#5.1.2.2.3p1] The C spec defines
    // a special rule for the main function. Reaching the end of the
    // main function is equivalent to returning 0, even though the
    // behavior is undefined for the other functions.
    if (strcmp(fn->name, "main") == 0)
      println("  mov $0, %%rax");

    // Epilogue
    println(".L.return.%s:", fn->name);
    println("  mov %%rbp, %%rsp");
    println("  pop %%rbp");
    println("  ret");
    println(".size %s, .-%s", fn->name, fn->name);
  }
}

void codegen(Obj *prog, FILE *out)
{
  output_file = out;

  File **files = get_input_files();
  for (int i = 0; files[i]; i++)
    println("  .file %d \"%s\"", files[i]->file_no, files[i]->name);

  assign_lvar_offsets(prog);
  emit_data(prog);
  emit_text(prog);
  println("  .section  .note.GNU-stack,\"\",@progbits");


  //print offset for each variable
  if (isDebug) {
    print_offset(prog);
  }
  //generate dwarf info
  if (opt_g)
    generate_dwarf_info(prog);
}



// Print offset.
static void print_offset(Obj *prog)
{
  for (Obj *fn = prog; fn; fn = fn->next)
  {

      
    for (Obj *var = fn->params; var; var = var->next)
    {
    printf("=====fn_name=%s var_name=%s offset=%d stack_size=%d\n", fn->name, var->name, var->offset, fn->stack_size );
    }
    for (Obj *var = fn->locals; var; var = var->next)
    {
      printf("=====fn_name=%s var_name=%s offset=%d stack_size=%d\n", fn->name, var->name, var->offset, fn->stack_size );
      //update the function name if it's missing
      if (!var->funcname)
        var->funcname = fn->name;
    }

  }
}


void assign_lvar_offsets(Obj *prog) {
    for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function)
      continue;

    int top = 16;
    int bottom = 0;

    if (fn->alloca_bottom && fn->alloca_bottom->offset) {          
        bottom = abs(fn->alloca_bottom->offset);
    }

    int gp = 0, fp = 0;

    // Assign offsets to pass-by-stack parameters.
        for (Obj *var = fn->params; var; var = var->next) {
      if (var->offset) {
        continue;
      }
      Type *ty = var->ty;

        // Use default alignment if not a vector
        int align = ty->align;
        // Only adjust alignment if the type is a vector
        if (ty->is_vector) {
            align = MAX(align, 16); // Ensure at least 16-byte alignment for vectors
        }


            switch (ty->kind) {
      case TY_STRUCT:
      case TY_UNION:
        if (pass_by_reg(ty, gp, fp)) {
          fp += has_flonum1(ty) + (ty->size > 8 && has_flonum2(ty));
          gp += !has_flonum1(ty) + (ty->size > 8 && !has_flonum2(ty));
          continue;
        }
        break;
      case TY_FLOAT:
      case TY_DOUBLE:
        if (fp++ < FP_MAX)
          continue;
        break;
      case TY_LDOUBLE:
        break;
            case TY_INT128:
                gp++;
                if (gp++ < GP_MAX) continue;
                break;
      default:
        if (gp++ < GP_MAX)
          continue;
      }

            // Adjust top alignment based on the type's alignment requirement
            align = (ty->size >= 16 || ty->kind == TY_INT128 || ty->vector_size == 16 || ty->is_vector) ? 16 : 8;
            top = align_to(top, align);
      var->offset = top;
            top += ty->size;
    }

    // Assign offsets to pass-by-register parameters and local variables.
        for (Obj *var = fn->locals; var; var = var->next) {
            int align = var->align;
            if ((var->ty->kind == TY_ARRAY && var->ty->size >= 16) || var->ty->is_vector ||
                var->ty->kind == TY_INT128 ||
                (var->ty->vector_size == 16)) {
                align = MAX(16, var->align);
            }

      if (isDebug)                      
        printf("======bottom=%d kind=%d size=%d fn_bottom=%d fn_stack_size=%d name=%s funcname=%s\n", bottom, var->ty->kind, var->ty->size, fn->alloca_bottom->offset, fn->alloca_bottom->stack_size, var->name, var->funcname);

      if (var->offset) {
        bottom += var->ty->size;
        bottom = align_to(bottom, align);
        continue;
      }

      bottom += var->ty->size;
      bottom = align_to(bottom, align);
      var->offset = -bottom;
    }

    fn->stack_size = align_to(bottom, 16);
  }
}



//check if a register is available
char *register_available() {

  int len = sizeof(newargreg64)/sizeof(newargreg64[0]);
  int i;

  
  for(i = 0; i < len; ++i)
  {
      //register already used
      bool isFound = check_register_used(newargreg64[i]);
      if (isFound)
        continue;
      else {
        add_register_used(newargreg64[i]);
        return newargreg64[i];
      }
  }
  //no registry available
  error("%s: %s:%d: error: in register_available : no register available!", CODEGEN_C, __FILE__, __LINE__);
}

//check if a specific register is available in priority if not try to found a new available
char *specific_register_available(char *regist) {

  int found = check_register_used(regist);
  if (!found) {
    add_register_used(regist);
    return regist;
  }
  return register_available();
  
}

//convert register 8 to register 64
char *register8_to_64(char *regist) {

int len = sizeof(newargreg8)/sizeof(newargreg8[0]);
int i;

  for(i = 0; i < len; ++i)
  {
      if(!strncmp(newargreg8[i], regist, strlen(regist)))
      {
          return newargreg64[i];
      }
  }
  error("%s: %s:%d: error: in register8_to_64 : unexpected error!", CODEGEN_C, __FILE__, __LINE__);
}

//convert register 16 to register 64
char *register16_to_64(char *regist) {

int len = sizeof(newargreg16)/sizeof(newargreg16[0]);
int i;

  for(i = 0; i < len; ++i)
  {
      if(!strncmp(newargreg16[i], regist, strlen(regist)))
      {
          return newargreg64[i];
      }
  }
  error("%s: %s:%d: error: in register16_to_64 : unexpected error!", CODEGEN_C, __FILE__, __LINE__);
}

//convert register 32 to register 64
char *register32_to_64(char *regist) {

int len = sizeof(newargreg32)/sizeof(newargreg32[0]);
int i;

  for(i = 0; i < len; ++i)
  {
      if(!strncmp(newargreg32[i], regist, strlen(regist)))
      {
          return newargreg64[i];
      }
  }
  error("%s: %s:%d: error: in register32_to_64 : unexpected error!", CODEGEN_C, __FILE__, __LINE__);
}

//add a register in the list of used registers
int add_register_used(char *regist) {

int len = sizeof(registerUsed)/sizeof(registerUsed[0]);
int i;
char *tmp = "free";
  for(i = 0; i < len; ++i)
  {
       if (!strncmp(registerUsed[i], tmp, strlen(registerUsed[i])))
      {
          registerUsed[i] = regist;
          return i;
      }
  }
  //no free location
  return -1;
}


//check if register used return 0 if not used
bool check_register_used(char *regist) {

int isFound = false;
int len = sizeof(registerUsed)/sizeof(registerUsed[0]);
int i;

  for(i = 0; i < len; ++i)
  {
      
      if(!strncmp(registerUsed[i], regist, strlen(regist)))
      {
        isFound = true;
        return isFound;
      }
  }
  //not found
  return isFound;
}


//clear the registerUseds
void clear_register_used() {

int len = sizeof(registerUsed)/sizeof(registerUsed[0]);
int i;

  for(i = 0; i < len; ++i)
  {
     registerUsed[i] = "free";
  }
}

//check if a register8 is used in a template
//if yes retrieve the register64 and add it in the registerUsed array
//if not check if a register 16 is found in a template

void check_register_in_template(char *template) {

int len = sizeof(newargreg64)/sizeof(newargreg64[0]);

   //check if register 64 found in template and mark it as used
    for(int i = 0; i < len; ++i)
  {
    if (strstr(template, newargreg64[i]) != NULL)
      add_register_used(newargreg64[i]);
  }
     //check if register 32 found in template and mark it as used
  len = sizeof(newargreg32)/sizeof(newargreg32[0]);     
    for(int i = 0; i < len; ++i)
  {

    if (strstr(template, newargreg32[i]) != NULL)      
      add_register_used(register32_to_64(newargreg32[i]));
  }

  //check if register 16 found in template and mark it as used
  len = sizeof(newargreg16)/sizeof(newargreg16[0]);     
    for(int i = 0; i < len; ++i)
  {
    if (strstr(template, newargreg16[i]) != NULL)      
      add_register_used(register16_to_64(newargreg16[i]));
  }

  //check if register 8 found in template and mark it as used
  len = sizeof(newargreg8)/sizeof(newargreg8[0]);     
    for(int i = 0; i < len; ++i)
  {
    if (strstr(template, newargreg8[i]) != NULL)      
      add_register_used(register8_to_64(newargreg8[i]));
  }


}


//from @cosmopolitan
static void pushx(void) {
  println("  sub $16,%%rsp");
  println("  movdqu %%xmm0,(%%rsp)");
  depth += 2;
}

//from @cosmopolitan
static void popx(int reg) {
  println("  movdqu (%%rsp), %%xmm%d", reg);
  println("  add $16, %%rsp");
  depth -= 2;

}

//from @cosmopolitan
void push2(void) {
  println("  push %%rdx");
  println("  push %%rax");
  depth++;
  depth++;
}

//from @cosmopolitan
void pop2(char *a, char *b) {
  println("  pop %s", a);
  println("  pop %s", b);
  depth--;
  depth--;  
}


void pushreg(const char *arg) {
  println("  push %%%s", arg);
  depth++;
}

