#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define PGSTAT_KIND_MIN 1
#define PGSTAT_KIND_MAX 3
#define PGSTAT_KIND_CUSTOM_MIN 4
#define PGSTAT_KIND_CUSTOM_MAX 6

typedef int PgStat_Kind;
typedef int TimestampTz;
typedef struct PgStat_EntryRef PgStat_EntryRef;
typedef struct PgStat_ShmemControl PgStat_ShmemControl;
typedef struct PgStat_HashKey PgStat_HashKey;
typedef struct PgStatShared_Common PgStatShared_Common;
typedef struct NameData NameData;

typedef struct PgStat_KindInfo
{
    bool        fixed_amount:1;
    bool        accessed_across_databases:1;
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

typedef struct PgStat_ShmemControl
{
    void *custom_data[PGSTAT_KIND_CUSTOM_MAX - PGSTAT_KIND_CUSTOM_MIN + 1];
} PgStat_ShmemControl;

/* Example data to simulate pgstat_get_kind_info function */
PgStat_KindInfo all_kind_info[PGSTAT_KIND_MAX + 1] = {
    {0},  /* Placeholder for index 0 */
    {true, true, 128, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Kind1"}, 
    {true, true, 256, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Kind2"}, 
    {true, true, 512, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "Kind3"}
};

const PgStat_KindInfo* pgstat_get_kind_info(PgStat_Kind kind)
{
    if (kind >= PGSTAT_KIND_MIN && kind <= PGSTAT_KIND_MAX)
        return &all_kind_info[kind];
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

    /* Assign the init_shmem_cb to all the kinds */
    for (PgStat_Kind kind = PGSTAT_KIND_MIN; kind <= PGSTAT_KIND_MAX; kind++)
    {
        all_kind_info[kind].init_shmem_cb = my_init_shmem_cb;
    }

    /* Initialize fixed-numbered stats */
    for (PgStat_Kind kind = PGSTAT_KIND_MIN; kind <= PGSTAT_KIND_MAX; kind++)
    {
        const PgStat_KindInfo *kind_info = pgstat_get_kind_info(kind);
        char *ptr;

        if (!kind_info || !kind_info->fixed_amount)
            continue;

        if (pgstat_is_kind_builtin(kind))
        {
            ptr = ((char *)ctl) + kind_info->shared_ctl_off;
        }
        else
        {
            int idx = kind - PGSTAT_KIND_CUSTOM_MIN;
            ctl->custom_data[idx] = ShmemAlloc(kind_info->shared_size);
            ptr = ctl->custom_data[idx];
        }

        kind_info->init_shmem_cb(ptr);
    }

    free(ctl);
    return 0;
}
