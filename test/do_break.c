#include "test.h"

int main() {
  int i = 0;
  do {
    if (i == 5)
      break;
    i++;
  } while (i < 10);
  ASSERT(5, i);
  printf("OK\n");
  return 0;
}
