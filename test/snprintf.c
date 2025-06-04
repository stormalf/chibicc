#include <stdio.h>
#include "test.h"
int main() {
  char buf[64];
  int n = snprintf(buf, sizeof(buf), "%.8g", 10000000.1);
  printf("buf = \"%s\"\n", buf);
  printf("n = %d\n", n);
  ASSERT(8, n);
  return 0;
}
