#include <stdio.h>
#include <stdint.h>
#include <assert.h>

struct S {
    uint8_t a;
    uint8_t b;
    uint32_t c;
};

int main() {
    struct S s = {0, 0, 0x12345678};
    s.a++;
    printf("s.a = %d, s.b = %d, s.c = 0x%x\n", s.a, s.b, s.c);
    assert(s.a == 1);
    assert(s.b == 0);
    assert(s.c == 0x12345678);
    
    s.b = 255;
    s.b++;
    printf("s.b = %d\n", s.b);
    assert(s.b == 0);
    
    printf("SUCCESS\n");
    return 0;
}
