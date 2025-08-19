#include "test.h"


typedef unsigned char v8qu __attribute__((vector_size(8)));
typedef char v8qi __attribute__((vector_size(8)));

int main(void) {
    v8qu a = {120u, 200u, 100u, 250u, 10u, 30u, 255u, 1u};
    v8qu b = {10u, 100u, 200u,  10u, 250u, 240u, 10u, 5u};

    v8qu result = (v8qu) __builtin_ia32_paddusb((v8qi)a, (v8qi)b);

    for (int i = 0; i < 8; i++) {
        printf("%u ", result[i]);
    }
    printf("\n");
    ASSERT(130, result[0]);
    ASSERT(255, result[1]);
    ASSERT(255, result[2]);
    ASSERT(255, result[3]);
    ASSERT(255, result[4]);
    ASSERT(255, result[5]);
    ASSERT(255, result[6]);
    ASSERT(6, result[7]);
    printf("OK\n");
    return 0;
}
