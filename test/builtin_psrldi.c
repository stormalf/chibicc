#include "test.h"

typedef int v2si __attribute__((vector_size(8))); // 2 x 32-bit ints

int main() {
    v2si a = {4, -4};  // second value has sign bit set

    // Logical shift right by vector count
    v2si count_vec = {1, 1};

    // Logical shift right by immediate count
    v2si r2 = __builtin_ia32_psrldi(a, 1);
    printf("psrldi immediate count: %u %u\n", (unsigned)r2[0], (unsigned)r2[1]);

    int count = 1;
    r2 = __builtin_ia32_psrldi(a, count);
    printf("psrldi immediate count: %u %u\n", (unsigned)r2[0], (unsigned)r2[1]);

    // psrldi : 2 2147483646

    ASSERT(2, (unsigned)r2[0]);
    ASSERT(2147483646, (unsigned)r2[1]);
    printf("OK\n");

    return 0;
}
