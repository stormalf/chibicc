
#include "test.h"

static int
ngx_atomic_fetch_add(char *value, int add)
{

int *ptr = &add;
    __asm__ volatile (

         
    "    xaddq  %0, %1;   "

    : "+r" (ptr) : "m" (*value) : "cc", "memory");

    return add;
}

int main () {
    int a = 10;
    int *b = 8;
    int res =  ngx_atomic_fetch_add(&b, a);
    printf("res=%d\n", res);
    ASSERT(10, res);
    return 0;

}