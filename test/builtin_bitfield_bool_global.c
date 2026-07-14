#include "test.h"

void cb(void);

struct bool_bitfield_global {
  _Bool b : 1;
  int x;
  void (*f)(void);
};

struct bool_bitfield_global g[2] = {
  { 1, 5, cb },
  { 0, 7, 0 },
};

void cb(void) {}

int main() {
  ASSERT(1, g[0].b);
  ASSERT(5, g[0].x);
  ASSERT(0, g[1].b);
  ASSERT(7, g[1].x);
  ASSERT((int)(long)cb, (int)(long)g[0].f);
  return 0;
}
