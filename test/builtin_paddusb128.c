#include "test.h"

typedef char v16hi __attribute__((vector_size(16)));
typedef unsigned char v16hu __attribute__((vector_size(16)));

int main() {
    v16hi a_vals = {
        250, 10, 200, 255, 100, 0, 50,  240,
        128, 64,  255, 1,   20, 30, 40,  50
    };
    v16hi b_vals = {
        10,  250, 100, 10, 200, 255, 250, 20,
        128, 200,  1,  255, 240, 230, 220, 210
    };

    v16hu result = (v16hu)__builtin_ia32_paddusb128(a_vals, b_vals);
    for (int i = 0; i < 16; i++) {
        printf("Result: %3u\n", result[i]);
        ASSERT(255, result[i]);
    }

    printf("\n");
    

    printf("OK\n");

    return 0;
}
