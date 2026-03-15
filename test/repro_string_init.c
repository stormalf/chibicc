#include "test.h"
#include <string.h>

struct S {
  char *p;
  char a[4];
  int i;
};

int main() {
  struct S sarr[] = {
    "foobar", "baz", 11,
    "foobaz", "bar", 22,
  };
  printf("sarr[0].p = %s\n", sarr[0].p);
  printf("sarr[0].a = %s\n", sarr[0].a);
  printf("sarr[0].i = %d\n", sarr[0].i);
  printf("sarr[1].p = %s\n", sarr[1].p);
  printf("sarr[1].a = %s\n", sarr[1].a);
  printf("sarr[1].i = %d\n", sarr[1].i);
  return 0;
}
