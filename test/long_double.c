// test-tanl.c
#include "test.h"
#include <math.h>



#define ASSERT(cond) \
  do { if (!(cond))  __builtin_abort(); } while (0)

int main(void) {
  static const double inputs[] = {
    -1.0,
    -0.5,
    -0.1,
     0.0,
     0.1,
     0.5,
     1.0
  };

  for (int i = 0; i < (int)(sizeof(inputs)/sizeof(*inputs)); i++) {
    double x = inputs[i];

    long double ld = (long double)x;
    long double tld = tanl(ld);
    double td = tan(x);

    /* Compare in long double domain */
    long double diff = fabsl((long double)td - tld);

    ASSERT(diff < 1e-12L);
  }
  double x1 = 0.5;
  ASSERT(fabs(tan(x1) - tanl((long double)x1)) < 1e-12);
  printf("Ok \n");

  return 0;
}
