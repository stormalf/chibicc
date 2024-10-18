#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/* Simulating atomic operations and spinlocks */
#define BM_LOCKED 0x01

typedef struct pg_atomic_uint32
{
    volatile uint32_t value;
} pg_atomic_uint32;

/* Atomic fetch and OR operation */
static inline uint32_t pg_atomic_fetch_or_u32(volatile pg_atomic_uint32 *ptr, uint32_t or_)
{
    return __sync_fetch_and_or(&ptr->value, or_);
}

/* Atomic fetch and AND operation to clear the lock */
static inline uint32_t pg_atomic_fetch_and_u32(volatile pg_atomic_uint32 *ptr, uint32_t and_)
{
    return __sync_fetch_and_and(&ptr->value, and_);
}

/* Memory barrier implementations */
#if defined(__x86_64__)
#define pg_memory_barrier_impl()        \
    __asm__ __volatile__ ("lock; addl $0,0(%%rsp)" : : : "memory", "cc")
#endif

/* Spin delay implementation */
static inline void pg_spin_delay_impl(void)
{
    __asm__ __volatile__(" rep; nop \n");
}

/* Simulated constants */
#define BM_PIN_COUNT_WAITER 0x02
#define BUFFER_LOCK_UNLOCK 0x00
#define InvalidBuffer 0
#define BufferIsValid(buf) ((buf) != InvalidBuffer)
#define BufferIsLocal(buf) ((buf) < 0)

/* SpinDelayStatus structure */
typedef struct
{
    int spins;
    int delays;
    int cur_delay;
    const char *file;
    int line;
    const char *func;
} SpinDelayStatus;

/* BufferTag and BufferDesc structures */
typedef struct BufferDesc
{
    int buf_id;
    pg_atomic_uint32 state;
    int content_lock;
} BufferDesc;

typedef int Buffer;

/* Log an error (simulated) */
void elog(const char *level, const char *fmt, int val)
{
    fprintf(stderr, "%s: %s %d\n", level, fmt, val);
    exit(EXIT_FAILURE);
}

/* Simulate unpinning buffer */
void UnpinBuffer(BufferDesc *desc)
{
    /* Simulated unpinning operation */
    printf("UnpinBuffer: buffer %d unpinned\n", desc->buf_id);
}

/* Get buffer descriptor */
BufferDesc* GetBufferDescriptor(int buffer_id)
{
    static BufferDesc descs[10];
    if (buffer_id < 0 || buffer_id >= 10)
        return NULL;

    descs[buffer_id].buf_id = buffer_id;
    return &descs[buffer_id];
}

/* Simulate unpinning local buffer */
void UnpinLocalBuffer(Buffer buffer)
{
    printf("UnpinLocalBuffer: local buffer %d unpinned\n", buffer);
}

/* Lock buffer header - set BM_LOCKED in buffer state */
uint32_t LockBufHdr(BufferDesc *desc)
{
    SpinDelayStatus delayStatus;
    uint32_t old_buf_state;

    /* Memory barrier before locking */
    pg_memory_barrier_impl();

    /* Simulate locking mechanism */
    old_buf_state = pg_atomic_fetch_or_u32(&desc->state, BM_LOCKED);
    printf("LockBufHdr: old_buf_state = %d, new state = %d\n", old_buf_state, desc->state.value);

    /* If it wasn't set before, we're OK */
    if (!(old_buf_state & BM_LOCKED))
        return old_buf_state | BM_LOCKED;

    return old_buf_state;
}

/* Unlock buffer header - clear BM_LOCKED flag */
void UnlockBufHdr(BufferDesc *desc)
{
    /* Clear BM_LOCKED flag */
    pg_atomic_fetch_and_u32(&desc->state, ~BM_LOCKED);
    printf("UnlockBufHdr: buffer %d unlocked\n", desc->buf_id);

    /* Memory barrier after unlocking */
    pg_memory_barrier_impl();
}

/*
 * ReleaseBuffer - release the pin on a buffer
 */
void ReleaseBuffer(Buffer buffer)
{
    if (!BufferIsValid(buffer))
        elog("ERROR", "bad buffer ID:", buffer);

    if (BufferIsLocal(buffer))
        UnpinLocalBuffer(buffer);
    else
        UnpinBuffer(GetBufferDescriptor(buffer - 1));
}

/*
 * UnlockReleaseBuffer - release the content lock and pin on a buffer
 */
void UnlockReleaseBuffer(Buffer buffer)
{
    /* Unlock the buffer */
    BufferDesc *desc = GetBufferDescriptor(buffer - 1);
    if (desc != NULL)
    {
        UnlockBufHdr(desc);
    }
    
    /* Release the buffer */
    ReleaseBuffer(buffer);
}

/* Main function to test lock/release with spin delay and memory barriers */
int main(void)
{
    /* Initialize a buffer descriptor */
    BufferDesc buf;
    buf.state.value = 0;  // Initialize state
    buf.buf_id = 1;       // Initialize buffer ID

    /* Perform 20 lock/release operations */
    for (int i = 0; i < 20; i++)
    {
        printf("---- Iteration %d ----\n", i + 1);

        /* Lock the buffer header */
        uint32_t result = LockBufHdr(&buf);
        printf("Lock acquired, result state: 0x%x\n", result);

        /* Spin delay for a short duration to simulate contention */
        pg_spin_delay_impl();

        /* Unlock and release the buffer */
        UnlockReleaseBuffer(buf.buf_id + 1);

        printf("--------------------\n");
    }

    return 0;
}
