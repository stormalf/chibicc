#include "test.h"

typedef short __v8hi __attribute__((vector_size(16)));


__v8hi test_punpckhwd128(__v8hi a, __v8hi b) {
    return __builtin_ia32_punpckhwd128(a, b);
}

int main(void) {
    __v8hi a = {  0,  1,  2,  3,  4,  5,  6,  7 };
    __v8hi b = {100,101,102,103,104,105,106,107 };

    __v8hi r = test_punpckhwd128(a, b);

    for (int i = 0; i < 8; i++)
        printf("%d ", r[i]);
    printf("\n");

    ASSERT(4, r[0]);
    ASSERT(104, r[1]);
    ASSERT(5, r[2]);
    ASSERT(105, r[3]);
    ASSERT(6, r[4]);
    ASSERT(106, r[5]);
    ASSERT(7, r[6]);
    ASSERT(107, r[7]);

    printf("OK\n");
    return 0;
}

