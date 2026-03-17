#include "chibicc.h"

#define GP_MAX 6
#define FP_MAX 8

static FILE *output_file;
static int depth;
static char *argreg8[] = {"%dil", "%sil", "%dl", "%cl", "%r8b", "%r9b"};
static char *argreg16[] = {"%di", "%si", "%dx", "%cx", "%r8w", "%r9w"};
static char *argreg32[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};
static char *argreg64[] = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};


static char *newargreg8[] =  {"%cl", "%dl", "%al", "%sil", "%dil", "%r8b", "%r9b", "%r11b", "%r12b", "%r13b", "%r14b", "%r15b"};
static char *newargreg16[] = {"%cx", "%dx", "%ax", "%si",  "%di",  "%r8w", "%r9w", "%r11w", "%r12w", "%r13w", "%r14w", "%r15w"};
static char *newargreg32[] = {"%ecx","%edx","%eax","%esi","%edi","%r8d", "%r9d",  "%r11d", "%r12d", "%r13d", "%r14d", "%r15d"};
static char *newargreg64[] = {"%rcx","%rdx","%rax","%rsi","%rdi","%r8",  "%r9",  "%r11",  "%r12",  "%r13",  "%r14",  "%r15"};
static char *registerUsed[] = {"free", "free", "free", "free", "free", "free", "free", "free", "free", "free", "free", "free"};


extern int64_t eval(Node *node);

static Obj *current_fn;
static char *lvar_ptr;
bool dont_reuse_stack = false;
extern bool opt_omit_frame_pointer;
extern bool opt_fbuiltin;
extern bool opt_optimize_level3;

static void gen_expr(Node *node);
static void gen_stmt(Node *node);
static void print_offset(Obj *prog);
static int cmp_ctor(const void *a, const void *b);
static void emit_constructors(void);
static void emit_destructors(void); 



static int last_loc_line = 0;

typedef struct CtorFunc {
  char *name;
  int priority;
} CtorFunc;

static CtorFunc *constructors[256];
static int constructor_cnt = 0;

static CtorFunc *destructors[256];
static int destructor_cnt = 0;

struct {
  int *data;
  int capacity;
  int depth;
  int bottom;
} static tmp_stack;

static char *sym(Obj *var) {
  return var->asmname ? var->asmname : var->name;
}

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


static bool is_omit_fp(Obj *fn) {
  if (!opt_omit_frame_pointer) return false;
  if (fn->force_frame_pointer) return false;
  if (fn->stack_align > 16) return false;
  // 16-byte atomics/int128 on stack can be used by cmpxchg16b paths.
  // Keep a frame pointer for these cases to preserve slot alignment.
  for (Obj *var = fn->locals; var; var = var->next) {
    if (var->ty && var->ty->size == 16 &&
        (var->ty->is_atomic || var->ty->kind == TY_INT128 || var->ty->kind == TY_LDOUBLE))
      return false;
  }
  for (Obj *var = fn->params; var; var = var->next) {
    if (var->ty && var->ty->size == 16 &&
        (var->ty->is_atomic || var->ty->kind == TY_INT128 || var->ty->kind == TY_LDOUBLE))
      return false;
  }
  return true;
}

static int push_tmpstack(void) {
  if (tmp_stack.depth == tmp_stack.capacity) {
    tmp_stack.capacity += 4;
    tmp_stack.data = realloc(tmp_stack.data, sizeof(int) * tmp_stack.capacity);
  }

  int offset;
  if (!dont_reuse_stack) {
      int bottom = current_fn->stack_size + (tmp_stack.depth + 1) * 8;
    tmp_stack.bottom = MAX(tmp_stack.bottom, bottom);
    offset = -bottom;
  } else {
    tmp_stack.bottom += 8;
    offset = -tmp_stack.bottom;
  }
  tmp_stack.data[tmp_stack.depth] = offset;
  tmp_stack.depth++;
  return offset;
}

static int pop_tmpstack(void) {
  tmp_stack.depth--;
  return tmp_stack.data[tmp_stack.depth];
}

static int push_tmp(void) {
  if (is_omit_fp(current_fn)) {
    println("  push %%rax");
    depth++;
    return 0;
  }
  int offset = push_tmpstack();
  println("  mov %%rax, %d(%s)", offset, lvar_ptr);
  return offset;
}

static void pop_tmp(char *arg) {
  if (is_omit_fp(current_fn)) {
    println("  pop %s", arg);
    depth--;
    return;
  }
  int offset = pop_tmpstack();
  println("  mov %d(%s), %s", offset, lvar_ptr, arg);
}


static void push_tmpf(void) {
  if (is_omit_fp(current_fn)) {
    println("  sub $8, %%rsp");
    println("  movsd %%xmm0, (%%rsp)");
    depth++;
    return;
  }
  int offset = push_tmpstack();
  println("  movsd %%xmm0, %d(%s)", offset, lvar_ptr);
}

static void pop_tmpf(int reg) {
  if (is_omit_fp(current_fn)) {
    println("  movsd (%%rsp), %%xmm%d", reg);
    println("  add $8, %%rsp");
    depth--;
    return;
  }
  int offset = pop_tmpstack();
  println("  movsd %d(%s), %%xmm%d", offset, lvar_ptr, reg);
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

static void pushf(void)
{
  println("  sub $8, %%rsp");
  println("  movsd %%xmm0, (%%rsp)");
  depth++;
}

static void popf(int reg)
{
  println("  movsd (%%rsp), %%xmm%d", reg);
  println("  add $8, %%rsp");
  depth--;
}

static void pushld(void) {
  println("  sub $16, %%rsp");
  println("  fstpt (%%rsp)");
  depth += 2;
}

static void popld(void) {
  println("  fldt (%%rsp)");
  println("  add $16, %%rsp");
  depth -= 2;
}

static void pushv(void) {
  println("  sub $16, %%rsp");
  println("  movdqu %%xmm0, (%%rsp)");
  depth += 2; 
}

static void popv(int reg) {
  println("  movdqu (%%rsp), %%xmm%d", reg);
  println("  add $16, %%rsp");
  depth -= 2;
}

void pushx(void) {
  println("  push %%rdx");
  println("  push %%rax");
  depth++;
  depth++;
}

void popx(char *a, char *b) {
  println("  pop %s", a);
  println("  pop %s", b);
  depth--;
  depth--;  
}

static void pushx_tmp(void) {
  if (is_omit_fp(current_fn)) {
    println("  push %%rdx");
    println("  push %%rax");
    depth += 2;
    return;
  }
  int off_rdx = push_tmpstack(); 
  println("  mov %%rdx, %d(%s)", off_rdx, lvar_ptr);
  int off_rax = push_tmpstack();  
  println("  mov %%rax, %d(%s)", off_rax, lvar_ptr);
}

static void popx_tmp(char *a, char *b) {
  if (is_omit_fp(current_fn)) {
    println("  pop %s", a);
    println("  pop %s", b);
    depth -= 2;
    return;
  }
  int off_rax = pop_tmpstack();   
  println("  mov %d(%s), %s", off_rax, lvar_ptr, a);
  int off_rdx = pop_tmpstack();   
  println("  mov %d(%s), %s", off_rdx, lvar_ptr, b);
}

static void push_xmm(int x) {
  println("  sub $16, %%rsp");
  println("  movdqu %%xmm%d, (%%rsp)", x);
  depth += 2;
}

static void pop_xmm(int x) {
  println("  movdqu (%%rsp), %%xmm%d", x);
  println("  add $16, %%rsp");
  depth -= 2;
}



// Round up `n` to the nearest multiple of `align`. For instance,
// align_to(5, 8) returns 8 and align_to(11, 8) returns 16.
int align_to(int n, int align)
{
  return ((n + align - 1) / align) * align;
}

static void print_visibility(Obj *obj) {
  if (obj->visibility) {
    if (!strcmp(obj->visibility, "hidden")) {
      println("  .hidden\t%s", sym(obj));
    } else if (!strcmp(obj->visibility, "protected")) {
      println("  .protected %s", sym(obj));
    }
  } 
  if (obj->is_static) {
    println("  .local\t%s", sym(obj));
  } else {
    println("  .globl\t%s", sym(obj));
  }
  if (obj->is_weak) {
    
    println("  .weak\t%s", sym(obj));
  }
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
  }
  return "%rdx";
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
  }
  return "%rdi";
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
  }
  return "%rsi";
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
  }
  return "%r8";
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
  }
  return "%r9";
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
  }
  return "%r10";
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
  }
  return "%r11";
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
  }
  return "%rbx";
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
  }
  return "%rcx";
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
  }
  return "%rax";
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
      if (is_omit_fp(current_fn))
        println("  mov %d(%%rsp), %%rax", node->var->offset + current_fn->stack_size + depth * 8);
      else
        println("  mov %d(%s), %%rax", node->var->offset, node->var->ptr);
      return;
    }

    // Local variable
    if (node->var->is_local)
    {
      if (is_omit_fp(current_fn))
        println("  lea %d(%%rsp), %%rax", node->var->offset + current_fn->stack_size + depth * 8);
      else
        println("  lea %d(%s), %%rax", node->var->offset, node->var->ptr);
      return;
    }


    if (opt_fpic)
    {
      // Thread-local variable
      if (node->var->is_tls)
      {
        println("  data16 lea \"%s\"@tlsgd(%%rip), %%rdi", sym(node->var));
        println("  .value 0x6666");
        println("  rex64");
        println("  call __tls_get_addr@PLT");
        return;
      }

      // Function or global variable
      println("  mov \"%s\"@GOTPCREL(%%rip), %%rax", sym(node->var));
      return;
    }

    // Thread-local variable
    if (node->var->is_tls)
    {
      println("  mov %%fs:0, %%rax");
      if (node->var->is_definition)
        println("  add $\"%s\"@tpoff, %%rax", sym(node->var));
      else 
        println("  add %s@gottpoff(%%rip), %%rax", sym(node->var));
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
        println("  lea \"%s\"(%%rip), %%rax", sym(node->var));
      else
        println("  mov \"%s\"@GOTPCREL(%%rip), %%rax", sym(node->var));
      return;
    }

    // Global variable
    println("  lea \"%s\"(%%rip), %%rax", sym(node->var));
    return;
  case ND_DEREF:
    gen_expr(node->lhs);
    return;
  case ND_COMMA:
    gen_expr(node->lhs);
    gen_addr(node->rhs);
    return;
  case ND_MEMBER:
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
    if (node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION )
    {
      gen_expr(node);
      return;
    }
    break;
  case ND_VLA_PTR:
    if (is_omit_fp(current_fn))
      println("  lea %d(%%rsp), %%rax", node->var->offset + current_fn->stack_size + depth * 8);
    else
      println("  lea %d(%s), %%rax", node->var->offset, node->var->ptr);
    return;
  case ND_ADD: 
  case ND_SUB:
  case ND_MUL:
  case ND_DIV:
  case ND_BITXOR:
  case ND_BITAND:
  case ND_BITOR:
    if (is_vector(node->lhs->ty) || (node->rhs && is_vector(node->rhs->ty))) {
      gen_expr(node->lhs);
      gen_expr(node->rhs);  
      return;
    }
    return;
  case ND_CAST:
    if (is_vector(node->ty)) {
      gen_expr(node);
      return;
    }
    return;
  
  }

  error_tok(node->tok, "%s:%d not an lvalue %d", __FILE__, __LINE__, node->kind);
}

// Copy n bytes from the source address in %rax to the destination in dst_reg.
static void gen_mem_copy(const char *dst_reg, int n) {
  int i = 0;
  while (n >= 8) {
    println("  movq %d(%%rax), %%r8", i);
    println("  movq %%r8, %d(%s)", i, dst_reg);
    n -= 8;
    i += 8;
  }
  while (n >= 4) {
    println("  movl %d(%%rax), %%r8d", i);
    println("  movl %%r8d, %d(%s)", i, dst_reg);
    n -= 4;
    i += 4;
  }
  while (n >= 2) {
    println("  movw %d(%%rax), %%r8w", i);
    println("  movw %%r8w, %d(%s)", i, dst_reg);
    n -= 2;
    i += 2;
  }
  while (n >= 1) {
    println("  movb %d(%%rax), %%r8b", i);
    println("  movb %%r8b, %d(%s)", i, dst_reg);
    --n;
    ++i;
  }
}

// Copy n bytes from %rax to dst_reg + offset
static void gen_mem_copy_with_offset(const char *dst_reg, int offset, int n) {
  int i = 0;
  while (n >= 8) {
    println("  movq %d(%%rax), %%r8", i);
    println("  movq %%r8, %d(%s)", offset + i, dst_reg);
    n -= 8;
    i += 8;
  }
  while (n >= 4) {
    println("  movl %d(%%rax), %%r8d", i);
    println("  movl %%r8d, %d(%s)", offset + i, dst_reg);
    n -= 4;
    i += 4;
  }
  while (n >= 2) {
    println("  movw %d(%%rax), %%r8w", i);
    println("  movw %%r8w, %d(%s)", offset + i, dst_reg);
    n -= 2;
    i += 2;
  }
  while (n >= 1) {
    println("  movb %d(%%rax), %%r8b", i);
    println("  movb %%r8b, %d(%s)", offset + i, dst_reg);
    --n;
    ++i;
  }
}

// Zero n bytes starting from offset bytes off %rbp.
static void gen_mem_zero(int offset, int n) {
  int i = offset;
  if (is_omit_fp(current_fn))
    i += current_fn->stack_size + depth * 8;

  while (n >= 8) {
    if (is_omit_fp(current_fn))
      println("  movq $0, %d(%%rsp)", i);
    else
      println("  movq $0, %d(%s)", i, lvar_ptr);
    n -= 8;
    i += 8;
  }
  while (n >= 4) {
    if (is_omit_fp(current_fn))
      println("  movl $0, %d(%%rsp)", i);
    else
      println("  movl $0, %d(%s)", i, lvar_ptr);
    n -= 4;
    i += 4;
  }
  while (n >= 2) {
    if (is_omit_fp(current_fn))
      println("  movw $0, %d(%%rsp)", i);
    else
      println("  movw $0, %d(%s)", i, lvar_ptr);
    n -= 2;
    i += 2;
  }
  while (n >= 1) {
    if (is_omit_fp(current_fn))
      println("  movb $0, %d(%%rsp)", i);
    else
      println("  movb $0, %d(%s)", i, lvar_ptr);
    --n;
    ++i;
  }
}

// Load a value from where %rax is pointing to.
static void load(Type *ty)
{
  if (!ty)
    error("%s: %s:%d: error: in load : ty is null!", __FILE__, __FILE__, __LINE__);

  switch (ty->kind)
  {
  case TY_VECTOR: {
    if (ty->base->kind == TY_FLOAT || ty->base->kind == TY_DOUBLE) {      
      println("  movups (%%rax), %%xmm0");  
    } else if (is_integer(ty->base)) {
     
      println("  movdqu (%%rax), %%xmm0"); 
    } else {
      error("%s: %s:%d: error: in load : unsupported vector base type %d", __FILE__, __FILE__, __LINE__, ty->base->kind);
    }
    return;
  }
  case TY_ARRAY:
  case TY_STRUCT:
  case TY_UNION:
  case TY_FUNC:
  case TY_VLA:
    // If it is an array, do not attempt to load a value to the
    // register because in general we can't load an entire array to a
    // register. As a result, the result of an evaluation of an array
    // becomes not the array itself but the address of the array.
    // This is where "array is automatically converted to a pointer to
    // the first element of the array in C" occurs.
    return;
  case TY_FLOAT:
    println("  movss (%%rax), %%xmm0");
    return;
  case TY_DOUBLE:
    println("  movsd (%%rax), %%xmm0");
    return;
  case TY_LDOUBLE:
    println("  fldt (%%rax)");
    return;
  case TY_INT128:
    println("  mov 8(%%rax), %%rdx");  // Load upper 64 bits into RDX
    println("  mov (%%rax), %%rax");  // Load lower 64 bits into RAX
    return;    
  }

  char *insn = ty->is_unsigned ? "movz" : "movs";

  // When we load a char or a short value to a register, we always
  // extend them to the size of int, so we can assume the lower half of
  // a register always contains a valid value. The upper half of a
  // register for char, short and int may contain garbage. When we load
  // a long value to a register, it simply occupies the entire register.
  if (ty->size == 1)
    println("  %sbl (%%rax), %%eax", insn);
  else if (ty->size == 2)
    println("  %swl (%%rax), %%eax", insn);
  else if (ty->size == 4)
    println("  movsxd (%%rax), %%rax");
  else
    println("  mov (%%rax), %%rax");
}

// Store %rax to an address that the stack top is pointing to.
static void store(Type *ty)
{
  if (!ty)
    error("%s %d: in store : ty is null!", __FILE__, __LINE__);
  pop_tmp("%rdi");


  switch (ty->kind)
  {
  case TY_VECTOR:
    if (ty->base->kind == TY_FLOAT || ty->base->kind == TY_DOUBLE) {
      println("  movups %%xmm0, (%%rdi)");  // store into rdi, not rax
    } else if (is_integer(ty->base)) {
      println("  movdqu %%xmm0, (%%rdi)");
    } else {
      error("%s %d: in store : unsupported vector base type %d", __FILE__, __LINE__, ty->base->kind);
    }
    return;
  case TY_STRUCT:
  case TY_UNION:
    gen_mem_copy("%rdi", ty->size);
    println("  mov %%rdi, %%rax");
    return;
  case TY_FLOAT:
    println("  movss %%xmm0, (%%rdi)");
    return;
  case TY_DOUBLE:
    println("  movsd %%xmm0, (%%rdi)");
    return;
  case TY_LDOUBLE:
    println("  fld %%st(0)");
    println("  fstpt (%%rdi)");
    return;
  case TY_INT128:
    println("  mov %%rax, (%%rdi)");
    println("  mov %%rdx, 8(%%rdi)");
    return;    
  }

  if (ty->size == 1)
    println("  mov %%al, (%%rdi)");
  else if (ty->size == 2)
    println("  mov %%ax, (%%rdi)");
  else if (ty->size == 4)
    println("  mov %%eax, (%%rdi)");
  else
    println("  mov %%rax, (%%rdi)");
}

static void cmp_zero(Type *ty)
{
  if (!ty)
    error("%s %d: in cmp_zero : ty is null!", __FILE__, __LINE__);
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

#define REDZONE(X)  \
  "sub\t$16,%rsp\n" \
  "\t" X "\n"       \
  "\tadd\t$16,%rsp"


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
  U128,
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
  case TY_LLONG:
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
static char i32i64[] = "movslq %eax, %rax";
static char i32f64[] = "cvtsi2sdl %eax, %xmm0";
static char i32f80[] = "mov %eax, -4(%rsp); fildl -4(%rsp)";

static char u32f32[] = "mov %eax, %eax; cvtsi2ssq %rax, %xmm0";
static char u32i64[] = "mov %eax, %eax";
static char u32f64[] = "mov %eax, %eax; cvtsi2sdq %rax, %xmm0";
static char u32f80[] = "mov %eax, %eax; mov %rax, -8(%rsp); fildll -8(%rsp)";

static char i64f32[] = "cvtsi2ssq %rax, %xmm0";
static char i64f64[] = "cvtsi2sdq %rax, %xmm0";
static char i64f80[] = "movq %rax, -8(%rsp); fildll -8(%rsp)";

static char u64f32[] =
  "test %rax,%rax; js 1f; pxor %xmm0,%xmm0; cvtsi2ss %rax,%xmm0; jmp 2f; "
  "1: mov %rax,%rdi; and $1,%eax; pxor %xmm0,%xmm0; shr %rdi; "
  "or %rax,%rdi; cvtsi2ss %rdi,%xmm0; addss %xmm0,%xmm0; 2:";
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
static char f32u64[] =
  "cvttss2siq %xmm0, %rcx; movq %rcx, %rdx; movl $0x5F000000, %eax; "
  "movd %eax, %xmm1; subss %xmm1, %xmm0; cvttss2siq %xmm0, %rax; "
  "sarq $63, %rdx; andq %rdx, %rax; orq %rcx, %rax;";
static char f32f64[] = "cvtss2sd %xmm0, %xmm0";
static char f32f80[] = "movss %xmm0, -4(%rsp); flds -4(%rsp)";

static char f64i8[] = "cvttsd2sil %xmm0, %eax; movsbl %al, %eax";
static char f64u8[] = "cvttsd2sil %xmm0, %eax; movzbl %al, %eax";
static char f64i16[] = "cvttsd2sil %xmm0, %eax; movswl %ax, %eax";
static char f64u16[] = "cvttsd2sil %xmm0, %eax; movzwl %ax, %eax";
static char f64i32[] = "cvttsd2sil %xmm0, %eax";
static char f64u32[] = "cvttsd2siq %xmm0, %rax";
static char f64i64[] = "cvttsd2siq %xmm0, %rax";
static char f64u64[] =
  "cvttsd2siq %xmm0, %rcx; movq %rcx, %rdx; mov $0x43e0000000000000, %rax; "
  "movq %rax, %xmm1; subsd %xmm1, %xmm0; cvttsd2siq %xmm0, %rax; "
  "sarq $63, %rdx; andq %rdx, %rax; orq %rcx, %rax";
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
static char f80u64[] =
  "movl $0x5f000000, -4(%rsp); flds -4(%rsp); fucomi %st(1), %st; setbe %al;"
  "fldz; fcmovbe %st(1), %st; fstp %st(1); fsubrp %st, %st(1); fnstcw -12(%rsp);"
  "movzwl -12(%rsp), %ecx; orl $3072, %ecx; movw %cx, -10(%rsp); fldcw -10(%rsp);"
  "fistpll -8(%rsp); fldcw -12(%rsp); shlq $63, %rax; xorq -8(%rsp), %rax;";

static char f80f32[] = "fstps -8(%rsp); movss -8(%rsp), %xmm0";
static char f80f64[] = "fstpl -8(%rsp); movsd -8(%rsp), %xmm0";


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
  if (!to)
    error("%s %d: in cast : to type is null!", __FILE__, __LINE__);    
  if (!from)
    from = copy_type(to);    
  if (to->kind == TY_VOID)
    return;

  if (to->kind == TY_BOOL)
  {
    cmp_zero(from);
    if (is_flonum(from)) {
      println("  setne %%al");
      println("  setp %%dl");
      println("  or %%dl, %%al");
   } else {
      println("  setne %%al");
   }

    println("  movzx %%al, %%eax");
    return;
  }

  if (is_vector(from) ||is_vector(to))
    return;

  int t1 = getTypeId(from);
  int t2 = getTypeId(to);
  if (cast_table[t1][t2])
    println("  %s", cast_table[t1][t2]);
}

