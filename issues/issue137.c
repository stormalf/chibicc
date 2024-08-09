#include <stdio.h>
#include <string.h>
static const char hello[] = "hello, hello!";

void test_compress(compr, comprLen, uncompr, uncomprLen) char *compr,
  *uncompr;
long comprLen, uncomprLen;
{
    int err;
    long len = (long)strlen(hello) + 1;

    //strcpy((char *)uncompr, "garbage");

    printf("uncompress(): %s\n", (char *)uncompr);
}

int main(int argc, char **argv)
{
    test_compress(&hello, 14, &hello, 14);
    return 0;
}
