
#include "test.h"

// static inline int __sync_fetch_and_add(int *ptr, int value) {
//     int old_value;
//     __asm__ __volatile__(
//         "lock; xaddl %0, %1"
//         : "=r" (old_value), "+m" (*ptr)
//         : "0" (value)
//         : "memory"
//     );
//     return old_value;
// }

int main() {
    int value = 5;
    int old_value = __sync_fetch_and_add(&value, 3);
    printf("Old value: %d, New value: %d\n", old_value, value); // Old value: 5, New value: 8
    ASSERT(5, old_value);
    ASSERT(8, value);
    return 0;
}

