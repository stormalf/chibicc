#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

v4sf subss_test(v4sf a, v4sf b) {
    return __builtin_ia32_subss(a, b);
}

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {0.5f, 1.5f, 2.5f, 3.5f};
    v4sf c = subss_test(a, b);
    (int)c[0];

    ASSERT(0, c[0]);
    ASSERT(2, c[1]);
    ASSERT(3, c[2]);
    ASSERT(4, c[3]);
    printf("OK\n");
    return 0;
}

