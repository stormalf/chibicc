#include "test.h"
#include <stddef.h>
#include <stdio.h>

struct AlignedStruct {
    int x;
} __attribute__((aligned(32)));

void foo(struct AlignedStruct a) {
    printf("val: %d\n", a.x);
}

int main() {
    struct AlignedStruct s = {1};
    foo(s);
    ASSERT(1, 1);
    return 0;
}
