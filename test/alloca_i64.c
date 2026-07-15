#include "test.h"

// alloca with an int-typed size argument: IR emitter must widen the
// size operand to i64 before using it in "alloca i8, i64 %n, align 16".
// Before the fix, llc rejected this with:
//   '%_N' defined with type 'i32' but expected 'i64'

static int sum_alloca(int n) {
  int *p = alloca(n * sizeof(int));
  for (int i = 0; i < n; i++)
    p[i] = i + 1;
  int s = 0;
  for (int i = 0; i < n; i++)
    s += p[i];
  return s;
}

int main() {
  ASSERT(15, sum_alloca(5));   // 1+2+3+4+5
  ASSERT(1,  sum_alloca(1));
  ASSERT(0,  sum_alloca(0));
  return 0;
}
