#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
    uint32_t f1;
    uint32_t f2;
    uint32_t f3;
    uint16_t f4;
    uint8_t f5;
    uint8_t f6;
} LOCKTAG;

typedef struct {
    LOCKTAG lock;
    int mode;
} LOCALLOCKTAG;

// Mock MemSet similar to PostgreSQL's
#define MemSet(start, val, len) memset(start, val, len)

int main() {
    printf("sizeof(LOCKTAG) = %zu\n", sizeof(LOCKTAG));
    printf("sizeof(LOCALLOCKTAG) = %zu\n", sizeof(LOCALLOCKTAG));
    
    assert(sizeof(LOCKTAG) == 16);
    // On 64-bit, we expect 8-byte alignment, so 20 -> 24
    // assert(sizeof(LOCALLOCKTAG) == 24);

    LOCALLOCKTAG tag;
    // Fill with garbage
    memset(&tag, 0x5a, sizeof(tag));
    
    // Clear with MemSet
    MemSet(&tag, 0, sizeof(tag));
    
    uint8_t *p = (uint8_t *)&tag;
    for (size_t i = 0; i < sizeof(tag); i++) {
        if (p[i] != 0) {
            printf("ERROR: byte %zu is not zero: 0x%02x\n", i, p[i]);
            return 1;
        }
    }
    
    printf("SUCCESS: all bytes cleared\n");
    return 0;
}
