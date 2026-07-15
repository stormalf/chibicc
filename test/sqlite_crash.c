/*
 * test_chibicc_funcptr.c
 *
 * Reproducer for chibicc miscompiling SQLite's aSyscall[] dispatch.
 *
 * HYPOTHESIS
 * ----------
 * Inside unixOpen (sqlite3.c ~47122), SQLite does NOT call vfs->xOpen
 * directly.  It calls OS functions through a global syscall-wrapper table:
 *
 *   static struct unix_syscall {
 *       const char *zName;
 *       sqlite3_syscall_ptr pCurrent;   // <-- function pointer
 *       sqlite3_syscall_ptr pDefault;
 *   } aSyscall[] = {
 *       { "open",   (sqlite3_syscall_ptr)open,   0 },
 *       ...
 *   };
 *   #define osOpen  ((int(*)(const char*,int,...))aSyscall[0].pCurrent)
 *
 * So every OS call inside unixOpen is a DOUBLE DEREFERENCE:
 *   1. load aSyscall[N].pCurrent  (pointer stored in a struct array)
 *   2. cast & call it
 *
 * chibicc is likely miscompiling the struct-array initializer, storing
 * the wrong value in pCurrent (e.g. the zName pointer instead of the
 * function pointer, or an off-by-one in the struct layout).
 *
 * This file reproduces that exact pattern in isolation.
 *
 * BUILD
 * -----
 *   # reference build – must PASS:
 *   gcc   -o test_chibicc_funcptr test_chibicc_funcptr.c && ./test_chibicc_funcptr
 *   clang -o test_chibicc_funcptr test_chibicc_funcptr.c && ./test_chibicc_funcptr
 *
 *   # chibicc build – expected to CRASH or print CORRUPT pointer:
 *   chibicc -o test_chibicc_funcptr test_chibicc_funcptr.c && ./test_chibicc_funcptr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

/* ------------------------------------------------------------------ */
/* Replicate SQLite's exact aSyscall pattern                           */
/* ------------------------------------------------------------------ */

/* SQLite typedef for the generic slot */
typedef void (*sqlite3_syscall_ptr)(void);

/* Mirror of sqlite3's unix_syscall struct (same field order) */
struct unix_syscall {
    const char        *zName;       /* offset 0  : 8 bytes (ptr)  */
    sqlite3_syscall_ptr pCurrent;   /* offset 8  : 8 bytes (fptr) */
    sqlite3_syscall_ptr pDefault;   /* offset 16 : 8 bytes (fptr) */
};

/*
 * Declare the real syscall wrappers we will put in the table.
 * We use actual libc functions so a bad pointer is immediately fatal.
 */
static int    wrap_open (const char *path, int flags, ...) { return open(path, flags, 0666); }
static int    wrap_close(int fd)                           { return close(fd); }
static int    wrap_stat (const char *path, struct stat *s) { return stat(path, s); }
static ssize_t wrap_read (int fd, void *buf, size_t n)     { return read(fd, buf, n); }
static ssize_t wrap_write(int fd, const void *buf, size_t n){ return write(fd, buf, n); }
static int    wrap_fstat(int fd, struct stat *s)           { return fstat(fd, s); }
static int    wrap_ftruncate(int fd, off_t len)            { return ftruncate(fd, len); }
static int    wrap_fcntl(int fd, int cmd, ...)             { return fcntl(fd, cmd); }
static int    wrap_unlink(const char *p)                   { return unlink(p); }

/*
 * The table — THIS is what chibicc miscompiles.
 *
 * SQLite initialises it with a compound literal / designated-initialiser
 * style in the amalgamation.  We use the simplest possible form so that
 * even a minimal compiler must get it right.
 *
 * Key danger: chibicc may store &zName (a char*) into pCurrent's slot
 * because both are pointer-sized and the struct layout confuses its
 * code-gen for array-of-struct initializers.
 */
