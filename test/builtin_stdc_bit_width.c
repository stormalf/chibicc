#include <stdbit.h>
#include "test.h"

int main(void) {
    ASSERT(0, stdc_bit_width(0u));
    ASSERT(1, stdc_bit_width(1u));
    ASSERT(2, stdc_bit_width(2u));
    ASSERT(2, stdc_bit_width(3u));
    ASSERT(3, stdc_bit_width(4u));
    ASSERT(4, stdc_bit_width(8u));
    ASSERT(4, stdc_bit_width(15u));
    ASSERT(5, stdc_bit_width(16u));
    ASSERT(31, stdc_bit_width(0x7FFFFFFFu));
    ASSERT(32, stdc_bit_width(0xFFFFFFFFu));
    ASSERT(33, stdc_bit_width(0x100000000ull));
    ASSERT(64, stdc_bit_width(0xFFFFFFFFFFFFFFFFull));
    printf("OK\n");
    return 0;
}