#include "test.h"

typedef struct {
  int gp_offset;
  int fp_offset;
  void *overflow_arg_area;
  void *reg_save_area;
} __va_elem;

typedef __va_elem va_list[1];

int ret3(void) { return 3; }

typedef struct { int a, b; short c; char d; } Ty4_mini;
int struct_test4(Ty4_mini x, int n) { switch(n) { case 0: return x.a; case 1: return x.b; case 2: return x.c; default: return x.d; } }

int main() {
  ASSERT(3, ret3());
  ASSERT(10, ({ Ty4_mini x={10,20,30,40}; struct_test4(x, 0); }));
  ASSERT(20, ({ Ty4_mini x={10,20,30,40}; struct_test4(x, 1); }));
  printf("OK\n");
  return 0;
}
