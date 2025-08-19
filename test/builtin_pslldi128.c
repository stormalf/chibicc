#include "test.h"
#include <stdint.h>

// Declare the builtin
typedef int __m128i __attribute__((__vector_size__(16), __may_alias__));


int main() {
    __m128i v = { 1, 2, 3, 4 };   // Four 32-bit integers in the 128-bit vector
    int shift = 2;                // Shift left by 2 bits

    __m128i result = __builtin_ia32_pslldi128(v, shift);

    uint32_t *vals = (uint32_t *)&result;
    printf("Result: %u %u %u %u\n", vals[0], vals[1], vals[2], vals[3]);

    ASSERT(4, result[0]);
    ASSERT(8, result[1]);
    ASSERT(12, result[2]);
    ASSERT(16, result[3]);

    result = __builtin_ia32_pslldi128(v, 2);
    ASSERT(4, result[0]);
    ASSERT(8, result[1]);
    ASSERT(12, result[2]);
    ASSERT(16, result[3]);
    printf("OK\n");
    return 0;
}
