# chibicc: A Small C Compiler from Rui Ueyama

This project has been forked from https://github.com/rui314/chibicc

I want to play with it and to add some other options like choosing other linker than default ld.
It's for learning purposes too, to try to understand existing code and to extend it.
Using PVS.studio to find some potential issues and fix them.

Trying to work on issues and pull requests done in the original repository.

## usage

./chibicc --help
or
./chibicc -h

    chibicc is a C compiler based on chibicc created by Rui Ueyama.
    See original project https://github.com/rui314/chibicc for more information
    this chibicc contains only some differences for now like new parameters
    chibicc usage :
    --help or -h print the help
    --version or -v print the version of chibicc
    -cc1 run the cc1 function needs -cc1-input (-cc1-output optional) parameter
    -fuse-ld to specify other linker than ld used by default
    -x Specify the language of the following input files.
        Permissible languages include: c assembler none
        'none' means revert to the default behavior of
        guessing the language based on the file's extension.
    -S generate assembly file
    -o path to output executable if omitted a.out generated
    -c path to source to compile
    -Xlinker <arg> Pass <arg> on to the linker.
    -Wl,<options> Pass comma-separated <options> on to the linker.
    -z <arg> Pass <arg> on to the linker.
    -soname <arg> Pass -soname <arg> on to the linker.
    --version-script <arg> Pass --version-script <arg> to the linker.
    -I<path> Pass path to the include directories
    -L<path> Pass path to the lib directories
    -D<macro> define macro example -DM13
    -U<macro> undefine macro example -UM13
    -s to strip all symbols during linkage phasis
    -M -MD -MP -MMD -MF <arg> -MT <arg> -MQ <arg> compiler write a list of input files to
        stdout in a format that "make" command can read. This feature is
        used to automate file dependency management
    -fpic or -fPIC Generate position-independent code (PIC)
    -fno-pic disables the generation of position-independent code with relative address references
    -fcommon is the default if not specified, it's mainly useful to enable legacy code to link without errors
    -fno-common specifies that the compiler places uninitialized global variables in the BSS section of the object file.
    -static  pass to the linker to link a program statically
    -pthread pass to the linker to link with lpthread library
    -shared pass to the linker to produce a shared object which can then be linked with other objects to form an executable.
    -hashmap-test to test the hashmap function
    -idirafter <dir> apply to lookup for both the #include "file" and #include <file> directives.
    -### to dump all commands executed by chibicc
    -debug to dump all commands executed by chibicc in a log file in /tmp/chibicc.log
    -E Stop after the preprocessing stage; do not run the compiler proper.
        The output is in the form of preprocessed source code, which is sent to the standard output.
        Input files that don’t require preprocessing are ignored.
    -rpath <dir> Add a directory to the runtime library search path this parameter is passed to the linker.
        This is used when linking an ELF executable with shared objects.
        All -rpath arguments are concatenated and passed to the runtime linker,
        which uses them to locate shared objects at runtime.
        The -rpath option is also used when locating shared objects
        which are needed by shared objects explicitly included in the link.
    -dumpmachine it's required by some projects returns x86_64-linux-gnu
    -dotfile generates a file with .dot extension that can be visualized using graphviz package
    chibicc [ -o <path> ] <file>

## Examples

Note that probably you need to define the include parameter and lib parameter to be able to execute these examples outside the chibicc directory. If you forgot you will have similar error message :

    /usr/include/stdio.h:33: #include <stddef.h>
                                    ^ stddef.h: cannot open file: No such file or directory

To solve it, add the include and lib parameter like below assuming that we are in the parent chibicc directory :

        chibicc pointerofpointers.c -I./chibicc/include -L./chibicc/lib

printing the help

    ./chibicc --help

    ./chibicc -h

printing the version

    ./chibicc --version

    ./chibicc -v

compiling and generating an executable

    ./chibicc -o ./test/hello ./test/hello.c

specifying another linker than the default one here lld :

    ./chibicc -o ./test/hello ./test/hello.c -fuse-ld ld.lld

