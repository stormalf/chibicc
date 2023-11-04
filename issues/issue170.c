


#include <stdbool.h>
#include <complex.h>
#include <tgmath.h>
#include <inttypes.h>

struct named_init_test {
  int a;
  int b;
};

extern void structfunc(struct named_init_test);

int main(int argc, char **argv)
{
  struct named_init_test nit = {
    .a = 3,
    .b = 5,
  };

  for (int loop_var = 0; loop_var < 3; loop_var++)
  {
    nit.a += nit.b;
  }

  structfunc((struct named_init_test){1, 0});

  return nit.a != 0;
}
