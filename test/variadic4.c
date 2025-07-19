#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "test.h"

void test_variadic(int count, ...) {
  va_list ap;
  va_start(ap, count);

  char c   = va_arg(ap, int);               // promoted
  unsigned char uc = va_arg(ap, int);       // promoted
  short s  = va_arg(ap, int);               // promoted
  unsigned short us = va_arg(ap, int);      // promoted
  int i    = va_arg(ap, int);
  unsigned int ui = va_arg(ap, unsigned int);
  long l   = va_arg(ap, long);
  unsigned long ul = va_arg(ap, unsigned long);
  long long ll = va_arg(ap, long long);
  unsigned long long ull = va_arg(ap, unsigned long long);

  float f  = (float)va_arg(ap, double);     // promoted to double
  double d = va_arg(ap, double);

  printf("char: %d\n", c);
  printf("unsigned char: %u\n", uc);
  printf("short: %d\n", s);
  printf("unsigned short: %u\n", us);
  printf("int: %d\n", i);
  printf("unsigned int: %u\n", ui);
  printf("long: %ld\n", l);
  printf("unsigned long: %lu\n", ul);
  printf("long long: %lld\n", ll);
  printf("unsigned long long: %llu\n", ull);
  printf("float: %f\n", f);
  printf("double: %f\n", d);
  ASSERT(-1, c);
  ASSERT(255, uc);
  ASSERT(-12345, s);
  ASSERT(54321, us);
  ASSERT(-123456, i);
  ASSERT(123456u, ui);
  ASSERT(-123456789L, l);
  ASSERT(123456789UL, ul);
  ASSERT(-123456789012345LL, ll);
  ASSERT(123456789012345ULL, ull);
  ASSERT(1.25f, f);
  ASSERT(3.14159, d);

  va_end(ap);
}

int main() {
  test_variadic(12,
    (char)-1, (unsigned char)255,
    (short)-12345, (unsigned short)54321,
    -123456, 123456u,
    -123456789L, 123456789UL,
    -123456789012345LL, 123456789012345ULL,
    1.25f, 3.14159
  );
}
