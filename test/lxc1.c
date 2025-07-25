
#include <unistd.h>
#include "test.h"
/* Container's specific file/directory names */
#define LXC_CONFIG_FNAME      "config"
#define LXC_PARTIAL_FNAME     "partial"
#define LXC_ROOTFS_DNAME      "rootfs"
#define LXC_TIMESTAMP_FNAME   "ts"
#define LXC_COMMENT_FNAME     "comment"

#define ARRAY_SIZE(x)                                                        \
	(__builtin_choose_expr(!__builtin_types_compatible_p(typeof(x),      \
							     typeof(&*(x))), \
			       sizeof(x) / sizeof((x)[0]), ((void)0)))


int main(int argc, char *argv[])
{
    int std_fds[] = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
    printf("ARRAY_SIZE(std_fds) = %ld\n", ARRAY_SIZE(std_fds));
	ASSERT(3, ARRAY_SIZE(std_fds));
	return 0;
}