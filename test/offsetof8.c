#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "test.h"

#define FLEXIBLE_ARRAY_MEMBER /* empty */

// Dummy definitions for types used within DecodedBkpBlock and DecodedXLogRecord
typedef uint32_t BlockNumber;
typedef uint8_t ForkNumber;
typedef int32_t Buffer;
typedef uint32_t XLogRecPtr;
typedef uint32_t XLogRecord;
typedef uint16_t RepOriginId;
typedef uint32_t TransactionId;

typedef struct {
    int dummy; // Placeholder to represent RelFileLocator
} RelFileLocator;

// Original struct definitions

typedef struct {
    bool        in_use;
    RelFileLocator rlocator;
    ForkNumber  forknum;
    BlockNumber blkno;
    Buffer      prefetch_buffer;
    uint8_t     flags;
    bool        has_image;
    bool        apply_image;
    char        *bkp_image;
    uint16_t    hole_offset;
    uint16_t    hole_length;
    uint16_t    bimg_len;
    uint8_t     bimg_info;
    bool        has_data;
    char        *data;
    uint16_t    data_len;
    uint16_t    data_bufsz;
} DecodedBkpBlock;

typedef struct {
    size_t      size;
    bool        oversized;
    struct DecodedXLogRecord *next;

    XLogRecPtr  lsn;
    XLogRecPtr  next_lsn;
    XLogRecord  header;
    RepOriginId record_origin;
    TransactionId toplevel_xid;
    char        *main_data;
    uint32_t    main_data_len;
    int         max_block_id;
    DecodedBkpBlock blocks[FLEXIBLE_ARRAY_MEMBER];
} DecodedXLogRecord;

int main() {
    // Try to calculate offset of the flexible array member
    size_t offset = offsetof(DecodedXLogRecord, blocks[0]);
    printf("Offset of 'blocks[0]' in DecodedXLogRecord: %zu\n", offset);
    ASSERT(64, offset);

    return 0;
}
