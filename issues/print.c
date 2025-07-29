// print.c
#include "file.h"
#include <stdio.h>

void file_mdump() {
  for (size_t i = 0; i < file_nnames; i++)
    printf("%s\n", file_names[i]);
}
