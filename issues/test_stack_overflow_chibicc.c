#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define STACK_OVERFLOW_MAX_SIZE (4096*2)

static void faulthandler_suppress_crash_report(void) {}

static uintptr_t
stack_overflow(uintptr_t min_sp, uintptr_t max_sp, size_t *depth)
{
    volatile unsigned char buffer[4096];
    uintptr_t sp = (uintptr_t)&buffer;
    *depth += 1;
    if (sp < min_sp || max_sp < sp)
        return sp;
    buffer[0] = 1;
    buffer[4095] = 0;
    return stack_overflow(min_sp, max_sp, depth);
}

int main(void)
{
    size_t depth = 0;
    uintptr_t sp = (uintptr_t)&depth;
    uintptr_t lower_limit, upper_limit;

    if (STACK_OVERFLOW_MAX_SIZE <= sp) {
        lower_limit = sp - STACK_OVERFLOW_MAX_SIZE;
    } else {
        lower_limit = 0;
    }

    if (UINTPTR_MAX - STACK_OVERFLOW_MAX_SIZE >= sp) {
        upper_limit = sp + STACK_OVERFLOW_MAX_SIZE;
    } else {
        upper_limit = UINTPTR_MAX;
    }

    uintptr_t stop = stack_overflow(lower_limit, upper_limit, &depth);
    size_t size;
    if (sp < stop)
        size = stop - sp;
    else
        size = sp - stop;

    printf("Allocated %zu bytes on the stack, %zu recursive calls\n", size, depth);
    return 0;
}