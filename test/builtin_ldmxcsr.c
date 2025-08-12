#include "test.h"
#include <stdint.h>

int main(void) {
    // Read the current MXCSR
    uint32_t mxcsr = __builtin_ia32_stmxcsr();
    printf("Initial MXCSR: 0x%08x\n", mxcsr);

    // Prepare a new MXCSR value (example: mask all exceptions)
    uint32_t new_mxcsr = mxcsr | (1 << 15);

    // Load the new value
    __builtin_ia32_ldmxcsr(new_mxcsr);

    // Read back
    uint32_t mxcsr_after = __builtin_ia32_stmxcsr();
    printf("After load MXCSR: 0x%08x\n", mxcsr_after);

    //restore back
        // Load the new value
    __builtin_ia32_ldmxcsr(mxcsr);

    printf("Restored MXCSR: 0x%08x\n", mxcsr);
    ASSERT(0x00001f80, mxcsr);
    ASSERT(0x00009f80, mxcsr_after);
    printf("OK\n");
    return 0;
}
