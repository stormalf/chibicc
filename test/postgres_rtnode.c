#include <stdio.h>
#include <stdint.h>
#include "test.h"

// Define the macros as described
#define RT_MAKE_PREFIX(a) CppConcat(a,_)
#define RT_MAKE_NAME(name) RT_MAKE_NAME_(RT_MAKE_PREFIX(RT_PREFIX),name)
#define RT_MAKE_NAME_(a,b) CppConcat(a,b)
#define CppConcat(a, b) a ## b

// Example prefix definition
#define RT_PREFIX node

// Use the macros to define RT_NODE_4, RT_NODE_16, etc.
#define RT_NODE_4 RT_MAKE_NAME(node_4)
#define RT_NODE_16 RT_MAKE_NAME(node_16)
#define RT_NODE_48 RT_MAKE_NAME(node_48)

// Example struct definitions using flexible array members
typedef struct {
    int base;
    uint8_t chunks[16]; // Example fanout size
    uint8_t children[1]; // Flexible array member
} RT_NODE_4;

typedef struct {
    int base;
    uint8_t chunks[32]; // Example fanout size
    uint8_t children[1]; // Flexible array member
} RT_NODE_16;

typedef struct {
    int base;
    uint8_t chunks[48]; // Example fanout size
    uint8_t children[1]; // Flexible array member
} RT_NODE_48;

// Define the size class info structure
typedef struct {
    const char *name;
    int fanout;
    size_t allocsize;
} RT_SIZE_CLASS_ELEM;

// Example RT_FANOUT macros
#define RT_FANOUT_4 16
#define RT_FANOUT_16_LO 32
#define RT_FANOUT_16_HI 48
#define RT_FANOUT_48 64
#define RT_FANOUT_256 256

// Example RT_SIZE_CLASS_INFO array with correct sizes
static const RT_SIZE_CLASS_ELEM RT_SIZE_CLASS_INFO[] = {
    [0] = {
        .name = "node_radix_tree node4",
        .fanout = RT_FANOUT_4,
        .allocsize = sizeof(RT_NODE_4) + RT_FANOUT_4 * sizeof(uint8_t),
    },
    [1] = {
        .name = "node_radix_tree node16_lo",
        .fanout = RT_FANOUT_16_LO,
        .allocsize = sizeof(RT_NODE_16) + RT_FANOUT_16_LO * sizeof(uint8_t),
    },
    [2] = {
        .name = "node_radix_tree node16_hi",
        .fanout = RT_FANOUT_16_HI,
        .allocsize = sizeof(RT_NODE_16) + RT_FANOUT_16_HI * sizeof(uint8_t),
    },
    [3] = {
        .name = "node_radix_tree node48",
        .fanout = RT_FANOUT_48,
        .allocsize = sizeof(RT_NODE_48) + RT_FANOUT_48 * sizeof(uint8_t),
    },
    [4] = {
        .name = "node_radix_tree node256",
        .fanout = RT_FANOUT_256,
        .allocsize = sizeof(RT_NODE_48),
    },
};

// Print function to check values
void print_size_class_info(const RT_SIZE_CLASS_ELEM *info) {
    printf("Name: %s\n", info->name);
    printf("Fanout: %d\n", info->fanout);
    printf("Alloc Size: %zu\n", info->allocsize);
}

int main() {
    // Print size class information for demonstration
    for (int i = 0; i < 5; i++) {
        print_size_class_info(&RT_SIZE_CLASS_INFO[i]);        
    }
    ASSERT(16,RT_FANOUT_4 );
    ASSERT(40, sizeof(RT_NODE_4) + RT_FANOUT_4 * sizeof(uint8_t) );
    ASSERT(32, RT_FANOUT_16_LO );
    ASSERT(72, sizeof(RT_NODE_16) + RT_FANOUT_16_LO * sizeof(uint8_t) );
    ASSERT(48, RT_FANOUT_16_HI);
    ASSERT(88, sizeof(RT_NODE_16) + RT_FANOUT_16_HI * sizeof(uint8_t) );
    ASSERT(64, RT_FANOUT_48);
    ASSERT(120, sizeof(RT_NODE_48) + RT_FANOUT_48 * sizeof(uint8_t) );
    ASSERT(256, RT_FANOUT_256);
    ASSERT(56, sizeof(RT_NODE_48)  );

    return 0;

}
