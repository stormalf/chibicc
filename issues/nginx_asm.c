#include <stdint.h>
#include <stdio.h>


#ifdef	__USE_MISC
# ifndef __u_char_defined
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
#  define __u_char_defined
# endif
typedef __loff_t loff_t;
#endif

#define NGX_SMP_LOCK                 "lock ; "
typedef int64_t                     ngx_atomic_int_t;
typedef uint64_t                    ngx_atomic_uint_t;
typedef volatile ngx_atomic_uint_t  ngx_atomic_t;
#define NGX_ATOMIC_T_LEN            (sizeof("-9223372036854775808") - 1)

/* TODO: auto_conf: ngx_inline   inline __inline __inline__ */
#ifndef ngx_inline
#define ngx_inline      inline
#endif

static ngx_inline ngx_atomic_uint_t
ngx_atomic_cmp_set(ngx_atomic_t *lock, ngx_atomic_uint_t old,
    ngx_atomic_uint_t set)
{
    u_char  res;

    __asm__ volatile (

         NGX_SMP_LOCK
    "    cmpxchgq  %3, %1;   "
    "    sete      %0;       "

    : "=a" (res) : "m" (*lock), "a" (old), "r" (set) : "cc", "memory");

    return res;
}

int main(int argc, char *argv[])
{
    ngx_atomic_uint_t lock = 0;
    ngx_atomic_cmp_set(&lock, 0, 1);
    return 0;
}