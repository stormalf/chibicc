#include "test.h"
#include <stdint.h>

typedef char __m128i __attribute__((__vector_size__(16), __may_alias__));
typedef unsigned char __m128u __attribute__((__vector_size__(16), __may_alias__));


__m128i test_psubusb128(__m128i a, __m128i b) {
    return __builtin_ia32_psubusb128(a, b);
}

int main() {
    // Initialize with unsigned bytes
    __m128i a = (__m128i){ 200, 255, 0, 50, 100, 5, 255, 10,
                           200, 255, 0, 50, 100, 5, 255, 10 };
    __m128i b = (__m128i){ 100, 100, 100, 100, 200, 200, 5, 20,
                           100, 100, 100, 100, 200, 200, 5, 20 };

    __m128u result = (__m128u)test_psubusb128(a, b);

    unsigned char *res = (unsigned char *)&result;
    printf("Result: ");
    for (int i = 0; i < 16; i++)
        printf("%u ", res[i]);
    printf("\n");

    // Expected (saturated at 0)
    // 100, 155, 0, 0, 0, 0, 250, 0,
    // 100, 155, 0, 0, 0, 0, 250, 0
    ASSERT(100, result[0]);
    ASSERT(155, result[1]);
    ASSERT(0, result[2]);
    ASSERT(0, result[3]);
    ASSERT(0, result[4]);
    ASSERT(0, result[5]);
    ASSERT(250, result[6]);
    ASSERT(0, result[7]);
    ASSERT(100, result[8]);
    ASSERT(155, result[9]);
    ASSERT(0, result[10]);
    ASSERT(0, result[11]);
    ASSERT(0, result[12]);
    ASSERT(0, result[13]);
    ASSERT(250, result[14]);
    ASSERT(0, result[15]);
    printf("OK\n");

}
