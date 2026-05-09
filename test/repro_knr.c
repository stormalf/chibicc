#include "test.h"
static int byte_swap(word)
int word;
{
  return word;
}

int main() {
  ASSERT(0x1234, byte_swap(0x1234));
  return 0;
}
