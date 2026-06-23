#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "test.h"

__attribute__((noinline))
static void callee(int a, int b, int c, int d, int e, int f, int g, const char *fmt, char *buf) {
    uint64_t sp;
    __asm__ volatile ("movq %%rsp, %0" : "=r"(sp));

    if (sp % 16 != 8) {
        fprintf(stderr, "FAIL: stack misaligned in callee! rsp=0x%lx (mod 16 = %lu)\n", sp, sp % 16);
        exit(1);
    }

    snprintf(buf, 128, fmt, g);
}

__attribute__((noinline))
static int caller(int id) {
    char buf[128];
    memset(buf, 0, sizeof(buf));

    callee(1, 2, 3, 4, 5, 6, id, "path_%d", buf);

    return strcmp(buf, "path_42") != 0;
}

int main(void) {
    printf("Starting stack_align_test...\n");

    if (caller(42) != 0) {
        printf("[FAIL] buffer corruption or alignment error\n");
        return 1;
    }

    printf("[PASS] stack_align_test\n");
    return 0;
}
