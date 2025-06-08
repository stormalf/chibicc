#include <stdio.h>
#include <math.h>
#include "test.h"

int main() {
    printf("Positive Infinity: %f\n", INFINITY);
    ASSERT(INFINITY, __builtin_inf());
    return 0;
}
