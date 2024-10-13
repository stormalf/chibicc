#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "test.h"

typedef int64_t int64;
typedef uint64_t uint64;
typedef int32_t int32;
typedef uint32_t uint32;
// Define macros for delays and logging
#define MIN_DELAY_USEC 1000
#define MAX_DELAY_USEC 1000000
#define NUM_DELAYS 10
#define SPINS_PER_DELAY 1000

#define PANIC 1
#define S_LOCK_TEST


#if defined(__GNUC__) || defined(__INTEL_COMPILER)

#define PG_HAVE_ATOMIC_FLAG_SUPPORT
typedef struct pg_atomic_flag
{
	volatile char value;
} pg_atomic_flag;

#define PG_HAVE_ATOMIC_U32_SUPPORT
typedef struct pg_atomic_uint32
{
	volatile uint32 value;
} pg_atomic_uint32;


#endif


#ifdef __x86_64__
#define PG_HAVE_ATOMIC_U64_SUPPORT
typedef struct pg_atomic_uint64
{
	/* alignment guaranteed due to being on a 64bit platform */
	volatile uint64 value;
} pg_atomic_uint64;
#endif	/* __x86_64__ */




#ifdef __x86_64__		/* AMD Opteron, Intel EM64T */
#define HAS_TEST_AND_SET

typedef unsigned char slock_t;

#define TAS(lock) tas(lock)

/*
 * On Intel EM64T, it's a win to use a non-locking test before the xchg proper,
 * but only when spinning.
 *
 * See also Implementing Scalable Atomic Locks for Multi-Core Intel(tm) EM64T
 * and IA32, by Michael Chynoweth and Mary R. Lee. As of this writing, it is
 * available at:
 * http://software.intel.com/en-us/articles/implementing-scalable-atomic-locks-for-multi-core-intel-em64t-and-ia32-architectures
 */
#define TAS_SPIN(lock)    (*(lock) ? 1 : TAS(lock))

static __inline__ int
tas(volatile slock_t *lock)
{
	slock_t		_res = 1;

	__asm__ __volatile__(
		"	lock			\n"
		"	xchgb	%0,%1	\n"
:		"+q"(_res), "+m"(*lock)
:		/* no inputs */
:		"memory", "cc");

	return (int) _res;
}

#define SPIN_DELAY() spin_delay()

static __inline__ void
spin_delay(void)
{
	/*
	 * Adding a PAUSE in the spin delay loop is demonstrably a no-op on
	 * Opteron, but it may be of some use on EM64T, so we keep it.
	 */
	__asm__ __volatile__(
		" rep; nop			\n");
}

#endif	 /* __x86_64__ */


#if defined(__GNUC__) || defined(__INTEL_COMPILER)

#define PG_HAVE_ATOMIC_TEST_SET_FLAG
static inline bool
pg_atomic_test_set_flag_impl(volatile pg_atomic_flag *ptr)
{
	char		_res = 1;

	__asm__ __volatile__(
		"	lock			\n"
		"	xchgb	%0,%1	\n"
:		"+q"(_res), "+m"(ptr->value)
:
:		"memory");
	return _res == 0;
}

#define PG_HAVE_ATOMIC_CLEAR_FLAG
static inline void
pg_atomic_clear_flag_impl(volatile pg_atomic_flag *ptr)
{
	/*
	 * On a TSO architecture like x86 it's sufficient to use a compiler
	 * barrier to achieve release semantics.
	 */
	__asm__ __volatile__("" ::: "memory");
	ptr->value = 0;
}

#define PG_HAVE_ATOMIC_COMPARE_EXCHANGE_U32
static inline bool
pg_atomic_compare_exchange_u32_impl(volatile pg_atomic_uint32 *ptr,
									uint32 *expected, uint32 newval)
{
	char	ret;

	/*
	 * Perform cmpxchg and use the zero flag which it implicitly sets when
	 * equal to measure the success.
	 */
	__asm__ __volatile__(
		"	lock				\n"
		"	cmpxchgl	%4,%5	\n"
		"   setz		%2		\n"
:		"=a" (*expected), "=m"(ptr->value), "=q" (ret)
:		"a" (*expected), "r" (newval), "m"(ptr->value)
:		"memory", "cc");
	return (bool) ret;
}

#define PG_HAVE_ATOMIC_FETCH_ADD_U32
static inline uint32
pg_atomic_fetch_add_u32_impl(volatile pg_atomic_uint32 *ptr, int32 add_)
{
	uint32 res;
	__asm__ __volatile__(
		"	lock				\n"
		"	xaddl	%0,%1		\n"
:		"=q"(res), "=m"(ptr->value)
:		"0" (add_), "m"(ptr->value)
:		"memory", "cc");
	return res;
}

#ifdef __x86_64__

