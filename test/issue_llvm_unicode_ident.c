// Test that non-ASCII identifiers (e.g. Unicode variable names) are correctly
// quoted in LLVM IR output so that llc can parse them.
#include "test.h"

int π = 3;

int main() {
  ASSERT(3, π);
  printf("OK\n");
  return 0;
}
