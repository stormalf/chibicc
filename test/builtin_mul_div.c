#include "test.h"

typedef double double2 __attribute__((vector_size(16)));

int main() {
    double2 a = {10.0, 7.0};
    double2 b = {5.0, 4.0};
    double2 c = __builtin_ia32_mulsd(a, b);
    double2 d = __builtin_ia32_divsd(a, b);

    printf("%.1f %.1f\n", c[0], c[1]); 
    printf("%.1f %.1f\n", d[0], d[1]); 

    ASSERT(50, c[0]);
    ASSERT(7, c[1]);

    ASSERT(2, d[0]);
    ASSERT(7, d[1]);
    printf("OK\n");
    return 0;
}
