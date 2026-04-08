#include "test.h"
#include <stdint.h>
typedef int32_t i32;

void fn0(i32 x, i32 y, i32 a[x][5]) {
  ASSERT(8, sizeof(a));
  ASSERT(20, sizeof(a[0]));  
}

void fn0_1(i32 x,  i32 a[x][5]) {
  ASSERT(8, sizeof(a));
  ASSERT(20, sizeof(a[0]));  
}



void fn0_2(i32 x,  i32 a[x][x]) {
  ASSERT(8, sizeof(a));
  ASSERT(28, sizeof(a[0]));  
}


void fn1(i32 x, i32 y, i32 z, i32 a[x][y][z]) {
  ASSERT(8, sizeof(a));
  ASSERT(32, sizeof(a[0]));  
}

void fn2(i32 y, i32 x, i32 a[x][y]) {
  ASSERT(8, sizeof(a));
  ASSERT(28, sizeof(a[0]));
}

// 2D VLA - accessing first dimension
void fn_2d(i32 x, i32 y, i32 a[x][y]) {
  ASSERT(8, sizeof(a));
  ASSERT(16, sizeof(a[0]));  // y * sizeof(int) = 4 * 4 = 16
}

int main(void){
  fn0(7, 4, 0);
  fn0_1(7, 0);
  fn0_2(7, 0);
  fn1(7, 4, 2, 0);
  fn2(7, 4, 0);
  fn_2d(7, 4, 0);
  printf("OK\n");
  return 0;
}
