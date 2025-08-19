#include "test.h"
#include <stdint.h>

typedef int v4si __attribute__((vector_size(16)));


int main() {
    v4si a = { 0xFFFFFFFF, 0x80000000, 0x12345678, 0x00000001 };

    // Shift right logical by 1
    v4si r = __builtin_ia32_psrldi128((v4si)a, 1);

    unsigned int *res = (unsigned int *)&r;
    for (int i = 0; i < 4; i++) {
        printf("%08x ", res[i]);
    }
    printf("\n");

        
    ASSERT(0x7fffffff, r[0]);
    ASSERT(0x40000000, r[1]);
    ASSERT(0x091a2b3c, r[2]);
    ASSERT(0x00000000, r[3]);
    
    int count = 1;
    r = __builtin_ia32_psrldi128((v4si)a, count);

    res = (unsigned int *)&r;
    for (int i = 0; i < 4; i++) {
        printf("%08x ", res[i]);
    }
    printf("\n");
    
    ASSERT(0x7fffffff, r[0]);
    ASSERT(0x40000000, r[1]);
    ASSERT(0x091a2b3c, r[2]);
    ASSERT(0x00000000, r[3]);

    printf("OK\n");

    return 0;
}
