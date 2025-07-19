
#include "test.h"
int main() {
    int value = 0;
    int old_value = __sync_lock_test_and_set(&value, 1);
    printf("Old value: %d, New value: %d\n", old_value, value); // Old value: 0, New value: 1
    ASSERT(0, old_value);
    ASSERT(1, value);
    return 0;
}
