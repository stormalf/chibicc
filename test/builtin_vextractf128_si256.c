// test_vextractf128_si256.c
#include <immintrin.h>
#include <string.h>
#include "test.h"

static void check(int cond, const char *msg) {
    if (!cond) {
        printf("FAIL: %s\n", msg);
        __builtin_abort();
    }
}

int main(void) {
    // Build a known 256-bit vector:
    // lane 0 (low 128):  0,1,2,3
    // lane 1 (high 128): 4,5,6,7
    int data[8] = {0,1,2,3,4,5,6,7};

    __m256i v = _mm256_loadu_si256((__m256i*)data);

    // Extract low 128-bit lane (imm8 = 0)
    __m128i lo = (__m128i)__builtin_ia32_vextractf128_si256((__v8si)v, 0);

    // Extract high 128-bit lane (imm8 = 1)
    __m128i hi = (__m128i)__builtin_ia32_vextractf128_si256((__v8si)v, 1);

    int out_lo[4];
    int out_hi[4];

    _mm_storeu_si128((__m128i*)out_lo, lo);
    _mm_storeu_si128((__m128i*)out_hi, hi);

    // Validate low lane
    check(out_lo[0] == 0, "lo[0]");
    check(out_lo[1] == 1, "lo[1]");
    check(out_lo[2] == 2, "lo[2]");
    check(out_lo[3] == 3, "lo[3]");

    // Validate high lane
    check(out_hi[0] == 4, "hi[0]");
    check(out_hi[1] == 5, "hi[1]");
    check(out_hi[2] == 6, "hi[2]");
    check(out_hi[3] == 7, "hi[3]");

    printf("OK\n");
    return 0;
}
