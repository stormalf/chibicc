#include <stdio.h>
#include <stdarg.h>
void test(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int x = va_arg(ap, int);
  printf("x = %d\n", x);
}

int main() {
  test("int", 42);
}
