#include "test.h"

static inline int add(int a, int b) {
  return a + b;
}

int main() {
  ASSERT(7, add(3, 4));
  ASSERT(10, add(2, 8));
  ASSERT(0, add(0, 0));
  return 0;
}
