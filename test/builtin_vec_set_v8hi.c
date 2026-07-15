#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
#include "test.h"

int main() {
    uint16_t X[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    __m128i x;
    memcpy(&x, X, 16);

    // Insert 99 at index 2
    __m128i r = _mm_insert_epi16(x, 99, 2);

    uint16_t out[8];
    memcpy(out, &r, 16);
    ASSERT(10,  out[0]);
    ASSERT(20,  out[1]);
    ASSERT(99,  out[2]);
    ASSERT(40,  out[3]);
    ASSERT(50,  out[4]);
    ASSERT(60,  out[5]);
    ASSERT(70,  out[6]);
    ASSERT(80,  out[7]);
    return 0;
}
