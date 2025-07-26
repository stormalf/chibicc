#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

void test(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  // char is promoted to int in variadic arguments
  int c = va_arg(ap, int);

  printf("c = %d\n", c);
  assert(c == 42);

  va_end(ap);
}

int main() {
  char x = 42;
  test("char", x);
  printf("Test passed.\n");
  return 0;
}
