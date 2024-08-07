#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stddef.h>

// Define the required constants and types
typedef uint64_t Size;
typedef uint8_t MemoryContextMethodID;

typedef struct MemoryChunk
{
    uint64_t hdrmask;
} MemoryChunk;

typedef struct AllocBlockData
{
    struct AllocBlockData *prev;
    struct AllocBlockData *next;
    char *freeptr;
    char *endptr;
    void *aset;
} AllocBlockData;

typedef AllocBlockData *AllocBlock;

typedef struct AllocSetData
{
    struct AllocBlockData *blocks;
    Size allocChunkLimit;
    Size initBlockSize;
    Size maxBlockSize;
    Size nextBlockSize;
    Size mem_allocated;
    MemoryChunk **freelist;
} AllocSetData;

typedef AllocSetData *AllocSet;
typedef AllocSet MemoryContext;

#define MEMORY_CONTEXT_METHODID_BITS 8
#define MEMORYCHUNK_EXTERNAL_BASEBIT MEMORY_CONTEXT_METHODID_BITS
#define MEMORYCHUNK_VALUE_BASEBIT (MEMORYCHUNK_EXTERNAL_BASEBIT + 1)
#define MEMORYCHUNK_BLOCKOFFSET_BASEBIT (MEMORYCHUNK_VALUE_BASEBIT + 30)

#define UINT64CONST(x) (x##ULL)
#define MEMORYCHUNK_MAGIC (UINT64CONST(0xB1A8DB858EB6EFBA) >> MEMORYCHUNK_VALUE_BASEBIT << MEMORYCHUNK_VALUE_BASEBIT)

#define METHOD_ID 0x01
#define ALLOC_BLOCKHDRSZ offsetof(AllocBlockData, freeptr)
#define ALLOC_CHUNKHDRSZ sizeof(MemoryChunk)
#define ALLOC_MINBITS 3
#define ALLOCSET_NUM_FREELISTS 11

#define MAXALIGN(x) (((x) + 7) & ~7)

#define MCTX_ASET_ID 1

// Define dummy implementations of undefined functions/macros
#define VALGRIND_MAKE_MEM_NOACCESS(addr, size)
#define VALGRIND_MAKE_MEM_DEFINED(addr, size)
#define VALGRIND_MAKE_MEM_UNDEFINED(addr, size)

static inline void *MemoryChunkGetPointer(MemoryChunk *chunk) {
    return (void *)(chunk + 1);
}

static inline int AllocSetFreeIndex(Size size) {
    int idx = 0;
    while ((1U << idx) < size) {
        idx++;
    }
    return idx;
}

static inline Size GetChunkSizeFromFreeListIdx(int idx) {
    return (1U << idx);
}

typedef struct AllocFreeListLink
{
    struct MemoryChunk *next;
} AllocFreeListLink;

static inline AllocFreeListLink *GetFreeListLink(MemoryChunk *chunk) {
    return (AllocFreeListLink *) chunk;
}

static inline void
MemoryChunkSetHdrMask(MemoryChunk *chunk, void *block,
                      Size value, MemoryContextMethodID methodid)
{
    Size blockoffset = (char *)chunk - (char *)block;
    chunk->hdrmask = (((uint64_t)blockoffset) << 34) |
                     (((uint64_t)value) << 4) |
                     methodid;
}

static inline void
MemoryChunkSetHdrMaskExternal(MemoryChunk *chunk,
                              MemoryContextMethodID methodid)
{
    chunk->hdrmask = MEMORYCHUNK_MAGIC |
                     (((uint64_t)1) << MEMORYCHUNK_EXTERNAL_BASEBIT) |
                     methodid;
}

