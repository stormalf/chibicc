// Test that roundps works with --backend-llvm
#include <smmintrin.h>
#include "test.h"

int main() {
  __m128 v = _mm_set_ps(1.4, 2.4, 3.6, 4.6);
  __m128 r = _mm_round_ps(v, _MM_FROUND_TO_NEAREST_INT);

  ASSERT(5, r[0]);
  ASSERT(4, r[1]);
  return 0;
}
