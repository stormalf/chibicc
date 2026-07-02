#include "test.h"

int myfunc1(int a, int b, int c) {
  return a + b;
}

int main() {
  int x;
  int y;
  int z;
  int a = 8;
  ASSERT(13, myfunc1(5, 8, 0));
  printf("%d\n", a);
  return 0;
}
