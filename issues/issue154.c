#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#define VTERM_MAX_CHARS_PER_CELL 6

typedef union {
  /**
   * Tag indicating which union member is actually valid. This variable
   * coincides with the `type` member of the `rgb` and the `indexed` struct
   * in memory. Please use the `VTERM_COLOR_IS_*` test macros to check whether
   * a particular type flag is set.
   */
  uint8_t type;

  /**
   * Valid if `VTERM_COLOR_IS_RGB(type)` is true. Holds the RGB colour values.
   */
  struct {
    /**
     * Same as the top-level `type` member stored in VTermColor.
     */
    uint8_t type;

    /**
     * The actual 8-bit red, green, blue colour values.
     */
    uint8_t red, green, blue;
  } rgb;

  /**
   * If `VTERM_COLOR_IS_INDEXED(type)` is true, this member holds the index into
   * the colour palette.
   */
  struct {
    /**
     * Same as the top-level `type` member stored in VTermColor.
     */
    uint8_t type;

    /**
     * Index into the colour map.
     */
    uint8_t idx;
  } indexed;
} VTermColor;

typedef struct {
  int start_row;
  int end_row;
  int start_col;
  int end_col;
} VTermRect;

typedef enum {
  VTERM_DAMAGE_CELL,    /* every cell */
  VTERM_DAMAGE_ROW,     /* entire rows */
  VTERM_DAMAGE_SCREEN,  /* entire screen */
  VTERM_DAMAGE_SCROLL,  /* entire screen + scrollrect */

  VTERM_N_DAMAGES
} VTermDamageSize;

typedef struct {
  int (*damage)(VTermRect rect, void *user);
  int (*moverect)(VTermRect dest, VTermRect src, void *user);
  int (*bell)(void *user);
  int (*resize)(int rows, int cols, void *user);
  int (*sb_clear)(void* user);
} VTermScreenCallbacks;


typedef struct
{
  /* After the bitfield */
  VTermColor   fg, bg;

  unsigned int bold      : 1;
  unsigned int underline : 2;
  unsigned int italic    : 1;
  unsigned int blink     : 1;
  unsigned int reverse   : 1;
  unsigned int conceal   : 1;
  unsigned int strike    : 1;
  unsigned int font      : 4; /* 0 to 9 */
  unsigned int small     : 1;
  unsigned int baseline  : 2;

  /* Extra state storage that isn't strictly pen-related */
  unsigned int protected_cell : 1;
  unsigned int dwl            : 1; /* on a DECDWL or DECDHL line */
  unsigned int dhl            : 2; /* on a DECDHL line (1=top 2=bottom) */
} ScreenPen;

typedef struct
{
  uint32_t chars[VTERM_MAX_CHARS_PER_CELL];
  ScreenPen pen;
} ScreenCell;

typedef struct {
    unsigned int bold      : 1;
    unsigned int underline : 2;
    unsigned int italic    : 1;
    unsigned int blink     : 1;
    unsigned int reverse   : 1;
    unsigned int conceal   : 1;
    unsigned int strike    : 1;
    unsigned int font      : 4; /* 0 to 9 */
    unsigned int dwl       : 1; /* On a DECDWL or DECDHL line */
    unsigned int dhl       : 2; /* On a DECDHL line (1=top 2=bottom) */
    unsigned int small     : 1;
    unsigned int baseline  : 2;
} VTermScreenCellAttrs;

typedef struct {
  uint32_t chars[VTERM_MAX_CHARS_PER_CELL];
  char     width;
  VTermScreenCellAttrs attrs;
  VTermColor fg, bg;
} VTermScreenCell;



// struct VTermScreen
// {
//   char *vt;
//   char *state;

//   const VTermScreenCallbacks *callbacks;
//   void *cbdata;

//   VTermDamageSize damage_merge;
//   /* start_row == -1 => no damage */
//   VTermRect damaged;
//   VTermRect pending_scrollrect;
//   int pending_scroll_downward, pending_scroll_rightward;

//   int rows;
//   int cols;

//   unsigned int global_reverse : 1;
//   unsigned int reflow : 1;

//   /* Primary and Altscreen. buffers[1] is lazily allocated as needed */
//   ScreenCell *buffers[2];

//   /* buffer will == buffers[0] or buffers[1], depending on altscreen */
//   ScreenCell *buffer;

//   /* buffer for a single screen row used in scrollback storage callbacks */
//   VTermScreenCell *sb_buffer;

//   ScreenPen pen;
// };






struct VTermScreen
{
  int rows;
  int cols;
  ScreenPen pen;
};

typedef struct VTermScreen VTermScreen;


static inline ScreenCell *getcell(const ScreenCell *screen, int row, int col)
{
    ScreenCell *sc;
  return  sc;
}


      int main() {

        ScreenCell *screen = NULL;
        int row, col;
    ScreenCell *cell = getcell(screen, row, col);
      cell->pen = (ScreenPen){
        /* Only copy .fg and .bg; leave things like rv in reset state */
        .fg = screen->pen.fg,
        .bg = screen->pen.bg,
      };

        return 0;

      }