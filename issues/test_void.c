/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set et ft=c ts=2 sts=2 sw=2 fenc=utf-8                               :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
//#include "test.h"
#include <stdio.h>
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

void lotsOfArgs(const char *file, int line, const char *func, __int128 beg,
                __int128 end, __int128 got, const char *gotcode, bool isfatal) {
}


void testAbi(void) {
  ASSERT(0, ({
           char buf[200];
           sprintf(buf, "%d %d %d %d %032jjx %032jjx", 1, 2, 3, 4,
                   I128(0x1ffffffff, 0x2ffffffff),
                   I128(0x3eeeeeeee, 0x4eeeeeeee));
           strcmp("1 2 3 4 00000001ffffffff00000002ffffffff "
                  "00000003eeeeeeee00000004eeeeeeee",
                  buf);
         }));
  ASSERT(0, ({
           char buf[200];
           sprintf(buf, "%d %d %d %d %d %032jjx %032jjx", 1, 2, 3, 4, 5,
                   I128(0x1ffffffff, 0x2ffffffff),
                   I128(0x3eeeeeeee, 0x4eeeeeeee));
           strcmp("1 2 3 4 5 00000001ffffffff00000002ffffffff "
                  "00000003eeeeeeee00000004eeeeeeee",
                  buf);
         }));
}

int main(void) {
  testAbi();
  return 0;
}