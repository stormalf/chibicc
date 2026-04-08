#include "test.h"

void fn1(int z, int a[z], int b1[sizeof(a)]) {
  ASSERT(8, sizeof(a));
  ASSERT(8, sizeof(b1));
}

void fn2(int z, int (*a)[z], int b1[sizeof(*a)]) {
  ASSERT(28, sizeof(*a));
  ASSERT(8, sizeof(b1));
}

int main() {
  fn1(7, 0, 0);
  fn2(7, 0, 0);
  printf("OK\n");
  return 0;
}