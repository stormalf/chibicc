#include "test.h"

typedef double double2 __attribute__((vector_size(16)));

double2 add_double2(double2 a, double2 b) {
    return a + b;
}

int main() {
    double2 a = {1.1, 2.2};
    double2 b = {3.3, 4.4};
    double2 c ;
    c = add_double2(a, b);
    double2 d = add_double2(a, c);
    printf("c = %f %f\n", c[0], c[1]);
    ASSERT(4, (int)c[0]);
    ASSERT(6, (int)c[1]);
    printf("d = %f %f\n", d[0], d[1]);
    ASSERT(5, d[0]);
    ASSERT(8, d[1]);
    return 0;
}
