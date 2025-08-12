#include "test.h"

typedef  char __v8qi __attribute__((vector_size(8)));
typedef  unsigned char __v8qu __attribute__((vector_size(8)));

int main(void) {
    __v8qi a = {100, 250, 30, 40, 200, 60, 70, 80};
    __v8qi b = {150, 200, 50, 20, 180, 70, 60, 90};

    __v8qi r = __builtin_ia32_pminub(a, b);
    __v8qu r2 = (__v8qu) r;
    for (int i = 0; i < 8; i++) {
        printf("r[%d] = %u\n", i, r[i]);
    }

    for (int i = 0; i < 8; i++) {
        printf("r2[%d] = %u\n", i, r2[i]);
    }
    ASSERT(100, r2[0]);
    ASSERT(200, r2[1]);
    ASSERT(30, r2[2]);
    ASSERT(20, r2[3]);
    ASSERT(180, r2[4]);
    ASSERT(60, r2[5]);
    ASSERT(60, r2[6]);
    ASSERT(80, r2[7]);

    printf("OK\n");
    return 0;
}
