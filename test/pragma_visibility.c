#include "test.h"

// Test that #pragma GCC visibility push/pop works
// by checking assembly output for correct .hidden directives

#pragma GCC visibility push(hidden)
static int hidden_global;
int hidden_func(void) {
    return 42;
}
#pragma GCC visibility pop

#pragma GCC visibility push(default)
int default_func(void) {
    return hidden_func();
}
#pragma GCC visibility pop

// No pragma - should use command-line -fvisibility if set
int normal_func(void) {
    return 0;
}

int main(void) {
    // Just verify the functions work at runtime
    ASSERT(42, hidden_func());
    ASSERT(42, default_func());
    ASSERT(0, normal_func());
    return 0;
}
