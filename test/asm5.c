#include <stdint.h>
#include <stdio.h>
#include "test.h"
void DoCheck(uint32_t dwSomeValue)
{
   uint32_t dwRes;

   // Assumes dwSomeValue is not zero.
   asm ("bsfl %1 , %0 ;"
     : "=r" (dwRes)
     : "r" (dwSomeValue)
     : "cc");
   printf("%u: %u %u\n", 0, dwSomeValue, dwRes);
   ASSERT(0, dwRes);
   ASSERT(5, dwSomeValue);
   //assert(dwRes > 3);
}

void do_print(uint32_t dwSomeValue)
{
   uint32_t dwRes;

   for (uint32_t x=0; x < 5; x++)
   {
      // Assumes dwSomeValue is not zero.
      asm ("bsfl %1 , %0 ;"
        : "=r" (dwRes)
        : "r" (dwSomeValue)
        : "cc");

      printf("%u: %u %u\n", x, dwSomeValue, dwRes);
   }
}


int main() {
    uint32_t a = 5;
    DoCheck(a);
    do_print(a);

    return 0;
}