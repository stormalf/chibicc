#include "test.h"

typedef int int4 __attribute__((vector_size(16)));

int main(void) {
    int4 v = {10, 20, 30, 40};

    int a0 = __builtin_ia32_vec_ext_v4si(v, 0);
    int a1 = __builtin_ia32_vec_ext_v4si(v, 1);
    int a2 = __builtin_ia32_vec_ext_v4si(v, 2);
    int a3 = __builtin_ia32_vec_ext_v4si(v, 3);

    printf("%d %d %d %d\n", a0, a1, a2, a3); // Expected: 10 20 30 40
    return 0;
}
