
#include <stdatomic.h>
#include "test.h"

// static inline int __sync_val_compare_and_swap(int *ptr, int oldval, int newval) {
//     int result;
//     __asm__ __volatile__(
//         "lock; cmpxchgl %2, %1"
//         : "=a" (result), "+m" (*ptr)
//         : "r" (newval), "0" (oldval)
//         : "memory"
//     );
//     return result;
// }


int main() {
    int value = 5;
    int old_value = __sync_val_compare_and_swap(&value, 5, 10);
    printf("Old value: %d, New value: %d\n", old_value, value); // Old value: 5, New value: 10
    ASSERT(5, old_value);
    ASSERT(10, value);
    return 0;
}

