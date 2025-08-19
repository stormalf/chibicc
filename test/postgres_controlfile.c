#include "test.h"
#include <string.h>
#include <stdint.h>

typedef struct {
    union {
        uint32_t x;
        uint64_t y;
    } u;
    uint32_t version;
    uint8_t flags[4];
} ControlFile;

int main(void) {
    ControlFile cf;

    // Zero the whole struct (mimics memset in write_gvar_data)
    memset(&cf, 0, sizeof(cf));

    // Initialize union member 'x'
    cf.u.x = 0x12345678;

    // Initialize version
    cf.version = 42;

    // Initialize flags array
    cf.flags[0] = 1;
    cf.flags[1] = 2;
    cf.flags[2] = 3;
    cf.flags[3] = 4;

    // "Write" the struct to a buffer
    uint8_t buf[sizeof(ControlFile)];
    memcpy(buf, &cf, sizeof(cf));

    // Print buffer contents in hex
    printf("Buffer bytes:\n");
    for (size_t i = 0; i < sizeof(buf); i++) {
        printf("%02x ", buf[i]);
        if ((i + 1) % 8 == 0) printf("\n");
    }
    ASSERT(0x78, buf[0]);
    ASSERT(0x56, buf[1]);
    ASSERT(0x34, buf[2]);
    ASSERT(0x12, buf[3]);
    ASSERT(0x00, buf[4]);
    ASSERT(0x00, buf[5]);
    ASSERT(0x00, buf[6]);
    ASSERT(0x00, buf[7]);
    ASSERT(0x2a, buf[8]);
    ASSERT(0x00, buf[9]);
    ASSERT(0x00, buf[10]);
    ASSERT(0x00, buf[11]);
    ASSERT(0x01, buf[12]);
    ASSERT(0x02, buf[13]);
    ASSERT(0x03, buf[14]);
    ASSERT(0x04, buf[15]);
    return 0;
}
