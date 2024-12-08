#include <stdio.h>

struct S {
  int a;
  char b;
  int c[3];
};
int main(void) {
  struct S s = {42, .c[1] = 99};
  printf("=====%d %d %d %d %d\n", s.a, s.b, s.c[0], s.c[1], s.c[2]);
  return 0;
}

