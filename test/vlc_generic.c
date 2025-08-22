#include "test.h"
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

#define VLC_USED __attribute__((unused))
#define VLC_MALLOC __attribute__((malloc))

// Generic macro using builtins
#define mul_overflow(a,b,r) \
    _Generic(*(r), \
        unsigned: __builtin_umul_overflow(a, b, (unsigned *)(r)), \
        unsigned long: __builtin_umull_overflow(a, b, (unsigned long *)(r)), \
        unsigned long long: __builtin_umulll_overflow(a, b, (unsigned long long *)(r)))

// VLC-like allocation using builtins
VLC_USED VLC_MALLOC
static inline void *vlc_alloc(size_t count, size_t size) {
    size_t total = 0;
    if (mul_overflow(count, size, &total))
        return NULL;
    return malloc(total);
}

int main(void) {
    size_t n = 10, sz = sizeof(int);
    int *arr = vlc_alloc(n, sz);
    if (!arr) {
        printf("Allocation failed (overflow?)\n");
        return 1;
    }
    printf("=======n=%d, sz=%d, arr=%p\n");
    for (size_t i = 0; i < n; i++)
        arr[i] = (int)i;

    for (size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);

    // Test overflow
    int *overflow_test = vlc_alloc(SIZE_MAX, SIZE_MAX);
    if (!overflow_test)
        printf("Overflow detected correctly!\n");

    return 0;
}
