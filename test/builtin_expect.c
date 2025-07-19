
#include "test.h"
int main() {
    int x = 10;
    if (__builtin_expect(x == 10, 1)) {
        printf("Expected branch\n");
    } else {
        printf("Unexpected branch\n");
        ASSERT(0, 1); // This should not happen
    }

    if (__builtin_expect(x == 5, 1)) {
        printf("Expected branch 2\n");
        ASSERT(0, 1); // This should not happen
    } else {
        printf("Unexpected branch 2\n");
    }
    return 0;
}


