#include "test.h"

__attribute__((noinline)) static int tail_fn(int x) {
    _Alignas(32) volatile int buf[8];
    buf[0] = x;
    return buf[0];
}

__attribute__((noinline)) static int helper(int x) {
    _Alignas(32) volatile int buf[8];
    buf[0] = x;
    return tail_fn(buf[0] + 1);
}

int main(void) {
    _Alignas(32) volatile int result;
    for (int i = 0; i < 20; i++) {
        result = helper(i);
        if (result != i + 1)
            return 1;
    }
    return 0;
}
