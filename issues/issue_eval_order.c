#include "test.h"
int main() {
  int a = 0;
  // If L-to-R: 0 1 2
  // If R-to-L: 2 1 0
  printf("%d %d %d\n", a++, a++, a++);
  return 0;
}
