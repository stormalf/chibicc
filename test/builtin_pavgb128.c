#include "test.h"

typedef unsigned char uchar16 __attribute__((vector_size(16)));
typedef char char16 __attribute__((vector_size(16)));

int main() {
    char16 a = {100, 200, 255, 0,   1,  50, 128,  64,
                 5,  250, 100, 30, 200, 100,  1,  255};
    char16 b = {100,  55,  10, 0, 255, 200, 127, 192,
                 250,  10, 100, 30, 100, 200, 254, 255};

    uchar16 c = (uchar16)__builtin_ia32_pavgb128(a, b);

    for (int i = 0; i < 16; i++)
        printf("%u ", c[i]);
    printf("\n");
    ASSERT(100, c[0]);
    ASSERT(128, c[1]);
    ASSERT(133, c[2]);
    ASSERT(0, c[3]);
    ASSERT(128, c[4]);
    ASSERT(125, c[5]);
    ASSERT(128, c[6]);
    ASSERT(128, c[7]);
    ASSERT(128, c[8]);
    ASSERT(130, c[9]);
    ASSERT(100, c[10]);
    ASSERT(30, c[11]);
    ASSERT(150, c[12]);
    ASSERT(150, c[13]);
    ASSERT(128, c[14]);
    ASSERT(255, c[15]);

    printf("OK\n");
    return 0;
}
