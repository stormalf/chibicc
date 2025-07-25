#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>


typedef uint32_t uint32;

typedef struct {
    volatile uint32 value;
} pg_atomic_uint32;

#define AssertPointerAlignment(ptr, align) assert(((uintptr_t)(ptr) % (align)) == 0)

#define LW_EXCLUSIVE 1
#define LW_SHARED 2
#define LW_LOCK_MASK 0xF
#define LW_VAL_EXCLUSIVE 0x10
#define LW_VAL_SHARED 0x20

typedef struct {
    pg_atomic_uint32 state;
#ifdef LOCK_DEBUG
    void* owner;
#endif
} LWLock;

/* Atomic compare-and-exchange function */
static inline bool
pg_atomic_compare_exchange_u32_impl(volatile pg_atomic_uint32 *ptr,
                                    uint32 *expected, uint32 newval)
{
    unsigned char ret;  // Use unsigned char for setz result

    __asm__ __volatile__(
        "lock\n\t"
        "cmpxchgl %3, %2\n\t"
        "setz %1"
    : "=a" (*expected), "=q" (ret), "+m" (ptr->value)
    : "r" (newval), "a" (*expected)
    : "memory", "cc");
    assert(1 == ret);
    return (bool) ret;
}

static inline bool
pg_atomic_compare_exchange_u32(volatile pg_atomic_uint32 *ptr,
                               uint32 *expected, uint32 newval)
{
    AssertPointerAlignment(ptr, 4);
    AssertPointerAlignment(expected, 4);

    return pg_atomic_compare_exchange_u32_impl(ptr, expected, newval);
}

/* Attempt to lock function */
static bool
LWLockAttemptLock(LWLock *lock, uint32 mode)
{
    uint32 old_state;

    //Assert(mode == LW_EXCLUSIVE || mode == LW_SHARED);

    old_state = lock->state.value;

    while (true)
    {
        uint32 desired_state;
        bool lock_free;

        desired_state = old_state;

        if (mode == LW_EXCLUSIVE)
        {
            lock_free = (old_state & LW_LOCK_MASK) == 0;
            if (lock_free)
                desired_state += LW_VAL_EXCLUSIVE;
        }
        else
        {
            lock_free = (old_state & LW_VAL_EXCLUSIVE) == 0;
            if (lock_free)
                desired_state += LW_VAL_SHARED;
        }

        if (pg_atomic_compare_exchange_u32(&lock->state, &old_state, desired_state))
        {
            if (lock_free)
            {
#ifdef LOCK_DEBUG
                if (mode == LW_EXCLUSIVE)
                    lock->owner = (void*)1;  // Simulating a lock owner for debug
#endif
                return false;
            }
            else
                return true;
        }
    }
}

int main() {
    LWLock lock = {{0}};  // Initialize the lock

    // Attempt to acquire an exclusive lock
    if (!LWLockAttemptLock(&lock, LW_EXCLUSIVE)) {
        printf("Acquired exclusive lock.\n");
    } else {
        printf("Failed to acquire exclusive lock.\n");
    }

    // Attempt to acquire a shared lock
    if (!LWLockAttemptLock(&lock, LW_SHARED)) {
        printf("Acquired shared lock.\n");
    } else {
        printf("Failed to acquire shared lock.\n");
    }

    return 0;
}
