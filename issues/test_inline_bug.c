// Reproduction of cal inline bug: loop + inlined array access with constant index
#include "test.h"

static const struct {
  const char *name;
  const char *value;
} items[] = {
  {"today", "REVERSE"},
  {"wknum", "INVERSE"},
  {"weeks", ""},
  {"header", ""},
  {"workday", ""},
  {"weekend", ""},
};

static inline const char *get_item_value(int id) {
  return items[id].value;
}

int main() {
  // This pattern matches cal: loop with inline function using constant index
  for (int d = 0; d < 6; d++) {
    const char *s = get_item_value(0);
    if (!s) return d + 1;
    if (s[0] == '\0') return d + 100;
  }

  // Also test with printf-like pattern (nested in argument list)
  for (int d = 0; d < 6; d++) {
    printf("test d=%d s=%s\n", d, get_item_value(0));
  }

  return 0;
}
