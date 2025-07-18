#include <stdarg.h>
#include "test.h"


typedef struct { int x; int y; } Point;

int sum_point_array(int count, ...) {
  va_list ap;
  va_start(ap, count);

  Point *arr = va_arg(ap, Point *);

  va_end(ap);

  int sum = 0;
  for (int i = 0; i < count; i++)
    sum += arr[i].x + arr[i].y;

  return sum;
}

int sum_array(int count, ...) {
  va_list ap;
  va_start(ap, count);

  int *arr = va_arg(ap, int *);

  va_end(ap);

  int sum = 0;
  for (int i = 0; i < count; i++)
    sum += arr[i];

  return sum;
}


int sum_float_array(int count, ...) {
  va_list ap;
  va_start(ap, count);

  float *arr = va_arg(ap, float *);

  va_end(ap);

  float sum = 0;
  for (int i = 0; i < count; i++)
    sum += arr[i];

  return (int)sum;
}

int mix_array_scalar(int count, ...) {
  va_list ap;
  va_start(ap, count);

  int *arr = va_arg(ap, int *);
  int extra = va_arg(ap, int);

  va_end(ap);

  int sum = extra;
  for (int i = 0; i < count; i++)
    sum += arr[i];

  return sum;
}


int main() {
    ASSERT(10, ({
    int a[] = {1,2,3,4};
    sum_array(4, a);
    }));

    
    ASSERT(6, ({
    float a[] = {1.5, 2.5, 2.0};
    sum_float_array(3, a);
    }));

    ASSERT(20, ({
    int a[] = {3,4,5,6};
    mix_array_scalar(4, a, 2); // 2 + 3+4+5+6 = 20
    }));

    
    ASSERT(21, ({
    Point pts[] = {{1,2},{3,4},{5,6}};
    sum_point_array(3, pts);
    }));
    
    return 0;
}


