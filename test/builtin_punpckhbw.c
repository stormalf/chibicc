#include "test.h"

typedef char v8qi __attribute__((vector_size(8)));

int main() {
    v8qi a = {0,1,2,3,4,5,6,7};
    v8qi b = {10,11,12,13,14,15,16,17};

    v8qi result = (v8qi)__builtin_ia32_punpckhbw(a, b);

    for (int i = 0; i < 8; i++) {
        printf("%u ", (unsigned int)result[i]);
    }
    ASSERT(0, a[0]);
    ASSERT(1, a[1]);
    ASSERT(2, a[2]);
    ASSERT(3, a[3]);
    ASSERT(4, a[4]);
    ASSERT(5, a[5]);
    ASSERT(6, a[6]);
    ASSERT(7, a[7]);
    ASSERT(10, b[0]);
    ASSERT(11, b[1]);
    ASSERT(12, b[2]);
    ASSERT(13, b[3]);
    ASSERT(14, b[4]);
    ASSERT(15, b[5]);
    ASSERT(16, b[6]);
    ASSERT(17, b[7]);
    ASSERT(4, result[0]);
    ASSERT(14, result[1]);
    ASSERT(5, result[2]);
    ASSERT(15, result[3]);
    ASSERT(6, result[4]);
    ASSERT(16, result[5]);
    ASSERT(7, result[6]);
    ASSERT(17, result[7]);
    
    printf("OK\n");
    return 0;
}
