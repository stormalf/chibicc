#include "test.h"

typedef double double2 __attribute__((vector_size(16)));

int main() {
    double2 a = {4.0, 9.0};
    double2 b = __builtin_ia32_sqrtsd(a);

    printf("sqrtsd: %.1f %.1f\n", b[0], b[1]); // Expected: 2.0 3.0
    ASSERT(2, b[0]);
    ASSERT(9, b[1]);
    printf("OK\n");
    return 0;
}
