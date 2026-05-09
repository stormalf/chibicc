#include "test.h"

struct S {
  int x;
};

struct S s __attribute__((aligned(16)));

int main(void)
{
  /* Check that alignment is applied */
  if (((unsigned long)&s % 16) != 0) {
    printf("alignment failed\n");
    return 1;
  }

  printf("OK\n");
  return 0;
}
