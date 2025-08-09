#include "test.h"

typedef long long __m64 __attribute__((vector_size(8)));
typedef int __v1di __attribute__((vector_size(8)));

// Forward declaration of the intrinsic (usually built-in by compiler)
__m64 __builtin_ia32_psllqi(__m64 a, int count);

int main() {
    __m64 a = (__m64){0x123456789abcdef0LL}; // sample 64-bit value packed in __m64
    int count = 1; // shift left by 1 bit

    __m64 result = __builtin_ia32_psllqi(a, count);


    // Print result as 64-bit integer (cast vector to long long)
    long long *p = (long long*)&result;
    printf("Result after psllqi by %d: 0x%llx\n", count, p[0]);

    ASSERT(897170912, result[0]);

    __m64 result = __builtin_ia32_psllqi(a, 1);

    ASSERT(897170912, result[0]);

    printf("OK\n");
    return 0;
}
