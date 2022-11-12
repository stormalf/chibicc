; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, %struct._IO_codecvt*, %struct._IO_wide_data*, %struct._IO_FILE*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type opaque
%struct._IO_codecvt = type opaque
%struct._IO_wide_data = type opaque
%struct.StringArray = type { i8**, i32, i32 }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.Token = type { i32, %struct.Token*, i64, x86_fp80, i8*, i32, %struct.Type*, i8*, %struct.File*, i8*, i32, i32, i8, i8, %struct.Hideset*, %struct.Token* }
%struct.Type = type { i32, i32, i32, i8, i8, i8, %struct.Type*, %struct.Type*, %struct.Type*, %struct.Token*, %struct.Token*, i32, %struct.Node*, %struct.Obj*, %struct.Member*, i8, i8, %struct.Type*, %struct.Type*, i8, %struct.Type* }
%struct.Node = type { i32, %struct.Node*, %struct.Type*, %struct.Token*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, i8*, i8*, %struct.Node*, %struct.Member*, %struct.Type*, %struct.Node*, i8, %struct.Obj*, i8*, i8*, %struct.Node*, %struct.Node*, %struct.Node*, i64, i64, i8*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Obj*, %struct.Node*, i8, %struct.Obj*, i64, x86_fp80, i32, [12 x i8] }
%struct.Obj = type { %struct.Obj*, i8*, i8*, %struct.Type*, %struct.Token*, i8, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8*, %struct.Relocation*, i8, %struct.Obj*, %struct.Node*, %struct.Obj*, %struct.Obj*, %struct.Obj*, i32, i8, i8, %struct.StringArray }
%struct.Relocation = type { %struct.Relocation*, i32, i8**, i64 }
%struct.Member = type { %struct.Member*, %struct.Type*, %struct.Token*, %struct.Token*, i32, i32, i32, i8, i32, i32 }
%struct.File = type { i8*, i32, i8*, i8*, i32 }
%struct.Hideset = type opaque
%struct.glob_t = type { i64, i8**, i64, i32, void (i8*)*, i8* (i8*)*, i8* (i8*)*, i32 (i8*, i8*)*, i32 (i8*, i8*)* }

@opt_fcommon = dso_local global i8 1, align 1
@opt_fbuiltin = dso_local global i8 1, align 1
@isDotfile = dso_local global i8 0, align 1
@isDebug = dso_local global i8 0, align 1
@.str = private unnamed_addr constant [2 x i8] c" \00", align 1
@previousfile = dso_local global i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0), align 8
@.str.1 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@stdout = external global %struct._IO_FILE*, align 8
@.str.3 = private unnamed_addr constant [18 x i8] c"x86_64-linux-gnu\0A\00", align 1
@f = dso_local global %struct._IO_FILE* null, align 8
@logFile = internal global [17 x i8] c"/tmp/chibicc.log\00", align 16
@.str.4 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str.5 = private unnamed_addr constant [59 x i8] c"%s : in main Issue with -debug parameter, file not opened!\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"main.c\00", align 1
@opt_cc1 = internal global i8 0, align 1
@isCc1input = internal global i8 0, align 1
@.str.7 = private unnamed_addr constant [58 x i8] c"%s : in main with -cc1 parameter -cc1-input is mandatory!\00", align 1
@input_paths = internal global %struct.StringArray zeroinitializer, align 8
@opt_o = dso_local global i8* null, align 8
@opt_c = internal global i8 0, align 1
@opt_S = internal global i8 0, align 1
@opt_E = internal global i8 0, align 1
@.str.8 = private unnamed_addr constant [77 x i8] c"%s : in main cannot specify '-o' with '-c,' '-S' or '-E' with multiple files\00", align 1
@.str.9 = private unnamed_addr constant [3 x i8] c"-l\00", align 1
@.str.10 = private unnamed_addr constant [5 x i8] c"-Wl,\00", align 1
@.str.11 = private unnamed_addr constant [2 x i8] c",\00", align 1
@.str.12 = private unnamed_addr constant [3 x i8] c".s\00", align 1
@.str.13 = private unnamed_addr constant [3 x i8] c".o\00", align 1
@.str.14 = private unnamed_addr constant [15 x i8] c"type == FILE_C\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [23 x i8] c"int main(int, char **)\00", align 1
@opt_M = internal global i8 0, align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"a.out\00", align 1
@opt_MT = internal global i8* null, align 8
@include_paths = dso_local global %struct.StringArray zeroinitializer, align 8
@opt_fpic = dso_local global i8 0, align 1
@base_file = dso_local global i8* null, align 8
@dotf = dso_local global %struct._IO_FILE* null, align 8
@dot_file = dso_local global i8* null, align 8
@tmpfiles = internal global %struct.StringArray zeroinitializer, align 8
@.str.16 = private unnamed_addr constant [3 x i8] c"}\0A\00", align 1
@.str.17 = private unnamed_addr constant [84 x i8] c"parameter without value! the following parameters need to be followed by a value :\0A\00", align 1
@.str.18 = private unnamed_addr constant [130 x i8] c"-o, -I, -idirafter, -include, -x, -MF, -MQ, -MT, -Xlinker, -cc1-input, -cc1-output, -fuse-ld, -soname, -rpath, --version-script \0A\00", align 1
@.str.19 = private unnamed_addr constant [5 x i8] c"-###\00", align 1
@opt_hash_hash_hash = internal global i8 0, align 1
@.str.20 = private unnamed_addr constant [5 x i8] c"-cc1\00", align 1
@.str.21 = private unnamed_addr constant [7 x i8] c"--help\00", align 1
@.str.22 = private unnamed_addr constant [3 x i8] c"-h\00", align 1
@.str.23 = private unnamed_addr constant [10 x i8] c"--version\00", align 1
@.str.24 = private unnamed_addr constant [3 x i8] c"-v\00", align 1
@.str.25 = private unnamed_addr constant [9 x i8] c"-fuse-ld\00", align 1
@opt_linker = internal global i8* null, align 8
@.str.26 = private unnamed_addr constant [3 x i8] c"-o\00", align 1
@.str.27 = private unnamed_addr constant [3 x i8] c"-S\00", align 1
@.str.28 = private unnamed_addr constant [7 x i8] c"-debug\00", align 1
@.str.29 = private unnamed_addr constant [9 x i8] c"-dotfile\00", align 1
@.str.30 = private unnamed_addr constant [9 x i8] c"-fcommon\00", align 1
@.str.31 = private unnamed_addr constant [12 x i8] c"-fno-common\00", align 1
@.str.32 = private unnamed_addr constant [13 x i8] c"-fno-builtin\00", align 1
@.str.33 = private unnamed_addr constant [3 x i8] c"-c\00", align 1
@.str.34 = private unnamed_addr constant [3 x i8] c"-E\00", align 1
@.str.35 = private unnamed_addr constant [3 x i8] c"-I\00", align 1
@.str.36 = private unnamed_addr constant [3 x i8] c"-D\00", align 1
@.str.37 = private unnamed_addr constant [3 x i8] c"-U\00", align 1
@.str.38 = private unnamed_addr constant [9 x i8] c"-include\00", align 1
@opt_include = internal global %struct.StringArray zeroinitializer, align 8
@.str.39 = private unnamed_addr constant [3 x i8] c"-x\00", align 1
@opt_x = internal global i32 0, align 4
@.str.40 = private unnamed_addr constant [7 x i8] c"-Wl,-z\00", align 1
@.str.41 = private unnamed_addr constant [9 x i8] c"-Xlinker\00", align 1
@ld_extra_args = internal global %struct.StringArray zeroinitializer, align 8
@.str.42 = private unnamed_addr constant [16 x i8] c"-version-script\00", align 1
@.str.43 = private unnamed_addr constant [17 x i8] c"--version-script\00", align 1
@.str.44 = private unnamed_addr constant [3 x i8] c"-s\00", align 1
@.str.45 = private unnamed_addr constant [3 x i8] c"-M\00", align 1
@.str.46 = private unnamed_addr constant [4 x i8] c"-MF\00", align 1
@opt_MF = internal global i8* null, align 8
@.str.47 = private unnamed_addr constant [4 x i8] c"-MP\00", align 1
@opt_MP = internal global i8 0, align 1
@.str.48 = private unnamed_addr constant [4 x i8] c"-MT\00", align 1
@.str.49 = private unnamed_addr constant [6 x i8] c"%s %s\00", align 1
@.str.50 = private unnamed_addr constant [4 x i8] c"-MD\00", align 1
@opt_MD = internal global i8 0, align 1
@.str.51 = private unnamed_addr constant [4 x i8] c"-MQ\00", align 1
@.str.52 = private unnamed_addr constant [5 x i8] c"-MMD\00", align 1
@opt_MMD = internal global i8 0, align 1
@.str.53 = private unnamed_addr constant [6 x i8] c"-fpic\00", align 1
@.str.54 = private unnamed_addr constant [6 x i8] c"-fPIC\00", align 1
@.str.55 = private unnamed_addr constant [9 x i8] c"-fno-pic\00", align 1
@.str.56 = private unnamed_addr constant [11 x i8] c"-cc1-input\00", align 1
@.str.57 = private unnamed_addr constant [12 x i8] c"-cc1-output\00", align 1
@isCc1output = internal global i8 0, align 1
@output_file = internal global i8* null, align 8
@.str.58 = private unnamed_addr constant [11 x i8] c"-idirafter\00", align 1
@.str.59 = private unnamed_addr constant [8 x i8] c"-static\00", align 1
@opt_static = internal global i8 0, align 1
@.str.60 = private unnamed_addr constant [8 x i8] c"-shared\00", align 1
@opt_shared = internal global i8 0, align 1
@.str.61 = private unnamed_addr constant [9 x i8] c"-pthread\00", align 1
@.str.62 = private unnamed_addr constant [10 x i8] c"-lpthread\00", align 1
@.str.63 = private unnamed_addr constant [3 x i8] c"-L\00", align 1
@.str.64 = private unnamed_addr constant [14 x i8] c"-hashmap-test\00", align 1
@.str.65 = private unnamed_addr constant [13 x i8] c"-dumpmachine\00", align 1
@.str.66 = private unnamed_addr constant [8 x i8] c"-soname\00", align 1
@.str.67 = private unnamed_addr constant [7 x i8] c"-rpath\00", align 1
@r_path = internal global i8* null, align 8
@.str.68 = private unnamed_addr constant [3 x i8] c"-O\00", align 1
@.str.69 = private unnamed_addr constant [3 x i8] c"-W\00", align 1
@.str.70 = private unnamed_addr constant [3 x i8] c"-g\00", align 1
@.str.71 = private unnamed_addr constant [6 x i8] c"-std=\00", align 1
@.str.72 = private unnamed_addr constant [5 x i8] c"-std\00", align 1
@.str.73 = private unnamed_addr constant [15 x i8] c"-ffreestanding\00", align 1
@.str.74 = private unnamed_addr constant [24 x i8] c"-fno-omit-frame-pointer\00", align 1
@.str.75 = private unnamed_addr constant [21 x i8] c"-fno-stack-protector\00", align 1
@.str.76 = private unnamed_addr constant [21 x i8] c"-fno-strict-aliasing\00", align 1
@.str.77 = private unnamed_addr constant [5 x i8] c"-m64\00", align 1
@.str.78 = private unnamed_addr constant [5 x i8] c"-m32\00", align 1
@.str.79 = private unnamed_addr constant [16 x i8] c"--whole-archive\00", align 1
@.str.80 = private unnamed_addr constant [19 x i8] c"--no-whole-archive\00", align 1
@.str.81 = private unnamed_addr constant [14 x i8] c"-fsigned-char\00", align 1
@.str.82 = private unnamed_addr constant [11 x i8] c"-Bsymbolic\00", align 1
@.str.83 = private unnamed_addr constant [3 x i8] c"-z\00", align 1
@.str.84 = private unnamed_addr constant [5 x i8] c"defs\00", align 1
@.str.85 = private unnamed_addr constant [6 x i8] c"-flto\00", align 1
@.str.86 = private unnamed_addr constant [10 x i8] c"-pedantic\00", align 1
@.str.87 = private unnamed_addr constant [10 x i8] c"-nostdinc\00", align 1
@.str.88 = private unnamed_addr constant [14 x i8] c"-mno-red-zone\00", align 1
@.str.89 = private unnamed_addr constant [3 x i8] c"-w\00", align 1
@.str.90 = private unnamed_addr constant [38 x i8] c"%s in parse_args unknown argument: %s\00", align 1
@.str.91 = private unnamed_addr constant [34 x i8] c"%s : in parse_args no input files\00", align 1
@__const.take_arg.x = private unnamed_addr constant [15 x i8*] [i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.26, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.35, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.58, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.39, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.46, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.48, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.51, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.41, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.56, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.57, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.66, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.67, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.43, i32 0, i32 0)], align 16
@stderr = external global %struct._IO_FILE*, align 8
@.str.92 = private unnamed_addr constant [215 x i8] c"chibicc is a C compiler based on chibicc created by Rui Ueyama.\0A See original project https://github.com/rui314/chibicc for more information\0A this chibicc contains only some differences for now like new parameters\0A\00", align 1
@.str.93 = private unnamed_addr constant [3029 x i8] c"chibicc usage :\0A --help or -h print the help\0A --version or -v print the version of chibicc\0A -cc1 run the cc1 function needs -cc1-input (-cc1-output optional) parameter \0A -fuse-ld to specify other linker than ld used by default \0A -x Specify the language of the following input files.\0A     Permissible languages include: c assembler none\0A     'none' means revert to the default behavior of\0A     guessing the language based on the file's extension.\0A -S generate assembly file \0A -o path to output executable if omitted a.out generated\0A -c path to source to compile \0A -Xlinker <arg> Pass <arg> on to the linker.\0A -Wl,<options> Pass comma-separated <options> on to the linker.\0A -z <arg> Pass <arg> on to the linker. \0A -soname <arg> Pass -soname <arg> on to the linker. \0A --version-script <arg> Pass --version-script <arg> to the linker.\0A -I<path> Pass path to the include directories \0A -L<path> Pass path to the lib directories \0A -D<macro> define macro example -DM13 \0A -U<macro> undefine macro example -UM13\0A -s to strip all symbols during linkage phasis \0A -M -MD -MP -MMD -MF <arg> -MT <arg> -MQ <arg> compiler write a list of input files to \0A     stdout in a format that \22make\22 command can read. This feature is\0A     used to automate file dependency management\0A -fpic or -fPIC Generate position-independent code (PIC)\0A -fno-pic disables the generation of position-independent code with relative address references\0A -fcommon is the default if not specified, it's mainly useful to enable legacy code to link without errors\0A -fno-common specifies that the compiler places uninitialized global variables in the BSS section of the object file.\0A -static  pass to the linker to link a program statically\0A -pthread pass to the linker to link with lpthread library \0A -shared pass to the linker to produce a shared object which can then be linked with other objects to form an executable.\0A -hashmap-test to test the hashmap function \0A -idirafter <dir> apply to lookup for both the #include \22file\22 and #include <file> directives.\0A -### to dump all commands executed by chibicc \0A -debug to dump all commands executed by chibicc in a log file in /tmp/chibicc.log\0A -E Stop after the preprocessing stage; do not run the compiler proper. \0A     The output is in the form of preprocessed source code, which is sent to the standard output.\0A     Input files that don\E2\80\99t require preprocessing are ignored.\0A -rpath <dir> Add a directory to the runtime library search path this parameter is passed to the linker. \0A     This is used when linking an ELF executable with shared objects.\0A     All -rpath arguments are concatenated and passed to the runtime linker,\0A     which uses them to locate shared objects at runtime. \0A     The -rpath option is also used when locating shared objects \0A     which are needed by shared objects explicitly included in the link. \0A -dumpmachine it's required by some projects returns x86_64-linux-gnu\0A -dotfile generates a file with .dot extension that can be visualized using graphviz package \0A chibicc [ -o <path> ] <file>\0A\00", align 1
@.str.94 = private unnamed_addr constant [17 x i8] c"%s version : %s\0A\00", align 1
@.str.95 = private unnamed_addr constant [8 x i8] c"chibicc\00", align 1
@.str.96 = private unnamed_addr constant [7 x i8] c"1.0.17\00", align 1
@.str.97 = private unnamed_addr constant [63 x i8] c"%s : in check_parms_length maximum length parameter overpassed\00", align 1
@.str.98 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@.str.99 = private unnamed_addr constant [2 x i8] c"c\00", align 1
@.str.100 = private unnamed_addr constant [10 x i8] c"assembler\00", align 1
@.str.101 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.102 = private unnamed_addr constant [64 x i8] c"%s : in parse_opt_x <command line>: unknown argument for -x: %s\00", align 1
@.str.103 = private unnamed_addr constant [42 x i8] c"%s in quote_makefile buf pointer is null!\00", align 1
@.str.104 = private unnamed_addr constant [11 x i8] c"%s/include\00", align 1
@.str.105 = private unnamed_addr constant [19 x i8] c"/usr/local/include\00", align 1
@.str.106 = private unnamed_addr constant [30 x i8] c"/usr/include/x86_64-linux-gnu\00", align 1
@.str.107 = private unnamed_addr constant [13 x i8] c"/usr/include\00", align 1
@.str.108 = private unnamed_addr constant [29 x i8] c"/usr/include/chibicc/include\00", align 1
@std_include_paths = internal global %struct.StringArray zeroinitializer, align 8
@.str.109 = private unnamed_addr constant [29 x i8] c"%s : in cc1 -include: %s: %s\00", align 1
@.str.110 = private unnamed_addr constant [34 x i8] c"%s : in must_tokenize_file %s: %s\00", align 1
@.str.111 = private unnamed_addr constant [3 x i8] c".d\00", align 1
@.str.112 = private unnamed_addr constant [2 x i8] c"-\00", align 1
@.str.113 = private unnamed_addr constant [4 x i8] c"%s:\00", align 1
@.str.114 = private unnamed_addr constant [8 x i8] c" \\\0A  %s\00", align 1
@.str.115 = private unnamed_addr constant [3 x i8] c"\0A\0A\00", align 1
@.str.116 = private unnamed_addr constant [6 x i8] c"%s:\0A\0A\00", align 1
@.str.117 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.118 = private unnamed_addr constant [5 x i8] c"%.*s\00", align 1
@.str.119 = private unnamed_addr constant [50 x i8] c"%s : in open_file cannot open output file: %s: %s\00", align 1
@.str.120 = private unnamed_addr constant [3 x i8] c".a\00", align 1
@.str.121 = private unnamed_addr constant [4 x i8] c".so\00", align 1
@.str.122 = private unnamed_addr constant [5 x i8] c".so.\00", align 1
@.str.123 = private unnamed_addr constant [4 x i8] c".lo\00", align 1
@.str.124 = private unnamed_addr constant [3 x i8] c".c\00", align 1
@.str.125 = private unnamed_addr constant [6 x i8] c".so.4\00", align 1
@.str.126 = private unnamed_addr constant [65 x i8] c"%s : in get_file_type <command line>: unknown file extension: %s\00", align 1
@.str.127 = private unnamed_addr constant [3 x i8] c"as\00", align 1
@.str.128 = private unnamed_addr constant [4 x i8] c" %s\00", align 1
@.str.129 = private unnamed_addr constant [44 x i8] c"%s : in run_subprocess exec failed: %s: %s\0A\00", align 1
@.str.130 = private unnamed_addr constant [29 x i8] c"%s : in run_cc1 args is null\00", align 1
@.str.131 = private unnamed_addr constant [20 x i8] c"/tmp/chibicc-XXXXXX\00", align 1
@.str.132 = private unnamed_addr constant [41 x i8] c"%s : in create_tmpfile path path is null\00", align 1
@.str.133 = private unnamed_addr constant [42 x i8] c"%s : in create_tmpfile mkstemp failed: %s\00", align 1
@.str.134 = private unnamed_addr constant [3 x i8] c"ld\00", align 1
@.str.135 = private unnamed_addr constant [3 x i8] c"-m\00", align 1
@.str.136 = private unnamed_addr constant [11 x i8] c"elf_x86_64\00", align 1
@.str.137 = private unnamed_addr constant [10 x i8] c"%s/crti.o\00", align 1
@.str.138 = private unnamed_addr constant [15 x i8] c"%s/crtbeginS.o\00", align 1
@.str.139 = private unnamed_addr constant [10 x i8] c"%s/crt1.o\00", align 1
@.str.140 = private unnamed_addr constant [14 x i8] c"%s/crtbegin.o\00", align 1
@.str.141 = private unnamed_addr constant [4 x i8] c"-L.\00", align 1
@.str.142 = private unnamed_addr constant [5 x i8] c"-L%s\00", align 1
@.str.143 = private unnamed_addr constant [28 x i8] c"-L/usr/lib/x86_64-linux-gnu\00", align 1
@.str.144 = private unnamed_addr constant [13 x i8] c"-L/usr/lib64\00", align 1
@.str.145 = private unnamed_addr constant [9 x i8] c"-L/lib64\00", align 1
@.str.146 = private unnamed_addr constant [31 x i8] c"-L/usr/lib/x86_64-pc-linux-gnu\00", align 1
@.str.147 = private unnamed_addr constant [31 x i8] c"-L/usr/lib/x86_64-redhat-linux\00", align 1
@.str.148 = private unnamed_addr constant [11 x i8] c"-L/usr/lib\00", align 1
@.str.149 = private unnamed_addr constant [7 x i8] c"-L/lib\00", align 1
@.str.150 = private unnamed_addr constant [16 x i8] c"-dynamic-linker\00", align 1
@.str.151 = private unnamed_addr constant [28 x i8] c"/lib64/ld-linux-x86-64.so.2\00", align 1
@.str.152 = private unnamed_addr constant [14 x i8] c"--start-group\00", align 1
@.str.153 = private unnamed_addr constant [6 x i8] c"-lgcc\00", align 1
@.str.154 = private unnamed_addr constant [9 x i8] c"-lgcc_eh\00", align 1
@.str.155 = private unnamed_addr constant [4 x i8] c"-lc\00", align 1
@.str.156 = private unnamed_addr constant [12 x i8] c"--end-group\00", align 1
@.str.157 = private unnamed_addr constant [12 x i8] c"--as-needed\00", align 1
@.str.158 = private unnamed_addr constant [8 x i8] c"-lgcc_s\00", align 1
@.str.159 = private unnamed_addr constant [15 x i8] c"--no-as-needed\00", align 1
@.str.160 = private unnamed_addr constant [13 x i8] c"%s/crtendS.o\00", align 1
@.str.161 = private unnamed_addr constant [12 x i8] c"%s/crtend.o\00", align 1
@.str.162 = private unnamed_addr constant [10 x i8] c"%s/crtn.o\00", align 1
@.str.163 = private unnamed_addr constant [33 x i8] c"/usr/lib/x86_64-linux-gnu/crti.o\00", align 1
@.str.164 = private unnamed_addr constant [26 x i8] c"/usr/lib/x86_64-linux-gnu\00", align 1
@.str.165 = private unnamed_addr constant [18 x i8] c"/usr/lib64/crti.o\00", align 1
@.str.166 = private unnamed_addr constant [11 x i8] c"/usr/lib64\00", align 1
@.str.167 = private unnamed_addr constant [47 x i8] c"%s : in find_libpath library path is not found\00", align 1
@.str.168 = private unnamed_addr constant [43 x i8] c"/usr/lib/gcc/x86_64-linux-gnu/*/crtbegin.o\00", align 1
@.str.169 = private unnamed_addr constant [35 x i8] c"/usr/lib/gcc/x86_64-*/*/crtbegin.o\00", align 1
@.str.170 = private unnamed_addr constant [46 x i8] c"/usr/lib/gcc/x86_64-pc-linux-gnu/*/crtbegin.o\00", align 1
@.str.171 = private unnamed_addr constant [46 x i8] c"/usr/lib/gcc/x86_64-redhat-linux/*/crtbegin.o\00", align 1
@__const.find_gcc_libpath.paths = private unnamed_addr constant [4 x i8*] [i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.168, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.169, i32 0, i32 0), i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.170, i32 0, i32 0), i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.171, i32 0, i32 0)], align 16
@.str.172 = private unnamed_addr constant [55 x i8] c"%s : in find_gcc_libpath gcc library path is not found\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @extract_filename(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  %5 = call noalias i8* @strdup(i8* noundef %4) #10
  %6 = call i8* @__xpg_basename(i8* noundef %5) #10
  store i8* %6, i8** %3, align 8
  %7 = load i8*, i8** %3, align 8
  %8 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i64 0, i64 0), i8* noundef %7)
  ret i8* %8
}

