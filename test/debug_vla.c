#include "test.h"

void fn(int x, int a[x]) {
  int y = sizeof(a);
  ASSERT(8, y);
}

int main() {
  fn(5, 0);
  printf("OK\n");
  return 0;
}
