

/* Value type.  */
/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 294 "sys-utils/hwclock-parse-date.y"

    int intval;
    char *textintval;
    struct timespec timespec;
    int rel;

#line 454 "sys-utils/hwclock-parse-date.c"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

int main(void)
{

    return 0;
}