// Returns true if 'ty' is or contains a pointer (recursively)
static bool has_pointer(Type *ty) {
  if (!ty)
    return false;

  switch (ty->kind) {
  case TY_PTR:
    return true;
  case TY_VECTOR:
  case TY_ARRAY:
    return has_pointer(ty->base);

  case TY_STRUCT:
  case TY_UNION: {
    for (Member *mem = ty->members; mem; mem = mem->next) {
      if (has_pointer(mem->ty))
        return true;
    }
    return false;
  }

  default:
    return false;
  }
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
static bool has_flonum(Type *ty, int lo, int hi, int offset) {
  if (ty->is_variadic && (ty->kind == TY_STRUCT || ty->kind == TY_UNION))
    return false;
    
  if (ty->kind == TY_STRUCT || ty->kind == TY_UNION) {
    for (Member *mem = ty->members; mem; mem = mem->next) {
      int tmpoffset = offset + mem->offset;
      if ((tmpoffset + mem->ty->size) <= lo)
        continue;
      if (hi <= tmpoffset)
        break;
      if (!has_flonum(mem->ty, lo, hi, tmpoffset))
        return false;
    }
    return true;
  }

  if (ty->kind == TY_ARRAY) {
    for (int i = 0; i < ty->array_len; i++) {
      int tmpoffset = offset + ty->base->size * i;
      if ((tmpoffset + ty->base->size) <= lo)
        continue;
      if (hi <= tmpoffset)
        break;
      if (!has_flonum(ty->base, lo, hi, tmpoffset))
        return false;
      }
    return true;
  }

  if (ty->kind == TY_VECTOR)
    return true;

  return ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE;
}


static bool has_flonum1(Type *ty)
{
  return has_flonum(ty, 0, 8, 0);
}

static bool has_flonum2(Type *ty)
{
  return has_flonum(ty, 8, 16, 0);
}

static bool has_longdouble(Type *ty) {
  if (!ty)
    return false;
  if (ty->kind == TY_LDOUBLE)
    return true;
  if (ty->kind != TY_STRUCT && ty->kind != TY_UNION)
    return false;

  for (Member *mem = ty->members; mem; mem = mem->next) {
    if (has_longdouble(mem->ty))
      return true;
  }
  return false;
}



static bool pass_by_reg(Type *ty, int gp, int fp) {
  if (ty->size > 16)
    return false;
  if (has_longdouble(ty))
    return false;
  int fp_inc = has_flonum1(ty) + (ty->size > 8 && has_flonum2(ty));
  int gp_inc = !has_flonum1(ty) + (ty->size > 8 && !has_flonum2(ty));

  if (fp_inc && (fp + fp_inc > FP_MAX))
    return false;
  if (gp_inc && (gp + gp_inc > GP_MAX))
    return false;
  
  if (ty->is_variadic && !has_flonum1(ty) && !has_pointer(ty))
    return false;

  return true;
}


static void push_struct(Node *arg)
{
    Type *ty = arg->ty;
    int min_align = has_longdouble(ty) ? 16 : 8;
    int align = MAX(ty->align, min_align);

    if (arg->pass_by_stack && arg->stack_offset >= 0) {
        gen_mem_copy_with_offset("%rsp", arg->stack_offset, ty->size);
    } else {
        int size = align_to(ty->size, align);
        println("  sub $%d, %%rsp", size);
        depth += size / 8;
        gen_mem_copy("%rsp", ty->size);
    }
}


static void push_args2(Node *args, bool first_pass)
{
  if (!args)
    return;
  push_args2(args->next, first_pass);

  if (first_pass != args->pass_by_stack)
    return;

  gen_expr(args);

  if (first_pass) {
    switch (args->ty->kind)
    {
    case TY_STRUCT:
    case TY_UNION:
      if (args->ty->size == 0)
        return;    
      push_struct(args);
      break;
    case TY_FLOAT:
      println("  movss %%xmm0, %d(%%rsp)", args->stack_offset);
      break;
    case TY_DOUBLE:
      println("  movsd %%xmm0, %d(%%rsp)", args->stack_offset);
      break;
    case TY_VECTOR:
      println("  movdqu %%xmm0, %d(%%rsp)", args->stack_offset);
      break;
    case TY_LDOUBLE:
      println("  fstpt %d(%%rsp)", args->stack_offset);
      break;
    case TY_INT128:
      println("  mov %%rax, %d(%%rsp)", args->stack_offset);
      println("  mov %%rdx, %d(%%rsp)", args->stack_offset + 8);
      break;
    default:
      println("  mov %%rax, %d(%%rsp)", args->stack_offset);
    }
  } else {
    switch (args->ty->kind)
    {
    case TY_STRUCT:
    case TY_UNION:
      if (args->ty->size == 0)
        return;    
      push_struct(args);
      break;
    case TY_VECTOR:
      pushv();
      break;
    case TY_FLOAT:
    case TY_DOUBLE:
      pushf();
      break;
    case TY_LDOUBLE:
      println("  sub $16, %%rsp");
      println("  fstpt (%%rsp)");
      depth += 2;
      break;
    case TY_INT128:
      pushx();
      break;    
    default:
      push();
    }
  }
}

// Calculate stack offsets for stack-passed arguments taking in account the alignment
static void calculate_stack_offsets(Node *args, int *stack_offset, int *max_align) {
  for (Node *arg = args; arg; arg = arg->next) {
    if (!arg->pass_by_stack) {
      arg->stack_offset = -1;
      continue;
    }

    Type *ty = arg->ty;
    int align = MAX(ty->align, 8);
    *max_align = MAX(*max_align, align);

    *stack_offset = align_to(*stack_offset, align);
    arg->stack_offset = *stack_offset;

    int arg_size = align_to(ty->size, 8); // At least 8 bytes on stack
    *stack_offset += arg_size;
  }
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
  int gp = 0, fp = 0;

  // If the return type is a large struct/union, the caller passes
  // a pointer to a buffer as if it were the first argument.
  if (node->ret_buffer && node->ty->size > 16)
    gp++;

  // Load as many arguments to the registers as possible.
  for (Node *arg = node->args; arg; arg = arg->next)
  {
    Type *ty = arg->ty;
    if (!ty)
      error("%s %d: in push_args : type is null!", __FILE__, __LINE__);  

    switch (ty->kind)
    {
    case TY_STRUCT:
    case TY_UNION:
      if (ty->size == 0)
        continue;

      if (pass_by_reg(ty, gp, fp) ) {
          fp += has_flonum1(ty) + (ty->size > 8 && has_flonum2(ty));
          gp += !has_flonum1(ty) + (ty->size > 8 && !has_flonum2(ty));
        } else {
          arg->pass_by_stack = true;
        }
        break;  
    case TY_VECTOR:
    case TY_FLOAT:
    case TY_DOUBLE:
      if (fp++ >= FP_MAX)
      {
        arg->pass_by_stack = true;
      }
      break;
    case TY_LDOUBLE:
      arg->pass_by_stack = true;
      break;
    case TY_INT128:
      if (gp + 1 >= GP_MAX) {
        arg->pass_by_stack = true;
      } else {
        gp += 2;
      }
      break;
    default:
      if (gp++ >= GP_MAX)
      {
        arg->pass_by_stack = true;
      }
    }
  }

  int stack_offset = 0;
  int max_align = 16;  
  
  calculate_stack_offsets(node->args, &stack_offset, &max_align);

  int total_stack_bytes = stack_offset;
  int stack_units = (total_stack_bytes + 7) / 8;

  if ((depth + stack_units) % 2 != 0)
  {
    stack_units++;
  }

  if (stack_units > 0) {
    println("  sub $%d, %%rsp", stack_units * 8);
    depth += stack_units;
  }

  if (max_align > 16) {
    println("  and $-%d, %%rsp", max_align);
  }

  push_args2(node->args, true);  // stack pass
  push_args2(node->args, false); // reg pass

  // If the return type is a large struct/union, the caller passes
  // a pointer to a buffer as if it were the first argument.
  if (node->ret_buffer && node->ty->size > 16)
  {
    println("  lea %d(%s), %%rax", node->ret_buffer->offset, node->ret_buffer->ptr);
    push();
  }

  return stack_units;
}

static void copy_ret_buffer(Obj *var)
{
  Type *ty = var->ty;
  if (!ty)
    error("%s %d: in copy_ret_buffer : type is null!", __FILE__, __LINE__);  

  int gp = 0, fp = 0;

    if (has_flonum1(ty)) {
        int offset = var->offset;
        if (is_omit_fp(current_fn))
          offset += current_fn->stack_size + depth * 8;

        // Allow sizes 4, 8, 12, and 16 for floating-point types
        assert(ty->size == 4 || ty->size == 8 || ty->size == 12 || ty->size == 16);

        if (ty->size == 4) {
            println("  movss %%xmm0, %d(%s)", offset, var->ptr);
        } else if (ty->size == 8) {
            println("  movsd %%xmm0, %d(%s)", offset, var->ptr);
        } else if (ty->size == 12 || ty->size == 16) {
            println("  movsd %%xmm0, %d(%s)", offset, var->ptr);
            if (ty->size == 12) {
                println("  movss %%xmm1, %d(%s)", offset + 8, var->ptr);
            } else if (ty->size == 16) {
                println("  movsd %%xmm1, %d(%s)", offset + 8, var->ptr);
            }
        }
    fp++;
    } else {
        int offset = var->offset;
        if (is_omit_fp(current_fn))
          offset += current_fn->stack_size + depth * 8;
        // **Change 1: Handle the first 8 bytes for integer types (up to 64 bits)**
        for (int i = 0; i < MIN(8, ty->size); i++) {
      println("  mov %%al, %d(%s)", offset + i, var->ptr);
      println("  shr $8, %%rax");
    }
    gp++;
  }

  if (ty->size > 8)
  {
    int offset = var->offset;
    if (is_omit_fp(current_fn))
      offset += current_fn->stack_size + depth * 8;
    if (has_flonum2(ty))
    {
      assert(ty->size == 12 || ty->size == 16);
      if (ty->size == 12)
        println("  movss %%xmm%d, %d(%s)", fp, offset + 8, var->ptr);
      else
        println("  movsd %%xmm%d, %d(%s)", fp, offset + 8, var->ptr);
    }
    else
    {
      char *reg1 = (gp == 0) ? "%al" : "%dl";
      char *reg2 = (gp == 0) ? "%rax" : "%rdx";
      for (int i = 8; i < MIN(16, ty->size); i++)
      {
        println("  mov %s, %d(%s)", reg1, offset + i, var->ptr);
        println("  shr $8, %s", reg2);
      }
    }
  }
}

static void copy_struct_reg(void)
{
  Type *ty = current_fn->ty->return_ty;
  if (!ty)
    error("%s %d: in copy_struct_reg : type is null!", __FILE__, __LINE__);  
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

  if (!ty)
    error("%s %d: in copy_struct_mem : type is null!", __FILE__, __LINE__);  
  Obj *var = current_fn->params;
  if (is_omit_fp(current_fn))
    println("  mov %d(%%rsp), %%rdi", var->offset + current_fn->stack_size + depth * 8);
  else
    println("  mov %d(%s), %%rdi", var->offset, var->ptr);
  gen_mem_copy("%rdi", ty->size);
  //from @fuhsnn Copy returned-by-stack aggregate's pointer to rax
  println("  mov %%rdi, %%rax");
}

static void builtin_alloca(Node *node)
{
  // Align the resulting pointer, not just the size.
  int align = node->val > 16 ? node->val : 16;

  if (!current_fn->alloca_bottom) {
    // new_rsp = (rsp - size) & -align; return new_rsp
    println("  mov %%rsp, %%rax");
    println("  sub %%rdi, %%rax");
    println("  and $-%d, %%rax", align);
    println("  mov %%rax, %%rsp");
    return;
  }

  // Shift the temporary area by delta, where:
  // new_bottom = (old_bottom - size) & -align
  // delta = old_bottom - new_bottom
  println("  mov %d(%s), %%rax", current_fn->alloca_bottom->offset, current_fn->alloca_bottom->ptr); // old_bottom
  println("  mov %%rax, %%rcx");
  println("  sub %%rsp, %%rcx"); // tmp_size
  println("  mov %%rax, %%rdx");
  println("  sub %%rdi, %%rdx");
  println("  and $-%d, %%rdx", align); // new_bottom
  println("  mov %%rax, %%rsi");
  println("  sub %%rdx, %%rsi"); // delta

  println("  mov %%rsp, %%r8");  // old_rsp (src)
  println("  sub %%rsi, %%rsp"); // new_rsp
  println("  mov %%rsp, %%r9");  // new_rsp (dst)

  println("1:");
  println("  cmp $0, %%rcx");
  println("  je 2f");
  println("  mov (%%r8), %%r10b");
  println("  mov %%r10b, (%%r9)");
  println("  inc %%r8");
  println("  inc %%r9");
  println("  dec %%rcx");
  println("  jmp 1b");
  println("2:");

  // Move alloca_bottom pointer and return new_bottom in rax
  println("  mov %%rdx, %d(%s)", current_fn->alloca_bottom->offset, current_fn->alloca_bottom->ptr);
  println("  mov %%rdx, %%rax");
}

//from cosmopolitan
static void HandleAtomicArithmetic(Node *node, const char *op, bool return_new) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);

  if (node->ty->size == 16) {
    println("  mov %%rax, %%r8"); // val low
    println("  mov %%rdx, %%r9"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  mov %%rdx, %%rcx");
    
    println("  %s %%r8, %%rbx", op);
    println("  %s %%r9, %%rcx", op);

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    if (return_new) {
        println("  mov %%rbx, %%rax");
        println("  mov %%rcx, %%rdx");
    }
    return;
  }

  pop_tmp("%r9");
  println("  mov %s, %s", reg_ax(node->ty->size), reg_si(node->ty->size));
  println("  mov (%%r9), %s", reg_ax(node->ty->size));
  println("1:  mov %s, %s", reg_ax(node->ty->size), reg_dx(node->ty->size));
  println("  mov %s, %s", reg_ax(node->ty->size), reg_di(node->ty->size));
  println("  %s %s, %s", op, reg_si(node->ty->size), reg_dx(node->ty->size));
  println("  lock cmpxchg %s, (%%r9)", reg_dx(node->ty->size));
  println("  jnz 1b");
  if (return_new)
    println("  mov %s, %s", reg_dx(node->ty->size), reg_ax(node->ty->size));
  else
    println("  mov %s, %s", reg_di(node->ty->size), reg_ax(node->ty->size));

}

static void gen_memset(Node *node) {
  if (opt_fbuiltin) {    
    gen_expr(node->builtin_dest);
    push_tmp();
    gen_expr(node->builtin_val);
    push_tmp();
    gen_expr(node->builtin_size);
    push_tmp();
    pop_tmp("%rcx");  
    pop_tmp("%rsi");  
    pop_tmp("%rdi");  
    println("  mov %%rdi, %%r8");
    println("  mov %%sil, %%al");  
    println("  cld");
    println("  rep stosb");  
    println("  mov %%r8, %%rax");
  }     
}

static void gen_memcpy(Node *node) {
  if (opt_fbuiltin) {    
    gen_expr(node->builtin_dest);   
    push_tmp();                         
    gen_expr(node->builtin_src);    
    push_tmp();                         
    gen_expr(node->builtin_size);   
    println("  mov %%rax, %%rcx");  
    pop_tmp("%rsi");                    
    pop_tmp("%rdi");                   
    println("  mov %%rdi, %%rax");
    println("  cld");
    println("  rep movsb");
    return;
  }
}


static void gen_int128_op(Node *node) {
    if (node->rhs) {
      gen_expr(node->rhs);
      pushx_tmp();
    }
    gen_expr(node->lhs);
    if (node->rhs)
      popx_tmp("%rdi", "%rsi");

  switch (node->kind) {
    case ND_ADD:
      println("  add %%rdi, %%rax");
      println("  adc %%rsi, %%rdx");
      break;
    case ND_SUB:
      println("  sub %%rdi, %%rax");
      println("  sbb %%rsi, %%rdx"); 
      break;
    case ND_MUL:
      println("  imul %%rdi, %%rdx");
      println("  imul %%rax, %%rsi");
      println("  add %%rdx, %%rsi");
      println("  mul %%rdi");
      println("  add %%rsi, %%rdx");     
      break; 
    case ND_DIV:
    case ND_MOD:
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
      break;    
    case ND_NEG:
      println("  neg %%rax");
      println("  adc $0, %%rdx");
      println("  neg %%rdx");
      break;
    case ND_BITNOT:
      println("  not %%rax");
      println("  not %%rdx");  
      break;    
    case ND_BITAND:
      println("  and %%rdi, %%rax");
      println("  and %%rsi, %%rdx");  
      break;
    case ND_BITOR:
      println("  or %%rdi, %%rax");
      println("  or %%rsi, %%rdx");    
      break; 
    case ND_BITXOR:
      println("  xor %%rdi, %%rax");
      println("  xor %%rsi, %%rdx");   
      break;  
    case ND_EQ:
      println("  mov %%rax, %%r8"); // Move lower 64 bits of lhs to r8
      println("  mov %%rdx, %%r9"); // Move upper 64 bits of lhs to r9
      println("  xor %%r8, %%rdi"); // Compare lower 64 bits of lhs and rhs
      println("  xor %%r9, %%rsi"); // Compare upper 64 bits of lhs and rhs
      println("  or %%rsi, %%rdi"); // Combine the results
      println("  sete %%al");       // Set AL if the result is zero (equal)
      println("  movzx %%al, %%eax"); // Zero extend AL to EAX            
      break;
    case ND_NE:
      println("  xor %%rax, %%rdi");
      println("  xor %%rdx, %%rsi");
      println("  or %%rsi, %%rdi");
      println("  setne %%al");
      println("  movzb %%al, %%rax");  // Zero-extend al to rax to ensure the whole rax is correctly set
      break;
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
      break;
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
      break;   
    case ND_SHL:
        println("  mov %%rdi, %%rcx");  
        println("  shld %%cl, %%rax, %%rdx");
        println("  shl %%cl, %%rax");
        println("  xor %%edi, %%edi");
        println("  and $64, %%cl");
        println("  cmovne %%rax, %%rdx");
        println("  cmovne %%rdi, %%rax");  
      break;  
    case ND_SHR: {
      int c = count();
      // Move shift amount to CL register
      println("  mov %%rdi, %%rcx");
      if (node->lhs->ty->is_unsigned) {
        // Handle unsigned 128-bit shift right
        println("  cmp $64, %%rcx");
        println("  jae .Lshift_gt64_unsigned_%d", c);

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
        println("  jae .Lshift_gt64_signed_%d", c);

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
      break;
    }
    default:
        error_tok(node->tok,"%s: %s:%d: error: in gen_int128_op : unsupported int128 operation %d", __FILE__, __FILE__, __LINE__, node->kind);
    }
}

static void scalar_to_xmm(Type *vec_ty, const char *xmm_reg) {
    switch (vec_ty->base->kind) {
    case TY_INT:
      println("  movd %%eax, %s", xmm_reg);      
      println("  pshufd $0x0, %s, %s", xmm_reg, xmm_reg); 
      break; 
    case TY_LLONG:
    case TY_LONG:
      println("  movq %%rax, %s", xmm_reg);       
      println("  movddup %s, %s", xmm_reg, xmm_reg); 
      break; 
    case TY_FLOAT:
      println("  shufps $0x00, %s, %s", xmm_reg, xmm_reg);
      break;
    case TY_DOUBLE:
      println("  shufpd $0x00, %s, %s", xmm_reg, xmm_reg);
      break;
    default:
      error("%s: %s:%d: error: in scalar_to_xmm : unsupported vector base type for scalar promotion %d", __FILE__, __FILE__, __LINE__, vec_ty->base->kind);
    }
}


static void gen_vector_op(Node *node) {
  if (node->rhs) {
    gen_expr(node->rhs);
    if (node->rhs->is_scalar_promoted)
      scalar_to_xmm(node->rhs->ty, "%xmm0");
    push_xmm(0);      
  }
  if (node->lhs) {
    gen_expr(node->lhs); 
    if (node->lhs->is_scalar_promoted)
      scalar_to_xmm(node->lhs->ty, "%xmm0");
  }
  
  if (node->rhs)
    pop_xmm(1);


  switch (node->kind) {
  case ND_ADD:
  case ND_SUB:
  case ND_MUL:
    break;
  case ND_BITXOR:
  case ND_BITAND:
  case ND_BITOR:
  case ND_BITNOT:
    break;
  case ND_DIV:
    if (is_integer(node->lhs->ty->base))
      error_tok(node->tok, "%s: %s:%d: error: in gen_vector_op :  integer vector division not supported", __FILE__, __FILE__, __LINE__);
    break;
  case ND_NEG:
    //gen_expr(node->lhs);          // materialize operand in %xmm0
    break;    
  default:
    error_tok(node->tok, "%s: %s:%d: error: in gen_vector_op :  unsupported vector operation %d", __FILE__, __FILE__, __LINE__, node->kind);
  }

  Type *vec_ty = node->lhs->ty;
  if (vec_ty->kind == TY_PTR && vec_ty->base->kind == TY_VECTOR)
    vec_ty = vec_ty->base;

  if (vec_ty->kind != TY_VECTOR)
    error_tok(node->tok, "%s: %s:%d: error: in gen_vector_op : lhs is not a vector", __FILE__, __FILE__, __LINE__);

  // if (node->rhs)
  //   load_vector_operand(node->rhs, "%xmm1");    
  // load_vector_operand(node->lhs, "%xmm0");


  switch (vec_ty->base->kind) {
    case TY_FLOAT:
      switch (node->kind) {
      case ND_ADD:
        println("  addps %%xmm1, %%xmm0");
        break;
      case ND_SUB:
        println("  subps %%xmm1, %%xmm0");
        break;
      case ND_MUL:
        println("  mulps %%xmm1, %%xmm0");
        break;
      case ND_DIV:
        println("  divps %%xmm1, %%xmm0");
        break;
      case ND_BITXOR:
        println("  pxor %%xmm1, %%xmm0");
        break;
      case ND_BITAND:
        println("  pand %%xmm1, %%xmm0");
        break;
      case ND_BITOR:
        println("  por %%xmm1, %%xmm0");
        break;
      case ND_NEG: 
        println("  xorps %%xmm1, %%xmm1");     
        println("  subps %%xmm0, %%xmm1");     
        println("  movups %%xmm1, %%xmm0"); 
        break;                
      default:
        error_tok(node->tok, "%s: %s:%d: error: unsupported float vector operation", __FILE__, __FILE__, __LINE__);
      }
      break;
  case TY_DOUBLE:
    switch (node->kind) {
    case ND_ADD:
      println("  addpd %%xmm1, %%xmm0");
      break;
    case ND_SUB:
      println("  subpd %%xmm1, %%xmm0");
      break;
    case ND_MUL:
      println("  mulpd %%xmm1, %%xmm0");
      break;
    case ND_DIV:
      println("  divpd %%xmm1, %%xmm0");
      break;
    case ND_BITXOR:
      println("  pxor %%xmm1, %%xmm0");
      break;
    case ND_BITAND:
      println("  pand %%xmm1, %%xmm0");
      break;
    case ND_BITOR:
      println("  por %%xmm1, %%xmm0");
      break;
    case ND_NEG: 
      println("  xorpd %%xmm1, %%xmm1");     
      println("  subpd %%xmm0, %%xmm1");     
      println("  movapd %%xmm1, %%xmm0");  
      break;      
    default:
      error_tok(node->tok, "%s: %s:%d: error: unsupported double vector operation", __FILE__, __FILE__, __LINE__);
    }
    break;
  case TY_LLONG:
  case TY_LONG:
    switch (node->kind) {
    case ND_ADD:
      println("  paddq %%xmm1, %%xmm0");
      break;
    case ND_SUB:
      println("  psubq %%xmm1, %%xmm0");
      break;
    case ND_MUL:
      println("  pmulld %%xmm1, %%xmm0"); // Note: no native 64-bit integer multiply in SSE2; might need scalar fallback
      break;
    case ND_BITXOR:
      println("  pxor %%xmm1, %%xmm0");
      break;
    case ND_BITAND:
      println("  pand %%xmm1, %%xmm0");
      break;
    case ND_BITOR:
      println("  por %%xmm1, %%xmm0");
      break;
    case ND_NEG:
      println("  pxor %%xmm1, %%xmm1");
      println("  psubq %%xmm0, %%xmm1");
      println("  movdqa %%xmm1, %%xmm0");
      break;
    case ND_BITNOT:
      println("  pcmpeqq %%xmm1, %%xmm1"); // SSE4.1; for SSE2 use two 32-bit pcmpeqd and pack
      println("  pxor %%xmm1, %%xmm0");
      break;
    default:
      error_tok(node->tok, "%s: %s:%d: error: long vector operation not supported", __FILE__, __FILE__, __LINE__);
    }
    break;
  case TY_INT:
    switch (node->kind) {
    case ND_ADD:
      println("  paddd %%xmm1, %%xmm0");
      break;
    case ND_SUB:
      println("  psubd %%xmm1, %%xmm0");
      break;
    case ND_MUL:
      println("  pmulld %%xmm1, %%xmm0");
      break;
    case ND_BITXOR:
      println("  pxor %%xmm1, %%xmm0");
      break;
    case ND_BITAND:
      println("  pand %%xmm1, %%xmm0");
      break;
    case ND_BITOR:
      println("  por %%xmm1, %%xmm0");
      break;
    case ND_NEG: 
      println("  pxor %%xmm1, %%xmm1");      
      println("  psubd %%xmm0, %%xmm1");     
      println("  movdqa %%xmm1, %%xmm0");
      break;
    case ND_BITNOT:
      println("  pcmpeqd %%xmm1, %%xmm1"); 
      println("  pxor %%xmm1, %%xmm0");  
      break;      
    default:
      error_tok(node->tok, "%s: %s:%d: error: integer vector operation not supported", __FILE__, __FILE__, __LINE__);
    }
    break;
  }
}

static void gen_cmpxchg(Node *node) {
  int sz = node->cas_ptr->ty->base->size;
  gen_expr(node->cas_ptr);
  push_tmp();
  gen_expr(node->cas_expected);
  push_tmp();
  gen_expr(node->cas_desired);      
  println("  mov %%rax, %%rcx");
  pop_tmp("%rsi");
  pop_tmp("%rdi");

  if (sz == 16) {
     println("  mov %%rcx, %%r8"); // desired ptr
     
     println("  mov (%%r8), %%rbx");
     println("  mov 8(%%r8), %%rcx");
     
     println("  mov (%%rsi), %%rax");
     println("  mov 8(%%rsi), %%rdx");
     
     println("  lock cmpxchg16b (%%rdi)");
     
     println("  je 1f");
     println("  mov %%rax, (%%rsi)");
     println("  mov %%rdx, 8(%%rsi)");
     println("1:");
     println("  sete %%al");
     println("  movzbl %%al, %%eax");
     if (node->cas_success || node->cas_failure) {
        println("  mfence");
     }
     return;
  }

  if (sz == 1) {
    println("  movb (%%rcx), %%cl");
  } else if (sz == 2) {
    println("  movw (%%rcx), %%cx");
  } else if (sz == 4) {
    println("  movl (%%rcx), %%ecx");
  } else if (sz == 8) {
    println("  movq (%%rcx), %%rcx");
  }
  if (sz == 1) {
    println("  movb (%%rsi), %%al");
  } else if (sz == 2) {
    println("  movw (%%rsi), %%ax");
  } else if (sz == 4) {
    println("  movl (%%rsi), %%eax");
  } else if (sz == 8) {
    println("  movq (%%rsi), %%rax");
  }
  println("  lock cmpxchg %s, (%%rdi)", reg_cx(sz));
  println("  je 1f");
  println("  mov %s, (%%rsi)", reg_ax(sz));
  println("1:");
  println("  sete %%al");
  println("  movzbl %%al, %%eax");

  if (node->cas_success || node->cas_failure) {
    println("  mfence");
  }
}


static void gen_cmpxchgn(Node *node) {
    int sz = node->cas_ptr->ty->base->size;
    gen_expr(node->cas_ptr);
    push_tmp();
    gen_expr(node->cas_expected);
    push_tmp();
    gen_expr(node->cas_desired);
    if (node->cas_desired->ty->kind == TY_FLOAT)
        println("  movd %%xmm0, %%eax");
    else if (node->cas_desired->ty->kind == TY_DOUBLE)
        println("  movq %%xmm0, %%rax");
    println("  mov %%rax, %%rcx");

    if (sz == 16) {
        println("  mov %%rax, %%rbx");
        println("  mov %%rdx, %%rcx");
        pop_tmp("%rsi");
        pop_tmp("%rdi");

        println("  mov (%%rsi), %%rax");
        println("  mov 8(%%rsi), %%rdx");

        println("  lock cmpxchg16b (%%rdi)");

        println("  je 1f");
        println("  mov %%rax, (%%rsi)");
        println("  mov %%rdx, 8(%%rsi)");
        println("1:");
        println("  sete %%al");
        println("  movzbl %%al, %%eax");
        if (node->cas_success || node->cas_failure) {
            println("  mfence");
        }
        return;
    }

    pop_tmp("%rsi");
    pop_tmp("%rdi");

    if (sz == 1) println("  movb (%%rsi), %%al");
    else if (sz == 2) println("  movw (%%rsi), %%ax");
    else if (sz == 4) println("  movl (%%rsi), %%eax");
    else println("  movq (%%rsi), %%rax");

    if (sz == 1) {
        println("  lock cmpxchg %%cl, (%%rdi)");
    } else if (sz == 2) {
        println("  lock cmpxchg %%cx, (%%rdi)");
    } else if (sz == 4) {
        println("  lock cmpxchg %%ecx, (%%rdi)");
    } else if (sz == 8) {
        println("  lock cmpxchg %%rcx, (%%rdi)");
    }
    
    println("  je 1f");
    if (sz == 1) println("  movb %%al, (%%rsi)");
    else if (sz == 2) println("  movw %%ax, (%%rsi)");
    else if (sz == 4) println("  movl %%eax, (%%rsi)");
    else println("  movq %%rax, (%%rsi)");
    println("1:");

    println("  sete %%al");
    println("  movzbl %%al, %%eax");
    if (node->cas_success || node->cas_failure) {
        println("  mfence");
    }
}

static void gen_signbit(Node *node) {  
  gen_expr(node->lhs);
  switch (node->lhs->ty->kind) {
  case TY_FLOAT:
    println("  movd %%xmm0, %%eax");
    println("  shr $31, %%eax");
    return;
  case TY_DOUBLE:
    println("  movmskpd %%xmm0, %%eax"); 
    println("  and $1, %%eax");         
    return;
  case TY_LDOUBLE:
    // println("  fxam");
    // println("  fnstsw %%ax");
    // println("  fstp %%st(0)");
    // println("  and $0x200, %%eax");
    println("  sub $16, %%rsp");
    println("  fstpt (%%rsp)");
    println("  movb 9(%%rsp), %%al");   // Get the byte containing the sign bit
    println("  shr $7, %%al");          // Move sign bit to LSB
    println("  movzbl %%al, %%eax");    // Zero-extend to EAX
    println("  add $16, %%rsp");
    return;
  default:
    unreachable();
  }
}

static void gen_isunordered(Node *node) {
  if (node->lhs->ty && node->rhs->ty && (node->lhs->ty->kind == TY_LDOUBLE || node->rhs->ty->kind == TY_LDOUBLE)) {
    gen_expr(node->lhs);
    pushld();
    gen_expr(node->rhs);
    popld();
    println("  fucomip");
    println("  fstp %%st(0)");
    println("  setp %%al");
    println("  movzx %%al, %%eax");
    return;
  }
  gen_expr(node->lhs);
  push_tmpf();
  gen_expr(node->rhs);
  pop_tmpf(1);
  if (node->lhs->ty->kind == TY_DOUBLE)
    println("  ucomisd %%xmm1, %%xmm0");
  else
    println("  ucomiss %%xmm1, %%xmm0");
  println("  setp %%al");
  println("  movzx %%al, %%eax");
  return;
}

static void gen_builtin(Node *node, const char *insn, const char *reg) {
    gen_expr(node->builtin_val); 
    println("  %s %%%s, %%%s", insn, reg, reg); 
}

static void gen_vec_init_v2si(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rdx");
  println("  shl $32, %%rax");    
  println("  or %%rdx, %%rax");  
  println("  movq %%rax, %%xmm0");
}


static void gen_vec_ext(Node *node) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  println("  movslq %%eax, %%rcx");
  println("  and $%d, %%ecx", node->kind == ND_VECEXTV2SI ? 1 : 3);
  println("  movl (%%rsp,%%rcx,4), %%eax");
  pop_xmm(0);
}

