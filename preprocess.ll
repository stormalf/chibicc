; ModuleID = 'preprocess.c'
source_filename = "preprocess.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.HashMap = type { %struct.HashEntry*, i32, i32 }
%struct.HashEntry = type { i8*, i32, i8* }
%struct.StringArray = type { i8**, i32, i32 }
%struct.CondIncl = type { %struct.CondIncl*, i32, %struct.Token*, i8 }
%struct.Token = type { i32, %struct.Token*, i64, x86_fp80, i8*, i32, %struct.Type*, i8*, %struct.File*, i8*, i32, i32, i8, i8, %struct.Hideset*, %struct.Token* }
%struct.Type = type { i32, i32, i32, i8, i8, i8, %struct.Type*, %struct.Type*, %struct.Type*, %struct.Token*, %struct.Token*, i32, %struct.Node*, %struct.Obj*, %struct.Member*, i8, i8, %struct.Type*, %struct.Type*, i8, %struct.Type* }
%struct.Node = type { i32, %struct.Node*, %struct.Type*, %struct.Token*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, i8*, i8*, %struct.Node*, %struct.Member*, %struct.Type*, %struct.Node*, i8, %struct.Obj*, i8*, i8*, %struct.Node*, %struct.Node*, %struct.Node*, i64, i64, i8*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Obj*, %struct.Node*, i8, %struct.Obj*, i64, x86_fp80, i32, [12 x i8] }
%struct.Obj = type { %struct.Obj*, i8*, i8*, %struct.Type*, %struct.Token*, i8, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8*, %struct.Relocation*, i8, %struct.Obj*, %struct.Node*, %struct.Obj*, %struct.Obj*, %struct.Obj*, i32, i8, i8, %struct.StringArray }
%struct.Relocation = type { %struct.Relocation*, i32, i8**, i64 }
%struct.Member = type { %struct.Member*, %struct.Type*, %struct.Token*, %struct.Token*, i32, i32, i32, i8, i32, i32 }
%struct.File = type { i8*, i32, i8*, i8*, i32 }
%struct.Hideset = type { %struct.Hideset*, i8* }
%struct.Macro = type { i8*, i8, %struct.MacroParam*, i8*, %struct.Token*, %struct.Token* (%struct.Token*)* }
%struct.MacroParam = type { %struct.MacroParam*, i8* }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.MacroArg = type { %struct.MacroArg*, i8*, i8, %struct.Token* }

@search_include_paths.cache = internal global %struct.HashMap zeroinitializer, align 8
@include_paths = external global %struct.StringArray, align 8
@.str = private unnamed_addr constant [6 x i8] c"%s/%s\00", align 1
@include_next_idx = internal global i32 0, align 4
@.str.1 = private unnamed_addr constant [16 x i8] c"__has_attribute\00", align 1
@.str.2 = private unnamed_addr constant [11 x i8] c"<built-in>\00", align 1
@macros = internal global %struct.HashMap zeroinitializer, align 8
@.str.3 = private unnamed_addr constant [6 x i8] c"_LP64\00", align 1
@.str.4 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@.str.5 = private unnamed_addr constant [25 x i8] c"__C99_MACRO_WITH_VA_ARGS\00", align 1
@.str.6 = private unnamed_addr constant [8 x i8] c"__ELF__\00", align 1
@.str.7 = private unnamed_addr constant [9 x i8] c"__LP64__\00", align 1
@.str.8 = private unnamed_addr constant [18 x i8] c"__SIZEOF_DOUBLE__\00", align 1
@.str.9 = private unnamed_addr constant [2 x i8] c"8\00", align 1
@.str.10 = private unnamed_addr constant [17 x i8] c"__SIZEOF_FLOAT__\00", align 1
@.str.11 = private unnamed_addr constant [2 x i8] c"4\00", align 1
@.str.12 = private unnamed_addr constant [15 x i8] c"__SIZEOF_INT__\00", align 1
@.str.13 = private unnamed_addr constant [23 x i8] c"__SIZEOF_LONG_DOUBLE__\00", align 1
@.str.14 = private unnamed_addr constant [21 x i8] c"__SIZEOF_LONG_LONG__\00", align 1
@.str.15 = private unnamed_addr constant [16 x i8] c"__SIZEOF_LONG__\00", align 1
@.str.16 = private unnamed_addr constant [19 x i8] c"__SIZEOF_POINTER__\00", align 1
@.str.17 = private unnamed_addr constant [21 x i8] c"__SIZEOF_PTRDIFF_T__\00", align 1
@.str.18 = private unnamed_addr constant [17 x i8] c"__SIZEOF_SHORT__\00", align 1
@.str.19 = private unnamed_addr constant [2 x i8] c"2\00", align 1
@.str.20 = private unnamed_addr constant [18 x i8] c"__SIZEOF_SIZE_T__\00", align 1
@.str.21 = private unnamed_addr constant [14 x i8] c"__SIZE_TYPE__\00", align 1
@.str.22 = private unnamed_addr constant [14 x i8] c"unsigned long\00", align 1
@.str.23 = private unnamed_addr constant [16 x i8] c"__STDC_HOSTED__\00", align 1
@.str.24 = private unnamed_addr constant [20 x i8] c"__STDC_NO_COMPLEX__\00", align 1
@.str.25 = private unnamed_addr constant [16 x i8] c"__STDC_UTF_16__\00", align 1
@.str.26 = private unnamed_addr constant [16 x i8] c"__STDC_UTF_32__\00", align 1
@.str.27 = private unnamed_addr constant [17 x i8] c"__STDC_VERSION__\00", align 1
@.str.28 = private unnamed_addr constant [8 x i8] c"201112L\00", align 1
@.str.29 = private unnamed_addr constant [9 x i8] c"__STDC__\00", align 1
@.str.30 = private unnamed_addr constant [22 x i8] c"__USER_LABEL_PREFIX__\00", align 1
@.str.31 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.32 = private unnamed_addr constant [12 x i8] c"__alignof__\00", align 1
@.str.33 = private unnamed_addr constant [9 x i8] c"_Alignof\00", align 1
@.str.34 = private unnamed_addr constant [8 x i8] c"__amd64\00", align 1
@.str.35 = private unnamed_addr constant [10 x i8] c"__amd64__\00", align 1
@.str.36 = private unnamed_addr constant [12 x i8] c"__chibicc__\00", align 1
@.str.37 = private unnamed_addr constant [10 x i8] c"__const__\00", align 1
@.str.38 = private unnamed_addr constant [6 x i8] c"const\00", align 1
@.str.39 = private unnamed_addr constant [14 x i8] c"__gnu_linux__\00", align 1
@.str.40 = private unnamed_addr constant [11 x i8] c"__inline__\00", align 1
@.str.41 = private unnamed_addr constant [7 x i8] c"inline\00", align 1
@.str.42 = private unnamed_addr constant [8 x i8] c"__linux\00", align 1
@.str.43 = private unnamed_addr constant [10 x i8] c"__linux__\00", align 1
@.str.44 = private unnamed_addr constant [11 x i8] c"__signed__\00", align 1
@.str.45 = private unnamed_addr constant [7 x i8] c"signed\00", align 1
@.str.46 = private unnamed_addr constant [11 x i8] c"__typeof__\00", align 1
@.str.47 = private unnamed_addr constant [7 x i8] c"typeof\00", align 1
@.str.48 = private unnamed_addr constant [7 x i8] c"__unix\00", align 1
@.str.49 = private unnamed_addr constant [9 x i8] c"__unix__\00", align 1
@.str.50 = private unnamed_addr constant [13 x i8] c"__volatile__\00", align 1
@.str.51 = private unnamed_addr constant [9 x i8] c"volatile\00", align 1
@.str.52 = private unnamed_addr constant [9 x i8] c"__x86_64\00", align 1
@.str.53 = private unnamed_addr constant [11 x i8] c"__x86_64__\00", align 1
@.str.54 = private unnamed_addr constant [6 x i8] c"linux\00", align 1
@.str.55 = private unnamed_addr constant [5 x i8] c"unix\00", align 1
@.str.56 = private unnamed_addr constant [8 x i8] c"nonnull\00", align 1
@.str.57 = private unnamed_addr constant [9 x i8] c"__FILE__\00", align 1
@.str.58 = private unnamed_addr constant [9 x i8] c"__LINE__\00", align 1
@.str.59 = private unnamed_addr constant [12 x i8] c"__COUNTER__\00", align 1
@.str.60 = private unnamed_addr constant [14 x i8] c"__TIMESTAMP__\00", align 1
@.str.61 = private unnamed_addr constant [14 x i8] c"__BASE_FILE__\00", align 1
@.str.62 = private unnamed_addr constant [9 x i8] c"__DATE__\00", align 1
@.str.63 = private unnamed_addr constant [9 x i8] c"__TIME__\00", align 1
@cond_incl = internal global %struct.CondIncl* null, align 8
@.str.64 = private unnamed_addr constant [55 x i8] c"%s: in preprocess : unterminated conditional directive\00", align 1
@.str.65 = private unnamed_addr constant [13 x i8] c"preprocess.c\00", align 1
@.str.66 = private unnamed_addr constant [29 x i8] c"%s: in add_macro : m is null\00", align 1
@.str.67 = private unnamed_addr constant [34 x i8] c"%s: in quote_string : buf is null\00", align 1
@.str.68 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@counter_macro.i = internal global i32 0, align 4
@.str.69 = private unnamed_addr constant [25 x i8] c"??? ??? ?? ??:??:?? ????\00", align 1
@base_file = external global i8*, align 8
@format_date.mon = internal global [12 x [4 x i8]] [[4 x i8] c"Jan\00", [4 x i8] c"Feb\00", [4 x i8] c"Mar\00", [4 x i8] c"Apr\00", [4 x i8] c"May\00", [4 x i8] c"Jun\00", [4 x i8] c"Jul\00", [4 x i8] c"Aug\00", [4 x i8] c"Sep\00", [4 x i8] c"Oct\00", [4 x i8] c"Nov\00", [4 x i8] c"Dec\00"], align 16
@.str.70 = private unnamed_addr constant [12 x i8] c"\22%s %2d %d\22\00", align 1
@.str.71 = private unnamed_addr constant [17 x i8] c"\22%02d:%02d:%02d\22\00", align 1
@.str.72 = private unnamed_addr constant [8 x i8] c"include\00", align 1
@.str.73 = private unnamed_addr constant [13 x i8] c"include_next\00", align 1
@.str.74 = private unnamed_addr constant [7 x i8] c"define\00", align 1
@.str.75 = private unnamed_addr constant [6 x i8] c"undef\00", align 1
@.str.76 = private unnamed_addr constant [54 x i8] c"%s: in preprocess2 : macro name must be an identifier\00", align 1
@.str.77 = private unnamed_addr constant [3 x i8] c"if\00", align 1
@.str.78 = private unnamed_addr constant [6 x i8] c"ifdef\00", align 1
@.str.79 = private unnamed_addr constant [7 x i8] c"ifndef\00", align 1
@.str.80 = private unnamed_addr constant [5 x i8] c"elif\00", align 1
@.str.81 = private unnamed_addr constant [33 x i8] c"%s: in preprocess2 : stray #elif\00", align 1
@.str.82 = private unnamed_addr constant [5 x i8] c"else\00", align 1
@.str.83 = private unnamed_addr constant [33 x i8] c"%s: in preprocess2 : stray #else\00", align 1
@.str.84 = private unnamed_addr constant [6 x i8] c"endif\00", align 1
@.str.85 = private unnamed_addr constant [34 x i8] c"%s: in preprocess2 : stray #endif\00", align 1
@.str.86 = private unnamed_addr constant [5 x i8] c"line\00", align 1
@.str.87 = private unnamed_addr constant [7 x i8] c"pragma\00", align 1
@.str.88 = private unnamed_addr constant [5 x i8] c"once\00", align 1
@pragma_once = internal global %struct.HashMap zeroinitializer, align 8
@.str.89 = private unnamed_addr constant [6 x i8] c"error\00", align 1
@.str.90 = private unnamed_addr constant [27 x i8] c"%s: in preprocess2 : error\00", align 1
@.str.91 = private unnamed_addr constant [8 x i8] c"warning\00", align 1
@.str.92 = private unnamed_addr constant [13 x i8] c"warning: %s\0A\00", align 1
@.str.93 = private unnamed_addr constant [52 x i8] c"%s: in preprocess2 : invalid preprocessor directive\00", align 1
@.str.94 = private unnamed_addr constant [2 x i8] c"#\00", align 1
@.str.95 = private unnamed_addr constant [2 x i8] c"<\00", align 1
@.str.96 = private unnamed_addr constant [2 x i8] c">\00", align 1
@.str.97 = private unnamed_addr constant [44 x i8] c"%s: in read_include_filename : expected '>'\00", align 1
@.str.98 = private unnamed_addr constant [51 x i8] c"%s: in read_include_filename : expected a filename\00", align 1
@.str.99 = private unnamed_addr constant [33 x i8] c"%s: in join_tokens : buf is null\00", align 1
@.str.100 = private unnamed_addr constant [30 x i8] c"%s: in copy_token : t is null\00", align 1
@include_file.include_guards = internal global %struct.HashMap zeroinitializer, align 8
@.str.101 = private unnamed_addr constant [47 x i8] c"%s: in include_file : %s: cannot open file: %s\00", align 1
@.str.102 = private unnamed_addr constant [64 x i8] c"%s: in read_macro_definition : macro name must be an identifier\00", align 1
@.str.103 = private unnamed_addr constant [2 x i8] c"(\00", align 1
@.str.104 = private unnamed_addr constant [2 x i8] c")\00", align 1
@.str.105 = private unnamed_addr constant [2 x i8] c",\00", align 1
@.str.106 = private unnamed_addr constant [4 x i8] c"...\00", align 1
@.str.107 = private unnamed_addr constant [12 x i8] c"__VA_ARGS__\00", align 1
@.str.108 = private unnamed_addr constant [49 x i8] c"%s in read_macro_params : expected an identifier\00", align 1
@.str.109 = private unnamed_addr constant [37 x i8] c"%s: in read_macro_params : m is null\00", align 1
@.str.110 = private unnamed_addr constant [12 x i8] c"extra token\00", align 1
@.str.111 = private unnamed_addr constant [39 x i8] c"%s: in eval_const_expr : no expression\00", align 1
@.str.112 = private unnamed_addr constant [37 x i8] c"%s: in eval_const_expr : extra token\00", align 1
@.str.113 = private unnamed_addr constant [8 x i8] c"defined\00", align 1
@.str.114 = private unnamed_addr constant [58 x i8] c"%s: in read_const_expr : macro name must be an identifier\00", align 1
@.str.115 = private unnamed_addr constant [35 x i8] c"%s: in push_cond_incl : ci is null\00", align 1
@.str.116 = private unnamed_addr constant [46 x i8] c"%s: in read_line_marker : invalid line marker\00", align 1
@.str.117 = private unnamed_addr constant [44 x i8] c"%s: in read_line_marker : filename expected\00", align 1
@.str.118 = private unnamed_addr constant [97 x i8] c"%s: in join_adjacent_string_literals : unsupported non-standard concatenation of string literals\00", align 1
@.str.119 = private unnamed_addr constant [52 x i8] c"%s: in join_adjacent_string_literals :  buf is null\00", align 1
@.str.120 = private unnamed_addr constant [3 x i8] c"u8\00", align 1
@.str.121 = private unnamed_addr constant [24 x i8] c"internal error at %s:%d\00", align 1
@.str.122 = private unnamed_addr constant [32 x i8] c"%s: in new_hideset : hs is null\00", align 1
@.str.123 = private unnamed_addr constant [37 x i8] c"%s: in read_macro_args : arg is null\00", align 1
@.str.124 = private unnamed_addr constant [44 x i8] c"%s: in read_macro_args : too many arguments\00", align 1
@.str.125 = private unnamed_addr constant [51 x i8] c"%s: in read_macro_arg_one : premature end of input\00", align 1
@.str.126 = private unnamed_addr constant [40 x i8] c"%s: in read_macro_arg_one : arg is null\00", align 1
@.str.127 = private unnamed_addr constant [56 x i8] c"%s: in subst : '#' is not followed by a macro parameter\00", align 1
@.str.128 = private unnamed_addr constant [3 x i8] c"##\00", align 1
@.str.129 = private unnamed_addr constant [62 x i8] c"%s: in subst : '##' cannot appear at start of macro expansion\00", align 1
@.str.130 = private unnamed_addr constant [60 x i8] c"%s: in subst : '##' cannot appear at end of macro expansion\00", align 1
@.str.131 = private unnamed_addr constant [11 x i8] c"__VA_OPT__\00", align 1
@.str.132 = private unnamed_addr constant [9 x i8] c"%.*s%.*s\00", align 1
@.str.133 = private unnamed_addr constant [52 x i8] c"%s: in paste : pasting forms '%s', an invalid token\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @search_include_paths(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  %7 = load i8*, i8** %3, align 8
  %8 = getelementptr inbounds i8, i8* %7, i64 0
  %9 = load i8, i8* %8, align 1
  %10 = sext i8 %9 to i32
  %11 = icmp eq i32 %10, 47
  br i1 %11, label %12, label %14

12:                                               ; preds = %1
  %13 = load i8*, i8** %3, align 8
  store i8* %13, i8** %2, align 8
  br label %47

14:                                               ; preds = %1
  %15 = load i8*, i8** %3, align 8
  %16 = call i8* @hashmap_get(%struct.HashMap* noundef @search_include_paths.cache, i8* noundef %15)
  store i8* %16, i8** %4, align 8
  %17 = load i8*, i8** %4, align 8
  %18 = icmp ne i8* %17, null
  br i1 %18, label %19, label %21

19:                                               ; preds = %14
  %20 = load i8*, i8** %4, align 8
  store i8* %20, i8** %2, align 8
  br label %47

21:                                               ; preds = %14
  store i32 0, i32* %5, align 4
  br label %22

22:                                               ; preds = %43, %21
  %23 = load i32, i32* %5, align 4
  %24 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @include_paths, i32 0, i32 2), align 4
  %25 = icmp slt i32 %23, %24
  br i1 %25, label %26, label %46

26:                                               ; preds = %22
  %27 = load i8**, i8*** getelementptr inbounds (%struct.StringArray, %struct.StringArray* @include_paths, i32 0, i32 0), align 8
  %28 = load i32, i32* %5, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds i8*, i8** %27, i64 %29
  %31 = load i8*, i8** %30, align 8
  %32 = load i8*, i8** %3, align 8
  %33 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0), i8* noundef %31, i8* noundef %32)
  store i8* %33, i8** %6, align 8
  %34 = load i8*, i8** %6, align 8
  %35 = call zeroext i1 @file_exists(i8* noundef %34)
  br i1 %35, label %37, label %36

36:                                               ; preds = %26
  br label %43

37:                                               ; preds = %26
  %38 = load i8*, i8** %3, align 8
  %39 = load i8*, i8** %6, align 8
  call void @hashmap_put(%struct.HashMap* noundef @search_include_paths.cache, i8* noundef %38, i8* noundef %39)
  %40 = load i32, i32* %5, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* @include_next_idx, align 4
  %42 = load i8*, i8** %6, align 8
  store i8* %42, i8** %2, align 8
  br label %47

43:                                               ; preds = %36
  %44 = load i32, i32* %5, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, i32* %5, align 4
  br label %22, !llvm.loop !6

46:                                               ; preds = %22
  store i8* null, i8** %2, align 8
  br label %47

47:                                               ; preds = %46, %37, %19, %12
  %48 = load i8*, i8** %2, align 8
  ret i8* %48
}

declare i8* @hashmap_get(%struct.HashMap* noundef, i8* noundef) #1

declare i8* @format(i8* noundef, ...) #1

declare zeroext i1 @file_exists(i8* noundef) #1

declare void @hashmap_put(%struct.HashMap* noundef, i8* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @define_macro(i8* noundef %0, i8* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %struct.Token*, align 8
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %6 = load i8*, i8** %3, align 8
  %7 = call i32 @strncmp(i8* noundef %6, i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.1, i64 0, i64 0), i64 noundef 15) #8
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %9, label %16

9:                                                ; preds = %2
  %10 = load i8*, i8** %4, align 8
  %11 = call %struct.File* @new_file(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0), i32 noundef 1, i8* noundef %10)
  %12 = call %struct.Token* @tokenize(%struct.File* noundef %11)
  store %struct.Token* %12, %struct.Token** %5, align 8
  %13 = load i8*, i8** %3, align 8
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  %15 = call %struct.Macro* @add_macro(i8* noundef %13, i1 noundef zeroext true, %struct.Token* noundef %14)
  br label %16

16:                                               ; preds = %9, %2
  ret void
}

; Function Attrs: nounwind readonly willreturn
declare i32 @strncmp(i8* noundef, i8* noundef, i64 noundef) #2

declare %struct.Token* @tokenize(%struct.File* noundef) #1

