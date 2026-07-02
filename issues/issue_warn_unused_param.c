// Test that parameters used as builtin overflow destination are not
// reported as unused.

#include "test.h"

static inline int uadd_overflow(unsigned a, unsigned b, unsigned *res) {
  return __builtin_uadd_overflow(a, b, res);
}

int main() {
  unsigned r;
  return uadd_overflow(1, 2, &r);
}
