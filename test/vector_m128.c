#include <xmmintrin.h>
#include "test.h"

int main() {
    __m128 a = _mm_set_ps(4, 3, 2, 1);
    __m128 b = _mm_add_ps(a, a);
    float *f = (float *)&b;
    printf("%f %f %f %f\n", f[0], f[1], f[2], f[3]);
    ASSERT(2, f[0]);
    ASSERT(4, f[1]);
    ASSERT(6, f[2]);
    ASSERT(8, f[3]);
    printf("OK\n");
    return 0;
}