specifying another linker than the default one here mold (https://github.com/rui314/mold)

    ./chibicc -o ./test/hello ./test/hello.c -fuse-ld mold

generating assembly file

    ./chibicc -S ./test/hello.c

generating a.out file if no parameter -o provided

    ./chibicc ./test/hello.c

generating the object only : it generates the pointerofpointers.o

    ./chibicc -c pointerofpointers.c -I./chibicc/include -L./chibicc/lib

generating executable from objects :

    ./chibicc pointerofpointers.o -o pointersofpointers

defining condition at compile time :

    ./chibicc -o ./test/mydefine ./test/define.c -DM13 -I../include -L../lib
    ./test/mydefine
    3

undefining condition at compile time :

    ./chibicc -o ./test/mydefine ./test/define.c -UM13 -I../include -L../lib
    ./test/mydefine
    4

By default the symbol tables is populated:

    chibicc -o ./test/mydefine ./test/define.c
    objdump -t ./test/mydefine
    ./test/mydefine:     file format elf64-x86-64
    SYMBOL TABLE:
    0000000000000000 l    df *ABS*  0000000000000000              crt1.o
    0000000000400320 l     O .note.ABI-tag  0000000000000020              \_\_abi_tag
    0000000000000000 l    df *ABS*  0000000000000000              crtstuff.c

Stripping symbol tables during linkage phasis adding -s parameter :

    ./chibicc -o ./test/mydefine ./test/define.c -s
    objdump -t ./test/mydefine
    ./test/mydefine:     file format elf64-x86-64
    SYMBOL TABLE:
    no symbols

other way to generate assembly file

    ./chibicc ./test/define.c -cc1 -cc1-input ./test/define.c -cc1-output mydefine.s

generating dependencies in std output :

    ./chibicc  ./test/define.c -M
    define.o: \
    ./test/define.c \
    /usr/include/stdio.h \
    /usr/include/x86_64-linux-gnu/bits/libc-header-start.h \
    /usr/include/features.h \

generating dependencies in a output file with ".d" extension and generating executable a.out :

    ./chibicc  ./test/define.c -MD
    ls *.d
    define.d

## options always passed to the linker

it means that if you don't use the ld linker or ld.lld probably some options should be conditionned depending your linker

    lld-link: warning: ignoring unknown argument '-o'
    lld-link: warning: ignoring unknown argument '-m'
    lld-link: warning: ignoring unknown argument '-L/usr/lib/gcc/x86_64-linux-gnu/9'
    lld-link: warning: ignoring unknown argument '-L/usr/lib/x86_64-linux-gnu'
    lld-link: warning: ignoring unknown argument '-L/usr/lib64'
    lld-link: warning: ignoring unknown argument '-L/lib64'
    lld-link: warning: ignoring unknown argument '-L/usr/lib/x86_64-linux-gnu'
    lld-link: warning: ignoring unknown argument '-L/usr/lib/x86_64-pc-linux-gnu'
    lld-link: warning: ignoring unknown argument '-L/usr/lib/x86_64-redhat-linux'
    lld-link: warning: ignoring unknown argument '-L/usr/lib'
    lld-link: warning: ignoring unknown argument '-L/lib'
    lld-link: warning: ignoring unknown argument '-dynamic-linker'
    lld-link: warning: ignoring unknown argument '-lc'
    lld-link: warning: ignoring unknown argument '-lgcc'
    lld-link: warning: ignoring unknown argument '--as-needed'
    lld-link: warning: ignoring unknown argument '-lgcc_s'
    lld-link: warning: ignoring unknown argument '--no-as-needed'

## options ignored

List of options ignored :

    "-O"
    "-W"
    "-g"
    "-std="
    "-std"
    "-ffreestanding"
    "-fno-omit-frame-pointer"
    "-fno-stack-protector"
    "-fno-strict-aliasing"
    "-m64"
    "-m32"
    "--whole-archive"
    "--no-whole-archive"
    "-Bsymbolic"
    "-z"
    "defs"
    "-flto"
    "-pedantic"
    "-nostdinc"
    "-mno-red-zone"
    "-w"


## Dockerfile and devcontainer

Adding dockerfile suggested by 0xc0 https://github.com/0xc0/chibicc/tree/new
To build :

    docker build -t chibicc .

Adding also a devcontainer for those that want to use visual code inside a container (needs vs code extension remote-containers).

## Examples of C projects compiled successfully using chibicc

tcc : tcc compiler (https://github.com/LuaDist/tcc.git)

    chibicc -o tcc tcc.c -DTCC_TARGET_X86_64 -O2 -g -Wall -Wno-pointer-sign -lm -ldl
    chibicc -o libtcc1.o -c lib/libtcc1.c -O2 -Wall
    ar rcs libtcc1.a libtcc1.o
    chibicc -o libtcc.o -c libtcc.c -DTCC_TARGET_X86_64 -O2 -g -Wall -Wno-pointer-sign
    ar rcs libtcc.a libtcc.o
    ./texi2pod.pl tcc-doc.texi tcc.pod
    pod2man --section=1 --center=" " --release=" " tcc.pod > tcc.1
    chibicc -o libtcc_test tests/libtcc_test.c libtcc.a -I. -O2 -g -Wall -Wno-pointer-sign -lm -ldl

for some projects you need to define CC=chibicc before executing ./configure.

curl : https://github.com/curl/curl.git

    autoreconf -fi
    CC=chibicc CFLAGS=-fpic LDFLAGS=-fpic ./configure --with-openssl
    make

        make[2]: Entering directory ...
        CC       libcurl_la-altsvc.lo
        CC       libcurl_la-amigaos.lo
        ...
        CC       ../lib/curl_multibyte.o
        CC       ../lib/version_win32.o
        CC       ../lib/dynbuf.o
        CCLD     curl

openssl : https://github.com/openssl/openssl.git
Very interesting project that helps to find some bugs (see issue from 108 to 118). It doesn't link well for now!

    CC=chibicc ./Configure
    
    You need to remove from the file from openssl/crypto/perlasm/x86_64-xlate.pl

    	my $section='.note.gnu.property, #alloc';

    by :

    	my $section='.note.gnu.property';

    make

    It fails for extended assembly :

    chibicc  -Iinclude  -fPIC -pthread -m64 -Wall -O3 -DOPENSSL_BUILDING_OPENSSL -DNDEBUG   -c -o engines/afalg-dso-e_afalg.o engines/e_afalg.c
    /usr/include/x86_64-linux-gnu/asm/swab.h:10:    __asm__("bswapl %0" : "=r" (val) : "0" (val));
                                                                     ^ parse.c : in asm_stmt : extended assembly not managed yet!

    Replace chibicc by gcc for compiling this one :

    gcc  -Iinclude  -fPIC -pthread -m64 -Wall -O3 -DOPENSSL_BUILDING_OPENSSL -DNDEBUG   -c -o engines/afalg-dso-e_afalg.o engines/e_afalg.c

    make

openssh-portable : https://github.com/openssh/openssh-portable.git

    autoreconf -fi
    CC=chibicc ./configure
    make


luajit: https://github.com/LuaJIT/LuaJIT.git 
    
    CC=chibicc make


git: https://github.com/git/git.git

    autoreconf -fi
    CC=chibicc CFLAGS=-fPIC ./configure
    make

nmap: https://github.com/nmap/nmap.git

    CC=chibicc CFLAGS=-fPIC ./configure
    make
    ...
    chibicc -o ncat -fPIC   ncat_main.o ncat_connect.o ncat_core.o ncat_posix.o ncat_listen.o ncat_proxy.o ncat_ssl.o base64.o http.o util.o sys_wrap.o http_digest.o ncat_lua.o ../nsock/src/libnsock.a ../nbase/libnbase.a -lssl -lcrypto -lpcap ./../liblua/liblua.a -lm
    make[1]: Leaving directory '../nmap/ncat'

## Limits

Some C projects doesn't compile for now. It helps to find some bugs and to try to fix them!

VLC : https://github.com/videolan/vlc.git 

    ./boostrap
    CC=chibicc CFLAGS="-fPIC" DEFS="-DHAVE_CONFIG_H -DHAVE_ATTRIBUTE_PACKED -DVLC_USED -DVLC_API -DVLC_DEPRECATED -DVLC_MALLOC" ./configure --disable-lua --disable-a52 --disable-xcb --disable-qt --disable-po --target=linux
    make all

    VLC doesn't compile with chibicc because it has some extended assembly inline that are not managed yet. Even if for this part I'll try to use gcc it failed during linking with multiple definitions. If I use gcc to compile VLC it compiles fine. Perhaps mixing chibicc and gcc is not a great idea!
    
util-linux : https://github.com/util-linux/util-linux.git

    ./autogen.sh
    CC=chibicc CFLAGS=-fPIC ./configure

    It fails only on extended assembly. Compiling fine lots of tools like fdisk, setsid, kill, mount...


## TODO

- trying to compile other C projects from source to see what is missing or which bug we have with chibicc.
- trying to manage other assembly functions like \_\_asm\_\_("xchgb %b0,%h0": "=Q"(x):"0"(x));

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

## debug

To debug with gdb don't forget to use the set follow-fork-mode child because chibicc creates a child job.

    gdb ./chibicc
    (gdb) set follow-fork-mode child
    (gdb) r issues/issue116.c -o issues/issue116
    Starting program: /home/stormalf/ubuntu/chibicc/chibicc issues/issue116.c -o issues/issue116
    [Attaching after process 174090 fork to child process 174091]
    [New inferior 2 (process 174091)]
    [Detaching after fork from parent process 174090]
    [Inferior 1 (process 174090) detached]
    process 174091 is executing new program: /home/stormalf/ubuntu/chibicc/chibicc
    [Switching to process 174091]

    Thread 2.1 "chibicc" hit Breakpoint 1, 0x0000000000432726 in parse () at parse.c:3703
    3703          return "UNREACHABLE";    // Atomic e


## diagram

Example of diagram generated with -dotfile parameter :

![diagram](https://github.com/stormalf/chibicc/blob/main/asm.png)


## release notes

1.0.14 Removing sanitizing functions, causing issue during git compile. Fixing issue caused by fix issue 120. Fixing issue with -I \<dir\>. Fixing also the preprocess when some macros are defined after they are used, gcc allows it. For now the temporary fix manages only macro with empty body that they are used before their definition. Fixing issue #126 about old C style skipping for now the extra tokens. Fixing issue #128 about union initialized by an expression. Fixing a basic extended assembly #125 (partially) for now only something like 	\__asm\__("bswapl %0" : "=r" (val) : "0" (val)); works (a lot of work to forecast to add other assembly possibilities step by step). Fixing #127(#126) more securely (ignoring was not enough causing issue during linkage). Fixing a mistake on removing the fix for issue #121 that caused an infinite loop.



## old release notes

1.0.0 Initial version

1.0.1 adding --version -v option and fixing the -cc1 parameter that caused segmentation fault if other mandatory parameters are missing.
trying to document cc1 and x options and adding a max length control parameter. Adding documentation for other parameters too.

1.0.2 fixing issue with cc1 parameter only -cc1-input parameter is mandatory. Finishing parameters documentation.

1.0.3 trying to add some sanitizing functions and check if arguments have valid allowed characters (probably too strict!).

1.0.4 Fixing the output directory for dependencies "xxx.d" when -MD option is set, the output "xxx.d" file is generated in the current directory if no -o parameter defined or in the directory defined by -o parameter (issue #30). Adding Dockerfile and a devcontainer for those who want to play with that (issue #23). Typecheck void type expressions in return and assignment (issue #41). Binary add segfaults when at least 1 arg is non-numeric, and both are non-pointer types (issue #42). It's UB to have a call to va_start without a corresponding call to va_end (issue #51). Fix bug in codegen.c (issue #52). fix issue in main.c (issue #54). Fixed bug in preprocessor process extraneous tokens (issue #95). Hashmap: Do not insert duplicate keys (issue #98).

1.0.5 Fixing assembler error on larger than 32-bit bitfields (issue #65) by GabrielRavier. Fixing bitfield validation by zamfofex (issue #28). Replacing memcmp by strncmp (issue #48) by math4tots. Fixing empty structs as one-byte object (issue #36) by edubart.

1.0.6 Anonymously named bitfield member segfaults compiler (issue #31). Fixing anonymous union field (issue #45) by zamfofex. Fixing wrong size of string initialized by braces (issue #80) by zamfofex.

1.0.7 Internal error when initializing array of long with string literals (issue #72) by GabrielRavier. Fixing postfix tails on compound literals (issue #47) by zamfofex. Trying to fix nested designators error(issue #62). Fixing Using goto inside statement expressions gives an error (issue #37) by zamfofex. Fixing function type parameter without identifier errs (issue #63) by zamfofex.

1.0.8 Internal error on long double initializer (issue #69). Codegen error on atomic long double operation assignments (issue #71). Fix atomic fetch operations (issue #101) by chjj. Adding -soname < arg > and -rpath < dir > parameters (needed to be able to compile curl from source). Soname is used to create a symbolic link and rpath is passed to the linker. Testing chibicc with some C projects (compiling fine tcc, curl).

1.0.9 Adding pthread and pedantic to omitted parameters list. Added -fno-pic parameter. Adding ignored parameter: m32, nostdinc. Adding -dumpmachine parameter. Fixing issue with \_\_has_attribute(diagnose_if). Adding lots of attributes that can be applied to function (for now ignored them) : "\_\_attribute\_\_((noreturn))", "\_\_attribute\_\_((returns_twice))",
"\_\_attribute\_\_((noinline))", "\_\_attribute\_\_((always_inline))", "\_\_attribute\_\_((flatten))", "\_\_attribute\_\_((pure))",
"\_\_attribute\_\_((nothrow))", "\_\_attribute\_\_((sentinel))", "\_\_attribute\_\_((format))", "\_\_attribute\_\_((format_arg))",
"\_\_attribute\_\_((no_instrument_function))", "\_\_attribute\_\_((section))", "\_\_attribute\_\_((constructor))",
"\_\_attribute\_\_((destructor))", "\_\_attribute\_\_((used))", "\_\_attribute\_\_((unused))", "\_\_attribute\_\_((deprecated))",
"\_\_attribute\_\_((weak))", "\_\_attribute\_\_((alias))", "\_\_attribute\_\_((malloc))",
"\_\_attribute\_\_((warn_unused_result))", "\_\_attribute\_\_((nonnull))", "\_\_attribute\_\_((externally_visible))",
"\_\_attribute\_\_((visibility(\"default\")))", "\_\_attribute\_\_((visibility(\"hidden\")))",
"\_\_attribute\_\_((visibility(\"protected\")))", "\_\_attribute\_\_((visibility(\"internal\")))"

1.0.10 Fixing issue about string initialized by function-like (issue #107). Fixing issue when a macro ends a line and the next line starts by "#ifdef" the "#" is not recognized starting from beginning of the line (issue #108). Managing \#warning as preprocessor instruction (issue #109). Fixing issue with union initializer when comma found like "input_control_param_t it = { .id = p_input, .time.i_val = 1};" (issue #110) and input_control_param_t it = { .id = p_input,} (issue #113). Removing fix for issue 106 (caused other issues with VLC when trying to compile).

1.0.11 Fixing issue #113 about \_Atomic when it's placed after the type. Fixing other issue like issue #108 sometimes some #ifdef are not recognized if a macro ends the previous line and the next line starting by a preprocessing instruction. Managing differently -soname and adding option -z, and --version-script. Adding -debug option to write commands in /tmp/chibicc.log (later I'll add some debugs info/values on this file to help to fix bugs). Adding 2 functions in stdatomic.h needed by VLC atomic_compare_exchange_strong_explicit(object, expected, desired, success, failure) that returns false for now and atomic_compare_exchange_weak_explicit(object, expected, desired, success, failure) that returns false too. Managing .lo files (libtool object). Adding generic path for Fix 'gcc library path is not found' on some platforms #108 by [Stardust8502](https://github.com/Stardust8502/chibicc). 

1.0.12 Adding -dotfile parameter that generates a xxx.dot file that we can visualized using graphviz package by [hdewig100](https://github.com/hedwig100/chibicc). Adding in error message chibicc file name and function when a message error is displayed to help for debugging. Adding in Makefile the way to create shared library libchibicc.so. Fixing issue #116 with 1024_160 splitted wrongly in two tokens. Fixing issue #117 with number after generic parameter like "fromtype##2obj_decode". Fixing issue #118 same as 117, to allow some identifiers to start by number when they are generics. Linking lpthread if -pthread is passed. Ignoring -z and -Bsymbolic. Fixing the issue with linkage need to add current directory to the path before the others (probably it's a security issue because it means that for compiling the objects library found in the current path will be taken in priority!)
Fixing issue #119 about cmathcalls. Removing fix for #119 caused an infinite loop and fixing it by adding _Complex as attribute like _Atomic.

1.0.13 Adding other projects compiled successfully with chibicc. Adding some information in debug file like all tokens generated by tokenize function. Fixing some issues found with vlc static_assert function outside a function(#120 and #121). Adding -no-whole-archive and -whole-archive as ignored parameters. Fixing issue with #line that generates negative numbers that caused assembly issue. Fixing issue with argument used twice in regexec function that caused "undefined variable".
