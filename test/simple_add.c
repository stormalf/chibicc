#include "test.h"

int main() {
  unsigned char buf[64] = {0};
  unsigned char *out = buf;
  int i = 0;

  out[i++] = 'A';
  out[i++] = 'B';
  out[i++] = 'C';

  printf("buf = %s\n", buf);

  unsigned char *p = buf + 10;
  p += 5;
  *p = 'X';

  printf("buf[15] = %c\n", buf[15]);

  return strcmp(buf, "ABC") != 0 || buf[15] != 'X';
}
