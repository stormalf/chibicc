#include "test.h"
#include "wmmintrin.h"

int main() {
  __m128i a = _mm_set_epi64x(0, 1);
  __m128i b = _mm_set_epi64x(0, 2);

  _mm_clmulepi64_si128(a, b, 0);

  return 0;
}
