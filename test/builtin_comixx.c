#include "test.h"


// If you want to avoid xmmintrin.h, define the builtins manually:
typedef float v4sf __attribute__((vector_size(16)));

static inline int test_comieq(v4sf A, v4sf B) {
    return __builtin_ia32_comieq((v4sf)A, (v4sf)B);
}

static inline int test_comineq(v4sf A, v4sf B) {
    return __builtin_ia32_comineq((v4sf)A, (v4sf)B);
}

static inline int test_comile(v4sf A, v4sf B) {
    return __builtin_ia32_comile((v4sf)A, (v4sf)B);
}

static inline int test_comigt(v4sf A, v4sf B) {
    return __builtin_ia32_comigt((v4sf)A, (v4sf)B);
}

static inline int test_comilt(v4sf A, v4sf B) {
    return __builtin_ia32_comilt((v4sf)A, (v4sf)B);
}

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {1.0f, 3.0f, 2.0f, 4.0f};
    v4sf c = {1.0f/0.0f, 2.0f, 3.0f, 4.0f}; // c[0] = +inf to test NaN/unordered behavior

    printf("comieq (a, b): %d\n", test_comieq(a, b));   // expect 0 (not equal)
    ASSERT(1, test_comieq(a, b));
    printf("comieq (a, a): %d\n", test_comieq(a, a));   // expect 1 (equal)
    ASSERT(1, test_comieq(a, a));
    printf("comineq (a, b): %d\n", test_comineq(a, b)); // expect 1 (not equal)
    ASSERT(0, test_comineq(a, b));
    printf("comineq (a, a): %d\n", test_comineq(a, a)); // expect 0 (equal)
    ASSERT(0, test_comineq(a, a));

    printf("comile (a, b): %d\n", test_comile(a, b));   // expect 1 (1 <= 1)
    ASSERT(1, test_comile(a, b));
    printf("comile (b, a): %d\n", test_comile(b, a));   // expect 0 (3 <= 1 false)
    ASSERT(1, test_comile(b, a));
    printf("comile (a, c): %d\n", test_comile(a, c));   // behavior with +inf
    ASSERT(1, test_comile(a, c));

    printf("comigt (a, b): %d\n", test_comigt(a, b));   // expect 0 (1 > 1 false)
    ASSERT(0, test_comigt(a, b));
    printf("comigt (b, a): %d\n", test_comigt(b, a));   // expect 1 (3 > 1)
    ASSERT(0, test_comigt(b, a));
    printf("comigt (a, c): %d\n", test_comigt(a, c));   // behavior with +inf

    printf("comilt (a, b): %d\n", test_comilt(a, b));   // expect 0 (1 < 1 false)
    ASSERT(0, test_comilt(a, b));
    printf("comilt (b, a): %d\n", test_comilt(b, a));   // expect 0 (3 < 1 false)
    ASSERT(0, test_comilt(b, a));
    printf("comilt (a, c): %d\n", test_comilt(a, c));   // behavior with +inf
    ASSERT(1, test_comilt(a, c));
    printf("OK\n");
    return 0;
}
