#include "test.h"
 /* confdefs.h */
#define PACKAGE_NAME "PostgreSQL"
#define PACKAGE_TARNAME "postgresql"
#define PACKAGE_VERSION "17devel"
#define PACKAGE_STRING "PostgreSQL 17devel"
#define PACKAGE_BUGREPORT "pgsql-bugs@lists.postgresql.org"
#define PACKAGE_URL "https://www.postgresql.org/"
#define CONFIGURE_ARGS " 'CC=chibicc' 'CFLAGS=-fpic' 'LDFLAGS=-fpic'"
#define PG_MAJORVERSION "17"
#define PG_MAJORVERSION_NUM 17
#define PG_MINORVERSION_NUM 0
#define PG_VERSION "17devel"
#define DEF_PGPORT 5432
#define DEF_PGPORT_STR "5432"
#define BLCKSZ 8192
#define RELSEG_SIZE 131072
#define XLOG_BLCKSZ 8192
/* end confdefs.h.  */

/* Does the compiler advertise C89 conformance?
   Do not test the value of __STDC__, because some compilers set it to 0
   while being otherwise adequately conformant. */
#if !defined __STDC__
# error "Compiler does not advertise C89 conformance"
#endif

#include <stddef.h>
#include <stdarg.h>
struct stat;
/* Most of the following tests are stolen from RCS 5.7 src/conf.sh.  */
struct buf { int x; };
struct buf * (*rcsopen) (struct buf *, struct stat *, int);
static char *e (p, i)
     char **p;
     int i;
{
  return p[i];
}

static char *f (char * (*g) (char **, int), char **p, ...)
{
  char *s;
  va_list v;
  va_start (v,p);
  s = g (p, va_arg (v,int));
  va_end (v);
  return s;
}

/* OSF 4.0 Compaq cc is some sort of almost-ANSI by default.  It has
   function prototypes and stuff, but not \xHH hex character constants.
   These do not provoke an error unfortunately, instead are silently treated
   as an "x".  The following induces an error, until -std is added to get
   proper ANSI mode.  Curiously \x00 != x always comes out true, for an
   array size at least.  It is necessary to write \x00 == 0 to get something
   that is true only with -std.  */
int osf4_cc_array ['\x00' == 0 ? 1 : -1];

/* IBM C 6 for AIX is almost-ANSI by default, but it replaces macro parameters
   inside strings and character constants.  */
#define FOO(x) 'x'
int xlc6_cc_array[FOO(a) == 'x' ? 1 : -1];

int test (int i, double x);
struct s1 {int (*f) (int a);};
struct s2 {int (*f) (double a);};
int pairnames (int, char **, int *(*)(struct buf *, struct stat *, int),
               int, int);

// Does the compiler advertise C99 conformance?
#if !defined __STDC_VERSION__ ||__STDC_VERSION__ < 199901L
# error "Compiler does not advertise C99 conformance"
#endif

#include <stdbool.h>
extern int puts (const char *);
extern int printf (const char *, ...);
extern int dprintf (int, const char *, ...);
extern void *malloc (size_t);

// Check varargs macros.  These examples are taken from C99 6.10.3.5.
// dprintf is used instead of fprintf to avoid needing to declare
// FILE and stderr.
#define debug(...) dprintf (2, __VA_ARGS__)
#define showlist(...) puts (#__VA_ARGS__)
#define report(test,...) ((test) ? puts (#test) : printf (__VA_ARGS__))
static void
test_varargs_macros (void)
{
  int x = 1234;
  int y = 5678;
  debug ("Flag");
  debug ("X = %d\n", x);
  showlist (The first, second, and third items.);
  report (x>y, "x is %d but y is %d", x, y);
}

// Check long long types.
#define BIG64 18446744073709551615ull
#define BIG32 4294967295ul
#define BIG_OK (BIG64 / BIG32 == 4294967297ull && BIG64 % BIG32 == 0)
#if !BIG_OK
  #error "your preprocessor is broken"
#endif
#if BIG_OK
#else
  #error "your preprocessor is broken"
#endif
static long long int bignum = -9223372036854775807LL;
static unsigned long long int ubignum = BIG64;

struct incomplete_array
{
  int datasize;
  double data[];
};

struct named_init {
  int number;
  const wchar_t *name;
  double average;
};

typedef const char *ccp;

static inline int
test_restrict (ccp restrict text)
{
  // See if C++-style comments work.
  // Iterate through items via the restricted pointer.
  // Also check for declarations in for loops.
  for (unsigned int i = 0; *(text+i) != '\0'; ++i)
    continue;
  return 0;
}

// Check varargs and va_copy.
static bool
test_varargs (const char *format, ...)
{
  va_list args;
  va_start (args, format);
  va_list args_copy;
  va_copy (args_copy, args);

  const char *str = "";
  int number = 0;
  float fnumber = 0;

  while (*format)
    {
      switch (*format++)
      {
      case 's': // string
        str = va_arg (args_copy, const char *);
        break;
      case 'd': // int
        number = va_arg (args_copy, int);
        break;
      case 'f': // float
        fnumber = va_arg (args_copy, double);
        break;
      default:
        break;
      }
    }
  va_end (args_copy);
  va_end (args);

  return *str && number && fnumber;
}


int
main (int argc, char **argv)
{
  int ok = 0;

ok |= (argc == 0 ||f (e, argv, 0) != argv[0] ||f (e, argv, 1) != argv[1]);


  // Check bool.
  _Bool success = false;
  success |= (argc != 0);

  // Check restrict.
  if (test_restrict ("String literal") == 0)
    success = true;
  char *restrict newvar = "Another string";

  // Check varargs.
  success &= test_varargs ("s, d' f .", "string", 65, 34.234);
  test_varargs_macros ();

  // Check flexible array members.
  struct incomplete_array *ia =
    malloc (sizeof (struct incomplete_array) + (sizeof (double) * 10));
  ia->datasize = 10;
  for (int i = 0; i < ia->datasize; ++i)
    ia->data[i] = i * 1.234;

  // Check named initializers.
  struct named_init ni = {
    .number = 34,
    .name = L"Test wide string",
    .average = 543.34343,
  };

  ni.number = 58;

  int dynamic_array[ni.number];
  dynamic_array[0] = argv[0][0];
  dynamic_array[ni.number - 1] = 543;

  // work around unused variable warnings
  ok |= (!success ||bignum == 0LL ||ubignum == 0uLL ||newvar[0] == 'x'
       ||dynamic_array[ni.number - 1] != 543);
  printf("\nOK=%d\n", ok);
  ASSERT(0, ok);
  return ok;
}