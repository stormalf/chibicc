#include <stdio.h>

typedef float __v4si __attribute__((__vector_size__(16)));
//typedef int __v4si;

void process_vector(__v4si vec) {
    for (int i = 0; i < 4; i++) {
        printf("vec[%d] = %d\n", i, vec[i]);
    }
}

int main() {
    __v4si vec = {1, 2, 3, 4};
    process_vector(vec);
    return 0;
}
