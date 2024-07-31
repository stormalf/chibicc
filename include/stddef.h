#ifndef __STDDEF_H
#define __STDDEF_H

#define NULL ((void *)0)

typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef unsigned int wchar_t;
typedef long max_align_t;


#define __builtin_choose_expr(cond, true_expr, false_expr) (cond ? true_expr : false_expr)

#define offsetof(type, member) ((size_t)&(((type *)0)->member))
//#define static_assert(x, msg) extern char STATIC_MSG(msg, __LINE__) [(x)?1:-1]
// #ifndef _Static_assert
#define CONCAT_(prefix, suffix) prefix##suffix
/// Concatenate `prefix, suffix` into `prefixsuffix`
#define CONCAT(prefix, suffix) CONCAT_(prefix, suffix)
#define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)
//#define static_assert(x, msg) extern char STATIC_MSG(msg, __LINE__) [(x)?1:-1]
//#define _Static_assert static_assert
#define _Static_assert STATIC_ASSERT
#define StaticAssertDecl STATIC_ASSERT
#define Assert STATIC_ASSERT
#define STATIC_ASSERT(COND,MSG) static int MAKE_UNIQUE_VARIABLE_NAME(prefix)[(COND)?1:-1]
#define STATIC_ASSERT(COND) static int MAKE_UNIQUE_VARIABLE_NAME(prefix)[(COND)?1:-1]
#define STATIC_ASSERT(...) 

// #endif /* _Static_assert */

#endif
