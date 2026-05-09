#include "test.h"
#include <stdint.h>
#include <stdlib.h>

void write_buf(char *buf, uint64_t val, int sz)
{
  if (sz == 1)
    *buf = (char)val;
  else if (sz == 2)
    *(uint16_t *)buf = (uint16_t)val;
  else if (sz == 4)
    *(uint32_t *)buf = (uint32_t)val;
  else if (sz == 8)
    *(uint64_t *)buf = val;
  else
    exit(1);
}

int main() {
    char buf[8];
    unsigned char val = 0xff;
    write_buf(buf, val, 1);
    unsigned char read = (unsigned char)buf[0];
    printf("read: %d\n", read);
    ASSERT(255, read);
    printf("OK\n");
}
