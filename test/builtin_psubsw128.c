#include "test.h"
#include <stdint.h>

typedef long long __v2di __attribute__((__vector_size__(16)));
typedef short __v8hi __attribute__((__vector_size__(16)));

int main() {
    __v8hi a = {30000, -20000, 15000, -32768, 1000, -1000, 20000, -15000};
    __v8hi b = {10000, -20000, 20000, 1000, 5000, -4000, -30000, 20000};

    __v8hi res = __builtin_ia32_psubsw128(a, b);

    short *vals = (short*)&res;
    for (int i = 0; i < 8; i++)
        printf("%d ", vals[i]);
    printf("\n");

    ASSERT(20000, res[0]);
    ASSERT(0, res[1]);
    ASSERT(-5000, res[2]);
    ASSERT(-32768, res[3]);
    ASSERT(-4000, res[4]);
    ASSERT(3000, res[5]);
    ASSERT(32767, res[6]);
    ASSERT(-32768, res[7]);
    printf("OK\n");
    return 0;
}
