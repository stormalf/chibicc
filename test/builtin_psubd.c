
#include "test.h"

typedef int v2si __attribute__((vector_size(8)));

int main(void) {
    v2si a = {100000, -200000};
    v2si b = {50000, 100000};

    v2si result = (v2si)__builtin_ia32_psubd(a, b);

    for (int i = 0; i < 2; i++)
        printf("%d ", result[i]);
    printf("\n");
    ASSERT(100000, a[0]);
    ASSERT(-200000, a[1]);
    ASSERT(50000, b[0]);
    ASSERT(100000, b[1]);
    ASSERT(50000, result[0]);
    ASSERT(-300000, result[1]);
    printf("OK\n");
}
