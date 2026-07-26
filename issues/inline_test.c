#include "test.h"

static inline int add(int a, int b) { return a + b; }
static inline int mul(int a, int b) { return a * b; }

int main() {
  int x = add(1, 2);  // Assignment 
  int y = mul(3, 4);  // Assignment
  ASSERT(3, x);
  ASSERT(12, y);
  return x + y;
}