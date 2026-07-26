#include "test.h"

int main() {
  ASSERT(3.0, __builtin_ceil(2.3));
  ASSERT(2.0, __builtin_floor(2.7));
  ASSERT(-2.0, __builtin_ceil(-2.7));
  ASSERT(-3.0, __builtin_floor(-2.3));
  printf("OK\n");
  return 0;
}
