#include "test.h"
#include <stdint.h>
typedef int32_t i32;

// Simplified test - only one dimension parameter
void fn_simple(i32 z, i32 a[z]) {
  ASSERT(8, sizeof(a));
}

int main(void){
  fn_simple(7, 0);
  printf("OK\n");
  return 0;
}