static void gen_vec_init_binop(Node *node, const char *insn) {
  for (int i = 0; i < node->builtin_nargs; i++) {
    if (i == 0) {
        gen_expr(node->builtin_args[i]);  // result in %eax
        println("  movd %%eax, %%xmm0");
    } else {
        // Preserve previously packed lanes across arg evaluation.
        push_xmm(0);
        gen_expr(node->builtin_args[i]);  // result in %eax
        pop_xmm(0);
        println("  %s $%d, %%eax, %%xmm0", insn, i);
    }
  } 
}

static void gen_pshufd(Node *node) {
  gen_expr(node->lhs);
  int imm = node->rhs->val;
  println("  pshufd $%d, %%xmm0, %%xmm0", imm);
}


static void gen_shuf_binop(Node *node, const char *insn) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(1);
  println("  %s $%ld, %%xmm1, %%xmm0", insn, node->rhs->val);
}

static void gen_psll_binop(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  if (node->rhs->kind == ND_NUM)
    println("  %s $%ld, %%xmm1", insn, node->rhs->val);
  else {
    println("  movq %%rax, %%xmm0");
    println("  %s %%xmm0, %%xmm1", insn);
  }
  println("  movups %%xmm1, %%xmm0");      
}


// Walk node to find a numeric constant. Works for ND_ASSIGN, ND_COMMA, ND_CAST etc.
static int get_const_int_from_node(Node *node) {
  if (!node)
    error("%s: %s:%d: error: in get_const_int_from_node : expected constant node", __FILE__, __FILE__, __LINE__);
  while (true) {
    if (node->kind == ND_NUM) return node->val;
    if (node->kind == ND_CAST) { node = node->lhs; continue; }
    if (node->kind == ND_COMMA) { node = node->rhs; continue; }
    if (node->kind == ND_ASSIGN) { node = node->rhs; continue; }
    break;
  }

  error_tok(node->tok, "%s: %s:%d: error: in get_const_int_from_node : not a compile-time integer constant", __FILE__, __FILE__, __LINE__);
 
}

static Node *unwrap_casts(Node *node) {
  while (node && (node->kind == ND_CAST || node->kind == ND_COMMA))
    node = node->lhs;
  return node;
}

// Fill vals[] with mask_node->var->ty->array_len ints (expect 4).
static void get_mask_values(Node *mask_node, int *vals, int expected_len) {
  mask_node = unwrap_casts(mask_node);
  if (!mask_node->var || !mask_node->var->init)
    error_tok(mask_node->tok, "%s: %s:%d: error: in get_mask_values : shuffle mask must be a constant vector initializer! %d", __FILE__, __FILE__, __LINE__, mask_node->kind);

  Initializer *init = mask_node->var->init;
  int len = mask_node->var->ty->array_len;

  for (int i = 0; i < len; i++) {
    Initializer *elem = init->children[i];
    vals[i] = get_const_int_from_node(elem->expr);
  }
}


// Try to find imm1/imm2 (two shufps immediates) that produce mask[0..3].
// Returns true on success.
static bool decompose_shuffle_mask_from_vals(int mask[4], int *out_imm1, int *out_imm2) {
  // mask entries must be 0..7
  for (int i = 0; i < 4; i++) if (mask[i] < 0 || mask[i] > 7) return false;

  for (int comb = 0; comb < (1 << 4); comb++) {
    int idx[4];
    int ia[2] = {-1,-1}, ib[2] = {-1,-1};
    bool ok = true;

    for (int j = 0; j < 4; j++) {
      int bit = (comb >> j) & 1;
      if (mask[j] < 4) idx[j] = bit;        // from a -> index 0/1 in intermediate
      else idx[j] = 2 + bit;               // from b -> index 2/3 in intermediate

      if (idx[j] < 2) {
        if (ia[idx[j]] == -1) ia[idx[j]] = mask[j];
        else if (ia[idx[j]] != mask[j]) { ok = false; break; }
      } else {
        int k = idx[j] - 2;
        if (ib[k] == -1) ib[k] = mask[j] - 4;
        else if (ib[k] != mask[j] - 4) { ok = false; break; }
      }
    }
    if (!ok) continue;

    for (int t = 0; t < 2; t++) { if (ia[t] == -1) ia[t] = 0; if (ib[t] == -1) ib[t] = 0; }

    int imm1 = (ia[0] & 3) | ((ia[1] & 3) << 2) | ((ib[0] & 3) << 4) | ((ib[1] & 3) << 6);
    int imm2 = (idx[0] & 3) | ((idx[1] & 3) << 2) | ((idx[2] & 3) << 4) | ((idx[3] & 3) << 6);

    // simulate
    int intermediate[4];
    intermediate[0] = ia[0];            // reference a indices 0..3 treated as 0..3
    intermediate[1] = ia[1];
    intermediate[2] = ib[0] + 4;       // convert back to 4..7
    intermediate[3] = ib[1] + 4;

    int final[4];
    for (int j = 0; j < 4; j++) final[j] = intermediate[(imm2 >> (2*j)) & 3];

    bool match = true;
    for (int j = 0; j < 4; j++) if (final[j] != mask[j]) { match = false; break; }
    if (!match) continue;

    *out_imm1 = imm1;
    *out_imm2 = imm2;
    return true;
  }
  return false;
}

static void gen_shuffle(Node *node, const char *insn) {
  assert(node->builtin_nargs == 3);
  // Evaluate args so %xmm0 ends with lhs and %xmm1 ends with rhs as before:
  gen_expr(node->builtin_args[0]);        // leaves a in %xmm0
  println("  movups %%xmm0, %%xmm2");     // save a in xmm2
  gen_expr(node->builtin_args[1]);        // leaves b in %xmm0
  println("  movups %%xmm0, %%xmm1");     // save b in xmm1
  println("  movups %%xmm2, %%xmm0");     // restore a into xmm0 (dest)
  // read the 4 mask values
  int mask[4];
  get_mask_values(node->builtin_args[2], mask, 4);
  // try to decompose into two shufps immediates
  int imm1, imm2;
  if (decompose_shuffle_mask_from_vals(mask, &imm1, &imm2)) {
    // emit exactly what GCC emits
    println("  %s $%d, %%xmm1, %%xmm0", insn, imm1); // shufps imm1, xmm1, xmm0
    println("  %s $%d, %%xmm0, %%xmm0", insn, imm2); // shufps imm2, xmm0, xmm0
  } else {
    // fallback: try a single shufps immediate (simple encode) or emit more general sequence
    // Build single-byte immediate where bits are (lane3<<6)|(lane2<<4)|(lane1<<2)|lane0
    int single = ((mask[3] & 3) << 6) | ((mask[2] & 3) << 4) | ((mask[1] & 3) << 2) | (mask[0] & 3);
    println("  %s $%d, %%xmm1, %%xmm0", insn, single);
  }
}

static void gen_maskmovq(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); 
  println("  movq (%%rax), %%mm1"); 
  gen_expr(node->builtin_args[0]);  
  println("  movq (%%rax), %%mm0");       
  gen_addr(node->builtin_args[2]); 
  println("  movq %%rax, %%rdi"); 
  println("  maskmovq %%mm1, %%mm0");
  println("  emms");
}


static void gen_maskmovdqu(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); 
  println("  movdqu (%%rax), %%xmm1"); 
  gen_expr(node->builtin_args[0]);  
  println("  movdqu (%%rax), %%xmm0");       
  gen_addr(node->builtin_args[2]); 
  println("  movq %%rax, %%rdi"); 
  println("  maskmovdqu %%xmm1, %%xmm0");
}

static void gen_cvtpi2ps(Node *node) {
  gen_expr(node->lhs);    
  gen_addr(node->rhs);    
  println("  movq (%%rax), %%mm0"); 
  println("  cvtpi2ps %%mm0, %%xmm0");  
  println("  emms");
} 

static void gen_loadhps(Node *node) {
  gen_expr(node->lhs);
  println("  movups (%%rax), %%xmm0");
  push_xmm(0);
  gen_expr(node->rhs);
  println("  movq (%%rax), %%xmm1");
  pop_xmm(0);
  println("  movlhps %%xmm1, %%xmm0");
}

static void gen_packss128_binop(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs); 
  pop_xmm(1); 
  println("  %s %%xmm0, %%xmm1", insn); 
  println("  movdqu %%xmm1, %%xmm0");
}


static void gen_alloc(Node *node) {
  gen_expr(node->lhs); // Assume size to allocate is in RAX
  println("  mov %%rax, %%rdi"); // Move size to RDI (or appropriate register)
  println("  sub %%rdi, %%rsp"); // Allocate space on the stack
  println("  mov %%rsp, %%rax"); // Store the new stack pointer (allocated memory address) in RAX
}

static void gen_release(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%rax, %%rdi");
  
  if (node->ty->size == 16) {
      println("  xor %%rax, %%rax");
      println("  mov %%rax, (%%rdi)");
      println("  mov %%rax, 8(%%rdi)");
      return;
  }

  println("  xor %%eax, %%eax");
  println("  mov %s, (%%rdi)", reg_ax(node->ty->size));
}

static void gen_rdtsc(Node *node) {
  println("  rdtsc");
  println("  shl $32, %%rdx");
  println("  or %%rdx, %%rax");
}

static void gen_rdpkru(Node *node) {
  println("  movl $0, %%eax");
  println("  movl %%eax, %%ecx");
  println("  rdpkru");
}

static void gen_bsrsi(Node *node) {
  gen_expr(node->lhs);
  println("  bsrl %%eax, %%eax");
}

static void gen_bsrdi(Node *node) {
  gen_expr(node->lhs);
  println("  bsrq %%rax, %%rax");
}

static void gen_rdpmc(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%eax, %%ecx"); 
  println("  rdpmc");
}

static void gen_rdtscp(Node *node) {
  gen_expr(node->lhs);
  println("  movq %%rax, %%rdi");
  println("  rdtscp");        
  println("  movl %%ecx, (%%rdi)"); 
  println("  movl %%edx, %%edx");  
  println("  salq $32, %%rdx");      
  println("  or %%rdx, %%rax");     
}

static void gen_rolqi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%al, %%bl"); 
  gen_expr(node->rhs); 
  println("  mov %%al, %%cl");  
  println("  rolb %%cl, %%bl"); 
  println("  movzb %%bl, %%rax"); 
}

static void gen_rorqi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%al, %%bl"); 
  gen_expr(node->rhs); 
  println("  mov %%al, %%cl");  
  println("  rorb %%cl, %%bl"); 
  println("  movzb %%bl, %%rax"); 
}

static void gen_rolhi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%ax, %%bx");  
  gen_expr(node->rhs);  
  println("  mov %%al, %%cl"); 
  println("  rolw %%cl, %%bx");
  println("  movzx %%bx, %%rax");  
}

static void gen_rorhi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%ax, %%bx");  
  gen_expr(node->rhs);  
  println("  mov %%al, %%cl"); 
  println("  rorw %%cl, %%bx");
  println("  movzx %%bx, %%rax");  
}

static void gen_readeflags_u64(Node *node) {
  println("  pushfq");
  println("  popq %%rax");
}

static void gen_writeeflags_u64(Node *node) {
  gen_expr(node->lhs);
  println("  pushq $%ld", node->lhs->val);
  println("  popfq");
}

static void gen_incsspq(Node *node) {
  gen_expr(node->lhs);
  println("  incsspq %%rax");
}

static void gen_rstorssp(Node *node) {
  gen_addr(node->lhs);
  println("  rstorssp (%%rax)");
}

static void gen_wrssd(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrssd %%eax, (%%rdx)");
}

static void gen_wrssq(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrssq %%rax, (%%rdx)");
}

static void gen_wrussd(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrussd %%eax, (%%rdx)");
}

static void gen_wrussq(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrussq %%rax, (%%rdx)");
}

static void gen_clrssbsy(Node *node) {
  gen_expr(node->lhs);
  if (node->lhs->kind == ND_NUM)
    println("  clrssbsy %ld", node->lhs->val);
  else
    println("  clrssbsy (%%rax)");
}

static void gen_sbb_u32(Node *node) { 
  gen_expr(node->builtin_args[0]);
  println("  movl %%eax, %%edi");
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, %%esi");    
  gen_expr(node->builtin_args[2]);
  println("  movl %%eax, %%edx");    
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");    
  println("  movl %%edi, %%eax");
  println("  bt $0, %%edx");
  println("  sbbl %%esi, %%eax");
  println("  setc %%dl");
  println("  movzbl %%dl, %%edx");
  println("  movl %%edx, (%%rcx)");
}

static void gen_sbb_u64(Node *node) { 
  gen_expr(node->builtin_args[0]);
  println("  movq %%rax, %%rdi");
  gen_expr(node->builtin_args[1]);
  println("  movq %%rax, %%rsi");    
  gen_expr(node->builtin_args[2]);
  println("  movq %%rax, %%rdx");    
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");    
  println("  movq %%rsi, %%rax");
  println("  sbbq %%rdx, %%rax");
  println("  sbbq %%rdi, %%rax");
  println("  movq %%rax, (%%rcx)");
  println("  setc %%al");
}


static void gen_addcarryx_u32(Node *node) { 
  gen_expr(node->builtin_args[0]);
  println("  movb %%al, %%dil");
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, %%esi");    
  gen_expr(node->builtin_args[2]);
  println("  movl %%eax, %%edx");    
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");    
  println("  movl %%esi, %%eax");
  println("  movzx %%dil, %%r8d ");
  println("  addl %%edx, %%eax");
  println("  addl %%r8d, %%eax");
  println("  setc %%al");
  println("  movl %%eax, (%%rcx)");
}

static void gen_addcarryx_u64(Node *node) { 
  gen_expr(node->builtin_args[0]);
  println("  movq %%rax, %%rdi");
  gen_expr(node->builtin_args[1]);
  println("  movq %%rax, %%rsi");    
  gen_expr(node->builtin_args[2]);
  println("  movq %%rax, %%rdx");    
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");    
  println("  movq %%rsi, %%rax");
  println("  addq    %%rdx, %%rax");
  println("  addq    %%rdi, %%rax");
  println("  movq    %%rax, (%%rcx)");
}

static void gen_tzcnt_u16(Node *node) {
  gen_expr(node->lhs); 
  println("  testw %%ax, %%ax");
  println("  jne 1f");
  println("  movl $16, %%eax");
  println("  jmp 2f");
  println("1:");
  println("  bsfw %%ax, %%ax");
  println("2:");
}

static void gen_bextr_u32(Node *node) {
  gen_expr(node->lhs);
  println("  push %%rax");
  gen_expr(node->rhs);
  println("  movl %%eax, %%ecx");
  println("  pop %%rax");

  println("  movl %%ecx, %%edx");
  println("  andl $0xff, %%edx");

  println("  shrl $8, %%ecx");
  println("  andl $0xff, %%ecx");

  println("  testl %%ecx, %%ecx");
  println("  je 1f");

  println("  cmpl $32, %%edx");
  println("  jae 1f");

  println("  movl $32, %%esi");
  println("  subl %%edx, %%esi");
  println("  cmpl %%esi, %%ecx");
  println("  cmova %%esi, %%ecx");

  println("  shrl %%cl, %%eax");

  println("  movl $1, %%esi");
  println("  shll %%cl, %%esi");
  println("  decl %%esi");
  println("  andl %%esi, %%eax");
  println("  jmp 2f");

  println("1:");
  println("  xorl %%eax, %%eax");
  println("2:");
}


static void gen_binop1(Node *node, const char *insn) {
  println("  %s %%rax", insn);
}

static void gen_binop2(Node *node, const char *insn) {
  println("  %s %s", insn, reg_ax(node->ty->size));
}


static void gen_nothing(Node *node) {
  println("  mov $0, %%rax");
}

static void gen_singleop(Node *node, const char *insn) {
  println("  %s", insn);
}


static void gen_mul_overflow(Node *node) {
  int c = count(); 
  Type *ty = node->lhs->ty;  
  if (ty->base)
    ty = ty->base;
  int size = ty->size;
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  push_tmp();
  gen_expr(node->builtin_dest);
  push_tmp();
  pop_tmp("%rcx"); // result ptr (moved to rcx to free rdx)
  pop_tmp("%rsi"); 
  pop_tmp("%rdi"); 
  if (size == 1) {
    // For 8-bit values (char)
    println("  mov %%dil, %%al");
    if (ty->is_unsigned)
      println("  mul %%sil");
    else
      println("  imul %%sil");
    println("  jo .L.overflowm%d", c);
    println("  mov %%al, (%%rcx)");
    println("  mov $0, %%al");       
    println("  jmp .L.donem%d", c);   
  } else if (size == 2) {
    // For 16-bit values (short)
    println("  mov %%di, %%ax");
    if (ty->is_unsigned)
      println("  mul %%si");
    else
      println("  imul %%si");
    println("  jo .L.overflowm%d", c);
    println("  mov %%ax, (%%rcx)");
    println("  mov $0, %%ax");       
    println("  jmp .L.donem%d", c);   
  } else if (size == 4) {
    // For 32-bit values (int)
    println("  mov %%edi, %%eax");   
    if (ty->is_unsigned)
      println("  mul %%esi");
    else
      println("  imul %%esi");
    println("  jo .L.overflowm%d", c);  
    println("  mov %%eax, (%%rcx)");   
    println("  mov $0, %%eax");       
    println("  jmp .L.donem%d", c);   
  } else if (size == 8) {
    // For 64-bit values (long long)
    println("  mov %%rdi, %%rax");    
    if (ty->is_unsigned)
      println("  mul %%rsi");
    else
      println("  imul %%rsi");
    println("  jo .L.overflowm%d", c);  
    println("  mov %%rax, (%%rcx)"); 
    println("  mov $0, %%rax");       
    println("  jmp .L.donem%d", c);  
  }
  println(".L.overflowm%d:", c);
  // Store truncated result on overflow
  if (size == 1) println("  mov %%al, (%%rcx)");
  else if (size == 2) println("  mov %%ax, (%%rcx)");
  else if (size == 4) println("  mov %%eax, (%%rcx)");
  else if (size == 8) println("  mov %%rax, (%%rcx)");

  println("  mov $1, %%rax");           
  println(".L.donem%d:", c);
}


