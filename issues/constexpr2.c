#include "test.h"
#include <stdint.h>

#if !1u - 1 > 0
#error
#endif

extern int extarr[55];
int garr[11];
static int sgarr[33];
//_Bool str_lit_bool_init = "abc" ? "foo" && "bar" : 0;

void array_cast_to_bool(int j) {
  static int slarr[5];
  int larr[7];
  char vla[j];

  DASSERT((_Bool)extarr && (_Bool)garr && (_Bool)sgarr &&
  (_Bool)slarr && (_Bool)larr && (_Bool)vla);
  // ASSERT(1, str_lit_bool_init);
}
int extarr[55];

extern int ext_var;
extern void ext_fn(void);
SASSERT(2 == ((_Bool)&ext_var + (_Bool)ext_fn));
#ifdef NOTGCC
SASSERT(3 == ((_Bool)(long long)&ext_var + (_Bool)(_Bool)ext_fn + (_Bool)(long long)(_Bool)ext_fn));
#endif

int main(void) {
  array_cast_to_bool(11);

  DASSERT((_Bool)0.1f == 1);
  DASSERT((_Bool)2 == 1);
  DASSERT((_Bool)(0.0f + 0.1f) == 1);
  DASSERT((_Bool)(2 * 3) == 1);

  DASSERT( -1 < 0 );

  DASSERT( 3U << 31 >> 31 == 1);
  DASSERT( 1 << 31 >> 31 == -1);

  DASSERT(0.2 > 0.1);
  DASSERT(0.1 < 0.2);
  DASSERT(0.2 != 0.1);
  DASSERT(!(0.2 <= 0.1));
  DASSERT(!(0.1 >= 0.2));
  DASSERT(!(0.1 == 0.2));
  DASSERT(!!0.1);

  DASSERT(0.1 ? 1 : 0);

  DASSERT((long)-0x1U == 4294967295);
  DASSERT((long)-0x1  == -1);
  DASSERT((long)-0xFFFFFFF0U == 16);
  DASSERT((long)-0xFFFFFFF0  == 16);

  DASSERT((long)~0x1U == 4294967294);
  DASSERT((long)~0x1  == -2);
  DASSERT((long)~0xFFFFFFF0U == 15);
  DASSERT((long)~0xFFFFFFF0  == 15);

  DASSERT((long)(0x80000000U << 1) == 0);
  DASSERT((long)(0xFFFFFFFFU + 1) == 0);
  DASSERT((long)(0U - 1) == 0xFFFFFFFFU);
  DASSERT((long)(25989 * 2972383464U) == 4287027336);

  // static_assert(INT32_MIN / -1 == INT32_MIN);
  // static_assert(INT64_MIN / -1 == INT64_MIN);
  // static_assert(INT32_MIN % -1 == 0);
  // static_assert(INT64_MIN % -1 == 0);

  DASSERT(13835058055282163712.0  == (double)13835058055282163712ULL);
  DASSERT(13835058055282163712.0f == (float) 13835058055282163712ULL);
  DASSERT(13835058055282163712ULL == (unsigned long long) 13835058055282163712.0f);
  DASSERT(13835058055282163712ULL == (unsigned long long) 13835058055282163712.0);

  DASSERT(13835058055282163711ULL == (unsigned long long) 13835058055282163711.0L);
  DASSERT(13835058055282163711.0L == (long double) 13835058055282163711ULL);

  DASSERT( 16777217.0 != (float)16777217.0 );
  DASSERT( 9007199254740993.0L != (double)9007199254740993.0L || sizeof(double) == sizeof(long double) );

#ifdef NOTCLANG
  DASSERT( 127 == (unsigned char)511.0 >> 1 );
#endif
  DASSERT( (long long)(0.1f * 1e12f) == 99999997952LL );

  ASSERT(1, ({ int i = 2; char arr[ (i++,3) ]; i == sizeof arr; }) );

  {
    char (*arr_ptr)[UINT32_MAX + 1ULL];
    DASSERT( sizeof(*arr_ptr) == (UINT32_MAX + 1ULL));
  }

  {
    char arr[3];
    DASSERT(8 == sizeof((0 ? arr:arr)));
    DASSERT(8 == sizeof((0 ? 0:arr)));
    DASSERT(8 == sizeof((0 ? arr:0)));
    DASSERT(8 == sizeof(({arr;})));

    DASSERT(8 == sizeof((0,arr)));
    DASSERT(3 == sizeof( (typeof(arr)){0} ));
  }

  printf("OK\n");
  return 0;
}