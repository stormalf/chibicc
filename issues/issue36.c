#include <stdio.h>
#include "test.h"
typedef struct empty_struct {} empty_struct;

int f(empty_struct a) {
    return 0;
}

int main() {
    f((empty_struct){});
    printf("%ld\n", sizeof(empty_struct));
    ASSERT(0, sizeof(empty_struct));
    return 0;
}