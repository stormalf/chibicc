#include "test.h"
#include <stdint.h>
typedef int32_t i32;
typedef uint8_t u8;


void fn2(i32 z, i32 (*a)[z]){
  ASSERT(28, sizeof(*a));

}

int main(void){
  fn2(7,0);
  printf("OK\n");
  return 0;
}
  
