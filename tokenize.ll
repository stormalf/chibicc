; ModuleID = 'tokenize.c'
source_filename = "tokenize.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, %struct._IO_codecvt*, %struct._IO_wide_data*, %struct._IO_FILE*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type opaque
%struct._IO_codecvt = type opaque
%struct._IO_wide_data = type opaque
%struct.File = type { i8*, i32, i8*, i8*, i32 }
%struct.Type = type { i32, i32, i32, i8, i8, i8, %struct.Type*, %struct.Type*, %struct.Type*, %struct.Token*, %struct.Token*, i32, %struct.Node*, %struct.Obj*, %struct.Member*, i8, i8, %struct.Type*, %struct.Type*, i8, %struct.Type* }
%struct.Token = type { i32, %struct.Token*, i64, x86_fp80, i8*, i32, %struct.Type*, i8*, %struct.File*, i8*, i32, i32, i8, i8, %struct.Hideset*, %struct.Token* }
%struct.Hideset = type opaque
%struct.Node = type { i32, %struct.Node*, %struct.Type*, %struct.Token*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, i8*, i8*, %struct.Node*, %struct.Member*, %struct.Type*, %struct.Node*, i8, %struct.Obj*, i8*, i8*, %struct.Node*, %struct.Node*, %struct.Node*, i64, i64, i8*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Obj*, %struct.Node*, i8, %struct.Obj*, i64, x86_fp80, i32, [12 x i8] }
%struct.Obj = type { %struct.Obj*, i8*, i8*, %struct.Type*, %struct.Token*, i8, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8*, %struct.Relocation*, i8, %struct.Obj*, %struct.Node*, %struct.Obj*, %struct.Obj*, %struct.Obj*, i32, i8, i8, %struct.StringArray }
%struct.Relocation = type { %struct.Relocation*, i32, i8**, i64 }
%struct.StringArray = type { i8**, i32, i32 }
%struct.Member = type { %struct.Member*, %struct.Type*, %struct.Token*, %struct.Token*, i32, i32, i32, i8, i32, i32 }
%struct.HashMap = type { %struct.HashEntry*, i32, i32 }
%struct.HashEntry = type { i8*, i32, i8* }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@stderr = external global %struct._IO_FILE*, align 8
@.str = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@current_file = internal global %struct.File* null, align 8
@.str.1 = private unnamed_addr constant [28 x i8] c"%s: in skip : expected '%s'\00", align 1
@.str.2 = private unnamed_addr constant [11 x i8] c"tokenize.c\00", align 1
@at_bol = internal global i8 0, align 1
@has_space = internal global i8 0, align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"//\00", align 1
@.str.4 = private unnamed_addr constant [3 x i8] c"/*\00", align 1
@.str.5 = private unnamed_addr constant [3 x i8] c"*/\00", align 1
@.str.6 = private unnamed_addr constant [41 x i8] c"%s: in tokenize : unclosed block comment\00", align 1
@.str.7 = private unnamed_addr constant [5 x i8] c"eEpP\00", align 1
@.str.8 = private unnamed_addr constant [3 x i8] c"+-\00", align 1
@.str.9 = private unnamed_addr constant [4 x i8] c"u8\22\00", align 1
@.str.10 = private unnamed_addr constant [3 x i8] c"u\22\00", align 1
@.str.11 = private unnamed_addr constant [3 x i8] c"L\22\00", align 1
@ty_int = external global %struct.Type*, align 8
@.str.12 = private unnamed_addr constant [3 x i8] c"U\22\00", align 1
@ty_uint = external global %struct.Type*, align 8
@.str.13 = private unnamed_addr constant [3 x i8] c"u'\00", align 1
@ty_ushort = external global %struct.Type*, align 8
@.str.14 = private unnamed_addr constant [3 x i8] c"L'\00", align 1
@.str.15 = private unnamed_addr constant [3 x i8] c"U'\00", align 1
@.str.16 = private unnamed_addr constant [32 x i8] c"%s: in tokenize : invalid token\00", align 1
@input_files = internal global %struct.File** null, align 8
@.str.17 = private unnamed_addr constant [30 x i8] c"%s: in new_file file is null!\00", align 1
@.str.18 = private unnamed_addr constant [4 x i8] c"\EF\BB\BF\00", align 1
@tokenize_file.file_no = internal global i32 0, align 4
@.str.19 = private unnamed_addr constant [42 x i8] c"%s: in tokenize_file input_files is null!\00", align 1
@.str.20 = private unnamed_addr constant [8 x i8] c"%s:%d: \00", align 1
@.str.21 = private unnamed_addr constant [6 x i8] c"%.*s\0A\00", align 1
@.str.22 = private unnamed_addr constant [4 x i8] c"%*s\00", align 1
@.str.23 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.24 = private unnamed_addr constant [3 x i8] c"^ \00", align 1
@is_keyword.map = internal global %struct.HashMap zeroinitializer, align 8
@is_keyword.kw = internal global [45 x i8*] [i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.26, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.27, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.30, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.31, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.32, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.33, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.34, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.35, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.37, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.39, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.40, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.41, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.42, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.43, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.44, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.45, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.47, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.48, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.49, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.50, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.51, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.52, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.53, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.54, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.55, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.56, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.57, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.58, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.59, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.60, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.61, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.63, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.64, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.65, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.66, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.67, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.68, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.69, i32 0, i32 0)], align 16
@.str.25 = private unnamed_addr constant [7 x i8] c"return\00", align 1
@.str.26 = private unnamed_addr constant [3 x i8] c"if\00", align 1
@.str.27 = private unnamed_addr constant [5 x i8] c"else\00", align 1
@.str.28 = private unnamed_addr constant [4 x i8] c"for\00", align 1
@.str.29 = private unnamed_addr constant [6 x i8] c"while\00", align 1
@.str.30 = private unnamed_addr constant [4 x i8] c"int\00", align 1
@.str.31 = private unnamed_addr constant [7 x i8] c"sizeof\00", align 1
@.str.32 = private unnamed_addr constant [5 x i8] c"char\00", align 1
@.str.33 = private unnamed_addr constant [7 x i8] c"struct\00", align 1
@.str.34 = private unnamed_addr constant [6 x i8] c"union\00", align 1
@.str.35 = private unnamed_addr constant [6 x i8] c"short\00", align 1
@.str.36 = private unnamed_addr constant [5 x i8] c"long\00", align 1
@.str.37 = private unnamed_addr constant [5 x i8] c"void\00", align 1
@.str.38 = private unnamed_addr constant [8 x i8] c"typedef\00", align 1
@.str.39 = private unnamed_addr constant [6 x i8] c"_Bool\00", align 1
@.str.40 = private unnamed_addr constant [5 x i8] c"enum\00", align 1
@.str.41 = private unnamed_addr constant [7 x i8] c"static\00", align 1
@.str.42 = private unnamed_addr constant [5 x i8] c"goto\00", align 1
@.str.43 = private unnamed_addr constant [6 x i8] c"break\00", align 1
@.str.44 = private unnamed_addr constant [9 x i8] c"continue\00", align 1
@.str.45 = private unnamed_addr constant [7 x i8] c"switch\00", align 1
@.str.46 = private unnamed_addr constant [5 x i8] c"case\00", align 1
@.str.47 = private unnamed_addr constant [8 x i8] c"default\00", align 1
@.str.48 = private unnamed_addr constant [7 x i8] c"extern\00", align 1
@.str.49 = private unnamed_addr constant [9 x i8] c"_Alignof\00", align 1
@.str.50 = private unnamed_addr constant [9 x i8] c"_Alignas\00", align 1
@.str.51 = private unnamed_addr constant [3 x i8] c"do\00", align 1
@.str.52 = private unnamed_addr constant [7 x i8] c"signed\00", align 1
@.str.53 = private unnamed_addr constant [9 x i8] c"unsigned\00", align 1
@.str.54 = private unnamed_addr constant [6 x i8] c"const\00", align 1
@.str.55 = private unnamed_addr constant [9 x i8] c"volatile\00", align 1
@.str.56 = private unnamed_addr constant [5 x i8] c"auto\00", align 1
@.str.57 = private unnamed_addr constant [9 x i8] c"register\00", align 1
@.str.58 = private unnamed_addr constant [9 x i8] c"restrict\00", align 1
@.str.59 = private unnamed_addr constant [11 x i8] c"__restrict\00", align 1
@.str.60 = private unnamed_addr constant [13 x i8] c"__restrict__\00", align 1
@.str.61 = private unnamed_addr constant [10 x i8] c"_Noreturn\00", align 1
@.str.62 = private unnamed_addr constant [6 x i8] c"float\00", align 1
@.str.63 = private unnamed_addr constant [7 x i8] c"double\00", align 1
@.str.64 = private unnamed_addr constant [7 x i8] c"typeof\00", align 1
@.str.65 = private unnamed_addr constant [4 x i8] c"asm\00", align 1
@.str.66 = private unnamed_addr constant [14 x i8] c"_Thread_local\00", align 1
@.str.67 = private unnamed_addr constant [9 x i8] c"__thread\00", align 1
@.str.68 = private unnamed_addr constant [8 x i8] c"_Atomic\00", align 1
@.str.69 = private unnamed_addr constant [14 x i8] c"__attribute__\00", align 1
@ty_float = external global %struct.Type*, align 8
@ty_ldouble = external global %struct.Type*, align 8
@ty_double = external global %struct.Type*, align 8
@.str.70 = private unnamed_addr constant [52 x i8] c"%s: in convert_pp_number : invalid numeric constant\00", align 1
@.str.71 = private unnamed_addr constant [3 x i8] c"0x\00", align 1
@.str.72 = private unnamed_addr constant [3 x i8] c"0b\00", align 1
@.str.73 = private unnamed_addr constant [4 x i8] c"LLU\00", align 1
@.str.74 = private unnamed_addr constant [4 x i8] c"LLu\00", align 1
@.str.75 = private unnamed_addr constant [4 x i8] c"llU\00", align 1
@.str.76 = private unnamed_addr constant [4 x i8] c"llu\00", align 1
@.str.77 = private unnamed_addr constant [4 x i8] c"ULL\00", align 1
@.str.78 = private unnamed_addr constant [4 x i8] c"Ull\00", align 1
@.str.79 = private unnamed_addr constant [4 x i8] c"uLL\00", align 1
@.str.80 = private unnamed_addr constant [4 x i8] c"ull\00", align 1
@.str.81 = private unnamed_addr constant [3 x i8] c"lu\00", align 1
@.str.82 = private unnamed_addr constant [3 x i8] c"ul\00", align 1
@.str.83 = private unnamed_addr constant [3 x i8] c"LL\00", align 1
@.str.84 = private unnamed_addr constant [3 x i8] c"ll\00", align 1
@ty_ulong = external global %struct.Type*, align 8
@ty_long = external global %struct.Type*, align 8
@.str.85 = private unnamed_addr constant [46 x i8] c"%s: in read_utf16_string_literal buf is null!\00", align 1
@.str.86 = private unnamed_addr constant [52 x i8] c"%s: in string_literal_end : unclosed string literal\00", align 1
@.str.87 = private unnamed_addr constant [55 x i8] c"%s: in read_escaped_char : invalid hex escape sequence\00", align 1
@.str.88 = private unnamed_addr constant [46 x i8] c"%s: in read_utf32_string_literal buf is null!\00", align 1
@.str.89 = private unnamed_addr constant [30 x i8] c"%s: in new_token tok is null!\00", align 1
@.str.90 = private unnamed_addr constant [40 x i8] c"%s: in read_string_literal buf is null!\00", align 1
@ty_char = external global %struct.Type*, align 8
@.str.91 = private unnamed_addr constant [49 x i8] c"%s: in read_char_literal : unclosed char literal\00", align 1
@read_punct.kw = internal global [23 x i8*] [i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.93, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.94, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.95, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.96, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.97, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.98, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.100, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.101, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.102, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.103, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.104, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.105, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.106, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.107, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.108, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.109, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.110, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.111, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.112, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.113, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.114, i32 0, i32 0)], align 16
@.str.92 = private unnamed_addr constant [4 x i8] c"<<=\00", align 1
@.str.93 = private unnamed_addr constant [4 x i8] c">>=\00", align 1
@.str.94 = private unnamed_addr constant [4 x i8] c"...\00", align 1
@.str.95 = private unnamed_addr constant [3 x i8] c"==\00", align 1
@.str.96 = private unnamed_addr constant [3 x i8] c"!=\00", align 1
@.str.97 = private unnamed_addr constant [3 x i8] c"<=\00", align 1
@.str.98 = private unnamed_addr constant [3 x i8] c">=\00", align 1
@.str.99 = private unnamed_addr constant [3 x i8] c"->\00", align 1
@.str.100 = private unnamed_addr constant [3 x i8] c"+=\00", align 1
@.str.101 = private unnamed_addr constant [3 x i8] c"-=\00", align 1
@.str.102 = private unnamed_addr constant [3 x i8] c"*=\00", align 1
@.str.103 = private unnamed_addr constant [3 x i8] c"/=\00", align 1
@.str.104 = private unnamed_addr constant [3 x i8] c"++\00", align 1
@.str.105 = private unnamed_addr constant [3 x i8] c"--\00", align 1
@.str.106 = private unnamed_addr constant [3 x i8] c"%=\00", align 1
@.str.107 = private unnamed_addr constant [3 x i8] c"&=\00", align 1
@.str.108 = private unnamed_addr constant [3 x i8] c"|=\00", align 1
@.str.109 = private unnamed_addr constant [3 x i8] c"^=\00", align 1
@.str.110 = private unnamed_addr constant [3 x i8] c"&&\00", align 1
@.str.111 = private unnamed_addr constant [3 x i8] c"||\00", align 1
@.str.112 = private unnamed_addr constant [3 x i8] c"<<\00", align 1
@.str.113 = private unnamed_addr constant [3 x i8] c">>\00", align 1
@.str.114 = private unnamed_addr constant [3 x i8] c"##\00", align 1
@.str.115 = private unnamed_addr constant [2 x i8] c"-\00", align 1
@stdin = external global %struct._IO_FILE*, align 8
@.str.116 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.117 = private unnamed_addr constant [3 x i8] c"\\u\00", align 1
@.str.118 = private unnamed_addr constant [3 x i8] c"\\U\00", align 1

; Function Attrs: noinline noreturn nounwind optnone uwtable
define dso_local void @error(i8* noundef %0, ...) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca [1 x %struct.__va_list_tag], align 16
  store i8* %0, i8** %2, align 8
  %4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %5 = bitcast %struct.__va_list_tag* %4 to i8*
  call void @llvm.va_start(i8* %5)
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %7 = load i8*, i8** %2, align 8
  %8 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %9 = call i32 @vfprintf(%struct._IO_FILE* noundef %6, i8* noundef %7, %struct.__va_list_tag* noundef %8)
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %11 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %10, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i64 0, i64 0))
  %12 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %13 = bitcast %struct.__va_list_tag* %12 to i8*
  call void @llvm.va_end(i8* %13)
  call void @exit(i32 noundef 9) #9
  unreachable
}

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.va_start(i8*) #1

declare i32 @vfprintf(%struct._IO_FILE* noundef, i8* noundef, %struct.__va_list_tag* noundef) #2

declare i32 @fprintf(%struct._IO_FILE* noundef, i8* noundef, ...) #2

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.va_end(i8*) #1

; Function Attrs: noreturn nounwind
declare void @exit(i32 noundef) #3

; Function Attrs: noinline noreturn nounwind optnone uwtable
define dso_local void @error_at(i8* noundef %0, i8* noundef %1, ...) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i8*, align 8
  %7 = alloca [1 x %struct.__va_list_tag], align 16
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  store i32 1, i32* %5, align 4
  %8 = load %struct.File*, %struct.File** @current_file, align 8
  %9 = getelementptr inbounds %struct.File, %struct.File* %8, i32 0, i32 2
  %10 = load i8*, i8** %9, align 8
  store i8* %10, i8** %6, align 8
  br label %11

11:                                               ; preds = %24, %2
  %12 = load i8*, i8** %6, align 8
  %13 = load i8*, i8** %3, align 8
  %14 = icmp ult i8* %12, %13
  br i1 %14, label %15, label %27

15:                                               ; preds = %11
  %16 = load i8*, i8** %6, align 8
  %17 = load i8, i8* %16, align 1
  %18 = sext i8 %17 to i32
  %19 = icmp eq i32 %18, 10
  br i1 %19, label %20, label %23

20:                                               ; preds = %15
  %21 = load i32, i32* %5, align 4
  %22 = add nsw i32 %21, 1
  store i32 %22, i32* %5, align 4
  br label %23

23:                                               ; preds = %20, %15
  br label %24

24:                                               ; preds = %23
  %25 = load i8*, i8** %6, align 8
  %26 = getelementptr inbounds i8, i8* %25, i32 1
  store i8* %26, i8** %6, align 8
  br label %11, !llvm.loop !6

27:                                               ; preds = %11
  %28 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i64 0, i64 0
  %29 = bitcast %struct.__va_list_tag* %28 to i8*
  call void @llvm.va_start(i8* %29)
  %30 = load %struct.File*, %struct.File** @current_file, align 8
  %31 = getelementptr inbounds %struct.File, %struct.File* %30, i32 0, i32 0
  %32 = load i8*, i8** %31, align 8
  %33 = load %struct.File*, %struct.File** @current_file, align 8
  %34 = getelementptr inbounds %struct.File, %struct.File* %33, i32 0, i32 2
  %35 = load i8*, i8** %34, align 8
  %36 = load i32, i32* %5, align 4
  %37 = load i8*, i8** %3, align 8
  %38 = load i8*, i8** %4, align 8
  %39 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i64 0, i64 0
  call void @verror_at(i8* noundef %32, i8* noundef %35, i32 noundef %36, i8* noundef %37, i8* noundef %38, %struct.__va_list_tag* noundef %39)
  %40 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i64 0, i64 0
  %41 = bitcast %struct.__va_list_tag* %40 to i8*
  call void @llvm.va_end(i8* %41)
  call void @exit(i32 noundef 8) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @verror_at(i8* noundef %0, i8* noundef %1, i32 noundef %2, i8* noundef %3, i8* noundef %4, %struct.__va_list_tag* noundef %5) #4 {
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  %10 = alloca i8*, align 8
  %11 = alloca i8*, align 8
  %12 = alloca %struct.__va_list_tag*, align 8
  %13 = alloca i8*, align 8
  %14 = alloca i8*, align 8
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  store i8* %0, i8** %7, align 8
  store i8* %1, i8** %8, align 8
  store i32 %2, i32* %9, align 4
  store i8* %3, i8** %10, align 8
  store i8* %4, i8** %11, align 8
  store %struct.__va_list_tag* %5, %struct.__va_list_tag** %12, align 8
  %17 = load i8*, i8** %10, align 8
  store i8* %17, i8** %13, align 8
  br label %18

18:                                               ; preds = %30, %6
  %19 = load i8*, i8** %8, align 8
  %20 = load i8*, i8** %13, align 8
  %21 = icmp ult i8* %19, %20
  br i1 %21, label %22, label %28