static struct unix_syscall aSyscall[] = {
    /* index 0 */ { "open",      (sqlite3_syscall_ptr)wrap_open,      0 },
    /* index 1 */ { "close",     (sqlite3_syscall_ptr)wrap_close,     0 },
    /* index 2 */ { "stat",      (sqlite3_syscall_ptr)wrap_stat,      0 },
    /* index 3 */ { "read",      (sqlite3_syscall_ptr)wrap_read,      0 },
    /* index 4 */ { "write",     (sqlite3_syscall_ptr)wrap_write,     0 },
    /* index 5 */ { "fstat",     (sqlite3_syscall_ptr)wrap_fstat,     0 },
    /* index 6 */ { "ftruncate", (sqlite3_syscall_ptr)wrap_ftruncate, 0 },
    /* index 7 */ { "fcntl",     (sqlite3_syscall_ptr)wrap_fcntl,     0 },
    /* index 8 */ { "unlink",    (sqlite3_syscall_ptr)wrap_unlink,    0 },
};
#define NSYSCALL ((int)(sizeof(aSyscall)/sizeof(aSyscall[0])))

/* Convenience macros – exact pattern SQLite uses with osOpen etc. */
#define osOpen      ((int(*)(const char*,int,...))      aSyscall[0].pCurrent)
#define osClose     ((int(*)(int))                      aSyscall[1].pCurrent)
#define osStat      ((int(*)(const char*,struct stat*)) aSyscall[2].pCurrent)
#define osRead      ((ssize_t(*)(int,void*,size_t))     aSyscall[3].pCurrent)
#define osWrite     ((ssize_t(*)(int,const void*,size_t))aSyscall[4].pCurrent)
#define osFstat     ((int(*)(int,struct stat*))         aSyscall[5].pCurrent)
#define osFtruncate ((int(*)(int,off_t))                aSyscall[6].pCurrent)
#define osFcntl     ((int(*)(int,int,...))              aSyscall[7].pCurrent)
#define osUnlink    ((int(*)(const char*))              aSyscall[8].pCurrent)

/* ------------------------------------------------------------------ */
/* Step 1 – audit the table before calling anything                    */
/* ------------------------------------------------------------------ */
static int audit_table(void)
{
    int bad = 0;

    /* We'll compare stored pointers against the known-good addresses.   */
    sqlite3_syscall_ptr expected[] = {
        (sqlite3_syscall_ptr)wrap_open,
        (sqlite3_syscall_ptr)wrap_close,
        (sqlite3_syscall_ptr)wrap_stat,
        (sqlite3_syscall_ptr)wrap_read,
        (sqlite3_syscall_ptr)wrap_write,
        (sqlite3_syscall_ptr)wrap_fstat,
        (sqlite3_syscall_ptr)wrap_ftruncate,
        (sqlite3_syscall_ptr)wrap_fcntl,
        (sqlite3_syscall_ptr)wrap_unlink,
    };

    printf("\n--- aSyscall[] pointer audit ---\n");
    printf("%-12s  %-18s  %-18s  %s\n",
           "name", "expected", "actual pCurrent", "status");
    printf("%-12s  %-18s  %-18s  %s\n",
           "----", "--------", "---------------", "------");

    for (int i = 0; i < NSYSCALL; i++) {
        uintptr_t exp = (uintptr_t)expected[i];
        uintptr_t got = (uintptr_t)aSyscall[i].pCurrent;
        int ok = (exp == got);
        if (!ok) bad++;
        printf("%-12s  %#018lx  %#018lx  %s\n",
               aSyscall[i].zName, (unsigned long)exp, (unsigned long)got,
               ok ? "OK" : "*** CORRUPT ***");
    }
    return bad;
}

