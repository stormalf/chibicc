#include "test.h"
#include <immintrin.h>
#include <stdint.h>

int main() {
  unsigned char a[32] = {1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16,
                         1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16};
  unsigned char b[32] = {10,10,10,10, 0,0,0,0, 10,10,10,10, 0,0,0,0,
                         10,10,10,10, 0,0,0,0, 10,10,10,10, 0,0,0,0};

  __m256i va = _mm256_loadu_si256((const __m256i *)a);
  __m256i vb = _mm256_loadu_si256((const __m256i *)b);
  __m256i vc = _mm256_mpsadbw_epu8(va, vb, 0);

  short out[16];
  _mm256_storeu_si256((__m256i *)out, vc);

  ASSERT(30, out[0]);
  ASSERT(26, out[1]);
  ASSERT(22, out[2]);
  ASSERT(18, out[3]);
  ASSERT(14, out[4]);
  ASSERT(10, out[5]);
  ASSERT(6, out[6]);
  ASSERT(4, out[7]);
  ASSERT(30, out[8]);
  ASSERT(26, out[9]);
  ASSERT(22, out[10]);
  ASSERT(18, out[11]);
  ASSERT(14, out[12]);
  ASSERT(10, out[13]);
  ASSERT(6, out[14]);
  ASSERT(4, out[15]);

  printf("OK\n");
  return 0;
}
