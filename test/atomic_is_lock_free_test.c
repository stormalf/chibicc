#include "test.h"
#include <stdbool.h>

int main() {
    printf("%d\n", __atomic_is_lock_free(1, NULL));
    ASSERT(1, __atomic_is_lock_free(1, NULL));
    printf("%d\n", __atomic_is_lock_free(2, NULL));
    ASSERT(1, __atomic_is_lock_free(2, NULL));
    printf("%d\n", __atomic_is_lock_free(4, NULL));
    ASSERT(1, __atomic_is_lock_free(4, NULL));
    printf("%d\n", __atomic_is_lock_free(8, NULL));
    ASSERT(1, __atomic_is_lock_free(8, NULL));
    printf("%d\n", __atomic_is_lock_free(16, NULL));
    ASSERT(0, __atomic_is_lock_free(16, NULL));
    printf("%d\n", __atomic_is_lock_free(3, NULL));
    ASSERT(1, __atomic_is_lock_free(3, NULL));
    return 0;
}
