#include "test.h"

// Declare the builtin manually (so we don't need xmmintrin.h)
int __builtin_ia32_cvtss2si(__attribute__((vector_size(16))) float v);

int main(void) {
    // Create a vector of 4 floats (matches __v4sf)
    __attribute__((vector_size(16))) float vec = { 42.5f, 2.0f, -3.0f, 99.0f };

    // Convert the lowest element to int
    int result = __builtin_ia32_cvtss2si(vec);

    printf("Input[0] = %.2f -> int = %d\n", vec[0], result);


    ASSERT(42, vec[0]);
    ASSERT(42, result);
    printf("OK\n");
    return 0;
}