static void gen_sub_overflow(Node *node) {
    int c = count(); 
    Type *ty = node->builtin_dest->ty;  
    if (ty->base)
      ty = ty->base;
    gen_expr(node->lhs);
    if (ty->size == 16) pushx_tmp(); else push_tmp();
    gen_expr(node->rhs);
    if (ty->size == 16) pushx_tmp(); else push_tmp();
    gen_expr(node->builtin_dest);
    push_tmp();
    pop_tmp("%rdx");  
    if (ty->size == 16) popx_tmp("%rcx", "%rsi"); else pop_tmp("%rsi");
    if (ty->size == 16) popx_tmp("%rax", "%rdi"); else pop_tmp("%rdi");

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
    } else if (ty->size == 8) {
        println("  mov %%rdi, %%rax");
        println("  sub %%rsi, %%rax");
        println("  mov %%rax, (%%rdx)");
    } else if (ty->size == 16) { // __int128
        // lhs in rax:rdi (low:high), rhs in rcx:rsi. rdx is result ptr
        println("  sub %%rcx, %%rax");        // sub low
        println("  sbb %%rsi, %%rdi");        // sbb high

        println("  mov %%rax, (%%rdx)");      // store result low
        println("  mov %%rdi, 8(%%rdx)");     // store result high
    }
    if (ty->is_unsigned)
      println("  setc %%al");
    else
      println("  seto %%al");
    println("  movzx %%al, %%eax");  
    println("  cmp $0, %%eax");
    println("  jne .Loverflows%d", c);
    println("  mov $0, %%eax");
    println("  jmp .Lends%d", c);
    println(".Loverflows%d:", c);
    println("  mov $1, %%eax");
    println(".Lends%d:", c);
}


static void gen_fetchadd(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r8"); // val low
    println("  mov %%rdx, %%r9"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r8, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r9, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");
    return;
  }
  pop_tmp("%rdi");
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
}

static void gen_add_fetch(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r8"); // val low
    println("  mov %%rdx, %%r9"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r8, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r9, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    println("  mov %%rbx, %%rax");
    println("  mov %%rcx, %%rdx");
    return;
  }
  pop_tmp("%rdi");
  println("  mov %%rax, %%rdx");
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
  println("  add %s, %s", reg_ax(node->ty->size), reg_dx(node->ty->size));
  println("  mov %%rdx, %%rax");
}

static void gen_sub_fetch(Node *node) {
  gen_expr(node->lhs); 
  push_tmp();
  gen_expr(node->rhs);  
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r8"); // val low
    println("  mov %%rdx, %%r9"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r8, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r9, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    println("  mov %%rbx, %%rax");
    println("  mov %%rcx, %%rdx");
    return;
  }
  println("  mov %%rax, %%rdx");
  pop_tmp("%rdi");
  println("  neg %s", reg_ax(node->ty->size));
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
  println("  sub %s, %s", reg_dx(node->ty->size), reg_ax(node->ty->size)); 
}

static void gen_fetchsub(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r8"); // val low
    println("  mov %%rdx, %%r9"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r8, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r9, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");
    return;
  }
  pop_tmp("%rdi");
  println("  neg %s", reg_ax(node->ty->size));
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
}

static void gen_store_binop(Node *node, const char *insn) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(0);
  println("  %s %%xmm0, (%%rax)", insn); 
}

static void gen_loadlps(Node *node) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(0);
  println("  movlps (%%rax), %%xmm0");
}

static void gen_stmxcsr(Node *node) {
  if (node->lhs) {
    gen_expr(node->lhs); 
    println("  stmxcsr (%%rax)"); 
  } else {
    println("  stmxcsr -8(%%rsp)");  
    println("  mov -8(%%rsp), %%eax");
  }
} 

static void gen_single_addr_binop(Node *node, const char *insn){
  gen_addr(node->lhs);    
  println("  %s (%%rax)", insn);
}

static void gen_add_overflow(Node *node) {
  int c = count();  // Unique label counter
  Type *ty = node->builtin_dest->ty;  
  if (ty->base)
    ty = ty->base;

  gen_expr(node->lhs);
  if (ty->size == 16) pushx_tmp(); else push_tmp();
  gen_expr(node->rhs);
  if (ty->size == 16) pushx_tmp(); else push_tmp();
  gen_expr(node->builtin_dest);
  push_tmp();

  pop_tmp("%rdx");  
  if (ty->size == 16) popx_tmp("%rcx", "%rsi"); else pop_tmp("%rsi");
  if (ty->size == 16) popx_tmp("%rax", "%rdi"); else pop_tmp("%rdi"); 

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
  } else if (ty->size == 8) {
      println("  mov %%rdi, %%rax");
      println("  add %%rsi, %%rax");
      println("  mov %%rax, (%%rdx)");
  } else if (ty->size == 16) { // __int128
      // lhs in rax:rdi (low:high), rhs in rcx:rsi. rdx is result ptr
      println("  add %%rcx, %%rax");        // add low
      println("  adc %%rsi, %%rdi");        // adc high

      println("  mov %%rax, (%%rdx)");      // store result low
      println("  mov %%rdi, 8(%%rdx)");     // store result high
  }

  // Check for overflow
  // Check for overflow
  if (ty->is_unsigned)
    println("  setc %%al");
  else
    println("  seto %%al");
  println("  movzx %%al, %%eax");  // Zero-extend AL to EAX

  // Return 0 if no overflow, 1 if overflow
  println("  cmp $0, %%eax");
  println("  jne .Loverflowa%d", c);
  println("  mov $0, %%eax");
  println("  jmp .Lenda%d", c);
  println(".Loverflowa%d:", c);
  println("  mov $1, %%eax");
  println(".Lenda%d:", c);

}

static void gen_umul_overflow(Node *node) {
    int c = count();
    Type *ty = node->lhs->ty;
    if (ty->base)
        ty = ty->base;
    int size = ty->size;

    // Generate expressions
    gen_expr(node->lhs);
    push_tmp();
    gen_expr(node->rhs);
    push_tmp();
    gen_expr(node->builtin_dest);
    push_tmp();

    // Pop arguments
    pop_tmp("%rdx");  // result pointer (can be NULL)
    pop_tmp("%rsi");  // rhs
    pop_tmp("%rdi");  // lhs
    println("  mov %%rdx, %%rcx");
    // Multiply
    if (size == 1) {
        println("  movzbl %%di, %%eax");
        println("  movzbl %%si, %%ebx");
        println("  mul %%bl");           // AL * BL -> AX
        println("  jc .Loverflowm%d", c);
    } else if (size == 2) {
        println("  movzwl %%di, %%eax");
        println("  movzwl %%si, %%ebx");
        println("  mul %%bx");          // AX * BX -> DX:AX
        println("  jc .Loverflowm%d", c);
    } else if (size == 4) {
        println("  mov %%edi, %%eax");
        println("  mul %%esi");        // EAX * ESI -> EDX:EAX
        println("  jc .Loverflowm%d", c);
    } else if (size >= 8) {
        println("  mov %%rdi, %%rax");
        println("  mul %%rsi");        // RAX * RSI -> RDX:RAX
        println("  test %%rdx, %%rdx"); // overflow check
        println("  jnz .Loverflowm%d", c);
    }

    // Store result if destination pointer is not NULL
    println("  test %%rcx, %%rcx");
    println("  jz .Ldonem%d", c);
    if (size == 1) println("  mov %%al, (%%rcx)");
    else if (size == 2) println("  mov %%ax, (%%rcx)");
    else if (size == 4) println("  mov %%eax, (%%rcx)");
    else if (size == 8) println("  mov %%rax, (%%rcx)");
    
    println(".Ldonem%d:", c);
    println("  mov $0, %%rax");       // return 0 for no overflow
    println("  jmp .Lend%d", c);

    // Overflow label
    println(".Loverflowm%d:", c);
    println("  test %%rcx, %%rcx");    // only store if pointer not NULL
    println("  jz .Loverflow_end%d", c);
    if (size == 1) println("  movb $0, (%%rcx)");
    else if (size == 2) println("  movw $0, (%%rcx)");
    else if (size == 4) println("  movl $0, (%%rcx)");
    else if (size == 8) println("  movq $0, (%%rcx)");
    println(".Loverflow_end%d:", c);
    println("  mov $1, %%rax");        // return 1 for overflow
    println(".Lend%d:", c);
}


static void gen_uadd_overflow(Node *node) {
  int c = count(); 
  Type *ty = node->builtin_dest->ty;
  if (ty->base)
      ty = ty->base;

  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  push_tmp();
  gen_expr(node->builtin_dest);
  push_tmp();

  pop_tmp("%rdx");  
  pop_tmp("%rsi");  
  pop_tmp("%rdi"); 

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
  println("  setc %%al");          // carry flag = unsigned overflow
  println("  movzx %%al, %%eax");  // zero-extend AL to EAX

  // Return 0 if no overflow, 1 if overflow
  println("  cmp $0, %%eax");
  println("  jne .Loverflowa%d", c);
  println("  mov $0, %%eax");
  println("  jmp .Lenda%d", c);
  println(".Loverflowa%d:", c);
  println("  mov $1, %%eax");
  println(".Lenda%d:", c);
}


static void gen_parity(Node *node) {
  gen_expr(node->lhs);
  if (node->lhs->kind == ND_NUM) {
    uint64_t x = node->lhs->val;  
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    int parity = x & 1;
    println("  mov $%d, %%eax", parity); 

  } else {
    println("  mov %%rax, %%rcx");   // copy to rcx
    println("  shr $32, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $16, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $8, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $4, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $2, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  mov %%rax, %%rcx");
    println("  shr $1, %%rcx");
    println("  xor %%rcx, %%rax");
    println("  and $1, %%eax");  // final parity in eax

  }
}

static void gen_mwait(Node *node) {
  gen_expr(node->builtin_args[0]); 
  push_tmp();
  gen_expr(node->builtin_args[1]); 
  push_tmp();
  pop_tmp("%rcx");
  pop_tmp("%rax");
  println("mwait");
}

static void gen_monitor(Node *node) {
  gen_expr(node->builtin_args[0]); 
  push_tmp();

  gen_expr(node->builtin_args[1]); 
  push_tmp();

  gen_expr(node->builtin_args[2]); 
  push_tmp();
  pop_tmp("%rdx");
  pop_tmp("%rcx");
  pop_tmp("%rax");
  println("monitor");
}

static void gen_movq128(Node *node) {
  gen_expr(node->lhs); 
  println("  movq %%xmm0, %%xmm1");  
  println("  pxor %%xmm0, %%xmm0");  
  println("  movq %%xmm1, %%xmm0");  
}

static void gen_movnti(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->rhs->kind == ND_NUM)
    println("  mov $%ld, %%ecx", node->rhs->val);
  else 
    println("  movq (%%rax), %%rcx");
  pop_tmp("%rax");
  println("  movnti %%ecx, (%%rax)"); 
}

static void gen_movnti64(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->rhs->kind == ND_NUM)
    println("  mov $%ld, %%rcx", node->rhs->val);
  else 
    println("  movq (%%rax), %%rcx");
  pop_tmp("%rax");
  println("  movnti %%rcx, (%%rax)"); 
}

static void gen_movnt_binop(Node *node, const char *insn) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(0);
  int c = count();
  println("  test $15, %%rax");
  println("  jnz .L.movnt_unaligned.%d", c);
  println("  %s %%xmm0, (%%rax)", insn);
  println("  jmp .L.movnt_done.%d", c);
  println(".L.movnt_unaligned.%d:", c);
  // movnt* faults on unaligned memory; fall back to unaligned SSE store.
  if (!strcmp(insn, "movntpd"))
    println("  movupd %%xmm0, (%%rax)");
  else
    println("  movdqu %%xmm0, (%%rax)");
  println(".L.movnt_done.%d:", c);
}

static void gen_movntdqa(Node *node) {
  gen_expr(node->lhs);
  int c = count();
  println("  test $15, %%rax");
  println("  jnz .L.movntdqa_unaligned.%d", c);
  println("  movntdqa (%%rax), %%xmm0");
  println("  jmp .L.movntdqa_done.%d", c);
  println(".L.movntdqa_unaligned.%d:", c);
  // movntdqa faults on unaligned memory; fall back to unaligned load.
  println("  movdqu (%%rax), %%xmm0");
  println(".L.movntdqa_done.%d:", c);
}

static void gen_crc32qi(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32b %%al, %%ecx");
  println("  movl %%ecx, %%eax");
}

static void gen_crc32di(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32q %%rax, %%rcx");
  println("  movl %%ecx, %%eax");
}

static void gen_crc32hi(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32w %%ax, %%ecx");
  println("  movl %%ecx, %%eax");
}


static void gen_crc32si(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32l %%eax, %%ecx");
  println("  movl %%ecx, %%eax");
}



// Helper to emit MMX two-operand instruction
static void gen_sse_binop1(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->rhs);
  println("  movss %%xmm0, %%xmm1"); 
  gen_expr(node->lhs);
  println("  %s %%xmm1, %%xmm0", insn);
}

static void gen_sse_binop2(Node *node, const char *insn, const char *reg, bool rhs_is_imm) {
  gen_expr(node->lhs);
  println("  %s %%xmm0, %%%s", insn, reg);  
}


static void gen_sse_binop3(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn);
}


static void gen_sse_binop4(Node *node, const char *insn, const char *insn2) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm0, %%xmm1", insn); 
  println("  %s %%al", insn2);
  println("  movzx %%al, %%eax");
}


static void gen_sse_binop5(Node *node, const char *insn, const char *insn2) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn); 
  println("  %s %%al", insn2);
  println("  movzx %%al, %%eax");
}

static void gen_sse_binop6(Node *node, const char *insn, const char *insn2) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm0, %%xmm1", insn); 
  println("  setnp %%dl");
  println("  %s %%al", insn2);
  println("  and %%al, %%dl");
  println("  movzx %%dl, %%eax");
}

static void gen_sse_binop7(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm0, %%xmm1", insn);  
  println("  movdqa %%xmm1, %%xmm0");  
}

static void gen_sse_binop8(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs);
  println("  movq (%%rax), %%xmm0");
  println("  %s %%xmm0, %%%s", insn, reg);  
}


static void gen_sse_binop9(Node *node, const char *insn) {
  gen_expr(node->lhs);  
  push_xmm(0);
  gen_expr(node->rhs); 
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn);
}

static void gen_sse_binop10(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs); 
  println("  movq %%rax, %%rdi");    
  gen_expr(node->rhs);  
  println("  %s %%%s, (%%rdi)", insn, reg);    
}

static void gen_sse_binop11(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs); 
  println("  movq %%rax, %%rdi");    
  gen_expr(node->rhs);  
  println("  %s %%%s, %%xmm0", insn, reg);  
}

static void gen_sse_binop12(Node *node, const char *insn) {
  gen_expr(node->lhs); 
  println("  movups %%xmm0, %%xmm1");   
  println("  %s  %%xmm0, %%xmm1", insn);  
}



static void gen_lddqu(Node *node) {
    gen_addr(node->lhs);       
    println("  lddqu (%%rax), %%xmm0");
}

static void gen_sse_pblendvb128(Node *node) {
  assert(node->builtin_nargs == 3);  
  gen_expr(node->builtin_args[0]); 
  println("  movups %%xmm0, %%xmm1"); 
  gen_expr(node->builtin_args[1]);      
  println("  movups %%xmm0, %%xmm2"); 
  gen_expr(node->builtin_args[2]); 
  println("  pblendvb %%xmm2, %%xmm1"); 
  println("  movups %%xmm1, %%xmm0");
}

static void gen_sse_blendvpx(Node *node, const char *insn) {
  assert(node->builtin_nargs == 3);  
  gen_expr(node->builtin_args[0]); 
  println("  movups (%%rax), %%xmm1"); 
  gen_expr(node->builtin_args[1]);      
  println("  movups (%%rax), %%xmm2"); 
  gen_expr(node->builtin_args[2]); 
  println("  movups (%%rax), %%xmm0"); 
  println("  %s %%xmm0, %%xmm2, %%xmm1", insn); 
  println("  movups %%xmm1, %%xmm0");
}



static void gen_cvt_mmx_binop(Node *node, const char *insn) {
  gen_addr(node->lhs);   
  println("  movups (%%rax), %%xmm0"); 
  println("  %s %%xmm0, %%mm0", insn);  
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
  }

static void gen_cvt_sse_binop2(Node *node, const char *insn, const char *reg, bool is_address) {  
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(0);
  if (is_address)
    println("  %s (%%%s), %%xmm0", insn, reg);
  else 
    println("  %s %%%s, %%xmm0", insn, reg);
}

static void gen_cvt_mmx_binop3(Node *node, const char *insn) {
  gen_expr(node->lhs);        
  println("  %s %%xmm0, %%mm0", insn);
  gen_addr(node->lhs);         
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0"); 
  println("  emms");
}

static void gen_cvt_mmx_binop4(Node *node, const char *insn) {
  gen_expr(node->lhs);    
  println("  movq (%%rax), %%mm0");    
  println("  %s %%mm0, %%xmm0", insn);
  println("  emms");
}


// Helper to emit MMX two-operand instruction
static void gen_mmx_binop(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->lhs);
  println("  movq (%%rax), %%mm0");

  if (rhs_is_imm) {
    if (node->rhs->kind == ND_NUM) {
      println("  %s $%ld, %%mm0", insn, node->rhs->val);
    } else {
      gen_expr(node->rhs);
      println("  movq %%rax, %%mm1");
      println("  %s %%mm1, %%mm0", insn);
    }
  } else {
    gen_expr(node->rhs);
    println("  movq (%%rax), %%mm1");
    println("  %s %%mm1, %%mm0", insn);
  }

  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
}

static void gen_mmx_binop1(Node *node, const char *insn) {
  gen_expr(node->lhs);    
  println("  movq (%%rax), %%mm0");
  println("  %s %%mm0, %%mm0", insn);
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
}

static void gen_sse_testz(Node *node) {
    gen_expr(node->lhs);   // %xmm0 = M
    push_xmm(0);
    gen_expr(node->rhs);   // %xmm0 = V
    pop_xmm(1);
    // ptest performs V & M
    println("  ptest %%xmm0, %%xmm1");  // sets ZF and CF
    println("  setz %%al");             // AL = 1 if ZF=1
    println("  movzx %%al, %%eax");     // zero-extend to EAX
}

static void gen_sse_testc(Node *node) {
    gen_expr(node->lhs);              // %xmm0 = M
    push_xmm(0);
    gen_expr(node->rhs);              // %xmm0 = V
    pop_xmm(1);
    // ptest xmm1, xmm0 → sets ZF/CF
    println("  ptest %%xmm0, %%xmm1"); // CF = ((V & M) != M)
    // set result based on CF
    println("  setc %%al");            // AL = 1 if CF=1
    println("  movzx %%al, %%eax");    // zero-extend to EAX
}

static void gen_sse_testnzc(Node *node) {              
    gen_expr(node->rhs);   
    push_xmm(0);
    gen_expr(node->lhs);             
    pop_xmm(1);
    println("  ptest %%xmm1, %%xmm0");  
    // ptestnzc returns 1 if ZF==0 AND CF==0 (not zero and not carry)
    println("  setnz %%al");            // al = 1 if ZF==0
    println("  setnc %%cl");            // cl = 1 if CF==0
    println("  and %%cl, %%al");        // al = al & cl
    println("  movzx %%al, %%eax");     
}

static void gen_cas(Node *node)   {
  if (node->cas_addr->ty->base->size == 16) {
    gen_expr(node->cas_addr);
    push_tmp();
    if (node->cas_new->ty && node->cas_new->ty->kind == TY_LDOUBLE && node->cas_new->kind == ND_VAR) {
        gen_addr(node->cas_new);
        println("  mov 8(%%rax), %%rdx");
        println("  mov (%%rax), %%rax");
    } else {
        gen_expr(node->cas_new);
        if (node->cas_new->ty && node->cas_new->ty->kind == TY_LDOUBLE) {
             println("  sub $16, %%rsp");
             println("  fstpt (%%rsp)");
             println("  pop %%rax");
             println("  pop %%rdx");
        }
    }
    pushx_tmp();
    gen_expr(node->cas_old);
    println("  mov %%rax, %%r8");
    println("  mov (%%r8), %%rax");
    println("  mov 8(%%r8), %%rdx");
    
    popx_tmp("%rbx", "%rcx"); // new -> rcx:rbx
    pop_tmp("%rdi"); // addr

    println("  lock cmpxchg16b (%%rdi)");
    println("  sete %%cl");
    println("  je 1f");
    println("  mov %%rax, (%%r8)");
    println("  mov %%rdx, 8(%%r8)");
    println("1:");
    println("  movzbl %%cl, %%eax");
    return;
  }

  gen_expr(node->cas_addr);
  push_tmp();
  gen_expr(node->cas_new);
  push_tmp();
  gen_expr(node->cas_old);
  println("  mov %%rax, %%r8");
  if (!node->cas_old->ty->base)
    error("%s %d: in gen_cas :node->cas_old base type is null!", __FILE__, __LINE__); 
  load(node->cas_old->ty->base);
  pop_tmp("%rdx"); // new
  pop_tmp("%rdi"); // addr
  if (!node->cas_addr->ty->base)
    error("%s %d: in gen_cas : node->cas_addr base type is null!", __FILE__, __LINE__); 
  int sz = node->cas_addr->ty->base->size;
  println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));
  println("  sete %%cl");
  println("  je 1f");
  println("  mov %s, (%%r8)", reg_ax(sz));
  println("1:");
  println("  movzbl %%cl, %%eax");
  return;
  }

static void gen_bool_cas(Node *node) {
  gen_expr(node->cas_ptr);      
  push_tmp();
  gen_expr(node->cas_expected);  
  if (node->cas_ptr->ty->base->size == 16) {
    pushx_tmp();
    gen_expr(node->cas_desired);
    if (node->cas_desired->ty && node->cas_desired->ty->kind == TY_LDOUBLE) {
        println("  sub $16, %%rsp");
        println("  fstpt (%%rsp)");
        println("  pop %%rax");
        println("  pop %%rdx");
    }
    
    println("  mov %%rax, %%rbx");
    println("  mov %%rdx, %%rcx");
    
    popx_tmp("%rax", "%rdx"); // expected -> rdx:rax
    pop_tmp("%rdi"); // addr

    println("  lock cmpxchg16b (%%rdi)");
    println("  sete %%al");
    println("  movzbl %%al, %%eax");
    return;
  }
  push_tmp();
  gen_expr(node->cas_desired);   
  push_tmp();
  pop_tmp("%rdx");
  pop_tmp("%rax");
  pop_tmp("%rdi");
  int sz = node->cas_ptr->ty->base->size;
  if (!node->cas_ptr->ty->base)
    error("%s %d: in gen_bool_cas : node->cas_ptr base type is null!", __FILE__, __LINE__);   
  println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz)); 
  println("  sete %%al");       
  println("  movzbl %%al, %%eax"); 
}


static void  gen_add_and_fetch(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->lhs->ty->base->size == 16) {
    println("  mov %%rax, %%r8"); // val low
    println("  mov %%rdx, %%r9"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r8, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r9, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    println("  mov %%rbx, %%rax");
    println("  mov %%rcx, %%rdx");
    return;
  }
  pop_tmp("%rdi");  
  int sz = node->lhs->ty->base->size;
  println("  mov %%rax, %%rcx");           
  println("  lock xadd %s, (%%rdi)", reg_ax(sz));
  println("  add %%rcx, %%rax");
 }


static void gen_sub_and_fetch(Node *node) {
  gen_expr(node->lhs);    
  push_tmp();
  gen_expr(node->rhs);    
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r8"); // val low
    println("  mov %%rdx, %%r9"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r8, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r9, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");

    println("  mov %%rbx, %%rax");
    println("  mov %%rcx, %%rdx");
    return;
  }
  push_tmp();
  pop_tmp("%rax");        
  pop_tmp("%rdi");        
  int sz = node->lhs->ty->base->size;
  println("  mov %s, %s", reg_ax(sz), reg_cx(sz));               
  println("  neg %s", reg_ax(sz));               
  println("  lock xadd %s, (%%rdi)", reg_ax(sz));
  println("  sub %s, %s", reg_cx(sz), reg_ax(sz));      
}

static void gen_prefetch(Node *node) {
  Node *ptr = node->builtin_args[0];
  Node *rw = node->builtin_args[1];
  Node *locality = node->builtin_args[2];
  gen_expr(ptr);
  push_tmp();
  if (rw)
    gen_expr(rw);
  if (locality)
    gen_expr(locality);

  int loc = 3; 
    if (locality && locality->kind == ND_NUM) {
        loc = locality->val;
    }

    const char *instr;
    switch (loc) {
        case 0: instr = "prefetchnta"; break;
        case 1: instr = "prefetcht2"; break;
        case 2: instr = "prefetcht1"; break;
        case 3: instr = "prefetcht0"; break;
        default: instr = "prefetcht0"; break;
    }

    pop_tmp("%rax");
    println("  %s (%%rax)", instr);

}

