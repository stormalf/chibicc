#include "test.h"

int main() {
  int a = 0x7fffffff;
  int b = 1;
  int res;
  int overflow = __builtin_add_overflow(a, b, &res);
  ASSERT(1, overflow);
  ASSERT(0x80000000, res);

  long long la = 0x7fffffffffffffffLL;
  long long lb = 1;
  long long lres;
  int loverflow = __builtin_add_overflow(la, lb, &lres);
  ASSERT(1, loverflow);
  LASSERT(0x8000000000000000LL, lres);

  int c = 10;
  int d = 20;
  int cd;
  int no_overflow = __builtin_add_overflow(c, d, &cd);
  ASSERT(0, no_overflow);
  ASSERT(30, cd);

  printf("OK\n");
  return 0;
}
