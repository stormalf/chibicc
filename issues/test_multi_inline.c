#include "test.h"

static int g;

static inline int add(int a, int b) {
  return a + b;
}

int main() {
  int x = 5;
  for (int i = 0; i < 1000; i++) {
    x = add(x, 3);
  }
  ASSERT(3005, x);
  
  x = 0;
  int j = 0;
  while (j < 100) {
    x = add(x, j);
    j++;
  }
  ASSERT(4950, x);
  return 0;
}
