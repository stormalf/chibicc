#include <stdio.h>
#include <string.h>
#include <stdint.h>

size_t test_func(unsigned char *dst, const unsigned char *src, int srclen) {
  uint8_t *out = (uint8_t *)dst;
  int i = 0;
  int stride = 48;
  int wrap_cnt = 0;
  
  for (; i + 100 <= srclen; i += 96) {
    int until_nl = stride - wrap_cnt;
    if (until_nl > 32) {
      out[0] = 'A' + (i / 96);
      out += 32;
      wrap_cnt += 32;
    } else {
      out[0] = 'a' + (i / 96);
      out += until_nl + 1;
      wrap_cnt = 32 - until_nl;
    }
  }
  
  return (size_t)(out - (uint8_t *)dst);
}

int main() {
  unsigned char buf[512] = {0};
  unsigned char src[256];
  memset(src, 0x41, sizeof(src));
  
  size_t written = test_func(buf, src, 200);
  
  printf("written=%zu\n", written);
  for (int i = 0; i < (int)written && i < 20; i++) {
    printf("%02x ", buf[i]);
  }
  printf("\n");
  
  if (written > 0 && buf[0] != 0)
    return 0;
  else
    return 1;
}
