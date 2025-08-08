#include "test.h"
#include <stdint.h>

int main() {
    unsigned int mxcsr = __builtin_ia32_stmxcsr();
    printf("MXCSR register value: 0x%x\n", mxcsr);
    ASSERT(0x1f80, mxcsr);
    return 0;
}
