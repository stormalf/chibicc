#include "test.h"
#include <stdbool.h>

#ifdef OMIT_FRAME_POINTER
# define EXPECTED 0
#else
# define EXPECTED 1
#endif


void test0() { bool x = false; printf("frame_address(0) = %p\n", __builtin_frame_address(0)); x =  __builtin_frame_address(0); ASSERT(1, x);}
void test1() { bool x = false; printf("frame_address(1) = %p\n", __builtin_frame_address(1)); x =  __builtin_frame_address(1); ASSERT(1, x);}
void test2() { bool x = false; printf("frame_address(2) = %p\n", __builtin_frame_address(2)); x =  __builtin_frame_address(2); ASSERT(1, x);}
void test3() { bool x = false; printf("frame_address(3) = %p\n", __builtin_frame_address(3)); x =  __builtin_frame_address(3); ASSERT(EXPECTED, x);}

int main() {
  test0();
  test1();
  test2();
  test3();
  return 0;
}