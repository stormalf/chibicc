#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BLCKSZ 8192
typedef long int int64;
#define PG_IO_ALIGN_SIZE		4096
#define pg_attribute_aligned(a) __attribute__((aligned(a)))

typedef union PGIOAlignedBlock
{
#ifdef pg_attribute_aligned
	pg_attribute_aligned(PG_IO_ALIGN_SIZE)
#endif
	char		data[BLCKSZ];
	double		force_align_d;
	int64		force_align_i64;
} PGIOAlignedBlock;



ssize_t
pg_pwrite_zeros(int fd, size_t size, off_t offset)
{
	static const PGIOAlignedBlock zbuffer = {{0}};	/* worth BLCKSZ */
	//void	   *zerobuf_addr = unconstify(PGIOAlignedBlock *, &zbuffer)->data;
	//struct iovec iov[PG_IOV_MAX];
	size_t		remaining_size = size;
	ssize_t		total_written = 0;

	// /* Loop, writing as many blocks as we can for each system call. */
	// while (remaining_size > 0)
	// {
	// 	int			iovcnt = 0;
	// 	ssize_t		written;

		// for (; iovcnt < PG_IOV_MAX && remaining_size > 0; iovcnt++)
		// {
		// 	size_t		this_iov_size;

		// 	iov[iovcnt].iov_base = zerobuf_addr;

		// 	if (remaining_size < BLCKSZ)
		// 		this_iov_size = remaining_size;
		// 	else
		// 		this_iov_size = BLCKSZ;

		// 	iov[iovcnt].iov_len = this_iov_size;
		// 	remaining_size -= this_iov_size;
		// }

	// 	written = pg_pwritev_with_retry(fd, iov, iovcnt, offset);

	// 	if (written < 0)
	// 		return written;

	// 	offset += written;
	// 	total_written += written;
	// }

	// Assert(total_written == size);

	return total_written;
}

int main() {
    off_t offset = 1;
    ssize_t size = 1;
    int fd = 0;
    ssize_t res = pg_pwrite_zeros(fd, size, offset);
    printf("res = %ld\n", res);
    return 0;
}