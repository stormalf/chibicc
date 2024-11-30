#include <stdio.h>
#include <stdint.h>
#include <assert.h>
typedef unsigned long long uint64;
#define MAXIMUM_ALIGNOF 8
#define ALIGNOF_DOUBLE 8
/* The normal alignment of `int', in bytes. */
#define ALIGNOF_INT 4

/* The normal alignment of `long', in bytes. */
#define ALIGNOF_LONG 8

/* The normal alignment of `long long int', in bytes. */
/* #undef ALIGNOF_LONG_LONG_INT */

/* The normal alignment of `PG_INT128_TYPE', in bytes. */
#define ALIGNOF_PG_INT128_TYPE 16

/* The normal alignment of `short', in bytes. */
#define ALIGNOF_SHORT 2


#define TYPEALIGN(ALIGNVAL,LEN)  \
	(((uintptr_t) (LEN) + ((ALIGNVAL) - 1)) & ~((uintptr_t) ((ALIGNVAL) - 1)))

#define SHORTALIGN(LEN)			TYPEALIGN(ALIGNOF_SHORT, (LEN))
#define INTALIGN(LEN)			TYPEALIGN(ALIGNOF_INT, (LEN))
#define LONGALIGN(LEN)			TYPEALIGN(ALIGNOF_LONG, (LEN))
#define DOUBLEALIGN(LEN)		TYPEALIGN(ALIGNOF_DOUBLE, (LEN))
#define MAXALIGN(LEN)			TYPEALIGN(MAXIMUM_ALIGNOF, (LEN))


#define INT64CONST(x)  (x##L)
#define UINT64CONST(x) (x##UL)

#define MEMORYCHUNK_BLOCKOFFSET_MASK 	UINT64CONST(0x3FFFFFFE)

/* define the least significant base-0 bit of each portion of the hdrmask */
#define MEMORYCHUNK_EXTERNAL_BASEBIT	MEMORY_CONTEXT_METHODID_BITS
#define MEMORYCHUNK_VALUE_BASEBIT		(MEMORYCHUNK_EXTERNAL_BASEBIT + 1)
#define MEMORYCHUNK_BLOCKOFFSET_BASEBIT	(MEMORYCHUNK_VALUE_BASEBIT + 29)

#define MEMORY_CONTEXT_METHODID_BITS 4
#define MEMORY_CONTEXT_METHODID_MASK \
    ((((uint64_t) 1) << MEMORY_CONTEXT_METHODID_BITS) - 1)

#define MEMORYCHUNK_MAGIC		(UINT64CONST(0xB1A8DB858EB6EFBA) >> \
								 MEMORYCHUNK_VALUE_BASEBIT << \
								 MEMORYCHUNK_VALUE_BASEBIT)


/* Use macros to simplify assigning the Bogus methods */
#define BOGUS_MCTX(id) \
    [id].free_p = BogusFree, \
    [id].realloc = BogusRealloc, \
    [id].get_chunk_context = BogusGetChunkContext, \
    [id].get_chunk_space = BogusGetChunkSpace




/* Enum for memory context method IDs */
typedef enum MemoryContextMethodID {
    MCTX_0_RESERVED_UNUSEDMEM_ID,      /* 0 */
    MCTX_1_RESERVED_GLIBC_ID,           /* 1 */
    MCTX_2_RESERVED_GLIBC_ID,           /* 2 */
    MCTX_ASET_ID,                       /* 3 */
    MCTX_GENERATION_ID,                 /* 4 */
    MCTX_SLAB_ID,                       /* 5 */
    MCTX_ALIGNED_REDIRECT_ID,           /* 6 */
    MCTX_BUMP_ID,                       /* 7 */
    MCTX_8_UNUSED_ID,                   /* 8 */
    MCTX_9_UNUSED_ID,                   /* 9 */
    MCTX_10_UNUSED_ID,                  /* 10 */
    MCTX_11_UNUSED_ID,                  /* 11 */
    MCTX_12_UNUSED_ID,                  /* 12 */
    MCTX_13_UNUSED_ID,                  /* 13 */
    MCTX_14_UNUSED_ID,                  /* 14 */
    MCTX_15_RESERVED_WIPEDMEM_ID        /* 15 */
} MemoryContextMethodID;

