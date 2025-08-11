#include "test.h"

// Declare the builtin manually without any headers
typedef long long __m128; 
typedef float __v4sf __attribute__((vector_size(16)));

// A struct with a float member
struct S {
    float f;
};


int main(void) {
    // Create a vector of 4 floats (like __v4sf)
   __v4sf vec = { 123.456f, 2.0f, -3.0f, 99.0f };

    // Convert the lowest float to 64-bit int
    __m128 result = __builtin_ia32_cvttss2si(vec);

    printf("Input[0] = %.3f -> int64 = %lld\n", vec[0], result);

    if (result == 123)
        printf("PASS\n");
    else
        printf("FAIL\n");

    ASSERT(123, result);

    struct S s = { 456.25f };

    __v4sf member_vec = { s.f, 0.0f, 0.0f, 0.0f };
    int result_member = __builtin_ia32_cvttss2si(member_vec);
    printf("Struct member float: %.2f -> int: %d\n", member_vec[0], result_member);
    ASSERT(456, result_member);
    printf("OK\n");
    return  0;
}