#define PG_HAVE_ATOMIC_COMPARE_EXCHANGE_U64
static inline bool
pg_atomic_compare_exchange_u64_impl(volatile pg_atomic_uint64 *ptr,
									uint64 *expected, uint64 newval)
{
	char	ret;

	//AssertPointerAlignment(expected, 8);

	/*
	 * Perform cmpxchg and use the zero flag which it implicitly sets when
	 * equal to measure the success.
	 */
	__asm__ __volatile__(
		"	lock				\n"
		"	cmpxchgq	%4,%5	\n"
		"   setz		%2		\n"
:		"=a" (*expected), "=m"(ptr->value), "=q" (ret)
:		"a" (*expected), "r" (newval), "m"(ptr->value)
:		"memory", "cc");
	return (bool) ret;
}

#define PG_HAVE_ATOMIC_FETCH_ADD_U64
static inline uint64
pg_atomic_fetch_add_u64_impl(volatile pg_atomic_uint64 *ptr, int64 add_)
{
	uint64 res;
	__asm__ __volatile__(
		"	lock				\n"
		"	xaddq	%0,%1		\n"
:		"=q"(res), "=m"(ptr->value)
:		"0" (add_), "m"(ptr->value)
:		"memory", "cc");
	return res;
}

#endif /* __x86_64__ */

#endif /* defined(__GNUC__) || defined(__INTEL_COMPILER) */



// Struct to hold spin delay status
typedef struct {
    int spins;
    int delays;
    int cur_delay;
    const char *file;
    int line;
    const char *func;
} SpinDelayStatus;

void
s_unlock(volatile slock_t *lock)
{
	*lock = 0;
}

// Dummy functions for simulation
void pg_usleep(int usec) {
    usleep(usec);
}

void pgstat_report_wait_start(int event) {
    printf("Wait event started: %d\n", event);
}

void pgstat_report_wait_end() {
    printf("Wait event ended\n");
}

void elog(int level, const char *fmt, ...) {
    // Simplified logging function
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "LOG [%d]: ", level);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

double pg_prng_double(void *state) {
    // Simple random number generator for delay increase
    return (double)rand() / RAND_MAX;
}

static void s_lock_stuck(const char *file, int line, const char *func) {
    if (!func)
        func = "(unknown)";
#if defined(S_LOCK_TEST)
    fprintf(stderr, "\nStuck spinlock detected at %s, %s:%d.\n", func, file, line);
    exit(1);
#else
    elog(PANIC, "stuck spinlock detected at %s, %s:%d", func, file, line);
#endif
}

// Initialize spin delay status
static void init_spin_delay(SpinDelayStatus *status, const char *file, int line, const char *func) {
    status->spins = 0;
    status->delays = 0;
    status->cur_delay = 0;
    status->file = file;
    status->line = line;
    status->func = func;
}

// Finish spin delay
static void finish_spin_delay(SpinDelayStatus *status) {
    // Placeholder for additional cleanup if needed
}

// Perform spin delay
void perform_spin_delay(SpinDelayStatus *status) {
    // CPU-specific delay each time through the loop
    for (int i = 0; i < SPINS_PER_DELAY; i++) {
        // Simulate spinning
    }

    // Block the process every spins_per_delay tries
    if (++(status->spins) >= SPINS_PER_DELAY) {
        if (++(status->delays) > NUM_DELAYS)
            s_lock_stuck(status->file, status->line, status->func);

        if (status->cur_delay == 0) // first time to delay?
            status->cur_delay = MIN_DELAY_USEC;

        // Report wait event and sleep
        pgstat_report_wait_start(0);
        pg_usleep(status->cur_delay);
        pgstat_report_wait_end();

        // Increase delay by a random fraction between 1X and 2X
        status->cur_delay += (int)(status->cur_delay * pg_prng_double(NULL) + 0.5);

        // Wrap back to minimum delay when max is exceeded
        if (status->cur_delay > MAX_DELAY_USEC)
            status->cur_delay = MIN_DELAY_USEC;

        status->spins = 0;
    }
}


// Platform-independent portion of waiting for a spinlock
int s_lock(volatile slock_t *lock, const char *file, int line, const char *func) {
    SpinDelayStatus delayStatus;
    init_spin_delay(&delayStatus, file, line, func);

    while (TAS_SPIN(lock)) {
        perform_spin_delay(&delayStatus);
    }

    finish_spin_delay(&delayStatus);
    return delayStatus.delays;
}

#ifdef USE_DEFAULT_S_UNLOCK
void s_unlock(volatile slock_t *lock) {
    *lock = 0; // Release lock
}
#endif

// Main function to test the spinlock functions
int main() {
    slock_t lock = 0;
    SpinDelayStatus status = {0, 0, 0, __FILE__, __LINE__, __func__};

    // Simulate acquiring and releasing the spinlock
    s_lock(&lock, __FILE__, __LINE__, __func__);
    printf("Lock acquired %d\n", lock);
    ASSERT(1, lock);
    s_unlock(&lock);
    printf("Lock released %d\n", lock);
    ASSERT(0, lock);

    return 0;
}
