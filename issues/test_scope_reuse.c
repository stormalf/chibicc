#include "test.h"

int test_sibling_scopes(void) {
  int sum = 0;
  {
    int a[100];
    for (int i = 0; i < 100; i++)
      a[i] = i;
    for (int i = 0; i < 100; i++)
      sum += a[i];
  }
  {
    int b[100];
    for (int i = 0; i < 100; i++)
      b[i] = i * 2;
    for (int i = 0; i < 100; i++)
      sum += b[i];
  }
  return sum;
}

int main() {
  ASSERT(14850, test_sibling_scopes());
  return 0;
}
