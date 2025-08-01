#include <stdarg.h>
#include <stddef.h>
#include "test.h"

typedef struct {
  char c;
} SmallStruct;

void test(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  SmallStruct s = va_arg(ap, SmallStruct);
  printf("s.c = %d\n", s.c);
  ASSERT(42, s.c);
}

int main() {
  SmallStruct s = {42};
  test("struct", s);
  ASSERT(42, s.c);
}
