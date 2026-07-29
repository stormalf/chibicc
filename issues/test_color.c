#include "test.h"

static const struct { char *scheme; char *dflt; } colors[] = {
  [0] = { "today", "REVERSE" },
  [1] = { "wknum", "INVERSE" },
};

static inline const char *get_color(int id) {
  return colors[id].dflt;
}

int main() {
  for (int d = 0; d < 2; d++) {
    const char *s1 = get_color(d);
    const char *s2 = get_color(0);
    printf("d=%d s1=%s s2=%s s1=%s\n", d, s1, s2, s1);
  }
  return 0;
}
