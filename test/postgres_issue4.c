#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>  // Required for offsetof
#include "test.h"

#define PGSTAT_KIND_MIN 1
#define PGSTAT_KIND_MAX	256		/* Maximum ID allowed */
#define PGSTAT_KIND_CUSTOM_MIN	128
#define PGSTAT_KIND_CUSTOM_MAX	PGSTAT_KIND_MAX
#define PGSTAT_KIND_CUSTOM_SIZE	(PGSTAT_KIND_CUSTOM_MAX - PGSTAT_KIND_CUSTOM_MIN + 1)
#define PGSTAT_KIND_BUILTIN_SIZE 10  // Size based on the number of elements in pgstat_kind_builtin_infos

// Define the dummy callback functions
void pgstat_archiver_init_shmem_cb(void *stats) { printf("Archiver init_shmem_cb called with %p\n", stats); }
void pgstat_bgwriter_init_shmem_cb(void *stats) { printf("BgWriter init_shmem_cb called with %p\n", stats); }
void pgstat_checkpointer_init_shmem_cb(void *stats) { printf("Checkpointer init_shmem_cb called with %p\n", stats); }
void pgstat_io_init_shmem_cb(void *stats) { printf("IO init_shmem_cb called with %p\n", stats); }
void pgstat_slru_init_shmem_cb(void *stats) { printf("SLRU init_shmem_cb called with %p\n", stats); }
void pgstat_wal_init_shmem_cb(void *stats) { printf("WAL init_shmem_cb called with %p\n", stats); }
void pgstat_database_flush_cb(void) { printf("database flush\n"); }
void pgstat_database_reset_timestamp_cb(void) { printf("database reset timestamp\n"); }
void pgstat_relation_flush_cb(void) { printf("pgstat_relation_flush_cb\n"); }
void pgstat_relation_delete_pending_cb(void) { printf("pgstat_relation_delete_pending_cb\n"); }
void pgstat_function_flush_cb(void) { printf("pgstat_function_flush_cb\n"); }
void pgstat_subscription_flush_cb(void) { printf("pgstat_subscription_flush_cb\n"); }
void pgstat_subscription_reset_timestamp_cb(void) { printf("pgstat_subscription_reset_timestamp_cb\n"); }
void pgstat_replslot_reset_timestamp_cb(void) { printf("pgstat_replslot_reset_timestamp_cb\n"); }
void pgstat_replslot_to_serialized_name_cb(void) { printf("pgstat_replslot_to_serialized_name_cb\n"); }
void pgstat_replslot_from_serialized_name_cb(void) { printf("pgstat_replslot_from_serialized_name_cb\n"); }


typedef int PgStat_Kind;
typedef int TimestampTz;
typedef struct PgStat_EntryRef PgStat_EntryRef;
typedef struct PgStat_ShmemControl PgStat_ShmemControl;
typedef struct PgStat_HashKey PgStat_HashKey;
typedef struct PgStatShared_Common PgStatShared_Common;
typedef struct NameData NameData;

// Define some dummy structures to satisfy the offsetof macro usage
typedef struct PgStatShared_Database { int stats; } PgStatShared_Database;
typedef struct PgStatShared_Relation { int stats; } PgStatShared_Relation;
typedef struct PgStatShared_Function { int stats; } PgStatShared_Function;
typedef struct PgStatShared_ReplSlot { int stats; } PgStatShared_ReplSlot;
typedef struct PgStatShared_Subscription { int stats; } PgStatShared_Subscription;
typedef struct PgStatShared_Archiver { int stats; } PgStatShared_Archiver;
typedef struct PgStatShared_BgWriter { int stats; } PgStatShared_BgWriter;
typedef struct PgStatShared_Checkpointer { int stats; } PgStatShared_Checkpointer;
typedef struct PgStatShared_IO { int stats; } PgStatShared_IO;
typedef struct PgStatShared_SLRU { int stats; } PgStatShared_SLRU;
typedef struct PgStatShared_Wal { int stats; } PgStatShared_Wal;

typedef struct PgStat_Snapshot {
    PgStatShared_Archiver archiver;
    PgStatShared_BgWriter bgwriter;
    PgStatShared_Checkpointer checkpointer;
    PgStatShared_IO io;
    PgStatShared_SLRU slru;
    PgStatShared_Wal wal;
} PgStat_Snapshot;

