#include "test.h"

typedef int int4 __attribute__((vector_size(16)));

int main() {
    int4 a = {1, 2, 3, 4};
    int4 b = {1, 0, 1, 0};
    int4 c = __builtin_ia32_psrld128(a, b); // shift each 32-bit element right by 1

    for(int i = 0; i < 4; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    ASSERT(0, c[0]);
    ASSERT(1, c[1]);
    ASSERT(1, c[2]);
    ASSERT(2, c[3]);

    printf("OK\n");
    return 0;
}
