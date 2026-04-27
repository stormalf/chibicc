#include <stdio.h>

void check(void) {
    void *rsp;
    asm("mov %%rsp, %0" : "=r"(rsp));

    if (((unsigned long)rsp & 15) != 0) {
        printf("FAIL: stack misaligned\n");
    } else {
        printf("OK: stack aligned\n");
    }
}

int main() {
    check();
    return 0;
}
