#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int add_all(int n, ...) {
  va_list ap;
  va_start(ap, n);
  int sum = 0;
  int i;
  for (i = 0; i < n; i++)
    sum += va_arg(ap, int);
  va_end(ap);
  return sum;
}

int main() {
  int x = add_all(3, 1, 2, 3);
  printf("add_all(3,1,2,3) = %d\n", x);
  if (x != 6) {
    fprintf(stderr, "FAIL: expected 6, got %d\n", x);
    return 1;
  }
  printf("OK\n");
  return 0;
}
