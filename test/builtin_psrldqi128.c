#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
#include "test.h"

int main() {
    uint8_t X[16];
    for (int i = 0; i < 16; i++)
        X[i] = (uint8_t)(i + 1);

    __m128i x;
    memcpy(&x, X, 16);

    // Shift right by 4 bytes
    __m128i r = _mm_srli_si128(x, 4);

    uint8_t out[16];
    memcpy(out, &r, 16);

    for (int i = 0; i < 16; i++) {
        uint8_t expected = 0;
        if (i < 12)
            expected = X[i + 4];

        if (out[i] != expected) {
            printf("Mismatch at %d: got %u expected %u\n", i, out[i], expected);
            return 1;
        }
    }

    // Shift left by 4 bytes
    __m128i s = _mm_slli_si128(x, 4);
    memcpy(out, &s, 16);

    for (int i = 0; i < 16; i++) {
        uint8_t expected = 0;
        if (i >= 4)
            expected = X[i - 4];

        if (out[i] != expected) {
            printf("Mismatch at %d: got %u expected %u\n", i, out[i], expected);
            return 1;
        }
    }

    printf("OK\n");
    return 0;
}
