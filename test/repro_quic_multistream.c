/*
 * quic_txp_timeout_repro.c
 *
 * Minimal reproducer for:
 *   ERROR: 'ossl_time_compare(ossl_time_now(), op_deadline) <= 0' failed
 *   "internal error (txp generate)"
 *   @ test/quic_multistream_test.c:1104
 *
 * Root cause hypothesis:
 *   chibicc miscompiles one or more of:
 *     (a) uint64_t arithmetic used in OSSL_TIME comparison
 *     (b) struct bitfield access in QUIC_TXPIM_PKT / OSSL_QUIC_FRAME_STREAM
 *     (c) multi-return / out-pointer pattern in ossl_quic_tx_packetiser_generate()
 *     (d) __attribute__((packed)) struct layout affecting frame serialization
 *
 * Build with chibicc:
 *   chibicc -o quic_txp_timeout_repro quic_txp_timeout_repro.c
 *
 * Build with gcc/clang for reference:
 *   gcc -o quic_txp_timeout_repro_ref quic_txp_timeout_repro.c && ./quic_txp_timeout_repro_ref
 *
 * Expected: all assertions pass, exit 0
 * Failure:  any assertion fails or the "txp generate" simulation returns an error
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* -----------------------------------------------------------------------
 * 1. OSSL_TIME emulation
 *    OpenSSL represents time as a uint64_t nanosecond count.
 *    ossl_time_compare() must return negative/zero/positive correctly.
 *    chibicc bug vector: uint64_t subtraction used as signed comparison.
 * ----------------------------------------------------------------------- */

typedef uint64_t OSSL_TIME;

#define OSSL_TIME_NS  UINT64_C(1)
#define OSSL_TIME_US  UINT64_C(1000)
#define OSSL_TIME_MS  UINT64_C(1000000)
#define OSSL_TIME_SEC UINT64_C(1000000000)

/* Mirrors the real ossl_time_compare():
 *   returns -1 if a < b, 0 if a == b, +1 if a > b
 * Potential chibicc issue: if the compiler sign-extends or truncates the
 * uint64_t difference when storing into an int, the compare is wrong. */
static int ossl_time_compare(OSSL_TIME a, OSSL_TIME b)
{
    if (a < b) return -1;
    if (a > b) return  1;
    return 0;
}

static OSSL_TIME ossl_time_now(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (OSSL_TIME)ts.tv_sec * OSSL_TIME_SEC
         + (OSSL_TIME)ts.tv_nsec * OSSL_TIME_NS;
}

static OSSL_TIME ossl_time_add(OSSL_TIME t, OSSL_TIME d) { return t + d; }

/* -----------------------------------------------------------------------
 * 2. QUIC frame structs with bitfields
 *    chibicc bug vector: bitfield read/write order or width truncation.
 *    OSSL_QUIC_FRAME_STREAM uses fin:1 and has_explicit_len:1 bitfields.
 * ----------------------------------------------------------------------- */

typedef struct {
    uint64_t stream_id;
    uint64_t offset;
    uint64_t len;
    unsigned int is_fin        : 1;   /* FIN bit */
    unsigned int has_data      : 1;   /* whether data pointer is valid */
    unsigned int    _pad       : 6;
    const unsigned char *data;
} OSSL_QUIC_FRAME_STREAM;

/* Verify bitfield layout is not corrupted by chibicc */
static int test_stream_frame_bitfields(void)
{
    OSSL_QUIC_FRAME_STREAM f;
    memset(&f, 0, sizeof(f));

    f.stream_id = 0xDEADBEEF01020304ULL;
    f.offset    = 0x0000000000001000ULL;
    f.len       = 512;
    f.is_fin    = 1;
    f.has_data  = 0;
    f.data      = NULL;

    if (f.stream_id != 0xDEADBEEF01020304ULL) {
        fprintf(stderr, "FAIL: stream_id corrupted: got 0x%llx\n",
                (unsigned long long)f.stream_id);
        return 0;
    }
    if (f.is_fin != 1) {
        fprintf(stderr, "FAIL: is_fin bitfield wrong: got %u\n", f.is_fin);
        return 0;
    }
    if (f.has_data != 0) {
        fprintf(stderr, "FAIL: has_data bitfield wrong: got %u\n", f.has_data);
        return 0;
    }

    /* Toggle — chibicc sometimes fails to isolate adjacent bitfields */
    f.is_fin   = 0;
    f.has_data = 1;
    if (f.is_fin != 0 || f.has_data != 1) {
        fprintf(stderr, "FAIL: bitfield toggle corrupted neighbours: "
                "is_fin=%u has_data=%u\n", f.is_fin, f.has_data);
        return 0;
    }

    printf("PASS: stream frame bitfields\n");
    return 1;
}

