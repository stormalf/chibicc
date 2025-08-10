#include "test.h"
#include <math.h>

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, NAN, 3.0f, 4.0f};
    v4sf b = {2.0f, 5.0f, NAN, 4.0f};

    // cmpordps returns true (all bits set) if neither element is NaN, false (0) otherwise
    v4sf c = __builtin_ia32_cmpordps(a, b);

    unsigned int *r = (unsigned int *)&c;

    printf("cmpordps results:\n");
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = 0x%08x\n", i, r[i]);
    }

    ASSERT(-2147483648, c[0]);
    ASSERT(0, c[1]);
    ASSERT(0, c[2]);
    ASSERT(-2147483648, c[3]);
    printf("OK\n");
    return 0;
}
