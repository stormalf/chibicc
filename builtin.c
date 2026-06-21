#include "chibicc.h"

void gen_builtin_alloca(Node *node)
{
  int align = node->val > 16 ? node->val : 16;
  Obj *fn = get_current_fn();

  if (!fn->alloca_bottom) {
    println("  mov %%rsp, %%rax");
    println("  sub %%rdi, %%rax");
    println("  and $-%d, %%rax", align);
    println("  mov %%rax, %%rsp");
    return;
  }

  int off = fn->alloca_bottom->offset;
  const char *ptr = fn->alloca_bottom->ptr;
  if (is_omit_fp(fn)) {
    off += fn->stack_size;
    ptr = "%rsp";
  }

  println("  mov %d(%s), %%rax", off, ptr);
  println("  mov %%rax, %%rcx");
  println("  sub %%rsp, %%rcx");
  println("  mov %%rax, %%rdx");
  println("  sub %%rdi, %%rdx");
  println("  and $-%d, %%rdx", align);
  println("  mov %%rax, %%rsi");
  println("  sub %%rdx, %%rsi");

  println("  mov %%rsp, %%r8");
  println("  sub %%rsi, %%rsp");
  println("  mov %%rsp, %%r9");

  println("1:");
  println("  cmp $0, %%rcx");
  println("  je 2f");
  println("  mov (%%r8), %%r11b");
  println("  mov %%r11b, (%%r9)");
  println("  inc %%r8");
  println("  inc %%r9");
  println("  dec %%rcx");
  println("  jmp 1b");
  println("2:");

  println("  mov %%rdx, %d(%s)", off, ptr);
  println("  mov %%rdx, %%rax");
}

void gen_memset(Node *node) {
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
    println("  mov %%rdi, %%r9");
    println("  mov %%sil, %%al");
    println("  cld");
    println("  rep stosb");
    println("  mov %%r9, %%rax");
  }
}

void gen_memcpy(Node *node) {
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

void gen_builtin_single(Node *node, const char *insn, const char *reg) {
    gen_expr(node->builtin_val);
    println("  %s %%%s, %%%s", insn, reg, reg);
}

void gen_builtin_stdc_bit_ceil(Node *node)  {
  int c = count();
  gen_expr(node->lhs);
  int sz = node->lhs->ty->size;

  if (sz == 8) {
    println("  cmp $1, %%rax");
    println("  ja .Lceil_greater_%d", c);
    println("  mov $1, %%rax");
    println("  jmp .Lceil_done_%d", c);
    println(".Lceil_greater_%d:", c);
    println("  dec %%rax");
    println("  bsr %%rax, %%rax");
    println("  add $1, %%rax");
    println("  mov %%rax, %%rcx");
    println("  mov $1, %%rax");
    println("  shl %%cl, %%rax");
    println(".Lceil_done_%d:", c);
  } else {
    println("  cmp $1, %%eax");
    println("  ja .Lceil_greater_%d", c);
    println("  mov $1, %%eax");
    println("  jmp .Lceil_done_%d", c);
    println(".Lceil_greater_%d:", c);
    println("  dec %%eax");
    println("  bsr %%eax, %%eax");
    println("  add $1, %%eax");
    println("  mov %%eax, %%ecx");
    println("  mov $1, %%eax");
    println("  shl %%cl, %%eax");
    println(".Lceil_done_%d:", c);
  }
}

void gen_add_overflow(Node *node) {
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
  } else if (ty->size == 16) {
      println("  add %%rcx, %%rax");
      println("  adc %%rsi, %%rdi");
      println("  mov %%rax, (%%rdx)");
      println("  mov %%rdi, 8(%%rdx)");
  }

  if (ty->is_unsigned)
    println("  setc %%al");
  else
    println("  seto %%al");
  println("  movzx %%al, %%eax");

  println("  cmp $0, %%eax");
  println("  jne .Loverflowa%d", c);
  println("  mov $0, %%eax");
  println("  jmp .Lenda%d", c);
  println(".Loverflowa%d:", c);
  println("  mov $1, %%eax");
  println(".Lenda%d:", c);
}

