#include <smmintrin.h>
#include "test.h"

int main() {
  __m128 a = _mm_set_ps(9.0f, 8.0f, 7.0f, 1.0f);
  __m128 b = _mm_set_ps(0.0f, 0.0f, 0.0f, 2.6f);

  __m128 r = _mm_round_ss(a, b, _MM_FROUND_TO_NEAREST_INT);

  // low lane: 2.6 -> 3.0
  ASSERT(3.0f, r[0]);

  // upper lanes come from 'a'
  ASSERT(7.0f, r[1]);
  ASSERT(8.0f, r[2]);
  ASSERT(9.0f, r[3]);

  return 0;
}