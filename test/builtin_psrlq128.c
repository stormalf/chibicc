#include "test.h"

typedef long long  v2li __attribute__((vector_size(16)));

int main() {
    v2li a = {1, 2,};
    v2li b = {1, 0};
    v2li c = __builtin_ia32_psrlq128(a, b); // shift each 32-bit element right by 1

    for(int i = 0; i < 2; i++) {
        printf("%lld ", c[i]);
    }
    printf("\n");

    ASSERT(0, c[0]);
    ASSERT(1, c[1]);

    printf("OK\n");
    return 0;
}
