#include <stdio.h>
#include <stdint.h>
_Alignas(32) int x;
long double f(long double x) { return x + 1.0L; }
long double f2(long double *p) { return p[1]; }
typedef __attribute__((aligned(32))) int A;
int main() {
  char __attribute__((aligned(32))) buf[3];
  long double x = 3.0L;
  int __attribute__((aligned(32))) y = 0;
  A z;
  printf("f=%Lf\n", f(x));
  printf("alignof(A)=%zu alignof(z)=%zu\n", _Alignof(A), _Alignof(z));
  printf("buf%%32=%zu y%%32=%zu z%%32=%zu\n", ((uintptr_t)buf)%32, ((uintptr_t)&y)%32, ((uintptr_t)&z)%32);
  return 0;
}
