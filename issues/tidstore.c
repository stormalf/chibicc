#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define BITS_PER_BITMAPWORD 32
#define WORDNUM(x)   ((x) / BITS_PER_BITMAPWORD)
#define BITNUM(x)    ((x) % BITS_PER_BITMAPWORD)

#define InvalidOffsetNumber 0
#define PG_INT8_MAX 127
#define MaxOffsetNumber 2048

typedef uint16_t OffsetNumber;
typedef uint32_t bitmapword;
typedef uint32_t BlockNumber;

#define FLEXIBLE_ARRAY_MEMBER 
/* NUM_FULL_OFFSETS calculation */
#define NUM_FULL_OFFSETS ((sizeof(uintptr_t) - sizeof(uint8_t) - sizeof(int8_t)) / sizeof(OffsetNumber))

#define MAX_OFFSET_IN_BITMAP (BITS_PER_BITMAPWORD * PG_INT8_MAX - 1)
#define WORDS_PER_PAGE(n)    ((n) / BITS_PER_BITMAPWORD + 1)

typedef struct BlocktableEntry
{
    struct
    {
        uint8_t flags;
        int8_t nwords;
        OffsetNumber full_offsets[NUM_FULL_OFFSETS];
    } header;

    bitmapword words[FLEXIBLE_ARRAY_MEMBER]; // Flexible array member
} BlocktableEntry;

#define MaxBlocktableEntrySize \
    (offsetof(BlocktableEntry, words) + sizeof(bitmapword) * WORDS_PER_PAGE(MAX_OFFSET_IN_BITMAP))

typedef struct TidStore
{
    struct
    {
        void *shared;
        void *local;
    } tree;

    int is_shared;
} TidStore;

#define Assert assert

#define elog(level, ...) do { \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
    exit(1); \
} while (0)

int TidStoreIsShared(TidStore *ts) {
    return ts->is_shared;
}

void shared_ts_set(void *shared, BlockNumber blkno, BlocktableEntry *page) {
    printf("Shared store set: blkno=%u, nwords=%d\n", blkno, page->header.nwords);
}

void local_ts_set(void *local, BlockNumber blkno, BlocktableEntry *page) {
    printf("Local store set: blkno=%u, nwords=%d\n", blkno, page->header.nwords);
}

void TidStoreSetBlockOffsets(TidStore *ts, BlockNumber blkno, OffsetNumber *offsets, int num_offsets)
{
    union
    {
        char data[MaxBlocktableEntrySize];
        BlocktableEntry force_align_entry;
    } data;

    BlocktableEntry *page = (BlocktableEntry *) data.data;
    bitmapword word;
    int wordnum;
    int next_word_threshold;
    int idx = 0;

    Assert(num_offsets > 0);

    /* Check if the given offset numbers are ordered */
    for (int i = 1; i < num_offsets; i++)
        Assert(offsets[i] > offsets[i - 1]);

    memset(page, 0, offsetof(BlocktableEntry, words));

    if (num_offsets <= NUM_FULL_OFFSETS)
    {
        for (int i = 0; i < num_offsets; i++)
        {
            OffsetNumber off = offsets[i];

            /* safety check to ensure we don't overrun bit array bounds */
            if (off == InvalidOffsetNumber || off > MAX_OFFSET_IN_BITMAP)
                elog(1, "tuple offset out of range: %u", off);

            page->header.full_offsets[i] = off;
        }

        page->header.nwords = 0;
    }
    else
    {
        for (wordnum = 0, next_word_threshold = BITS_PER_BITMAPWORD;
             wordnum <= WORDNUM(offsets[num_offsets - 1]);
             wordnum++, next_word_threshold += BITS_PER_BITMAPWORD)
        {
            word = 0;

            while (idx < num_offsets)
            {
                OffsetNumber off = offsets[idx];

                /* safety check to ensure we don't overrun bit array bounds */
                if (off == InvalidOffsetNumber || off > MAX_OFFSET_IN_BITMAP)
                    elog(1, "tuple offset out of range: %u", off);

                if (off >= next_word_threshold)
                    break;

                word |= ((bitmapword) 1 << BITNUM(off));
                idx++;
            }

            /* write out offset bitmap for this wordnum */
            page->words[wordnum] = word;
        }

        page->header.nwords = wordnum;
        Assert(page->header.nwords == WORDS_PER_PAGE(offsets[num_offsets - 1]));
    }

    if (TidStoreIsShared(ts))
        shared_ts_set(ts->tree.shared, blkno, page);
    else
        local_ts_set(ts->tree.local, blkno, page);
}

int main() {
    TidStore ts = { .is_shared = 0 }; // Set to local store
    OffsetNumber offsets[] = {1, 2, 33, 34, 35};
    int num_offsets = sizeof(offsets) / sizeof(offsets[0]);

    printf("NUM_FULL_OFFSETS: %d\n", NUM_FULL_OFFSETS);
    TidStoreSetBlockOffsets(&ts, 42, offsets, num_offsets);

    return 0;
}
