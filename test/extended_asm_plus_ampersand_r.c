// Test that "+&r" (read-write with early clobber) constraint works in extended asm.
#include "test.h"

int main() {
  unsigned short x = 42, y = 7, z = 0;
  __asm__ ("cmpw %2,%1\n movw %1,%0\n cmovgw %2,%1\n cmovgw %0,%2"
           : "=&r"(z), "+&r"(x), "+r"(y) : : "cc");
  return 0;
}
