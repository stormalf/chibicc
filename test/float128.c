#include "test.h"

typedef __float128 _Float128;

_Float128 add(_Float128 a, _Float128 b) {
  return a + b;
}

int gt(_Float128 a, _Float128 b) {
  return a > b;
}

int main() {
  ASSERT(16, sizeof(_Float128));
  ASSERT(16, _Alignof(_Float128));

  _Float128 x = 1.0;
  _Float128 y = 2.0;
  _Float128 z = x + y;
  ASSERT(1, z > 2.0);
  ASSERT(0, z < 2.0);
  ASSERT(1, gt(y, x));

  _Float128 w = add(x, y);
  ASSERT(1, w > 2.0);

  _Float128 arr[4];
  arr[0] = 10.0;
  arr[1] = 20.0;
  ASSERT(1, arr[1] > arr[0]);

  double d = (double)x;
  ASSERT(1, d > 0);

  return 0;
}
