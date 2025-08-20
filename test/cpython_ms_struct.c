#include "test.h"
#include <stddef.h>

// Normal struct
struct Normal {
    char c;
    int i;
    short s;
};

// MS struct
struct __attribute__((ms_struct)) Ms {
    char c;
    int i;
    short s;
};

int main(void) {
    printf("sizeof(Normal) = %zu\n", sizeof(struct Normal));
    printf("  offsets: c=%zu i=%zu s=%zu\n",
           offsetof(struct Normal, c),
           offsetof(struct Normal, i),
           offsetof(struct Normal, s));

    printf("sizeof(Ms)     = %zu\n", sizeof(struct Ms));
    printf("  offsets: c=%zu i=%zu s=%zu\n",
           offsetof(struct Ms, c),
           offsetof(struct Ms, i),
           offsetof(struct Ms, s));

    ASSERT(12, sizeof(struct Normal));
    ASSERT(0,  offsetof(struct Normal, c));
    ASSERT(4,  offsetof(struct Normal, i));
    ASSERT(8,  offsetof(struct Normal, s));
    ASSERT(12, sizeof(struct Ms));
    ASSERT(0,  offsetof(struct Ms, c));
    ASSERT(4,  offsetof(struct Ms, i));
    ASSERT(8,  offsetof(struct Ms, s));
    printf("OK\n");
    return 0;
}
