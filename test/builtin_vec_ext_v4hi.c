#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int __builtin_ia32_vec_ext_v4hi(v4hi vec, int index);

int main(void) {
    v4hi v = {100, 200, -300, 400};
    int r0 = __builtin_ia32_vec_ext_v4hi(v, 0);
    int r1 = __builtin_ia32_vec_ext_v4hi(v, 1);
    int r2 = __builtin_ia32_vec_ext_v4hi(v, 2);
    int r3 = __builtin_ia32_vec_ext_v4hi(v, 3);
    ASSERT(100, r0);
    ASSERT(200, r1);
    ASSERT(-300, r2);
    ASSERT(400, r3);
    return 0;
}
