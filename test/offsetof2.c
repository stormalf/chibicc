#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "test.h"
typedef struct {
    int stats;
} PgStatShared_Example;

typedef struct {
    bool fixed_amount;
    uint32_t shared_size;
    uint32_t shared_data_off;
} PgStat_KindInfo;

typedef struct {
    PgStatShared_Example example;
} PgStat_ShmemControl;

static const PgStat_KindInfo pgstat_kind_example_info = {
    .fixed_amount = true,
    .shared_size = sizeof(PgStatShared_Example),
    .shared_data_off = offsetof(PgStatShared_Example, stats),
};

int main(void) {
    PgStat_ShmemControl ctl;
    printf("Size of PgStatShared_Example: %zu\n", sizeof(PgStatShared_Example));
    printf("Offset of 'stats': %zu\n", offsetof(PgStatShared_Example, stats));

    char *ptr = ((char *)&ctl) + pgstat_kind_example_info.shared_data_off;
    printf("Pointer to 'stats' in PgStat_ShmemControl: %p\n", ptr);
    ASSERT(4, sizeof(PgStatShared_Example) );
    ASSERT(0, offsetof(PgStatShared_Example, stats));
    
    return 0;
}
