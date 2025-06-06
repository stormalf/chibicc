#include <stdio.h>

#if defined(__APPLE__) && defined(__has_include) && __has_include(<crt_externs.h>)
#include <crt_externs.h>
static char** mi_get_environ(void) {
  return (*_NSGetEnviron());
}
#else
extern char** environ;
static char** mi_get_environ(void) {
  return environ;
}
#endif

int main(void) {
  char** env = mi_get_environ();
  if (env) {
    printf("Environment variable example: %s\n", env[0]);
  } else {
    printf("Environment is NULL\n");
  }
  return 0;
}
