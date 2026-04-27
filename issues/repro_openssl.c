#include <stdio.h>

__attribute__((noinline, noclone))
long check(void)
{
    long rsp;
    asm volatile(
        "mov %%rsp, %0"
        : "=r"(rsp)
    );
    return rsp & 15;
}

__attribute__((noinline))
long callee(long a, long b, long c, long d)
{
    return check();
}

int main()
{
    long r = callee(1,2,3,4);
    printf("%ld\n", r);
}