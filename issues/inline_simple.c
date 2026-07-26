#include "test.h"

static inline int add(int a, int b) { return a + b; }

int main() {
  int x = add(1, 2);
  ASSERT(3, x);
  return 0;
}