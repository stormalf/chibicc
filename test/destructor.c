#include <stdio.h>

__attribute__((constructor))
void setup() {
    printf("constructor called\n");
}

__attribute__((destructor))
void teardown() {
    printf("destructor called\n");
}

int main() {
    printf("main called\n");
    return 0;
}
