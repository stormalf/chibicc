#include "test.h"

typedef char v8qi __attribute__((vector_size(8)));

int main() {
    v8qi a = {1, 2, 3, 4, 5, 6, 7, 8};
    v8qi b = {10, 20, 30, 40, 50, 60, 70, 80};

    v8qi result = __builtin_ia32_paddb(a, b);

    for (int i = 0; i < 8; i++) {
        printf("%d ", (int)result[i]);
    }
    
    for (int i = 0; i < 8; i++) {
        printf("%d ", (int)a[i]);
        ASSERT(i + 1, a[i]);
    }
    for (int i = 0; i < 8; i++) {
        printf("%d ", (int)b[i]);
        ASSERT((i + 1) * 10 , b[i]);
    }

    ASSERT(11, result[0]);
    ASSERT(22, result[1]);
    ASSERT(33, result[2]);
    ASSERT(44, result[3]);
    ASSERT(55, result[4]);
    ASSERT(66, result[5]);
    ASSERT(77, result[6]);
    ASSERT(88, result[7]);

    printf("OK\n");

    return 0;
}
