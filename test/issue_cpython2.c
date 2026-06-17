#include "test.h"


typedef struct { long a; long b; } S2;
S2 call_assembly() {
    S2 r = {0, 0};
    asm volatile(
        "mov $10, %%rax\n\t"
        "mov $20, %%rdx\n\t"
        "mov %%rax, %0\n\t"
        "mov %%rdx, %1"
        : "=r"(r.a), "=r"(r.b)
        :
        : "rax", "rdx"
    );
    return r;
}
int myfunc() {
    S2 s = call_assembly();
    return s.a + s.b;
}
typedef struct { long a; long b; long c; } S3;
S3 call_assembly2() {
    S3 r = {0, 0, 0};
    asm volatile(
        "mov $1, %%rax\n\t"
        "mov $2, %%rcx\n\t"
        "mov $3, %%r8\n\t"
        "mov %%rax, %0\n\t"
        "mov %%rcx, %1\n\t"
        "mov %%r8,  %2"
        : "=r"(r.a), "=r"(r.b), "=r"(r.c)
        :
        : "rax", "rcx", "r8"
    );
    return r;
}
int myfunc2() {
    S3 s = call_assembly2();
    return (int)(s.a + s.b + s.c);
}

typedef struct { int x; long y; } Padded;
Padded call_assembly3() {
    Padded r = {0, 0};
    asm volatile(
        "mov $42,  %%eax\n\t"
        "mov $100, %%rdx\n\t"
        "mov %%eax, %0\n\t"
        "mov %%rdx, %1"
        : "=r"(r.x), "=r"(r.y)
        :
        : "rax", "rdx"
    );
    return r;
}
int myfunc3() {
    Padded p = call_assembly3();
    return p.x + (int)p.y;
}

typedef struct { long val; } S1;
S1 call_assembly_nv() {
    S1 r = {99};
    asm (
        "mov $10, %%rax\n\t"
        "mov %%rax, %0"
        : "=r"(r.val)
        :
        : "rax"
    );
    return r;
}
int myfunc4() {
    return (int)call_assembly_nv().val;
}

typedef struct { long a; long b; } S4;
S4 call_assembly4() {
    S4 r = {0, 0};
    asm volatile(
        "mov $7, %%rax\n\t"
        "mov $3, %%rdx\n\t"
        "mov %%rax, %0\n\t"
        "mov %%rdx, %1"
        : "=r"(r.a), "=r"(r.b)
        :
        : "rax", "rdx"
    );
    return r;
}
S4 middle() { return call_assembly4(); }
int myfunc5() {
    S4 s = middle();
    return (int)(s.a * s.b);
}

typedef struct { long val; } S5;
S5 call_assembly_mem() {
    S5 r;
    asm volatile(
        "movq $55, %0"
        : "=m"(r.val)
    );
    return r;
}
int myfunc6() {
    return (int)call_assembly_mem().val;
}

int main() {
    ASSERT(30, myfunc());
    ASSERT(6, myfunc2());
    ASSERT(142, myfunc3());
    ASSERT(10, myfunc4());
    ASSERT(21, myfunc5());
    ASSERT(55, myfunc6());
    return 0;
}
