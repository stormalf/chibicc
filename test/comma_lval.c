#include "test.h"

int main() {
  // (expr, lval) = val  — comma expression yielding an lvalue
  ASSERT(5, ({ int i=2, j=3; (i=5,j)=6; i; }));
  ASSERT(6, ({ int i=2, j=3; (i=5,j)=6; j; }));
  return 0;
}
