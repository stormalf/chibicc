#include <stdio.h>

int main() {
    int x = 42;
    int y = 0;
    asm ("movl %[src], %[dst]" : : [dst]"r"(&y), [src]"r"(x) : "memory");
    printf("y = %d\n", y);
    return 0;
}
