// Test: chibicc should NOT warn about unused static inline functions
// (GCC behavior: -Wunused-function does not apply to static inline)
static inline int unused_static_inline(void) { return 1; }

// Test: chibicc should NOT warn about static functions/vars in its own
// system headers (include/stdarg.h has static helper functions)
#include <stdio.h>

int main(void) {
  printf("OK\n");
  return 0;
}
