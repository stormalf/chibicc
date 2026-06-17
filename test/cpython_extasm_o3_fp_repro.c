#include <alloca.h>
#include <setjmp.h>
#include <stdint.h>
#include "test.h"
int myglobal = 18;
/*
 * Stronger CPython-like repro for -O3 + -fomit-frame-pointer + extended asm.
 *
 * Compile/run:
 *   ./chibicc -std=c11 -O3 -fomit-frame-pointer \
 *     -o issues/cpython_extasm_o3_fp_repro.exe issues/cpython_extasm_o3_fp_repro.c
 *   ./issues/cpython_extasm_o3_fp_repro.exe
 *
 * The test combines:
 * 1) deep-ish recursion
 * 2) dynamic alloca and post-call memory verification
 * 3) calls with >6 integer args (stack-passed args on SysV x86-64)
 * 4) function-pointer dispatch
 * 5) GNU extended asm that clobbers %rbx and uses r/w constraints
 *
 * With correct codegen the asm and pure-C paths must match exactly.
 *
 * If parse.c disables omit-frame-pointer when it sees asm, this repro can be masked.
 */

typedef struct Blob {
  uint64_t tag;
  uint64_t len;
  uint8_t data[64];
  uint64_t tail;
} Blob;

typedef uint64_t (*mix_fn_t)(uint64_t, uint64_t, uint64_t, uint64_t *);
typedef uint64_t (*step_fn_t)(uint64_t, uint64_t, uint64_t);

static jmp_buf g_jb;
static volatile uint64_t g_setjmp_sig;

__attribute__((noinline)) static uint64_t consume10(
    uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5,
    uint64_t a6, uint64_t a7, uint64_t a8, uint64_t a9, uint64_t a10, Blob *b) {
  uint64_t x = a1 + a2 + a3 + a4 + a5;
  uint64_t y = a6 ^ a7 ^ a8 ^ a9 ^ a10;

  if (!b)
    return x ^ y;

  x ^= b->tag;
  y += b->tail;
  x += (uint64_t)b->data[(a1 + a8) & 63];
  y ^= (uint64_t)b->data[(a2 + a9) & 63];
  return (x << 7) ^ (x >> 11) ^ (y << 3) ^ (y >> 5);
}

__attribute__((noinline)) static uint64_t mix_ref(
    uint64_t x, uint64_t y, uint64_t z, uint64_t *acc) {
  uint64_t out = (x + y) ^ z;
  out = (out << 13) | (out >> (64 - 13));
  *acc ^= out;
  return out + y;
}

__attribute__((noinline)) static uint64_t mix_extasm(
    uint64_t x, uint64_t y, uint64_t z, uint64_t *acc) {
  volatile uint64_t a __attribute__((aligned(32))) = x;
  volatile uint64_t b = y;
  uint64_t out = 0;

  __asm__ volatile(
      "add %2, %0\n\t"
      "xor %3, %0\n\t"
      "rol $13, %0\n\t"
      "xor %%rbx, %%rbx\n\t"
      : "=&r"(out)
      : "0"(a), "r"(b), "r"(z)
      : "rbx", "cc", "memory");

  *acc ^= out;
  return out + b;
}

__attribute__((noinline)) static uint64_t worker(
    int depth, uint64_t seed, mix_fn_t mix, uint64_t salt) {
  volatile uint64_t anchor __attribute__((aligned(32))) =
      seed ^ 0x9e3779b97f4a7c15ULL ^ salt;

  if (depth <= 0)
    return anchor + salt;

  int sz = 96 + ((depth * 13) & 127);
  uint8_t *scratch = (uint8_t *)alloca((size_t)sz);

  for (int i = 0; i < sz; i++)
    scratch[i] = (uint8_t)((seed + salt + depth + i) & 0xff);

  uint64_t local = anchor + (uint64_t)scratch[depth % sz] + (uint64_t)depth;
  uint64_t mixed = mix(seed + (uint64_t)(depth * 3), local,
                       (uint64_t)(uintptr_t)scratch ^ salt, (uint64_t *)&anchor);

  Blob b = {0};
  b.tag = mixed ^ anchor;
  b.len = (uint64_t)sz;
  b.tail = seed + local + mixed + salt;
  for (int i = 0; i < 64; i++)
    b.data[i] = (uint8_t)(scratch[(i * 7 + depth) % sz] ^ (uint8_t)i);

  uint64_t c = consume10(
      (uint64_t)depth, mixed, local, anchor, b.tag,
      b.tail, (uint64_t)(uintptr_t)scratch, (uint64_t)sz, seed, salt, &b);

  for (int i = 0; i < sz; i++) {
    uint8_t want = (uint8_t)((seed + salt + depth + i) & 0xff);
    if (scratch[i] != want) {
      printf("stack corruption at depth=%d idx=%d got=%u want=%u\n",
             depth, i, (unsigned)scratch[i], (unsigned)want);
      return 0;
    }
  }

  return c ^ worker(depth - 1, mixed + c + (uint64_t)(depth * 17), mix, salt + 1);
}

