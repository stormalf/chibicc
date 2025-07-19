
#include "test.h"

// static inline int __sync_fetch_and_sub(int *ptr, int value) {
//     int old_value;
//     __asm__ __volatile__(
//         "lock; xaddl %0, %1"
//         : "=r" (old_value), "+m" (*ptr)
//         : "0" (-value)
//         : "memory"
//     );
//     return old_value;
// }


int main() {
    int value = 5;
    int old_value = __sync_fetch_and_sub(&value, 2);
    printf("Old value: %d, New value: %d\n", old_value, value); // Old value: 5, New value: 3
    ASSERT(5, old_value);
    ASSERT(3, value);
    return 0;
}

