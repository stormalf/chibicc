#include "test.h"
typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {0xFFFFFFFF, 0x00000000, 0xAAAAAAAA, 0x55555555};
    v4sf b = {0x0F0F0F0F, 0xF0F0F0F0, 0xAAAAAAAA, 0xFFFFFFFF};

    v4sf c = __builtin_ia32_andps(a, b);

    for (int i = 0; i < 4; i++) {
        printf("c[%d] = 0x%08X\n", i, *(unsigned int*)&c[i]);
    }

    ASSERT(134217728, c[0]);
    ASSERT(0, c[1]);
    ASSERT(-2147483648, c[2]);
    ASSERT(1073741824, c[3]);
    printf("OK\n");
    return 0;
}
