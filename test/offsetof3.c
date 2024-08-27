#include <stdio.h>
#include <stdint.h>
#include <stddef.h>  // For offsetof
#include "test.h"
// Defining structures as per your request
typedef union
{
    struct // Normal varlena (4-byte length)
    {
        uint32_t va_header;
        char va_data[]; // Flexible array member
    } va_4byte;

    struct // Compressed-in-line format
    {
        uint32_t va_header;
        uint32_t va_tcinfo; // Original data size (excludes header) and compression method
        char va_data[];     // Compressed data
    } va_compressed;
} varattrib_4b;

typedef struct
{
    uint8_t va_header;
    char va_data[]; // Data begins here
} varattrib_1b;

// TOAST pointers are a subset of varattrib_1b with an identifying tag byte
typedef struct
{
    uint8_t va_header;  // Always 0x80 or 0x01
    uint8_t va_tag;     // Type of datum
    char va_data[];     // Type-specific data
} varattrib_1b_e;

// Macro definitions
#define VARHDRSZ_EXTERNAL offsetof(varattrib_1b_e, va_data)
#define VARHDRSZ_COMPRESSED offsetof(varattrib_4b, va_compressed.va_data)
#define VARHDRSZ_SHORT offsetof(varattrib_1b, va_data)

int main(void)
{
    // Print the calculated sizes using the macros
    printf("VARHDRSZ_EXTERNAL: %zu bytes\n", VARHDRSZ_EXTERNAL);
    printf("VARHDRSZ_COMPRESSED: %zu bytes\n", VARHDRSZ_COMPRESSED);
    printf("VARHDRSZ_SHORT: %zu bytes\n", VARHDRSZ_SHORT);
    ASSERT(2, VARHDRSZ_EXTERNAL);
    ASSERT(8, VARHDRSZ_COMPRESSED);
    ASSERT(1, VARHDRSZ_SHORT );

    return 0;
}
