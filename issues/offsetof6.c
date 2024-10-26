#include <stdio.h>
#include <stddef.h>

// Define the Udata structure
typedef struct {
    struct {
        int type;   // Type of the userdata
        void *next; // Link to next garbage collected object
    } gc;           // GCObject header
    union {
        struct {
            // Placeholder for additional user values
            void *uv[4]; // Allow 4 values for userdata
        };
        char bindata[8];  // Alternative space for userdata
    };
} Udata;

int main() {
    // Calculate the offset of the uv member within the Udata structure
    size_t offset_uv = offsetof(Udata, uv);
    
    // Print the calculated offset
    printf("Offset of uv in Udata: %zu\n", offset_uv);
    
    // Additional check for the size of Udata
    printf("Size of Udata: %zu\n", sizeof(Udata));

    return 0;
}
