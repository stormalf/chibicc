#include "test.h"

#define IS_ATOMIC_INT(v) _Generic(&(v), _Atomic int *: 1, default: 0)

typedef _Atomic int AInt;

int main(void) {
  _Atomic int a = 1, b = 2;
  int c = 3;
  ASSERT(1, IS_ATOMIC_INT(a));
  ASSERT(1, IS_ATOMIC_INT(b));
  ASSERT(0, IS_ATOMIC_INT(c));

  AInt x = 5;
  int y = 6;
  ASSERT(1, IS_ATOMIC_INT(x));
  ASSERT(0, IS_ATOMIC_INT(y));

  // ensure separate declaration after atomic typedef stays non-atomic
  int z = 7;
  ASSERT(0, IS_ATOMIC_INT(z));

  printf("OK\n");
  return 0;
}
