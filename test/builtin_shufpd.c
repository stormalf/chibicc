#include "test.h"

#define _MM_SHUFFLE(z, y, x, w) \
  (((z) << 6) | ((y) << 4) | ((x) << 2) | (w))

typedef double __m128 __attribute__((vector_size(16)));

int main(void) {
    __m128 a = {1.0f, 2.0f};
    __m128 b = {5.0f, 6.0f};
    __m128 r = __builtin_ia32_shufpd(a, b, _MM_SHUFFLE(0,1,2,3));

    float *f = (float*)&r;
    printf("%f %f\n", f[0], f[1]);
    ASSERT(0, f[0]);
    ASSERT(2, f[1]);

    r = __builtin_ia32_shufpd(a, b, 27);
    ASSERT(0, f[0]);
    ASSERT(2, f[1]);


    printf("OK\n");
    return 0;
}
