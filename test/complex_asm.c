#include "test.h"

int main() {
  int a = 10, b = 20;
  int result = 5;

  __asm__ volatile (
      "add %[src], %[dst]\n"
      : [dst] "+r" (result)
      : [src] "r" (a + b)
  );

  printf("Result = %d\n", result);
  ASSERT(35, result);
  return 0;
}