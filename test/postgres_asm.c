
#include <stdio.h>
#include <stdint.h>
#include "test.h"
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef uint8_t uint8;
typedef int8_t int8;

typedef uint8 bits8;			/* >= 8 bits */
typedef uint16 bits16;			/* >= 16 bits */
typedef uint32 bits32;			/* >= 32 bits */

const uint8 pg_rightmost_one_pos[256] = {
	0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};


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

const uint8 pg_number_of_ones[256] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};

#define INT64CONST(x)  (x##L)
#define UINT64CONST(x) (x##UL)
#define PG_INT8_MIN		(-0x7F-1)
#define PG_INT8_MAX		(0x7F)
#define PG_UINT8_MAX	(0xFF)
#define PG_INT16_MIN	(-0x7FFF-1)
#define PG_INT16_MAX	(0x7FFF)
#define PG_UINT16_MAX	(0xFFFF)
#define PG_INT32_MIN	(-0x7FFFFFFF-1)
#define PG_INT32_MAX	(0x7FFFFFFF)
#define PG_UINT32_MAX	(0xFFFFFFFFU)
#define PG_INT64_MIN	(-INT64CONST(0x7FFFFFFFFFFFFFFF) - 1)
#define PG_INT64_MAX	INT64CONST(0x7FFFFFFFFFFFFFFF)
#define PG_UINT64_MAX	UINT64CONST(0xFFFFFFFFFFFFFFFF)


#define TYPEALIGN(ALIGNVAL,LEN)  \
	(((uintptr_t) (LEN) + ((ALIGNVAL) - 1)) & ~((uintptr_t) ((ALIGNVAL) - 1)))

#define SHORTALIGN(LEN)			TYPEALIGN(ALIGNOF_SHORT, (LEN))
#define INTALIGN(LEN)			TYPEALIGN(ALIGNOF_INT, (LEN))
#define LONGALIGN(LEN)			TYPEALIGN(ALIGNOF_LONG, (LEN))
#define DOUBLEALIGN(LEN)		TYPEALIGN(ALIGNOF_DOUBLE, (LEN))
#define MAXALIGN(LEN)			TYPEALIGN(MAXIMUM_ALIGNOF, (LEN))
/* MAXALIGN covers only built-in types, not buffers */
#define BUFFERALIGN(LEN)		TYPEALIGN(ALIGNOF_BUFFER, (LEN))
#define CACHELINEALIGN(LEN)		TYPEALIGN(PG_CACHE_LINE_SIZE, (LEN))

#define TYPEALIGN_DOWN(ALIGNVAL,LEN)  \
	(((uintptr_t) (LEN)) & ~((uintptr_t) ((ALIGNVAL) - 1)))

#define SHORTALIGN_DOWN(LEN)	TYPEALIGN_DOWN(ALIGNOF_SHORT, (LEN))
#define INTALIGN_DOWN(LEN)		TYPEALIGN_DOWN(ALIGNOF_INT, (LEN))
#define LONGALIGN_DOWN(LEN)		TYPEALIGN_DOWN(ALIGNOF_LONG, (LEN))
#define DOUBLEALIGN_DOWN(LEN)	TYPEALIGN_DOWN(ALIGNOF_DOUBLE, (LEN))
#define MAXALIGN_DOWN(LEN)		TYPEALIGN_DOWN(MAXIMUM_ALIGNOF, (LEN))
#define BUFFERALIGN_DOWN(LEN)	TYPEALIGN_DOWN(ALIGNOF_BUFFER, (LEN))


/*-------------------------------------------------------------------------
 *
 * pg_bitutils.h
 *	  Miscellaneous functions for bit-wise operations.
 *
 *
 * Copyright (c) 2019-2024, PostgreSQL Global Development Group
 *
 * src/include/port/pg_bitutils.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_BITUTILS_H
#define PG_BITUTILS_H

#ifdef _MSC_VER
#include <intrin.h>
#define HAVE_BITSCAN_FORWARD
#define HAVE_BITSCAN_REVERSE

#else
#if defined(HAVE__BUILTIN_CTZ)
#define HAVE_BITSCAN_FORWARD
#endif

#if defined(HAVE__BUILTIN_CLZ)
#define HAVE_BITSCAN_REVERSE
#endif
#endif							/* _MSC_VER */



