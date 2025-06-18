#include <stdio.h>
#include <limits.h>

int main() {
    unsigned long long expected_ull = 18446744073709551615ULL;
    unsigned long expected_ul = 18446744073709551615UL;

    // Assuming SIZEOF_LONG == 8
    unsigned long test_ul = 0xFFFFFFFFFFFFFFFFUL;

    printf("Expected ULL: %llu\n", expected_ull);
    printf("Expected UL: %lu\n", expected_ul);
    printf("Test UL: %lu\n", test_ul);

    if (test_ul == expected_ul) {
        printf("Test UL Passed\n");
    } else {
        printf("Test UL Failed\n");
    }

    printf("unsigned int %ld\n", sizeof(unsigned int));
    printf("unsigned long %ld\n", sizeof(unsigned long));
    // For unsigned int, ensure correct size handling
    if (sizeof(unsigned int) == 8) {
        unsigned int test_ui = 0xFFFFFFFFFFFFFFFFU;
        printf("Test UI: %u\n", test_ui);
        if (test_ui == expected_ull) {
            printf("Test UI Passed\n");
        } else {
            printf("Test UI Failed\n");
        }
    } else {
        printf("Skipping unsigned int test as its size is not 64-bit.\n");
    }

    return 0;
}
