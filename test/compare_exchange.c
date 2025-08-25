#include "test.h"
#include <stdbool.h>
#include <stdint.h>

int main() {
    int x = 42;
    int expected;
    int desired;
    bool result;

    printf("=== Testing __atomic_compare_exchange_n ===\n");

    // Example 1: successful CAS
    x = 42;
    expected = 42;
    desired = 100;
    result = __atomic_compare_exchange_n(&x, &expected, desired, false,
                                        __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    printf("CAS_N success? %d, x=%d, expected=%d\n", result, x, expected);
    ASSERT(42, expected);
    ASSERT(100, x);
    ASSERT(1, result);
    // Example 2: failed CAS
    x = 50;
    expected = 42;
    desired = 200;
    result = __atomic_compare_exchange_n(&x, &expected, desired, false,
                                        __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    printf("CAS_N success? %d, x=%d, expected=%d\n", result, x, expected);

    printf("\n=== Testing __atomic_compare_exchange ===\n");
    ASSERT(50, expected);
    ASSERT(50, x);
    ASSERT(0, result);
    // Using __atomic_compare_exchange (strong variant)
    x = 42;
    expected = 50;
    desired = 123;
    result = __atomic_compare_exchange(&x, &expected, &desired, false,
                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    printf("CAS success? %d, x=%d, expected=%d\n", result, x, expected);
    ASSERT(42, expected);
    ASSERT(42, x);
    ASSERT(0, result);
    // Failed CAS
    x = 50;
    expected = 42;
    desired = 999;
    result = __atomic_compare_exchange(&x, &expected, &desired, false,
                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    printf("CAS success? %d, x=%d, expected=%d\n", result, x, expected);
    ASSERT(50, expected);
    ASSERT(50, x);
    ASSERT(0, result);
    return 0;
}
