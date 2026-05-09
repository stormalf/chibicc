#include "test.h"
#include <stdint.h>

typedef uintptr_t Datum;

typedef struct TableAmRoutine {
    int type;
} TableAmRoutine;

static const TableAmRoutine heapam_methods = {
    .type = 400,
};

// Simulate the handler function returning a pointer as Datum
Datum heap_tableam_handler(void) {
    return (Datum)&heapam_methods;
}

// Simulate OidFunctionCall0 calling the handler
Datum OidFunctionCall0(int oid) {
    if (oid == 3)
        return heap_tableam_handler();
    return 0;
}

int main() {
    // Simulate GetTableAmRoutine
    Datum datum = OidFunctionCall0(3);
    const TableAmRoutine *routine = (const TableAmRoutine *)datum;
    
    if (routine->type != 400) {
        printf("FAIL: routine->type = %d, expected 400\n", routine->type);
        exit(1);
    }
    printf("OK\n");
    return 0;
}