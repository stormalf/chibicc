#include <smmintrin.h>
#include "test.h"

int main() {
  __m128d v = _mm_set_pd(1.6, 2.6);
  __m128d r = _mm_round_pd(v, _MM_FROUND_TO_NEAREST_INT);

  ASSERT(3, r[0]);
  ASSERT(2, r[1]);
  
  return 0;
}