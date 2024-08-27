#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include "test.h"

const uint8_t pg_leftmost_one_pos[256] = {
    0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

static inline int pg_leftmost_one_pos64(uint64_t word)
{
    int shift = 64 - 8;

    while ((word >> shift) == 0)
        shift -= 8;

    return shift + pg_leftmost_one_pos[(word >> shift) & 255];
}

static inline int pg_ceil_log2_64(uint64_t num)
{
    if (num < 2)
        return 0;
    else
        return pg_leftmost_one_pos64(num - 1) + 1;
}

static int my_log2(long num)
{
    if (num > LONG_MAX / 2)
        num = LONG_MAX / 2;

#if SIZEOF_LONG < 8
    return 2;
#else
    return pg_ceil_log2_64(num);
#endif
}

static int next_pow2_int(long num)
{
    if (num > INT_MAX / 2)
        num = INT_MAX / 2;
    int log2 = my_log2(num);
    printf("pg_ceil_log2_64=%d\n", log2);
    return 1 << log2;
}

int main()
{
    long test_values[] = {1, 2, 3, 536870912, LONG_MAX};
    for (int i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i) {
        printf("Input: %ld, next_pow2_int: %d\n", test_values[i], next_pow2_int(test_values[i]));
        if (i == 0)
            ASSERT(4, next_pow2_int(test_values[i]) );
        else if (i == 1)
            ASSERT(4, next_pow2_int(test_values[i]) );
        else if (i == 2)
            ASSERT(4, next_pow2_int(test_values[i]) );
        else if (i == 3)
            ASSERT(4, next_pow2_int(test_values[i]) );
        else if (i == 4)
            ASSERT(4, next_pow2_int(test_values[i]) );
    }
    return 0;
}
