#include "test.h"

typedef int (*fptr_t)(int, int, int, int, int, int);

int foo(int a, int b, int c, int d, int e, int f) {
    return a + b + c + d + e + f;
}

fptr_t get_foo() {
    return foo;
}

int main() {
    // Evaluation of get_foo() will put the address of 'foo' into %rax.
    // However, before calling it, chibicc will pop the 6 arguments into registers.
    // If ANY of those pops or intermediate logic clobbers %rax, the call will fail.
    // Actually, the current code moves %rax to %r10 *after* all pops.
    // So any pop into %rax would clobber it. But pops are into rdi, rsi, etc.
    
    // Wait, what if one of the arguments IS a call?
    // get_foo()(1, 2, 3, 4, 5, 6)
    ASSERT(21, get_foo()(1, 2, 3, 4, 5, 6));
    return 0;
}
