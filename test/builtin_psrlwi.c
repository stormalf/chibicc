#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = (v4hi){4, 8, -4, -8};  // v4hi with signed values

    // Logical shift right by immediate 1 bit
    v4hi result = __builtin_ia32_psrlwi(a, 1);

    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Expect: 2 4 32766 32764 (logical shift right ignores sign bit)
    ASSERT(2, result[0]);
    ASSERT(4, result[1]);
    ASSERT(32766, result[2]);
    ASSERT(32764, result[3]);

    int count = 1;
    result = __builtin_ia32_psrlwi(a, count);

    ASSERT(2, result[0]);
    ASSERT(4, result[1]);
    ASSERT(32766, result[2]);
    ASSERT(32764, result[3]);
    printf("OK\n");

    return 0;
}
