/* Test range switch behavior for signed and unsigned switch expressions */
#include "test.h"
#include <stdint.h>

int main(void) {
  int r;

  /* Signed range: negative start should match when value is negative */
  int s = -1;
  r = 0;
  switch (s) {
    case -3 ... -2:
      r = -1;
      break;
    case -1 ... 1:
      r = 1;
      break;
    default:
      r = 0;
  }
  ASSERT(1, r);

  /* Unsigned range: large unsigned values must match correctly */
  unsigned int u = 0x80000000u; /* 2147483648 */
  r = 0;
  switch (u) {
    case 0x80000000u ... 0x80000010u:
      r = 2;
      break;
    default:
      r = 0;
  }
  ASSERT(2, r);

  /* Signed single-case check (equality path) */
  s = -1;
  r = 0;
  switch (s) {
    case -1:
      r = 3;
      break;
    default:
      r = 0;
  }
  ASSERT(3, r);

  puts("OK");
  return 0;
}
