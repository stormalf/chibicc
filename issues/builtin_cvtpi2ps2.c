#include <xmmintrin.h>
#include "test.h"

int main() {
    __m128 a = (__m128){100.0f, 200.0f, 300.0f, 400.0f}; // upper 2 will be kept
    __m64  b = (__m64){1, 2};                           // lower 2 will be converted to float
    printf("a = %f %f %f %f\n", a[0], a[1], a[2], a[3]);
    ASSERT(100, a[0]);
    ASSERT(200, a[1]);
    ASSERT(300, a[2]);
    ASSERT(400, a[3]);
    int *p = (int *)&b;
    printf("b = %d %d\n", p[0], p[1]);  // Correct: 1 2
    ASSERT(1, p[0]);
    ASSERT(2, p[1]);
    float *p2 = (float *)&a;

     __m128 result = __builtin_ia32_cvtpi2ps(a, b);

    float *f = (float *)&result;
    printf("%f %f %f %f\n", f[0], f[1], f[2], f[3]);
    ASSERT(1, f[0]);
    ASSERT(2, f[1]);
    ASSERT(300, f[2]);
    ASSERT(400, f[3]);
    return 0;
}
