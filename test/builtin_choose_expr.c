
#include <stdio.h>
#include "test.h"
#define ARRAY_SIZE(x) (__builtin_choose_expr(!__builtin_types_compatible_p(typeof(x), typeof(&*(x))), sizeof(x) / sizeof((x)[0]), (void)0))

int main() {
    int arr[10];
    printf("Array size: %lu\n", ARRAY_SIZE(arr));
    ASSERT(10, ARRAY_SIZE(arr));
    return 0;
}

