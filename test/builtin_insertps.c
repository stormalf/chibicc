#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
  v4sf d = {1,2,3,4};
  v4sf s = {5,6,7,8};

  v4sf r;
  r = __builtin_ia32_insertps128(d, s, 0x00);
  ASSERT(5, r[0]); ASSERT(2, r[1]); ASSERT(3, r[2]); ASSERT(4, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0x10);
  ASSERT(1, r[0]); ASSERT(5, r[1]); ASSERT(3, r[2]); ASSERT(4, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0x20);
  ASSERT(1, r[0]); ASSERT(2, r[1]); ASSERT(5, r[2]); ASSERT(4, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0x30);
  ASSERT(1, r[0]); ASSERT(2, r[1]); ASSERT(3, r[2]); ASSERT(5, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0x40);
  ASSERT(6, r[0]); ASSERT(2, r[1]); ASSERT(3, r[2]); ASSERT(4, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0x80);
  ASSERT(7, r[0]); ASSERT(2, r[1]); ASSERT(3, r[2]); ASSERT(4, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0xC0);
  ASSERT(8, r[0]); ASSERT(2, r[1]); ASSERT(3, r[2]); ASSERT(4, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0x01);
  ASSERT(0, r[0]); ASSERT(2, r[1]); ASSERT(3, r[2]); ASSERT(4, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0x22);
  ASSERT(1, r[0]); ASSERT(0, r[1]); ASSERT(5, r[2]); ASSERT(4, r[3]);

  r = __builtin_ia32_insertps128(d, s, 0x33);
  ASSERT(0, r[0]); ASSERT(0, r[1]); ASSERT(3, r[2]); ASSERT(5, r[3]);

  return 0;
}
