// Test scope-based allocator with simple block scopes
#include <stdio.h>

int foo(void) {
  int a = 1;
  {
    int b = 2;
    a += b;
  }
  {
    int c = 3;
    a += c;
  }
  return a;
}

int main() {
  int x = foo();
  printf("foo() = %d (expect 6)\n", x);
  if (x != 6) {
    fprintf(stderr, "FAIL: expected 6, got %d\n", x);
    return 1;
  }
  return 0;
}
