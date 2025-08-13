#include "test.h"
typedef unsigned long long u64;


int main() {
    u64 x = 0;
    __builtin_ia32_movntq(&x, 0x1122334455667788ULL);
    printf("x = 0x%llx\n", x);
    LASSERT(0x1122334455667788ULL, x);
    printf("OK\n");
    return 0;
}
