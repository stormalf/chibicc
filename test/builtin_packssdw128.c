#include "test.h"

typedef int   __v4si  __attribute__((vector_size(16)));
typedef short __v8hi  __attribute__((vector_size(16)));


__v8hi test_packssdw128(__v4si a, __v4si b) {
    return __builtin_ia32_packssdw128(a, b);
}

int main(void) {
    __v4si a = { 1000, 40000, -40000, -1000 };
    __v4si b = { 2000, -50000, 50000, -2000 };

    __v8hi r = test_packssdw128(a, b);

    for (int i = 0; i < 8; i++) {
        printf("%d ", r[i]);
    }
    printf("\n");
    ASSERT(1000, r[0]);
    ASSERT(32767, r[1]);
    ASSERT(-32768, r[2]);
    ASSERT(-1000, r[3]);
    ASSERT(2000, r[4]);
    ASSERT(-32768, r[5]);
    ASSERT(32767, r[6]);
    ASSERT(-2000, r[7]);
    printf("OK\n");
    return 0;
}
