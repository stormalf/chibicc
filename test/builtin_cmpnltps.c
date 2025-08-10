#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 4.0f, 3.0f, 6.0f};
    v4sf b = {2.0f, 3.0f, 3.0f, 7.0f};

    v4sf c = __builtin_ia32_cmpnltps(a, b);

    unsigned int *res = (unsigned int*)&c;
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = 0x%08x\n", i, res[i]);
    }

    ASSERT(0, c[0]);
    ASSERT(-2147483648, c[1]);
    ASSERT(-2147483648, c[2]);
    ASSERT(0, c[3]);
    printf("OK\n");
    return 0;
}
