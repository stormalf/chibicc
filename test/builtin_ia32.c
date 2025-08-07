#include "test.h"
void test(void) {
  __builtin_ia32_pause();
  __builtin_ia32_lfence();
  __builtin_ia32_mfence();
  __builtin_ia32_sfence();
  __builtin_ia32_emms();
}


int main() {
    test();
    printf("OK\n");
    return 0;
}