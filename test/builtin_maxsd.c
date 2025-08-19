#include "test.h"

typedef double v2df __attribute__((vector_size(16)));


int main(void) {
    v2df a = { 1.0, 4.0 };
    v2df b = { 3.0, 2.0 };

    v2df c = __builtin_ia32_maxsd(a, b);

    printf("max: %f %f\n", c[0], c[1]); 
    ASSERT(3, c[0]);
    ASSERT(4, c[1]);
    printf("OK\n");
    return 0;
}
