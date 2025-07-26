
#include <limits.h>
#include "test.h"

int main() {
    printf("INT_MAX: %d\n", INT_MAX);    
    printf("INT_MIN: %d\n", INT_MIN);
    printf("LONG_MAX: %ld\n", LONG_MAX);
    ASSERT(2147483647, INT_MAX);
    ASSERT(-2147483648, INT_MIN);
    ASSERT(9223372036854775807L, LONG_MAX);
    return 0;
}

