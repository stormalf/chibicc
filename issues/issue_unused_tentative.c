#include "test.h"

static const int tbl[8][256];
int foo(int c0, int c1) {
  return tbl[0][c0] ^ tbl[1][c1];
}
static const int tbl[8][256] = {0};

int main() {
  ASSERT(0, foo(1, 4));
  ASSERT(0, foo(2, 8));
  return 0;
}
