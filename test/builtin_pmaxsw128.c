#include "test.h"

typedef short short8 __attribute__((vector_size(16)));

int main() {
    short8 a = {1000, -2000, 3000, -4000, 5000, -6000, 7000, -8000};
    short8 b = {-1000, 2000, -3000, 4000, -5000, 6000, -7000, 8000};

    short8 c = __builtin_ia32_pmaxsw128(a, b); // signed max per lane

    for(int i = 0; i < 8; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    ASSERT(1000, c[0]);
    ASSERT(2000, c[1]);
    ASSERT(3000, c[2]);
    ASSERT(4000, c[3]);
    ASSERT(5000, c[4]);
    ASSERT(6000, c[5]);
    ASSERT(7000, c[6]);
    ASSERT(8000, c[7]);
    printf("OK\n");
    return 0;
}