; Function Attrs: nounwind
declare i8* @__xpg_basename(i8* noundef) #1

; Function Attrs: nounwind
declare noalias i8* @strdup(i8* noundef) #1

declare i8* @format(i8* noundef, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @extract_path(i8* noundef %0, i8* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i64, align 8
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %10 = load i8*, i8** %3, align 8
  %11 = call i64 @strlen(i8* noundef %10) #11
  %12 = trunc i64 %11 to i32
  store i32 %12, i32* %5, align 4
  %13 = load i8*, i8** %4, align 8
  %14 = call i64 @strlen(i8* noundef %13) #11
  %15 = trunc i64 %14 to i32
  store i32 %15, i32* %6, align 4
  %16 = load i32, i32* %5, align 4
  %17 = load i32, i32* %6, align 4
  %18 = sub nsw i32 %16, %17
  %19 = add nsw i32 %18, 1
  store i32 %19, i32* %7, align 4
  %20 = load i32, i32* %7, align 4
  %21 = zext i32 %20 to i64
  %22 = call i8* @llvm.stacksave()
  store i8* %22, i8** %8, align 8
  %23 = alloca i8, i64 %21, align 16
  store i64 %21, i64* %9, align 8
  call void @llvm.memset.p0i8.i64(i8* align 16 %23, i8 0, i64 %21, i1 false)
  %24 = load i8*, i8** %3, align 8
  %25 = sub i64 %21, 1
  %26 = call i8* @strncpy(i8* noundef %23, i8* noundef %24, i64 noundef %25) #10
  %27 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i64 0, i64 0), i8* noundef %23)
  %28 = load i8*, i8** %8, align 8
  call void @llvm.stackrestore(i8* %28)
  ret i8* %27
}

; Function Attrs: nounwind readonly willreturn
declare i64 @strlen(i8* noundef) #3

; Function Attrs: nofree nosync nounwind willreturn
declare i8* @llvm.stacksave() #4

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #5

; Function Attrs: nounwind
declare i8* @strncpy(i8* noundef, i8* noundef, i64 noundef) #1

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.stackrestore(i8*) #4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @replace_extn(i8* noundef %0, i8* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %7 = load i8*, i8** %3, align 8
  %8 = call i8* @extract_filename(i8* noundef %7)
  store i8* %8, i8** %5, align 8
  %9 = load i8*, i8** %5, align 8
  %10 = call i8* @strrchr(i8* noundef %9, i32 noundef 46) #11
  store i8* %10, i8** %6, align 8
  %11 = load i8*, i8** %6, align 8
  %12 = icmp ne i8* %11, null
  br i1 %12, label %13, label %15

13:                                               ; preds = %2
  %14 = load i8*, i8** %6, align 8
  store i8 0, i8* %14, align 1
  br label %15

15:                                               ; preds = %13, %2
  %16 = load i8*, i8** %5, align 8
  %17 = load i8*, i8** %4, align 8
  %18 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0), i8* noundef %16, i8* noundef %17)
  ret i8* %18
}

; Function Attrs: nounwind readonly willreturn
declare i8* @strrchr(i8* noundef, i32 noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @dump_machine() #0 {
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %2 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %1, i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.3, i64 0, i64 0))
  ret void
}

declare i32 @fprintf(%struct._IO_FILE* noundef, i8* noundef, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @file_exists(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.stat, align 8
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  %5 = call i32 @stat(i8* noundef %4, %struct.stat* noundef %3) #10
  %6 = icmp ne i32 %5, 0
  %7 = xor i1 %6, true
  ret i1 %7
}

; Function Attrs: nounwind
declare i32 @stat(i8* noundef, %struct.stat* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, i8** noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca %struct.StringArray, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i8*, align 8
  %12 = alloca i32, align 4
  %13 = alloca i8*, align 8
  %14 = alloca i8*, align 8
  %15 = alloca i8*, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %16 = call i32 @atexit(void ()* noundef @cleanup) #10
  %17 = load i32, i32* %4, align 4
  %18 = load i8**, i8*** %5, align 8
  call void @parse_args(i32 noundef %17, i8** noundef %18)
  %19 = load i8, i8* @isDebug, align 1
  %20 = trunc i8 %19 to i1
  br i1 %20, label %21, label %30

21:                                               ; preds = %2
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %23 = icmp eq %struct._IO_FILE* %22, null
  br i1 %23, label %24, label %30

24:                                               ; preds = %21
  %25 = call noalias %struct._IO_FILE* @fopen(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @logFile, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  store %struct._IO_FILE* %25, %struct._IO_FILE** @f, align 8
  %26 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %27 = icmp eq %struct._IO_FILE* %26, null
  br i1 %27, label %28, label %29

28:                                               ; preds = %24
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([59 x i8], [59 x i8]* @.str.5, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

29:                                               ; preds = %24
  br label %30

30:                                               ; preds = %29, %21, %2
  call void @init_macros()
  %31 = load i8, i8* @opt_cc1, align 1
  %32 = trunc i8 %31 to i1
  br i1 %32, label %33, label %37

33:                                               ; preds = %30
  %34 = load i8, i8* @isCc1input, align 1
  %35 = trunc i8 %34 to i1
  br i1 %35, label %37, label %36

36:                                               ; preds = %33
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([58 x i8], [58 x i8]* @.str.7, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

37:                                               ; preds = %33, %30
  %38 = load i8, i8* @opt_cc1, align 1
  %39 = trunc i8 %38 to i1
  br i1 %39, label %40, label %44

40:                                               ; preds = %37
  %41 = load i8**, i8*** %5, align 8
  %42 = getelementptr inbounds i8*, i8** %41, i64 0
  %43 = load i8*, i8** %42, align 8
  call void @add_default_include_paths(i8* noundef %43)
  call void @cc1()
  store i32 0, i32* %3, align 4
  br label %193

44:                                               ; preds = %37
  %45 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @input_paths, i32 0, i32 2), align 4
  %46 = icmp sgt i32 %45, 1
  br i1 %46, label %47, label %60

47:                                               ; preds = %44
  %48 = load i8*, i8** @opt_o, align 8
  %49 = icmp ne i8* %48, null
  br i1 %49, label %50, label %60

50:                                               ; preds = %47
  %51 = load i8, i8* @opt_c, align 1
  %52 = trunc i8 %51 to i1
  br i1 %52, label %59, label %53

53:                                               ; preds = %50
  %54 = load i8, i8* @opt_S, align 1
  %55 = trunc i8 %54 to i1
  br i1 %55, label %59, label %56

56:                                               ; preds = %53
  %57 = load i8, i8* @opt_E, align 1
  %58 = trunc i8 %57 to i1
  br i1 %58, label %59, label %60

59:                                               ; preds = %56, %53, %50
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([77 x i8], [77 x i8]* @.str.8, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

60:                                               ; preds = %56, %47, %44
  %61 = bitcast %struct.StringArray* %6 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %61, i8 0, i64 16, i1 false)
  store i32 0, i32* %7, align 4
  br label %62

62:                                               ; preds = %176, %60
  %63 = load i32, i32* %7, align 4
  %64 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @input_paths, i32 0, i32 2), align 4
  %65 = icmp slt i32 %63, %64
  br i1 %65, label %66, label %179

66:                                               ; preds = %62
  %67 = load i8**, i8*** getelementptr inbounds (%struct.StringArray, %struct.StringArray* @input_paths, i32 0, i32 0), align 8
  %68 = load i32, i32* %7, align 4
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds i8*, i8** %67, i64 %69
  %71 = load i8*, i8** %70, align 8
  store i8* %71, i8** %8, align 8
  %72 = load i8*, i8** %8, align 8
  %73 = call i32 @strncmp(i8* noundef %72, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0), i64 noundef 2) #11
  %74 = icmp ne i32 %73, 0
  br i1 %74, label %77, label %75

75:                                               ; preds = %66
  %76 = load i8*, i8** %8, align 8
  call void @strarray_push(%struct.StringArray* noundef %6, i8* noundef %76)
  br label %176

77:                                               ; preds = %66
  %78 = load i8*, i8** %8, align 8
  %79 = call i32 @strncmp(i8* noundef %78, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.10, i64 0, i64 0), i64 noundef 4) #11
  %80 = icmp ne i32 %79, 0
  br i1 %80, label %94, label %81

81:                                               ; preds = %77
  %82 = load i8*, i8** %8, align 8
  %83 = getelementptr inbounds i8, i8* %82, i64 4
  %84 = call noalias i8* @strdup(i8* noundef %83) #10
  store i8* %84, i8** %9, align 8
  %85 = load i8*, i8** %9, align 8
  %86 = call i8* @strtok(i8* noundef %85, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i64 0, i64 0)) #10
  store i8* %86, i8** %10, align 8
  br label %87

87:                                               ; preds = %90, %81
  %88 = load i8*, i8** %10, align 8
  %89 = icmp ne i8* %88, null
  br i1 %89, label %90, label %93

90:                                               ; preds = %87
  %91 = load i8*, i8** %10, align 8
  call void @strarray_push(%struct.StringArray* noundef %6, i8* noundef %91)
  %92 = call i8* @strtok(i8* noundef null, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i64 0, i64 0)) #10
  store i8* %92, i8** %10, align 8
  br label %87, !llvm.loop !6

93:                                               ; preds = %87
  br label %176

94:                                               ; preds = %77
  %95 = load i8*, i8** @opt_o, align 8
  %96 = icmp ne i8* %95, null
  br i1 %96, label %97, label %99

97:                                               ; preds = %94
  %98 = load i8*, i8** @opt_o, align 8
  store i8* %98, i8** %11, align 8
  br label %109

99:                                               ; preds = %94
  %100 = load i8, i8* @opt_S, align 1
  %101 = trunc i8 %100 to i1
  br i1 %101, label %102, label %105

102:                                              ; preds = %99
  %103 = load i8*, i8** %8, align 8
  %104 = call i8* @replace_extn(i8* noundef %103, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.12, i64 0, i64 0))
  store i8* %104, i8** %11, align 8
  br label %108

105:                                              ; preds = %99
  %106 = load i8*, i8** %8, align 8
  %107 = call i8* @replace_extn(i8* noundef %106, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.13, i64 0, i64 0))
  store i8* %107, i8** %11, align 8
  br label %108

108:                                              ; preds = %105, %102
  br label %109

109:                                              ; preds = %108, %97
  %110 = load i8*, i8** %8, align 8
  %111 = call i32 @get_file_type(i8* noundef %110)
  store i32 %111, i32* %12, align 4
  %112 = load i32, i32* %12, align 4
  %113 = icmp eq i32 %112, 3
  br i1 %113, label %120, label %114

114:                                              ; preds = %109
  %115 = load i32, i32* %12, align 4
  %116 = icmp eq i32 %115, 4
  br i1 %116, label %120, label %117

117:                                              ; preds = %114
  %118 = load i32, i32* %12, align 4
  %119 = icmp eq i32 %118, 5
  br i1 %119, label %120, label %122

120:                                              ; preds = %117, %114, %109
  %121 = load i8*, i8** %8, align 8
  call void @strarray_push(%struct.StringArray* noundef %6, i8* noundef %121)
  br label %176

122:                                              ; preds = %117
  %123 = load i32, i32* %12, align 4
  %124 = icmp eq i32 %123, 2
  br i1 %124, label %125, label %132

125:                                              ; preds = %122
  %126 = load i8, i8* @opt_S, align 1
  %127 = trunc i8 %126 to i1
  br i1 %127, label %131, label %128

128:                                              ; preds = %125
  %129 = load i8*, i8** %8, align 8
  %130 = load i8*, i8** %11, align 8
  call void @assemble(i8* noundef %129, i8* noundef %130)
  br label %131

131:                                              ; preds = %128, %125
  br label %176

132:                                              ; preds = %122
  %133 = load i32, i32* %12, align 4
  %134 = icmp eq i32 %133, 1
  br i1 %134, label %135, label %136

135:                                              ; preds = %132
  br label %137

136:                                              ; preds = %132
  call void @__assert_fail(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.14, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i32 noundef 1171, i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)) #13
  unreachable

137:                                              ; preds = %135
  %138 = load i8, i8* @opt_E, align 1
  %139 = trunc i8 %138 to i1
  br i1 %139, label %143, label %140

140:                                              ; preds = %137
  %141 = load i8, i8* @opt_M, align 1
  %142 = trunc i8 %141 to i1
  br i1 %142, label %143, label %147

143:                                              ; preds = %140, %137
  %144 = load i32, i32* %4, align 4
  %145 = load i8**, i8*** %5, align 8
  %146 = load i8*, i8** %8, align 8
  call void @run_cc1(i32 noundef %144, i8** noundef %145, i8* noundef %146, i8* noundef null)
  br label %176

147:                                              ; preds = %140
  %148 = load i8, i8* @opt_S, align 1
  %149 = trunc i8 %148 to i1
  br i1 %149, label %150, label %155

150:                                              ; preds = %147
  %151 = load i32, i32* %4, align 4
  %152 = load i8**, i8*** %5, align 8
  %153 = load i8*, i8** %8, align 8
  %154 = load i8*, i8** %11, align 8
  call void @run_cc1(i32 noundef %151, i8** noundef %152, i8* noundef %153, i8* noundef %154)
  br label %176

155:                                              ; preds = %147
  %156 = load i8, i8* @opt_c, align 1
  %157 = trunc i8 %156 to i1
  br i1 %157, label %158, label %166

158:                                              ; preds = %155
  %159 = call i8* @create_tmpfile()
  store i8* %159, i8** %13, align 8
  %160 = load i32, i32* %4, align 4
  %161 = load i8**, i8*** %5, align 8
  %162 = load i8*, i8** %8, align 8
  %163 = load i8*, i8** %13, align 8
  call void @run_cc1(i32 noundef %160, i8** noundef %161, i8* noundef %162, i8* noundef %163)
  %164 = load i8*, i8** %13, align 8
  %165 = load i8*, i8** %11, align 8
  call void @assemble(i8* noundef %164, i8* noundef %165)
  br label %176

166:                                              ; preds = %155
  %167 = call i8* @create_tmpfile()
  store i8* %167, i8** %14, align 8
  %168 = call i8* @create_tmpfile()
  store i8* %168, i8** %15, align 8
  %169 = load i32, i32* %4, align 4
  %170 = load i8**, i8*** %5, align 8
  %171 = load i8*, i8** %8, align 8
  %172 = load i8*, i8** %14, align 8
  call void @run_cc1(i32 noundef %169, i8** noundef %170, i8* noundef %171, i8* noundef %172)
  %173 = load i8*, i8** %14, align 8
  %174 = load i8*, i8** %15, align 8
  call void @assemble(i8* noundef %173, i8* noundef %174)
  %175 = load i8*, i8** %15, align 8
  call void @strarray_push(%struct.StringArray* noundef %6, i8* noundef %175)
  br label %176

176:                                              ; preds = %166, %158, %150, %143, %131, %120, %93, %75
  %177 = load i32, i32* %7, align 4
  %178 = add nsw i32 %177, 1
  store i32 %178, i32* %7, align 4
  br label %62, !llvm.loop !8

179:                                              ; preds = %62
  %180 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %6, i32 0, i32 2
  %181 = load i32, i32* %180, align 4
  %182 = icmp sgt i32 %181, 0
  br i1 %182, label %183, label %191

183:                                              ; preds = %179
  %184 = load i8*, i8** @opt_o, align 8
  %185 = icmp ne i8* %184, null
  br i1 %185, label %186, label %188

186:                                              ; preds = %183
  %187 = load i8*, i8** @opt_o, align 8
  br label %189

188:                                              ; preds = %183
  br label %189

189:                                              ; preds = %188, %186
  %190 = phi i8* [ %187, %186 ], [ getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i64 0, i64 0), %188 ]
  call void @run_linker(%struct.StringArray* noundef %6, i8* noundef %190)
  br label %191

191:                                              ; preds = %189, %179
  %192 = load i8*, i8** @opt_MT, align 8
  call void @free(i8* noundef %192) #10
  store i32 0, i32* %3, align 4
  br label %193

193:                                              ; preds = %191, %40
  %194 = load i32, i32* %3, align 4
  ret i32 %194
}

; Function Attrs: nounwind
declare i32 @atexit(void ()* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal void @cleanup() #0 {
  %1 = alloca i32, align 4
  %2 = load i8, i8* @isDebug, align 1
  %3 = trunc i8 %2 to i1
  br i1 %3, label %20, label %4

4:                                                ; preds = %0
  store i32 0, i32* %1, align 4
  br label %5

5:                                                ; preds = %16, %4
  %6 = load i32, i32* %1, align 4
  %7 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @tmpfiles, i32 0, i32 2), align 4
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %9, label %19

9:                                                ; preds = %5
  %10 = load i8**, i8*** getelementptr inbounds (%struct.StringArray, %struct.StringArray* @tmpfiles, i32 0, i32 0), align 8
  %11 = load i32, i32* %1, align 4
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds i8*, i8** %10, i64 %12
  %14 = load i8*, i8** %13, align 8
  %15 = call i32 @unlink(i8* noundef %14) #10
  br label %16

16:                                               ; preds = %9
  %17 = load i32, i32* %1, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, i32* %1, align 4
  br label %5, !llvm.loop !9

19:                                               ; preds = %5
  br label %20

20:                                               ; preds = %19, %0
  %21 = load i8, i8* @isDebug, align 1
  %22 = trunc i8 %21 to i1
  br i1 %22, label %23, label %29

23:                                               ; preds = %20
  %24 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %25 = icmp ne %struct._IO_FILE* %24, null
  br i1 %25, label %26, label %29

26:                                               ; preds = %23
  %27 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %28 = call i32 @fclose(%struct._IO_FILE* noundef %27)
  br label %29

29:                                               ; preds = %26, %23, %20
  %30 = load i8, i8* @isDotfile, align 1
  %31 = trunc i8 %30 to i1
  br i1 %31, label %32, label %40

32:                                               ; preds = %29
  %33 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %34 = icmp ne %struct._IO_FILE* %33, null
  br i1 %34, label %35, label %40

35:                                               ; preds = %32
  %36 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %37 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %36, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.16, i64 0, i64 0))
  %38 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %39 = call i32 @fclose(%struct._IO_FILE* noundef %38)
  br label %40

