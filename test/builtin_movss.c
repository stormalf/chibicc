
#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {5.5f, 6.5f, 7.5f, 8.5f};

    v4sf c = __builtin_ia32_movss(a, b);

    printf("c = %f %f %f %f\n", c[0], c[1], c[2], c[3]);
    // Should print: 5.5 2.0 3.0 4.0

    ASSERT(5, c[0]);
    ASSERT(2, c[1]);
    ASSERT(3, c[2]);
    ASSERT(4, c[3]);

    printf("OK\n");
}
