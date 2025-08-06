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
    printf("c = %f %f\n", c[0], c[1]);
    ASSERT(4, (int)c[0]);
    ASSERT(6, (int)c[1]);
}
