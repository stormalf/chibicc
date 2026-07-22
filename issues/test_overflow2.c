#include "test.h"
int main() {
  long long ex_a = 0x100000000LL;
  long long ex_b = 1;
  int ex_res;
  int ex_overflow = __builtin_add_overflow(ex_a, ex_b, &ex_res);
  printf("ex_overflow => %d\n", ex_overflow);
  printf("ex_res => %d\n", ex_res);
  return 0;
}
