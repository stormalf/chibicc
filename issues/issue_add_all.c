#include "test.h"

int main() {
  ASSERT(6, add_all(3, 1, 2, 3));
  ASSERT(5, add_all(4, 1, 2, 3, -1));
  printf("OK\n");
  return 0;
}
