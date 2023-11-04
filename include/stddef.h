#ifndef __STDDEF_H
#define __STDDEF_H

#define NULL ((void *)0)

typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef unsigned int wchar_t;
typedef long max_align_t;

#define offsetof(type, member) ((size_t)&(((type *)0)->member))

#ifndef _Static_assert
#define CONCAT_(prefix, suffix) prefix##suffix
/// Concatenate `prefix, suffix` into `prefixsuffix`
#define CONCAT(prefix, suffix) CONCAT_(prefix, suffix)
#define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)

#define _Static_assert STATIC_ASSERT
#define STATIC_ASSERT(COND,MSG) static int MAKE_UNIQUE_VARIABLE_NAME(prefix)[(COND)?1:-1]
#define STATIC_ASSERT(COND) static int MAKE_UNIQUE_VARIABLE_NAME(prefix)[(COND)?1:-1]
#define STATIC_ASSERT(...) 

#endif /* _Static_assert */

#endif
