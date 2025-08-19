#include "test.h"

typedef int __m128i __attribute__((vector_size(16)));

int main() {
    __m128i a = {40, 30, 20, 10}; // [40, 30, 20, 10]
    __m128i b = {400, 300, 200, 100}; // [400, 300, 200, 100]

    __m128i r = __builtin_ia32_punpckldq128(a, b);

    // Expected: Interleave low 2 dwords from a and b:
    // a low part: 20, 10
    // b low part: 200, 100
    // => 20, 200, 10, 100  (in reverse order for little-endian print)

    
    printf("%d %d %d %d\n", r[0], r[1], r[2], r[3]);
    ASSERT(40, r[0]);
    ASSERT(400, r[1]);
    ASSERT(30, r[2]);
    ASSERT(300, r[3]);
    printf("OK\n");
    return 0;
}
