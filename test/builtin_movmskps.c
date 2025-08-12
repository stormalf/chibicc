#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

// Declare the builtin directly
int __builtin_ia32_movmskps(v4sf a);

int main(void) {
    v4sf vec = { 1.0f, -2.0f, 3.0f, -4.0f };

    // movmskps should produce a 4-bit mask of sign bits
    // bit0 = sign of vec[0], bit1 = sign of vec[1], etc.
    int mask = __builtin_ia32_movmskps(vec);

    printf("Vector: %f %f %f %f\n", vec[0], vec[1], vec[2], vec[3]);
    printf("Mask: %d (binary %04b)\n", mask, mask);

    // Expected:
    // vec[0] > 0 => bit0 = 0
    // vec[1] < 0 => bit1 = 1
    // vec[2] > 0 => bit2 = 0
    // vec[3] < 0 => bit3 = 1
    // So mask = 0b1010 = 10
    ASSERT(10, mask);
    ASSERT(1, vec[0]);
    ASSERT(-2, vec[1]);
    ASSERT(3, vec[2]);
    ASSERT(-4, vec[3]);
    printf("OK\n");
    return 0;
}
