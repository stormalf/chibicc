#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint32_t padding[252]; // 1008 bytes
    uint32_t offset[20];
} ShmemControl;

int main() {
    ShmemControl ctrl;
    printf("Base: %p\n", (void *)&ctrl);
    for (int i = 0; i < 15; i++) {
        printf("Kind %d - Offset: %zu, Pointer: %p\n", 
               i, (size_t)((char *)&ctrl.offset[i] - (char *)&ctrl), (void *)&ctrl.offset[i]);
    }
    return 0;
}
