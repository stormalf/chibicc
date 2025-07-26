#include <stddef.h>
#include <stdarg.h>
#include "test.h"

typedef struct {
  char _Alignas(1024) pad;
} BigAlign;

void test(int count, ...) {
  va_list ap;
  va_start(ap, count);

  for (int i = 0; i < count; i++)
    printf("arg[%d] = %p\n", i, va_arg(ap, void *));

  va_end(ap);
}

int main() {
  BigAlign a, b;
  test(2, &a, &b);  // If va_area isn't big enough or not aligned, crash likely
}
