// Test that GDB can read pointer parameters after a function call
// (when the argument register has been reused).  DW_OP_fbreg is
// required; DW_OP_regN would return the wrong value here.
#include "test.h"
#include <stdio.h>

struct Point { int x, y; };

static int callee(struct Point *p, int flag) {
  // This function call will clobber %rdi and %rsi (the param regs).
  printf("flag=%d\n", flag);
  // If GDB can read *p here, the DWARF location is correct.
  return p->x + p->y;
}

int main() {
  struct Point pt = {3, 4};
  int sum = callee(&pt, 1);
  ASSERT(7, sum);
  return 0;
}
