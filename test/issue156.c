#include <stdint.h>
#include "test.h"
#include <stddef.h>
#include <stdlib.h>

#include <sys/epoll.h>

/* Valid opcodes ( "op" parameter ) to issue to epoll_ctl().  */
#define EPOLL_CTL_ADD 1 /* Add a file descriptor to the interface.  */
#define EPOLL_CTL_DEL 2 /* Remove a file descriptor from the interface.  */
#define EPOLL_CTL_MOD 3 /* Change file descriptor epoll_event structure.  */
#define lengthof(array) (sizeof (array) / sizeof ((array)[0]))

typedef size_t Size;
typedef struct MemoryChunk
{

	/* bitfield for storing details about the chunk */
	unsigned long int 	hdrmask;		/* must be last */
} MemoryChunk;

typedef enum MemoryContextMethodID
{
	MCTX_UNUSED1_ID,			/* 000 occurs in never-used memory */
	MCTX_UNUSED2_ID,			/* glibc malloc'd chunks usually match 001 */
	MCTX_UNUSED3_ID,			/* glibc malloc'd chunks > 128kB match 010 */
	MCTX_ASET_ID,
	MCTX_GENERATION_ID,
	MCTX_SLAB_ID,
	MCTX_ALIGNED_REDIRECT_ID,
	MCTX_UNUSED4_ID				/* 111 occurs in wipe_mem'd memory */
} MemoryContextMethodID;


STATIC_ASSERT(EPOLL_CTL_ADD < 4);

struct uv__io_cqring_offsets {
  uint32_t head;
  uint32_t tail;
  uint32_t ring_mask;
  uint32_t ring_entries;
  uint32_t overflow;
  uint32_t cqes;
  uint64_t reserved0;
  uint64_t reserved1;
};

STATIC_ASSERT(40 == sizeof(struct uv__io_cqring_offsets));

struct uv__io_sqring_offsets {
  uint32_t head;
  uint32_t tail;
  uint32_t ring_mask;
  uint32_t ring_entries;
  uint32_t flags;
  uint32_t dropped;
  uint32_t array;
  uint32_t reserved0;
  uint64_t reserved1;
};

struct uv__io_uring_params {
  uint32_t sq_entries;
  uint32_t cq_entries;
  uint32_t flags;
  uint32_t sq_thread_cpu;
  uint32_t sq_thread_idle;
  uint32_t features;
  uint32_t reserved[4];
  struct uv__io_sqring_offsets sq_off;  /* 40 bytes */
  struct uv__io_cqring_offsets cq_off;  /* 40 bytes */
};

STATIC_ASSERT(40 + 40 + 40 == sizeof(struct uv__io_uring_params));

int main() {
  char s [10] = {0};
  int x = lengthof(s);
  MemoryChunk *chunk = (struct MemoryChunk*)malloc(sizeof(struct MemoryChunk));
	Size value;
  MemoryContextMethodID methodid = 3;
  chunk->hdrmask = (((unsigned long int) 100) << 34) |
		(((unsigned long int) value) << 4) |
		methodid;

    return 0;
}