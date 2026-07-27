#include "test.h"

static inline int add(int a, int b) {
    return a + b;
}

static inline int mul(int a, int b) {
    return a * b;
}

static inline int neg(int a) {
    return -a;
}

int main() {
    ASSERT(3, add(1, 2));
    ASSERT(12, mul(3, 4));
    ASSERT(-5, neg(5));
    ASSERT(7, add(3, 4));
    ASSERT(20, mul(5, 4));
    return 0;
}
