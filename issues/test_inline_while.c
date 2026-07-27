#include "test.h"

static inline int sum_while(int n) {
  int total = 0;
  while (n) {
    total += n;
    n--;
  }
  return total;
}

static inline int call_sum_while(int n) {
  return sum_while(n);
}

int main() {
  ASSERT(55, call_sum_while(10));
  ASSERT(0, call_sum_while(0));
  ASSERT(1, call_sum_while(1));
  ASSERT(5050, call_sum_while(100));
  return 0;
}
