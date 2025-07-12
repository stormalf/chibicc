 #include <stdarg.h>
 #include <stdbool.h>
 #include <stdlib.h>
 #include <wchar.h>
 #include <stdio.h>
 #include "test.h"
 // Check varargs macros.  These examples are taken from C99 6.10.3.5.
 #define debug(...) fprintf (stderr, __VA_ARGS__)
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
   ASSERT(1234, x);
   ASSERT(5678, y);
   printf("\n");
 }
 
 // Check long long types.
 #define BIG64 18446744073709551615ull
 #define BIG32 4294967295ul
 #define BIG_OK (BIG64 / BIG32 == 4294967297ull && BIG64 % BIG32 == 0)
 #if !BIG_OK
   your preprocessor is broken;
 #endif
 #if BIG_OK
 #else
   your preprocessor is broken;
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
 static void
 test_varargs (const char *format, ...)
 {
   va_list args;
   va_start (args, format);
   va_list args_copy;
   va_copy (args_copy, args);
 
   const char *str;
   int number;
   float fnumber;
 
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
 }
 
 int
 main ()
 {
 
   // Check bool.
   _Bool success = false;
 
   // Check restrict.
   if (test_restrict ("String literal") == 0)
     success = true;
   char *restrict newvar = "Another string";
 
   // Check varargs.
   test_varargs ("s, d' f .", "string", 65, 34.234);
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
   dynamic_array[ni.number - 1] = 543;
 
   // work around unused variable warnings
   return (!success || bignum == 0LL || ubignum == 0uLL ||  newvar[0] == 'x' ||
 	   dynamic_array[ni.number - 1] != 543);
 
   ;
   return 0;
 }