declare %struct.File* @new_file(i8* noundef, i32 noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Macro* @add_macro(i8* noundef %0, i1 noundef zeroext %1, %struct.Token* noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca i8, align 1
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Macro*, align 8
  store i8* %0, i8** %4, align 8
  %8 = zext i1 %1 to i8
  store i8 %8, i8* %5, align 1
  store %struct.Token* %2, %struct.Token** %6, align 8
  %9 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 48) #9
  %10 = bitcast i8* %9 to %struct.Macro*
  store %struct.Macro* %10, %struct.Macro** %7, align 8
  %11 = load %struct.Macro*, %struct.Macro** %7, align 8
  %12 = icmp eq %struct.Macro* %11, null
  br i1 %12, label %13, label %14

13:                                               ; preds = %3
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([29 x i8], [29 x i8]* @.str.66, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

14:                                               ; preds = %3
  %15 = load i8*, i8** %4, align 8
  %16 = load %struct.Macro*, %struct.Macro** %7, align 8
  %17 = getelementptr inbounds %struct.Macro, %struct.Macro* %16, i32 0, i32 0
  store i8* %15, i8** %17, align 8
  %18 = load i8, i8* %5, align 1
  %19 = trunc i8 %18 to i1
  %20 = load %struct.Macro*, %struct.Macro** %7, align 8
  %21 = getelementptr inbounds %struct.Macro, %struct.Macro* %20, i32 0, i32 1
  %22 = zext i1 %19 to i8
  store i8 %22, i8* %21, align 8
  %23 = load %struct.Token*, %struct.Token** %6, align 8
  %24 = load %struct.Macro*, %struct.Macro** %7, align 8
  %25 = getelementptr inbounds %struct.Macro, %struct.Macro* %24, i32 0, i32 4
  store %struct.Token* %23, %struct.Token** %25, align 8
  %26 = load i8*, i8** %4, align 8
  %27 = load %struct.Macro*, %struct.Macro** %7, align 8
  %28 = bitcast %struct.Macro* %27 to i8*
  call void @hashmap_put(%struct.HashMap* noundef @macros, i8* noundef %26, i8* noundef %28)
  %29 = load %struct.Macro*, %struct.Macro** %7, align 8
  ret %struct.Macro* %29
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @undef_macro(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  call void @hashmap_delete(%struct.HashMap* noundef @macros, i8* noundef %3)
  ret void
}

declare void @hashmap_delete(%struct.HashMap* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @init_macros() #0 {
  %1 = alloca i64, align 8
  %2 = alloca %struct.tm*, align 8
  call void @define_macro(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.3, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.5, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.6, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.7, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.8, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.10, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.12, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.13, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.14, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.15, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.16, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.17, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.18, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.20, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.21, i64 0, i64 0), i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.22, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.23, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.24, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.25, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.26, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.27, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.28, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.29, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.30, i64 0, i64 0), i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.31, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.32, i64 0, i64 0), i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.33, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.34, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.35, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.37, i64 0, i64 0), i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.38, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.39, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.40, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.41, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.42, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.43, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.44, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.45, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.46, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.47, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.48, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.49, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.50, i64 0, i64 0), i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.51, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.52, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.53, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.54, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.55, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  call void @define_macro(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.56, i64 0, i64 0), i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  %3 = call %struct.Macro* @add_builtin(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.57, i64 0, i64 0), %struct.Token* (%struct.Token*)* noundef @file_macro)
  %4 = call %struct.Macro* @add_builtin(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.58, i64 0, i64 0), %struct.Token* (%struct.Token*)* noundef @line_macro)
  %5 = call %struct.Macro* @add_builtin(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.59, i64 0, i64 0), %struct.Token* (%struct.Token*)* noundef @counter_macro)
  %6 = call %struct.Macro* @add_builtin(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.60, i64 0, i64 0), %struct.Token* (%struct.Token*)* noundef @timestamp_macro)
  %7 = call %struct.Macro* @add_builtin(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.61, i64 0, i64 0), %struct.Token* (%struct.Token*)* noundef @base_file_macro)
  %8 = call i64 @time(i64* noundef null) #9
  store i64 %8, i64* %1, align 8
  %9 = call %struct.tm* @localtime(i64* noundef %1) #9
  store %struct.tm* %9, %struct.tm** %2, align 8
  %10 = load %struct.tm*, %struct.tm** %2, align 8
  %11 = call i8* @format_date(%struct.tm* noundef %10)
  call void @define_macro(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.62, i64 0, i64 0), i8* noundef %11)
  %12 = load %struct.tm*, %struct.tm** %2, align 8
  %13 = call i8* @format_time(%struct.tm* noundef %12)
  call void @define_macro(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.63, i64 0, i64 0), i8* noundef %13)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Macro* @add_builtin(i8* noundef %0, %struct.Token* (%struct.Token*)* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca %struct.Token* (%struct.Token*)*, align 8
  %5 = alloca %struct.Macro*, align 8
  store i8* %0, i8** %3, align 8
  store %struct.Token* (%struct.Token*)* %1, %struct.Token* (%struct.Token*)** %4, align 8
  %6 = load i8*, i8** %3, align 8
  %7 = call %struct.Macro* @add_macro(i8* noundef %6, i1 noundef zeroext true, %struct.Token* noundef null)
  store %struct.Macro* %7, %struct.Macro** %5, align 8
  %8 = load %struct.Token* (%struct.Token*)*, %struct.Token* (%struct.Token*)** %4, align 8
  %9 = load %struct.Macro*, %struct.Macro** %5, align 8
  %10 = getelementptr inbounds %struct.Macro, %struct.Macro* %9, i32 0, i32 5
  store %struct.Token* (%struct.Token*)* %8, %struct.Token* (%struct.Token*)** %10, align 8
  %11 = load %struct.Macro*, %struct.Macro** %5, align 8
  ret %struct.Macro* %11
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @file_macro(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  br label %3

3:                                                ; preds = %8, %1
  %4 = load %struct.Token*, %struct.Token** %2, align 8
  %5 = getelementptr inbounds %struct.Token, %struct.Token* %4, i32 0, i32 15
  %6 = load %struct.Token*, %struct.Token** %5, align 8
  %7 = icmp ne %struct.Token* %6, null
  br i1 %7, label %8, label %12

8:                                                ; preds = %3
  %9 = load %struct.Token*, %struct.Token** %2, align 8
  %10 = getelementptr inbounds %struct.Token, %struct.Token* %9, i32 0, i32 15
  %11 = load %struct.Token*, %struct.Token** %10, align 8
  store %struct.Token* %11, %struct.Token** %2, align 8
  br label %3, !llvm.loop !8

12:                                               ; preds = %3
  %13 = load %struct.Token*, %struct.Token** %2, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 8
  %15 = load %struct.File*, %struct.File** %14, align 16
  %16 = getelementptr inbounds %struct.File, %struct.File* %15, i32 0, i32 3
  %17 = load i8*, i8** %16, align 8
  %18 = load %struct.Token*, %struct.Token** %2, align 8
  %19 = call %struct.Token* @new_str_token(i8* noundef %17, %struct.Token* noundef %18)
  ret %struct.Token* %19
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @line_macro(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca i32, align 4
  store %struct.Token* %0, %struct.Token** %2, align 8
  br label %4

4:                                                ; preds = %9, %1
  %5 = load %struct.Token*, %struct.Token** %2, align 8
  %6 = getelementptr inbounds %struct.Token, %struct.Token* %5, i32 0, i32 15
  %7 = load %struct.Token*, %struct.Token** %6, align 8
  %8 = icmp ne %struct.Token* %7, null
  br i1 %8, label %9, label %13

9:                                                ; preds = %4
  %10 = load %struct.Token*, %struct.Token** %2, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 15
  %12 = load %struct.Token*, %struct.Token** %11, align 8
  store %struct.Token* %12, %struct.Token** %2, align 8
  br label %4, !llvm.loop !9

13:                                               ; preds = %4
  %14 = load %struct.Token*, %struct.Token** %2, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 10
  %16 = load i32, i32* %15, align 16
  %17 = load %struct.Token*, %struct.Token** %2, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 8
  %19 = load %struct.File*, %struct.File** %18, align 16
  %20 = getelementptr inbounds %struct.File, %struct.File* %19, i32 0, i32 4
  %21 = load i32, i32* %20, align 8
  %22 = add nsw i32 %16, %21
  store i32 %22, i32* %3, align 4
  %23 = load i32, i32* %3, align 4
  %24 = load %struct.Token*, %struct.Token** %2, align 8
  %25 = call %struct.Token* @new_num_token(i32 noundef %23, %struct.Token* noundef %24)
  ret %struct.Token* %25
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @counter_macro(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %3 = load i32, i32* @counter_macro.i, align 4
  %4 = add nsw i32 %3, 1
  store i32 %4, i32* @counter_macro.i, align 4
  %5 = load %struct.Token*, %struct.Token** %2, align 8
  %6 = call %struct.Token* @new_num_token(i32 noundef %3, %struct.Token* noundef %5)
  ret %struct.Token* %6
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @timestamp_macro(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.stat, align 8
  %5 = alloca [30 x i8], align 16
  store %struct.Token* %0, %struct.Token** %3, align 8
  %6 = load %struct.Token*, %struct.Token** %3, align 8
  %7 = getelementptr inbounds %struct.Token, %struct.Token* %6, i32 0, i32 8
  %8 = load %struct.File*, %struct.File** %7, align 16
  %9 = getelementptr inbounds %struct.File, %struct.File* %8, i32 0, i32 0
  %10 = load i8*, i8** %9, align 8
  %11 = call i32 @stat(i8* noundef %10, %struct.stat* noundef %4) #9
  %12 = icmp ne i32 %11, 0
  br i1 %12, label %13, label %16

13:                                               ; preds = %1
  %14 = load %struct.Token*, %struct.Token** %3, align 8
  %15 = call %struct.Token* @new_str_token(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.69, i64 0, i64 0), %struct.Token* noundef %14)
  store %struct.Token* %15, %struct.Token** %2, align 8
  br label %25

16:                                               ; preds = %1
  %17 = getelementptr inbounds %struct.stat, %struct.stat* %4, i32 0, i32 12
  %18 = getelementptr inbounds %struct.timespec, %struct.timespec* %17, i32 0, i32 0
  %19 = getelementptr inbounds [30 x i8], [30 x i8]* %5, i64 0, i64 0
  %20 = call i8* @ctime_r(i64* noundef %18, i8* noundef %19) #9
  %21 = getelementptr inbounds [30 x i8], [30 x i8]* %5, i64 0, i64 24
  store i8 0, i8* %21, align 8
  %22 = getelementptr inbounds [30 x i8], [30 x i8]* %5, i64 0, i64 0
  %23 = load %struct.Token*, %struct.Token** %3, align 8
  %24 = call %struct.Token* @new_str_token(i8* noundef %22, %struct.Token* noundef %23)
  store %struct.Token* %24, %struct.Token** %2, align 8
  br label %25

25:                                               ; preds = %16, %13
  %26 = load %struct.Token*, %struct.Token** %2, align 8
  ret %struct.Token* %26
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @base_file_macro(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %3 = load i8*, i8** @base_file, align 8
  %4 = load %struct.Token*, %struct.Token** %2, align 8
  %5 = call %struct.Token* @new_str_token(i8* noundef %3, %struct.Token* noundef %4)
  ret %struct.Token* %5
}

; Function Attrs: nounwind
declare i64 @time(i64* noundef) #3

; Function Attrs: nounwind
declare %struct.tm* @localtime(i64* noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @format_date(%struct.tm* noundef %0) #0 {
  %2 = alloca %struct.tm*, align 8
  store %struct.tm* %0, %struct.tm** %2, align 8
  %3 = load %struct.tm*, %struct.tm** %2, align 8
  %4 = getelementptr inbounds %struct.tm, %struct.tm* %3, i32 0, i32 4
  %5 = load i32, i32* %4, align 8
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [12 x [4 x i8]], [12 x [4 x i8]]* @format_date.mon, i64 0, i64 %6
  %8 = getelementptr inbounds [4 x i8], [4 x i8]* %7, i64 0, i64 0
  %9 = load %struct.tm*, %struct.tm** %2, align 8
  %10 = getelementptr inbounds %struct.tm, %struct.tm* %9, i32 0, i32 3
  %11 = load i32, i32* %10, align 4
  %12 = load %struct.tm*, %struct.tm** %2, align 8
  %13 = getelementptr inbounds %struct.tm, %struct.tm* %12, i32 0, i32 5
  %14 = load i32, i32* %13, align 4
  %15 = add nsw i32 %14, 1900
  %16 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.70, i64 0, i64 0), i8* noundef %8, i32 noundef %11, i32 noundef %15)
  ret i8* %16
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @format_time(%struct.tm* noundef %0) #0 {
  %2 = alloca %struct.tm*, align 8
  store %struct.tm* %0, %struct.tm** %2, align 8
  %3 = load %struct.tm*, %struct.tm** %2, align 8
  %4 = getelementptr inbounds %struct.tm, %struct.tm* %3, i32 0, i32 2
  %5 = load i32, i32* %4, align 8
  %6 = load %struct.tm*, %struct.tm** %2, align 8
  %7 = getelementptr inbounds %struct.tm, %struct.tm* %6, i32 0, i32 1
  %8 = load i32, i32* %7, align 4
  %9 = load %struct.tm*, %struct.tm** %2, align 8
  %10 = getelementptr inbounds %struct.tm, %struct.tm* %9, i32 0, i32 0
  %11 = load i32, i32* %10, align 8
  %12 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.71, i64 0, i64 0), i32 noundef %5, i32 noundef %8, i32 noundef %11)
  ret i8* %12
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Token* @preprocess(%struct.Token* noundef %0, i1 noundef zeroext %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i8, align 1
  %5 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %6 = zext i1 %1 to i8
  store i8 %6, i8* %4, align 1
  %7 = load %struct.Token*, %struct.Token** %3, align 8
  %8 = call %struct.Token* @preprocess2(%struct.Token* noundef %7)
  store %struct.Token* %8, %struct.Token** %3, align 8
  %9 = load %struct.Token*, %struct.Token** %3, align 8
  %10 = call %struct.Token* @preprocess3(%struct.Token* noundef %9)
  store %struct.Token* %10, %struct.Token** %3, align 8
  %11 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %12 = icmp ne %struct.CondIncl* %11, null
  br i1 %12, label %13, label %20

13:                                               ; preds = %2
  %14 = load i8, i8* %4, align 1
  %15 = trunc i8 %14 to i1
  br i1 %15, label %20, label %16

16:                                               ; preds = %13
  %17 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %18 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %17, i32 0, i32 2
  %19 = load %struct.Token*, %struct.Token** %18, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %19, i8* noundef getelementptr inbounds ([55 x i8], [55 x i8]* @.str.64, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

20:                                               ; preds = %13, %2
  %21 = load %struct.Token*, %struct.Token** %3, align 8
  call void @convert_pp_tokens(%struct.Token* noundef %21)
  %22 = load %struct.Token*, %struct.Token** %3, align 8
  call void @join_adjacent_string_literals(%struct.Token* noundef %22)
  %23 = load %struct.Token*, %struct.Token** %3, align 8
  store %struct.Token* %23, %struct.Token** %5, align 8
  br label %24

24:                                               ; preds = %36, %20
  %25 = load %struct.Token*, %struct.Token** %5, align 8
  %26 = icmp ne %struct.Token* %25, null
  br i1 %26, label %27, label %40

27:                                               ; preds = %24
  %28 = load %struct.Token*, %struct.Token** %5, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 11
  %30 = load i32, i32* %29, align 4
  %31 = call i32 @abs(i32 noundef %30) #11
  %32 = load %struct.Token*, %struct.Token** %5, align 8
  %33 = getelementptr inbounds %struct.Token, %struct.Token* %32, i32 0, i32 10
  %34 = load i32, i32* %33, align 16
  %35 = add nsw i32 %34, %31
  store i32 %35, i32* %33, align 16
  br label %36

36:                                               ; preds = %27
  %37 = load %struct.Token*, %struct.Token** %5, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 1
  %39 = load %struct.Token*, %struct.Token** %38, align 8
  store %struct.Token* %39, %struct.Token** %5, align 8
  br label %24, !llvm.loop !10

40:                                               ; preds = %24
  %41 = load %struct.Token*, %struct.Token** %3, align 8
  ret %struct.Token* %41
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @preprocess2(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token, align 16
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca i8, align 1
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8, align 1
  %11 = alloca i8*, align 8
  %12 = alloca i8*, align 8
  %13 = alloca i64, align 8
  %14 = alloca i8, align 1
  %15 = alloca i8, align 1
  store %struct.Token* %0, %struct.Token** %2, align 8
  %16 = bitcast %struct.Token* %3 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %16, i8 0, i64 128, i1 false)
  store %struct.Token* %3, %struct.Token** %4, align 8
  br label %17

17:                                               ; preds = %389, %371, %360, %334, %324, %315, %304, %295, %267, %236, %209, %183, %155, %138, %127, %102, %82, %29, %25, %1
  %18 = load %struct.Token*, %struct.Token** %2, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 0
  %20 = load i32, i32* %19, align 16
  %21 = icmp ne i32 %20, 6
  br i1 %21, label %22, label %398

22:                                               ; preds = %17
  %23 = load %struct.Token*, %struct.Token** %2, align 8
  %24 = call zeroext i1 @expand_macro(%struct.Token** noundef %2, %struct.Token* noundef %23)
  br i1 %24, label %25, label %26

25:                                               ; preds = %22
  br label %17, !llvm.loop !11

26:                                               ; preds = %22
  %27 = load %struct.Token*, %struct.Token** %2, align 8
  %28 = call zeroext i1 @is_hash(%struct.Token* noundef %27)
  br i1 %28, label %50, label %29

29:                                               ; preds = %26
  %30 = load %struct.Token*, %struct.Token** %2, align 8
  %31 = getelementptr inbounds %struct.Token, %struct.Token* %30, i32 0, i32 8
  %32 = load %struct.File*, %struct.File** %31, align 16
  %33 = getelementptr inbounds %struct.File, %struct.File* %32, i32 0, i32 4
  %34 = load i32, i32* %33, align 8
  %35 = load %struct.Token*, %struct.Token** %2, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 11
  store i32 %34, i32* %36, align 4
  %37 = load %struct.Token*, %struct.Token** %2, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 8
  %39 = load %struct.File*, %struct.File** %38, align 16
  %40 = getelementptr inbounds %struct.File, %struct.File* %39, i32 0, i32 3
  %41 = load i8*, i8** %40, align 8
  %42 = load %struct.Token*, %struct.Token** %2, align 8
  %43 = getelementptr inbounds %struct.Token, %struct.Token* %42, i32 0, i32 9
  store i8* %41, i8** %43, align 8
  %44 = load %struct.Token*, %struct.Token** %2, align 8
  %45 = load %struct.Token*, %struct.Token** %4, align 8
  %46 = getelementptr inbounds %struct.Token, %struct.Token* %45, i32 0, i32 1
  store %struct.Token* %44, %struct.Token** %46, align 8
  store %struct.Token* %44, %struct.Token** %4, align 8
  %47 = load %struct.Token*, %struct.Token** %2, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 1
  %49 = load %struct.Token*, %struct.Token** %48, align 8
  store %struct.Token* %49, %struct.Token** %2, align 8
  br label %17, !llvm.loop !11

50:                                               ; preds = %26
  %51 = load %struct.Token*, %struct.Token** %2, align 8
  store %struct.Token* %51, %struct.Token** %5, align 8
  %52 = load %struct.Token*, %struct.Token** %2, align 8
  %53 = getelementptr inbounds %struct.Token, %struct.Token* %52, i32 0, i32 1
  %54 = load %struct.Token*, %struct.Token** %53, align 8
  store %struct.Token* %54, %struct.Token** %2, align 8
  %55 = load %struct.Token*, %struct.Token** %2, align 8
  %56 = call zeroext i1 @equal(%struct.Token* noundef %55, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.72, i64 0, i64 0))
  br i1 %56, label %57, label %110

57:                                               ; preds = %50
  %58 = load %struct.Token*, %struct.Token** %2, align 8
  %59 = getelementptr inbounds %struct.Token, %struct.Token* %58, i32 0, i32 1
  %60 = load %struct.Token*, %struct.Token** %59, align 8
  %61 = call i8* @read_include_filename(%struct.Token** noundef %2, %struct.Token* noundef %60, i8* noundef %6)
  store i8* %61, i8** %7, align 8
  %62 = load i8*, i8** %7, align 8
  %63 = getelementptr inbounds i8, i8* %62, i64 0
  %64 = load i8, i8* %63, align 1
  %65 = sext i8 %64 to i32
  %66 = icmp ne i32 %65, 47
  br i1 %66, label %67, label %92

67:                                               ; preds = %57
  %68 = load i8, i8* %6, align 1
  %69 = trunc i8 %68 to i1
  br i1 %69, label %70, label %92

70:                                               ; preds = %67
  %71 = load %struct.Token*, %struct.Token** %5, align 8
  %72 = getelementptr inbounds %struct.Token, %struct.Token* %71, i32 0, i32 8
  %73 = load %struct.File*, %struct.File** %72, align 16
  %74 = getelementptr inbounds %struct.File, %struct.File* %73, i32 0, i32 0
  %75 = load i8*, i8** %74, align 8
  %76 = call noalias i8* @strdup(i8* noundef %75) #9
  %77 = call i8* @dirname(i8* noundef %76) #9
  %78 = load i8*, i8** %7, align 8
  %79 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0), i8* noundef %77, i8* noundef %78)
  store i8* %79, i8** %8, align 8
  %80 = load i8*, i8** %8, align 8
  %81 = call zeroext i1 @file_exists(i8* noundef %80)
  br i1 %81, label %82, label %91

82:                                               ; preds = %70
  %83 = load %struct.Token*, %struct.Token** %2, align 8
  %84 = load i8*, i8** %8, align 8
  %85 = load %struct.Token*, %struct.Token** %5, align 8
  %86 = getelementptr inbounds %struct.Token, %struct.Token* %85, i32 0, i32 1
  %87 = load %struct.Token*, %struct.Token** %86, align 8
  %88 = getelementptr inbounds %struct.Token, %struct.Token* %87, i32 0, i32 1
  %89 = load %struct.Token*, %struct.Token** %88, align 8
  %90 = call %struct.Token* @include_file(%struct.Token* noundef %83, i8* noundef %84, %struct.Token* noundef %89)
  store %struct.Token* %90, %struct.Token** %2, align 8
  br label %17, !llvm.loop !11

91:                                               ; preds = %70
  br label %92

92:                                               ; preds = %91, %67, %57
  %93 = load i8*, i8** %7, align 8
  %94 = call i8* @search_include_paths(i8* noundef %93)
  store i8* %94, i8** %9, align 8
  %95 = load %struct.Token*, %struct.Token** %2, align 8
  %96 = load i8*, i8** %9, align 8
  %97 = icmp ne i8* %96, null
  br i1 %97, label %98, label %100

98:                                               ; preds = %92
  %99 = load i8*, i8** %9, align 8
  br label %102

100:                                              ; preds = %92
  %101 = load i8*, i8** %7, align 8
  br label %102

102:                                              ; preds = %100, %98
  %103 = phi i8* [ %99, %98 ], [ %101, %100 ]
  %104 = load %struct.Token*, %struct.Token** %5, align 8
  %105 = getelementptr inbounds %struct.Token, %struct.Token* %104, i32 0, i32 1
  %106 = load %struct.Token*, %struct.Token** %105, align 8
  %107 = getelementptr inbounds %struct.Token, %struct.Token* %106, i32 0, i32 1
  %108 = load %struct.Token*, %struct.Token** %107, align 8
  %109 = call %struct.Token* @include_file(%struct.Token* noundef %95, i8* noundef %103, %struct.Token* noundef %108)
  store %struct.Token* %109, %struct.Token** %2, align 8
  br label %17, !llvm.loop !11

110:                                              ; preds = %50
  %111 = load %struct.Token*, %struct.Token** %2, align 8
  %112 = call zeroext i1 @equal(%struct.Token* noundef %111, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.73, i64 0, i64 0))
  br i1 %112, label %113, label %135

113:                                              ; preds = %110
  %114 = load %struct.Token*, %struct.Token** %2, align 8
  %115 = getelementptr inbounds %struct.Token, %struct.Token* %114, i32 0, i32 1
  %116 = load %struct.Token*, %struct.Token** %115, align 8
  %117 = call i8* @read_include_filename(%struct.Token** noundef %2, %struct.Token* noundef %116, i8* noundef %10)
  store i8* %117, i8** %11, align 8
  %118 = load i8*, i8** %11, align 8
  %119 = call i8* @search_include_next(i8* noundef %118)
  store i8* %119, i8** %12, align 8
  %120 = load %struct.Token*, %struct.Token** %2, align 8
  %121 = load i8*, i8** %12, align 8
  %122 = icmp ne i8* %121, null
  br i1 %122, label %123, label %125

123:                                              ; preds = %113
  %124 = load i8*, i8** %12, align 8
  br label %127

125:                                              ; preds = %113
  %126 = load i8*, i8** %11, align 8
  br label %127

127:                                              ; preds = %125, %123
  %128 = phi i8* [ %124, %123 ], [ %126, %125 ]
  %129 = load %struct.Token*, %struct.Token** %5, align 8
  %130 = getelementptr inbounds %struct.Token, %struct.Token* %129, i32 0, i32 1
  %131 = load %struct.Token*, %struct.Token** %130, align 8
  %132 = getelementptr inbounds %struct.Token, %struct.Token* %131, i32 0, i32 1
  %133 = load %struct.Token*, %struct.Token** %132, align 8
  %134 = call %struct.Token* @include_file(%struct.Token* noundef %120, i8* noundef %128, %struct.Token* noundef %133)
  store %struct.Token* %134, %struct.Token** %2, align 8
  br label %17, !llvm.loop !11

135:                                              ; preds = %110
  %136 = load %struct.Token*, %struct.Token** %2, align 8
  %137 = call zeroext i1 @equal(%struct.Token* noundef %136, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.74, i64 0, i64 0))
  br i1 %137, label %138, label %142

138:                                              ; preds = %135
  %139 = load %struct.Token*, %struct.Token** %2, align 8
  %140 = getelementptr inbounds %struct.Token, %struct.Token* %139, i32 0, i32 1
  %141 = load %struct.Token*, %struct.Token** %140, align 8
  call void @read_macro_definition(%struct.Token** noundef %2, %struct.Token* noundef %141)
  br label %17, !llvm.loop !11

142:                                              ; preds = %135
  %143 = load %struct.Token*, %struct.Token** %2, align 8
  %144 = call zeroext i1 @equal(%struct.Token* noundef %143, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.75, i64 0, i64 0))
  br i1 %144, label %145, label %168

145:                                              ; preds = %142
  %146 = load %struct.Token*, %struct.Token** %2, align 8
  %147 = getelementptr inbounds %struct.Token, %struct.Token* %146, i32 0, i32 1
  %148 = load %struct.Token*, %struct.Token** %147, align 8
  store %struct.Token* %148, %struct.Token** %2, align 8
  %149 = load %struct.Token*, %struct.Token** %2, align 8
  %150 = getelementptr inbounds %struct.Token, %struct.Token* %149, i32 0, i32 0
  %151 = load i32, i32* %150, align 16
  %152 = icmp ne i32 %151, 0
  br i1 %152, label %153, label %155

153:                                              ; preds = %145
  %154 = load %struct.Token*, %struct.Token** %2, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %154, i8* noundef getelementptr inbounds ([54 x i8], [54 x i8]* @.str.76, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

155:                                              ; preds = %145
  %156 = load %struct.Token*, %struct.Token** %2, align 8
  %157 = getelementptr inbounds %struct.Token, %struct.Token* %156, i32 0, i32 4
  %158 = load i8*, i8** %157, align 16
  %159 = load %struct.Token*, %struct.Token** %2, align 8
  %160 = getelementptr inbounds %struct.Token, %struct.Token* %159, i32 0, i32 5
  %161 = load i32, i32* %160, align 8
  %162 = sext i32 %161 to i64
  %163 = call noalias i8* @strndup(i8* noundef %158, i64 noundef %162) #9
  call void @undef_macro(i8* noundef %163)
  %164 = load %struct.Token*, %struct.Token** %2, align 8
  %165 = getelementptr inbounds %struct.Token, %struct.Token* %164, i32 0, i32 1
  %166 = load %struct.Token*, %struct.Token** %165, align 8
  %167 = call %struct.Token* @skip_line(%struct.Token* noundef %166)
  store %struct.Token* %167, %struct.Token** %2, align 8
  br label %17, !llvm.loop !11

168:                                              ; preds = %142
  %169 = load %struct.Token*, %struct.Token** %2, align 8
  %170 = call zeroext i1 @equal(%struct.Token* noundef %169, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.77, i64 0, i64 0))
  br i1 %170, label %171, label %184

171:                                              ; preds = %168
  %172 = load %struct.Token*, %struct.Token** %2, align 8
  %173 = call i64 @eval_const_expr(%struct.Token** noundef %2, %struct.Token* noundef %172)
  store i64 %173, i64* %13, align 8
  %174 = load %struct.Token*, %struct.Token** %5, align 8
  %175 = load i64, i64* %13, align 8
  %176 = icmp ne i64 %175, 0
  %177 = call %struct.CondIncl* @push_cond_incl(%struct.Token* noundef %174, i1 noundef zeroext %176)
  %178 = load i64, i64* %13, align 8
  %179 = icmp ne i64 %178, 0
  br i1 %179, label %183, label %180

180:                                              ; preds = %171
  %181 = load %struct.Token*, %struct.Token** %2, align 8
  %182 = call %struct.Token* @skip_cond_incl(%struct.Token* noundef %181)
  store %struct.Token* %182, %struct.Token** %2, align 8
  br label %183

183:                                              ; preds = %180, %171
  br label %17, !llvm.loop !11

184:                                              ; preds = %168
  %185 = load %struct.Token*, %struct.Token** %2, align 8
  %186 = call zeroext i1 @equal(%struct.Token* noundef %185, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.78, i64 0, i64 0))
  br i1 %186, label %187, label %210

187:                                              ; preds = %184
  %188 = load %struct.Token*, %struct.Token** %2, align 8
  %189 = getelementptr inbounds %struct.Token, %struct.Token* %188, i32 0, i32 1
  %190 = load %struct.Token*, %struct.Token** %189, align 8
  %191 = call %struct.Macro* @find_macro(%struct.Token* noundef %190)
  %192 = icmp ne %struct.Macro* %191, null
  %193 = zext i1 %192 to i8
  store i8 %193, i8* %14, align 1
  %194 = load %struct.Token*, %struct.Token** %2, align 8
  %195 = load i8, i8* %14, align 1
  %196 = trunc i8 %195 to i1
  %197 = call %struct.CondIncl* @push_cond_incl(%struct.Token* noundef %194, i1 noundef zeroext %196)
  %198 = load %struct.Token*, %struct.Token** %2, align 8
  %199 = getelementptr inbounds %struct.Token, %struct.Token* %198, i32 0, i32 1
  %200 = load %struct.Token*, %struct.Token** %199, align 8
  %201 = getelementptr inbounds %struct.Token, %struct.Token* %200, i32 0, i32 1
  %202 = load %struct.Token*, %struct.Token** %201, align 8
  %203 = call %struct.Token* @skip_line(%struct.Token* noundef %202)
  store %struct.Token* %203, %struct.Token** %2, align 8
  %204 = load i8, i8* %14, align 1
  %205 = trunc i8 %204 to i1
  br i1 %205, label %209, label %206

206:                                              ; preds = %187
  %207 = load %struct.Token*, %struct.Token** %2, align 8
  %208 = call %struct.Token* @skip_cond_incl(%struct.Token* noundef %207)
  store %struct.Token* %208, %struct.Token** %2, align 8
  br label %209

209:                                              ; preds = %206, %187
  br label %17, !llvm.loop !11

210:                                              ; preds = %184
  %211 = load %struct.Token*, %struct.Token** %2, align 8
  %212 = call zeroext i1 @equal(%struct.Token* noundef %211, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.79, i64 0, i64 0))
  br i1 %212, label %213, label %237

213:                                              ; preds = %210
  %214 = load %struct.Token*, %struct.Token** %2, align 8
  %215 = getelementptr inbounds %struct.Token, %struct.Token* %214, i32 0, i32 1
  %216 = load %struct.Token*, %struct.Token** %215, align 8
  %217 = call %struct.Macro* @find_macro(%struct.Token* noundef %216)
  %218 = icmp ne %struct.Macro* %217, null
  %219 = zext i1 %218 to i8
  store i8 %219, i8* %15, align 1
  %220 = load %struct.Token*, %struct.Token** %2, align 8
  %221 = load i8, i8* %15, align 1
  %222 = trunc i8 %221 to i1
  %223 = xor i1 %222, true
  %224 = call %struct.CondIncl* @push_cond_incl(%struct.Token* noundef %220, i1 noundef zeroext %223)
  %225 = load %struct.Token*, %struct.Token** %2, align 8
  %226 = getelementptr inbounds %struct.Token, %struct.Token* %225, i32 0, i32 1
  %227 = load %struct.Token*, %struct.Token** %226, align 8
  %228 = getelementptr inbounds %struct.Token, %struct.Token* %227, i32 0, i32 1
  %229 = load %struct.Token*, %struct.Token** %228, align 8
  %230 = call %struct.Token* @skip_line(%struct.Token* noundef %229)
  store %struct.Token* %230, %struct.Token** %2, align 8
  %231 = load i8, i8* %15, align 1
  %232 = trunc i8 %231 to i1
  br i1 %232, label %233, label %236

233:                                              ; preds = %213
  %234 = load %struct.Token*, %struct.Token** %2, align 8
  %235 = call %struct.Token* @skip_cond_incl(%struct.Token* noundef %234)
  store %struct.Token* %235, %struct.Token** %2, align 8
  br label %236

236:                                              ; preds = %233, %213
  br label %17, !llvm.loop !11

237:                                              ; preds = %210
  %238 = load %struct.Token*, %struct.Token** %2, align 8
  %239 = call zeroext i1 @equal(%struct.Token* noundef %238, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.80, i64 0, i64 0))
  br i1 %239, label %240, label %268

240:                                              ; preds = %237
  %241 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %242 = icmp ne %struct.CondIncl* %241, null
  br i1 %242, label %243, label %248

243:                                              ; preds = %240
  %244 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %245 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %244, i32 0, i32 1
  %246 = load i32, i32* %245, align 8
  %247 = icmp eq i32 %246, 2
  br i1 %247, label %248, label %250

248:                                              ; preds = %243, %240
  %249 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %249, i8* noundef getelementptr inbounds ([33 x i8], [33 x i8]* @.str.81, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

250:                                              ; preds = %243
  %251 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %252 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %251, i32 0, i32 1
  store i32 1, i32* %252, align 8
  %253 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %254 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %253, i32 0, i32 3
  %255 = load i8, i8* %254, align 8
  %256 = trunc i8 %255 to i1
  br i1 %256, label %264, label %257

257:                                              ; preds = %250
  %258 = load %struct.Token*, %struct.Token** %2, align 8
  %259 = call i64 @eval_const_expr(%struct.Token** noundef %2, %struct.Token* noundef %258)
  %260 = icmp ne i64 %259, 0
  br i1 %260, label %261, label %264

261:                                              ; preds = %257
  %262 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %263 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %262, i32 0, i32 3
  store i8 1, i8* %263, align 8
  br label %267

264:                                              ; preds = %257, %250
  %265 = load %struct.Token*, %struct.Token** %2, align 8
  %266 = call %struct.Token* @skip_cond_incl(%struct.Token* noundef %265)
  store %struct.Token* %266, %struct.Token** %2, align 8
  br label %267

267:                                              ; preds = %264, %261
  br label %17, !llvm.loop !11

268:                                              ; preds = %237
  %269 = load %struct.Token*, %struct.Token** %2, align 8
  %270 = call zeroext i1 @equal(%struct.Token* noundef %269, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i64 0, i64 0))
  br i1 %270, label %271, label %296

271:                                              ; preds = %268
  %272 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %273 = icmp ne %struct.CondIncl* %272, null
  br i1 %273, label %274, label %279

274:                                              ; preds = %271
  %275 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %276 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %275, i32 0, i32 1
  %277 = load i32, i32* %276, align 8
  %278 = icmp eq i32 %277, 2
  br i1 %278, label %279, label %281

279:                                              ; preds = %274, %271
  %280 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %280, i8* noundef getelementptr inbounds ([33 x i8], [33 x i8]* @.str.83, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

281:                                              ; preds = %274
  %282 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %283 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %282, i32 0, i32 1
  store i32 2, i32* %283, align 8
  %284 = load %struct.Token*, %struct.Token** %2, align 8
  %285 = getelementptr inbounds %struct.Token, %struct.Token* %284, i32 0, i32 1
  %286 = load %struct.Token*, %struct.Token** %285, align 8
  %287 = call %struct.Token* @skip_line(%struct.Token* noundef %286)
  store %struct.Token* %287, %struct.Token** %2, align 8
  %288 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %289 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %288, i32 0, i32 3
  %290 = load i8, i8* %289, align 8
  %291 = trunc i8 %290 to i1
  br i1 %291, label %292, label %295

292:                                              ; preds = %281
  %293 = load %struct.Token*, %struct.Token** %2, align 8
  %294 = call %struct.Token* @skip_cond_incl(%struct.Token* noundef %293)
  store %struct.Token* %294, %struct.Token** %2, align 8
  br label %295

295:                                              ; preds = %292, %281
  br label %17, !llvm.loop !11

296:                                              ; preds = %268
  %297 = load %struct.Token*, %struct.Token** %2, align 8
  %298 = call zeroext i1 @equal(%struct.Token* noundef %297, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.84, i64 0, i64 0))
  br i1 %298, label %299, label %312

299:                                              ; preds = %296
  %300 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %301 = icmp ne %struct.CondIncl* %300, null
  br i1 %301, label %304, label %302

