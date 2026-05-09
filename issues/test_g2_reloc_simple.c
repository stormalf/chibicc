#include "test.h"

int g1 = 77;
int *p = &g1;

int main() {
    printf("g1 = %d, p = %p, &g1 = %p\n", g1, p, &g1);
    ASSERT(77, *p);
    return 0;
}
