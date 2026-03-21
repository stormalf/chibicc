// test/atomic_is_lock_free_fail.c
#include <stdatomic.h>
#include "test.h"
int main() {
  int x;
  int y;
  y = __atomic_is_lock_free(sizeof(x), &x);
  printf("%d\n", y);
  ASSERT(1, y);
  return 0;
}
