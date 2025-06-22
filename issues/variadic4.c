#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

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
