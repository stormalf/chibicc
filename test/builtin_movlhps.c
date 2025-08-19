#include "test.h"
#include <stdint.h>

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {5.0f, 6.0f, 7.0f, 8.0f};

    // movlhps moves low 64 bits (2 floats) from b into high 64 bits of a
    v4sf c = __builtin_ia32_movlhps(a, b);

    printf("Result vector:\n");
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, c[i]);
    }

    // Expected:
    // c[0] = a[0] = 1.0
    // c[1] = a[1] = 2.0
    // c[2] = b[0] = 5.0
    // c[3] = b[1] = 6.0
    ASSERT(1, c[0]);
    ASSERT(2, c[1]);
    ASSERT(5, c[2]);
    ASSERT(6, c[3]);

    return 0;
}
