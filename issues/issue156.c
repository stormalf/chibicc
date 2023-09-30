#include <stdint.h>
#include <stdio.h>

#include <sys/epoll.h>

/* Valid opcodes ( "op" parameter ) to issue to epoll_ctl().  */
#define EPOLL_CTL_ADD 1 /* Add a file descriptor to the interface.  */
#define EPOLL_CTL_DEL 2 /* Remove a file descriptor from the interface.  */
#define EPOLL_CTL_MOD 3 /* Change file descriptor epoll_event structure.  */
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

    return 0;
}