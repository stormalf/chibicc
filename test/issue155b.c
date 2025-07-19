#include <stdbool.h>
#include <asm-generic/int-ll64.h>
#include <errno.h>

#include "test.h"
static inline int lxc_caps_down(void)
{
	return 0;
}

static inline int lxc_caps_up(void)
{
	return 0;
}

static inline int lxc_ambient_caps_up(void)
{
	return 0;
}

static inline int lxc_ambient_caps_down(void)
{
	return 0;
}

static inline int lxc_caps_init(void)
{
	return 0;
}

static inline int lxc_caps_last_cap(__u32 *cap)
{
	return -1;
}

typedef int cap_value_t;
typedef int cap_flag_t;
static inline bool lxc_proc_cap_is_set(cap_value_t cap, cap_flag_t flag)
{
	return false;
}

static inline bool lxc_file_cap_is_set(const char *path, cap_value_t cap,
				       cap_flag_t flag)
{
	return false;
}


#define lxc_priv(__lxc_function)                          \
	({                                                \
		__label__ out;                            \
		int __ret, __ret2, ___errno = 0;          \
		__ret = lxc_caps_up();                    \
		if (__ret)                                \
			goto out;                         \
		__ret = __lxc_function;                   \
		if (__ret)                                \
			___errno = errno;                 \
		__ret2 = lxc_caps_down();                 \
	out:                                              \
		__ret ? errno = ___errno, __ret : __ret2; \
	})

#define lxc_unpriv(__lxc_function)                        \
	({                                                \
		__label__ out;                            \
		int __ret, __ret2, ___errno = 0;          \
		__ret = lxc_caps_down();                  \
		if (__ret)                                \
			goto out;                         \
		__ret = __lxc_function;                   \
		if (__ret)                                \
			___errno = errno;                 \
		__ret2 = lxc_caps_up();                   \
	out:                                              \
		__ret ? errno = ___errno, __ret : __ret2; \
	})



int main()
{
    int a = lxc_unpriv(lxc_caps_up());
	printf("%d\n", a);
	ASSERT(0, a);
    return 0;
}
