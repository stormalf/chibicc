#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/* Simulating atomic operations and spinlocks */
#define BM_LOCKED 0x01

typedef struct pg_atomic_uint32
{
	volatile uint32_t value;
} pg_atomic_uint32;

/* Atomic fetch and OR operation (using __sync_fetch_and_or) */
static inline uint32_t
pg_atomic_fetch_or_u32_impl(volatile pg_atomic_uint32 *ptr, uint32_t or_)
{
	/* Use GCC built-in function for atomic fetch-and-or */
	return __sync_fetch_and_or(&ptr->value, or_);
}

static inline uint32_t
pg_atomic_fetch_or_u32(volatile pg_atomic_uint32 *ptr, uint32_t or_)
{
	/* Call the implementation */
	return pg_atomic_fetch_or_u32_impl(ptr, or_);
}

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

/* Simulated constants and delay parameters */
#define spins_per_delay 10
#define NUM_DELAYS 1000
#define MIN_DELAY_USEC 100
#define MAX_DELAY_USEC 1000000

/* Simulated wait event reporting functions */
void pgstat_report_wait_start(const char *event) {}
void pgstat_report_wait_end() {}

/* Simulated usleep */
void pg_usleep(int usec)
{
	usleep(usec);
}

/* Simulated random generator */
double pg_prng_double()
{
	return (double)rand() / RAND_MAX;
}

/* Spinlock stuck handler */
void s_lock_stuck(const char *file, int line, const char *func)
{
	fprintf(stderr, "PANIC: stuck spinlock detected at %s, line %d in function %s\n", file, line, func);
	exit(1);
}

/* Perform spin delay (provided) */
void perform_spin_delay(SpinDelayStatus *status)
{
	/* CPU-specific delay each time through the loop */
	usleep(1);  // Simulate minimal CPU delay for the example

	/* Block the process every spins_per_delay tries */
	if (++(status->spins) >= spins_per_delay)
	{
		if (++(status->delays) > NUM_DELAYS)
			s_lock_stuck(status->file, status->line, status->func);

		if (status->cur_delay == 0) /* first time to delay? */
			status->cur_delay = MIN_DELAY_USEC;

		/* Report wait event and sleep */
		pgstat_report_wait_start("WAIT_EVENT_SPIN_DELAY");
		pg_usleep(status->cur_delay);
		pgstat_report_wait_end();

		/* Increase delay exponentially */
		status->cur_delay += (int) (status->cur_delay * pg_prng_double() + 0.5);

		/* Wrap back to minimum delay when max is exceeded */
		if (status->cur_delay > MAX_DELAY_USEC)
			status->cur_delay = MIN_DELAY_USEC;

		status->spins = 0;
	}
}

/* BufferTag and BufferDesc structures (same as before) */
typedef unsigned int Oid;
typedef Oid RelFileNumber;
typedef uint32_t BlockNumber;

typedef enum ForkNumber
{
	InvalidForkNumber = -1,
	MAIN_FORKNUM = 0,
	FSM_FORKNUM,
	VISIBILITYMAP_FORKNUM,
	INIT_FORKNUM
} ForkNumber;

typedef struct buftag
{
	Oid spcOid;
	Oid dbOid;
	RelFileNumber relNumber;
	ForkNumber forkNum;
	BlockNumber blockNum;
} BufferTag;

typedef struct BufferDesc
{
	BufferTag tag;
	int buf_id;
	pg_atomic_uint32 state;
	int wait_backend_pgprocno;
	int freeNext;
	int content_lock;
} BufferDesc;

/* Spin delay initialization (same as before) */
static inline void init_spin_delay(SpinDelayStatus *status, const char *file, int line, const char *func)
{
	status->spins = 0;
	status->delays = 0;
	status->cur_delay = 0;
	status->file = file;
	status->line = line;
	status->func = func;
}

#define init_local_spin_delay(status) init_spin_delay(status, __FILE__, __LINE__, __func__)

/* Function that uses the spinlock */
uint32_t LockBufHdr(BufferDesc *desc)
{
	SpinDelayStatus delayStatus;
	uint32_t old_buf_state;

	init_local_spin_delay(&delayStatus);

	while (true)
	{
		/* Set BM_LOCKED flag using atomic fetch and OR */
		old_buf_state = pg_atomic_fetch_or_u32(&desc->state, BM_LOCKED);
        printf("=====old_buf_state %d %d %d\n", old_buf_state, desc->state, BM_LOCKED);
		/* If it wasn't set before, we're OK */
		if (!(old_buf_state & BM_LOCKED))
			break;

		/* Perform spin delay to avoid getting stuck */
		perform_spin_delay(&delayStatus);
	}

	/* Return the new state */
	return old_buf_state | BM_LOCKED;
}

/* Main function to simulate buffer locking */
int main(void)
{
	/* Initialize a buffer descriptor */
	BufferDesc buf;
	buf.state.value = 0;  // Initialize state

	/* Attempt to acquire the spinlock on the buffer */
	uint32_t result = LockBufHdr(&buf);

	/* Print result to verify if the spinlock was successfully acquired */
	printf("Lock acquired, result state: 0x%x\n", result);

	return 0;
}