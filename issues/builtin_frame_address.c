#include <stdio.h>

int main() {
    void *f0 = __builtin_frame_address(0);
    printf("%p\n", f0);
    void *f1 = __builtin_frame_address(1);
    printf("%p\n", f1);
    void *f2 = __builtin_frame_address(2);
    printf("%p\n", f2);
    void *f3 = __builtin_frame_address(3);
    printf("%p\n", f3);
    
    printf("Frame address (level 0): %p\n", f0);
    printf("Frame address (level 1): %p\n", f1);
    printf("Frame address (level 2): %p\n", f2);
    printf("Frame address (level 3): %p\n", f3);
}
