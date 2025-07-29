// file.h
#ifndef FILE_H
#define FILE_H
#include <stddef.h>
#define file_protected __attribute__((__visibility__("hidden")))

extern file_protected const char *file_names[];
extern file_protected const size_t file_nnames;

#endif
