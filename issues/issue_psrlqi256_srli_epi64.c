#include <immintrin.h>
#include "test.h"

typedef unsigned long long uint64_t;

int main(void) {
  __m256i a = _mm256_set1_epi32(0x12345678);
  __m256i r = _mm256_srli_epi64(a, 4);
  uint64_t out[4];
  _mm256_storeu_si256((__m256i*)out, r);
  return 0;
}
