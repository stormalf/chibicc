#include "test.h"

int foo() { return 42; }

int main() {
    int (*f)() = foo;
    ASSERT(42, f());
    return 0;
}
