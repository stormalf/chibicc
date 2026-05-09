#include "test.h"

int main() {
  int x = 0;

  __asm__ volatile(
    "# %rax %rbx %rcx %rdx %rsi %rdi %r8 %r9 %r10 %r11 %r12 %r13 %r14 %r15\n"
    "movl $123, %0\n"
    : "=m"(x)
    :
    : "memory");

  ASSERT(123, x);
  return 0;
}
