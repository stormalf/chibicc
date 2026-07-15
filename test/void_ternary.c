#include "test.h"

int g;

void bar(void) {
  g = 1;
}

int c1(void) { return 1; }
int c2(void) { return 1; }

int main() {
  g = 0;
  (c1() && c2()) ? bar() : (void)0;
  ASSERT(1, g);

  g = 0;
  (0 && c2()) ? bar() : (void)0;
  ASSERT(0, g);

  g = 0;
  (c1() && 1) ? (void)0 : bar();
  ASSERT(0, g);

  return 0;
}
