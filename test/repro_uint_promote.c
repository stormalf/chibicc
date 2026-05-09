#include "test.h"

int main() {
    unsigned int u = 0x80000000;
    long l = u;
    printf("u: %u\n", u);
    printf("l: %ld\n", l);
    if (l < 0) {
        printf("FAILED: promoted to negative\n");
        return 1;
    }
    ASSERT(2147483648, u);
    ASSERT(2147483648, l);
    printf("PASSED\n");
    return 0;
}
