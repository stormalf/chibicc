#include <stdio.h>
#include <stdint.h>

struct S {
  uint64_t x : 64;
};

int main() {
  struct S s = {0};
  s.x = 0x123456789ABCDEF0;
  printf("s.x = %lx (expected 123456789abcdef0)\n", s.x);
  if (s.x != 0x123456789ABCDEF0) {
    printf("BUG: s.x is %lx, expected 123456789abcdef0\n", s.x);
    return 1;
  }
  printf("OK\n");
  return 0;
}
