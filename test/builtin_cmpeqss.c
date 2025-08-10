#include "test.h"
typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {1.0f, 0.0f, 0.0f, 0.0f};

    v4sf c = __builtin_ia32_cmpeqss(a, b);

    printf("c[0] = 0x%X\n", *(unsigned int*)&c[0]);
    printf("c[1] = %f\n", c[1]);
    printf("c[2] = %f\n", c[2]);
    printf("c[3] = %f\n", c[3]);
    ASSERT(-2147483648, c[0]);
    ASSERT(2, c[1]);
    ASSERT(3, c[2]);
    ASSERT(4, c[3]);
    printf("OK\n");
    return 0;
}