static void gen_fetchnand(Node *node) {
    gen_expr(node->lhs);  
    push_tmp();
    gen_expr(node->rhs);  
    
    if (node->lhs->ty->base->size == 16) {
        println("  mov %%rax, %%r8"); // val low
        println("  mov %%rdx, %%r9"); // val high
        pop_tmp("%rdi"); // addr

        println("  mov (%%rdi), %%rax"); // old low
        println("  mov 8(%%rdi), %%rdx"); // old high

        println("1:");
        println("  mov %%rax, %%rbx");
        println("  mov %%rdx, %%rcx");
        
        println("  and %%r8, %%rbx");
        println("  and %%r9, %%rcx");
        println("  not %%rbx");
        println("  not %%rcx");

        println("  lock cmpxchg16b (%%rdi)");
        println("  jnz 1b");

        if (node->kind == ND_NANDFETCH) {
            println("  mov %%rbx, %%rax");
            println("  mov %%rcx, %%rdx");
        }
        return;
    }

    println("  mov %%rax, %%rsi");   
    pop_tmp("%rdi");
    int sz = node->lhs->ty->base->size;
    switch(sz) {
        case 1: println("  movzbl (%%rdi), %%rax"); break;
        case 2: println("  movzwl (%%rdi), %%rax"); break;
        case 4: println("  movl (%%rdi), %%eax");   break;
        case 8: println("  movq (%%rdi), %%rax");   break;
        default: error("%s %d: in gen_fetchnand : unsupported size %d!", __FILE__, __LINE__, sz); 
    }
    int label = count();
    println(".L.fetchnand_loop_%d:", label);
    println("  mov %%rax, %%rdx");  
    println("  and %%rsi, %%rdx");  
    println("  not %%rdx");         
    println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));
    println("  jnz .L.fetchnand_loop_%d", label);

    if (node->kind == ND_NANDFETCH)
        println("  mov %%rdx, %%rax"); 

}



static void gen_cas_n(Node *node)   {  
  gen_expr(node->cas_addr);
  push_tmp();
  gen_expr(node->cas_new);  
  if (node->cas_new->ty && node->cas_new->ty->kind == TY_LDOUBLE) {
      println("  sub $16, %%rsp");
      println("  fstpt (%%rsp)");
      println("  pop %%rax");
      println("  pop %%rdx");
  }
  if (node->cas_addr->ty && node->cas_addr->ty->base && node->cas_addr->ty->base->size == 16) {
    pushx_tmp();
    gen_expr(node->cas_old);
    if (node->cas_old->ty && node->cas_old->ty->kind == TY_LDOUBLE) {
        println("  sub $16, %%rsp");
        println("  fstpt (%%rsp)");
        println("  pop %%rax");
        println("  pop %%rdx");
    }
    
    // old is in rdx:rax
    
    popx_tmp("%rbx", "%rcx"); // new -> rcx:rbx
    pop_tmp("%rdi"); // addr

    println("  lock cmpxchg16b (%%rdi)");
    // result (old value) is in rdx:rax, which is what we want to return
    return;
  }
  push_tmp();
  gen_expr(node->cas_old); 

  pop_tmp("%rdx"); /* new */
  pop_tmp("%rdi"); /* addr */
  int sz = node->cas_addr->ty->base->size;
  if (!node->cas_addr->ty->base)
    error("%s %d: in gen_cas_n : node->cas_addr base type is null!", __FILE__, __LINE__);   

  println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));

  {
    Type *bt = node->cas_old->ty;

    switch (bt->kind) {
    case TY_BOOL:
      println("  movzx %%al, %%eax");
      break;
    case TY_CHAR:
      if (bt->is_unsigned)
        println("  movzbl %%al, %%eax");
      else
        println("  movsbl %%al, %%eax");
      break;
    case TY_SHORT:
      if (bt->is_unsigned)
        println("  movzwl %%ax, %%eax");
      else
        println("  movswl %%ax, %%eax");
      break;
    default:
      break;
    }
  }

  return;
}

static void gen_single_binop(const char *insn) {
  println("  %s", insn);
}

static void gen_cvt_binop(Node *node, const char *insn) {
  gen_addr(node->lhs);    
  if (node->lhs->kind == ND_VAR || node->lhs->kind == ND_MEMBER) {
      println("  %s (%%rax), %%rax", insn);   
  } else {
      println("  %s %%xmm0, %%rax", insn);   
  }
}

