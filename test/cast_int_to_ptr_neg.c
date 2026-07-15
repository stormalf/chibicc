#include "test.h"

int main() {
  void *p = (void *)-1;
  ASSERT(1, p == (void *)-1);
  ASSERT(0, p == (void *)0);
  void *q = (void *)(unsigned)0xFFFFFFFFu;
  ASSERT(0, q == (void *)-1);
  ASSERT(1, q == (void *)(unsigned long)0xFFFFFFFFu);
  return 0;
}
