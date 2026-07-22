#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
#include "test.h"
#include <stdlib.h>

#define ASSERT(expected, actual) do { \
    if ((expected) != (actual)) { \
        fprintf(stderr, "FAIL: line %d: expected %d, got %d\n", __LINE__, (expected), (actual)); \
        exit(1); \
    } \
} while(0)

int main() {
    uint16_t X[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    __m128i x;
    memcpy(&x, X, 16);

    // pshufhw 0x1B: high words [3,2,1,0] = reverse high words
    __m128i r = _mm_shufflehi_epi16(x, 0x1B);
    uint16_t out[8];
    memcpy(out, &r, 16);
    ASSERT(10, out[0]);
    ASSERT(20, out[1]);
    ASSERT(30, out[2]);
    ASSERT(40, out[3]);
    ASSERT(80, out[4]);
    ASSERT(70, out[5]);
    ASSERT(60, out[6]);
    ASSERT(50, out[7]);

    // pshuflw 0x1B: low words [3,2,1,0] = reverse low words
    __m128i s = _mm_shufflelo_epi16(x, 0x1B);
    memcpy(out, &s, 16);
    ASSERT(40, out[0]);
    ASSERT(30, out[1]);
    ASSERT(20, out[2]);
    ASSERT(10, out[3]);
    ASSERT(50, out[4]);
    ASSERT(60, out[5]);
    ASSERT(70, out[6]);
    ASSERT(80, out[7]);

    printf("All tests passed!\n");
    return 0;
}
