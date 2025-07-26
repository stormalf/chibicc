#include "test.h"


#define max(a, b) ({ typeof(a) _a = (a); typeof(b) _b = (b); _a > _b ? _a : _b; })

int foo(int x) {
    return ({
        int y = x * 2;
        y + 3;
    });
}

#define clamp(val, low, high) ({           \
    typeof(val) _val = (val);               \
    typeof(low) _low = (low);               \
    typeof(high) _high = (high);            \
    _val < _low ? _low : (_val > _high ? _high : _val); \
}) __attribute__((always_inline));

static inline int clamp_int(int val, int low, int high) __attribute__((always_inline));

static inline int clamp_int(int val, int low, int high) {
    return clamp(val, low, high);
}

// _Float16 support
_Float16 f16 = 1.5;

// Complex type
#include <complex.h>
float _Complex c = 1.0 + 2.0I;

// Atomic example (basic)
#include <stdatomic.h>
_Atomic int atomic_int;

// Inline asm
int foo2() {
  int x;
  asm ("movl $1, %0" : "=r"(x));
  return x;
}

// Attribute usage
int __attribute__((unused)) foo_unused(int x) {
  return x + 1;
}

// Variadic macros
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)



int main() {
    int x = 10, y = 20;
    printf("max is %d\n", max(x, y));
    ASSERT(20, max(x, y)); 

    double dx = 3.14, dy = 2.71;
    printf("max is %f\n", max(dx, dy));
    ASSERT(3, max(dx, dy));

    printf("foo(5) = %d\n", foo(5));
    ASSERT(13, foo(5));

    printf("clamp_int(5, 0, 10) = %d\n", clamp_int(5, 0, 10));
    ASSERT(5, clamp_int(5, 0, 10));
    printf("clamp_int(-5, 0, 10) = %d\n", clamp_int(-5, 0, 10));
    ASSERT(0, clamp_int(-5, 0, 10));
    printf("clamp_int(15, 0, 10) = %d\n", clamp_int(15, 0, 10));
    ASSERT(10, clamp_int(15, 0, 10));
    printf("foo2() returns %d\n",foo2());
    ASSERT(1, foo2());
    return 0;
}
