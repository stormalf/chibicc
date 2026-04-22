#include "test.h"
#include <stdint.h>
#include <x86intrin.h>


int main(void) {

    uint8_t A[32];
    uint8_t B[32];

    for (int i = 0; i < 32; i++) {
        A[i] = i;        // 0..31
        B[i] = i + 1;    // 1..32
    }

    __m256i a = *(__m256i *)A;
    __m256i b = *(__m256i *)B;

    __m256i c = _mm256_subs_epu8(a, b);

    uint8_t *res = (uint8_t *)&c;

    // Validate: saturating subtract → always 0
    for (int i = 0; i < 32; i++) {
        if (res[i] != 0)
        return 1;
    }
    printf("OK\n");
    return 0;
}