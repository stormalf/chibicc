#ifndef __STDDEF_H
#define __STDDEF_H

#define NULL ((void *)0)

typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef unsigned int wchar_t;
typedef long max_align_t;


// #  define INTPTR_MIN		(-9223372036854775807L-1)
// #  define INTPTR_MAX		(9223372036854775807L)
// #  define UINTPTR_MAX		(18446744073709551615UL)
// #  define PTRDIFF_MIN		(-9223372036854775807L-1)
// #  define PTRDIFF_MAX		(9223372036854775807L)
// #  define SIZE_MAX		(18446744073709551615UL)
// #  define INTMAX_MIN		(-9223372036854775807L-1)
// #  define INTMAX_MAX		(9223372036854775807L)
// #  define UINTMAX_MAX		(18446744073709551615UL)
//  #define __INTPTR_TYPE__ long int 
//  #define __UINTPTR_TYPE__ long unsigned int 
//  #define __UINT32_TYPE__ unsigned int
// #define __INT_LEAST32_TYPE__ __INT32_TYPE__
// #define __UINT_LEAST32_TYPE__ __UINT32_TYPE__
// #define __INT64_TYPE__ long long int
// #define __UINT64_TYPE__ unsigned long long int
// #define 	INTPTR_MIN   (-__INTPTR_MAX__-1)
// #define 	INTPTR_MAX   __INTPTR_MAX__
// #define 	UINTPTR_MAX   __UINTPTR_MAX__
// #define 	PTRDIFF_MIN   (-__PTRDIFF_MAX__-1)
// #define 	PTRDIFF_MAX   __PTRDIFF_MAX__
// #define 	SIZE_MAX   __SIZE_MAX__
// #define 	INTMAX_MIN   (-__INTMAX_MAX__-1)
// #define 	INTMAX_MAX   __INTMAX_MAX__
// #define 	UINTMAX_MAX   __UINTMAX_MAX__

#define offsetof(type, member) ((size_t)&(((type *)0)->member))
//#define static_assert(x, msg) extern char STATIC_MSG(msg, __LINE__) [(x)?1:-1]
// #ifndef _Static_assert
#define CONCAT_(prefix, suffix) prefix##suffix
/// Concatenate `prefix, suffix` into `prefixsuffix`
#define CONCAT(prefix, suffix) CONCAT_(prefix, suffix)
#define MAKE_UNIQUE_VARIABLE_NAME(prefix) CONCAT(prefix##_, __LINE__)
//#define static_assert(x, msg) extern char STATIC_MSG(msg, __LINE__) [(x)?1:-1]
//#define _Static_assert static_assert
//#define static_assert(x, msg) _Static_assert(x, msg)
// #define _Static_assert STATIC_ASSERT
// #define StaticAssertDecl STATIC_ASSERT
// #define Assert STATIC_ASSERT
// #define STATIC_ASSERT(COND,MSG) static int MAKE_UNIQUE_VARIABLE_NAME(prefix)[(COND)?1:-1]
// #define STATIC_ASSERT(COND) static int MAKE_UNIQUE_VARIABLE_NAME(prefix)[(COND)?1:-1]
// #define STATIC_ASSERT(...) 

// #endif /* _Static_assert */

#endif
