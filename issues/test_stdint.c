#include <byteswap.h>
#include <stdint.h>
#include <float.h>
#include <stdio.h>

uint16_t swap_bytes(uint16_t x) {
  return (x >> 8) | (x << 8);
}

int main() {
  uint16_t x = 0x1234;
  uint16_t y = swap_bytes(x);
  printf("Original: 0x%x, Swapped: 0x%x\n", x, y);
  __uint16_t a = 0x3456;
  __uint16_t b = swap_bytes(a);
  printf("Original: 0x%x, Swapped: 0x%x\n", a, b);
  return 0;
}
