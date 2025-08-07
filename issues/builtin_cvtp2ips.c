#include <xmmintrin.h>
#include "test.h"

int main() {
    __m64 b = (__m64){1, 2};                      // two ints
    __m128 a = (__m128){100.0f, 200.0f, 300.0f, 400.0f};

    __m128 result = __builtin_ia32_cvtpi2ps(a, b);

    float *f = (float *)&result;
    printf("%f %f %f %f\n", f[0], f[1], f[2], f[3]);  // 1.0 2.0 300.0 400.0

    return 0;
}
