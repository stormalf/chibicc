
#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {4.0f, 9.0f, 16.0f, 25.0f};

    // Compute approximate reciprocal square root of each element
    v4sf r = __builtin_ia32_rsqrtps(a);

    printf("Reciprocal square roots:\n");
    for (int i = 0; i < 4; i++) {
        printf("r[%d] = %f\n", i, r[i]);
    }

    ASSERT(0, r[0]);
    ASSERT(0, r[1]);
    ASSERT(0, r[2]);
    ASSERT(0, r[3]);
    printf("OK\n");
    return 0;
}
