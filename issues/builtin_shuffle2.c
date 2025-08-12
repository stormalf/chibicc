#include "test.h"

typedef float float4 __attribute__((vector_size(16)));
typedef int __v4si __attribute__((vector_size(16)));

#define TEST_SHUFFLE(a, b, mask) do { \
    float4 res = __builtin_shuffle(a, b, mask); \
    printf("mask = {%d,%d,%d,%d} => ", mask[0], mask[1], mask[2], mask[3]); \
    printf("{%.1f, %.1f, %.1f, %.1f}\n", res[0], res[1], res[2], res[3]); \
} while (0)

int main(void) {
    float4 a = {1.0, 2.0, 3.0, 4.0};
    float4 b = {5.0, 6.0, 7.0, 8.0};

    // Masks: 0–3 pull from 'a', 4–7 pull from 'b'
    __v4si mask1 = {0, 1, 2, 3}; // identity from a
    __v4si mask2 = {4, 5, 6, 7}; // identity from b
    __v4si mask3 = {0, 4, 1, 5}; // interleave a,b
    __v4si mask4 = {2, 7, 0, 5}; // mixed arbitrary
    __v4si mask5 = {7, 6, 5, 4}; // reverse b
    __v4si mask6 = {3, 2, 1, 0}; // reverse a
    __v4si mask7 = {0, 7, 4, 3}; // cross edges
    __v4si mask8 = {1, 4, 6, 2}; // mixed mid
    __v4si mask9 = {0, 4, 2, 7}; // your example

    TEST_SHUFFLE(a, b, mask1);
    TEST_SHUFFLE(a, b, mask2);
    TEST_SHUFFLE(a, b, mask3);
    TEST_SHUFFLE(a, b, mask4);
    TEST_SHUFFLE(a, b, mask5);
    TEST_SHUFFLE(a, b, mask6);
    TEST_SHUFFLE(a, b, mask7);
    TEST_SHUFFLE(a, b, mask8);
    TEST_SHUFFLE(a, b, mask9);

    return 0;
}