40:                                               ; preds = %35, %32, %29
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @parse_args(i32 noundef %0, i8** noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i8**, align 8
  %5 = alloca i32, align 4
  %6 = alloca %struct.StringArray, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i8*, align 8
  %12 = alloca i8*, align 8
  %13 = alloca i8*, align 8
  %14 = alloca i8*, align 8
  %15 = alloca i8*, align 8
  %16 = alloca i8*, align 8
  %17 = alloca i8*, align 8
  %18 = alloca i8*, align 8
  %19 = alloca i8*, align 8
  %20 = alloca i8*, align 8
  %21 = alloca i8*, align 8
  %22 = alloca i8*, align 8
  %23 = alloca i8*, align 8
  %24 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i8** %1, i8*** %4, align 8
  store i32 1, i32* %5, align 4
  br label %25

25:                                               ; preds = %49, %2
  %26 = load i32, i32* %5, align 4
  %27 = load i32, i32* %3, align 4
  %28 = icmp slt i32 %26, %27
  br i1 %28, label %29, label %52

29:                                               ; preds = %25
  %30 = load i8**, i8*** %4, align 8
  %31 = load i32, i32* %5, align 4
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds i8*, i8** %30, i64 %32
  %34 = load i8*, i8** %33, align 8
  %35 = call zeroext i1 @take_arg(i8* noundef %34)
  br i1 %35, label %36, label %48

36:                                               ; preds = %29
  %37 = load i8**, i8*** %4, align 8
  %38 = load i32, i32* %5, align 4
  %39 = add nsw i32 %38, 1
  store i32 %39, i32* %5, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds i8*, i8** %37, i64 %40
  %42 = load i8*, i8** %41, align 8
  %43 = icmp ne i8* %42, null
  br i1 %43, label %47, label %44

44:                                               ; preds = %36
  %45 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([84 x i8], [84 x i8]* @.str.17, i64 0, i64 0))
  %46 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([130 x i8], [130 x i8]* @.str.18, i64 0, i64 0))
  call void @usage(i32 noundef 1)
  br label %47

47:                                               ; preds = %44, %36
  br label %48

48:                                               ; preds = %47, %29
  br label %49

49:                                               ; preds = %48
  %50 = load i32, i32* %5, align 4
  %51 = add nsw i32 %50, 1
  store i32 %51, i32* %5, align 4
  br label %25, !llvm.loop !10

52:                                               ; preds = %25
  %53 = bitcast %struct.StringArray* %6 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %53, i8 0, i64 16, i1 false)
  store i32 1, i32* %7, align 4
  br label %54

54:                                               ; preds = %992, %52
  %55 = load i32, i32* %7, align 4
  %56 = load i32, i32* %3, align 4
  %57 = icmp slt i32 %55, %56
  br i1 %57, label %58, label %995

58:                                               ; preds = %54
  %59 = load i8**, i8*** %4, align 8
  %60 = load i32, i32* %7, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds i8*, i8** %59, i64 %61
  %63 = load i8*, i8** %62, align 8
  %64 = call i32 @strcmp(i8* noundef %63, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.19, i64 0, i64 0)) #11
  %65 = icmp ne i32 %64, 0
  br i1 %65, label %67, label %66

66:                                               ; preds = %58
  store i8 1, i8* @opt_hash_hash_hash, align 1
  br label %992

67:                                               ; preds = %58
  %68 = load i8**, i8*** %4, align 8
  %69 = load i32, i32* %7, align 4
  %70 = sext i32 %69 to i64
  %71 = getelementptr inbounds i8*, i8** %68, i64 %70
  %72 = load i8*, i8** %71, align 8
  %73 = call i32 @strcmp(i8* noundef %72, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0)) #11
  %74 = icmp ne i32 %73, 0
  br i1 %74, label %76, label %75

75:                                               ; preds = %67
  store i8 1, i8* @opt_cc1, align 1
  br label %992

76:                                               ; preds = %67
  %77 = load i8**, i8*** %4, align 8
  %78 = load i32, i32* %7, align 4
  %79 = sext i32 %78 to i64
  %80 = getelementptr inbounds i8*, i8** %77, i64 %79
  %81 = load i8*, i8** %80, align 8
  %82 = call i32 @strcmp(i8* noundef %81, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.21, i64 0, i64 0)) #11
  %83 = icmp ne i32 %82, 0
  br i1 %83, label %84, label %92

84:                                               ; preds = %76
  %85 = load i8**, i8*** %4, align 8
  %86 = load i32, i32* %7, align 4
  %87 = sext i32 %86 to i64
  %88 = getelementptr inbounds i8*, i8** %85, i64 %87
  %89 = load i8*, i8** %88, align 8
  %90 = call i32 @strcmp(i8* noundef %89, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.22, i64 0, i64 0)) #11
  %91 = icmp ne i32 %90, 0
  br i1 %91, label %93, label %92

92:                                               ; preds = %84, %76
  call void @usage(i32 noundef 0)
  br label %992

93:                                               ; preds = %84
  %94 = load i8**, i8*** %4, align 8
  %95 = load i32, i32* %7, align 4
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds i8*, i8** %94, i64 %96
  %98 = load i8*, i8** %97, align 8
  %99 = call i32 @strcmp(i8* noundef %98, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.23, i64 0, i64 0)) #11
  %100 = icmp ne i32 %99, 0
  br i1 %100, label %101, label %109

101:                                              ; preds = %93
  %102 = load i8**, i8*** %4, align 8
  %103 = load i32, i32* %7, align 4
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds i8*, i8** %102, i64 %104
  %106 = load i8*, i8** %105, align 8
  %107 = call i32 @strcmp(i8* noundef %106, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.24, i64 0, i64 0)) #11
  %108 = icmp ne i32 %107, 0
  br i1 %108, label %110, label %109

109:                                              ; preds = %101, %93
  call void @printVersion(i32 noundef 0)
  br label %992

110:                                              ; preds = %101
  %111 = load i8**, i8*** %4, align 8
  %112 = load i32, i32* %7, align 4
  %113 = sext i32 %112 to i64
  %114 = getelementptr inbounds i8*, i8** %111, i64 %113
  %115 = load i8*, i8** %114, align 8
  %116 = call i32 @strcmp(i8* noundef %115, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.25, i64 0, i64 0)) #11
  %117 = icmp ne i32 %116, 0
  br i1 %117, label %126, label %118

118:                                              ; preds = %110
  %119 = load i8**, i8*** %4, align 8
  %120 = load i32, i32* %7, align 4
  %121 = add nsw i32 %120, 1
  store i32 %121, i32* %7, align 4
  %122 = sext i32 %121 to i64
  %123 = getelementptr inbounds i8*, i8** %119, i64 %122
  %124 = load i8*, i8** %123, align 8
  store i8* %124, i8** @opt_linker, align 8
  %125 = load i8*, i8** @opt_linker, align 8
  call void @check_parms_length(i8* noundef %125)
  br label %992

126:                                              ; preds = %110
  %127 = load i8**, i8*** %4, align 8
  %128 = load i32, i32* %7, align 4
  %129 = sext i32 %128 to i64
  %130 = getelementptr inbounds i8*, i8** %127, i64 %129
  %131 = load i8*, i8** %130, align 8
  %132 = call i32 @strcmp(i8* noundef %131, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.26, i64 0, i64 0)) #11
  %133 = icmp ne i32 %132, 0
  br i1 %133, label %142, label %134

134:                                              ; preds = %126
  %135 = load i8**, i8*** %4, align 8
  %136 = load i32, i32* %7, align 4
  %137 = add nsw i32 %136, 1
  store i32 %137, i32* %7, align 4
  %138 = sext i32 %137 to i64
  %139 = getelementptr inbounds i8*, i8** %135, i64 %138
  %140 = load i8*, i8** %139, align 8
  store i8* %140, i8** @opt_o, align 8
  %141 = load i8*, i8** @opt_o, align 8
  call void @check_parms_length(i8* noundef %141)
  br label %992

142:                                              ; preds = %126
  %143 = load i8**, i8*** %4, align 8
  %144 = load i32, i32* %7, align 4
  %145 = sext i32 %144 to i64
  %146 = getelementptr inbounds i8*, i8** %143, i64 %145
  %147 = load i8*, i8** %146, align 8
  %148 = call i32 @strncmp(i8* noundef %147, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.26, i64 0, i64 0), i64 noundef 2) #11
  %149 = icmp ne i32 %148, 0
  br i1 %149, label %157, label %150

150:                                              ; preds = %142
  %151 = load i8**, i8*** %4, align 8
  %152 = load i32, i32* %7, align 4
  %153 = sext i32 %152 to i64
  %154 = getelementptr inbounds i8*, i8** %151, i64 %153
  %155 = load i8*, i8** %154, align 8
  %156 = getelementptr inbounds i8, i8* %155, i64 2
  store i8* %156, i8** @opt_o, align 8
  br label %992

157:                                              ; preds = %142
  %158 = load i8**, i8*** %4, align 8
  %159 = load i32, i32* %7, align 4
  %160 = sext i32 %159 to i64
  %161 = getelementptr inbounds i8*, i8** %158, i64 %160
  %162 = load i8*, i8** %161, align 8
  %163 = call i32 @strcmp(i8* noundef %162, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.27, i64 0, i64 0)) #11
  %164 = icmp ne i32 %163, 0
  br i1 %164, label %166, label %165

165:                                              ; preds = %157
  store i8 1, i8* @opt_S, align 1
  br label %992

166:                                              ; preds = %157
  %167 = load i8**, i8*** %4, align 8
  %168 = load i32, i32* %7, align 4
  %169 = sext i32 %168 to i64
  %170 = getelementptr inbounds i8*, i8** %167, i64 %169
  %171 = load i8*, i8** %170, align 8
  %172 = call i32 @strcmp(i8* noundef %171, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.28, i64 0, i64 0)) #11
  %173 = icmp ne i32 %172, 0
  br i1 %173, label %175, label %174

174:                                              ; preds = %166
  store i8 1, i8* @isDebug, align 1
  br label %992

175:                                              ; preds = %166
  %176 = load i8**, i8*** %4, align 8
  %177 = load i32, i32* %7, align 4
  %178 = sext i32 %177 to i64
  %179 = getelementptr inbounds i8*, i8** %176, i64 %178
  %180 = load i8*, i8** %179, align 8
  %181 = call i32 @strcmp(i8* noundef %180, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.29, i64 0, i64 0)) #11
  %182 = icmp ne i32 %181, 0
  br i1 %182, label %184, label %183

183:                                              ; preds = %175
  store i8 1, i8* @isDotfile, align 1
  br label %992

184:                                              ; preds = %175
  %185 = load i8**, i8*** %4, align 8
  %186 = load i32, i32* %7, align 4
  %187 = sext i32 %186 to i64
  %188 = getelementptr inbounds i8*, i8** %185, i64 %187
  %189 = load i8*, i8** %188, align 8
  %190 = call i32 @strcmp(i8* noundef %189, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.30, i64 0, i64 0)) #11
  %191 = icmp ne i32 %190, 0
  br i1 %191, label %193, label %192

192:                                              ; preds = %184
  store i8 1, i8* @opt_fcommon, align 1
  br label %992

193:                                              ; preds = %184
  %194 = load i8**, i8*** %4, align 8
  %195 = load i32, i32* %7, align 4
  %196 = sext i32 %195 to i64
  %197 = getelementptr inbounds i8*, i8** %194, i64 %196
  %198 = load i8*, i8** %197, align 8
  %199 = call i32 @strcmp(i8* noundef %198, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.31, i64 0, i64 0)) #11
  %200 = icmp ne i32 %199, 0
  br i1 %200, label %202, label %201

201:                                              ; preds = %193
  store i8 0, i8* @opt_fcommon, align 1
  br label %992

202:                                              ; preds = %193
  %203 = load i8**, i8*** %4, align 8
  %204 = load i32, i32* %7, align 4
  %205 = sext i32 %204 to i64
  %206 = getelementptr inbounds i8*, i8** %203, i64 %205
  %207 = load i8*, i8** %206, align 8
  %208 = call i32 @strcmp(i8* noundef %207, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.32, i64 0, i64 0)) #11
  %209 = icmp ne i32 %208, 0
  br i1 %209, label %211, label %210

210:                                              ; preds = %202
  store i8 0, i8* @opt_fbuiltin, align 1
  br label %992

211:                                              ; preds = %202
  %212 = load i8**, i8*** %4, align 8
  %213 = load i32, i32* %7, align 4
  %214 = sext i32 %213 to i64
  %215 = getelementptr inbounds i8*, i8** %212, i64 %214
  %216 = load i8*, i8** %215, align 8
  %217 = call i32 @strcmp(i8* noundef %216, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.33, i64 0, i64 0)) #11
  %218 = icmp ne i32 %217, 0
  br i1 %218, label %220, label %219

219:                                              ; preds = %211
  store i8 1, i8* @opt_c, align 1
  br label %992

220:                                              ; preds = %211
  %221 = load i8**, i8*** %4, align 8
  %222 = load i32, i32* %7, align 4
  %223 = sext i32 %222 to i64
  %224 = getelementptr inbounds i8*, i8** %221, i64 %223
  %225 = load i8*, i8** %224, align 8
  %226 = call i32 @strcmp(i8* noundef %225, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.34, i64 0, i64 0)) #11
  %227 = icmp ne i32 %226, 0
  br i1 %227, label %229, label %228

228:                                              ; preds = %220
  store i8 1, i8* @opt_E, align 1
  br label %992

229:                                              ; preds = %220
  %230 = load i8**, i8*** %4, align 8
  %231 = load i32, i32* %7, align 4
  %232 = sext i32 %231 to i64
  %233 = getelementptr inbounds i8*, i8** %230, i64 %232
  %234 = load i8*, i8** %233, align 8
  %235 = call i32 @strncmp(i8* noundef %234, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.35, i64 0, i64 0), i64 noundef 2) #11
  %236 = icmp ne i32 %235, 0
  br i1 %236, label %260, label %237

237:                                              ; preds = %229
  %238 = load i8**, i8*** %4, align 8
  %239 = load i32, i32* %7, align 4
  %240 = sext i32 %239 to i64
  %241 = getelementptr inbounds i8*, i8** %238, i64 %240
  %242 = load i8*, i8** %241, align 8
  %243 = call i64 @strlen(i8* noundef %242) #11
  %244 = icmp eq i64 %243, 2
  br i1 %244, label %245, label %252

245:                                              ; preds = %237
  %246 = load i8**, i8*** %4, align 8
  %247 = load i32, i32* %7, align 4
  %248 = add nsw i32 %247, 1
  store i32 %248, i32* %7, align 4
  %249 = sext i32 %248 to i64
  %250 = getelementptr inbounds i8*, i8** %246, i64 %249
  %251 = load i8*, i8** %250, align 8
  call void @strarray_push(%struct.StringArray* noundef @include_paths, i8* noundef %251)
  br label %259

252:                                              ; preds = %237
  %253 = load i8**, i8*** %4, align 8
  %254 = load i32, i32* %7, align 4
  %255 = sext i32 %254 to i64
  %256 = getelementptr inbounds i8*, i8** %253, i64 %255
  %257 = load i8*, i8** %256, align 8
  %258 = getelementptr inbounds i8, i8* %257, i64 2
  call void @strarray_push(%struct.StringArray* noundef @include_paths, i8* noundef %258)
  br label %259

259:                                              ; preds = %252, %245
  br label %992

260:                                              ; preds = %229
  %261 = load i8**, i8*** %4, align 8
  %262 = load i32, i32* %7, align 4
  %263 = sext i32 %262 to i64
  %264 = getelementptr inbounds i8*, i8** %261, i64 %263
  %265 = load i8*, i8** %264, align 8
  %266 = call i32 @strcmp(i8* noundef %265, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.36, i64 0, i64 0)) #11
  %267 = icmp ne i32 %266, 0
  br i1 %267, label %277, label %268

268:                                              ; preds = %260
  %269 = load i8**, i8*** %4, align 8
  %270 = load i32, i32* %7, align 4
  %271 = add nsw i32 %270, 1
  store i32 %271, i32* %7, align 4
  %272 = sext i32 %271 to i64
  %273 = getelementptr inbounds i8*, i8** %269, i64 %272
  %274 = load i8*, i8** %273, align 8
  store i8* %274, i8** %8, align 8
  %275 = load i8*, i8** %8, align 8
  call void @check_parms_length(i8* noundef %275)
  %276 = load i8*, i8** %8, align 8
  call void @define(i8* noundef %276)
  br label %992

277:                                              ; preds = %260
  %278 = load i8**, i8*** %4, align 8
  %279 = load i32, i32* %7, align 4
  %280 = sext i32 %279 to i64
  %281 = getelementptr inbounds i8*, i8** %278, i64 %280
  %282 = load i8*, i8** %281, align 8
  %283 = call i32 @strncmp(i8* noundef %282, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.36, i64 0, i64 0), i64 noundef 2) #11
  %284 = icmp ne i32 %283, 0
  br i1 %284, label %294, label %285

285:                                              ; preds = %277
  %286 = load i8**, i8*** %4, align 8
  %287 = load i32, i32* %7, align 4
  %288 = sext i32 %287 to i64
  %289 = getelementptr inbounds i8*, i8** %286, i64 %288
  %290 = load i8*, i8** %289, align 8
  %291 = getelementptr inbounds i8, i8* %290, i64 2
  store i8* %291, i8** %9, align 8
  %292 = load i8*, i8** %9, align 8
  call void @check_parms_length(i8* noundef %292)
  %293 = load i8*, i8** %9, align 8
  call void @define(i8* noundef %293)
  br label %992

294:                                              ; preds = %277
  %295 = load i8**, i8*** %4, align 8
  %296 = load i32, i32* %7, align 4
  %297 = sext i32 %296 to i64
  %298 = getelementptr inbounds i8*, i8** %295, i64 %297
  %299 = load i8*, i8** %298, align 8
  %300 = call i32 @strcmp(i8* noundef %299, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i64 0, i64 0)) #11
  %301 = icmp ne i32 %300, 0
  br i1 %301, label %311, label %302

302:                                              ; preds = %294
  %303 = load i8**, i8*** %4, align 8
  %304 = load i32, i32* %7, align 4
  %305 = add nsw i32 %304, 1
  store i32 %305, i32* %7, align 4
  %306 = sext i32 %305 to i64
  %307 = getelementptr inbounds i8*, i8** %303, i64 %306
  %308 = load i8*, i8** %307, align 8
  store i8* %308, i8** %10, align 8
  %309 = load i8*, i8** %10, align 8
  call void @check_parms_length(i8* noundef %309)
  %310 = load i8*, i8** %10, align 8
  call void @undef_macro(i8* noundef %310)
  br label %992

311:                                              ; preds = %294
  %312 = load i8**, i8*** %4, align 8
  %313 = load i32, i32* %7, align 4
  %314 = sext i32 %313 to i64
  %315 = getelementptr inbounds i8*, i8** %312, i64 %314
  %316 = load i8*, i8** %315, align 8
  %317 = call i32 @strncmp(i8* noundef %316, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i64 0, i64 0), i64 noundef 2) #11
  %318 = icmp ne i32 %317, 0
  br i1 %318, label %328, label %319

319:                                              ; preds = %311
  %320 = load i8**, i8*** %4, align 8
  %321 = load i32, i32* %7, align 4
  %322 = sext i32 %321 to i64
  %323 = getelementptr inbounds i8*, i8** %320, i64 %322
  %324 = load i8*, i8** %323, align 8
  %325 = getelementptr inbounds i8, i8* %324, i64 2
  store i8* %325, i8** %11, align 8
  %326 = load i8*, i8** %11, align 8
  call void @check_parms_length(i8* noundef %326)
  %327 = load i8*, i8** %11, align 8
  call void @undef_macro(i8* noundef %327)
  br label %992

328:                                              ; preds = %311
  %329 = load i8**, i8*** %4, align 8
  %330 = load i32, i32* %7, align 4
  %331 = sext i32 %330 to i64
  %332 = getelementptr inbounds i8*, i8** %329, i64 %331
  %333 = load i8*, i8** %332, align 8
  %334 = call i32 @strcmp(i8* noundef %333, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.38, i64 0, i64 0)) #11
  %335 = icmp ne i32 %334, 0
  br i1 %335, label %345, label %336

336:                                              ; preds = %328
  %337 = load i8**, i8*** %4, align 8
  %338 = load i32, i32* %7, align 4
  %339 = add nsw i32 %338, 1
  store i32 %339, i32* %7, align 4
  %340 = sext i32 %339 to i64
  %341 = getelementptr inbounds i8*, i8** %337, i64 %340
  %342 = load i8*, i8** %341, align 8
  store i8* %342, i8** %12, align 8
  %343 = load i8*, i8** %12, align 8
  call void @check_parms_length(i8* noundef %343)
  %344 = load i8*, i8** %12, align 8
  call void @strarray_push(%struct.StringArray* noundef @opt_include, i8* noundef %344)
  br label %992

345:                                              ; preds = %328
  %346 = load i8**, i8*** %4, align 8
  %347 = load i32, i32* %7, align 4
  %348 = sext i32 %347 to i64
  %349 = getelementptr inbounds i8*, i8** %346, i64 %348
  %350 = load i8*, i8** %349, align 8
  %351 = call i32 @strcmp(i8* noundef %350, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.39, i64 0, i64 0)) #11
  %352 = icmp ne i32 %351, 0
  br i1 %352, label %363, label %353

353:                                              ; preds = %345
  %354 = load i8**, i8*** %4, align 8
  %355 = load i32, i32* %7, align 4
  %356 = add nsw i32 %355, 1
  store i32 %356, i32* %7, align 4
  %357 = sext i32 %356 to i64
  %358 = getelementptr inbounds i8*, i8** %354, i64 %357
  %359 = load i8*, i8** %358, align 8
  store i8* %359, i8** %13, align 8
  %360 = load i8*, i8** %13, align 8
  call void @check_parms_length(i8* noundef %360)
  %361 = load i8*, i8** %13, align 8
  %362 = call i32 @parse_opt_x(i8* noundef %361)
  store i32 %362, i32* @opt_x, align 4
  br label %992

