#include "test.h"

asm(".pushsection \".test_section\", \"a\"\n"
    ".ascii \"hello world\\n\"\n"
    ".popsection\n");
    

asm(".pushsection \".debug_gdb_scripts\", \"MS\",%progbits,1\n"
  ".byte 4\n"
  ".ascii \"gdb.inlined-script\\n\"\n"
  ".ascii \"gdb.execute('''\\n\"\n"
  ".ascii \"define set_ts\\n\"\n"
  ".ascii \"    return orig_value\\n\"\n"
  ".byte 0\n"
  ".popsection\n"
);


int main() {

    printf("OK\n");
    return 0;
}