#include "test.h"
#include <stdint.h>

typedef unsigned char v16u8 __attribute__((vector_size(16)));
typedef char v16i8 __attribute__((vector_size(16)));

int main() {
    v16i8 a = {1, 2, 3, 4, 5, 6, 7, 8,
               9,10,11,12,13,14,15,16};
    v16i8 b = {100,101,102,103,104,105,106,107,
               108,109,110,111,112,113,114,115};

    v16u8 result = (v16u8)__builtin_ia32_punpcklbw128(a, b);

    unsigned char *p = (unsigned char *)&result;
    for (int i = 0; i < 16; i++)
        printf("%d ", p[i]);
    printf("\n");

    ASSERT(1, p[0]);
    ASSERT(100, p[1]);
    ASSERT(2, p[2]);
    ASSERT(101, p[3]);
    ASSERT(3, p[4]);
    ASSERT(102, p[5]);
    ASSERT(4, p[6]);
    ASSERT(103, p[7]);
    ASSERT(5, p[8]);
    ASSERT(104, p[9]);
    ASSERT(6, p[10]);
    ASSERT(105, p[11]);
    ASSERT(7, p[12]);
    ASSERT(106, p[13]);
    ASSERT(8, p[14]);
    ASSERT(107, p[15]);

    printf("OK\n");
    return 0;
}
