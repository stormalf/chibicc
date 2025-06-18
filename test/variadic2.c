#include <stdarg.h>
#include <stdio.h>

typedef struct {
  char c;
} SmallStruct;

void test(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  SmallStruct s = va_arg(ap, SmallStruct);
  printf("s.c = %d\n", s.c);
}

int main() {
  SmallStruct s = {42};
  test("struct", s);
}