363:                                              ; preds = %345
  %364 = load i8**, i8*** %4, align 8
  %365 = load i32, i32* %7, align 4
  %366 = sext i32 %365 to i64
  %367 = getelementptr inbounds i8*, i8** %364, i64 %366
  %368 = load i8*, i8** %367, align 8
  %369 = call i32 @strncmp(i8* noundef %368, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.39, i64 0, i64 0), i64 noundef 2) #11
  %370 = icmp ne i32 %369, 0
  br i1 %370, label %381, label %371

371:                                              ; preds = %363
  %372 = load i8**, i8*** %4, align 8
  %373 = load i32, i32* %7, align 4
  %374 = sext i32 %373 to i64
  %375 = getelementptr inbounds i8*, i8** %372, i64 %374
  %376 = load i8*, i8** %375, align 8
  %377 = getelementptr inbounds i8, i8* %376, i64 2
  store i8* %377, i8** %14, align 8
  %378 = load i8*, i8** %14, align 8
  call void @check_parms_length(i8* noundef %378)
  %379 = load i8*, i8** %14, align 8
  %380 = call i32 @parse_opt_x(i8* noundef %379)
  store i32 %380, i32* @opt_x, align 4
  br label %992

381:                                              ; preds = %363
  %382 = load i8**, i8*** %4, align 8
  %383 = load i32, i32* %7, align 4
  %384 = sext i32 %383 to i64
  %385 = getelementptr inbounds i8*, i8** %382, i64 %384
  %386 = load i8*, i8** %385, align 8
  %387 = call i32 @strncmp(i8* noundef %386, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0), i64 noundef 2) #11
  %388 = icmp ne i32 %387, 0
  br i1 %388, label %389, label %397

389:                                              ; preds = %381
  %390 = load i8**, i8*** %4, align 8
  %391 = load i32, i32* %7, align 4
  %392 = sext i32 %391 to i64
  %393 = getelementptr inbounds i8*, i8** %390, i64 %392
  %394 = load i8*, i8** %393, align 8
  %395 = call i32 @strncmp(i8* noundef %394, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.10, i64 0, i64 0), i64 noundef 4) #11
  %396 = icmp ne i32 %395, 0
  br i1 %396, label %414, label %397

397:                                              ; preds = %389, %381
  %398 = load i8**, i8*** %4, align 8
  %399 = load i32, i32* %7, align 4
  %400 = sext i32 %399 to i64
  %401 = getelementptr inbounds i8*, i8** %398, i64 %400
  %402 = load i8*, i8** %401, align 8
  %403 = call i32 @strncmp(i8* noundef %402, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.40, i64 0, i64 0), i64 noundef 6) #11
  %404 = icmp ne i32 %403, 0
  br i1 %404, label %406, label %405

405:                                              ; preds = %397
  br label %992

406:                                              ; preds = %397
  %407 = load i8**, i8*** %4, align 8
  %408 = load i32, i32* %7, align 4
  %409 = sext i32 %408 to i64
  %410 = getelementptr inbounds i8*, i8** %407, i64 %409
  %411 = load i8*, i8** %410, align 8
  store i8* %411, i8** %15, align 8
  %412 = load i8*, i8** %15, align 8
  call void @check_parms_length(i8* noundef %412)
  %413 = load i8*, i8** %15, align 8
  call void @strarray_push(%struct.StringArray* noundef @input_paths, i8* noundef %413)
  br label %992

414:                                              ; preds = %389
  %415 = load i8**, i8*** %4, align 8
  %416 = load i32, i32* %7, align 4
  %417 = sext i32 %416 to i64
  %418 = getelementptr inbounds i8*, i8** %415, i64 %417
  %419 = load i8*, i8** %418, align 8
  %420 = call i32 @strcmp(i8* noundef %419, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.41, i64 0, i64 0)) #11
  %421 = icmp ne i32 %420, 0
  br i1 %421, label %431, label %422

422:                                              ; preds = %414
  %423 = load i8**, i8*** %4, align 8
  %424 = load i32, i32* %7, align 4
  %425 = add nsw i32 %424, 1
  store i32 %425, i32* %7, align 4
  %426 = sext i32 %425 to i64
  %427 = getelementptr inbounds i8*, i8** %423, i64 %426
  %428 = load i8*, i8** %427, align 8
  store i8* %428, i8** %16, align 8
  %429 = load i8*, i8** %16, align 8
  call void @check_parms_length(i8* noundef %429)
  %430 = load i8*, i8** %16, align 8
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef %430)
  br label %992

431:                                              ; preds = %414
  %432 = load i8**, i8*** %4, align 8
  %433 = load i32, i32* %7, align 4
  %434 = sext i32 %433 to i64
  %435 = getelementptr inbounds i8*, i8** %432, i64 %434
  %436 = load i8*, i8** %435, align 8
  %437 = call i32 @strcmp(i8* noundef %436, i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.42, i64 0, i64 0)) #11
  %438 = icmp ne i32 %437, 0
  br i1 %438, label %439, label %447

439:                                              ; preds = %431
  %440 = load i8**, i8*** %4, align 8
  %441 = load i32, i32* %7, align 4
  %442 = sext i32 %441 to i64
  %443 = getelementptr inbounds i8*, i8** %440, i64 %442
  %444 = load i8*, i8** %443, align 8
  %445 = call i32 @strcmp(i8* noundef %444, i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.43, i64 0, i64 0)) #11
  %446 = icmp ne i32 %445, 0
  br i1 %446, label %456, label %447

447:                                              ; preds = %439, %431
  %448 = load i8**, i8*** %4, align 8
  %449 = load i32, i32* %7, align 4
  %450 = add nsw i32 %449, 1
  store i32 %450, i32* %7, align 4
  %451 = sext i32 %450 to i64
  %452 = getelementptr inbounds i8*, i8** %448, i64 %451
  %453 = load i8*, i8** %452, align 8
  store i8* %453, i8** %17, align 8
  %454 = load i8*, i8** %17, align 8
  call void @check_parms_length(i8* noundef %454)
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.43, i64 0, i64 0))
  %455 = load i8*, i8** %17, align 8
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef %455)
  br label %992

456:                                              ; preds = %439
  %457 = load i8**, i8*** %4, align 8
  %458 = load i32, i32* %7, align 4
  %459 = sext i32 %458 to i64
  %460 = getelementptr inbounds i8*, i8** %457, i64 %459
  %461 = load i8*, i8** %460, align 8
  %462 = call i32 @strcmp(i8* noundef %461, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.39, i64 0, i64 0)) #11
  %463 = icmp ne i32 %462, 0
  br i1 %463, label %473, label %464

464:                                              ; preds = %456
  %465 = load i8**, i8*** %4, align 8
  %466 = load i32, i32* %7, align 4
  %467 = add nsw i32 %466, 1
  store i32 %467, i32* %7, align 4
  %468 = sext i32 %467 to i64
  %469 = getelementptr inbounds i8*, i8** %465, i64 %468
  %470 = load i8*, i8** %469, align 8
  store i8* %470, i8** %18, align 8
  %471 = load i8*, i8** %18, align 8
  call void @check_parms_length(i8* noundef %471)
  %472 = load i8*, i8** %18, align 8
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef %472)
  br label %992

473:                                              ; preds = %456
  %474 = load i8**, i8*** %4, align 8
  %475 = load i32, i32* %7, align 4
  %476 = sext i32 %475 to i64
  %477 = getelementptr inbounds i8*, i8** %474, i64 %476
  %478 = load i8*, i8** %477, align 8
  %479 = call i32 @strcmp(i8* noundef %478, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.44, i64 0, i64 0)) #11
  %480 = icmp ne i32 %479, 0
  br i1 %480, label %482, label %481

481:                                              ; preds = %473
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.44, i64 0, i64 0))
  br label %992

482:                                              ; preds = %473
  %483 = load i8**, i8*** %4, align 8
  %484 = load i32, i32* %7, align 4
  %485 = sext i32 %484 to i64
  %486 = getelementptr inbounds i8*, i8** %483, i64 %485
  %487 = load i8*, i8** %486, align 8
  %488 = call i32 @strcmp(i8* noundef %487, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.45, i64 0, i64 0)) #11
  %489 = icmp ne i32 %488, 0
  br i1 %489, label %491, label %490

490:                                              ; preds = %482
  store i8 1, i8* @opt_M, align 1
  br label %992

491:                                              ; preds = %482
  %492 = load i8**, i8*** %4, align 8
  %493 = load i32, i32* %7, align 4
  %494 = sext i32 %493 to i64
  %495 = getelementptr inbounds i8*, i8** %492, i64 %494
  %496 = load i8*, i8** %495, align 8
  %497 = call i32 @strcmp(i8* noundef %496, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.46, i64 0, i64 0)) #11
  %498 = icmp ne i32 %497, 0
  br i1 %498, label %507, label %499

499:                                              ; preds = %491
  %500 = load i8**, i8*** %4, align 8
  %501 = load i32, i32* %7, align 4
  %502 = add nsw i32 %501, 1
  store i32 %502, i32* %7, align 4
  %503 = sext i32 %502 to i64
  %504 = getelementptr inbounds i8*, i8** %500, i64 %503
  %505 = load i8*, i8** %504, align 8
  store i8* %505, i8** @opt_MF, align 8
  %506 = load i8*, i8** @opt_MF, align 8
  call void @check_parms_length(i8* noundef %506)
  br label %992

507:                                              ; preds = %491
  %508 = load i8**, i8*** %4, align 8
  %509 = load i32, i32* %7, align 4
  %510 = sext i32 %509 to i64
  %511 = getelementptr inbounds i8*, i8** %508, i64 %510
  %512 = load i8*, i8** %511, align 8
  %513 = call i32 @strcmp(i8* noundef %512, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.47, i64 0, i64 0)) #11
  %514 = icmp ne i32 %513, 0
  br i1 %514, label %516, label %515

515:                                              ; preds = %507
  store i8 1, i8* @opt_MP, align 1
  br label %992

516:                                              ; preds = %507
  %517 = load i8**, i8*** %4, align 8
  %518 = load i32, i32* %7, align 4
  %519 = sext i32 %518 to i64
  %520 = getelementptr inbounds i8*, i8** %517, i64 %519
  %521 = load i8*, i8** %520, align 8
  %522 = call i32 @strcmp(i8* noundef %521, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.48, i64 0, i64 0)) #11
  %523 = icmp ne i32 %522, 0
  br i1 %523, label %545, label %524

524:                                              ; preds = %516
  %525 = load i8*, i8** @opt_MT, align 8
  %526 = icmp eq i8* %525, null
  br i1 %526, label %527, label %534

527:                                              ; preds = %524
  %528 = load i8**, i8*** %4, align 8
  %529 = load i32, i32* %7, align 4
  %530 = add nsw i32 %529, 1
  store i32 %530, i32* %7, align 4
  %531 = sext i32 %530 to i64
  %532 = getelementptr inbounds i8*, i8** %528, i64 %531
  %533 = load i8*, i8** %532, align 8
  store i8* %533, i8** @opt_MT, align 8
  br label %543

534:                                              ; preds = %524
  %535 = load i8*, i8** @opt_MT, align 8
  %536 = load i8**, i8*** %4, align 8
  %537 = load i32, i32* %7, align 4
  %538 = add nsw i32 %537, 1
  store i32 %538, i32* %7, align 4
  %539 = sext i32 %538 to i64
  %540 = getelementptr inbounds i8*, i8** %536, i64 %539
  %541 = load i8*, i8** %540, align 8
  %542 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.49, i64 0, i64 0), i8* noundef %535, i8* noundef %541)
  store i8* %542, i8** @opt_MT, align 8
  br label %543

543:                                              ; preds = %534, %527
  %544 = load i8*, i8** @opt_MT, align 8
  call void @check_parms_length(i8* noundef %544)
  br label %992

545:                                              ; preds = %516
  %546 = load i8**, i8*** %4, align 8
  %547 = load i32, i32* %7, align 4
  %548 = sext i32 %547 to i64
  %549 = getelementptr inbounds i8*, i8** %546, i64 %548
  %550 = load i8*, i8** %549, align 8
  %551 = call i32 @strcmp(i8* noundef %550, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.50, i64 0, i64 0)) #11
  %552 = icmp ne i32 %551, 0
  br i1 %552, label %554, label %553

553:                                              ; preds = %545
  store i8 1, i8* @opt_MD, align 1
  br label %992

554:                                              ; preds = %545
  %555 = load i8**, i8*** %4, align 8
  %556 = load i32, i32* %7, align 4
  %557 = sext i32 %556 to i64
  %558 = getelementptr inbounds i8*, i8** %555, i64 %557
  %559 = load i8*, i8** %558, align 8
  %560 = call i32 @strcmp(i8* noundef %559, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.51, i64 0, i64 0)) #11
  %561 = icmp ne i32 %560, 0
  br i1 %561, label %585, label %562

562:                                              ; preds = %554
  %563 = load i8*, i8** @opt_MT, align 8
  %564 = icmp eq i8* %563, null
  br i1 %564, label %565, label %573

565:                                              ; preds = %562
  %566 = load i8**, i8*** %4, align 8
  %567 = load i32, i32* %7, align 4
  %568 = add nsw i32 %567, 1
  store i32 %568, i32* %7, align 4
  %569 = sext i32 %568 to i64
  %570 = getelementptr inbounds i8*, i8** %566, i64 %569
  %571 = load i8*, i8** %570, align 8
  %572 = call i8* @quote_makefile(i8* noundef %571)
  store i8* %572, i8** @opt_MT, align 8
  br label %583

573:                                              ; preds = %562
  %574 = load i8*, i8** @opt_MT, align 8
  %575 = load i8**, i8*** %4, align 8
  %576 = load i32, i32* %7, align 4
  %577 = add nsw i32 %576, 1
  store i32 %577, i32* %7, align 4
  %578 = sext i32 %577 to i64
  %579 = getelementptr inbounds i8*, i8** %575, i64 %578
  %580 = load i8*, i8** %579, align 8
  %581 = call i8* @quote_makefile(i8* noundef %580)
  %582 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.49, i64 0, i64 0), i8* noundef %574, i8* noundef %581)
  store i8* %582, i8** @opt_MT, align 8
  br label %583

583:                                              ; preds = %573, %565
  %584 = load i8*, i8** @opt_MT, align 8
  call void @check_parms_length(i8* noundef %584)
  br label %992

585:                                              ; preds = %554
  %586 = load i8**, i8*** %4, align 8
  %587 = load i32, i32* %7, align 4
  %588 = sext i32 %587 to i64
  %589 = getelementptr inbounds i8*, i8** %586, i64 %588
  %590 = load i8*, i8** %589, align 8
  %591 = call i32 @strcmp(i8* noundef %590, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.52, i64 0, i64 0)) #11
  %592 = icmp ne i32 %591, 0
  br i1 %592, label %594, label %593

593:                                              ; preds = %585
  store i8 1, i8* @opt_MMD, align 1
  store i8 1, i8* @opt_MD, align 1
  br label %992

594:                                              ; preds = %585
  %595 = load i8**, i8*** %4, align 8
  %596 = load i32, i32* %7, align 4
  %597 = sext i32 %596 to i64
  %598 = getelementptr inbounds i8*, i8** %595, i64 %597
  %599 = load i8*, i8** %598, align 8
  %600 = call i32 @strcmp(i8* noundef %599, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.53, i64 0, i64 0)) #11
  %601 = icmp ne i32 %600, 0
  br i1 %601, label %602, label %610

602:                                              ; preds = %594
  %603 = load i8**, i8*** %4, align 8
  %604 = load i32, i32* %7, align 4
  %605 = sext i32 %604 to i64
  %606 = getelementptr inbounds i8*, i8** %603, i64 %605
  %607 = load i8*, i8** %606, align 8
  %608 = call i32 @strcmp(i8* noundef %607, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.54, i64 0, i64 0)) #11
  %609 = icmp ne i32 %608, 0
  br i1 %609, label %611, label %610

610:                                              ; preds = %602, %594
  store i8 1, i8* @opt_fpic, align 1
  br label %992

611:                                              ; preds = %602
  %612 = load i8**, i8*** %4, align 8
  %613 = load i32, i32* %7, align 4
  %614 = sext i32 %613 to i64
  %615 = getelementptr inbounds i8*, i8** %612, i64 %614
  %616 = load i8*, i8** %615, align 8
  %617 = call i32 @strcmp(i8* noundef %616, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.55, i64 0, i64 0)) #11
  %618 = icmp ne i32 %617, 0
  br i1 %618, label %620, label %619

619:                                              ; preds = %611
  store i8 0, i8* @opt_fpic, align 1
  br label %992

620:                                              ; preds = %611
  %621 = load i8**, i8*** %4, align 8
  %622 = load i32, i32* %7, align 4
  %623 = sext i32 %622 to i64
  %624 = getelementptr inbounds i8*, i8** %621, i64 %623
  %625 = load i8*, i8** %624, align 8
  %626 = call i32 @strcmp(i8* noundef %625, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.56, i64 0, i64 0)) #11
  %627 = icmp ne i32 %626, 0
  br i1 %627, label %636, label %628

628:                                              ; preds = %620
  %629 = load i8**, i8*** %4, align 8
  %630 = load i32, i32* %7, align 4
  %631 = add nsw i32 %630, 1
  store i32 %631, i32* %7, align 4
  %632 = sext i32 %631 to i64
  %633 = getelementptr inbounds i8*, i8** %629, i64 %632
  %634 = load i8*, i8** %633, align 8
  store i8* %634, i8** @base_file, align 8
  %635 = load i8*, i8** @base_file, align 8
  call void @check_parms_length(i8* noundef %635)
  store i8 1, i8* @isCc1input, align 1
  br label %992

636:                                              ; preds = %620
  %637 = load i8**, i8*** %4, align 8
  %638 = load i32, i32* %7, align 4
  %639 = sext i32 %638 to i64
  %640 = getelementptr inbounds i8*, i8** %637, i64 %639
  %641 = load i8*, i8** %640, align 8
  %642 = call i32 @strcmp(i8* noundef %641, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.57, i64 0, i64 0)) #11
  %643 = icmp ne i32 %642, 0
  br i1 %643, label %652, label %644

644:                                              ; preds = %636
  store i8 1, i8* @isCc1output, align 1
  %645 = load i8**, i8*** %4, align 8
  %646 = load i32, i32* %7, align 4
  %647 = add nsw i32 %646, 1
  store i32 %647, i32* %7, align 4
  %648 = sext i32 %647 to i64
  %649 = getelementptr inbounds i8*, i8** %645, i64 %648
  %650 = load i8*, i8** %649, align 8
  store i8* %650, i8** @output_file, align 8
  %651 = load i8*, i8** @output_file, align 8
  call void @check_parms_length(i8* noundef %651)
  br label %992

652:                                              ; preds = %636
  %653 = load i8**, i8*** %4, align 8
  %654 = load i32, i32* %7, align 4
  %655 = sext i32 %654 to i64
  %656 = getelementptr inbounds i8*, i8** %653, i64 %655
  %657 = load i8*, i8** %656, align 8
  %658 = call i32 @strcmp(i8* noundef %657, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.58, i64 0, i64 0)) #11
  %659 = icmp ne i32 %658, 0
  br i1 %659, label %669, label %660

660:                                              ; preds = %652
  %661 = load i8**, i8*** %4, align 8
  %662 = load i32, i32* %7, align 4
  %663 = add nsw i32 %662, 1
  store i32 %663, i32* %7, align 4
  %664 = sext i32 %662 to i64
  %665 = getelementptr inbounds i8*, i8** %661, i64 %664
  %666 = load i8*, i8** %665, align 8
  store i8* %666, i8** %19, align 8
  %667 = load i8*, i8** %19, align 8
  call void @check_parms_length(i8* noundef %667)
  %668 = load i8*, i8** %19, align 8
  call void @strarray_push(%struct.StringArray* noundef %6, i8* noundef %668)
  br label %992

669:                                              ; preds = %652
  %670 = load i8**, i8*** %4, align 8
  %671 = load i32, i32* %7, align 4
  %672 = sext i32 %671 to i64
  %673 = getelementptr inbounds i8*, i8** %670, i64 %672
  %674 = load i8*, i8** %673, align 8
  %675 = call i32 @strcmp(i8* noundef %674, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.59, i64 0, i64 0)) #11
  %676 = icmp ne i32 %675, 0
  br i1 %676, label %678, label %677

677:                                              ; preds = %669
  store i8 1, i8* @opt_static, align 1
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.59, i64 0, i64 0))
  br label %992

678:                                              ; preds = %669
  %679 = load i8**, i8*** %4, align 8
  %680 = load i32, i32* %7, align 4
  %681 = sext i32 %680 to i64
  %682 = getelementptr inbounds i8*, i8** %679, i64 %681
  %683 = load i8*, i8** %682, align 8
  %684 = call i32 @strcmp(i8* noundef %683, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.60, i64 0, i64 0)) #11
  %685 = icmp ne i32 %684, 0
  br i1 %685, label %687, label %686

686:                                              ; preds = %678
  store i8 1, i8* @opt_shared, align 1
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.60, i64 0, i64 0))
  br label %992

687:                                              ; preds = %678
  %688 = load i8**, i8*** %4, align 8
  %689 = load i32, i32* %7, align 4
  %690 = sext i32 %689 to i64
  %691 = getelementptr inbounds i8*, i8** %688, i64 %690
  %692 = load i8*, i8** %691, align 8
  %693 = call i32 @strcmp(i8* noundef %692, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.61, i64 0, i64 0)) #11
  %694 = icmp ne i32 %693, 0
  br i1 %694, label %696, label %695

