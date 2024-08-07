#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef uint64_t Size;
typedef uint8_t MemoryContextMethodID;

typedef struct MemoryChunk
{
    uint64_t hdrmask;
} MemoryChunk;

#define MEMORY_CONTEXT_METHODID_BITS 8
#define MEMORYCHUNK_EXTERNAL_BASEBIT MEMORY_CONTEXT_METHODID_BITS
#define MEMORYCHUNK_VALUE_BASEBIT (MEMORYCHUNK_EXTERNAL_BASEBIT + 1)
#define MEMORYCHUNK_BLOCKOFFSET_BASEBIT (MEMORYCHUNK_VALUE_BASEBIT + 30)

#define UINT64CONST(x) (x##ULL)
#define MEMORYCHUNK_MAGIC (UINT64CONST(0xB1A8DB858EB6EFBA) >> MEMORYCHUNK_VALUE_BASEBIT << MEMORYCHUNK_VALUE_BASEBIT)

#define METHOD_ID 0x01

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
