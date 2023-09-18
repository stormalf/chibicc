#include <stdio.h>

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

    return 0;

}