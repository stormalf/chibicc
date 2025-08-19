#include "test.h"
#include <stdint.h>
#include <string.h>
#include <stddef.h>

int test(const char *ptr, size_t len, uintptr_t delta) {
    unsigned long ret;

	__asm__ (
		"0:\n\t"
		"movq (%2,%3), %0\n\t"
		"xorq (%2), %0\n\t"
		"jne 1f\n\t"
		"addq $0x8, %2\n\t"
		"subq $0x8, %1\n\t"
		"ja 0b\n\t"
		"movq $0x1, %0\n\t"
		"jmp 3f\n\t"
		"1:\n\t"
		"cmpq $0x8,%1\n\t"
		"jb 2f\n\t"
		"xorq %0, %0\n\t"
		"jmp 3f\n\t"
		"2:\n\t"
		"negq %1\n\t"
		"lea 0x40(,%1,8), %1\n\t"
		"shlq %b1, %0\n\t"
		"sete %b0\n\t"
		"movzbq %b0, %0\n\t"
		"3:\n"
		: "=&a"(ret),
		  "+c"(len),
		  "+r"(ptr)
		: "r"(delta)
		: "cc");
	return ret;
}


int main() {
    uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int delta = 0;
    int len = 4;

    int result = test(data, len, delta);
    printf("Result: %d\n", result);
	ASSERT(1, result);
    return 0;
}