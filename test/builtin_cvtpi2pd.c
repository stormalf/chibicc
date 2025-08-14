#include "test.h"

typedef int  mm64 __attribute__((vector_size(8))); // MMX 64-bit
typedef double v2df __attribute__((vector_size(16)));  // 2 doubles

v2df test_cvtpi2pd(mm64 a) {
    return __builtin_ia32_cvtpi2pd(a);
}

int main(void) {
    mm64 input = { 3, -2 }; // two 32-bit integers
    v2df output = test_cvtpi2pd(input);
    printf("%.1f %.1f\n", output[0], output[1]);

    ASSERT(3, output[0]);
    ASSERT(-2, output[1]);

    printf("OK\n");
    return 0;
}