695:                                              ; preds = %687
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.62, i64 0, i64 0))
  br label %992

696:                                              ; preds = %687
  %697 = load i8**, i8*** %4, align 8
  %698 = load i32, i32* %7, align 4
  %699 = sext i32 %698 to i64
  %700 = getelementptr inbounds i8*, i8** %697, i64 %699
  %701 = load i8*, i8** %700, align 8
  %702 = call i32 @strcmp(i8* noundef %701, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.63, i64 0, i64 0)) #11
  %703 = icmp ne i32 %702, 0
  br i1 %703, label %713, label %704

704:                                              ; preds = %696
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.63, i64 0, i64 0))
  %705 = load i8**, i8*** %4, align 8
  %706 = load i32, i32* %7, align 4
  %707 = add nsw i32 %706, 1
  store i32 %707, i32* %7, align 4
  %708 = sext i32 %707 to i64
  %709 = getelementptr inbounds i8*, i8** %705, i64 %708
  %710 = load i8*, i8** %709, align 8
  store i8* %710, i8** %20, align 8
  %711 = load i8*, i8** %20, align 8
  call void @check_parms_length(i8* noundef %711)
  %712 = load i8*, i8** %20, align 8
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef %712)
  br label %992

713:                                              ; preds = %696
  %714 = load i8**, i8*** %4, align 8
  %715 = load i32, i32* %7, align 4
  %716 = sext i32 %715 to i64
  %717 = getelementptr inbounds i8*, i8** %714, i64 %716
  %718 = load i8*, i8** %717, align 8
  %719 = call i32 @strncmp(i8* noundef %718, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.63, i64 0, i64 0), i64 noundef 2) #11
  %720 = icmp ne i32 %719, 0
  br i1 %720, label %730, label %721

721:                                              ; preds = %713
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.63, i64 0, i64 0))
  %722 = load i8**, i8*** %4, align 8
  %723 = load i32, i32* %7, align 4
  %724 = sext i32 %723 to i64
  %725 = getelementptr inbounds i8*, i8** %722, i64 %724
  %726 = load i8*, i8** %725, align 8
  %727 = getelementptr inbounds i8, i8* %726, i64 2
  store i8* %727, i8** %21, align 8
  %728 = load i8*, i8** %21, align 8
  call void @check_parms_length(i8* noundef %728)
  %729 = load i8*, i8** %21, align 8
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef %729)
  br label %992

730:                                              ; preds = %713
  %731 = load i8**, i8*** %4, align 8
  %732 = load i32, i32* %7, align 4
  %733 = sext i32 %732 to i64
  %734 = getelementptr inbounds i8*, i8** %731, i64 %733
  %735 = load i8*, i8** %734, align 8
  %736 = call i32 @strcmp(i8* noundef %735, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.64, i64 0, i64 0)) #11
  %737 = icmp ne i32 %736, 0
  br i1 %737, label %739, label %738

738:                                              ; preds = %730
  call void @hashmap_test()
  call void @exit(i32 noundef 0) #13
  unreachable

739:                                              ; preds = %730
  %740 = load i8**, i8*** %4, align 8
  %741 = load i32, i32* %7, align 4
  %742 = sext i32 %741 to i64
  %743 = getelementptr inbounds i8*, i8** %740, i64 %742
  %744 = load i8*, i8** %743, align 8
  %745 = call i32 @strcmp(i8* noundef %744, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #11
  %746 = icmp ne i32 %745, 0
  br i1 %746, label %748, label %747

747:                                              ; preds = %739
  call void @dump_machine()
  call void @exit(i32 noundef 0) #13
  unreachable

748:                                              ; preds = %739
  %749 = load i8**, i8*** %4, align 8
  %750 = load i32, i32* %7, align 4
  %751 = sext i32 %750 to i64
  %752 = getelementptr inbounds i8*, i8** %749, i64 %751
  %753 = load i8*, i8** %752, align 8
  %754 = call i32 @strcmp(i8* noundef %753, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.66, i64 0, i64 0)) #11
  %755 = icmp ne i32 %754, 0
  br i1 %755, label %765, label %756

756:                                              ; preds = %748
  %757 = load i8**, i8*** %4, align 8
  %758 = load i32, i32* %7, align 4
  %759 = add nsw i32 %758, 1
  store i32 %759, i32* %7, align 4
  %760 = sext i32 %759 to i64
  %761 = getelementptr inbounds i8*, i8** %757, i64 %760
  %762 = load i8*, i8** %761, align 8
  store i8* %762, i8** %22, align 8
  %763 = load i8*, i8** %22, align 8
  call void @check_parms_length(i8* noundef %763)
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.66, i64 0, i64 0))
  %764 = load i8*, i8** %22, align 8
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef %764)
  br label %992

765:                                              ; preds = %748
  %766 = load i8**, i8*** %4, align 8
  %767 = load i32, i32* %7, align 4
  %768 = sext i32 %767 to i64
  %769 = getelementptr inbounds i8*, i8** %766, i64 %768
  %770 = load i8*, i8** %769, align 8
  %771 = call i32 @strcmp(i8* noundef %770, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.67, i64 0, i64 0)) #11
  %772 = icmp ne i32 %771, 0
  br i1 %772, label %783, label %773

773:                                              ; preds = %765
  %774 = load i8**, i8*** %4, align 8
  %775 = load i32, i32* %7, align 4
  %776 = add nsw i32 %775, 1
  store i32 %776, i32* %7, align 4
  %777 = sext i32 %776 to i64
  %778 = getelementptr inbounds i8*, i8** %774, i64 %777
  %779 = load i8*, i8** %778, align 8
  store i8* %779, i8** %23, align 8
  %780 = load i8*, i8** %23, align 8
  call void @check_parms_length(i8* noundef %780)
  %781 = load i8*, i8** %23, align 8
  store i8* %781, i8** @r_path, align 8
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.67, i64 0, i64 0))
  %782 = load i8*, i8** @r_path, align 8
  call void @strarray_push(%struct.StringArray* noundef @ld_extra_args, i8* noundef %782)
  br label %992

783:                                              ; preds = %765
  %784 = load i8**, i8*** %4, align 8
  %785 = load i32, i32* %7, align 4
  %786 = sext i32 %785 to i64
  %787 = getelementptr inbounds i8*, i8** %784, i64 %786
  %788 = load i8*, i8** %787, align 8
  %789 = call i32 @strncmp(i8* noundef %788, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0), i64 noundef 2) #11
  %790 = icmp ne i32 %789, 0
  br i1 %790, label %791, label %959

791:                                              ; preds = %783
  %792 = load i8**, i8*** %4, align 8
  %793 = load i32, i32* %7, align 4
  %794 = sext i32 %793 to i64
  %795 = getelementptr inbounds i8*, i8** %792, i64 %794
  %796 = load i8*, i8** %795, align 8
  %797 = call i32 @strncmp(i8* noundef %796, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.69, i64 0, i64 0), i64 noundef 2) #11
  %798 = icmp ne i32 %797, 0
  br i1 %798, label %799, label %959

799:                                              ; preds = %791
  %800 = load i8**, i8*** %4, align 8
  %801 = load i32, i32* %7, align 4
  %802 = sext i32 %801 to i64
  %803 = getelementptr inbounds i8*, i8** %800, i64 %802
  %804 = load i8*, i8** %803, align 8
  %805 = call i32 @strncmp(i8* noundef %804, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.70, i64 0, i64 0), i64 noundef 2) #11
  %806 = icmp ne i32 %805, 0
  br i1 %806, label %807, label %959

807:                                              ; preds = %799
  %808 = load i8**, i8*** %4, align 8
  %809 = load i32, i32* %7, align 4
  %810 = sext i32 %809 to i64
  %811 = getelementptr inbounds i8*, i8** %808, i64 %810
  %812 = load i8*, i8** %811, align 8
  %813 = call i32 @strncmp(i8* noundef %812, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.71, i64 0, i64 0), i64 noundef 5) #11
  %814 = icmp ne i32 %813, 0
  br i1 %814, label %815, label %959

815:                                              ; preds = %807
  %816 = load i8**, i8*** %4, align 8
  %817 = load i32, i32* %7, align 4
  %818 = sext i32 %817 to i64
  %819 = getelementptr inbounds i8*, i8** %816, i64 %818
  %820 = load i8*, i8** %819, align 8
  %821 = call i32 @strncmp(i8* noundef %820, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.72, i64 0, i64 0), i64 noundef 4) #11
  %822 = icmp ne i32 %821, 0
  br i1 %822, label %823, label %959

823:                                              ; preds = %815
  %824 = load i8**, i8*** %4, align 8
  %825 = load i32, i32* %7, align 4
  %826 = sext i32 %825 to i64
  %827 = getelementptr inbounds i8*, i8** %824, i64 %826
  %828 = load i8*, i8** %827, align 8
  %829 = call i32 @strcmp(i8* noundef %828, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.73, i64 0, i64 0)) #11
  %830 = icmp ne i32 %829, 0
  br i1 %830, label %831, label %959

831:                                              ; preds = %823
  %832 = load i8**, i8*** %4, align 8
  %833 = load i32, i32* %7, align 4
  %834 = sext i32 %833 to i64
  %835 = getelementptr inbounds i8*, i8** %832, i64 %834
  %836 = load i8*, i8** %835, align 8
  %837 = call i32 @strcmp(i8* noundef %836, i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.74, i64 0, i64 0)) #11
  %838 = icmp ne i32 %837, 0
  br i1 %838, label %839, label %959

839:                                              ; preds = %831
  %840 = load i8**, i8*** %4, align 8
  %841 = load i32, i32* %7, align 4
  %842 = sext i32 %841 to i64
  %843 = getelementptr inbounds i8*, i8** %840, i64 %842
  %844 = load i8*, i8** %843, align 8
  %845 = call i32 @strcmp(i8* noundef %844, i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.75, i64 0, i64 0)) #11
  %846 = icmp ne i32 %845, 0
  br i1 %846, label %847, label %959

847:                                              ; preds = %839
  %848 = load i8**, i8*** %4, align 8
  %849 = load i32, i32* %7, align 4
  %850 = sext i32 %849 to i64
  %851 = getelementptr inbounds i8*, i8** %848, i64 %850
  %852 = load i8*, i8** %851, align 8
  %853 = call i32 @strcmp(i8* noundef %852, i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.76, i64 0, i64 0)) #11
  %854 = icmp ne i32 %853, 0
  br i1 %854, label %855, label %959

855:                                              ; preds = %847
  %856 = load i8**, i8*** %4, align 8
  %857 = load i32, i32* %7, align 4
  %858 = sext i32 %857 to i64
  %859 = getelementptr inbounds i8*, i8** %856, i64 %858
  %860 = load i8*, i8** %859, align 8
  %861 = call i32 @strcmp(i8* noundef %860, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.77, i64 0, i64 0)) #11
  %862 = icmp ne i32 %861, 0
  br i1 %862, label %863, label %959

863:                                              ; preds = %855
  %864 = load i8**, i8*** %4, align 8
  %865 = load i32, i32* %7, align 4
  %866 = sext i32 %865 to i64
  %867 = getelementptr inbounds i8*, i8** %864, i64 %866
  %868 = load i8*, i8** %867, align 8
  %869 = call i32 @strcmp(i8* noundef %868, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.78, i64 0, i64 0)) #11
  %870 = icmp ne i32 %869, 0
  br i1 %870, label %871, label %959

871:                                              ; preds = %863
  %872 = load i8**, i8*** %4, align 8
  %873 = load i32, i32* %7, align 4
  %874 = sext i32 %873 to i64
  %875 = getelementptr inbounds i8*, i8** %872, i64 %874
  %876 = load i8*, i8** %875, align 8
  %877 = call i32 @strcmp(i8* noundef %876, i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.79, i64 0, i64 0)) #11
  %878 = icmp ne i32 %877, 0
  br i1 %878, label %879, label %959

879:                                              ; preds = %871
  %880 = load i8**, i8*** %4, align 8
  %881 = load i32, i32* %7, align 4
  %882 = sext i32 %881 to i64
  %883 = getelementptr inbounds i8*, i8** %880, i64 %882
  %884 = load i8*, i8** %883, align 8
  %885 = call i32 @strcmp(i8* noundef %884, i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.80, i64 0, i64 0)) #11
  %886 = icmp ne i32 %885, 0
  br i1 %886, label %887, label %959

887:                                              ; preds = %879
  %888 = load i8**, i8*** %4, align 8
  %889 = load i32, i32* %7, align 4
  %890 = sext i32 %889 to i64
  %891 = getelementptr inbounds i8*, i8** %888, i64 %890
  %892 = load i8*, i8** %891, align 8
  %893 = call i32 @strcmp(i8* noundef %892, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.81, i64 0, i64 0)) #11
  %894 = icmp ne i32 %893, 0
  br i1 %894, label %895, label %959

895:                                              ; preds = %887
  %896 = load i8**, i8*** %4, align 8
  %897 = load i32, i32* %7, align 4
  %898 = sext i32 %897 to i64
  %899 = getelementptr inbounds i8*, i8** %896, i64 %898
  %900 = load i8*, i8** %899, align 8
  %901 = call i32 @strcmp(i8* noundef %900, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.82, i64 0, i64 0)) #11
  %902 = icmp ne i32 %901, 0
  br i1 %902, label %903, label %959

903:                                              ; preds = %895
  %904 = load i8**, i8*** %4, align 8
  %905 = load i32, i32* %7, align 4
  %906 = sext i32 %905 to i64
  %907 = getelementptr inbounds i8*, i8** %904, i64 %906
  %908 = load i8*, i8** %907, align 8
  %909 = call i32 @strcmp(i8* noundef %908, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.83, i64 0, i64 0)) #11
  %910 = icmp ne i32 %909, 0
  br i1 %910, label %911, label %959

911:                                              ; preds = %903
  %912 = load i8**, i8*** %4, align 8
  %913 = load i32, i32* %7, align 4
  %914 = sext i32 %913 to i64
  %915 = getelementptr inbounds i8*, i8** %912, i64 %914
  %916 = load i8*, i8** %915, align 8
  %917 = call i32 @strcmp(i8* noundef %916, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.84, i64 0, i64 0)) #11
  %918 = icmp ne i32 %917, 0
  br i1 %918, label %919, label %959

919:                                              ; preds = %911
  %920 = load i8**, i8*** %4, align 8
  %921 = load i32, i32* %7, align 4
  %922 = sext i32 %921 to i64
  %923 = getelementptr inbounds i8*, i8** %920, i64 %922
  %924 = load i8*, i8** %923, align 8
  %925 = call i32 @strcmp(i8* noundef %924, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.85, i64 0, i64 0)) #11
  %926 = icmp ne i32 %925, 0
  br i1 %926, label %927, label %959

927:                                              ; preds = %919
  %928 = load i8**, i8*** %4, align 8
  %929 = load i32, i32* %7, align 4
  %930 = sext i32 %929 to i64
  %931 = getelementptr inbounds i8*, i8** %928, i64 %930
  %932 = load i8*, i8** %931, align 8
  %933 = call i32 @strcmp(i8* noundef %932, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.86, i64 0, i64 0)) #11
  %934 = icmp ne i32 %933, 0
  br i1 %934, label %935, label %959

935:                                              ; preds = %927
  %936 = load i8**, i8*** %4, align 8
  %937 = load i32, i32* %7, align 4
  %938 = sext i32 %937 to i64
  %939 = getelementptr inbounds i8*, i8** %936, i64 %938
  %940 = load i8*, i8** %939, align 8
  %941 = call i32 @strcmp(i8* noundef %940, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.87, i64 0, i64 0)) #11
  %942 = icmp ne i32 %941, 0
  br i1 %942, label %943, label %959

943:                                              ; preds = %935
  %944 = load i8**, i8*** %4, align 8
  %945 = load i32, i32* %7, align 4
  %946 = sext i32 %945 to i64
  %947 = getelementptr inbounds i8*, i8** %944, i64 %946
  %948 = load i8*, i8** %947, align 8
  %949 = call i32 @strcmp(i8* noundef %948, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.88, i64 0, i64 0)) #11
  %950 = icmp ne i32 %949, 0
  br i1 %950, label %951, label %959

951:                                              ; preds = %943
  %952 = load i8**, i8*** %4, align 8
  %953 = load i32, i32* %7, align 4
  %954 = sext i32 %953 to i64
  %955 = getelementptr inbounds i8*, i8** %952, i64 %954
  %956 = load i8*, i8** %955, align 8
  %957 = call i32 @strcmp(i8* noundef %956, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.89, i64 0, i64 0)) #11
  %958 = icmp ne i32 %957, 0
  br i1 %958, label %960, label %959

959:                                              ; preds = %951, %943, %935, %927, %919, %911, %903, %895, %887, %879, %871, %863, %855, %847, %839, %831, %823, %815, %807, %799, %791, %783
  br label %992

960:                                              ; preds = %951
  %961 = load i8**, i8*** %4, align 8
  %962 = load i32, i32* %7, align 4
  %963 = sext i32 %962 to i64
  %964 = getelementptr inbounds i8*, i8** %961, i64 %963
  %965 = load i8*, i8** %964, align 8
  %966 = getelementptr inbounds i8, i8* %965, i64 0
  %967 = load i8, i8* %966, align 1
  %968 = sext i8 %967 to i32
  %969 = icmp eq i32 %968, 45
  br i1 %969, label %970, label %986

970:                                              ; preds = %960
  %971 = load i8**, i8*** %4, align 8
  %972 = load i32, i32* %7, align 4
  %973 = sext i32 %972 to i64
  %974 = getelementptr inbounds i8*, i8** %971, i64 %973
  %975 = load i8*, i8** %974, align 8
  %976 = getelementptr inbounds i8, i8* %975, i64 1
  %977 = load i8, i8* %976, align 1
  %978 = sext i8 %977 to i32
  %979 = icmp ne i32 %978, 0
  br i1 %979, label %980, label %986

980:                                              ; preds = %970
  %981 = load i8**, i8*** %4, align 8
  %982 = load i32, i32* %7, align 4
  %983 = sext i32 %982 to i64
  %984 = getelementptr inbounds i8*, i8** %981, i64 %983
  %985 = load i8*, i8** %984, align 8
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([38 x i8], [38 x i8]* @.str.90, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8* noundef %985) #12
  unreachable

986:                                              ; preds = %970, %960
  %987 = load i8**, i8*** %4, align 8
  %988 = load i32, i32* %7, align 4
  %989 = sext i32 %988 to i64
  %990 = getelementptr inbounds i8*, i8** %987, i64 %989
  %991 = load i8*, i8** %990, align 8
  call void @strarray_push(%struct.StringArray* noundef @input_paths, i8* noundef %991)
  br label %992

992:                                              ; preds = %986, %959, %773, %756, %721, %704, %695, %686, %677, %660, %644, %628, %619, %610, %593, %583, %553, %543, %515, %499, %490, %481, %464, %447, %422, %406, %405, %371, %353, %336, %319, %302, %285, %268, %259, %228, %219, %210, %201, %192, %183, %174, %165, %150, %134, %118, %109, %92, %75, %66
  %993 = load i32, i32* %7, align 4
  %994 = add nsw i32 %993, 1
  store i32 %994, i32* %7, align 4
  br label %54, !llvm.loop !11

995:                                              ; preds = %54
  store i32 0, i32* %24, align 4
  br label %996

996:                                              ; preds = %1008, %995
  %997 = load i32, i32* %24, align 4
  %998 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %6, i32 0, i32 2
  %999 = load i32, i32* %998, align 4
  %1000 = icmp slt i32 %997, %999
  br i1 %1000, label %1001, label %1011

1001:                                             ; preds = %996
  %1002 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %6, i32 0, i32 0
  %1003 = load i8**, i8*** %1002, align 8
  %1004 = load i32, i32* %24, align 4
  %1005 = sext i32 %1004 to i64
  %1006 = getelementptr inbounds i8*, i8** %1003, i64 %1005
  %1007 = load i8*, i8** %1006, align 8
  call void @strarray_push(%struct.StringArray* noundef @include_paths, i8* noundef %1007)
  br label %1008

1008:                                             ; preds = %1001
  %1009 = load i32, i32* %24, align 4
  %1010 = add nsw i32 %1009, 1
  store i32 %1010, i32* %24, align 4
  br label %996, !llvm.loop !12

1011:                                             ; preds = %996
  %1012 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @input_paths, i32 0, i32 2), align 4
  %1013 = icmp eq i32 %1012, 0
  br i1 %1013, label %1014, label %1015

1014:                                             ; preds = %1011
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([34 x i8], [34 x i8]* @.str.91, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

1015:                                             ; preds = %1011
  %1016 = load i8, i8* @opt_E, align 1
  %1017 = trunc i8 %1016 to i1
  br i1 %1017, label %1018, label %1019

1018:                                             ; preds = %1015
  store i32 1, i32* @opt_x, align 4
  br label %1019

1019:                                             ; preds = %1018, %1015
  ret void
}

declare noalias %struct._IO_FILE* @fopen(i8* noundef, i8* noundef) #2

; Function Attrs: noreturn
declare void @error(i8* noundef, ...) #6

declare void @init_macros() #2

