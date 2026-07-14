// Test that -Wunused-variable doesn't warn when a global variable
// has a forward tentative declaration before its use.
#include "test.h"

static const int tbl[8][4];

static int use_tbl(void) {
  return tbl[0][0] + tbl[1][1];
}

static const int tbl[8][4] = {
  {1, 2, 3, 4},
  {5, 6, 7, 8},
};

int main() {
  ASSERT(7, use_tbl());
  printf("OK\n");
  return 0;
}
