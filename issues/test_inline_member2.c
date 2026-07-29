// More complex inline + member access test
#include "test.h"

static const struct {
  const char *scheme;
  const char *dflt;
} colors[] = {
  { "workday", "REVERSE" },
  { "today", "INVERSE" },
};

static inline const char *get_color_seq(int id) {
  return colors[id].dflt;
}

int main() {
  // Multiple calls with different args, in different positions
  const char *a = get_color_seq(0);
  const char *b = get_color_seq(1);
  printf("a=%s b=%s\n", a, b);

  // Like cal pattern: inline in printf args after other args
  printf("seq=%s\n", get_color_seq(0));

  // Multiple inline calls in same printf
  printf("%s %s\n", get_color_seq(0), get_color_seq(1));

  printf("OK\n");
  return 0;
}
