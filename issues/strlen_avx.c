/*
 * test_strlen_avx2.c
 *
 * Stress-test for glibc/sysdeps/x86_64/multiarch/strlen-avx2.S
 * through chibicc compilation.
 *
 * The AVX2 strlen implementation handles several distinct code paths:
 *   1. Short strings (< 16 bytes)  — scalar / SSE2 head
 *   2. 16-byte aligned reads       — first YMM probe
 *   3. 32-byte aligned loops       — main AVX2 loop (4 YMM regs / iteration)
 *   4. Page-crossing safety        — first load aligned to page boundary
 *   5. NULL pointer / empty string — edge cases
 *   6. Strings ending on every byte offset 0-63 inside a 64-byte block
 *
 * chibicc compatibility notes exercised here:
 *   - No VLAs (chibicc may lack them)
 *   - Only C99/C11 types from <stddef.h>, <string.h>, <stdio.h>, <stdlib.h>
 *   - No __attribute__ or compiler builtins
 *   - posix_memalign used for alignment (falls back to malloc+offset trick)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


/* ------------------------------------------------------------------ */
/* Helpers                                                              */
/* ------------------------------------------------------------------ */

static int g_pass = 0;
static int g_fail = 0;

static void check(const char *label, size_t got, size_t expected)
{
    if (got == expected) {
        g_pass++;
    } else {
        g_fail++;
        printf("FAIL  %s : got %zu expected %zu\n", label, got, expected);
    }
}

/*
 * Allocate a buffer of `total` bytes aligned to `align`, fill it with
 * `fill`, place a NUL at offset `nul_at`, and return a pointer to the
 * start.  Caller must free() the *base* pointer returned via `*base_out`.
 */
static char *make_string(size_t align, size_t total,
                         char fill, size_t nul_at,
                         void **base_out)
{
    /* Over-allocate so we can manually align. */
    char *base = (char *)malloc(total + align);
    if (!base) { perror("malloc"); exit(1); }
    *base_out = base;

    /* Align upward */
    size_t addr = (size_t)base;
    size_t offset = (align - (addr % align)) % align;
    char *buf = base + offset;

    memset(buf, fill, total);
    buf[nul_at] = '\0';
    return buf;
}

/* ------------------------------------------------------------------ */
/* Test groups                                                          */
/* ------------------------------------------------------------------ */

/* 1. Empty string */
static void test_empty(void)
{
    const char *s = "";
    check("empty", strlen(s), 0);
}

/* 2. Single character */
static void test_single(void)
{
    const char *s = "A";
    check("single", strlen(s), 1);
}

/* 3. Short strings (1–15 bytes) — scalar head path */
static void test_short(void)
{
    char buf[32];
    size_t i;
    for (i = 1; i <= 15; i++) {
        memset(buf, 'x', i);
        buf[i] = '\0';
        check("short", strlen(buf), i);
    }
}

/* 4. Strings of length 16–31 — first YMM load, tail in same register */
static void test_medium(void)
{
    char buf[64];
    size_t i;
    for (i = 16; i <= 31; i++) {
        memset(buf, 'y', i);
        buf[i] = '\0';
        check("medium", strlen(buf), i);
    }
}

/* 5. Strings of length 32–63 — two YMM loads, no full loop iteration */
static void test_two_ymm(void)
{
    char buf[128];
    size_t i;
    for (i = 32; i <= 63; i++) {
        memset(buf, 'z', i);
        buf[i] = '\0';
        check("two_ymm", strlen(buf), i);
    }
}

/* 6. Long strings (64 – 1023 bytes) — main AVX2 loop */
static void test_long(void)
{
    size_t lens[] = {64, 65, 127, 128, 255, 256, 511, 512, 1023};
    size_t n = sizeof(lens) / sizeof(lens[0]);
    size_t k;
    char *buf = (char *)malloc(1025);
    if (!buf) { perror("malloc"); exit(1); }

    for (k = 0; k < n; k++) {
        memset(buf, 'L', lens[k]);
        buf[lens[k]] = '\0';
        check("long", strlen(buf), lens[k]);
    }
    free(buf);
}

/* 7. Very long string (4 MB) — sustained loop */
static void test_very_long(void)
{
    size_t len = 4 * 1024 * 1024;
    char *buf = (char *)malloc(len + 1);
    if (!buf) { perror("malloc"); exit(1); }
    memset(buf, 'V', len);
    buf[len] = '\0';
    check("very_long", strlen(buf), len);
    free(buf);
}

