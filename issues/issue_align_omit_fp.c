#include "test.h"

typedef int v8si __attribute__((vector_size(32)));

void take_v8si(v8si v, int a, int b, int c, int d, int e, int f, v8si v2) {
}

int foo() { return 42; }

int main() {
    v8si v = {0};
    int (*f)() = foo;
    // The call to take_v8si will trigger stack alignment for the 8th argument (v2).
    // If f is a local variable, its address will be calculated using depth.
    // If push_args realigns the stack, the address of f will be wrong.
    take_v8si(v, 1, 2, 3, 4, 5, 6, v);
    ASSERT(42, f());
    return 0;
}
