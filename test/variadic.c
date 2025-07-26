#include <stddef.h>
#include <stdarg.h>
#include "test.h"
void test(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int x = va_arg(ap, int);
  printf("x = %d\n", x);
  ASSERT(42, x);
}

int main() {
  test("int", 42);
}