typedef struct PgStat_KindInfo {
    bool        fixed_amount : 1;
    bool        accessed_across_databases : 1;
    uint32_t    shared_size;
    uint32_t    snapshot_ctl_off;
    uint32_t    shared_ctl_off;
    uint32_t    shared_data_off;
    uint32_t    shared_data_len;
    uint32_t    pending_size;
    bool        (*flush_pending_cb)(PgStat_EntryRef *sr, bool nowait);
    void        (*delete_pending_cb)(PgStat_EntryRef *sr);
    void        (*reset_timestamp_cb)(PgStatShared_Common *header, TimestampTz ts);
    void        (*to_serialized_name)(const PgStat_HashKey *key, const PgStatShared_Common *header, NameData *name);
    bool        (*from_serialized_name)(const NameData *name, PgStat_HashKey *key);
    void        (*init_shmem_cb)(void *stats);
    void        (*reset_all_cb)(TimestampTz ts);
    void        (*snapshot_cb)(void);
    const char *const name;
} PgStat_KindInfo;

typedef struct PgStat_ShmemControl {
    void *custom_data[PGSTAT_KIND_CUSTOM_MAX - PGSTAT_KIND_CUSTOM_MIN + 1];
    // Added dummy members for fixed amounts
    PgStatShared_Archiver archiver;
    PgStatShared_BgWriter bgwriter;
    PgStatShared_Checkpointer checkpointer;
    PgStatShared_IO io;
    PgStatShared_SLRU slru;
    PgStatShared_Wal wal;
} PgStat_ShmemControl;


// Updated PgStat_KindInfo array with missing elements
static const PgStat_KindInfo pgstat_kind_builtin_infos[PGSTAT_KIND_BUILTIN_SIZE] = {
    [0] = {0},  // Placeholder for index 0

    [1] = {
        .name = "database",
        .fixed_amount = false,
        .accessed_across_databases = true,
        .shared_size = sizeof(PgStatShared_Database),
        .shared_data_off = offsetof(PgStatShared_Database, stats),
        .shared_data_len = sizeof(((PgStatShared_Database *) 0)->stats),
        .flush_pending_cb = pgstat_database_flush_cb,
        .reset_timestamp_cb = pgstat_database_reset_timestamp_cb,
    },
    [2] = {
        .name = "relation",
        .fixed_amount = false,
        .shared_size = sizeof(PgStatShared_Relation),
        .shared_data_off = offsetof(PgStatShared_Relation, stats),
        .shared_data_len = sizeof(((PgStatShared_Relation *) 0)->stats),
        .flush_pending_cb = pgstat_relation_flush_cb,
        .delete_pending_cb = pgstat_relation_delete_pending_cb,
    },
    [3] = {
        .name = "function",
        .fixed_amount = false,
        .shared_size = sizeof(PgStatShared_Function),
        .shared_data_off = offsetof(PgStatShared_Function, stats),
        .shared_data_len = sizeof(((PgStatShared_Function *) 0)->stats),
        .flush_pending_cb = pgstat_function_flush_cb,
    },
    [4] = {
        .name = "replslot",
        .fixed_amount = false,
        .accessed_across_databases = true,
        .shared_size = sizeof(PgStatShared_ReplSlot),
        .shared_data_off = offsetof(PgStatShared_ReplSlot, stats),
        .shared_data_len = sizeof(((PgStatShared_ReplSlot *) 0)->stats),
        .reset_timestamp_cb = pgstat_replslot_reset_timestamp_cb,
        .to_serialized_name = pgstat_replslot_to_serialized_name_cb,
        .from_serialized_name = pgstat_replslot_from_serialized_name_cb,
    },
    [5] = {
        .name = "subscription",
        .fixed_amount = false,
        .accessed_across_databases = true,
        .shared_size = sizeof(PgStatShared_Subscription),
        .shared_data_off = offsetof(PgStatShared_Subscription, stats),
        .shared_data_len = sizeof(((PgStatShared_Subscription *) 0)->stats),
        .flush_pending_cb = pgstat_subscription_flush_cb,
        .reset_timestamp_cb = pgstat_subscription_reset_timestamp_cb,
    },
    [6] = {
        .name = "archiver",
        .fixed_amount = true,
        .shared_size = sizeof(PgStatShared_Archiver),
        .snapshot_ctl_off = offsetof(PgStat_Snapshot, archiver),
        .shared_ctl_off = offsetof(PgStat_ShmemControl, archiver),
        .shared_data_off = offsetof(PgStatShared_Archiver, stats),
        .shared_data_len = sizeof(((PgStatShared_Archiver *) 0)->stats),
        .init_shmem_cb = pgstat_archiver_init_shmem_cb,
        .reset_all_cb = NULL,
        .snapshot_cb = NULL,
    },
    [7] = {
        .name = "bgwriter",
        .fixed_amount = true,
        .snapshot_ctl_off = offsetof(PgStat_Snapshot, bgwriter),
        .shared_ctl_off = offsetof(PgStat_ShmemControl, bgwriter),
        .shared_data_off = offsetof(PgStatShared_BgWriter, stats),
        .shared_data_len = sizeof(((PgStatShared_BgWriter *) 0)->stats),
        .init_shmem_cb = pgstat_bgwriter_init_shmem_cb,
        .reset_all_cb = NULL,
        .snapshot_cb = NULL,
    },
    [8] = {
        .name = "checkpointer",
        .fixed_amount = true,
        .snapshot_ctl_off = offsetof(PgStat_Snapshot, checkpointer),
        .shared_ctl_off = offsetof(PgStat_ShmemControl, checkpointer),
        .shared_data_off = offsetof(PgStatShared_Checkpointer, stats),
        .shared_data_len = sizeof(((PgStatShared_Checkpointer *) 0)->stats),
        .init_shmem_cb = pgstat_checkpointer_init_shmem_cb,
        .reset_all_cb = NULL,
        .snapshot_cb = NULL,
    },
    [9] = {
        .name = "io",
        .fixed_amount = true,
        .snapshot_ctl_off = offsetof(PgStat_Snapshot, io),
        .shared_ctl_off = offsetof(PgStat_ShmemControl, io),
        .shared_data_off = offsetof(PgStatShared_IO, stats),
        .shared_data_len = sizeof(((PgStatShared_IO *) 0)->stats),
        .init_shmem_cb = pgstat_io_init_shmem_cb,
        .reset_all_cb = NULL,
        .snapshot_cb = NULL,
    },
};

