#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "test.h"

#define NUM_FREELISTS 32

typedef unsigned char uint8;  /* == 8 bits */
typedef unsigned short uint16; /* == 16 bits */
typedef unsigned int uint32;  /* == 32 bits */

const uint8 pg_leftmost_one_pos[256] = {
    0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

typedef uint32_t uint32;
typedef uint32_t Size; // Placeholder for actual size type

// Define the HASHELEMENT structure
typedef struct HASHELEMENT {
    struct HASHELEMENT *link;  // link to next entry in same bucket
    uint32 hashvalue;          // hash function result for this entry
} HASHELEMENT;

// Define hash bucket and segment
typedef HASHELEMENT *HASHBUCKET;
typedef HASHBUCKET *HASHSEGMENT;

// Define the structure for the hash header
struct hash_header {
    // Placeholder for actual header contents
};

// Define the HTAB structure
struct HTAB {
    struct hash_header *hctl;  /* => shared control information */
    HASHSEGMENT *dir;          /* directory of segment starts */
    Size keysize;              /* hash key length in bytes */
    long ssize;                /* segment size --- must be power of 2 */
    int sshift;                /* segment shift = log2(ssize) */
};
typedef struct HASHHDR HASHHDR;
typedef unsigned char slock_t;

typedef struct {
    slock_t mutex;             /* spinlock for this freelist */
    long nentries;             /* number of entries in associated buckets */
    HASHELEMENT *freeList;     /* chain of free elements */
} FreeListData;

struct HASHHDR {
    FreeListData freeList[NUM_FREELISTS];
    long dsize;                /* directory size */
    long nsegs;                /* number of allocated segments (<= dsize) */
    uint32 max_bucket;         /* ID of maximum bucket in use */
    uint32 high_mask;          /* mask to modulo into entire table */
    uint32 low_mask;           /* mask to modulo into lower half of table */
    Size keysize;              /* hash key length in bytes */
    Size entrysize;            /* total user element size in bytes */
    long num_partitions;       /* # partitions (must be power of 2), or 0 */
    long max_dsize;            /* 'dsize' limit if directory is fixed size */
    long ssize;                /* segment size --- must be power of 2 */
    int sshift;                /* segment shift = log2(ssize) */
    int nelem_alloc;           /* number of entries to allocate at once */
#ifdef HASH_STATISTICS
    long accesses;
    long collisions;
#endif
};

// Simulate error handling
void hash_corrupted(struct HTAB *hashp) {
    fprintf(stderr, "Hash table corrupted!\n");
    exit(EXIT_FAILURE);
}

static inline int
pg_leftmost_one_pos32(uint32 word) {
#ifdef HAVE__BUILTIN_CLZ
    return 31 - __builtin_clz(word);
#elif defined(_MSC_VER)
    unsigned long result;
    bool non_zero;
    non_zero = _BitScanReverse(&result, word);
    return (int) result;
#else
    int shift = 32 - 8;
    while ((word >> shift) == 0)
        shift -= 8;
    return shift + pg_leftmost_one_pos[(word >> shift) & 255];
#endif
}

static inline uint32
pg_ceil_log2_32(uint32 num) {
    if (num < 2)
        return 0;
    else
        return pg_leftmost_one_pos32(num - 1) + 1;
}

/* calculate ceil(log base 2) of num */
int
my_log2(long num) {
    /* guard against too-large input, which would be invalid for pg_ceil_log2_*() */
    if (num > LONG_MAX / 2)
        num = LONG_MAX / 2;
#if SIZEOF_LONG < 8
    return pg_ceil_log2_32(num);
#else
    return pg_ceil_log2_64(num);
#endif
}

/* calculate first power of 2 >= num, bounded to what will fit in an int */
static int
next_pow2_int(long num)
{
	if (num > INT_MAX / 2)
		num = INT_MAX / 2;
	return 1 << my_log2(num);
}


/* Convert a hash value to a bucket number */
static inline uint32
calc_bucket(HASHHDR *hctl, uint32 hash_val) {
    uint32 bucket;
    bucket = hash_val & hctl->high_mask;
    if (bucket > hctl->max_bucket)
        bucket = bucket & hctl->low_mask;
    return bucket;
}

// Define the MOD macro
#define MOD(x, y) ((x) & ((y) - 1))

// The function to be tested
static inline uint32_t
hash_initial_lookup(struct HTAB *hashp, uint32_t hashvalue, HASHBUCKET **bucketptr) {
    if (!hashp || !hashp->dir) {
        fprintf(stderr, "Hash table or directory is NULL!\n");
        exit(EXIT_FAILURE);
    }
    struct hash_header *hctl = hashp->hctl;
    HASHSEGMENT segp;
    long segment_num;
    long segment_ndx;
    uint32_t bucket;
    bucket = calc_bucket(hctl, hashvalue);
    segment_num = bucket >> hashp->sshift;
    segment_ndx = MOD(bucket, hashp->ssize);
    if (segment_num >= hashp->ssize) {
        fprintf(stderr, "Segment number %ld out of bounds (%ld)!\n",
                segment_num, hashp->ssize);
        exit(EXIT_FAILURE);
    }
    segp = hashp->dir[segment_num];
    if (!segp) {
        fprintf(stderr, "Hash segment %ld is NULL!\n", segment_num);
        exit(EXIT_FAILURE);
    }
    *bucketptr = &segp[segment_ndx];
    return bucket;
}

// Initialize the hash table (simplified version)
void init_htab(struct HTAB *hashp, int nelem) {
    int ssize;
    int sshift;
    int max_bucket;
    int high_mask;
    int low_mask;
	int			nbuckets;
    HASHHDR *hctl;

    // Calculate segment size and shift
    ssize = next_pow2_int(nelem / 256);
    if (ssize < 1)
        ssize = 1;
    sshift = 8;

    // Allocate memory for hctl
    hctl = (HASHHDR *) malloc(sizeof(HASHHDR));
    if (!hctl) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize hctl
    hctl->dsize = 1;
    hctl->nsegs = 1;
    hctl->max_bucket = 0;
    hctl->high_mask = 1;
    hctl->low_mask = 0;
    hctl->keysize = sizeof(int); // Example key size
    hctl->entrysize = sizeof(HASHELEMENT);
    hctl->num_partitions = 1;
    hctl->max_dsize = 1;
    hctl->ssize = ssize;
    hctl->sshift = sshift;
    hctl->nelem_alloc = nelem;

	nbuckets = next_pow2_int(nelem);
    // Allocate memory for directory
    hashp->dir = (HASHSEGMENT *) malloc(hctl->dsize * sizeof(HASHSEGMENT));
    if (!hashp->dir) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(hctl);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for first segment
    hashp->dir[0] = (HASHBUCKET *) calloc(ssize, sizeof(HASHBUCKET));
    if (!hashp->dir[0]) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(hashp->dir);
        free(hctl);
        exit(EXIT_FAILURE);
    }

    // Initialize the hash table structure
    hashp->hctl = hctl;
    hashp->keysize = sizeof(int);
    hashp->ssize = ssize;
    hashp->sshift = sshift;
}

// Test the hash_initial_lookup function
int main() {
    struct HTAB hash_table;
    struct HASHELEMENT element;
    uint32_t hash_value = 3926571702;
    HASHBUCKET *bucketptr;

    // Initialize the hash table with an example size
    init_htab(&hash_table, 1000);

    // Perform the hash lookup
    uint32_t bucket = hash_initial_lookup(&hash_table, hash_value, &bucketptr);

    // Output the result
    printf("Hash value: %u\n", hash_value);
    ASSERT(3926571702, hash_value);
    printf("Bucket: %u\n", bucket);
    printf("Bucket pointer: %p\n", (void *)bucketptr);

    // Cleanup allocated memory
    free(hash_table.dir[0]);
    free(hash_table.dir);
    free(hash_table.hctl);

    return 0;
}
