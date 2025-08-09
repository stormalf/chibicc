#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {1, 2, 3, 4};
    v4hi b = {5, 6, 7, 8};


    v4hi result = (v4hi)__builtin_ia32_pmaddwd(a, b);

    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }

    ASSERT(1, a[0]);
    ASSERT(2, a[1]);
    ASSERT(3, a[2]);
    ASSERT(4, a[3]);
    ASSERT(5, b[0]);
    ASSERT(6, b[1]);
    ASSERT(7, b[2]);
    ASSERT(8, b[3]);

    ASSERT(17, result[0]);
    ASSERT(0, result[1]);
    ASSERT(53, result[2]);
    ASSERT(0, result[3]);
    printf("OK\n");

    return 0;
}
