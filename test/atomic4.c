#include <stdio.h>
#include <stdbool.h>

// Test for __atomic_compare_exchange_n
void test_compare_exchange_n() {
    int x = 42;
    int expected = 42;
    int desired = 100;

    // Should succeed, since *x == expected
    bool success = __atomic_compare_exchange_n(&x, &expected, desired,
                                               false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);

    printf("=== __atomic_compare_exchange_n ===\n");
    printf("success=%d, x=%d, expected=%d\n", success, x, expected);

    // Reset for failure case
    x = 200;
    expected = 42;
    desired = 300;

    success = __atomic_compare_exchange_n(&x, &expected, desired,
                                          false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);

    printf("failure case: success=%d, x=%d, expected=%d\n", success, x, expected);
}

// Test for __atomic_compare_exchange
void test_compare_exchange() {
    int x = 42;
    int expected = 42;
    int desired = 100;

    // Same semantics but explicit expected as a pointer
    bool success = __atomic_compare_exchange(&x, &expected, &desired,
                                             false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);

    printf("=== __atomic_compare_exchange ===\n");
    printf("success=%d, x=%d, expected=%d\n", success, x, expected);

    // Reset for failure case
    x = 200;
    expected = 42;
    desired = 300;

    success = __atomic_compare_exchange(&x, &expected, &desired,
                                        false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);

    printf("failure case: success=%d, x=%d, expected=%d\n", success, x, expected);
}

int main() {
    test_compare_exchange_n();
    test_compare_exchange();
    return 0;
}
