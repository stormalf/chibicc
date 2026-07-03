#include "test.h"

typedef int int4 __attribute__((vector_size(16)));

int main(void) {
    int4 a = {1, 2, 3, 4};
    ASSERT(1, a[0]);
    ASSERT(2, a[1]);
    ASSERT(3, a[2]);
    ASSERT(4, a[3]);
    printf("OK\n");
    return 0;
}
