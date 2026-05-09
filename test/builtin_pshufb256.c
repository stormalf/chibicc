#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
  uint8_t X[32];
  uint8_t M[32];

  // Initialize X with known pattern
  for (int i = 0; i < 32; i++) {
    X[i] = i;
  }

  // Mask: reverse each 16-byte lane
  for (int i = 0; i < 32; i++) {
    M[i] = 15 - (i % 16);
  }

  __m256i x, m;
  memcpy(&x, X, 32);
  memcpy(&m, M, 32);

  __m256i r = _mm256_shuffle_epi8(x, m);

  uint8_t out[32];
  memcpy(out, &r, 32);

  // validate: each lane is reversed
  for (int i = 0; i < 32; i++) {
    int lane_base = (i / 16) * 16;
    int idx = lane_base + (15 - (i % 16));

    if (out[i] != X[idx])
      return 1;
  }

  printf("OK\n");
  return 0;
}