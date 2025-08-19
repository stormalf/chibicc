#include "test.h"
// compile with: chibicc -o test test.c
typedef double v2df __attribute__((vector_size(16)));

extern v2df __builtin_ia32_movsd(v2df, v2df);

int main(void) {
    v2df a = { 1.5, 2.5 };
    v2df b = { 9.0, 8.0 };

    v2df c = __builtin_ia32_movsd(a, b);
    // movsd should copy only the lower element from 'a', keeping the upper from 'b'

    printf("c[0] = %f\n", c[0]); // expect 1.5
    printf("c[1] = %f\n", c[1]); // expect 8.0

    ASSERT(9, c[0]);
    ASSERT(2, c[1]);
    printf("OK\n");
    return 0;

}
