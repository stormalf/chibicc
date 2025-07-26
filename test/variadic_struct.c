#include <stdarg.h>
#include "test.h"
typedef struct {
  int x;
  int y;
} Point;


typedef struct {
  int i;
  double d;
} Mixed;


typedef union {
  int i;
  float f;
} IntOrFloat;


typedef struct {
  long a;
  long b;
} Pair;


typedef struct {
  int a, b, c, d, e;
} BigStruct;

int test_big_struct(int count, ...) {
  va_list ap;
  va_start(ap, count);

  BigStruct bs = va_arg(ap, BigStruct);

  va_end(ap);

  return bs.a + bs.b + bs.c + bs.d + bs.e;
}


long test_multi(int count, ...) {
  va_list ap;
  va_start(ap, count);

  int x = va_arg(ap, int);
  Pair p = va_arg(ap, Pair);
  double d = va_arg(ap, double);

  va_end(ap);

  return x + p.a + p.b + (long)d;
}


int test_union_int(int count, ...) {
  va_list ap;
  va_start(ap, count);

  IntOrFloat u = va_arg(ap, IntOrFloat);

  va_end(ap);
  return u.i;
}

int test_mixed_struct(int count, ...) {
  va_list ap;
  va_start(ap, count);

  Mixed m = va_arg(ap, Mixed);

  va_end(ap);

  return m.i + (int)m.d;
}


int test_struct_sum(int count, ...) {
  va_list ap;
  va_start(ap, count);

  Point p = va_arg(ap, Point);

  va_end(ap);

  return p.x + p.y;
}

int main() {
    ASSERT(30, test_struct_sum(1, (Point){10, 20}));
    ASSERT(15, test_mixed_struct(1, (Mixed){5, 10.5}));
    ASSERT(42, test_union_int(1, (IntOrFloat){42}));
    ASSERT(1 + 2 + 3 + 4, test_multi(3, 1, (Pair){2,3}, 4.0));
    ASSERT(15, test_big_struct(1, (BigStruct){1,2,3,4,5}));
    return 0;
}
