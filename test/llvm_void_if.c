// Compile: ./chibicc --backend-llvm -o test/llvm_void_if.exe test/llvm_void_if.c -xc test/common -Itest
#include "test.h"

void my_assert(int expected, int actual) {
  if (expected == actual) {
    printf("%d\n", actual);
  } else {
    printf("expected %d got %d\n", expected, actual);
    exit(1);
  }
}

int main() {
  my_assert(35, 35);
  printf("OK\n");
  return 0;
}