22:                                               ; preds = %18
  %23 = load i8*, i8** %13, align 8
  %24 = getelementptr inbounds i8, i8* %23, i64 -1
  %25 = load i8, i8* %24, align 1
  %26 = sext i8 %25 to i32
  %27 = icmp ne i32 %26, 10
  br label %28

28:                                               ; preds = %22, %18
  %29 = phi i1 [ false, %18 ], [ %27, %22 ]
  br i1 %29, label %30, label %33

30:                                               ; preds = %28
  %31 = load i8*, i8** %13, align 8
  %32 = getelementptr inbounds i8, i8* %31, i32 -1
  store i8* %32, i8** %13, align 8
  br label %18, !llvm.loop !8

33:                                               ; preds = %28
  %34 = load i8*, i8** %10, align 8
  store i8* %34, i8** %14, align 8
  br label %35

35:                                               ; preds = %47, %33
  %36 = load i8*, i8** %14, align 8
  %37 = load i8, i8* %36, align 1
  %38 = sext i8 %37 to i32
  %39 = icmp ne i32 %38, 0
  br i1 %39, label %40, label %45

40:                                               ; preds = %35
  %41 = load i8*, i8** %14, align 8
  %42 = load i8, i8* %41, align 1
  %43 = sext i8 %42 to i32
  %44 = icmp ne i32 %43, 10
  br label %45

45:                                               ; preds = %40, %35
  %46 = phi i1 [ false, %35 ], [ %44, %40 ]
  br i1 %46, label %47, label %50

47:                                               ; preds = %45
  %48 = load i8*, i8** %14, align 8
  %49 = getelementptr inbounds i8, i8* %48, i32 1
  store i8* %49, i8** %14, align 8
  br label %35, !llvm.loop !9

50:                                               ; preds = %45
  %51 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %52 = load i8*, i8** %7, align 8
  %53 = load i32, i32* %9, align 4
  %54 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %51, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.20, i64 0, i64 0), i8* noundef %52, i32 noundef %53)
  store i32 %54, i32* %15, align 4
  %55 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %56 = load i8*, i8** %14, align 8
  %57 = load i8*, i8** %13, align 8
  %58 = ptrtoint i8* %56 to i64
  %59 = ptrtoint i8* %57 to i64
  %60 = sub i64 %58, %59
  %61 = trunc i64 %60 to i32
  %62 = load i8*, i8** %13, align 8
  %63 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %55, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.21, i64 0, i64 0), i32 noundef %61, i8* noundef %62)
  %64 = load i8*, i8** %13, align 8
  %65 = load i8*, i8** %10, align 8
  %66 = load i8*, i8** %13, align 8
  %67 = ptrtoint i8* %65 to i64
  %68 = ptrtoint i8* %66 to i64
  %69 = sub i64 %67, %68
  %70 = trunc i64 %69 to i32
  %71 = call i32 @display_width(i8* noundef %64, i32 noundef %70)
  %72 = load i32, i32* %15, align 4
  %73 = add nsw i32 %71, %72
  store i32 %73, i32* %16, align 4
  %74 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %75 = load i32, i32* %16, align 4
  %76 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %74, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.22, i64 0, i64 0), i32 noundef %75, i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.23, i64 0, i64 0))
  %77 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %78 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %77, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.24, i64 0, i64 0))
  %79 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %80 = load i8*, i8** %11, align 8
  %81 = load %struct.__va_list_tag*, %struct.__va_list_tag** %12, align 8
  %82 = call i32 @vfprintf(%struct._IO_FILE* noundef %79, i8* noundef %80, %struct.__va_list_tag* noundef %81)
  %83 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %84 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %83, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i64 0, i64 0))
  ret void
}

; Function Attrs: noinline noreturn nounwind optnone uwtable
define dso_local void @error_tok(%struct.Token* noundef %0, i8* noundef %1, ...) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca [1 x %struct.__va_list_tag], align 16
  store %struct.Token* %0, %struct.Token** %3, align 8
  store i8* %1, i8** %4, align 8
  %6 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  %7 = bitcast %struct.__va_list_tag* %6 to i8*
  call void @llvm.va_start(i8* %7)
  %8 = load %struct.Token*, %struct.Token** %3, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 8
  %10 = load %struct.File*, %struct.File** %9, align 16
  %11 = getelementptr inbounds %struct.File, %struct.File* %10, i32 0, i32 0
  %12 = load i8*, i8** %11, align 8
  %13 = load %struct.Token*, %struct.Token** %3, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 8
  %15 = load %struct.File*, %struct.File** %14, align 16
  %16 = getelementptr inbounds %struct.File, %struct.File* %15, i32 0, i32 2
  %17 = load i8*, i8** %16, align 8
  %18 = load %struct.Token*, %struct.Token** %3, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 10
  %20 = load i32, i32* %19, align 16
  %21 = load %struct.Token*, %struct.Token** %3, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 4
  %23 = load i8*, i8** %22, align 16
  %24 = load i8*, i8** %4, align 8
  %25 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  call void @verror_at(i8* noundef %12, i8* noundef %17, i32 noundef %20, i8* noundef %23, i8* noundef %24, %struct.__va_list_tag* noundef %25)
  %26 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  %27 = bitcast %struct.__va_list_tag* %26 to i8*
  call void @llvm.va_end(i8* %27)
  call void @exit(i32 noundef 7) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @warn_tok(%struct.Token* noundef %0, i8* noundef %1, ...) #4 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca [1 x %struct.__va_list_tag], align 16
  store %struct.Token* %0, %struct.Token** %3, align 8
  store i8* %1, i8** %4, align 8
  %6 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  %7 = bitcast %struct.__va_list_tag* %6 to i8*
  call void @llvm.va_start(i8* %7)
  %8 = load %struct.Token*, %struct.Token** %3, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 8
  %10 = load %struct.File*, %struct.File** %9, align 16
  %11 = getelementptr inbounds %struct.File, %struct.File* %10, i32 0, i32 0
  %12 = load i8*, i8** %11, align 8
  %13 = load %struct.Token*, %struct.Token** %3, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 8
  %15 = load %struct.File*, %struct.File** %14, align 16
  %16 = getelementptr inbounds %struct.File, %struct.File* %15, i32 0, i32 2
  %17 = load i8*, i8** %16, align 8
  %18 = load %struct.Token*, %struct.Token** %3, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 10
  %20 = load i32, i32* %19, align 16
  %21 = load %struct.Token*, %struct.Token** %3, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 4
  %23 = load i8*, i8** %22, align 16
  %24 = load i8*, i8** %4, align 8
  %25 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  call void @verror_at(i8* noundef %12, i8* noundef %17, i32 noundef %20, i8* noundef %23, i8* noundef %24, %struct.__va_list_tag* noundef %25)
  %26 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  %27 = bitcast %struct.__va_list_tag* %26 to i8*
  call void @llvm.va_end(i8* %27)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @equal(%struct.Token* noundef %0, i8* noundef %1) #4 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i8*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %struct.Token*, %struct.Token** %3, align 8
  %6 = getelementptr inbounds %struct.Token, %struct.Token* %5, i32 0, i32 4
  %7 = load i8*, i8** %6, align 16
  %8 = load i8*, i8** %4, align 8
  %9 = load %struct.Token*, %struct.Token** %3, align 8
  %10 = getelementptr inbounds %struct.Token, %struct.Token* %9, i32 0, i32 5
  %11 = load i32, i32* %10, align 8
  %12 = sext i32 %11 to i64
  %13 = call i32 @strncmp(i8* noundef %7, i8* noundef %8, i64 noundef %12) #10
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %15, label %25

15:                                               ; preds = %2
  %16 = load i8*, i8** %4, align 8
  %17 = load %struct.Token*, %struct.Token** %3, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 5
  %19 = load i32, i32* %18, align 8
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds i8, i8* %16, i64 %20
  %22 = load i8, i8* %21, align 1
  %23 = sext i8 %22 to i32
  %24 = icmp eq i32 %23, 0
  br label %25

25:                                               ; preds = %15, %2
  %26 = phi i1 [ false, %2 ], [ %24, %15 ]
  ret i1 %26
}

; Function Attrs: nounwind readonly willreturn
declare i32 @strncmp(i8* noundef, i8* noundef, i64 noundef) #5

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Token* @skip(%struct.Token* noundef %0, i8* noundef %1) #4 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i8*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %struct.Token*, %struct.Token** %3, align 8
  %6 = load i8*, i8** %4, align 8
  %7 = call zeroext i1 @equal(%struct.Token* noundef %5, i8* noundef %6)
  br i1 %7, label %11, label %8

8:                                                ; preds = %2
  %9 = load %struct.Token*, %struct.Token** %3, align 8
  %10 = load i8*, i8** %4, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0), i8* noundef %10) #11
  unreachable

11:                                               ; preds = %2
  %12 = load %struct.Token*, %struct.Token** %3, align 8
  %13 = getelementptr inbounds %struct.Token, %struct.Token* %12, i32 0, i32 1
  %14 = load %struct.Token*, %struct.Token** %13, align 8
  ret %struct.Token* %14
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @consume(%struct.Token** noundef %0, %struct.Token* noundef %1, i8* noundef %2) #4 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca i8*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store i8* %2, i8** %7, align 8
  %8 = load %struct.Token*, %struct.Token** %6, align 8
  %9 = load i8*, i8** %7, align 8
  %10 = call zeroext i1 @equal(%struct.Token* noundef %8, i8* noundef %9)
  br i1 %10, label %11, label %16

11:                                               ; preds = %3
  %12 = load %struct.Token*, %struct.Token** %6, align 8
  %13 = getelementptr inbounds %struct.Token, %struct.Token* %12, i32 0, i32 1
  %14 = load %struct.Token*, %struct.Token** %13, align 8
  %15 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %14, %struct.Token** %15, align 8
  store i1 true, i1* %4, align 1
  br label %19

16:                                               ; preds = %3
  %17 = load %struct.Token*, %struct.Token** %6, align 8
  %18 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %17, %struct.Token** %18, align 8
  store i1 false, i1* %4, align 1
  br label %19

19:                                               ; preds = %16, %11
  %20 = load i1, i1* %4, align 1
  ret i1 %20
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @startswith(i8* noundef %0, i8* noundef %1) #4 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load i8*, i8** %3, align 8
  %6 = load i8*, i8** %4, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = call i64 @strlen(i8* noundef %7) #10
  %9 = call i32 @strncmp(i8* noundef %5, i8* noundef %6, i64 noundef %8) #10
  %10 = icmp eq i32 %9, 0
  ret i1 %10
}

; Function Attrs: nounwind readonly willreturn
declare i64 @strlen(i8* noundef) #5

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @convert_pp_tokens(%struct.Token* noundef %0) #4 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %4 = load %struct.Token*, %struct.Token** %2, align 8
  store %struct.Token* %4, %struct.Token** %3, align 8
  br label %5

5:                                                ; preds = %25, %1
  %6 = load %struct.Token*, %struct.Token** %3, align 8
  %7 = getelementptr inbounds %struct.Token, %struct.Token* %6, i32 0, i32 0
  %8 = load i32, i32* %7, align 16
  %9 = icmp ne i32 %8, 6
  br i1 %9, label %10, label %29

10:                                               ; preds = %5
  %11 = load %struct.Token*, %struct.Token** %3, align 8
  %12 = call zeroext i1 @is_keyword(%struct.Token* noundef %11)
  br i1 %12, label %13, label %16

13:                                               ; preds = %10
  %14 = load %struct.Token*, %struct.Token** %3, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 0
  store i32 2, i32* %15, align 16
  br label %24

16:                                               ; preds = %10
  %17 = load %struct.Token*, %struct.Token** %3, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 0
  %19 = load i32, i32* %18, align 16
  %20 = icmp eq i32 %19, 5
  br i1 %20, label %21, label %23

21:                                               ; preds = %16
  %22 = load %struct.Token*, %struct.Token** %3, align 8
  call void @convert_pp_number(%struct.Token* noundef %22)
  br label %23

23:                                               ; preds = %21, %16
  br label %24

24:                                               ; preds = %23, %13
  br label %25

25:                                               ; preds = %24
  %26 = load %struct.Token*, %struct.Token** %3, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  store %struct.Token* %28, %struct.Token** %3, align 8
  br label %5, !llvm.loop !10

29:                                               ; preds = %5
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @is_keyword(%struct.Token* noundef %0) #4 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca i32, align 4
  store %struct.Token* %0, %struct.Token** %2, align 8
  %4 = load i32, i32* getelementptr inbounds (%struct.HashMap, %struct.HashMap* @is_keyword.map, i32 0, i32 1), align 8
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %6, label %20

6:                                                ; preds = %1
  store i32 0, i32* %3, align 4
  br label %7

7:                                                ; preds = %16, %6
  %8 = load i32, i32* %3, align 4
  %9 = sext i32 %8 to i64
  %10 = icmp ult i64 %9, 45
  br i1 %10, label %11, label %19

11:                                               ; preds = %7
  %12 = load i32, i32* %3, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [45 x i8*], [45 x i8*]* @is_keyword.kw, i64 0, i64 %13
  %15 = load i8*, i8** %14, align 8
  call void @hashmap_put(%struct.HashMap* noundef @is_keyword.map, i8* noundef %15, i8* noundef inttoptr (i64 1 to i8*))
  br label %16

16:                                               ; preds = %11
  %17 = load i32, i32* %3, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, i32* %3, align 4
  br label %7, !llvm.loop !11

19:                                               ; preds = %7
  br label %20

20:                                               ; preds = %19, %1
  %21 = load %struct.Token*, %struct.Token** %2, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 4
  %23 = load i8*, i8** %22, align 16
  %24 = load %struct.Token*, %struct.Token** %2, align 8
  %25 = getelementptr inbounds %struct.Token, %struct.Token* %24, i32 0, i32 5
  %26 = load i32, i32* %25, align 8
  %27 = call i8* @hashmap_get2(%struct.HashMap* noundef @is_keyword.map, i8* noundef %23, i32 noundef %26)
  %28 = icmp ne i8* %27, null
  ret i1 %28
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @convert_pp_number(%struct.Token* noundef %0) #4 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca x86_fp80, align 16
  %5 = alloca %struct.Type*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %6 = load %struct.Token*, %struct.Token** %2, align 8
  %7 = call zeroext i1 @convert_pp_int(%struct.Token* noundef %6)
  br i1 %7, label %8, label %9

8:                                                ; preds = %1
  br label %66

9:                                                ; preds = %1
  %10 = load %struct.Token*, %struct.Token** %2, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 4
  %12 = load i8*, i8** %11, align 16
  %13 = call x86_fp80 @strtold(i8* noundef %12, i8** noundef %3) #12
  store x86_fp80 %13, x86_fp80* %4, align 16
  %14 = load i8*, i8** %3, align 8
  %15 = load i8, i8* %14, align 1
  %16 = sext i8 %15 to i32
  %17 = icmp eq i32 %16, 102
  br i1 %17, label %23, label %18

18:                                               ; preds = %9
  %19 = load i8*, i8** %3, align 8
  %20 = load i8, i8* %19, align 1
  %21 = sext i8 %20 to i32
  %22 = icmp eq i32 %21, 70
  br i1 %22, label %23, label %27

23:                                               ; preds = %18, %9
  %24 = load %struct.Type*, %struct.Type** @ty_float, align 8
  store %struct.Type* %24, %struct.Type** %5, align 8
  %25 = load i8*, i8** %3, align 8
  %26 = getelementptr inbounds i8, i8* %25, i32 1
  store i8* %26, i8** %3, align 8
  br label %44

27:                                               ; preds = %18
  %28 = load i8*, i8** %3, align 8
  %29 = load i8, i8* %28, align 1
  %30 = sext i8 %29 to i32
  %31 = icmp eq i32 %30, 108
  br i1 %31, label %37, label %32

32:                                               ; preds = %27
  %33 = load i8*, i8** %3, align 8
  %34 = load i8, i8* %33, align 1
  %35 = sext i8 %34 to i32
  %36 = icmp eq i32 %35, 76
  br i1 %36, label %37, label %41

37:                                               ; preds = %32, %27
  %38 = load %struct.Type*, %struct.Type** @ty_ldouble, align 8
  store %struct.Type* %38, %struct.Type** %5, align 8
  %39 = load i8*, i8** %3, align 8
  %40 = getelementptr inbounds i8, i8* %39, i32 1
  store i8* %40, i8** %3, align 8
  br label %43

41:                                               ; preds = %32
  %42 = load %struct.Type*, %struct.Type** @ty_double, align 8
  store %struct.Type* %42, %struct.Type** %5, align 8
  br label %43

43:                                               ; preds = %41, %37
  br label %44

44:                                               ; preds = %43, %23
  %45 = load %struct.Token*, %struct.Token** %2, align 8
  %46 = getelementptr inbounds %struct.Token, %struct.Token* %45, i32 0, i32 4
  %47 = load i8*, i8** %46, align 16
  %48 = load %struct.Token*, %struct.Token** %2, align 8
  %49 = getelementptr inbounds %struct.Token, %struct.Token* %48, i32 0, i32 5
  %50 = load i32, i32* %49, align 8
  %51 = sext i32 %50 to i64
  %52 = getelementptr inbounds i8, i8* %47, i64 %51
  %53 = load i8*, i8** %3, align 8
  %54 = icmp ne i8* %52, %53
  br i1 %54, label %55, label %57