302:                                              ; preds = %299
  %303 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %303, i8* noundef getelementptr inbounds ([34 x i8], [34 x i8]* @.str.85, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

304:                                              ; preds = %299
  %305 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %306 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %305, i32 0, i32 0
  %307 = load %struct.CondIncl*, %struct.CondIncl** %306, align 8
  store %struct.CondIncl* %307, %struct.CondIncl** @cond_incl, align 8
  %308 = load %struct.Token*, %struct.Token** %2, align 8
  %309 = getelementptr inbounds %struct.Token, %struct.Token* %308, i32 0, i32 1
  %310 = load %struct.Token*, %struct.Token** %309, align 8
  %311 = call %struct.Token* @skip_line(%struct.Token* noundef %310)
  store %struct.Token* %311, %struct.Token** %2, align 8
  br label %17, !llvm.loop !11

312:                                              ; preds = %296
  %313 = load %struct.Token*, %struct.Token** %2, align 8
  %314 = call zeroext i1 @equal(%struct.Token* noundef %313, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.86, i64 0, i64 0))
  br i1 %314, label %315, label %319

315:                                              ; preds = %312
  %316 = load %struct.Token*, %struct.Token** %2, align 8
  %317 = getelementptr inbounds %struct.Token, %struct.Token* %316, i32 0, i32 1
  %318 = load %struct.Token*, %struct.Token** %317, align 8
  call void @read_line_marker(%struct.Token** noundef %2, %struct.Token* noundef %318)
  br label %17, !llvm.loop !11

319:                                              ; preds = %312
  %320 = load %struct.Token*, %struct.Token** %2, align 8
  %321 = getelementptr inbounds %struct.Token, %struct.Token* %320, i32 0, i32 0
  %322 = load i32, i32* %321, align 16
  %323 = icmp eq i32 %322, 5
  br i1 %323, label %324, label %326

324:                                              ; preds = %319
  %325 = load %struct.Token*, %struct.Token** %2, align 8
  call void @read_line_marker(%struct.Token** noundef %2, %struct.Token* noundef %325)
  br label %17, !llvm.loop !11

326:                                              ; preds = %319
  %327 = load %struct.Token*, %struct.Token** %2, align 8
  %328 = call zeroext i1 @equal(%struct.Token* noundef %327, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.87, i64 0, i64 0))
  br i1 %328, label %329, label %346

329:                                              ; preds = %326
  %330 = load %struct.Token*, %struct.Token** %2, align 8
  %331 = getelementptr inbounds %struct.Token, %struct.Token* %330, i32 0, i32 1
  %332 = load %struct.Token*, %struct.Token** %331, align 8
  %333 = call zeroext i1 @equal(%struct.Token* noundef %332, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.88, i64 0, i64 0))
  br i1 %333, label %334, label %346

334:                                              ; preds = %329
  %335 = load %struct.Token*, %struct.Token** %2, align 8
  %336 = getelementptr inbounds %struct.Token, %struct.Token* %335, i32 0, i32 8
  %337 = load %struct.File*, %struct.File** %336, align 16
  %338 = getelementptr inbounds %struct.File, %struct.File* %337, i32 0, i32 0
  %339 = load i8*, i8** %338, align 8
  call void @hashmap_put(%struct.HashMap* noundef @pragma_once, i8* noundef %339, i8* noundef inttoptr (i64 1 to i8*))
  %340 = load %struct.Token*, %struct.Token** %2, align 8
  %341 = getelementptr inbounds %struct.Token, %struct.Token* %340, i32 0, i32 1
  %342 = load %struct.Token*, %struct.Token** %341, align 8
  %343 = getelementptr inbounds %struct.Token, %struct.Token* %342, i32 0, i32 1
  %344 = load %struct.Token*, %struct.Token** %343, align 8
  %345 = call %struct.Token* @skip_line(%struct.Token* noundef %344)
  store %struct.Token* %345, %struct.Token** %2, align 8
  br label %17, !llvm.loop !11

346:                                              ; preds = %329, %326
  %347 = load %struct.Token*, %struct.Token** %2, align 8
  %348 = call zeroext i1 @equal(%struct.Token* noundef %347, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.87, i64 0, i64 0))
  br i1 %348, label %349, label %361

349:                                              ; preds = %346
  br label %350

350:                                              ; preds = %354, %349
  %351 = load %struct.Token*, %struct.Token** %2, align 8
  %352 = getelementptr inbounds %struct.Token, %struct.Token* %351, i32 0, i32 1
  %353 = load %struct.Token*, %struct.Token** %352, align 8
  store %struct.Token* %353, %struct.Token** %2, align 8
  br label %354

354:                                              ; preds = %350
  %355 = load %struct.Token*, %struct.Token** %2, align 8
  %356 = getelementptr inbounds %struct.Token, %struct.Token* %355, i32 0, i32 12
  %357 = load i8, i8* %356, align 8
  %358 = trunc i8 %357 to i1
  %359 = xor i1 %358, true
  br i1 %359, label %350, label %360, !llvm.loop !12

360:                                              ; preds = %354
  br label %17, !llvm.loop !11

361:                                              ; preds = %346
  %362 = load %struct.Token*, %struct.Token** %2, align 8
  %363 = call zeroext i1 @equal(%struct.Token* noundef %362, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.89, i64 0, i64 0))
  br i1 %363, label %364, label %366

364:                                              ; preds = %361
  %365 = load %struct.Token*, %struct.Token** %2, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %365, i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @.str.90, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

366:                                              ; preds = %361
  %367 = load %struct.Token*, %struct.Token** %2, align 8
  %368 = getelementptr inbounds %struct.Token, %struct.Token* %367, i32 0, i32 12
  %369 = load i8, i8* %368, align 8
  %370 = trunc i8 %369 to i1
  br i1 %370, label %371, label %372

371:                                              ; preds = %366
  br label %17, !llvm.loop !11

372:                                              ; preds = %366
  %373 = load %struct.Token*, %struct.Token** %2, align 8
  %374 = call zeroext i1 @equal(%struct.Token* noundef %373, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.91, i64 0, i64 0))
  br i1 %374, label %375, label %396

375:                                              ; preds = %372
  %376 = load %struct.Token*, %struct.Token** %2, align 8
  %377 = getelementptr inbounds %struct.Token, %struct.Token* %376, i32 0, i32 1
  %378 = load %struct.Token*, %struct.Token** %377, align 8
  %379 = getelementptr inbounds %struct.Token, %struct.Token* %378, i32 0, i32 7
  %380 = load i8*, i8** %379, align 8
  %381 = icmp ne i8* %380, null
  br i1 %381, label %382, label %389

382:                                              ; preds = %375
  %383 = load %struct.Token*, %struct.Token** %2, align 8
  %384 = getelementptr inbounds %struct.Token, %struct.Token* %383, i32 0, i32 1
  %385 = load %struct.Token*, %struct.Token** %384, align 8
  %386 = getelementptr inbounds %struct.Token, %struct.Token* %385, i32 0, i32 7
  %387 = load i8*, i8** %386, align 8
  %388 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.92, i64 0, i64 0), i8* noundef %387)
  br label %389

389:                                              ; preds = %382, %375
  %390 = load %struct.Token*, %struct.Token** %2, align 8
  %391 = getelementptr inbounds %struct.Token, %struct.Token* %390, i32 0, i32 1
  %392 = load %struct.Token*, %struct.Token** %391, align 8
  %393 = getelementptr inbounds %struct.Token, %struct.Token* %392, i32 0, i32 1
  %394 = load %struct.Token*, %struct.Token** %393, align 8
  %395 = call %struct.Token* @skip_line(%struct.Token* noundef %394)
  store %struct.Token* %395, %struct.Token** %2, align 8
  br label %17, !llvm.loop !11

396:                                              ; preds = %372
  %397 = load %struct.Token*, %struct.Token** %2, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %397, i8* noundef getelementptr inbounds ([52 x i8], [52 x i8]* @.str.93, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

398:                                              ; preds = %17
  %399 = load %struct.Token*, %struct.Token** %2, align 8
  %400 = load %struct.Token*, %struct.Token** %4, align 8
  %401 = getelementptr inbounds %struct.Token, %struct.Token* %400, i32 0, i32 1
  store %struct.Token* %399, %struct.Token** %401, align 8
  %402 = getelementptr inbounds %struct.Token, %struct.Token* %3, i32 0, i32 1
  %403 = load %struct.Token*, %struct.Token** %402, align 8
  ret %struct.Token* %403
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Token* @preprocess3(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token, align 16
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Macro*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %6 = bitcast %struct.Token* %3 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %6, i8 0, i64 128, i1 false)
  store %struct.Token* %3, %struct.Token** %4, align 8
  br label %7

7:                                                ; preds = %29, %27, %1
  %8 = load %struct.Token*, %struct.Token** %2, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 0
  %10 = load i32, i32* %9, align 16
  %11 = icmp ne i32 %10, 6
  br i1 %11, label %12, label %36

12:                                               ; preds = %7
  %13 = load %struct.Token*, %struct.Token** %2, align 8
  %14 = call %struct.Macro* @find_macro(%struct.Token* noundef %13)
  store %struct.Macro* %14, %struct.Macro** %5, align 8
  %15 = load %struct.Macro*, %struct.Macro** %5, align 8
  %16 = icmp ne %struct.Macro* %15, null
  br i1 %16, label %17, label %29

17:                                               ; preds = %12
  %18 = load %struct.Macro*, %struct.Macro** %5, align 8
  %19 = getelementptr inbounds %struct.Macro, %struct.Macro* %18, i32 0, i32 4
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 5
  %22 = load i32, i32* %21, align 8
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %24, label %29

24:                                               ; preds = %17
  %25 = load %struct.Token*, %struct.Token** %2, align 8
  %26 = call zeroext i1 @expand_macro(%struct.Token** noundef %2, %struct.Token* noundef %25)
  br i1 %26, label %27, label %28

27:                                               ; preds = %24
  br label %7, !llvm.loop !13

28:                                               ; preds = %24
  br label %29

29:                                               ; preds = %28, %17, %12
  %30 = load %struct.Token*, %struct.Token** %2, align 8
  %31 = load %struct.Token*, %struct.Token** %4, align 8
  %32 = getelementptr inbounds %struct.Token, %struct.Token* %31, i32 0, i32 1
  store %struct.Token* %30, %struct.Token** %32, align 8
  store %struct.Token* %30, %struct.Token** %4, align 8
  %33 = load %struct.Token*, %struct.Token** %2, align 8
  %34 = getelementptr inbounds %struct.Token, %struct.Token* %33, i32 0, i32 1
  %35 = load %struct.Token*, %struct.Token** %34, align 8
  store %struct.Token* %35, %struct.Token** %2, align 8
  br label %7, !llvm.loop !13

36:                                               ; preds = %7
  %37 = load %struct.Token*, %struct.Token** %2, align 8
  %38 = load %struct.Token*, %struct.Token** %4, align 8
  %39 = getelementptr inbounds %struct.Token, %struct.Token* %38, i32 0, i32 1
  store %struct.Token* %37, %struct.Token** %39, align 8
  %40 = getelementptr inbounds %struct.Token, %struct.Token* %3, i32 0, i32 1
  %41 = load %struct.Token*, %struct.Token** %40, align 8
  ret %struct.Token* %41
}

; Function Attrs: noreturn
declare void @error_tok(%struct.Token* noundef, i8* noundef, ...) #4

declare void @convert_pp_tokens(%struct.Token* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal void @join_adjacent_string_literals(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i32, align 4
  %5 = alloca %struct.Type*, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca i32, align 4
  %8 = alloca %struct.Token*, align 8
  %9 = alloca %struct.Token*, align 8
  %10 = alloca %struct.Token*, align 8
  %11 = alloca i32, align 4
  %12 = alloca %struct.Token*, align 8
  %13 = alloca i8*, align 8
  %14 = alloca i32, align 4
  %15 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %16 = load %struct.Token*, %struct.Token** %2, align 8
  store %struct.Token* %16, %struct.Token** %3, align 8
  br label %17

17:                                               ; preds = %125, %34, %1
  %18 = load %struct.Token*, %struct.Token** %3, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 0
  %20 = load i32, i32* %19, align 16
  %21 = icmp ne i32 %20, 6
  br i1 %21, label %22, label %126

22:                                               ; preds = %17
  %23 = load %struct.Token*, %struct.Token** %3, align 8
  %24 = getelementptr inbounds %struct.Token, %struct.Token* %23, i32 0, i32 0
  %25 = load i32, i32* %24, align 16
  %26 = icmp ne i32 %25, 3
  br i1 %26, label %34, label %27

27:                                               ; preds = %22
  %28 = load %struct.Token*, %struct.Token** %3, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 1
  %30 = load %struct.Token*, %struct.Token** %29, align 8
  %31 = getelementptr inbounds %struct.Token, %struct.Token* %30, i32 0, i32 0
  %32 = load i32, i32* %31, align 16
  %33 = icmp ne i32 %32, 3
  br i1 %33, label %34, label %38

34:                                               ; preds = %27, %22
  %35 = load %struct.Token*, %struct.Token** %3, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 1
  %37 = load %struct.Token*, %struct.Token** %36, align 8
  store %struct.Token* %37, %struct.Token** %3, align 8
  br label %17, !llvm.loop !14

38:                                               ; preds = %27
  %39 = load %struct.Token*, %struct.Token** %3, align 8
  %40 = call i32 @getStringKind(%struct.Token* noundef %39)
  store i32 %40, i32* %4, align 4
  %41 = load %struct.Token*, %struct.Token** %3, align 8
  %42 = getelementptr inbounds %struct.Token, %struct.Token* %41, i32 0, i32 6
  %43 = load %struct.Type*, %struct.Type** %42, align 16
  %44 = getelementptr inbounds %struct.Type, %struct.Type* %43, i32 0, i32 8
  %45 = load %struct.Type*, %struct.Type** %44, align 8
  store %struct.Type* %45, %struct.Type** %5, align 8
  %46 = load %struct.Token*, %struct.Token** %3, align 8
  %47 = getelementptr inbounds %struct.Token, %struct.Token* %46, i32 0, i32 1
  %48 = load %struct.Token*, %struct.Token** %47, align 8
  store %struct.Token* %48, %struct.Token** %6, align 8
  br label %49

49:                                               ; preds = %77, %38
  %50 = load %struct.Token*, %struct.Token** %6, align 8
  %51 = getelementptr inbounds %struct.Token, %struct.Token* %50, i32 0, i32 0
  %52 = load i32, i32* %51, align 16
  %53 = icmp eq i32 %52, 3
  br i1 %53, label %54, label %81

54:                                               ; preds = %49
  %55 = load %struct.Token*, %struct.Token** %6, align 8
  %56 = call i32 @getStringKind(%struct.Token* noundef %55)
  store i32 %56, i32* %7, align 4
  %57 = load i32, i32* %4, align 4
  %58 = icmp eq i32 %57, 0
  br i1 %58, label %59, label %66

59:                                               ; preds = %54
  %60 = load i32, i32* %7, align 4
  store i32 %60, i32* %4, align 4
  %61 = load %struct.Token*, %struct.Token** %6, align 8
  %62 = getelementptr inbounds %struct.Token, %struct.Token* %61, i32 0, i32 6
  %63 = load %struct.Type*, %struct.Type** %62, align 16
  %64 = getelementptr inbounds %struct.Type, %struct.Type* %63, i32 0, i32 8
  %65 = load %struct.Type*, %struct.Type** %64, align 8
  store %struct.Type* %65, %struct.Type** %5, align 8
  br label %76

66:                                               ; preds = %54
  %67 = load i32, i32* %7, align 4
  %68 = icmp ne i32 %67, 0
  br i1 %68, label %69, label %75

69:                                               ; preds = %66
  %70 = load i32, i32* %4, align 4
  %71 = load i32, i32* %7, align 4
  %72 = icmp ne i32 %70, %71
  br i1 %72, label %73, label %75

73:                                               ; preds = %69
  %74 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %74, i8* noundef getelementptr inbounds ([97 x i8], [97 x i8]* @.str.118, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

75:                                               ; preds = %69, %66
  br label %76

76:                                               ; preds = %75, %59
  br label %77

77:                                               ; preds = %76
  %78 = load %struct.Token*, %struct.Token** %6, align 8
  %79 = getelementptr inbounds %struct.Token, %struct.Token* %78, i32 0, i32 1
  %80 = load %struct.Token*, %struct.Token** %79, align 8
  store %struct.Token* %80, %struct.Token** %6, align 8
  br label %49, !llvm.loop !15

81:                                               ; preds = %49
  %82 = load %struct.Type*, %struct.Type** %5, align 8
  %83 = getelementptr inbounds %struct.Type, %struct.Type* %82, i32 0, i32 1
  %84 = load i32, i32* %83, align 4
  %85 = icmp sgt i32 %84, 1
  br i1 %85, label %86, label %115

86:                                               ; preds = %81
  %87 = load %struct.Token*, %struct.Token** %3, align 8
  store %struct.Token* %87, %struct.Token** %8, align 8
  br label %88

88:                                               ; preds = %110, %86
  %89 = load %struct.Token*, %struct.Token** %8, align 8
  %90 = getelementptr inbounds %struct.Token, %struct.Token* %89, i32 0, i32 0
  %91 = load i32, i32* %90, align 16
  %92 = icmp eq i32 %91, 3
  br i1 %92, label %93, label %114

93:                                               ; preds = %88
  %94 = load %struct.Token*, %struct.Token** %8, align 8
  %95 = getelementptr inbounds %struct.Token, %struct.Token* %94, i32 0, i32 6
  %96 = load %struct.Type*, %struct.Type** %95, align 16
  %97 = getelementptr inbounds %struct.Type, %struct.Type* %96, i32 0, i32 8
  %98 = load %struct.Type*, %struct.Type** %97, align 8
  %99 = getelementptr inbounds %struct.Type, %struct.Type* %98, i32 0, i32 1
  %100 = load i32, i32* %99, align 4
  %101 = icmp eq i32 %100, 1
  br i1 %101, label %102, label %109

102:                                              ; preds = %93
  %103 = load %struct.Token*, %struct.Token** %8, align 8
  %104 = load %struct.Token*, %struct.Token** %8, align 8
  %105 = load %struct.Type*, %struct.Type** %5, align 8
  %106 = call %struct.Token* @tokenize_string_literal(%struct.Token* noundef %104, %struct.Type* noundef %105)
  %107 = bitcast %struct.Token* %103 to i8*
  %108 = bitcast %struct.Token* %106 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %107, i8* align 16 %108, i64 128, i1 false)
  br label %109

109:                                              ; preds = %102, %93
  br label %110

110:                                              ; preds = %109
  %111 = load %struct.Token*, %struct.Token** %8, align 8
  %112 = getelementptr inbounds %struct.Token, %struct.Token* %111, i32 0, i32 1
  %113 = load %struct.Token*, %struct.Token** %112, align 8
  store %struct.Token* %113, %struct.Token** %8, align 8
  br label %88, !llvm.loop !16

114:                                              ; preds = %88
  br label %115

115:                                              ; preds = %114, %81
  br label %116

116:                                              ; preds = %121, %115
  %117 = load %struct.Token*, %struct.Token** %3, align 8
  %118 = getelementptr inbounds %struct.Token, %struct.Token* %117, i32 0, i32 0
  %119 = load i32, i32* %118, align 16
  %120 = icmp eq i32 %119, 3
  br i1 %120, label %121, label %125

121:                                              ; preds = %116
  %122 = load %struct.Token*, %struct.Token** %3, align 8
  %123 = getelementptr inbounds %struct.Token, %struct.Token* %122, i32 0, i32 1
  %124 = load %struct.Token*, %struct.Token** %123, align 8
  store %struct.Token* %124, %struct.Token** %3, align 8
  br label %116, !llvm.loop !17

125:                                              ; preds = %116
  br label %17, !llvm.loop !14

126:                                              ; preds = %17
  %127 = load %struct.Token*, %struct.Token** %2, align 8
  store %struct.Token* %127, %struct.Token** %9, align 8
  br label %128

128:                                              ; preds = %242, %145, %126
  %129 = load %struct.Token*, %struct.Token** %9, align 8
  %130 = getelementptr inbounds %struct.Token, %struct.Token* %129, i32 0, i32 0
  %131 = load i32, i32* %130, align 16
  %132 = icmp ne i32 %131, 6
  br i1 %132, label %133, label %264

133:                                              ; preds = %128
  %134 = load %struct.Token*, %struct.Token** %9, align 8
  %135 = getelementptr inbounds %struct.Token, %struct.Token* %134, i32 0, i32 0
  %136 = load i32, i32* %135, align 16
  %137 = icmp ne i32 %136, 3
  br i1 %137, label %145, label %138

138:                                              ; preds = %133
  %139 = load %struct.Token*, %struct.Token** %9, align 8
  %140 = getelementptr inbounds %struct.Token, %struct.Token* %139, i32 0, i32 1
  %141 = load %struct.Token*, %struct.Token** %140, align 8
  %142 = getelementptr inbounds %struct.Token, %struct.Token* %141, i32 0, i32 0
  %143 = load i32, i32* %142, align 16
  %144 = icmp ne i32 %143, 3
  br i1 %144, label %145, label %149

145:                                              ; preds = %138, %133
  %146 = load %struct.Token*, %struct.Token** %9, align 8
  %147 = getelementptr inbounds %struct.Token, %struct.Token* %146, i32 0, i32 1
  %148 = load %struct.Token*, %struct.Token** %147, align 8
  store %struct.Token* %148, %struct.Token** %9, align 8
  br label %128, !llvm.loop !18

149:                                              ; preds = %138
  %150 = load %struct.Token*, %struct.Token** %9, align 8
  %151 = getelementptr inbounds %struct.Token, %struct.Token* %150, i32 0, i32 1
  %152 = load %struct.Token*, %struct.Token** %151, align 8
  store %struct.Token* %152, %struct.Token** %10, align 8
  br label %153

153:                                              ; preds = %158, %149
  %154 = load %struct.Token*, %struct.Token** %10, align 8
  %155 = getelementptr inbounds %struct.Token, %struct.Token* %154, i32 0, i32 0
  %156 = load i32, i32* %155, align 16
  %157 = icmp eq i32 %156, 3
  br i1 %157, label %158, label %162

158:                                              ; preds = %153
  %159 = load %struct.Token*, %struct.Token** %10, align 8
  %160 = getelementptr inbounds %struct.Token, %struct.Token* %159, i32 0, i32 1
  %161 = load %struct.Token*, %struct.Token** %160, align 8
  store %struct.Token* %161, %struct.Token** %10, align 8
  br label %153, !llvm.loop !19

162:                                              ; preds = %153
  %163 = load %struct.Token*, %struct.Token** %9, align 8
  %164 = getelementptr inbounds %struct.Token, %struct.Token* %163, i32 0, i32 6
  %165 = load %struct.Type*, %struct.Type** %164, align 16
  %166 = getelementptr inbounds %struct.Type, %struct.Type* %165, i32 0, i32 11
  %167 = load i32, i32* %166, align 8
  store i32 %167, i32* %11, align 4
  %168 = load %struct.Token*, %struct.Token** %9, align 8
  %169 = getelementptr inbounds %struct.Token, %struct.Token* %168, i32 0, i32 1
  %170 = load %struct.Token*, %struct.Token** %169, align 8
  store %struct.Token* %170, %struct.Token** %12, align 8
  br label %171

171:                                              ; preds = %184, %162
  %172 = load %struct.Token*, %struct.Token** %12, align 8
  %173 = load %struct.Token*, %struct.Token** %10, align 8
  %174 = icmp ne %struct.Token* %172, %173
  br i1 %174, label %175, label %188

175:                                              ; preds = %171
  %176 = load i32, i32* %11, align 4
  %177 = load %struct.Token*, %struct.Token** %12, align 8
  %178 = getelementptr inbounds %struct.Token, %struct.Token* %177, i32 0, i32 6
  %179 = load %struct.Type*, %struct.Type** %178, align 16
  %180 = getelementptr inbounds %struct.Type, %struct.Type* %179, i32 0, i32 11
  %181 = load i32, i32* %180, align 8
  %182 = add nsw i32 %176, %181
  %183 = sub nsw i32 %182, 1
  store i32 %183, i32* %11, align 4
  br label %184

184:                                              ; preds = %175
  %185 = load %struct.Token*, %struct.Token** %12, align 8
  %186 = getelementptr inbounds %struct.Token, %struct.Token* %185, i32 0, i32 1
  %187 = load %struct.Token*, %struct.Token** %186, align 8
  store %struct.Token* %187, %struct.Token** %12, align 8
  br label %171, !llvm.loop !20

188:                                              ; preds = %171
  %189 = load %struct.Token*, %struct.Token** %9, align 8
  %190 = getelementptr inbounds %struct.Token, %struct.Token* %189, i32 0, i32 6
  %191 = load %struct.Type*, %struct.Type** %190, align 16
  %192 = getelementptr inbounds %struct.Type, %struct.Type* %191, i32 0, i32 8
  %193 = load %struct.Type*, %struct.Type** %192, align 8
  %194 = getelementptr inbounds %struct.Type, %struct.Type* %193, i32 0, i32 1
  %195 = load i32, i32* %194, align 4
  %196 = sext i32 %195 to i64
  %197 = load i32, i32* %11, align 4
  %198 = sext i32 %197 to i64
  %199 = call noalias i8* @calloc(i64 noundef %196, i64 noundef %198) #9
  store i8* %199, i8** %13, align 8
  %200 = load i8*, i8** %13, align 8
  %201 = icmp eq i8* %200, null
  br i1 %201, label %202, label %203

202:                                              ; preds = %188
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([52 x i8], [52 x i8]* @.str.119, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

203:                                              ; preds = %188
  store i32 0, i32* %14, align 4
  %204 = load %struct.Token*, %struct.Token** %9, align 8
  store %struct.Token* %204, %struct.Token** %15, align 8
  br label %205

205:                                              ; preds = %238, %203
  %206 = load %struct.Token*, %struct.Token** %15, align 8
  %207 = load %struct.Token*, %struct.Token** %10, align 8
  %208 = icmp ne %struct.Token* %206, %207
  br i1 %208, label %209, label %242

209:                                              ; preds = %205
  %210 = load i8*, i8** %13, align 8
  %211 = load i32, i32* %14, align 4
  %212 = sext i32 %211 to i64
  %213 = getelementptr inbounds i8, i8* %210, i64 %212
  %214 = load %struct.Token*, %struct.Token** %15, align 8
  %215 = getelementptr inbounds %struct.Token, %struct.Token* %214, i32 0, i32 7
  %216 = load i8*, i8** %215, align 8
  %217 = load %struct.Token*, %struct.Token** %15, align 8
  %218 = getelementptr inbounds %struct.Token, %struct.Token* %217, i32 0, i32 6
  %219 = load %struct.Type*, %struct.Type** %218, align 16
  %220 = getelementptr inbounds %struct.Type, %struct.Type* %219, i32 0, i32 1
  %221 = load i32, i32* %220, align 4
  %222 = sext i32 %221 to i64
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %213, i8* align 1 %216, i64 %222, i1 false)
  %223 = load i32, i32* %14, align 4
  %224 = load %struct.Token*, %struct.Token** %15, align 8
  %225 = getelementptr inbounds %struct.Token, %struct.Token* %224, i32 0, i32 6
  %226 = load %struct.Type*, %struct.Type** %225, align 16
  %227 = getelementptr inbounds %struct.Type, %struct.Type* %226, i32 0, i32 1
  %228 = load i32, i32* %227, align 4
  %229 = add nsw i32 %223, %228
  %230 = load %struct.Token*, %struct.Token** %15, align 8
  %231 = getelementptr inbounds %struct.Token, %struct.Token* %230, i32 0, i32 6
  %232 = load %struct.Type*, %struct.Type** %231, align 16
  %233 = getelementptr inbounds %struct.Type, %struct.Type* %232, i32 0, i32 8
  %234 = load %struct.Type*, %struct.Type** %233, align 8
  %235 = getelementptr inbounds %struct.Type, %struct.Type* %234, i32 0, i32 1
  %236 = load i32, i32* %235, align 4
  %237 = sub nsw i32 %229, %236
  store i32 %237, i32* %14, align 4
  br label %238

238:                                              ; preds = %209
  %239 = load %struct.Token*, %struct.Token** %15, align 8
  %240 = getelementptr inbounds %struct.Token, %struct.Token* %239, i32 0, i32 1
  %241 = load %struct.Token*, %struct.Token** %240, align 8
  store %struct.Token* %241, %struct.Token** %15, align 8
  br label %205, !llvm.loop !21

242:                                              ; preds = %205
  %243 = load %struct.Token*, %struct.Token** %9, align 8
  %244 = load %struct.Token*, %struct.Token** %9, align 8
  %245 = call %struct.Token* @copy_token(%struct.Token* noundef %244)
  %246 = bitcast %struct.Token* %243 to i8*
  %247 = bitcast %struct.Token* %245 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %246, i8* align 16 %247, i64 128, i1 false)
  %248 = load %struct.Token*, %struct.Token** %9, align 8
  %249 = getelementptr inbounds %struct.Token, %struct.Token* %248, i32 0, i32 6
  %250 = load %struct.Type*, %struct.Type** %249, align 16
  %251 = getelementptr inbounds %struct.Type, %struct.Type* %250, i32 0, i32 8
  %252 = load %struct.Type*, %struct.Type** %251, align 8
  %253 = load i32, i32* %11, align 4
  %254 = call %struct.Type* @array_of(%struct.Type* noundef %252, i32 noundef %253)
  %255 = load %struct.Token*, %struct.Token** %9, align 8
  %256 = getelementptr inbounds %struct.Token, %struct.Token* %255, i32 0, i32 6
  store %struct.Type* %254, %struct.Type** %256, align 16
  %257 = load i8*, i8** %13, align 8
  %258 = load %struct.Token*, %struct.Token** %9, align 8
  %259 = getelementptr inbounds %struct.Token, %struct.Token* %258, i32 0, i32 7
  store i8* %257, i8** %259, align 8
  %260 = load %struct.Token*, %struct.Token** %10, align 8
  %261 = load %struct.Token*, %struct.Token** %9, align 8
  %262 = getelementptr inbounds %struct.Token, %struct.Token* %261, i32 0, i32 1
  store %struct.Token* %260, %struct.Token** %262, align 8
  %263 = load %struct.Token*, %struct.Token** %10, align 8
  store %struct.Token* %263, %struct.Token** %9, align 8
  br label %128, !llvm.loop !18

264:                                              ; preds = %128
  ret void
}

