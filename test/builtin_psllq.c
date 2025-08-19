#include "test.h"

typedef long long __m64 __attribute__((vector_size(8)));

int main() {
    __m64 a = (__m64){0x1000LL};
    __m64 count = (__m64){4};  // shift left by 4 bits

    __m64 result = __builtin_ia32_psllq(a, count);

    printf("0x%llx\n", (unsigned long long)result[0]);
    // Expected output: 0x10000 (0x1000 << 4)
    ASSERT(0x10000, result[0]);
    printf("OK\n");
    return 0;
}
