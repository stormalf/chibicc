// Test that attributes before the type are correctly handled.
// This test exercises all major attributes in pre-type position.
// NOTE: __attribute__((packed/aligned)) before "struct" keyword does NOT
// affect the struct type in GCC.  The correct placement is after "struct".

#include "test.h"

// --- section attribute ---
const __attribute__((section("sec1"))) int gsec_int = 42;
const __attribute__((section("sec2"))) int gsec_arr[4] = {1,2,3,4};

// --- aligned attribute on variable ---
__attribute__((aligned(64))) int galign_var;
__attribute__((aligned(128))) char galign_buf[16];

// --- weak attribute ---
__attribute__((weak)) int gweak_var = 0;

// --- used attribute ---
__attribute__((used)) int gused_var;

// --- unused attribute ---
__attribute__((unused)) static int gunused_var;

// --- noinline attribute on function ---
__attribute__((noinline)) int noinline_func(void) { return 1; }

// --- always_inline attribute ---
__attribute__((always_inline)) static inline int always_inline_func(void) { return 2; }

// --- combined multiple attributes before type ---
__attribute__((section("sec3"), aligned(32))) int gcombined_var;

int main(void) {
  // --- section ---
  ASSERT(42, gsec_int);
  ASSERT(1, gsec_arr[0]);

  // --- aligned ---
  ASSERT(0, (unsigned long)&galign_var % 64);
  ASSERT(0, (unsigned long)&galign_buf % 128);

  // --- weak ---
  ASSERT(0, gweak_var);

  // --- used ---
  ASSERT(0, gused_var);

  // --- noinline ---
  ASSERT(1, noinline_func());

  // --- always_inline ---
  ASSERT(2, always_inline_func());

  // --- combined ---
  ASSERT(0, (unsigned long)&gcombined_var % 32);

  // Test attribute after variable name
  int local_var __attribute__((unused)) = 200;
  ASSERT(200, local_var);

  // Test aligned on local variable before type
  __attribute__((aligned(64))) int local_align = 300;
  ASSERT(300, local_align);
  ASSERT(0, (unsigned long)&local_align % 64);

  printf("OK\n");
  return 0;
}
