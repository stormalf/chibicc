// Reproduction of cal inline bug: complex function + loop + inlined array access
#include "test.h"

typedef struct { int days[7]; int next; } Month;
typedef struct { int julian; int day_width; int gutter_width; int weekstart; } Ctl;

static const struct {
  const char *scheme;
  const char *dflt;
} colors[] = {
  [0] = {"today", "REVERSE"},
  [1] = {"wknum", "INVERSE"},
};

static inline const char *get_color_seq(int id) {
  return colors[id].dflt;
}

int main() {
  Month m;
  Ctl ctl = {0};
  int reqday = 1;

  for (int d = 0; d < 7; d++)
    m.days[d] = d == 6 ? 1 : -1;

  for (int week_line = 0; week_line < 1; week_line++) {
    int skip = ctl.day_width ? ctl.day_width : 3;
    int firstwork = ctl.weekstart == 1 ? 1 : 0;

    for (int d = 0; d < 7; d++) {
      if (m.days[d] > 0) {
        if (reqday == m.days[d]) {
          printf("%*s%s%*d%s",
            skip - (ctl.julian ? 3 : 2),
            "", get_color_seq(0), 2,
            m.days[d], get_color_seq(0));
        }
      }
    }
  }

  printf("OK\n");
  return 0;
}
