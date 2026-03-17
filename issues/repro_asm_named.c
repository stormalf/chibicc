#include "test.h"

int main() {
    int x = 42;
    int y = 0;
    asm ("movl %[src], %[dst]" : [dst]"=r"(&y) : [src]"r"(x));
    printf("y = %d\n", y);
    ASSERT(42, y);
    return 0;
}
