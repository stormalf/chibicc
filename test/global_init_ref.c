// Test: static globals referenced only in other globals' initializers
// should NOT produce -Wunused-variable warnings.
#include "test.h"

static int referenced = 42;
static int *referencing = &referenced;

int main() {
    ASSERT(42, *referencing);
    return 0;
}
