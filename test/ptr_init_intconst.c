#include "test.h"

typedef unsigned char char_u;
typedef long long_i;
typedef unsigned long long_u;

struct opt {
  char *name;
  long_u flags;
  char_u *var;
  char_u *def_val[2];
};

static long g_chi = 0;

// `def_val` pointer members are initialized from integer constants cast to
// pointers (e.g. (char_u *)10L). They must keep the integer value and not be
// dropped to NULL.
static struct opt options[] = {
  {(char *)"other", 0, (char_u *)&g_chi, {(char_u *)5L, (char_u *)0L}},
  {(char *)"chistory", 1, (char_u *)&g_chi, {(char_u *)10L, (char_u *)0L}},
};

int main() {
  long v0 = (long)(long_i)options[0].def_val[0];
  long v1 = (long)(long_i)options[1].def_val[0];
  ASSERT(5, v0);
  ASSERT(10, v1);

  g_chi = v1;
  ASSERT(10, g_chi);
  return 0;
}
