#include "test.h"

struct media {
  char *name;
  float w;
  float h;
};

static struct media prt_mediasize[] = {
  { "A4", 595.0f, 842.0f },
  { "Letter", 612.0f, 792.0f },
};

int main() {
  ASSERT(595, (int)prt_mediasize[0].w);
  ASSERT(842, (int)prt_mediasize[0].h);
  ASSERT(612, (int)prt_mediasize[1].w);
  ASSERT(792, (int)prt_mediasize[1].h);
  printf("OK\n");
  return 0;
}
