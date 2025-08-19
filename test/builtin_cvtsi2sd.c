#include "test.h"

typedef double float2 __attribute__((vector_size(16)));

int main(void) {
    float2 v = {0.0, 1.0}; // 2 doubles
    int x = 42;

    // Convert int x to double and store in the lowest element of v
    v = __builtin_ia32_cvtsi2sd(v, x);

    printf("v = {%.1f, %.1f}\n", v[0], v[1]);

    // Expected output:
    // v[0] = 42.0  (converted from x)
    // v[1] = 1.0   (unchanged)
    ASSERT(42, v[0]);
    ASSERT(1, v[1]);
    printf("OK\n");

    return 0;
}
