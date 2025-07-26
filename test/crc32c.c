#include "test.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "crc32c.h"
// Postgres-style macros
#define INIT_CRC32C(crc) ((crc) = 0xFFFFFFFF)
#define FIN_CRC32C(crc) ((crc) ^= 0xFFFFFFFF)
#define COMP_CRC32C(crc, data, len) ((crc) = pg_comp_crc32c((crc), (data), (len)))

// Simple table-based CRC32C (Castagnoli) — assume you've already filled `pg_crc32c_table`
extern const uint32_t pg_crc32c_table[8][256];

// Reference implementation
uint32_t pg_comp_crc32c(uint32_t crc, const void *data, size_t len) {
    const uint8_t *p = data;

    while (len--)
        crc = pg_crc32c_table[0][(crc ^ *p++) & 0xFF] ^ (crc >> 8);

    return crc;
}

// Custom structure simulating Postgres control file
typedef struct {
    uint32_t system_id;
    uint32_t state;
    uint8_t  data[16];
    uint32_t crc;  // stored CRC
} ControlFileData;

int main() {
    ControlFileData cf = {
        .system_id = 0xAABBCCDD,
        .state = 0x11223344,
        .data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        .crc = 0
    };

    uint32_t crc;
    INIT_CRC32C(crc);
    COMP_CRC32C(crc, (char*)&cf, offsetof(ControlFileData, crc));
    FIN_CRC32C(crc);

    printf("Computed CRC32C: 0x%08X\n", crc);
    ASSERT(0xB3D795D9, crc);

    return 0;
}
