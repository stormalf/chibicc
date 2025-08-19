#include "test.h"

typedef  int __m128i __attribute__((vector_size(16)));

int main() {
    __m128i a =  {1, 2, 3, 4};
    __m128i b =  {1, 0, 0, 0};
    __m128i c = __builtin_ia32_pslld128(a, b);  // shift left each 32-bit element by 1


    printf("%d %d %d %d\n", c[0], c[1], c[2], c[3]);
    ASSERT(2, c[0]);
    ASSERT(4, c[1]);
    ASSERT(6, c[2]);
    ASSERT(8, c[3]);
    printf("OK\n");
    return 0;
}
