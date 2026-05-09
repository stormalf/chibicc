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
     -pie Create a dynamically linked position independent 
     -fpie Create a dynamically linked position independent
     -fPIE Create a dynamically linked position independent
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
     -dM Print macro definitions in -E mode instead of normal output
     -print print all tokens in a log file in /tmp/chibicc.log 
     -A print Abstract Syntax Tree in a log file in /tmp/chibicc.log 
     -msse enabling sse support 
     -mno-sse disabling sse support 
     -msse2 enabling sse2 support 
     -mno-sse2 disabling sse2 support 
     -msse3 enabling sse3 support 
     -mno-sse3 disabling sse3 support 
     -msse4 enabling sse4 support 
     -mno-sse4 disabling sse4 support 
     -msse4.1 enabling sse4.1 support 
     -mcrc32 enabling crc32 instruction support 
     -nostdlib  Do not use the standard system startup files or libraries when linking 
     -nostdinc Do not use the standard system header files when compiling 
     -std=c99 generates an error on implicit function declaration (without -std only a warning is emitted) 
     -std=c11 generates an error on implicit function declaration (without -std only a warning is emitted) 
     -mmmx enabling mmx instructions 
     -mno-mmx disabling mmx instructions 
     -mavx enabling avx instructions 
     -mavx2 enabling avx2 instructions 
     -print-search-dirs prints minimal information on install dir. 
     -Werror any warning is sent as an error and stops the compile 
     -f-omit-frame-pointer omits frame pointer and uses rsp-relative addressing. Minimal stack usage 
     -f-no-omit-frame-pointer always keeps frame pointer (default) 
     -g enabling debug symbols 
     -O0 disabling optimization 
     -O or -O1 enabling optimization level 1 
     -O2 enabling optimization level 2 
     -O3 enabling optimization level 3 
     chibicc [ -o <path> ] <file>

## compile

To compile chibicc with make :

    make

To compile chibicc with cmake you need to install boost library. Then you can compile it with cmake :

    cmake -S . -B ./build  
    cd build
    make

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
  
    "-P"
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Wno-switch"
    "-Wno-clobbered"
    "-Wduplicated-cond" 
    "-Wno-unused-variable"    
    "-Wno-unused-parameter"
    "-Wno-sign-compare"
    "-Wno-format-y2k"
    "-Wno-uninitialized"
    "-Wmissing-prototypes"
    "-Wmissing-declarations"
    "-Wredundant-decls"
    "-Winit-self"     
    "-fno-math-errno"
    "-fno-rounding-math"
    "-fno-signaling-nans"
    "-fcx-limited-range"
    "-funsafe-math-optimizations"
    "-funroll-loops"
    "-ffreestanding"
    "-funwind-tables"
    "-fno-stack-protector"
    "-fno-strict-aliasing"
    "-m64"
    "-m32"
    "--whole-archive"
    "--no-whole-archive"
    "-fsigned-char"
    "-Bsymbolic"
    "-pedantic"
    "-pedantic-errors"
    "-nostdinc"
    "-mno-red-zone"
    "-fvisibility=default"
    "-fvisibility=hidden"
    "-Wsign-compare"
    "-Wundef"
    "-Wpointer-arith"
    "-Wvolatile-register-var"
    "-Wformat"
    "-Wformat-security"
    "-Wduplicated-branches"
    "-Wbad-function-cast"
    "-Wwrite-strings"
    "-Wlogical-op"
    "-Wshadow=local"
    "-Wmultistatement-macros"
    "-fstack-protector"
    "-fstack-protector-strong"
    "-fstack-clash-protection"
    "-fdiagnostics-show-option"
    "-fasynchronous-unwind-tables"
    "-fexceptions"
    "-fprofile-arcs"
    "-ftest-coverage"
    "-w"
    "--param=ssp-buffer-size=4"
    "-fno-lto"
    "-fprofile-arcs"
    "-ftest-coverage"
    "-ffat-lto-objects"
    "-static-libstdc++"
    "-static-libgcc"
    "-pipe"   
    "-Wno-missing-declarations"
    "-mindirect-branch-register"
    "-fno-fast-math"
    "-fno-strict-overflow"
    "-fexcess-precision=standard"
    "-Wno-shadow"
    "-mpku"
    "-mshstk"
    "-mlwp"
    "-mrtm"        
    "-mserialize"
    "-mtsxldtrk"
    "-muintr"
    "-mwbnoinvd"
    "-mrdpid"
    "-mfsgsbase"
    "-mavx..."
    "-m3dnow"
    "-Wno-unreachable-code"
    "-flax-vector-conversions"
    "-W..."

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

    make test
    TESTDONE: 1855 tests were considered during 3598 seconds.
    TESTDONE: 1574 tests out of 1574 reported OK: 100%


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
    make test


util-linux : https://github.com/util-linux/util-linux.git

    ./autogen.sh
    CC=chibicc CFLAGS=-fPIC ./configure
    make

    //to check if the compiled programs by chibicc work : 
    make check-programs
    cd tests
    run.sh 
    ---------------------------------------------------------------------
    All 341 tests PASSED
    ---------------------------------------------------------------------
        

nginx: https://github.com/nginx/nginx.git 

    CC=chibicc CFLAGS=-fPIC ./auto/configure --with-http_ssl_module
    make
    


zlib: https://github.com/madler/zlib.git

    CC=chibicc CFLAGS="-fPIC" ./configure
    make

    make test
    ...
    *** zlib test OK ***
    ...
    *** zlib shared test OK ***
    ...
    *** zlib 64-bit test OK ***
    

vim: https://github.com/vim/vim.git

    CC=chibicc CFLAGS="-fPIC" ./configure
    make
    make test    



