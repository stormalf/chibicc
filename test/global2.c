#include <stdio.h>
#include "test.h"

struct Wrap {
    void *func;
};

int global;
void inc_global (void)
{
  global++;
}

struct Wrap global_wrap[] = {
    ((struct Wrap) {inc_global}),
    inc_global,
};



void test_compound_with_relocs (void)
{
  struct Wrap local_wrap[] = {
      ((struct Wrap) {inc_global}),
      inc_global,
  };
  void (*p)(void);
  p = global_wrap[0].func; p();
  printf("global_wrap[0].func = %p\n", global_wrap[0].func);
  p = global_wrap[1].func; p();
  printf("global_wrap[1].func = %p\n", global_wrap[1].func);
  p = local_wrap[0].func; p();
  printf("local_wrap[0].func = %p\n", local_wrap[0].func);
  p = local_wrap[1].func; p();
  printf("local_wrap[1].func = %p\n", local_wrap[1].func);
}

int main() {
    test_compound_with_relocs();
    return 0;
}