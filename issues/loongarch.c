//#include <arm_acle.h>
int
main ()
{
unsigned int crc = 0;
    crc = __crc32cb(crc, 0);
    crc = __crc32ch(crc, 0);
    crc = __crc32cw(crc, 0);
    crc = __crc32cd(crc, 0);
    /* return computed value, to prevent the above being optimized away */
    return crc == 0;
;
return undeclared_func(123);
}