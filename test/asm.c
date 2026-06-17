#include "test.h"

long asm_fn1(void) {
  long r;
  asm("mov $50, %0" : "=r"(r));
  return r;
}

long asm_fn2(void) {
  long r;
  asm volatile("mov $55, %0" : "=r"(r));
  return r;
}

int main() {
  ASSERT(50, asm_fn1());
  ASSERT(55, asm_fn2());

  printf("OK\n");
  return 0;
}
