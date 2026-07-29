// Reproduction of cal inline bug with struct member access
#include "test.h"

static const struct {
  const char *scheme;
  const char *dflt;
} colors[] = {
  { "workday", "REVERSE" },
  { "today", "INVERSE" },
};

static inline const char *get_color_seq(int id) {
  return colors[id].scheme;
}

int main() {
  printf("color = %s\n", get_color_seq(0));
  printf("color = %s\n", get_color_seq(1));
  printf("OK\n");
  return 0;
}