const PgStat_KindInfo* pgstat_get_kind_info(PgStat_Kind kind)
{
    if (kind >= PGSTAT_KIND_MIN && kind <= PGSTAT_KIND_MAX)
        return &pgstat_kind_builtin_infos[kind];
    return NULL;
}

bool pgstat_is_kind_builtin(PgStat_Kind kind)
{
    return kind < PGSTAT_KIND_CUSTOM_MIN;
}

void* ShmemAlloc(size_t size)
{
    return malloc(size);
}

/* Dummy init_shmem_cb implementation */
void my_init_shmem_cb(void *stats)
{
    printf("Shared memory initialized with size: %p\n", stats);
}


int main(void)
{
    PgStat_ShmemControl *ctl = malloc(sizeof(PgStat_ShmemControl));

    if (ctl == NULL) {
        perror("Failed to allocate memory for PgStat_ShmemControl");
        return EXIT_FAILURE;
    }

    /* Initialize fixed-numbered stats */
    for (PgStat_Kind kind = PGSTAT_KIND_MIN; kind <= 6; kind++)
    {
        const PgStat_KindInfo *kind_info = pgstat_get_kind_info(kind);
        char *ptr = NULL;

        if (!kind_info) {
            printf("No kind info found for kind %d\n", kind);
            continue;
        }

        if (kind_info->fixed_amount) {
            if (pgstat_is_kind_builtin(kind)) {
                ptr = ((char *)ctl) + kind_info->shared_ctl_off;
            } else {
                int idx = kind - PGSTAT_KIND_CUSTOM_MIN;
                ctl->custom_data[idx] = ShmemAlloc(kind_info->shared_size);
                if (ctl->custom_data[idx] == NULL) {
                    perror("Failed to allocate memory for custom_data");
                    continue;
                }
                ptr = ctl->custom_data[idx];
            }
            printf("Initializing %s with shared size %u\n", kind_info->name, kind_info->shared_size);
            printf("init_shmem_cb is NULL for kind %d %d %d %d %ld %d\n", kind, sizeof(PgStatShared_Archiver), kind_info->shared_size, kind, sizeof(kind_info), kind_info->fixed_amount);
            ASSERT(4, sizeof(PgStatShared_Archiver));
            ASSERT(4, kind_info->shared_size);
            ASSERT(6, kind);
            ASSERT(8,  sizeof(kind_info));
            ASSERT(1, kind_info->fixed_amount);
            kind_info->init_shmem_cb(ptr);
            
        }
    }
    printf("Initialization complete\n");

    free(ctl);
    return 0;
}