; Function Attrs: nounwind readnone willreturn
declare i32 @abs(i32 noundef) #5

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #6

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Macro* @find_macro(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Macro*, align 8
  %3 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %4 = load %struct.Token*, %struct.Token** %3, align 8
  %5 = getelementptr inbounds %struct.Token, %struct.Token* %4, i32 0, i32 0
  %6 = load i32, i32* %5, align 16
  %7 = icmp ne i32 %6, 0
  br i1 %7, label %8, label %9

8:                                                ; preds = %1
  store %struct.Macro* null, %struct.Macro** %2, align 8
  br label %18

9:                                                ; preds = %1
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 4
  %12 = load i8*, i8** %11, align 16
  %13 = load %struct.Token*, %struct.Token** %3, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 5
  %15 = load i32, i32* %14, align 8
  %16 = call i8* @hashmap_get2(%struct.HashMap* noundef @macros, i8* noundef %12, i32 noundef %15)
  %17 = bitcast i8* %16 to %struct.Macro*
  store %struct.Macro* %17, %struct.Macro** %2, align 8
  br label %18

18:                                               ; preds = %9, %8
  %19 = load %struct.Macro*, %struct.Macro** %2, align 8
  ret %struct.Macro* %19
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @expand_macro(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca i1, align 1
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Macro*, align 8
  %7 = alloca %struct.Hideset*, align 8
  %8 = alloca %struct.Token*, align 8
  %9 = alloca %struct.Token*, align 8
  %10 = alloca %struct.Token*, align 8
  %11 = alloca %struct.MacroArg*, align 8
  %12 = alloca %struct.Token*, align 8
  %13 = alloca %struct.Hideset*, align 8
  %14 = alloca %struct.Token*, align 8
  %15 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %16 = load %struct.Token*, %struct.Token** %5, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 14
  %18 = load %struct.Hideset*, %struct.Hideset** %17, align 16
  %19 = load %struct.Token*, %struct.Token** %5, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 4
  %21 = load i8*, i8** %20, align 16
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = getelementptr inbounds %struct.Token, %struct.Token* %22, i32 0, i32 5
  %24 = load i32, i32* %23, align 8
  %25 = call zeroext i1 @hideset_contains(%struct.Hideset* noundef %18, i8* noundef %21, i32 noundef %24)
  br i1 %25, label %26, label %27

26:                                               ; preds = %2
  store i1 false, i1* %3, align 1
  br label %158

27:                                               ; preds = %2
  %28 = load %struct.Token*, %struct.Token** %5, align 8
  %29 = call %struct.Macro* @find_macro(%struct.Token* noundef %28)
  store %struct.Macro* %29, %struct.Macro** %6, align 8
  %30 = load %struct.Macro*, %struct.Macro** %6, align 8
  %31 = icmp ne %struct.Macro* %30, null
  br i1 %31, label %33, label %32

32:                                               ; preds = %27
  store i1 false, i1* %3, align 1
  br label %158

33:                                               ; preds = %27
  %34 = load %struct.Macro*, %struct.Macro** %6, align 8
  %35 = getelementptr inbounds %struct.Macro, %struct.Macro* %34, i32 0, i32 5
  %36 = load %struct.Token* (%struct.Token*)*, %struct.Token* (%struct.Token*)** %35, align 8
  %37 = icmp ne %struct.Token* (%struct.Token*)* %36, null
  br i1 %37, label %38, label %51

38:                                               ; preds = %33
  %39 = load %struct.Macro*, %struct.Macro** %6, align 8
  %40 = getelementptr inbounds %struct.Macro, %struct.Macro* %39, i32 0, i32 5
  %41 = load %struct.Token* (%struct.Token*)*, %struct.Token* (%struct.Token*)** %40, align 8
  %42 = load %struct.Token*, %struct.Token** %5, align 8
  %43 = call %struct.Token* %41(%struct.Token* noundef %42)
  %44 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %43, %struct.Token** %44, align 8
  %45 = load %struct.Token*, %struct.Token** %5, align 8
  %46 = getelementptr inbounds %struct.Token, %struct.Token* %45, i32 0, i32 1
  %47 = load %struct.Token*, %struct.Token** %46, align 8
  %48 = load %struct.Token**, %struct.Token*** %4, align 8
  %49 = load %struct.Token*, %struct.Token** %48, align 8
  %50 = getelementptr inbounds %struct.Token, %struct.Token* %49, i32 0, i32 1
  store %struct.Token* %47, %struct.Token** %50, align 8
  store i1 true, i1* %3, align 1
  br label %158

51:                                               ; preds = %33
  %52 = load %struct.Macro*, %struct.Macro** %6, align 8
  %53 = getelementptr inbounds %struct.Macro, %struct.Macro* %52, i32 0, i32 1
  %54 = load i8, i8* %53, align 8
  %55 = trunc i8 %54 to i1
  br i1 %55, label %56, label %99

56:                                               ; preds = %51
  %57 = load %struct.Token*, %struct.Token** %5, align 8
  %58 = getelementptr inbounds %struct.Token, %struct.Token* %57, i32 0, i32 14
  %59 = load %struct.Hideset*, %struct.Hideset** %58, align 16
  %60 = load %struct.Macro*, %struct.Macro** %6, align 8
  %61 = getelementptr inbounds %struct.Macro, %struct.Macro* %60, i32 0, i32 0
  %62 = load i8*, i8** %61, align 8
  %63 = call %struct.Hideset* @new_hideset(i8* noundef %62)
  %64 = call %struct.Hideset* @hideset_union(%struct.Hideset* noundef %59, %struct.Hideset* noundef %63)
  store %struct.Hideset* %64, %struct.Hideset** %7, align 8
  %65 = load %struct.Macro*, %struct.Macro** %6, align 8
  %66 = getelementptr inbounds %struct.Macro, %struct.Macro* %65, i32 0, i32 4
  %67 = load %struct.Token*, %struct.Token** %66, align 8
  %68 = load %struct.Hideset*, %struct.Hideset** %7, align 8
  %69 = call %struct.Token* @add_hideset(%struct.Token* noundef %67, %struct.Hideset* noundef %68)
  store %struct.Token* %69, %struct.Token** %8, align 8
  %70 = load %struct.Token*, %struct.Token** %8, align 8
  store %struct.Token* %70, %struct.Token** %9, align 8
  br label %71

71:                                               ; preds = %80, %56
  %72 = load %struct.Token*, %struct.Token** %9, align 8
  %73 = getelementptr inbounds %struct.Token, %struct.Token* %72, i32 0, i32 0
  %74 = load i32, i32* %73, align 16
  %75 = icmp ne i32 %74, 6
  br i1 %75, label %76, label %84

76:                                               ; preds = %71
  %77 = load %struct.Token*, %struct.Token** %5, align 8
  %78 = load %struct.Token*, %struct.Token** %9, align 8
  %79 = getelementptr inbounds %struct.Token, %struct.Token* %78, i32 0, i32 15
  store %struct.Token* %77, %struct.Token** %79, align 8
  br label %80

80:                                               ; preds = %76
  %81 = load %struct.Token*, %struct.Token** %9, align 8
  %82 = getelementptr inbounds %struct.Token, %struct.Token* %81, i32 0, i32 1
  %83 = load %struct.Token*, %struct.Token** %82, align 8
  store %struct.Token* %83, %struct.Token** %9, align 8
  br label %71, !llvm.loop !22

84:                                               ; preds = %71
  %85 = load %struct.Token*, %struct.Token** %8, align 8
  %86 = load %struct.Token*, %struct.Token** %5, align 8
  %87 = getelementptr inbounds %struct.Token, %struct.Token* %86, i32 0, i32 1
  %88 = load %struct.Token*, %struct.Token** %87, align 8
  %89 = call %struct.Token* @append(%struct.Token* noundef %85, %struct.Token* noundef %88)
  %90 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %89, %struct.Token** %90, align 8
  %91 = load %struct.Token*, %struct.Token** %5, align 8
  %92 = getelementptr inbounds %struct.Token, %struct.Token* %91, i32 0, i32 13
  %93 = load i8, i8* %92, align 1
  %94 = trunc i8 %93 to i1
  %95 = load %struct.Token**, %struct.Token*** %4, align 8
  %96 = load %struct.Token*, %struct.Token** %95, align 8
  %97 = getelementptr inbounds %struct.Token, %struct.Token* %96, i32 0, i32 13
  %98 = zext i1 %94 to i8
  store i8 %98, i8* %97, align 1
  store i1 true, i1* %3, align 1
  br label %158

99:                                               ; preds = %51
  %100 = load %struct.Token*, %struct.Token** %5, align 8
  %101 = getelementptr inbounds %struct.Token, %struct.Token* %100, i32 0, i32 1
  %102 = load %struct.Token*, %struct.Token** %101, align 8
  %103 = call zeroext i1 @equal(%struct.Token* noundef %102, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.103, i64 0, i64 0))
  br i1 %103, label %105, label %104

104:                                              ; preds = %99
  store i1 false, i1* %3, align 1
  br label %158

105:                                              ; preds = %99
  %106 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %106, %struct.Token** %10, align 8
  %107 = load %struct.Token*, %struct.Token** %5, align 8
  %108 = load %struct.Macro*, %struct.Macro** %6, align 8
  %109 = getelementptr inbounds %struct.Macro, %struct.Macro* %108, i32 0, i32 2
  %110 = load %struct.MacroParam*, %struct.MacroParam** %109, align 8
  %111 = load %struct.Macro*, %struct.Macro** %6, align 8
  %112 = getelementptr inbounds %struct.Macro, %struct.Macro* %111, i32 0, i32 3
  %113 = load i8*, i8** %112, align 8
  %114 = call %struct.MacroArg* @read_macro_args(%struct.Token** noundef %5, %struct.Token* noundef %107, %struct.MacroParam* noundef %110, i8* noundef %113)
  store %struct.MacroArg* %114, %struct.MacroArg** %11, align 8
  %115 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %115, %struct.Token** %12, align 8
  %116 = load %struct.Token*, %struct.Token** %10, align 8
  %117 = getelementptr inbounds %struct.Token, %struct.Token* %116, i32 0, i32 14
  %118 = load %struct.Hideset*, %struct.Hideset** %117, align 16
  %119 = load %struct.Token*, %struct.Token** %12, align 8
  %120 = getelementptr inbounds %struct.Token, %struct.Token* %119, i32 0, i32 14
  %121 = load %struct.Hideset*, %struct.Hideset** %120, align 16
  %122 = call %struct.Hideset* @hideset_intersection(%struct.Hideset* noundef %118, %struct.Hideset* noundef %121)
  store %struct.Hideset* %122, %struct.Hideset** %13, align 8
  %123 = load %struct.Hideset*, %struct.Hideset** %13, align 8
  %124 = load %struct.Macro*, %struct.Macro** %6, align 8
  %125 = getelementptr inbounds %struct.Macro, %struct.Macro* %124, i32 0, i32 0
  %126 = load i8*, i8** %125, align 8
  %127 = call %struct.Hideset* @new_hideset(i8* noundef %126)
  %128 = call %struct.Hideset* @hideset_union(%struct.Hideset* noundef %123, %struct.Hideset* noundef %127)
  store %struct.Hideset* %128, %struct.Hideset** %13, align 8
  %129 = load %struct.Macro*, %struct.Macro** %6, align 8
  %130 = getelementptr inbounds %struct.Macro, %struct.Macro* %129, i32 0, i32 4
  %131 = load %struct.Token*, %struct.Token** %130, align 8
  %132 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %133 = call %struct.Token* @subst(%struct.Token* noundef %131, %struct.MacroArg* noundef %132)
  store %struct.Token* %133, %struct.Token** %14, align 8
  %134 = load %struct.Token*, %struct.Token** %14, align 8
  %135 = load %struct.Hideset*, %struct.Hideset** %13, align 8
  %136 = call %struct.Token* @add_hideset(%struct.Token* noundef %134, %struct.Hideset* noundef %135)
  store %struct.Token* %136, %struct.Token** %14, align 8
  %137 = load %struct.Token*, %struct.Token** %14, align 8
  store %struct.Token* %137, %struct.Token** %15, align 8
  br label %138

138:                                              ; preds = %147, %105
  %139 = load %struct.Token*, %struct.Token** %15, align 8
  %140 = getelementptr inbounds %struct.Token, %struct.Token* %139, i32 0, i32 0
  %141 = load i32, i32* %140, align 16
  %142 = icmp ne i32 %141, 6
  br i1 %142, label %143, label %151

143:                                              ; preds = %138
  %144 = load %struct.Token*, %struct.Token** %10, align 8
  %145 = load %struct.Token*, %struct.Token** %15, align 8
  %146 = getelementptr inbounds %struct.Token, %struct.Token* %145, i32 0, i32 15
  store %struct.Token* %144, %struct.Token** %146, align 8
  br label %147

147:                                              ; preds = %143
  %148 = load %struct.Token*, %struct.Token** %15, align 8
  %149 = getelementptr inbounds %struct.Token, %struct.Token* %148, i32 0, i32 1
  %150 = load %struct.Token*, %struct.Token** %149, align 8
  store %struct.Token* %150, %struct.Token** %15, align 8
  br label %138, !llvm.loop !23

151:                                              ; preds = %138
  %152 = load %struct.Token*, %struct.Token** %14, align 8
  %153 = load %struct.Token*, %struct.Token** %5, align 8
  %154 = getelementptr inbounds %struct.Token, %struct.Token* %153, i32 0, i32 1
  %155 = load %struct.Token*, %struct.Token** %154, align 8
  %156 = call %struct.Token* @append(%struct.Token* noundef %152, %struct.Token* noundef %155)
  %157 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %156, %struct.Token** %157, align 8
  store i1 true, i1* %3, align 1
  br label %158

158:                                              ; preds = %151, %104, %84, %38, %32, %26
  %159 = load i1, i1* %3, align 1
  ret i1 %159
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64 noundef, i64 noundef) #3

; Function Attrs: noreturn
declare void @error(i8* noundef, ...) #4

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @new_str_token(i8* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load i8*, i8** %3, align 8
  %7 = call i8* @quote_string(i8* noundef %6)
  store i8* %7, i8** %5, align 8
  %8 = load %struct.Token*, %struct.Token** %4, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 8
  %10 = load %struct.File*, %struct.File** %9, align 16
  %11 = getelementptr inbounds %struct.File, %struct.File* %10, i32 0, i32 0
  %12 = load i8*, i8** %11, align 8
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 8
  %15 = load %struct.File*, %struct.File** %14, align 16
  %16 = getelementptr inbounds %struct.File, %struct.File* %15, i32 0, i32 1
  %17 = load i32, i32* %16, align 8
  %18 = load i8*, i8** %5, align 8
  %19 = call %struct.File* @new_file(i8* noundef %12, i32 noundef %17, i8* noundef %18)
  %20 = call %struct.Token* @tokenize(%struct.File* noundef %19)
  ret %struct.Token* %20
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @quote_string(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  store i32 3, i32* %3, align 4
  store i32 0, i32* %4, align 4
  br label %8

8:                                                ; preds = %37, %1
  %9 = load i8*, i8** %2, align 8
  %10 = load i32, i32* %4, align 4
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds i8, i8* %9, i64 %11
  %13 = load i8, i8* %12, align 1
  %14 = icmp ne i8 %13, 0
  br i1 %14, label %15, label %40

15:                                               ; preds = %8
  %16 = load i8*, i8** %2, align 8
  %17 = load i32, i32* %4, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds i8, i8* %16, i64 %18
  %20 = load i8, i8* %19, align 1
  %21 = sext i8 %20 to i32
  %22 = icmp eq i32 %21, 92
  br i1 %22, label %31, label %23

23:                                               ; preds = %15
  %24 = load i8*, i8** %2, align 8
  %25 = load i32, i32* %4, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds i8, i8* %24, i64 %26
  %28 = load i8, i8* %27, align 1
  %29 = sext i8 %28 to i32
  %30 = icmp eq i32 %29, 34
  br i1 %30, label %31, label %34

31:                                               ; preds = %23, %15
  %32 = load i32, i32* %3, align 4
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %3, align 4
  br label %34

34:                                               ; preds = %31, %23
  %35 = load i32, i32* %3, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %3, align 4
  br label %37

37:                                               ; preds = %34
  %38 = load i32, i32* %4, align 4
  %39 = add nsw i32 %38, 1
  store i32 %39, i32* %4, align 4
  br label %8, !llvm.loop !24

40:                                               ; preds = %8
  %41 = load i32, i32* %3, align 4
  %42 = sext i32 %41 to i64
  %43 = call noalias i8* @calloc(i64 noundef 1, i64 noundef %42) #9
  store i8* %43, i8** %5, align 8
  %44 = load i8*, i8** %5, align 8
  %45 = icmp eq i8* %44, null
  br i1 %45, label %46, label %47

46:                                               ; preds = %40
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([34 x i8], [34 x i8]* @.str.67, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

47:                                               ; preds = %40
  %48 = load i8*, i8** %5, align 8
  store i8* %48, i8** %6, align 8
  %49 = load i8*, i8** %6, align 8
  %50 = getelementptr inbounds i8, i8* %49, i32 1
  store i8* %50, i8** %6, align 8
  store i8 34, i8* %49, align 1
  store i32 0, i32* %7, align 4
  br label %51

51:                                               ; preds = %85, %47
  %52 = load i8*, i8** %2, align 8
  %53 = load i32, i32* %7, align 4
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds i8, i8* %52, i64 %54
  %56 = load i8, i8* %55, align 1
  %57 = icmp ne i8 %56, 0
  br i1 %57, label %58, label %88

58:                                               ; preds = %51
  %59 = load i8*, i8** %2, align 8
  %60 = load i32, i32* %7, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds i8, i8* %59, i64 %61
  %63 = load i8, i8* %62, align 1
  %64 = sext i8 %63 to i32
  %65 = icmp eq i32 %64, 92
  br i1 %65, label %74, label %66

66:                                               ; preds = %58
  %67 = load i8*, i8** %2, align 8
  %68 = load i32, i32* %7, align 4
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds i8, i8* %67, i64 %69
  %71 = load i8, i8* %70, align 1
  %72 = sext i8 %71 to i32
  %73 = icmp eq i32 %72, 34
  br i1 %73, label %74, label %77

74:                                               ; preds = %66, %58
  %75 = load i8*, i8** %6, align 8
  %76 = getelementptr inbounds i8, i8* %75, i32 1
  store i8* %76, i8** %6, align 8
  store i8 92, i8* %75, align 1
  br label %77

77:                                               ; preds = %74, %66
  %78 = load i8*, i8** %2, align 8
  %79 = load i32, i32* %7, align 4
  %80 = sext i32 %79 to i64
  %81 = getelementptr inbounds i8, i8* %78, i64 %80
  %82 = load i8, i8* %81, align 1
  %83 = load i8*, i8** %6, align 8
  %84 = getelementptr inbounds i8, i8* %83, i32 1
  store i8* %84, i8** %6, align 8
  store i8 %82, i8* %83, align 1
  br label %85

85:                                               ; preds = %77
  %86 = load i32, i32* %7, align 4
  %87 = add nsw i32 %86, 1
  store i32 %87, i32* %7, align 4
  br label %51, !llvm.loop !25

88:                                               ; preds = %51
  %89 = load i8*, i8** %6, align 8
  %90 = getelementptr inbounds i8, i8* %89, i32 1
  store i8* %90, i8** %6, align 8
  store i8 34, i8* %89, align 1
  %91 = load i8*, i8** %6, align 8
  %92 = getelementptr inbounds i8, i8* %91, i32 1
  store i8* %92, i8** %6, align 8
  store i8 0, i8* %91, align 1
  %93 = load i8*, i8** %5, align 8
  ret i8* %93
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @new_num_token(i32 noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca %struct.Token*, align 8
  %5 = alloca i8*, align 8
  store i32 %0, i32* %3, align 4
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load i32, i32* %3, align 4
  %7 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.68, i64 0, i64 0), i32 noundef %6)
  store i8* %7, i8** %5, align 8
  %8 = load %struct.Token*, %struct.Token** %4, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 8
  %10 = load %struct.File*, %struct.File** %9, align 16
  %11 = getelementptr inbounds %struct.File, %struct.File* %10, i32 0, i32 0
  %12 = load i8*, i8** %11, align 8
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 8
  %15 = load %struct.File*, %struct.File** %14, align 16
  %16 = getelementptr inbounds %struct.File, %struct.File* %15, i32 0, i32 1
  %17 = load i32, i32* %16, align 8
  %18 = load i8*, i8** %5, align 8
  %19 = call %struct.File* @new_file(i8* noundef %12, i32 noundef %17, i8* noundef %18)
  %20 = call %struct.Token* @tokenize(%struct.File* noundef %19)
  ret %struct.Token* %20
}

; Function Attrs: nounwind
declare i32 @stat(i8* noundef, %struct.stat* noundef) #3

; Function Attrs: nounwind
declare i8* @ctime_r(i64* noundef, i8* noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @is_hash(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %3 = load %struct.Token*, %struct.Token** %2, align 8
  %4 = getelementptr inbounds %struct.Token, %struct.Token* %3, i32 0, i32 12
  %5 = load i8, i8* %4, align 8
  %6 = trunc i8 %5 to i1
  br i1 %6, label %7, label %10

7:                                                ; preds = %1
  %8 = load %struct.Token*, %struct.Token** %2, align 8
  %9 = call zeroext i1 @equal(%struct.Token* noundef %8, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.94, i64 0, i64 0))
  br label %10

10:                                               ; preds = %7, %1
  %11 = phi i1 [ false, %1 ], [ %9, %7 ]
  ret i1 %11
}

declare zeroext i1 @equal(%struct.Token* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @read_include_filename(%struct.Token** noundef %0, %struct.Token* noundef %1, i8* noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca %struct.Token*, align 8
  %9 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store i8* %2, i8** %7, align 8
  %10 = load %struct.Token*, %struct.Token** %6, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 0
  %12 = load i32, i32* %11, align 16
  %13 = icmp eq i32 %12, 3
  br i1 %13, label %14, label %31

14:                                               ; preds = %3
  %15 = load i8*, i8** %7, align 8
  store i8 1, i8* %15, align 1
  %16 = load %struct.Token*, %struct.Token** %6, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 1
  %18 = load %struct.Token*, %struct.Token** %17, align 8
  %19 = call %struct.Token* @skip_line(%struct.Token* noundef %18)
  %20 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %19, %struct.Token** %20, align 8
  %21 = load %struct.Token*, %struct.Token** %6, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 4
  %23 = load i8*, i8** %22, align 16
  %24 = getelementptr inbounds i8, i8* %23, i64 1
  %25 = load %struct.Token*, %struct.Token** %6, align 8
  %26 = getelementptr inbounds %struct.Token, %struct.Token* %25, i32 0, i32 5
  %27 = load i32, i32* %26, align 8
  %28 = sub nsw i32 %27, 2
  %29 = sext i32 %28 to i64
  %30 = call noalias i8* @strndup(i8* noundef %24, i64 noundef %29) #9
  store i8* %30, i8** %4, align 8
  br label %84

31:                                               ; preds = %3
  %32 = load %struct.Token*, %struct.Token** %6, align 8
  %33 = call zeroext i1 @equal(%struct.Token* noundef %32, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.95, i64 0, i64 0))
  br i1 %33, label %34, label %69

34:                                               ; preds = %31
  %35 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %35, %struct.Token** %8, align 8
  br label %36

36:                                               ; preds = %53, %34
  %37 = load %struct.Token*, %struct.Token** %6, align 8
  %38 = call zeroext i1 @equal(%struct.Token* noundef %37, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.96, i64 0, i64 0))
  %39 = xor i1 %38, true
  br i1 %39, label %40, label %57

40:                                               ; preds = %36
  %41 = load %struct.Token*, %struct.Token** %6, align 8
  %42 = getelementptr inbounds %struct.Token, %struct.Token* %41, i32 0, i32 12
  %43 = load i8, i8* %42, align 8
  %44 = trunc i8 %43 to i1
  br i1 %44, label %50, label %45

45:                                               ; preds = %40
  %46 = load %struct.Token*, %struct.Token** %6, align 8
  %47 = getelementptr inbounds %struct.Token, %struct.Token* %46, i32 0, i32 0
  %48 = load i32, i32* %47, align 16
  %49 = icmp eq i32 %48, 6
  br i1 %49, label %50, label %52

50:                                               ; preds = %45, %40
  %51 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %51, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.97, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

52:                                               ; preds = %45
  br label %53

53:                                               ; preds = %52
  %54 = load %struct.Token*, %struct.Token** %6, align 8
  %55 = getelementptr inbounds %struct.Token, %struct.Token* %54, i32 0, i32 1
  %56 = load %struct.Token*, %struct.Token** %55, align 8
  store %struct.Token* %56, %struct.Token** %6, align 8
  br label %36, !llvm.loop !26

57:                                               ; preds = %36
  %58 = load i8*, i8** %7, align 8
  store i8 0, i8* %58, align 1
  %59 = load %struct.Token*, %struct.Token** %6, align 8
  %60 = getelementptr inbounds %struct.Token, %struct.Token* %59, i32 0, i32 1
  %61 = load %struct.Token*, %struct.Token** %60, align 8
  %62 = call %struct.Token* @skip_line(%struct.Token* noundef %61)
  %63 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %62, %struct.Token** %63, align 8
  %64 = load %struct.Token*, %struct.Token** %8, align 8
  %65 = getelementptr inbounds %struct.Token, %struct.Token* %64, i32 0, i32 1
  %66 = load %struct.Token*, %struct.Token** %65, align 8
  %67 = load %struct.Token*, %struct.Token** %6, align 8
  %68 = call i8* @join_tokens(%struct.Token* noundef %66, %struct.Token* noundef %67)
  store i8* %68, i8** %4, align 8
  br label %84

69:                                               ; preds = %31
  %70 = load %struct.Token*, %struct.Token** %6, align 8
  %71 = getelementptr inbounds %struct.Token, %struct.Token* %70, i32 0, i32 0
  %72 = load i32, i32* %71, align 16
  %73 = icmp eq i32 %72, 0
  br i1 %73, label %74, label %82

74:                                               ; preds = %69
  %75 = load %struct.Token**, %struct.Token*** %5, align 8
  %76 = load %struct.Token*, %struct.Token** %6, align 8
  %77 = call %struct.Token* @copy_line(%struct.Token** noundef %75, %struct.Token* noundef %76)
  %78 = call %struct.Token* @preprocess2(%struct.Token* noundef %77)
  store %struct.Token* %78, %struct.Token** %9, align 8
  %79 = load %struct.Token*, %struct.Token** %9, align 8
  %80 = load i8*, i8** %7, align 8
  %81 = call i8* @read_include_filename(%struct.Token** noundef %9, %struct.Token* noundef %79, i8* noundef %80)
  store i8* %81, i8** %4, align 8
  br label %84

82:                                               ; preds = %69
  %83 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %83, i8* noundef getelementptr inbounds ([51 x i8], [51 x i8]* @.str.98, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

84:                                               ; preds = %74, %57, %14
  %85 = load i8*, i8** %4, align 8
  ret i8* %85
}

; Function Attrs: nounwind
declare i8* @dirname(i8* noundef) #3

; Function Attrs: nounwind
declare noalias i8* @strdup(i8* noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @include_file(%struct.Token* noundef %0, i8* noundef %1, %struct.Token* noundef %2) #0 {
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %5, align 8
  store i8* %1, i8** %6, align 8
  store %struct.Token* %2, %struct.Token** %7, align 8
  %10 = load i8*, i8** %6, align 8
  %11 = call i8* @hashmap_get(%struct.HashMap* noundef @pragma_once, i8* noundef %10)
  %12 = icmp ne i8* %11, null
  br i1 %12, label %13, label %15

13:                                               ; preds = %3
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %14, %struct.Token** %4, align 8
  br label %49

15:                                               ; preds = %3
  %16 = load i8*, i8** %6, align 8
  %17 = call i8* @hashmap_get(%struct.HashMap* noundef @include_file.include_guards, i8* noundef %16)
  store i8* %17, i8** %8, align 8
  %18 = load i8*, i8** %8, align 8
  %19 = icmp ne i8* %18, null
  br i1 %19, label %20, label %26

20:                                               ; preds = %15
  %21 = load i8*, i8** %8, align 8
  %22 = call i8* @hashmap_get(%struct.HashMap* noundef @macros, i8* noundef %21)
  %23 = icmp ne i8* %22, null
  br i1 %23, label %24, label %26

24:                                               ; preds = %20
  %25 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %25, %struct.Token** %4, align 8
  br label %49

26:                                               ; preds = %20, %15
  %27 = load i8*, i8** %6, align 8
  %28 = call %struct.Token* @tokenize_file(i8* noundef %27)
  store %struct.Token* %28, %struct.Token** %9, align 8
  %29 = load %struct.Token*, %struct.Token** %9, align 8
  %30 = icmp ne %struct.Token* %29, null
  br i1 %30, label %37, label %31

31:                                               ; preds = %26
  %32 = load %struct.Token*, %struct.Token** %7, align 8
  %33 = load i8*, i8** %6, align 8
  %34 = call i32* @__errno_location() #11
  %35 = load i32, i32* %34, align 4
  %36 = call i8* @strerror(i32 noundef %35) #9
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %32, i8* noundef getelementptr inbounds ([47 x i8], [47 x i8]* @.str.101, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0), i8* noundef %33, i8* noundef %36) #10
  unreachable

37:                                               ; preds = %26
  %38 = load %struct.Token*, %struct.Token** %9, align 8
  %39 = call i8* @detect_include_guard(%struct.Token* noundef %38)
  store i8* %39, i8** %8, align 8
  %40 = load i8*, i8** %8, align 8
  %41 = icmp ne i8* %40, null
  br i1 %41, label %42, label %45

42:                                               ; preds = %37
  %43 = load i8*, i8** %6, align 8
  %44 = load i8*, i8** %8, align 8
  call void @hashmap_put(%struct.HashMap* noundef @include_file.include_guards, i8* noundef %43, i8* noundef %44)
  br label %45

45:                                               ; preds = %42, %37
  %46 = load %struct.Token*, %struct.Token** %9, align 8
  %47 = load %struct.Token*, %struct.Token** %5, align 8
  %48 = call %struct.Token* @append(%struct.Token* noundef %46, %struct.Token* noundef %47)
  store %struct.Token* %48, %struct.Token** %4, align 8
  br label %49

49:                                               ; preds = %45, %24, %13
  %50 = load %struct.Token*, %struct.Token** %4, align 8
  ret %struct.Token* %50
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @search_include_next(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  br label %5

5:                                                ; preds = %22, %1
  %6 = load i32, i32* @include_next_idx, align 4
  %7 = load i32, i32* getelementptr inbounds (%struct.StringArray, %struct.StringArray* @include_paths, i32 0, i32 2), align 4
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %9, label %25

9:                                                ; preds = %5
  %10 = load i8**, i8*** getelementptr inbounds (%struct.StringArray, %struct.StringArray* @include_paths, i32 0, i32 0), align 8
  %11 = load i32, i32* @include_next_idx, align 4
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds i8*, i8** %10, i64 %12
  %14 = load i8*, i8** %13, align 8
  %15 = load i8*, i8** %3, align 8
  %16 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0), i8* noundef %14, i8* noundef %15)
  store i8* %16, i8** %4, align 8
  %17 = load i8*, i8** %4, align 8
  %18 = call zeroext i1 @file_exists(i8* noundef %17)
  br i1 %18, label %19, label %21

