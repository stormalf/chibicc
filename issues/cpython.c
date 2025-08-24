#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#define NB_SMALL_SIZE_CLASSES 32
#define OBMALLOC_USED_POOLS_SIZE (2 * ((NB_SMALL_SIZE_CLASSES + 7) / 8) * 8)
#define MAX_POOLS_IN_ARENA 8
#define INITIAL_ARENA_OBJECTS 16

typedef void* poolp;

struct arena_object { int dummy; };

struct _obmalloc_pools {
    poolp used[OBMALLOC_USED_POOLS_SIZE];
};

struct _obmalloc_mgmt {
    struct arena_object* arenas;
    uint maxarenas;
    struct arena_object* unused_arena_objects;
    struct arena_object* usable_arenas;
    struct arena_object* nfp2lasta[MAX_POOLS_IN_ARENA + 1];
    size_t narenas_currently_allocated;
    size_t ntimes_arena_allocated;
    size_t narenas_highwater;
    size_t raw_allocated_blocks;
};

typedef struct _obmalloc_state {
    struct _obmalloc_pools pools;
    struct _obmalloc_mgmt mgmt;
} OMState;

// Simulate the interpreter state
static OMState obmalloc_state_main;
static OMState* get_state(void) {
    return &obmalloc_state_main;
}

// Simulated allocation
void* _PyObject_Malloc(size_t nbytes) {
    OMState *state = get_state();
    void* ptr = malloc(nbytes);
    if (ptr) state->mgmt.raw_allocated_blocks++;
    return ptr;
}

int main(void) {
    OMState *state = get_state();

    printf("State address: %p\n", state);
    printf("Pools address: %p\n", &state->pools);
    printf("Mgmt address: %p\n", &state->mgmt);

    // Initialize pools
    for (int i = 0; i < OBMALLOC_USED_POOLS_SIZE; i++)
        state->pools.used[i] = (poolp)(uintptr_t)(0x1000 + i);

    // Allocate multiple objects
    void* objs[10];
    for (int i = 0; i < 10; i++) {
        objs[i] = _PyObject_Malloc(64);
        printf("Allocated object[%d]: %p\n", i, objs[i]);
    }

    printf("Raw allocated blocks: %zu\n", state->mgmt.raw_allocated_blocks);

    return 0;
}
