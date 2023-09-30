#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#define Array(T)       \
  struct {             \
    T *contents;       \
    uint32_t size;     \
    uint32_t capacity; \
  }



#define SUBTREE_BITS    \
  bool visible : 1;     \
  bool named : 1;       \
  bool extra : 1;       \
  bool has_changes : 1; \
  bool is_missing : 1;  \
  bool is_keyword : 1;

#define SUBTREE_SIZE           \
  uint8_t padding_columns;     \
  uint8_t padding_rows : 4;    \
  uint8_t lookahead_bytes : 4; \
  uint8_t padding_bytes;       \
  uint8_t size_bytes;



typedef struct {
  volatile uint32_t ref_count;
  int padding;
  int size;
  uint32_t lookahead_bytes;
  uint32_t error_cost;
  uint32_t child_count;
  char * symbol;
  char * parse_state;

  bool visible : 1;
  bool named : 1;
  bool extra : 1;
  bool fragile_left : 1;
  bool fragile_right : 1;
  bool has_changes : 1;
  bool has_external_tokens : 1;
  bool has_external_scanner_state_change : 1;
  bool depends_on_column: 1;
  bool is_missing : 1;
  bool is_keyword : 1;

  


  union {
    // Non-terminal subtrees (`child_count > 0`)
    struct {
      uint32_t visible_child_count;
      uint32_t named_child_count;
      uint32_t visible_descendant_count;
      int32_t dynamic_precedence;
      uint16_t repeat_depth;
      uint16_t production_id;
      struct {
        char * symbol;
        char * parse_state;
      } first_leaf;
    };

    // External terminal subtrees (`child_count == 0 && has_external_tokens`)
    char * external_scanner_state;

    // Error terminal subtrees (`child_count == 0 && symbol == ts_builtin_sym_error`)
    int32_t lookahead_char;
  };
} SubtreeHeapData;



struct SubtreeInlineData {
  bool is_inline : 1;
  SUBTREE_BITS
  uint8_t symbol;
  uint16_t parse_state;
  SUBTREE_SIZE
};


typedef struct SubtreeInlineData SubtreeInlineData;

// The fundamental building block of a syntax tree.
typedef union {
  SubtreeInlineData data;
  const SubtreeHeapData *ptr;
} Subtree;

typedef struct {
  const Subtree *subtree;
  int position;
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


#define ts_subtree_children(self) \
  ((self).data.is_inline ? NULL : (Subtree *)((self).ptr) - (self).ptr->child_count)

#define array_back(self) array_get(self, (self)->size - 1)


int main() {
Iterator *self;
    TreeCursorEntry entry = *array_back(&self->cursor.stack);
    for (uint32_t i = 0; i < 10; i++) {
      const Subtree *child = &ts_subtree_children(*entry.subtree)[i];
    }
    return 0;
}