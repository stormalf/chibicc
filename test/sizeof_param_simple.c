#include "test.h"

void fn(int z, int a[z], int b[sizeof(a)]) {
  ASSERT(8, sizeof(a));      // pointer size
  ASSERT(8, sizeof(b));      // pointer size (array decays to pointer in parameter)
  ASSERT(4, sizeof(*a)); 
  ASSERT(4, sizeof(*b)); 
}

int main() {
  fn(5, 0, 0);
  printf("OK\n");
  return 0;
}