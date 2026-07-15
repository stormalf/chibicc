#include "test.h"

int main() {
  // ND_POS
  ASSERT(42, +42);

  // ND_BUILTIN_CLZ, CTZ, POPCOUNT
  ASSERT(31, __builtin_clz(1));
  ASSERT(0, __builtin_ctz(1));
  ASSERT(1, __builtin_popcount(4));
  ASSERT(8, __builtin_popcount(255));
  ASSERT(3, __builtin_popcount(7));

  // ND_EXPECT
  ASSERT(1, __builtin_expect(1, 1));

  // ND_UNREACHABLE should not crash
  if (0) __builtin_unreachable();

  // ND_BUILTIN_BSWAP
  ASSERT(0x3412, __builtin_bswap16(0x1234));
  ASSERT(0x78563412, __builtin_bswap32(0x12345678));

  // ND_PARITY
  ASSERT(1, __builtin_parity(1));
  ASSERT(0, __builtin_parity(3));
  ASSERT(1, __builtin_parity(7));

  // ND_BUILTIN_ISNAN
  ASSERT(0, __builtin_isnan(1.0));

  // ND_POS as unary plus on variable
  int x = 10;
  ASSERT(10, +x);
  ASSERT(10, +(+x));

  // ND_STDC_BIT_CEIL
  ASSERT(1, __builtin_stdc_bit_ceil(0));
  ASSERT(1, __builtin_stdc_bit_ceil(1));
  ASSERT(2, __builtin_stdc_bit_ceil(2));
  ASSERT(4, __builtin_stdc_bit_ceil(3));
  ASSERT(8, __builtin_stdc_bit_ceil(5));

  // ND_BUILTIN_ADD_OVERFLOW
  {
    int r;
    ASSERT(0, __builtin_add_overflow(1, 2, &r));
    ASSERT(3, r);
    ASSERT(1, __builtin_add_overflow(2147483647, 1, &r));
  }

  // ND_BUILTIN_SUB_OVERFLOW
  {
    int r;
    ASSERT(0, __builtin_sub_overflow(5, 3, &r));
    ASSERT(2, r);
    ASSERT(1, __builtin_sub_overflow(-2147483647 - 1, 1, &r));
  }

  // ND_BUILTIN_MUL_OVERFLOW
  {
    int r;
    ASSERT(0, __builtin_mul_overflow(3, 4, &r));
    ASSERT(12, r);
    ASSERT(1, __builtin_mul_overflow(1000000, 1000000, &r));
  }

  // ND_UADD_OVERFLOW
  {
    unsigned r;
    ASSERT(0, __builtin_uadd_overflow(1u, 2u, &r));
    ASSERT(3, r);
  }

  // ND_UMUL_OVERFLOW
  {
    unsigned r;
    ASSERT(0, __builtin_umul_overflow(3u, 4u, &r));
    ASSERT(12, r);
  }

  printf("OK\n");
  return 0;
}
