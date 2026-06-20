#include "test.h"
#include <stddef.h>

struct AlignedStruct {
    int x;
} __attribute__((aligned(32)));

int main() {
    struct AlignedStruct s = {42};
    ASSERT(42, s.x);
    ASSERT(1, offsetof(struct AlignedStruct, x) % 32 == 0);
    return 0;
}
