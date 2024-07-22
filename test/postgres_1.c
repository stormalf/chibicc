#include <stdio.h>
#define PG_PRINTF_ATTRIBUTE printf
#if defined(__GNUC__) || defined(__IBMC__)
#define pg_attribute_format_arg(a) __attribute__((format_arg(a)))
#define pg_attribute_printf(f,a) __attribute__((format(PG_PRINTF_ATTRIBUTE, f, a)))
#else
#define pg_attribute_format_arg(a)
#define pg_attribute_printf(f,a)
#endif

#define BLCKSZ 8192
typedef long int int64;
#define PG_IO_ALIGN_SIZE		4096

typedef union PGIOAlignedBlock
{
#ifdef pg_attribute_aligned
	pg_attribute_aligned(PG_IO_ALIGN_SIZE)
#endif
	char		data[BLCKSZ];
	double		force_align_d;
	int64		force_align_i64;
} PGIOAlignedBlock;

typedef union PGAlignedBlock
{
	char		data[BLCKSZ];
	double		force_align_d;
	int64		force_align_i64;
} PGAlignedBlock;


int main(void)
{
    PGAlignedBlock block;
    printf("%ld\n", sizeof(block));
    PGIOAlignedBlock ioblock;
    printf("%ld\n", sizeof(ioblock));
    return 0;
}