; Function Attrs: noinline nounwind optnone uwtable
define internal void @add_default_include_paths(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  %5 = call noalias i8* @strdup(i8* noundef %4) #10
  %6 = call i8* @dirname(i8* noundef %5) #10
  %7 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.104, i64 0, i64 0), i8* noundef %6)
  call void @strarray_push(%struct.StringArray* noundef @include_paths, i8* noundef %7)
  call void @strarray_push(%struct.StringArray* noundef @include_paths, i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.105, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef @include_paths, i8* noundef getelementptr inbounds ([30 x i8], [30 x i8]* @.str.106, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef @include_paths, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.107, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef @include_paths, i8* noundef getelementptr inbounds ([29 x i8], [29 x i8]* @.str.108, i64 0, i64 0))
  store i32 0, i32* %3, align 4
  br label %8

8:                                                ; preds = %18, %1
  %9 = load i32, i32* %3, align 4
  %10 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @include_paths, i32 0, i32 2), align 4
  %11 = icmp slt i32 %9, %10
  br i1 %11, label %12, label %21

12:                                               ; preds = %8
  %13 = load i8**, i8*** getelementptr inbounds (%struct.StringArray, %struct.StringArray* @include_paths, i32 0, i32 0), align 8
  %14 = load i32, i32* %3, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds i8*, i8** %13, i64 %15
  %17 = load i8*, i8** %16, align 8
  call void @strarray_push(%struct.StringArray* noundef @std_include_paths, i8* noundef %17)
  br label %18

18:                                               ; preds = %12
  %19 = load i32, i32* %3, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, i32* %3, align 4
  br label %8, !llvm.loop !13

21:                                               ; preds = %8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @cc1() #0 {
  %1 = alloca %struct.Token*, align 8
  %2 = alloca i32, align 4
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca i8, align 1
  %8 = alloca %struct.Obj*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i64, align 8
  %11 = alloca %struct._IO_FILE*, align 8
  %12 = alloca %struct._IO_FILE*, align 8
  store %struct.Token* null, %struct.Token** %1, align 8
  store i32 0, i32* %2, align 4
  br label %13

13:                                               ; preds = %44, %0
  %14 = load i32, i32* %2, align 4
  %15 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @opt_include, i32 0, i32 2), align 4
  %16 = icmp slt i32 %14, %15
  br i1 %16, label %17, label %47

17:                                               ; preds = %13
  %18 = load i8**, i8*** getelementptr inbounds (%struct.StringArray, %struct.StringArray* @opt_include, i32 0, i32 0), align 8
  %19 = load i32, i32* %2, align 4
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds i8*, i8** %18, i64 %20
  %22 = load i8*, i8** %21, align 8
  store i8* %22, i8** %3, align 8
  %23 = load i8*, i8** %3, align 8
  %24 = call zeroext i1 @file_exists(i8* noundef %23)
  br i1 %24, label %25, label %27

25:                                               ; preds = %17
  %26 = load i8*, i8** %3, align 8
  store i8* %26, i8** %4, align 8
  br label %38

27:                                               ; preds = %17
  %28 = load i8*, i8** %3, align 8
  %29 = call i8* @search_include_paths(i8* noundef %28)
  store i8* %29, i8** %4, align 8
  %30 = load i8*, i8** %4, align 8
  %31 = icmp ne i8* %30, null
  br i1 %31, label %37, label %32

32:                                               ; preds = %27
  %33 = load i8*, i8** %3, align 8
  %34 = call i32* @__errno_location() #14
  %35 = load i32, i32* %34, align 4
  %36 = call i8* @strerror(i32 noundef %35) #10
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([29 x i8], [29 x i8]* @.str.109, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8* noundef %33, i8* noundef %36) #12
  unreachable

37:                                               ; preds = %27
  br label %38

38:                                               ; preds = %37, %25
  %39 = load i8*, i8** %4, align 8
  %40 = call %struct.Token* @must_tokenize_file(i8* noundef %39)
  store %struct.Token* %40, %struct.Token** %5, align 8
  %41 = load %struct.Token*, %struct.Token** %1, align 8
  %42 = load %struct.Token*, %struct.Token** %5, align 8
  %43 = call %struct.Token* @append_tokens(%struct.Token* noundef %41, %struct.Token* noundef %42)
  store %struct.Token* %43, %struct.Token** %1, align 8
  br label %44

44:                                               ; preds = %38
  %45 = load i32, i32* %2, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, i32* %2, align 4
  br label %13, !llvm.loop !14

47:                                               ; preds = %13
  %48 = load i8*, i8** @base_file, align 8
  %49 = call %struct.Token* @must_tokenize_file(i8* noundef %48)
  store %struct.Token* %49, %struct.Token** %6, align 8
  store i8 0, i8* %7, align 1
  %50 = load %struct.Token*, %struct.Token** %1, align 8
  %51 = load %struct.Token*, %struct.Token** %6, align 8
  %52 = call %struct.Token* @append_tokens(%struct.Token* noundef %50, %struct.Token* noundef %51)
  store %struct.Token* %52, %struct.Token** %1, align 8
  %53 = load %struct.Token*, %struct.Token** %1, align 8
  %54 = load i8, i8* %7, align 1
  %55 = trunc i8 %54 to i1
  %56 = call %struct.Token* @preprocess(%struct.Token* noundef %53, i1 noundef zeroext %55)
  store %struct.Token* %56, %struct.Token** %1, align 8
  %57 = load i8, i8* @opt_M, align 1
  %58 = trunc i8 %57 to i1
  br i1 %58, label %62, label %59

59:                                               ; preds = %47
  %60 = load i8, i8* @opt_MD, align 1
  %61 = trunc i8 %60 to i1
  br i1 %61, label %62, label %67

62:                                               ; preds = %59, %47
  call void @print_dependencies()
  %63 = load i8, i8* @opt_M, align 1
  %64 = trunc i8 %63 to i1
  br i1 %64, label %65, label %66

65:                                               ; preds = %62
  br label %88

66:                                               ; preds = %62
  br label %67

67:                                               ; preds = %66, %59
  %68 = load i8, i8* @opt_E, align 1
  %69 = trunc i8 %68 to i1
  br i1 %69, label %70, label %72

70:                                               ; preds = %67
  %71 = load %struct.Token*, %struct.Token** %1, align 8
  call void @print_tokens(%struct.Token* noundef %71)
  br label %88

72:                                               ; preds = %67
  %73 = load %struct.Token*, %struct.Token** %1, align 8
  %74 = call %struct.Obj* @parse(%struct.Token* noundef %73)
  store %struct.Obj* %74, %struct.Obj** %8, align 8
  %75 = call noalias %struct._IO_FILE* @open_memstream(i8** noundef %9, i64* noundef %10) #10
  store %struct._IO_FILE* %75, %struct._IO_FILE** %11, align 8
  %76 = load %struct.Obj*, %struct.Obj** %8, align 8
  %77 = load %struct._IO_FILE*, %struct._IO_FILE** %11, align 8
  call void @codegen(%struct.Obj* noundef %76, %struct._IO_FILE* noundef %77)
  %78 = load %struct._IO_FILE*, %struct._IO_FILE** %11, align 8
  %79 = call i32 @fclose(%struct._IO_FILE* noundef %78)
  %80 = load i8*, i8** @output_file, align 8
  %81 = call %struct._IO_FILE* @open_file(i8* noundef %80)
  store %struct._IO_FILE* %81, %struct._IO_FILE** %12, align 8
  %82 = load i8*, i8** %9, align 8
  %83 = load i64, i64* %10, align 8
  %84 = load %struct._IO_FILE*, %struct._IO_FILE** %12, align 8
  %85 = call i64 @fwrite(i8* noundef %82, i64 noundef %83, i64 noundef 1, %struct._IO_FILE* noundef %84)
  %86 = load %struct._IO_FILE*, %struct._IO_FILE** %12, align 8
  %87 = call i32 @fclose(%struct._IO_FILE* noundef %86)
  br label %88

88:                                               ; preds = %72, %70, %65
  ret void
}

; Function Attrs: nounwind readonly willreturn
declare i32 @strncmp(i8* noundef, i8* noundef, i64 noundef) #3

declare void @strarray_push(%struct.StringArray* noundef, i8* noundef) #2

; Function Attrs: nounwind
declare i8* @strtok(i8* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @get_file_type(i8* noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  %4 = load i32, i32* @opt_x, align 4
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %6, label %8

6:                                                ; preds = %1
  %7 = load i32, i32* @opt_x, align 4
  store i32 %7, i32* %2, align 4
  br label %42

8:                                                ; preds = %1
  %9 = load i8*, i8** %3, align 8
  %10 = call zeroext i1 @endswith(i8* noundef %9, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.120, i64 0, i64 0))
  br i1 %10, label %11, label %12

11:                                               ; preds = %8
  store i32 4, i32* %2, align 4
  br label %42

12:                                               ; preds = %8
  %13 = load i8*, i8** %3, align 8
  %14 = call zeroext i1 @endswith(i8* noundef %13, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.121, i64 0, i64 0))
  br i1 %14, label %19, label %15

15:                                               ; preds = %12
  %16 = load i8*, i8** %3, align 8
  %17 = call i8* @strstr(i8* noundef %16, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.122, i64 0, i64 0)) #11
  %18 = icmp ne i8* %17, null
  br i1 %18, label %19, label %20

19:                                               ; preds = %15, %12
  store i32 5, i32* %2, align 4
  br label %42

20:                                               ; preds = %15
  %21 = load i8*, i8** %3, align 8
  %22 = call zeroext i1 @endswith(i8* noundef %21, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.123, i64 0, i64 0))
  br i1 %22, label %23, label %24

23:                                               ; preds = %20
  store i32 5, i32* %2, align 4
  br label %42

24:                                               ; preds = %20
  %25 = load i8*, i8** %3, align 8
  %26 = call zeroext i1 @endswith(i8* noundef %25, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.13, i64 0, i64 0))
  br i1 %26, label %27, label %28

27:                                               ; preds = %24
  store i32 3, i32* %2, align 4
  br label %42

28:                                               ; preds = %24
  %29 = load i8*, i8** %3, align 8
  %30 = call zeroext i1 @endswith(i8* noundef %29, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.124, i64 0, i64 0))
  br i1 %30, label %31, label %32

31:                                               ; preds = %28
  store i32 1, i32* %2, align 4
  br label %42

32:                                               ; preds = %28
  %33 = load i8*, i8** %3, align 8
  %34 = call zeroext i1 @endswith(i8* noundef %33, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.12, i64 0, i64 0))
  br i1 %34, label %35, label %36

35:                                               ; preds = %32
  store i32 2, i32* %2, align 4
  br label %42

36:                                               ; preds = %32
  %37 = load i8*, i8** %3, align 8
  %38 = call zeroext i1 @endswith(i8* noundef %37, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.125, i64 0, i64 0))
  br i1 %38, label %39, label %40

39:                                               ; preds = %36
  store i32 5, i32* %2, align 4
  br label %42

40:                                               ; preds = %36
  %41 = load i8*, i8** %3, align 8
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([65 x i8], [65 x i8]* @.str.126, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8* noundef %41) #12
  unreachable

42:                                               ; preds = %39, %35, %31, %27, %23, %19, %11, %6
  %43 = load i32, i32* %2, align 4
  ret i32 %43
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @assemble(i8* noundef %0, i8* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca [6 x i8*], align 16
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %6 = getelementptr inbounds [6 x i8*], [6 x i8*]* %5, i64 0, i64 0
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.127, i64 0, i64 0), i8** %6, align 8
  %7 = getelementptr inbounds i8*, i8** %6, i64 1
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.33, i64 0, i64 0), i8** %7, align 8
  %8 = getelementptr inbounds i8*, i8** %7, i64 1
  %9 = load i8*, i8** %3, align 8
  store i8* %9, i8** %8, align 8
  %10 = getelementptr inbounds i8*, i8** %8, i64 1
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.26, i64 0, i64 0), i8** %10, align 8
  %11 = getelementptr inbounds i8*, i8** %10, i64 1
  %12 = load i8*, i8** %4, align 8
  store i8* %12, i8** %11, align 8
  %13 = getelementptr inbounds i8*, i8** %11, i64 1
  store i8* null, i8** %13, align 8
  %14 = getelementptr inbounds [6 x i8*], [6 x i8*]* %5, i64 0, i64 0
  call void @run_subprocess(i8** noundef %14)
  ret void
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8* noundef, i8* noundef, i32 noundef, i8* noundef) #7

; Function Attrs: noinline nounwind optnone uwtable
define internal void @run_cc1(i32 noundef %0, i8** noundef %1, i8* noundef %2, i8* noundef %3) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i8**, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i8**, align 8
  store i32 %0, i32* %5, align 4
  store i8** %1, i8*** %6, align 8
  store i8* %2, i8** %7, align 8
  store i8* %3, i8** %8, align 8
  %10 = load i32, i32* %5, align 4
  %11 = add nsw i32 %10, 10
  %12 = sext i32 %11 to i64
  %13 = call noalias i8* @calloc(i64 noundef %12, i64 noundef 8) #10
  %14 = bitcast i8* %13 to i8**
  store i8** %14, i8*** %9, align 8
  %15 = load i8**, i8*** %9, align 8
  %16 = icmp eq i8** %15, null
  br i1 %16, label %17, label %18

17:                                               ; preds = %4
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([29 x i8], [29 x i8]* @.str.130, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

18:                                               ; preds = %4
  %19 = load i8**, i8*** %9, align 8
  %20 = bitcast i8** %19 to i8*
  %21 = load i8**, i8*** %6, align 8
  %22 = bitcast i8** %21 to i8*
  %23 = load i32, i32* %5, align 4
  %24 = sext i32 %23 to i64
  %25 = mul i64 %24, 8
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %20, i8* align 8 %22, i64 %25, i1 false)
  %26 = load i8**, i8*** %9, align 8
  %27 = load i32, i32* %5, align 4
  %28 = add nsw i32 %27, 1
  store i32 %28, i32* %5, align 4
  %29 = sext i32 %27 to i64
  %30 = getelementptr inbounds i8*, i8** %26, i64 %29
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8** %30, align 8
  %31 = load i8*, i8** %7, align 8
  %32 = icmp ne i8* %31, null
  br i1 %32, label %33, label %45

33:                                               ; preds = %18
  %34 = load i8**, i8*** %9, align 8
  %35 = load i32, i32* %5, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %5, align 4
  %37 = sext i32 %35 to i64
  %38 = getelementptr inbounds i8*, i8** %34, i64 %37
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.56, i64 0, i64 0), i8** %38, align 8
  %39 = load i8*, i8** %7, align 8
  %40 = load i8**, i8*** %9, align 8
  %41 = load i32, i32* %5, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, i32* %5, align 4
  %43 = sext i32 %41 to i64
  %44 = getelementptr inbounds i8*, i8** %40, i64 %43
  store i8* %39, i8** %44, align 8
  br label %45

45:                                               ; preds = %33, %18
  %46 = load i8*, i8** %8, align 8
  %47 = icmp ne i8* %46, null
  br i1 %47, label %48, label %60

48:                                               ; preds = %45
  %49 = load i8**, i8*** %9, align 8
  %50 = load i32, i32* %5, align 4
  %51 = add nsw i32 %50, 1
  store i32 %51, i32* %5, align 4
  %52 = sext i32 %50 to i64
  %53 = getelementptr inbounds i8*, i8** %49, i64 %52
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.57, i64 0, i64 0), i8** %53, align 8
  %54 = load i8*, i8** %8, align 8
  %55 = load i8**, i8*** %9, align 8
  %56 = load i32, i32* %5, align 4
  %57 = add nsw i32 %56, 1
  store i32 %57, i32* %5, align 4
  %58 = sext i32 %56 to i64
  %59 = getelementptr inbounds i8*, i8** %55, i64 %58
  store i8* %54, i8** %59, align 8
  br label %60

60:                                               ; preds = %48, %45
  %61 = load i8**, i8*** %9, align 8
  call void @run_subprocess(i8** noundef %61)
  %62 = load i8**, i8*** %9, align 8
  %63 = bitcast i8** %62 to i8*
  call void @free(i8* noundef %63) #10
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @create_tmpfile() #0 {
  %1 = alloca i8*, align 8
  %2 = alloca i32, align 4
  %3 = call noalias i8* @strdup(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.131, i64 0, i64 0)) #10
  store i8* %3, i8** %1, align 8
  %4 = load i8*, i8** %1, align 8
  %5 = icmp eq i8* %4, null
  br i1 %5, label %6, label %7

6:                                                ; preds = %0
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([41 x i8], [41 x i8]* @.str.132, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

7:                                                ; preds = %0
  %8 = load i8*, i8** %1, align 8
  %9 = call i32 @mkstemp(i8* noundef %8)
  store i32 %9, i32* %2, align 4
  %10 = load i32, i32* %2, align 4
  %11 = icmp eq i32 %10, -1
  br i1 %11, label %12, label %16

12:                                               ; preds = %7
  %13 = call i32* @__errno_location() #14
  %14 = load i32, i32* %13, align 4
  %15 = call i8* @strerror(i32 noundef %14) #10
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str.133, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8* noundef %15) #12
  unreachable

16:                                               ; preds = %7
  %17 = load i32, i32* %2, align 4
  %18 = call i32 @close(i32 noundef %17)
  %19 = load i8*, i8** %1, align 8
  call void @strarray_push(%struct.StringArray* noundef @tmpfiles, i8* noundef %19)
  %20 = load i8*, i8** %1, align 8
  ret i8* %20
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @run_linker(%struct.StringArray* noundef %0, i8* noundef %1) #0 {
  %3 = alloca %struct.StringArray*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %struct.StringArray, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store %struct.StringArray* %0, %struct.StringArray** %3, align 8
  store i8* %1, i8** %4, align 8
  %10 = bitcast %struct.StringArray* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %10, i8 0, i64 16, i1 false)
  %11 = load i8*, i8** @opt_linker, align 8
  %12 = icmp ne i8* %11, null
  br i1 %12, label %13, label %15

13:                                               ; preds = %2
  %14 = load i8*, i8** @opt_linker, align 8
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %14)
  br label %16

15:                                               ; preds = %2
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.134, i64 0, i64 0))
  br label %16

16:                                               ; preds = %15, %13
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.26, i64 0, i64 0))
  %17 = load i8*, i8** %4, align 8
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %17)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.135, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.136, i64 0, i64 0))
  %18 = call i8* @find_libpath()
  store i8* %18, i8** %6, align 8
  %19 = call i8* @find_gcc_libpath()
  store i8* %19, i8** %7, align 8
  %20 = load i8, i8* @opt_shared, align 1
  %21 = trunc i8 %20 to i1
  br i1 %21, label %22, label %27

22:                                               ; preds = %16
  %23 = load i8*, i8** %6, align 8
  %24 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.137, i64 0, i64 0), i8* noundef %23)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %24)
  %25 = load i8*, i8** %7, align 8
  %26 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.138, i64 0, i64 0), i8* noundef %25)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %26)
  br label %34

27:                                               ; preds = %16
  %28 = load i8*, i8** %6, align 8
  %29 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.139, i64 0, i64 0), i8* noundef %28)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %29)
  %30 = load i8*, i8** %6, align 8
  %31 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.137, i64 0, i64 0), i8* noundef %30)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %31)
  %32 = load i8*, i8** %7, align 8
  %33 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.140, i64 0, i64 0), i8* noundef %32)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %33)
  br label %34

34:                                               ; preds = %27, %22
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.141, i64 0, i64 0))
  %35 = load i8*, i8** %7, align 8
  %36 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.142, i64 0, i64 0), i8* noundef %35)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %36)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @.str.143, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.144, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.145, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @.str.143, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.146, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.147, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.148, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.149, i64 0, i64 0))
  %37 = load i8, i8* @opt_static, align 1
  %38 = trunc i8 %37 to i1
  br i1 %38, label %40, label %39

39:                                               ; preds = %34
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.150, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @.str.151, i64 0, i64 0))
  br label %40

40:                                               ; preds = %39, %34
  store i32 0, i32* %8, align 4
  br label %41

41:                                               ; preds = %51, %40
  %42 = load i32, i32* %8, align 4
  %43 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @ld_extra_args, i32 0, i32 2), align 4
  %44 = icmp slt i32 %42, %43
  br i1 %44, label %45, label %54

45:                                               ; preds = %41
  %46 = load i8**, i8*** getelementptr inbounds (%struct.StringArray, %struct.StringArray* @ld_extra_args, i32 0, i32 0), align 8
  %47 = load i32, i32* %8, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds i8*, i8** %46, i64 %48
  %50 = load i8*, i8** %49, align 8
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %50)
  br label %51

51:                                               ; preds = %45
  %52 = load i32, i32* %8, align 4
  %53 = add nsw i32 %52, 1
  store i32 %53, i32* %8, align 4
  br label %41, !llvm.loop !15

54:                                               ; preds = %41
  store i32 0, i32* %9, align 4
  br label %55

55:                                               ; preds = %69, %54
  %56 = load i32, i32* %9, align 4
  %57 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %58 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %57, i32 0, i32 2
  %59 = load i32, i32* %58, align 4
  %60 = icmp slt i32 %56, %59
  br i1 %60, label %61, label %72

61:                                               ; preds = %55
  %62 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %63 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %62, i32 0, i32 0
  %64 = load i8**, i8*** %63, align 8
  %65 = load i32, i32* %9, align 4
  %66 = sext i32 %65 to i64
  %67 = getelementptr inbounds i8*, i8** %64, i64 %66
  %68 = load i8*, i8** %67, align 8
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %68)
  br label %69

69:                                               ; preds = %61
  %70 = load i32, i32* %9, align 4
  %71 = add nsw i32 %70, 1
  store i32 %71, i32* %9, align 4
  br label %55, !llvm.loop !16

72:                                               ; preds = %55
  %73 = load i8, i8* @opt_static, align 1
  %74 = trunc i8 %73 to i1
  br i1 %74, label %75, label %76

75:                                               ; preds = %72
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.152, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.153, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.154, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.155, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.156, i64 0, i64 0))
  br label %77

