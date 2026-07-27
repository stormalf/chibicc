#include "test.h"

static inline int add(int a, int b) {
  return a + b;
}

static inline int double_add(int x) {
  return add(x, x);
}

int main() {
  ASSERT(10, double_add(5));
  ASSERT(0, double_add(0));
  ASSERT(4, double_add(2));
  return 0;
}
