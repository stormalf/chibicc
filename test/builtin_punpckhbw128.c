#include "test.h"

typedef unsigned char __v16qu __attribute__((vector_size(16)));
typedef char __v16qi __attribute__((vector_size(16)));


__v16qi test_punpckhbw(__v16qi a, __v16qi b) {
    return __builtin_ia32_punpckhbw128(a, b);
}

int main(void) {
    __v16qi a = {  0,  1,  2,  3,  4,  5,  6,  7,
                   8,  9, 10, 11, 12, 13, 14, 15 };
    __v16qi b = {100,101,102,103,104,105,106,107,
                 108,109,110,111,112,113,114,115 };

    __v16qu r = (__v16qu)test_punpckhbw(a, b);

    for (int i = 0; i < 16; i++)
        printf("%u ", r[i]);
    printf("\n");
    ASSERT(8, r[0]);
    ASSERT(108, r[1]);
    ASSERT(9, r[2]);
    ASSERT(109, r[3]);
    ASSERT(10, r[4]);
    ASSERT(110, r[5]);
    ASSERT(11, r[6]);
    ASSERT(111, r[7]);
    ASSERT(12, r[8]);
    ASSERT(112, r[9]);
    ASSERT(13, r[10]);
    ASSERT(113, r[11]);
    ASSERT(14, r[12]);
    ASSERT(114, r[13]);
    ASSERT(15, r[14]);
    ASSERT(115, r[15]);

    printf("OK\n");

    return 0;
}
