#include "test.h"

int main(void) {
  unsigned int x = 0x01234567u;
  ASSERT(0x23456701u, __builtin_rotateleft32(x, 8));
  ASSERT(0x01234567u, __builtin_rotateleft32(x, 0));
  ASSERT(0x01234567u, __builtin_rotateleft32(x, 32));
  ASSERT(0x12345670u, __builtin_rotateleft32(x, 4));
  ASSERT(0x12345670u, __builtin_rotateleft32(x, 36));
  printf("OK\n");
  return 0;
}
