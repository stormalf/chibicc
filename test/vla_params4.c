#include "test.h"
#include <stdint.h>
typedef int32_t i32;
typedef uint8_t u8;

void fn4(i32 x,i32,i32 y,i32,i32,i32 z,i32 a[x+y][y+z][z+x]) {
  ASSERT(8, sizeof(a));
  ASSERT(1008, sizeof(a[0]));
  ASSERT(56, sizeof(a[0][0]));
}


int main(void){
  fn4(3,0,7,0,0,11,0);

  printf("OK\n");
  return 0;
}
