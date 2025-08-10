#include "test.h"
#include <stdint.h>

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {1.0f, 1.5f, 3.5f, 4.0f};

    // __builtin_ia32_cmpnleps returns a mask vector where
    // each element is 0xFFFFFFFF if !(a[i] <= b[i]) (i.e. a[i] > b[i]),
    // else 0x0.
    v4sf c = __builtin_ia32_cmpnleps(a, b);

    uint32_t *res = (uint32_t *)&c;

    printf("cmpnleps results:\n");
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = 0x%08x  => %s\n", i, res[i], res[i] ? "true" : "false");
    }

    ASSERT(0, c[0]);
    ASSERT(-2147483648, c[1]);
    ASSERT(0, c[2]);
    ASSERT(0, c[3]);
    printf("OK\n");
    return 0;
}