libwepb: https://github.com/webmproject/libwebp.git

    CC=chibicc CFLAGS="-fpic" LDFLAGS="-fpic -lpng -ljpeg" cmake -S . -B ./build
    cd build
    cmake --build .
    ~/libwebp/build$ ./img2webp -version
    WebP Encoder version: 1.3.2
    WebP Mux version: 1.3.2
    libsharpyuv: 0.4.0
    [no output file specified]   [0 frames, 0 bytes].


memcached: https://github.com/memcached/memcached.git
    
    autoreconf -fi
    CC=chibicc CFLAGS=-fpic LDFLAGS=-fpic ./configure
    make
    make test
    All tests successful.
    Files=113, Tests=180224, 224 wallclock secs (19.91 usr  1.86 sys + 49.12 cusr 22.93 csys = 93.82 CPU)
    Result: PASS
    

nmap : https://github.com/nmap/nmap

    CC=chibicc ./configure --with-dbus
    make
    make check
    Testing nmap_dns
    Testing nmap_dns finished without errors
    Ran 292 tests. 0 failures.


vlc : https://github.com/videolan/vlc.git 

    autoreconf -fiv
    ./bootstrap
    CC=chibicc CFLAGS="-fPIC -std=c11"  ./configure --disable-lua --disable-xcb --disable-qt --disable-alsa --disable-sse --host x86_64-linux-gnu 
    make all


sqlite : https://github.com/sqlite/sqlite.git

    CC=chibicc CFLAGS="-std=c11" ./configure
    make all
    make test
    FAILED: All-Debug test/walsetlk.test (0)
    14:13 bld(10/10) fuzz(54/54) tcl(2470/2470) f1 ETC 00:00
    1 failures:
    FAILED: All-Debug test/walsetlk.test
    


php-src: https://github.com/php/php-src.git

    CC=chibicc CFLAGS="-fPIC -std=c11" ./buildconf && ./configure && make clean && make && make test
    Number of tests : 21533             15498
    Tests skipped   :  6035 ( 28.0%) --------
    Tests warned    :     3 (  0.0%) (  0.0%)
    Tests failed    :     0 (  0.0%) (  0.0%)
    Expected fail   :     8 (  0.0%) (  0.1%)
    Tests passed    : 15487 ( 71.9%) ( 99.9%)


openssl : https://github.com/openssl/openssl.git

    CC=chibicc ./Configure    
    make
    make test



postgres: https://github.com/postgres/postgres.git  (in case of bad network use git clone --filter=blob:none --depth=1 https://github.com/postgres/postgres.git --branch master)

    CC=chibicc  CFLAGS="-g -std=c11" ./configure --host x86_64-linux-gnu 
    make
    make check    
    # (test process exited with exit code 2)
    1..229
    # All 229 tests passed.


## meson

to be able to use meson with chibicc (meson hack is to do the meson configure using gcc and rename gcc to gcc_old chibicc to gcc and meson compile will call chibicc).

lxc: https://github.com/lxc/lxc.git

    CC=chibicc CFLAGS="-fpic" meson build && cd build && meson compile

    
  

## Limits

Some C projects doesn't compile for now or crash after being compiled with chibicc. It helps to find some bugs and to try to fix them!

cpython: git clone https://github.com/python/cpython.git 
        
        CC=chibicc CFLAGS="-std=c11"  ./configure  --host=x86_64-pc-linux-gnu 
        make && make test
        some tests failed 
        test_recursion_limit (test.test_marshal.BugsTestCase.test_recursion_limit) ... Fatal Python error: Segmentation fault
        test_repr_deep (test.test_userlist.UserListTest.test_repr_deep) ... Fatal Python error: Segmentation fault

        25 tests skipped
        3 tests skipped (resource denied)
        6 re-run tests
        5 tests failed:
            test.test_gdb.test_pretty_print test_call test_ctypes
            test_faulthandler test_frame_pointer_unwind

        467 tests OK.

        Total duration: 32 min 1 sec
        Total tests: run=47,875 failures=3,170 skipped=2,621
        Total test files: run=503/500 failed=5 skipped=25 resource_denied=3 rerun=6



## features added 

    - some extended assembly syntax taken in account (only when on macro body they are failing)
    - adding basic support on int128 (probably some operations are still not supported)
    - adding vector management and scalar promotion to vector    
    - alignment attributes supported (like GNUC level 4)
    - some basic optimization
    - some basic debug information (dwarf information)
    - adding support on __m256 avx2

 
## TODO

- trying to pass GNUC from 4 to higher compatibility level
- trying to compile other C projects from source to see what is missing or which bug we have with chibicc.
- trying to fix issue with postgres tests
- trying to rewrite extended assembly to be more robust
- trying to improve chibicc by reporting tests from slimcc to see what is missing/need to be fixed.


## issues and pull requests fixed

<https://github.com/stormalf/chibicc/blob/main/ISSUES.md>


## known issues

    git 2 tests failed    
    vim: compile OK, tests OK except 1.
    cpython : compile OK, some tests KO      
    sqlite: compile OK, tests OK (except 1)   
           

## projects compiled successfully with chibicc

    util-linux : compile OK, tests OK    
    nginx: compile OK
    zlib: compile OK, tests OK
    nmap: compile OK, tests OK    
    openssh-portable : compile OK, tests OK
    vlc: compile OK  
    memcached : compile OK, tests OK      
    php-src : compile OK, tests OK    
    openssl: compile OK, tests OK
    postgres execution : compile OK, tests OK    
    

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

1.0.24.1 


## old release notes

<https://github.com/stormalf/chibicc/blob/main/RELEASE_NOTES.md>