/*
 * pg_leftmost_one_pos32
 *		Returns the position of the most significant set bit in "word",
 *		measured from the least significant bit.  word must not be 0.
 */
static inline int
pg_leftmost_one_pos32(uint32 word)
{
#ifdef HAVE__BUILTIN_CLZ
	//Assert(word != 0);

	return 31 - __builtin_clz(word);
#elif defined(_MSC_VER)
	unsigned long result;
	bool		non_zero;

	//Assert(word != 0);

	non_zero = _BitScanReverse(&result, word);
	return (int) result;
#else
	int			shift = 32 - 8;

	//Assert(word != 0);

	while ((word >> shift) == 0)
		shift -= 8;

	return shift + pg_leftmost_one_pos[(word >> shift) & 255];
#endif							/* HAVE__BUILTIN_CLZ */
}

/*
 * pg_leftmost_one_pos64
 *		As above, but for a 64-bit word.
 */
static inline int
pg_leftmost_one_pos64(uint64 word)
{
#ifdef HAVE__BUILTIN_CLZ
	//Assert(word != 0);

#if defined(HAVE_LONG_INT_64)
	return 63 - __builtin_clzl(word);
#elif defined(HAVE_LONG_LONG_INT_64)
	return 63 - __builtin_clzll(word);
#else
#error must have a working 64-bit integer datatype
#endif							/* HAVE_LONG_INT_64 */

#elif defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_ARM64))
	unsigned long result;
	bool		non_zero;

	//Assert(word != 0);

	non_zero = _BitScanReverse64(&result, word);
	return (int) result;
#else
	int			shift = 64 - 8;

	//Assert(word != 0);

	while ((word >> shift) == 0)
		shift -= 8;

	return shift + pg_leftmost_one_pos[(word >> shift) & 255];
#endif							/* HAVE__BUILTIN_CLZ */
}

/*
 * pg_rightmost_one_pos32
 *		Returns the position of the least significant set bit in "word",
 *		measured from the least significant bit.  word must not be 0.
 */
static inline int
pg_rightmost_one_pos32(uint32 word)
{
#ifdef HAVE__BUILTIN_CTZ
	//Assert(word != 0);

	return __builtin_ctz(word);
#elif defined(_MSC_VER)
	unsigned long result;
	bool		non_zero;

	//Assert(word != 0);

	non_zero = _BitScanForward(&result, word);
	return (int) result;
#else
	int			result = 0;

	//Assert(word != 0);

	while ((word & 255) == 0)
	{
		word >>= 8;
		result += 8;
	}
	result += pg_rightmost_one_pos[word & 255];
	return result;
#endif							/* HAVE__BUILTIN_CTZ */
}

/*
 * pg_rightmost_one_pos64
 *		As above, but for a 64-bit word.
 */
static inline int
pg_rightmost_one_pos64(uint64 word)
{
#ifdef HAVE__BUILTIN_CTZ
	//Assert(word != 0);

#if defined(HAVE_LONG_INT_64)
	return __builtin_ctzl(word);
#elif defined(HAVE_LONG_LONG_INT_64)
	return __builtin_ctzll(word);
#else
#error must have a working 64-bit integer datatype
#endif							/* HAVE_LONG_INT_64 */

#elif defined(_MSC_VER) && (defined(_M_AMD64) || defined(_M_ARM64))
	unsigned long result;
	bool		non_zero;

	//Assert(word != 0);

	non_zero = _BitScanForward64(&result, word);
	return (int) result;
#else
	int			result = 0;

	//Assert(word != 0);

	while ((word & 255) == 0)
	{
		word >>= 8;
		result += 8;
	}
	result += pg_rightmost_one_pos[word & 255];
	return result;
#endif							/* HAVE__BUILTIN_CTZ */
}

/*
 * pg_nextpower2_32
 *		Returns the next higher power of 2 above 'num', or 'num' if it's
 *		already a power of 2.
 *
 * 'num' mustn't be 0 or be above PG_UINT32_MAX / 2 + 1.
 */
