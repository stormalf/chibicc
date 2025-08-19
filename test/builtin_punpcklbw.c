#include "test.h"

typedef char v8qi __attribute__((vector_size(8))); // 8 bytes vector

int main() {
    v8qi a = {1,2,3,4,5,6,7,8};
    v8qi b = {10,20,30,40,50,60,70,80};

    v8qi result = __builtin_ia32_punpcklbw(a, b);

    for (int i = 0; i < 8; i++) {
        printf("%d ", (int)result[i]);
    }
    ASSERT(1, a[0]);
    ASSERT(2, a[1]);
    ASSERT(3, a[2]);
    ASSERT(4, a[3]);
    ASSERT(5, a[4]);
    ASSERT(6, a[5]);
    ASSERT(7, a[6]);
    ASSERT(8, a[7]);

    ASSERT(10, b[0]);
    ASSERT(20, b[1]);
    ASSERT(30, b[2]);
    ASSERT(40, b[3]);
    ASSERT(50, b[4]);
    ASSERT(60, b[5]);
    ASSERT(70, b[6]);
    ASSERT(80, b[7]);

    ASSERT(1, result[0]);
    ASSERT(10, result[1]);
    ASSERT(2, result[2]);
    ASSERT(20, result[3]);
    ASSERT(3, result[4]);
    ASSERT(30, result[5]);
    ASSERT(4, result[6]);
    ASSERT(40, result[7]);
    printf("OK\n");

    return 0;
}
