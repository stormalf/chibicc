#include "test.h"
#include <immintrin.h>
#include <stdint.h>

int main() {
  signed char a[32];
  signed char b[32];
  for (int i = 0; i < 32; i++) {
    a[i] = (signed char)(i - 16);
    b[i] = 0;
  }

  __m256i va = _mm256_loadu_si256((const __m256i *)a);
  __m256i vb = _mm256_loadu_si256((const __m256i *)b);
  __m256i vc = _mm256_cmpgt_epi8(va, vb);

  unsigned char out[32];
  _mm256_storeu_si256((__m256i *)out, vc);

  for (int i = 0; i < 32; i++) {
    int exp = (a[i] > 0) ? 0xff : 0x00;
    ASSERT(exp, out[i]);
  }

  printf("OK\n");
  return 0;
}
