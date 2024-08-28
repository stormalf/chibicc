#include "test.h"
#include <stdbool.h>

#define BANE         0x8000000000000000
#define BANE1        0x8000000000000001
#define BANE2        0x8000000000000002
#define IMAX         0x7fffffffffffffff
#define IMAX2        0xfffffffffffffffd
#define I128(HI, LO) ((LO) | (unsigned __int128)(HI) << 64)

__int128 add128(__int128 x, __int128 y) {
  return x + y;
}

__int128 sub128x5(__int128 a, __int128 b, __int128 c, __int128 d, __int128 e) {
  return a - b - c - d - e;
}

__int128 sub128x6(int f, __int128 a, __int128 b, __int128 c, __int128 d,
                  __int128 e) {
  return f - a - b - c - d - e;
}


void testDivu128(void) {
  unsigned __int128 x, y;
    x = I128(0, 2);
  y = I128(-1ul, -1ul);
  ASSERT128(I128(0, 0), x / y);

}

int main() {
    testDivu128();
    return 0;
}