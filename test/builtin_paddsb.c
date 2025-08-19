#include "test.h"

typedef char v8qi __attribute__((vector_size(8)));

int main() {
    v8qi a = {120, -120, 100, -100, 50, -50, 127, -128};
    v8qi b = {10, -10, 50, -50, 100, -100, 1, -1};

    v8qi result = (v8qi) __builtin_ia32_paddsb(a, b);

    for (int i = 0; i < 8; i++)
        printf("%d ", result[i]);
   
    ASSERT(120, a[0]);
    ASSERT(-120, a[1]);
    ASSERT(100, a[2]);
    ASSERT(-100, a[3]);
    ASSERT(50, a[4]);
    ASSERT(-50, a[5]);
    ASSERT(127, a[6]);
    ASSERT(-128, a[7]);
    ASSERT(10, b[0]);
    ASSERT(-10, b[1]);
    ASSERT(50, b[2]);
    ASSERT(-50, b[3]);
    ASSERT(100, b[4]);
    ASSERT(-100, b[5]);
    ASSERT(1, b[6]);
    ASSERT(-1, b[7]);

    ASSERT(127, result[0]);
    ASSERT(-128, result[1]);
    ASSERT(127, result[2]);
    ASSERT(-128, result[3]);
    ASSERT(127, result[4]);
    ASSERT(-128, result[5]);
    ASSERT(127, result[6]);
    ASSERT(-128, result[7]);
    printf("OK\n");

    return 0;
}
