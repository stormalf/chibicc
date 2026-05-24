// Test: inline asm + __builtin_frame_address in same function with -O3.
// The inline asm's base register (decided at parse time) can mismatch
// the actual frame setup (if force_frame_pointer is set after asm parsing).
// This can cause reading wrong memory (e.g., loading 0 as function pointer).
#include "test.h"

int target(void) {
    return 42;
}

// Function that uses both inline asm and __builtin_frame_address.
// With -O3: asm parser sees is_omit_fp=true, uses (%rsp).
// Then __builtin_frame_address sets force_frame_pointer=true.
// At codegen: is_omit_fp=false, %rbp is set up, but asm template
// still references (%rsp) with wrong offset.
__attribute__((noinline)) int mixed_asm_and_frameaddr(int x) {
    int (*fp)(void) = target;
    int result;
    
    // Inline asm to load the function pointer from stack
    asm volatile("mov %1, %0" : "=r"(result) : "m"(fp));
    
    // Force frame pointer (triggers force_frame_pointer = true)
    void *addr = __builtin_frame_address(0);
    (void)addr;
    
    return result;
}

int main() {
    int result = mixed_asm_and_frameaddr(42);
    // result should be the address of 'target' (not NULL)
    if (result == 0) {
        return 1;
    }
    return 0;
}
