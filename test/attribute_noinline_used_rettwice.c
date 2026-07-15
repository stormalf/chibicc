#include "test.h"

// Test __attribute__((noinline))
__attribute__((noinline))
static int noinline_fn(void) {
    return 10;
}

// Test __attribute__((returns_twice))
__attribute__((returns_twice))
int my_retset(void) {
    return 20;
}

// Test __attribute__((used))
__attribute__((used))
static int used_var = 30;

__attribute__((used))
static int used_fn(void) {
    return used_var;
}

int main(void) {
    ASSERT(10, noinline_fn());
    ASSERT(20, my_retset());
    ASSERT(30, used_fn());
    return 0;
}
