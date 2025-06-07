
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>


#define MAXIMUM_ALIGNOF 8
#define BLCKSZ 8192
typedef unsigned char uint8;	/* == 8 bits */
typedef unsigned short uint16;	/* == 16 bits */
typedef unsigned int uint32;	/* == 32 bits */
typedef uint8 bits8;			/* >= 8 bits */
typedef uint16 bits16;			/* >= 16 bits */
typedef uint32 bits32;			/* >= 32 bits */


#define FLEXIBLE_ARRAY_MEMBER	/* empty */




typedef struct ItemIdData
{
	unsigned	lp_off:15,		/* offset to tuple (from start of page) */
				lp_flags:2,		/* state of line pointer, see below */
				lp_len:15;		/* byte length of tuple */
} ItemIdData;

struct HeapTupleHeaderData
{
	union
	{
		char * t_heap;
		char * t_datum;
	}			t_choice;

	char * t_ctid;		/* current TID of this or newer tuple (or a
								 * speculative insertion token) */

	/* Fields below here must match MinimalTupleData! */

#define FIELDNO_HEAPTUPLEHEADERDATA_INFOMASK2 2
	uint16		t_infomask2;	/* number of attributes + various flags */

#define FIELDNO_HEAPTUPLEHEADERDATA_INFOMASK 3
	uint16		t_infomask;		/* various flag bits, see below */

#define FIELDNO_HEAPTUPLEHEADERDATA_HOFF 4
	uint8		t_hoff;			/* sizeof header incl. bitmap, padding */

	/* ^ - 23 bytes - ^ */
#define FIELDNO_HEAPTUPLEHEADERDATA_BITS 5
	bits8		t_bits[FLEXIBLE_ARRAY_MEMBER];	/* bitmap of NULLs */

};
typedef struct HeapTupleHeaderData HeapTupleHeaderData;


typedef struct PageHeaderData
{
	/* XXX LSN is member of *any* block, not only page-organized ones */
	char * pd_lsn;		/* LSN: next byte after last byte of xlog
								 * record for last change to this page */
	uint16		pd_checksum;	/* checksum */
	uint16		pd_flags;		/* flag bits, see below */
	int * pd_lower;		/* offset to start of free space */
	int * pd_upper;		/* offset to end of free space */
	int * pd_special;	/* offset to start of special space */
	uint16		pd_pagesize_version;
	char * pd_prune_xid; /* oldest prunable XID, or zero if none */
	ItemIdData	pd_linp[FLEXIBLE_ARRAY_MEMBER]; /* line pointer array */
	} PageHeaderData;



#define SizeofHeapTupleHeader offsetof(HeapTupleHeaderData, t_bits)

// #define offsetof(t, d) __builtin_offsetof(t, d)
#define SizeOfPageHeaderData (offsetof(PageHeaderData, pd_linp))

#define TYPEALIGN(ALIGNVAL,LEN)  \
	(((uintptr_t) (LEN) + ((ALIGNVAL) - 1)) & ~((uintptr_t) ((ALIGNVAL) - 1)))
#define MAXALIGN(LEN)			TYPEALIGN(MAXIMUM_ALIGNOF, (LEN))


#define MaxHeapTuplesPerPage	\
	((int) ((BLCKSZ - SizeOfPageHeaderData) / \
			(MAXALIGN(SizeofHeapTupleHeader) + sizeof(ItemIdData))))
// #define myvalue 190
// #define MaxHeapTuplesPerPage myvalue + 100

#define MAX_TUPLES_PER_PAGE  MaxHeapTuplesPerPage


typedef struct
{
	int			nredirected;	/* numbers of entries in arrays below */
	int			ndead;
	int			nunused;
	/*
	 * marked[i] is true if item i is entered in one of the above arrays.
	 *
	 * This needs to be MaxHeapTuplesPerPage + 1 long as FirstOffsetNumber is
	 * 1. Otherwise every access would need to subtract 1.
	 */
	bool	marked[MaxHeapTuplesPerPage + 1];

} PruneState;


int
heap_page_prune()
{
	PruneState	prstate;
	memset(prstate.marked, 0, sizeof(prstate.marked));
	printf("====%ld\n", sizeof(prstate.marked));
	printf("====%d\n", MaxHeapTuplesPerPage + 1);
	printf("====ok\n");

    return 0;
}

int main() {
	heap_page_prune();
    return 0;
}