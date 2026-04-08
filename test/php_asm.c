// test_asm_guard.c
#include "test.h"
#define XXH_COMPILER_GUARD(var) __asm__("" : "+r" (var))

int main(void) {
    int x = 42;
    XXH_COMPILER_GUARD(x);
    ASSERT(42, x);
    return 0;
}
