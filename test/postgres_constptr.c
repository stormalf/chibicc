#include "test.h"

// Regression test: string literal pointers in const aggregates must remain
// proper relocations, not raw bytes copied into pointer slots.
static const char *const names[] = {"serializable", "read committed"};

struct NameRec { const char *name; };
static const struct NameRec recs[] = {{"foo"}, {"bar"}};

int main(void) {
  ASSERT(0, strcmp(names[0], "serializable"));
  ASSERT(0, strcmp(names[1], "read committed"));
  ASSERT(0, strcmp(recs[0].name, "foo"));
  ASSERT(0, strcmp(recs[1].name, "bar"));
  printf("OK\n");
  return 0;
}