55:                                               ; preds = %44
  %56 = load %struct.Token*, %struct.Token** %2, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %56, i8* noundef getelementptr inbounds ([52 x i8], [52 x i8]* @.str.70, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

57:                                               ; preds = %44
  %58 = load %struct.Token*, %struct.Token** %2, align 8
  %59 = getelementptr inbounds %struct.Token, %struct.Token* %58, i32 0, i32 0
  store i32 4, i32* %59, align 16
  %60 = load x86_fp80, x86_fp80* %4, align 16
  %61 = load %struct.Token*, %struct.Token** %2, align 8
  %62 = getelementptr inbounds %struct.Token, %struct.Token* %61, i32 0, i32 3
  store x86_fp80 %60, x86_fp80* %62, align 16
  %63 = load %struct.Type*, %struct.Type** %5, align 8
  %64 = load %struct.Token*, %struct.Token** %2, align 8
  %65 = getelementptr inbounds %struct.Token, %struct.Token* %64, i32 0, i32 6
  store %struct.Type* %63, %struct.Type** %65, align 16
  br label %66

66:                                               ; preds = %57, %8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Token* @tokenize_string_literal(%struct.Token* noundef %0, %struct.Type* noundef %1) #4 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  %6 = load %struct.Type*, %struct.Type** %4, align 8
  %7 = getelementptr inbounds %struct.Type, %struct.Type* %6, i32 0, i32 1
  %8 = load i32, i32* %7, align 4
  %9 = icmp eq i32 %8, 2
  br i1 %9, label %10, label %18

10:                                               ; preds = %2
  %11 = load %struct.Token*, %struct.Token** %3, align 8
  %12 = getelementptr inbounds %struct.Token, %struct.Token* %11, i32 0, i32 4
  %13 = load i8*, i8** %12, align 16
  %14 = load %struct.Token*, %struct.Token** %3, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 4
  %16 = load i8*, i8** %15, align 16
  %17 = call %struct.Token* @read_utf16_string_literal(i8* noundef %13, i8* noundef %16)
  store %struct.Token* %17, %struct.Token** %5, align 8
  br label %27

18:                                               ; preds = %2
  %19 = load %struct.Token*, %struct.Token** %3, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 4
  %21 = load i8*, i8** %20, align 16
  %22 = load %struct.Token*, %struct.Token** %3, align 8
  %23 = getelementptr inbounds %struct.Token, %struct.Token* %22, i32 0, i32 4
  %24 = load i8*, i8** %23, align 16
  %25 = load %struct.Type*, %struct.Type** %4, align 8
  %26 = call %struct.Token* @read_utf32_string_literal(i8* noundef %21, i8* noundef %24, %struct.Type* noundef %25)
  store %struct.Token* %26, %struct.Token** %5, align 8
  br label %27

27:                                               ; preds = %18, %10
  %28 = load %struct.Token*, %struct.Token** %3, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 1
  %30 = load %struct.Token*, %struct.Token** %29, align 8
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = getelementptr inbounds %struct.Token, %struct.Token* %31, i32 0, i32 1
  store %struct.Token* %30, %struct.Token** %32, align 8
  %33 = load %struct.Token*, %struct.Token** %5, align 8
  ret %struct.Token* %33
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @read_utf16_string_literal(i8* noundef %0, i8* noundef %1) #4 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i16*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  %10 = alloca %struct.Token*, align 8
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %11 = load i8*, i8** %4, align 8
  %12 = getelementptr inbounds i8, i8* %11, i64 1
  %13 = call i8* @string_literal_end(i8* noundef %12)
  store i8* %13, i8** %5, align 8
  %14 = load i8*, i8** %5, align 8
  %15 = load i8*, i8** %3, align 8
  %16 = ptrtoint i8* %14 to i64
  %17 = ptrtoint i8* %15 to i64
  %18 = sub i64 %16, %17
  %19 = call noalias i8* @calloc(i64 noundef 2, i64 noundef %18) #12
  %20 = bitcast i8* %19 to i16*
  store i16* %20, i16** %6, align 8
  %21 = load i16*, i16** %6, align 8
  %22 = icmp eq i16* %21, null
  br i1 %22, label %23, label %24

23:                                               ; preds = %2
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([46 x i8], [46 x i8]* @.str.85, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

24:                                               ; preds = %2
  store i32 0, i32* %7, align 4
  %25 = load i8*, i8** %4, align 8
  %26 = getelementptr inbounds i8, i8* %25, i64 1
  store i8* %26, i8** %8, align 8
  br label %27

27:                                               ; preds = %81, %36, %24
  %28 = load i8*, i8** %8, align 8
  %29 = load i8*, i8** %5, align 8
  %30 = icmp ult i8* %28, %29
  br i1 %30, label %31, label %82

31:                                               ; preds = %27
  %32 = load i8*, i8** %8, align 8
  %33 = load i8, i8* %32, align 1
  %34 = sext i8 %33 to i32
  %35 = icmp eq i32 %34, 92
  br i1 %35, label %36, label %46

36:                                               ; preds = %31
  %37 = load i8*, i8** %8, align 8
  %38 = getelementptr inbounds i8, i8* %37, i64 1
  %39 = call i32 @read_escaped_char(i8** noundef %8, i8* noundef %38)
  %40 = trunc i32 %39 to i16
  %41 = load i16*, i16** %6, align 8
  %42 = load i32, i32* %7, align 4
  %43 = add nsw i32 %42, 1
  store i32 %43, i32* %7, align 4
  %44 = sext i32 %42 to i64
  %45 = getelementptr inbounds i16, i16* %41, i64 %44
  store i16 %40, i16* %45, align 2
  br label %27, !llvm.loop !12

46:                                               ; preds = %31
  %47 = load i8*, i8** %8, align 8
  %48 = call i32 @decode_utf8(i8** noundef %8, i8* noundef %47)
  store i32 %48, i32* %9, align 4
  %49 = load i32, i32* %9, align 4
  %50 = icmp ult i32 %49, 65536
  br i1 %50, label %51, label %59

51:                                               ; preds = %46
  %52 = load i32, i32* %9, align 4
  %53 = trunc i32 %52 to i16
  %54 = load i16*, i16** %6, align 8
  %55 = load i32, i32* %7, align 4
  %56 = add nsw i32 %55, 1
  store i32 %56, i32* %7, align 4
  %57 = sext i32 %55 to i64
  %58 = getelementptr inbounds i16, i16* %54, i64 %57
  store i16 %53, i16* %58, align 2
  br label %81

59:                                               ; preds = %46
  %60 = load i32, i32* %9, align 4
  %61 = sub i32 %60, 65536
  store i32 %61, i32* %9, align 4
  %62 = load i32, i32* %9, align 4
  %63 = lshr i32 %62, 10
  %64 = and i32 %63, 1023
  %65 = add i32 55296, %64
  %66 = trunc i32 %65 to i16
  %67 = load i16*, i16** %6, align 8
  %68 = load i32, i32* %7, align 4
  %69 = add nsw i32 %68, 1
  store i32 %69, i32* %7, align 4
  %70 = sext i32 %68 to i64
  %71 = getelementptr inbounds i16, i16* %67, i64 %70
  store i16 %66, i16* %71, align 2
  %72 = load i32, i32* %9, align 4
  %73 = and i32 %72, 1023
  %74 = add i32 56320, %73
  %75 = trunc i32 %74 to i16
  %76 = load i16*, i16** %6, align 8
  %77 = load i32, i32* %7, align 4
  %78 = add nsw i32 %77, 1
  store i32 %78, i32* %7, align 4
  %79 = sext i32 %77 to i64
  %80 = getelementptr inbounds i16, i16* %76, i64 %79
  store i16 %75, i16* %80, align 2
  br label %81

81:                                               ; preds = %59, %51
  br label %27, !llvm.loop !12

82:                                               ; preds = %27
  %83 = load i8*, i8** %3, align 8
  %84 = load i8*, i8** %5, align 8
  %85 = getelementptr inbounds i8, i8* %84, i64 1
  %86 = call %struct.Token* @new_token(i32 noundef 3, i8* noundef %83, i8* noundef %85)
  store %struct.Token* %86, %struct.Token** %10, align 8
  %87 = load %struct.Type*, %struct.Type** @ty_ushort, align 8
  %88 = load i32, i32* %7, align 4
  %89 = add nsw i32 %88, 1
  %90 = call %struct.Type* @array_of(%struct.Type* noundef %87, i32 noundef %89)
  %91 = load %struct.Token*, %struct.Token** %10, align 8
  %92 = getelementptr inbounds %struct.Token, %struct.Token* %91, i32 0, i32 6
  store %struct.Type* %90, %struct.Type** %92, align 16
  %93 = load i16*, i16** %6, align 8
  %94 = bitcast i16* %93 to i8*
  %95 = load %struct.Token*, %struct.Token** %10, align 8
  %96 = getelementptr inbounds %struct.Token, %struct.Token* %95, i32 0, i32 7
  store i8* %94, i8** %96, align 8
  %97 = load %struct.Token*, %struct.Token** %10, align 8
  ret %struct.Token* %97
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @read_utf32_string_literal(i8* noundef %0, i8* noundef %1, %struct.Type* noundef %2) #4 {
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i32*, align 8
  %9 = alloca i32, align 4
  %10 = alloca i8*, align 8
  %11 = alloca %struct.Token*, align 8
  store i8* %0, i8** %4, align 8
  store i8* %1, i8** %5, align 8
  store %struct.Type* %2, %struct.Type** %6, align 8
  %12 = load i8*, i8** %5, align 8
  %13 = getelementptr inbounds i8, i8* %12, i64 1
  %14 = call i8* @string_literal_end(i8* noundef %13)
  store i8* %14, i8** %7, align 8
  %15 = load i8*, i8** %7, align 8
  %16 = load i8*, i8** %5, align 8
  %17 = ptrtoint i8* %15 to i64
  %18 = ptrtoint i8* %16 to i64
  %19 = sub i64 %17, %18
  %20 = call noalias i8* @calloc(i64 noundef 4, i64 noundef %19) #12
  %21 = bitcast i8* %20 to i32*
  store i32* %21, i32** %8, align 8
  %22 = load i32*, i32** %8, align 8
  %23 = icmp eq i32* %22, null
  br i1 %23, label %24, label %25

24:                                               ; preds = %3
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([46 x i8], [46 x i8]* @.str.88, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

25:                                               ; preds = %3
  store i32 0, i32* %9, align 4
  %26 = load i8*, i8** %5, align 8
  %27 = getelementptr inbounds i8, i8* %26, i64 1
  store i8* %27, i8** %10, align 8
  br label %28

28:                                               ; preds = %54, %25
  %29 = load i8*, i8** %10, align 8
  %30 = load i8*, i8** %7, align 8
  %31 = icmp ult i8* %29, %30
  br i1 %31, label %32, label %55

32:                                               ; preds = %28
  %33 = load i8*, i8** %10, align 8
  %34 = load i8, i8* %33, align 1
  %35 = sext i8 %34 to i32
  %36 = icmp eq i32 %35, 92
  br i1 %36, label %37, label %46

37:                                               ; preds = %32
  %38 = load i8*, i8** %10, align 8
  %39 = getelementptr inbounds i8, i8* %38, i64 1
  %40 = call i32 @read_escaped_char(i8** noundef %10, i8* noundef %39)
  %41 = load i32*, i32** %8, align 8
  %42 = load i32, i32* %9, align 4
  %43 = add nsw i32 %42, 1
  store i32 %43, i32* %9, align 4
  %44 = sext i32 %42 to i64
  %45 = getelementptr inbounds i32, i32* %41, i64 %44
  store i32 %40, i32* %45, align 4
  br label %54

46:                                               ; preds = %32
  %47 = load i8*, i8** %10, align 8
  %48 = call i32 @decode_utf8(i8** noundef %10, i8* noundef %47)
  %49 = load i32*, i32** %8, align 8
  %50 = load i32, i32* %9, align 4
  %51 = add nsw i32 %50, 1
  store i32 %51, i32* %9, align 4
  %52 = sext i32 %50 to i64
  %53 = getelementptr inbounds i32, i32* %49, i64 %52
  store i32 %48, i32* %53, align 4
  br label %54

54:                                               ; preds = %46, %37
  br label %28, !llvm.loop !13

55:                                               ; preds = %28
  %56 = load i8*, i8** %4, align 8
  %57 = load i8*, i8** %7, align 8
  %58 = getelementptr inbounds i8, i8* %57, i64 1
  %59 = call %struct.Token* @new_token(i32 noundef 3, i8* noundef %56, i8* noundef %58)
  store %struct.Token* %59, %struct.Token** %11, align 8
  %60 = load %struct.Type*, %struct.Type** %6, align 8
  %61 = load i32, i32* %9, align 4
  %62 = add nsw i32 %61, 1
  %63 = call %struct.Type* @array_of(%struct.Type* noundef %60, i32 noundef %62)
  %64 = load %struct.Token*, %struct.Token** %11, align 8
  %65 = getelementptr inbounds %struct.Token, %struct.Token* %64, i32 0, i32 6
  store %struct.Type* %63, %struct.Type** %65, align 16
  %66 = load i32*, i32** %8, align 8
  %67 = bitcast i32* %66 to i8*
  %68 = load %struct.Token*, %struct.Token** %11, align 8
  %69 = getelementptr inbounds %struct.Token, %struct.Token* %68, i32 0, i32 7
  store i8* %67, i8** %69, align 8
  %70 = load %struct.Token*, %struct.Token** %11, align 8
  ret %struct.Token* %70
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Token* @tokenize(%struct.File* noundef %0) #4 {
  %2 = alloca %struct.File*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct.Token, align 16
  %5 = alloca %struct.Token*, align 8
  %6 = alloca i8, align 1
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  store %struct.File* %0, %struct.File** %2, align 8
  %13 = load %struct.File*, %struct.File** %2, align 8
  store %struct.File* %13, %struct.File** @current_file, align 8
  %14 = load %struct.File*, %struct.File** %2, align 8
  %15 = getelementptr inbounds %struct.File, %struct.File* %14, i32 0, i32 2
  %16 = load i8*, i8** %15, align 8
  store i8* %16, i8** %3, align 8
  %17 = bitcast %struct.Token* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %17, i8 0, i64 128, i1 false)
  store %struct.Token* %4, %struct.Token** %5, align 8
  store i8 0, i8* %6, align 1
  store i8 1, i8* @at_bol, align 1
  store i8 0, i8* @has_space, align 1
  br label %18

18:                                               ; preds = %372, %352, %330, %313, %292, %269, %250, %233, %217, %201, %186, %172, %71, %56, %48, %36, %1
  %19 = load i8*, i8** %3, align 8
  %20 = load i8, i8* %19, align 1
  %21 = icmp ne i8 %20, 0
  br i1 %21, label %22, label %389

22:                                               ; preds = %18
  %23 = load i8*, i8** %3, align 8
  %24 = call zeroext i1 @startswith(i8* noundef %23, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i64 0, i64 0))
  br i1 %24, label %25, label %37

25:                                               ; preds = %22
  %26 = load i8*, i8** %3, align 8
  %27 = getelementptr inbounds i8, i8* %26, i64 2
  store i8* %27, i8** %3, align 8
  br label %28

28:                                               ; preds = %33, %25
  %29 = load i8*, i8** %3, align 8
  %30 = load i8, i8* %29, align 1
  %31 = sext i8 %30 to i32
  %32 = icmp ne i32 %31, 10
  br i1 %32, label %33, label %36

33:                                               ; preds = %28
  %34 = load i8*, i8** %3, align 8
  %35 = getelementptr inbounds i8, i8* %34, i32 1
  store i8* %35, i8** %3, align 8
  br label %28, !llvm.loop !14

36:                                               ; preds = %28
  store i8 1, i8* @has_space, align 1
  br label %18, !llvm.loop !15

37:                                               ; preds = %22
  %38 = load i8*, i8** %3, align 8
  %39 = call zeroext i1 @startswith(i8* noundef %38, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i64 0, i64 0))
  br i1 %39, label %40, label %51

40:                                               ; preds = %37
  %41 = load i8*, i8** %3, align 8
  %42 = getelementptr inbounds i8, i8* %41, i64 2
  %43 = call i8* @strstr(i8* noundef %42, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.5, i64 0, i64 0)) #10
  store i8* %43, i8** %7, align 8
  %44 = load i8*, i8** %7, align 8
  %45 = icmp ne i8* %44, null
  br i1 %45, label %48, label %46

46:                                               ; preds = %40
  %47 = load i8*, i8** %3, align 8
  call void (i8*, i8*, ...) @error_at(i8* noundef %47, i8* noundef getelementptr inbounds ([41 x i8], [41 x i8]* @.str.6, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

48:                                               ; preds = %40
  %49 = load i8*, i8** %7, align 8
  %50 = getelementptr inbounds i8, i8* %49, i64 2
  store i8* %50, i8** %3, align 8
  store i8 1, i8* @has_space, align 1
  br label %18, !llvm.loop !15

51:                                               ; preds = %37
  %52 = load i8*, i8** %3, align 8
  %53 = load i8, i8* %52, align 1
  %54 = sext i8 %53 to i32
  %55 = icmp eq i32 %54, 10
  br i1 %55, label %56, label %59

56:                                               ; preds = %51
  %57 = load i8*, i8** %3, align 8
  %58 = getelementptr inbounds i8, i8* %57, i32 1
  store i8* %58, i8** %3, align 8
  store i8 1, i8* @at_bol, align 1
  store i8 0, i8* @has_space, align 1
  br label %18, !llvm.loop !15

59:                                               ; preds = %51
  %60 = call i16** @__ctype_b_loc() #13
  %61 = load i16*, i16** %60, align 8
  %62 = load i8*, i8** %3, align 8
  %63 = load i8, i8* %62, align 1
  %64 = sext i8 %63 to i32
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds i16, i16* %61, i64 %65
  %67 = load i16, i16* %66, align 2
  %68 = zext i16 %67 to i32
  %69 = and i32 %68, 8192
  %70 = icmp ne i32 %69, 0
  br i1 %70, label %71, label %74

71:                                               ; preds = %59
  %72 = load i8*, i8** %3, align 8
  %73 = getelementptr inbounds i8, i8* %72, i32 1
  store i8* %73, i8** %3, align 8
  store i8 1, i8* @has_space, align 1
  br label %18, !llvm.loop !15

74:                                               ; preds = %59
  %75 = load i8*, i8** %3, align 8
  %76 = getelementptr inbounds i8, i8* %75, i64 -1
  store i8* %76, i8** %8, align 8
  %77 = load i8*, i8** %3, align 8
  store i8* %77, i8** %9, align 8
  %78 = call i16** @__ctype_b_loc() #13
  %79 = load i16*, i16** %78, align 8
  %80 = load i8*, i8** %3, align 8
  %81 = load i8, i8* %80, align 1
  %82 = sext i8 %81 to i32
  %83 = sext i32 %82 to i64
  %84 = getelementptr inbounds i16, i16* %79, i64 %83
  %85 = load i16, i16* %84, align 2
  %86 = zext i16 %85 to i32
  %87 = and i32 %86, 2048
  %88 = icmp ne i32 %87, 0
  br i1 %88, label %107, label %89

89:                                               ; preds = %74
  %90 = load i8*, i8** %3, align 8
  %91 = load i8, i8* %90, align 1
  %92 = sext i8 %91 to i32
  %93 = icmp eq i32 %92, 46
  br i1 %93, label %94, label %181

94:                                               ; preds = %89
  %95 = call i16** @__ctype_b_loc() #13
  %96 = load i16*, i16** %95, align 8
  %97 = load i8*, i8** %3, align 8
  %98 = getelementptr inbounds i8, i8* %97, i64 1
  %99 = load i8, i8* %98, align 1
  %100 = sext i8 %99 to i32
  %101 = sext i32 %100 to i64
  %102 = getelementptr inbounds i16, i16* %96, i64 %101
  %103 = load i16, i16* %102, align 2
  %104 = zext i16 %103 to i32
  %105 = and i32 %104, 2048
  %106 = icmp ne i32 %105, 0
  br i1 %106, label %107, label %181

107:                                              ; preds = %94, %74
  %108 = load i8*, i8** %8, align 8
  %109 = load i8, i8* %108, align 1
  %110 = sext i8 %109 to i32
  %111 = icmp ne i32 %110, 35
  br i1 %111, label %112, label %181

112:                                              ; preds = %107
  %113 = load i8*, i8** %3, align 8
  %114 = getelementptr inbounds i8, i8* %113, i32 1
  store i8* %114, i8** %3, align 8
  store i8* %113, i8** %10, align 8
  br label %115

115:                                              ; preds = %166, %112
  %116 = load i8*, i8** %3, align 8
  %117 = getelementptr inbounds i8, i8* %116, i64 0
  %118 = load i8, i8* %117, align 1
  %119 = sext i8 %118 to i32
  %120 = icmp ne i32 %119, 0
  br i1 %120, label %121, label %144

121:                                              ; preds = %115
  %122 = load i8*, i8** %3, align 8
  %123 = getelementptr inbounds i8, i8* %122, i64 1
  %124 = load i8, i8* %123, align 1
  %125 = sext i8 %124 to i32
  %126 = icmp ne i32 %125, 0
  br i1 %126, label %127, label %144

127:                                              ; preds = %121
  %128 = load i8*, i8** %3, align 8
  %129 = getelementptr inbounds i8, i8* %128, i64 0
  %130 = load i8, i8* %129, align 1
  %131 = sext i8 %130 to i32
  %132 = call i8* @strchr(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i64 0, i64 0), i32 noundef %131) #10
  %133 = icmp ne i8* %132, null
  br i1 %133, label %134, label %144

134:                                              ; preds = %127
  %135 = load i8*, i8** %3, align 8
  %136 = getelementptr inbounds i8, i8* %135, i64 1
  %137 = load i8, i8* %136, align 1
  %138 = sext i8 %137 to i32
  %139 = call i8* @strchr(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.8, i64 0, i64 0), i32 noundef %138) #10
  %140 = icmp ne i8* %139, null
  br i1 %140, label %141, label %144

