#include <immintrin.h>
#include "test.h"

int main() {
  __m256i x = _mm256_set1_epi32(1);
  __m128i y = _mm_set1_epi32(2);

  __m256i r = _mm256_insertf128_si256(x, y, 1);

  int out[8];
  _mm256_storeu_si256((__m256i*)out, r);

  // upper lane should be 2
  for (int i = 4; i < 8; i++)
    if (out[i] != 2) return 1;

  printf("OK\n");
}
