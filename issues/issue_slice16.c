#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  char *p;
  size_t n;
} Slice;  /* 16 bytes: {ptr, i64} */

static size_t use_slice(Slice s) {
  /* read both fields; verify the pointer points to the right data */
  size_t sum = 0;
  for (size_t i = 0; i < s.n; i++)
    sum += (size_t)s.p[i];
  return sum + (size_t)(uintptr_t)s.p;  /* include pointer value */
}

int main(void) {
  char buf[8] = {10, 20, 30, 40, 50, 60, 70, 80};
  Slice s;
  s.p = buf;
  s.n = 8;
  size_t r = use_slice(s);
  printf("result=%zu (expect=%zu)\n", r, (size_t)(10+20+30+40+50+60+70+80) + (size_t)(uintptr_t)buf);
  if (r != (size_t)(10+20+30+40+50+60+70+80) + (size_t)(uintptr_t)buf) {
    printf("FAILED: 16-byte struct with pointer passed by value is corrupted\n");
    return 1;
  }
  printf("OK 16-byte struct with pointer by value\n");
  return 0;
}
