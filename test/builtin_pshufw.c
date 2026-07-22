#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

v4hi __builtin_ia32_pshufw(v4hi vec, int imm);

int __builtin_ia32_vec_ext_v4hi(v4hi vec, int index);

int main(void) {
    v4hi v = {10, 20, 30, 40};
    // Shuffle: swap element 0 and 3 (binary: 11 10 01 00 -> 00 01 10 11 = 0x1B)
    v4hi r = __builtin_ia32_pshufw(v, 0x1B);
    int r0 = __builtin_ia32_vec_ext_v4hi(r, 0);
    int r1 = __builtin_ia32_vec_ext_v4hi(r, 1);
    int r2 = __builtin_ia32_vec_ext_v4hi(r, 2);
    int r3 = __builtin_ia32_vec_ext_v4hi(r, 3);
    ASSERT(40, r0);
    ASSERT(30, r1);
    ASSERT(20, r2);
    ASSERT(10, r3);
    return 0;
}
