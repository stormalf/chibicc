// noinline_stack_init.c
#include <stdio.h>
#include <stdint.h>

__attribute__((noinline))
uintptr_t f(int cond)
{
    uintptr_t p;
    if (cond) {
        p = 0x12345678;
    }
    return p;
}

int main(void)
{
    uintptr_t v = f(1);
    if (v != 0x12345678) {
        puts("BUG: uninitialized or clobbered");
        return 1;
    }
    return 0;
}
