#include <stdio.h>
#include <stdarg.h>
#include "test.h"

typedef struct {
  char _Alignas(1024) c;
} Aligned1024;

void test_va_args(const char *label, int n, ...) {
  va_list ap;
  va_start(ap, n);

  long double ld = va_arg(ap, long double);
  Aligned1024 *a = va_arg(ap, Aligned1024 *);
  int i = va_arg(ap, int);

  printf("%s:\n", label);
  printf("long double = %Lf\n", ld);
  printf("Aligned1024->c = %d\n", a->c);
  printf("int = %d\n", i);
  ASSERT(77, a->c);

  va_end(ap);
}

int main(void) {
  long double ld = 3.1415926535897932384626L;
  Aligned1024 a = {.c = 77};

  test_va_args("Test2", 3, ld, &a, 123);
  return 0;
}
