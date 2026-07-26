#include <smmintrin.h>
#include "test.h"

int main() {
  __m128d d = _mm_set_pd(1.0, 2.0);
  __m128d v = _mm_set_pd(3.0, 4.0);
  __m128d r = _mm_round_sd(d, v, _MM_FROUND_TO_NEAREST_INT);

  ASSERT(4, r[0]);
  ASSERT(1, r[1]);
  return 0;
}