// Generate code for a given node.
static void gen_expr(Node *node)
{
  if (!node)
    error("%s: %s:%d: error: in gen_expr : node is null!", __FILE__, __FILE__, __LINE__);
  if (node->tok && node->tok->line_no != last_loc_line) {
  println("  .loc %d %u", node->tok->file->file_no, node->tok->line_no);
      last_loc_line = node->tok->line_no;
  }

  switch (node->kind)
  {
  case ND_NULL_EXPR:
    return;
  case ND_NUM:
  {
    switch (node->ty->kind)
    {
    case TY_FLOAT:
    {
      union { float f32; uint32_t u32; } u = {node->fval};
      println("  mov $%u, %%eax  # float %Lf", u.u32, node->fval);
      println("  movq %%rax, %%xmm0"); 
      return;
    }
    case TY_DOUBLE:
    {
      union { double f64; uint64_t u64; } u = {node->fval};
      println("  mov $%lu, %%rax  # double %Lf", u.u64, node->fval);
      println("  movq %%rax, %%xmm0");

      return;
    }
    case TY_LDOUBLE:
    {
      union { long double f80; uint64_t u64[2]; } u;
      memset(&u, 0, sizeof(u));
      u.f80 = node->fval;
      println("  mov $%lu, %%rax  # long double %Lf", u.u64[0], node->fval);
      println("  mov %%rax, -16(%%rsp)");
      println("  mov $%lu, %%rax", u.u64[1]);
      println("  mov %%rax, -8(%%rsp)");
      println("  fldt -16(%%rsp)");
      return;
    }
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

    }

    println("  mov $%ld, %%rax", node->val);
    return;
  }
  case ND_POS:
    gen_expr(node->lhs);
    return;
  case ND_NEG:
    gen_expr(node->lhs);

    if (is_int128(node->ty)) {
      gen_int128_op(node);
      return;
    }
    if (is_vector(node->ty)) {
      gen_vector_op(node);  
      return;
  }
        
    switch (node->ty->kind)
    {
    case TY_FLOAT:
      println("  mov $1, %%rax");
      println("  shl $31, %%rax");
      println("  movq %%rax, %%xmm1");
      println("  xorps %%xmm1, %%xmm0");
      return;
    case TY_DOUBLE:
      println("  mov $1, %%rax");
      println("  shl $63, %%rax");
      println("  movq %%rax, %%xmm1");
      println("  xorpd %%xmm1, %%xmm0");
      return;
    case TY_LDOUBLE:
      println("  fchs");
      return;
    }

    println("  neg %%rax");
    return;
  case ND_VAR:
    gen_addr(node);
    if (!node->ty)
      add_type(node);
    load(node->ty);
    return;
  case ND_MEMBER:
  {
    gen_addr(node);
    if (!node->ty)
      error("%s %d: in gen_expr : ND_MEMBER node type is null!", __FILE__, __LINE__);  
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
    if (!node->ty)
      error("%s %d: in gen_expr : ND_DEREF node type is null!", __FILE__, __LINE__); 
    load(node->ty);
    return;
  case ND_ADDR:
    gen_addr(node->lhs);
    return;
  case ND_ASSIGN:    
     // Optimization: Evaluate RHS first for simple scalars to reduce stack usage.
    // This avoids keeping the address on stack while evaluating RHS (which might involve calls).
    if (!is_bitfield(node->lhs) && 
        !is_int128(node->ty) && 
        !is_vector(node->ty) && node->ty &&
        node->ty->kind != TY_STRUCT && node->ty->kind != TY_UNION &&
        node->ty->kind != TY_FLOAT && node->ty->kind != TY_DOUBLE && node->ty->kind != TY_LDOUBLE) 
    {
        gen_expr(node->rhs);
        push_tmp();
        gen_addr(node->lhs);
        pop_tmp("%rdi"); // Value

        if (node->ty->size == 1) println("  mov %%dil, (%%rax)");
        else if (node->ty->size == 2) println("  mov %%di, (%%rax)");
        else if (node->ty->size == 4) println("  mov %%edi, (%%rax)");
        else println("  mov %%rdi, (%%rax)");
        println("  mov %%rdi, %%rax");
        return;
    }
    gen_addr(node->lhs);
    int tmp_offset = push_tmp();
    gen_expr(node->rhs);
    if (node->lhs->kind == ND_MEMBER && node->lhs->member->is_bitfield)
    {
      println("  mov %%rax, %%r8");
      Member *mem = node->lhs->member;
      println("  mov %%rax, %%rdi");
      if (mem->bit_width >= 64)
      {
        println("  mov $-1, %%rax");
        println("  and %%rax, %%rdi");
      }
      else if (mem->bit_width >= 32)
      {
        println("  mov $%ld, %%rax", (1L << mem->bit_width) - 1);
        println("  and %%rax, %%rdi");
      }
      else
      {
        println("  and $%ld, %%rdi", (1L << mem->bit_width) - 1);
      }

      println("  shl $%d, %%rdi", mem->bit_offset);
      if (is_omit_fp(current_fn))
        println("  mov (%%rsp), %%rax");
      else
        println("  mov %d(%s), %%rax", tmp_offset, lvar_ptr);
      load(mem->ty);

        
      long mask = ((1L << mem->bit_width) - 1) << mem->bit_offset;
      println("  mov $%ld, %%r9", ~mask);
      println("  and %%r9, %%rax");
      println("  or %%rdi, %%rax");
      store(node->ty);
      println("  mov %%r8, %%rax");
      if (mem->ty->kind == TY_BOOL)
        return;

      if (mem->bit_width < 64) {
        long mask2 = (1L << mem->bit_width) - 1;
        println("  mov $%ld, %%r9", mask2);
        println("  and %%r9, %%rax");

        // Assignment to a bitfield yields the stored field value.
        // Normalize by field width only (independent of storage bit offset).
        if (!mem->ty->is_unsigned) {
          int shift = 64 - mem->bit_width;
          println("  shl $%d, %%rax", shift);
          println("  sar $%d, %%rax", shift);
        }
      }

      return;
    }
    store(node->ty);

    // Keep assignment-expression results canonical for narrow integer types.
    // The value in %rax may still carry wider intermediate bits even though
    // only 1/2 bytes were stored to memory.
    if (is_integer(node->ty)) {
      if (node->ty->kind == TY_BOOL) {
        println("  movzbl %%al, %%eax");
      } else if (node->ty->size == 1) {
        if (node->ty->is_unsigned)
          println("  movzbl %%al, %%eax");
        else
          println("  movsbl %%al, %%eax");
      } else if (node->ty->size == 2) {
        if (node->ty->is_unsigned)
          println("  movzwl %%ax, %%eax");
        else
          println("  movswl %%ax, %%eax");
      }
    }
    return;
  case ND_STMT_EXPR:
    for (Node *n = node->body; n; n = n->next)
    {
      if (n->next)
        gen_stmt(n);
      else if (n->kind == ND_EXPR_STMT)
        gen_expr(n->lhs);
      else
        gen_stmt(n);
    }
    return;
  case ND_COMMA:
    gen_expr(node->lhs);
    if (node->lhs->ty && node->lhs->ty->kind == TY_LDOUBLE)
      println("  fstp %%st(0)");
    gen_expr(node->rhs);
    return;
  case ND_CAST:
    gen_expr(node->lhs);    
    if (!node->ty)   
      error("%s %d: in gen_expr : ND_CAST node type is null!", __FILE__, __LINE__); 
    cast(node->lhs->ty, node->ty);
    return;
  case ND_MEMZERO:
    gen_mem_zero(node->var->offset, node->var->ty->size);
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
  case ND_BITNOT:
    if (is_int128(node->ty)) {
      gen_int128_op(node);
      return;
    }
    if (is_vector(node->ty)) {
      gen_vector_op(node);  
      return;
    }
    gen_expr(node->lhs);
    println("  not %%rax");
    return;
  case ND_LOGAND:
    if (is_int128(node->ty)) {
      gen_int128_op(node);
      return;
    }
    if (is_vector(node->ty)) {
      gen_vector_op(node);  
      return;
    }
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
    if (is_int128(node->ty)) {
      gen_int128_op(node);
      return;
    }
    if (is_vector(node->ty)) {
      gen_vector_op(node);  
      return;
    }
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
    if (node->lhs->kind == ND_VAR && (!strcmp(sym(node->lhs->var), "alloca") ||  !strcmp(sym(node->lhs->var), "__builtin_alloca")))
    {
      gen_expr(node->args);
      println("  mov %%rax, %%rdi");
      //builtin_alloca();
      builtin_alloca(node);
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
      if (!ty)
        error("%s %d: in gen_expr : type is null!", __FILE__, __LINE__);  

      switch (ty->kind)
      {
      case TY_STRUCT:
      case TY_UNION:
        if (ty->size == 0)
          continue;
        if (!pass_by_reg(ty, gp, fp))
          continue;

        if (has_flonum1(ty))
          popf(fp++);
        else
          pop(argreg64[gp++]);

        if (ty->size > 8) {
          if (has_flonum2(ty))
            popf(fp++);
          else
            pop(argreg64[gp++]);
        }
        break;
      case TY_VECTOR:
        if (fp < FP_MAX)
          popv(fp++);
        break;      
      case TY_FLOAT:
      case TY_DOUBLE:
        if (fp < FP_MAX)
          popf(fp++);
        break;
      case TY_LDOUBLE:
        break;
      case TY_INT128:
        if (gp + 2 <= GP_MAX) {
          int a = gp++;
          int b = gp++;
          popx(argreg64[a], argreg64[b]);
        }      
        break;  
      default:
        if (gp < GP_MAX)
          pop(argreg64[gp++]);
        break;
      }
    }



    // Function call
    println("  mov %%rax, %%r10");
    //println("  mov $%d, %%rax", fp);
    println("  mov $%d, %%al", fp);
     
    // Tail call optimization
    if (node->is_tail && opt_optimize_level3) {
        char *funcname = NULL;
        if (node->lhs->kind == ND_VAR && node->lhs->var->is_function)
            funcname = sym(node->lhs->var);

        if (funcname && strcmp(funcname, sym(current_fn)) == 0) {
            // Recursive tail call optimization
            Node *arg = node->args;
            Obj *param = current_fn->params;
            while (arg && param) {
                if (arg->pass_by_stack) {
                    for (int i = 0; i < arg->ty->size; i += 8) {
                        int dest_offset = param->offset + i;
                        if (strcmp(param->ptr, "%rsp") == 0)
                            dest_offset += current_fn->stack_size + depth * 8;

                        println("  mov %d(%%rsp), %%r11", arg->stack_offset + i);
                        println("  mov %%r11, %d(%s)", dest_offset, param->ptr);
                    }
                }
                arg = arg->next;
                param = param->next;
            }

            // Restore stack pointer before jumping back to function body
            // .L.body is now before the sub instruction, so we just need to reset RSP
            if (is_omit_fp(current_fn)) {
                // No frame pointer: just clean up stack args
                if (stack_args > 0)
                    println("  add $%d, %%rsp", stack_args * 8);
                    //println("  add $%d, %%rsp", current_fn->stack_size);
            } else {
                // Frame pointer exists: restore RSP to base pointer
                bool use_rbx = (current_fn->stack_align > 16);
                char *base = use_rbx ? "%rbx" : "%rbp";
                println("  mov %s, %%rsp", base);
            }

            depth -= stack_args;
            println("  jmp .L.body.%s", sym(current_fn));
            return;
        }

        if (stack_args == 0 && current_fn->stack_size == 0) {
            if (is_omit_fp(current_fn)) {
                //println("  add $%d, %%rsp", current_fn->stack_size);
                println("  add $%d, %%rsp", stack_args * 8);
            } else {
                println("  mov %%rbp, %%rsp");
                println("  pop %%rbp");
            }
            println("  jmp *%%r10");
            return;
        }
    }

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
      if (is_omit_fp(current_fn))
        println("  lea %d(%%rsp), %%rax", node->ret_buffer->offset + current_fn->stack_size + depth * 8);
      else
      println("  lea %d(%s), %%rax", node->ret_buffer->offset, node->ret_buffer->ptr);
    }

    return;
  }
  case ND_LABEL_VAL:
    println("  lea %s(%%rip), %%rax", node->unique_label);
    return;
  case ND_CAS: gen_cas(node); return;
  case ND_CAS_N: gen_cas_n(node); return;
  case ND_FETCHNAND:
  case ND_NANDFETCH: gen_fetchnand(node); return;
  case ND_ADD_AND_FETCH: gen_add_and_fetch(node); return;
  case ND_SUB_AND_FETCH: gen_sub_and_fetch(node); return;
  case ND_BOOL_CAS: gen_bool_cas(node); return;
  case ND_MEMBARRIER:
  case ND_SYNC: {
    println("  mfence"); // x86-64 instruction for full memory barrier
    return;
  }
  case ND_BUILTIN_MEMCPY: gen_memcpy(node); return;
  case ND_BUILTIN_MEMSET: gen_memset(node); return;
  case ND_BUILTIN_CLZ: {
    gen_expr(node->builtin_val); 
    println("  bsr %%eax, %%eax"); 
    println("  xor $31, %%eax"); 
    return;
  }
  case ND_BUILTIN_CLZLL:
  case ND_BUILTIN_CLZL: {
    gen_expr(node->builtin_val); 
    println("  bsr %%rax, %%rax");       
    println("  xor $63, %%eax");       

    return;
  }
  case ND_BUILTIN_CTZ: gen_builtin(node, "bsf", "eax"); return;
  case ND_BUILTIN_CTZLL:
  case ND_BUILTIN_CTZL: gen_builtin(node, "bsf", "rax"); return;
  case ND_BUILTIN_BSWAP16: {
      gen_expr(node->builtin_val);  
      println("  mov %%ax, %%dx");  
      println("  rol $8, %%dx");    
      println("  mov %%dx, %%ax");  
      return;
  }

  case ND_BUILTIN_BSWAP32: {
      gen_expr(node->builtin_val);  
      println("  bswap %%eax");     
      return;
  }

  case ND_BUILTIN_BSWAP64: {
      gen_expr(node->builtin_val);  
      println("  bswap %%rax");     
      return;
  }  
  case ND_BUILTIN_FRAME_ADDRESS: {
    int c = count();
  
    gen_expr(node->lhs);
  
  // Guard: limit frame walking to 64 levels
  println("  mov $64, %%rdi");
  println("  cmp %%rax, %%rdi");
  println("  ja .Lframe_address_ok%d", c);   // if rax < 64, continue
  println("  jmp .Lframe_address_null%d", c); // else, bail out

  println(".Lframe_address_ok%d:", c);
    
    println("  cmp $0, %%rax");
    println("  je .Lframe_address_%d", c);
    // Frame-chain builtins must walk canonical frame pointers (%rbp),
    // not lvar_ptr (which may be %rbx when stack is realigned).
    println("  mov %%rbp, %%rcx");


    println(".Lframe_address_loop%d:", c);
  println("  test %%rax, %%rax");
    println("  jz .Lframe_address_done%d", c);
  println("  test %%rcx, %%rcx");
  println("  jz .Lframe_address_null%d", c);
  println("  mov (%%rcx), %%rcx");  // rcx = *(rcx) (next frame)
  println("  sub $1, %%rax");
    println("  jmp .Lframe_address_loop%d", c);

    println(".Lframe_address_done%d:", c);
  println("  mov %%rcx, %%rax");  // return result
  println("  jmp .Lframe_address_return%d", c);

    println(".Lframe_address_%d:", c);
    println("  mov %%rbp, %%rax");  // level 0: return current frame
  println("  jmp .Lframe_address_return%d", c);

  println(".Lframe_address_null%d:", c);
  println("  mov $0, %%rax");     // return NULL

  println(".Lframe_address_return%d:", c);
    return;
  }
  case ND_POPCOUNTL:
  case ND_POPCOUNTLL: gen_builtin(node, "popcnt", "rax"); return;
  case ND_POPCOUNT:   gen_builtin(node, "popcnt", "eax"); return;
  case ND_EXPECT: {
    gen_expr(node->lhs); 
    push_tmp(); 
    gen_expr(node->rhs);     
    pop_tmp("%rdi"); 
    println("  cmp %%rax, %%rdi");
    println("  mov %%rdi, %%rax");
    return;
  }   
  case ND_ABORT: {
    println("  call abort"); 
    return;
  }
  case ND_RETURN_ADDR: {

    // Return-address builtin is also anchored on canonical frame pointer.
    println("  mov %%rbp, %%rax");
    int tmpdepth = eval(node->lhs);
    
    for (int i = 0; i < tmpdepth; i++) {
      println("  mov (%%rax), %%rax");
    }
    
    println("  mov 8(%%rax), %%rax");
    return;
  }
  case ND_UMULL_OVERFLOW:
  case ND_UMULLL_OVERFLOW:
  case ND_UMUL_OVERFLOW: gen_umul_overflow(node); return;  
  case ND_UADDL_OVERFLOW:
  case ND_UADDLL_OVERFLOW:
  case ND_UADD_OVERFLOW: gen_uadd_overflow(node); return;
  case ND_BUILTIN_ADD_OVERFLOW: gen_add_overflow(node); return;
  case ND_BUILTIN_SUB_OVERFLOW: gen_sub_overflow(node); return;
  case ND_BUILTIN_MUL_OVERFLOW: gen_mul_overflow(node); return;
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
    push_tmp();
    gen_expr(node->rhs);

    int sz = node->lhs->ty->base->size;
    if (sz == 16) {
      println("  mov %%rax, %%rbx");
      println("  mov %%rdx, %%rcx");
      pop_tmp("%rdi");
      println("  mov (%%rdi), %%rax");
      println("  mov 8(%%rdi), %%rdx");
      println("1:");
      println("  lock cmpxchg16b (%%rdi)");
      println("  jnz 1b");
      return;
    }
    pop_tmp("%rdi");
    println("  xchg %s, (%%rdi)", reg_ax(sz));
    return;
  }
  case ND_EXCH_N:
  case ND_TESTANDSET: {
    gen_expr(node->lhs);
    push_tmp();
    gen_expr(node->rhs);    
    if (node->ty && node->ty->kind == TY_FLOAT)
        println("  movd %%xmm0, %%eax");
    else if (node->ty->kind == TY_DOUBLE)
        println("  movq %%xmm0, %%rax");
    if (node->ty->size == 16) {
      if (node->rhs->ty && node->rhs->ty->kind == TY_LDOUBLE) {
          println("  sub $16, %%rsp");
          println("  fstpt (%%rsp)");
          println("  pop %%rax");
          println("  pop %%rdx");
      }
      println("  mov %%rax, %%rbx");
      println("  mov %%rdx, %%rcx");
      pop_tmp("%rdi");
      println("  mov (%%rdi), %%rax");
      println("  mov 8(%%rdi), %%rdx");
      println("1:");
      println("  lock cmpxchg16b (%%rdi)");
      println("  jnz 1b");
      return;
    }
    pop_tmp("%rdi");
    println("  xchg %s, (%%rdi)", reg_ax(node->ty->size));
    if (node->ty->kind == TY_FLOAT)
         println("  movd %%eax, %%xmm0");
    else if (node->ty->kind == TY_DOUBLE)
         println("  movq %%rax, %%xmm0");
    return;
  }
  case ND_CMPEXCH: gen_cmpxchg(node); return;
  case ND_CMPEXCH_N: gen_cmpxchgn(node); return;
  case ND_TESTANDSETA: {
    gen_expr(node->lhs);
    push_tmp();
    if (node->ty->size == 16) {
        pop_tmp("%rdi");
        println("  mov (%%rdi), %%rax");
        println("  mov 8(%%rdi), %%rdx");
        println("1:");
        println("  mov $1, %%rbx");
        println("  xor %%rcx, %%rcx");
        println("  lock cmpxchg16b (%%rdi)");
        println("  jnz 1b");
        println("  or %%rdx, %%rax");
        println("  setne %%al");
        println("  movzbl %%al, %%eax");
        return;
    }
    println("  mov $1, %%eax");    
    pop_tmp("%rdi");
    println("  xchg %s, (%%rdi)", reg_ax(node->ty->size));
    return;
  }
  case ND_LOAD: {
    gen_expr(node->rhs);
    push_tmp();
    gen_expr(node->lhs);
    if (node->ty->size == 16) {
      println("  mov (%%rax), %%rcx");
      println("  mov 8(%%rax), %%rdx");
      pop_tmp("%rdi");
      println("  mov %%rcx, (%%rdi)");
      println("  mov %%rdx, 8(%%rdi)");
      return;
    }
    println("  mov (%%rax), %s", reg_ax(node->ty->size));    
    pop_tmp("%rdi");
    println("  mov %s, (%%rdi)", reg_ax(node->ty->size));
    return;
  }
  case ND_LOAD_N: {
    gen_expr(node->lhs);
    if (node->ty->size == 16) {
      println("  mov 8(%%rax), %%rdx");
      println("  mov (%%rax), %%rax");
    } else {
      println(" mov (%%rax), %s", reg_ax(node->ty->size));
      if (node->ty->kind == TY_FLOAT)
         println("  movd %%eax, %%xmm0");
      else if (node->ty->kind == TY_DOUBLE)
         println("  movq %%rax, %%xmm0");
    }
    if (node->memorder) {
        println("  mfence");
    }
    return;
  }
  case ND_STORE: {
    gen_expr(node->lhs);
    push_tmp();
    gen_expr(node->rhs);    
    pop_tmp("%rdi");
    if (node->ty->size == 16) {
      println("  mov (%%rax), %%rcx");
      println("  mov 8(%%rax), %%rdx");
      println("  mov %%rcx, (%%rdi)");
      println("  mov %%rdx, 8(%%rdi)");
      if (node->memorder) {
        println("  mfence");
      }
      return;
    }
    println("  mov (%%rax),%s", reg_ax(node->ty->size));
    println("  mov %s, (%%rdi)", reg_ax(node->ty->size));
    if (node->memorder) {
      println("  mfence");
    }
    return;
  }
  case ND_STORE_N:
    gen_expr(node->lhs);
    push_tmp();
    gen_expr(node->rhs);    
    if (node->ty && node->ty->kind == TY_FLOAT)
        println("  movd %%xmm0, %%eax");
    else if (node->ty && node->ty->kind == TY_DOUBLE)
        println("  movq %%xmm0, %%rax");
    if (node->ty && node->ty->size == 16) {
      if (node->rhs->ty && node->rhs->ty->kind == TY_LDOUBLE) {
          println("  sub $16, %%rsp");
          println("  fstpt (%%rsp)");
          println("  pop %%rax");
          println("  pop %%rdx");
      }
      println("  mov %%rax, %%rbx");
      println("  mov %%rdx, %%rcx");
      pop_tmp("%rdi");
      println("  mov %%rbx, (%%rdi)");
      println("  mov %%rcx, 8(%%rdi)");
      if (node->memorder) {
        println("  mfence");
      }
      return;
    }
    pop_tmp("%rdi");
    println("  mov %s, (%%rdi)", reg_ax(node->ty->size));
    if (node->memorder) {
      println("  mfence");
    }
    return;
  case ND_CLEAR:
    gen_expr(node->lhs);
    println("  mov %%rax, %%rdi");
    println("  xor %%eax, %%eax");
    println("  mov %s, (%%rdi)", reg_ax(node->ty->size));
    if (node->memorder) {
      println("  mfence");
    }
    return;
  case ND_FETCHADD: gen_fetchadd(node); return;
  case ND_FETCHSUB: gen_fetchsub(node); return;
  case ND_ADDFETCH: gen_add_fetch(node); return;  
  case ND_SUBFETCH: gen_sub_fetch(node); return;    
  case ND_FETCHXOR: HandleAtomicArithmetic(node, "xor", false); return;
  case ND_FETCHAND: HandleAtomicArithmetic(node, "and", false); return;
  case ND_FETCHOR: HandleAtomicArithmetic(node, "or", false); return;
  case ND_ORFETCH: HandleAtomicArithmetic(node, "or", true); return;    
  case ND_ANDFETCH: HandleAtomicArithmetic(node, "and", true); return;
  case ND_XORFETCH: HandleAtomicArithmetic(node, "xor", true); return;
  case ND_RELEASE: gen_release(node); return;
  case ND_ALLOC: gen_alloc(node); return;
  case ND_BUILTIN_NANF:  
  case ND_BUILTIN_HUGE_VALF:
  case ND_BUILTIN_INFF: {
    union {
      float f;
      uint32_t i;
    } u;
    u.f = node->fval;
    println("  mov $%u, %%eax", u.i);
    println("  movd %%eax, %%xmm0");
    return;
  }
  case ND_BUILTIN_NAN:
  case ND_BUILTIN_HUGE_VAL:
  case ND_BUILTIN_INF: {
    union {
      double d;
      uint64_t i;
    } u;
    u.d = node->fval;
    println("  movq $%lu, %%rax", u.i);
    println("  movq %%rax, %%xmm0");
    return;
}
  case ND_BUILTIN_NANL:
  case ND_BUILTIN_HUGE_VALL: {
    union {
      long double ld;
      uint8_t bytes[10];
    } u;
    u.ld = node->fval;

  for (int i = 0; i < 10; i++)
    println("  movb $%d, -%d(%%rsp)", u.bytes[i], 10 - i);

  println("  fldt -10(%%rsp)");
  return;
  }
  case ND_EMMS: gen_single_binop("emms"); return;
  case ND_SFENCE: gen_single_binop("sfence"); return;
  case ND_LFENCE: gen_single_binop("lfence"); return;
  case ND_MFENCE: gen_single_binop("mfence"); return;
  case ND_PAUSE: gen_single_binop("pause"); return;
  case ND_STMXCSR: gen_stmxcsr(node); return;
  case ND_LDMXCSR: gen_single_addr_binop(node, "ldmxcsr"); return;
  case ND_SHUFPS: gen_shuf_binop(node, "shufps"); return;
  case ND_SHUFPD: gen_shuf_binop(node, "shufpd"); return;
  case ND_SHUFFLE: gen_shuffle(node, "shufps"); return;
  case ND_CVTPI2PS: gen_cvtpi2ps(node); return;   
  case ND_CVTPS2PI:  gen_cvt_mmx_binop3(node, "cvtps2pi"); return;
  case ND_CVTSS2SI: gen_sse_binop2(node, "cvtss2si", "eax", false); return;
  case ND_CVTSS2SI64: gen_cvt_binop(node, "cvtss2siq"); return;
  case ND_CVTTSS2SI: gen_cvt_binop(node, "cvttss2si"); return;
  case ND_CVTTSS2SI64: gen_cvt_binop(node, "cvttss2siq"); return;
  case ND_CVTTPS2PI: gen_cvt_mmx_binop(node, "cvttps2pi"); return;
  case ND_CVTSI2SS: gen_cvt_sse_binop2(node, "cvtsi2ss", "eax", false); return;
  case ND_CVTSI642SS: gen_cvt_sse_binop2(node, "cvtsi2ss", "rax", false); return;
  case ND_MOVLHPS: gen_sse_binop3(node, "movlhps", false);  return; 
  case ND_MOVHLPS: gen_sse_binop3(node, "movhlps", false);  return; 
  case ND_UNPCKHPS: gen_sse_binop3(node, "unpckhps", false);  return; 
  case ND_UNPCKLPS: gen_sse_binop3(node, "unpcklps", false);  return; 
  case ND_LOADHPS: gen_loadhps(node); return; 
  case ND_STOREHPS: gen_store_binop(node, "movhps"); return; 
  case ND_LOADLPS: gen_loadlps(node); return; 
  case ND_STORELPS: gen_store_binop(node, "movlps"); return;   
  case ND_MOVMSKPS: gen_sse_binop2(node, "movmskps", "eax", false);  return;   
  case ND_CLFLUSH: gen_single_addr_binop(node, "clflush"); return;
  case ND_VECINITV2SI: gen_vec_init_v2si(node); return;
  case ND_VECEXTV2SI: gen_vec_ext(node); return;
  case ND_VECEXTV4SI: gen_vec_ext(node); return;
  case ND_PACKSSWB:   gen_mmx_binop(node, "packsswb", false); return;
  case ND_PACKSSDW:   gen_mmx_binop(node, "packssdw", false); return;
  case ND_PACKUSWB:   gen_mmx_binop(node, "packuswb", false); return;
  case ND_PUNPCKHBW:  gen_mmx_binop(node, "punpckhbw", false); return;
  case ND_PUNPCKHWD:  gen_mmx_binop(node, "punpckhwd", false); return;
  case ND_PUNPCKHDQ:  gen_mmx_binop(node, "punpckhdq", false); return;
  case ND_PUNPCKLBW:  gen_mmx_binop(node, "punpcklbw", false); return;
  case ND_PUNPCKLWD:  gen_mmx_binop(node, "punpcklwd", false); return;
  case ND_PUNPCKLDQ:  gen_mmx_binop(node, "punpckldq", false); return;
  case ND_PADDB:      gen_mmx_binop(node, "paddb", false); return;
  case ND_PADDW:      gen_mmx_binop(node, "paddw", false); return;
  case ND_PADDD:      gen_mmx_binop(node, "paddd", false); return;
  case ND_PADDQ:      gen_mmx_binop(node, "paddq", false); return;
  case ND_PADDSB:     gen_mmx_binop(node, "paddsb", false); return;
  case ND_PADDSW:     gen_mmx_binop(node, "paddsw", false); return;
  case ND_PADDUSB:    gen_mmx_binop(node, "paddusb", false); return;
  case ND_PADDUSW:    gen_mmx_binop(node, "paddusw", false); return;
  case ND_PSUBB:      gen_mmx_binop(node, "psubb", false); return;
  case ND_PSUBW:      gen_mmx_binop(node, "psubw", false); return;
  case ND_PSUBD:      gen_mmx_binop(node, "psubd", false); return;
  case ND_PSUBQ:      gen_mmx_binop(node, "psubq", false); return;
  case ND_PSUBSB:     gen_mmx_binop(node, "psubsb", false); return;
  case ND_PSUBSW:     gen_mmx_binop(node, "psubsw", false); return;
  case ND_PSUBUSB:    gen_mmx_binop(node, "psubusb", false); return;
  case ND_PSUBUSW:    gen_mmx_binop(node, "psubusw", false); return;
  case ND_PMADDWD:    gen_mmx_binop(node, "pmaddwd", false); return;
  case ND_PMULHW:     gen_mmx_binop(node, "pmulhw", false); return;
  case ND_PMULLW:     gen_mmx_binop(node, "pmullw", false); return;
  case ND_PSLLW:      gen_mmx_binop(node, "psllw", false); return;
  case ND_PSLLWI:     gen_mmx_binop(node, "psllw", true);  return;
  case ND_PSLLD:      gen_mmx_binop(node, "pslld", false); return;
  case ND_PSLLDI:     gen_mmx_binop(node, "pslld", true);  return;
  case ND_PSLLQ:      gen_mmx_binop(node, "psllq", false); return;
  case ND_PSLLQI:     gen_mmx_binop(node, "psllq", true);  return;
  case ND_PSRAW:      gen_mmx_binop(node, "psraw", false); return;
  case ND_PSRAWI:     gen_mmx_binop(node, "psraw", true);  return;
  case ND_PSRAD:      gen_mmx_binop(node, "psrad", false); return;
  case ND_PSRADI:     gen_mmx_binop(node, "psrad", true);  return;
  case ND_PSRLW:      gen_mmx_binop(node, "psrlw", false); return;
  case ND_PSRLWI:     gen_mmx_binop(node, "psrlw", true);  return;
  case ND_PSRLD:      gen_mmx_binop(node, "psrld", false); return;
  case ND_PSRLDI:     gen_mmx_binop(node, "psrld", true);  return;
  case ND_PSRLQ:      gen_mmx_binop(node, "psrlq", false); return;
  case ND_PSRLQI:     gen_mmx_binop(node, "psrlq", true);  return;
  case ND_PAND:       gen_mmx_binop(node, "pand", false);  return;
  case ND_PANDN:      gen_mmx_binop(node, "pandn", false); return;
  case ND_POR:        gen_mmx_binop(node, "por", false);   return;
  case ND_PXOR:       gen_mmx_binop(node, "pxor", false);  return;  
  case ND_PCMPEQB:    gen_mmx_binop(node, "pcmpeqb", false);  return;      
  case ND_PCMPGTB:    gen_mmx_binop(node, "pcmpgtb", false);  return;     
  case ND_PCMPEQW:    gen_mmx_binop(node, "pcmpeqw", false);  return;     
  case ND_PCMPGTW:    gen_mmx_binop(node, "pcmpgtw", false);  return;    
  case ND_PCMPEQD:    gen_mmx_binop(node, "pcmpeqd", false);  return;     
  case ND_PCMPGTD:    gen_mmx_binop(node, "pcmpgtd", false);  return;           
  case ND_VECINITV4HI: gen_vec_init_binop(node, "pinsrw"); return;
  case ND_VECINITV8QI: gen_vec_init_binop(node, "pinsrb"); return;
  case ND_ADDSS: gen_sse_binop1(node, "addss", false);  return;    
  case ND_SUBSS: gen_sse_binop1(node, "subss", false);  return;    
  case ND_MULSS: gen_sse_binop1(node, "mulss", false);  return;    
  case ND_DIVSS: gen_sse_binop1(node, "divss", false);  return;    
  case ND_SQRTSS: gen_sse_binop2(node, "sqrtss", "xmm0", false);  return;   
  case ND_RCPSS: gen_sse_binop2(node, "rcpss", "xmm0", false);  return;   
  case ND_RSQRTSS: gen_sse_binop2(node, "rsqrtss", "xmm0", false);  return;   
  case ND_MINSS: gen_sse_binop1(node, "minss", false);  return; 
  case ND_MAXSS: gen_sse_binop1(node, "maxss", false);  return; 
  case ND_SQRTPS: gen_sse_binop2(node, "sqrtps", "xmm0", false);  return;  
  case ND_RCPPS: gen_sse_binop2(node, "rcpps", "xmm0", false);  return;  
  case ND_RSQRTPS: gen_sse_binop2(node, "rsqrtps", "xmm0", false);  return;  
  case ND_MINPS: gen_sse_binop3(node, "minps", false);  return; 
  case ND_MAXPS: gen_sse_binop3(node, "maxps", false);  return; 
  case ND_ANDPS: gen_sse_binop3(node, "andps", false);  return; 
  case ND_ANDNPS:  gen_sse_binop3(node, "andnps", false);  return; 
  case ND_ORPS:  gen_sse_binop3(node, "orps", false);  return; 
  case ND_XORPS:  gen_sse_binop3(node, "xorps", false);  return; 
  case ND_CMPEQSS: gen_sse_binop3(node, "cmpeqss", false);  return; 
  case ND_CMPLTSS: gen_sse_binop3(node, "cmpltss", false);  return; 
  case ND_CMPLESS: gen_sse_binop3(node, "cmpless", false);  return; 
  case ND_MOVSS: gen_sse_binop3(node, "movss", false);  return; 
  case ND_CMPNEQSS: gen_sse_binop3(node, "cmpneqss", false);  return; 
  case ND_CMPNLTSS: gen_sse_binop3(node, "cmpnltss", false);  return; 
  case ND_CMPNLESS: gen_sse_binop3(node, "cmpnless", false);  return; 
  case ND_CMPORDSS: gen_sse_binop3(node, "cmpordss", false);  return; 
  case ND_CMPUNORDSS: gen_sse_binop3(node, "cmpunordss", false);  return; 
  case ND_CMPEQPS: gen_sse_binop3(node, "cmpeqps", false);  return; 
  case ND_CMPLTPS: gen_sse_binop3(node, "cmpltps", false);  return; 
  case ND_CMPLEPS: gen_sse_binop3(node, "cmpleps", false);  return; 
  case ND_CMPGTPS: gen_sse_binop3(node, "cmpps $0x6,", false);  return; 
  case ND_CMPGEPS: gen_sse_binop3(node, "cmpps $0xD,", false);  return; 
  case ND_CMPNEQPS: gen_sse_binop3(node, "cmpps $4,", false);  return; 
  case ND_CMPNLTPS: gen_sse_binop3(node, "cmpps $5,", false);  return; 
  case ND_CMPNLEPS: gen_sse_binop3(node, "cmpps $6,", false);  return; 
  case ND_CMPNGTPS:  gen_sse_binop3(node, "cmpps $2,", false);  return; 
  case ND_CMPNGEPS:  gen_sse_binop3(node, "cmpps $1,", false);  return;
  case ND_CMPORDPS: gen_sse_binop3(node, "cmpordps", false);  return;  
  case ND_CMPUNORDPS: gen_sse_binop3(node, "cmpunordps", false);  return;  
  case ND_PHADDW128: gen_sse_binop3(node, "phaddw", false);  return; 
  case ND_PHADDD128: gen_sse_binop3(node, "phaddd", false);  return; 
  case ND_PHADDSW128: gen_sse_binop3(node, "phaddsw", false);  return;
  case ND_PHADDW: gen_mmx_binop(node, "phaddw", false); return;
  case ND_PHADDD: gen_mmx_binop(node, "phaddd", false);  return;
  case ND_PHADDSW: gen_mmx_binop(node, "phaddsw", false);  return;
  case ND_COMIEQ: gen_sse_binop4(node, "comiss", "sete");  return;  
  case ND_COMILT: gen_sse_binop4(node, "comiss", "setb");  return;  
  case ND_COMILE: gen_sse_binop4(node, "comiss", "setbe");  return;  
  case ND_COMIGT: gen_sse_binop4(node, "comiss", "seta");  return;  
  case ND_COMIGE: gen_sse_binop5(node, "comiss", "setae");  return;  
  case ND_COMINEQ: gen_sse_binop4(node, "comiss", "setne");  return;  
  case ND_UCOMIEQ: gen_sse_binop6(node, "comiss", "sete");  return;  
  case ND_UCOMILT: gen_sse_binop6(node, "comiss", "setb");  return;  
  case ND_UCOMILE: gen_sse_binop6(node, "ucomiss", "setbe");  return;  
  case ND_UCOMIGT: gen_sse_binop5(node, "ucomiss", "seta");  return;  
  case ND_UCOMIGE: gen_sse_binop5(node, "ucomiss", "setae");  return;  
  case ND_UCOMINEQ: gen_sse_binop4(node, "ucomiss", "setne");  return;  
  case ND_PMAXSW: gen_sse_binop7(node, "pmaxsw"); return;
  case ND_PMAXUB: gen_sse_binop7(node, "pmaxub"); return;
  case ND_PMINSW: gen_sse_binop7(node, "pminsw"); return;
  case ND_PMINUB: gen_sse_binop7(node, "pminub"); return;
  case ND_PMOVMSKB: gen_sse_binop8(node, "pmovmskb", "eax"); return;
  case ND_PMULHUW: gen_sse_binop9(node, "pmulhuw"); return;
  case ND_MASKMOVQ: gen_maskmovq(node); return;
  case ND_PAVGB: gen_mmx_binop(node, "pavgb", false);  return;      
  case ND_PAVGW: gen_mmx_binop(node, "pavgw", false);  return;      
  case ND_PSADBW: gen_mmx_binop(node, "psadbw", false);  return;   
  case ND_MOVNTQ: gen_sse_binop10(node, "movnti", "rax"); return;   
  case ND_MOVNTPS: gen_sse_binop10(node, "movups", "xmm0"); return;
  case ND_ADDSD: gen_sse_binop3(node, "addsd", false);  return;    
  case ND_SUBSD: gen_sse_binop3(node, "subsd", false);  return;  
  case ND_MULSD: gen_sse_binop3(node, "mulsd", false);  return;    
  case ND_DIVSD: gen_sse_binop3(node, "divsd", false);  return;   
  case ND_SQRTPD: gen_sse_binop2(node, "sqrtpd", "xmm0", false);  return;  
  case ND_MOVSD: gen_sse_binop3(node, "movsd", false);  return;   
  case ND_SQRTSD: gen_sse_binop2(node, "sqrtsd", "xmm0", false);  return;  
  case ND_MINPD: gen_sse_binop3(node, "minpd", false);  return;   
  case ND_MINSD: gen_sse_binop3(node, "minsd", false);  return;   
  case ND_MAXPD: gen_sse_binop3(node, "maxpd", false);  return;  
  case ND_MAXSD: gen_sse_binop3(node, "maxsd", false);  return;  
  case ND_ANDPD: gen_sse_binop3(node, "andpd", false);  return;  
  case ND_ANDNPD: gen_sse_binop3(node, "andnpd", false);  return;
  case ND_ORPD: gen_sse_binop3(node, "orpd", false);  return;     
  case ND_XORPD: gen_sse_binop3(node, "xorpd", false);  return;     
  case ND_CMPEQPD: gen_sse_binop3(node, "cmpeqpd", false);  return;   
  case ND_CMPLTPD: gen_sse_binop3(node, "cmpltpd", false);  return;   
  case ND_CMPLEPD: gen_sse_binop3(node, "cmplepd", false);  return;   
  case ND_CMPGTPD: gen_sse_binop3(node, "cmpnlepd", false);  return;   
  case ND_CMPGEPD: gen_sse_binop3(node, "cmpnltpd", false);  return;   
  case ND_CMPNEQPD: gen_sse_binop3(node, "cmpneqpd", false);  return;   
  case ND_CMPNLTPD: gen_sse_binop3(node, "cmpnltpd", false);  return;   
  case ND_CMPNLEPD: gen_sse_binop3(node, "cmpnlepd", false);  return;   
  case ND_CMPNGTPD: gen_sse_binop3(node, "cmplepd", false);  return;   
  case ND_CMPNGEPD: gen_sse_binop3(node, "cmpltpd", false);  return;   
  case ND_CMPORDPD: gen_sse_binop3(node, "cmpordpd", false);  return;   
  case ND_CMPUNORDPD: gen_sse_binop3(node, "cmpunordpd", false);  return;  
  case ND_CMPEQSD: gen_sse_binop3(node, "cmpeqsd", false);  return;   
  case ND_CMPLTSD: gen_sse_binop3(node, "cmpltsd", false);  return;   
  case ND_CMPLESD: gen_sse_binop3(node, "cmplesd", false);  return;   
  case ND_CMPNEQSD: gen_sse_binop3(node, "cmpneqsd", false);  return;  
  case ND_CMPNLTSD: gen_sse_binop3(node, "cmpnltsd", false);  return;   
  case ND_CMPNLESD: gen_sse_binop3(node, "cmpnlesd", false);  return;   
  case ND_CMPORDSD: gen_sse_binop3(node, "cmpordsd", false);  return;   
  case ND_CMPUNORDSD: gen_sse_binop3(node, "cmpunordsd", false);  return;  
  case ND_COMISDEQ: gen_sse_binop4(node, "comisd", "sete");  return;  
  case ND_COMISDLT: gen_sse_binop4(node, "comisd", "setb");  return;  
  case ND_COMISDLE: gen_sse_binop4(node, "comisd", "setbe");  return; 
  case ND_COMISDGT: gen_sse_binop4(node, "comisd", "seta");  return;
  case ND_COMISDGE: gen_sse_binop4(node, "comisd", "setae");  return;    
  case ND_COMISDNEQ: gen_sse_binop4(node, "comisd", "setne");  return;   
  case ND_UCOMISDEQ: gen_sse_binop4(node, "ucomisd", "sete");  return;  
  case ND_UCOMISDLT: gen_sse_binop4(node, "ucomisd", "setb");  return;  
  case ND_UCOMISDLE: gen_sse_binop4(node, "ucomisd", "setbe");  return; 
  case ND_UCOMISDGT: gen_sse_binop4(node, "ucomisd", "seta");  return;
  case ND_UCOMISDGE: gen_sse_binop4(node, "ucomisd", "setae");  return;    
  case ND_UCOMISDNEQ: gen_sse_binop4(node, "ucomisd", "setne");  return;     
  case ND_MOVQ128: gen_movq128(node);  return;     
  case ND_CVTDQ2PD: gen_sse_binop2(node, "cvtdq2pd", "xmm0", false); return;
  case ND_CVTDQ2PS: gen_sse_binop2(node, "cvtdq2ps", "xmm0", false); return;
  case ND_CVTPD2DQ: gen_sse_binop2(node, "cvtpd2dq", "xmm0", false); return;
  case ND_CVTPD2PI: gen_cvt_mmx_binop3(node, "cvtpd2pi"); return;
  case ND_CVTPD2PS: gen_sse_binop2(node, "cvtpd2ps", "xmm0", false); return;
  case ND_CVTTPD2DQ: gen_sse_binop2(node, "cvttpd2dq", "xmm0", false); return;
  case ND_CVTTPD2PI: gen_cvt_mmx_binop3(node, "cvttpd2pi"); return;
  case ND_CVTPI2PD: gen_cvt_mmx_binop4(node, "cvtpi2pd"); return;
  case ND_CVTPS2DQ: gen_sse_binop2(node, "cvtps2dq", "xmm0", false); return;
  case ND_CVTTPS2DQ: gen_sse_binop2(node, "cvttps2dq", "xmm0", false); return;
  case ND_CVTPS2PD: gen_sse_binop2(node, "cvtps2pd", "xmm0", false); return;
  case ND_CVTSD2SI: gen_sse_binop2(node, "cvtsd2si", "eax", false); return;
  case ND_CVTSD2SI64: gen_sse_binop2(node, "cvtsd2siq", "rax", false); return;
  case ND_CVTTSD2SI: gen_sse_binop2(node, "cvttsd2si", "eax", false); return;
  case ND_CVTTSD2SI64: gen_sse_binop2(node, "cvttsd2siq", "rax", false); return;
  case ND_CVTSD2SS: gen_sse_binop3(node, "cvtsd2ss", false); return;
  case ND_CVTSI2SD:  gen_sse_binop11(node, "cvtsi2sd", "rax"); return;  
  case ND_CVTSI642SD:  gen_sse_binop11(node, "cvtsi2sdq", "rax"); return;  
  case ND_CVTSS2SD: gen_sse_binop3(node, "cvtss2sd", false); return;
  case ND_UNPCKHPD: gen_sse_binop3(node, "unpckhpd", false); return;
  case ND_UNPCKLPD: gen_sse_binop3(node, "unpcklpd", false); return;
  case ND_LOADHPD: gen_cvt_sse_binop2(node, "movhpd", "rax", true); return;
  case ND_LOADLPD: gen_cvt_sse_binop2(node, "movlpd", "rax", true); return;
  case ND_MOVMSKPD: gen_sse_binop2(node, "movmskpd", "rax", false);  return;   
  case ND_PACKSSWB128: gen_packss128_binop(node, "packsswb");  return;   
  case ND_PACKSSDW128: gen_packss128_binop(node, "packssdw");  return;   
  case ND_PACKUSWB128: gen_packss128_binop(node, "packuswb");  return;   
  case ND_PUNPCKHBW128: gen_packss128_binop(node, "punpckhbw");  return; 
  case ND_PUNPCKHWD128: gen_packss128_binop(node, "punpckhwd");  return;   
  case ND_PUNPCKHDQ128: gen_packss128_binop(node, "punpckhdq");  return;  
  case ND_PUNPCKHQDQ128: gen_packss128_binop(node, "punpckhqdq");  return;   
  case ND_PUNPCKLBW128: gen_packss128_binop(node, "punpcklbw");  return;   
  case ND_PUNPCKLWD128: gen_packss128_binop(node, "punpcklwd");  return;   
  case ND_PUNPCKLDQ128: gen_packss128_binop(node, "punpckldq");  return;   
  case ND_PUNPCKLQDQ128: gen_packss128_binop(node, "punpcklqdq");  return;   
  case ND_PADDSB128: gen_sse_binop3(node, "paddsb", false); return; 
  case ND_PADDSW128: gen_sse_binop3(node, "paddsw", false); return; 
  case ND_PADDUSB128: gen_sse_binop3(node, "paddusb", false); return; 
  case ND_PADDUSW128: gen_sse_binop3(node, "paddusw", false); return; 
  case ND_PSUBSB128: gen_sse_binop3(node, "psubsb", false); return; 
  case ND_PSUBSW128: gen_sse_binop3(node, "psubsw", false); return; 
  case ND_PSUBUSB128: gen_sse_binop3(node, "psubusb", false); return; 
  case ND_PSUBUSW128: gen_sse_binop3(node, "psubusw", false); return; 
  case ND_PMADDWD128: gen_sse_binop3(node, "pmaddwd", false); return; 
  case ND_PMULHW128: gen_sse_binop3(node, "pmulhw", false); return; 
  case ND_PMULUDQ:  case ND_PMULUDQ128: gen_sse_binop3(node, "pmuludq", false); return; 
  case ND_PSLLWI128: gen_psll_binop(node, "psllw"); return;
  case ND_PSLLDI128: gen_psll_binop(node, "pslld"); return;  
  case ND_PSLLQI128: gen_psll_binop(node, "psllq"); return;  
  case ND_PSRAWI128: gen_psll_binop(node, "psraw"); return;  
  case ND_PSRADI128: gen_psll_binop(node, "psrad"); return;  
  case ND_PSRLWI128: gen_psll_binop(node, "psrlw"); return;  
  case ND_PSRLDI128: gen_psll_binop(node, "psrld"); return;  
  case ND_PSRLQI128: gen_psll_binop(node, "psrlq"); return;  
  case ND_PSLLW128:gen_sse_binop3(node, "psllw", false); return; 
  case ND_PSLLD128:gen_sse_binop3(node, "pslld", false); return; 
  case ND_PSLLQ128:gen_sse_binop3(node, "psllq", false); return; 
  case ND_PSRAW128:gen_sse_binop3(node, "psraw", false); return; 
  case ND_PSRAD128:gen_sse_binop3(node, "psrad", false); return; 
  case ND_PSRLW128:gen_sse_binop3(node, "psrlw", false); return; 
  case ND_PSRLD128:gen_sse_binop3(node, "psrld", false); return; 
  case ND_PSRLQ128:gen_sse_binop3(node, "psrlq", false); return; 
  case ND_PANDN128:gen_sse_binop3(node, "pandn", false); return; 
  case ND_PMAXSW128:gen_sse_binop3(node, "pmaxsw", false); return; 
  case ND_PMAXUB128:gen_sse_binop3(node, "pmaxub", false); return; 
  case ND_PMINSW128:gen_sse_binop3(node, "pminsw", false); return; 
  case ND_PMINUB128:gen_sse_binop3(node, "pminub", false); return; 
  case ND_PHSUBW128:gen_sse_binop3(node, "phsubw", false); return;
  case ND_PHSUBD128:gen_sse_binop3(node, "phsubd", false); return;
  case ND_PHSUBSW128: gen_sse_binop3(node, "phsubsw", false); return;
  case ND_PMADDUBSW128: gen_sse_binop3(node, "pmaddubsw", false); return;
  case ND_PMULHRSW128: gen_sse_binop3(node, "pmulhrsw", false); return;
  case ND_PMOVMSKB128: gen_sse_binop2(node, "pmovmskb", "eax", false);  return;   
  case ND_PMULHUW128: gen_sse_binop9(node, "pmulhuw"); return; 
  case ND_PSHUFB128: gen_sse_binop3(node, "pshufb", false); return;
  case ND_PSIGNB128: gen_sse_binop3(node, "psignb", false); return;
  case ND_PSIGNW128: gen_sse_binop3(node, "psignw", false); return;
  case ND_PSIGND128: gen_sse_binop3(node, "psignd", false); return;  
  case ND_PHSUBW: gen_mmx_binop(node, "phsubw", false); return;
  case ND_PHSUBD: gen_mmx_binop(node, "phsubd", false); return;
  case ND_PHSUBSW: gen_mmx_binop(node, "phsubsw", false); return;
  case ND_PMADDUBSW: gen_mmx_binop(node, "pmaddubsw", false); return;
  case ND_PMULHRSW: gen_mmx_binop(node, "pmulhrsw", false); return;
  case ND_PSHUFB: gen_mmx_binop(node, "pshufb", false); return;
  case ND_PSIGNB: gen_mmx_binop(node, "psignb", false); return;
  case ND_PSIGNW: gen_mmx_binop(node, "psignw", false); return;
  case ND_PSIGND: gen_mmx_binop(node, "psignd", false); return;
  case ND_MASKMOVDQU: gen_maskmovdqu(node); return;
  case ND_PAVGB128:gen_sse_binop3(node, "pavgb", false); return; 
  case ND_PAVGW128:gen_sse_binop3(node, "pavgw", false); return; 
  case ND_PSADBW128:gen_sse_binop3(node, "psadbw", false); return; 
  case ND_MOVNTI: gen_movnti(node); return;
  case ND_MOVNTI64: gen_movnti64(node); return;
  case ND_MOVNTDQ: gen_movnt_binop(node, "movntdq"); return;
  case ND_MOVNTPD: gen_movnt_binop(node, "movntpd"); return;
  case ND_PARITYL:
  case ND_PARITYLL:
  case ND_PARITY: gen_parity(node); return;
  case ND_MWAIT: gen_mwait(node); return;
  case ND_MONITOR: gen_monitor(node); return;
  case ND_ADDSUBPS: gen_sse_binop3(node, "addsubps", false);  return;
  case ND_HADDPS: gen_sse_binop3(node, "haddps", false);  return;
  case ND_HSUBPS: gen_sse_binop3(node, "hsubps", false);  return;
  case ND_MOVSHDUP: gen_sse_binop12(node, "movshdup");  return;
  case ND_MOVSLDUP: gen_sse_binop12(node, "movsldup");  return;
  case ND_ADDSUBPD: gen_sse_binop3(node, "addsubpd", false);  return;
  case ND_HADDPD: gen_sse_binop3(node, "haddpd", false);  return;
  case ND_HSUBPD: gen_sse_binop3(node, "hsubpd", false);  return;  
  case ND_LDDQU: gen_lddqu(node); return;
  case ND_PABSB128: gen_sse_binop2(node, "pabsb", "xmm0", false); return;
  case ND_PABSW128: gen_sse_binop2(node, "pabsw", "xmm0", false); return;
  case ND_PABSD128: gen_sse_binop2(node, "pabsd", "xmm0", false); return;
  case ND_PABSB: gen_mmx_binop1(node, "pabsb"); return;
  case ND_PABSW: gen_mmx_binop1(node, "pabsw"); return;
  case ND_PABSD: gen_mmx_binop1(node, "pabsd"); return;
  case ND_PTESTZ128: gen_sse_testz(node); return;
  case ND_PTESTC128: gen_sse_testc(node); return;
  case ND_PTESTNZC128: gen_sse_testnzc(node); return;
  case ND_PBLENDVB128: gen_sse_pblendvb128(node); return;
  case ND_BLENDVPS: gen_sse_blendvpx(node, "blendvps"); return;
  case ND_BLENDVPD: gen_sse_blendvpx(node, "blendvpd"); return;
  case ND_PMINSB128: gen_sse_binop3(node, "pminsb", false); return; 
  case ND_PMAXSB128: gen_sse_binop3(node, "pmaxsb", false); return; 
  case ND_PMINUW128: gen_sse_binop3(node, "pminuw", false); return; 
  case ND_PMAXUW128: gen_sse_binop3(node, "pmaxuw", false); return;   
  case ND_PMINSD128: gen_sse_binop3(node, "pminsd", false); return; 
  case ND_PMAXSD128: gen_sse_binop3(node, "pmaxsd", false); return;     
  case ND_PMINUD128: gen_sse_binop3(node, "pminud", false); return; 
  case ND_PMAXUD128: gen_sse_binop3(node, "pmaxud", false); return;    
  case ND_PMULDQ128: gen_sse_binop3(node, "pmuldq", false); return;     
  case ND_PHMINPOSUW128: gen_sse_binop2(node, "phminposuw", "xmm0", false);  return; 
  case ND_PMOVSXBD128: gen_sse_binop2(node, "pmovsxbd", "xmm0", false);  return; 
  case ND_PMOVSXWD128: gen_sse_binop2(node, "pmovsxwd", "xmm0", false);  return;
  case ND_PMOVSXBQ128: gen_sse_binop2(node, "pmovsxbq", "xmm0", false);  return;
  case ND_PMOVSXDQ128: gen_sse_binop2(node, "pmovsxdq", "xmm0", false);  return;
  case ND_PMOVSXWQ128: gen_sse_binop2(node, "pmovsxwq", "xmm0", false);  return;
  case ND_PMOVSXBW128: gen_sse_binop2(node, "pmovsxbw", "xmm0", false);  return;
  case ND_PMOVZXBD128: gen_sse_binop2(node, "pmovzxbd", "xmm0", false);  return; 
  case ND_PMOVZXWD128: gen_sse_binop2(node, "pmovzxwd", "xmm0", false);  return;
  case ND_PMOVZXBQ128: gen_sse_binop2(node, "pmovzxbq", "xmm0", false);  return;
  case ND_PMOVZXDQ128: gen_sse_binop2(node, "pmovzxdq", "xmm0", false);  return;
  case ND_PMOVZXWQ128: gen_sse_binop2(node, "pmovzxwq", "xmm0", false);  return;
  case ND_PMOVZXBW128: gen_sse_binop2(node, "pmovzxbw", "xmm0", false);  return;
  case ND_PACKUSDW128: gen_sse_binop3(node, "packusdw", false); return; 
  case ND_MOVNTDQA: gen_movntdqa(node); return;
  case ND_CRC32QI: gen_crc32qi(node); return;
  case ND_CRC32HI: gen_crc32hi(node); return;
  case ND_CRC32SI: gen_crc32si(node); return;
  case ND_CRC32DI: gen_crc32di(node); return;
  case ND_PSHUFD: gen_pshufd(node); return;
  case ND_PREFETCH: gen_prefetch(node); return;
  case ND_RDTSC: gen_rdtsc(node); return;
  case ND_READEFLAGS_U64: gen_readeflags_u64(node); return;
  case ND_RDSSPQ: gen_binop1(node, "rdsspq"); return;
  case ND_SAVEPREVSSP: gen_singleop(node, "saveprevssp"); return;
  case ND_SETSSBSY: gen_singleop(node, "setssbsy"); return;
  case ND_SLWPCB: gen_binop1(node, "slwpcb"); return;
  case ND_RDPKRU: gen_rdpkru(node); return;
  case ND_XBEGIN: gen_nothing(node); return;
  case ND_XEND: gen_singleop(node, "xend"); return;
  case ND_SERIALIZE: gen_singleop(node, "serialize"); return;
  case ND_XSUSLDTRK: gen_singleop(node, "xsusldtrk"); return;
  case ND_XRESLDTRK: gen_singleop(node, "xresldtrk"); return;
  case ND_CLUI: gen_singleop(node, "clui"); return;
  case ND_STUI: gen_singleop(node, "stui"); return;
  case ND_TESTUI: gen_singleop(node, "testui"); return;
  case ND_WBNOINVD: gen_singleop(node, "wbnoinvd"); return;
  case ND_XTEST: gen_singleop(node, "xtest"); return;
  case ND_WBINVD: gen_singleop(node, "wbinvd"); return;
  case ND_RDPID: gen_binop1(node, "rdpid"); return;
  case ND_RDFSBASE32: 
  case ND_RDFSBASE64: gen_binop2(node, "rdfsbase"); return;
  case ND_RDGSBASE32: 
  case ND_RDGSBASE64: gen_binop2(node, "rdgsbase"); return;
  case ND_VZEROALL: gen_singleop(node, "vzeroall"); return;
  case ND_VZEROUPPER: gen_singleop(node, "vzeroupper"); return;
  case ND_FEMMS: gen_singleop(node, "femms"); return;
  case ND_BSRSI: gen_bsrsi(node); return;
  case ND_RDPMC: gen_rdpmc(node); return;
  case ND_RDTSCP: gen_rdtscp(node); return;
  case ND_ROLQI: gen_rolqi(node); return;
  case ND_RORQI: gen_rorqi(node); return;
  case ND_ROLHI: gen_rolhi(node); return;
  case ND_RORHI: gen_rorhi(node); return;  
  case ND_BSRDI: gen_bsrdi(node); return;  
  case ND_WRITEEFLAGS_U64: gen_writeeflags_u64(node); return;  
  case ND_INCSSPQ: gen_incsspq(node); return;
  case ND_RSTORSSP: gen_rstorssp(node); return;
  case ND_WRSSD: gen_wrssd(node); return;
  case ND_WRSSQ: gen_wrssq(node); return;
  case ND_WRUSSD: gen_wrussd(node); return;
  case ND_WRUSSQ: gen_wrussq(node); return;
  case ND_CLRSSBSY: gen_clrssbsy(node); return;
  case ND_SBB_U32: gen_sbb_u32(node); return;  
  case ND_ADDCARRYX_U32: gen_addcarryx_u32(node); return;
  case ND_SBB_U64: gen_sbb_u64(node); return;
  case ND_ADDCARRYX_U64: gen_addcarryx_u64(node); return;
  case ND_TZCNT_U16: gen_tzcnt_u16(node); return;
  case ND_BEXTR_U32: gen_bextr_u32(node); return;
  case ND_FPCLASSIFY: gen_fpclassify(node->fpc); return;
  case ND_ISUNORDERED: gen_isunordered(node); return;
  case ND_SIGNBIT:
  case ND_SIGNBITF:
  case ND_SIGNBITL: gen_signbit(node); return;
}
  
