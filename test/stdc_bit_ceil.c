#include "test.h"

int main() {
  ASSERT(1, __builtin_stdc_bit_ceil(0));
  ASSERT(1, __builtin_stdc_bit_ceil(1));
  ASSERT(2, __builtin_stdc_bit_ceil(2));
  ASSERT(4, __builtin_stdc_bit_ceil(3));
  ASSERT(4, __builtin_stdc_bit_ceil(4));
  ASSERT(8, __builtin_stdc_bit_ceil(5));
  ASSERT(8, __builtin_stdc_bit_ceil(7));
  ASSERT(8, __builtin_stdc_bit_ceil(8));
  ASSERT(16, __builtin_stdc_bit_ceil(9));

  ASSERT(1, __builtin_stdc_bit_ceil(0U));
  ASSERT(1, __builtin_stdc_bit_ceil(1U));
  ASSERT(2, __builtin_stdc_bit_ceil(2U));
  ASSERT(4, __builtin_stdc_bit_ceil(3U));

  ASSERT(1, __builtin_stdc_bit_ceil(0UL));
  ASSERT(1, __builtin_stdc_bit_ceil(1UL));
  ASSERT(2, __builtin_stdc_bit_ceil(2UL));
  ASSERT(4, __builtin_stdc_bit_ceil(3UL));

  ASSERT(1, __builtin_stdc_bit_ceil(0ULL));
  ASSERT(1, __builtin_stdc_bit_ceil(1ULL));
  ASSERT(2, __builtin_stdc_bit_ceil(2ULL));
  ASSERT(4, __builtin_stdc_bit_ceil(3ULL));

  printf("OK\n");
  return 0;
}
