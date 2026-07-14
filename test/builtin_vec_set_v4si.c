#include "test.h"

typedef int v4si __attribute__((vector_size(16)));

v4si __builtin_ia32_vec_set_v4si(v4si vec, int val, int index);

int main(void) {
    v4si v = {10, 20, 30, 40};
    v4si r = __builtin_ia32_vec_set_v4si(v, 99, 2);
    int r0 = __builtin_ia32_vec_ext_v4si(r, 0);
    int r1 = __builtin_ia32_vec_ext_v4si(r, 1);
    int r2 = __builtin_ia32_vec_ext_v4si(r, 2);
    int r3 = __builtin_ia32_vec_ext_v4si(r, 3);
    ASSERT(10, r0);
    ASSERT(20, r1);
    ASSERT(99, r2);
    ASSERT(40, r3);
    return 0;
}
