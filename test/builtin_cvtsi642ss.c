#include "test.h"
#include <stdint.h>

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    int64_t b = 42;

    v4sf c = __builtin_ia32_cvtsi642ss(a, b);

    printf("c[0] = %f\n", c[0]); // should print 42.0
    printf("c[1] = %f\n", c[1]); // should print 2.0 (unchanged)
    printf("c[2] = %f\n", c[2]);
    printf("c[3] = %f\n", c[3]);
    ASSERT(42, c[0]);
    ASSERT(2, c[1]);
    ASSERT(3, c[2]);
    ASSERT(4, c[3]);
    printf("OK\n");
    return 0;
}