/* Array of strings to represent each enum */
const char *memory_context_names[] = {
    [MCTX_0_RESERVED_UNUSEDMEM_ID] = "Unused Memory",
    [MCTX_1_RESERVED_GLIBC_ID] = "glibc Malloc'd Chunks",
    [MCTX_2_RESERVED_GLIBC_ID] = "glibc Large Chunks",
    [MCTX_ASET_ID] = "Aset Memory Context",
    [MCTX_GENERATION_ID] = "Generation Memory Context",
    [MCTX_SLAB_ID] = "Slab Memory Context",
    [MCTX_ALIGNED_REDIRECT_ID] = "Aligned Redirect Context",
    [MCTX_BUMP_ID] = "Bump Memory Context",
    [MCTX_15_RESERVED_WIPEDMEM_ID] = "Wiped Memory Context"
};



/* Simulated VALGRIND macros */
#define VALGRIND_MAKE_MEM_DEFINED(addr, size)
#define VALGRIND_MAKE_MEM_NOACCESS(addr, size)

/* Forward declaration of the Bogus functions */
static void BogusFree(void *pointer);
static void *BogusRealloc(void *pointer, size_t size, int flags);
static void *BogusGetChunkContext(void *pointer);
static size_t BogusGetChunkSpace(void *pointer);


/* Mock functions for Bogus* methods */
static void BogusFree(void *pointer) {
    printf("BogusFree called with pointer %p\n", pointer);
}

static void *BogusRealloc(void *pointer, size_t size, int flags) {
    printf("BogusRealloc called with pointer %p and size %zu\n", pointer, size);
    return NULL;
}

static void *BogusGetChunkContext(void *pointer) {
    printf("BogusGetChunkContext called with pointer %p\n", pointer);
    return NULL;
}

static size_t BogusGetChunkSpace(void *pointer) {
    printf("BogusGetChunkSpace called with pointer %p\n", pointer);
    return 0;
}


/* Function to get the Memory Context Method ID from a header */
static inline MemoryContextMethodID
GetMemoryChunkMethodID(const void *pointer)
{
    uint64_t header;

    /* Assert that the pointer is aligned */
    assert(pointer == (const void *) MAXALIGN(pointer));

    /* Access the uint64 header (simulated for this example) */
    VALGRIND_MAKE_MEM_DEFINED((char *) pointer - sizeof(uint64_t), sizeof(uint64_t));
    header = *((const uint64_t *) ((const char *) pointer - sizeof(uint64_t)));
    VALGRIND_MAKE_MEM_NOACCESS((char *) pointer - sizeof(uint64_t), sizeof(uint64_t));

    return (MemoryContextMethodID) (header & MEMORY_CONTEXT_METHODID_MASK);
}

/* Test function for GetMemoryChunkMethodID */
int main()
{
    /* Simulate a memory chunk header with a known context ID */
    uint64_t header = MCTX_ASET_ID;
    void *pointer = (void *) &header + sizeof(uint64_t); /* Point to the simulated chunk */
    header = *((const uint64 *) ((const char *) pointer - sizeof(uint64)));

    /* Retrieve and print the context method ID */
    MemoryContextMethodID id = GetMemoryChunkMethodID(pointer);
    printf("Retrieved ID: %d (%s)\n", id, memory_context_names[id]);

    /* Validate if the correct ID was retrieved */
    if (id == MCTX_ASET_ID) {
        printf("GetMemoryChunkMethodID works correctly.\n");
    } else {
        printf("GetMemoryChunkMethodID failed.\n");
    }

    printf("Memory chunk magic: %lu \n", MEMORYCHUNK_MAGIC);
    printf("Max alignment: %lu \n", MAXALIGN(pointer));
    printf("header: %lu \n", header);

    return 0;
}
