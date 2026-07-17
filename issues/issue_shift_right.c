#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* mirrors libcrux shift_right_94 but operates on a single int16 */
static int16_t ref_shift(int16_t x) {
  return (int16_t)((uint32_t)(int32_t)x >> (uint32_t)(int32_t)15);
}
/* what a buggy signed-shift compiler would produce */
static int16_t buggy_shift(int16_t x) {
  return (int16_t)(x >> 15);
}

int main(void) {
  int fails = 0;
  for (int v = -32768; v <= 32767; v++) {
    int16_t x = (int16_t)v;
    int16_t a = ref_shift(x);
    int16_t b = buggy_shift(x);
    if (a != b) {
      printf("DIFF x=%d ref=%d buggy=%d\n", x, a, b);
      fails++;
      if (fails > 8) break;
    }
  }
  if (fails) { printf("FAILED: shift_right semantics differ (signed vs unsigned)\n"); return 1; }
  printf("OK shift_right_94 semantics correct\n");
  return 0;
}