void gen_sub_overflow(Node *node) {
    int c = count();
    Type *ty = node->builtin_dest->ty;
    if (ty->base)
      ty = ty->base;

    gen_expr(node->lhs);
    if (ty->size == 16)
      pushx_tmp();
    else
      push_tmp();
    gen_expr(node->rhs);
    if (ty->size == 16)
      pushx_tmp();
    else
      push_tmp();
    gen_expr(node->builtin_dest);
    push_tmp();

    pop_tmp("%rdx");
    if (ty->size == 16)
      popx_tmp("%rcx", "%rsi");
    else
      pop_tmp("%rsi");
    if (ty->size == 16)
      popx_tmp("%rax", "%rdi");
    else
      pop_tmp("%rdi");

    if (ty->size == 1) {
        if (node->lhs->ty->is_unsigned) {
          println("  movzbl %%dil, %%eax");
        } else {
          println("  movsbl %%dil, %%eax");
        }
        println("  movslq %%eax, %%rax");

        if (node->rhs->ty->is_unsigned) {
          println("  movzbl %%sil, %%ecx");
        } else {
          println("  movsbl %%sil, %%ecx");
        }
        println("  movslq %%ecx, %%rcx");

        println("  sub %%rcx, %%rax");
        println("  mov %%al, (%%rdx)");

        if (ty->is_unsigned) {
          println("  cmp $0, %%rax");
          println("  jl .Loverflows%d", c);
          println("  cmp $255, %%rax");
          println("  jg .Loverflows%d", c);
        } else {
          println("  cmp $-128, %%rax");
          println("  jl .Loverflows%d", c);
          println("  cmp $127, %%rax");
          println("  jg .Loverflows%d", c);
        }
        println("  mov $0, %%eax");
        println("  jmp .Lends%d", c);
        println(".Loverflows%d:", c);
        println("  mov $1, %%eax");
        println(".Lends%d:", c);
        return;
    } else if (ty->size == 2) {
        if (node->lhs->ty->is_unsigned) {
          println("  movzwl %%di, %%eax");
        } else {
          println("  movswl %%di, %%eax");
        }
        println("  movslq %%eax, %%rax");

        if (node->rhs->ty->is_unsigned) {
          println("  movzwl %%si, %%ecx");
        } else {
          println("  movswl %%si, %%ecx");
        }
        println("  movslq %%ecx, %%rcx");

        println("  sub %%rcx, %%rax");
        println("  mov %%ax, (%%rdx)");

        if (ty->is_unsigned) {
          println("  cmp $0, %%rax");
          println("  jl .Loverflows%d", c);
          println("  cmp $65535, %%rax");
          println("  jg .Loverflows%d", c);
        } else {
          println("  cmp $-32768, %%rax");
          println("  jl .Loverflows%d", c);
          println("  cmp $32767, %%rax");
          println("  jg .Loverflows%d", c);
        }
        println("  mov $0, %%eax");
        println("  jmp .Lends%d", c);
        println(".Loverflows%d:", c);
        println("  mov $1, %%eax");
        println(".Lends%d:", c);
        return;
    } else if (ty->size == 4) {
        println("  mov %%edi, %%eax");
        if (!node->lhs->ty->is_unsigned)
          println("  movslq %%eax, %%rax");

        println("  mov %%esi, %%ecx");
        if (!node->rhs->ty->is_unsigned)
          println("  movslq %%ecx, %%rcx");

        println("  sub %%rcx, %%rax");
        println("  mov %%eax, (%%rdx)");

        if (ty->is_unsigned) {
          println("  cmp $0, %%rax");
          println("  jl .Loverflows%d", c);
          println("  mov $4294967295, %%rcx");
          println("  cmp %%rcx, %%rax");
          println("  jg .Loverflows%d", c);
        } else {
          println("  mov $-2147483648, %%rcx");
          println("  cmp %%rcx, %%rax");
          println("  jl .Loverflows%d", c);
          println("  mov $2147483647, %%rcx");
          println("  cmp %%rcx, %%rax");
          println("  jg .Loverflows%d", c);
        }
        println("  mov $0, %%eax");
        println("  jmp .Lends%d", c);
        println(".Loverflows%d:", c);
        println("  mov $1, %%eax");
        println(".Lends%d:", c);
        return;
    } else if (ty->size == 8) {
        println("  mov %%rdi, %%rax");
        if (node->lhs->ty->is_unsigned) {
          println("  xor %%rcx, %%rcx");
        } else {
          println("  mov %%rdi, %%rcx");
          println("  sar $63, %%rcx");
        }

        println("  mov %%rsi, %%rbx");
        if (node->rhs->ty->is_unsigned) {
          println("  xor %%r8, %%r8");
        } else {
          println("  mov %%rsi, %%r8");
          println("  sar $63, %%r8");
        }

        println("  sub %%rbx, %%rax");
        println("  sbb %%r8, %%rcx");

        println("  mov %%rax, (%%rdx)");

        if (ty->is_unsigned) {
          println("  test %%rcx, %%rcx");
          println("  sete %%al");
          println("  xor $1, %%al");
          println("  movzx %%al, %%eax");
        } else {
          println("  mov %%rax, %%r8");
          println("  sar $63, %%r8");
          println("  cmp %%r8, %%rcx");
          println("  sete %%al");
          println("  xor $1, %%al");
          println("  movzx %%al, %%eax");
        }

        return;
    } else if (ty->size == 16) {
        println("  sub %%rcx, %%rax");
        println("  sbb %%rsi, %%rdi");
        println("  mov %%rax, (%%rdx)");
        println("  mov %%rdi, 8(%%rdx)");
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

void gen_mul_overflow(Node *node) {
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
  pop_tmp("%rcx");
  pop_tmp("%rsi");
  pop_tmp("%rdi");
  if (size == 1) {
    println("  mov %%dil, %%al");
    if (ty->is_unsigned)
      println("  mul %%sil");
    else
      println("  imul %%sil");
    println("  jo .L.overflowm%d", c);
    println("  mov %%al, (%%rcx)");
    println("  mov $0, %%eax");
    println("  jmp .L.donem%d", c);
  } else if (size == 2) {
    println("  mov %%di, %%ax");
    if (ty->is_unsigned)
      println("  mul %%si");
    else
      println("  imul %%si");
    println("  jo .L.overflowm%d", c);
    println("  mov %%ax, (%%rcx)");
    println("  mov $0, %%eax");
    println("  jmp .L.donem%d", c);
  } else if (size == 4) {
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
  if (size == 1) println("  mov %%al, (%%rcx)");
  else if (size == 2) println("  mov %%ax, (%%rcx)");
  else if (size == 4) println("  mov %%eax, (%%rcx)");
  else if (size == 8) println("  mov %%rax, (%%rcx)");

  println("  mov $1, %%rax");
  println(".L.donem%d:", c);
}

void gen_umul_overflow(Node *node) {
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

    pop_tmp("%rdx");
    pop_tmp("%rsi");
    pop_tmp("%rdi");
    println("  mov %%rdx, %%rcx");

    if (size == 1) {
        println("  movzbl %%di, %%eax");
        println("  movzbl %%si, %%ebx");
        println("  mul %%bl");
        println("  jc .Loverflowm%d", c);
    } else if (size == 2) {
        println("  movzwl %%di, %%eax");
        println("  movzwl %%si, %%ebx");
        println("  mul %%bx");
        println("  jc .Loverflowm%d", c);
    } else if (size == 4) {
        println("  mov %%edi, %%eax");
        println("  mul %%esi");
        println("  jc .Loverflowm%d", c);
    } else if (size >= 8) {
        println("  mov %%rdi, %%rax");
        println("  mul %%rsi");
        println("  test %%rdx, %%rdx");
        println("  jnz .Loverflowm%d", c);
    }

    println("  test %%rcx, %%rcx");
    println("  jz .Ldonem%d", c);
    if (size == 1) println("  mov %%al, (%%rcx)");
    else if (size == 2) println("  mov %%ax, (%%rcx)");
    else if (size == 4) println("  mov %%eax, (%%rcx)");
    else if (size == 8) println("  mov %%rax, (%%rcx)");

    println(".Ldonem%d:", c);
    println("  mov $0, %%rax");
    println("  jmp .Lend%d", c);

    println(".Loverflowm%d:", c);
    println("  test %%rcx, %%rcx");
    println("  jz .Loverflow_end%d", c);
    if (size == 1) println("  movb $0, (%%rcx)");
    else if (size == 2) println("  movw $0, (%%rcx)");
    else if (size == 4) println("  movl $0, (%%rcx)");
    else if (size == 8) println("  movq $0, (%%rcx)");
    println(".Loverflow_end%d:", c);
    println("  mov $1, %%rax");
    println(".Lend%d:", c);
}

void gen_uadd_overflow(Node *node) {
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
  println("  setc %%al");
  println("  movzx %%al, %%eax");

  println("  cmp $0, %%eax");
  println("  jne .Loverflowa%d", c);
  println("  mov $0, %%eax");
  println("  jmp .Lenda%d", c);
  println(".Loverflowa%d:", c);
  println("  mov $1, %%eax");
  println(".Lenda%d:", c);
}

void gen_alloc(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%rax, %%rdi");
  println("  sub %%rdi, %%rsp");
  println("  mov %%rsp, %%rax");
}

void gen_prefetch(Node *node) {
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

void gen_builtin_clz(Node *node) {
    gen_expr(node->builtin_val);
    println("  bsr %%eax, %%eax");
    println("  xor $31, %%eax");
}

void gen_builtin_clzl(Node *node) {
    gen_expr(node->builtin_val);
    println("  bsr %%rax, %%rax");
    println("  xor $63, %%eax");
}

void gen_builtin_bswap16(Node *node) {
    gen_expr(node->builtin_val);
    println("  mov %%ax, %%dx");
    println("  rol $8, %%dx");
    println("  mov %%dx, %%ax");
}

void gen_builtin_bswap32(Node *node) {
    gen_expr(node->builtin_val);
    println("  bswap %%eax");
}

void gen_builtin_bswap64(Node *node) {
    gen_expr(node->builtin_val);
    println("  bswap %%rax");
}

void gen_builtin_frame_address(Node *node) {
    int c = count();

    gen_expr(node->lhs);

    if (is_omit_fp(get_current_fn())) {
        // With -fomit-frame-pointer: level 0 returns %rsp,
        // level > 0 returns NULL (can't walk the chain).
        println("  cmp $0, %%rax");
        println("  jne .Lframe_address_null%d", c);
        println("  mov %%rsp, %%rax");
        println("  jmp .Lframe_address_return%d", c);
        println(".Lframe_address_null%d:", c);
        println("  mov $0, %%rax");
        println(".Lframe_address_return%d:", c);
        return;
    }

    println("  mov $64, %%rdi");
    println("  cmp %%rax, %%rdi");
    println("  ja .Lframe_address_ok%d", c);
    println("  jmp .Lframe_address_null%d", c);

    println(".Lframe_address_ok%d:", c);

    println("  cmp $0, %%rax");
    println("  je .Lframe_address_%d", c);
    println("  mov %%rbp, %%rcx");

    println(".Lframe_address_loop%d:", c);
    println("  test %%rax, %%rax");
    println("  jz .Lframe_address_done%d", c);
    println("  test %%rcx, %%rcx");
    println("  jz .Lframe_address_null%d", c);
    println("  mov (%%rcx), %%rcx");
    println("  sub $1, %%rax");
    println("  jmp .Lframe_address_loop%d", c);

    println(".Lframe_address_done%d:", c);
    println("  mov %%rcx, %%rax");
    println("  jmp .Lframe_address_return%d", c);

    println(".Lframe_address_%d:", c);
    println("  mov %%rbp, %%rax");
    println("  jmp .Lframe_address_return%d", c);

    println(".Lframe_address_null%d:", c);
    println("  mov $0, %%rax");

    println(".Lframe_address_return%d:", c);
}

void gen_builtin_expect(Node *node) {
    gen_expr(node->lhs);
    push_tmp();
    gen_expr(node->rhs);
    pop_tmp("%rdi");
    println("  cmp %%rax, %%rdi");
    println("  mov %%rdi, %%rax");
}

void gen_builtin_abort(Node *node) {
    (void)node;
    println("  call abort");
}

void gen_builtin_return_address(Node *node) {
    println("  mov %%rbp, %%rax");
    int tmpdepth = eval(node->lhs);

    for (int i = 0; i < tmpdepth; i++) {
      println("  mov (%%rax), %%rax");
    }

    println("  mov 8(%%rax), %%rax");
}

void gen_builtin_isnan(Node *node) {
    gen_expr(node->builtin_val);
    if (node->builtin_val->ty->kind == TY_FLOAT) {
        println("  movss %%xmm0, %%xmm1");
        println("  ucomiss %%xmm1, %%xmm1");
    } else {
        println("  ucomisd %%xmm0, %%xmm0");
    }

    println("  setp %%al");
    println("  movzx %%al, %%eax");
}

void gen_builtin_nanf(Node *node) {
    union {
      float f;
      uint32_t i;
    } u;
    u.f = node->fval;
    println("  mov $%u, %%eax", u.i);
    println("  movd %%eax, %%xmm0");
}

void gen_builtin_nan(Node *node) {
    union {
      double d;
      uint64_t i;
    } u;
    u.d = node->fval;
    println("  movq $%lu, %%rax", u.i);
    println("  movq %%rax, %%xmm0");
}

void gen_builtin_nanl(Node *node) {
    union {
      long double ld;
      uint8_t bytes[10];
    } u;
    u.ld = node->fval;

    for (int i = 0; i < 10; i++)
      println("  movb $%d, -%d(%%rsp)", u.bytes[i], 10 - i);

    println("  fldt -10(%%rsp)");
}

// ============================================================
// Phase 1: Misc instruction emitters, Atomic ops, CRC32
// (no static helper dependencies)
// ============================================================

void gen_tzcnt_u16(Node *node) {
  gen_expr(node->lhs);
  println("  testw %%ax, %%ax");
  println("  jne 1f");
  println("  movl $16, %%eax");
  println("  jmp 2f");
  println("1:");
  println("  bsfw %%ax, %%ax");
  println("2:");
}

void gen_bextr_u32(Node *node) {
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

void gen_binop1(Node *node, const char *insn) {
  println("  %s %%rax", insn);
}

void gen_binop2(Node *node, const char *insn) {
  println("  %s %s", insn, reg_ax(node->ty->size));
}

void gen_nothing(Node *node) {
  println("  mov $0, %%rax");
}

void gen_singleop(Node *node, const char *insn) {
  println("  %s", insn);
}

void gen_fetchadd(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r11, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");
    return;
  }
  pop_tmp("%rdi");
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
}

void gen_add_fetch(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r11, %%rcx");

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

void gen_sub_fetch(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r11, %%rcx");

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

void gen_fetchsub(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r11, %%rcx");

    println("  lock cmpxchg16b (%%rdi)");
    println("  jnz 1b");
    return;
  }
  pop_tmp("%rdi");
  println("  neg %s", reg_ax(node->ty->size));
  println("  lock xadd %s, (%%rdi)", reg_ax(node->ty->size));
}

void gen_crc32qi(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32b %%al, %%ecx");
  println("  movl %%ecx, %%eax");
}

void gen_crc32di(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32q %%rax, %%rcx");
  println("  movl %%ecx, %%eax");
}

void gen_crc32hi(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32w %%ax, %%ecx");
  println("  movl %%ecx, %%eax");
}

void gen_crc32si(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rcx");
  println("  crc32l %%eax, %%ecx");
  println("  movl %%ecx, %%eax");
}

// ============================================================
// Phase 2: Platform Intrinsics (Group A) and CAS/Atomic (Group H)
// Dependencies: gen_addr, load (now non-static)
// ============================================================

void gen_release(Node *node) {
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

void gen_rdtsc(Node *node) {
  println("  rdtsc");
  println("  shl $32, %%rdx");
  println("  or %%rdx, %%rax");
}

void gen_rdpkru(Node *node) {
  println("  movl $0, %%eax");
  println("  movl %%eax, %%ecx");
  println("  rdpkru");
}

void gen_bsrsi(Node *node) {
  gen_expr(node->lhs);
  println("  bsrl %%eax, %%eax");
}

void gen_bsrdi(Node *node) {
  gen_expr(node->lhs);
  println("  bsrq %%rax, %%rax");
}

void gen_rdpmc(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%eax, %%ecx"); 
  println("  rdpmc");
}

void gen_rdtscp(Node *node) {
  gen_expr(node->lhs);
  println("  movq %%rax, %%rdi");
  println("  rdtscp");        
  println("  movl %%ecx, (%%rdi)"); 
  println("  movl %%edx, %%edx");  
  println("  salq $32, %%rdx");      
  println("  or %%rdx, %%rax");     
}

void gen_rolqi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%al, %%bl"); 
  gen_expr(node->rhs); 
  println("  mov %%al, %%cl");  
  println("  rolb %%cl, %%bl"); 
  println("  movzb %%bl, %%rax"); 
}

void gen_rorqi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%al, %%bl"); 
  gen_expr(node->rhs); 
  println("  mov %%al, %%cl");  
  println("  rorb %%cl, %%bl"); 
  println("  movzb %%bl, %%rax"); 
}

void gen_rolhi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%ax, %%bx");  
  gen_expr(node->rhs);  
  println("  mov %%al, %%cl"); 
  println("  rolw %%cl, %%bx");
  println("  movzx %%bx, %%rax");  
}

void gen_rorhi(Node *node) {
  gen_expr(node->lhs);
  println("  mov %%ax, %%bx");  
  gen_expr(node->rhs);  
  println("  mov %%al, %%cl"); 
  println("  rorw %%cl, %%bx");
  println("  movzx %%bx, %%rax");  
}

void gen_readeflags_u64(Node *node) {
  println("  pushfq");
  println("  popq %%rax");
}

void gen_writeeflags_u64(Node *node) {
  gen_expr(node->lhs);
  println("  pushq $%ld", (int64_t)node->lhs->val);
  println("  popfq");
}

void gen_incsspq(Node *node) {
  gen_expr(node->lhs);
  println("  incsspq %%rax");
}

void gen_rstorssp(Node *node) {
  gen_addr(node->lhs);
  println("  rstorssp (%%rax)");
}

void gen_wrssd(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrssd %%eax, (%%rdx)");
}

void gen_wrssq(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrssq %%rax, (%%rdx)");
}

void gen_wrussd(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrussd %%eax, (%%rdx)");
}

void gen_wrussq(Node *node) {
  gen_expr(node->rhs);
  println("  movq %%rax, %%rdx");
  gen_expr(node->lhs);
  println("  wrussq %%rax, (%%rdx)");
}

void gen_clrssbsy(Node *node) {
  gen_expr(node->lhs);
  if (node->lhs->kind == ND_NUM)
    println("  clrssbsy %ld", (int64_t)node->lhs->val);
  else
    println("  clrssbsy (%%rax)");
}

void gen_sbb_u32(Node *node) { 
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

void gen_sbb_u64(Node *node) { 
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

void gen_addcarryx_u32(Node *node) { 
  gen_expr(node->builtin_args[0]);
  println("  movb %%al, %%dil");
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, %%esi");    
  gen_expr(node->builtin_args[2]);
  println("  movl %%eax, %%edx");    
  gen_expr(node->builtin_args[3]);
  println("  movq %%rax, %%rcx");    
  println("  movl %%esi, %%eax");
  println("  movzx %%dil, %%r9d ");
  println("  addl %%edx, %%eax");
  println("  addl %%r9d, %%eax");
  println("  setc %%al");
  println("  movl %%eax, (%%rcx)");
}

void gen_addcarryx_u64(Node *node) { 
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

// CAS/Atomic functions (Group H)

void gen_cas(Node *node)   {
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
    println("  mov %%rax, %%r9");
    println("  mov (%%r9), %%rax");
    println("  mov 8(%%r9), %%rdx");
    
    popx_tmp("%rbx", "%rcx"); // new -> rcx:rbx
    pop_tmp("%rdi"); // addr

    println("  lock cmpxchg16b (%%rdi)");
    println("  sete %%cl");
    println("  je 1f");
    println("  mov %%rax, (%%r9)");
    println("  mov %%rdx, 8(%%r9)");
    println("1:");
    println("  movzbl %%cl, %%eax");
    return;
  }

  gen_expr(node->cas_addr);
  push_tmp();
  gen_expr(node->cas_new);
  push_tmp();
  gen_expr(node->cas_old);
  println("  mov %%rax, %%r9");
  if (!node->cas_old->ty->base)
    error("%s:%d: in %s :node->cas_old base type is null!", __FILE__, __LINE__, __func__); 
  load(node->cas_old->ty->base);
  pop_tmp("%rdx"); // new
  pop_tmp("%rdi"); // addr
  if (!node->cas_addr->ty->base)
    error("%s:%d: in %s : node->cas_addr base type is null!", __FILE__, __LINE__, __func__); 
  int sz = node->cas_addr->ty->base->size;
  println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz));
  println("  sete %%cl");
  println("  je 1f");
  println("  mov %s, (%%r9)", reg_ax(sz));
  println("1:");
  println("  movzbl %%cl, %%eax");
  return;
  }

void gen_bool_cas(Node *node) {
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
    error("%s:%d: in %s : node->cas_ptr base type is null!", __FILE__, __LINE__, __func__);   
  println("  lock cmpxchg %s, (%%rdi)", reg_dx(sz)); 
  println("  sete %%al");       
  println("  movzbl %%al, %%eax"); 
}

void gen_add_and_fetch(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->lhs->ty->base->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  add %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  adc %%r11, %%rcx");

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

void gen_sub_and_fetch(Node *node) {
  gen_expr(node->lhs);    
  push_tmp();
  gen_expr(node->rhs);    
  if (node->ty->size == 16) {
    println("  mov %%rax, %%r9"); // val low
    println("  mov %%rdx, %%r11"); // val high
    pop_tmp("%rdi"); // addr

    println("  mov (%%rdi), %%rax"); // old low
    println("  mov 8(%%rdi), %%rdx"); // old high

    println("1:");
    println("  mov %%rax, %%rbx");
    println("  sub %%r9, %%rbx");
    println("  mov %%rdx, %%rcx");
    println("  sbb %%r11, %%rcx");

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

void gen_fetchnand(Node *node) {
    gen_expr(node->lhs);  
    push_tmp();
    gen_expr(node->rhs);  
    
    if (node->lhs->ty->base->size == 16) {
        println("  mov %%rax, %%r9"); // val low
        println("  mov %%rdx, %%r11"); // val high
        pop_tmp("%rdi"); // addr

        println("  mov (%%rdi), %%rax"); // old low
        println("  mov 8(%%rdi), %%rdx"); // old high

        println("1:");
        println("  mov %%rax, %%rbx");
        println("  mov %%rdx, %%rcx");
        
        println("  and %%r9, %%rbx");
        println("  and %%r11, %%rcx");
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
        default: error("%s:%d: in %s : unsupported size %d!", __FILE__, __LINE__, __func__, sz); 
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

void gen_cas_n(Node *node)   {  
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
    error("%s:%d: in %s : node->cas_addr base type is null!", __FILE__, __LINE__, __func__);   

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

void gen_single_binop(const char *insn) {
  println("  %s", insn);
}

void gen_cvt_binop(Node *node, const char *insn) {
  gen_addr(node->lhs);    
  if (node->lhs->kind == ND_VAR || node->lhs->kind == ND_MEMBER) {
      println("  %s (%%rax), %%rax", insn);   
  } else {
      println("  %s %%xmm0, %%rax", insn);   
  }
}

void gen_atomic_is_lock_free(Node *node) {
  gen_expr(node->lhs);
  int label = count();
  println("  cmp $0, %%rax");
  println("  jle .L.not_lock_free.%d", label);
  println("  cmp $8, %%rax");
  println("  jle .L.lock_free.%d", label);
  println(".L.not_lock_free.%d:", label);
  println("  mov $0, %%rax");
  println("  jmp .L.lock_free_done.%d", label);
  println(".L.lock_free.%d:", label);
  println("  mov $1, %%rax");
  println(".L.lock_free_done.%d:", label);
}

// ============================================================
// Phase 3: SSE store/load/move (Group D) and SSE binop helpers (Group F)
// Dependencies: push_xmm, pop_xmm (now non-static)
// ============================================================

void gen_store_binop(Node *node, const char *insn) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(0);
  println("  %s %%xmm0, (%%rax)", insn); 
}

void gen_loadlps(Node *node) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(0);
  println("  movlps (%%rax), %%xmm0");
}

void gen_stmxcsr(Node *node) {
  if (node->lhs) {
    gen_expr(node->lhs); 
    println("  stmxcsr (%%rax)"); 
  } else {
    println("  stmxcsr -8(%%rsp)");  
    println("  mov -8(%%rsp), %%eax");
  }
} 

void gen_single_addr_binop(Node *node, const char *insn){
  gen_addr(node->lhs);    
  println("  %s (%%rax)", insn);
}

void gen_parity(Node *node) {
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

void gen_mwait(Node *node) {
  gen_expr(node->builtin_args[0]); 
  push_tmp();
  gen_expr(node->builtin_args[1]); 
  push_tmp();
  pop_tmp("%rcx");
  pop_tmp("%rax");
  println("mwait");
}

void gen_monitor(Node *node) {
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

void gen_movq128(Node *node) {
  gen_expr(node->lhs); 
  println("  movq %%xmm0, %%xmm1");  
  println("  pxor %%xmm0, %%xmm0");  
  println("  movq %%xmm1, %%xmm0");  
}

void gen_movnti(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->rhs->kind == ND_NUM)
    println("  mov $%ld, %%ecx", (int64_t)node->rhs->val);
  else 
    println("  movq (%%rax), %%rcx");
  pop_tmp("%rax");
  println("  movnti %%ecx, (%%rax)"); 
}

void gen_movnti64(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  if (node->rhs->kind == ND_NUM)
    println("  mov $%ld, %%rcx", (int64_t)node->rhs->val);
  else 
    println("  movq (%%rax), %%rcx");
  pop_tmp("%rax");
  println("  movnti %%rcx, (%%rax)"); 
}

void gen_movnt_binop(Node *node, const char *insn) {
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

void gen_movntdqa(Node *node) {
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

// SSE binop helpers (Group F)

void gen_sse_binop1(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->rhs);
  println("  movss %%xmm0, %%xmm1"); 
  gen_expr(node->lhs);
  println("  %s %%xmm1, %%xmm0", insn);
}

void gen_sse_binop2(Node *node, const char *insn, const char *reg, bool rhs_is_imm) {
  gen_expr(node->lhs);
  println("  %s %%xmm0, %%%s", insn, reg);  
}

void gen_sse_binop3(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn);
}

void gen_sse_binop4(Node *node, const char *insn, const char *insn2) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm0, %%xmm1", insn); 
  println("  %s %%al", insn2);
  println("  movzx %%al, %%eax");
}

void gen_sse_binop5(Node *node, const char *insn, const char *insn2) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn); 
  println("  %s %%al", insn2);
  println("  movzx %%al, %%eax");
}

void gen_sse_binop6(Node *node, const char *insn, const char *insn2) {
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

void gen_sse_binop7(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  println("  %s %%xmm0, %%xmm1", insn);  
  println("  movdqu %%xmm1, %%xmm0");  
}

void gen_sse_binop8(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs);
  println("  movq (%%rax), %%xmm0");
  println("  %s %%xmm0, %%%s", insn, reg);  
}

void gen_sse_binop9(Node *node, const char *insn) {
  gen_expr(node->lhs);  
  push_xmm(0);
  gen_expr(node->rhs); 
  pop_xmm(1);
  println("  %s %%xmm1, %%xmm0", insn);
}

void gen_sse_binop10(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs); 
  println("  movq %%rax, %%rdi");    
  gen_expr(node->rhs);  
  println("  %s %%%s, (%%rdi)", insn, reg);    
}

void gen_sse_binop11(Node *node, const char *insn, const char *reg) {
  gen_expr(node->lhs); 
  println("  movq %%rax, %%rdi");    
  gen_expr(node->rhs);  
  println("  %s %%%s, %%xmm0", insn, reg);  
}

void gen_sse_binop12(Node *node, const char *insn) {
  gen_expr(node->lhs); 
  println("  movaps %%xmm0, %%xmm1");   
  println("  %s  %%xmm0, %%xmm1", insn);  
}

void gen_lddqu(Node *node) {
    gen_addr(node->lhs);       
    println("  lddqu (%%rax), %%xmm0");
}

// ============================================================
// Phase 4a: Vector/Shuffle/Init (Group I)
// ============================================================

void gen_signbit(Node *node) {  
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
    println("  sub $16, %%rsp");
    println("  fstpt (%%rsp)");
    println("  movb 9(%%rsp), %%al");
    println("  shr $7, %%al");
    println("  movzbl %%al, %%eax");
    println("  add $16, %%rsp");
    return;
  default:
    unreachable();
  }
}

void gen_isunordered(Node *node) {
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

void gen_vec_init_v2si(Node *node) {
  gen_expr(node->lhs);
  push_tmp();
  gen_expr(node->rhs);
  pop_tmp("%rdx");
  println("  shl $32, %%rax");    
  println("  or %%rdx, %%rax");  
  println("  movq %%rax, %%xmm0");
}

void gen_vec_ext(Node *node) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  println("  movslq %%eax, %%rcx");
  if (node->kind == ND_VECEXTV16QI) {
    println("  and $15, %%ecx");
    println("  movzbl (%%rsp,%%rcx), %%eax");
  } else if (node->kind == ND_VECEXTV8HI) {
    println("  and $7, %%ecx");
    println("  movswl (%%rsp,%%rcx,2), %%eax");
  } else if (node->kind == ND_VECEXTV4HI) {
    println("  and $3, %%ecx");
    println("  movswl (%%rsp,%%rcx,2), %%eax");
  } else if (node->kind == ND_VECEXTV2DI) {
    println("  and $1, %%ecx");
    println("  movq (%%rsp,%%rcx,8), %%rax");
  } else {
    println("  and $%d, %%ecx", node->kind == ND_VECEXTV2SI ? 1 : 3);
    println("  movl (%%rsp,%%rcx,4), %%eax");
  }
  pop_xmm(0);
}

void gen_vec_set_v4hi(Node *node) {
  gen_expr(node->builtin_args[0]);
  push_xmm(0);
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, 8(%%rsp)");
  gen_expr(node->builtin_args[2]);
  println("  and $3, %%eax");
  println("  movzwl 8(%%rsp), %%ecx");
  println("  movw %%cx, (%%rsp,%%rax,2)");
  println("  movq (%%rsp), %%mm0");
  pop_xmm(0);
}

void gen_vec_set_v8hi(Node *node) {
  gen_expr(node->builtin_args[0]);
  push_xmm(0);
  println("  sub $16, %%rsp");
  depth += 2;
  gen_expr(node->builtin_args[1]);
  println("  movl %%eax, (%%rsp)");
  gen_expr(node->builtin_args[2]);
  println("  and $7, %%eax");
  println("  movzwl (%%rsp), %%ecx");
  println("  movw %%cx, 16(%%rsp,%%rax,2)");
  println("  movdqu 16(%%rsp), %%xmm0");
  println("  add $16, %%rsp");
  depth -= 2;
  pop_xmm(0);
}

void gen_psubusb256(Node *node) {
  gen_expr(node->rhs); // B
  push_ymm(0);
  gen_expr(node->lhs); // A
  pop_ymm(1);
  println("  vpsubusb %%ymm1, %%ymm0, %%ymm0");
}

void gen_vec_init_binop(Node *node, const char *insn) {
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

void gen_pshufd(Node *node) {
  gen_expr(node->lhs);
  int imm = node->rhs->val;
  println("  pshufd $%d, %%xmm0, %%xmm0", imm);
}

void gen_pshufw(Node *node) {
  gen_expr(node->lhs);
  println("  movq (%%rax), %%mm0");
  int imm = node->rhs->val;
  println("  pshufw $%d, %%mm0, %%mm0", imm);
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
}

void gen_shuf_binop(Node *node, const char *insn) {
  gen_expr(node->rhs);
  push_xmm(0);
  gen_expr(node->lhs);
  pop_xmm(1);
  println("  %s $%ld, %%xmm1, %%xmm0", insn, (int64_t)node->rhs->val);
}

void gen_psll_binop(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(1);
  if (node->rhs->kind == ND_NUM)
    println("  %s $%ld, %%xmm1", insn, (int64_t)node->rhs->val);
  else {
    println("  movq %%rax, %%xmm0");
    println("  %s %%xmm0, %%xmm1", insn);
  }
  println("  movaps %%xmm1, %%xmm0");      
}

static int get_const_int_from_node(Node *node) {
  if (!node)
    error("%s:%d: error: in %s : expected constant node", __FILE__, __LINE__, __func__);
  while (true) {
    if (node->kind == ND_NUM) return node->val;
    if (node->kind == ND_CAST) { node = node->lhs; continue; }
    if (node->kind == ND_COMMA) { node = node->rhs; continue; }
    if (node->kind == ND_ASSIGN) { node = node->rhs; continue; }
    break;
  }

  error_tok(node->tok, "%s:%d: error: in %s : not a compile-time integer constant", __FILE__, __LINE__, __func__);
 
}

static Node *unwrap_casts(Node *node) {
  while (node && (node->kind == ND_CAST || node->kind == ND_COMMA))
    node = node->lhs;
  return node;
}

static void get_mask_values(Node *mask_node, int *vals, int expected_len) {
  mask_node = unwrap_casts(mask_node);
  if (!mask_node->var || !mask_node->var->init)
    error_tok(mask_node->tok, "%s:%d: error: in %s : shuffle mask must be a constant vector initializer! %d", __FILE__, __LINE__, __func__,  mask_node->kind);

  Initializer *init = mask_node->var->init;
  int len = mask_node->var->ty->array_len;

  for (int i = 0; i < len; i++) {
    Initializer *elem = init->children[i];
    vals[i] = get_const_int_from_node(elem->expr);
  }
}

static bool decompose_shuffle_mask_from_vals(int mask[4], int *out_imm1, int *out_imm2) {
  // mask entries must be 0..7
  for (int i = 0; i < 4; i++) if (mask[i] < 0 || mask[i] > 7) return false;

  for (int comb = 0; comb < (1 << 4); comb++) {
    int idx[4];
    int ia[2] = {-1,-1}, ib[2] = {-1,-1};
    bool ok = true;

    for (int j = 0; j < 4; j++) {
      int bit = (comb >> j) & 1;
      if (mask[j] < 4) idx[j] = bit;
      else idx[j] = 2 + bit;

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

    int intermediate[4];
    intermediate[0] = ia[0];
    intermediate[1] = ia[1];
    intermediate[2] = ib[0] + 4;
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

void gen_shuffle(Node *node, const char *insn) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);
  println("  movaps %%xmm0, %%xmm2");
  gen_expr(node->builtin_args[1]);
  println("  movaps %%xmm0, %%xmm1");
  println("  movaps %%xmm2, %%xmm0");
  int mask[4];
  get_mask_values(node->builtin_args[2], mask, 4);
  int imm1, imm2;
  if (decompose_shuffle_mask_from_vals(mask, &imm1, &imm2)) {
    println("  %s $%d, %%xmm1, %%xmm0", insn, imm1);
    println("  %s $%d, %%xmm0, %%xmm0", insn, imm2);
  } else {
    int single = ((mask[3] & 3) << 6) | ((mask[2] & 3) << 4) | ((mask[1] & 3) << 2) | (mask[0] & 3);
    println("  %s $%d, %%xmm1, %%xmm0", insn, single);
  }
}

void gen_maskmovq(Node *node) {
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

void gen_maskmovdqu(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); 
  println("  movdqu (%%rax), %%xmm1"); 
  gen_expr(node->builtin_args[0]);  
  println("  movdqu (%%rax), %%xmm0");       
  gen_addr(node->builtin_args[2]); 
  println("  movq %%rax, %%rdi"); 
  println("  maskmovdqu %%xmm1, %%xmm0");
}

void gen_cvtpi2ps(Node *node) {
  gen_expr(node->lhs);    
  gen_addr(node->rhs);    
  println("  movq (%%rax), %%mm0"); 
  println("  cvtpi2ps %%mm0, %%xmm0");  
  println("  emms");
} 

void gen_loadhps(Node *node) {
  gen_expr(node->lhs);
  println("  movups (%%rax), %%xmm0");
  push_xmm(0);
  gen_expr(node->rhs);
  println("  movq (%%rax), %%xmm1");
  pop_xmm(0);
  println("  movlhps %%xmm1, %%xmm0");
}

void gen_packss128_binop(Node *node, const char *insn) {
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs); 
  pop_xmm(1); 
  println("  %s %%xmm0, %%xmm1", insn); 
  println("  movdqu %%xmm1, %%xmm0");
}

// ============================================================
// Phase 4b: AVX2/MMX/Blend/Test (Group G)
// ============================================================

void gen_sse_pblendvb128(Node *node) {
  assert(node->builtin_nargs == 3);  
  gen_expr(node->builtin_args[0]); 
  println("  movaps %%xmm0, %%xmm1"); 
  gen_expr(node->builtin_args[1]);      
  println("  movaps %%xmm0, %%xmm2"); 
  gen_expr(node->builtin_args[2]); 
  println("  pblendvb %%xmm2, %%xmm1"); 
  println("  movaps %%xmm1, %%xmm0");
}

void gen_pblendvb256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[2]); // mask -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[1]); // src2 -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[0]); // src1 -> ymm0
  pop_ymm(2); // src2 -> ymm2
  pop_ymm(1); // mask -> ymm1
  println("  vpblendvb %%ymm1, %%ymm2, %%ymm0, %%ymm0");
}

void gen_sse_blendvpx(Node *node, const char *insn) {
  assert(node->builtin_nargs == 3);  
  gen_expr(node->builtin_args[0]); 
  println("  movups (%%rax), %%xmm1"); 
  gen_expr(node->builtin_args[1]);      
  println("  movups (%%rax), %%xmm2"); 
  gen_expr(node->builtin_args[2]); 
  println("  movups (%%rax), %%xmm0"); 
  println("  %s %%xmm0, %%xmm2, %%xmm1", insn); 
  println("  movaps %%xmm1, %%xmm0");
}

void gen_pcmpgtb256_mask(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[2]);
  push_tmp();

  gen_expr(node->builtin_args[0]);
  push_ymm(0);
  gen_expr(node->builtin_args[1]);
  push_ymm(0);
  pop_ymm(2);
  pop_ymm(1);
  println("  vpcmpgtb %%ymm2, %%ymm1, %%ymm0");
  println("  vpmovmskb %%ymm0, %%eax");
  pop_tmp("%rcx");
  println("  andl %%ecx, %%eax");
  println("  vzeroupper");
}

void gen_pshufb256(Node *node) {
  gen_expr(node->rhs);
  push_ymm(0);
  gen_expr(node->lhs);
  push_ymm(0);
  pop_ymm(0);
  pop_ymm(1);
  println("  vpshufb %%ymm1, %%ymm0, %%ymm0");
}

void gen_avx2_256(Node *node, const char *insn) {  
  gen_expr(node->lhs);
  int64_t imm_bits = eval(node->rhs);
  if (imm_bits < 0 || imm_bits > 255 * 8)
    error_tok(node->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  
  if (imm_bits % 8 != 0)
    error_tok(node->tok, "%s:%d: in %s: immediate must be multiple of 8", __FILE__, __LINE__, __func__);

  int64_t imm_bytes = imm_bits / 8;
  println("  %s $%ld, %%ymm0, %%ymm0", insn, imm_bytes);
}

void gen_sse2_dqshift(Node *node, const char *insn) {
  gen_expr(node->lhs);
  int64_t imm_bits = eval(node->rhs);
  if (imm_bits < 0 || imm_bits > 255 * 8)
    error_tok(node->tok, "%s:%d: in %s: immediate out of range", __FILE__, __LINE__, __func__);
  if (imm_bits % 8 != 0)
    error_tok(node->tok, "%s:%d: in %s: immediate must be multiple of 8", __FILE__, __LINE__, __func__);
  int64_t imm_bytes = imm_bits / 8;
  println("  %s $%ld, %%xmm0", insn, imm_bytes);
}

void gen_vinsertf128_si256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[0]);   // -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[1]);   // -> xmm0
  push_ymm(0);
  pop_ymm(2);
  pop_ymm(1);
  Node *imm = node->builtin_args[2];
  int64_t imm8 = eval(imm);
  if (imm8 < 0 || imm8 > 1)
    error_tok(imm->tok, "%s:%d: error: in %s: imm must be 0 or 1", __FILE__, __LINE__, __func__);
  int val = imm8 & 1;

  println("  vinsertf128 $%d, %%xmm2, %%ymm1, %%ymm0", val);
}

