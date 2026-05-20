#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main() {
  unsigned char out[512];
  memset(out, 0xAA, sizeof(out));
  unsigned char *p = out;
  
  *p++ = 'H';
  *p++ = 'e';
  *p++ = 'l';
  *p++ = 'l';
  *p++ = 'o';
  
  size_t n = p - out;
  printf("n=%zu, out=%.*s\n", n, (int)n, out);
  
  // test pointer arithmetic with optimization
  int i = 0;
  unsigned char *q = out;
  i += 32;
  q += 32;
  *q = '!';
  
  // test p[i++]
  unsigned char buf2[10];
  int j = 0;
  buf2[j++] = 'X';
  buf2[j++] = 'Y';
  buf2[j++] = 'Z';
  
  printf("buf2 = %.*s, out[32] = %c\n", 3, buf2, out[32]);
  
  // Test compound assignment with pointer
  unsigned char *r = out + 100;
  r += 10;
  *r = '?';
  printf("out[110] = %c\n", out[110]);
  
  // Simulate the actual pattern from encode_base64_avx2
  uint8_t *dst = out;
  int idx = 0;
  int stride = 0;
  
  // Test out += variable
  dst = out + 200;
  int written = 5;
  dst += written;
  *dst = '@';
  printf("out[205] = %c\n", out[205]);
  
  return 0;
}
