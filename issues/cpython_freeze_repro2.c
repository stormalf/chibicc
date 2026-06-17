/*
 * cpython_freeze_repro.c
 *
 * Reproducer for CPython _freeze_module segfault with chibicc -O3.
 * This test mimics the conditions under which getpath / _freeze_module
 * fails when compiled with -fomit-frame-pointer, specifically targeting:
 *  1. Stack alignment for library calls (snprintf) which use SSE.
 *  2. RSP-relative local variable access depth tracking.
 *  3. __builtin_frame_address(0) behavior with omit-fp.
 *  4. Constructor execution.
 *
 * Build/Run:
 *  ./chibicc -O3 issues/cpython_freeze_repro.c -o /tmp/repro && /tmp/repro
 */

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "test.h"

static int ctor_run = 0;

/* CPython uses constructors in some modules (e.g. mimalloc) */
__attribute__((constructor))
static void my_ctor(void) {
    ctor_run = 1;
}

/* 
 * Callee with 8 arguments.
 * In SysV ABI: 
 *   regs: rdi, rsi, rdx, rcx, r8, r9 (a, b, c, d, e, f)
 *   stack: g, fmt, buf (at [rsp], [rsp+8], [rsp+16])
 */
__attribute__((noinline))
static void callee(int a, int b, int c, int d, int e, int f, int g, const char *fmt, char *buf) {
    /* Capture RSP at entry to verify ABI alignment */
    uint64_t sp;
    __asm__ volatile ("movq %%rsp, %0" : "=r"(sp));

    /* x86-64 SysV ABI: 
       1. At CALL: caller_rsp % 16 == 0.
       2. After CALL pushes 8-byte return address, callee sees rsp % 16 == 8.
    */
    if (sp % 16 != 8) {
        fprintf(stderr, "FAIL: stack misaligned in callee! rsp=0x%lx (mod 16 = %lu)\n", sp, sp % 16);
        exit(1);
    }

    /* SSE instructions in snprintf require 16-byte alignment. 
       If misaligned, this may SIGSEGV. */
    snprintf(buf, 128, fmt, g);
}

/*
 * Function that exercises RSP-relative addressing with many stack-passed args.
 * When compiled with -O3 (omit-fp), chibicc uses RSP-relative access for 'buf'.
 */
__attribute__((noinline))
static int process_path_simulation(int id) {
    /* CPython's getpath.c uses large buffers and many local variables. */
    char buf[128];
    memset(buf, 0, sizeof(buf));

    /* Verify __builtin_frame_address(0) doesn't break omit-fp functions. */
    void *fa = __builtin_frame_address(0);
    if (fa == NULL) {
        fprintf(stderr, "FAIL: __builtin_frame_address(0) returned NULL\n");
        return 1;
    }

    /* 
     * Call with 9 arguments.
     * 1-6 in regs: 1, 2, 3, 4, 5, 6
     * 7-9 on stack: id, "path_%d", buf
     * 
     * If omit-fp is active and chibicc fails to adjust the offset for 'buf'
     * after pushing 'id' and 'fmt' to the stack, 'buf' pointer will be wrong.
     */
    callee(1, 2, 3, 4, 5, 6, id, "path_%d", buf);

    return strcmp(buf, "path_42") != 0;
}

int main(void) {
    printf("Starting cpython_freeze_repro...\n");

    if (!ctor_run) {
        printf("[FAIL] constructor not run\n");
        return 1;
    }

    /* 
     * Exercise the path that fails in _freeze_module.
     * This simulation targets stack pointer tracking and alignment under -O3.
     */
    if (process_path_simulation(42) != 0) {
        printf("[FAIL] buffer corruption or alignment error\n");
        return 1;
    }

    printf("[PASS] cpython_freeze_repro\n");
    return 0;
}
