#include "test.h"

typedef enum NodeTag {
    T_TableAmRoutine = 400
} NodeTag;

typedef struct Node {
    NodeTag type;
} Node;

typedef struct TableAmRoutine {
    NodeTag type;
} TableAmRoutine;

#define nodeTag(nodeptr) (((const Node*)(nodeptr))->type)
#define IsA(nodeptr, _type_) (nodeTag(nodeptr) == T_##_type_)

static const TableAmRoutine heapam_methods = {
    .type = T_TableAmRoutine,
};

const TableAmRoutine *GetTableAmRoutine(void) {
    return &heapam_methods;
}

int main() {
    const TableAmRoutine *routine = GetTableAmRoutine();
    
    if (!IsA(routine, TableAmRoutine)) {
        printf("FATAL: table access method handler 3 did not return a TableAmRoutine struct\n");
        exit(1);
    }
    printf("OK\n");
    return 0;
}