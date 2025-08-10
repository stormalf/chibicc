#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    // Initialize full 4-float vectors
    v4sf va = {1.5f, 3.3f, 4.4f, 5.5f};
    v4sf vb = {2.5f, 6.7f, 3.6f, 7.5f};

    // Perform scalar single-float addition on lowest elements
    v4sf vc = __builtin_ia32_addss(va, vb);

    // Extract the scalar result (lowest float)
    float result = ((float*)&vc)[0];

    printf("result = %f\n", result); // Should print 4.0
    ASSERT(4, vc[0]);
    ASSERT(3, vc[1]);
    ASSERT(4, vc[2]);
    ASSERT(5, vc[3]);
    ASSERT(4, result);

    return 0;
}
