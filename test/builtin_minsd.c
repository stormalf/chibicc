#include "test.h"

typedef double v2df __attribute__((vector_size(16)));


int main(void) {
    v2df a = { 1.0, 4.0 };
    v2df b = { 3.0, 2.0 };

    v2df c = __builtin_ia32_minsd(a, b);

    printf("min: %f %f\n", c[0], c[1]); // expect 1.0 2.0
    ASSERT(1, c[0]);
    ASSERT(4, c[1]);
    printf("OK\n");
    return 0;
}
