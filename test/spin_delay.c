#include "test.h"

static inline void pg_spin_delay_impl(void) {
    __asm__ __volatile__("rep; nop");
}

int main() {
    printf("Before spin delay.\n");
    for (int i = 0; i < 1000000; i++) {
        pg_spin_delay_impl();
    }
    printf("After spin delay.\n");
    return 0;
}