141:                                              ; preds = %134
  %142 = load i8*, i8** %3, align 8
  %143 = getelementptr inbounds i8, i8* %142, i64 2
  store i8* %143, i8** %3, align 8
  br label %166

144:                                              ; preds = %134, %127, %121, %115
  %145 = call i16** @__ctype_b_loc() #13
  %146 = load i16*, i16** %145, align 8
  %147 = load i8*, i8** %3, align 8
  %148 = load i8, i8* %147, align 1
  %149 = sext i8 %148 to i32
  %150 = sext i32 %149 to i64
  %151 = getelementptr inbounds i16, i16* %146, i64 %150
  %152 = load i16, i16* %151, align 2
  %153 = zext i16 %152 to i32
  %154 = and i32 %153, 8
  %155 = icmp ne i32 %154, 0
  br i1 %155, label %161, label %156

156:                                              ; preds = %144
  %157 = load i8*, i8** %3, align 8
  %158 = load i8, i8* %157, align 1
  %159 = sext i8 %158 to i32
  %160 = icmp eq i32 %159, 46
  br i1 %160, label %161, label %164

161:                                              ; preds = %156, %144
  %162 = load i8*, i8** %3, align 8
  %163 = getelementptr inbounds i8, i8* %162, i32 1
  store i8* %163, i8** %3, align 8
  br label %165

164:                                              ; preds = %156
  br label %167

165:                                              ; preds = %161
  br label %166

166:                                              ; preds = %165, %141
  br label %115

167:                                              ; preds = %164
  %168 = load i8*, i8** %3, align 8
  %169 = load i8, i8* %168, align 1
  %170 = sext i8 %169 to i32
  %171 = icmp ne i32 %170, 95
  br i1 %171, label %172, label %178

172:                                              ; preds = %167
  %173 = load i8*, i8** %10, align 8
  %174 = load i8*, i8** %3, align 8
  %175 = call %struct.Token* @new_token(i32 noundef 5, i8* noundef %173, i8* noundef %174)
  %176 = load %struct.Token*, %struct.Token** %5, align 8
  %177 = getelementptr inbounds %struct.Token, %struct.Token* %176, i32 0, i32 1
  store %struct.Token* %175, %struct.Token** %177, align 8
  store %struct.Token* %175, %struct.Token** %5, align 8
  br label %18, !llvm.loop !15

178:                                              ; preds = %167
  %179 = load i8*, i8** %9, align 8
  store i8* %179, i8** %3, align 8
  store i8 1, i8* %6, align 1
  br label %180

180:                                              ; preds = %178
  br label %181

181:                                              ; preds = %180, %107, %94, %89
  %182 = load i8*, i8** %3, align 8
  %183 = load i8, i8* %182, align 1
  %184 = sext i8 %183 to i32
  %185 = icmp eq i32 %184, 34
  br i1 %185, label %186, label %198

186:                                              ; preds = %181
  %187 = load i8*, i8** %3, align 8
  %188 = load i8*, i8** %3, align 8
  %189 = call %struct.Token* @read_string_literal(i8* noundef %187, i8* noundef %188)
  %190 = load %struct.Token*, %struct.Token** %5, align 8
  %191 = getelementptr inbounds %struct.Token, %struct.Token* %190, i32 0, i32 1
  store %struct.Token* %189, %struct.Token** %191, align 8
  store %struct.Token* %189, %struct.Token** %5, align 8
  %192 = load %struct.Token*, %struct.Token** %5, align 8
  %193 = getelementptr inbounds %struct.Token, %struct.Token* %192, i32 0, i32 5
  %194 = load i32, i32* %193, align 8
  %195 = load i8*, i8** %3, align 8
  %196 = sext i32 %194 to i64
  %197 = getelementptr inbounds i8, i8* %195, i64 %196
  store i8* %197, i8** %3, align 8
  br label %18, !llvm.loop !15

198:                                              ; preds = %181
  %199 = load i8*, i8** %3, align 8
  %200 = call zeroext i1 @startswith(i8* noundef %199, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i64 0, i64 0))
  br i1 %200, label %201, label %214

201:                                              ; preds = %198
  %202 = load i8*, i8** %3, align 8
  %203 = load i8*, i8** %3, align 8
  %204 = getelementptr inbounds i8, i8* %203, i64 2
  %205 = call %struct.Token* @read_string_literal(i8* noundef %202, i8* noundef %204)
  %206 = load %struct.Token*, %struct.Token** %5, align 8
  %207 = getelementptr inbounds %struct.Token, %struct.Token* %206, i32 0, i32 1
  store %struct.Token* %205, %struct.Token** %207, align 8
  store %struct.Token* %205, %struct.Token** %5, align 8
  %208 = load %struct.Token*, %struct.Token** %5, align 8
  %209 = getelementptr inbounds %struct.Token, %struct.Token* %208, i32 0, i32 5
  %210 = load i32, i32* %209, align 8
  %211 = load i8*, i8** %3, align 8
  %212 = sext i32 %210 to i64
  %213 = getelementptr inbounds i8, i8* %211, i64 %212
  store i8* %213, i8** %3, align 8
  br label %18, !llvm.loop !15

214:                                              ; preds = %198
  %215 = load i8*, i8** %3, align 8
  %216 = call zeroext i1 @startswith(i8* noundef %215, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.10, i64 0, i64 0))
  br i1 %216, label %217, label %230

217:                                              ; preds = %214
  %218 = load i8*, i8** %3, align 8
  %219 = load i8*, i8** %3, align 8
  %220 = getelementptr inbounds i8, i8* %219, i64 1
  %221 = call %struct.Token* @read_utf16_string_literal(i8* noundef %218, i8* noundef %220)
  %222 = load %struct.Token*, %struct.Token** %5, align 8
  %223 = getelementptr inbounds %struct.Token, %struct.Token* %222, i32 0, i32 1
  store %struct.Token* %221, %struct.Token** %223, align 8
  store %struct.Token* %221, %struct.Token** %5, align 8
  %224 = load %struct.Token*, %struct.Token** %5, align 8
  %225 = getelementptr inbounds %struct.Token, %struct.Token* %224, i32 0, i32 5
  %226 = load i32, i32* %225, align 8
  %227 = load i8*, i8** %3, align 8
  %228 = sext i32 %226 to i64
  %229 = getelementptr inbounds i8, i8* %227, i64 %228
  store i8* %229, i8** %3, align 8
  br label %18, !llvm.loop !15

230:                                              ; preds = %214
  %231 = load i8*, i8** %3, align 8
  %232 = call zeroext i1 @startswith(i8* noundef %231, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i64 0, i64 0))
  br i1 %232, label %233, label %247

233:                                              ; preds = %230
  %234 = load i8*, i8** %3, align 8
  %235 = load i8*, i8** %3, align 8
  %236 = getelementptr inbounds i8, i8* %235, i64 1
  %237 = load %struct.Type*, %struct.Type** @ty_int, align 8
  %238 = call %struct.Token* @read_utf32_string_literal(i8* noundef %234, i8* noundef %236, %struct.Type* noundef %237)
  %239 = load %struct.Token*, %struct.Token** %5, align 8
  %240 = getelementptr inbounds %struct.Token, %struct.Token* %239, i32 0, i32 1
  store %struct.Token* %238, %struct.Token** %240, align 8
  store %struct.Token* %238, %struct.Token** %5, align 8
  %241 = load %struct.Token*, %struct.Token** %5, align 8
  %242 = getelementptr inbounds %struct.Token, %struct.Token* %241, i32 0, i32 5
  %243 = load i32, i32* %242, align 8
  %244 = load i8*, i8** %3, align 8
  %245 = sext i32 %243 to i64
  %246 = getelementptr inbounds i8, i8* %244, i64 %245
  store i8* %246, i8** %3, align 8
  br label %18, !llvm.loop !15

247:                                              ; preds = %230
  %248 = load i8*, i8** %3, align 8
  %249 = call zeroext i1 @startswith(i8* noundef %248, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.12, i64 0, i64 0))
  br i1 %249, label %250, label %264

250:                                              ; preds = %247
  %251 = load i8*, i8** %3, align 8
  %252 = load i8*, i8** %3, align 8
  %253 = getelementptr inbounds i8, i8* %252, i64 1
  %254 = load %struct.Type*, %struct.Type** @ty_uint, align 8
  %255 = call %struct.Token* @read_utf32_string_literal(i8* noundef %251, i8* noundef %253, %struct.Type* noundef %254)
  %256 = load %struct.Token*, %struct.Token** %5, align 8
  %257 = getelementptr inbounds %struct.Token, %struct.Token* %256, i32 0, i32 1
  store %struct.Token* %255, %struct.Token** %257, align 8
  store %struct.Token* %255, %struct.Token** %5, align 8
  %258 = load %struct.Token*, %struct.Token** %5, align 8
  %259 = getelementptr inbounds %struct.Token, %struct.Token* %258, i32 0, i32 5
  %260 = load i32, i32* %259, align 8
  %261 = load i8*, i8** %3, align 8
  %262 = sext i32 %260 to i64
  %263 = getelementptr inbounds i8, i8* %261, i64 %262
  store i8* %263, i8** %3, align 8
  br label %18, !llvm.loop !15

264:                                              ; preds = %247
  %265 = load i8*, i8** %3, align 8
  %266 = load i8, i8* %265, align 1
  %267 = sext i8 %266 to i32
  %268 = icmp eq i32 %267, 39
  br i1 %268, label %269, label %289

269:                                              ; preds = %264
  %270 = load i8*, i8** %3, align 8
  %271 = load i8*, i8** %3, align 8
  %272 = load %struct.Type*, %struct.Type** @ty_int, align 8
  %273 = call %struct.Token* @read_char_literal(i8* noundef %270, i8* noundef %271, %struct.Type* noundef %272)
  %274 = load %struct.Token*, %struct.Token** %5, align 8
  %275 = getelementptr inbounds %struct.Token, %struct.Token* %274, i32 0, i32 1
  store %struct.Token* %273, %struct.Token** %275, align 8
  store %struct.Token* %273, %struct.Token** %5, align 8
  %276 = load %struct.Token*, %struct.Token** %5, align 8
  %277 = getelementptr inbounds %struct.Token, %struct.Token* %276, i32 0, i32 2
  %278 = load i64, i64* %277, align 16
  %279 = trunc i64 %278 to i8
  %280 = sext i8 %279 to i64
  %281 = load %struct.Token*, %struct.Token** %5, align 8
  %282 = getelementptr inbounds %struct.Token, %struct.Token* %281, i32 0, i32 2
  store i64 %280, i64* %282, align 16
  %283 = load %struct.Token*, %struct.Token** %5, align 8
  %284 = getelementptr inbounds %struct.Token, %struct.Token* %283, i32 0, i32 5
  %285 = load i32, i32* %284, align 8
  %286 = load i8*, i8** %3, align 8
  %287 = sext i32 %285 to i64
  %288 = getelementptr inbounds i8, i8* %286, i64 %287
  store i8* %288, i8** %3, align 8
  br label %18, !llvm.loop !15

289:                                              ; preds = %264
  %290 = load i8*, i8** %3, align 8
  %291 = call zeroext i1 @startswith(i8* noundef %290, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.13, i64 0, i64 0))
  br i1 %291, label %292, label %310

292:                                              ; preds = %289
  %293 = load i8*, i8** %3, align 8
  %294 = load i8*, i8** %3, align 8
  %295 = getelementptr inbounds i8, i8* %294, i64 1
  %296 = load %struct.Type*, %struct.Type** @ty_ushort, align 8
  %297 = call %struct.Token* @read_char_literal(i8* noundef %293, i8* noundef %295, %struct.Type* noundef %296)
  %298 = load %struct.Token*, %struct.Token** %5, align 8
  %299 = getelementptr inbounds %struct.Token, %struct.Token* %298, i32 0, i32 1
  store %struct.Token* %297, %struct.Token** %299, align 8
  store %struct.Token* %297, %struct.Token** %5, align 8
  %300 = load %struct.Token*, %struct.Token** %5, align 8
  %301 = getelementptr inbounds %struct.Token, %struct.Token* %300, i32 0, i32 2
  %302 = load i64, i64* %301, align 16
  %303 = and i64 %302, 65535
  store i64 %303, i64* %301, align 16
  %304 = load %struct.Token*, %struct.Token** %5, align 8
  %305 = getelementptr inbounds %struct.Token, %struct.Token* %304, i32 0, i32 5
  %306 = load i32, i32* %305, align 8
  %307 = load i8*, i8** %3, align 8
  %308 = sext i32 %306 to i64
  %309 = getelementptr inbounds i8, i8* %307, i64 %308
  store i8* %309, i8** %3, align 8
  br label %18, !llvm.loop !15

310:                                              ; preds = %289
  %311 = load i8*, i8** %3, align 8
  %312 = call zeroext i1 @startswith(i8* noundef %311, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.14, i64 0, i64 0))
  br i1 %312, label %313, label %327

313:                                              ; preds = %310
  %314 = load i8*, i8** %3, align 8
  %315 = load i8*, i8** %3, align 8
  %316 = getelementptr inbounds i8, i8* %315, i64 1
  %317 = load %struct.Type*, %struct.Type** @ty_int, align 8
  %318 = call %struct.Token* @read_char_literal(i8* noundef %314, i8* noundef %316, %struct.Type* noundef %317)
  %319 = load %struct.Token*, %struct.Token** %5, align 8
  %320 = getelementptr inbounds %struct.Token, %struct.Token* %319, i32 0, i32 1
  store %struct.Token* %318, %struct.Token** %320, align 8
  store %struct.Token* %318, %struct.Token** %5, align 8
  %321 = load %struct.Token*, %struct.Token** %5, align 8
  %322 = getelementptr inbounds %struct.Token, %struct.Token* %321, i32 0, i32 5
  %323 = load i32, i32* %322, align 8
  %324 = load i8*, i8** %3, align 8
  %325 = sext i32 %323 to i64
  %326 = getelementptr inbounds i8, i8* %324, i64 %325
  store i8* %326, i8** %3, align 8
  br label %18, !llvm.loop !15

327:                                              ; preds = %310
  %328 = load i8*, i8** %3, align 8
  %329 = call zeroext i1 @startswith(i8* noundef %328, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.15, i64 0, i64 0))
  br i1 %329, label %330, label %344

330:                                              ; preds = %327
  %331 = load i8*, i8** %3, align 8
  %332 = load i8*, i8** %3, align 8
  %333 = getelementptr inbounds i8, i8* %332, i64 1
  %334 = load %struct.Type*, %struct.Type** @ty_uint, align 8
  %335 = call %struct.Token* @read_char_literal(i8* noundef %331, i8* noundef %333, %struct.Type* noundef %334)
  %336 = load %struct.Token*, %struct.Token** %5, align 8
  %337 = getelementptr inbounds %struct.Token, %struct.Token* %336, i32 0, i32 1
  store %struct.Token* %335, %struct.Token** %337, align 8
  store %struct.Token* %335, %struct.Token** %5, align 8
  %338 = load %struct.Token*, %struct.Token** %5, align 8
  %339 = getelementptr inbounds %struct.Token, %struct.Token* %338, i32 0, i32 5
  %340 = load i32, i32* %339, align 8
  %341 = load i8*, i8** %3, align 8
  %342 = sext i32 %340 to i64
  %343 = getelementptr inbounds i8, i8* %341, i64 %342
  store i8* %343, i8** %3, align 8
  br label %18, !llvm.loop !15

344:                                              ; preds = %327
  %345 = load i8*, i8** %3, align 8
  %346 = load i8*, i8** %8, align 8
  %347 = load i8, i8* %6, align 1
  %348 = trunc i8 %347 to i1
  %349 = call i32 @read_ident(i8* noundef %345, i8* noundef %346, i1 noundef zeroext %348)
  store i32 %349, i32* %11, align 4
  %350 = load i32, i32* %11, align 4
  %351 = icmp ne i32 %350, 0
  br i1 %351, label %352, label %367

352:                                              ; preds = %344
  %353 = load i8*, i8** %3, align 8
  %354 = load i8*, i8** %3, align 8
  %355 = load i32, i32* %11, align 4
  %356 = sext i32 %355 to i64
  %357 = getelementptr inbounds i8, i8* %354, i64 %356
  %358 = call %struct.Token* @new_token(i32 noundef 0, i8* noundef %353, i8* noundef %357)
  %359 = load %struct.Token*, %struct.Token** %5, align 8
  %360 = getelementptr inbounds %struct.Token, %struct.Token* %359, i32 0, i32 1
  store %struct.Token* %358, %struct.Token** %360, align 8
  store %struct.Token* %358, %struct.Token** %5, align 8
  %361 = load %struct.Token*, %struct.Token** %5, align 8
  %362 = getelementptr inbounds %struct.Token, %struct.Token* %361, i32 0, i32 5
  %363 = load i32, i32* %362, align 8
  %364 = load i8*, i8** %3, align 8
  %365 = sext i32 %363 to i64
  %366 = getelementptr inbounds i8, i8* %364, i64 %365
  store i8* %366, i8** %3, align 8
  br label %18, !llvm.loop !15

367:                                              ; preds = %344
  %368 = load i8*, i8** %3, align 8
  %369 = call i32 @read_punct(i8* noundef %368)
  store i32 %369, i32* %12, align 4
  %370 = load i32, i32* %12, align 4
  %371 = icmp ne i32 %370, 0
  br i1 %371, label %372, label %387

372:                                              ; preds = %367
  %373 = load i8*, i8** %3, align 8
  %374 = load i8*, i8** %3, align 8
  %375 = load i32, i32* %12, align 4
  %376 = sext i32 %375 to i64
  %377 = getelementptr inbounds i8, i8* %374, i64 %376
  %378 = call %struct.Token* @new_token(i32 noundef 1, i8* noundef %373, i8* noundef %377)
  %379 = load %struct.Token*, %struct.Token** %5, align 8
  %380 = getelementptr inbounds %struct.Token, %struct.Token* %379, i32 0, i32 1
  store %struct.Token* %378, %struct.Token** %380, align 8
  store %struct.Token* %378, %struct.Token** %5, align 8
  %381 = load %struct.Token*, %struct.Token** %5, align 8
  %382 = getelementptr inbounds %struct.Token, %struct.Token* %381, i32 0, i32 5
  %383 = load i32, i32* %382, align 8
  %384 = load i8*, i8** %3, align 8
  %385 = sext i32 %383 to i64
  %386 = getelementptr inbounds i8, i8* %384, i64 %385
  store i8* %386, i8** %3, align 8
  br label %18, !llvm.loop !15

