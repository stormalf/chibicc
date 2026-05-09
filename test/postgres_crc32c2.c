#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef uint32_t uint32;
typedef uint8_t uint8;
typedef uint32_t pg_crc32c;
#define MOCK_AUTH_NONCE_LEN 32

typedef struct {
    uint32_t pg_control_version;
    uint32_t catalog_version_no;
    uint32_t maxAlign;
    uint32_t floatFormat;
    uint32_t blcksz;
    uint32_t relseg_size;
    uint32_t xlog_blcksz;
    uint32_t xlog_seg_size;
    uint32_t nameDataLen;
    uint32_t indexMaxKeys;
    uint32_t toast_max_chunk_size;
    uint32_t loblksize;
    uint32_t float8ByVal;
    uint8_t default_char_signedness;
    char mock_authentication_nonce[MOCK_AUTH_NONCE_LEN];
    pg_crc32c crc;
} ControlFileData;

int main(void) {
    
    printf("offsetof(crc) = %zu\n", offsetof(ControlFileData, crc));
    printf("sizeof(ControlFileData) = %zu\n", sizeof(ControlFileData));
    return 0;
}
