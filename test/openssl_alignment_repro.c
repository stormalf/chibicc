/*
 * reproduction.c
 *
 * This test case reproduces a common source of runtime segfaults in OpenSSL
 * when compiled with chibicc. It targets a bug where the stack pointer
 * becomes misaligned during function calls when the frame pointer is omitted
 * (triggered by -O1 or higher).
 */

#include "test.h"
#include <emmintrin.h>
#include <smmintrin.h>

/* 
 * This function uses SSE instructions (__m128i). 
 * The x86-64 ABI requires the stack to be aligned to 16 bytes upon entry.
 * If the caller provides an unaligned stack, instructions like _mm_set1_epi32
 * (which may result in 'movdqa' or aligned stack spills) will trigger a SIGSEGV.
 */
void __attribute__((noinline)) target_function(int val) {
    __m128i x = _mm_set1_epi32(val);
    printf("SSE operation successful: %d\n", _mm_extract_epi32(x, 0));
}

/* 
 * In chibicc, compiling this with -O1 enables omit-frame-pointer.
 * If there's a bug in depth tracking or prologue/epilogue math,
 * the 'call' to target_function will be misaligned.
 */
void __attribute__((noinline)) caller(int val) {
    /* We pass several arguments to exercise the register/stack logic */
    target_function(val);
}

int main() {
    printf("Starting alignment test...\n");
    caller(42);
    return 0;
}
