// Reproduction of cal crash: inline function + array of structs + constant index
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
  for (int d = 0; d < 6; d++) {
    const char *s = get_item_value(0);
    if (!s) return d + 1;
    // printf("d=%d s=%s\n", d, s);
  }
  return 0;
}
