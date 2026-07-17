#include <stdio.h>
#include <stdint.h>
int main(void) {
  /* Reproduce the montgomery_reduce shift semantics */
  int32_t value = -123456;            /* negative */
  int16_t c_signed = (int16_t)(value >> 16);          /* signed shift */
  uint32_t u = (uint32_t)value;
  int16_t c_unsigned = (int16_t)(u >> 16U);           /* C semantics: unsigned */
  printf("signed_shift  = %d\n", (int)c_signed);
  printf("unsigned_shift= %d\n", (int)c_unsigned);
  if (c_signed != c_unsigned) {
    printf("MISMATCH: compiler treats value>>16U as signed shift\n");
    return 1;
  }
  printf("OK shift semantics\n");
  return 0;
}
