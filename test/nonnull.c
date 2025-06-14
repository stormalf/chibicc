#include <stddef.h>
#include <stdio.h>

// Declarations + definitions so linker can find them
void foo(char *p, char *q) __attribute__((__nonnull__));
void foo(char *p, char *q) { }

void bar(char *p, char *q, char *r) __attribute__((__nonnull__(1, 3)));
void bar(char *p, char *q, char *r) { }

void baz(char *p, char *q) __attribute__((__nonnull__));
void baz(char *p, char *q) {
  if (p)
    *p = 'A';
  if (q)
    *q = 'B';
}

typedef void (*nonnull_fn_t)(char *p, char *q) __attribute__((__nonnull__(2)));

void use_typedef(nonnull_fn_t fn, char *a, char *b) {
  fn(a, b);
}

int main() {
  char x = 'x', y = 'y', z = 'z';

  foo(&x, &y);
  bar(&x, NULL, &z);
  baz(&x, &y);

  use_typedef(baz, &x, &y);
  printf("x: %c, y: %c, z: %c\n", x, y, z);
  return 0;
}
