#include "test.h"

static int seq[16];
static int nseq;

int f(int v) {
  seq[nseq++] = v;
  return v;
}

static void reset_seq(void) {
  nseq = 0;
}

static void check(char *op, int *expect, int len) {
  for (int i = 0; i < len; i++)
    ASSERT(expect[i], seq[i]);

  ASSERT(len, nseq);
  printf("%s ok\n", op);

  reset_seq();
}

int main(void) {
  int e12[]  = {1, 2};
  int e123[] = {1, 2, 3};

  f(1) | f(2);
  check("|", e12, 2);

  f(1) & f(2);
  check("&", e12, 2);

  f(1) ^ f(2);
  check("^", e12, 2);

  f(1) << f(2);
  check("<<", e12, 2);

  f(1) >> f(2);
  check(">>", e12, 2);

  f(1) | f(2) | f(3);
  check("| chain", e123, 3);

  f(1) & f(2) & f(3);
  check("& chain", e123, 3);

  f(1) ^ f(2) ^ f(3);
  check("^ chain", e123, 3);

  printf("OK\n");
  return 0;
}