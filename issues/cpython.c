#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
/* ----------------- Mock CPython structs ----------------- */

typedef struct _obmalloc_state OMState;
typedef struct _obmalloc_pools poolp;
typedef struct _obmalloc_mgmt _mgmt;
typedef struct PyDictObject PyDictObject;

/* For simplicity, we use dummy pointers/values */
struct _obmalloc_pools {
    void* used[32];
};

struct _obmalloc_mgmt {
    void* arenas;
    void* unused_arena_objects;
    void* usable_arenas;
    void* nfp2lasta[16];
    size_t narenas_currently_allocated;
    size_t ntimes_arena_allocated;
    size_t narenas_highwater;
    size_t raw_allocated_blocks;
};

struct _obmalloc_state {
    struct _obmalloc_pools pools;
    struct _obmalloc_mgmt mgmt;
};

struct PyDictObject {
    void* ma_keys;
    void* ma_values;
};

/* ----------------- Global state ----------------- */
static struct _obmalloc_state obmalloc_state_main;
static bool obmalloc_state_initialized = true;

/* ----------------- Inline helpers ----------------- */
static inline OMState* get_state(void) {
    return &obmalloc_state_main;
}

/* ----------------- Mock PyObject_Malloc ----------------- */
void* PyObject_Malloc(size_t size) {
    OMState* state = get_state();
    void* ptr = malloc(size);
    if (ptr) state->mgmt.raw_allocated_blocks++;
    return ptr;
}

/* ----------------- Minimal PyDict_New ----------------- */
PyDictObject* PyDict_New(void) {
    PyDictObject* d = PyObject_Malloc(sizeof(PyDictObject));
    d->ma_keys = PyObject_Malloc(16);
    d->ma_values = PyObject_Malloc(16);
    return d;
}

/* ----------------- Minimal _PyUnicode_InitGlobalObjects ----------------- */
void _PyUnicode_InitGlobalObjects(void) {
    PyDictObject* interned = PyDict_New();
    /* Write test values to verify memory */
    *(uintptr_t*)interned->ma_keys = 0x12345678;
    *(uintptr_t*)interned->ma_values = 0x87654321;

    printf("Allocated PyDictObject: %p\n", interned);
    printf("ma_keys: %p, ma_values: %p\n",
           interned->ma_keys, interned->ma_values);
    printf("ma_keys value: 0x%lx, ma_values value: 0x%lx\n",
           *(uintptr_t*)interned->ma_keys, *(uintptr_t*)interned->ma_values);
}

/* ----------------- Main ----------------- */
int main(void) {
    OMState* state = get_state();
    printf("Address of state: %p\n", state);
    printf("Address of pools.used: %p\n", state->pools.used);
    printf("Address of mgmt: %p\n", &state->mgmt);
    printf("Address of mgmt.nfp2lasta: %p\n", state->mgmt.nfp2lasta);
    printf("Address of mgmt.raw_allocated_blocks: %p\n", &state->mgmt.raw_allocated_blocks);

    _PyUnicode_InitGlobalObjects();
    return 0;
}