static inline uint32
pg_nextpower2_32(uint32 num)
{
	//Assert(num > 0 && num <= PG_UINT32_MAX / 2 + 1);

	/*
	 * A power 2 number has only 1 bit set.  Subtracting 1 from such a number
	 * will turn on all previous bits resulting in no common bits being set
	 * between num and num-1.
	 */
	if ((num & (num - 1)) == 0)
		return num;				/* already power 2 */

	return ((uint32) 1) << (pg_leftmost_one_pos32(num) + 1);
}

/*
 * pg_nextpower2_64
 *		Returns the next higher power of 2 above 'num', or 'num' if it's
 *		already a power of 2.
 *
 * 'num' mustn't be 0 or be above PG_UINT64_MAX / 2  + 1.
 */
static inline uint64
pg_nextpower2_64(uint64 num)
{
	//Assert(num > 0 && num <= PG_UINT64_MAX / 2 + 1);

	/*
	 * A power 2 number has only 1 bit set.  Subtracting 1 from such a number
	 * will turn on all previous bits resulting in no common bits being set
	 * between num and num-1.
	 */
	if ((num & (num - 1)) == 0)
		return num;				/* already power 2 */

	return ((uint64) 1) << (pg_leftmost_one_pos64(num) + 1);
}

/*
 * pg_prevpower2_32
 *		Returns the next lower power of 2 below 'num', or 'num' if it's
 *		already a power of 2.
 *
 * 'num' mustn't be 0.
 */
static inline uint32
pg_prevpower2_32(uint32 num)
{
	return ((uint32) 1) << pg_leftmost_one_pos32(num);
}

/*
 * pg_prevpower2_64
 *		Returns the next lower power of 2 below 'num', or 'num' if it's
 *		already a power of 2.
 *
 * 'num' mustn't be 0.
 */
static inline uint64
pg_prevpower2_64(uint64 num)
{
	return ((uint64) 1) << pg_leftmost_one_pos64(num);
}

/*
 * pg_ceil_log2_32
 *		Returns equivalent of ceil(log2(num))
 */
static inline uint32
pg_ceil_log2_32(uint32 num)
{
	if (num < 2)
		return 0;
	else
		return pg_leftmost_one_pos32(num - 1) + 1;
}

/*
 * pg_ceil_log2_64
 *		Returns equivalent of ceil(log2(num))
 */
static inline uint64
pg_ceil_log2_64(uint64 num)
{
	if (num < 2)
		return 0;
	else
		return pg_leftmost_one_pos64(num - 1) + 1;
}

/*
 * With MSVC on x86_64 builds, try using native popcnt instructions via the
 * __popcnt and __popcnt64 intrinsics.  These don't work the same as GCC's
 * __builtin_popcount* intrinsic functions as they always emit popcnt
 * instructions.
 */
#if defined(_MSC_VER) && defined(_M_AMD64)
#define HAVE_X86_64_POPCNTQ
#endif

/*
 * On x86_64, we can use the hardware popcount instruction, but only if
 * we can verify that the CPU supports it via the cpuid instruction.
 *
 * Otherwise, we fall back to a hand-rolled implementation.
 */
#ifdef HAVE_X86_64_POPCNTQ
#if defined(HAVE__GET_CPUID) || defined(HAVE__CPUID)
#define TRY_POPCNT_FAST 1
#endif
#endif

#ifdef TRY_POPCNT_FAST
/* Attempt to use the POPCNT instruction, but perform a runtime check first */
extern PGDLLIMPORT int (*pg_popcount32) (uint32 word);
extern PGDLLIMPORT int (*pg_popcount64) (uint64 word);
extern PGDLLIMPORT uint64 (*pg_popcount_optimized) (const char *buf, int bytes);
extern PGDLLIMPORT uint64 (*pg_popcount_masked_optimized) (const char *buf, int bytes, bits8 mask);

/*
 * We can also try to use the AVX-512 popcount instruction on some systems.
 * The implementation of that is located in its own file because it may
 * require special compiler flags that we don't want to apply to any other
 * files.
 */
