#include <stdio.h>

int main(void) {
  unsigned int eax, edx;

  __asm__ __volatile__ (
    ".byte 0x0f, 0x01, 0xd0"   // xgetbv
    : "=a"(eax), "=d"(edx)
    : "c"(0)
  );

  printf("xgetbv eax: %08x edx: %08x\n", eax, edx);
  return 0;
}
