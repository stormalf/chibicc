#include <stdio.h>
#include "test.h"

void format_int128(char *buf, unsigned __int128 val) {
  unsigned long long high = val >> 64;
  unsigned long long low = val & 0xFFFFFFFFFFFFFFFFULL;
  sprintf(buf, "%016llx%016llx", high, low);
}

int main() {
    char temp[33];  // Buffer to hold formatted 128-bit values
    unsigned __int128 high = 0x1ffffffff;
    unsigned __int128 low = 0x2ffffffff;
    unsigned __int128 result = (high << 64) | low;
    format_int128(temp, I128(0x1ffffffff, 0x2ffffffff));
    printf("temp = %s\n", temp);

    printf("Expected High: 0x00000001ffffffff, Low: 0x00000002ffffffff\n");
    printf("Actual High: 0x%016llx, Low: 0x%016llx\n",
           (unsigned long long)(result >> 64),
           (unsigned long long)result);

    return 0;
}
