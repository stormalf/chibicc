#include "test.h"

int main() {
  ({ char buf[100]; sprintf(buf, "%d %d %s", 1, 2, "foo"); strcmp("1 2 foo", buf) });
  return 0;
}
