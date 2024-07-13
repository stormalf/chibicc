#include <stdio.h>
#include <stdint.h>

#define MPACK_PARENT_NODE(n) (((n) - 1)->pos == (size_t)-1 ? NULL : (n) - 1)

typedef struct mpack_node_s {
  char *tok;
  size_t pos;
  /* flag to determine if the key was visited when traversing a map */
  int key_visited;
  /* allow 2 instances mpack_data_t per node. the reason is that when
   * serializing, the user may need to keep track of traversal state besides the
   * parent node reference */
  char *data[2];
} mpack_node_t;

typedef struct {
  char *parser;
  int reg, ext, unpacking, mtdict;
  char *string_buffer;
} Unpacker;


int main() {
 Unpacker *unpacker;
 mpack_node_t *node;
 if (1 == 0 )
  unpacker->string_buffer + MPACK_PARENT_NODE(node)->pos;
 return 0;
}