#include <stdio.h>
#include "test.h"

typedef float __v4si __attribute__((__vector_size__(16)));
//typedef int __v4si;

void process_vector(__v4si vec) {
    for (int i = 0; i < 4; i++) {
        printf("vec[%d] = %f\n", i, vec[i]);
    }
}

int main() {
    __v4si vec = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        printf("vec[%d] = %f\n", i, vec[i]);
        if (i == 0) {
            ASSERT(1, vec[i]);
        } else if (i == 1) {
            ASSERT(2, vec[i]);
        } else if (i == 2) {
            ASSERT(3, vec[i]);
        } else if (i == 3) {
            ASSERT(4, vec[i]);
        }
    }
    process_vector(vec);
    return 0;
}
