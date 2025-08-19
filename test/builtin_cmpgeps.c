#include "test.h"
#include <stdint.h>

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 4.0f, 3.0f, 7.0f};
    v4sf b = {1.0f, 2.0f, 3.5f, 5.0f};

    // cmpgeps: compare a >= b for each element, result is mask (all bits set or zero)
    v4sf c = __builtin_ia32_cmpgeps(a, b);

    // Print results as integers to see the mask bits (0xFFFFFFFF or 0)
    uint32_t* mask = (uint32_t*)&c;

    printf("cmpgeps results:\n");
    for (int i = 0; i < 4; i++) {
        printf("a[%d] >= b[%d] : %s (mask=0x%08x)\n",
               i, i, mask[i] == 0xFFFFFFFF ? "true" : "false", mask[i]);
    }

    ASSERT(-2147483648, c[0]);
    ASSERT(-2147483648, c[1]);
    ASSERT(0, c[2]);
    ASSERT(-2147483648, c[3]);
    printf("OK\n");
    return 0;
}
