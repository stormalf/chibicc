#include "test.h"

typedef char v16qi __attribute__((vector_size(16)));

v16qi __builtin_ia32_vec_set_v16qi(v16qi vec, int val, int index);

int main(void) {
    v16qi v;
    for (int i = 0; i < 16; i++)
        ((char *)&v)[i] = (char)(i * 2);
    v16qi r = __builtin_ia32_vec_set_v16qi(v, 99, 5);
    int r0 = __builtin_ia32_vec_ext_v16qi(r, 0);
    int r5 = __builtin_ia32_vec_ext_v16qi(r, 5);
    int r15 = __builtin_ia32_vec_ext_v16qi(r, 15);
    ASSERT(0,  r0);
    ASSERT(99, r5);
    ASSERT(30, r15);
    return 0;
}
