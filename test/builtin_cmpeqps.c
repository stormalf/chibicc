
#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {1.0f, 5.0f, 3.0f, 7.0f};

    v4sf res = __builtin_ia32_cmpeqps(a, b);

    unsigned int *p = (unsigned int*)&res;

    // Each lane will be 0xffffffff if equal, else 0
    printf("cmpeqps results:\n");
    for (int i = 0; i < 4; i++) {
        printf("lane %d: 0x%x\n", i, p[i]);
    }

    ASSERT(-2147483648, res[0]);
    ASSERT(0, res[1]);
    ASSERT(-2147483648, res[2]);
    ASSERT(0, res[3]);
    printf("OK\n");

    return 0;
}
