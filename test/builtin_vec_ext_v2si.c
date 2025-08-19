#include "test.h"

// Define a 2-element int vector type (like __v2si)
typedef int v2si __attribute__((vector_size(8)));

// Prototype for the builtin so the compiler accepts it
int __builtin_ia32_vec_ext_v2si(v2si vec, int index);

int main(void) {
    // Create a vector with two ints: 123456 and 789012
    v2si v = {123456, 789012};

    // Extract elements using the builtin
    int elem0 = __builtin_ia32_vec_ext_v2si(v, 0);
    int elem1 = __builtin_ia32_vec_ext_v2si(v, 1);

    printf("elem0 = %d\n", elem0);
    printf("elem1 = %d\n", elem1);
    ASSERT(123456, elem0);
    ASSERT(789012, elem1);

    return 0;
}
