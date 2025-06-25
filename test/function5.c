#include <stdio.h>
#include <stdarg.h>
#include "test.h"

void dummy(long double x1, long double x2, long double x3, long double x4, long double x5,
           long double x6, long double x7, long double x8, long double x9, long double x10,
           long double x11, long double x12, long double x13, long double x14,
           int dummy, ...) {
  va_list ap;
  va_start(ap, dummy);

  long double x = va_arg(ap, long double); // Should now be on stack
  printf("Overflow long double = %Lf\n", x);
  ASSERT( 99.99L, x);

  va_end(ap);
}

int main() {
  // 14 long double args → xmm0-xmm7 are full → remaining will go to overflow (stack)
  dummy(1.1L, 2.2L, 3.3L, 4.4L, 5.5L, 6.6L, 7.7L, 8.8L,
        9.9L, 10.10L, 11.11L, 12.12L, 13.13L, 14.14L,
        42,         // Dummy int to mark end of named args
        99.99L);    // This long double should be read from stack

  return 0;
}
