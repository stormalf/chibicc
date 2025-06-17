#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "test.h"

typedef struct pg_atomic_uint64 {
    volatile uint64_t value;
} pg_atomic_uint64;

// Atomic compare and exchange function
static inline bool pg_atomic_compare_exchange_u64_impl(volatile pg_atomic_uint64 *ptr,
                                                       uint64_t *expected, uint64_t newval)
{
    char ret;

    // Assume pointer alignment is already checked before this function
    __asm__ __volatile__(
        "	lock				\n"
        "	cmpxchgq	%4,%5	\n"
        "   setz		%2		\n"
    :   "=a" (*expected), "=m"(ptr->value), "=q" (ret)
    :   "a" (*expected), "r" (newval), "m"(ptr->value)
    :   "memory", "cc");

    fprintf(stderr, "====pg_atomic_compare_exchange_u64_impl: %lld\n", ptr->value);
    return (bool) ret;
}

// Test the compare and exchange function
void test_pg_atomic_compare_exchange_u64() {
    pg_atomic_uint64 atomic_value;
    atomic_value.value = 42;  // Initial value

    uint64_t expected = 42;    // Value we expect
    uint64_t new_value = 100;  // New value we want to set

    // Test successful compare-and-exchange
    bool result = pg_atomic_compare_exchange_u64_impl(&atomic_value, &expected, new_value);
    printf("Test 1 - Successful exchange: Result = %d, New Value = %llu, Expected = %llu\n",
           result, atomic_value.value, expected);

    ASSERT(100, atomic_value.value);  // Check if the value was updated
    ASSERT(42, expected);              // Check if expected was updated
    // Reset expected for the next test
    expected = 100;

    // Test unsuccessful compare-and-exchange (expected should not be 42 anymore)
    expected = 42;  // Now set expected to a value that doesn't match
    result = pg_atomic_compare_exchange_u64_impl(&atomic_value, &expected, new_value);
    printf("Test 2 - Unsuccessful exchange: Result = %d, New Value = %llu, Expected = %llu\n",
           result, atomic_value.value, expected);
    ASSERT(100, atomic_value.value);  // Value should remain unchanged
    ASSERT(100, expected);             // Expected should still be 100
}

int main() {
    test_pg_atomic_compare_exchange_u64();
    return 0;
}
