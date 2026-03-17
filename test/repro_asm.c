// repro_asm_ptr_input.c
#include "test.h"
int main() {
  int x = 5;
  int y = 0;

  __asm__(
    "movl %1, (%0)"
    :
    : "r"(&y), "r"(x)
    : "memory"
  );
  printf("y = %d\n", y);
  ASSERT(5, y);

  return 0;
}

