#include "test.h"

static int foo(int unused, int used) {
    return used;
}

int main() {
    ASSERT(5, foo(1, 5));
    return 0;
}