if (node->lhs && (is_vector(node->lhs->ty) || (node->rhs && is_vector(node->rhs->ty)))) {
  gen_vector_op(node);
  return;
}
  //managing INT128
  if (is_int128(node->lhs->ty)) {
    gen_int128_op(node);
    return;
  } 

switch (node->lhs->ty->kind)
{
  case TY_FLOAT:
  case TY_DOUBLE:
  {
    gen_expr(node->rhs);
    push_tmpf();
    gen_expr(node->lhs);
    pop_tmpf(1);

    char *sz = (node->lhs->ty->kind == TY_FLOAT) ? "ss" : "sd";

    switch (node->kind)
    {
    case ND_ADD:
      println("  add%s %%xmm1, %%xmm0", sz);
      return;
    case ND_SUB:
      println("  sub%s %%xmm1, %%xmm0", sz);
      return;
    case ND_MUL:
      println("  mul%s %%xmm1, %%xmm0", sz);
      return;
    case ND_DIV:
      println("  div%s %%xmm1, %%xmm0", sz);
      return;
    case ND_EQ:
    case ND_NE:
    case ND_LT:
    case ND_LE:
      println("  ucomi%s %%xmm0, %%xmm1", sz);

      if (node->kind == ND_EQ)
      {
        println("  sete %%al");
        println("  setnp %%dl");
        println("  and %%dl, %%al");
      }
      else if (node->kind == ND_NE)
      {
        println("  setne %%al");
        println("  setp %%dl");
        println("  or %%dl, %%al");
      }
      else if (node->kind == ND_LT)
      {
        println("  seta %%al");
      }
      else
      {
        println("  setae %%al");
      }

      println("  and $1, %%al");
      println("  movzb %%al, %%rax");
      return;
    }

    error_tok(node->tok, "%s invalid expression", __FILE__);
  }
  case TY_LDOUBLE:
  {
    gen_expr(node->lhs);
    pushld();
    gen_expr(node->rhs);
    popld();

    switch (node->kind)
    {
    case ND_ADD:
      println("  faddp");
      return;
    case ND_SUB:
      println("  fsubp");
      return;
    case ND_MUL:
      println("  fmulp");
      return;
    case ND_DIV:
      println("  fdivp");
      return;
    case ND_EQ:
    case ND_NE:
    case ND_LT:
    case ND_LE:
      println("  fucomip");
      println("  fstp %%st(0)");

      if (node->kind == ND_EQ) {
        println("  sete %%al");
        println("  setnp %%dl");
        println("  and %%dl, %%al");
      } else if (node->kind == ND_NE) {
        println("  setne %%al");
        println("  setp %%dl");
        println("  or %%dl, %%al");
      } else if (node->kind == ND_LT) {        
        println("  setb %%al");
        println("  setnp %%dl");
        println("  and %%dl, %%al");
      } else {
        println("  setbe %%al");
        println("  setnp %%dl");
        println("  and %%dl, %%al");   
      }

      println("  movzbl %%al, %%eax");
      return;
    }


    error_tok(node->tok, "%s invalid expression", __FILE__);
  }
  }

  if (!is_int128(node->rhs->ty)) {
    gen_expr(node->rhs);
    push_tmp();
    gen_expr(node->lhs);
    pop_tmp("%rdi");
  }

  char *ax, *di, *dx;

  if (node->lhs->ty->size == 8 || node->lhs->ty->base)
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
    println("  sub %s, %s", di, ax);
    return;
  case ND_MUL:
    println("  imul %s, %s", di, ax);
    return;
  case ND_DIV:
  case ND_MOD:
    if (node->ty->is_unsigned)
    {
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
    return;
  case ND_BITAND:
    println("  and %s, %s", di, ax);
    return;
  case ND_BITOR:
    println("  or %s, %s", di, ax);
    return;
  case ND_BITXOR:
    println("  xor %s, %s", di, ax);
    return;
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
    println("  cmp %s, %s", di, ax);

    if (node->kind == ND_EQ)
    {
      println("  sete %%al");
    }
    else if (node->kind == ND_NE)
    {
      println("  setne %%al");
    }
    else if (node->kind == ND_LT)
    {
      if (node->lhs->ty->is_unsigned)
        println("  setb %%al");
      else
        println("  setl %%al");
    }
    else if (node->kind == ND_LE)
    {
      if (node->lhs->ty->is_unsigned)
        println("  setbe %%al");
      else
        println("  setle %%al");
    }

    println("  movzb %%al, %%rax");
    return;
  case ND_SHL:
    println("  mov %%rdi, %%rcx");
    println("  shl %%cl, %s", ax);
    return;
  case ND_SHR:
    println("  mov %%rdi, %%rcx");
    if (node->lhs->ty->is_unsigned)
      println("  shr %%cl, %s", ax);
    else
      println("  sar %%cl, %s", ax);
    return;
  }

  error_tok(node->tok, "%s invalid expression", __FILE__);
}

static void gen_stmt(Node *node)
{
  if (!node)
    error("%s: %s:%d: error: in gen_stmt : node is null!", __FILE__, __FILE__, __LINE__);
  if (node->tok && node->tok->line_no != last_loc_line) {
  println("  .loc %d %u", node->tok->file->file_no, node->tok->line_no);
        last_loc_line = node->tok->line_no;
  }

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
      char *ax, *di, *dx;

      if (node->cond->ty->size == 8) {
        ax = "%rax";
        di = "%rdi";
        dx = "%rdx";
      } else {
        ax = "%eax";
        di = "%edi";
        dx = "%edx";
      }

      if (n->begin == n->end) {
        println("  mov $%ld, %s", n->begin, dx);
        println("  cmp %s, %s", dx, ax);
        println("  je %s", n->label);
        continue;
      }

      // [GNU] Case ranges
      println("  mov %s, %s", ax, di);
      println("  mov $%ld, %s", n->begin, dx);
      println("  sub %s, %s", dx, di);
      println("  mov $%ld, %s", n->end - n->begin, dx);
      println("  cmp %s, %s", dx, di);
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
    if (node->lhs)
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
    if (node->lhs)    
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

    println("  jmp .L.return.%s", sym(current_fn));
    return;
  case ND_EXPR_STMT:
    gen_expr(node->lhs);
    if (node->lhs->ty && node->lhs->ty->kind == TY_LDOUBLE)
      println("  fstp %%st(0)");
    return;
  case ND_ASM:
    println("  %s", node->asm_str);
    return;
  }

  error_tok(node->tok, "%s invalid statement", __FILE__);
}


