#include "test.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Reproducer for CPython's ctypes ms_struct bitfield layout expectations.
// With GCC/Clang this attribute switches to MSVC-compatible bitfield packing.

struct __attribute__((ms_struct)) BITS_msvc {
  signed int A : 1, B : 2, C : 3, D : 4, E : 5, F : 6, G : 7, H : 8, I : 9;
  signed short M : 1, N : 2, O : 3, P : 4, Q : 5, R : 6, S : 7;
};


// ---------------------------------------------------------------------------
// The struct under test — verbatim from CPython
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
struct __attribute__((ms_struct)) Example_gh_86098_pack {
    uint8_t  a :8;
    uint8_t  b :8;
    uint32_t c :16;
};
#pragma pack(pop)


int main() {
  struct BITS_msvc x = {};

  x.P = 7;
  x.Q = -9;

  // Known-good layout for GCC/Clang __attribute__((ms_struct)) on x86_64:
  // - 45 bits of int fields consume 2 full 32-bit allocation units => 8 bytes
  // - short fields start at offset 8
  // P=7 and Q=-9 (5-bit signed) yields bytes 8..9 == 0xc0 0x5d.
  unsigned char *p = (unsigned char *)&x;
  if (sizeof(x) != 12)
    return 1;
  if (p[6] != 0 || p[7] != 0)
    return 2;
  if (p[8] != 0xc0 || p[9] != 0x5d)
    return 3;

  struct Example_gh_86098_pack value;
  memset(&value, 0, sizeof(value));

  ASSERT(6, sizeof(struct Example_gh_86098_pack));
  ASSERT(1, _Alignof(struct Example_gh_86098_pack));

  printf("OK\n");
  return 0;
}

