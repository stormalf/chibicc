#include <stdint.h>
#include <stdio.h>
void DoCheck(uint32_t dwSomeValue)
{
   uint32_t dwRes;

   // Assumes dwSomeValue is not zero.
   asm ("bsfl %1 , %0 ;"
     : "=r" (dwRes)
     : "r" (dwSomeValue)
     : "cc");

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