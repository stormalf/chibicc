// Test that GDB can read a pointer parameter after nested function calls
// have clobbered the argument registers (the CPython scenario).
#include "test.h"
#include <stdio.h>

struct Point { int x, y; };

// A helper that accepts many args to clobber all GP registers
__attribute__((noinline))
static int clobber_all(int a, int b, int c, int d, int e, int f, 
                        int g, int h, int i, int j) {
  return a + b + c + d + e + f + g + h + i + j;
}

__attribute__((noinline))
static int use_pointer_after_clobber(struct Point *p, int flag) {
  // Clobber all argument registers with a call
  int sum = clobber_all(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  // After this call, %rdi, %rsi, etc. have all been overwritten.
  // If DWARF uses DW_OP_regN, GDB would read garbage for p and flag here.
  // With DW_OP_fbreg, GDB reads from the stack where chibicc saved them.
  return p->x + p->y + sum;
}

int main() {
  struct Point pt = {3, 4};
  ASSERT(3+4+55, use_pointer_after_clobber(&pt, 1));
  return 0;
}
