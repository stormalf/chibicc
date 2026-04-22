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
    uint16_t a[16] = {
        0xFFFF, 0x1234, 0x8000, 0x0001,
        0x00FF, 0x7FFF, 0xAAAA, 0x5555,
        0x0002, 0x00F0, 0x0F0F, 0x3333,
        0xFFFF, 0x0003, 0x2222, 0x8001
    };

    uint16_t b[16] = {
        0xFFFF, 0x0002, 0x0002, 0xFFFF,
        0x0101, 0x0002, 0x1111, 0x2222,
        0x1000, 0x0F0F, 0xF0F0, 0x0003,
        0xFFFF, 0x0004, 0x3333, 0x7FFF
    };

    __m256i va = _mm256_loadu_si256((__m256i*)a);
    __m256i vb = _mm256_loadu_si256((__m256i*)b);
    __m256i vr = __builtin_ia32_pmulhuw256(va, vb);

    uint16_t out[16];
    _mm256_storeu_si256((__m256i*)out, vr);

    for (int i = 0; i < 16; i++) {
        uint32_t ref = (uint32_t)a[i] * (uint32_t)b[i];
        uint16_t expected = ref >> 16;

        if (out[i] != expected) {
            printf("FAIL lane %d: got=%u expected=%u\n",
                   i, out[i], expected);
            __builtin_abort();
        }
    }

    printf("OK\n");
    return 0;
}
