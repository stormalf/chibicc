#include "test.h"
#include <stdint.h>

typedef short v8hi __attribute__((vector_size(16)));
typedef int   v4si __attribute__((vector_size(16)));

v4si pmaddwd128_test(v8hi a, v8hi b) {
    return __builtin_ia32_pmaddwd128(a, b);
}

int main() {
    v8hi a = {1, 2, 3, 4, -5, -6, 7, 8};
    v8hi b = {10, 20, 30, 40, 50, 60, -70, -80};

    v4si res = pmaddwd128_test(a, b);
    printf("%d %d %d %d\n", res[0], res[1], res[2], res[3]);
    // Expected:
    // res[0] = (1*10 + 2*20) = 10 + 40 = 50
    // res[1] = (3*30 + 4*40) = 90 + 160 = 250
    // res[2] = (-5*50 + -6*60) = -250 + -360 = -610
    // res[3] = (7*-70 + 8*-80) = -490 + -640 = -1130

    ASSERT(50, res[0]);
    ASSERT(250, res[1]);
    ASSERT(-610, res[2]);
    ASSERT(-1130, res[3]);
    printf("OK\n");
}
