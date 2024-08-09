
//#include <string.h>
typedef unsigned char  Byte;  /* 8 bits */
typedef unsigned long  uLong; /* 32 bits or more */
#define OF(args)  args

static char hello[] = "hello, hello!";

void test_compress OF((Byte * compr, uLong comprLen,
                       Byte *uncompr, uLong uncomprLen));

/* ===========================================================================
 * Test compress() and uncompress()
 */
void test_compress(compr, comprLen, uncompr, uncomprLen)
    Byte *compr,
    *uncompr;
uLong comprLen, uncomprLen;
{
    int err;
    uLong len = 14;



    // if (strcmp((char *)uncompr, hello))
    // {
    //     return;
    // }
    // else
    // {
    //     //printf("uncompress(): %s\n", (char *)uncompr);
    // }
}


int main() {
    return 0;
}