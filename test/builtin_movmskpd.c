#include "test.h"

typedef double double2 __attribute__((vector_size(16))); // 2 doubles
typedef float v4sf __attribute__((vector_size(16)));

int main(void) {
    v4sf vec = { 1.0f, -2.0f, 3.0f, -4.0f };

    // movmskps should produce a 4-bit mask of sign bits
    // bit0 = sign of vec[0], bit1 = sign of vec[1], etc.
    double mask = __builtin_ia32_movmskps(vec);

    printf("vec[0] = %.1f\n", vec[0]); 
    printf("vec[1] = %.1f\n", vec[1]); 

    ASSERT(10, mask);
    printf("OK\n");
    return 0;
}
