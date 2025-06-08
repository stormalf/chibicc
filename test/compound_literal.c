#include <stdio.h>
#include "test.h"
struct Wrap {
  int (*func)();
};

int inc_global() {
  static int i = 0;
  return ++i;
}

struct Wrap global_wrap[] = {
    ((struct Wrap){inc_global}),
    {inc_global}
};

int main() {
  printf("global_wrap[0].func() = %d\n", global_wrap[0].func());
  ASSERT(2, global_wrap[0].func());
  return 0;
}

