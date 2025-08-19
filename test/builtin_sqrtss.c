#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf va = {16.0f, 3.3f, 4.4f, 5.5f};

    v4sf vc = __builtin_ia32_sqrtss(va);

    float result = ((float*)&vc)[0];

    printf("result = %f\n", result);  // Expected: sqrt(16.0) = 4.0

    // Check lowest element is correct (scalar sqrt)
    ASSERT(4, result);

    // The other elements should be copied from the input vector (va)
    ASSERT(4, vc[0]);
    ASSERT(3, vc[1]);
    ASSERT(4, vc[2]);
    ASSERT(5, vc[3]);
    printf("OK\n");

    return 0;
}
