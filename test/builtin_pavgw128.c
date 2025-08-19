#include "test.h"

typedef unsigned short ushort8 __attribute__((vector_size(16)));
typedef short short8 __attribute__((vector_size(16)));

int main() {
    short8 a = {1000, 2000, 65535, 0, 1, 5000, 32000, 100};
    short8 b = {1000,  555,   10, 0, 65535, 6000, 32767, 65535};

    ushort8 c = (ushort8)__builtin_ia32_pavgw128(a, b);

    for (int i = 0; i < 8; i++)
        printf("%u ", c[i]);
    printf("\n");
    ASSERT(1000, c[0]);
    ASSERT(1278, c[1]);
    ASSERT(32773, c[2]);
    ASSERT(0, c[3]);
    ASSERT(32768, c[4]);
    ASSERT(5500, c[5]);
    ASSERT(32384, c[6]);
    ASSERT(32818, c[7]);
    printf("OK\n");
    return 0;
}
