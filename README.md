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
        -msse3 enabling sse3 support 
        -msse4 enabling sse4 support 
        -nostdlib  Do not use the standard system startup files or libraries when linking 
        -nostdinc Do not use the standard system header files when compiling 
        -std=c99 generates an error on implicit function declaration (without -std only a warning is emitted)
        -std=c11 generates an error on implicit function declaration (without -std only a warning is emitted)
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

    "-O"
    "-W"
    "-P"
    "-ffreestanding"
    "-fno-omit-frame-pointer"
    "-fomit-frame-pointer"
    "-funwind-tables"
    "-fno-stack-protector"
    "-fno-strict-aliasing"
    "-m64"
    "-m32"
    "--whole-archive"
    "--no-whole-archive"
    "-fsigned-char"
    "-Bsymbolic"
    "-z"
    "defs"
    "-pedantic"
    "-nostdinc"
    "-mno-red-zone"
    "-fvisibility=default"
    "-fvisibility=hidden"
    "-Werror=invalid-command-line-argument"
    "-Werror=unknown-warning-option"
    "-Wsign-compare"
    "-Wundef"
    "-Wpointer-arith"
    "-Wvolatile-register-var"
    "-Wformat"
    "-Wformat-security"
    "-Wduplicated-branches"
    "-Wduplicated-cond"
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
    "--print-search-dirs"
    "-msse4.1"
    "-fprofile-arcs"
    "-ftest-coverage"
    "-fdiagnostics-show-option"
    "-Xc"
    "-Aa"
    "-rdynamic"
    "-w"
    "--param=ssp-buffer-size=4"
    "-fno-lto"
    "-fp-model"
    "-fprofile-arcs"
    "-ftest-coverage"

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
    TESTDONE: 1722 tests were considered during 3895 seconds.
    TESTDONE: 1392 tests out of 1392 reported OK: 100%


openssl : https://github.com/openssl/openssl.git

    CC=chibicc ./Configure
    
    You need to remove from the file from openssl/crypto/perlasm/x86_64-xlate.pl

    	my $section='.note.gnu.property, #alloc';

    by :

    	my $section='.note.gnu.property';

    make

    make test
    

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

    Manually fixing the config.status and removing D["HAVE_UNION_SEMUN"]=" 1"
    ./autogen.sh
    CC=chibicc CFLAGS=-fPIC ./configure
    make

    //to check if the compiled programs by chibicc work : 
    make check-programs
    cd tests
    run.sh 
    ---------------------------------------------------------------------
    All 340 tests PASSED
    ---------------------------------------------------------------------
        

nginx: https://github.com/nginx/nginx.git 

    CC=chibicc CFLAGS=-fPIC ./auto/configure
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
    == SUMMARY ==
    Test run on 2023 Sep 23 14:15:31
    OK: 10
    FAILED: 0: []
    skipped: 0    


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


   
cpython: git clone git@github.com:python/cpython.git
        
        CC=chibicc ./configure
        make && make test
        failure with  

    Process terminating with default action of signal 11 (SIGSEGV): dumping core
    ==82695==  Access not within mapped region at address 0x25
    ==82695==    at 0xB7BC8B: ??? (pystate.c:1435)
    ==82695==    by 0xB7BAFB: ??? (pystate.c:1534)
    ==82695==    by 0xB89CEC: ??? (pystate.c:1576)
    ==82695==    by 0xB6F3F6: ??? (pylifecycle.c:667)
    ==82695==    by 0xB69FDA: ??? (pylifecycle.c:943)
    ==82695==    by 0xB699A1: ??? (pylifecycle.c:1112)
    ==82695==    by 0xB784E5: ??? (pylifecycle.c:1432)
    ==82695==    by 0x4088D7: ??? (_freeze_module.c:65)
    ==82695==    by 0x407294: ??? (_freeze_module.c:224)
    ==82695==    by 0x497D1C9: (below main) (libc_start_call_main.h:58)


nmap : https://github.com/nmap/nmap

    CC=chibicc ./configure --with-dbus
    make
    make check
    Testing nmap_dns
    Testing nmap_dns finished without errors
    Ran 292 tests. 0 failures.


## meson

to be able to use meson with chibicc (meson doesn't know chibicc compiler), I changed the detect.py file in /usr/lib/python3/dist-packages/mesonbuild/compilers/detect.py to add support for chibicc. After that I can now using meson for some projects that are configured to use it.

lxc: https://github.com/lxc/lxc.git

    CC=chibicc CFLAGS="-fpic" meson build && cd build && meson compile


## Limits

Some C projects doesn't compile for now or crash after being compiled with chibicc. It helps to find some bugs and to try to fix them!

VLC : https://github.com/videolan/vlc.git 

    autoreconf -fiv
    ./bootstrap
    CC=chibicc CFLAGS="-fPIC" CXXFLAGS="" DEFS="-DHAVE_CONFIG_H -DHAVE_ATTRIBUTE_PACKED -DVLC_USED -DVLC_API -DVLC_DEPRECATED -DVLC_MALLOC" LDFLAGS="-fPIC" ./configure  --disable-xcb --disable-qt --disable-a52 --disable-sse --disable-dbus
    make all

    VLC doesn't compile with chibicc :
    /usr/include/systemd/sd-id128.h:138: error:                 sd_id128_t b = va_arg(ap, sd_id128_t);
                                                                         ^ tokenize.c parse.c declaration 1328: in skip : expected ','


postgres: https://github.com/postgres/postgres.git  (in case of bad network use git clone --filter=blob:none --depth=1 https://github.com/postgres/postgres.git --branch master)

    CC=chibicc  CFLAGS="-g" ./configure --host x86_64-linux-gnu --disable-spinlocks ac_cv_type___int128=no
    make
    make check
    failed with :
    2025-06-08 23:05:39.492 CEST [206164] FATAL:  unrecognized SI message ID: -96
    2025-06-08 23:05:39.492 CEST [206164] STATEMENT:  ALTER TABLE pg_proc ADD PRIMARY KEY USING INDEX pg_proc_oid_index;

## TODO

- trying to compile other C projects from source to see what is missing or which bug we have with chibicc.
- Trying to find the root cause of segmentation fault with postgres initdb command.


## issues and pull requests fixed

<https://github.com/stormalf/chibicc/blob/main/ISSUES.md>


## known issues

    postgres execution : ko
    git 2 tests failed
    openssh-portable regress test failed
    curl 2 tests ko
    memcached test stuck at t/binary-extstore.t ......... 5947/?
    vim: compile OK, tests KO (depending the version of chibicc failed early or in the last tests).

## projects compiled successfully with chibicc

    util-linux : compile OK, tests OK    
    nginx: compile OK
    zlib: compile OK, tests OK
    nmap: compile OK, tests OK    


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

1.0.22.9    Reporting fixes from 1.0.22.9_dev (like implicit function declaration, -std=c11 -std=c99...). Fixing issue with \__atomic_load_n during linking of nmap. Fixing issue with vim (due to a mistake in ND_ASSIGN).
## old release notes

<https://github.com/stormalf/chibicc/blob/main/RELEASE_NOTES.md>


