#include <stdio.h>
#include "test.h"

int main(int argc, char **argv) {
    printf("Hello World!\n");
    printf("%d\n", argc);
    ASSERT(1, argc);

    return 0;
}