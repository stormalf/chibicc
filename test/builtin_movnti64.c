#include "test.h"
#include <stdint.h>

int main() {
    long long x = 0;

    __builtin_ia32_movnti64(&x, 0x1122334455667788LL);

    printf("x = 0x%llX\n", x);  // Should print 1122334455667788
    LASSERT(0x1122334455667788, x);
    printf("OK\n");
    return 0;
}
