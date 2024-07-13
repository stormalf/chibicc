#include <stdio.h>
#include <assert.h>
# define __ASMNAME(cname)  __ASMNAME2 (__USER_LABEL_PREFIX__, cname)
# define __ASMNAME2(prefix, cname) __STRING (prefix) cname
#define __REDIRECT(name, proto, alias) name proto __asm__ (__ASMNAME (#alias))


// extern int __REDIRECT (fscanf, (FILE *__restrict __stream,
// 				const char *__restrict __format, ...),
// 		       __isoc99_fscanf) __wur;


#define TEST 10
#define TEST2 10
int toto(int a, int b) {
    return a + b;
}

// main function -
// where the execution of program begins
int main()
{
    static_assert(TEST == 10, "TEST is not 10");
    // prints hello world
    //printf("Hello World\n");
 
    return 0;
}