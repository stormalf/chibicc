#include "test.h"

int main() {
  // Regression: __builtin_mul_overflow() must return 0/1 in %eax,
  // not just in %ax/%al. Otherwise callers can see a non-zero "true"
  // even when no overflow happened (e.g. Postgres int2/int4 paths).
  short a = 1234;
  short b = 2;
  short out = 0;

  int of = __builtin_mul_overflow(a, b, &out);
  ASSERT(0, of);
  ASSERT(2468, out);
  return 0;
}

