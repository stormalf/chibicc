#include "test.h"

typedef double double2 __attribute__((vector_size(16))); // 2 doubles

int main(void) {
    double2 a = {1.0, 2.0};  // xmm0: low=1.0, high=2.0
    double2 b = {3.0, 4.0};  // xmm1: low=3.0, high=4.0
    double2 r = __builtin_ia32_unpckhpd(a, b);

    printf("r[0] = %.1f\n", r[0]); // from high of a (2.0)
    printf("r[1] = %.1f\n", r[1]); // from high of b (4.0)

    ASSERT(2, r[0]);
    ASSERT(4, r[1]);
    printf("OK\n");
    return 0;
}
