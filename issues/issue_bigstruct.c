#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  int16_t data[512];  /* 1024 bytes */
  uint8_t extra;
} BigStruct;

static BigStruct make_big(int seed) {
  BigStruct s;
  for (int i = 0; i < 512; i++) s.data[i] = (int16_t)(seed + i);
  s.extra = (uint8_t)(seed & 0xff);
  return s;
}

static int check_big(BigStruct *s, int seed) {
  for (int i = 0; i < 512; i++) {
    if (s->data[i] != (int16_t)(seed + i)) {
      printf("MISMATCH at [%d]: got %d expected %d\n", i, (int)s->data[i], (int)(int16_t)(seed + i));
      return 1;
    }
  }
  if (s->extra != (uint8_t)(seed & 0xff)) {
    printf("EXTRA MISMATCH: got %d expected %d\n", (int)s->extra, (int)(uint8_t)(seed & 0xff));
    return 1;
  }
  return 0;
}

int main(void) {
  BigStruct s = make_big(42);
  int r = check_big(&s, 42);
  if (r) { printf("FAILED\n"); return 1; }
  printf("OK big struct by-value return works\n");
  return 0;
}
