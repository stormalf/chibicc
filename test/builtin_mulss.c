#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf va = {1.5f, 3.3f, 4.4f, 5.5f};
    v4sf vb = {2.5f, 6.7f, 2.6f, 7.5f};

    v4sf vc = __builtin_ia32_mulss(va, vb);

    float result = ((float*)&vc)[0];

    printf("result = %f\n", result);  // Expected: 1.5 * 2.5 = 3.75

    // Check lowest element is correct (scalar mul)
    ASSERT(3, result);

    // The other elements should be copied from the first vector (va)
    ASSERT(3, vc[0]);
    ASSERT(3, vc[1]);
    ASSERT(4, vc[2]);
    ASSERT(5, vc[3]);

    printf("OK\n");
    return 0;
}
