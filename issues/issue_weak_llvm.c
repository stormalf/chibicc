#include "test.h"

int no_def(void) __attribute__((weak));

int main() {
  if (no_def)
    return 1;
  printf("OK\n");
  return 0;
}