#ifdef USE_AVX512_POPCNT_WITH_RUNTIME_CHECK
extern bool pg_popcount_avx512_available(void);
extern uint64 pg_popcount_avx512(const char *buf, int bytes);
extern uint64 pg_popcount_masked_avx512(const char *buf, int bytes, bits8 mask);
#endif

#else
/* Use a portable implementation -- no need for a function pointer. */


static inline int
pg_popcount32_slow(uint32 word)
{
#ifdef HAVE__BUILTIN_POPCOUNT
	return __builtin_popcount(word);
#else							/* !HAVE__BUILTIN_POPCOUNT */
	int			result = 0;

	while (word != 0)
	{
		result += pg_number_of_ones[word & 255];
		word >>= 8;
	}

	return result;
#endif							/* HAVE__BUILTIN_POPCOUNT */
}

/*
 * pg_popcount64_slow
 *		Return the number of 1 bits set in word
 */
static inline int
pg_popcount64_slow(uint64 word)
{
#ifdef HAVE__BUILTIN_POPCOUNT
#if defined(HAVE_LONG_INT_64)
	return __builtin_popcountl(word);
#elif defined(HAVE_LONG_LONG_INT_64)
	return __builtin_popcountll(word);
#else
#error must have a working 64-bit integer datatype
#endif
#else							/* !HAVE__BUILTIN_POPCOUNT */
	int			result = 0;

	while (word != 0)
	{
		result += pg_number_of_ones[word & 255];
		word >>= 8;
	}

	return result;
#endif							/* HAVE__BUILTIN_POPCOUNT */
}

/*
 * pg_popcount_slow
 *		Returns the number of 1-bits in buf
 */
static uint64
pg_popcount_slow(const char *buf, int bytes)
{
	uint64		popcnt = 0;

#if SIZEOF_VOID_P >= 8
	/* Process in 64-bit chunks if the buffer is aligned. */
	if (buf == (const char *) TYPEALIGN(8, buf))
	{
		const uint64 *words = (const uint64 *) buf;

		while (bytes >= 8)
		{
			popcnt += pg_popcount64_slow(*words++);
			bytes -= 8;
		}

		buf = (const char *) words;
	}
#else
	/* Process in 32-bit chunks if the buffer is aligned. */
	if (buf == (const char *) TYPEALIGN(4, buf))
	{
		const uint32 *words = (const uint32 *) buf;

		while (bytes >= 4)
		{
			popcnt += pg_popcount32_slow(*words++);
			bytes -= 4;
		}

		buf = (const char *) words;
	}
#endif

	/* Process any remaining bytes */
	while (bytes--)
		popcnt += pg_number_of_ones[(unsigned char) *buf++];

	return popcnt;
}

/*
 * pg_popcount_masked_slow
 *		Returns the number of 1-bits in buf after applying the mask to each byte
 */
static uint64
pg_popcount_masked_slow(const char *buf, int bytes, bits8 mask)
{
	uint64		popcnt = 0;

#if SIZEOF_VOID_P >= 8
	/* Process in 64-bit chunks if the buffer is aligned */
	uint64		maskv = ~UINT64CONST(0) / 0xFF * mask;

	if (buf == (const char *) TYPEALIGN(8, buf))
	{
		const uint64 *words = (const uint64 *) buf;

		while (bytes >= 8)
		{
			popcnt += pg_popcount64_slow(*words++ & maskv);
			bytes -= 8;
		}

		buf = (const char *) words;
	}
#else
	/* Process in 32-bit chunks if the buffer is aligned. */
	uint32		maskv = ~((uint32) 0) / 0xFF * mask;

	if (buf == (const char *) TYPEALIGN(4, buf))
	{
		const uint32 *words = (const uint32 *) buf;

		while (bytes >= 4)
		{
			popcnt += pg_popcount32_slow(*words++ & maskv);
			bytes -= 4;
		}

		buf = (const char *) words;
	}
#endif

	/* Process any remaining bytes */
	while (bytes--)
		popcnt += pg_number_of_ones[(unsigned char) *buf++ & mask];

	return popcnt;
}


