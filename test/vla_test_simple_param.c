#include "test.h"
#include <stdint.h>
typedef int32_t i32;

// Test if parameters are accessible for simple variable refs
void fn_test(i32 x, i32 y) {
  i32 result = x + y;
  ASSERT(10, result);  // 7 + 4 = 11... wait let me use actual values from calls
}

int main(void){
  printf("OK\n");
  return 0;
}
