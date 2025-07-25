
#include "test.h"
static inline void pg_memory_barrier_impl(void) {
#if defined(__i386__) || defined(__i386)
    __asm__ __volatile__("lock; addl $0,0(%%esp)" : : : "memory", "cc");
#elif defined(__x86_64__)
    __asm__ __volatile__("lock; addl $0,0(%%rsp)" : : : "memory", "cc");
#endif
}

int main() {
    int x = 0;
    pg_memory_barrier_impl();
    x = 1;
    pg_memory_barrier_impl();
    printf("Memory barrier applied. x = %d\n", x);
    ASSERT(1, x);
    return 0;
}
