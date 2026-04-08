#include "test.h"
int global = 0;
void fn(int x, int arr[++global]) {
  ASSERT(1, global);
}
int main() {
  fn(0, 0);
  global = 0;
  fn(0, 0);
  printf("OK\n");
  return 0;
}