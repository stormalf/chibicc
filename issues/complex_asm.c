#include "test.h"

int main() {
    int a = 10, b = 20;
    int result;

    // Extended assembly with named operand and expression inside parentheses
    __asm__ volatile (
        "add %[src], %[dst]\n"
        : [dst] "=r" (result)      // output operand name [dst]
        : [src] "r" (a + b)        // input operand name [src], expression in parentheses
    );

    printf("Result = %d\n", result);

    return 0;
}
