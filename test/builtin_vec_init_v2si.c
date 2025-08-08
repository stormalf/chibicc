#include "test.h"

typedef int v2si __attribute__((vector_size(8))); // 2 × 4 bytes = 8 bytes

// Prototype for the builtin so the compiler doesn't warn
v2si __builtin_ia32_vec_init_v2si(int, int);

int main(void) {
    v2si v = __builtin_ia32_vec_init_v2si(123456, 0);
    int *p = (int *)&v;
    printf("%d %d\n", p[0], p[1]);
    ASSERT(123456, p[0]);
    ASSERT(0, p[1]);
    return 0;
}
