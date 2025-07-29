#include <stdio.h>

void test0() { printf("frame_address(0) = %p\n", __builtin_frame_address(0)); }
void test1() { printf("frame_address(1) = %p\n", __builtin_frame_address(1)); }
void test2() { printf("frame_address(2) = %p\n", __builtin_frame_address(2)); }
void test3() { printf("frame_address(3) = %p\n", __builtin_frame_address(3)); }

int main() {
  test0();
  test1();
  test2();
  test3();
  return 0;
}
