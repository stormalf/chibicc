#include "test.h"

typedef short __v8hi __attribute__((vector_size(16)));

int main() {
    __v8hi a = {16, 15, 14, 13, 12, 11, 10, 9};
    __v8hi b = {26, 25, 24, 23, 22, 21, 20, 19};

    __v8hi res = (__v8hi)__builtin_ia32_punpcklwd128(
        (__v8hi)a, (__v8hi)b
    );

    short *vals = (short *)&res;
    for (int i = 0; i < 8; i++)
        printf("%d ", vals[i]);
    printf("\n");
    ASSERT(16, vals[0]);
    ASSERT(26, vals[1]);
    ASSERT(15, vals[2]);
    ASSERT(25, vals[3]);
    ASSERT(14, vals[4]);
    ASSERT(24, vals[5]);
    ASSERT(13, vals[6]);
    ASSERT(23, vals[7]);
    printf("OK\n");
    return 0;
}
