#include "test.h"
#include <stdint.h>

typedef short v8hi __attribute__((vector_size(16)));



int main() {
    v8hi a = { 0xFFFF, 0x8000, 0x1234, 0x0001, 0x7FFF, 0x4000, 0xAAAA, 0x5555 };

    // Shift right logical by 1
    v8hi r = __builtin_ia32_psrlwi128((v8hi)a, 1);

    unsigned short *res = (unsigned short *)&r;
    for (int i = 0; i < 8; i++) {
        printf("%04x ", res[i]);
    }
    printf("\n");

    ASSERT(0x7fff, r[0]);
    ASSERT(0x4000, r[1]);
    ASSERT(0x091a, r[2]);
    ASSERT(0x0000, r[3]);
    ASSERT(0x3fff, r[4]);
    ASSERT(0x2000, r[5]);
    ASSERT(0x5555, r[6]);
    ASSERT(0x2aaa, r[7]);
    int count = 1;
    r = __builtin_ia32_psrlwi128((v8hi)a, count);

    res = (unsigned short *)&r;
    for (int i = 0; i < 8; i++) {
        printf("%04x ", res[i]);
    }
    printf("\n");

    ASSERT(0x7fff, r[0]);
    ASSERT(0x4000, r[1]);
    ASSERT(0x091a, r[2]);
    ASSERT(0x0000, r[3]);
    ASSERT(0x3fff, r[4]);
    ASSERT(0x2000, r[5]);
    ASSERT(0x5555, r[6]);
    ASSERT(0x2aaa, r[7]);    
    printf("OK\n");
    return 0;
}
