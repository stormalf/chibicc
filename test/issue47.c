#include "test.h"
// a.c
struct S { int n; };

int main(void) {
    printf("%d\n", (struct S){1}.n);
    ASSERT(1, (struct S){1}.n);
    return 0;
}