76:                                               ; preds = %72
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.155, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.153, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.157, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.158, i64 0, i64 0))
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.159, i64 0, i64 0))
  br label %77

77:                                               ; preds = %76, %75
  %78 = load i8, i8* @opt_shared, align 1
  %79 = trunc i8 %78 to i1
  br i1 %79, label %80, label %83

80:                                               ; preds = %77
  %81 = load i8*, i8** %7, align 8
  %82 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.160, i64 0, i64 0), i8* noundef %81)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %82)
  br label %86

83:                                               ; preds = %77
  %84 = load i8*, i8** %7, align 8
  %85 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.161, i64 0, i64 0), i8* noundef %84)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %85)
  br label %86

86:                                               ; preds = %83, %80
  %87 = load i8*, i8** %6, align 8
  %88 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.162, i64 0, i64 0), i8* noundef %87)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef %88)
  call void @strarray_push(%struct.StringArray* noundef %5, i8* noundef null)
  %89 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %5, i32 0, i32 0
  %90 = load i8**, i8*** %89, align 8
  call void @run_subprocess(i8** noundef %90)
  ret void
}

; Function Attrs: nounwind
declare void @free(i8* noundef) #1

; Function Attrs: nounwind
declare i32 @unlink(i8* noundef) #1

declare i32 @fclose(%struct._IO_FILE* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @take_arg(i8* noundef %0) #0 {
  %2 = alloca i1, align 1
  %3 = alloca i8*, align 8
  %4 = alloca [15 x i8*], align 16
  %5 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  %6 = bitcast [15 x i8*]* %4 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %6, i8* align 16 bitcast ([15 x i8*]* @__const.take_arg.x to i8*), i64 120, i1 false)
  store i32 0, i32* %5, align 4
  br label %7

7:                                                ; preds = %21, %1
  %8 = load i32, i32* %5, align 4
  %9 = sext i32 %8 to i64
  %10 = icmp ult i64 %9, 15
  br i1 %10, label %11, label %24

11:                                               ; preds = %7
  %12 = load i8*, i8** %3, align 8
  %13 = load i32, i32* %5, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds [15 x i8*], [15 x i8*]* %4, i64 0, i64 %14
  %16 = load i8*, i8** %15, align 8
  %17 = call i32 @strcmp(i8* noundef %12, i8* noundef %16) #11
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %20, label %19

19:                                               ; preds = %11
  store i1 true, i1* %2, align 1
  br label %25

20:                                               ; preds = %11
  br label %21

21:                                               ; preds = %20
  %22 = load i32, i32* %5, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* %5, align 4
  br label %7, !llvm.loop !17

24:                                               ; preds = %7
  store i1 false, i1* %2, align 1
  br label %25

25:                                               ; preds = %24, %19
  %26 = load i1, i1* %2, align 1
  ret i1 %26
}

declare i32 @printf(i8* noundef, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal void @usage(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %4 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %3, i8* noundef getelementptr inbounds ([215 x i8], [215 x i8]* @.str.92, i64 0, i64 0))
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %6 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %5, i8* noundef getelementptr inbounds ([3029 x i8], [3029 x i8]* @.str.93, i64 0, i64 0))
  %7 = load i32, i32* %2, align 4
  call void @exit(i32 noundef %7) #13
  unreachable
}

; Function Attrs: nounwind readonly willreturn
declare i32 @strcmp(i8* noundef, i8* noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal void @printVersion(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.94, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.95, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.96, i64 0, i64 0))
  %4 = load i32, i32* %2, align 4
  call void @exit(i32 noundef %4) #13
  unreachable
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @check_parms_length(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = call i64 @strlen(i8* noundef %3) #11
  %5 = icmp ugt i64 %4, 101
  br i1 %5, label %6, label %7

6:                                                ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([63 x i8], [63 x i8]* @.str.97, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

7:                                                ; preds = %1
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @define(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  %5 = call i8* @strchr(i8* noundef %4, i32 noundef 61) #11
  store i8* %5, i8** %3, align 8
  %6 = load i8*, i8** %3, align 8
  %7 = icmp ne i8* %6, null
  br i1 %7, label %8, label %18

8:                                                ; preds = %1
  %9 = load i8*, i8** %2, align 8
  %10 = load i8*, i8** %3, align 8
  %11 = load i8*, i8** %2, align 8
  %12 = ptrtoint i8* %10 to i64
  %13 = ptrtoint i8* %11 to i64
  %14 = sub i64 %12, %13
  %15 = call noalias i8* @strndup(i8* noundef %9, i64 noundef %14) #10
  %16 = load i8*, i8** %3, align 8
  %17 = getelementptr inbounds i8, i8* %16, i64 1
  call void @define_macro(i8* noundef %15, i8* noundef %17)
  br label %20

18:                                               ; preds = %1
  %19 = load i8*, i8** %2, align 8
  call void @define_macro(i8* noundef %19, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.98, i64 0, i64 0))
  br label %20

20:                                               ; preds = %18, %8
  ret void
}

declare void @undef_macro(i8* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @parse_opt_x(i8* noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  %4 = load i8*, i8** %3, align 8
  %5 = call i32 @strcmp(i8* noundef %4, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.99, i64 0, i64 0)) #11
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %8, label %7

7:                                                ; preds = %1
  store i32 1, i32* %2, align 4
  br label %20

8:                                                ; preds = %1
  %9 = load i8*, i8** %3, align 8
  %10 = call i32 @strcmp(i8* noundef %9, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.100, i64 0, i64 0)) #11
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %13, label %12

12:                                               ; preds = %8
  store i32 2, i32* %2, align 4
  br label %20

13:                                               ; preds = %8
  %14 = load i8*, i8** %3, align 8
  %15 = call i32 @strcmp(i8* noundef %14, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.101, i64 0, i64 0)) #11
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %18, label %17

17:                                               ; preds = %13
  store i32 0, i32* %2, align 4
  br label %20

18:                                               ; preds = %13
  %19 = load i8*, i8** %3, align 8
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([64 x i8], [64 x i8]* @.str.102, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8* noundef %19) #12
  unreachable

20:                                               ; preds = %17, %12, %7
  %21 = load i32, i32* %2, align 4
  ret i32 %21
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @quote_makefile(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  %7 = load i8*, i8** %2, align 8
  %8 = call i64 @strlen(i8* noundef %7) #11
  %9 = mul i64 %8, 2
  %10 = add i64 %9, 1
  %11 = call noalias i8* @calloc(i64 noundef 1, i64 noundef %10) #10
  store i8* %11, i8** %3, align 8
  %12 = load i8*, i8** %3, align 8
  %13 = icmp eq i8* %12, null
  br i1 %13, label %14, label %15

14:                                               ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str.103, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

15:                                               ; preds = %1
  store i32 0, i32* %4, align 4
  store i32 0, i32* %5, align 4
  br label %16

16:                                               ; preds = %105, %15
  %17 = load i8*, i8** %2, align 8
  %18 = load i32, i32* %4, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds i8, i8* %17, i64 %19
  %21 = load i8, i8* %20, align 1
  %22 = icmp ne i8 %21, 0
  br i1 %22, label %23, label %108

23:                                               ; preds = %16
  %24 = load i8*, i8** %2, align 8
  %25 = load i32, i32* %4, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds i8, i8* %24, i64 %26
  %28 = load i8, i8* %27, align 1
  %29 = sext i8 %28 to i32
  switch i32 %29, label %93 [
    i32 36, label %30
    i32 35, label %41
    i32 32, label %52
    i32 9, label %52
  ]

30:                                               ; preds = %23
  %31 = load i8*, i8** %3, align 8
  %32 = load i32, i32* %5, align 4
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %5, align 4
  %34 = sext i32 %32 to i64
  %35 = getelementptr inbounds i8, i8* %31, i64 %34
  store i8 36, i8* %35, align 1
  %36 = load i8*, i8** %3, align 8
  %37 = load i32, i32* %5, align 4
  %38 = add nsw i32 %37, 1
  store i32 %38, i32* %5, align 4
  %39 = sext i32 %37 to i64
  %40 = getelementptr inbounds i8, i8* %36, i64 %39
  store i8 36, i8* %40, align 1
  br label %104

41:                                               ; preds = %23
  %42 = load i8*, i8** %3, align 8
  %43 = load i32, i32* %5, align 4
  %44 = add nsw i32 %43, 1
  store i32 %44, i32* %5, align 4
  %45 = sext i32 %43 to i64
  %46 = getelementptr inbounds i8, i8* %42, i64 %45
  store i8 92, i8* %46, align 1
  %47 = load i8*, i8** %3, align 8
  %48 = load i32, i32* %5, align 4
  %49 = add nsw i32 %48, 1
  store i32 %49, i32* %5, align 4
  %50 = sext i32 %48 to i64
  %51 = getelementptr inbounds i8, i8* %47, i64 %50
  store i8 35, i8* %51, align 1
  br label %104

52:                                               ; preds = %23, %23
  %53 = load i32, i32* %4, align 4
  %54 = sub nsw i32 %53, 1
  store i32 %54, i32* %6, align 4
  br label %55

55:                                               ; preds = %74, %52
  %56 = load i32, i32* %6, align 4
  %57 = icmp sge i32 %56, 0
  br i1 %57, label %58, label %66

58:                                               ; preds = %55
  %59 = load i8*, i8** %2, align 8
  %60 = load i32, i32* %6, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds i8, i8* %59, i64 %61
  %63 = load i8, i8* %62, align 1
  %64 = sext i8 %63 to i32
  %65 = icmp eq i32 %64, 92
  br label %66

66:                                               ; preds = %58, %55
  %67 = phi i1 [ false, %55 ], [ %65, %58 ]
  br i1 %67, label %68, label %77

68:                                               ; preds = %66
  %69 = load i8*, i8** %3, align 8
  %70 = load i32, i32* %5, align 4
  %71 = add nsw i32 %70, 1
  store i32 %71, i32* %5, align 4
  %72 = sext i32 %70 to i64
  %73 = getelementptr inbounds i8, i8* %69, i64 %72
  store i8 92, i8* %73, align 1
  br label %74

74:                                               ; preds = %68
  %75 = load i32, i32* %6, align 4
  %76 = add nsw i32 %75, -1
  store i32 %76, i32* %6, align 4
  br label %55, !llvm.loop !18

77:                                               ; preds = %66
  %78 = load i8*, i8** %3, align 8
  %79 = load i32, i32* %5, align 4
  %80 = add nsw i32 %79, 1
  store i32 %80, i32* %5, align 4
  %81 = sext i32 %79 to i64
  %82 = getelementptr inbounds i8, i8* %78, i64 %81
  store i8 92, i8* %82, align 1
  %83 = load i8*, i8** %2, align 8
  %84 = load i32, i32* %4, align 4
  %85 = sext i32 %84 to i64
  %86 = getelementptr inbounds i8, i8* %83, i64 %85
  %87 = load i8, i8* %86, align 1
  %88 = load i8*, i8** %3, align 8
  %89 = load i32, i32* %5, align 4
  %90 = add nsw i32 %89, 1
  store i32 %90, i32* %5, align 4
  %91 = sext i32 %89 to i64
  %92 = getelementptr inbounds i8, i8* %88, i64 %91
  store i8 %87, i8* %92, align 1
  br label %104

93:                                               ; preds = %23
  %94 = load i8*, i8** %2, align 8
  %95 = load i32, i32* %4, align 4
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds i8, i8* %94, i64 %96
  %98 = load i8, i8* %97, align 1
  %99 = load i8*, i8** %3, align 8
  %100 = load i32, i32* %5, align 4
  %101 = add nsw i32 %100, 1
  store i32 %101, i32* %5, align 4
  %102 = sext i32 %100 to i64
  %103 = getelementptr inbounds i8, i8* %99, i64 %102
  store i8 %98, i8* %103, align 1
  br label %104

104:                                              ; preds = %93, %77, %41, %30
  br label %105

105:                                              ; preds = %104
  %106 = load i32, i32* %4, align 4
  %107 = add nsw i32 %106, 1
  store i32 %107, i32* %4, align 4
  br label %16, !llvm.loop !19

108:                                              ; preds = %16
  %109 = load i8*, i8** %3, align 8
  ret i8* %109
}

declare void @hashmap_test() #2

; Function Attrs: noreturn nounwind
declare void @exit(i32 noundef) #7

; Function Attrs: argmemonly nofree nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #8

; Function Attrs: nounwind readonly willreturn
declare i8* @strchr(i8* noundef, i32 noundef) #3

declare void @define_macro(i8* noundef, i8* noundef) #2

; Function Attrs: nounwind
declare noalias i8* @strndup(i8* noundef, i64 noundef) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64 noundef, i64 noundef) #1

; Function Attrs: nounwind
declare i8* @dirname(i8* noundef) #1

declare i8* @search_include_paths(i8* noundef) #2

; Function Attrs: nounwind
declare i8* @strerror(i32 noundef) #1

; Function Attrs: nounwind readnone willreturn
declare i32* @__errno_location() #9

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @must_tokenize_file(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.Token*, align 8
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  %5 = call %struct.Token* @tokenize_file(i8* noundef %4)
  store %struct.Token* %5, %struct.Token** %3, align 8
  %6 = load %struct.Token*, %struct.Token** %3, align 8
  %7 = icmp ne %struct.Token* %6, null
  br i1 %7, label %13, label %8

8:                                                ; preds = %1
  %9 = load i8*, i8** %2, align 8
  %10 = call i32* @__errno_location() #14
  %11 = load i32, i32* %10, align 4
  %12 = call i8* @strerror(i32 noundef %11) #10
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([34 x i8], [34 x i8]* @.str.110, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8* noundef %9, i8* noundef %12) #12
  unreachable

13:                                               ; preds = %1
  %14 = load %struct.Token*, %struct.Token** %3, align 8
  ret %struct.Token* %14
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @append_tokens(%struct.Token* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = icmp ne %struct.Token* %7, null
  br i1 %8, label %9, label %14

9:                                                ; preds = %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 0
  %12 = load i32, i32* %11, align 16
  %13 = icmp eq i32 %12, 6
  br i1 %13, label %14, label %16

14:                                               ; preds = %9, %2
  %15 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %15, %struct.Token** %3, align 8
  br label %34

16:                                               ; preds = %9
  %17 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %17, %struct.Token** %6, align 8
  br label %18

18:                                               ; preds = %25, %16
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 1
  %21 = load %struct.Token*, %struct.Token** %20, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 0
  %23 = load i32, i32* %22, align 16
  %24 = icmp ne i32 %23, 6
  br i1 %24, label %25, label %29

25:                                               ; preds = %18
  %26 = load %struct.Token*, %struct.Token** %6, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  store %struct.Token* %28, %struct.Token** %6, align 8
  br label %18, !llvm.loop !20

29:                                               ; preds = %18
  %30 = load %struct.Token*, %struct.Token** %5, align 8
  %31 = load %struct.Token*, %struct.Token** %6, align 8
  %32 = getelementptr inbounds %struct.Token, %struct.Token* %31, i32 0, i32 1
  store %struct.Token* %30, %struct.Token** %32, align 8
  %33 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %33, %struct.Token** %3, align 8
  br label %34

34:                                               ; preds = %29, %14
  %35 = load %struct.Token*, %struct.Token** %3, align 8
  ret %struct.Token* %35
}

declare %struct.Token* @preprocess(%struct.Token* noundef, i1 noundef zeroext) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal void @print_dependencies() #0 {
  %1 = alloca i8*, align 8
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct._IO_FILE*, align 8
  %5 = alloca %struct.File**, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = load i8*, i8** @opt_MF, align 8
  %9 = icmp ne i8* %8, null
  br i1 %9, label %10, label %12

10:                                               ; preds = %0
  %11 = load i8*, i8** @opt_MF, align 8
  store i8* %11, i8** %1, align 8
  br label %48

12:                                               ; preds = %0
  %13 = load i8, i8* @opt_MD, align 1
  %14 = trunc i8 %13 to i1
  br i1 %14, label %15, label %40

15:                                               ; preds = %12
  %16 = load i8*, i8** @opt_o, align 8
  %17 = icmp ne i8* %16, null
  br i1 %17, label %18, label %20

18:                                               ; preds = %15
  %19 = load i8*, i8** @opt_o, align 8
  br label %22

20:                                               ; preds = %15
  %21 = load i8*, i8** @base_file, align 8
  br label %22

22:                                               ; preds = %20, %18
  %23 = phi i8* [ %19, %18 ], [ %21, %20 ]
  %24 = call i8* @replace_extn(i8* noundef %23, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.111, i64 0, i64 0))
  store i8* %24, i8** %1, align 8
  %25 = load i8*, i8** @opt_o, align 8
  %26 = icmp ne i8* %25, null
  br i1 %26, label %27, label %39

27:                                               ; preds = %22
  %28 = load i8*, i8** @opt_o, align 8
  %29 = call i8* @extract_filename(i8* noundef %28)
  store i8* %29, i8** %3, align 8
  %30 = load i8*, i8** @opt_o, align 8
  %31 = load i8*, i8** %3, align 8
  %32 = call i8* @extract_path(i8* noundef %30, i8* noundef %31)
  store i8* %32, i8** %2, align 8
  %33 = load i8*, i8** %2, align 8
  %34 = load i8*, i8** %1, align 8
  %35 = load i8*, i8** %1, align 8
  %36 = call i64 @strlen(i8* noundef %35) #11
  %37 = call i8* @strncat(i8* noundef %33, i8* noundef %34, i64 noundef %36) #10
  %38 = load i8*, i8** %2, align 8
  store i8* %38, i8** %1, align 8
  br label %39

39:                                               ; preds = %27, %22
  br label %47

40:                                               ; preds = %12
  %41 = load i8*, i8** @opt_o, align 8
  %42 = icmp ne i8* %41, null
  br i1 %42, label %43, label %45

43:                                               ; preds = %40
  %44 = load i8*, i8** @opt_o, align 8
  store i8* %44, i8** %1, align 8
  br label %46

45:                                               ; preds = %40
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.112, i64 0, i64 0), i8** %1, align 8
  br label %46

46:                                               ; preds = %45, %43
  br label %47

47:                                               ; preds = %46, %39
  br label %48

48:                                               ; preds = %47, %10
  %49 = load i8*, i8** %1, align 8
  %50 = call %struct._IO_FILE* @open_file(i8* noundef %49)
  store %struct._IO_FILE* %50, %struct._IO_FILE** %4, align 8
  %51 = load i8*, i8** @opt_MT, align 8
  %52 = icmp ne i8* %51, null
  br i1 %52, label %53, label %57

53:                                               ; preds = %48
  %54 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %55 = load i8*, i8** @opt_MT, align 8
  %56 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %54, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.113, i64 0, i64 0), i8* noundef %55)
  br label %63

57:                                               ; preds = %48
  %58 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %59 = load i8*, i8** @base_file, align 8
  %60 = call i8* @replace_extn(i8* noundef %59, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.13, i64 0, i64 0))
  %61 = call i8* @quote_makefile(i8* noundef %60)
  %62 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %58, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.113, i64 0, i64 0), i8* noundef %61)
  br label %63

63:                                               ; preds = %57, %53
  %64 = call %struct.File** @get_input_files()
  store %struct.File** %64, %struct.File*** %5, align 8
  store i32 0, i32* %6, align 4
  br label %65

65:                                               ; preds = %95, %63
  %66 = load %struct.File**, %struct.File*** %5, align 8
  %67 = load i32, i32* %6, align 4
  %68 = sext i32 %67 to i64
  %69 = getelementptr inbounds %struct.File*, %struct.File** %66, i64 %68
  %70 = load %struct.File*, %struct.File** %69, align 8
  %71 = icmp ne %struct.File* %70, null
  br i1 %71, label %72, label %98

72:                                               ; preds = %65
  %73 = load i8, i8* @opt_MMD, align 1
  %74 = trunc i8 %73 to i1
  br i1 %74, label %75, label %85

75:                                               ; preds = %72
  %76 = load %struct.File**, %struct.File*** %5, align 8
  %77 = load i32, i32* %6, align 4
  %78 = sext i32 %77 to i64
  %79 = getelementptr inbounds %struct.File*, %struct.File** %76, i64 %78
  %80 = load %struct.File*, %struct.File** %79, align 8
  %81 = getelementptr inbounds %struct.File, %struct.File* %80, i32 0, i32 0
  %82 = load i8*, i8** %81, align 8
  %83 = call zeroext i1 @in_std_include_path(i8* noundef %82)
  br i1 %83, label %84, label %85

84:                                               ; preds = %75
  br label %95

85:                                               ; preds = %75, %72
  %86 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %87 = load %struct.File**, %struct.File*** %5, align 8
  %88 = load i32, i32* %6, align 4
  %89 = sext i32 %88 to i64
  %90 = getelementptr inbounds %struct.File*, %struct.File** %87, i64 %89
  %91 = load %struct.File*, %struct.File** %90, align 8
  %92 = getelementptr inbounds %struct.File, %struct.File* %91, i32 0, i32 0
  %93 = load i8*, i8** %92, align 8
  %94 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %86, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.114, i64 0, i64 0), i8* noundef %93)
  br label %95

95:                                               ; preds = %85, %84
  %96 = load i32, i32* %6, align 4
  %97 = add nsw i32 %96, 1
  store i32 %97, i32* %6, align 4
  br label %65, !llvm.loop !21

98:                                               ; preds = %65
  %99 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %100 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %99, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.115, i64 0, i64 0))
  %101 = load i8, i8* @opt_MP, align 1
  %102 = trunc i8 %101 to i1
  br i1 %102, label %103, label %139

103:                                              ; preds = %98
  store i32 1, i32* %7, align 4
  br label %104