387:                                              ; preds = %367
  %388 = load i8*, i8** %3, align 8
  call void (i8*, i8*, ...) @error_at(i8* noundef %388, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @.str.16, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

389:                                              ; preds = %18
  %390 = load i8*, i8** %3, align 8
  %391 = load i8*, i8** %3, align 8
  %392 = call %struct.Token* @new_token(i32 noundef 6, i8* noundef %390, i8* noundef %391)
  %393 = load %struct.Token*, %struct.Token** %5, align 8
  %394 = getelementptr inbounds %struct.Token, %struct.Token* %393, i32 0, i32 1
  store %struct.Token* %392, %struct.Token** %394, align 8
  store %struct.Token* %392, %struct.Token** %5, align 8
  %395 = getelementptr inbounds %struct.Token, %struct.Token* %4, i32 0, i32 1
  %396 = load %struct.Token*, %struct.Token** %395, align 8
  call void @add_line_numbers(%struct.Token* noundef %396)
  %397 = getelementptr inbounds %struct.Token, %struct.Token* %4, i32 0, i32 1
  %398 = load %struct.Token*, %struct.Token** %397, align 8
  ret %struct.Token* %398
}

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #6

; Function Attrs: nounwind readonly willreturn
declare i8* @strstr(i8* noundef, i8* noundef) #5

; Function Attrs: nounwind readnone willreturn
declare i16** @__ctype_b_loc() #7

; Function Attrs: nounwind readonly willreturn
declare i8* @strchr(i8* noundef, i32 noundef) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @new_token(i32 noundef %0, i8* noundef %1, i8* noundef %2) #4 {
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca %struct.Token*, align 8
  store i32 %0, i32* %4, align 4
  store i8* %1, i8** %5, align 8
  store i8* %2, i8** %6, align 8
  %8 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 128) #12
  %9 = bitcast i8* %8 to %struct.Token*
  store %struct.Token* %9, %struct.Token** %7, align 8
  %10 = load %struct.Token*, %struct.Token** %7, align 8
  %11 = icmp eq %struct.Token* %10, null
  br i1 %11, label %12, label %13

12:                                               ; preds = %3
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([30 x i8], [30 x i8]* @.str.89, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

13:                                               ; preds = %3
  %14 = load i32, i32* %4, align 4
  %15 = load %struct.Token*, %struct.Token** %7, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 0
  store i32 %14, i32* %16, align 16
  %17 = load i8*, i8** %5, align 8
  %18 = load %struct.Token*, %struct.Token** %7, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 4
  store i8* %17, i8** %19, align 16
  %20 = load i8*, i8** %6, align 8
  %21 = load i8*, i8** %5, align 8
  %22 = ptrtoint i8* %20 to i64
  %23 = ptrtoint i8* %21 to i64
  %24 = sub i64 %22, %23
  %25 = trunc i64 %24 to i32
  %26 = load %struct.Token*, %struct.Token** %7, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 5
  store i32 %25, i32* %27, align 8
  %28 = load %struct.File*, %struct.File** @current_file, align 8
  %29 = load %struct.Token*, %struct.Token** %7, align 8
  %30 = getelementptr inbounds %struct.Token, %struct.Token* %29, i32 0, i32 8
  store %struct.File* %28, %struct.File** %30, align 16
  %31 = load %struct.File*, %struct.File** @current_file, align 8
  %32 = getelementptr inbounds %struct.File, %struct.File* %31, i32 0, i32 3
  %33 = load i8*, i8** %32, align 8
  %34 = load %struct.Token*, %struct.Token** %7, align 8
  %35 = getelementptr inbounds %struct.Token, %struct.Token* %34, i32 0, i32 9
  store i8* %33, i8** %35, align 8
  %36 = load i8, i8* @at_bol, align 1
  %37 = trunc i8 %36 to i1
  %38 = load %struct.Token*, %struct.Token** %7, align 8
  %39 = getelementptr inbounds %struct.Token, %struct.Token* %38, i32 0, i32 12
  %40 = zext i1 %37 to i8
  store i8 %40, i8* %39, align 8
  %41 = load i8, i8* @has_space, align 1
  %42 = trunc i8 %41 to i1
  %43 = load %struct.Token*, %struct.Token** %7, align 8
  %44 = getelementptr inbounds %struct.Token, %struct.Token* %43, i32 0, i32 13
  %45 = zext i1 %42 to i8
  store i8 %45, i8* %44, align 1
  store i8 0, i8* @has_space, align 1
  store i8 0, i8* @at_bol, align 1
  %46 = load %struct.Token*, %struct.Token** %7, align 8
  ret %struct.Token* %46
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @read_string_literal(i8* noundef %0, i8* noundef %1) #4 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca %struct.Token*, align 8
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %10 = load i8*, i8** %4, align 8
  %11 = getelementptr inbounds i8, i8* %10, i64 1
  %12 = call i8* @string_literal_end(i8* noundef %11)
  store i8* %12, i8** %5, align 8
  %13 = load i8*, i8** %5, align 8
  %14 = load i8*, i8** %4, align 8
  %15 = ptrtoint i8* %13 to i64
  %16 = ptrtoint i8* %14 to i64
  %17 = sub i64 %15, %16
  %18 = call noalias i8* @calloc(i64 noundef 1, i64 noundef %17) #12
  store i8* %18, i8** %6, align 8
  %19 = load i8*, i8** %6, align 8
  %20 = icmp eq i8* %19, null
  br i1 %20, label %21, label %22

21:                                               ; preds = %2
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.90, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

22:                                               ; preds = %2
  store i32 0, i32* %7, align 4
  %23 = load i8*, i8** %4, align 8
  %24 = getelementptr inbounds i8, i8* %23, i64 1
  store i8* %24, i8** %8, align 8
  br label %25

25:                                               ; preds = %53, %22
  %26 = load i8*, i8** %8, align 8
  %27 = load i8*, i8** %5, align 8
  %28 = icmp ult i8* %26, %27
  br i1 %28, label %29, label %54

29:                                               ; preds = %25
  %30 = load i8*, i8** %8, align 8
  %31 = load i8, i8* %30, align 1
  %32 = sext i8 %31 to i32
  %33 = icmp eq i32 %32, 92
  br i1 %33, label %34, label %44

34:                                               ; preds = %29
  %35 = load i8*, i8** %8, align 8
  %36 = getelementptr inbounds i8, i8* %35, i64 1
  %37 = call i32 @read_escaped_char(i8** noundef %8, i8* noundef %36)
  %38 = trunc i32 %37 to i8
  %39 = load i8*, i8** %6, align 8
  %40 = load i32, i32* %7, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* %7, align 4
  %42 = sext i32 %40 to i64
  %43 = getelementptr inbounds i8, i8* %39, i64 %42
  store i8 %38, i8* %43, align 1
  br label %53

44:                                               ; preds = %29
  %45 = load i8*, i8** %8, align 8
  %46 = getelementptr inbounds i8, i8* %45, i32 1
  store i8* %46, i8** %8, align 8
  %47 = load i8, i8* %45, align 1
  %48 = load i8*, i8** %6, align 8
  %49 = load i32, i32* %7, align 4
  %50 = add nsw i32 %49, 1
  store i32 %50, i32* %7, align 4
  %51 = sext i32 %49 to i64
  %52 = getelementptr inbounds i8, i8* %48, i64 %51
  store i8 %47, i8* %52, align 1
  br label %53

53:                                               ; preds = %44, %34
  br label %25, !llvm.loop !16

54:                                               ; preds = %25
  %55 = load i8*, i8** %3, align 8
  %56 = load i8*, i8** %5, align 8
  %57 = getelementptr inbounds i8, i8* %56, i64 1
  %58 = call %struct.Token* @new_token(i32 noundef 3, i8* noundef %55, i8* noundef %57)
  store %struct.Token* %58, %struct.Token** %9, align 8
  %59 = load %struct.Type*, %struct.Type** @ty_char, align 8
  %60 = load i32, i32* %7, align 4
  %61 = add nsw i32 %60, 1
  %62 = call %struct.Type* @array_of(%struct.Type* noundef %59, i32 noundef %61)
  %63 = load %struct.Token*, %struct.Token** %9, align 8
  %64 = getelementptr inbounds %struct.Token, %struct.Token* %63, i32 0, i32 6
  store %struct.Type* %62, %struct.Type** %64, align 16
  %65 = load i8*, i8** %6, align 8
  %66 = load %struct.Token*, %struct.Token** %9, align 8
  %67 = getelementptr inbounds %struct.Token, %struct.Token* %66, i32 0, i32 7
  store i8* %65, i8** %67, align 8
  %68 = load %struct.Token*, %struct.Token** %9, align 8
  ret %struct.Token* %68
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @read_char_literal(i8* noundef %0, i8* noundef %1, %struct.Type* noundef %2) #4 {
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i32, align 4
  %9 = alloca i8*, align 8
  %10 = alloca %struct.Token*, align 8
  store i8* %0, i8** %4, align 8
  store i8* %1, i8** %5, align 8
  store %struct.Type* %2, %struct.Type** %6, align 8
  %11 = load i8*, i8** %5, align 8
  %12 = getelementptr inbounds i8, i8* %11, i64 1
  store i8* %12, i8** %7, align 8
  %13 = load i8*, i8** %7, align 8
  %14 = load i8, i8* %13, align 1
  %15 = sext i8 %14 to i32
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %17, label %19

17:                                               ; preds = %3
  %18 = load i8*, i8** %4, align 8
  call void (i8*, i8*, ...) @error_at(i8* noundef %18, i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.91, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

19:                                               ; preds = %3
  %20 = load i8*, i8** %7, align 8
  %21 = load i8, i8* %20, align 1
  %22 = sext i8 %21 to i32
  %23 = icmp eq i32 %22, 92
  br i1 %23, label %24, label %28

24:                                               ; preds = %19
  %25 = load i8*, i8** %7, align 8
  %26 = getelementptr inbounds i8, i8* %25, i64 1
  %27 = call i32 @read_escaped_char(i8** noundef %7, i8* noundef %26)
  store i32 %27, i32* %8, align 4
  br label %31

28:                                               ; preds = %19
  %29 = load i8*, i8** %7, align 8
  %30 = call i32 @decode_utf8(i8** noundef %7, i8* noundef %29)
  store i32 %30, i32* %8, align 4
  br label %31

31:                                               ; preds = %28, %24
  %32 = load i8*, i8** %7, align 8
  %33 = call i8* @strchr(i8* noundef %32, i32 noundef 39) #10
  store i8* %33, i8** %9, align 8
  %34 = load i8*, i8** %9, align 8
  %35 = icmp ne i8* %34, null
  br i1 %35, label %38, label %36

36:                                               ; preds = %31
  %37 = load i8*, i8** %7, align 8
  call void (i8*, i8*, ...) @error_at(i8* noundef %37, i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.91, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

38:                                               ; preds = %31
  %39 = load i8*, i8** %4, align 8
  %40 = load i8*, i8** %9, align 8
  %41 = getelementptr inbounds i8, i8* %40, i64 1
  %42 = call %struct.Token* @new_token(i32 noundef 4, i8* noundef %39, i8* noundef %41)
  store %struct.Token* %42, %struct.Token** %10, align 8
  %43 = load i32, i32* %8, align 4
  %44 = sext i32 %43 to i64
  %45 = load %struct.Token*, %struct.Token** %10, align 8
  %46 = getelementptr inbounds %struct.Token, %struct.Token* %45, i32 0, i32 2
  store i64 %44, i64* %46, align 16
  %47 = load %struct.Type*, %struct.Type** %6, align 8
  %48 = load %struct.Token*, %struct.Token** %10, align 8
  %49 = getelementptr inbounds %struct.Token, %struct.Token* %48, i32 0, i32 6
  store %struct.Type* %47, %struct.Type** %49, align 16
  %50 = load %struct.Token*, %struct.Token** %10, align 8
  ret %struct.Token* %50
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @read_ident(i8* noundef %0, i8* noundef %1, i1 noundef zeroext %2) #4 {
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i8, align 1
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  %10 = alloca i8*, align 8
  store i8* %0, i8** %5, align 8
  store i8* %1, i8** %6, align 8
  %11 = zext i1 %2 to i8
  store i8 %11, i8* %7, align 1
  %12 = load i8*, i8** %5, align 8
  store i8* %12, i8** %8, align 8
  %13 = load i8*, i8** %8, align 8
  %14 = call i32 @decode_utf8(i8** noundef %8, i8* noundef %13)
  store i32 %14, i32* %9, align 4
  %15 = load i8*, i8** %6, align 8
  %16 = load i8, i8* %15, align 1
  %17 = sext i8 %16 to i32
  %18 = icmp eq i32 %17, 35
  br i1 %18, label %22, label %19

19:                                               ; preds = %3
  %20 = load i8, i8* %7, align 1
  %21 = trunc i8 %20 to i1
  br i1 %21, label %22, label %27

22:                                               ; preds = %19, %3
  %23 = load i32, i32* %9, align 4
  %24 = call zeroext i1 @is_ident3(i32 noundef %23)
  br i1 %24, label %26, label %25

25:                                               ; preds = %22
  store i32 0, i32* %4, align 4
  br label %47

26:                                               ; preds = %22
  br label %32

27:                                               ; preds = %19
  %28 = load i32, i32* %9, align 4
  %29 = call zeroext i1 @is_ident1(i32 noundef %28)
  br i1 %29, label %31, label %30

30:                                               ; preds = %27
  store i32 0, i32* %4, align 4
  br label %47

31:                                               ; preds = %27
  br label %32

32:                                               ; preds = %31, %26
  br label %33

33:                                               ; preds = %45, %32
  %34 = load i8*, i8** %8, align 8
  %35 = call i32 @decode_utf8(i8** noundef %10, i8* noundef %34)
  store i32 %35, i32* %9, align 4
  %36 = load i32, i32* %9, align 4
  %37 = call zeroext i1 @is_ident2(i32 noundef %36)
  br i1 %37, label %45, label %38

38:                                               ; preds = %33
  %39 = load i8*, i8** %8, align 8
  %40 = load i8*, i8** %5, align 8
  %41 = ptrtoint i8* %39 to i64
  %42 = ptrtoint i8* %40 to i64
  %43 = sub i64 %41, %42
  %44 = trunc i64 %43 to i32
  store i32 %44, i32* %4, align 4
  br label %47

45:                                               ; preds = %33
  %46 = load i8*, i8** %10, align 8
  store i8* %46, i8** %8, align 8
  br label %33

47:                                               ; preds = %38, %30, %25
  %48 = load i32, i32* %4, align 4
  ret i32 %48
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @read_punct(i8* noundef %0) #4 {
  %2 = alloca i32, align 4
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i32 0, i32* %4, align 4
  br label %5

5:                                                ; preds = %24, %1
  %6 = load i32, i32* %4, align 4
  %7 = sext i32 %6 to i64
  %8 = icmp ult i64 %7, 23
  br i1 %8, label %9, label %27

9:                                                ; preds = %5
  %10 = load i8*, i8** %3, align 8
  %11 = load i32, i32* %4, align 4
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds [23 x i8*], [23 x i8*]* @read_punct.kw, i64 0, i64 %12
  %14 = load i8*, i8** %13, align 8
  %15 = call zeroext i1 @startswith(i8* noundef %10, i8* noundef %14)
  br i1 %15, label %16, label %23

16:                                               ; preds = %9
  %17 = load i32, i32* %4, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds [23 x i8*], [23 x i8*]* @read_punct.kw, i64 0, i64 %18
  %20 = load i8*, i8** %19, align 8
  %21 = call i64 @strlen(i8* noundef %20) #10
  %22 = trunc i64 %21 to i32
  store i32 %22, i32* %2, align 4
  br label %41

23:                                               ; preds = %9
  br label %24

24:                                               ; preds = %23
  %25 = load i32, i32* %4, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, i32* %4, align 4
  br label %5, !llvm.loop !17

27:                                               ; preds = %5
  %28 = call i16** @__ctype_b_loc() #13
  %29 = load i16*, i16** %28, align 8
  %30 = load i8*, i8** %3, align 8
  %31 = load i8, i8* %30, align 1
  %32 = sext i8 %31 to i32
  %33 = sext i32 %32 to i64
  %34 = getelementptr inbounds i16, i16* %29, i64 %33
  %35 = load i16, i16* %34, align 2
  %36 = zext i16 %35 to i32
  %37 = and i32 %36, 4
  %38 = icmp ne i32 %37, 0
  %39 = zext i1 %38 to i64
  %40 = select i1 %38, i32 1, i32 0
  store i32 %40, i32* %2, align 4
  br label %41

41:                                               ; preds = %27, %16
  %42 = load i32, i32* %2, align 4
  ret i32 %42
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @add_line_numbers(%struct.Token* noundef %0) #4 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  store %struct.Token* %0, %struct.Token** %2, align 8
  %5 = load %struct.File*, %struct.File** @current_file, align 8
  %6 = getelementptr inbounds %struct.File, %struct.File* %5, i32 0, i32 2
  %7 = load i8*, i8** %6, align 8
  store i8* %7, i8** %3, align 8
  store i32 1, i32* %4, align 4
  br label %8

8:                                                ; preds = %30, %1
  %9 = load i8*, i8** %3, align 8
  %10 = load %struct.Token*, %struct.Token** %2, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 4
  %12 = load i8*, i8** %11, align 16
  %13 = icmp eq i8* %9, %12
  br i1 %13, label %14, label %21

14:                                               ; preds = %8
  %15 = load i32, i32* %4, align 4
  %16 = load %struct.Token*, %struct.Token** %2, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 10
  store i32 %15, i32* %17, align 16
  %18 = load %struct.Token*, %struct.Token** %2, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 1
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  store %struct.Token* %20, %struct.Token** %2, align 8
  br label %21

21:                                               ; preds = %14, %8
  %22 = load i8*, i8** %3, align 8
  %23 = load i8, i8* %22, align 1
  %24 = sext i8 %23 to i32
  %25 = icmp eq i32 %24, 10
  br i1 %25, label %26, label %29

26:                                               ; preds = %21
  %27 = load i32, i32* %4, align 4
  %28 = add nsw i32 %27, 1
  store i32 %28, i32* %4, align 4
  br label %29

29:                                               ; preds = %26, %21
  br label %30

30:                                               ; preds = %29
  %31 = load i8*, i8** %3, align 8
  %32 = getelementptr inbounds i8, i8* %31, i32 1
  store i8* %32, i8** %3, align 8
  %33 = load i8, i8* %31, align 1
  %34 = icmp ne i8 %33, 0
  br i1 %34, label %8, label %35, !llvm.loop !18

35:                                               ; preds = %30
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.File** @get_input_files() #4 {
  %1 = load %struct.File**, %struct.File*** @input_files, align 8
  ret %struct.File** %1
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.File* @new_file(i8* noundef %0, i32 noundef %1, i8* noundef %2) #4 {
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i8*, align 8
  %7 = alloca %struct.File*, align 8
  store i8* %0, i8** %4, align 8
  store i32 %1, i32* %5, align 4
  store i8* %2, i8** %6, align 8
  %8 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 40) #12
  %9 = bitcast i8* %8 to %struct.File*
  store %struct.File* %9, %struct.File** %7, align 8
  %10 = load %struct.File*, %struct.File** %7, align 8
  %11 = icmp eq %struct.File* %10, null
  br i1 %11, label %12, label %13

12:                                               ; preds = %3
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([30 x i8], [30 x i8]* @.str.17, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

13:                                               ; preds = %3
  %14 = load i8*, i8** %4, align 8
  %15 = load %struct.File*, %struct.File** %7, align 8
  %16 = getelementptr inbounds %struct.File, %struct.File* %15, i32 0, i32 0
  store i8* %14, i8** %16, align 8
  %17 = load i8*, i8** %4, align 8
  %18 = load %struct.File*, %struct.File** %7, align 8
  %19 = getelementptr inbounds %struct.File, %struct.File* %18, i32 0, i32 3
  store i8* %17, i8** %19, align 8
  %20 = load i32, i32* %5, align 4
  %21 = load %struct.File*, %struct.File** %7, align 8
  %22 = getelementptr inbounds %struct.File, %struct.File* %21, i32 0, i32 1
  store i32 %20, i32* %22, align 8
  %23 = load i8*, i8** %6, align 8
  %24 = load %struct.File*, %struct.File** %7, align 8
  %25 = getelementptr inbounds %struct.File, %struct.File* %24, i32 0, i32 2
  store i8* %23, i8** %25, align 8
  %26 = load %struct.File*, %struct.File** %7, align 8
  ret %struct.File* %26
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64 noundef, i64 noundef) #8

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Token* @tokenize_file(i8* noundef %0) #4 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %struct.File*, align 8
  store i8* %0, i8** %3, align 8
  %6 = load i8*, i8** %3, align 8
  %7 = call i8* @read_file(i8* noundef %6)
  store i8* %7, i8** %4, align 8
  %8 = load i8*, i8** %4, align 8
  %9 = icmp ne i8* %8, null
  br i1 %9, label %11, label %10

10:                                               ; preds = %1
  store %struct.Token* null, %struct.Token** %2, align 8
  br label %53

11:                                               ; preds = %1
  %12 = load i8*, i8** %4, align 8
  %13 = call i32 @memcmp(i8* noundef %12, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.18, i64 0, i64 0), i64 noundef 3) #10
  %14 = icmp ne i32 %13, 0
  br i1 %14, label %18, label %15

15:                                               ; preds = %11
  %16 = load i8*, i8** %4, align 8
  %17 = getelementptr inbounds i8, i8* %16, i64 3
  store i8* %17, i8** %4, align 8
  br label %18

18:                                               ; preds = %15, %11
  %19 = load i8*, i8** %4, align 8
  call void @canonicalize_newline(i8* noundef %19)
  %20 = load i8*, i8** %4, align 8
  call void @remove_backslash_newline(i8* noundef %20)
  %21 = load i8*, i8** %4, align 8
  call void @convert_universal_chars(i8* noundef %21)
  %22 = load i8*, i8** %3, align 8
  %23 = load i32, i32* @tokenize_file.file_no, align 4
  %24 = add nsw i32 %23, 1
  %25 = load i8*, i8** %4, align 8
  %26 = call %struct.File* @new_file(i8* noundef %22, i32 noundef %24, i8* noundef %25)
  store %struct.File* %26, %struct.File** %5, align 8
  %27 = load %struct.File**, %struct.File*** @input_files, align 8
  %28 = bitcast %struct.File** %27 to i8*
  %29 = load i32, i32* @tokenize_file.file_no, align 4
  %30 = add nsw i32 %29, 2
  %31 = sext i32 %30 to i64
  %32 = mul i64 8, %31
  %33 = call i8* @realloc(i8* noundef %28, i64 noundef %32) #12
  %34 = bitcast i8* %33 to %struct.File**
  store %struct.File** %34, %struct.File*** @input_files, align 8
  %35 = load %struct.File**, %struct.File*** @input_files, align 8
  %36 = icmp eq %struct.File** %35, null
  br i1 %36, label %37, label %38

37:                                               ; preds = %18
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str.19, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

38:                                               ; preds = %18
  %39 = load %struct.File*, %struct.File** %5, align 8
  %40 = load %struct.File**, %struct.File*** @input_files, align 8
  %41 = load i32, i32* @tokenize_file.file_no, align 4
  %42 = sext i32 %41 to i64
  %43 = getelementptr inbounds %struct.File*, %struct.File** %40, i64 %42
  store %struct.File* %39, %struct.File** %43, align 8
  %44 = load %struct.File**, %struct.File*** @input_files, align 8
  %45 = load i32, i32* @tokenize_file.file_no, align 4
  %46 = add nsw i32 %45, 1
  %47 = sext i32 %46 to i64
  %48 = getelementptr inbounds %struct.File*, %struct.File** %44, i64 %47
  store %struct.File* null, %struct.File** %48, align 8
  %49 = load i32, i32* @tokenize_file.file_no, align 4
  %50 = add nsw i32 %49, 1
  store i32 %50, i32* @tokenize_file.file_no, align 4
  %51 = load %struct.File*, %struct.File** %5, align 8
  %52 = call %struct.Token* @tokenize(%struct.File* noundef %51)
  store %struct.Token* %52, %struct.Token** %2, align 8
  br label %53

53:                                               ; preds = %38, %10
  %54 = load %struct.Token*, %struct.Token** %2, align 8
  ret %struct.Token* %54
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @read_file(i8* noundef %0) #4 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct._IO_FILE*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i64, align 8
  %7 = alloca %struct._IO_FILE*, align 8
  %8 = alloca [4096 x i8], align 16
  %9 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  %10 = load i8*, i8** %3, align 8
  %11 = call i32 @strcmp(i8* noundef %10, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.115, i64 0, i64 0)) #10
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %13, label %15

