#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

// Define types
typedef unsigned char uint8;	/* == 8 bits */
typedef unsigned short uint16;	/* == 16 bits */
typedef unsigned int uint32;	/* == 32 bits */
typedef uint32_t Size; // Placeholder for actual size type

// Array for leftmost one position
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

// Function to get the position of the leftmost one bit
static inline int pg_leftmost_one_pos32(uint32 word) {
    if (word == 0)
        return -1;

    int shift = 24;
    if (word & 0xFFFF0000) { word >>= 16; shift += 16; }
    if (word & 0x0000FF00) { word >>= 8;  shift += 8;  }
    return shift + pg_leftmost_one_pos[word];
}

// Function to calculate the ceiling of the log base 2
static inline uint32 pg_ceil_log2_32(uint32 num) {
    if (num < 2)
        return 0;
    else
        return pg_leftmost_one_pos32(num - 1) + 1;
}

// Simulate bucket calculation
uint32_t calc_bucket(struct hash_header *hctl, uint32_t hashvalue) {
    return hashvalue % 16; // Simple hash function for simulation
}

// Define the MOD macro
#define MOD(x, y) ((x) & ((y) - 1))

// Simulate error handling
void hash_corrupted(struct HTAB *hashp) {
    fprintf(stderr, "Hash table corrupted!\n");
    exit(EXIT_FAILURE);
}

// The function to be tested
static inline uint32_t hash_initial_lookup(struct HTAB *hashp, uint32_t hashvalue, HASHBUCKET **bucketptr) {
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
        fprintf(stderr, "Segment number %ld out of bounds (%ld)!\n", segment_num, hashp->ssize);
        hash_corrupted(hashp);
    }

    segp = hashp->dir[segment_num];

    if (segp == NULL) {
        hash_corrupted(hashp);
    }

    *bucketptr = &segp[segment_ndx];
    return bucket;
}

// Main function to test the `hash_initial_lookup` function
int main() {
    struct HTAB hashp;
    struct hash_header hctl;
    HASHBUCKET buckets[4]; // Array to hold bucket pointers
    HASHSEGMENT segments[2]; // Array to hold segment pointers

    // Initialize example data
    hashp.hctl = &hctl;
    hashp.ssize = 4; // Segment size (must be power of 2)
    hashp.sshift = 2; // Segment shift (log2 of ssize)
    hashp.dir = segments;
    hashp.ssize = 2; // Number of segments

    // Initialize segments
    for (int i = 0; i < 4; ++i) {
        buckets[i] = (HASHELEMENT *)malloc(sizeof(HASHELEMENT));
        if (buckets[i] == NULL) {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
        buckets[i]->link = NULL;
        buckets[i]->hashvalue = i; // Example hash value
    }

    segments[0] = &buckets[0];
    segments[1] = &buckets[2];

    HASHBUCKET *bucketptr;
    uint32_t bucket = hash_initial_lookup(&hashp, 2, &bucketptr);

    printf("Bucket: %u\n", bucket);
    if (bucketptr != NULL) {
        HASHELEMENT *elem = (HASHELEMENT *)*bucketptr;
        printf("Bucket pointer value: %u\n", elem->hashvalue);
    } else {
        printf("Bucket pointer is NULL\n");
    }

    // Free allocated memory
    for (int i = 0; i < 4; ++i) {
        free(buckets[i]);
    }

    return 0;
}
