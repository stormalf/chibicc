#include <bits/types.h>
#include <stdint.h>

#include "test.h"
#define NGX_SMP_LOCK
#define ngx_inline inline

typedef __u_char u_char;
typedef unsigned long ngx_atomic_uint_t;
typedef volatile ngx_atomic_uint_t ngx_atomic_t;
static ngx_inline ngx_atomic_uint_t

ngx_atomic_cmp_set(ngx_atomic_t *lock, ngx_atomic_uint_t old,
                   ngx_atomic_uint_t set)
{
    u_char res;

    __asm__ volatile(

        NGX_SMP_LOCK
        "    cmpxchgq  %3, %1;   "
        "    sete      %0;       "

        : "=a"(res)
        : "m"(*lock), "a"(old), "r"(set)
        : "cc", "memory");

    return res;
}

int main(void)
{
    ngx_atomic_uint_t mylock = 8;
    ngx_atomic_t *lock = &mylock;
    ngx_atomic_uint_t old = 7;
    ngx_atomic_uint_t set = 1;
    ngx_atomic_uint_t t = ngx_atomic_cmp_set(lock, old, set);
    printf("lock = %ld, old= %ld, set = %ld\n", mylock, old, set);
    ASSERT(8, mylock);
    ASSERT(7, old);
    ASSERT(1, set);
    return 0;
}