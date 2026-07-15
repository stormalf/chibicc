#include "test.h"

int main() {
  typedef float float4 __attribute__((ext_vector_type(4)));
  float4 v = (float4){1.0f, 2.0f, 3.0f, 4.0f};
  ASSERT(1, v[0]);
  ASSERT(2, v[1]);
  return 0;
}
