#include <stdint.h>
#include <features.h>
#include <bits/types.h>
#include <inttypes.h>
#define __inline inline

/* Swap bytes in 16-bit value.  */
#define __bswap_constant_16(x)					\
  ((__uint16_t) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))


static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{
#if __GNUC_PREREQ (4, 8)
  return __builtin_bswap16 (__bsx);
#else
  return __bswap_constant_16 (__bsx);
#endif
}

int main(void)
{
    unsigned len, left, have, last = 0;
     unsigned used = 0;
  __uint16_t x = 0x1234;
  __uint16_t y = __bswap_16(x);
  return 0;
}