static void emit_data(Obj *prog)
{
  for (Obj *var = prog; var; var = var->next)
  {
    //issue 35 about array not initialized completely.
    if (var->ty->size != 0)
      println("  .zero %ld", labs(var->ty->size));
    if (var->alias_name)
      println("  .set \"%s\", %s", sym(var), var->alias_name);
    if (var->is_weak)
      println("  .weak \"%s\"", sym(var));
    if (var->is_function || !var->is_definition)
      continue;
    print_visibility(var);

    int align = (var->ty->kind == TY_ARRAY && var->ty->size >= 16)
                    ? MAX(16, var->align)
                    : var->align;

    // Common symbol
    if (opt_fcommon && var->is_tentative && !var->is_tls && !var->section && !var->is_static)
    {
      if (var->ty->kind == TY_FUNC)
         continue;
      //from @fuhsnn incomplete array assuming to have one element
      if (var->ty->kind == TY_ARRAY && var->ty->size < 0)
        var->ty->size = var->ty->base->size;
      println("  .comm %s, %ld, %d", sym(var), var->ty->size, align);
      continue;
    }
    

    // .data or .tdata
    if (var->init_data)
    {
      //from cosmopolitan
      if (var->section) {
        println("  .section %s,\"aw\",@progbits", var->section);
      }
      else if (var->is_tls)
        println("  .section .tdata,\"awT\",@progbits");
      else
        println("  .section .data,\"aw\",@progbits");

            
      println("  .type %s, @object", sym(var));
      println("  .size %s, %ld", sym(var), labs(var->ty->size));
      if (align > 1) println("  .align %d", align);
      println("%s:", sym(var));


      Relocation *rel = var->rel;
      int unit_size = (var->ty->kind == TY_ARRAY) ? var->ty->base->size : var->ty->size;
      int pos = 0;
      while (pos < var->ty->size)
      {
        if (rel && rel->offset == pos)
        {
          if (var->is_function) {
            println("  .long %s - . + %ld", *rel->label, rel->addend);
          } else if (!var->is_extern) {
            println("  .quad %s%+ld", *rel->label, rel->addend);
          }
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


      println("  .size %s, %ld", sym(var), var->ty->size);
      continue;
    }

    if (var->section) {
      println("  .section %s,\"aw\",@nobits", var->section);
    }
    else if (var->is_tls)
      println("  .section .tbss,\"awT\",@nobits");
    else
      println("  .section .bss,\"aw\",@nobits");

    if (align > 1) println("  .align %d", align);
    println("%s:", sym(var));
    if (var->ty->size != 0)
      println("  .zero %ld", labs(var->ty->size));
  }
}

static void store_fp(int r, int offset, int sz, char *ptr)
{
  switch (sz) {
  case 0:
    // No operation for size 0
    return;  
  case 2:
    // movw is used for 2-byte (16-bit) words
    println("  movw %%xmm%d, %d(%s)", r, offset, ptr);
    return;
  case 4:
    println("  movss %%xmm%d, %d(%s)", r, offset, ptr);
    return;
  case 8:
    println("  movsd %%xmm%d, %d(%s)", r, offset, ptr);
    return;
  case 16:
    println("  movups %%xmm%d, %d(%s)", r, offset, ptr); // movaps for 16-byte (128-bit) vector
    return;
  }
  
  // Handle wide FP/vector objects (32, 64, ...)
  if (sz % 16 == 0) {
    for (int i = 0; i < sz; i += 16) {
      println("  movups %%xmm%d, %d(%s)", r + i / 16, offset + i, ptr);
    }
    return;
  }
  printf("===== r=%d offset=%d sz=%d\n", r, offset, sz);
  unreachable();
}

static void store_gp(int r, int offset, int sz, char *ptr) {
  switch (sz) {
  case 0:
    // No operation for size 0
    return;      
  case 1:
    println("  mov %s, %d(%s)", argreg8[r], offset, ptr);
    return;
  case 2:
    println("  mov %s, %d(%s)", argreg16[r], offset, ptr);
    return;
  case 4:
    println("  mov %s, %d(%s)", argreg32[r], offset, ptr);
    return;
  case 8:
    println("  mov %s, %d(%s)", argreg64[r], offset, ptr);
    return;
  case 16:
    // Assuming we can use xmm registers to store 128 bits
    println("  movdqu %%xmm%d, %d(%s)", r, offset, ptr);
    return;
  default:
    for (int i = 0; i < sz; i++) {
      println("  mov %s, %d(%s)", argreg8[r], offset + i, ptr);
      println("  shr $8, %s", argreg64[r]);
    }
    return;
  }
}


static void emit_text(Obj *prog)
{
  
  // First pass: collect constructor/destructor attributes
  for (Obj *fn = prog; fn; fn = fn->next) {

    if (!fn->is_function || !fn->is_definition)
      continue;

    if (fn->is_constructor || fn->ty->is_constructor) {
      int priority = fn->constructor_priority > fn->ty->constructor_priority
                    ? fn->constructor_priority
                    : fn->ty->constructor_priority;
      if (priority < 0 || priority > 65535)
        priority = 65535;

      CtorFunc *f = calloc(1, sizeof(CtorFunc));
      f->name = sym(fn);
      f->priority = priority;
      constructors[constructor_cnt++] = f;
    }

    // Combine destructor flags and pick max priority
    if (fn->is_destructor || fn->ty->is_destructor) {
      int priority = fn->destructor_priority > fn->ty->destructor_priority
                    ? fn->destructor_priority
                    : fn->ty->destructor_priority;
      if (priority < 0 || priority > 65535)
        priority = 65535;

      CtorFunc *f = calloc(1, sizeof(CtorFunc));
      f->name = sym(fn);
      f->priority = priority;
      destructors[destructor_cnt++] = f;
    }

  }

  println("  .section .text");
  println(".L.text_start:");
  for (Obj *fn = prog; fn; fn = fn->next)
  {
    // Emit alias if fn->alias_name is set
    if (fn->alias_name) {
      // Handle weak alias
      println("  .weak %s", sym(fn));                 // Mark the function as weak
      println("  .set %s, %s", sym(fn), fn->alias_name);  // Define alias
    }

    if (!fn->is_function || !fn->is_definition)
      continue;


    // No code is emitted for "static inline" functions
    // if no one is referencing them.
    if (!fn->is_live)
      continue;

    if (fn->is_static)
      println("  .local %s", sym(fn));
    else 
      println("  .globl %s", sym(fn));

    // Respect section attribute if set
    if (fn->section)
      println("  .section %s,\"ax\",@progbits", fn->section);
    else
      println("  .section .text,\"ax\",@progbits");
    println("  .type %s, @function", sym(fn));
    println("%s:", sym(fn));

    current_fn = fn;
    tmp_stack.bottom = fn->stack_size;

    bool use_rbx = (fn->stack_align > 16);
    lvar_ptr = use_rbx ? "%rbx" : "%rbp";
    // Prologue
    long reserved_pos = ftell(output_file);
   
    if (!is_omit_fp(fn)) {
    println("  push %%rbp");
    println("  .cfi_startproc");
    println("  .cfi_def_cfa_offset 16");
    println("  .cfi_offset %%rbp, -16");    
    println("  mov %%rsp, %%rbp");
    println("  .cfi_def_cfa_register %%rbp");  
    }
  
    if (use_rbx) {
      println("  push %%rbx");
      println("  mov %%rsp, %%rbx");
      println("  and $-%d, %%rbx", fn->stack_align);
      println("  mov %%rbx, %%rsp");
    }

    // Place .L.body label:
    // - BEFORE sub for frame-pointer functions (allows RSP restoration + re-execution of sub)
    // - AFTER sub for omit-fp functions (avoids re-allocating stack on each jump)
    // Note: Recursive TCO is disabled for omit-fp with stack params, so no offset issues
    if (!is_omit_fp(fn))
      println(".L.body.%s:", sym(fn));
    
    reserved_pos = ftell(output_file);
    println("                           ");
    
    if (is_omit_fp(fn))
      println(".L.body.%s:", sym(fn));
    
    // Save RSP for alloca/VLA support if needed
    if (fn->alloca_bottom && fn->alloca_bottom->offset)
      println("  mov %%rsp, %d(%s)", fn->alloca_bottom->offset, lvar_ptr);
    //issue with postgres and local variables not initialized!
    for (Obj *var = fn->locals; var; var = var->next) {     
        if (!var->init && !var->is_param &&
            (var->ty->kind == TY_STRUCT ||
            var->ty->kind == TY_UNION ||
            var->ty->kind == TY_ARRAY ||
            is_vector(var->ty))) {
            gen_mem_zero(var->offset, var->ty->size);
        }
    }


    // Save arg registers if function is variadic
    if (fn->va_area)
    {
      int gp = 0, fp = 0;
      for (Obj *var = fn->params; var; var = var->next)
      {
        Type *ty = var->ty;
        if (!ty)
          error("%s %d: in emit_text : type is null!", __FILE__, __LINE__);  
        switch (ty->kind)
        {
          case TY_STRUCT:
          case TY_UNION:
            if (ty->size == 0)
              continue;
            if (!pass_by_reg(ty, gp, fp))
              continue;

            if (has_flonum1(ty))
              fp++;
            else
              gp++;

            if (ty->size > 8) {
              if (has_flonum2(ty))
          fp++;
        else
          gp++;
            }
            continue;
          case TY_VECTOR:
          case TY_FLOAT:
          case TY_DOUBLE:
            if (fp < FP_MAX)
              fp++;
            continue;
          case TY_LDOUBLE:
            continue;
          case TY_INT128:
            if (gp + 1 < FP_MAX) {
              gp++;
              gp++;
            }
            continue;                      
          default:
            if (gp < GP_MAX)
              gp++;
        }
      }

      int off = fn->va_area->offset;
      char *ptr = fn->va_area->ptr;
      if (is_omit_fp(fn))
        off += fn->stack_size;

      // va_elem
      println("  movl $%d, %d(%s)", gp * 8, off, ptr);          // gp_offset
      println("  movl $%d, %d(%s)", fp * 16 + 48, off + 4, ptr); // fp_offset
      if (is_omit_fp(fn)) {
        println("  movq %%rsp, %d(%s)", off + 8, ptr);            // overflow_arg_area
        println("  addq $%d, %d(%s)", fn->stack_size + fn->overflow_arg_area - 8, off + 8, ptr);
      } else {
      println("  movq %%rbp, %d(%s)", off + 8, ptr);            // overflow_arg_area
      println("  addq $%d, %d(%s)", fn->overflow_arg_area, off + 8, ptr);
      }
      println("  movq %s, %d(%s)", ptr, off + 16, ptr); // reg_save_area
      println("  addq $%d, %d(%s)", off + 24, off + 16, ptr);

      // __reg_save_area__
      println("  movq %%rdi, %d(%s)", off + 24, ptr);
      println("  movq %%rsi, %d(%s)", off + 32, ptr);
      println("  movq %%rdx, %d(%s)", off + 40, ptr);
      println("  movq %%rcx, %d(%s)", off + 48, ptr);
      println("  movq %%r8, %d(%s)", off + 56, ptr);
      println("  movq %%r9, %d(%s)", off + 64, ptr);
      println("  movups %%xmm0, %d(%s)", off + 72, ptr);
      println("  movups %%xmm1, %d(%s)", off + 88, ptr);
      println("  movups %%xmm2, %d(%s)", off + 104, ptr);
      println("  movups %%xmm3, %d(%s)", off + 120, ptr);
      println("  movups %%xmm4, %d(%s)", off + 136, ptr);
      println("  movups %%xmm5, %d(%s)", off + 152, ptr);
      println("  movups %%xmm6, %d(%s)", off + 168, ptr);
      println("  movups %%xmm7, %d(%s)", off + 184, ptr);
    }

    // Save passed-by-register arguments to the stack
    int gp = 0, fp = 0;
    for (Obj *var = fn->params; var; var = var->next)
    {
      // if (var->offset > 0)
      //   continue;
      if (var->pass_by_stack)
        continue;
        
      int offset = var->offset;  
        if (offset == 0) {
          if (is_omit_fp(fn))
            offset = -16;
          else
            offset = -fn->stack_size - 16;
        } else if (is_omit_fp(fn))
            offset += fn->stack_size;

      Type *ty = var->ty;
      if (!ty)
        error("%s %d: in emit_text : type is null!", __FILE__, __LINE__);  
      switch (ty->kind)
      {
      case TY_VECTOR:
        if (ty->base->kind == TY_FLOAT || ty->base->kind == TY_DOUBLE) {
          store_fp(fp++, offset, ty->size, var->ptr);
        } else if (is_integer(ty->base)) {
          store_fp(fp++, offset, ty->size, var->ptr);
        } else {
          error("%s %d: in emit_text : Unsupported vector base type", __FILE__, __LINE__);  
        }
        break;
      case TY_STRUCT:
      case TY_UNION:
        assert(ty->size <= 16);
        if (has_flonum(ty, 0, 8, 0))
          store_fp(fp++, offset, MIN(8, ty->size), var->ptr);
        else
          store_gp(gp++, offset, MIN(8, ty->size), var->ptr);

        if (ty->size > 8)
        {
          if (has_flonum(ty, 8, 16, 0))
            store_fp(fp++, offset + 8, ty->size - 8, var->ptr);
          else
            store_gp(gp++, offset + 8, ty->size - 8, var->ptr);
        }
        break;
      case TY_FLOAT:
      case TY_DOUBLE:
        store_fp(fp++, offset, ty->size, var->ptr);
        break;
      case TY_INT128:
        store_gp(gp++, offset + 0, 8, var->ptr);
        store_gp(gp++, offset + 8, 8, var->ptr);
        break;
      default:
        store_gp(gp++, offset, ty->size, var->ptr);
      }
    }

    // Emit code
    gen_stmt(fn->body);
    assert(depth == 0);
    assert(tmp_stack.depth == 0);
    long cur_pos = ftell(output_file);
    fseek(output_file, reserved_pos, SEEK_SET);
    //println("  sub $%d, %%rsp", align_to(tmp_stack.bottom, 16));
    if (is_omit_fp(fn))
      println("  sub $%d, %%rsp", tmp_stack.bottom);
    else
      println("  sub $%d, %%rsp", align_to(tmp_stack.bottom, 16));
    fseek(output_file, cur_pos, SEEK_SET);

    // [https://www.sigbus.info/n1570#5.1.2.2.3p1] The C spec defines
    // a special rule for the main function. Reaching the end of the
    // main function is equivalent to returning 0, even though the
    // behavior is undefined for the other functions.
    if (strcmp(sym(fn), "main") == 0) {
      println("  mov $0, %%rax");
    } 

    // Epilogue
    println(".L.return.%s:", sym(fn));
    if (use_rbx)
      println("  mov -8(%%rbp), %%rbx");
    if (!is_omit_fp(fn)) {
    println("  mov %%rbp, %%rsp");
    println("  pop %%rbp");
    println("  .cfi_def_cfa %%rsp, 8");
    } else {
      println("  add $%d, %%rsp", fn->stack_size);
    }
    println("  ret");
    if (!is_omit_fp(fn)) 
      println("  .cfi_endproc");
    println("  .size %s, .-%s", sym(fn), sym(fn));
    println(".L.end.%s:", sym(fn));
  }
  println(".L.text_end:");
  emit_constructors(); 
  emit_destructors(); 
  
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
  emit_debug_info(prog);
  println("  .section  .note.GNU-stack,\"\",@progbits");
  //print offset for each variable
  if (isDebug)
    print_offset(prog);
}



// Print offset.
static void print_offset(Obj *prog)
{
  for (Obj *fn = prog; fn; fn = fn->next)
  {

      
    for (Obj *var = fn->params; var; var = var->next)
    {
    printf("=====fn_name=%s var_name=%s offset=%d stack_size=%d var_alignment=%d\n", sym(fn), sym(var), var->offset, fn->stack_size, var->stack_align );
    }
    for (Obj *var = fn->locals; var; var = var->next)
    {
      printf("=====fn_name=%s var_name=%s offset=%d stack_size=%d var_alignment=%d\n", sym(fn), sym(var), var->offset, fn->stack_size, var->align );
      //update the function name if it's missing
      if (!var->funcname)
        var->funcname = sym(fn);
    }

  }
}

static int get_align(Obj *var) {
  int align = var->align;
  if ((var->ty->kind == TY_ARRAY && var->ty->size >= 16) || 
      is_vector(var->ty) || var->ty->kind == TY_INT128)
    align = MAX(16, align);
  return align;
}

static int get_lvar_align(Obj *fn, int align) {
  for (Obj *var = fn->locals; var; var = var->next)
    align = MAX(align, get_align(var));
  return align;
}

static int assign_lvar_offsets2(Obj *fn, int bottom, char *ptr) {
  for (Obj *var = fn->locals; var; var = var->next) {
    int align = get_align(var);

    if (var->offset) {
      // Skip variables that already have an offset
      continue;
    }

    // When the frame uses a super-aligned base pointer (stack_align > 16),
    // each variable's slot size must be a multiple of stack_align
    int size = var->ty->size;
    if (fn->stack_align > 16)
      size = align_to(size, fn->stack_align);

    bottom = align_to(bottom + size, align);
    var->offset = -bottom;
    var->ptr = ptr;
  }
  return align_to(bottom, 16);
}


void assign_lvar_offsets(Obj *prog) {
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;

    fn->stack_align = get_lvar_align(fn, 16);
    bool omit_fp = is_omit_fp(fn);

    int bottom = fn->stack_size;
    if (omit_fp) bottom -= 8;
    if (bottom < 0) bottom = 0;

    int gp = 0, fp = 0;
    int max_align = 8;
    int stack = 0;

    // If variables already have offsets (assigned during parsing for inline asm),
    // ensure 'bottom' reflects the space they occupy.
    for (Obj *var = fn->locals; var; var = var->next) {
      if (var->offset && !var->is_param) {
        int limit = -var->offset; // offsets are negative
        if (limit > bottom) bottom = limit;
      }
    }

    for (Obj *var = fn->params; var; var = var->next) {
      var->is_param = true;
      if (var->offset) continue;

      Type *ty = var->ty;
      if (!ty) error("%s %d: type is null!", __FILE__, __LINE__);

      // ABI: Check if passed in registers
      if (ty->kind == TY_STRUCT || ty->kind == TY_UNION) {
        if (pass_by_reg(ty, gp, fp)) {
          fp += has_flonum1(ty) + (ty->size > 8 && has_flonum2(ty));
          gp += !has_flonum1(ty) + (ty->size > 8 && !has_flonum2(ty));
          continue;
        }
      } else if (ty->kind == TY_VECTOR || ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE) {
        if (fp < FP_MAX) { fp++; continue; }
      } else if (ty->kind == TY_INT128) {
        if (gp + 1 < GP_MAX) { gp += 2; continue; }
      } else if (ty->kind != TY_LDOUBLE) {
        if (gp++ < GP_MAX) continue;
      }

      // Passed on stack
      var->pass_by_stack = true;
      int align = (ty->kind == TY_STRUCT || ty->kind == TY_UNION) ? MAX(ty->align, 8) :
                  (ty->kind == TY_LDOUBLE || ty->kind == TY_INT128 || ty->kind == TY_VECTOR) ? 16 : 8;
      max_align = MAX(max_align, align);
      
      stack = align_to(stack, align);
      if (omit_fp) {
        var->offset = stack + 8;
        var->ptr = "%rsp";
      } else {
      var->offset = stack + 16;
      var->ptr = "%rbp";
      }

      int size = (ty->kind == TY_STRUCT || ty->kind == TY_UNION) ? align_to(ty->size, align) :
                 (ty->kind == TY_LDOUBLE || ty->kind == TY_INT128 || ty->kind == TY_VECTOR) ? 16 : 8;
      stack += size;
    }

    if (fn->ty->is_variadic)
      fn->overflow_arg_area = stack + 16;

    char *base = omit_fp ? "%rsp" : (fn->stack_align > 16) ? "%rbx" : "%rbp";
    fn->stack_size = assign_lvar_offsets2(fn, bottom, base);
    if (omit_fp)
      fn->stack_size += 8;
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
  error("%s: %s:%d: error: in register_available : no register available!", __FILE__, __FILE__, __LINE__);
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
  error("%s: %s:%d: error: in register8_to_64 : unexpected error!", __FILE__, __FILE__, __LINE__);
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
  error("%s: %s:%d: error: in register16_to_64 : unexpected error!", __FILE__, __FILE__, __LINE__);
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
  error("%s: %s:%d: error: in register32_to_64 : unexpected error!", __FILE__, __FILE__, __LINE__);
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

static int cmp_ctor(const void *a, const void *b) {
  return (*(CtorFunc **)a)->priority - (*(CtorFunc **)b)->priority;
}



static void emit_constructors(void) {
  if (constructor_cnt == 0)
    return;
  qsort(constructors, constructor_cnt, sizeof(CtorFunc *), cmp_ctor);
  println("  .section .init_array,\"aw\",@init_array");
  println("  .p2align 3");
  for (int i = 0; i < constructor_cnt; i++) {
    println("  .quad %s", constructors[i]->name);
  }
  println("  .text");
}


static void emit_destructors(void) {
  if (destructor_cnt == 0)
    return;
  qsort(destructors, destructor_cnt, sizeof(CtorFunc *), cmp_ctor);
  println("  .section .fini_array,\"aw\",@fini_array");
  println("  .p2align 3");
  for (int i = 0; i < destructor_cnt; i++) {
    println("  .quad %s", destructors[i]->name);
  }
  println("  .text");
}


#define FPCLASSIFY_FLOAT \
  "\tmovaps\t%%xmm0,%%xmm1\n\
\tmov\t$0x7fffffff,%%eax\n\
\tmovd\t%%eax,%%xmm2\n\
\tandps\t%%xmm2,%%xmm1\n\
\tmov\t$%d,%%eax\n\
\tucomiss\t%%xmm1,%%xmm1\n\
\tjp\t9f\n\
\tmov\t$0x7f7fffff,%%edi\n\
\tmovd\t%%edi,%%xmm2\n\
\tucomiss\t%%xmm2,%%xmm1\n\
\tja\t2f\n\
\tmov\t$0x00800000,%%edi\n\
\tmovd\t%%edi,%%xmm2\n\
\tucomiss\t%%xmm2,%%xmm1\n\
\tjnb\t3f\n\
\txorps\t%%xmm1,%%xmm1\n\
\tucomiss\t%%xmm1,%%xmm0\n\
\tjp\t1f\n\
\tmovl\t$%d,%%eax\n\
\tje\t9f\n\
1:\tmovl\t$%d,%%eax\n\
\tjmp\t9f\n\
2:\tmovl\t$%d,%%eax\n\
\tjmp\t9f\n\
3:\tmovl\t$%d,%%eax\n\
9:"

#define FPCLASSIFY_DOUBLE \
  "\tmovapd\t%%xmm0,%%xmm1\n\
\tmov\t$0x7fffffffffffffff,%%rax\n\
\tmovq\t%%rax,%%xmm2\n\
\tandps\t%%xmm2,%%xmm1\n\
\tmov\t$%d,%%eax\n\
\tucomisd\t%%xmm1,%%xmm1\n\
\tjp\t9f\n\
\tmov\t$0x7fefffffffffffff,%%rdi\n\
\tmovq\t%%rdi,%%xmm2\n\
\tucomisd\t%%xmm2,%%xmm1\n\
\tja\t2f\n\
\tmov\t$0x0010000000000000,%%rdi\n\
\tmovq\t%%rdi,%%xmm2\n\
\tucomisd\t%%xmm2,%%xmm1\n\
\tjnb\t3f\n\
\txorps\t%%xmm1,%%xmm1\n\
\tucomisd\t%%xmm1,%%xmm0\n\
\tjp\t1f\n\
\tmovl\t$%d,%%eax\n\
\tje\t9f\n\
1:\tmovl\t$%d,%%eax\n\
\tjmp\t9f\n\
2:\tmovl\t$%d,%%eax\n\
\tjmp\t9f\n\
3:\tmovl\t$%d,%%eax\n\
9:"

#define FPCLASSIFY_LDOUBLE \
  "\tmov\t$%d,%%eax\n\
\tfld\t%%st\n\
\tfabs\n\
\tfucomi\t%%st,%%st\n\
\tjp\t6f\n\
\tpush\t$0x7ffe\n\
\tpush\t$-1\n\
\tfldt\t(%%rsp)\n\
\tadd\t$16,%%rsp\n\
\tfxch\n\
\tmov\t$%d,%%eax\n\
\tfucomi\n\
\tfstp\t%%st(1)\n\
\tja\t7f\n\
\tmov\t$1,%%edi\n\
\tpush\t%%rdi\n\
\tror\t%%rdi\n\
\tpush\t%%rdi\n\
\tfldt\t(%%rsp)\n\
\tadd\t$16,%%rsp\n\
\tfxch\n\
\tmov\t$%d,%%eax\n\
\tfucomip\n\
\tfstp\t%%st\n\
\tjnb\t8f\n\
\tfldz\n\
\tfxch\n\
\tfucomip\n\
\tfstp\t%%st\n\
\tjp\t5f\n\
\tmov\t$%d,%%eax\n\
\tje\t9f\n\
5:\tmov\t$%d,%%eax\n\
\tjmp\t9f\n\
6:\tfstp\t%%st\n\
\tfstp\t%%st\n\
\tjmp\t9f\n\
7:\tfstp\t%%st\n\
\tfstp\t%%st\n\
\tjmp\t9f\n\
8:\tfstp\t%%st\n\
9:"

void gen_fpclassify(FpClassify *fpc) {
  int fpnan = fpc->args[0];
  int fpinf = fpc->args[1];
  int fpnorm = fpc->args[2];
  int fpsubnorm = fpc->args[3];
  int fpzero = fpc->args[4];
  gen_expr(fpc->node);
  switch (fpc->node->ty->kind) {
    case TY_FLOAT:
      println(FPCLASSIFY_FLOAT, fpnan, fpzero, fpsubnorm, fpinf, fpnorm);
      break;
    case TY_DOUBLE:
      println(FPCLASSIFY_DOUBLE, fpnan, fpzero, fpsubnorm, fpinf, fpnorm);
      break;
    case TY_LDOUBLE:
      println(FPCLASSIFY_LDOUBLE, fpnan, fpinf, fpnorm, fpzero, fpsubnorm);
      break;
    default:
      unreachable();
  }
}
