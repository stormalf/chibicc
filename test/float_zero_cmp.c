// Test: comparing a floating-point value used as a truth condition against
// zero must emit IR that llc accepts (regression: "double 0.0" as fcmp's
// second operand was rejected by llc).
#include "test.h"

int main() {
  double d = 1.0;
  float f = 2.0f;
  long double ld = 3.0L;

  if (!(d != 0.0)) return 1;
  if (!(f != 0.0f)) return 2;
  if (!(ld != 0.0L)) return 3;

  if (d && f && ld) return 0;
  return 4;
}
