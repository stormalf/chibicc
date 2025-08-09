
#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main(void) {
    v4hi a = {1000, -2000, 3000, -32768};
    v4hi b = {500, 500, -3000, 1};

    v4hi result = (v4hi)__builtin_ia32_psubw(a, b);

    for (int i = 0; i < 4; i++)
        printf("%d ", result[i]);
    ASSERT(1000, a[0]);
    ASSERT(-2000, a[1]);
    ASSERT(3000, a[2]);
    ASSERT(-32768, a[3]);
    ASSERT(500, b[0]);
    ASSERT(500, b[1]);
    ASSERT(-3000, b[2]);
    ASSERT(1, b[3]);

    ASSERT(500, result[0]);
    ASSERT(-2500, result[1]);
    ASSERT(6000, result[2]);
    ASSERT(32767, result[3]);

    printf("\n");

    printf("OK\n");
}
