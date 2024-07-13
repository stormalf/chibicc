#include <stdint.h>
#include <stdio.h>
#include "test.h"
static inline uint32_t lj_bswap(uint32_t x)
{
  uint32_t r; __asm__("bswap %0" : "=r" (r) : "0" (x)); return r;
}


int main() {

    int a = lj_bswap(18);
    printf("%d\n", a);

    ASSERT(301989888, a);
    return 0;

}