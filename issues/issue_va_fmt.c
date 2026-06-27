#include "test.h"

typedef struct {
  int gp_offset;
  int fp_offset;
  void *overflow_arg_area;
  void *reg_save_area;
} __va_elem;

typedef __va_elem va_list[1];

int my_fmt(char *buf, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int result = vsprintf(buf, fmt, ap);
  return result;
}

int main() {
  char buf[100];
  int r = my_fmt(buf, "%d %d %s", 1, 2, "foo");
  printf("%s\n", buf);
  printf("ret=%d\n", r);
  return 0;
}
