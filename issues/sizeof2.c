#include <stdio.h>
#include <stddef.h>

// Define some structures with function pointers
typedef struct {
    int a;
    void (*func)(void);
} PgStatShared_Database;

typedef struct {
    int b;
    void (*func)(void);
} PgStatShared_Relation;

// Define a structure that will use sizeof
typedef struct {
    size_t shared_size;
    size_t offset_of_a;
    size_t offset_of_func;
} PgStat_KindInfo;

void example_func(void) {
    printf("Example function called.\n");
}

int main(void) {
    // Initialize PgStat_KindInfo with sizeof PgStatShared_Database
    PgStat_KindInfo kind_info = {
        .shared_size = sizeof(PgStatShared_Database),
        .offset_of_a = offsetof(PgStatShared_Database, a),
        .offset_of_func = offsetof(PgStatShared_Database, func)
    };
    
    // Create instances of PgStatShared_Database and PgStatShared_Relation
    PgStatShared_Database db_instance;
    PgStatShared_Relation rel_instance;
    
    // Print size and offset information
    printf("Size of PgStatShared_Database: %zu\n", sizeof(PgStatShared_Database));
    printf("Size of PgStatShared_Relation: %zu\n", sizeof(PgStatShared_Relation));
    printf("Offset of 'a' in PgStatShared_Database: %zu\n", offsetof(PgStatShared_Database, a));
    printf("Offset of 'func' in PgStatShared_Database: %zu\n", offsetof(PgStatShared_Database, func));
    
    // Print values from PgStat_KindInfo
    printf("PgStat_KindInfo.shared_size: %zu\n", kind_info.shared_size);
    printf("PgStat_KindInfo.offset_of_a: %zu\n", kind_info.offset_of_a);
    printf("PgStat_KindInfo.offset_of_func: %zu\n", kind_info.offset_of_func);
    
    // Assign a function pointer to PgStatShared_Database instance and test
    db_instance.func = example_func;
    if (db_instance.func) {
        db_instance.func();
    } else {
        printf("Function pointer in PgStatShared_Database is NULL.\n");
    }
    
    return 0;
}
