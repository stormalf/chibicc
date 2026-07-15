#include "test.h"

static const int table[8][256] = {0};

int main() {
  int c0 = 1, c1 = 2;
  int x = table[0][c0] ^ table[1][c1];
  return x;
}
