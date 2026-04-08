#include <stdbit.h>
#include "test.h"
#include <stdio.h>

int main(void) {
  // ---- trailing zeros ----
  ASSERT(4, stdc_trailing_zeros((unsigned int)16));
  ASSERT(0, stdc_trailing_zeros((unsigned int)1));
  ASSERT(1, stdc_trailing_zeros((unsigned int)2));
  ASSERT(3, stdc_trailing_zeros((unsigned int)8));

  ASSERT(4, stdc_trailing_zeros((unsigned long)16));
  ASSERT(4, stdc_trailing_zeros((unsigned long long)16));

  // non power of two
  ASSERT(1, stdc_trailing_zeros((unsigned int)6));  // 110b

  // ---- count ones ----
  ASSERT(1, stdc_count_ones((unsigned int)8));
  ASSERT(2, stdc_count_ones((unsigned int)10)); // 1010b
  ASSERT(4, stdc_count_ones((unsigned int)15)); // 1111b

  ASSERT(1, stdc_count_ones((unsigned long)8));
  ASSERT(1, stdc_count_ones((unsigned long long)8));

  // ---- has single bit ----
  ASSERT(1, stdc_has_single_bit((unsigned int)1));
  ASSERT(1, stdc_has_single_bit((unsigned int)8));
  ASSERT(0, stdc_has_single_bit((unsigned int)10));
  ASSERT(0, stdc_has_single_bit((unsigned int)0));

  ASSERT(1, stdc_has_single_bit((unsigned long)16));
  ASSERT(0, stdc_has_single_bit((unsigned long long)18));

  // ---- small integer types (promotion checks) ----
  ASSERT(3, stdc_trailing_zeros((unsigned char)8));
  ASSERT(1, stdc_count_ones((unsigned char)8));
  ASSERT(1, stdc_has_single_bit((unsigned char)8));

  ASSERT(2, stdc_count_ones((unsigned short)3));
  ASSERT(0, stdc_has_single_bit((unsigned short)3));

  printf("OK\n");
  return 0;
}
