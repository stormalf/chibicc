// chibicc -xc test/common -Itest test/liveness.c
#include "test.h"

int main() {
  int dead;    // never read/written -> should not allocate stack slot
  int alive;   // the one actually used
  alive = 10;

  // After our liveness analysis, only 'alive' should have a stack slot.
  // The compiler should produce correct code even with dead variables.
  ASSERT(10, alive);
  return 0;
}
