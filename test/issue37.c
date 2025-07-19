#include "test.h"


int main() {
  int r = ({
    int x;
    goto label;
label:
    x = 42;
    ASSERT(42, x);
    x;
  });
  return 0;
}