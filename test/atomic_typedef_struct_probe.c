#include "test.h"

typedef struct { int v; } S;
typedef _Atomic(S) AS;

int main(void) {
  AS a;
  S b;
  a.v = 7;
  b.v = 9;
  ASSERT(7, a.v);
  ASSERT(9, b.v);
  printf("OK\n");
  return 0;
}
