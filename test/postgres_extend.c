#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* ---- PostgreSQL-like typedefs ---- */

typedef uint32_t BlockNumber;
typedef int ForkNumber;

#define InvalidBlockNumber ((BlockNumber)107)

/* ---- Interrupt macros (intentionally non-trivial) ---- */

static volatile int interrupt_hold_depth = 0;

#define HOLD_INTERRUPTS()   do { interrupt_hold_depth++; } while (0)
#define RESUME_INTERRUPTS() do { interrupt_hold_depth--; } while (0)

/* ---- SMgrRelation definition ---- */

typedef struct SMgrRelationData {
    int smgr_which;
    BlockNumber smgr_cached_nblocks[4];
} SMgrRelationData;

typedef SMgrRelationData *SMgrRelation;

/* ---- smgr switch table ---- */

typedef void (*smgr_zeroextend_fn)(
    SMgrRelation reln,
    ForkNumber forknum,
    BlockNumber blocknum,
    int nblocks,
    bool skipFsync
);

typedef struct {
    smgr_zeroextend_fn smgr_zeroextend;
} smgrsw_entry;

/* ---- Test instrumentation ---- */

static int last_seen_nblocks = -1;
static BlockNumber last_seen_blocknum = 0;
static ForkNumber last_seen_forknum = -1;

/* ---- Backend implementation ---- */

static void
test_zeroextend(SMgrRelation reln,
                ForkNumber forknum,
                BlockNumber blocknum,
                int nblocks,
                bool skipFsync)
{
    (void)skipFsync;

    /* Capture arguments to detect corruption */
    last_seen_nblocks = nblocks;
    last_seen_blocknum = blocknum;
    last_seen_forknum = forknum;

    /* Simulate extension */
    reln->smgr_cached_nblocks[forknum] = blocknum + nblocks;
}

/* ---- Global switch table ---- */

static smgrsw_entry smgrsw[] = {
    { test_zeroextend }
};

/* ---- Function under test (verbatim logic) ---- */

void
smgrzeroextend(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum,
               int nblocks, bool skipFsync)
{
    HOLD_INTERRUPTS();

    smgrsw[reln->smgr_which].smgr_zeroextend(
        reln, forknum, blocknum, nblocks, skipFsync
    );

    if (reln->smgr_cached_nblocks[forknum] == blocknum)
        reln->smgr_cached_nblocks[forknum] = blocknum + nblocks;
    else
        reln->smgr_cached_nblocks[forknum] = InvalidBlockNumber;

    RESUME_INTERRUPTS();
}

/* ---- Test harness ---- */

int main(void)
{
    SMgrRelationData reln;
    reln.smgr_which = 0;

    for (int i = 0; i < 4; i++)
        reln.smgr_cached_nblocks[i] = 0;

    BlockNumber blocknum = 100;
    int extend_by = 7;
    ForkNumber forknum = 1;

    smgrzeroextend(&reln, forknum, blocknum, extend_by, false);

    /* ---- Validation ---- */

    if (last_seen_nblocks != extend_by) {
        fprintf(stderr,
                "FAIL: nblocks corrupted (expected %d, got %d)\n",
                extend_by, last_seen_nblocks);
        return 1;
    }

    if (last_seen_blocknum != blocknum) {
        fprintf(stderr,
                "FAIL: blocknum corrupted\n");
        return 2;
    }

    if (reln.smgr_cached_nblocks[forknum] != blocknum + extend_by) {
        fprintf(stderr,
                "FAIL: cached_nblocks wrong (expected %u, got %u)\n",
                blocknum + extend_by,
                reln.smgr_cached_nblocks[forknum]);
        return 3;
    }

    if (interrupt_hold_depth != 0) {
        fprintf(stderr,
                "FAIL: interrupt depth mismatch (%d)\n",
                interrupt_hold_depth);
        return 4;
    }

    printf("PASS\n");
    return 0;
}
