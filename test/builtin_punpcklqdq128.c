#include "test.h"

typedef long long  __m128i __attribute__((vector_size(16)));
int main() {
    __m128i a = {4, 1}; // { low=1, high=4 }
    __m128i b = {8, 2}; // { low=2, high=8 }

    __m128i r = __builtin_ia32_punpcklqdq128(a, b);

    unsigned long long *vals = (unsigned long long *)&r;
    printf("%llu %llu\n", vals[0], vals[1]);
    // Expected: low64(a)=1, low64(b)=2 => {1, 2}
    ASSERT(4, r[0]);
    ASSERT(8, r[1]);
    printf("OK\n");
    return 0;
}
