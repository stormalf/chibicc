#include "chibicc.h"
#define STRINGS_C "strings.c"



void strarray_push(StringArray *arr, char *s) {
  if (!arr->data) {
    arr->data = calloc(8, sizeof(char *));
    arr->capacity = 8;
  }

  if (arr->capacity == arr->len) {
    char **tmp = realloc(arr->data, sizeof(char *) * arr->capacity * 2);
    if (tmp == NULL)
      error("%s: %s:%d: error: in strarray_push reallocation of arr->data failed!", STRINGS_C, __FILE__, __LINE__);
    arr->data = tmp;
    arr->capacity *= 2;
  }

  arr->data[arr->len++] = s;
}



// Takes a printf-style format string and returns a formatted string.
char *format(const char *fmt, ...) {
  char *buf;
  size_t buflen;
  FILE *out = open_memstream(&buf, &buflen);
  if (out == NULL)
    error("%s: %s:%d: error: in strarray_push out is null", STRINGS_C, __FILE__, __LINE__);
     
  va_list ap;
  va_start(ap, fmt);
  vfprintf(out, fmt, ap);
  va_end(ap);
  fclose(out);
  return buf;
}
