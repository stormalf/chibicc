// test_avx2_pslldi256.c
//
// Checks:
//   - __AVX2__ macro definition
//   - builtin typing/codegen
//   - vpslld immediate emission
//   - correct 32-bit lane shifting
//
// Expected:
//   exit code 0

#include <immintrin.h>
#include <stdio.h>


int main(void) {

#ifdef __AVX2__

    __m256i v =
        _mm256_set_epi32(
            8, 7, 6, 5,
            4, 3, 2, 1);

    // maps to:
    // __builtin_ia32_pslldi256(...)
    __m256i r = _mm256_slli_epi32(v, 1);

    int out[8];

    _mm256_storeu_si256((__m256i *)out, r);

    // _mm256_set_epi32 stores reversed order
    if (out[0] != 2)  return 1;
    if (out[1] != 4)  return 2;
    if (out[2] != 6)  return 3;
    if (out[3] != 8)  return 4;
    if (out[4] != 10) return 5;
    if (out[5] != 12) return 6;
    if (out[6] != 14) return 7;
    if (out[7] != 16) return 8;
    printf("Ok\n");

    return 0;

#else
#error "__AVX2__ not defined"
#endif
}