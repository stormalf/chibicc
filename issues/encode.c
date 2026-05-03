#include <stdio.h>

__attribute__((noinline))
void g(unsigned char *p, long len,
       long a, long b, long c, long d, long e) {

  for (long i = 0; i < len; i++) {
    if (p[i] != (unsigned char)i) {
      printf("BAD at %ld\n", i);
      return;
    }
  }
  printf("OK\n");
}

int main() {
  unsigned char buf[200000];

  for (int i = 0; i < 200000; i++)
    buf[i] = i;

  g(buf, 1024, 1111,2,3,4,5);
return 0;
}
