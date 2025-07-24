#include <stdarg.h>
#include "test.h"
typedef struct {
  char g;
} G;

typedef struct {
  float f;
} F;

typedef struct {
  char l;
  float d;
} A;

typedef struct __attribute__((aligned(32))) {
  char c;
  char pad[31]; // ensure struct size >= alignment
} Aligned1024;

long double test_variadic(G g0, G g1, F f0, F f1, int i0, int i1, ...) {
  va_list ap;
  va_start(ap, i1);

  long double ret = i0 + i1;
  printf("start ret=%Lf\n", ret);
  ASSERT(300, ret);
  // Read long double
  long double ld = va_arg(ap, long double);
  ret += ld;
  printf("after long double ret=%Lf\n", ret);
  ASSERT(301, ret);
  // Read Aligned1024
  Aligned1024 s1 = va_arg(ap, Aligned1024);
  ret += s1.c;
  printf("after Aligned1024 ret=%Lf (s1.c=%d)\n", ret, s1.c);
  ASSERT(378, ret);
  // Read int
  int i2 = va_arg(ap, int);
  ret += i2;
  printf("after int ret=%Lf (i2=%d)\n", ret, i2);
  ASSERT(678, ret);
  // Read double
  double d = va_arg(ap, double);
  ret += d;
  printf("after double ret=%Lf (d=%f)\n", ret, d);
  ASSERT(683, ret);
  // Read another Aligned1024
  Aligned1024 s2 = va_arg(ap, Aligned1024);
  ret += s2.c;
  printf("after second Aligned1024 ret=%Lf (s2.c=%d)\n", ret, s2.c);
  ASSERT(760, ret);
  int i3 = va_arg(ap, int);
  ret += i3;
  printf("after last int ret=%Lf (d=%d)\n", ret, i3);
  ASSERT(1160, ret);
  va_end(ap);
  return ret;
}

int main(void) {
  G g0 = {10}, g1 = {11};
  F f0 = {20.0}, f1 = {21.0};
  Aligned1024 s = {.c = 77};

  long double res = test_variadic(
    g0, g1,
    f0, f1,
    100, 200,
    (long double)1.5,
    s,
    300,
    (double)4.5,
    s,
    400
  );

  printf("Final result: %Lf\n", res);
  ASSERT(1160, res);
  return 0;
}
