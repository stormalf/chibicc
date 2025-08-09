
#include "test.h"

typedef char v8qi __attribute__((vector_size(8)));

int main(void) {
    v8qi a = {100, -50, 30, -128, 10, 20, 30, 40};
    v8qi b = {50, 50, -30, 1, 5, 5, 5, 5};

    v8qi result = (v8qi)__builtin_ia32_psubb(a, b);

    for (int i = 0; i < 8; i++)
        printf("%d ", result[i]);
    ASSERT(100, a[0]);
    ASSERT(-50, a[1]);
    ASSERT(30, a[2]);
    ASSERT(-128, a[3]);
    ASSERT(10, a[4]);
    ASSERT(20, a[5]);
    ASSERT(30, a[6]);
    ASSERT(40, a[7]);
    ASSERT(50, b[0]);
    ASSERT(50, b[1]);
    ASSERT(-30, b[2]);
    ASSERT(1, b[3]);
    ASSERT(5, b[4]);
    ASSERT(5, b[5]);
    ASSERT(5, b[6]);
    ASSERT(5, b[7]);

    ASSERT(50, result[0]);
    ASSERT(-100, result[1]);
    ASSERT(60, result[2]);
    ASSERT(127, result[3]);
    ASSERT(5, result[4]);
    ASSERT(15, result[5]);
    ASSERT(25, result[6]);
    ASSERT(35, result[7]);
    
    printf("\n");
    printf("OK\n");
}