void gen_avx2_permdi256(Node *node) {
  gen_expr(node->lhs);  
  println("  vpermq $%ld, %%ymm0, %%ymm0", (int64_t)eval(node->rhs));
}

void gen_avx2_psll_binop(Node *node, const char *insn) {
  gen_expr(node->lhs); // ymm0 = lhs
  if (node->rhs->kind == ND_NUM) {
    println("  %s $%ld, %%ymm0, %%ymm0", insn, (int64_t)node->rhs->val);
  } else {
    push_vec(node->lhs->ty);
    gen_expr(node->rhs);
    println("  movq %%rax, %%xmm1");
    pop_vec(node->lhs->ty, 0);
    println("  %s %%xmm1, %%ymm0, %%ymm0", insn);
  }
}

void gen_avx2_palignr256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); // B -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[0]); // A -> ymm0
  pop_ymm(1);
  int64_t imm_bytes = eval(node->builtin_args[2]) / 8;
  println("  vpalignr $%ld, %%ymm1, %%ymm0, %%ymm0", imm_bytes);
}

void gen_vperm2i128_si256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); // Y -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[0]); // X -> ymm0
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  println("  vperm2i128 $%ld, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_pblendd256(Node *node) {
  assert(node->builtin_nargs == 3);
  gen_expr(node->builtin_args[1]); // B -> ymm0
  push_ymm(0);
  gen_expr(node->builtin_args[0]); // A -> ymm0
  pop_ymm(1);
  int64_t imm = eval(node->builtin_args[2]);
  println("  vpblendd $%ld, %%ymm1, %%ymm0, %%ymm0", imm);
}

