#include "test.h"
#include <smmintrin.h>

int main() {
  __m128i x = _mm_setr_epi8(
      1, 2, 3, 4,
      5, 6, 7, 8,
      0, 0, 0, 0,
      0, 0, 0, 0);

  __m128i y = _mm_setr_epi8(
      10, 10, 10, 10,
      0, 0, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0);

  __m128i r = _mm_mpsadbw_epu8(x, y, 0);

  ASSERT(30, _mm_extract_epi16(r, 0));

  return 0;
}