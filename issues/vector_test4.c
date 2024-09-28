#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <xmmintrin.h>
/* Define the default attributes for the functions in this file. */
// #define __DEFAULT_FN_ATTRS __attribute__((__always_inline__, __nodebug__, __target__("sse"), __min_vector_width__(128)))
// #define __DEFAULT_FN_ATTRS_MMX __attribute__((__always_inline__, __nodebug__, __target__("mmx,sse"), __min_vector_width__(64)))

// typedef int __v4si __attribute__((__vector_size__(16)));
// typedef float __v4sf __attribute__((__vector_size__(16)));
// typedef float __m128 __attribute__((__vector_size__(16), __aligned__(16)));
// typedef float __m128_u __attribute__((__vector_size__(16), __aligned__(1)));

// static __inline__ __m128 __DEFAULT_FN_ATTRS
// _mm_add_ss(__m128 __a, __m128 __b)
// {
//   __a[0] += __b[0];
//   return __a;
// }

// static __inline__ __m128 __DEFAULT_FN_ATTRS
// _mm_add_ps(__m128 __a, __m128 __b)
// {
//   return (__m128)((__v4sf)__a + (__v4sf)__b);
// }

/* SSE2 */
// typedef double __v2df __attribute__ ((__vector_size__ (16)));
// typedef long long __v2di __attribute__ ((__vector_size__ (16)));
// typedef unsigned long long __v2du __attribute__ ((__vector_size__ (16)));
// typedef int __v4si __attribute__ ((__vector_size__ (16)));
// typedef unsigned int __v4su __attribute__ ((__vector_size__ (16)));
// typedef short __v8hi __attribute__ ((__vector_size__ (16)));
// typedef unsigned short __v8hu __attribute__ ((__vector_size__ (16)));
// typedef char __v16qi __attribute__ ((__vector_size__ (16)));
// typedef signed char __v16qs __attribute__ ((__vector_size__ (16)));
// typedef unsigned char __v16qu __attribute__ ((__vector_size__ (16)));



// // Function prototype
// uint32_t pg_comp_crc32c_sse42(uint32_t crc, const void *data, size_t len);


// // Function implementation
// uint32_t pg_comp_crc32c_sse42(uint32_t crc, const void *data, size_t len) {
//     const unsigned char *p = data;
//     const unsigned char *pend = p + len;

// #ifdef __x86_64__
//     while (p + 8 <= pend) {
//         crc = (uint32_t) _mm_crc32_u64(crc, *((const uint64_t *) p));
//         p += 8;
//     }

//     if (p + 4 <= pend) {
//         crc = _mm_crc32_u32(crc, *((const unsigned int *) p));
//         p += 4;
//     }
// #else
//     while (p + 4 <= pend) {
//         crc = _mm_crc32_u32(crc, *((const unsigned int *) p));
//         p += 4;
//     }
// #endif

//     while (p < pend) {
//         crc = _mm_crc32_u8(crc, *p);
//         p++;
//     }

//     return crc;
// }


int main() {
    // Example data
    const char data[] = "This is a test string for CRC32C!";
    size_t tmplength = sizeof(data);
    size_t length = sizeof(data) - 1; // Exclude the null terminator
    printf("length = %ld templength=%ld\n", length, tmplength);

    // // Initial CRC value
    // uint32_t crc = 0;

    // // Compute CRC
    // crc = pg_comp_crc32c_sse42(crc, data, length);

    // // Print the result
    // printf("CRC32C: %08X\n", crc);

    return 0;
}
