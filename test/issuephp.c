#include "test.h"
#include <stdint.h>
#include <stdbool.h>

bool multiply_with_overflow(uint32_t a, uint32_t b, uint32_t *result) {
    uint32_t res, m_overflow;

    // Use GCC inline assembly to do: res = a * b, with overflow in m_overflow
    asm volatile (
        "mull %3"                  // Multiply EAX by operand %3 → result in EDX:EAX
        : "=&a"(res), "=&d"(m_overflow) // outputs: EAX → res, EDX → m_overflow
        : "a"(a), "rm"(b)          // inputs: a in EAX, b in reg/mem
    );

    *result = res;
    return m_overflow != 0;
}

int main(void) {
    uint32_t a = 0xFFFFFFFF;
    uint32_t b = 2;
    uint32_t res;

    bool overflow = multiply_with_overflow(a, b, &res);

    printf("Result: %u (0x%08x)\n", res, res);
    printf("Overflow: %s\n", overflow ? "Yes" : "No");
    ASSERT(1, overflow);
    ASSERT(0xfffffffe, res);

    uint32_t nmemb = 0xFFFFFFFE;
    uint32_t size = 2;
    uint32_t offset = 1;
    uint32_t resm = nmemb;
    uint32_t m_overflow;

    __asm__ volatile (
        "mull %3\n\t"
        "add %4, %0\n\t"
        "adc $0, %1"
        : "=&a"(resm), "=&d"(m_overflow)
        : "%0"(resm), "rm"(size), "rm"(offset)
        : "cc"
    );

    printf("Result: %u (0x%08x)\n", resm, resm);
    printf("Overflow: %u\n", m_overflow);
    ASSERT(1, m_overflow);
    ASSERT(0xfffffffd, resm);

    return 0;
}