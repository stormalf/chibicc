// Regression test for overflow_arg_area bug:
// When assign_lvar_offsets is called twice (once from extended_asm.c, once from
// codegen.c), params with var->offset already set are skipped and 'stack' stays
// 0, giving overflow_arg_area = 16 instead of the correct value (e.g. 24).
// This causes va_arg to read the wrong stack argument.
#include "test.h"
#include <stdarg.h>

// This function takes 7 integer arguments. The first 6 fit in GP registers;
// the 7th is passed on the stack (overflow area). va_arg must use the correct
// overflow_arg_area offset to read it.
static int sum7(int a, int b, int c, int d, int e, int f, ...) {
  va_list ap;
  va_start(ap, f);
  int g = va_arg(ap, int);
  va_end(ap);
  return a + b + c + d + e + f + g;
}

int main() {
  // Call the variadic function twice with the same arguments.
  // Before the fix, the second call produced a wrong result because
  // overflow_arg_area was 16 instead of 24 on the second codegen pass.
  ASSERT(28, sum7(1, 2, 3, 4, 5, 6, 7));
  ASSERT(28, sum7(1, 2, 3, 4, 5, 6, 7));
  return 0;
}
