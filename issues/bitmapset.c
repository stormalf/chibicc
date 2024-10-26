#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

// Define constants and types
#define BITS_PER_BITMAPWORD 64
#define WORDNUM(x)  ((x) / BITS_PER_BITMAPWORD) // Calculate the word number
#define BITNUM(x)   ((x) % BITS_PER_BITMAPWORD)  // Calculate the bit number

typedef uint64_t bitmapword;       // must be an unsigned type
typedef int64_t signedbitmapword;  // must be the matching signed type
#define FLEXIBLE_ARRAY_MEMBER      /* empty */

// Bitmapset structure definition
typedef struct Bitmapset
{
    int nwords;                     // number of words in array
    bitmapword words[FLEXIBLE_ARRAY_MEMBER]; // really [nwords]
} Bitmapset;

// Macro to calculate the size of the Bitmapset
#define BITMAPSET_SIZE(nwords) \
    (offsetof(Bitmapset, words) + (nwords) * sizeof(bitmapword))

// Function to check if the bitmapset is valid
static inline int bms_is_valid_set(const Bitmapset *a)
{
    return a != NULL && a->nwords >= 0;
}

// Function to create a singleton bitmapset
Bitmapset *
bms_make_singleton(int x)
{
    Bitmapset *result;
    int wordnum, bitnum;

    // Check for negative input
    if (x < 0)
        fprintf(stderr, "ERROR: negative bitmapset member not allowed\n");
    
    wordnum = WORDNUM(x); // Calculate the word number
    bitnum = BITNUM(x);   // Calculate the bit number
    
    // Allocate memory for the bitmapset
    result = (Bitmapset *) calloc(1, BITMAPSET_SIZE(wordnum + 1));
    
    // Initialize the bitmapset
    result->nwords = wordnum + 1;
    result->words[wordnum] = ((bitmapword) 1 << bitnum);
    
    return result;
}

/*
 * bms_copy - make a palloc'd copy of a bitmapset
 */
Bitmapset *
bms_copy(const Bitmapset *a)
{
    Bitmapset *result;
    size_t size;

    assert(bms_is_valid_set(a));

    if (a == NULL)
        return NULL;

    size = BITMAPSET_SIZE(a->nwords);
    result = (Bitmapset *) malloc(size);  // Simulating palloc
    memcpy(result, a, size);
    return result;
}

/*
 * bms_is_member - is X a member of A?
 */
bool
bms_is_member(int x, const Bitmapset *a)
{
    int wordnum, bitnum;

    assert(bms_is_valid_set(a));

    /* Check for negative input */
    if (x < 0)
        fprintf(stderr, "ERROR: negative bitmapset member not allowed\n");
    
    if (a == NULL)
        return false;

    wordnum = WORDNUM(x);
    bitnum = BITNUM(x);
    if (wordnum >= a->nwords)
        return false;
    if ((a->words[wordnum] & ((bitmapword) 1 << bitnum)) != 0)
        return true;
    return false;
}

// Main function to test the bitmapset operations
int main() {
    // Create a singleton bitmapset with a valid positive integer
    int valid_member = 5; // A valid index
    Bitmapset *bs = bms_make_singleton(valid_member);
    
    // Print the created bitmapset
    if (bs) {
        printf("Bitmapset created with nwords: %d\n", bs->nwords);
        printf("Bitmapset words[0]: %llu\n", (unsigned long long)bs->words[WORDNUM(valid_member)]);
    }

    // Check if valid_member is in the bitmapset
    if (bms_is_member(valid_member, bs)) {
        printf("%d is a member of the bitmapset.\n", valid_member);
    } else {
        printf("%d is NOT a member of the bitmapset.\n", valid_member);
    }

    // Copy the bitmapset
    Bitmapset *bs_copy = bms_copy(bs);
    if (bs_copy) {
        printf("Copied Bitmapset with nwords: %d\n", bs_copy->nwords);
        printf("Copied Bitmapset words[0]: %llu\n", (unsigned long long)bs_copy->words[WORDNUM(valid_member)]);
    }

    // Free allocated memory
    free(bs);
    free(bs_copy);

    return 0;
}
