#include "test.h"

typedef __int128 int128;
typedef unsigned __int128 uint128;

// Aligned struct (natural alignment for __int128 is 16)
struct A {
  char c;
  uint128 val;
};

// Packed struct (misaligned __int128 starting at offset 1)
struct P {
  char c;
  uint128 val;
} __attribute__((packed));

int main() {
  // 1. Unsigned division and modulo
  // u1 = 10 * 2^64
  uint128 u1 = (uint128)10 << 64; 
  uint128 u2 = 3;
  uint128 uq = u1 / u2;
  uint128 ur = u1 % u2;

  // q = (10 * 2^64) / 3 = 61489146912365172053
  // High 64 bits should be 3.
  // Low 64 bits should be 6148914691236517205.
  ASSERT(3, (long)(uq >> 64));
  ASSERT(6148914691236517205ULL, (unsigned long)(uq & 0xFFFFFFFFFFFFFFFFULL));
  ASSERT(1, (long)ur);

  // 2. Signed division and modulo
  int128 s1 = (int128)-100;
  int128 s2 = 3;
  ASSERT(-33, (long)(s1 / s2));
  ASSERT(-1, (long)(s1 % s2));

  int128 s3 = 100;
  int128 s4 = -3;
  ASSERT(-33, (long)(s3 / s4));
  ASSERT(1, (long)(s3 % s4));

  int128 s5 = -100;
  int128 s6 = -3;
  ASSERT(33, (long)(s5 / s6));
  ASSERT(-1, (long)(s5 % s6));

  // 3. Large signed values crossing 64-bit boundary
  // s7 = 5 * 2^70
  int128 s7 = (int128)5 << 70;
  int128 s8 = (int128)1 << 60;
  // Result should be 5 * 2^10 = 5120
  ASSERT(5120, (long)(s7 / s8));

  int128 s9 = -((int128)5 << 70);
  ASSERT(-5120, (long)(s9 / s8));

  // 4. Power of 2 division
  uint128 u3 = (uint128)1 << 100;
  uint128 u4 = (uint128)1 << 96;
  ASSERT(16, (long)(u3 / u4));

  // 5. Modulo with large result
  uint128 u5 = ((uint128)1 << 64) + 10;
  ASSERT(10, (long)(u5 % ((uint128)1 << 64)));

  // 6. Packed struct (potentially misaligned)
  struct P p_inst;
  p_inst.val = (uint128)20 << 64;
  uint128 uq_p = p_inst.val / 3;
  ASSERT(6, (long)(uq_p >> 64)); // (20 * 2^64) / 3 -> high part is 6
  ASSERT(2, (long)(p_inst.val % 3)); // (20 * 2^64) % 3 -> 2

  // 7. Aligned struct
  struct A a_inst;
  a_inst.val = (uint128)15 << 64;
  ASSERT(5, (long)(a_inst.val / 3 >> 64)); // (15 * 2^64) / 3 -> high part is 5
  ASSERT(0, (long)(a_inst.val % 3)); // (15 * 2^64) % 3 -> 0

  printf("OK\n");
  return 0;
}