19:                                               ; preds = %9
  %20 = load i8*, i8** %4, align 8
  store i8* %20, i8** %2, align 8
  br label %26

21:                                               ; preds = %9
  br label %22

22:                                               ; preds = %21
  %23 = load i32, i32* @include_next_idx, align 4
  %24 = add nsw i32 %23, 1
  store i32 %24, i32* @include_next_idx, align 4
  br label %5, !llvm.loop !27

25:                                               ; preds = %5
  store i8* null, i8** %2, align 8
  br label %26

26:                                               ; preds = %25, %19
  %27 = load i8*, i8** %2, align 8
  ret i8* %27
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @read_macro_definition(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca %struct.MacroParam*, align 8
  %8 = alloca %struct.Macro*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %9 = load %struct.Token*, %struct.Token** %4, align 8
  %10 = getelementptr inbounds %struct.Token, %struct.Token* %9, i32 0, i32 0
  %11 = load i32, i32* %10, align 16
  %12 = icmp ne i32 %11, 0
  br i1 %12, label %13, label %15

13:                                               ; preds = %2
  %14 = load %struct.Token*, %struct.Token** %4, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %14, i8* noundef getelementptr inbounds ([64 x i8], [64 x i8]* @.str.102, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

15:                                               ; preds = %2
  %16 = load %struct.Token*, %struct.Token** %4, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 4
  %18 = load i8*, i8** %17, align 16
  %19 = load %struct.Token*, %struct.Token** %4, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 5
  %21 = load i32, i32* %20, align 8
  %22 = sext i32 %21 to i64
  %23 = call noalias i8* @strndup(i8* noundef %18, i64 noundef %22) #9
  store i8* %23, i8** %5, align 8
  %24 = load %struct.Token*, %struct.Token** %4, align 8
  %25 = getelementptr inbounds %struct.Token, %struct.Token* %24, i32 0, i32 1
  %26 = load %struct.Token*, %struct.Token** %25, align 8
  store %struct.Token* %26, %struct.Token** %4, align 8
  %27 = load %struct.Token*, %struct.Token** %4, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 13
  %29 = load i8, i8* %28, align 1
  %30 = trunc i8 %29 to i1
  br i1 %30, label %50, label %31

31:                                               ; preds = %15
  %32 = load %struct.Token*, %struct.Token** %4, align 8
  %33 = call zeroext i1 @equal(%struct.Token* noundef %32, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.103, i64 0, i64 0))
  br i1 %33, label %34, label %50

34:                                               ; preds = %31
  store i8* null, i8** %6, align 8
  %35 = load %struct.Token*, %struct.Token** %4, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 1
  %37 = load %struct.Token*, %struct.Token** %36, align 8
  %38 = call %struct.MacroParam* @read_macro_params(%struct.Token** noundef %4, %struct.Token* noundef %37, i8** noundef %6)
  store %struct.MacroParam* %38, %struct.MacroParam** %7, align 8
  %39 = load i8*, i8** %5, align 8
  %40 = load %struct.Token**, %struct.Token*** %3, align 8
  %41 = load %struct.Token*, %struct.Token** %4, align 8
  %42 = call %struct.Token* @copy_line(%struct.Token** noundef %40, %struct.Token* noundef %41)
  %43 = call %struct.Macro* @add_macro(i8* noundef %39, i1 noundef zeroext false, %struct.Token* noundef %42)
  store %struct.Macro* %43, %struct.Macro** %8, align 8
  %44 = load %struct.MacroParam*, %struct.MacroParam** %7, align 8
  %45 = load %struct.Macro*, %struct.Macro** %8, align 8
  %46 = getelementptr inbounds %struct.Macro, %struct.Macro* %45, i32 0, i32 2
  store %struct.MacroParam* %44, %struct.MacroParam** %46, align 8
  %47 = load i8*, i8** %6, align 8
  %48 = load %struct.Macro*, %struct.Macro** %8, align 8
  %49 = getelementptr inbounds %struct.Macro, %struct.Macro* %48, i32 0, i32 3
  store i8* %47, i8** %49, align 8
  br label %56

50:                                               ; preds = %31, %15
  %51 = load i8*, i8** %5, align 8
  %52 = load %struct.Token**, %struct.Token*** %3, align 8
  %53 = load %struct.Token*, %struct.Token** %4, align 8
  %54 = call %struct.Token* @copy_line(%struct.Token** noundef %52, %struct.Token* noundef %53)
  %55 = call %struct.Macro* @add_macro(i8* noundef %51, i1 noundef zeroext true, %struct.Token* noundef %54)
  br label %56

56:                                               ; preds = %50, %34
  ret void
}

; Function Attrs: nounwind
declare noalias i8* @strndup(i8* noundef, i64 noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @skip_line(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %4 = load %struct.Token*, %struct.Token** %3, align 8
  %5 = getelementptr inbounds %struct.Token, %struct.Token* %4, i32 0, i32 12
  %6 = load i8, i8* %5, align 8
  %7 = trunc i8 %6 to i1
  br i1 %7, label %8, label %10

8:                                                ; preds = %1
  %9 = load %struct.Token*, %struct.Token** %3, align 8
  store %struct.Token* %9, %struct.Token** %2, align 8
  br label %24

10:                                               ; preds = %1
  %11 = load %struct.Token*, %struct.Token** %3, align 8
  call void (%struct.Token*, i8*, ...) @warn_tok(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.110, i64 0, i64 0))
  br label %12

12:                                               ; preds = %18, %10
  %13 = load %struct.Token*, %struct.Token** %3, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 12
  %15 = load i8, i8* %14, align 8
  %16 = trunc i8 %15 to i1
  %17 = xor i1 %16, true
  br i1 %17, label %18, label %22

18:                                               ; preds = %12
  %19 = load %struct.Token*, %struct.Token** %3, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 1
  %21 = load %struct.Token*, %struct.Token** %20, align 8
  store %struct.Token* %21, %struct.Token** %3, align 8
  br label %12, !llvm.loop !28

22:                                               ; preds = %12
  %23 = load %struct.Token*, %struct.Token** %3, align 8
  store %struct.Token* %23, %struct.Token** %2, align 8
  br label %24

24:                                               ; preds = %22, %8
  %25 = load %struct.Token*, %struct.Token** %2, align 8
  ret %struct.Token* %25
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i64 @eval_const_expr(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca %struct.Token*, align 8
  %9 = alloca %struct.Token*, align 8
  %10 = alloca i64, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %11, %struct.Token** %5, align 8
  %12 = load %struct.Token**, %struct.Token*** %3, align 8
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 1
  %15 = load %struct.Token*, %struct.Token** %14, align 8
  %16 = call %struct.Token* @read_const_expr(%struct.Token** noundef %12, %struct.Token* noundef %15)
  store %struct.Token* %16, %struct.Token** %6, align 8
  %17 = load %struct.Token*, %struct.Token** %6, align 8
  %18 = call %struct.Token* @preprocess2(%struct.Token* noundef %17)
  store %struct.Token* %18, %struct.Token** %6, align 8
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 0
  %21 = load i32, i32* %20, align 16
  %22 = icmp eq i32 %21, 6
  br i1 %22, label %23, label %25

23:                                               ; preds = %2
  %24 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %24, i8* noundef getelementptr inbounds ([39 x i8], [39 x i8]* @.str.111, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

25:                                               ; preds = %2
  %26 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %26, %struct.Token** %7, align 8
  br label %27

27:                                               ; preds = %50, %25
  %28 = load %struct.Token*, %struct.Token** %7, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 0
  %30 = load i32, i32* %29, align 16
  %31 = icmp ne i32 %30, 6
  br i1 %31, label %32, label %54

32:                                               ; preds = %27
  %33 = load %struct.Token*, %struct.Token** %7, align 8
  %34 = getelementptr inbounds %struct.Token, %struct.Token* %33, i32 0, i32 0
  %35 = load i32, i32* %34, align 16
  %36 = icmp eq i32 %35, 0
  br i1 %36, label %37, label %49

37:                                               ; preds = %32
  %38 = load %struct.Token*, %struct.Token** %7, align 8
  %39 = getelementptr inbounds %struct.Token, %struct.Token* %38, i32 0, i32 1
  %40 = load %struct.Token*, %struct.Token** %39, align 8
  store %struct.Token* %40, %struct.Token** %8, align 8
  %41 = load %struct.Token*, %struct.Token** %7, align 8
  %42 = load %struct.Token*, %struct.Token** %7, align 8
  %43 = call %struct.Token* @new_num_token(i32 noundef 0, %struct.Token* noundef %42)
  %44 = bitcast %struct.Token* %41 to i8*
  %45 = bitcast %struct.Token* %43 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %44, i8* align 16 %45, i64 128, i1 false)
  %46 = load %struct.Token*, %struct.Token** %8, align 8
  %47 = load %struct.Token*, %struct.Token** %7, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 1
  store %struct.Token* %46, %struct.Token** %48, align 8
  br label %49

49:                                               ; preds = %37, %32
  br label %50

50:                                               ; preds = %49
  %51 = load %struct.Token*, %struct.Token** %7, align 8
  %52 = getelementptr inbounds %struct.Token, %struct.Token* %51, i32 0, i32 1
  %53 = load %struct.Token*, %struct.Token** %52, align 8
  store %struct.Token* %53, %struct.Token** %7, align 8
  br label %27, !llvm.loop !29

54:                                               ; preds = %27
  %55 = load %struct.Token*, %struct.Token** %6, align 8
  call void @convert_pp_tokens(%struct.Token* noundef %55)
  %56 = load %struct.Token*, %struct.Token** %6, align 8
  %57 = call i64 @const_expr(%struct.Token** noundef %9, %struct.Token* noundef %56)
  store i64 %57, i64* %10, align 8
  %58 = load %struct.Token*, %struct.Token** %9, align 8
  %59 = getelementptr inbounds %struct.Token, %struct.Token* %58, i32 0, i32 0
  %60 = load i32, i32* %59, align 16
  %61 = icmp ne i32 %60, 6
  br i1 %61, label %62, label %64

62:                                               ; preds = %54
  %63 = load %struct.Token*, %struct.Token** %9, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %63, i8* noundef getelementptr inbounds ([37 x i8], [37 x i8]* @.str.112, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

64:                                               ; preds = %54
  %65 = load i64, i64* %10, align 8
  ret i64 %65
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.CondIncl* @push_cond_incl(%struct.Token* noundef %0, i1 noundef zeroext %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i8, align 1
  %5 = alloca %struct.CondIncl*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %6 = zext i1 %1 to i8
  store i8 %6, i8* %4, align 1
  %7 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 32) #9
  %8 = bitcast i8* %7 to %struct.CondIncl*
  store %struct.CondIncl* %8, %struct.CondIncl** %5, align 8
  %9 = load %struct.CondIncl*, %struct.CondIncl** %5, align 8
  %10 = icmp eq %struct.CondIncl* %9, null
  br i1 %10, label %11, label %12

11:                                               ; preds = %2
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([35 x i8], [35 x i8]* @.str.115, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

12:                                               ; preds = %2
  %13 = load %struct.CondIncl*, %struct.CondIncl** @cond_incl, align 8
  %14 = load %struct.CondIncl*, %struct.CondIncl** %5, align 8
  %15 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %14, i32 0, i32 0
  store %struct.CondIncl* %13, %struct.CondIncl** %15, align 8
  %16 = load %struct.CondIncl*, %struct.CondIncl** %5, align 8
  %17 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %16, i32 0, i32 1
  store i32 0, i32* %17, align 8
  %18 = load %struct.Token*, %struct.Token** %3, align 8
  %19 = load %struct.CondIncl*, %struct.CondIncl** %5, align 8
  %20 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %19, i32 0, i32 2
  store %struct.Token* %18, %struct.Token** %20, align 8
  %21 = load i8, i8* %4, align 1
  %22 = trunc i8 %21 to i1
  %23 = load %struct.CondIncl*, %struct.CondIncl** %5, align 8
  %24 = getelementptr inbounds %struct.CondIncl, %struct.CondIncl* %23, i32 0, i32 3
  %25 = zext i1 %22 to i8
  store i8 %25, i8* %24, align 8
  %26 = load %struct.CondIncl*, %struct.CondIncl** %5, align 8
  store %struct.CondIncl* %26, %struct.CondIncl** @cond_incl, align 8
  %27 = load %struct.CondIncl*, %struct.CondIncl** %5, align 8
  ret %struct.CondIncl* %27
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @skip_cond_incl(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  br label %3

3:                                                ; preds = %52, %26, %1
  %4 = load %struct.Token*, %struct.Token** %2, align 8
  %5 = getelementptr inbounds %struct.Token, %struct.Token* %4, i32 0, i32 0
  %6 = load i32, i32* %5, align 16
  %7 = icmp ne i32 %6, 6
  br i1 %7, label %8, label %56

8:                                                ; preds = %3
  %9 = load %struct.Token*, %struct.Token** %2, align 8
  %10 = call zeroext i1 @is_hash(%struct.Token* noundef %9)
  br i1 %10, label %11, label %33

11:                                               ; preds = %8
  %12 = load %struct.Token*, %struct.Token** %2, align 8
  %13 = getelementptr inbounds %struct.Token, %struct.Token* %12, i32 0, i32 1
  %14 = load %struct.Token*, %struct.Token** %13, align 8
  %15 = call zeroext i1 @equal(%struct.Token* noundef %14, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.77, i64 0, i64 0))
  br i1 %15, label %26, label %16

16:                                               ; preds = %11
  %17 = load %struct.Token*, %struct.Token** %2, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 1
  %19 = load %struct.Token*, %struct.Token** %18, align 8
  %20 = call zeroext i1 @equal(%struct.Token* noundef %19, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.78, i64 0, i64 0))
  br i1 %20, label %26, label %21

21:                                               ; preds = %16
  %22 = load %struct.Token*, %struct.Token** %2, align 8
  %23 = getelementptr inbounds %struct.Token, %struct.Token* %22, i32 0, i32 1
  %24 = load %struct.Token*, %struct.Token** %23, align 8
  %25 = call zeroext i1 @equal(%struct.Token* noundef %24, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.79, i64 0, i64 0))
  br i1 %25, label %26, label %33

26:                                               ; preds = %21, %16, %11
  %27 = load %struct.Token*, %struct.Token** %2, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 1
  %29 = load %struct.Token*, %struct.Token** %28, align 8
  %30 = getelementptr inbounds %struct.Token, %struct.Token* %29, i32 0, i32 1
  %31 = load %struct.Token*, %struct.Token** %30, align 8
  %32 = call %struct.Token* @skip_cond_incl2(%struct.Token* noundef %31)
  store %struct.Token* %32, %struct.Token** %2, align 8
  br label %3, !llvm.loop !30

33:                                               ; preds = %21, %8
  %34 = load %struct.Token*, %struct.Token** %2, align 8
  %35 = call zeroext i1 @is_hash(%struct.Token* noundef %34)
  br i1 %35, label %36, label %52

36:                                               ; preds = %33
  %37 = load %struct.Token*, %struct.Token** %2, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 1
  %39 = load %struct.Token*, %struct.Token** %38, align 8
  %40 = call zeroext i1 @equal(%struct.Token* noundef %39, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.80, i64 0, i64 0))
  br i1 %40, label %51, label %41

41:                                               ; preds = %36
  %42 = load %struct.Token*, %struct.Token** %2, align 8
  %43 = getelementptr inbounds %struct.Token, %struct.Token* %42, i32 0, i32 1
  %44 = load %struct.Token*, %struct.Token** %43, align 8
  %45 = call zeroext i1 @equal(%struct.Token* noundef %44, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i64 0, i64 0))
  br i1 %45, label %51, label %46

46:                                               ; preds = %41
  %47 = load %struct.Token*, %struct.Token** %2, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 1
  %49 = load %struct.Token*, %struct.Token** %48, align 8
  %50 = call zeroext i1 @equal(%struct.Token* noundef %49, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.84, i64 0, i64 0))
  br i1 %50, label %51, label %52

51:                                               ; preds = %46, %41, %36
  br label %56

52:                                               ; preds = %46, %33
  %53 = load %struct.Token*, %struct.Token** %2, align 8
  %54 = getelementptr inbounds %struct.Token, %struct.Token* %53, i32 0, i32 1
  %55 = load %struct.Token*, %struct.Token** %54, align 8
  store %struct.Token* %55, %struct.Token** %2, align 8
  br label %3, !llvm.loop !30

56:                                               ; preds = %51, %3
  %57 = load %struct.Token*, %struct.Token** %2, align 8
  ret %struct.Token* %57
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @read_line_marker(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca i8, align 1
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %7, %struct.Token** %5, align 8
  store i8 1, i8* %6, align 1
  %8 = load %struct.Token**, %struct.Token*** %3, align 8
  %9 = load %struct.Token*, %struct.Token** %4, align 8
  %10 = call %struct.Token* @copy_line(%struct.Token** noundef %8, %struct.Token* noundef %9)
  %11 = load i8, i8* %6, align 1
  %12 = trunc i8 %11 to i1
  %13 = call %struct.Token* @preprocess(%struct.Token* noundef %10, i1 noundef zeroext %12)
  store %struct.Token* %13, %struct.Token** %4, align 8
  %14 = load %struct.Token*, %struct.Token** %4, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 16
  %17 = icmp ne i32 %16, 4
  br i1 %17, label %18, label %27

18:                                               ; preds = %2
  %19 = load %struct.Token*, %struct.Token** %4, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 6
  %21 = load %struct.Type*, %struct.Type** %20, align 16
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 0
  %23 = load i32, i32* %22, align 8
  %24 = icmp ne i32 %23, 4
  br i1 %24, label %25, label %27

25:                                               ; preds = %18
  %26 = load %struct.Token*, %struct.Token** %4, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %26, i8* noundef getelementptr inbounds ([46 x i8], [46 x i8]* @.str.116, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

27:                                               ; preds = %18, %2
  %28 = load %struct.Token*, %struct.Token** %4, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 2
  %30 = load i64, i64* %29, align 16
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = getelementptr inbounds %struct.Token, %struct.Token* %31, i32 0, i32 10
  %33 = load i32, i32* %32, align 16
  %34 = sext i32 %33 to i64
  %35 = sub nsw i64 %30, %34
  %36 = trunc i64 %35 to i32
  %37 = load %struct.Token*, %struct.Token** %5, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 8
  %39 = load %struct.File*, %struct.File** %38, align 16
  %40 = getelementptr inbounds %struct.File, %struct.File* %39, i32 0, i32 4
  store i32 %36, i32* %40, align 8
  %41 = load %struct.Token*, %struct.Token** %4, align 8
  %42 = getelementptr inbounds %struct.Token, %struct.Token* %41, i32 0, i32 1
  %43 = load %struct.Token*, %struct.Token** %42, align 8
  store %struct.Token* %43, %struct.Token** %4, align 8
  %44 = load %struct.Token*, %struct.Token** %4, align 8
  %45 = getelementptr inbounds %struct.Token, %struct.Token* %44, i32 0, i32 0
  %46 = load i32, i32* %45, align 16
  %47 = icmp eq i32 %46, 6
  br i1 %47, label %48, label %49

48:                                               ; preds = %27
  br label %64

49:                                               ; preds = %27
  %50 = load %struct.Token*, %struct.Token** %4, align 8
  %51 = getelementptr inbounds %struct.Token, %struct.Token* %50, i32 0, i32 0
  %52 = load i32, i32* %51, align 16
  %53 = icmp ne i32 %52, 3
  br i1 %53, label %54, label %56

54:                                               ; preds = %49
  %55 = load %struct.Token*, %struct.Token** %4, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %55, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.117, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

56:                                               ; preds = %49
  %57 = load %struct.Token*, %struct.Token** %4, align 8
  %58 = getelementptr inbounds %struct.Token, %struct.Token* %57, i32 0, i32 7
  %59 = load i8*, i8** %58, align 8
  %60 = load %struct.Token*, %struct.Token** %5, align 8
  %61 = getelementptr inbounds %struct.Token, %struct.Token* %60, i32 0, i32 8
  %62 = load %struct.File*, %struct.File** %61, align 16
  %63 = getelementptr inbounds %struct.File, %struct.File* %62, i32 0, i32 3
  store i8* %59, i8** %63, align 8
  br label %64

64:                                               ; preds = %56, %48
  ret void
}

declare i32 @printf(i8* noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @join_tokens(%struct.Token* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca i32, align 4
  %6 = alloca %struct.Token*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i32, align 4
  %9 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  store i32 1, i32* %5, align 4
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  store %struct.Token* %10, %struct.Token** %6, align 8
  br label %11

11:                                               ; preds = %40, %2
  %12 = load %struct.Token*, %struct.Token** %6, align 8
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  %14 = icmp ne %struct.Token* %12, %13
  br i1 %14, label %15, label %20

15:                                               ; preds = %11
  %16 = load %struct.Token*, %struct.Token** %6, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 0
  %18 = load i32, i32* %17, align 16
  %19 = icmp ne i32 %18, 6
  br label %20

20:                                               ; preds = %15, %11
  %21 = phi i1 [ false, %11 ], [ %19, %15 ]
  br i1 %21, label %22, label %44

22:                                               ; preds = %20
  %23 = load %struct.Token*, %struct.Token** %6, align 8
  %24 = load %struct.Token*, %struct.Token** %3, align 8
  %25 = icmp ne %struct.Token* %23, %24
  br i1 %25, label %26, label %34

26:                                               ; preds = %22
  %27 = load %struct.Token*, %struct.Token** %6, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 13
  %29 = load i8, i8* %28, align 1
  %30 = trunc i8 %29 to i1
  br i1 %30, label %31, label %34

31:                                               ; preds = %26
  %32 = load i32, i32* %5, align 4
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %5, align 4
  br label %34

34:                                               ; preds = %31, %26, %22
  %35 = load %struct.Token*, %struct.Token** %6, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 5
  %37 = load i32, i32* %36, align 8
  %38 = load i32, i32* %5, align 4
  %39 = add nsw i32 %38, %37
  store i32 %39, i32* %5, align 4
  br label %40

40:                                               ; preds = %34
  %41 = load %struct.Token*, %struct.Token** %6, align 8
  %42 = getelementptr inbounds %struct.Token, %struct.Token* %41, i32 0, i32 1
  %43 = load %struct.Token*, %struct.Token** %42, align 8
  store %struct.Token* %43, %struct.Token** %6, align 8
  br label %11, !llvm.loop !31

44:                                               ; preds = %20
  %45 = load i32, i32* %5, align 4
  %46 = sext i32 %45 to i64
  %47 = call noalias i8* @calloc(i64 noundef 1, i64 noundef %46) #9
  store i8* %47, i8** %7, align 8
  %48 = load i8*, i8** %7, align 8
  %49 = icmp eq i8* %48, null
  br i1 %49, label %50, label %51

50:                                               ; preds = %44
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([33 x i8], [33 x i8]* @.str.99, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

51:                                               ; preds = %44
  store i32 0, i32* %8, align 4
  %52 = load %struct.Token*, %struct.Token** %3, align 8
  store %struct.Token* %52, %struct.Token** %9, align 8
  br label %53

53:                                               ; preds = %97, %51
  %54 = load %struct.Token*, %struct.Token** %9, align 8
  %55 = load %struct.Token*, %struct.Token** %4, align 8
  %56 = icmp ne %struct.Token* %54, %55
  br i1 %56, label %57, label %62

57:                                               ; preds = %53
  %58 = load %struct.Token*, %struct.Token** %9, align 8
  %59 = getelementptr inbounds %struct.Token, %struct.Token* %58, i32 0, i32 0
  %60 = load i32, i32* %59, align 16
  %61 = icmp ne i32 %60, 6
  br label %62

62:                                               ; preds = %57, %53
  %63 = phi i1 [ false, %53 ], [ %61, %57 ]
  br i1 %63, label %64, label %101

64:                                               ; preds = %62
  %65 = load %struct.Token*, %struct.Token** %9, align 8
  %66 = load %struct.Token*, %struct.Token** %3, align 8
  %67 = icmp ne %struct.Token* %65, %66
  br i1 %67, label %68, label %79

68:                                               ; preds = %64
  %69 = load %struct.Token*, %struct.Token** %9, align 8
  %70 = getelementptr inbounds %struct.Token, %struct.Token* %69, i32 0, i32 13
  %71 = load i8, i8* %70, align 1
  %72 = trunc i8 %71 to i1
  br i1 %72, label %73, label %79

73:                                               ; preds = %68
  %74 = load i8*, i8** %7, align 8
  %75 = load i32, i32* %8, align 4
  %76 = add nsw i32 %75, 1
  store i32 %76, i32* %8, align 4
  %77 = sext i32 %75 to i64
  %78 = getelementptr inbounds i8, i8* %74, i64 %77
  store i8 32, i8* %78, align 1
  br label %79

79:                                               ; preds = %73, %68, %64
  %80 = load i8*, i8** %7, align 8
  %81 = load i32, i32* %8, align 4
  %82 = sext i32 %81 to i64
  %83 = getelementptr inbounds i8, i8* %80, i64 %82
  %84 = load %struct.Token*, %struct.Token** %9, align 8
  %85 = getelementptr inbounds %struct.Token, %struct.Token* %84, i32 0, i32 4
  %86 = load i8*, i8** %85, align 16
  %87 = load %struct.Token*, %struct.Token** %9, align 8
  %88 = getelementptr inbounds %struct.Token, %struct.Token* %87, i32 0, i32 5
  %89 = load i32, i32* %88, align 8
  %90 = sext i32 %89 to i64
  %91 = call i8* @strncpy(i8* noundef %83, i8* noundef %86, i64 noundef %90) #9
  %92 = load %struct.Token*, %struct.Token** %9, align 8
  %93 = getelementptr inbounds %struct.Token, %struct.Token* %92, i32 0, i32 5
  %94 = load i32, i32* %93, align 8
  %95 = load i32, i32* %8, align 4
  %96 = add nsw i32 %95, %94
  store i32 %96, i32* %8, align 4
  br label %97

97:                                               ; preds = %79
  %98 = load %struct.Token*, %struct.Token** %9, align 8
  %99 = getelementptr inbounds %struct.Token, %struct.Token* %98, i32 0, i32 1
  %100 = load %struct.Token*, %struct.Token** %99, align 8
  store %struct.Token* %100, %struct.Token** %9, align 8
  br label %53, !llvm.loop !32

101:                                              ; preds = %62
  %102 = load i8*, i8** %7, align 8
  %103 = load i32, i32* %8, align 4
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds i8, i8* %102, i64 %104
  store i8 0, i8* %105, align 1
  %106 = load i8*, i8** %7, align 8
  ret i8* %106
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @copy_line(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token, align 16
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = bitcast %struct.Token* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %7, i8 0, i64 128, i1 false)
  store %struct.Token* %5, %struct.Token** %6, align 8
  br label %8

8:                                                ; preds = %19, %2
  %9 = load %struct.Token*, %struct.Token** %4, align 8
  %10 = getelementptr inbounds %struct.Token, %struct.Token* %9, i32 0, i32 12
  %11 = load i8, i8* %10, align 8
  %12 = trunc i8 %11 to i1
  %13 = xor i1 %12, true
  br i1 %13, label %14, label %23

14:                                               ; preds = %8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = call %struct.Token* @copy_token(%struct.Token* noundef %15)
  %17 = load %struct.Token*, %struct.Token** %6, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 1
  store %struct.Token* %16, %struct.Token** %18, align 8
  store %struct.Token* %16, %struct.Token** %6, align 8
  br label %19

19:                                               ; preds = %14
  %20 = load %struct.Token*, %struct.Token** %4, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 1
  %22 = load %struct.Token*, %struct.Token** %21, align 8
  store %struct.Token* %22, %struct.Token** %4, align 8
  br label %8, !llvm.loop !33

23:                                               ; preds = %8
  %24 = load %struct.Token*, %struct.Token** %4, align 8
  %25 = call %struct.Token* @new_eof(%struct.Token* noundef %24)
  %26 = load %struct.Token*, %struct.Token** %6, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  store %struct.Token* %25, %struct.Token** %27, align 8
  %28 = load %struct.Token*, %struct.Token** %4, align 8
  %29 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %28, %struct.Token** %29, align 8
  %30 = getelementptr inbounds %struct.Token, %struct.Token* %5, i32 0, i32 1
  %31 = load %struct.Token*, %struct.Token** %30, align 8
  ret %struct.Token* %31
}

; Function Attrs: nounwind
declare i8* @strncpy(i8* noundef, i8* noundef, i64 noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @copy_token(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %4 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 128) #9
  %5 = bitcast i8* %4 to %struct.Token*
  store %struct.Token* %5, %struct.Token** %3, align 8
  %6 = load %struct.Token*, %struct.Token** %3, align 8
  %7 = icmp eq %struct.Token* %6, null
  br i1 %7, label %8, label %9

8:                                                ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([30 x i8], [30 x i8]* @.str.100, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

9:                                                ; preds = %1
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = load %struct.Token*, %struct.Token** %2, align 8
  %12 = bitcast %struct.Token* %10 to i8*
  %13 = bitcast %struct.Token* %11 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %12, i8* align 16 %13, i64 128, i1 false)
  %14 = load %struct.Token*, %struct.Token** %3, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 1
  store %struct.Token* null, %struct.Token** %15, align 8
  %16 = load %struct.Token*, %struct.Token** %3, align 8
  ret %struct.Token* %16
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @new_eof(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %4 = load %struct.Token*, %struct.Token** %2, align 8
  %5 = call %struct.Token* @copy_token(%struct.Token* noundef %4)
  store %struct.Token* %5, %struct.Token** %3, align 8
  %6 = load %struct.Token*, %struct.Token** %3, align 8
  %7 = getelementptr inbounds %struct.Token, %struct.Token* %6, i32 0, i32 0
  store i32 6, i32* %7, align 16
  %8 = load %struct.Token*, %struct.Token** %3, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 5
  store i32 0, i32* %9, align 8
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  ret %struct.Token* %10
}

; Function Attrs: argmemonly nofree nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #7

declare %struct.Token* @tokenize_file(i8* noundef) #1

; Function Attrs: nounwind
declare i8* @strerror(i32 noundef) #3

; Function Attrs: nounwind readnone willreturn
declare i32* @__errno_location() #5

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @detect_include_guard(%struct.Token* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.Token*, align 8
  %4 = alloca i8*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %5 = load %struct.Token*, %struct.Token** %3, align 8
  %6 = call zeroext i1 @is_hash(%struct.Token* noundef %5)
  br i1 %6, label %7, label %12

7:                                                ; preds = %1
  %8 = load %struct.Token*, %struct.Token** %3, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 1
  %10 = load %struct.Token*, %struct.Token** %9, align 8
  %11 = call zeroext i1 @equal(%struct.Token* noundef %10, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.79, i64 0, i64 0))
  br i1 %11, label %13, label %12

12:                                               ; preds = %7, %1
  store i8* null, i8** %2, align 8
  br label %101

13:                                               ; preds = %7
  %14 = load %struct.Token*, %struct.Token** %3, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 1
  %16 = load %struct.Token*, %struct.Token** %15, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 1
  %18 = load %struct.Token*, %struct.Token** %17, align 8
  store %struct.Token* %18, %struct.Token** %3, align 8
  %19 = load %struct.Token*, %struct.Token** %3, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 0
  %21 = load i32, i32* %20, align 16
  %22 = icmp ne i32 %21, 0
  br i1 %22, label %23, label %24

23:                                               ; preds = %13
  store i8* null, i8** %2, align 8
  br label %101

24:                                               ; preds = %13
  %25 = load %struct.Token*, %struct.Token** %3, align 8
  %26 = getelementptr inbounds %struct.Token, %struct.Token* %25, i32 0, i32 4
  %27 = load i8*, i8** %26, align 16
  %28 = load %struct.Token*, %struct.Token** %3, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 5
  %30 = load i32, i32* %29, align 8
  %31 = sext i32 %30 to i64
  %32 = call noalias i8* @strndup(i8* noundef %27, i64 noundef %31) #9
  store i8* %32, i8** %4, align 8
  %33 = load %struct.Token*, %struct.Token** %3, align 8
  %34 = getelementptr inbounds %struct.Token, %struct.Token* %33, i32 0, i32 1
  %35 = load %struct.Token*, %struct.Token** %34, align 8
  store %struct.Token* %35, %struct.Token** %3, align 8
  %36 = load %struct.Token*, %struct.Token** %3, align 8
  %37 = call zeroext i1 @is_hash(%struct.Token* noundef %36)
  br i1 %37, label %38, label %51

38:                                               ; preds = %24
  %39 = load %struct.Token*, %struct.Token** %3, align 8
  %40 = getelementptr inbounds %struct.Token, %struct.Token* %39, i32 0, i32 1
  %41 = load %struct.Token*, %struct.Token** %40, align 8
  %42 = call zeroext i1 @equal(%struct.Token* noundef %41, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.74, i64 0, i64 0))
  br i1 %42, label %43, label %51

43:                                               ; preds = %38
  %44 = load %struct.Token*, %struct.Token** %3, align 8
  %45 = getelementptr inbounds %struct.Token, %struct.Token* %44, i32 0, i32 1
  %46 = load %struct.Token*, %struct.Token** %45, align 8
  %47 = getelementptr inbounds %struct.Token, %struct.Token* %46, i32 0, i32 1
  %48 = load %struct.Token*, %struct.Token** %47, align 8
  %49 = load i8*, i8** %4, align 8
  %50 = call zeroext i1 @equal(%struct.Token* noundef %48, i8* noundef %49)
  br i1 %50, label %52, label %51

51:                                               ; preds = %43, %38, %24
  store i8* null, i8** %2, align 8
  br label %101

52:                                               ; preds = %43
  br label %53

53:                                               ; preds = %99, %61, %52
  %54 = load %struct.Token*, %struct.Token** %3, align 8
  %55 = getelementptr inbounds %struct.Token, %struct.Token* %54, i32 0, i32 0
  %56 = load i32, i32* %55, align 16
  %57 = icmp ne i32 %56, 6
  br i1 %57, label %58, label %100

58:                                               ; preds = %53
  %59 = load %struct.Token*, %struct.Token** %3, align 8
  %60 = call zeroext i1 @is_hash(%struct.Token* noundef %59)
  br i1 %60, label %65, label %61

61:                                               ; preds = %58
  %62 = load %struct.Token*, %struct.Token** %3, align 8
  %63 = getelementptr inbounds %struct.Token, %struct.Token* %62, i32 0, i32 1
  %64 = load %struct.Token*, %struct.Token** %63, align 8
  store %struct.Token* %64, %struct.Token** %3, align 8
  br label %53, !llvm.loop !34

65:                                               ; preds = %58
  %66 = load %struct.Token*, %struct.Token** %3, align 8
  %67 = getelementptr inbounds %struct.Token, %struct.Token* %66, i32 0, i32 1
  %68 = load %struct.Token*, %struct.Token** %67, align 8
  %69 = call zeroext i1 @equal(%struct.Token* noundef %68, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.84, i64 0, i64 0))
  br i1 %69, label %70, label %81

70:                                               ; preds = %65
  %71 = load %struct.Token*, %struct.Token** %3, align 8
  %72 = getelementptr inbounds %struct.Token, %struct.Token* %71, i32 0, i32 1
  %73 = load %struct.Token*, %struct.Token** %72, align 8
  %74 = getelementptr inbounds %struct.Token, %struct.Token* %73, i32 0, i32 1
  %75 = load %struct.Token*, %struct.Token** %74, align 8
  %76 = getelementptr inbounds %struct.Token, %struct.Token* %75, i32 0, i32 0
  %77 = load i32, i32* %76, align 16
  %78 = icmp eq i32 %77, 6
  br i1 %78, label %79, label %81

79:                                               ; preds = %70
  %80 = load i8*, i8** %4, align 8
  store i8* %80, i8** %2, align 8
  br label %101

81:                                               ; preds = %70, %65
  %82 = load %struct.Token*, %struct.Token** %3, align 8
  %83 = call zeroext i1 @equal(%struct.Token* noundef %82, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.77, i64 0, i64 0))
  br i1 %83, label %90, label %84

84:                                               ; preds = %81
  %85 = load %struct.Token*, %struct.Token** %3, align 8
  %86 = call zeroext i1 @equal(%struct.Token* noundef %85, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.78, i64 0, i64 0))
  br i1 %86, label %90, label %87

