#include "test.h"
// test/builtin_maskmovq.c
typedef char __m64 __attribute__((__vector_size__(8)));

__m64 a = { 1, 2 , 3, 4, 5, 6, 7, 8};
__m64 m = { -1, 0 , -1, 0, -1, 0, -1, 0};
char dst[8];

int main() {
    __builtin_ia32_maskmovq(a, m, dst);
    for (int i = 0; i < 8; i++)
      printf("%d ", dst[i]);
    ASSERT(1, dst[0]);
    ASSERT(0, dst[1]);
    ASSERT(3, dst[2]);
    ASSERT(0, dst[3]);
    ASSERT(5, dst[4]);
    ASSERT(0, dst[5]);
    ASSERT(7, dst[6]);
    ASSERT(0, dst[7]);


    printf("OK\n");
    return 0;
}
