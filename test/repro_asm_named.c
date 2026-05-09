#include "test.h"

int main() {
    int x = 42;
    int y = 0;
    __asm__ (
    "movl %[src], (%[dst])"
    :
    : [src]"r"(x), [dst]"r"(&y)
    : "memory"
    );
    printf("y = %d\n", y);
    ASSERT(42, y);
    return 0;
}
