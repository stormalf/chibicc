#include "test.h"
#include <smmintrin.h>

int main() {
  __m128i d = _mm_setzero_si128();
  __m128i r = _mm_insert_epi8(d, 42, 5);
  ASSERT(42, _mm_extract_epi8(r, 5));

  r = _mm_insert_epi32(d, 12345, 2);
  ASSERT(12345, _mm_extract_epi32(r, 2));

  r = _mm_insert_epi64(d, 987654321, 0);
  ASSERT(987654321, _mm_extract_epi64(r, 0));

  return 0;
}
