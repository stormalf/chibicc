# issues

List all issues found and fixed

## issues and pull requests fixed

    - Add dockerfile #23 pull request from 0xc0
    - Issue #30 from ludocode
    - Typecheck void type expressions in return and assignment #41 pull request from StrongerXi
    - Binary add segfaults when at least 1 arg is non-numeric, and both are non-pointer types #42 pull request from StrongerXi
    - It's UB to have a call to va_start without a corresponding call to va_end #51 pull request from camel-cdr
    - Fix bug in codegen.c if (ty->size == 4) instead of if (ty->size == 12) #52 pull request from mtsamis
    - difficulty in understanding priorities. #54 pull request from ihsinme
    - Fixed bug in preprocessor process extraneous tokens. #95 pull request from memleaker
    - Hashmap: Do not insert duplicate keys #98 pull request from boki1
    - issue #65 assembler error on larger than 32-bit bitfields from GabrielRavier
    - issue #28 bitfield validation from zamfofex
    - issue #48 asan issues with memcmp from math4tots
    - issue #36 assertion when using empty structs from edubart
    - issue #31 Anonymously named bitfield member segfaults compiler from Anonymously named bitfield member segfaults compiler fixed by zamfofex
    - issue #45 When anonymous union field is specified by designator, compiler crashe from vain0x fixed by zamfofex
    - issue #80 Size of string is wrong from tyfkda
    - issue #72 Internal error when initializing array of long with string literals from GabrielRavier
    - issue #47 postfix tails on compound literals from vain0x
    - issue #62 Nested designators error from sanxiyn
    - issue #37 Using goto inside statement expressions gives an error from edubart
    - issue #63 Function type parameter without identifier errs from sanxiyn
    - issue #69 Internal error on long double initializer from GabrielRavier
    - issue #71 Codegen error on _Atomic long double operation assignments from GabrielRavier
    - Fix atomic fetch operations #101 pull request from chjj
    - issue #107 string intialized by function-like failed during compilation
    - issue #108 if a macro ends a line and the next line starts by "#ifdef" the "#" is not recognized starting from beginning of the line.
    - issue #109 managing #warning as preprocess instruction
    - issue #110 union initialized by  "input_control_param_t it = { .id = p_input, .time.i_val = 1};" failed due to comma.
    - issue #113 depending where is _Atomic parsing failed
        ./issues/issue113.c:7:         char *_Atomic str; /**< Current value (if character string) */
                                             ^ expected ','
    - issue #116 (issue #110 at rui314/chibicc) token incorrectly splitted into two tokens the first one considered wrongly as number
        ./issues/issue116.c:26:     make_dh(1024_160);
                                                ^ expected ','
    - issue #117 parsing failed if a generic argument in macro starts by a number example  ...(void))fromtype##2obj_decode... in this case chibicc considers wrongly 2 as a number.
    - issue #118 issues/issue118.c:1: NID_sha_224
                                     ^ parse.c: in primary : error: undefined variable
    - issue #119 caused by _Complex attribute   /usr/include/x86_64-linux-gnu/bits/cmathcalls.h:55: __MATHCALL (cacos, (_Mdouble_complex_ __z));
                                                                                                                                ^ expected ','
    - issue #120 in VLC static_assert function outside a function caused an issue with chibicc
        issues/issue120.c:30: static_assert(AOUT_CHANIDX_MAX == AOUT_CHAN_MAX, "channel count mismatch");
                                                             ^ tokenize.c: in skip : expected ','
    - issue #121 in VLC static_assert function with sizeof or offsetof caused an issue with chibicc:
        ./include/stddef.h:11: #define offsetof(type, member) ((size_t)&(((type *)0)->member))
                                                                       ^ tokenize.c: in skip : expected ','
    - issue #122 in util_linux compilation it fails during assembly "file number less than 0" when #line generates negative number
    - issue #123 in util_linux compilation fails with regex when a local variable in arguments it's used for another argument.
           extern int regexec(..., size_t __nmatch,...   regmatch_t __pmatch[_Restrict_arr_  _REGEX_NELTS(__nmatch)],...
    - issue #124 some macro defined after their used caused issue with chibicc. gcc allows it. 
    - issue #125 extended assembly not managed yet. First taken in account of extended assembly (basic one only one operand)
    - issue #126 old C style with declaration argument type after the function parameters and before the beginning of the function body :
            size_t strlcpy(dst, src, siz) char *dst; const char *src; size_t siz; {...
            strlcpy.c:44:2: error:  char *dst;
                                    ^ tokenize.c: in skip : expected '{'
    - issue #127 incorrect fix for old C style that cause issue later during linkage.
    - issue #128 union initialized by an expression failed :
            issues/issue127.c:49:     union sockaddr_u localaddr = lfdi->remoteaddr;
                                                                 ^ tokenize.c: in skip : expected ','
    - issue #131 (ISS-131) parsing issue when trying to compile nginx project caused by fix #121                                                                
    - issue #133 with old C style function declaration using comma to declare same type of variable : 
        test/example.c:89: Byte *compr, *uncompr;
                                      ^ tokenize.c: in skip : expected ';'
    - issue #134 (ISS-134) with parameter expression during zlib project due to bug in func_params2.                                     
    - issue #136 (ISS-136) zlib project error with unknown extension: main.c : in get_file_type : unknown file extension: libz.so.1.2.12                             
    - issue #139 (ISS-139) extended assembly compiling but execution doesn't return the correct result.