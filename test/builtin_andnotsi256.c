#include <immintrin.h>
#include "test.h"
#include <stdint.h>

static void check(int cond, const char *msg) {
    if (!cond) {
        printf("FAIL: %s\n", msg);
        __builtin_abort();
    }
}

int main(void) {
    // 256-bit pattern split into 8 x 32-bit integers
    uint32_t a_data[8] = {
        0x00000000, 0xFFFFFFFF,
        0xAAAAAAAA, 0x55555555,
        0x12345678, 0xFFFFFFFF,
        0x0F0F0F0F, 0xF0F0F0F0
    };

    uint32_t b_data[8] = {
        0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF
    };

    __m256i a = _mm256_loadu_si256((const __m256i*)a_data);
    __m256i b = _mm256_loadu_si256((const __m256i*)b_data);

    __m256i r = __builtin_ia32_andnotsi256(a, b);

    uint32_t out[8];
    _mm256_storeu_si256((__m256i*)out, r);

    // Expected: ~a & b == ~a (since b is all 1s)
    check(out[0] == ~a_data[0], "lane 0");
    check(out[1] == ~a_data[1], "lane 1");
    check(out[2] == ~a_data[2], "lane 2");
    check(out[3] == ~a_data[3], "lane 3");
    check(out[4] == ~a_data[4], "lane 4");
    check(out[5] == ~a_data[5], "lane 5");
    check(out[6] == ~a_data[6], "lane 6");
    check(out[7] == ~a_data[7], "lane 7");

    printf("OK\n");
    return 0;
}
