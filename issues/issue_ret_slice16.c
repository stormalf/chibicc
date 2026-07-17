#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  char *p;
  size_t n;
} Slice;  /* 16 bytes: {ptr, i64} */

static Slice make_slice(char *buf, size_t n) {
  Slice s;
  s.p = buf;
  s.n = n;
  return s;  /* returned by value -> in registers per new ABI */
}

int main(void) {
  char buf[8] = {1,2,3,4,5,6,7,8};
  Slice s = make_slice(buf, 8);
  if (s.p != buf || s.n != 8) {
    printf("FAILED: returned 16-byte struct corrupted p=%p buf=%p n=%zu\n",
           (void*)s.p, (void*)buf, s.n);
    return 1;
  }
  size_t sum = 0;
  for (size_t i = 0; i < s.n; i++) sum += (size_t)s.p[i];
  if (sum != 36) { printf("FAILED sum=%zu\n", sum); return 1; }
  printf("OK 16-byte struct returned by value\n");
  return 0;
}
