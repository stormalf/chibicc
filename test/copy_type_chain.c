#include "test.h"

// copy_type must not create self-loops in decl_next when called
// multiple times on the same incomplete struct type.

struct flexible { int len; char data[]; };
struct flexible a = {0};
struct flexible b = {1, {42}};
struct flexible c = {2};

int main(void) {
  ASSERT(44, a.len + b.data[0] + c.len);
  printf("OK\n");
  return 0;
}
