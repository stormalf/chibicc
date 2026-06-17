// Test: Bitwise OR (|) operand evaluation order
//
// In C, the evaluation order of operands of | is unspecified.
// GCC evaluates left-to-right, chibicc evaluates right-to-left.
// This test demonstrates the difference.
//
// The git maintenance scheduler (builtin/gc.c) relied on | to chain
// function calls with side effects, assuming left-to-right order.
// This caused t7900-maintenance.sh to fail when compiled with chibicc.

#include "test.h"
#include <string.h>

static int order[10];
static int idx;

static int func(int n) {
    order[idx++] = n;
    return n;
}

int main(void) {
    int ret, i;

    idx = 0;
    ret = func(1) | func(2) | func(3);

    printf("bitwise OR evaluation order (func(1) | func(2) | func(3)):\n");
    printf("  order: ");
    for (i = 0; i < idx; i++)
        printf("%d ", order[i]);
    printf("\n");

    if (idx == 3 && order[0] == 1 && order[1] == 2 && order[2] == 3)
        printf("  => left-to-right (gcc)\n");
    else if (idx == 3 && order[0] == 3 && order[1] == 2 && order[2] == 1)
        printf("  => right-to-left (chibicc)\n");
    else
        printf("  => other order (compiler-specific)\n");



    // The fix: use sequential statements instead of chaining |
    idx = 0;
    ret = 0;
    ret |= func(1);
    ret |= func(2);
    ret |= func(3);

    printf("\nsequential |= evaluation order:\n");
    printf("  order: ");
    for (i = 0; i < idx; i++)
        printf("%d ", order[i]);
    printf("\n");

    if (idx == 3 && order[0] == 1 && order[1] == 2 && order[2] == 3)
        printf("  => left-to-right (guaranteed by sequence points)\n");
    else
        printf("  => unexpected order\n");

    printf("Ok\n");        
    return 0;
}
