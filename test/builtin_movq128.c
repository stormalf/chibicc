#include "test.h"

typedef long long int int2 __attribute__((vector_size(16)));

int main(void) {
    int2 a = {1, 2};
    int2 b;

    // Move 128-bit vector a into b
    b = __builtin_ia32_movq128(a);

    printf("b = {%lld, %lld}\n", b[0], b[1]);

    ASSERT(1, b[0]);
    ASSERT(0, b[1]);
    printf("OK\n");
    return 0;
}