// Define AllocSetAlloc function
void *AllocSetAlloc(MemoryContext context, Size size)
{
    AllocSet set = (AllocSet)context;
    AllocBlock block;
    MemoryChunk *chunk;
    int fidx;
    Size chunk_size;
    Size blksize;

    if (size > set->allocChunkLimit)
    {
        chunk_size = MAXALIGN(size);
        blksize = chunk_size + ALLOC_BLOCKHDRSZ + ALLOC_CHUNKHDRSZ;
        block = (AllocBlock)malloc(blksize);
        if (block == NULL)
            return NULL;

        context->mem_allocated += blksize;

        block->aset = set;
        block->freeptr = block->endptr = ((char *)block) + blksize;
        chunk = (MemoryChunk *)(((char *)block) + ALLOC_BLOCKHDRSZ);

        MemoryChunkSetHdrMaskExternal(chunk, MCTX_ASET_ID);

        if (set->blocks != NULL)
        {
            block->prev = set->blocks;
            block->next = set->blocks->next;
            if (block->next)
                block->next->prev = block;
            set->blocks->next = block;
        }
        else
        {
            block->prev = NULL;
            block->next = NULL;
            set->blocks = block;
        }

        VALGRIND_MAKE_MEM_NOACCESS((char *)MemoryChunkGetPointer(chunk) + size, chunk_size - size);
        VALGRIND_MAKE_MEM_NOACCESS(chunk, ALLOC_CHUNKHDRSZ);

        return MemoryChunkGetPointer(chunk);
    }

    fidx = AllocSetFreeIndex(size);
    chunk = set->freelist[fidx];
    if (chunk != NULL)
    {
        AllocFreeListLink *link = GetFreeListLink(chunk);

        VALGRIND_MAKE_MEM_DEFINED(chunk, ALLOC_CHUNKHDRSZ);
        VALGRIND_MAKE_MEM_DEFINED(link, sizeof(AllocFreeListLink));
        set->freelist[fidx] = link->next;
        VALGRIND_MAKE_MEM_NOACCESS(link, sizeof(AllocFreeListLink));

        VALGRIND_MAKE_MEM_NOACCESS((char *)MemoryChunkGetPointer(chunk) + size, GetChunkSizeFromFreeListIdx(fidx) - size);
        VALGRIND_MAKE_MEM_NOACCESS(chunk, ALLOC_CHUNKHDRSZ);

        return MemoryChunkGetPointer(chunk);
    }

    chunk_size = GetChunkSizeFromFreeListIdx(fidx);

    if ((block = set->blocks) != NULL)
    {
        Size availspace = block->endptr - block->freeptr;

        if (availspace < (chunk_size + ALLOC_CHUNKHDRSZ))
        {
            while (availspace >= ((1 << ALLOC_MINBITS) + ALLOC_CHUNKHDRSZ))
            {
                AllocFreeListLink *link;
                Size availchunk = availspace - ALLOC_CHUNKHDRSZ;
                int a_fidx = AllocSetFreeIndex(availchunk);

                if (availchunk != GetChunkSizeFromFreeListIdx(a_fidx))
                {
                    a_fidx--;
                    availchunk = GetChunkSizeFromFreeListIdx(a_fidx);
                }

                chunk = (MemoryChunk *)(block->freeptr);
                VALGRIND_MAKE_MEM_UNDEFINED(chunk, ALLOC_CHUNKHDRSZ);
                block->freeptr += (availchunk + ALLOC_CHUNKHDRSZ);
                availspace -= (availchunk + ALLOC_CHUNKHDRSZ);

                MemoryChunkSetHdrMask(chunk, block, a_fidx, MCTX_ASET_ID);
                link = GetFreeListLink(chunk);

                VALGRIND_MAKE_MEM_DEFINED(link, sizeof(AllocFreeListLink));
                link->next = set->freelist[a_fidx];
                VALGRIND_MAKE_MEM_NOACCESS(link, sizeof(AllocFreeListLink));

                set->freelist[a_fidx] = chunk;
            }
            block = NULL;
        }
    }

    if (block == NULL)
    {
        Size required_size;
        blksize = set->nextBlockSize;
        set->nextBlockSize <<= 1;
        if (set->nextBlockSize > set->maxBlockSize)
            set->nextBlockSize = set->maxBlockSize;

        required_size = chunk_size + ALLOC_BLOCKHDRSZ + ALLOC_CHUNKHDRSZ;
        while (blksize < required_size)
            blksize <<= 1;

        block = (AllocBlock)malloc(blksize);
        while (block == NULL && blksize > 1024 * 1024)
        {
            blksize >>= 1;
            if (blksize < required_size)
                break;
            block = (AllocBlock)malloc(blksize);
        }

        if (block == NULL)
            return NULL;

        context->mem_allocated += blksize;

        block->aset = set;
        block->freeptr = ((char *)block) + ALLOC_BLOCKHDRSZ;
        block->endptr = ((char *)block) + blksize;

        VALGRIND_MAKE_MEM_NOACCESS(block->freeptr, blksize - ALLOC_BLOCKHDRSZ);
        block->prev = NULL;
        block->next = set->blocks;
        if (block->next)
            block->next->prev = block;
        set->blocks = block;
    }

    chunk = (MemoryChunk *)(block->freeptr);
    VALGRIND_MAKE_MEM_UNDEFINED(chunk, ALLOC_CHUNKHDRSZ);
    block->freeptr += (chunk_size + ALLOC_CHUNKHDRSZ);

    MemoryChunkSetHdrMask(chunk, block, fidx, MCTX_ASET_ID);

    VALGRIND_MAKE_MEM_NOACCESS((char *)MemoryChunkGetPointer(chunk) + size, chunk_size - size);
    VALGRIND_MAKE_MEM_NOACCESS(chunk, ALLOC_CHUNKHDRSZ);

    return MemoryChunkGetPointer(chunk);
}

// Main function to test AllocSetAlloc
int main() {
    void *block = malloc(1024);
    MemoryChunk *chunk = (MemoryChunk *)((char *)block + 64); // Example offset

    Size value = 0x12345;
    MemoryContextMethodID methodid = METHOD_ID;

    MemoryChunkSetHdrMask(chunk, block, value, methodid);
    printf("Internal hdrmask: 0x%016lx\n", chunk->hdrmask);

    // Check that hdrmask is not null
    assert(chunk->hdrmask != 0);

    MemoryChunkSetHdrMaskExternal(chunk, methodid);
    printf("External hdrmask: 0x%016lx\n", chunk->hdrmask);

    // Check that hdrmask is not null
    assert(chunk->hdrmask != 0);

    free(block);
    return 0;
}
