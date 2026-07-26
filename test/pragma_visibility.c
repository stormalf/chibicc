#include "test.h"

// Test that #pragma GCC visibility push/pop works correctly

#pragma GCC visibility push(hidden)
static int hidden_global;
int hidden_fn(void) {
    return 1;
}
#pragma GCC visibility pop

#pragma GCC visibility push(default)
int default_fn(void) {
    return 2;
}
#pragma GCC visibility pop

int main(void) {
    ASSERT(1, hidden_fn());
    ASSERT(2, default_fn());
    return 0;
}
