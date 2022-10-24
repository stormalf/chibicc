
// if we move the use of the macro after #define statement chibicc compiles it fine.
// but if the macro is used before its definition, chibicc fails to compile it. gcc compiles it fine!
static const char rcsid[] __attribute__((unused)) =
    "@(#) $Header$";

#define __attribute__(args)

int main(void)
{
    return 0;
}