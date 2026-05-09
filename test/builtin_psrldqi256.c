#include <immintrin.h>
#include <stdint.h>
#include <string.h>
#include "test.h"

int main() {
  uint8_t X[32];
  for (int i = 0; i < 32; i++)
    X[i] = (uint8_t)(i + 1);

  __m256i x;
  memcpy(&x, X, 32);

  // Shift right by 4 bytes within each 128-bit lane.
  __m256i r = _mm256_srli_si256(x, 4);

  uint8_t out[32];
  memcpy(out, &r, 32);

  for (int i = 0; i < 32; i++) {
    int lane_base = (i / 16) * 16;
    uint8_t expected = 0;
    int j = i + 4;
    if (j < lane_base + 16)
      expected = X[j];
    if (out[i] != expected)
      return 1;
  }

  printf("OK\n");
  return 0;
}
