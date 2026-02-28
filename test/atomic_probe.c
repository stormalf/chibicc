#include "test.h"

int main(void) {
  _Atomic int a = 1, b = 2;
  int c = 3;
  a += 1;
  b += 1;
  c += 1;

  typedef _Atomic int AI;
  AI x = 10;
  int y = 20;
  x += 5;
  y += 5;

  ASSERT(2, a);
  ASSERT(3, b);
  ASSERT(4, c);
  ASSERT(15, x);
  ASSERT(25, y);

  // if atomic leaks to y, this can generate different code paths; value still should be sane
  ASSERT(4, _Alignof(int));
  ASSERT(4, _Alignof(y));

  printf("OK\n");
  return 0;
}