87:                                               ; preds = %84
  %88 = load %struct.Token*, %struct.Token** %3, align 8
  %89 = call zeroext i1 @equal(%struct.Token* noundef %88, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.79, i64 0, i64 0))
  br i1 %89, label %90, label %95

90:                                               ; preds = %87, %84, %81
  %91 = load %struct.Token*, %struct.Token** %3, align 8
  %92 = getelementptr inbounds %struct.Token, %struct.Token* %91, i32 0, i32 1
  %93 = load %struct.Token*, %struct.Token** %92, align 8
  %94 = call %struct.Token* @skip_cond_incl(%struct.Token* noundef %93)
  store %struct.Token* %94, %struct.Token** %3, align 8
  br label %99

95:                                               ; preds = %87
  %96 = load %struct.Token*, %struct.Token** %3, align 8
  %97 = getelementptr inbounds %struct.Token, %struct.Token* %96, i32 0, i32 1
  %98 = load %struct.Token*, %struct.Token** %97, align 8
  store %struct.Token* %98, %struct.Token** %3, align 8
  br label %99

99:                                               ; preds = %95, %90
  br label %53, !llvm.loop !34

100:                                              ; preds = %53
  store i8* null, i8** %2, align 8
  br label %101

101:                                              ; preds = %100, %79, %51, %23, %12
  %102 = load i8*, i8** %2, align 8
  ret i8* %102
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @append(%struct.Token* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Token, align 16
  %7 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %8 = load %struct.Token*, %struct.Token** %4, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 0
  %10 = load i32, i32* %9, align 16
  %11 = icmp eq i32 %10, 6
  br i1 %11, label %12, label %14

12:                                               ; preds = %2
  %13 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %13, %struct.Token** %3, align 8
  br label %36

14:                                               ; preds = %2
  %15 = bitcast %struct.Token* %6 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %15, i8 0, i64 128, i1 false)
  store %struct.Token* %6, %struct.Token** %7, align 8
  br label %16

16:                                               ; preds = %26, %14
  %17 = load %struct.Token*, %struct.Token** %4, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 0
  %19 = load i32, i32* %18, align 16
  %20 = icmp ne i32 %19, 6
  br i1 %20, label %21, label %30

21:                                               ; preds = %16
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = call %struct.Token* @copy_token(%struct.Token* noundef %22)
  %24 = load %struct.Token*, %struct.Token** %7, align 8
  %25 = getelementptr inbounds %struct.Token, %struct.Token* %24, i32 0, i32 1
  store %struct.Token* %23, %struct.Token** %25, align 8
  store %struct.Token* %23, %struct.Token** %7, align 8
  br label %26

26:                                               ; preds = %21
  %27 = load %struct.Token*, %struct.Token** %4, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 1
  %29 = load %struct.Token*, %struct.Token** %28, align 8
  store %struct.Token* %29, %struct.Token** %4, align 8
  br label %16, !llvm.loop !35

30:                                               ; preds = %16
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = load %struct.Token*, %struct.Token** %7, align 8
  %33 = getelementptr inbounds %struct.Token, %struct.Token* %32, i32 0, i32 1
  store %struct.Token* %31, %struct.Token** %33, align 8
  %34 = getelementptr inbounds %struct.Token, %struct.Token* %6, i32 0, i32 1
  %35 = load %struct.Token*, %struct.Token** %34, align 8
  store %struct.Token* %35, %struct.Token** %3, align 8
  br label %36

36:                                               ; preds = %30, %12
  %37 = load %struct.Token*, %struct.Token** %3, align 8
  ret %struct.Token* %37
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.MacroParam* @read_macro_params(%struct.Token** noundef %0, %struct.Token* noundef %1, i8** noundef %2) #0 {
  %4 = alloca %struct.MacroParam*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca i8**, align 8
  %8 = alloca %struct.MacroParam, align 8
  %9 = alloca %struct.MacroParam*, align 8
  %10 = alloca %struct.MacroParam*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store i8** %2, i8*** %7, align 8
  %11 = bitcast %struct.MacroParam* %8 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %11, i8 0, i64 16, i1 false)
  store %struct.MacroParam* %8, %struct.MacroParam** %9, align 8
  br label %12

12:                                               ; preds = %71, %3
  %13 = load %struct.Token*, %struct.Token** %6, align 8
  %14 = call zeroext i1 @equal(%struct.Token* noundef %13, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  %15 = xor i1 %14, true
  br i1 %15, label %16, label %88

16:                                               ; preds = %12
  %17 = load %struct.MacroParam*, %struct.MacroParam** %9, align 8
  %18 = icmp ne %struct.MacroParam* %17, %8
  br i1 %18, label %19, label %22

19:                                               ; preds = %16
  %20 = load %struct.Token*, %struct.Token** %6, align 8
  %21 = call %struct.Token* @skip(%struct.Token* noundef %20, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.105, i64 0, i64 0))
  store %struct.Token* %21, %struct.Token** %6, align 8
  br label %22

22:                                               ; preds = %19, %16
  %23 = load %struct.Token*, %struct.Token** %6, align 8
  %24 = call zeroext i1 @equal(%struct.Token* noundef %23, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.106, i64 0, i64 0))
  br i1 %24, label %25, label %34

25:                                               ; preds = %22
  %26 = load i8**, i8*** %7, align 8
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.107, i64 0, i64 0), i8** %26, align 8
  %27 = load %struct.Token*, %struct.Token** %6, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 1
  %29 = load %struct.Token*, %struct.Token** %28, align 8
  %30 = call %struct.Token* @skip(%struct.Token* noundef %29, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  %31 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %30, %struct.Token** %31, align 8
  %32 = getelementptr inbounds %struct.MacroParam, %struct.MacroParam* %8, i32 0, i32 0
  %33 = load %struct.MacroParam*, %struct.MacroParam** %32, align 8
  store %struct.MacroParam* %33, %struct.MacroParam** %4, align 8
  br label %95

34:                                               ; preds = %22
  %35 = load %struct.Token*, %struct.Token** %6, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 0
  %37 = load i32, i32* %36, align 16
  %38 = icmp ne i32 %37, 0
  br i1 %38, label %39, label %41

39:                                               ; preds = %34
  %40 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %40, i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.108, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

41:                                               ; preds = %34
  %42 = load %struct.Token*, %struct.Token** %6, align 8
  %43 = getelementptr inbounds %struct.Token, %struct.Token* %42, i32 0, i32 1
  %44 = load %struct.Token*, %struct.Token** %43, align 8
  %45 = call zeroext i1 @equal(%struct.Token* noundef %44, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.106, i64 0, i64 0))
  br i1 %45, label %46, label %65

46:                                               ; preds = %41
  %47 = load %struct.Token*, %struct.Token** %6, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 4
  %49 = load i8*, i8** %48, align 16
  %50 = load %struct.Token*, %struct.Token** %6, align 8
  %51 = getelementptr inbounds %struct.Token, %struct.Token* %50, i32 0, i32 5
  %52 = load i32, i32* %51, align 8
  %53 = sext i32 %52 to i64
  %54 = call noalias i8* @strndup(i8* noundef %49, i64 noundef %53) #9
  %55 = load i8**, i8*** %7, align 8
  store i8* %54, i8** %55, align 8
  %56 = load %struct.Token*, %struct.Token** %6, align 8
  %57 = getelementptr inbounds %struct.Token, %struct.Token* %56, i32 0, i32 1
  %58 = load %struct.Token*, %struct.Token** %57, align 8
  %59 = getelementptr inbounds %struct.Token, %struct.Token* %58, i32 0, i32 1
  %60 = load %struct.Token*, %struct.Token** %59, align 8
  %61 = call %struct.Token* @skip(%struct.Token* noundef %60, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  %62 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %61, %struct.Token** %62, align 8
  %63 = getelementptr inbounds %struct.MacroParam, %struct.MacroParam* %8, i32 0, i32 0
  %64 = load %struct.MacroParam*, %struct.MacroParam** %63, align 8
  store %struct.MacroParam* %64, %struct.MacroParam** %4, align 8
  br label %95

65:                                               ; preds = %41
  %66 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 16) #9
  %67 = bitcast i8* %66 to %struct.MacroParam*
  store %struct.MacroParam* %67, %struct.MacroParam** %10, align 8
  %68 = load %struct.MacroParam*, %struct.MacroParam** %10, align 8
  %69 = icmp eq %struct.MacroParam* %68, null
  br i1 %69, label %70, label %71

70:                                               ; preds = %65
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([37 x i8], [37 x i8]* @.str.109, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

71:                                               ; preds = %65
  %72 = load %struct.Token*, %struct.Token** %6, align 8
  %73 = getelementptr inbounds %struct.Token, %struct.Token* %72, i32 0, i32 4
  %74 = load i8*, i8** %73, align 16
  %75 = load %struct.Token*, %struct.Token** %6, align 8
  %76 = getelementptr inbounds %struct.Token, %struct.Token* %75, i32 0, i32 5
  %77 = load i32, i32* %76, align 8
  %78 = sext i32 %77 to i64
  %79 = call noalias i8* @strndup(i8* noundef %74, i64 noundef %78) #9
  %80 = load %struct.MacroParam*, %struct.MacroParam** %10, align 8
  %81 = getelementptr inbounds %struct.MacroParam, %struct.MacroParam* %80, i32 0, i32 1
  store i8* %79, i8** %81, align 8
  %82 = load %struct.MacroParam*, %struct.MacroParam** %10, align 8
  %83 = load %struct.MacroParam*, %struct.MacroParam** %9, align 8
  %84 = getelementptr inbounds %struct.MacroParam, %struct.MacroParam* %83, i32 0, i32 0
  store %struct.MacroParam* %82, %struct.MacroParam** %84, align 8
  store %struct.MacroParam* %82, %struct.MacroParam** %9, align 8
  %85 = load %struct.Token*, %struct.Token** %6, align 8
  %86 = getelementptr inbounds %struct.Token, %struct.Token* %85, i32 0, i32 1
  %87 = load %struct.Token*, %struct.Token** %86, align 8
  store %struct.Token* %87, %struct.Token** %6, align 8
  br label %12, !llvm.loop !36

88:                                               ; preds = %12
  %89 = load %struct.Token*, %struct.Token** %6, align 8
  %90 = getelementptr inbounds %struct.Token, %struct.Token* %89, i32 0, i32 1
  %91 = load %struct.Token*, %struct.Token** %90, align 8
  %92 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %91, %struct.Token** %92, align 8
  %93 = getelementptr inbounds %struct.MacroParam, %struct.MacroParam* %8, i32 0, i32 0
  %94 = load %struct.MacroParam*, %struct.MacroParam** %93, align 8
  store %struct.MacroParam* %94, %struct.MacroParam** %4, align 8
  br label %95

95:                                               ; preds = %88, %46, %25
  %96 = load %struct.MacroParam*, %struct.MacroParam** %4, align 8
  ret %struct.MacroParam* %96
}

declare %struct.Token* @skip(%struct.Token* noundef, i8* noundef) #1

declare void @warn_tok(%struct.Token* noundef, i8* noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @read_const_expr(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token, align 16
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca i8, align 1
  %9 = alloca %struct.Macro*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %10 = load %struct.Token**, %struct.Token*** %3, align 8
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  %12 = call %struct.Token* @copy_line(%struct.Token** noundef %10, %struct.Token* noundef %11)
  store %struct.Token* %12, %struct.Token** %4, align 8
  %13 = bitcast %struct.Token* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %13, i8 0, i64 128, i1 false)
  store %struct.Token* %5, %struct.Token** %6, align 8
  br label %14

14:                                               ; preds = %58, %49, %2
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 0
  %17 = load i32, i32* %16, align 16
  %18 = icmp ne i32 %17, 6
  br i1 %18, label %19, label %65

19:                                               ; preds = %14
  %20 = load %struct.Token*, %struct.Token** %4, align 8
  %21 = call zeroext i1 @equal(%struct.Token* noundef %20, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.113, i64 0, i64 0))
  br i1 %21, label %25, label %22

22:                                               ; preds = %19
  %23 = load %struct.Token*, %struct.Token** %4, align 8
  %24 = call zeroext i1 @equal(%struct.Token* noundef %23, i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.1, i64 0, i64 0))
  br i1 %24, label %25, label %58

25:                                               ; preds = %22, %19
  %26 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %26, %struct.Token** %7, align 8
  %27 = load %struct.Token*, %struct.Token** %4, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 1
  %29 = load %struct.Token*, %struct.Token** %28, align 8
  %30 = call zeroext i1 @consume(%struct.Token** noundef %4, %struct.Token* noundef %29, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.103, i64 0, i64 0))
  %31 = zext i1 %30 to i8
  store i8 %31, i8* %8, align 1
  %32 = load %struct.Token*, %struct.Token** %4, align 8
  %33 = getelementptr inbounds %struct.Token, %struct.Token* %32, i32 0, i32 0
  %34 = load i32, i32* %33, align 16
  %35 = icmp ne i32 %34, 0
  br i1 %35, label %36, label %38

36:                                               ; preds = %25
  %37 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %37, i8* noundef getelementptr inbounds ([58 x i8], [58 x i8]* @.str.114, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

38:                                               ; preds = %25
  %39 = load %struct.Token*, %struct.Token** %4, align 8
  %40 = call %struct.Macro* @find_macro(%struct.Token* noundef %39)
  store %struct.Macro* %40, %struct.Macro** %9, align 8
  %41 = load %struct.Token*, %struct.Token** %4, align 8
  %42 = getelementptr inbounds %struct.Token, %struct.Token* %41, i32 0, i32 1
  %43 = load %struct.Token*, %struct.Token** %42, align 8
  store %struct.Token* %43, %struct.Token** %4, align 8
  %44 = load i8, i8* %8, align 1
  %45 = trunc i8 %44 to i1
  br i1 %45, label %46, label %49

46:                                               ; preds = %38
  %47 = load %struct.Token*, %struct.Token** %4, align 8
  %48 = call %struct.Token* @skip(%struct.Token* noundef %47, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  store %struct.Token* %48, %struct.Token** %4, align 8
  br label %49

49:                                               ; preds = %46, %38
  %50 = load %struct.Macro*, %struct.Macro** %9, align 8
  %51 = icmp ne %struct.Macro* %50, null
  %52 = zext i1 %51 to i64
  %53 = select i1 %51, i32 1, i32 0
  %54 = load %struct.Token*, %struct.Token** %7, align 8
  %55 = call %struct.Token* @new_num_token(i32 noundef %53, %struct.Token* noundef %54)
  %56 = load %struct.Token*, %struct.Token** %6, align 8
  %57 = getelementptr inbounds %struct.Token, %struct.Token* %56, i32 0, i32 1
  store %struct.Token* %55, %struct.Token** %57, align 8
  store %struct.Token* %55, %struct.Token** %6, align 8
  br label %14, !llvm.loop !37

58:                                               ; preds = %22
  %59 = load %struct.Token*, %struct.Token** %4, align 8
  %60 = load %struct.Token*, %struct.Token** %6, align 8
  %61 = getelementptr inbounds %struct.Token, %struct.Token* %60, i32 0, i32 1
  store %struct.Token* %59, %struct.Token** %61, align 8
  store %struct.Token* %59, %struct.Token** %6, align 8
  %62 = load %struct.Token*, %struct.Token** %4, align 8
  %63 = getelementptr inbounds %struct.Token, %struct.Token* %62, i32 0, i32 1
  %64 = load %struct.Token*, %struct.Token** %63, align 8
  store %struct.Token* %64, %struct.Token** %4, align 8
  br label %14, !llvm.loop !37

65:                                               ; preds = %14
  %66 = load %struct.Token*, %struct.Token** %4, align 8
  %67 = load %struct.Token*, %struct.Token** %6, align 8
  %68 = getelementptr inbounds %struct.Token, %struct.Token* %67, i32 0, i32 1
  store %struct.Token* %66, %struct.Token** %68, align 8
  %69 = getelementptr inbounds %struct.Token, %struct.Token* %5, i32 0, i32 1
  %70 = load %struct.Token*, %struct.Token** %69, align 8
  ret %struct.Token* %70
}

declare i64 @const_expr(%struct.Token** noundef, %struct.Token* noundef) #1

declare zeroext i1 @consume(%struct.Token** noundef, %struct.Token* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @skip_cond_incl2(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  br label %4

4:                                                ; preds = %48, %27, %1
  %5 = load %struct.Token*, %struct.Token** %3, align 8
  %6 = getelementptr inbounds %struct.Token, %struct.Token* %5, i32 0, i32 0
  %7 = load i32, i32* %6, align 16
  %8 = icmp ne i32 %7, 6
  br i1 %8, label %9, label %52

9:                                                ; preds = %4
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = call zeroext i1 @is_hash(%struct.Token* noundef %10)
  br i1 %11, label %12, label %34

12:                                               ; preds = %9
  %13 = load %struct.Token*, %struct.Token** %3, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 1
  %15 = load %struct.Token*, %struct.Token** %14, align 8
  %16 = call zeroext i1 @equal(%struct.Token* noundef %15, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.77, i64 0, i64 0))
  br i1 %16, label %27, label %17

17:                                               ; preds = %12
  %18 = load %struct.Token*, %struct.Token** %3, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 1
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  %21 = call zeroext i1 @equal(%struct.Token* noundef %20, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.78, i64 0, i64 0))
  br i1 %21, label %27, label %22

22:                                               ; preds = %17
  %23 = load %struct.Token*, %struct.Token** %3, align 8
  %24 = getelementptr inbounds %struct.Token, %struct.Token* %23, i32 0, i32 1
  %25 = load %struct.Token*, %struct.Token** %24, align 8
  %26 = call zeroext i1 @equal(%struct.Token* noundef %25, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.79, i64 0, i64 0))
  br i1 %26, label %27, label %34

27:                                               ; preds = %22, %17, %12
  %28 = load %struct.Token*, %struct.Token** %3, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 1
  %30 = load %struct.Token*, %struct.Token** %29, align 8
  %31 = getelementptr inbounds %struct.Token, %struct.Token* %30, i32 0, i32 1
  %32 = load %struct.Token*, %struct.Token** %31, align 8
  %33 = call %struct.Token* @skip_cond_incl2(%struct.Token* noundef %32)
  store %struct.Token* %33, %struct.Token** %3, align 8
  br label %4, !llvm.loop !38

34:                                               ; preds = %22, %9
  %35 = load %struct.Token*, %struct.Token** %3, align 8
  %36 = call zeroext i1 @is_hash(%struct.Token* noundef %35)
  br i1 %36, label %37, label %48

37:                                               ; preds = %34
  %38 = load %struct.Token*, %struct.Token** %3, align 8
  %39 = getelementptr inbounds %struct.Token, %struct.Token* %38, i32 0, i32 1
  %40 = load %struct.Token*, %struct.Token** %39, align 8
  %41 = call zeroext i1 @equal(%struct.Token* noundef %40, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.84, i64 0, i64 0))
  br i1 %41, label %42, label %48

42:                                               ; preds = %37
  %43 = load %struct.Token*, %struct.Token** %3, align 8
  %44 = getelementptr inbounds %struct.Token, %struct.Token* %43, i32 0, i32 1
  %45 = load %struct.Token*, %struct.Token** %44, align 8
  %46 = getelementptr inbounds %struct.Token, %struct.Token* %45, i32 0, i32 1
  %47 = load %struct.Token*, %struct.Token** %46, align 8
  store %struct.Token* %47, %struct.Token** %2, align 8
  br label %54

48:                                               ; preds = %37, %34
  %49 = load %struct.Token*, %struct.Token** %3, align 8
  %50 = getelementptr inbounds %struct.Token, %struct.Token* %49, i32 0, i32 1
  %51 = load %struct.Token*, %struct.Token** %50, align 8
  store %struct.Token* %51, %struct.Token** %3, align 8
  br label %4, !llvm.loop !38

52:                                               ; preds = %4
  %53 = load %struct.Token*, %struct.Token** %3, align 8
  store %struct.Token* %53, %struct.Token** %2, align 8
  br label %54

54:                                               ; preds = %52, %42
  %55 = load %struct.Token*, %struct.Token** %2, align 8
  ret %struct.Token* %55
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @getStringKind(%struct.Token* noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %4 = load %struct.Token*, %struct.Token** %3, align 8
  %5 = getelementptr inbounds %struct.Token, %struct.Token* %4, i32 0, i32 4
  %6 = load i8*, i8** %5, align 16
  %7 = call i32 @strcmp(i8* noundef %6, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.120, i64 0, i64 0)) #8
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %10, label %9

9:                                                ; preds = %1
  store i32 1, i32* %2, align 4
  br label %22

