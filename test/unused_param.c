#include "test.h"

// __attribute__((unused)) before the type
static int test1(__attribute__((unused)) void *p, int y) { (void)y; return 0; }
// __attribute__((unused)) after the name
static int test2(void *p __attribute__((unused)), int y) { (void)y; return 0; }
// __attribute__((__unused__)) before the type
static int test3(__attribute__((__unused__)) void *p, int y) { (void)y; return 0; }
// __attribute__((__unused__)) after the name
static int test4(void *p __attribute__((__unused__)), int y) { (void)y; return 0; }
// Non-pointer types
static int test5(__attribute__((unused)) int x, int y) { return y; }
// Multiple unused params
static int test6(__attribute__((unused)) int a, __attribute__((unused)) int b) { return 0; }
// Pointer-to-pointer type
static int test7(__attribute__((unused)) void **pp, int y) { (void)y; return 0; }

int main() {
  test1(0, 1);
  test2(0, 1);
  test3(0, 1);
  test4(0, 1);
  test5(1, 2);
  test6(1, 2);
  test7(0, 1);
  return 0;
}
