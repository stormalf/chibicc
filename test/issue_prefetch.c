// test/builtin_prefetch_fail.c
#include "test.h"
struct S {
  int *entries;
};

#define PREFETCH_NEIGHBORHOOD(x) __builtin_prefetch(x.entries)

int main() {
  struct S s;
  PREFETCH_NEIGHBORHOOD(s);
  printf("Ok\n");
  return 0;
}