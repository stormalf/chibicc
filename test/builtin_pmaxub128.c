#include "test.h"

typedef unsigned char uchar16 __attribute__((vector_size(16)));
typedef char char16 __attribute__((vector_size(16)));

int main() {
    char16 a = {1, 200, 3, 150, 5, 250, 7, 100, 9, 50, 11, 25, 13, 75, 15, 0};
    char16 b = {100, 50, 200, 100, 150, 0, 50, 200, 250, 25, 5, 255, 0, 100, 20, 10};

    uchar16 c = (uchar16)__builtin_ia32_pmaxub128(a, b); // unsigned max per 8-bit lane

    for(int i = 0; i < 16; i++) {
        printf("%u ", c[i]);
    }
    printf("\n");
    ASSERT(100, c[0]);
    ASSERT(200, c[1]);
    ASSERT(200, c[2]);
    ASSERT(150, c[3]);
    ASSERT(150, c[4]);
    ASSERT(250, c[5]);
    ASSERT(50, c[6]);
    ASSERT(200, c[7]);
    ASSERT(250, c[8]);
    ASSERT(50, c[9]);
    ASSERT(11, c[10]);
    ASSERT(255, c[11]);
    ASSERT(13, c[12]);
    ASSERT(100, c[13]);
    ASSERT(20, c[14]);
    ASSERT(10, c[15]);
    printf("OK\n");
    return 0;
}
