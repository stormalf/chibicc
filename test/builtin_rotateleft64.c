#include "test.h"

int main(void) {
  unsigned long long x = 0x0123456789ABCDEFULL;
  LASSERT(0x23456789ABCDEF01ULL, __builtin_rotateleft64(x, 8));
  LASSERT(0x0123456789ABCDEFULL, __builtin_rotateleft64(x, 0));
  LASSERT(0x0123456789ABCDEFULL, __builtin_rotateleft64(x, 64));
  LASSERT(0x123456789ABCDEF0ULL, __builtin_rotateleft64(x, 4));
  LASSERT(0x123456789ABCDEF0ULL, __builtin_rotateleft64(x, 68));
  printf("OK\n");
  return 0;
}
