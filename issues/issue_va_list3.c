#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int add_all(int n, ...) {
  va_list ap;
  va_start(ap, n);
  int sum = va_arg(ap, int);
  va_end(ap);
  return sum;
}

int main() {
  int x = add_all(3, 42);
  printf("add_all(3,42) = %d\n", x);
  if (x != 42) {
    fprintf(stderr, "FAIL: expected 42, got %d\n", x);
    return 1;
  }
  printf("OK\n");
  return 0;
}
