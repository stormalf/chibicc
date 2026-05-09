// test_avx2_psrldi256.c
//
// Verifies:
//   - __AVX2__ macro exists
//   - __builtin_ia32_psrldi256 lowering
//   - correct vpsrld codegen
//   - logical (NOT arithmetic) right shift semantics
//
// Expected:
//   exit code 0

#include <immintrin.h>

int main(void) {

#ifdef __AVX2__

    // Use negative values to distinguish:
    // logical shift vs arithmetic shift
    //
    // arithmetic:
    //   0xFFFFFFFF >> 1 -> 0xFFFFFFFF
    //
    // logical:
    //   0xFFFFFFFF >> 1 -> 0x7FFFFFFF

    __m256i v =
        _mm256_set1_epi32(-1);

    __m256i r =
        _mm256_srli_epi32(v, 1);

    unsigned int out[8];

    _mm256_storeu_si256((__m256i *)out, r);

    for (int i = 0; i < 8; i++) {
        if (out[i] != 0x7FFFFFFF)
            return i + 1;
    }

       __m256i v1 =
        _mm256_set1_epi32(0x80000000);

    __m256i r1 =
        _mm256_srli_epi32(v1, 31);

    unsigned int out1[8];

    _mm256_storeu_si256((__m256i *)out1, r1);

    for (int i = 0; i < 8; i++) {
        if (out1[i] != 1)
            return 1;
    }

    return 0;

#else
#error "__AVX2__ not defined"
#endif
}
