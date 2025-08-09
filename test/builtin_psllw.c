#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a     = (v4hi){1, 2, 3, 4};   // v4hi
    v4hi count = (v4hi){1, 1, 1, 1};   // shift each by 1 bit

    v4hi result = __builtin_ia32_psllw(a, count);

    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%d ", a[i]);
        ASSERT(i + 1, a[i]);
    }

    for (int i = 0; i < 4; i++) {
        printf("%d ", count[i]);
        ASSERT(1, count[i]);
    }


    ASSERT(0, result[0]);
    ASSERT(0, result[1]);
    ASSERT(0, result[2]);
    ASSERT(0, result[3]);

    printf("OK\n");

    return 0;
}