13:                                               ; preds = %1
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8
  store %struct._IO_FILE* %14, %struct._IO_FILE** %4, align 8
  br label %22

15:                                               ; preds = %1
  %16 = load i8*, i8** %3, align 8
  %17 = call noalias %struct._IO_FILE* @fopen(i8* noundef %16, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.116, i64 0, i64 0))
  store %struct._IO_FILE* %17, %struct._IO_FILE** %4, align 8
  %18 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %19 = icmp ne %struct._IO_FILE* %18, null
  br i1 %19, label %21, label %20

20:                                               ; preds = %15
  store i8* null, i8** %2, align 8
  br label %67

21:                                               ; preds = %15
  br label %22

22:                                               ; preds = %21, %13
  %23 = call noalias %struct._IO_FILE* @open_memstream(i8** noundef %5, i64* noundef %6) #12
  store %struct._IO_FILE* %23, %struct._IO_FILE** %7, align 8
  br label %24

24:                                               ; preds = %32, %22
  %25 = getelementptr inbounds [4096 x i8], [4096 x i8]* %8, i64 0, i64 0
  %26 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %27 = call i64 @fread(i8* noundef %25, i64 noundef 1, i64 noundef 4096, %struct._IO_FILE* noundef %26)
  %28 = trunc i64 %27 to i32
  store i32 %28, i32* %9, align 4
  %29 = load i32, i32* %9, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %31, label %32

31:                                               ; preds = %24
  br label %38

32:                                               ; preds = %24
  %33 = getelementptr inbounds [4096 x i8], [4096 x i8]* %8, i64 0, i64 0
  %34 = load i32, i32* %9, align 4
  %35 = sext i32 %34 to i64
  %36 = load %struct._IO_FILE*, %struct._IO_FILE** %7, align 8
  %37 = call i64 @fwrite(i8* noundef %33, i64 noundef 1, i64 noundef %35, %struct._IO_FILE* noundef %36)
  br label %24

38:                                               ; preds = %31
  %39 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %40 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8
  %41 = icmp ne %struct._IO_FILE* %39, %40
  br i1 %41, label %42, label %45

42:                                               ; preds = %38
  %43 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  %44 = call i32 @fclose(%struct._IO_FILE* noundef %43)
  br label %45

45:                                               ; preds = %42, %38
  %46 = load %struct._IO_FILE*, %struct._IO_FILE** %7, align 8
  %47 = call i32 @fflush(%struct._IO_FILE* noundef %46)
  %48 = load i64, i64* %6, align 8
  %49 = icmp eq i64 %48, 0
  br i1 %49, label %58, label %50

50:                                               ; preds = %45
  %51 = load i8*, i8** %5, align 8
  %52 = load i64, i64* %6, align 8
  %53 = sub i64 %52, 1
  %54 = getelementptr inbounds i8, i8* %51, i64 %53
  %55 = load i8, i8* %54, align 1
  %56 = sext i8 %55 to i32
  %57 = icmp ne i32 %56, 10
  br i1 %57, label %58, label %61

58:                                               ; preds = %50, %45
  %59 = load %struct._IO_FILE*, %struct._IO_FILE** %7, align 8
  %60 = call i32 @fputc(i32 noundef 10, %struct._IO_FILE* noundef %59)
  br label %61

61:                                               ; preds = %58, %50
  %62 = load %struct._IO_FILE*, %struct._IO_FILE** %7, align 8
  %63 = call i32 @fputc(i32 noundef 0, %struct._IO_FILE* noundef %62)
  %64 = load %struct._IO_FILE*, %struct._IO_FILE** %7, align 8
  %65 = call i32 @fclose(%struct._IO_FILE* noundef %64)
  %66 = load i8*, i8** %5, align 8
  store i8* %66, i8** %2, align 8
  br label %67

67:                                               ; preds = %61, %20
  %68 = load i8*, i8** %2, align 8
  ret i8* %68
}

; Function Attrs: nounwind readonly willreturn
declare i32 @memcmp(i8* noundef, i8* noundef, i64 noundef) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal void @canonicalize_newline(i8* noundef %0) #4 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  store i32 0, i32* %3, align 4
  store i32 0, i32* %4, align 4
  br label %5

5:                                                ; preds = %66, %1
  %6 = load i8*, i8** %2, align 8
  %7 = load i32, i32* %3, align 4
  %8 = sext i32 %7 to i64
  %9 = getelementptr inbounds i8, i8* %6, i64 %8
  %10 = load i8, i8* %9, align 1
  %11 = icmp ne i8 %10, 0
  br i1 %11, label %12, label %67

12:                                               ; preds = %5
  %13 = load i8*, i8** %2, align 8
  %14 = load i32, i32* %3, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds i8, i8* %13, i64 %15
  %17 = load i8, i8* %16, align 1
  %18 = sext i8 %17 to i32
  %19 = icmp eq i32 %18, 13
  br i1 %19, label %20, label %37

20:                                               ; preds = %12
  %21 = load i8*, i8** %2, align 8
  %22 = load i32, i32* %3, align 4
  %23 = add nsw i32 %22, 1
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds i8, i8* %21, i64 %24
  %26 = load i8, i8* %25, align 1
  %27 = sext i8 %26 to i32
  %28 = icmp eq i32 %27, 10
  br i1 %28, label %29, label %37

29:                                               ; preds = %20
  %30 = load i32, i32* %3, align 4
  %31 = add nsw i32 %30, 2
  store i32 %31, i32* %3, align 4
  %32 = load i8*, i8** %2, align 8
  %33 = load i32, i32* %4, align 4
  %34 = add nsw i32 %33, 1
  store i32 %34, i32* %4, align 4
  %35 = sext i32 %33 to i64
  %36 = getelementptr inbounds i8, i8* %32, i64 %35
  store i8 10, i8* %36, align 1
  br label %66

37:                                               ; preds = %20, %12
  %38 = load i8*, i8** %2, align 8
  %39 = load i32, i32* %3, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds i8, i8* %38, i64 %40
  %42 = load i8, i8* %41, align 1
  %43 = sext i8 %42 to i32
  %44 = icmp eq i32 %43, 13
  br i1 %44, label %45, label %53

45:                                               ; preds = %37
  %46 = load i32, i32* %3, align 4
  %47 = add nsw i32 %46, 1
  store i32 %47, i32* %3, align 4
  %48 = load i8*, i8** %2, align 8
  %49 = load i32, i32* %4, align 4
  %50 = add nsw i32 %49, 1
  store i32 %50, i32* %4, align 4
  %51 = sext i32 %49 to i64
  %52 = getelementptr inbounds i8, i8* %48, i64 %51
  store i8 10, i8* %52, align 1
  br label %65

53:                                               ; preds = %37
  %54 = load i8*, i8** %2, align 8
  %55 = load i32, i32* %3, align 4
  %56 = add nsw i32 %55, 1
  store i32 %56, i32* %3, align 4
  %57 = sext i32 %55 to i64
  %58 = getelementptr inbounds i8, i8* %54, i64 %57
  %59 = load i8, i8* %58, align 1
  %60 = load i8*, i8** %2, align 8
  %61 = load i32, i32* %4, align 4
  %62 = add nsw i32 %61, 1
  store i32 %62, i32* %4, align 4
  %63 = sext i32 %61 to i64
  %64 = getelementptr inbounds i8, i8* %60, i64 %63
  store i8 %59, i8* %64, align 1
  br label %65

65:                                               ; preds = %53, %45
  br label %66

66:                                               ; preds = %65, %29
  br label %5, !llvm.loop !19

67:                                               ; preds = %5
  %68 = load i8*, i8** %2, align 8
  %69 = load i32, i32* %4, align 4
  %70 = sext i32 %69 to i64
  %71 = getelementptr inbounds i8, i8* %68, i64 %70
  store i8 0, i8* %71, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @remove_backslash_newline(i8* noundef %0) #4 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  store i32 0, i32* %3, align 4
  store i32 0, i32* %4, align 4
  store i32 0, i32* %5, align 4
  br label %6

6:                                                ; preds = %81, %1
  %7 = load i8*, i8** %2, align 8
  %8 = load i32, i32* %3, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds i8, i8* %7, i64 %9
  %11 = load i8, i8* %10, align 1
  %12 = icmp ne i8 %11, 0
  br i1 %12, label %13, label %82

13:                                               ; preds = %6
  %14 = load i8*, i8** %2, align 8
  %15 = load i32, i32* %3, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds i8, i8* %14, i64 %16
  %18 = load i8, i8* %17, align 1
  %19 = sext i8 %18 to i32
  %20 = icmp eq i32 %19, 92
  br i1 %20, label %21, label %35

21:                                               ; preds = %13
  %22 = load i8*, i8** %2, align 8
  %23 = load i32, i32* %3, align 4
  %24 = add nsw i32 %23, 1
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i8, i8* %22, i64 %25
  %27 = load i8, i8* %26, align 1
  %28 = sext i8 %27 to i32
  %29 = icmp eq i32 %28, 10
  br i1 %29, label %30, label %35

30:                                               ; preds = %21
  %31 = load i32, i32* %3, align 4
  %32 = add nsw i32 %31, 2
  store i32 %32, i32* %3, align 4
  %33 = load i32, i32* %5, align 4
  %34 = add nsw i32 %33, 1
  store i32 %34, i32* %5, align 4
  br label %81

35:                                               ; preds = %21, %13
  %36 = load i8*, i8** %2, align 8
  %37 = load i32, i32* %3, align 4
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds i8, i8* %36, i64 %38
  %40 = load i8, i8* %39, align 1
  %41 = sext i8 %40 to i32
  %42 = icmp eq i32 %41, 10
  br i1 %42, label %43, label %68

43:                                               ; preds = %35
  %44 = load i8*, i8** %2, align 8
  %45 = load i32, i32* %3, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, i32* %3, align 4
  %47 = sext i32 %45 to i64
  %48 = getelementptr inbounds i8, i8* %44, i64 %47
  %49 = load i8, i8* %48, align 1
  %50 = load i8*, i8** %2, align 8
  %51 = load i32, i32* %4, align 4
  %52 = add nsw i32 %51, 1
  store i32 %52, i32* %4, align 4
  %53 = sext i32 %51 to i64
  %54 = getelementptr inbounds i8, i8* %50, i64 %53
  store i8 %49, i8* %54, align 1
  br label %55

55:                                               ; preds = %64, %43
  %56 = load i32, i32* %5, align 4
  %57 = icmp sgt i32 %56, 0
  br i1 %57, label %58, label %67

58:                                               ; preds = %55
  %59 = load i8*, i8** %2, align 8
  %60 = load i32, i32* %4, align 4
  %61 = add nsw i32 %60, 1
  store i32 %61, i32* %4, align 4
  %62 = sext i32 %60 to i64
  %63 = getelementptr inbounds i8, i8* %59, i64 %62
  store i8 10, i8* %63, align 1
  br label %64

64:                                               ; preds = %58
  %65 = load i32, i32* %5, align 4
  %66 = add nsw i32 %65, -1
  store i32 %66, i32* %5, align 4
  br label %55, !llvm.loop !20

67:                                               ; preds = %55
  br label %80

68:                                               ; preds = %35
  %69 = load i8*, i8** %2, align 8
  %70 = load i32, i32* %3, align 4
  %71 = add nsw i32 %70, 1
  store i32 %71, i32* %3, align 4
  %72 = sext i32 %70 to i64
  %73 = getelementptr inbounds i8, i8* %69, i64 %72
  %74 = load i8, i8* %73, align 1
  %75 = load i8*, i8** %2, align 8
  %76 = load i32, i32* %4, align 4
  %77 = add nsw i32 %76, 1
  store i32 %77, i32* %4, align 4
  %78 = sext i32 %76 to i64
  %79 = getelementptr inbounds i8, i8* %75, i64 %78
  store i8 %74, i8* %79, align 1
  br label %80

80:                                               ; preds = %68, %67
  br label %81

81:                                               ; preds = %80, %30
  br label %6, !llvm.loop !21

82:                                               ; preds = %6
  br label %83

83:                                               ; preds = %92, %82
  %84 = load i32, i32* %5, align 4
  %85 = icmp sgt i32 %84, 0
  br i1 %85, label %86, label %95

86:                                               ; preds = %83
  %87 = load i8*, i8** %2, align 8
  %88 = load i32, i32* %4, align 4
  %89 = add nsw i32 %88, 1
  store i32 %89, i32* %4, align 4
  %90 = sext i32 %88 to i64
  %91 = getelementptr inbounds i8, i8* %87, i64 %90
  store i8 10, i8* %91, align 1
  br label %92

92:                                               ; preds = %86
  %93 = load i32, i32* %5, align 4
  %94 = add nsw i32 %93, -1
  store i32 %94, i32* %5, align 4
  br label %83, !llvm.loop !22

95:                                               ; preds = %83
  %96 = load i8*, i8** %2, align 8
  %97 = load i32, i32* %4, align 4
  %98 = sext i32 %97 to i64
  %99 = getelementptr inbounds i8, i8* %96, i64 %98
  store i8 0, i8* %99, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @convert_universal_chars(i8* noundef %0) #4 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  %6 = load i8*, i8** %2, align 8
  store i8* %6, i8** %3, align 8
  br label %7

7:                                                ; preds = %86, %1
  %8 = load i8*, i8** %2, align 8
  %9 = load i8, i8* %8, align 1
  %10 = icmp ne i8 %9, 0
  br i1 %10, label %11, label %87

