#include "test.h"

typedef double double2 __attribute__((vector_size(16))); // 2 doubles

int main(void) {
    double2 a = {1.0, 2.0};  // xmm0: low=1.0, high=2.0
    double b = 99.0;
    double2 r = __builtin_ia32_loadhpd(a, &b);

    printf("r[0] = %.1f\n", r[0]); // from low of a (1.0)
    printf("r[1] = %.1f\n", r[1]); // from low of b (3.0)

    ASSERT(1, r[0]);
    ASSERT(99, r[1]);
    printf("OK\n");
    return 0;
}
