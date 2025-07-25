
#include <limits.h>
#include "test.h"



int main() {
  printf("sizeof(char) = %ld\n", sizeof(char));
  ASSERT(1, sizeof(char));
  printf("sizeof(short) = %ld\n", sizeof(short));
  ASSERT(2, sizeof(short));
  printf("sizeof(int) = %ld\n", sizeof(int));
  ASSERT(4, sizeof(int));
  printf("sizeof(long) = %ld\n", sizeof(long));
  ASSERT(8, sizeof(long));
  printf("sizeof(long long) = %ld\n", sizeof(long long));
  ASSERT(8, sizeof(long long));
  printf("sizeof(float) = %ld\n", sizeof(float));
  ASSERT(4, sizeof(float));
  printf("sizeof(double) = %ld\n", sizeof(double));
  ASSERT(8, sizeof(double));
  printf("sizeof(long double) = %ld\n", sizeof(long double));
  ASSERT(16, sizeof(long double));
  printf("sizeof(void *) = %ld\n", sizeof(void *));
  ASSERT(8, sizeof(void *));
  printf("sizeof(char *) = %ld\n", sizeof(char *));
  ASSERT(8, sizeof(char *));
  printf("sizeof(int *) = %ld\n", sizeof(int *));
  ASSERT(8, sizeof(int *));
  printf("sizeof(long *) = %ld\n", sizeof(long *));
  ASSERT(8, sizeof(long *));
  printf("sizeof(float *) = %ld\n", sizeof(long *));
  ASSERT(8, sizeof(long *));
  printf("sizeof(double *) = %ld\n", sizeof(double *));
  ASSERT(8, sizeof(double *));
  printf("sizeof(long double *) = %ld\n", sizeof(long double *));
  ASSERT(8, sizeof(long double *));
  printf("sizeof(char[10]) = %ld\n", sizeof(char[10]));
  ASSERT(10, sizeof(char[10]));
  printf("sizeof(int[10]) = %ld\n", sizeof(int[10]));
  ASSERT(40, sizeof(int[10]));
  printf("sizeof(long[10]) = %ld\n", sizeof(long[10]));
  ASSERT(80, sizeof(long[10]));
  printf("sizeof(float[10]) = %ld\n", sizeof(float[10]));
  ASSERT(40, sizeof(float[10]));
  printf("sizeof(double[10]) = %ld\n", sizeof(double[10]));
  ASSERT(80, sizeof(double[10]));
  printf("sizeof(long double[10]) = %ld\n", sizeof(long double[10]));
  ASSERT(160, sizeof(long double[10]));
  printf("sizeof(struct {int a; int b;}) = %ld\n", sizeof(struct {int a; int b;}));
  ASSERT(8, sizeof(struct {int a; int b;}));
  printf("sizeof(struct {int a; int b; int c;}) = %ld\n", sizeof(struct {int a; int b; int c;}));
  ASSERT(12, sizeof(struct {int a; int b; int c;}));
  printf("sizeof(struct {int a; int b; int c; int d;}) = %ld\n", sizeof(struct {int a; int b; int c; int d;}));
  ASSERT(16, sizeof(struct {int a; int b; int c; int d;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e;}));
  ASSERT(20, sizeof(struct {int a; int b; int c; int d; int e;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e; int f;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e; int f;}));      
  ASSERT(24, sizeof(struct {int a; int b; int c; int d; int e; int f;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e; int f; int g;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e; int f; int g;}));
  ASSERT(28, sizeof(struct {int a; int b; int c; int d; int e; int f; int g;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h;}));
  ASSERT(32, sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i;}));
  ASSERT(36, sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j;}));
  ASSERT(40, sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k;}));
  ASSERT(44, sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k; int l;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k; int l;}));      
  ASSERT(48,  sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k; int l;}));
  printf("sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k; int l; int m;}) = %ld\n", sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k; int l; int m;}));
  ASSERT(52, sizeof(struct {int a; int b; int c; int d; int e; int f; int g; int h; int i; int j; int k; int l; int m;}));
  printf("expected = 18446744073709551615 %lld\n", 0xFFFFFFFFFFFFFFFFULL);
  printf("__WORDSIZE = %d\n", __WORDSIZE);
  ASSERT(64,  __WORDSIZE);
  // __uint128_t u128 = 12345678900987654321;
  printf("%lld\n", (unsigned long long) LONG_MAX);
  // printf("%llx\n", (unsigned long long)(u128 & 0xFFFFFFFFFFFFFFFF));
  printf("%lld\n", (unsigned long long) ULONG_MAX);

  return(0);

}