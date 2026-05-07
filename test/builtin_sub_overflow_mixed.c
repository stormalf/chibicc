#include "test.h"

typedef unsigned long long u64;
typedef long long i64;
typedef unsigned int u32;
typedef int i32;
typedef unsigned short u16;
typedef short i16;

typedef int bool;

int main() {
  // u16 -> i16 boundary
  {
    u16 x = 32768;
    i16 r16 = 0;
    bool of16 = __builtin_sub_overflow(0, x, &r16);
    ASSERT(0, of16);
    ASSERT(-32768, r16);

    x = 32769;
    of16 = __builtin_sub_overflow(0, x, &r16);
    ASSERT(1, of16);
    ASSERT(32767, r16);
  }

  // u32 -> i32 boundary
  {
    u32 x = 2147483648U;
    i32 r32 = 0;
    bool of32 = __builtin_sub_overflow(0, x, &r32);
    ASSERT(0, of32);
    ASSERT(-2147483648, r32);

    x = 2147483649U;
    of32 = __builtin_sub_overflow(0, x, &r32);
    ASSERT(1, of32);
    ASSERT(2147483647, r32);
  }

  // u64 -> i64 boundary
  u64 a = 9223372036854775808ULL;
  i64 r = 0;
  bool of = __builtin_sub_overflow(0, a, &r);
  ASSERT(0, of);
  LASSERT(-9223372036854775808LL, r);

  u64 b = 9223372036854775809ULL;
  of = __builtin_sub_overflow(0, b, &r);
  ASSERT(1, of);
  LASSERT(9223372036854775807LL, r);

  printf("OK\n");
  return 0;
}