10:                                               ; preds = %1
  %11 = load %struct.Token*, %struct.Token** %3, align 8
  %12 = getelementptr inbounds %struct.Token, %struct.Token* %11, i32 0, i32 4
  %13 = load i8*, i8** %12, align 16
  %14 = getelementptr inbounds i8, i8* %13, i64 0
  %15 = load i8, i8* %14, align 1
  %16 = sext i8 %15 to i32
  switch i32 %16, label %21 [
    i32 34, label %17
    i32 117, label %18
    i32 85, label %19
    i32 76, label %20
  ]

17:                                               ; preds = %10
  store i32 0, i32* %2, align 4
  br label %22

18:                                               ; preds = %10
  store i32 2, i32* %2, align 4
  br label %22

19:                                               ; preds = %10
  store i32 3, i32* %2, align 4
  br label %22

20:                                               ; preds = %10
  store i32 4, i32* %2, align 4
  br label %22

21:                                               ; preds = %10
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.121, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0), i32 noundef 1325) #10
  unreachable

22:                                               ; preds = %20, %19, %18, %17, %9
  %23 = load i32, i32* %2, align 4
  ret i32 %23
}

declare %struct.Token* @tokenize_string_literal(%struct.Token* noundef, %struct.Type* noundef) #1

declare %struct.Type* @array_of(%struct.Type* noundef, i32 noundef) #1

; Function Attrs: nounwind readonly willreturn
declare i32 @strcmp(i8* noundef, i8* noundef) #2

declare i8* @hashmap_get2(%struct.HashMap* noundef, i8* noundef, i32 noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @hideset_contains(%struct.Hideset* noundef %0, i8* noundef %1, i32 noundef %2) #0 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.Hideset*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  store %struct.Hideset* %0, %struct.Hideset** %5, align 8
  store i8* %1, i8** %6, align 8
  store i32 %2, i32* %7, align 4
  br label %8

8:                                                ; preds = %30, %3
  %9 = load %struct.Hideset*, %struct.Hideset** %5, align 8
  %10 = icmp ne %struct.Hideset* %9, null
  br i1 %10, label %11, label %34

11:                                               ; preds = %8
  %12 = load %struct.Hideset*, %struct.Hideset** %5, align 8
  %13 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %12, i32 0, i32 1
  %14 = load i8*, i8** %13, align 8
  %15 = call i64 @strlen(i8* noundef %14) #8
  %16 = load i32, i32* %7, align 4
  %17 = sext i32 %16 to i64
  %18 = icmp eq i64 %15, %17
  br i1 %18, label %19, label %29

19:                                               ; preds = %11
  %20 = load %struct.Hideset*, %struct.Hideset** %5, align 8
  %21 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %20, i32 0, i32 1
  %22 = load i8*, i8** %21, align 8
  %23 = load i8*, i8** %6, align 8
  %24 = load i32, i32* %7, align 4
  %25 = sext i32 %24 to i64
  %26 = call i32 @strncmp(i8* noundef %22, i8* noundef %23, i64 noundef %25) #8
  %27 = icmp ne i32 %26, 0
  br i1 %27, label %29, label %28

28:                                               ; preds = %19
  store i1 true, i1* %4, align 1
  br label %35

29:                                               ; preds = %19, %11
  br label %30

30:                                               ; preds = %29
  %31 = load %struct.Hideset*, %struct.Hideset** %5, align 8
  %32 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %31, i32 0, i32 0
  %33 = load %struct.Hideset*, %struct.Hideset** %32, align 8
  store %struct.Hideset* %33, %struct.Hideset** %5, align 8
  br label %8, !llvm.loop !39

34:                                               ; preds = %8
  store i1 false, i1* %4, align 1
  br label %35

35:                                               ; preds = %34, %28
  %36 = load i1, i1* %4, align 1
  ret i1 %36
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Hideset* @hideset_union(%struct.Hideset* noundef %0, %struct.Hideset* noundef %1) #0 {
  %3 = alloca %struct.Hideset*, align 8
  %4 = alloca %struct.Hideset*, align 8
  %5 = alloca %struct.Hideset, align 8
  %6 = alloca %struct.Hideset*, align 8
  store %struct.Hideset* %0, %struct.Hideset** %3, align 8
  store %struct.Hideset* %1, %struct.Hideset** %4, align 8
  %7 = bitcast %struct.Hideset* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %7, i8 0, i64 16, i1 false)
  store %struct.Hideset* %5, %struct.Hideset** %6, align 8
  br label %8

8:                                                ; preds = %18, %2
  %9 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %10 = icmp ne %struct.Hideset* %9, null
  br i1 %10, label %11, label %22

11:                                               ; preds = %8
  %12 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %13 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %12, i32 0, i32 1
  %14 = load i8*, i8** %13, align 8
  %15 = call %struct.Hideset* @new_hideset(i8* noundef %14)
  %16 = load %struct.Hideset*, %struct.Hideset** %6, align 8
  %17 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %16, i32 0, i32 0
  store %struct.Hideset* %15, %struct.Hideset** %17, align 8
  store %struct.Hideset* %15, %struct.Hideset** %6, align 8
  br label %18

18:                                               ; preds = %11
  %19 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %20 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %19, i32 0, i32 0
  %21 = load %struct.Hideset*, %struct.Hideset** %20, align 8
  store %struct.Hideset* %21, %struct.Hideset** %3, align 8
  br label %8, !llvm.loop !40

22:                                               ; preds = %8
  %23 = load %struct.Hideset*, %struct.Hideset** %4, align 8
  %24 = load %struct.Hideset*, %struct.Hideset** %6, align 8
  %25 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %24, i32 0, i32 0
  store %struct.Hideset* %23, %struct.Hideset** %25, align 8
  %26 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %5, i32 0, i32 0
  %27 = load %struct.Hideset*, %struct.Hideset** %26, align 8
  ret %struct.Hideset* %27
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Hideset* @new_hideset(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.Hideset*, align 8
  store i8* %0, i8** %2, align 8
  %4 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 16) #9
  %5 = bitcast i8* %4 to %struct.Hideset*
  store %struct.Hideset* %5, %struct.Hideset** %3, align 8
  %6 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %7 = icmp eq %struct.Hideset* %6, null
  br i1 %7, label %8, label %9

8:                                                ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @.str.122, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

9:                                                ; preds = %1
  %10 = load i8*, i8** %2, align 8
  %11 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %12 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %11, i32 0, i32 1
  store i8* %10, i8** %12, align 8
  %13 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  ret %struct.Hideset* %13
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @add_hideset(%struct.Token* noundef %0, %struct.Hideset* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Hideset*, align 8
  %5 = alloca %struct.Token, align 16
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Hideset* %1, %struct.Hideset** %4, align 8
  %8 = bitcast %struct.Token* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %8, i8 0, i64 128, i1 false)
  store %struct.Token* %5, %struct.Token** %6, align 8
  br label %9

9:                                                ; preds = %25, %2
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = icmp ne %struct.Token* %10, null
  br i1 %11, label %12, label %29

12:                                               ; preds = %9
  %13 = load %struct.Token*, %struct.Token** %3, align 8
  %14 = call %struct.Token* @copy_token(%struct.Token* noundef %13)
  store %struct.Token* %14, %struct.Token** %7, align 8
  %15 = load %struct.Token*, %struct.Token** %7, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 14
  %17 = load %struct.Hideset*, %struct.Hideset** %16, align 16
  %18 = load %struct.Hideset*, %struct.Hideset** %4, align 8
  %19 = call %struct.Hideset* @hideset_union(%struct.Hideset* noundef %17, %struct.Hideset* noundef %18)
  %20 = load %struct.Token*, %struct.Token** %7, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 14
  store %struct.Hideset* %19, %struct.Hideset** %21, align 16
  %22 = load %struct.Token*, %struct.Token** %7, align 8
  %23 = load %struct.Token*, %struct.Token** %6, align 8
  %24 = getelementptr inbounds %struct.Token, %struct.Token* %23, i32 0, i32 1
  store %struct.Token* %22, %struct.Token** %24, align 8
  store %struct.Token* %22, %struct.Token** %6, align 8
  br label %25

25:                                               ; preds = %12
  %26 = load %struct.Token*, %struct.Token** %3, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  store %struct.Token* %28, %struct.Token** %3, align 8
  br label %9, !llvm.loop !41

29:                                               ; preds = %9
  %30 = getelementptr inbounds %struct.Token, %struct.Token* %5, i32 0, i32 1
  %31 = load %struct.Token*, %struct.Token** %30, align 8
  ret %struct.Token* %31
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.MacroArg* @read_macro_args(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.MacroParam* noundef %2, i8* noundef %3) #0 {
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.MacroParam*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca %struct.Token*, align 8
  %10 = alloca %struct.MacroArg, align 8
  %11 = alloca %struct.MacroArg*, align 8
  %12 = alloca %struct.MacroParam*, align 8
  %13 = alloca %struct.MacroArg*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.MacroParam* %2, %struct.MacroParam** %7, align 8
  store i8* %3, i8** %8, align 8
  %14 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %14, %struct.Token** %9, align 8
  %15 = load %struct.Token*, %struct.Token** %6, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 1
  %19 = load %struct.Token*, %struct.Token** %18, align 8
  store %struct.Token* %19, %struct.Token** %6, align 8
  %20 = bitcast %struct.MacroArg* %10 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %20, i8 0, i64 32, i1 false)
  store %struct.MacroArg* %10, %struct.MacroArg** %11, align 8
  %21 = load %struct.MacroParam*, %struct.MacroParam** %7, align 8
  store %struct.MacroParam* %21, %struct.MacroParam** %12, align 8
  br label %22

22:                                               ; preds = %41, %4
  %23 = load %struct.MacroParam*, %struct.MacroParam** %12, align 8
  %24 = icmp ne %struct.MacroParam* %23, null
  br i1 %24, label %25, label %45

25:                                               ; preds = %22
  %26 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %27 = icmp ne %struct.MacroArg* %26, %10
  br i1 %27, label %28, label %31

28:                                               ; preds = %25
  %29 = load %struct.Token*, %struct.Token** %6, align 8
  %30 = call %struct.Token* @skip(%struct.Token* noundef %29, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.105, i64 0, i64 0))
  store %struct.Token* %30, %struct.Token** %6, align 8
  br label %31

31:                                               ; preds = %28, %25
  %32 = load %struct.Token*, %struct.Token** %6, align 8
  %33 = call %struct.MacroArg* @read_macro_arg_one(%struct.Token** noundef %6, %struct.Token* noundef %32, i1 noundef zeroext false)
  %34 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %35 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %34, i32 0, i32 0
  store %struct.MacroArg* %33, %struct.MacroArg** %35, align 8
  store %struct.MacroArg* %33, %struct.MacroArg** %11, align 8
  %36 = load %struct.MacroParam*, %struct.MacroParam** %12, align 8
  %37 = getelementptr inbounds %struct.MacroParam, %struct.MacroParam* %36, i32 0, i32 1
  %38 = load i8*, i8** %37, align 8
  %39 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %40 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %39, i32 0, i32 1
  store i8* %38, i8** %40, align 8
  br label %41

41:                                               ; preds = %31
  %42 = load %struct.MacroParam*, %struct.MacroParam** %12, align 8
  %43 = getelementptr inbounds %struct.MacroParam, %struct.MacroParam* %42, i32 0, i32 0
  %44 = load %struct.MacroParam*, %struct.MacroParam** %43, align 8
  store %struct.MacroParam* %44, %struct.MacroParam** %12, align 8
  br label %22, !llvm.loop !42

45:                                               ; preds = %22
  %46 = load i8*, i8** %8, align 8
  %47 = icmp ne i8* %46, null
  br i1 %47, label %48, label %81

48:                                               ; preds = %45
  %49 = load %struct.Token*, %struct.Token** %6, align 8
  %50 = call zeroext i1 @equal(%struct.Token* noundef %49, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  br i1 %50, label %51, label %62

51:                                               ; preds = %48
  %52 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 32) #9
  %53 = bitcast i8* %52 to %struct.MacroArg*
  store %struct.MacroArg* %53, %struct.MacroArg** %13, align 8
  %54 = load %struct.MacroArg*, %struct.MacroArg** %13, align 8
  %55 = icmp eq %struct.MacroArg* %54, null
  br i1 %55, label %56, label %57

56:                                               ; preds = %51
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([37 x i8], [37 x i8]* @.str.123, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

57:                                               ; preds = %51
  %58 = load %struct.Token*, %struct.Token** %6, align 8
  %59 = call %struct.Token* @new_eof(%struct.Token* noundef %58)
  %60 = load %struct.MacroArg*, %struct.MacroArg** %13, align 8
  %61 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %60, i32 0, i32 3
  store %struct.Token* %59, %struct.Token** %61, align 8
  br label %72

62:                                               ; preds = %48
  %63 = load %struct.MacroParam*, %struct.MacroParam** %12, align 8
  %64 = load %struct.MacroParam*, %struct.MacroParam** %7, align 8
  %65 = icmp ne %struct.MacroParam* %63, %64
  br i1 %65, label %66, label %69

66:                                               ; preds = %62
  %67 = load %struct.Token*, %struct.Token** %6, align 8
  %68 = call %struct.Token* @skip(%struct.Token* noundef %67, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.105, i64 0, i64 0))
  store %struct.Token* %68, %struct.Token** %6, align 8
  br label %69

69:                                               ; preds = %66, %62
  %70 = load %struct.Token*, %struct.Token** %6, align 8
  %71 = call %struct.MacroArg* @read_macro_arg_one(%struct.Token** noundef %6, %struct.Token* noundef %70, i1 noundef zeroext true)
  store %struct.MacroArg* %71, %struct.MacroArg** %13, align 8
  br label %72

72:                                               ; preds = %69, %57
  %73 = load i8*, i8** %8, align 8
  %74 = load %struct.MacroArg*, %struct.MacroArg** %13, align 8
  %75 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %74, i32 0, i32 1
  store i8* %73, i8** %75, align 8
  %76 = load %struct.MacroArg*, %struct.MacroArg** %13, align 8
  %77 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %76, i32 0, i32 2
  store i8 1, i8* %77, align 8
  %78 = load %struct.MacroArg*, %struct.MacroArg** %13, align 8
  %79 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %80 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %79, i32 0, i32 0
  store %struct.MacroArg* %78, %struct.MacroArg** %80, align 8
  store %struct.MacroArg* %78, %struct.MacroArg** %11, align 8
  br label %87

81:                                               ; preds = %45
  %82 = load %struct.MacroParam*, %struct.MacroParam** %12, align 8
  %83 = icmp ne %struct.MacroParam* %82, null
  br i1 %83, label %84, label %86

84:                                               ; preds = %81
  %85 = load %struct.Token*, %struct.Token** %9, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %85, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.124, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

86:                                               ; preds = %81
  br label %87

87:                                               ; preds = %86, %72
  %88 = load %struct.Token*, %struct.Token** %6, align 8
  %89 = call %struct.Token* @skip(%struct.Token* noundef %88, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  %90 = load %struct.Token*, %struct.Token** %6, align 8
  %91 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %90, %struct.Token** %91, align 8
  %92 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %10, i32 0, i32 0
  %93 = load %struct.MacroArg*, %struct.MacroArg** %92, align 8
  ret %struct.MacroArg* %93
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Hideset* @hideset_intersection(%struct.Hideset* noundef %0, %struct.Hideset* noundef %1) #0 {
  %3 = alloca %struct.Hideset*, align 8
  %4 = alloca %struct.Hideset*, align 8
  %5 = alloca %struct.Hideset, align 8
  %6 = alloca %struct.Hideset*, align 8
  store %struct.Hideset* %0, %struct.Hideset** %3, align 8
  store %struct.Hideset* %1, %struct.Hideset** %4, align 8
  %7 = bitcast %struct.Hideset* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %7, i8 0, i64 16, i1 false)
  store %struct.Hideset* %5, %struct.Hideset** %6, align 8
  br label %8

8:                                                ; preds = %30, %2
  %9 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %10 = icmp ne %struct.Hideset* %9, null
  br i1 %10, label %11, label %34

11:                                               ; preds = %8
  %12 = load %struct.Hideset*, %struct.Hideset** %4, align 8
  %13 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %14 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %13, i32 0, i32 1
  %15 = load i8*, i8** %14, align 8
  %16 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %17 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %16, i32 0, i32 1
  %18 = load i8*, i8** %17, align 8
  %19 = call i64 @strlen(i8* noundef %18) #8
  %20 = trunc i64 %19 to i32
  %21 = call zeroext i1 @hideset_contains(%struct.Hideset* noundef %12, i8* noundef %15, i32 noundef %20)
  br i1 %21, label %22, label %29

22:                                               ; preds = %11
  %23 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %24 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %23, i32 0, i32 1
  %25 = load i8*, i8** %24, align 8
  %26 = call %struct.Hideset* @new_hideset(i8* noundef %25)
  %27 = load %struct.Hideset*, %struct.Hideset** %6, align 8
  %28 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %27, i32 0, i32 0
  store %struct.Hideset* %26, %struct.Hideset** %28, align 8
  store %struct.Hideset* %26, %struct.Hideset** %6, align 8
  br label %29

29:                                               ; preds = %22, %11
  br label %30

30:                                               ; preds = %29
  %31 = load %struct.Hideset*, %struct.Hideset** %3, align 8
  %32 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %31, i32 0, i32 0
  %33 = load %struct.Hideset*, %struct.Hideset** %32, align 8
  store %struct.Hideset* %33, %struct.Hideset** %3, align 8
  br label %8, !llvm.loop !43

34:                                               ; preds = %8
  %35 = getelementptr inbounds %struct.Hideset, %struct.Hideset* %5, i32 0, i32 0
  %36 = load %struct.Hideset*, %struct.Hideset** %35, align 8
  ret %struct.Hideset* %36
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @subst(%struct.Token* noundef %0, %struct.MacroArg* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.MacroArg*, align 8
  %5 = alloca %struct.Token, align 16
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.MacroArg*, align 8
  %8 = alloca %struct.MacroArg*, align 8
  %9 = alloca %struct.MacroArg*, align 8
  %10 = alloca %struct.Token*, align 8
  %11 = alloca %struct.MacroArg*, align 8
  %12 = alloca %struct.Token*, align 8
  %13 = alloca %struct.MacroArg*, align 8
  %14 = alloca %struct.Token*, align 8
  %15 = alloca %struct.Token*, align 8
  %16 = alloca %struct.MacroArg*, align 8
  %17 = alloca %struct.Token*, align 8
  %18 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.MacroArg* %1, %struct.MacroArg** %4, align 8
  %19 = bitcast %struct.Token* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %19, i8 0, i64 128, i1 false)
  store %struct.Token* %5, %struct.Token** %6, align 8
  br label %20

20:                                               ; preds = %334, %330, %298, %259, %237, %170, %164, %101, %40, %2
  %21 = load %struct.Token*, %struct.Token** %3, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 0
  %23 = load i32, i32* %22, align 16
  %24 = icmp ne i32 %23, 6
  br i1 %24, label %25, label %342

25:                                               ; preds = %20
  %26 = load %struct.Token*, %struct.Token** %3, align 8
  %27 = call zeroext i1 @equal(%struct.Token* noundef %26, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.94, i64 0, i64 0))
  br i1 %27, label %28, label %53

28:                                               ; preds = %25
  %29 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %30 = load %struct.Token*, %struct.Token** %3, align 8
  %31 = getelementptr inbounds %struct.Token, %struct.Token* %30, i32 0, i32 1
  %32 = load %struct.Token*, %struct.Token** %31, align 8
  %33 = call %struct.MacroArg* @find_arg(%struct.MacroArg* noundef %29, %struct.Token* noundef %32)
  store %struct.MacroArg* %33, %struct.MacroArg** %7, align 8
  %34 = load %struct.MacroArg*, %struct.MacroArg** %7, align 8
  %35 = icmp ne %struct.MacroArg* %34, null
  br i1 %35, label %40, label %36

36:                                               ; preds = %28
  %37 = load %struct.Token*, %struct.Token** %3, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 1
  %39 = load %struct.Token*, %struct.Token** %38, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %39, i8* noundef getelementptr inbounds ([56 x i8], [56 x i8]* @.str.127, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

40:                                               ; preds = %28
  %41 = load %struct.Token*, %struct.Token** %3, align 8
  %42 = load %struct.MacroArg*, %struct.MacroArg** %7, align 8
  %43 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %42, i32 0, i32 3
  %44 = load %struct.Token*, %struct.Token** %43, align 8
  %45 = call %struct.Token* @stringize(%struct.Token* noundef %41, %struct.Token* noundef %44)
  %46 = load %struct.Token*, %struct.Token** %6, align 8
  %47 = getelementptr inbounds %struct.Token, %struct.Token* %46, i32 0, i32 1
  store %struct.Token* %45, %struct.Token** %47, align 8
  store %struct.Token* %45, %struct.Token** %6, align 8
  %48 = load %struct.Token*, %struct.Token** %3, align 8
  %49 = getelementptr inbounds %struct.Token, %struct.Token* %48, i32 0, i32 1
  %50 = load %struct.Token*, %struct.Token** %49, align 8
  %51 = getelementptr inbounds %struct.Token, %struct.Token* %50, i32 0, i32 1
  %52 = load %struct.Token*, %struct.Token** %51, align 8
  store %struct.Token* %52, %struct.Token** %3, align 8
  br label %20, !llvm.loop !44

53:                                               ; preds = %25
  %54 = load %struct.Token*, %struct.Token** %3, align 8
  %55 = call zeroext i1 @equal(%struct.Token* noundef %54, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.105, i64 0, i64 0))
  br i1 %55, label %56, label %103

56:                                               ; preds = %53
  %57 = load %struct.Token*, %struct.Token** %3, align 8
  %58 = getelementptr inbounds %struct.Token, %struct.Token* %57, i32 0, i32 1
  %59 = load %struct.Token*, %struct.Token** %58, align 8
  %60 = call zeroext i1 @equal(%struct.Token* noundef %59, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.128, i64 0, i64 0))
  br i1 %60, label %61, label %103

61:                                               ; preds = %56
  %62 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %63 = load %struct.Token*, %struct.Token** %3, align 8
  %64 = getelementptr inbounds %struct.Token, %struct.Token* %63, i32 0, i32 1
  %65 = load %struct.Token*, %struct.Token** %64, align 8
  %66 = getelementptr inbounds %struct.Token, %struct.Token* %65, i32 0, i32 1
  %67 = load %struct.Token*, %struct.Token** %66, align 8
  %68 = call %struct.MacroArg* @find_arg(%struct.MacroArg* noundef %62, %struct.Token* noundef %67)
  store %struct.MacroArg* %68, %struct.MacroArg** %8, align 8
  %69 = load %struct.MacroArg*, %struct.MacroArg** %8, align 8
  %70 = icmp ne %struct.MacroArg* %69, null
  br i1 %70, label %71, label %102

71:                                               ; preds = %61
  %72 = load %struct.MacroArg*, %struct.MacroArg** %8, align 8
  %73 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %72, i32 0, i32 2
  %74 = load i8, i8* %73, align 8
  %75 = trunc i8 %74 to i1
  br i1 %75, label %76, label %102

76:                                               ; preds = %71
  %77 = load %struct.MacroArg*, %struct.MacroArg** %8, align 8
  %78 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %77, i32 0, i32 3
  %79 = load %struct.Token*, %struct.Token** %78, align 8
  %80 = getelementptr inbounds %struct.Token, %struct.Token* %79, i32 0, i32 0
  %81 = load i32, i32* %80, align 16
  %82 = icmp eq i32 %81, 6
  br i1 %82, label %83, label %91

83:                                               ; preds = %76
  %84 = load %struct.Token*, %struct.Token** %3, align 8
  %85 = getelementptr inbounds %struct.Token, %struct.Token* %84, i32 0, i32 1
  %86 = load %struct.Token*, %struct.Token** %85, align 8
  %87 = getelementptr inbounds %struct.Token, %struct.Token* %86, i32 0, i32 1
  %88 = load %struct.Token*, %struct.Token** %87, align 8
  %89 = getelementptr inbounds %struct.Token, %struct.Token* %88, i32 0, i32 1
  %90 = load %struct.Token*, %struct.Token** %89, align 8
  store %struct.Token* %90, %struct.Token** %3, align 8
  br label %101

91:                                               ; preds = %76
  %92 = load %struct.Token*, %struct.Token** %3, align 8
  %93 = call %struct.Token* @copy_token(%struct.Token* noundef %92)
  %94 = load %struct.Token*, %struct.Token** %6, align 8
  %95 = getelementptr inbounds %struct.Token, %struct.Token* %94, i32 0, i32 1
  store %struct.Token* %93, %struct.Token** %95, align 8
  store %struct.Token* %93, %struct.Token** %6, align 8
  %96 = load %struct.Token*, %struct.Token** %3, align 8
  %97 = getelementptr inbounds %struct.Token, %struct.Token* %96, i32 0, i32 1
  %98 = load %struct.Token*, %struct.Token** %97, align 8
  %99 = getelementptr inbounds %struct.Token, %struct.Token* %98, i32 0, i32 1
  %100 = load %struct.Token*, %struct.Token** %99, align 8
  store %struct.Token* %100, %struct.Token** %3, align 8
  br label %101

101:                                              ; preds = %91, %83
  br label %20, !llvm.loop !44

102:                                              ; preds = %71, %61
  br label %103

103:                                              ; preds = %102, %56, %53
  %104 = load %struct.Token*, %struct.Token** %3, align 8
  %105 = call zeroext i1 @equal(%struct.Token* noundef %104, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.128, i64 0, i64 0))
  br i1 %105, label %106, label %184

106:                                              ; preds = %103
  %107 = load %struct.Token*, %struct.Token** %6, align 8
  %108 = icmp eq %struct.Token* %107, %5
  br i1 %108, label %109, label %111

109:                                              ; preds = %106
  %110 = load %struct.Token*, %struct.Token** %3, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %110, i8* noundef getelementptr inbounds ([62 x i8], [62 x i8]* @.str.129, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

111:                                              ; preds = %106
  %112 = load %struct.Token*, %struct.Token** %3, align 8
  %113 = getelementptr inbounds %struct.Token, %struct.Token* %112, i32 0, i32 1
  %114 = load %struct.Token*, %struct.Token** %113, align 8
  %115 = getelementptr inbounds %struct.Token, %struct.Token* %114, i32 0, i32 0
  %116 = load i32, i32* %115, align 16
  %117 = icmp eq i32 %116, 6
  br i1 %117, label %118, label %120

118:                                              ; preds = %111
  %119 = load %struct.Token*, %struct.Token** %3, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %119, i8* noundef getelementptr inbounds ([60 x i8], [60 x i8]* @.str.130, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

120:                                              ; preds = %111
  %121 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %122 = load %struct.Token*, %struct.Token** %3, align 8
  %123 = getelementptr inbounds %struct.Token, %struct.Token* %122, i32 0, i32 1
  %124 = load %struct.Token*, %struct.Token** %123, align 8
  %125 = call %struct.MacroArg* @find_arg(%struct.MacroArg* noundef %121, %struct.Token* noundef %124)
  store %struct.MacroArg* %125, %struct.MacroArg** %9, align 8
  %126 = load %struct.MacroArg*, %struct.MacroArg** %9, align 8
  %127 = icmp ne %struct.MacroArg* %126, null
  br i1 %127, label %128, label %170

128:                                              ; preds = %120
  %129 = load %struct.MacroArg*, %struct.MacroArg** %9, align 8
  %130 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %129, i32 0, i32 3
  %131 = load %struct.Token*, %struct.Token** %130, align 8
  %132 = getelementptr inbounds %struct.Token, %struct.Token* %131, i32 0, i32 0
  %133 = load i32, i32* %132, align 16
  %134 = icmp ne i32 %133, 6
  br i1 %134, label %135, label %164

135:                                              ; preds = %128
  %136 = load %struct.Token*, %struct.Token** %6, align 8
  %137 = load %struct.Token*, %struct.Token** %6, align 8
  %138 = load %struct.MacroArg*, %struct.MacroArg** %9, align 8
  %139 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %138, i32 0, i32 3
  %140 = load %struct.Token*, %struct.Token** %139, align 8
  %141 = call %struct.Token* @paste(%struct.Token* noundef %137, %struct.Token* noundef %140)
  %142 = bitcast %struct.Token* %136 to i8*
  %143 = bitcast %struct.Token* %141 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %142, i8* align 16 %143, i64 128, i1 false)
  %144 = load %struct.MacroArg*, %struct.MacroArg** %9, align 8
  %145 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %144, i32 0, i32 3
  %146 = load %struct.Token*, %struct.Token** %145, align 8
  %147 = getelementptr inbounds %struct.Token, %struct.Token* %146, i32 0, i32 1
  %148 = load %struct.Token*, %struct.Token** %147, align 8
  store %struct.Token* %148, %struct.Token** %10, align 8
  br label %149

149:                                              ; preds = %159, %135
  %150 = load %struct.Token*, %struct.Token** %10, align 8
  %151 = getelementptr inbounds %struct.Token, %struct.Token* %150, i32 0, i32 0
  %152 = load i32, i32* %151, align 16
  %153 = icmp ne i32 %152, 6
  br i1 %153, label %154, label %163

154:                                              ; preds = %149
  %155 = load %struct.Token*, %struct.Token** %10, align 8
  %156 = call %struct.Token* @copy_token(%struct.Token* noundef %155)
  %157 = load %struct.Token*, %struct.Token** %6, align 8
  %158 = getelementptr inbounds %struct.Token, %struct.Token* %157, i32 0, i32 1
  store %struct.Token* %156, %struct.Token** %158, align 8
  store %struct.Token* %156, %struct.Token** %6, align 8
  br label %159

159:                                              ; preds = %154
  %160 = load %struct.Token*, %struct.Token** %10, align 8
  %161 = getelementptr inbounds %struct.Token, %struct.Token* %160, i32 0, i32 1
  %162 = load %struct.Token*, %struct.Token** %161, align 8
  store %struct.Token* %162, %struct.Token** %10, align 8
  br label %149, !llvm.loop !45

163:                                              ; preds = %149
  br label %164

164:                                              ; preds = %163, %128
  %165 = load %struct.Token*, %struct.Token** %3, align 8
  %166 = getelementptr inbounds %struct.Token, %struct.Token* %165, i32 0, i32 1
  %167 = load %struct.Token*, %struct.Token** %166, align 8
  %168 = getelementptr inbounds %struct.Token, %struct.Token* %167, i32 0, i32 1
  %169 = load %struct.Token*, %struct.Token** %168, align 8
  store %struct.Token* %169, %struct.Token** %3, align 8
  br label %20, !llvm.loop !44

170:                                              ; preds = %120
  %171 = load %struct.Token*, %struct.Token** %6, align 8
  %172 = load %struct.Token*, %struct.Token** %6, align 8
  %173 = load %struct.Token*, %struct.Token** %3, align 8
  %174 = getelementptr inbounds %struct.Token, %struct.Token* %173, i32 0, i32 1
  %175 = load %struct.Token*, %struct.Token** %174, align 8
  %176 = call %struct.Token* @paste(%struct.Token* noundef %172, %struct.Token* noundef %175)
  %177 = bitcast %struct.Token* %171 to i8*
  %178 = bitcast %struct.Token* %176 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %177, i8* align 16 %178, i64 128, i1 false)
  %179 = load %struct.Token*, %struct.Token** %3, align 8
  %180 = getelementptr inbounds %struct.Token, %struct.Token* %179, i32 0, i32 1
  %181 = load %struct.Token*, %struct.Token** %180, align 8
  %182 = getelementptr inbounds %struct.Token, %struct.Token* %181, i32 0, i32 1
  %183 = load %struct.Token*, %struct.Token** %182, align 8
  store %struct.Token* %183, %struct.Token** %3, align 8
  br label %20, !llvm.loop !44

