#include "test.h"

typedef double double2 __attribute__((vector_size(16)));

int main() {
    double2 a = {1.0, 2.0};
    double2 b = {3.0, 4.0};
    double2 c = __builtin_ia32_addsd(a, b);

    printf("%.1f %.1f\n", c[0], c[1]); // Expected: 4.0 2.0
    ASSERT(4, c[0]);
    ASSERT(2, c[1]);
    printf("OK\n");
    return 0;
}
