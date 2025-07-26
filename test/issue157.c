#include <stdbool.h>
#include <stdint.h>
#include "test.h"

#define Array(T)       \
  struct {             \
    T *contents;       \
    uint32_t size;     \
    uint32_t capacity; \
  }


typedef union {

  char * data;
  const char *ptr;
} Subtree;

typedef struct {
  uint32_t bytes;
  char *extent;
} Length;


typedef struct {
  const Subtree *subtree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
  uint32_t descendant_index;
} TreeCursorEntry;


typedef struct {
  const char *tree;
  Array(TreeCursorEntry) stack;
} TreeCursor;



typedef struct {
  TreeCursor cursor;
  const char *language;
  unsigned visible_depth;
  bool in_padding;
} Iterator;


static bool iterator_tree_is_visible(const Iterator *self) {

  if (self->cursor.stack.size > 1) {
    Subtree parent = *self->cursor.stack.contents[self->cursor.stack.size - 2].subtree;
    return false;
    }
    return false;
}

int main()

{

    return 0;
}