11:                                               ; preds = %7
  %12 = load i8*, i8** %2, align 8
  %13 = call zeroext i1 @startswith(i8* noundef %12, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.117, i64 0, i64 0))
  br i1 %13, label %14, label %36

14:                                               ; preds = %11
  %15 = load i8*, i8** %2, align 8
  %16 = getelementptr inbounds i8, i8* %15, i64 2
  %17 = call i32 @read_universal_char(i8* noundef %16, i32 noundef 4)
  store i32 %17, i32* %4, align 4
  %18 = load i32, i32* %4, align 4
  %19 = icmp ne i32 %18, 0
  br i1 %19, label %20, label %29

20:                                               ; preds = %14
  %21 = load i8*, i8** %2, align 8
  %22 = getelementptr inbounds i8, i8* %21, i64 6
  store i8* %22, i8** %2, align 8
  %23 = load i8*, i8** %3, align 8
  %24 = load i32, i32* %4, align 4
  %25 = call i32 @encode_utf8(i8* noundef %23, i32 noundef %24)
  %26 = load i8*, i8** %3, align 8
  %27 = sext i32 %25 to i64
  %28 = getelementptr inbounds i8, i8* %26, i64 %27
  store i8* %28, i8** %3, align 8
  br label %35

29:                                               ; preds = %14
  %30 = load i8*, i8** %2, align 8
  %31 = getelementptr inbounds i8, i8* %30, i32 1
  store i8* %31, i8** %2, align 8
  %32 = load i8, i8* %30, align 1
  %33 = load i8*, i8** %3, align 8
  %34 = getelementptr inbounds i8, i8* %33, i32 1
  store i8* %34, i8** %3, align 8
  store i8 %32, i8* %33, align 1
  br label %35

35:                                               ; preds = %29, %20
  br label %86

36:                                               ; preds = %11
  %37 = load i8*, i8** %2, align 8
  %38 = call zeroext i1 @startswith(i8* noundef %37, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.118, i64 0, i64 0))
  br i1 %38, label %39, label %61

39:                                               ; preds = %36
  %40 = load i8*, i8** %2, align 8
  %41 = getelementptr inbounds i8, i8* %40, i64 2
  %42 = call i32 @read_universal_char(i8* noundef %41, i32 noundef 8)
  store i32 %42, i32* %5, align 4
  %43 = load i32, i32* %5, align 4
  %44 = icmp ne i32 %43, 0
  br i1 %44, label %45, label %54

45:                                               ; preds = %39
  %46 = load i8*, i8** %2, align 8
  %47 = getelementptr inbounds i8, i8* %46, i64 10
  store i8* %47, i8** %2, align 8
  %48 = load i8*, i8** %3, align 8
  %49 = load i32, i32* %5, align 4
  %50 = call i32 @encode_utf8(i8* noundef %48, i32 noundef %49)
  %51 = load i8*, i8** %3, align 8
  %52 = sext i32 %50 to i64
  %53 = getelementptr inbounds i8, i8* %51, i64 %52
  store i8* %53, i8** %3, align 8
  br label %60

54:                                               ; preds = %39
  %55 = load i8*, i8** %2, align 8
  %56 = getelementptr inbounds i8, i8* %55, i32 1
  store i8* %56, i8** %2, align 8
  %57 = load i8, i8* %55, align 1
  %58 = load i8*, i8** %3, align 8
  %59 = getelementptr inbounds i8, i8* %58, i32 1
  store i8* %59, i8** %3, align 8
  store i8 %57, i8* %58, align 1
  br label %60

60:                                               ; preds = %54, %45
  br label %85

61:                                               ; preds = %36
  %62 = load i8*, i8** %2, align 8
  %63 = getelementptr inbounds i8, i8* %62, i64 0
  %64 = load i8, i8* %63, align 1
  %65 = sext i8 %64 to i32
  %66 = icmp eq i32 %65, 92
  br i1 %66, label %67, label %78

67:                                               ; preds = %61
  %68 = load i8*, i8** %2, align 8
  %69 = getelementptr inbounds i8, i8* %68, i32 1
  store i8* %69, i8** %2, align 8
  %70 = load i8, i8* %68, align 1
  %71 = load i8*, i8** %3, align 8
  %72 = getelementptr inbounds i8, i8* %71, i32 1
  store i8* %72, i8** %3, align 8
  store i8 %70, i8* %71, align 1
  %73 = load i8*, i8** %2, align 8
  %74 = getelementptr inbounds i8, i8* %73, i32 1
  store i8* %74, i8** %2, align 8
  %75 = load i8, i8* %73, align 1
  %76 = load i8*, i8** %3, align 8
  %77 = getelementptr inbounds i8, i8* %76, i32 1
  store i8* %77, i8** %3, align 8
  store i8 %75, i8* %76, align 1
  br label %84

78:                                               ; preds = %61
  %79 = load i8*, i8** %2, align 8
  %80 = getelementptr inbounds i8, i8* %79, i32 1
  store i8* %80, i8** %2, align 8
  %81 = load i8, i8* %79, align 1
  %82 = load i8*, i8** %3, align 8
  %83 = getelementptr inbounds i8, i8* %82, i32 1
  store i8* %83, i8** %3, align 8
  store i8 %81, i8* %82, align 1
  br label %84

84:                                               ; preds = %78, %67
  br label %85

85:                                               ; preds = %84, %60
  br label %86

86:                                               ; preds = %85, %35
  br label %7, !llvm.loop !23

87:                                               ; preds = %7
  %88 = load i8*, i8** %3, align 8
  store i8 0, i8* %88, align 1
  ret void
}

; Function Attrs: nounwind
declare i8* @realloc(i8* noundef, i64 noundef) #8

declare i32 @display_width(i8* noundef, i32 noundef) #2

declare void @hashmap_put(%struct.HashMap* noundef, i8* noundef, i8* noundef) #2

declare i8* @hashmap_get2(%struct.HashMap* noundef, i8* noundef, i32 noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @convert_pp_int(%struct.Token* noundef %0) #4 {
  %2 = alloca i1, align 1
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i64, align 8
  %7 = alloca i8, align 1
  %8 = alloca i8, align 1
  %9 = alloca %struct.Type*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 4
  %12 = load i8*, i8** %11, align 16
  store i8* %12, i8** %4, align 8
  store i32 10, i32* %5, align 4
  %13 = load i8*, i8** %4, align 8
  %14 = call i32 @strncasecmp(i8* noundef %13, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.71, i64 0, i64 0), i64 noundef 2) #10
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %32, label %16

16:                                               ; preds = %1
  %17 = call i16** @__ctype_b_loc() #13
  %18 = load i16*, i16** %17, align 8
  %19 = load i8*, i8** %4, align 8
  %20 = getelementptr inbounds i8, i8* %19, i64 2
  %21 = load i8, i8* %20, align 1
  %22 = sext i8 %21 to i32
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds i16, i16* %18, i64 %23
  %25 = load i16, i16* %24, align 2
  %26 = zext i16 %25 to i32
  %27 = and i32 %26, 4096
  %28 = icmp ne i32 %27, 0
  br i1 %28, label %29, label %32

29:                                               ; preds = %16
  %30 = load i8*, i8** %4, align 8
  %31 = getelementptr inbounds i8, i8* %30, i64 2
  store i8* %31, i8** %4, align 8
  store i32 16, i32* %5, align 4
  br label %59

32:                                               ; preds = %16, %1
  %33 = load i8*, i8** %4, align 8
  %34 = call i32 @strncasecmp(i8* noundef %33, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.72, i64 0, i64 0), i64 noundef 2) #10
  %35 = icmp ne i32 %34, 0
  br i1 %35, label %51, label %36

36:                                               ; preds = %32
  %37 = load i8*, i8** %4, align 8
  %38 = getelementptr inbounds i8, i8* %37, i64 2
  %39 = load i8, i8* %38, align 1
  %40 = sext i8 %39 to i32
  %41 = icmp eq i32 %40, 48
  br i1 %41, label %48, label %42

42:                                               ; preds = %36
  %43 = load i8*, i8** %4, align 8
  %44 = getelementptr inbounds i8, i8* %43, i64 2
  %45 = load i8, i8* %44, align 1
  %46 = sext i8 %45 to i32
  %47 = icmp eq i32 %46, 49
  br i1 %47, label %48, label %51

48:                                               ; preds = %42, %36
  %49 = load i8*, i8** %4, align 8
  %50 = getelementptr inbounds i8, i8* %49, i64 2
  store i8* %50, i8** %4, align 8
  store i32 2, i32* %5, align 4
  br label %58

51:                                               ; preds = %42, %32
  %52 = load i8*, i8** %4, align 8
  %53 = load i8, i8* %52, align 1
  %54 = sext i8 %53 to i32
  %55 = icmp eq i32 %54, 48
  br i1 %55, label %56, label %57

56:                                               ; preds = %51
  store i32 8, i32* %5, align 4
  br label %57

57:                                               ; preds = %56, %51
  br label %58

58:                                               ; preds = %57, %48
  br label %59

59:                                               ; preds = %58, %29
  %60 = load i8*, i8** %4, align 8
  %61 = load i32, i32* %5, align 4
  %62 = call i64 @strtoul(i8* noundef %60, i8** noundef %4, i32 noundef %61) #12
  store i64 %62, i64* %6, align 8
  store i8 0, i8* %7, align 1
  store i8 0, i8* %8, align 1
  %63 = load i8*, i8** %4, align 8
  %64 = call zeroext i1 @startswith(i8* noundef %63, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.73, i64 0, i64 0))
  br i1 %64, label %86, label %65

65:                                               ; preds = %59
  %66 = load i8*, i8** %4, align 8
  %67 = call zeroext i1 @startswith(i8* noundef %66, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.74, i64 0, i64 0))
  br i1 %67, label %86, label %68

68:                                               ; preds = %65
  %69 = load i8*, i8** %4, align 8
  %70 = call zeroext i1 @startswith(i8* noundef %69, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.75, i64 0, i64 0))
  br i1 %70, label %86, label %71

71:                                               ; preds = %68
  %72 = load i8*, i8** %4, align 8
  %73 = call zeroext i1 @startswith(i8* noundef %72, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.76, i64 0, i64 0))
  br i1 %73, label %86, label %74

74:                                               ; preds = %71
  %75 = load i8*, i8** %4, align 8
  %76 = call zeroext i1 @startswith(i8* noundef %75, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0))
  br i1 %76, label %86, label %77

77:                                               ; preds = %74
  %78 = load i8*, i8** %4, align 8
  %79 = call zeroext i1 @startswith(i8* noundef %78, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.78, i64 0, i64 0))
  br i1 %79, label %86, label %80

80:                                               ; preds = %77
  %81 = load i8*, i8** %4, align 8
  %82 = call zeroext i1 @startswith(i8* noundef %81, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.79, i64 0, i64 0))
  br i1 %82, label %86, label %83

83:                                               ; preds = %80
  %84 = load i8*, i8** %4, align 8
  %85 = call zeroext i1 @startswith(i8* noundef %84, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.80, i64 0, i64 0))
  br i1 %85, label %86, label %89

86:                                               ; preds = %83, %80, %77, %74, %71, %68, %65, %59
  %87 = load i8*, i8** %4, align 8
  %88 = getelementptr inbounds i8, i8* %87, i64 3
  store i8* %88, i8** %4, align 8
  store i8 1, i8* %8, align 1
  store i8 1, i8* %7, align 1
  br label %139

89:                                               ; preds = %83
  %90 = load i8*, i8** %4, align 8
  %91 = call i32 @strncasecmp(i8* noundef %90, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.81, i64 0, i64 0), i64 noundef 2) #10
  %92 = icmp ne i32 %91, 0
  br i1 %92, label %93, label %97

93:                                               ; preds = %89
  %94 = load i8*, i8** %4, align 8
  %95 = call i32 @strncasecmp(i8* noundef %94, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.82, i64 0, i64 0), i64 noundef 2) #10
  %96 = icmp ne i32 %95, 0
  br i1 %96, label %100, label %97

97:                                               ; preds = %93, %89
  %98 = load i8*, i8** %4, align 8
  %99 = getelementptr inbounds i8, i8* %98, i64 2
  store i8* %99, i8** %4, align 8
  store i8 1, i8* %8, align 1
  store i8 1, i8* %7, align 1
  br label %138

100:                                              ; preds = %93
  %101 = load i8*, i8** %4, align 8
  %102 = call zeroext i1 @startswith(i8* noundef %101, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.83, i64 0, i64 0))
  br i1 %102, label %106, label %103

103:                                              ; preds = %100
  %104 = load i8*, i8** %4, align 8
  %105 = call zeroext i1 @startswith(i8* noundef %104, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.84, i64 0, i64 0))
  br i1 %105, label %106, label %109

106:                                              ; preds = %103, %100
  %107 = load i8*, i8** %4, align 8
  %108 = getelementptr inbounds i8, i8* %107, i64 2
  store i8* %108, i8** %4, align 8
  store i8 1, i8* %7, align 1
  br label %137

109:                                              ; preds = %103
  %110 = load i8*, i8** %4, align 8
  %111 = load i8, i8* %110, align 1
  %112 = sext i8 %111 to i32
  %113 = icmp eq i32 %112, 76
  br i1 %113, label %119, label %114

114:                                              ; preds = %109
  %115 = load i8*, i8** %4, align 8
  %116 = load i8, i8* %115, align 1
  %117 = sext i8 %116 to i32
  %118 = icmp eq i32 %117, 108
  br i1 %118, label %119, label %122

119:                                              ; preds = %114, %109
  %120 = load i8*, i8** %4, align 8
  %121 = getelementptr inbounds i8, i8* %120, i32 1
  store i8* %121, i8** %4, align 8
  store i8 1, i8* %7, align 1
  br label %136

122:                                              ; preds = %114
  %123 = load i8*, i8** %4, align 8
  %124 = load i8, i8* %123, align 1
  %125 = sext i8 %124 to i32
  %126 = icmp eq i32 %125, 85
  br i1 %126, label %132, label %127

127:                                              ; preds = %122
  %128 = load i8*, i8** %4, align 8
  %129 = load i8, i8* %128, align 1
  %130 = sext i8 %129 to i32
  %131 = icmp eq i32 %130, 117
  br i1 %131, label %132, label %135

132:                                              ; preds = %127, %122
  %133 = load i8*, i8** %4, align 8
  %134 = getelementptr inbounds i8, i8* %133, i32 1
  store i8* %134, i8** %4, align 8
  store i8 1, i8* %8, align 1
  br label %135

135:                                              ; preds = %132, %127
  br label %136

136:                                              ; preds = %135, %119
  br label %137

137:                                              ; preds = %136, %106
  br label %138

138:                                              ; preds = %137, %97
  br label %139

139:                                              ; preds = %138, %86
  %140 = load i8*, i8** %4, align 8
  %141 = load %struct.Token*, %struct.Token** %3, align 8
  %142 = getelementptr inbounds %struct.Token, %struct.Token* %141, i32 0, i32 4
  %143 = load i8*, i8** %142, align 16
  %144 = load %struct.Token*, %struct.Token** %3, align 8
  %145 = getelementptr inbounds %struct.Token, %struct.Token* %144, i32 0, i32 5
  %146 = load i32, i32* %145, align 8
  %147 = sext i32 %146 to i64
  %148 = getelementptr inbounds i8, i8* %143, i64 %147
  %149 = icmp ne i8* %140, %148
  br i1 %149, label %150, label %151

150:                                              ; preds = %139
  store i1 false, i1* %2, align 1
  br label %262

151:                                              ; preds = %139
  %152 = load i32, i32* %5, align 4
  %153 = icmp eq i32 %152, 10
  br i1 %153, label %154, label %193

154:                                              ; preds = %151
  %155 = load i8, i8* %7, align 1
  %156 = trunc i8 %155 to i1
  br i1 %156, label %157, label %162

157:                                              ; preds = %154
  %158 = load i8, i8* %8, align 1
  %159 = trunc i8 %158 to i1
  br i1 %159, label %160, label %162

160:                                              ; preds = %157
  %161 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  store %struct.Type* %161, %struct.Type** %9, align 8
  br label %192

162:                                              ; preds = %157, %154
  %163 = load i8, i8* %7, align 1
  %164 = trunc i8 %163 to i1
  br i1 %164, label %165, label %167

165:                                              ; preds = %162
  %166 = load %struct.Type*, %struct.Type** @ty_long, align 8
  store %struct.Type* %166, %struct.Type** %9, align 8
  br label %191

167:                                              ; preds = %162
  %168 = load i8, i8* %8, align 1
  %169 = trunc i8 %168 to i1
  br i1 %169, label %170, label %180

170:                                              ; preds = %167
  %171 = load i64, i64* %6, align 8
  %172 = ashr i64 %171, 32
  %173 = icmp ne i64 %172, 0
  br i1 %173, label %174, label %176

174:                                              ; preds = %170
  %175 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  br label %178

176:                                              ; preds = %170
  %177 = load %struct.Type*, %struct.Type** @ty_uint, align 8
  br label %178

178:                                              ; preds = %176, %174
  %179 = phi %struct.Type* [ %175, %174 ], [ %177, %176 ]
  store %struct.Type* %179, %struct.Type** %9, align 8
  br label %190

180:                                              ; preds = %167
  %181 = load i64, i64* %6, align 8
  %182 = ashr i64 %181, 31
  %183 = icmp ne i64 %182, 0
  br i1 %183, label %184, label %186

184:                                              ; preds = %180
  %185 = load %struct.Type*, %struct.Type** @ty_long, align 8
  br label %188

186:                                              ; preds = %180
  %187 = load %struct.Type*, %struct.Type** @ty_int, align 8
  br label %188

188:                                              ; preds = %186, %184
  %189 = phi %struct.Type* [ %185, %184 ], [ %187, %186 ]
  store %struct.Type* %189, %struct.Type** %9, align 8
  br label %190

190:                                              ; preds = %188, %178
  br label %191

191:                                              ; preds = %190, %165
  br label %192

192:                                              ; preds = %191, %160
  br label %253

193:                                              ; preds = %151
  %194 = load i8, i8* %7, align 1
  %195 = trunc i8 %194 to i1
  br i1 %195, label %196, label %201

196:                                              ; preds = %193
  %197 = load i8, i8* %8, align 1
  %198 = trunc i8 %197 to i1
  br i1 %198, label %199, label %201

199:                                              ; preds = %196
  %200 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  store %struct.Type* %200, %struct.Type** %9, align 8
  br label %252

201:                                              ; preds = %196, %193
  %202 = load i8, i8* %7, align 1
  %203 = trunc i8 %202 to i1
  br i1 %203, label %204, label %214

204:                                              ; preds = %201
  %205 = load i64, i64* %6, align 8
  %206 = ashr i64 %205, 63
  %207 = icmp ne i64 %206, 0
  br i1 %207, label %208, label %210

208:                                              ; preds = %204
  %209 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  br label %212

210:                                              ; preds = %204
  %211 = load %struct.Type*, %struct.Type** @ty_long, align 8
  br label %212

212:                                              ; preds = %210, %208
  %213 = phi %struct.Type* [ %209, %208 ], [ %211, %210 ]
  store %struct.Type* %213, %struct.Type** %9, align 8
  br label %251

