/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set et ft=c ts=2 sts=2 sw=2 fenc=utf-8                               :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
//#include "test.h"
#include <string.h>
#include <stdio.h>
typedef float float4a1 __attribute__((__vector_size__(16), __aligned__(1)));
typedef double __v2df __attribute__ ((__vector_size__ (16)));
typedef long long __v2di __attribute__ ((__vector_size__ (16)));
typedef unsigned int __v4su __attribute__ ((__vector_size__ (16)));
typedef short __v8hi __attribute__ ((__vector_size__ (16)));
typedef unsigned short __v8hu __attribute__ ((__vector_size__ (16)));
typedef char __v16qi __attribute__ ((__vector_size__ (16)));
typedef signed char __v16qs __attribute__ ((__vector_size__ (16)));
typedef unsigned char __v16qu __attribute__ ((__vector_size__ (16)));


typedef float float4 __attribute__((__vector_size__(16)));
typedef float float4a16 __attribute__((__vector_size__(16), __aligned__(16)));
typedef char byte16 __attribute__((__vector_size__(16)));
typedef unsigned char ubyte16 __attribute__((__vector_size__(16)));
typedef double double2 __attribute__((__vector_size__(16)));
typedef double double2a1 __attribute__((__vector_size__(16), __aligned__(1)));
typedef double double2a16 __attribute__((__vector_size__(16), __aligned__(16)));
/* SSE2 */
typedef long long __v2di __attribute__ ((__vector_size__ (16)));
typedef unsigned long long __v2du __attribute__ ((__vector_size__ (16)));
typedef int __v4si __attribute__ ((__vector_size__ (16)));

void process_vector(float4a1 vec) {
    for (int i = 0; i < 4; i++) {
        printf("vec[%d] = %f\n", i, vec[i]);
    }
}


int main(void) {
    printf("sizeof(float4) = %ld\n", sizeof(float4));
    printf("sizeof(float4a1) = %ld\n", sizeof(float4a1));
    printf("sizeof(float4a16) = %ld\n", sizeof(float4a16));
    printf("sizeof(double2) = %ld\n", sizeof(double2));
    printf("sizeof(double2) = %ld\n", sizeof(double2a1));
    printf("sizeof(double2) = %ld\n", sizeof(double2a16));
    printf(" _Alignof(float4) = %ld\n",  _Alignof(float4));
    printf(" _Alignof(float4a1) = %ld\n",  _Alignof(float4a1));
    printf(" _Alignof(float4a16) = %ld\n",  _Alignof(float4a16));
    printf(" _Alignof(double2) = %ld\n",  _Alignof(double2));
    printf(" _Alignof(double2a1) = %ld\n",  _Alignof(double2a1));
    printf(" _Alignof(double2a16) = %ld\n",  _Alignof(double2a16));
    printf(" _Alignof(double2) = %ld\n",  _Alignof(double2));
    
  ASSERT(16, sizeof(float4));
  ASSERT(16, sizeof(float4a1));
  ASSERT(16, sizeof(float4a16));
  ASSERT(16, sizeof(double2));
  ASSERT(16, sizeof(double2a1));
  ASSERT(16, sizeof(double2a16));
  ASSERT(16, _Alignof(float4));
  ASSERT(1, _Alignof(float4a1));
  ASSERT(16, _Alignof(float4a16));
  ASSERT(16, _Alignof(double2));
  ASSERT(1, _Alignof(double2a1));
  ASSERT(16, _Alignof(double2a16));


    float4 v1;
    float4 v2;
    float x[4] = {1, 2, 3, 4};
    float y[4] = {1, 1, 1, 1};
    printf("v1: %p, x: %p\n", (void*)&v1, (void*)x);
    memcpy(&v1, x, 16);
    memcpy(&v2, y, 16);
    //v1 = v1 + v2;
    process_vector(v1);
    memcpy(x, &v1, 16);
    ASSERT(2, x[0]);
    // TODO(jart): fix me
    ASSERT(3, x[1]); 
    ASSERT(4, x[2]); 
    ASSERT(5, x[3]); 
    float4a1 v3 = {12, 2, 3, 14};
    for (int i = 0; i < 4; i++) {
        printf("v3[%d] = %f\n", i, v3[i]);
    }
    process_vector(v3);

    byte16 v;
    float x1[4] = {1, 2, 3, 4};
    float x2[4];
    memcpy(&v, x1, 16);
    //__builtin_ia32_movntdq(x1, &v);
    memcpy(x2, &v, 16);
    ASSERT(1, x2[0]);
    // TODO(jart): fix me
    ASSERT(2, x[1]); 


  return 0;
}