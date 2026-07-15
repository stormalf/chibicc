#include "test.h"

__float128 add(__float128 a, __float128 b) {
  return a + b;
}

int gt(__float128 a, __float128 b) {
  return a > b;
}

int main() {
  ASSERT(16, sizeof(__float128));
  ASSERT(16, _Alignof(__float128));

  __float128 x = 1.0;
  __float128 y = 2.0;
  __float128 z = x + y;
  ASSERT(1, z > 2.0);
  ASSERT(0, z < 2.0);
  ASSERT(1, gt(y, x));

  __float128 w = add(x, y);
  ASSERT(1, w > 2.0);

  __float128 arr[4];
  arr[0] = 10.0;
  arr[1] = 20.0;
  ASSERT(1, arr[1] > arr[0]);

  double d = (double)x;
  ASSERT(1, d > 0);

  return 0;
}