214:                                              ; preds = %201
  %215 = load i8, i8* %8, align 1
  %216 = trunc i8 %215 to i1
  br i1 %216, label %217, label %227

217:                                              ; preds = %214
  %218 = load i64, i64* %6, align 8
  %219 = ashr i64 %218, 32
  %220 = icmp ne i64 %219, 0
  br i1 %220, label %221, label %223

221:                                              ; preds = %217
  %222 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  br label %225

223:                                              ; preds = %217
  %224 = load %struct.Type*, %struct.Type** @ty_uint, align 8
  br label %225

225:                                              ; preds = %223, %221
  %226 = phi %struct.Type* [ %222, %221 ], [ %224, %223 ]
  store %struct.Type* %226, %struct.Type** %9, align 8
  br label %250

227:                                              ; preds = %214
  %228 = load i64, i64* %6, align 8
  %229 = ashr i64 %228, 63
  %230 = icmp ne i64 %229, 0
  br i1 %230, label %231, label %233

231:                                              ; preds = %227
  %232 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  store %struct.Type* %232, %struct.Type** %9, align 8
  br label %249

233:                                              ; preds = %227
  %234 = load i64, i64* %6, align 8
  %235 = ashr i64 %234, 32
  %236 = icmp ne i64 %235, 0
  br i1 %236, label %237, label %239

237:                                              ; preds = %233
  %238 = load %struct.Type*, %struct.Type** @ty_long, align 8
  store %struct.Type* %238, %struct.Type** %9, align 8
  br label %248

239:                                              ; preds = %233
  %240 = load i64, i64* %6, align 8
  %241 = ashr i64 %240, 31
  %242 = icmp ne i64 %241, 0
  br i1 %242, label %243, label %245

243:                                              ; preds = %239
  %244 = load %struct.Type*, %struct.Type** @ty_uint, align 8
  store %struct.Type* %244, %struct.Type** %9, align 8
  br label %247

245:                                              ; preds = %239
  %246 = load %struct.Type*, %struct.Type** @ty_int, align 8
  store %struct.Type* %246, %struct.Type** %9, align 8
  br label %247

247:                                              ; preds = %245, %243
  br label %248

248:                                              ; preds = %247, %237
  br label %249

249:                                              ; preds = %248, %231
  br label %250

250:                                              ; preds = %249, %225
  br label %251

251:                                              ; preds = %250, %212
  br label %252

252:                                              ; preds = %251, %199
  br label %253

253:                                              ; preds = %252, %192
  %254 = load %struct.Token*, %struct.Token** %3, align 8
  %255 = getelementptr inbounds %struct.Token, %struct.Token* %254, i32 0, i32 0
  store i32 4, i32* %255, align 16
  %256 = load i64, i64* %6, align 8
  %257 = load %struct.Token*, %struct.Token** %3, align 8
  %258 = getelementptr inbounds %struct.Token, %struct.Token* %257, i32 0, i32 2
  store i64 %256, i64* %258, align 16
  %259 = load %struct.Type*, %struct.Type** %9, align 8
  %260 = load %struct.Token*, %struct.Token** %3, align 8
  %261 = getelementptr inbounds %struct.Token, %struct.Token* %260, i32 0, i32 6
  store %struct.Type* %259, %struct.Type** %261, align 16
  store i1 true, i1* %2, align 1
  br label %262

262:                                              ; preds = %253, %150
  %263 = load i1, i1* %2, align 1
  ret i1 %263
}

; Function Attrs: nounwind
declare x86_fp80 @strtold(i8* noundef, i8** noundef) #8

; Function Attrs: nounwind readonly willreturn
declare i32 @strncasecmp(i8* noundef, i8* noundef, i64 noundef) #5

; Function Attrs: nounwind
declare i64 @strtoul(i8* noundef, i8** noundef, i32 noundef) #8

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @string_literal_end(i8* noundef %0) #4 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  store i8* %4, i8** %3, align 8
  br label %5

5:                                                ; preds = %31, %1
  %6 = load i8*, i8** %2, align 8
  %7 = load i8, i8* %6, align 1
  %8 = sext i8 %7 to i32
  %9 = icmp ne i32 %8, 34
  br i1 %9, label %10, label %34

10:                                               ; preds = %5
  %11 = load i8*, i8** %2, align 8
  %12 = load i8, i8* %11, align 1
  %13 = sext i8 %12 to i32
  %14 = icmp eq i32 %13, 10
  br i1 %14, label %20, label %15

15:                                               ; preds = %10
  %16 = load i8*, i8** %2, align 8
  %17 = load i8, i8* %16, align 1
  %18 = sext i8 %17 to i32
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %20, label %22

20:                                               ; preds = %15, %10
  %21 = load i8*, i8** %3, align 8
  call void (i8*, i8*, ...) @error_at(i8* noundef %21, i8* noundef getelementptr inbounds ([52 x i8], [52 x i8]* @.str.86, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

22:                                               ; preds = %15
  %23 = load i8*, i8** %2, align 8
  %24 = load i8, i8* %23, align 1
  %25 = sext i8 %24 to i32
  %26 = icmp eq i32 %25, 92
  br i1 %26, label %27, label %30

27:                                               ; preds = %22
  %28 = load i8*, i8** %2, align 8
  %29 = getelementptr inbounds i8, i8* %28, i32 1
  store i8* %29, i8** %2, align 8
  br label %30

30:                                               ; preds = %27, %22
  br label %31

31:                                               ; preds = %30
  %32 = load i8*, i8** %2, align 8
  %33 = getelementptr inbounds i8, i8* %32, i32 1
  store i8* %33, i8** %2, align 8
  br label %5, !llvm.loop !24

34:                                               ; preds = %5
  %35 = load i8*, i8** %2, align 8
  ret i8* %35
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @read_escaped_char(i8** noundef %0, i8* noundef %1) #4 {
  %3 = alloca i32, align 4
  %4 = alloca i8**, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i8** %0, i8*** %4, align 8
  store i8* %1, i8** %5, align 8
  %8 = load i8*, i8** %5, align 8
  %9 = load i8, i8* %8, align 1
  %10 = sext i8 %9 to i32
  %11 = icmp sle i32 48, %10
  br i1 %11, label %12, label %64

12:                                               ; preds = %2
  %13 = load i8*, i8** %5, align 8
  %14 = load i8, i8* %13, align 1
  %15 = sext i8 %14 to i32
  %16 = icmp sle i32 %15, 55
  br i1 %16, label %17, label %64

17:                                               ; preds = %12
  %18 = load i8*, i8** %5, align 8
  %19 = getelementptr inbounds i8, i8* %18, i32 1
  store i8* %19, i8** %5, align 8
  %20 = load i8, i8* %18, align 1
  %21 = sext i8 %20 to i32
  %22 = sub nsw i32 %21, 48
  store i32 %22, i32* %6, align 4
  %23 = load i8*, i8** %5, align 8
  %24 = load i8, i8* %23, align 1
  %25 = sext i8 %24 to i32
  %26 = icmp sle i32 48, %25
  br i1 %26, label %27, label %60

27:                                               ; preds = %17
  %28 = load i8*, i8** %5, align 8
  %29 = load i8, i8* %28, align 1
  %30 = sext i8 %29 to i32
  %31 = icmp sle i32 %30, 55
  br i1 %31, label %32, label %60

32:                                               ; preds = %27
  %33 = load i32, i32* %6, align 4
  %34 = shl i32 %33, 3
  %35 = load i8*, i8** %5, align 8
  %36 = getelementptr inbounds i8, i8* %35, i32 1
  store i8* %36, i8** %5, align 8
  %37 = load i8, i8* %35, align 1
  %38 = sext i8 %37 to i32
  %39 = sub nsw i32 %38, 48
  %40 = add nsw i32 %34, %39
  store i32 %40, i32* %6, align 4
  %41 = load i8*, i8** %5, align 8
  %42 = load i8, i8* %41, align 1
  %43 = sext i8 %42 to i32
  %44 = icmp sle i32 48, %43
  br i1 %44, label %45, label %59

45:                                               ; preds = %32
  %46 = load i8*, i8** %5, align 8
  %47 = load i8, i8* %46, align 1
  %48 = sext i8 %47 to i32
  %49 = icmp sle i32 %48, 55
  br i1 %49, label %50, label %59

50:                                               ; preds = %45
  %51 = load i32, i32* %6, align 4
  %52 = shl i32 %51, 3
  %53 = load i8*, i8** %5, align 8
  %54 = getelementptr inbounds i8, i8* %53, i32 1
  store i8* %54, i8** %5, align 8
  %55 = load i8, i8* %53, align 1
  %56 = sext i8 %55 to i32
  %57 = sub nsw i32 %56, 48
  %58 = add nsw i32 %52, %57
  store i32 %58, i32* %6, align 4
  br label %59

59:                                               ; preds = %50, %45, %32
  br label %60

60:                                               ; preds = %59, %27, %17
  %61 = load i8*, i8** %5, align 8
  %62 = load i8**, i8*** %4, align 8
  store i8* %61, i8** %62, align 8
  %63 = load i32, i32* %6, align 4
  store i32 %63, i32* %3, align 4
  br label %131

64:                                               ; preds = %12, %2
  %65 = load i8*, i8** %5, align 8
  %66 = load i8, i8* %65, align 1
  %67 = sext i8 %66 to i32
  %68 = icmp eq i32 %67, 120
  br i1 %68, label %69, label %112

69:                                               ; preds = %64
  %70 = load i8*, i8** %5, align 8
  %71 = getelementptr inbounds i8, i8* %70, i32 1
  store i8* %71, i8** %5, align 8
  %72 = call i16** @__ctype_b_loc() #13
  %73 = load i16*, i16** %72, align 8
  %74 = load i8*, i8** %5, align 8
  %75 = load i8, i8* %74, align 1
  %76 = sext i8 %75 to i32
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds i16, i16* %73, i64 %77
  %79 = load i16, i16* %78, align 2
  %80 = zext i16 %79 to i32
  %81 = and i32 %80, 4096
  %82 = icmp ne i32 %81, 0
  br i1 %82, label %85, label %83

83:                                               ; preds = %69
  %84 = load i8*, i8** %5, align 8
  call void (i8*, i8*, ...) @error_at(i8* noundef %84, i8* noundef getelementptr inbounds ([55 x i8], [55 x i8]* @.str.87, i64 0, i64 0), i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0)) #11
  unreachable

85:                                               ; preds = %69
  store i32 0, i32* %7, align 4
  br label %86

86:                                               ; preds = %105, %85
  %87 = call i16** @__ctype_b_loc() #13
  %88 = load i16*, i16** %87, align 8
  %89 = load i8*, i8** %5, align 8
  %90 = load i8, i8* %89, align 1
  %91 = sext i8 %90 to i32
  %92 = sext i32 %91 to i64
  %93 = getelementptr inbounds i16, i16* %88, i64 %92
  %94 = load i16, i16* %93, align 2
  %95 = zext i16 %94 to i32
  %96 = and i32 %95, 4096
  %97 = icmp ne i32 %96, 0
  br i1 %97, label %98, label %108

98:                                               ; preds = %86
  %99 = load i32, i32* %7, align 4
  %100 = shl i32 %99, 4
  %101 = load i8*, i8** %5, align 8
  %102 = load i8, i8* %101, align 1
  %103 = call i32 @from_hex(i8 noundef signext %102)
  %104 = add nsw i32 %100, %103
  store i32 %104, i32* %7, align 4
  br label %105

105:                                              ; preds = %98
  %106 = load i8*, i8** %5, align 8
  %107 = getelementptr inbounds i8, i8* %106, i32 1
  store i8* %107, i8** %5, align 8
  br label %86, !llvm.loop !25

108:                                              ; preds = %86
  %109 = load i8*, i8** %5, align 8
  %110 = load i8**, i8*** %4, align 8
  store i8* %109, i8** %110, align 8
  %111 = load i32, i32* %7, align 4
  store i32 %111, i32* %3, align 4
  br label %131

112:                                              ; preds = %64
  %113 = load i8*, i8** %5, align 8
  %114 = getelementptr inbounds i8, i8* %113, i64 1
  %115 = load i8**, i8*** %4, align 8
  store i8* %114, i8** %115, align 8
  %116 = load i8*, i8** %5, align 8
  %117 = load i8, i8* %116, align 1
  %118 = sext i8 %117 to i32
  switch i32 %118, label %127 [
    i32 97, label %119
    i32 98, label %120
    i32 116, label %121
    i32 110, label %122
    i32 118, label %123
    i32 102, label %124
    i32 114, label %125
    i32 101, label %126
  ]

119:                                              ; preds = %112
  store i32 7, i32* %3, align 4
  br label %131

120:                                              ; preds = %112
  store i32 8, i32* %3, align 4
  br label %131

121:                                              ; preds = %112
  store i32 9, i32* %3, align 4
  br label %131

122:                                              ; preds = %112
  store i32 10, i32* %3, align 4
  br label %131

123:                                              ; preds = %112
  store i32 11, i32* %3, align 4
  br label %131

124:                                              ; preds = %112
  store i32 12, i32* %3, align 4
  br label %131

125:                                              ; preds = %112
  store i32 13, i32* %3, align 4
  br label %131

126:                                              ; preds = %112
  store i32 27, i32* %3, align 4
  br label %131

127:                                              ; preds = %112
  %128 = load i8*, i8** %5, align 8
  %129 = load i8, i8* %128, align 1
  %130 = sext i8 %129 to i32
  store i32 %130, i32* %3, align 4
  br label %131

131:                                              ; preds = %127, %126, %125, %124, %123, %122, %121, %120, %119, %108, %60
  %132 = load i32, i32* %3, align 4
  ret i32 %132
}

declare i32 @decode_utf8(i8** noundef, i8* noundef) #2

declare %struct.Type* @array_of(%struct.Type* noundef, i32 noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @from_hex(i8 noundef signext %0) #4 {
  %2 = alloca i32, align 4
  %3 = alloca i8, align 1
  store i8 %0, i8* %3, align 1
  %4 = load i8, i8* %3, align 1
  %5 = sext i8 %4 to i32
  %6 = icmp sle i32 48, %5
  br i1 %6, label %7, label %15

7:                                                ; preds = %1
  %8 = load i8, i8* %3, align 1
  %9 = sext i8 %8 to i32
  %10 = icmp sle i32 %9, 57
  br i1 %10, label %11, label %15

11:                                               ; preds = %7
  %12 = load i8, i8* %3, align 1
  %13 = sext i8 %12 to i32
  %14 = sub nsw i32 %13, 48
  store i32 %14, i32* %2, align 4
  br label %33

15:                                               ; preds = %7, %1
  %16 = load i8, i8* %3, align 1
  %17 = sext i8 %16 to i32
  %18 = icmp sle i32 97, %17
  br i1 %18, label %19, label %28

19:                                               ; preds = %15
  %20 = load i8, i8* %3, align 1
  %21 = sext i8 %20 to i32
  %22 = icmp sle i32 %21, 102
  br i1 %22, label %23, label %28

23:                                               ; preds = %19
  %24 = load i8, i8* %3, align 1
  %25 = sext i8 %24 to i32
  %26 = sub nsw i32 %25, 97
  %27 = add nsw i32 %26, 10
  store i32 %27, i32* %2, align 4
  br label %33

28:                                               ; preds = %19, %15
  %29 = load i8, i8* %3, align 1
  %30 = sext i8 %29 to i32
  %31 = sub nsw i32 %30, 65
  %32 = add nsw i32 %31, 10
  store i32 %32, i32* %2, align 4
  br label %33

33:                                               ; preds = %28, %23, %11
  %34 = load i32, i32* %2, align 4
  ret i32 %34
}

declare zeroext i1 @is_ident3(i32 noundef) #2

declare zeroext i1 @is_ident1(i32 noundef) #2

declare zeroext i1 @is_ident2(i32 noundef) #2

; Function Attrs: nounwind readonly willreturn
declare i32 @strcmp(i8* noundef, i8* noundef) #5

declare noalias %struct._IO_FILE* @fopen(i8* noundef, i8* noundef) #2

; Function Attrs: nounwind
declare noalias %struct._IO_FILE* @open_memstream(i8** noundef, i64* noundef) #8

declare i64 @fread(i8* noundef, i64 noundef, i64 noundef, %struct._IO_FILE* noundef) #2

declare i64 @fwrite(i8* noundef, i64 noundef, i64 noundef, %struct._IO_FILE* noundef) #2

declare i32 @fclose(%struct._IO_FILE* noundef) #2

declare i32 @fflush(%struct._IO_FILE* noundef) #2

declare i32 @fputc(i32 noundef, %struct._IO_FILE* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @read_universal_char(i8* noundef %0, i32 noundef %1) #4 {
  %3 = alloca i32, align 4
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  store i32 %1, i32* %5, align 4
  store i32 0, i32* %6, align 4
  store i32 0, i32* %7, align 4
  br label %8

8:                                                ; preds = %38, %2
  %9 = load i32, i32* %7, align 4
  %10 = load i32, i32* %5, align 4
  %11 = icmp slt i32 %9, %10
  br i1 %11, label %12, label %41

12:                                               ; preds = %8
  %13 = call i16** @__ctype_b_loc() #13
  %14 = load i16*, i16** %13, align 8
  %15 = load i8*, i8** %4, align 8
  %16 = load i32, i32* %7, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds i8, i8* %15, i64 %17
  %19 = load i8, i8* %18, align 1
  %20 = sext i8 %19 to i32
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds i16, i16* %14, i64 %21
  %23 = load i16, i16* %22, align 2
  %24 = zext i16 %23 to i32
  %25 = and i32 %24, 4096
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %28, label %27

27:                                               ; preds = %12
  store i32 0, i32* %3, align 4
  br label %43

28:                                               ; preds = %12
  %29 = load i32, i32* %6, align 4
  %30 = shl i32 %29, 4
  %31 = load i8*, i8** %4, align 8
  %32 = load i32, i32* %7, align 4
  %33 = sext i32 %32 to i64
  %34 = getelementptr inbounds i8, i8* %31, i64 %33
  %35 = load i8, i8* %34, align 1
  %36 = call i32 @from_hex(i8 noundef signext %35)
  %37 = or i32 %30, %36
  store i32 %37, i32* %6, align 4
  br label %38

38:                                               ; preds = %28
  %39 = load i32, i32* %7, align 4
  %40 = add nsw i32 %39, 1
  store i32 %40, i32* %7, align 4
  br label %8, !llvm.loop !26

41:                                               ; preds = %8
  %42 = load i32, i32* %6, align 4
  store i32 %42, i32* %3, align 4
  br label %43

43:                                               ; preds = %41, %27
  %44 = load i32, i32* %3, align 4
  ret i32 %44
}

declare i32 @encode_utf8(i8* noundef, i32 noundef) #2

attributes #0 = { noinline noreturn nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind readonly willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { argmemonly nofree nounwind willreturn writeonly }
attributes #7 = { nounwind readnone willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #9 = { noreturn nounwind }
attributes #10 = { nounwind readonly willreturn }
attributes #11 = { noreturn }
attributes #12 = { nounwind }
attributes #13 = { nounwind readnone willreturn }

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
