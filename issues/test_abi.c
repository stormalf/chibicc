#include "test.h"
#include <stdbool.h>

#define BANE         0x8000000000000000
#define BANE1        0x8000000000000001
#define BANE2        0x8000000000000002
#define IMAX         0x7fffffffffffffff
#define IMAX2        0xfffffffffffffffd
#define I128(HI, LO) ((LO) | (unsigned __int128)(HI) << 64)

__int128 add128(__int128 x, __int128 y) {
  return x + y;
}

__int128 sub128x5(__int128 a, __int128 b, __int128 c, __int128 d, __int128 e) {
  return a - b - c - d - e;
}

__int128 sub128x6(int f, __int128 a, __int128 b, __int128 c, __int128 d,
                  __int128 e) {
  return f - a - b - c - d - e;
}


void format_int128(char *buf, unsigned __int128 val) {
  unsigned long long high = val >> 64;
  unsigned long long low = val & 0xFFFFFFFFFFFFFFFFULL;
  sprintf(buf, "%016llx%016llx", high, low);
}

void testAbi(void) {
  ASSERT(0, ({
           char buf[200];
           char temp[33];  // Buffer to hold formatted 128-bit values
           
           format_int128(temp, I128(0x1ffffffff, 0x2ffffffff));
           sprintf(buf, "%d %d %d %d %s ", 1, 2, 3, 4, temp);

           format_int128(temp, I128(0x3eeeeeeee, 0x4eeeeeeee));
           strcat(buf, temp);

           strcmp("1 2 3 4 00000001ffffffff00000002ffffffff "
                  "00000003eeeeeeee00000004eeeeeeee",
                  buf);
         }));

  ASSERT(0, ({
           char buf[200];
           char temp[33];  // Buffer to hold formatted 128-bit values

           format_int128(temp, I128(0x1ffffffff, 0x2ffffffff));
           sprintf(buf, "%d %d %d %d %d %s ", 1, 2, 3, 4, 5, temp);

           format_int128(temp, I128(0x3eeeeeeee, 0x4eeeeeeee));
           strcat(buf, temp);

           strcmp("1 2 3 4 5 00000001ffffffff00000002ffffffff "
                  "00000003eeeeeeee00000004eeeeeeee",
                  buf);
         }));
}


int main() {
        int res = 0;
        char buf[200];
        char temp[33];  // Buffer to hold formatted 128-bit values

        format_int128(temp, I128(0x1ffffffff, 0x2ffffffff));
        printf("temp length = %d %s\n", strlen(temp), temp);
        sprintf(buf, "%d %d %d %d %d %s ", 1, 2, 3, 4, 5, temp);

        format_int128(temp, I128(0x3eeeeeeee, 0x4eeeeeeee));
        strcat(buf, temp);

        res = strcmp("1 2 3 4 5 00000001ffffffff00000002ffffffff "
                  "00000003eeeeeeee00000004eeeeeeee",
                  buf);
        printf("=====res = %d\n", res);
    //testAbi();
    return 0;
}