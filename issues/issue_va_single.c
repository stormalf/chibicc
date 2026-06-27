#include "test.h"

int sum3(int a, int b, int c) {
  return a + b + c;
}

typedef struct {
  int gp_offset;
  int fp_offset;
  void *overflow_arg_area;
  void *reg_save_area;
} __va_elem;

typedef __va_elem va_list[1];

int test_simple_va(int n, ...) {
  va_list ap;
  va_start(ap, n);

  int x = va_arg(ap, int);
  return x;
}

int main() {
  ASSERT(1, test_simple_va(0, 1));
  ASSERT(2, test_simple_va(0, 2));
  printf("OK\n");
  return 0;
}
