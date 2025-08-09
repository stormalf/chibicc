#include "test.h"

typedef long long __m64;               // minimal __m64 definition
typedef short v4hi __attribute__((vector_size(8)));

int main(void) {
    v4hi a = {1, 2, 3, 4};

    // reinterpret v4hi as __m64 for builtin
    __m64 am = (__m64)a;

    // shift each 16-bit element left by 1 (immediate form)
    __m64 rm = (__m64)__builtin_ia32_psllwi(a, 1);

    // reinterpret back to vector for printing
    v4hi result = (v4hi)rm;
    for (int i = 0; i < 4; i++) {
        printf("%d ", a[i]);
        ASSERT(i+1, a[i]);
    }
    

    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    ASSERT(2, result[0]);
    ASSERT(4, result[1]);
    ASSERT(6, result[2]);
    ASSERT(8, result[3]);
    printf("OK\n");

    return 0;
}