#include <stdint.h>

typedef uintptr_t Datum;
/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 0
#define SIZEOF_DATUM SIZEOF_VOID_P
#define BITS_PER_BYTE		8

#define NUMERIC_ABBREV_BITS (SIZEOF_DATUM * BITS_PER_BYTE)



#if NUMERIC_ABBREV_BITS == 64

static Datum
numeric_abbrev_convert_var(const NumericVar *var, NumericSortSupport *nss)
{
	int			ndigits = var->ndigits;
	int			weight = var->weight;
	int64		result;

	if (ndigits == 0 || weight < -44)
	{
		result = 0;
	}
	else if (weight > 83)
	{
		result = PG_INT64_MAX;
	}
	else
	{
		result = ((int64) (weight + 44) << 56);

		switch (ndigits)
		{
			default:
				result |= ((int64) var->digits[3]);
				/* FALLTHROUGH */
			case 3:
				result |= ((int64) var->digits[2]) << 14;
				/* FALLTHROUGH */
			case 2:
				result |= ((int64) var->digits[1]) << 28;
				/* FALLTHROUGH */
			case 1:
				result |= ((int64) var->digits[0]) << 42;
				break;
		}
	}

	/* the abbrev is negated relative to the original */
	if (var->sign == NUMERIC_POS)
		result = -result;

	if (nss->estimating)
	{
		uint32		tmp = ((uint32) result
						   ^ (uint32) ((uint64) result >> 32));

		addHyperLogLog(&nss->abbr_card, DatumGetUInt32(hash_uint32(tmp)));
	}

	return NumericAbbrevGetDatum(result);
}

#endif							/* NUMERIC_ABBREV_BITS == 64 */

#if NUMERIC_ABBREV_BITS == 32

static Datum
numeric_abbrev_convert_var(const NumericVar *var, NumericSortSupport *nss)
{
	int			ndigits = var->ndigits;
	int			weight = var->weight;
	int32		result;

	if (ndigits == 0 || weight < -11)
	{
		result = 0;
	}
	else if (weight > 20)
	{
		result = PG_INT32_MAX;
	}
	else
	{
		NumericDigit nxt1 = (ndigits > 1) ? var->digits[1] : 0;

		weight = (weight + 11) * 4;

		result = var->digits[0];

		/*
		 * "result" now has 1 to 4 nonzero decimal digits. We pack in more
		 * digits to make 7 in total (largest we can fit in 24 bits)
		 */

		if (result > 999)
		{
			/* already have 4 digits, add 3 more */
			result = (result * 1000) + (nxt1 / 10);
			weight += 3;
		}
		else if (result > 99)
		{
			/* already have 3 digits, add 4 more */
			result = (result * 10000) + nxt1;
			weight += 2;
		}
		else if (result > 9)
		{
			NumericDigit nxt2 = (ndigits > 2) ? var->digits[2] : 0;

			/* already have 2 digits, add 5 more */
			result = (result * 100000) + (nxt1 * 10) + (nxt2 / 1000);
			weight += 1;
		}
		else
		{
			NumericDigit nxt2 = (ndigits > 2) ? var->digits[2] : 0;

			/* already have 1 digit, add 6 more */
			result = (result * 1000000) + (nxt1 * 100) + (nxt2 / 100);
		}

		result = result | (weight << 24);
	}

	/* the abbrev is negated relative to the original */
	if (var->sign == NUMERIC_POS)
		result = -result;

	if (nss->estimating)
	{
		uint32		tmp = (uint32) result;

		addHyperLogLog(&nss->abbr_card, DatumGetUInt32(hash_uint32(tmp)));
	}

	return NumericAbbrevGetDatum(result);
}

#endif							/* NUMERIC_ABBREV_BITS == 32 */