/* -----------------------------------------------------------------------
 * 3. TXP generate simulation
 *    The real ossl_quic_tx_packetiser_generate() returns a status code AND
 *    sets an output flag via a pointer.  chibicc bug vector: out-pointer
 *    write being optimised away or the return value path being wrong.
 * ----------------------------------------------------------------------- */

#define TXP_ERR_OK       0
#define TXP_ERR_INTERNAL 1   /* "internal error (txp generate)" */

typedef struct {
    int have_ack_eliciting; /* would produce ACK-eliciting packet */
    int generated;          /* a packet was actually generated    */
} TXP_STATUS;

/*
 * Simulate the TXP generate path.
 * Returns TXP_ERR_OK on success, TXP_ERR_INTERNAL on failure.
 * Writes result into *status.
 *
 * chibicc risk: if the compiler doesn't properly follow the pointer write
 * back to the caller, *status stays zero-initialised and the caller sees
 * generated=0, then sits in a spin-loop until the op_deadline expires.
 */
static int txp_generate(int should_succeed, TXP_STATUS *status)
{
    status->have_ack_eliciting = 1;

    if (!should_succeed) {
        /* This path corresponds to the "internal error (txp generate)" */
        status->generated = 0;
        return TXP_ERR_INTERNAL;
    }

    status->generated = 1;
    return TXP_ERR_OK;
}

static int test_txp_out_pointer(void)
{
    TXP_STATUS st;
    int rc;

    /* --- success path --- */
    memset(&st, 0, sizeof(st));
    rc = txp_generate(1, &st);
    if (rc != TXP_ERR_OK) {
        fprintf(stderr, "FAIL: txp_generate success path returned error %d\n", rc);
        return 0;
    }
    if (!st.generated) {
        fprintf(stderr, "FAIL: txp out-pointer 'generated' not set (chibicc write-back bug?)\n");
        return 0;
    }

    /* --- failure path --- */
    memset(&st, 0xFF, sizeof(st));  /* pre-poison */
    rc = txp_generate(0, &st);
    if (rc != TXP_ERR_INTERNAL) {
        fprintf(stderr, "FAIL: txp_generate failure path returned %d, want %d\n",
                rc, TXP_ERR_INTERNAL);
        return 0;
    }
    if (st.generated != 0) {
        fprintf(stderr, "FAIL: txp out-pointer 'generated' should be 0 on error, got %d\n",
                st.generated);
        return 0;
    }

    printf("PASS: txp out-pointer write-back\n");
    return 1;
}

/* -----------------------------------------------------------------------
 * 4. Deadline / spin-loop simulation
 *    Mirrors the multistream test op-runner at quic_multistream_test.c:1104.
 *    If ossl_time_compare() or ossl_time_now() are miscompiled the loop
 *    either never exits or exits immediately even when deadline hasn't passed.
 * ----------------------------------------------------------------------- */

#define OP_DEADLINE_MS 500   /* 500 ms — generous for CI */

static int test_deadline_compare(void)
{
    OSSL_TIME start    = ossl_time_now();
    OSSL_TIME deadline = ossl_time_add(start, 200 * OSSL_TIME_MS);

    /* Condition from quic_multistream_test.c:1104:
     *   ossl_time_compare(ossl_time_now(), op_deadline) <= 0
     * means: now <= deadline, i.e. we are still within the window.
     */
    int within = (ossl_time_compare(ossl_time_now(), deadline) <= 0);
    if (!within) {
        fprintf(stderr, "FAIL: deadline compare wrong immediately after creation "
                "(time arithmetic or compare bug)\n");
        return 0;
    }

    /* A deadline far in the past must be expired */
    OSSL_TIME past = ossl_time_add(start, 0) - 1000 * OSSL_TIME_SEC;
    /* Guard: only test if subtraction didn't underflow to a huge value */
    if (past < start) {
        int expired = (ossl_time_compare(ossl_time_now(), past) > 0);
        if (!expired) {
            fprintf(stderr, "FAIL: past deadline not detected as expired\n");
            return 0;
        }
    }

    printf("PASS: deadline time comparison\n");
    return 1;
}

