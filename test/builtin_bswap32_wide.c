#include "test.h"

int main() {
  unsigned long long x = 0x1122334455667788ULL;
  unsigned int r = __builtin_bswap32((unsigned int)x);
  ASSERT(0x88776655, r);
  return 0;
}
