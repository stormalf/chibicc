#include "test.h"
#include <string.h>

typedef unsigned char uchar16 __attribute__((vector_size(16)));
typedef char char16 __attribute__((vector_size(16)));

int main() {
    char16 src  = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
    char16 mask = {0x80,0,0x80,0,0x80,0,0x80,0,0x80,0,0x80,0,0x80,0,0x80,0};
    unsigned char dest[16];

    memset(dest, '.', sizeof(dest));

    __builtin_ia32_maskmovdqu(src, mask, dest);

    for (int i = 0; i < 16; i++)
        putchar(dest[i]);
    putchar('\n');
    
    ASSERT('A', dest[0]);
    ASSERT('C', dest[2]);
    ASSERT('E', dest[4]);
    ASSERT('G', dest[6]);
    ASSERT('I', dest[8]);
    ASSERT('K', dest[10]);
    ASSERT('M', dest[12]);
    ASSERT('O', dest[14]);
    printf("OK\n");
    return 0;
}
