#include "test.h"
#include <stdint.h>

int main() {
    int x = 0;

    // Non-temporal store 12345 into &x
    __builtin_ia32_movnti(&x, 12345);

    printf("x = %d\n", x); // Should print 12345

    ASSERT(12345, x);
    printf("OK\n");
    return 0;
}
