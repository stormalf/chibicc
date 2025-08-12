#include "test.h"

typedef float __m128 __attribute__((vector_size(16)));
typedef int __v2si __attribute__((vector_size(16)));

int main(void) {
    __m128 a = {1.0f, 2.0f, 3.0f, 4.0f};
    __m128 b = {5.0f, 6.0f, 7.0f, 8.0f};
    __v2si mask = {0,4,2,7};
    __m128 r = __builtin_shuffle(a, b, mask);

    float *f = (float*)&r;
    printf("%f %f %f %f\n", f[0], f[1], f[2], f[3]);
    ASSERT(1, f[0]);
    ASSERT(5, f[1]);
    ASSERT(3, f[2]);
    ASSERT(8, f[3]);

    printf("OK\n");
    return 0;
}
