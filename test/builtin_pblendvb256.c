#include <immintrin.h>
#include <stdint.h>
#include <string.h>
#include "test.h"

int main() {
  uint8_t A[32], B[32], M[32];
  for (int i = 0; i < 32; i++) {
    A[i] = (uint8_t)(i);
    B[i] = (uint8_t)(100 + i);
    M[i] = (i & 1) ? 0x80 : 0x00; // select B on odd bytes
  }

  __m256i a, b, m;
  memcpy(&a, A, 32);
  memcpy(&b, B, 32);
  memcpy(&m, M, 32);

  __m256i r = _mm256_blendv_epi8(a, b, m);

  uint8_t out[32];
  memcpy(out, &r, 32);

  for (int i = 0; i < 32; i++) {
    uint8_t expected = (i & 1) ? B[i] : A[i];
    if (out[i] != expected)
      return 1;
  }

  printf("OK\n");
  return 0;
}