int
pg_popcount32(uint32 word)
{
	return pg_popcount32_slow(word);
}

int
pg_popcount64(uint64 word)
{
	return pg_popcount64_slow(word);
}


/*
 * pg_popcount_optimized
 *		Returns the number of 1-bits in buf
 */
uint64
pg_popcount_optimized(const char *buf, int bytes)
{
	return pg_popcount_slow(buf, bytes);
}

/*
 * pg_popcount_masked_optimized
 *		Returns the number of 1-bits in buf after applying the mask to each byte
 */
uint64
pg_popcount_masked_optimized(const char *buf, int bytes, bits8 mask)
{
	return pg_popcount_masked_slow(buf, bytes, mask);
}


extern uint64 pg_popcount_optimized(const char *buf, int bytes);
extern uint64 pg_popcount_masked_optimized(const char *buf, int bytes, bits8 mask);

#endif							/* TRY_POPCNT_FAST */

/*
 * Returns the number of 1-bits in buf.
 *
 * If there aren't many bytes to process, the function call overhead of the
 * optimized versions isn't worth taking, so we inline a loop that consults
 * pg_number_of_ones in that case.  If there are many bytes to process, we
 * accept the function call overhead because the optimized versions are likely
 * to be faster.
 */
static inline uint64
pg_popcount(const char *buf, int bytes)
{
	/*
	 * We set the threshold to the point at which we'll first use special
	 * instructions in the optimized version.
	 */
#if SIZEOF_VOID_P >= 8
	int			threshold = 8;
#else
	int			threshold = 4;
#endif

	if (bytes < threshold)
	{
		uint64		popcnt = 0;

		while (bytes--)
			popcnt += pg_number_of_ones[(unsigned char) *buf++];
		return popcnt;
	}

	return pg_popcount_optimized(buf, bytes);
}

/*
 * Returns the number of 1-bits in buf after applying the mask to each byte.
 *
 * Similar to pg_popcount(), we only take on the function pointer overhead when
 * it's likely to be faster.
 */
static inline uint64
pg_popcount_masked(const char *buf, int bytes, bits8 mask)
{
	/*
	 * We set the threshold to the point at which we'll first use special
	 * instructions in the optimized version.
	 */
#if SIZEOF_VOID_P >= 8
	int			threshold = 8;
#else
	int			threshold = 4;
#endif

	if (bytes < threshold)
	{
		uint64		popcnt = 0;

		while (bytes--)
			popcnt += pg_number_of_ones[(unsigned char) *buf++ & mask];
		return popcnt;
	}

	return pg_popcount_masked_optimized(buf, bytes, mask);
}

/*
 * Rotate the bits of "word" to the right/left by n bits.
 */
static inline uint32
pg_rotate_right32(uint32 word, int n)
{
	return (word >> n) | (word << (32 - n));
}

static inline uint32
pg_rotate_left32(uint32 word, int n)
{
	return (word << n) | (word >> (32 - n));
}

/* size_t variants of the above, as required */

#if SIZEOF_SIZE_T == 4
#define pg_leftmost_one_pos_size_t pg_leftmost_one_pos32
#define pg_nextpower2_size_t pg_nextpower2_32
#define pg_prevpower2_size_t pg_prevpower2_32
#else
#define pg_leftmost_one_pos_size_t pg_leftmost_one_pos64
#define pg_nextpower2_size_t pg_nextpower2_64
#define pg_prevpower2_size_t pg_prevpower2_64
#endif

#endif							/* PG_BITUTILS_H */

void test_pg_popcount32() {
    uint32_t test_value = 0b11010110;  // binary: 11010110, expected popcount: 5
    int expected = 5;
    int result = pg_popcount32(test_value);
    if (result == expected) {
        printf("Test passed: pg_popcount32(%u) = %d\n", test_value, result);
        Assert(5, result);
    } else {
        printf("Test failed: pg_popcount32(%u) = %d, expected %d\n", test_value, result, expected);
    }
}

int main() {
    test_pg_popcount32();
    return 0;
}
