#include "test.h"
#include <stdint.h>

uint32_t a32 = 0xF0F0F0F0;
uint64_t a64 = 0xF0F0F0F0F0F0F0F0;


int main() {
    unsigned int c1 = __builtin_popcount(a32);   // emits popcnt eax, eax
    unsigned int c2 = __builtin_popcountl(a64);  // emits popcnt rax, rax
    unsigned int c3 = __builtin_popcountll(a64); // emits popcnt rax, rax

    printf("c1=%0x\n", c1);
    printf("c2=%0x\n", c2);
    printf("c3=%0x\n", c3);
    printf("OK\n");

    return 0;
}