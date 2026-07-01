#include "test.h"

int main() {
  int x = 0;
  __asm__ __volatile__ ("addl $1, %0" : "+r"(x));
  if (x != 1)
    return 1;
  return 0;
}
