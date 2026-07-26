#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
  v4sf x = {10, 20, 30, 40};
  ASSERT(10, __builtin_ia32_vec_ext_v4sf(x, 0));
  ASSERT(20, __builtin_ia32_vec_ext_v4sf(x, 1));
  ASSERT(30, __builtin_ia32_vec_ext_v4sf(x, 2));
  ASSERT(40, __builtin_ia32_vec_ext_v4sf(x, 3));
  return 0;
}
