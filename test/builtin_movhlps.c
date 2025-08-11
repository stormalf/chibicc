#include "test.h"
#include <stdint.h>

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {5.0f, 6.0f, 7.0f, 8.0f};

    // movhlps moves the upper half of b into the upper half of a
    v4sf c = __builtin_ia32_movhlps(a, b);

    printf("Result vector:\n");
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, ((float*)&c)[i]);
    }

    // Expected output:
    // c[0] = 1.0 (from a[0])
    // c[1] = 2.0 (from a[1])
    // c[2] = 7.0 (from b[2])
    // c[3] = 8.0 (from b[3])

    ASSERT(7, c[0]);
    ASSERT(8, c[1]);
    ASSERT(3, c[2]);
    ASSERT(4, c[3]);
    printf("OK\n");

    return 0;
}
