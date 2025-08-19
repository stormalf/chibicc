#include "test.h"

#define SCALAR 500

typedef int int4 __attribute__((vector_size(16)));

int main() {
    // This will trigger Chibicc error:
    int4 v = SCALAR;  // vector initializer must be an initializer list

    // Workaround: use braces
    int4 v2 = {SCALAR};

    // Print v2 to verify
    for (int i = 0; i < 4; i++) {
        printf("%d ", v2[i]);
    }
    printf("\n");

    ASSERT(500, v2[0]);
    ASSERT(0, v2[1]);
    ASSERT(0, v2[2]);
    ASSERT(0, v2[3]);

    return 0;
}