void gen_pmulhuw256(Node *node) {
  gen_expr(node->lhs); // A -> ymm0
  push_ymm(0);
  gen_expr(node->rhs); // B -> ymm0
  pop_ymm(1);
  println("  vpmulhuw %%ymm0, %%ymm1, %%ymm0");
}

void gen_andnotsi256(Node *node) {
  gen_expr(node->lhs); 
  push_ymm(0);
  gen_expr(node->rhs); // B -> ymm0
  pop_ymm(1);
  println("  vpandn %%ymm0, %%ymm1, %%ymm0");
}

void gen_vextractf128_si256(Node *node) {  
  gen_expr(node->lhs); // Source vector -> ymm0
  Node *imm_node = node->rhs;
  int64_t imm = eval(imm_node);
  if (imm < 0 || imm > 1) error_tok(imm_node->tok, "vextractf128 imm must be 0 or 1");
  println("  vextractf128 $%ld, %%ymm0, %%xmm0", imm);
}

void gen_si256 (Node *node) {
  gen_expr(node->lhs);
}

void gen_cvt_mmx_binop(Node *node, const char *insn) {
  gen_addr(node->lhs);   
  println("  movups (%%rax), %%xmm0"); 
  println("  %s %%xmm0, %%mm0", insn);  
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
  }

