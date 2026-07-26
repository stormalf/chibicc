#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));
typedef double v2df __attribute__((vector_size(16)));

int main() {
  v4sf a = {1,2,3,4};
  v4sf b = {5,6,7,8};
  v4sf r = __builtin_ia32_dpps(a, b, 0xFF);
  ASSERT(70, r[0]);
  ASSERT(70, r[1]);
  ASSERT(70, r[2]);
  ASSERT(70, r[3]);

  v2df c = {1,2};
  v2df d = {3,4};
  v2df s = __builtin_ia32_dppd(c, d, 0xFF);
  ASSERT(11, s[0]);
  ASSERT(11, s[1]);

  return 0;
}
