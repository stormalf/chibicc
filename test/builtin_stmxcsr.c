#include <stdint.h>
#include "test.h"

int main() {
    uint32_t mxcsr = 0;

    __builtin_ia32_stmxcsr(&mxcsr);

    printf("MXCSR = 0x%x\n", mxcsr);
    ASSERT(0x1f80, mxcsr);

    // Optionally: test known bit (e.g., flush-to-zero)
    if (mxcsr & (1 << 15))
        printf("Flush-to-zero is enabled\n");
    else
        printf("Flush-to-zero is disabled\n");

    return 0;
}
