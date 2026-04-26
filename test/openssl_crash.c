#include "test.h"
#include <stdint.h>

int main() {
    uint64_t x = 1;

    uint64_t y = x << 64;

    if (y != 0) {
        printf("FAIL: %lx\n", y);
        return 1;
    }

    printf("OK\n");
}
