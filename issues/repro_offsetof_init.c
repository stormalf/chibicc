#include <stdio.h>
#include <stddef.h>

struct Foo {
    int a;
    int b;
    int c;
    int data[100];
    int io;
};

struct Info {
    size_t off;
};

#define KIND_IO 10
#define SIZE 15

static const struct Info infos[SIZE] = {
    [1] = { offsetof(struct Foo, a) },
    [7] = { offsetof(struct Foo, b) },
    [9] = { offsetof(struct Foo, c) },
    [KIND_IO] = { offsetof(struct Foo, io) },
};

int main() {
    for (int i = 0; i < SIZE; i++) {
        printf("off[%d] = %zu\n", i, infos[i].off);
    }

    if (infos[KIND_IO].off == 0) {
        printf("BUG: off[%d] is 0!\n", KIND_IO);
        return 1;
    }
    printf("OK\n");
    return 0;
}
