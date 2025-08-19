#include "test.h"

typedef unsigned char uchar16 __attribute__((vector_size(16)));
typedef char char16 __attribute__((vector_size(16)));

int main() {
    char16 a = {1, 200, 3, 150, 5, 250, 7, 100, 9, 50, 11, 25, 13, 75, 15, 0};
    char16 b = {100, 50, 200, 100, 150, 0, 50, 200, 250, 25, 5, 255, 0, 100, 20, 10};

    uchar16 c = (uchar16)__builtin_ia32_pminub128(a, b); // unsigned min per 8-bit lane

    for(int i = 0; i < 16; i++) {
        printf("%u ", c[i]);
    }
    printf("\n");

    ASSERT(1, c[0]);
    ASSERT(50, c[1]);
    ASSERT(3, c[2]);
    ASSERT(100, c[3]);
    ASSERT(5, c[4]);
    ASSERT(0, c[5]);
    ASSERT(7, c[6]);
    ASSERT(100, c[7]);
    ASSERT(9, c[8]);
    ASSERT(25, c[9]);
    ASSERT(5, c[10]);
    ASSERT(25, c[11]);
    ASSERT(0, c[12]);
    ASSERT(75, c[13]);
    ASSERT(15, c[14]);
    ASSERT(0, c[15]);

    printf("OK\n");
    return 0;
}
