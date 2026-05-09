#include "test.h"

const int arr[2][2] = {{1,2},{3,4}};
int g2 = arr[1][1];

int main(void) {
  printf("g2 = %d\n", g2);
  ASSERT(4, g2);
  printf("OK\n");
}
