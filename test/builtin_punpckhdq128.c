#include "test.h"

typedef int __v4si __attribute__((vector_size(16)));

__v4si test_punpckhdq128(__v4si a, __v4si b) {
    return __builtin_ia32_punpckhdq128(a, b);
}

int main(void) {
    __v4si a = {  0,  1,  2,  3 };
    __v4si b = {100,101,102,103 };

    __v4si r = test_punpckhdq128(a, b);

    for (int i = 0; i < 4; i++)
        printf("%d ", r[i]);
    printf("\n");

    ASSERT(2, r[0]);
    ASSERT(102, r[1]);
    ASSERT(3, r[2]);
    ASSERT(103, r[3]);
    printf("OK\n");
    return 0;
}
