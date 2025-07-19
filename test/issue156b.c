#include <stdint.h>
#include "test.h"

void asmfunc(void) {
  const uint32_t ecx = 0;
  uint32_t eax, edx;
  // Use the raw opcode for xgetbv for compatibility with older toolchains.
  __asm__ volatile (
    ".byte 0x0f, 0x01, 0xd0\n"
    : "=a"(eax), "=d"(edx) : "c" (ecx));
    ASSERT(7, eax);
    ASSERT(0, edx);
    printf("eax=%d, edx=%d\n", eax, edx);
}

int main() {

    asmfunc();
    return 0;
}