void gen_cvt_sse_binop2(Node *node, const char *insn, const char *reg, bool is_address) {  
  gen_expr(node->lhs);
  push_xmm(0);
  gen_expr(node->rhs);
  pop_xmm(0);
  if (is_address)
    println("  %s (%%%s), %%xmm0", insn, reg);
  else 
    println("  %s %%%s, %%xmm0", insn, reg);
}

void gen_cvt_mmx_binop3(Node *node, const char *insn) {
  gen_expr(node->lhs);        
  println("  %s %%xmm0, %%mm0", insn);
  gen_addr(node->lhs);         
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0"); 
  println("  emms");
}

void gen_cvt_mmx_binop4(Node *node, const char *insn) {
  gen_expr(node->lhs);    
  println("  movq (%%rax), %%mm0");    
  println("  %s %%mm0, %%xmm0", insn);
  println("  emms");
}

void gen_mmx_binop(Node *node, const char *insn, bool rhs_is_imm) {
  gen_expr(node->lhs);
  println("  movq (%%rax), %%mm0");

  if (rhs_is_imm) {
    if (node->rhs->kind == ND_NUM) {
      println("  %s $%ld, %%mm0", insn, (int64_t)node->rhs->val);
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

void gen_mmx_binop1(Node *node, const char *insn) {
  gen_expr(node->lhs);    
  println("  movq (%%rax), %%mm0");
  println("  %s %%mm0, %%mm0", insn);
  println("  movq %%mm0, %%rax");
  println("  movq %%rax, %%xmm0");
  println("  emms");
}

void gen_sse_testz(Node *node) {
    gen_expr(node->lhs);   // %xmm0 = M
    push_xmm(0);
    gen_expr(node->rhs);   // %xmm0 = V
    pop_xmm(1);
    // ptest performs V & M
    println("  ptest %%xmm0, %%xmm1");  // sets ZF and CF
    println("  setz %%al");             // AL = 1 if ZF=1
    println("  movzx %%al, %%eax");     // zero-extend to EAX
}

void gen_sse_testc(Node *node) {
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

void gen_sse_testnzc(Node *node) {              
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
