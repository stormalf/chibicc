#include "test.h"

int main() {
  char *p = "hello";
  int n = 0;

  // while with char condition
  char *s = p;
  while (*s)
    s++;

  // if with char condition
  if (*p)
    n = 1;

  // do-while with char condition
  char *t = p;
  do {
    t++;
  } while (*t);

  // ternary with char condition
  n += *p ? 1 : 0;

  // logical NOT with char
  n += !*p;

  // logical AND with char
  n += *p && 1;

  // logical OR with char
  n += *p || 0;

  // nested logical with char
  n += (*p && *(p+1)) || 0;

  ASSERT(5, n);
  return 0;
}
