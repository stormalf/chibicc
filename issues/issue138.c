#include <bits/types.h>
#include <stdint.h>

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
    ngx_atomic_t *lock;
    ngx_atomic_uint_t old = 0;
    ngx_atomic_uint_t set = 0;
    ngx_atomic_uint_t t = ngx_atomic_cmp_set(lock, old, set);
    return 0;
}