#include "test.h"

#undef __builtin_choose_expr

int main(void) {
  int a[4] = {10, 20, 30, 40};
  int x = 3;
  int y = 5;

  ASSERT(11, __builtin_choose_expr(1, 11, undeclared_symbol + 1));
  ASSERT(7, __builtin_choose_expr(0, undeclared_symbol2 + 1, 7));

  __builtin_choose_expr(1, x, y) = 9;
  ASSERT(9, x);
  ASSERT(5, y);

  int *p = __builtin_assume_aligned(a, 16);
  ASSERT(20, p[1]);

  int *q = __builtin_assume_aligned(a + 1, 16, 0);
  ASSERT(20, *q);

  LASSERT((long long)(a + 1), (long long)__builtin_assume_aligned(a + 1, 16, 0));

  printf("OK\n");
  return 0;
}
