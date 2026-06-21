#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

v4hi __builtin_ia32_vec_set_v4hi(v4hi vec, int val, int index);

int main(void) {
    v4hi v = {10, 20, 30, 40};
    v4hi r = __builtin_ia32_vec_set_v4hi(v, 99, 2);
    int r0 = __builtin_ia32_vec_ext_v4hi(r, 0);
    int r1 = __builtin_ia32_vec_ext_v4hi(r, 1);
    int r2 = __builtin_ia32_vec_ext_v4hi(r, 2);
    int r3 = __builtin_ia32_vec_ext_v4hi(r, 3);
    ASSERT(10, r0);
    ASSERT(20, r1);
    ASSERT(99, r2);
    ASSERT(40, r3);
    return 0;
}
