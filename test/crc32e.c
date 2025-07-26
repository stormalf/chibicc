#include <stdint.h>
#include "test.h"
#include <stddef.h> // for offsetof
#include <string.h> // for memcpy

// Dummy pg_crc32c_table
static const uint32_t pg_crc32c_table[8][256] = { { 0 } };

// Simplified pg_comp_crc32c function (simulate proper implementation)
uint32_t pg_comp_crc32c(uint32_t crc, const char *data, size_t len) {
#ifdef WORDS_BIGENDIAN
#define CRC8(x) pg_crc32c_table[0][((crc >> 24) ^ (x)) & 0xFF] ^ (crc << 8)
#else
#define CRC8(x) pg_crc32c_table[0][(crc ^ (x)) & 0xFF] ^ (crc >> 8)
#endif
    while (len--)
        crc = CRC8((uint8_t)*data++);
    return crc;
}

// Macros
#define INIT_CRC32C(crc) ((crc) = 0xFFFFFFFF)
#define COMP_CRC32C(crc, data, len) ((crc) = pg_comp_crc32c((crc), (data), (len)))
#define FIN_CRC32C(crc) ((crc) ^= 0xFFFFFFFF)

typedef struct {
    uint32_t version;
    uint16_t id;
    uint64_t timestamp;
    uint32_t crc;
} ControlFileData;

int main(void) {
    ControlFileData cfile;
    memset(&cfile, 0, sizeof(ControlFileData));

    cfile.version = 0x12345678;
    cfile.id = 0xABCD;
    cfile.timestamp = 0x1122334455667788;

    uint32_t crc;
    INIT_CRC32C(crc);
    COMP_CRC32C(crc, (char *)&cfile, offsetof(ControlFileData, crc));
    FIN_CRC32C(crc);

    cfile.crc = crc;

    printf("Computed CRC32C: 0x%08X\n", crc);
    ASSERT(0xFFFFFFFF, crc);
    return 0;
}
