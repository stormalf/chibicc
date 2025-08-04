#include <stdlib.h>
#include "test.h"

int main() {
  int r = system("XXXX"); // Command doesn't exist
  printf("Returned: %d\n", r);
  ASSERT(32512, r);
  return 0;
}