/* ------------------------------------------------------------------ */
/* Step 2 – actually call through the double-dereference               */
/*           (mirrors what unixOpen does at sqlite3.c:47122)           */
/* ------------------------------------------------------------------ */
static int exercise_calls(void)
{
    const char *path = "/tmp/chibicc_syscall_test.db";
    char buf[16] = {0};
    struct stat st;
    int fd, failures = 0;

    printf("\n--- double-dereference call exercise ---\n");

    /* osStat – index 2 */
    printf("[TEST] osStat(\"/tmp\") ... ");
    fflush(stdout);
    if (osStat("/tmp", &st) == 0) {
        printf("OK (size=%lld)\n", (long long)st.st_size);
    } else {
        printf("FAIL errno=%d\n", errno); failures++;
    }

    /* osOpen – index 0: the exact call that crashes in unixOpen */
    printf("[TEST] osOpen(\"%s\") ... ", path);
    fflush(stdout);
    fd = osOpen(path, O_RDWR | O_CREAT | O_TRUNC);
    if (fd < 0) {
        printf("FAIL errno=%d\n", errno); failures++;
        return failures;
    }
    printf("OK (fd=%d)\n", fd);

    /* osWrite – index 4 */
    printf("[TEST] osWrite() ... ");
    fflush(stdout);
    const char *msg = "chibicc";
    ssize_t nw = osWrite(fd, msg, strlen(msg));
    if (nw != (ssize_t)strlen(msg)) {
        printf("FAIL nw=%zd errno=%d\n", nw, errno); failures++;
    } else {
        printf("OK\n");
    }

    /* osFstat – index 5 */
    printf("[TEST] osFstat() ... ");
    fflush(stdout);
    if (osFstat(fd, &st) != 0) {
        printf("FAIL errno=%d\n", errno); failures++;
    } else {
        printf("OK (size=%lld)\n", (long long)st.st_size);
    }

    /* osFcntl – index 7 */
    printf("[TEST] osFcntl(F_GETFL) ... ");
    fflush(stdout);
    int flags = osFcntl(fd, F_GETFL);
    if (flags < 0) {
        printf("FAIL errno=%d\n", errno); failures++;
    } else {
        printf("OK (flags=0x%x)\n", flags);
    }

    /* osFtruncate – index 6 */
    printf("[TEST] osFtruncate(0) ... ");
    fflush(stdout);
    if (osFtruncate(fd, 0) != 0) {
        printf("FAIL errno=%d\n", errno); failures++;
    } else {
        printf("OK\n");
    }

    /* osRead – index 3 */
    printf("[TEST] osRead() ... ");
    fflush(stdout);
    lseek(fd, 0, SEEK_SET);
    ssize_t nr = osRead(fd, buf, sizeof(buf)-1);
    /* after truncate we expect 0 bytes, just check it doesn't crash */
    if (nr < 0) {
        printf("FAIL errno=%d\n", errno); failures++;
    } else {
        printf("OK (nr=%zd)\n", nr);
    }

    /* osClose – index 1 */
    printf("[TEST] osClose() ... ");
    fflush(stdout);
    if (osClose(fd) != 0) {
        printf("FAIL errno=%d\n", errno); failures++;
    } else {
        printf("OK\n");
    }

    /* osUnlink – index 8 */
    printf("[TEST] osUnlink() ... ");
    fflush(stdout);
    if (osUnlink(path) != 0) {
        printf("FAIL errno=%d\n", errno); failures++;
    } else {
        printf("OK\n");
    }

    return failures;
}

/* ------------------------------------------------------------------ */
/* Step 3 – stress the SAME pointer loaded in a loop                   */
/*           chibicc bugs sometimes only appear after N dereferences   */
/* ------------------------------------------------------------------ */
static int stress_loop(void)
{
    printf("\n--- stress: 1000x indirect calls via aSyscall[2].pCurrent ---\n");
    int (*fn)(const char*, struct stat*) =
        (int(*)(const char*, struct stat*))aSyscall[2].pCurrent;

    struct stat st;
    int failures = 0;
    for (int i = 0; i < 1000; i++) {
        /* reload through the table each iteration, same as SQLite macros */
        int (*fp)(const char*, struct stat*) =
            (int(*)(const char*, struct stat*))aSyscall[2].pCurrent;
        if (fp("/tmp", &st) != 0) {
            fprintf(stderr, "[FAIL] stress iteration %d\n", i);
            failures++;
            break;
        }
    }
    (void)fn;   /* suppress unused warning */
    if (!failures) printf("[PASS] 1000 iterations OK\n");
    return failures;
}

/* ------------------------------------------------------------------ */
/* main                                                                 */
/* ------------------------------------------------------------------ */
int main(void)
{
    int total = 0;

    printf("=== chibicc aSyscall double-dereference reproducer ===\n");

    int corrupt = audit_table();
    if (corrupt) {
        fprintf(stderr,
            "\n[!!!] %d corrupt pointer(s) detected in aSyscall[].\n"
            "      Calling through them will likely SIGSEGV — stopping here\n"
            "      so Valgrind / AddressSanitizer can report cleanly.\n",
            corrupt);
        return EXIT_FAILURE;
    }

    total += exercise_calls();
    total += stress_loop();

    printf("\n=== %s (%d failure(s)) ===\n",
           total == 0 ? "ALL PASS" : "FAILED", total);
    return total ? EXIT_FAILURE : EXIT_SUCCESS;
}
