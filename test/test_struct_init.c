#include "test.h"

int g1 = 77;
int g2 = 4;
const struct {
  int *a, *b, *c;
} relo = {.a = &g1, .c = &g2};

int main() {
    printf("relo.a = %p, &g1 = %p, relo.c = %p, &g2 = %p\n", relo.a, &g1, relo.c, &g2);
    ASSERT(1, relo.a == &g1);
    ASSERT(1, relo.c == &g2);
    ASSERT(77, *relo.a);
    ASSERT(4, *relo.c);
    return 0;
}
