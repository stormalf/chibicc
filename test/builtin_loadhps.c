#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));
typedef float v2sf __attribute__((vector_size(8)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v2sf p = {5.0f, 6.0f};

    v4sf c = __builtin_ia32_loadhps(a, &p);

    printf("Result vector:\n");
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, ((float*)&c)[i]);
    }

    // Expected:
    // c[0] = 1.0
    // c[1] = 2.0
    // c[2] = 5.0
    // c[3] = 6.0

    ASSERT(1, c[0]);
    ASSERT(2, c[1]);
    ASSERT(5, c[2]);
    ASSERT(6, c[3]);
    printf("OK\n");

    return 0;
}
