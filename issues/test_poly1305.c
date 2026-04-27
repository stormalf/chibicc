#include <stdio.h>
#include <stdint.h>
#include <string.h>

void poly1305_blocks(void *ctx, const unsigned char *inp, size_t len, uint32_t padbit);

void __attribute__((noinline)) caller(void *ctx, const unsigned char *inp, size_t len, uint32_t padbit) {
    char padding[1];
    padding[0] = 0;
    poly1305_blocks(ctx, inp, len, padbit);
    (void)padding;
}

int main() {
    char x = 'a';
    uint32_t ctx[16] = {0};
    unsigned char inp[16] = {0};
    
    printf("Calling poly1305_blocks via caller...\n");
    caller(ctx, inp, 16, 0);
    printf("Successfully returned.\n");
    
    return 0;
}
