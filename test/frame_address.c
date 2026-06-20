#include "test.h"
#include <stdlib.h>

// Force stack alignment > 16 to trigger use_rbx in chibicc
void *get_parent_frame(void) __attribute__((noinline));
void *get_parent_frame(void) {
    volatile int x __attribute__((aligned(32))) = 0;
    // This should return the frame pointer of the caller (main)
    // If chibicc uses %rbx (lvar_ptr) instead of %rbp, this will return garbage/wrong frame
    return __builtin_frame_address(1);
}

void *get_return_addr(void) __attribute__((noinline));
void *get_return_addr(void) {
    volatile int x __attribute__((aligned(32))) = 0;
    return __builtin_return_address(0);
}

int main() {
    void *main_fp = __builtin_frame_address(0);
    void *parent_fp = get_parent_frame();
    
    // The parent of get_parent_frame should be main's frame pointer
    if (main_fp != parent_fp) {
        printf("FAIL: main_fp %p != parent_fp %p\n", main_fp, parent_fp);
        exit(1);
    }

    void *ra = get_return_addr();
    // Return address should be non-null and look like a code address
    if (!ra) {
        printf("FAIL: return address is NULL\n");
        exit(1);
    }

    printf("OK\n");
    return 0;
}
