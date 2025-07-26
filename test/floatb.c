
#include "test.h"

float add_float2(float x, float y) {
  return x + y;
}
int main() {
  float r = add_float2(2.3, 3.8);
  printf("%f\n", r);
  ASSERT(6.1, r);
}
