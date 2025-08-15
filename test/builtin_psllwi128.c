#include "test.h"
#include <stdint.h>

typedef short v8si __attribute__((vector_size(16)));

int main() {
    // Prepare test data: 8 x 16-bit words in a 128-bit vector
    v8si v = {1, 2, 3, 4, 0x8000, 0x4000, 0x1234, 0xFFFF};

    v8si r = __builtin_ia32_psllwi128(v, 1);


    for (int i = 0; i < 8; i++) {
        printf("%04x ", r[i]);
    }
    printf("\n");

    ASSERT(2, r[0]);
    ASSERT(4, r[1]);
    ASSERT(6, r[2]);
    ASSERT(8, r[3]);
    ASSERT(0, r[4]);
    ASSERT(-32768, r[5]);
    ASSERT(9320, r[6]);
    ASSERT(-2, r[7]);
    int count = 1;
    r = __builtin_ia32_psllwi128(v, count);


    for (int i = 0; i < 8; i++) {
        printf("%04x ", r[i]);
    }
    printf("\n");
    ASSERT(2, r[0]);
    ASSERT(4, r[1]);
    ASSERT(6, r[2]);
    ASSERT(8, r[3]);
    ASSERT(0, r[4]);
    ASSERT(-32768, r[5]);
    ASSERT(9320, r[6]);
    ASSERT(-2, r[7]);

    printf("OK\n");
    return 0;
}
