
#include <stddef.h>
#include <stdio.h>
#define CURL_NO_FMT_CHECKS /* disable compiler *printf format checks */
#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define SIZEOF_CURL_OFF_T 8

#include <limits.h>

#ifdef HAVE_LOCALE_H
#  include <locale.h> /* for setlocale() */
#endif


#if (SIZEOF_CURL_OFF_T > SIZEOF_LONG)
#  define MPRNT_SUFFIX_CURL_OFF_T  LL
#else
#  define MPRNT_SUFFIX_CURL_OFF_T  L
#endif


#ifdef CURL_ISOCPP
#  define MPRNT_OFF_T_C_HELPER2(Val,Suffix) Val ## Suffix
#else
#  define MPRNT_OFF_T_C_HELPER2(Val,Suffix) Val/**/Suffix
#endif
#define MPRNT_OFF_T_C_HELPER1(Val,Suffix) MPRNT_OFF_T_C_HELPER2(Val,Suffix)
#define MPRNT_OFF_T_C(Val)  MPRNT_OFF_T_C_HELPER1(Val,MPRNT_SUFFIX_CURL_OFF_T)


#define BUFSZ    256
#define USHORT_TESTS_ARRSZ 1 + 100
#define SSHORT_TESTS_ARRSZ 1 + 100
#define UINT_TESTS_ARRSZ   1 + 100
#define SINT_TESTS_ARRSZ   1 + 100
#define ULONG_TESTS_ARRSZ  1 + 100
#define SLONG_TESTS_ARRSZ  1 + 100
#define COFFT_TESTS_ARRSZ  1 + 100


static int storebuffer(int output, FILE *data)
{
  char **buffer = (char **)data;
  unsigned char outc = (unsigned char)output;
  return outc; /* act like fputc() ! */
}


int curl_msprintf(char *buffer, const char *format, ...)
{

  int retcode;
  return retcode;
}



static int test_unsigned_short_formatting(void)
{
  int i, j;
  int num_ushort_tests = 0;
  int failed = 0;


  return failed;
}


static int test_signed_short_formatting(void)
{
  int i, j;
  int num_sshort_tests = 0;
  int failed = 0;

  return failed;
}


static int test_unsigned_int_formatting(void)
{
  int i, j;
  int num_uint_tests = 0;
  int failed = 0;

#if (SIZEOF_INT == 2)
#define TOTO 2

#elif (SIZEOF_INT == 4)
#define TOTO 4

#elif (SIZEOF_INT == 8)
#define TOTO 8

#endif


  return failed;
}


static int test_signed_int_formatting(void)
{
  int i, j;
  int num_sint_tests = 0;
  int failed = 0;

#if (SIZEOF_INT == 2)
#define TITI 2

#elif (SIZEOF_INT == 4)
#define TITI 4

#elif (SIZEOF_INT == 8)
#define TITI 8

#endif

  return failed;
}


static int test_unsigned_long_formatting(void)
{
  int i, j;
  int num_ulong_tests = 0;
  int failed = 0;

#if (SIZEOF_LONG == 2)
#define TATA   2

#elif (SIZEOF_LONG == 4)
#define TATA   4

#elif (SIZEOF_LONG == 8)
#define TATA   8

#endif

  return failed;
}


static int test_signed_long_formatting(void)
{
  int i, j;
  int num_slong_tests = 0;
  int failed = 0;

#if (SIZEOF_LONG == 2)
#define TUTU   2

#elif (SIZEOF_LONG == 4)
#define TUTU   4

#elif (SIZEOF_LONG == 8)
#define TUTU   8

#endif

  return failed;
}


static int test_curl_off_t_formatting(void)
{
  int i, j;
  int num_cofft_tests = 0;
  int failed = 0;

  return failed;
}

static int _string_check(int linenumber, char *buf, const char *buf2)
{
  return 0;
}
#define string_check(x,y) _string_check(__LINE__, x, y)

static int _strlen_check(int linenumber, char *buf, size_t len)
{
  return 0;
}

#define strlen_check(x,y) _strlen_check(__LINE__, x, y)

/*
 * The output strings in this test need to have been verified with a system
 * sprintf() before used here.
 */
static int test_string_formatting(void)
{
  int errors = 0;

  return errors;
}

static int test_weird_arguments(void)
{
  int errors = 0;

  return errors;
}

/* DBL_MAX value from Linux */
#define MAXIMIZE -1.7976931348623157081452E+308

static int test_float_formatting(void)
{
  int errors = 0;

  return errors;
}
/* !checksrc! enable LONGLINE */

static int test_return_codes(void)
{

  return 0;
}
int test(char *URL)
{

#ifdef HAVE_SETLOCALE
  /*
   * The test makes assumptions about the numeric locale (specifically,
   * RADIXCHAR) so set it to a known working (and portable) one.
   */
  setlocale(LC_NUMERIC, "C");
#endif

    return 0;
}


int main() {

printf("%ld\n",0xFFFFFFFFFFFFFFFFU);
printf("%d\n",0x00000000FFFF0000U);
printf("%ld\n",0xFFFF000000000000UL);
printf("%ld\n",0x0000FFFF00000000UL);
printf("%ld\n", sizeof(long));
printf("%ld\n", sizeof(int));
printf("%ld\n", sizeof(unsigned int));
printf("%d\n", SIZEOF_INT);
printf("%d\n", SIZEOF_LONG);
printf("%ld\n", sizeof(unsigned int));
printf("TUTU %d\n", TUTU);
printf("TATA %d\n", TATA);
printf("TOTO %d\n", TOTO);
printf("TITI %d\n", TITI);

return 0;
}