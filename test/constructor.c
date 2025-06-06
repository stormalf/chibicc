#include <stdio.h>

__attribute__((constructor))
static void my_init(void) {
    printf("constructor called\n");
}

int main() {
    printf("main called\n");
    return 0;
}

