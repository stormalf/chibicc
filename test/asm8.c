
#include "test.h"

void add_and_subtract(int a, int b, int *sum, int *diff) {
    asm (
        "add %3, %2\n\t"
         "mov %2, %0\n\t"
        "sub %3, %2\n\t"
        "mov %2, %1\n\t"
        ""
        : "=r" (*sum), "=r" (*diff)    // Output operands
        : "r" (a), "r" (b)             // Input operands
        : "cc"                         // Clobbered registers
    );
}

int main(void) {
    int a = 10, b = 5;
    int sum = 0, diff = 0;

    add_and_subtract(a, b, &sum, &diff);

    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", diff);
    ASSERT(15, sum);
    ASSERT(10, diff);

    return 0;
}
