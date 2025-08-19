#include "test.h"

typedef int v2si __attribute__((vector_size(8))); // 2 x 32-bit ints

int main() {
    v2si a = {4, -4};  // second value has sign bit set

    // Logical shift right by vector count
    v2si count_vec = {1, 1};
    v2si r1 = __builtin_ia32_psrld(a, count_vec);
    printf("psrld variable count: %u %u\n", (unsigned)r1[0], (unsigned)r1[1]);


    ASSERT(0, (unsigned)r1[0]);
    ASSERT(0, (unsigned)r1[1]);
    printf("OK\n");
    return 0;
}
