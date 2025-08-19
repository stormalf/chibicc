#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));
typedef float v2sf __attribute__((vector_size(8)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v2sf p = {5.0f, 6.0f};

    __builtin_ia32_storelps(&p, a);

    printf("Result vector:\n");
    for (int i = 0; i < 2; i++) {
        printf("c[%d] = %f\n", i, ((float*)&p)[i]);
    }

    // Expected:
    // c[0] = 3.0
    // c[1] = 4.0

    ASSERT(1, p[0]);
    ASSERT(2, p[1]);
    v4sf c = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf d = {5.0f, 6.0f, 7.0f, 8.0f};

    __builtin_ia32_storelps(&d, c);
        printf("Result vector:\n");
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, ((float*)&d)[i]);
    }

    ASSERT(1, d[0]);
    ASSERT(2, d[1]);
    ASSERT(7, d[2]);
    ASSERT(8, d[3]);

    printf("OK\n");

    return 0;
}
