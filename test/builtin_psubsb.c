#include "test.h"

typedef char v8qi __attribute__((vector_size(8)));

int main() {
    v8qi a = {100, 50, -100, -50, 127, -128, 10, -10};
    v8qi b = {50, 100, -50, -100, 1, 1, 20, 20};

    v8qi result = __builtin_ia32_psubsb(a, b);

    for (int i = 0; i < 8; i++) {
        printf("%d ", (int)result[i]);
    }
    printf("\n");

    ASSERT(100, a[0]);
    ASSERT(50, a[1]);
    ASSERT(-100, a[2]);
    ASSERT(-50, a[3]);
    ASSERT(127, a[4]);
    ASSERT(-128, a[5]);
    ASSERT(10, a[6]);
    ASSERT(-10, a[7]);
    ASSERT(50, b[0]);
    ASSERT(100, b[1]);
    ASSERT(-50, b[2]);
    ASSERT(-100, b[3]);
    ASSERT(1, b[4]);
    ASSERT(1, b[5]);
    ASSERT(20, b[6]);
    ASSERT(20, b[7]);
    ASSERT(50, (int) result[0]);
    ASSERT(-50, (int) result[1]);
    ASSERT(-50, (int) result[2]);
    ASSERT(50, (int) result[3]);
    ASSERT(126, (int) result[4]);
    ASSERT(-128, (int) result[5]);
    ASSERT(-10, (int) result[6]);
    ASSERT(-30, (int) result[7]);
    printf("OK\n");

    return 0;
}
