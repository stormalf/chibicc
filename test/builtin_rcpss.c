#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

v4sf __builtin_ia32_rcpss(v4sf a);

int main() {
    v4sf a = {4.0f, 0, 0, 0};
    v4sf r = __builtin_ia32_rcpss(a);
    float approx_reciprocal = ((float*)&r)[0];

    // The reciprocal of 4.0f is 0.25, approximate result will be close.
    printf("approx reciprocal: %f\n", approx_reciprocal);
    ASSERT(0, r[0]);
    ASSERT(0, r[1]);
    ASSERT(0, r[2]);
    ASSERT(0, r[3]);
    printf("OK\n");
    return 0;
}
