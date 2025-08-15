#include "test.h"
#include <stdint.h>


typedef short __m128i __attribute__((__vector_size__(16), __may_alias__));
typedef unsigned short __m128u __attribute__((__vector_size__(16), __may_alias__));

int main() {
    // Test vectors
    __m128i a = (__m128i){ 500, 1000, 30000, 40000, 50, 60, 65535, 0 };
    __m128i b = (__m128i){ 100, 2000, 40000, 500, 100, 50, 65535, 1 };

    __m128u result = (__m128u)__builtin_ia32_psubusw128(a, b);

    uint16_t *res = (uint16_t *)&result;
    for (int i = 0; i < 8; i++) {
        printf("%u ", res[i]);
    }
    printf("\n");

    ASSERT(400, result[0]);
    ASSERT(0, result[1]);
    ASSERT(0, result[2]);
    ASSERT(39500, result[3]);
    ASSERT(0, result[4]);
    ASSERT(10, result[5]);
    ASSERT(0, result[6]);
    ASSERT(0, result[7]);

    printf("OK\n");
    return 0;
}
