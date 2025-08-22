#include "test.h"
#include <stdbool.h>

static bool test_unsigned(unsigned a, unsigned *r) {
    *r = a + 1;
    return true;
}

static bool test_ulong(unsigned long a, unsigned long *r) {
    *r = a + 10;
    return true;
}

static bool test_ull(unsigned long long a, unsigned long long *r) {
    *r = a + 100;
    return true;
}

// Generic macro using pointer type
#define add_generic(a, r) \
    _Generic((r), \
        unsigned*: test_unsigned(a, (unsigned *)(r)), \
        unsigned long*: test_ulong(a, (unsigned long *)(r)), \
        unsigned long long*: test_ull(a, (unsigned long long *)(r)))

int main(void) {
    unsigned u = 1;
    unsigned long ul = 10;
    unsigned long long ull = 100;

    unsigned ru = 0;
    unsigned long rul = 0;
    unsigned long long rull = 0;

    add_generic(u, &ru);
    add_generic(ul, &rul);
    add_generic(ull, &rull);

    printf("Results: ru=%u, rul=%lu, rull=%llu\n", ru, rul, rull);
    ASSERT(2, ru);
    ASSERT(20, rul);
    ASSERT(200, rull);

    return 0;
}
