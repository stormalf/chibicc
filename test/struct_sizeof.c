#include "test.h"
#include <stddef.h> // For offsetof
#include <stdbool.h> // For bool type

typedef struct PgStatShared_Archiver { int stats; } PgStatShared_Archiver;

// Define a struct with boolean bitfields and other fields
typedef struct {
    bool fixed_amount : 1;              // Bitfield for fixed amount
    bool accessed_across_databases : 1; // Bitfield for access across databases
    int id;                              // Integer ID
    char name[20];                       // Name field
    size_t shared_size;                  // This will be initialized using sizeof
} Item;

// Define a struct to hold an array of items
typedef struct {
    Item items[5]; // Array of 5 Items
} ItemCollection;

int main(void) {
    ItemCollection collection = {
        .items[0] = {0},
        .items[1] = { .shared_size = sizeof(PgStatShared_Archiver), .fixed_amount = false, .accessed_across_databases = true, .id = 2, .name = "Item2" }, // shared_size will be uninitialized
        .items[2] = { .id = 3, .name = "Item3" }, // Only id and name initialized, shared_size uninitialized
    };

    // Print the details of the collection
    for (int i = 0; i < 3; i++) {
        if (!collection.items[i].name)
            continue;
        printf("Item %d:\n", collection.items[i].id);
        printf("  Name: %s\n", collection.items[i].name);
        printf("  Fixed Amount: %d\n", collection.items[i].fixed_amount);
        printf("  Accessed Across Databases: %d\n", collection.items[i].accessed_across_databases);
        printf("  Shared Size: %zu\n", collection.items[i].shared_size); // May be uninitialized for some items
    }

    return 0;
}