__attribute__((noinline)) static uint64_t recursive_fold_ref(
    int depth, uint64_t a, uint64_t b, uint64_t c, uint64_t d,
    uint64_t e, uint64_t f, uint64_t g, uint64_t h) {
  volatile uint64_t guard = a ^ c ^ e ^ g ^ (uint64_t)depth;
  if (depth <= 0)
    return guard + b + d + f + h;

  uint64_t x = (a + b) ^ (c + d) ^ guard;
  uint64_t y = (e + f) ^ (g + h) ^ ((uint64_t)depth << 7);
  uint64_t z = ((x << 9) | (x >> (64 - 9))) ^ y;
  return z ^ recursive_fold_ref(depth - 1, b + z, c + x, d + y, e + z,
                                f + x, g + y, h + z, a + y);
}

__attribute__((noinline)) static uint64_t recursive_fold_asm(
    int depth, uint64_t a, uint64_t b, uint64_t c, uint64_t d,
    uint64_t e, uint64_t f, uint64_t g, uint64_t h) {
  volatile uint64_t guard = a ^ c ^ e ^ g ^ (uint64_t)depth;
  if (depth <= 0)
    return guard + b + d + f + h;

  uint64_t x = (a + b) ^ (c + d) ^ guard;
  uint64_t y = (e + f) ^ (g + h) ^ ((uint64_t)depth << 7);
  uint64_t z = 0;

  __asm__ volatile(
      "mov %1, %0\n\t"
      "rol $9, %0\n\t"
      "xor %2, %0\n\t"
      "xor %%rbx, %%rbx\n\t"
      : "=&r"(z)
      : "r"(x), "r"(y)
      : "rbx", "cc", "memory");

  return z ^ recursive_fold_asm(depth - 1, b + z, c + x, d + y, e + z,
                                f + x, g + y, h + z, a + y);
}

__attribute__((noinline)) static uint64_t recursive_ref(
    int depth, uint64_t a, uint64_t b, uint64_t c, uint64_t d,
    uint64_t e, uint64_t f, uint64_t g, uint64_t h) {
  volatile uint64_t guard = a ^ c ^ e ^ g ^ (uint64_t)depth;
  if (depth <= 0)
    return guard + b + d + f + h;

  uint64_t x = (a + b) ^ (c + d) ^ guard;
  uint64_t y = (e + f) ^ (g + h) ^ ((uint64_t)depth << 7);
  uint64_t z = ((x << 9) | (x >> (64 - 9))) ^ y;
  return recursive_ref(depth - 1, b + z, c + x, d + y, e + z,
                                f + x, g + y, h + z, a + y);
}

__attribute__((noinline)) static uint64_t step_ref(
    uint64_t x, uint64_t y, uint64_t z) {
  uint64_t out = (x + y) ^ z;
  out = (out << 17) | (out >> (64 - 17));
  return out ^ (y << 3);
}

__attribute__((noinline)) static uint64_t step_asm(
    uint64_t x, uint64_t y, uint64_t z) {
  uint64_t out = 0;
  __asm__ volatile(
      "mov %1, %0\n\t"
      "add %2, %0\n\t"
      "xor %3, %0\n\t"
      "rol $17, %0\n\t"
      "xor %%rbx, %%rbx\n\t"
      : "=&r"(out)
      : "r"(x), "r"(y), "r"(z)
      : "rbx", "cc", "memory");
  return out ^ (y << 3);
}

__attribute__((noinline)) static uint64_t recurse_with_jump(
    int depth, uint64_t s, uint64_t t, step_fn_t step, int jump_at) {
  volatile uint64_t local = s ^ t ^ (uint64_t)depth;
  int sz = 48 + ((depth * 11) & 63);
  uint8_t *p = (uint8_t *)alloca((size_t)sz);

  for (int i = 0; i < sz; i++)
    p[i] = (uint8_t)((s + t + depth + i) & 0xff);

  if (depth == jump_at) {
    g_setjmp_sig = local ^ (uint64_t)(uintptr_t)p ^ (uint64_t)sz;
    longjmp(g_jb, 1);
  }

  if (depth <= 0)
    return local + (uint64_t)p[0];

  uint64_t u = step(s + local, t + (uint64_t)sz, (uint64_t)(uintptr_t)p ^ local);
  uint64_t v = recurse_with_jump(depth - 1, t + u, s + local + 1, step, jump_at);

  for (int i = 0; i < sz; i++) {
    uint8_t want = (uint8_t)((s + t + depth + i) & 0xff);
    if (p[i] != want) {
      printf("setjmp path stack corruption depth=%d idx=%d got=%u want=%u\n",
             depth, i, (unsigned)p[i], (unsigned)want);
      return 0;
    }
  }

  return u ^ v ^ local;
}

