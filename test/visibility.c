#include "test.h"

extern __attribute__((visibility("default"))) int vis_default_var;
int vis_default_var = 42;

extern __attribute__((visibility("hidden"))) int vis_hidden_var;
int vis_hidden_var = 7;

extern __attribute__((visibility("default"))) int vis_default_func(int);
int vis_default_func(int x) { return x + 1; }

int main() {
  ASSERT(42, vis_default_var);
  ASSERT(7, vis_hidden_var);
  ASSERT(43, vis_default_func(42));
  return 0;
}
