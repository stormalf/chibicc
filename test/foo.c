#include <stdio.h>
#include "test.h"
const char str[] = {"foo"};

int main() {
    printf("foo %d\n", sizeof(str));
    return 0;
}