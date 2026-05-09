#include "test.h"
int main() {
  ASSERT(4, ({ typedef struct T T; struct T { int x; }; sizeof(T); }));
  printf("OK\n");
  return 0;
}