__attribute__((noinline)) static uint64_t run_setjmp_path(
    int depth, uint64_t s, uint64_t t, step_fn_t step, int jump_at) {
  g_setjmp_sig = 0;
  if (setjmp(g_jb) == 0)
    return recurse_with_jump(depth, s, t, step, jump_at);
  return g_setjmp_sig ^ s ^ t ^ (uint64_t)depth ^ (uint64_t)jump_at;
}

__attribute__((noinline)) static uint64_t vla_probe(
    int n, uint64_t seed, uint64_t salt) {
  int sz = 64 + (n & 127);
  volatile uint8_t vla[sz];
  uint64_t acc = seed ^ salt ^ (uint64_t)sz;

  for (int i = 0; i < sz; i++) {
    vla[i] = (uint8_t)((seed + salt + (uint64_t)i + (uint64_t)n) & 0xff);
    acc ^= (uint64_t)vla[i] << (i & 7);
  }

  return acc ^ (uint64_t)vla[(n * 3) % sz];
}

int main(void) {
  enum { DEPTH = 80, ROUNDS = 200, FOLD_DEPTH = 120, JUMP_DEPTH = 70 };
  uint64_t seed = 0x0123456789abcdefULL;
  uint64_t salt = 0xfeedfacecafebeefULL;
  uint64_t acc_ref = 0;
  uint64_t acc_asm = 0;
  uint64_t fold_ref = 0;
  uint64_t fold_asm = 0;
  uint64_t jump_ref = 0;
  uint64_t jump_asm = 0;
  uint64_t vla_acc = 0;

  for (int i = 0; i < ROUNDS; i++) {
    uint64_t s = seed + (uint64_t)i * 0x100000001b3ULL;
    uint64_t t = salt ^ (uint64_t)i * 0x9e3779b97f4a7c15ULL;
    acc_ref ^= worker(DEPTH, s, mix_ref, t);
    acc_asm ^= worker(DEPTH, s, mix_extasm, t);
    fold_ref ^= recursive_fold_ref(FOLD_DEPTH, s + 1, s + 2, s + 3, s + 4,
                                   t + 5, t + 6, t + 7, t + 8);
    fold_asm ^= recursive_fold_asm(FOLD_DEPTH, s + 1, s + 2, s + 3, s + 4,
                                   t + 5, t + 6, t + 7, t + 8);
    jump_ref ^= run_setjmp_path(JUMP_DEPTH, s ^ 0x1111ULL, t ^ 0x2222ULL,
                                step_ref, JUMP_DEPTH / 2);
    jump_asm ^= run_setjmp_path(JUMP_DEPTH, s ^ 0x1111ULL, t ^ 0x2222ULL,
                                step_asm, JUMP_DEPTH / 2);
    vla_acc ^= vla_probe(DEPTH + i, s, t);
  }

  printf("acc_ref=0x%llx\n", (unsigned long long)acc_ref);
  printf("acc_asm=0x%llx\n", (unsigned long long)acc_asm);
  printf("fold_ref=0x%llx\n", (unsigned long long)fold_ref);
  printf("fold_asm=0x%llx\n", (unsigned long long)fold_asm);
  printf("jump_ref=0x%llx\n", (unsigned long long)jump_ref);
  printf("jump_asm=0x%llx\n", (unsigned long long)jump_asm);
  printf("vla_acc=0x%llx\n", (unsigned long long)vla_acc);

  if (acc_ref != acc_asm) {
    printf("BUG: asm path diverged from reference (DEPTH=%d ROUNDS=%d)\n",
           DEPTH, ROUNDS);
    return 1;
  }
  if (fold_ref != fold_asm) {
    printf("BUG: recursive asm fold diverged (FOLD_DEPTH=%d)\n", FOLD_DEPTH);
    return 1;
  }
  if (jump_ref != jump_asm) {
    printf("BUG: setjmp/longjmp asm path diverged (JUMP_DEPTH=%d)\n", JUMP_DEPTH);
    return 1;
  }
  if (vla_acc == 0) {
    printf("BUG: vla probe produced suspicious zero accumulator\n");
    return 1;
  }
  uint64_t retx = recursive_ref(FOLD_DEPTH, seed + 1, seed + 2, seed + 3, seed + 4, seed + 5, seed + 6, seed + 7, seed + 8);

  printf("DONE\n");
  return 0;
}
