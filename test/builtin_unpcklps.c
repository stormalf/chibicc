#include "test.h"
#include <stdint.h>

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {5.0f, 6.0f, 7.0f, 8.0f};

    v4sf c = __builtin_ia32_unpcklps(a, b);

    printf("Result vector:\n");
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, ((float*)&c)[i]);
    }

    // Expected output:
    // c[0] = 3.0 (a2)
    // c[1] = 7.0 (b2)
    // c[2] = 4.0 (a3)
    // c[3] = 8.0 (b3)
    ASSERT(1, c[0]);
    ASSERT(5, c[1]);
    ASSERT(2, c[2]);
    ASSERT(6, c[3]);

    printf("OK\n");
    return 0;
}
