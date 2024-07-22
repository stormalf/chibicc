
#include <stdio.h>
#include "test.h"

// Check long long types.
#define BIG64 18446744073709551615ull
#define BIG32 4294967295ul
#define BIG_OK (BIG64 / BIG32 == 4294967297ull && BIG64 % BIG32 == 0)
#if !BIG_OK
  #error "your preprocessor is broken"
#endif
#if BIG_OK
#else
  #error "your preprocessor is broken"
#endif
static long long int bignum = -9223372036854775807LL;
static unsigned long long int ubignum = BIG64;

int main(void)
{
    printf("%lld\n", bignum);
    printf("%llu\n", ubignum);
  return 0;
}