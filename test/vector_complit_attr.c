#include "test.h"

int main() {
    int x = 0;
    // compound literal with inline __attribute__ before type (like xmmintrin.h _mm_move_ss)
    x += ((__attribute__((__vector_size__(16))) int){42, 0, 0, 0})[0];
    return x - 42;
}
