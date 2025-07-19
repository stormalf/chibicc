
#include <stdint.h>
#include "test.h"

void print_value(long value) {
    printf("Value in RAX: %ld\n", value);
}

// Function prototype for the test function
unsigned int my_clzl(long x);

int main() {
    // Test values
    long test_values[] = {
        0,                    // Should return 63 (all bits are zeros)
        1,                    // Should return 63 (1 << 63 has one leading zero)
        0xFFFFFFFFFFFFFFFE,   // Should return 0 (64-bit value with a single bit set)
        0x8000000000000000,   // Should return 0 (64-bit value with the highest bit set)
        0x7FFFFFFFFFFFFFFF,   // Should return 1 (all bits except the highest are set)
        0xFFFFFFFFFFFFFFFF    // Should return 0 (all bits are set)
    };

    // Test the `__builtin_clzl` function
    for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        long value = test_values[i];
        unsigned int result = my_clzl(value);
        printf("my_clzl(%ld) = %u\n", value, result);
        if (i == 0 || i == 1)
            ASSERT(63, result );
        else if (i == 2 || i == 3 || i == 5)
            ASSERT(0, result);
        else if (i == 4)
            ASSERT(1, result );

    }

    return 0;
}

// Dummy implementation of `__builtin_clzl` for demonstration
// In your real code, this would be replaced by the actual built-in function
unsigned int my_clzl(long x) {
    return __builtin_clzl(x);
}
