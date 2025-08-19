#include "test.h"

typedef double double2 __attribute__((vector_size(16)));

int main() {
    double2 a = {5.0, 7.0};
    double2 b = {2.0, 4.0};
    double2 c = __builtin_ia32_subsd(a, b);

    printf("%.1f %.1f\n", c[0], c[1]); // Expected: 3.0 7.0

    ASSERT(3, c[0]);
    ASSERT(7, c[1]);
    printf("OK\n");
    return 0;
}
