#include "test.h"
typedef short  __v8hi   __attribute__((vector_size(16)));
typedef unsigned char __v16qu __attribute__((vector_size(16)));
typedef char  __v16qi __attribute__((vector_size(16)));

__v16qi test_packuswb128(__v8hi a, __v8hi b) {
    return __builtin_ia32_packuswb128(a, b);
}

int main(void) {
    __v8hi a = { 100, 200, 300, -100, -200, 127, 255, 400 };
    __v8hi b = { 0, -1, 500, 128, 300, -500, 255, -255 };

    __v16qu r = (__v16qu)test_packuswb128(a, b);

    for (int i = 0; i < 16; i++)
        printf("%u ", r[i]);
    printf("\n");
    ASSERT(100, r[0]);
    ASSERT(200, r[1]);
    ASSERT(255, r[2]);
    ASSERT(0, r[3]);
    ASSERT(0, r[4]);
    ASSERT(127, r[5]);
    ASSERT(255, r[6]);
    ASSERT(255, r[7]);
    ASSERT(0, r[8]);
    ASSERT(0, r[9]);
    ASSERT(255, r[10]);
    ASSERT(128, r[11]);
    ASSERT(255, r[12]);
    ASSERT(0, r[13]);
    ASSERT(255, r[14]);
    ASSERT(0, r[15]);

    printf("OK\n");
    return 0;
}