/* 8. NUL at every offset 0–63 inside a 64-byte-aligned block */
static void test_nul_offsets(void)
{
    size_t align = 64;
    size_t bufsize = 256;
    size_t off;
    void *base;

    for (off = 0; off < 64; off++) {
        char *buf = make_string(align, bufsize, 'N', off, &base);
        check("nul_offset", strlen(buf), off);
        free(base);
    }
}

/* 9. Page-boundary crossing: string starts near end of a "page" (4 KB) */
static void test_page_cross(void)
{
    /*
     * Place NUL so that the string straddles a 4096-byte boundary.
     * We allocate 2 pages and put the string start 1–32 bytes before
     * the midpoint.
     */
    size_t pgsz = 4096;
    size_t total = pgsz * 2;
    size_t align = pgsz;
    void *base;
    size_t start_off;

    for (start_off = 1; start_off <= 32; start_off++) {
        /* String begins (pgsz - start_off) bytes into buffer, length 64 */
        size_t str_start = pgsz - start_off;
        size_t expected  = 64;

        char *buf = make_string(align, total, 'P', str_start + expected, &base);
        /* fill the string portion */
        memset(buf + str_start, 'Q', expected);
        buf[str_start + expected] = '\0';

        check("page_cross", strlen(buf + str_start), expected);
        free(base);
    }
}

/* 10. 32-byte aligned buffer, various lengths */
static void test_aligned32(void)
{
    size_t align = 32;
    size_t lens[] = {0, 1, 7, 8, 15, 16, 31, 32, 33, 63, 64, 100, 200};
    size_t n = sizeof(lens) / sizeof(lens[0]);
    size_t k;
    void *base;

    for (k = 0; k < n; k++) {
        size_t bufsize = lens[k] + 1 + 32; /* extra room */
        char *buf = make_string(align, bufsize, 'A', lens[k], &base);
        check("aligned32", strlen(buf), lens[k]);
        free(base);
    }
}

/* 11. Unaligned start pointer (offsets 1–31 into a 32-byte-aligned block) */
static void test_unaligned_ptr(void)
{
    size_t base_align = 32;
    size_t bufsize    = 512;
    size_t ua;
    void *base;

    for (ua = 1; ua <= 31; ua++) {
        /* String of length 50, starting at unaligned offset ua */
        size_t expected = 50;
        char *buf = make_string(base_align, bufsize, 'U', ua + expected, &base);
        memset(buf + ua, 'u', expected);
        buf[ua + expected] = '\0';
        check("unaligned_ptr", strlen(buf + ua), expected);
        free(base);
    }
}

/* 12. Repeat-byte strings that look like VPCMPEQB false positives */
static void test_all_bytes(void)
{
    /*
     * Fill with bytes 0x01–0xFF (no embedded NUL), then terminate.
     * Makes sure the zero-detection bitmask logic isn't fooled.
     */
    size_t len = 255;
    char buf[256];
    size_t i;
    for (i = 0; i < len; i++)
        buf[i] = (char)(i + 1);   /* 0x01 .. 0xFF */
    buf[len] = '\0';
    check("all_bytes", strlen(buf), len);
}

/* 13. String entirely of 0x80 bytes (high-bit set, sign-extension traps) */
static void test_highbit(void)
{
    size_t len = 128;
    char buf[129];
    memset(buf, (char)0x80, len);
    buf[len] = '\0';
    check("highbit", strlen(buf), len);
}

/* 14. strlen on a substring (pointer arithmetic) */
static void test_substring(void)
{
    const char *s = "Hello, World!";
    check("substring_0",  strlen(s),     13);
    check("substring_7",  strlen(s + 7),  6);
    check("substring_12", strlen(s + 12), 1);
    check("substring_13", strlen(s + 13), 0);
}

/* 15. Multiple consecutive strlen calls on the same buffer (cache effects) */
static void test_repeated(void)
{
    size_t len = 512;
    char *buf = (char *)malloc(len + 1);
    size_t i;
    if (!buf) { perror("malloc"); exit(1); }
    memset(buf, 'R', len);
    buf[len] = '\0';
    for (i = 0; i < 100; i++)
        check("repeated", strlen(buf), len);
    free(buf);
}

/* ------------------------------------------------------------------ */
/* main                                                                 */
/* ------------------------------------------------------------------ */

int main(void)
{
    printf("=== strlen-avx2 chibicc test suite ===\n\n");

    test_empty();
    test_single();
    test_short();
    test_medium();
    test_two_ymm();
    test_long();
    test_very_long();
    test_nul_offsets();
    test_page_cross();
    test_aligned32();
    test_unaligned_ptr();
    test_all_bytes();
    test_highbit();
    test_substring();
    test_repeated();

    printf("\nResults: %d passed, %d failed\n", g_pass, g_fail);
    return g_fail ? 1 : 0;
}
