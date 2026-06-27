#include "test.h"

int test_va(int n, ...) {
  va_list ap;
  va_start(ap, n);
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += va_arg(ap, int);
  return sum;
}

int main() {
  ASSERT(6, test_va(3, 1, 2, 3));
  ASSERT(5, test_va(4, 1, 2, 3, -1));
  printf("OK\n");
  return 0;
}
