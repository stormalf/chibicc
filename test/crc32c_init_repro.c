#include "test.h"
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef uint32_t (*crc_func_t)(uint32_t crc, const void *buf, size_t len);

static crc_func_t crc32c_fn;

#define POLY 0x82f63b78u
#define LONG 8192
#define LONGx1 "8192"
#define LONGx2 "16384"
#define SHORT 256
#define SHORTx1 "256"
#define SHORTx2 "512"

static volatile sig_atomic_t timed_out;

static void on_alarm(int signo) {
  (void)signo;
  timed_out = 1;
}

static uint32_t crc32c_sw(uint32_t crc, const void *buf, size_t len) {
  const uint8_t *p = (const uint8_t *)buf;
  crc = ~crc;
  while (len--) {
    crc ^= *p++;
    for (int i = 0; i < 8; i++)
      crc = (crc >> 1) ^ (POLY & (-(int32_t)(crc & 1)));
  }
  return ~crc;
}

static inline uint32_t gf2_matrix_times(uint32_t *mat, uint32_t vec) {
  uint32_t sum = 0;
  while (vec) {
    if (vec & 1)
      sum ^= *mat;
    vec >>= 1;
    mat++;
  }
  return sum;
}

static inline void gf2_matrix_square(uint32_t *square, uint32_t *mat) {
  for (unsigned n = 0; n < 32; n++)
    square[n] = gf2_matrix_times(mat, mat[n]);
}

static void crc32c_zeros_op(uint32_t *even, size_t len) {
  uint32_t odd[32];
  odd[0] = POLY;
  uint32_t row = 1;
  for (unsigned n = 1; n < 32; n++) {
    odd[n] = row;
    row <<= 1;
  }

  gf2_matrix_square(even, odd);
  gf2_matrix_square(odd, even);

  do {
    gf2_matrix_square(even, odd);
    len >>= 1;
    if (len == 0)
      return;
    gf2_matrix_square(odd, even);
    len >>= 1;
  } while (len);

  for (unsigned n = 0; n < 32; n++)
    even[n] = odd[n];
}

static void crc32c_zeros(uint32_t zeros[][256], size_t len) {
  uint32_t op[32];
  crc32c_zeros_op(op, len);
  for (unsigned n = 0; n < 256; n++) {
    zeros[0][n] = gf2_matrix_times(op, n);
    zeros[1][n] = gf2_matrix_times(op, n << 8);
    zeros[2][n] = gf2_matrix_times(op, n << 16);
    zeros[3][n] = gf2_matrix_times(op, n << 24);
  }
}

static inline uint32_t crc32c_shift(uint32_t zeros[][256], uint32_t crc) {
  return zeros[0][crc & 0xff] ^ zeros[1][(crc >> 8) & 0xff] ^
         zeros[2][(crc >> 16) & 0xff] ^ zeros[3][crc >> 24];
}

static pthread_once_t crc32c_once_hw = PTHREAD_ONCE_INIT;
static uint32_t crc32c_long[4][256];
static uint32_t crc32c_short[4][256];

static void crc32c_init_hw(void) {
  crc32c_zeros(crc32c_long, LONG);
  crc32c_zeros(crc32c_short, SHORT);
}

static uint32_t crc32c_hw(uint32_t crc, const void *buf, size_t len) {
  pthread_once(&crc32c_once_hw, crc32c_init_hw);

  crc = ~crc;
  uint64_t crc0 = crc;
  const unsigned char *next = (const unsigned char *)buf;

  while (len && ((uintptr_t)next & 7) != 0) {
    __asm__("crc32b\t" "(%1), %0" : "+r"(crc0) : "r"(next), "m"(*next));
    next++;
    len--;
  }

  while (len >= LONG * 3) {
    uint64_t crc1 = 0;
    uint64_t crc2 = 0;
    const unsigned char *end = next + LONG;
    do {
      __asm__("crc32q\t" "(%3), %0\n\t"
              "crc32q\t" LONGx1 "(%3), %1\n\t"
              "crc32q\t" LONGx2 "(%3), %2"
              : "+r"(crc0), "+r"(crc1), "+r"(crc2)
              : "r"(next), "m"(*next));
      next += 8;
    } while (next < end);
    crc0 = crc32c_shift(crc32c_long, crc0) ^ crc1;
    crc0 = crc32c_shift(crc32c_long, crc0) ^ crc2;
    next += LONG * 2;
    len -= LONG * 3;
  }

  while (len >= SHORT * 3) {
    uint64_t crc1 = 0;
    uint64_t crc2 = 0;
    const unsigned char *end = next + SHORT;
    do {
      __asm__("crc32q\t" "(%3), %0\n\t"
              "crc32q\t" SHORTx1 "(%3), %1\n\t"
              "crc32q\t" SHORTx2 "(%3), %2"
              : "+r"(crc0), "+r"(crc1), "+r"(crc2)
              : "r"(next), "m"(*next));
      next += 8;
    } while (next < end);
    crc0 = crc32c_shift(crc32c_short, crc0) ^ crc1;
    crc0 = crc32c_shift(crc32c_short, crc0) ^ crc2;
    next += SHORT * 2;
    len -= SHORT * 3;
  }

  {
    const unsigned char *end = next + (len - (len & 7));
    while (next < end) {
      __asm__("crc32q\t" "(%1), %0" : "+r"(crc0) : "r"(next), "m"(*next));
      next += 8;
    }
    len &= 7;
  }

  while (len) {
    __asm__("crc32b\t" "(%1), %0" : "+r"(crc0) : "r"(next), "m"(*next));
    next++;
    len--;
  }

  return ~crc0;
}

#define SSE42(have)                                                             \
  do {                                                                          \
    uint32_t eax, ecx;                                                          \
    eax = 1;                                                                    \
    __asm__("cpuid" : "=c"(ecx) : "a"(eax) : "%ebx", "%edx");                  \
    (have) = (ecx >> 20) & 1;                                                   \
  } while (0)

static void crc32c_init(void) {
  int sse42;

  SSE42(sse42);
  if (sse42) {
    crc32c_fn = crc32c_hw;
  } else {
    crc32c_fn = crc32c_sw;
  }
}

static void *worker(void *arg) {
  uint8_t *buf = (uint8_t *)arg;
  for (int i = 0; i < 3000; i++) {
    if (timed_out)
      return (void *)1;

    size_t len = 20000 + (i & 31);
    uint32_t got = crc32c_fn(0, buf, len);
    uint32_t exp = crc32c_sw(0, buf, len);
    if (got != exp)
      return (void *)2;
  }
  return 0;
}

int main(void) {
  signal(SIGALRM, on_alarm);
  alarm(50);

  crc32c_init();
  RASSERT(crc32c_fn != 0);

  uint8_t *buf = malloc(20512);
  RASSERT(buf != 0);
  for (int i = 0; i < 20512; i++)
    buf[i] = (uint8_t)((i * 131u + 17u) & 0xff);

  pthread_t th[4];
  for (int i = 0; i < 4; i++) {
    int rc = pthread_create(&th[i], 0, worker, buf);
    ASSERT(0, rc);
  }

  for (int i = 0; i < 4; i++) {
    void *ret = 0;
    int rc = pthread_join(th[i], &ret);
    ASSERT(0, rc);
    ASSERT(0, (int)(uintptr_t)ret);
  }

  ASSERT(0, timed_out);
  free(buf);
  return 0;
}
