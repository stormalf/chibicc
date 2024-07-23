#include <stdio.h>

#define SIZEOF_CURL_OFF_T 8



#if defined(__GNUC__) && ((__GNUC__ >= 3) || \
  ((__GNUC__ == 2) && defined(__GNUC_MINOR__) && (__GNUC_MINOR__ >= 7)))
#  define UNUSED_PARAM __attribute__((__unused__))
#  define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#  define UNUSED_PARAM /* NOTHING */
#  define WARN_UNUSED_RESULT
#endif



static int
krb5_decode(void *app_data, void *buf, int len,
            int level UNUSED_PARAM,
            char *conn UNUSED_PARAM)
{

  return len;
}



int main(int argc, char **argv)
{
  int i;
  for (i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }
  return 0;
}