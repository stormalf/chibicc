#include "test.h"

typedef float float4 __attribute__((vector_size(16)));
typedef double double2 __attribute__((vector_size(16)));

int main(void) {
    float4 a = {1.5f, -2.25f, 5.4f, 7.8f};

    // Convert two floats to two doubles
    double2 b = __builtin_ia32_cvtps2pd(a);

    printf("a = {%.2f, %.2f, %.2f, %.2f}\n", a[0], a[1], a[2], a[3]);
    printf("b = {%.2lf, %.2lf}\n", b[0], b[1]);

    ASSERT(1, b[0]);
    ASSERT(-2, b[1]);
    printf("OK\n");
    return 0;
}
