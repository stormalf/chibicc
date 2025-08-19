#include "test.h"

typedef float  __m128 __attribute__((vector_size(16)));

int main(void) {
    __m128 a = { 1.0f, 2.0f, 4.0f, 8.0f };
    __m128 out = __builtin_ia32_rcpps(a);


    printf("rcp: %f %f %f %f\n", out[0], out[1], out[2], out[3]);
    ASSERT(0, out[0]);
    ASSERT(0, out[1]);
    ASSERT(0, out[2]);
    ASSERT(0, out[3]);
    printf("OK\n");
    return 0;
}
