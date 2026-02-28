#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    char header[32];
    int arr[];
} Y;

int main(void) {
    if (offsetof(Y, arr) != 32)
        return 1;

    if (sizeof(Y) != 32)
        return 2;

    size_t sz = offsetof(Y, arr) + 4 * sizeof(int);
    Y *p = malloc(sz);
    if (!p)
        return 3;

    p->arr[3] = 42;

    free(p);
    return 0;
}