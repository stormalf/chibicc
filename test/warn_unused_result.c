// Test __attribute__((warn_unused_result))
#include "test.h"

__attribute__((warn_unused_result)) int foo(void) { return 42; }
int bar(void) { return 0; }

int main() {
    int x = foo();
    ASSERT(42, x);
    x = bar();
    ASSERT(0, x);
    printf("OK\n");
    return 0;
}
