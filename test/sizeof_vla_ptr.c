#include "test.h"

void fn(int z, int (*a)[z]) {
  // a is pointer to VLA of z ints
  // *a is VLA of z ints
  // sizeof(*a) should be z * sizeof(int)
  ASSERT(z*4, sizeof(*a));
}

int main() {
  fn(5, 0);
  printf("OK\n");
  return 0;
}