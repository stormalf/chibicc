#include "test.h"
#include <immintrin.h>
#include <stdint.h>

int main() {
  unsigned char a[32];
  for (int i = 0; i < 32; i++)
    a[i] = (unsigned char)(50 + i);

  __m256i va = _mm256_loadu_si256((const __m256i *)a);
  __m256i vb = _mm256_set1_epi8(51);
  __m256i vc = _mm256_subs_epu8(va, vb);

  unsigned char out[32];
  _mm256_storeu_si256((__m256i *)out, vc);

  for (int i = 0; i < 32; i++) {
    int exp = (a[i] < 51) ? 0 : (a[i] - 51);
    ASSERT(exp, out[i]);
  }

  printf("OK\n");
  return 0;
}
