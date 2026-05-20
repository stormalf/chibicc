#include "test.h"

#include <stdlib.h>
#include <sys/wait.h>

static int run_cmd(const char *cmd) {
  int rc = system(cmd);
  if (rc == -1)
    return 1;
  if (!WIFEXITED(rc) || WEXITSTATUS(rc) != 0)
    return 1;
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 1 || !argv[0])
    return 1;

  // DW_AT_stmt_list is a section offset into .debug_line. We rely on the
  // assembler-generated .debug_line starting at offset 0, so DW_AT_stmt_list
  // must be 0.
  char cmd[8192];
  snprintf(cmd, sizeof(cmd),
           "readelf --debug-dump=info %s 2>/dev/null | "
           "grep -q \"DW_AT_stmt_list\"",
           argv[0]);
  if (run_cmd(cmd))
    return 1;

  // Ensure .debug_line exists and includes this file.
  snprintf(cmd, sizeof(cmd),
           "readelf --debug-dump=decodedline %s 2>/dev/null | "
           "grep -q \"dwarf_stmt_list_is_zero\\\\.c\"",
           argv[0]);
  if (run_cmd(cmd))
    return 1;

  printf("OK\n");
  return 0;
}
