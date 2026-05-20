// Test that GDB can read a pointer parameter after its register is clobbered
#include "test.h"
#include <stdio.h>

struct Point { int x, y; };

int callee(struct Point *p, int flag) {
  // The call to printf will clobber %rdi and %rsi (the parameter registers).
  printf("flag=%d\n", flag);
  // If GDB can read p->x and p->y here, DW_OP_fbreg is working correctly.
  return p->x + p->y;
}

int main() {
  struct Point pt = {3, 4};
  ASSERT(7, callee(&pt, 1));
  return 0;
}
