#include "test.h"
#include <stdint.h>

typedef short v8hi __attribute__((vector_size(16)));


int main() {
    v8hi a = { 1000, -1000, 32767, -32768, 1234, -1234, 500, -500 };

    // Shift right arithmetic by 2 bits
    v8hi r = __builtin_ia32_psrawi128((v8hi)a, 2);

    short *res = (short *)&r;
    for (int i = 0; i < 8; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    ASSERT(250, r[0]);
    ASSERT(-250, r[1]);
    ASSERT(8191, r[2]);
    ASSERT(-8192, r[3]);
    ASSERT(308, r[4]);
    ASSERT(-309, r[5]);
    ASSERT(125, r[6]);
    ASSERT(-125, r[7]);

    int count = 2;
    r = __builtin_ia32_psrawi128((v8hi)a, 2);

    res = (short *)&r;
    for (int i = 0; i < 8; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    ASSERT(250, r[0]);
    ASSERT(-250, r[1]);
    ASSERT(8191, r[2]);
    ASSERT(-8192, r[3]);
    ASSERT(308, r[4]);
    ASSERT(-309, r[5]);
    ASSERT(125, r[6]);
    ASSERT(-125, r[7]);    
    printf("OK\n");

    return 0;
}