/* -----------------------------------------------------------------------
 * 5. uint64_t wrap-around / large-value arithmetic
 *    chibicc bug vector: 64-bit immediate constants or 64-bit multiply
 *    being silently truncated to 32 bits.
 * ----------------------------------------------------------------------- */
static int test_u64_arithmetic(void)
{
    /* 5 seconds in nanoseconds — requires 64-bit representation */
    uint64_t five_sec = 5ULL * 1000000000ULL;
    if (five_sec != UINT64_C(5000000000)) {
        fprintf(stderr, "FAIL: uint64 5sec constant wrong: got %llu\n",
                (unsigned long long)five_sec);
        return 0;
    }

    /* Subtraction that would underflow in 32-bit */
    uint64_t a = UINT64_C(0x100000001);
    uint64_t b = UINT64_C(0x000000002);
    uint64_t diff = a - b;
    if (diff != UINT64_C(0x0FFFFFFFF)) {
        fprintf(stderr, "FAIL: uint64 subtraction wrong: got 0x%llx\n",
                (unsigned long long)diff);
        return 0;
    }

    /* Comparison that looks equal in 32-bit but differs in 64-bit */
    uint64_t x = UINT64_C(0x100000000);
    uint64_t y = UINT64_C(0x000000000);
    if (x == y) {
        fprintf(stderr, "FAIL: uint64 comparison truncated to 32 bits\n");
        return 0;
    }

    printf("PASS: uint64 arithmetic\n");
    return 1;
}

/* -----------------------------------------------------------------------
 * 6. __attribute__((packed)) struct — affects wire-format serialization
 *    chibicc bug vector: ignoring packed, producing wrong sizeof/offsets.
 * ----------------------------------------------------------------------- */

typedef struct __attribute__((packed)) {
    uint8_t  first_byte;   /* QUIC packet type + flags */
    uint32_t version;      /* QUIC version (big-endian on wire) */
    uint8_t  dcil;         /* destination connection ID length */
    uint8_t  scil;         /* source connection ID length */
} QuicLongHeader;

static int test_packed_struct(void)
{
    /* Without packed: sizeof would be 8 (padding after first_byte) */
    /* With    packed: sizeof must be exactly 7 */
    if (sizeof(QuicLongHeader) != 7) {
        fprintf(stderr, "FAIL: packed struct sizeof wrong: got %zu, want 7 "
                "(chibicc ignoring __attribute__((packed))?)\n",
                sizeof(QuicLongHeader));
        return 0;
    }

    QuicLongHeader hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.first_byte = 0xC0;
    hdr.version    = 0x00000001;
    hdr.dcil       = 8;
    hdr.scil       = 0;

    /* Check offsets via memcpy-based read (avoids UB on unaligned) */
    uint32_t v;
    memcpy(&v, (char *)&hdr + 1, sizeof(v));
    if (v != 0x00000001) {
        fprintf(stderr, "FAIL: packed struct field offset wrong: version at wrong offset\n");
        return 0;
    }

    printf("PASS: packed struct layout\n");
    return 1;
}

/* -----------------------------------------------------------------------
 * main
 * ----------------------------------------------------------------------- */
int main(void)
{
    int pass = 1;

    printf("=== quic_txp_timeout reproducer ===\n\n");
    printf("Checking constructs that chibicc may miscompile,\n");
    printf("leading to 'internal error (txp generate)' / op deadline expiry.\n\n");

    pass &= test_u64_arithmetic();
    pass &= test_deadline_compare();
    pass &= test_stream_frame_bitfields();
    pass &= test_txp_out_pointer();
    pass &= test_packed_struct();

    printf("\n");
    if (pass) {
        printf("ALL TESTS PASSED\n");
        printf("(If this passes under gcc but fails under chibicc, the bug\n");
        printf(" is confirmed in chibicc's code generation for the failing test.)\n");
        return 0;
    } else {
        printf("ONE OR MORE TESTS FAILED — likely chibicc miscompilation\n");
        return 1;
    }
}
