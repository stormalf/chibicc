#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "c.h"



static inline void
store_att_byval(void *T, Datum newdatum, int attlen)
{
	switch (attlen)
	{
		case sizeof(char):
			*(char *) T = DatumGetChar(newdatum);
			break;
		case sizeof(int16):
			*(int16 *) T = DatumGetInt16(newdatum);
			break;
		case sizeof(int32):
			*(int32 *) T = DatumGetInt32(newdatum);
			break;
#if SIZEOF_DATUM == 8
		case sizeof(Datum):
			*(Datum *) T = newdatum;
			break;
#endif
		default:
			printf("unsupported byval length: %d", attlen);
	}
}

int main() {
  char c = 0;
  int16 i16 = 0;
  int32_t i32 = 0;
  Datum d = 0;

  Datum val_char = (Datum) 'A';
  Datum val_i16 = (Datum) 12345;
  Datum val_i32 = (Datum) 67890;
  Datum val_d = (Datum) 0x123456789ABCDEF0;

  store_att_byval(&c, val_char, sizeof(char));
  assert(c == 'A');
  printf("char stored ok: %c\n", c);

  store_att_byval(&i16, val_i16, sizeof(int16));
  assert(i16 == 12345);
  printf("int16 stored ok: %d\n", i16);

  store_att_byval(&i32, val_i32, sizeof(int32_t));
  assert(i32 == 67890);
  printf("int32 stored ok: %d\n", i32);

#if SIZEOF_DATUM == 8
  store_att_byval(&d, val_d, sizeof(Datum));
  assert(d == val_d);
  printf("Datum stored ok: 0x%lx\n", (unsigned long) d);
#endif

  printf("All store_att_byval tests passed.\n");
  printf("sizeof(char) = %zu\n", sizeof(char));
  printf("sizeof(short) = %zu\n", sizeof(short));
  printf("sizeof(int16_t) = %zu\n", sizeof(int16_t));
  printf("sizeof(int16) = %zu\n", sizeof(int16));
  return 0;
}
