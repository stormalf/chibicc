#include "test.h"

long double ld = 0.0L;

const int arr[2][2] = {{1,2},{3,4}};
int *const p1 = arr[1];

int g1 = ((int){77});
int g2 = arr[1][1];

const struct {
  int *a, *b, *c;
} relo = {.a = &g1, .c = &g2};
int *p2 = relo.c;
int *p1p = p1;

int main(void) {
  ASSERT(3, *p1);
  ASSERT(77, g1);
  ASSERT(4, g2);
  ASSERT(1, p2 == &g2);
  ASSERT(1, p1p == p1);
  printf("OK\n");
}
