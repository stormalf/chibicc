#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));
typedef double v2df __attribute__((vector_size(16)));

int main() {
  v4sf a = {1,2,3,4};
  v4sf b = {5,6,7,8};
  v4sf r = __builtin_ia32_blendps(a, b, 0b1100);
  ASSERT(1, r[0] );
  ASSERT(2, r[1]);
  ASSERT(7, r[2]);
  ASSERT(8, r[3]);

  r = __builtin_ia32_blendps(a, b, 0b0011);
  ASSERT(5, r[0]);
  ASSERT(6, r[1]);
  ASSERT(3, r[2]);
  ASSERT(4, r[3]);

  r = __builtin_ia32_blendps(a, b, 0);
  ASSERT(1, r[0]);
  ASSERT(2, r[1]);
  ASSERT(3, r[2]);
  ASSERT(4, r[3]);

  r = __builtin_ia32_blendps(a, b, 15);
  ASSERT(r[0] == 5, 1);
  ASSERT(r[1] == 6, 1);
  ASSERT(r[2] == 7, 1);
  ASSERT(r[3] == 8, 1);

  v2df c = {1,2};
  v2df d = {3,4};
  v2df s = __builtin_ia32_blendpd(c, d, 0b01);
  ASSERT(3, s[0]);
  ASSERT(2, s[1]);

  s = __builtin_ia32_blendpd(c, d, 0b10);
  ASSERT(1, s[0]);
  ASSERT(4, s[1]);

  s = __builtin_ia32_blendpd(c, d, 0);
  ASSERT(1, s[0]);
  ASSERT(2, s[1]);

  s = __builtin_ia32_blendpd(c, d, 3);
  ASSERT(3, s[0]);
  ASSERT(4, s[1]);

  typedef float v8sf __attribute__((vector_size(32)));
  typedef double v4df __attribute__((vector_size(32)));
  v8sf e = {1,2,3,4,5,6,7,8};
  v8sf f = {9,10,11,12,13,14,15,16};
  v8sf t = __builtin_ia32_blendps256(e, f, 0b10101010);
  ASSERT(1, t[0]);
  ASSERT(10, t[1]);
  ASSERT(3, t[2]);
  ASSERT(12, t[3]);
  ASSERT(5, t[4]);
  ASSERT(14, t[5]);
  ASSERT(7, t[6]);
  ASSERT(16, t[7]);

  t = __builtin_ia32_blendps256(e, f, 0);
  ASSERT(1, t[0]);
  ASSERT(2, t[1]);
  ASSERT(3, t[2]);
  ASSERT(4, t[3]);
  ASSERT(5, t[4]);
  ASSERT(6, t[5]);
  ASSERT(7, t[6]);
  ASSERT(8, t[7]);

  t = __builtin_ia32_blendps256(e, f, 255);
  ASSERT(9, t[0]);
  ASSERT(10, t[1]);
  ASSERT(11, t[2]);
  ASSERT(12, t[3]);
  ASSERT(13, t[4]);
  ASSERT(14, t[5]);
  ASSERT(15, t[6]);
  ASSERT(16, t[7]);

  v4df g = {1,2,3,4};
  v4df h = {5,6,7,8};
  v4df u = __builtin_ia32_blendpd256(g, h, 0b0110);
  ASSERT(1, u[0]);
  ASSERT(6, u[1]);
  ASSERT(7, u[2]);
  ASSERT(4, u[3]);

  u = __builtin_ia32_blendpd256(g, h, 0);
  ASSERT(1, u[0]);
  ASSERT(2, u[1]);
  ASSERT(3, u[2]);
  ASSERT(4, u[3]);

  u = __builtin_ia32_blendpd256(g, h, 15);
  ASSERT(5, u[0]);
  ASSERT(6, u[1]);
  ASSERT(7, u[2]);
  ASSERT(8, u[3]);

  return 0;
}
