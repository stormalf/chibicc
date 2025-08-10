
#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.5f, 2.5f, 3.5f, 4.5f};
    v4sf b = {1.5f, 2.0f, 4.0f, 5.0f};

    v4sf c = __builtin_ia32_cmpless(a, b);

    printf("c[0] = 0x%X\n", *(unsigned int*)&c[0]);  // expect 0xFFFFFFFF because 1.5 <= 1.5
    printf("c[1] = %f\n", c[1]);  // expect 2.5 (copied from a)
    printf("c[2] = %f\n", c[2]);  // expect 3.5
    printf("c[3] = %f\n", c[3]);  // expect 4.5

    ASSERT(-2147483648, c[0]);
    ASSERT(2, c[1]);
    ASSERT(3, c[2]);
    ASSERT(4, c[3]);

    printf("OK\n");

    return 0;
}
