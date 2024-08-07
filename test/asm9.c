#include <stdint.h>
#include <stdio.h>
#include <sys/syscall.h>
//#include "test.h"

void ff_put_pixels8_mmx(uint8_t *block, const uint8_t *pixels, int line_size, int h) {
    __asm__ volatile(
        "movq (%1), %%mm0 \n\t"
        "movq %%mm0, (%0) \n\t"
        : // No output operands
        : "r"(block), "r"(pixels) // Input operands
        : "memory" // Clobbered registers
    );
}

int atomic_add(int *ptr, int val) {
    int result;
    __asm__ volatile("lock; xaddl %0, %1"
                     : "=r"(result), "+m"(*ptr)
                     : "0"(val)
                     : "memory");
    return result;
}

static inline long syscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    long ret;
    __asm__ volatile ("syscall"
                      : "=a"(ret)
                      : "a"(n), "D"(a1), "S"(a2), "d"(a3),
                        "r"(a4), "r"(a5), "r"(a6)
                      : "rcx", "r11", "memory");
    return ret;
}

void *memcpy(void *dest, const void *src, size_t n) {
    __asm__ volatile(
        "rep movsb"
        : "+D"(dest), "+S"(src), "+c"(n)
        :
        : "memory");
    return dest;
}



int main(int argc, char **argv) {
    uint8_t block[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t pixels[8] = {1  , 2  , 3  , 4  , 5  , 6  , 7  , 8};
    ff_put_pixels8_mmx(block, pixels, 8, 1);
    printf("%d\n", block[0]);
    printf("%d\n", block[7]);
    printf("%d\n", pixels[0]);
    printf("%d\n", pixels[7]);
    // ASSERT(1, block[0]);
    // ASSERT(8, block[7]);
    // ASSERT(1, pixels[0]);
    // ASSERT(8, pixels[7]);

    int i = 8;
    int j = 0;
    int *ptr = &i;
    j = atomic_add(ptr, 1);
    printf("i=%d, j=%d\n", i, j);
    // ASSERT(9, i);
    // ASSERT(8, j);

    // long tid = syscall(SYS_gettid, 0, 0, 0, 0, 0, 0);
    // printf("Thread ID: %ld\n", tid);

    return 0;
}