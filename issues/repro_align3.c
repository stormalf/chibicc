#include <stdio.h>
#include <stddef.h>

typedef int aligned_int __attribute__((aligned(64)));

struct Foo {
    int x;
    aligned_int y;
};

int main() {
    printf("offsetof(y) = %zu\n", offsetof(struct Foo, y));
    if (offsetof(struct Foo, y) != 64) {
        printf("BUG: offsetof(y) is %zu, expected 64\n", offsetof(struct Foo, y));
        return 1;
    }
    printf("OK\n");
    return 0;
}
