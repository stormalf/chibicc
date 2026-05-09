#include <stdbit.h>
#include "test.h"

//#define __builtin_stdc_has_single_bit stdc_has_single_bit

int main(void) {
    ASSERT(1, stdc_has_single_bit(1u));
    ASSERT(1, stdc_has_single_bit(2u));
    ASSERT(1, stdc_has_single_bit(128u));
    ASSERT(1, stdc_has_single_bit(0x80000000u));
    ASSERT(0, stdc_has_single_bit(0u));
    ASSERT(0, stdc_has_single_bit(3u));
    ASSERT(0, stdc_has_single_bit(7u));
    unsigned x = 1;
    for (int i = 0; i < 100000; i++)
        if (__builtin_stdc_has_single_bit(x) != 1)
            return 1;
    printf("OK\n");
    return 0;
}