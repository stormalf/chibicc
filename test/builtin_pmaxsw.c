#include "test.h"

// Define a 4-element short vector type (like __v4hi)
typedef short v4hi __attribute__((vector_size(8)));


int main(void) {
    v4hi a = {10, 20, 30, 40};
    v4hi b = {15, 15, 35, 35};
    v4hi c = __builtin_ia32_pmaxsw(a, b);

    printf("Result: %hd %hd %hd %hd\n", c[0], c[1], c[2], c[3]);
    // Expected output: 15 20 35 40
    ASSERT(15, c[0]);
    ASSERT(20, c[1]);
    ASSERT(35, c[2]);
    ASSERT(40, c[3]);
    printf("OK\n");
    return 0;
}
