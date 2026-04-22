#include <immintrin.h>
#include <stdint.h>
#include <string.h>
#include "test.h"

int main() {
  int8_t A[32], B[32];

  for (int i = 0; i < 32; i++) {
    A[i] = i - 16;
    B[i] = 0;
  }

  __m256i a, b;
  memcpy(&a, A, 32);
  memcpy(&b, B, 32);

  __mmask32 k = _mm256_cmpgt_epi8_mask(a, b);

  for (int i = 0; i < 32; i++) {
    int expected = (A[i] > 0);
    int got = (k >> i) & 1;

    if (got != expected)
      return 1;
  }

  printf("Ok\n");
  return 0;
}