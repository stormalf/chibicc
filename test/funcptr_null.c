// Reproducer: function pointer from local variable becomes NULL
// when compiled with -O3 (omit-frame-pointer) under specific conditions.
// The crash is a call-through-zero (segfault at address 0x0).
#include "test.h"

int target(void) {
    return 42;
}

// Function that may be compiled with omit-frame-pointer (no __builtin_frame_address)
// and uses a function pointer stored in a local variable
__attribute__((noinline)) int call_fnptr(int x, int y, int z, int w) {
    int (*fp)(void) = target;
    volatile int a = x;
    volatile int b = y;
    volatile int c = z;
    volatile int d = w;
    // Prevent tail call optimization
    int sum = a + b + c + d;
    if (sum > 1000)
        return fp();
    return fp() + sum;
}

int main() {
    int result = call_fnptr(1, 2, 3, 4);
    if (result != 52) {
        return 1;
    }
    return 0;
}
