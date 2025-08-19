#include "test.h"
#include <stdint.h>

typedef long long v2di __attribute__((vector_size(16)));

v2di test_psllq_i128(v2di a) {
    // Equivalent to: return __builtin_ia32_psllqi128(a, 2);
    return __builtin_ia32_psllqi128(a, 2);
}

int main() {
    v2di a = {1, 2};   // Two 64-bit integers
    v2di b = test_psllq_i128(a);
    printf("%lld %lld\n", b[0], b[1]);
    ASSERT(4, b[0]);
    ASSERT(8, b[1]);
    printf("OK\n");
    return 0;
}
