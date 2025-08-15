#include "test.h"

typedef short short16 __attribute__((vector_size(16)));

int main() {
    short16 a = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    short16 b = {1, 0, 1, 0, 1, 0, 1, 0};
    short16 c = __builtin_ia32_psrlw128(a, b); // shift each 16-bit element right by 3

    for(int i = 0; i < 8; i++) {
        printf("%d ", c[i]);
        ASSERT(0, c[i]);
    }
    printf("\n");

    printf("OK\n");
    return 0;
}
