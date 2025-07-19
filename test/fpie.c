
#include "test.h"
char message[] = "Hello World";
int main(int argc, char *argv[], char *envp[])
{
    puts(message);
    printf("%ld\n", sizeof(message));
    ASSERT(12, sizeof(message));
    return 0;
}