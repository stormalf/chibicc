#include "test.h"
#include <x86intrin.h>

int main() {
  unsigned int r;

  /* control encoding: (len << 8) | start */
  r = __bextri_u32(0xDEADBEEF, (8 << 8) | 0);
  ASSERT(0xEF, r);

  r = __bextri_u32(0xDEADBEEF, (8 << 8) | 16);
  ASSERT(0xAD, r);

  r = __bextri_u32(0xDEADBEEF, (32 << 8) | 0);
  ASSERT(0xDEADBEEF, r);

  r = __bextri_u32(0xDEADBEEF, (1 << 8) | 31);
  ASSERT(0x1, r);

  r = __bextri_u32(0xDEADBEEF, (8 << 8) | 32);
  ASSERT(0x0, r);

  r = __bextri_u32(0xDEADBEEF, (8 << 8) | 24);
  ASSERT(0xDE, r);

  unsigned long long r64;
  r64 = __bextri_u64(0xABCDEF0123456789ULL, (16 << 8) | 0);
  LASSERT(0x6789, r64);

  r64 = __bextri_u64(0xABCDEF0123456789ULL, (16 << 8) | 32);
  LASSERT(0xEF01, r64);

  r64 = __bextri_u64(0xABCDEF0123456789ULL, (1 << 8) | 63);
  LASSERT(0x1, r64);

  r64 = __bextri_u64(0xABCDEF0123456789ULL, (8 << 8) | 64);
  LASSERT(0x0, r64);

  printf("OK\n");
  return 0;
}
