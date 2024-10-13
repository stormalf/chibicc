
#include <stdio.h>
#include <stdarg.h>

int fn1(int i, ...) {
  va_list ap; va_start(ap, i);
  long double ld = va_arg(ap, long double);
  va_end(ap);
  return ld;
}

int fn2(int i0, int i1, int i2, int i3, 
        int i4, int i5, int i6, ...) {
  va_list ap; va_start(ap, i6);
  int j = va_arg(ap, int);
  va_end(ap);
  return j;
}

void fn3(char*fmt,...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stdout, fmt, ap);
  va_end(ap);
}

int main(void) {
  printf("%d\n", fn1(1, (long double)44.0)); // exptect 44
  printf("%d\n", fn2(0,1,2,3,4,5,6,77)); // exptect 77
  fn3("%1.0f,%1.0f,%1.0f\n", 1.0, 2.0, 3.0); // exptect 1,2,3
  return 0;
}