104:                                              ; preds = %135, %103
  %105 = load %struct.File**, %struct.File*** %5, align 8
  %106 = load i32, i32* %7, align 4
  %107 = sext i32 %106 to i64
  %108 = getelementptr inbounds %struct.File*, %struct.File** %105, i64 %107
  %109 = load %struct.File*, %struct.File** %108, align 8
  %110 = icmp ne %struct.File* %109, null
  br i1 %110, label %111, label %138

111:                                              ; preds = %104
  %112 = load i8, i8* @opt_MMD, align 1
  %113 = trunc i8 %112 to i1
  br i1 %113, label %114, label %124

114:                                              ; preds = %111
  %115 = load %struct.File**, %struct.File*** %5, align 8
  %116 = load i32, i32* %7, align 4
  %117 = sext i32 %116 to i64
  %118 = getelementptr inbounds %struct.File*, %struct.File** %115, i64 %117
  %119 = load %struct.File*, %struct.File** %118, align 8
  %120 = getelementptr inbounds %struct.File, %struct.File* %119, i32 0, i32 0
  %121 = load i8*, i8** %120, align 8
  %122 = call zeroext i1 @in_std_include_path(i8* noundef %121)
  br i1 %122, label %123, label %124

123:                                              ; preds = %114
  br label %135

124:                                              ; preds = %114, %111
  %125 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %126 = load %struct.File**, %struct.File*** %5, align 8
  %127 = load i32, i32* %7, align 4
  %128 = sext i32 %127 to i64
  %129 = getelementptr inbounds %struct.File*, %struct.File** %126, i64 %128
  %130 = load %struct.File*, %struct.File** %129, align 8
  %131 = getelementptr inbounds %struct.File, %struct.File* %130, i32 0, i32 0
  %132 = load i8*, i8** %131, align 8
  %133 = call i8* @quote_makefile(i8* noundef %132)
  %134 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %125, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.116, i64 0, i64 0), i8* noundef %133)
  br label %135

135:                                              ; preds = %124, %123
  %136 = load i32, i32* %7, align 4
  %137 = add nsw i32 %136, 1
  store i32 %137, i32* %7, align 4
  br label %104, !llvm.loop !22

138:                                              ; preds = %104
  br label %139

139:                                              ; preds = %138, %98
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @print_tokens(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca i32, align 4
  store %struct.Token* %0, %struct.Token** %2, align 8
  %5 = load i8*, i8** @opt_o, align 8
  %6 = icmp ne i8* %5, null
  br i1 %6, label %7, label %9

7:                                                ; preds = %1
  %8 = load i8*, i8** @opt_o, align 8
  br label %10

9:                                                ; preds = %1
  br label %10

10:                                               ; preds = %9, %7
  %11 = phi i8* [ %8, %7 ], [ getelementptr inbounds ([2 x i8], [2 x i8]* @.str.112, i64 0, i64 0), %9 ]
  %12 = call %struct._IO_FILE* @open_file(i8* noundef %11)
  store %struct._IO_FILE* %12, %struct._IO_FILE** %3, align 8
  store i32 1, i32* %4, align 4
  br label %13

13:                                               ; preds = %53, %10
  %14 = load %struct.Token*, %struct.Token** %2, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 16
  %17 = icmp ne i32 %16, 6
  br i1 %17, label %18, label %57

18:                                               ; preds = %13
  %19 = load i32, i32* %4, align 4
  %20 = icmp sgt i32 %19, 1
  br i1 %20, label %21, label %29

21:                                               ; preds = %18
  %22 = load %struct.Token*, %struct.Token** %2, align 8
  %23 = getelementptr inbounds %struct.Token, %struct.Token* %22, i32 0, i32 12
  %24 = load i8, i8* %23, align 8
  %25 = trunc i8 %24 to i1
  br i1 %25, label %26, label %29

26:                                               ; preds = %21
  %27 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8
  %28 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %27, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.117, i64 0, i64 0))
  br label %29

29:                                               ; preds = %26, %21, %18
  %30 = load %struct.Token*, %struct.Token** %2, align 8
  %31 = getelementptr inbounds %struct.Token, %struct.Token* %30, i32 0, i32 13
  %32 = load i8, i8* %31, align 1
  %33 = trunc i8 %32 to i1
  br i1 %33, label %34, label %42

34:                                               ; preds = %29
  %35 = load %struct.Token*, %struct.Token** %2, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 12
  %37 = load i8, i8* %36, align 8
  %38 = trunc i8 %37 to i1
  br i1 %38, label %42, label %39

39:                                               ; preds = %34
  %40 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8
  %41 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %40, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i64 0, i64 0))
  br label %42

42:                                               ; preds = %39, %34, %29
  %43 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8
  %44 = load %struct.Token*, %struct.Token** %2, align 8
  %45 = getelementptr inbounds %struct.Token, %struct.Token* %44, i32 0, i32 5
  %46 = load i32, i32* %45, align 8
  %47 = load %struct.Token*, %struct.Token** %2, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 4
  %49 = load i8*, i8** %48, align 16
  %50 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %43, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.118, i64 0, i64 0), i32 noundef %46, i8* noundef %49)
  %51 = load i32, i32* %4, align 4
  %52 = add nsw i32 %51, 1
  store i32 %52, i32* %4, align 4
  br label %53

53:                                               ; preds = %42
  %54 = load %struct.Token*, %struct.Token** %2, align 8
  %55 = getelementptr inbounds %struct.Token, %struct.Token* %54, i32 0, i32 1
  %56 = load %struct.Token*, %struct.Token** %55, align 8
  store %struct.Token* %56, %struct.Token** %2, align 8
  br label %13, !llvm.loop !23

57:                                               ; preds = %13
  %58 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8
  %59 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %58, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.117, i64 0, i64 0))
  ret void
}

declare %struct.Obj* @parse(%struct.Token* noundef) #2

; Function Attrs: nounwind
declare noalias %struct._IO_FILE* @open_memstream(i8** noundef, i64* noundef) #1

declare void @codegen(%struct.Obj* noundef, %struct._IO_FILE* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct._IO_FILE* @open_file(i8* noundef %0) #0 {
  %2 = alloca %struct._IO_FILE*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct._IO_FILE*, align 8
  store i8* %0, i8** %3, align 8
  %5 = load i8*, i8** %3, align 8
  %6 = icmp ne i8* %5, null
  br i1 %6, label %7, label %11

7:                                                ; preds = %1
  %8 = load i8*, i8** %3, align 8
  %9 = call i32 @strcmp(i8* noundef %8, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.112, i64 0, i64 0)) #11
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %11, label %13

11:                                               ; preds = %7, %1
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  store %struct._IO_FILE* %12, %struct._IO_FILE** %2, align 8
  br label %25

13:                                               ; preds = %7
  %14 = load i8*, i8** %3, align 8
  %15 = call noalias %struct._IO_FILE* @fopen(i8* noundef %14, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  store %struct._IO_FILE* %15, %struct._IO_FILE** %4, align 8
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %17 = icmp ne %struct._IO_FILE* %16, null
  br i1 %17, label %23, label %18

18:                                               ; preds = %13
  %19 = load i8*, i8** %3, align 8
  %20 = call i32* @__errno_location() #14
  %21 = load i32, i32* %20, align 4
  %22 = call i8* @strerror(i32 noundef %21) #10
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([50 x i8], [50 x i8]* @.str.119, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8* noundef %19, i8* noundef %22) #12
  unreachable

23:                                               ; preds = %13
  %24 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  store %struct._IO_FILE* %24, %struct._IO_FILE** %2, align 8
  br label %25

25:                                               ; preds = %23, %11
  %26 = load %struct._IO_FILE*, %struct._IO_FILE** %2, align 8
  ret %struct._IO_FILE* %26
}

declare i64 @fwrite(i8* noundef, i64 noundef, i64 noundef, %struct._IO_FILE* noundef) #2

declare %struct.Token* @tokenize_file(i8* noundef) #2

; Function Attrs: nounwind
declare i8* @strncat(i8* noundef, i8* noundef, i64 noundef) #1

declare %struct.File** @get_input_files() #2

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @in_std_include_path(i8* noundef %0) #0 {
  %2 = alloca i1, align 1
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i32 0, i32* %4, align 4
  br label %7

7:                                                ; preds = %36, %1
  %8 = load i32, i32* %4, align 4
  %9 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @std_include_paths, i32 0, i32 2), align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %39

11:                                               ; preds = %7
  %12 = load i8**, i8*** getelementptr inbounds (%struct.StringArray, %struct.StringArray* @std_include_paths, i32 0, i32 0), align 8
  %13 = load i32, i32* %4, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds i8*, i8** %12, i64 %14
  %16 = load i8*, i8** %15, align 8
  store i8* %16, i8** %5, align 8
  %17 = load i8*, i8** %5, align 8
  %18 = call i64 @strlen(i8* noundef %17) #11
  %19 = trunc i64 %18 to i32
  store i32 %19, i32* %6, align 4
  %20 = load i8*, i8** %5, align 8
  %21 = load i8*, i8** %3, align 8
  %22 = load i32, i32* %6, align 4
  %23 = sext i32 %22 to i64
  %24 = call i32 @strncmp(i8* noundef %20, i8* noundef %21, i64 noundef %23) #11
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %26, label %35

26:                                               ; preds = %11
  %27 = load i8*, i8** %3, align 8
  %28 = load i32, i32* %6, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds i8, i8* %27, i64 %29
  %31 = load i8, i8* %30, align 1
  %32 = sext i8 %31 to i32
  %33 = icmp eq i32 %32, 47
  br i1 %33, label %34, label %35

34:                                               ; preds = %26
  store i1 true, i1* %2, align 1
  br label %40

35:                                               ; preds = %26, %11
  br label %36

36:                                               ; preds = %35
  %37 = load i32, i32* %4, align 4
  %38 = add nsw i32 %37, 1
  store i32 %38, i32* %4, align 4
  br label %7, !llvm.loop !24

39:                                               ; preds = %7
  store i1 false, i1* %2, align 1
  br label %40

40:                                               ; preds = %39, %34
  %41 = load i1, i1* %2, align 1
  ret i1 %41
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @endswith(i8* noundef %0, i8* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %7 = load i8*, i8** %3, align 8
  %8 = call i64 @strlen(i8* noundef %7) #11
  %9 = trunc i64 %8 to i32
  store i32 %9, i32* %5, align 4
  %10 = load i8*, i8** %4, align 8
  %11 = call i64 @strlen(i8* noundef %10) #11
  %12 = trunc i64 %11 to i32
  store i32 %12, i32* %6, align 4
  %13 = load i32, i32* %5, align 4
  %14 = load i32, i32* %6, align 4
  %15 = icmp sge i32 %13, %14
  br i1 %15, label %16, label %29

16:                                               ; preds = %2
  %17 = load i8*, i8** %3, align 8
  %18 = load i32, i32* %5, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds i8, i8* %17, i64 %19
  %21 = load i32, i32* %6, align 4
  %22 = sext i32 %21 to i64
  %23 = sub i64 0, %22
  %24 = getelementptr inbounds i8, i8* %20, i64 %23
  %25 = load i8*, i8** %4, align 8
  %26 = call i32 @strcmp(i8* noundef %24, i8* noundef %25) #11
  %27 = icmp ne i32 %26, 0
  %28 = xor i1 %27, true
  br label %29

29:                                               ; preds = %16, %2
  %30 = phi i1 [ false, %2 ], [ %28, %16 ]
  ret i1 %30
}

; Function Attrs: nounwind readonly willreturn
declare i8* @strstr(i8* noundef, i8* noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal void @run_subprocess(i8** noundef %0) #0 {
  %2 = alloca i8**, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i8** %0, i8*** %2, align 8
  %6 = load i8, i8* @opt_hash_hash_hash, align 1
  %7 = trunc i8 %6 to i1
  br i1 %7, label %8, label %35

8:                                                ; preds = %1
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %10 = load i8**, i8*** %2, align 8
  %11 = getelementptr inbounds i8*, i8** %10, i64 0
  %12 = load i8*, i8** %11, align 8
  %13 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %9, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i64 0, i64 0), i8* noundef %12)
  store i32 1, i32* %3, align 4
  br label %14

14:                                               ; preds = %29, %8
  %15 = load i8**, i8*** %2, align 8
  %16 = load i32, i32* %3, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds i8*, i8** %15, i64 %17
  %19 = load i8*, i8** %18, align 8
  %20 = icmp ne i8* %19, null
  br i1 %20, label %21, label %32

21:                                               ; preds = %14
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %23 = load i8**, i8*** %2, align 8
  %24 = load i32, i32* %3, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i8*, i8** %23, i64 %25
  %27 = load i8*, i8** %26, align 8
  %28 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %22, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.128, i64 0, i64 0), i8* noundef %27)
  br label %29

29:                                               ; preds = %21
  %30 = load i32, i32* %3, align 4
  %31 = add nsw i32 %30, 1
  store i32 %31, i32* %3, align 4
  br label %14, !llvm.loop !25

32:                                               ; preds = %14
  %33 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8
  %34 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %33, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.117, i64 0, i64 0))
  br label %35

35:                                               ; preds = %32, %1
  %36 = load i8, i8* @isDebug, align 1
  %37 = trunc i8 %36 to i1
  br i1 %37, label %38, label %68

38:                                               ; preds = %35
  %39 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %40 = icmp ne %struct._IO_FILE* %39, null
  br i1 %40, label %41, label %68

41:                                               ; preds = %38
  %42 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %43 = load i8**, i8*** %2, align 8
  %44 = getelementptr inbounds i8*, i8** %43, i64 0
  %45 = load i8*, i8** %44, align 8
  %46 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %42, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i64 0, i64 0), i8* noundef %45)
  store i32 1, i32* %4, align 4
  br label %47

47:                                               ; preds = %62, %41
  %48 = load i8**, i8*** %2, align 8
  %49 = load i32, i32* %4, align 4
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds i8*, i8** %48, i64 %50
  %52 = load i8*, i8** %51, align 8
  %53 = icmp ne i8* %52, null
  br i1 %53, label %54, label %65

54:                                               ; preds = %47
  %55 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %56 = load i8**, i8*** %2, align 8
  %57 = load i32, i32* %4, align 4
  %58 = sext i32 %57 to i64
  %59 = getelementptr inbounds i8*, i8** %56, i64 %58
  %60 = load i8*, i8** %59, align 8
  %61 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %55, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.128, i64 0, i64 0), i8* noundef %60)
  br label %62

62:                                               ; preds = %54
  %63 = load i32, i32* %4, align 4
  %64 = add nsw i32 %63, 1
  store i32 %64, i32* %4, align 4
  br label %47, !llvm.loop !26

65:                                               ; preds = %47
  %66 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %67 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %66, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.117, i64 0, i64 0))
  br label %68

68:                                               ; preds = %65, %38, %35
  %69 = call i32 @fork() #10
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %71, label %85

71:                                               ; preds = %68
  %72 = load i8**, i8*** %2, align 8
  %73 = getelementptr inbounds i8*, i8** %72, i64 0
  %74 = load i8*, i8** %73, align 8
  %75 = load i8**, i8*** %2, align 8
  %76 = call i32 @execvp(i8* noundef %74, i8** noundef %75) #10
  %77 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %78 = load i8**, i8*** %2, align 8
  %79 = getelementptr inbounds i8*, i8** %78, i64 0
  %80 = load i8*, i8** %79, align 8
  %81 = call i32* @__errno_location() #14
  %82 = load i32, i32* %81, align 4
  %83 = call i8* @strerror(i32 noundef %82) #10
  %84 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %77, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.129, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8* noundef %80, i8* noundef %83)
  call void @_exit(i32 noundef 99) #12
  unreachable

85:                                               ; preds = %68
  br label %86

86:                                               ; preds = %89, %85
  %87 = call i32 @wait(i32* noundef %5)
  %88 = icmp sgt i32 %87, 0
  br i1 %88, label %89, label %90

89:                                               ; preds = %86
  br label %86, !llvm.loop !27

90:                                               ; preds = %86
  %91 = load i32, i32* %5, align 4
  %92 = icmp ne i32 %91, 0
  br i1 %92, label %93, label %94

93:                                               ; preds = %90
  call void @exit(i32 noundef 1) #13
  unreachable

94:                                               ; preds = %90
  ret void
}

; Function Attrs: nounwind
declare i32 @fork() #1

; Function Attrs: nounwind
declare i32 @execvp(i8* noundef, i8** noundef) #1

; Function Attrs: noreturn
declare void @_exit(i32 noundef) #6

declare i32 @wait(i32* noundef) #2

declare i32 @mkstemp(i8* noundef) #2

declare i32 @close(i32 noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @find_libpath() #0 {
  %1 = alloca i8*, align 8
  %2 = call zeroext i1 @file_exists(i8* noundef getelementptr inbounds ([33 x i8], [33 x i8]* @.str.163, i64 0, i64 0))
  br i1 %2, label %3, label %4

3:                                                ; preds = %0
  store i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.164, i64 0, i64 0), i8** %1, align 8
  br label %8

4:                                                ; preds = %0
  %5 = call zeroext i1 @file_exists(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.165, i64 0, i64 0))
  br i1 %5, label %6, label %7

6:                                                ; preds = %4
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.166, i64 0, i64 0), i8** %1, align 8
  br label %8

7:                                                ; preds = %4
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([47 x i8], [47 x i8]* @.str.167, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable

8:                                                ; preds = %6, %3
  %9 = load i8*, i8** %1, align 8
  ret i8* %9
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @find_gcc_libpath() #0 {
  %1 = alloca [4 x i8*], align 16
  %2 = alloca i32, align 4
  %3 = alloca i8*, align 8
  %4 = bitcast [4 x i8*]* %1 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %4, i8* align 16 bitcast ([4 x i8*]* @__const.find_gcc_libpath.paths to i8*), i64 32, i1 false)
  store i32 0, i32* %2, align 4
  br label %5

5:                                                ; preds = %21, %0
  %6 = load i32, i32* %2, align 4
  %7 = sext i32 %6 to i64
  %8 = icmp ult i64 %7, 4
  br i1 %8, label %9, label %24

9:                                                ; preds = %5
  %10 = load i32, i32* %2, align 4
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds [4 x i8*], [4 x i8*]* %1, i64 0, i64 %11
  %13 = load i8*, i8** %12, align 8
  %14 = call i8* @find_file(i8* noundef %13)
  store i8* %14, i8** %3, align 8
  %15 = load i8*, i8** %3, align 8
  %16 = icmp ne i8* %15, null
  br i1 %16, label %17, label %20

17:                                               ; preds = %9
  %18 = load i8*, i8** %3, align 8
  %19 = call i8* @dirname(i8* noundef %18) #10
  ret i8* %19

20:                                               ; preds = %9
  br label %21

21:                                               ; preds = %20
  %22 = load i32, i32* %2, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* %2, align 4
  br label %5, !llvm.loop !28

24:                                               ; preds = %5
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([55 x i8], [55 x i8]* @.str.172, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)) #12
  unreachable
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @find_file(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct.glob_t, align 8
  store i8* %0, i8** %2, align 8
  store i8* null, i8** %3, align 8
  %5 = bitcast %struct.glob_t* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %5, i8 0, i64 72, i1 false)
  %6 = load i8*, i8** %2, align 8
  %7 = call i32 @glob(i8* noundef %6, i32 noundef 0, i32 (i8*, i32)* noundef null, %struct.glob_t* noundef %4) #10
  %8 = getelementptr inbounds %struct.glob_t, %struct.glob_t* %4, i32 0, i32 0
  %9 = load i64, i64* %8, align 8
  %10 = icmp ugt i64 %9, 0
  br i1 %10, label %11, label %20

11:                                               ; preds = %1
  %12 = getelementptr inbounds %struct.glob_t, %struct.glob_t* %4, i32 0, i32 1
  %13 = load i8**, i8*** %12, align 8
  %14 = getelementptr inbounds %struct.glob_t, %struct.glob_t* %4, i32 0, i32 0
  %15 = load i64, i64* %14, align 8
  %16 = sub i64 %15, 1
  %17 = getelementptr inbounds i8*, i8** %13, i64 %16
  %18 = load i8*, i8** %17, align 8
  %19 = call noalias i8* @strdup(i8* noundef %18) #10
  store i8* %19, i8** %3, align 8
  br label %20

20:                                               ; preds = %11, %1
  call void @globfree(%struct.glob_t* noundef %4) #10
  %21 = load i8*, i8** %3, align 8
  ret i8* %21
}

; Function Attrs: nounwind
declare i32 @glob(i8* noundef, i32 noundef, i32 (i8*, i32)* noundef, %struct.glob_t* noundef) #1

; Function Attrs: nounwind
declare void @globfree(%struct.glob_t* noundef) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind readonly willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nofree nosync nounwind willreturn }
attributes #5 = { argmemonly nofree nounwind willreturn writeonly }
attributes #6 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { argmemonly nofree nounwind willreturn }
attributes #9 = { nounwind readnone willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #10 = { nounwind }
attributes #11 = { nounwind readonly willreturn }
attributes #12 = { noreturn }
attributes #13 = { noreturn nounwind }
attributes #14 = { nounwind readnone willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
!16 = distinct !{!16, !7}
!17 = distinct !{!17, !7}
!18 = distinct !{!18, !7}
!19 = distinct !{!19, !7}
!20 = distinct !{!20, !7}
!21 = distinct !{!21, !7}
!22 = distinct !{!22, !7}
!23 = distinct !{!23, !7}
!24 = distinct !{!24, !7}
!25 = distinct !{!25, !7}
!26 = distinct !{!26, !7}
!27 = distinct !{!27, !7}
!28 = distinct !{!28, !7}
