#include "test.h"

#define _MM_SHUFFLE(z, y, x, w) \
  (((z) << 6) | ((y) << 4) | ((x) << 2) | (w))

typedef float __m128 __attribute__((vector_size(16)));

int main(void) {
    __m128 a = {1.0f, 2.0f, 3.0f, 4.0f};
    __m128 b = {5.0f, 6.0f, 7.0f, 8.0f};
    __m128 r = __builtin_ia32_shufps(a, b, _MM_SHUFFLE(0,1,2,3));

    float *f = (float*)&r;
    printf("%f %f %f %f\n", f[0], f[1], f[2], f[3]);
    ASSERT(4, f[0]);
    ASSERT(3, f[1]);
    ASSERT(6, f[2]);
    ASSERT(5, f[3]);
    r = __builtin_ia32_shufps(a, b, 27);
    ASSERT(4, f[0]);
    ASSERT(3, f[1]);
    ASSERT(6, f[2]);
    ASSERT(5, f[3]);

    printf("OK\n");
    return 0;
}
