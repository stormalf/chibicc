#ifndef __STDDEF_H
#define __STDDEF_H

#define NULL ((void *)0)

typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef unsigned int wchar_t;
typedef long max_align_t;
typedef float _Float32;
typedef double _Float64;
typedef long double _Float128;
typedef _Float32 _Float32x;
typedef _Float64 _Float64x;
typedef _Float128 _Float128x;
#define offsetof(type, member) ((size_t)&(((type *)0)->member))

#endif