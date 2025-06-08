#include <stdio.h>
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef unsigned long size_t;
typedef uint32 pg_crc32c;

#define NULL ((void *)0)

// Dummy versions of intrinsics (just XOR for testing logic)
uint32 _mm_crc32_u64(uint32 crc, uint64 data) {
  return crc ^ (uint32)(data ^ (data >> 32));
}

uint32 _mm_crc32_u32(uint32 crc, uint32 data) {
  return crc ^ data;
}

uint32 _mm_crc32_u8(uint32 crc, uint8 data) {
  return crc ^ data;
}

pg_crc32c pg_comp_crc32c_sse42(pg_crc32c crc, const void *data, size_t len) {
  const uint8 *p = data;
  const uint8 *pend = p + len;

#ifdef __x86_64__
  while (p + 8 <= pend) {
    crc = _mm_crc32_u64(crc, *((const uint64 *)p));
    p += 8;
  }

  if (p + 4 <= pend) {
    crc = _mm_crc32_u32(crc, *((const uint32 *)p));
    p += 4;
  }
#else
  while (p + 4 <= pend) {
    crc = _mm_crc32_u32(crc, *((const uint32 *)p));
    p += 4;
  }
#endif

  while (p < pend) {
    crc = _mm_crc32_u8(crc, *p);
    p++;
  }

  return crc;
}

int main() {
  char data[] = "HelloWorld";  // 10 bytes
  pg_crc32c crc = 0;

  // This should go through all paths: 8-byte, 2-byte, 1-byte
  crc = pg_comp_crc32c_sse42(crc, data, sizeof(data) - 1);  // Don't include NUL
  printf("crc=%d\n") ;
  printf("sizeof(data)=%ld\n", sizeof(data));
  // Print (you can compare values if needed)
  return crc != 0;  // Non-zero CRC expected
}
