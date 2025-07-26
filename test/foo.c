
#include "test.h"
const char str[] = {"foo"};

int main() {
    printf("foo %ld\n", sizeof(str));
    ASSERT(4, sizeof(str));
    return 0;
}