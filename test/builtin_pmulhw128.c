#include "test.h"

typedef short v8hi __attribute__((vector_size(16)));

int main() {
    // Two sets of signed 16-bit integers (8 elements in 128 bits)
    v8hi  a = {3000, -3000, 10000, -10000, 12345, -12345, 20000, -20000};
    v8hi b = {2, 3, -2, -3, 4, -4, 5, -5};

    // Multiply and keep the high 16 bits
    v8hi vc = __builtin_ia32_pmulhw128(a, b); // intrinsic for PMULHW


    // Print results
    printf("Result: ");
    for (int i = 0; i < 8; i++)
        printf("%d ", vc[i]);
    printf("\n");

    ASSERT(0, vc[0]);
    ASSERT(-1, vc[1]);
    ASSERT(-1, vc[2]);
    ASSERT(0, vc[3]);
    ASSERT(0, vc[4]);
    ASSERT(0, vc[5]);
    ASSERT(1, vc[6]);
    ASSERT(1, vc[7]);
    printf("OK\n");

    return 0;
}