184:                                              ; preds = %103
  %185 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %186 = load %struct.Token*, %struct.Token** %3, align 8
  %187 = call %struct.MacroArg* @find_arg(%struct.MacroArg* noundef %185, %struct.Token* noundef %186)
  store %struct.MacroArg* %187, %struct.MacroArg** %11, align 8
  %188 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %189 = icmp ne %struct.MacroArg* %188, null
  br i1 %189, label %190, label %263

190:                                              ; preds = %184
  %191 = load %struct.Token*, %struct.Token** %3, align 8
  %192 = getelementptr inbounds %struct.Token, %struct.Token* %191, i32 0, i32 1
  %193 = load %struct.Token*, %struct.Token** %192, align 8
  %194 = call zeroext i1 @equal(%struct.Token* noundef %193, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.128, i64 0, i64 0))
  br i1 %194, label %195, label %263

195:                                              ; preds = %190
  %196 = load %struct.Token*, %struct.Token** %3, align 8
  %197 = getelementptr inbounds %struct.Token, %struct.Token* %196, i32 0, i32 1
  %198 = load %struct.Token*, %struct.Token** %197, align 8
  %199 = getelementptr inbounds %struct.Token, %struct.Token* %198, i32 0, i32 1
  %200 = load %struct.Token*, %struct.Token** %199, align 8
  store %struct.Token* %200, %struct.Token** %12, align 8
  %201 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %202 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %201, i32 0, i32 3
  %203 = load %struct.Token*, %struct.Token** %202, align 8
  %204 = getelementptr inbounds %struct.Token, %struct.Token* %203, i32 0, i32 0
  %205 = load i32, i32* %204, align 16
  %206 = icmp eq i32 %205, 6
  br i1 %206, label %207, label %241

207:                                              ; preds = %195
  %208 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %209 = load %struct.Token*, %struct.Token** %12, align 8
  %210 = call %struct.MacroArg* @find_arg(%struct.MacroArg* noundef %208, %struct.Token* noundef %209)
  store %struct.MacroArg* %210, %struct.MacroArg** %13, align 8
  %211 = load %struct.MacroArg*, %struct.MacroArg** %13, align 8
  %212 = icmp ne %struct.MacroArg* %211, null
  br i1 %212, label %213, label %232

213:                                              ; preds = %207
  %214 = load %struct.MacroArg*, %struct.MacroArg** %13, align 8
  %215 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %214, i32 0, i32 3
  %216 = load %struct.Token*, %struct.Token** %215, align 8
  store %struct.Token* %216, %struct.Token** %14, align 8
  br label %217

217:                                              ; preds = %227, %213
  %218 = load %struct.Token*, %struct.Token** %14, align 8
  %219 = getelementptr inbounds %struct.Token, %struct.Token* %218, i32 0, i32 0
  %220 = load i32, i32* %219, align 16
  %221 = icmp ne i32 %220, 6
  br i1 %221, label %222, label %231

222:                                              ; preds = %217
  %223 = load %struct.Token*, %struct.Token** %14, align 8
  %224 = call %struct.Token* @copy_token(%struct.Token* noundef %223)
  %225 = load %struct.Token*, %struct.Token** %6, align 8
  %226 = getelementptr inbounds %struct.Token, %struct.Token* %225, i32 0, i32 1
  store %struct.Token* %224, %struct.Token** %226, align 8
  store %struct.Token* %224, %struct.Token** %6, align 8
  br label %227

227:                                              ; preds = %222
  %228 = load %struct.Token*, %struct.Token** %14, align 8
  %229 = getelementptr inbounds %struct.Token, %struct.Token* %228, i32 0, i32 1
  %230 = load %struct.Token*, %struct.Token** %229, align 8
  store %struct.Token* %230, %struct.Token** %14, align 8
  br label %217, !llvm.loop !46

231:                                              ; preds = %217
  br label %237

232:                                              ; preds = %207
  %233 = load %struct.Token*, %struct.Token** %12, align 8
  %234 = call %struct.Token* @copy_token(%struct.Token* noundef %233)
  %235 = load %struct.Token*, %struct.Token** %6, align 8
  %236 = getelementptr inbounds %struct.Token, %struct.Token* %235, i32 0, i32 1
  store %struct.Token* %234, %struct.Token** %236, align 8
  store %struct.Token* %234, %struct.Token** %6, align 8
  br label %237

237:                                              ; preds = %232, %231
  %238 = load %struct.Token*, %struct.Token** %12, align 8
  %239 = getelementptr inbounds %struct.Token, %struct.Token* %238, i32 0, i32 1
  %240 = load %struct.Token*, %struct.Token** %239, align 8
  store %struct.Token* %240, %struct.Token** %3, align 8
  br label %20, !llvm.loop !44

241:                                              ; preds = %195
  %242 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %243 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %242, i32 0, i32 3
  %244 = load %struct.Token*, %struct.Token** %243, align 8
  store %struct.Token* %244, %struct.Token** %15, align 8
  br label %245

245:                                              ; preds = %255, %241
  %246 = load %struct.Token*, %struct.Token** %15, align 8
  %247 = getelementptr inbounds %struct.Token, %struct.Token* %246, i32 0, i32 0
  %248 = load i32, i32* %247, align 16
  %249 = icmp ne i32 %248, 6
  br i1 %249, label %250, label %259

250:                                              ; preds = %245
  %251 = load %struct.Token*, %struct.Token** %15, align 8
  %252 = call %struct.Token* @copy_token(%struct.Token* noundef %251)
  %253 = load %struct.Token*, %struct.Token** %6, align 8
  %254 = getelementptr inbounds %struct.Token, %struct.Token* %253, i32 0, i32 1
  store %struct.Token* %252, %struct.Token** %254, align 8
  store %struct.Token* %252, %struct.Token** %6, align 8
  br label %255

255:                                              ; preds = %250
  %256 = load %struct.Token*, %struct.Token** %15, align 8
  %257 = getelementptr inbounds %struct.Token, %struct.Token* %256, i32 0, i32 1
  %258 = load %struct.Token*, %struct.Token** %257, align 8
  store %struct.Token* %258, %struct.Token** %15, align 8
  br label %245, !llvm.loop !47

259:                                              ; preds = %245
  %260 = load %struct.Token*, %struct.Token** %3, align 8
  %261 = getelementptr inbounds %struct.Token, %struct.Token* %260, i32 0, i32 1
  %262 = load %struct.Token*, %struct.Token** %261, align 8
  store %struct.Token* %262, %struct.Token** %3, align 8
  br label %20, !llvm.loop !44

263:                                              ; preds = %190, %184
  %264 = load %struct.Token*, %struct.Token** %3, align 8
  %265 = call zeroext i1 @equal(%struct.Token* noundef %264, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.131, i64 0, i64 0))
  br i1 %265, label %266, label %301

266:                                              ; preds = %263
  %267 = load %struct.Token*, %struct.Token** %3, align 8
  %268 = getelementptr inbounds %struct.Token, %struct.Token* %267, i32 0, i32 1
  %269 = load %struct.Token*, %struct.Token** %268, align 8
  %270 = call zeroext i1 @equal(%struct.Token* noundef %269, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.103, i64 0, i64 0))
  br i1 %270, label %271, label %301

271:                                              ; preds = %266
  %272 = load %struct.Token*, %struct.Token** %3, align 8
  %273 = getelementptr inbounds %struct.Token, %struct.Token* %272, i32 0, i32 1
  %274 = load %struct.Token*, %struct.Token** %273, align 8
  %275 = getelementptr inbounds %struct.Token, %struct.Token* %274, i32 0, i32 1
  %276 = load %struct.Token*, %struct.Token** %275, align 8
  %277 = call %struct.MacroArg* @read_macro_arg_one(%struct.Token** noundef %3, %struct.Token* noundef %276, i1 noundef zeroext true)
  store %struct.MacroArg* %277, %struct.MacroArg** %16, align 8
  %278 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %279 = call zeroext i1 @has_varargs(%struct.MacroArg* noundef %278)
  br i1 %279, label %280, label %298

280:                                              ; preds = %271
  %281 = load %struct.MacroArg*, %struct.MacroArg** %16, align 8
  %282 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %281, i32 0, i32 3
  %283 = load %struct.Token*, %struct.Token** %282, align 8
  store %struct.Token* %283, %struct.Token** %17, align 8
  br label %284

284:                                              ; preds = %293, %280
  %285 = load %struct.Token*, %struct.Token** %17, align 8
  %286 = getelementptr inbounds %struct.Token, %struct.Token* %285, i32 0, i32 0
  %287 = load i32, i32* %286, align 16
  %288 = icmp ne i32 %287, 6
  br i1 %288, label %289, label %297

289:                                              ; preds = %284
  %290 = load %struct.Token*, %struct.Token** %17, align 8
  %291 = load %struct.Token*, %struct.Token** %6, align 8
  %292 = getelementptr inbounds %struct.Token, %struct.Token* %291, i32 0, i32 1
  store %struct.Token* %290, %struct.Token** %292, align 8
  store %struct.Token* %290, %struct.Token** %6, align 8
  br label %293

293:                                              ; preds = %289
  %294 = load %struct.Token*, %struct.Token** %17, align 8
  %295 = getelementptr inbounds %struct.Token, %struct.Token* %294, i32 0, i32 1
  %296 = load %struct.Token*, %struct.Token** %295, align 8
  store %struct.Token* %296, %struct.Token** %17, align 8
  br label %284, !llvm.loop !48

297:                                              ; preds = %284
  br label %298

298:                                              ; preds = %297, %271
  %299 = load %struct.Token*, %struct.Token** %3, align 8
  %300 = call %struct.Token* @skip(%struct.Token* noundef %299, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  store %struct.Token* %300, %struct.Token** %3, align 8
  br label %20, !llvm.loop !44

301:                                              ; preds = %266, %263
  %302 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %303 = icmp ne %struct.MacroArg* %302, null
  br i1 %303, label %304, label %334

304:                                              ; preds = %301
  %305 = load %struct.MacroArg*, %struct.MacroArg** %11, align 8
  %306 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %305, i32 0, i32 3
  %307 = load %struct.Token*, %struct.Token** %306, align 8
  %308 = call %struct.Token* @preprocess2(%struct.Token* noundef %307)
  store %struct.Token* %308, %struct.Token** %18, align 8
  %309 = load %struct.Token*, %struct.Token** %3, align 8
  %310 = getelementptr inbounds %struct.Token, %struct.Token* %309, i32 0, i32 13
  %311 = load i8, i8* %310, align 1
  %312 = trunc i8 %311 to i1
  %313 = load %struct.Token*, %struct.Token** %18, align 8
  %314 = getelementptr inbounds %struct.Token, %struct.Token* %313, i32 0, i32 13
  %315 = zext i1 %312 to i8
  store i8 %315, i8* %314, align 1
  br label %316

316:                                              ; preds = %326, %304
  %317 = load %struct.Token*, %struct.Token** %18, align 8
  %318 = getelementptr inbounds %struct.Token, %struct.Token* %317, i32 0, i32 0
  %319 = load i32, i32* %318, align 16
  %320 = icmp ne i32 %319, 6
  br i1 %320, label %321, label %330

321:                                              ; preds = %316
  %322 = load %struct.Token*, %struct.Token** %18, align 8
  %323 = call %struct.Token* @copy_token(%struct.Token* noundef %322)
  %324 = load %struct.Token*, %struct.Token** %6, align 8
  %325 = getelementptr inbounds %struct.Token, %struct.Token* %324, i32 0, i32 1
  store %struct.Token* %323, %struct.Token** %325, align 8
  store %struct.Token* %323, %struct.Token** %6, align 8
  br label %326

326:                                              ; preds = %321
  %327 = load %struct.Token*, %struct.Token** %18, align 8
  %328 = getelementptr inbounds %struct.Token, %struct.Token* %327, i32 0, i32 1
  %329 = load %struct.Token*, %struct.Token** %328, align 8
  store %struct.Token* %329, %struct.Token** %18, align 8
  br label %316, !llvm.loop !49

330:                                              ; preds = %316
  %331 = load %struct.Token*, %struct.Token** %3, align 8
  %332 = getelementptr inbounds %struct.Token, %struct.Token* %331, i32 0, i32 1
  %333 = load %struct.Token*, %struct.Token** %332, align 8
  store %struct.Token* %333, %struct.Token** %3, align 8
  br label %20, !llvm.loop !44

334:                                              ; preds = %301
  %335 = load %struct.Token*, %struct.Token** %3, align 8
  %336 = call %struct.Token* @copy_token(%struct.Token* noundef %335)
  %337 = load %struct.Token*, %struct.Token** %6, align 8
  %338 = getelementptr inbounds %struct.Token, %struct.Token* %337, i32 0, i32 1
  store %struct.Token* %336, %struct.Token** %338, align 8
  store %struct.Token* %336, %struct.Token** %6, align 8
  %339 = load %struct.Token*, %struct.Token** %3, align 8
  %340 = getelementptr inbounds %struct.Token, %struct.Token* %339, i32 0, i32 1
  %341 = load %struct.Token*, %struct.Token** %340, align 8
  store %struct.Token* %341, %struct.Token** %3, align 8
  br label %20, !llvm.loop !44

342:                                              ; preds = %20
  %343 = load %struct.Token*, %struct.Token** %3, align 8
  %344 = load %struct.Token*, %struct.Token** %6, align 8
  %345 = getelementptr inbounds %struct.Token, %struct.Token* %344, i32 0, i32 1
  store %struct.Token* %343, %struct.Token** %345, align 8
  %346 = getelementptr inbounds %struct.Token, %struct.Token* %5, i32 0, i32 1
  %347 = load %struct.Token*, %struct.Token** %346, align 8
  ret %struct.Token* %347
}

; Function Attrs: nounwind readonly willreturn
declare i64 @strlen(i8* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.MacroArg* @read_macro_arg_one(%struct.Token** noundef %0, %struct.Token* noundef %1, i1 noundef zeroext %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca i8, align 1
  %7 = alloca %struct.Token, align 16
  %8 = alloca %struct.Token*, align 8
  %9 = alloca i32, align 4
  %10 = alloca %struct.MacroArg*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %11 = zext i1 %2 to i8
  store i8 %11, i8* %6, align 1
  %12 = bitcast %struct.Token* %7 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %12, i8 0, i64 128, i1 false)
  store %struct.Token* %7, %struct.Token** %8, align 8
  store i32 0, i32* %9, align 4
  br label %13

13:                                               ; preds = %50, %3
  %14 = load i32, i32* %9, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %20

16:                                               ; preds = %13
  %17 = load %struct.Token*, %struct.Token** %5, align 8
  %18 = call zeroext i1 @equal(%struct.Token* noundef %17, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  br i1 %18, label %19, label %20

19:                                               ; preds = %16
  br label %58

20:                                               ; preds = %16, %13
  %21 = load i32, i32* %9, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %23, label %30

23:                                               ; preds = %20
  %24 = load i8, i8* %6, align 1
  %25 = trunc i8 %24 to i1
  br i1 %25, label %30, label %26

26:                                               ; preds = %23
  %27 = load %struct.Token*, %struct.Token** %5, align 8
  %28 = call zeroext i1 @equal(%struct.Token* noundef %27, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.105, i64 0, i64 0))
  br i1 %28, label %29, label %30

29:                                               ; preds = %26
  br label %58

30:                                               ; preds = %26, %23, %20
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = getelementptr inbounds %struct.Token, %struct.Token* %31, i32 0, i32 0
  %33 = load i32, i32* %32, align 16
  %34 = icmp eq i32 %33, 6
  br i1 %34, label %35, label %37

35:                                               ; preds = %30
  %36 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %36, i8* noundef getelementptr inbounds ([51 x i8], [51 x i8]* @.str.125, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

37:                                               ; preds = %30
  %38 = load %struct.Token*, %struct.Token** %5, align 8
  %39 = call zeroext i1 @equal(%struct.Token* noundef %38, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.103, i64 0, i64 0))
  br i1 %39, label %40, label %43

40:                                               ; preds = %37
  %41 = load i32, i32* %9, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, i32* %9, align 4
  br label %50

43:                                               ; preds = %37
  %44 = load %struct.Token*, %struct.Token** %5, align 8
  %45 = call zeroext i1 @equal(%struct.Token* noundef %44, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.104, i64 0, i64 0))
  br i1 %45, label %46, label %49

46:                                               ; preds = %43
  %47 = load i32, i32* %9, align 4
  %48 = add nsw i32 %47, -1
  store i32 %48, i32* %9, align 4
  br label %49

49:                                               ; preds = %46, %43
  br label %50

50:                                               ; preds = %49, %40
  %51 = load %struct.Token*, %struct.Token** %5, align 8
  %52 = call %struct.Token* @copy_token(%struct.Token* noundef %51)
  %53 = load %struct.Token*, %struct.Token** %8, align 8
  %54 = getelementptr inbounds %struct.Token, %struct.Token* %53, i32 0, i32 1
  store %struct.Token* %52, %struct.Token** %54, align 8
  store %struct.Token* %52, %struct.Token** %8, align 8
  %55 = load %struct.Token*, %struct.Token** %5, align 8
  %56 = getelementptr inbounds %struct.Token, %struct.Token* %55, i32 0, i32 1
  %57 = load %struct.Token*, %struct.Token** %56, align 8
  store %struct.Token* %57, %struct.Token** %5, align 8
  br label %13

58:                                               ; preds = %29, %19
  %59 = load %struct.Token*, %struct.Token** %5, align 8
  %60 = call %struct.Token* @new_eof(%struct.Token* noundef %59)
  %61 = load %struct.Token*, %struct.Token** %8, align 8
  %62 = getelementptr inbounds %struct.Token, %struct.Token* %61, i32 0, i32 1
  store %struct.Token* %60, %struct.Token** %62, align 8
  %63 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 32) #9
  %64 = bitcast i8* %63 to %struct.MacroArg*
  store %struct.MacroArg* %64, %struct.MacroArg** %10, align 8
  %65 = load %struct.MacroArg*, %struct.MacroArg** %10, align 8
  %66 = icmp eq %struct.MacroArg* %65, null
  br i1 %66, label %67, label %68

67:                                               ; preds = %58
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.126, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0)) #10
  unreachable

68:                                               ; preds = %58
  %69 = getelementptr inbounds %struct.Token, %struct.Token* %7, i32 0, i32 1
  %70 = load %struct.Token*, %struct.Token** %69, align 8
  %71 = load %struct.MacroArg*, %struct.MacroArg** %10, align 8
  %72 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %71, i32 0, i32 3
  store %struct.Token* %70, %struct.Token** %72, align 8
  %73 = load %struct.Token*, %struct.Token** %5, align 8
  %74 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %73, %struct.Token** %74, align 8
  %75 = load %struct.MacroArg*, %struct.MacroArg** %10, align 8
  ret %struct.MacroArg* %75
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.MacroArg* @find_arg(%struct.MacroArg* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.MacroArg*, align 8
  %4 = alloca %struct.MacroArg*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.MacroArg*, align 8
  store %struct.MacroArg* %0, %struct.MacroArg** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %7 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  store %struct.MacroArg* %7, %struct.MacroArg** %6, align 8
  br label %8

8:                                                ; preds = %37, %2
  %9 = load %struct.MacroArg*, %struct.MacroArg** %6, align 8
  %10 = icmp ne %struct.MacroArg* %9, null
  br i1 %10, label %11, label %41

11:                                               ; preds = %8
  %12 = load %struct.Token*, %struct.Token** %5, align 8
  %13 = getelementptr inbounds %struct.Token, %struct.Token* %12, i32 0, i32 5
  %14 = load i32, i32* %13, align 8
  %15 = sext i32 %14 to i64
  %16 = load %struct.MacroArg*, %struct.MacroArg** %6, align 8
  %17 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %16, i32 0, i32 1
  %18 = load i8*, i8** %17, align 8
  %19 = call i64 @strlen(i8* noundef %18) #8
  %20 = icmp eq i64 %15, %19
  br i1 %20, label %21, label %36

21:                                               ; preds = %11
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = getelementptr inbounds %struct.Token, %struct.Token* %22, i32 0, i32 4
  %24 = load i8*, i8** %23, align 16
  %25 = load %struct.MacroArg*, %struct.MacroArg** %6, align 8
  %26 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %25, i32 0, i32 1
  %27 = load i8*, i8** %26, align 8
  %28 = load %struct.Token*, %struct.Token** %5, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 5
  %30 = load i32, i32* %29, align 8
  %31 = sext i32 %30 to i64
  %32 = call i32 @strncmp(i8* noundef %24, i8* noundef %27, i64 noundef %31) #8
  %33 = icmp ne i32 %32, 0
  br i1 %33, label %36, label %34

34:                                               ; preds = %21
  %35 = load %struct.MacroArg*, %struct.MacroArg** %6, align 8
  store %struct.MacroArg* %35, %struct.MacroArg** %3, align 8
  br label %42

36:                                               ; preds = %21, %11
  br label %37

37:                                               ; preds = %36
  %38 = load %struct.MacroArg*, %struct.MacroArg** %6, align 8
  %39 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %38, i32 0, i32 0
  %40 = load %struct.MacroArg*, %struct.MacroArg** %39, align 8
  store %struct.MacroArg* %40, %struct.MacroArg** %6, align 8
  br label %8, !llvm.loop !50

41:                                               ; preds = %8
  store %struct.MacroArg* null, %struct.MacroArg** %3, align 8
  br label %42

42:                                               ; preds = %41, %34
  %43 = load %struct.MacroArg*, %struct.MacroArg** %3, align 8
  ret %struct.MacroArg* %43
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @stringize(%struct.Token* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca i8*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load %struct.Token*, %struct.Token** %4, align 8
  %7 = call i8* @join_tokens(%struct.Token* noundef %6, %struct.Token* noundef null)
  store i8* %7, i8** %5, align 8
  %8 = load i8*, i8** %5, align 8
  %9 = load %struct.Token*, %struct.Token** %3, align 8
  %10 = call %struct.Token* @new_str_token(i8* noundef %8, %struct.Token* noundef %9)
  ret %struct.Token* %10
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @paste(%struct.Token* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %3, align 8
  %8 = getelementptr inbounds %struct.Token, %struct.Token* %7, i32 0, i32 5
  %9 = load i32, i32* %8, align 8
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 4
  %12 = load i8*, i8** %11, align 16
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 5
  %15 = load i32, i32* %14, align 8
  %16 = load %struct.Token*, %struct.Token** %4, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 4
  %18 = load i8*, i8** %17, align 16
  %19 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.132, i64 0, i64 0), i32 noundef %9, i8* noundef %12, i32 noundef %15, i8* noundef %18)
  store i8* %19, i8** %5, align 8
  %20 = load %struct.Token*, %struct.Token** %3, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 8
  %22 = load %struct.File*, %struct.File** %21, align 16
  %23 = getelementptr inbounds %struct.File, %struct.File* %22, i32 0, i32 0
  %24 = load i8*, i8** %23, align 8
  %25 = load %struct.Token*, %struct.Token** %3, align 8
  %26 = getelementptr inbounds %struct.Token, %struct.Token* %25, i32 0, i32 8
  %27 = load %struct.File*, %struct.File** %26, align 16
  %28 = getelementptr inbounds %struct.File, %struct.File* %27, i32 0, i32 1
  %29 = load i32, i32* %28, align 8
  %30 = load i8*, i8** %5, align 8
  %31 = call %struct.File* @new_file(i8* noundef %24, i32 noundef %29, i8* noundef %30)
  %32 = call %struct.Token* @tokenize(%struct.File* noundef %31)
  store %struct.Token* %32, %struct.Token** %6, align 8
  %33 = load %struct.Token*, %struct.Token** %6, align 8
  %34 = getelementptr inbounds %struct.Token, %struct.Token* %33, i32 0, i32 1
  %35 = load %struct.Token*, %struct.Token** %34, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 0
  %37 = load i32, i32* %36, align 16
  %38 = icmp ne i32 %37, 6
  br i1 %38, label %39, label %42

39:                                               ; preds = %2
  %40 = load %struct.Token*, %struct.Token** %3, align 8
  %41 = load i8*, i8** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %40, i8* noundef getelementptr inbounds ([52 x i8], [52 x i8]* @.str.133, i64 0, i64 0), i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.65, i64 0, i64 0), i8* noundef %41) #10
  unreachable

42:                                               ; preds = %2
  %43 = load %struct.Token*, %struct.Token** %6, align 8
  ret %struct.Token* %43
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @has_varargs(%struct.MacroArg* noundef %0) #0 {
  %2 = alloca i1, align 1
  %3 = alloca %struct.MacroArg*, align 8
  %4 = alloca %struct.MacroArg*, align 8
  store %struct.MacroArg* %0, %struct.MacroArg** %3, align 8
  %5 = load %struct.MacroArg*, %struct.MacroArg** %3, align 8
  store %struct.MacroArg* %5, %struct.MacroArg** %4, align 8
  br label %6

6:                                                ; preds = %23, %1
  %7 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %8 = icmp ne %struct.MacroArg* %7, null
  br i1 %8, label %9, label %27

9:                                                ; preds = %6
  %10 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %11 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %10, i32 0, i32 1
  %12 = load i8*, i8** %11, align 8
  %13 = call i32 @strcmp(i8* noundef %12, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.107, i64 0, i64 0)) #8
  %14 = icmp ne i32 %13, 0
  br i1 %14, label %22, label %15

15:                                               ; preds = %9
  %16 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %17 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %16, i32 0, i32 3
  %18 = load %struct.Token*, %struct.Token** %17, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 0
  %20 = load i32, i32* %19, align 16
  %21 = icmp ne i32 %20, 6
  store i1 %21, i1* %2, align 1
  br label %28

22:                                               ; preds = %9
  br label %23

23:                                               ; preds = %22
  %24 = load %struct.MacroArg*, %struct.MacroArg** %4, align 8
  %25 = getelementptr inbounds %struct.MacroArg, %struct.MacroArg* %24, i32 0, i32 0
  %26 = load %struct.MacroArg*, %struct.MacroArg** %25, align 8
  store %struct.MacroArg* %26, %struct.MacroArg** %4, align 8
  br label %6, !llvm.loop !51

27:                                               ; preds = %6
  store i1 false, i1* %2, align 1
  br label %28

28:                                               ; preds = %27, %15
  %29 = load i1, i1* %2, align 1
  ret i1 %29
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind readonly willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind readnone willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { argmemonly nofree nounwind willreturn writeonly }
attributes #7 = { argmemonly nofree nounwind willreturn }
attributes #8 = { nounwind readonly willreturn }
attributes #9 = { nounwind }
attributes #10 = { noreturn }
attributes #11 = { nounwind readnone willreturn }

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
!29 = distinct !{!29, !7}
!30 = distinct !{!30, !7}
!31 = distinct !{!31, !7}
!32 = distinct !{!32, !7}
!33 = distinct !{!33, !7}
!34 = distinct !{!34, !7}
!35 = distinct !{!35, !7}
!36 = distinct !{!36, !7}
!37 = distinct !{!37, !7}
!38 = distinct !{!38, !7}
!39 = distinct !{!39, !7}
!40 = distinct !{!40, !7}
!41 = distinct !{!41, !7}
!42 = distinct !{!42, !7}
!43 = distinct !{!43, !7}
!44 = distinct !{!44, !7}
!45 = distinct !{!45, !7}
!46 = distinct !{!46, !7}
!47 = distinct !{!47, !7}
!48 = distinct !{!48, !7}
!49 = distinct !{!49, !7}
!50 = distinct !{!50, !7}
!51 = distinct !{!51, !7}
