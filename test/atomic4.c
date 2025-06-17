#include <stdio.h>
#include <stdatomic.h>
#include <stdbool.h>
#include "test.h"

int main() {
    int a = 10;
    int expected = 10;
    int desired = 20;

    // Test __atomic_compare_exchange_n
    if (__atomic_compare_exchange_n(&a, &expected, desired, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
        printf("CAS succeeded, a = %d\n", a);
    } else {
        printf("CAS failed, a = %d, expected = %d\n", a, expected);
    }

    ASSERT(20, a);
    ASSERT(10, expected);
    // Test __atomic_exchange_n
    int result = __atomic_exchange_n(&a, 30, __ATOMIC_SEQ_CST);
    printf("Exchange: old a = %d, new a = %d\n", result, a);
    ASSERT(30, a);
    ASSERT(20, result);
    return 0;
}
