#include "test.h"
typedef double __m128d __attribute__ ((__vector_size__ (16)));

int main(void) {
    __m128d a = {42.75f, 37.8f};

    // Convert double to int
    long long b = __builtin_ia32_cvtsd2si64(a);

    printf("a[0] = %.2lf, a[1] = %.2lf\n", a[0], a[1]);
    ASSERT(42, a[0]);
    ASSERT(37, a[1]);
    printf("b = %lld\n", b); // Expected: 43
    ASSERT(43, b);
    printf("OK\n");
    return 0;
}
