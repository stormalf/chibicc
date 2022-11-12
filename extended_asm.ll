; ModuleID = 'extended_asm.c'
source_filename = "extended_asm.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.AsmExtended = type { %struct.AsmTemplate*, [10 x %struct.AsmOutput*], [10 x %struct.AsmInput*], [10 x %struct.AsmClobber*], i32, i32, i32, i32 }
%struct.AsmTemplate = type { i8*, i8 }
%struct.AsmOutput = type { %struct.Token*, i8*, i8*, i8*, i8, i32, i32, i8, i8, i8, i32, i8, i8 }
%struct.Token = type { i32, %struct.Token*, i64, x86_fp80, i8*, i32, %struct.Type*, i8*, %struct.File*, i8*, i32, i32, i8, i8, %struct.Hideset*, %struct.Token* }
%struct.Type = type { i32, i32, i32, i8, i8, i8, %struct.Type*, %struct.Type*, %struct.Type*, %struct.Token*, %struct.Token*, i32, %struct.Node*, %struct.Obj*, %struct.Member*, i8, i8, %struct.Type*, %struct.Type*, i8, %struct.Type* }
%struct.Node = type { i32, %struct.Node*, %struct.Type*, %struct.Token*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, i8*, i8*, %struct.Node*, %struct.Member*, %struct.Type*, %struct.Node*, i8, %struct.Obj*, i8*, i8*, %struct.Node*, %struct.Node*, %struct.Node*, i64, i64, i8*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Obj*, %struct.Node*, i8, %struct.Obj*, i64, x86_fp80, i32, [12 x i8] }
%struct.Obj = type { %struct.Obj*, i8*, i8*, %struct.Type*, %struct.Token*, i8, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8*, %struct.Relocation*, i8, %struct.Obj*, %struct.Node*, %struct.Obj*, %struct.Obj*, %struct.Obj*, i32, i8, i8, %struct.StringArray }
%struct.Relocation = type { %struct.Relocation*, i32, i8**, i64 }
%struct.StringArray = type { i8**, i32, i32 }
%struct.Member = type { %struct.Member*, %struct.Type*, %struct.Token*, %struct.Token*, i32, i32, i32, i8, i32, i32 }
%struct.File = type { i8*, i32, i8*, i8*, i32 }
%struct.Hideset = type opaque
%struct.AsmInput = type { %struct.Token*, i8*, i8*, i32, i8, i32, i32, i8, i8 }
%struct.AsmClobber = type { i8* }
%struct.VarScope = type { %struct.Obj*, %struct.Type*, %struct.Type*, i32 }

@asmExt = internal global %struct.AsmExtended* null, align 8
@nbInput = internal global i32 0, align 4
@nbOutput = internal global i32 0, align 4
@nbClobber = internal global i32 0, align 4
@nbLabel = internal global i32 0, align 4
@.str = private unnamed_addr constant [2 x i8] c";\00", align 1
@.str.1 = private unnamed_addr constant [50 x i8] c"%s : in extended_asm function : register is null!\00", align 1
@.str.2 = private unnamed_addr constant [15 x i8] c"extended_asm.c\00", align 1
@.str.3 = private unnamed_addr constant [57 x i8] c"%s : in extended_asm function : clobber not managed yet!\00", align 1
@.str.4 = private unnamed_addr constant [55 x i8] c"%s : in extended_asm function : label not managed yet!\00", align 1
@.str.5 = private unnamed_addr constant [94 x i8] c"%s : in extended_asm function : too much parameters or complex extended assembly not managed!\00", align 1
@.str.6 = private unnamed_addr constant [2 x i8] c":\00", align 1
@.str.7 = private unnamed_addr constant [3 x i8] c" %\00", align 1
@.str.8 = private unnamed_addr constant [3 x i8] c"%%\00", align 1
@.str.9 = private unnamed_addr constant [3 x i8] c" {\00", align 1
@.str.10 = private unnamed_addr constant [3 x i8] c"%{\00", align 1
@.str.11 = private unnamed_addr constant [3 x i8] c" |\00", align 1
@.str.12 = private unnamed_addr constant [3 x i8] c"%|\00", align 1
@.str.13 = private unnamed_addr constant [3 x i8] c" }\00", align 1
@.str.14 = private unnamed_addr constant [3 x i8] c"%}\00", align 1
@.str.15 = private unnamed_addr constant [3 x i8] c"=r\00", align 1
@.str.16 = private unnamed_addr constant [3 x i8] c"+r\00", align 1
@.str.17 = private unnamed_addr constant [2 x i8] c"=\00", align 1
@.str.18 = private unnamed_addr constant [2 x i8] c"+\00", align 1
@.str.19 = private unnamed_addr constant [5 x i8] c"%rax\00", align 1
@.str.20 = private unnamed_addr constant [3 x i8] c"=m\00", align 1
@.str.21 = private unnamed_addr constant [3 x i8] c"+m\00", align 1
@.str.22 = private unnamed_addr constant [3 x i8] c"=a\00", align 1
@.str.23 = private unnamed_addr constant [3 x i8] c"=b\00", align 1
@.str.24 = private unnamed_addr constant [3 x i8] c"=c\00", align 1
@.str.25 = private unnamed_addr constant [3 x i8] c"=d\00", align 1
@.str.26 = private unnamed_addr constant [5 x i8] c"%rbx\00", align 1
@.str.27 = private unnamed_addr constant [5 x i8] c"%rcx\00", align 1
@.str.28 = private unnamed_addr constant [5 x i8] c"%rdx\00", align 1
@.str.29 = private unnamed_addr constant [51 x i8] c"%s : in output_asm function : not implemented yet!\00", align 1
@.str.30 = private unnamed_addr constant [2 x i8] c",\00", align 1
@.str.31 = private unnamed_addr constant [2 x i8] c"(\00", align 1
@.str.32 = private unnamed_addr constant [49 x i8] c"%s : in output_asm function : variable undefined\00", align 1
@.str.33 = private unnamed_addr constant [52 x i8] c"%s : in output_asm function : variable type unknown\00", align 1
@.str.34 = private unnamed_addr constant [2 x i8] c")\00", align 1
@.str.35 = private unnamed_addr constant [50 x i8] c"%s : in output_asm function : output_str is null!\00", align 1
@.str.36 = private unnamed_addr constant [2 x i8] c"*\00", align 1
@.str.37 = private unnamed_addr constant [50 x i8] c"%s : in output_asm function : variable undefined2\00", align 1
@.str.38 = private unnamed_addr constant [53 x i8] c"%s : in output_asm function : variable type unknown2\00", align 1
@.str.39 = private unnamed_addr constant [51 x i8] c"%s : in output_asm function : output_str is null!2\00", align 1
@.str.40 = private unnamed_addr constant [51 x i8] c"%s : in output_asm function : identifier expected!\00", align 1
@.str.41 = private unnamed_addr constant [65 x i8] c"%s : in output_asm function : output constraint not managed yet!\00", align 1
@.str.42 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.43 = private unnamed_addr constant [3 x i8] c"%0\00", align 1
@.str.44 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@.str.45 = private unnamed_addr constant [3 x i8] c"%1\00", align 1
@.str.46 = private unnamed_addr constant [2 x i8] c"2\00", align 1
@.str.47 = private unnamed_addr constant [3 x i8] c"%2\00", align 1
@.str.48 = private unnamed_addr constant [2 x i8] c"3\00", align 1
@.str.49 = private unnamed_addr constant [3 x i8] c"%3\00", align 1
@.str.50 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@.str.51 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@.str.52 = private unnamed_addr constant [2 x i8] c"c\00", align 1
@.str.53 = private unnamed_addr constant [2 x i8] c"d\00", align 1
@.str.54 = private unnamed_addr constant [2 x i8] c"m\00", align 1
@.str.55 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.56 = private unnamed_addr constant [48 x i8] c"%s : in input_asm function : variable undefined\00", align 1
@.str.57 = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.str.58 = private unnamed_addr constant [3 x i8] c"0 \00", align 1
@.str.59 = private unnamed_addr constant [49 x i8] c"%s : in input_asm function : variable undefined2\00", align 1
@.str.60 = private unnamed_addr constant [71 x i8] c"%s : in input_asm function : input complex constraint not managed yet!\00", align 1
@.str.61 = private unnamed_addr constant [3 x i8] c", \00", align 1
@.str.62 = private unnamed_addr constant [3 x i8] c";\0A\00", align 1
@.str.63 = private unnamed_addr constant [3 x i8] c" $\00", align 1
@.str.64 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.65 = private unnamed_addr constant [8 x i8] c"  movq \00", align 1
@.str.66 = private unnamed_addr constant [8 x i8] c", %rsi\0A\00", align 1
@.str.67 = private unnamed_addr constant [10 x i8] c", (%rsi)\0A\00", align 1
@.str.68 = private unnamed_addr constant [10 x i8] c"-12(%rbp)\00", align 1
@.str.69 = private unnamed_addr constant [10 x i8] c"-24(%rbp)\00", align 1
@.str.70 = private unnamed_addr constant [10 x i8] c"-32(%rbp)\00", align 1
@.str.71 = private unnamed_addr constant [10 x i8] c"-40(%rbp)\00", align 1
@.str.72 = private unnamed_addr constant [10 x i8] c"-48(%rbp)\00", align 1
@.str.73 = private unnamed_addr constant [61 x i8] c"%s: in load_variable : nb of parameters > 5 not managed yet!\00", align 1
@.str.74 = private unnamed_addr constant [9 x i8] c"\0A  movb \00", align 1
@.str.75 = private unnamed_addr constant [9 x i8] c"\0A  movw \00", align 1
@.str.76 = private unnamed_addr constant [9 x i8] c"\0A  movl \00", align 1
@.str.77 = private unnamed_addr constant [9 x i8] c"\0A  movq \00", align 1
@.str.78 = private unnamed_addr constant [36 x i8] c"%s: in opcode : size %d unexpected!\00", align 1
@.str.79 = private unnamed_addr constant [49 x i8] c"%s: in update_register_size : reg %s unexpected!\00", align 1
@.str.80 = private unnamed_addr constant [3 x i8] c"%4\00", align 1
@.str.81 = private unnamed_addr constant [3 x i8] c"%5\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @extended_asm(%struct.Node* noundef %0, %struct.Token** noundef %1, %struct.Token* noundef %2) #0 {
  %4 = alloca %struct.Node*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i8*, align 8
  %11 = alloca i8*, align 8
  %12 = alloca i8*, align 8
  %13 = alloca i8*, align 8
  %14 = alloca i8*, align 8
  %15 = alloca i8*, align 8
  %16 = alloca i8*, align 8
  %17 = alloca i8*, align 8
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca i8*, align 8
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  store %struct.Node* %0, %struct.Node** %4, align 8
  store %struct.Token** %1, %struct.Token*** %5, align 8
  store %struct.Token* %2, %struct.Token** %6, align 8
  %24 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 264) #7
  %25 = bitcast i8* %24 to %struct.AsmExtended*
  store %struct.AsmExtended* %25, %struct.AsmExtended** @asmExt, align 8
  %26 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 16) #7
  %27 = bitcast i8* %26 to %struct.AsmTemplate*
  %28 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %29 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %28, i32 0, i32 0
  store %struct.AsmTemplate* %27, %struct.AsmTemplate** %29, align 8
  store i32 0, i32* %7, align 4
  br label %30

30:                                               ; preds = %41, %3
  %31 = load i32, i32* %7, align 4
  %32 = icmp slt i32 %31, 10
  br i1 %32, label %33, label %44

33:                                               ; preds = %30
  %34 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 48) #7
  %35 = bitcast i8* %34 to %struct.AsmInput*
  %36 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %37 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %36, i32 0, i32 2
  %38 = load i32, i32* %7, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %37, i64 0, i64 %39
  store %struct.AsmInput* %35, %struct.AsmInput** %40, align 8
  br label %41

41:                                               ; preds = %33
  %42 = load i32, i32* %7, align 4
  %43 = add nsw i32 %42, 1
  store i32 %43, i32* %7, align 4
  br label %30, !llvm.loop !6

44:                                               ; preds = %30
  store i32 0, i32* %8, align 4
  br label %45

45:                                               ; preds = %56, %44
  %46 = load i32, i32* %8, align 4
  %47 = icmp slt i32 %46, 10
  br i1 %47, label %48, label %59

48:                                               ; preds = %45
  %49 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 56) #7
  %50 = bitcast i8* %49 to %struct.AsmOutput*
  %51 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %52 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %51, i32 0, i32 1
  %53 = load i32, i32* %8, align 4
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %52, i64 0, i64 %54
  store %struct.AsmOutput* %50, %struct.AsmOutput** %55, align 8
  br label %56

56:                                               ; preds = %48
  %57 = load i32, i32* %8, align 4
  %58 = add nsw i32 %57, 1
  store i32 %58, i32* %8, align 4
  br label %45, !llvm.loop !8

59:                                               ; preds = %45
  store i32 0, i32* %9, align 4
  br label %60

60:                                               ; preds = %71, %59
  %61 = load i32, i32* %9, align 4
  %62 = icmp slt i32 %61, 10
  br i1 %62, label %63, label %74

63:                                               ; preds = %60
  %64 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 8) #7
  %65 = bitcast i8* %64 to %struct.AsmClobber*
  %66 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %67 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %66, i32 0, i32 3
  %68 = load i32, i32* %9, align 4
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds [10 x %struct.AsmClobber*], [10 x %struct.AsmClobber*]* %67, i64 0, i64 %69
  store %struct.AsmClobber* %65, %struct.AsmClobber** %70, align 8
  br label %71

71:                                               ; preds = %63
  %72 = load i32, i32* %9, align 4
  %73 = add nsw i32 %72, 1
  store i32 %73, i32* %9, align 4
  br label %60, !llvm.loop !9

74:                                               ; preds = %60
  %75 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 300) #7
  store i8* %75, i8** %10, align 8
  %76 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 300) #7
  store i8* %76, i8** %11, align 8
  %77 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 500) #7
  store i8* %77, i8** %12, align 8
  %78 = load %struct.Token*, %struct.Token** %6, align 8
  %79 = getelementptr inbounds %struct.Token, %struct.Token* %78, i32 0, i32 7
  %80 = load i8*, i8** %79, align 8
  store i8* %80, i8** %13, align 8
  %81 = load i8*, i8** %13, align 8
  %82 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %83 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %82, i32 0, i32 0
  %84 = load %struct.AsmTemplate*, %struct.AsmTemplate** %83, align 8
  %85 = getelementptr inbounds %struct.AsmTemplate, %struct.AsmTemplate* %84, i32 0, i32 0
  store i8* %81, i8** %85, align 8
  %86 = load i8*, i8** %13, align 8
  %87 = call zeroext i1 @check_template(i8* noundef %86)
  %88 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %89 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %88, i32 0, i32 0
  %90 = load %struct.AsmTemplate*, %struct.AsmTemplate** %89, align 8
  %91 = getelementptr inbounds %struct.AsmTemplate, %struct.AsmTemplate* %90, i32 0, i32 1
  %92 = zext i1 %87 to i8
  store i8 %92, i8* %91, align 8
  store i32 0, i32* %18, align 4
  store i32 0, i32* @nbInput, align 4
  store i32 0, i32* @nbOutput, align 4
  store i32 0, i32* @nbClobber, align 4
  store i32 0, i32* @nbLabel, align 4
  br label %93

93:                                               ; preds = %191, %74
  %94 = load %struct.Token*, %struct.Token** %6, align 8
  %95 = getelementptr inbounds %struct.Token, %struct.Token* %94, i32 0, i32 1
  %96 = load %struct.Token*, %struct.Token** %95, align 8
  %97 = call zeroext i1 @equal(%struct.Token* noundef %96, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i64 0, i64 0))
  br i1 %97, label %102, label %98

98:                                               ; preds = %93
  %99 = load %struct.Token*, %struct.Token** %6, align 8
  %100 = call zeroext i1 @equal(%struct.Token* noundef %99, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i64 0, i64 0))
  %101 = xor i1 %100, true
  br label %102

102:                                              ; preds = %98, %93
  %103 = phi i1 [ false, %93 ], [ %101, %98 ]
  br i1 %103, label %104, label %195

104:                                              ; preds = %102
  %105 = load i32, i32* %18, align 4
  switch i32 %105, label %183 [
    i32 0, label %106
    i32 1, label %107
    i32 2, label %123
    i32 3, label %177
    i32 4, label %179
  ]

106:                                              ; preds = %104
  br label %185

107:                                              ; preds = %104
  %108 = load %struct.Node*, %struct.Node** %4, align 8
  %109 = load %struct.Token**, %struct.Token*** %5, align 8
  %110 = load %struct.Token*, %struct.Token** %6, align 8
  %111 = call i8* @output_asm(%struct.Node* noundef %108, %struct.Token** noundef %109, %struct.Token* noundef %110)
  store i8* %111, i8** %15, align 8
  %112 = load i8*, i8** %15, align 8
  %113 = call i8* @generate_output_asm(i8* noundef %112)
  store i8* %113, i8** %16, align 8
  %114 = load i8*, i8** %10, align 8
  %115 = load i8*, i8** %16, align 8
  %116 = load i8*, i8** %16, align 8
  %117 = call i64 @strlen(i8* noundef %116) #8
  %118 = call i8* @strncat(i8* noundef %114, i8* noundef %115, i64 noundef %117) #7
  %119 = load i32, i32* @nbOutput, align 4
  %120 = add nsw i32 %119, 1
  store i32 %120, i32* @nbOutput, align 4
  %121 = load %struct.Token**, %struct.Token*** %5, align 8
  %122 = load %struct.Token*, %struct.Token** %121, align 8
  store %struct.Token* %122, %struct.Token** %6, align 8
  br label %185

123:                                              ; preds = %104
  %124 = load %struct.Node*, %struct.Node** %4, align 8
  %125 = load %struct.Token**, %struct.Token*** %5, align 8
  %126 = load %struct.Token*, %struct.Token** %6, align 8
  %127 = call i8* @input_asm(%struct.Node* noundef %124, %struct.Token** noundef %125, %struct.Token* noundef %126)
  store i8* %127, i8** %17, align 8
  %128 = load i8*, i8** %17, align 8
  %129 = call i8* @generate_input_asm(i8* noundef %128)
  store i8* %129, i8** %14, align 8
  %130 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %131 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %130, i32 0, i32 2
  %132 = load i32, i32* @nbInput, align 4
  %133 = sext i32 %132 to i64
  %134 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %131, i64 0, i64 %133
  %135 = load %struct.AsmInput*, %struct.AsmInput** %134, align 8
  %136 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %135, i32 0, i32 4
  %137 = load i8, i8* %136, align 4
  %138 = call i32 @retrieve_output_index(i8 noundef signext %137)
  store i32 %138, i32* %19, align 4
  %139 = load i32, i32* %19, align 4
  %140 = icmp slt i32 %139, 0
  br i1 %140, label %141, label %150

141:                                              ; preds = %123
  %142 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %143 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %142, i32 0, i32 2
  %144 = load i32, i32* @nbInput, align 4
  %145 = sext i32 %144 to i64
  %146 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %143, i64 0, i64 %145
  %147 = load %struct.AsmInput*, %struct.AsmInput** %146, align 8
  %148 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %147, i32 0, i32 3
  %149 = load i32, i32* %148, align 8
  store i32 %149, i32* %19, align 4
  br label %150

150:                                              ; preds = %141, %123
  %151 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %152 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %151, i32 0, i32 1
  %153 = load i32, i32* %19, align 4
  %154 = sext i32 %153 to i64
  %155 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %152, i64 0, i64 %154
  %156 = load %struct.AsmOutput*, %struct.AsmOutput** %155, align 8
  %157 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %156, i32 0, i32 3
  %158 = load i8*, i8** %157, align 8
  store i8* %158, i8** %20, align 8
  %159 = load i8*, i8** %20, align 8
  %160 = icmp ne i8* %159, null
  br i1 %160, label %163, label %161

161:                                              ; preds = %150
  %162 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %162, i8* noundef getelementptr inbounds ([50 x i8], [50 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

163:                                              ; preds = %150
  %164 = load i8*, i8** %14, align 8
  %165 = load i8*, i8** %20, align 8
  %166 = load i8*, i8** %17, align 8
  %167 = call i8* @subst_asm(i8* noundef %164, i8* noundef %165, i8* noundef %166)
  store i8* %167, i8** %14, align 8
  %168 = load i8*, i8** %11, align 8
  %169 = load i8*, i8** %14, align 8
  %170 = load i8*, i8** %14, align 8
  %171 = call i64 @strlen(i8* noundef %170) #8
  %172 = call i8* @strncat(i8* noundef %168, i8* noundef %169, i64 noundef %171) #7
  %173 = load i32, i32* @nbInput, align 4
  %174 = add nsw i32 %173, 1
  store i32 %174, i32* @nbInput, align 4
  %175 = load %struct.Token**, %struct.Token*** %5, align 8
  %176 = load %struct.Token*, %struct.Token** %175, align 8
  store %struct.Token* %176, %struct.Token** %6, align 8
  br label %185

177:                                              ; preds = %104
  %178 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %178, i8* noundef getelementptr inbounds ([57 x i8], [57 x i8]* @.str.3, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

179:                                              ; preds = %104
  %180 = load i32, i32* @nbLabel, align 4
  %181 = add nsw i32 %180, 1
  store i32 %181, i32* @nbLabel, align 4
  %182 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %182, i8* noundef getelementptr inbounds ([55 x i8], [55 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

183:                                              ; preds = %104
  %184 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %184, i8* noundef getelementptr inbounds ([94 x i8], [94 x i8]* @.str.5, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

185:                                              ; preds = %163, %107, %106
  %186 = load %struct.Token*, %struct.Token** %6, align 8
  %187 = call zeroext i1 @equal(%struct.Token* noundef %186, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i64 0, i64 0))
  br i1 %187, label %188, label %191

188:                                              ; preds = %185
  %189 = load i32, i32* %18, align 4
  %190 = add nsw i32 %189, 1
  store i32 %190, i32* %18, align 4
  br label %191

191:                                              ; preds = %188, %185
  %192 = load %struct.Token*, %struct.Token** %6, align 8
  %193 = getelementptr inbounds %struct.Token, %struct.Token* %192, i32 0, i32 1
  %194 = load %struct.Token*, %struct.Token** %193, align 8
  store %struct.Token* %194, %struct.Token** %6, align 8
  br label %93, !llvm.loop !10

195:                                              ; preds = %102
  %196 = load i8*, i8** %13, align 8
  %197 = load i8*, i8** %15, align 8
  %198 = load i8*, i8** %17, align 8
  %199 = call i8* @subst_asm(i8* noundef %196, i8* noundef %197, i8* noundef %198)
  store i8* %199, i8** %12, align 8
  %200 = load i8*, i8** %11, align 8
  %201 = icmp ne i8* %200, null
  br i1 %201, label %202, label %209

202:                                              ; preds = %195
  %203 = load i8*, i8** %11, align 8
  %204 = load i8*, i8** %12, align 8
  %205 = load i8*, i8** %12, align 8
  %206 = call i64 @strlen(i8* noundef %205) #8
  %207 = call i8* @strncat(i8* noundef %203, i8* noundef %204, i64 noundef %206) #7
  %208 = load i8*, i8** %11, align 8
  store i8* %208, i8** %12, align 8
  br label %209

209:                                              ; preds = %202, %195
  %210 = load i8*, i8** %10, align 8
  %211 = icmp ne i8* %210, null
  br i1 %211, label %212, label %218

212:                                              ; preds = %209
  %213 = load i8*, i8** %12, align 8
  %214 = load i8*, i8** %10, align 8
  %215 = load i8*, i8** %10, align 8
  %216 = call i64 @strlen(i8* noundef %215) #8
  %217 = call i8* @strncat(i8* noundef %213, i8* noundef %214, i64 noundef %216) #7
  br label %218

218:                                              ; preds = %212, %209
  %219 = load i8*, i8** %12, align 8
  %220 = call i8* @subst_asm(i8* noundef %219, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.7, i64 0, i64 0), i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.8, i64 0, i64 0))
  store i8* %220, i8** %12, align 8
  %221 = load i8*, i8** %12, align 8
  %222 = call i8* @subst_asm(i8* noundef %221, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0), i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.10, i64 0, i64 0))
  store i8* %222, i8** %12, align 8
  %223 = load i8*, i8** %12, align 8
  %224 = call i8* @subst_asm(i8* noundef %223, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i64 0, i64 0), i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.12, i64 0, i64 0))
  store i8* %224, i8** %12, align 8
  %225 = load i8*, i8** %12, align 8
  %226 = call i8* @subst_asm(i8* noundef %225, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.13, i64 0, i64 0), i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.14, i64 0, i64 0))
  store i8* %226, i8** %12, align 8
  %227 = load %struct.Token*, %struct.Token** %6, align 8
  %228 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %227, %struct.Token** %228, align 8
  store i32 0, i32* %21, align 4
  br label %229

229:                                              ; preds = %240, %218
  %230 = load i32, i32* %21, align 4
  %231 = icmp slt i32 %230, 10
  br i1 %231, label %232, label %243

232:                                              ; preds = %229
  %233 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %234 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %233, i32 0, i32 2
  %235 = load i32, i32* %21, align 4
  %236 = sext i32 %235 to i64
  %237 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %234, i64 0, i64 %236
  %238 = load %struct.AsmInput*, %struct.AsmInput** %237, align 8
  %239 = bitcast %struct.AsmInput* %238 to i8*
  call void @free(i8* noundef %239) #7
  br label %240

240:                                              ; preds = %232
  %241 = load i32, i32* %21, align 4
  %242 = add nsw i32 %241, 1
  store i32 %242, i32* %21, align 4
  br label %229, !llvm.loop !11

243:                                              ; preds = %229
  store i32 0, i32* %22, align 4
  br label %244

244:                                              ; preds = %255, %243
  %245 = load i32, i32* %22, align 4
  %246 = icmp slt i32 %245, 10
  br i1 %246, label %247, label %258

247:                                              ; preds = %244
  %248 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %249 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %248, i32 0, i32 1
  %250 = load i32, i32* %22, align 4
  %251 = sext i32 %250 to i64
  %252 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %249, i64 0, i64 %251
  %253 = load %struct.AsmOutput*, %struct.AsmOutput** %252, align 8
  %254 = bitcast %struct.AsmOutput* %253 to i8*
  call void @free(i8* noundef %254) #7
  br label %255

255:                                              ; preds = %247
  %256 = load i32, i32* %22, align 4
  %257 = add nsw i32 %256, 1
  store i32 %257, i32* %22, align 4
  br label %244, !llvm.loop !12

258:                                              ; preds = %244
  store i32 0, i32* %23, align 4
  br label %259

259:                                              ; preds = %270, %258
  %260 = load i32, i32* %23, align 4
  %261 = icmp slt i32 %260, 10
  br i1 %261, label %262, label %273

262:                                              ; preds = %259
  %263 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %264 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %263, i32 0, i32 3
  %265 = load i32, i32* %23, align 4
  %266 = sext i32 %265 to i64
  %267 = getelementptr inbounds [10 x %struct.AsmClobber*], [10 x %struct.AsmClobber*]* %264, i64 0, i64 %266
  %268 = load %struct.AsmClobber*, %struct.AsmClobber** %267, align 8
  %269 = bitcast %struct.AsmClobber* %268 to i8*
  call void @free(i8* noundef %269) #7
  br label %270

270:                                              ; preds = %262
  %271 = load i32, i32* %23, align 4
  %272 = add nsw i32 %271, 1
  store i32 %272, i32* %23, align 4
  br label %259, !llvm.loop !13

273:                                              ; preds = %259
  %274 = load i8*, i8** %12, align 8
  ret i8* %274
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64 noundef, i64 noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @check_template(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = call i8* @strchr(i8* noundef %3, i32 noundef 37) #8
  %5 = icmp ne i8* %4, null
  ret i1 %5
}

declare zeroext i1 @equal(%struct.Token* noundef, i8* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @output_asm(%struct.Node* noundef %0, %struct.Token** noundef %1, %struct.Token* noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token**, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca %struct.VarScope*, align 8
  store %struct.Node* %0, %struct.Node** %5, align 8
  store %struct.Token** %1, %struct.Token*** %6, align 8
  store %struct.Token* %2, %struct.Token** %7, align 8
  br label %10

10:                                               ; preds = %626, %3
  %11 = load %struct.Token*, %struct.Token** %7, align 8
  %12 = getelementptr inbounds %struct.Token, %struct.Token* %11, i32 0, i32 1
  %13 = load %struct.Token*, %struct.Token** %12, align 8
  %14 = call zeroext i1 @equal(%struct.Token* noundef %13, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i64 0, i64 0))
  br i1 %14, label %21, label %15

15:                                               ; preds = %10
  %16 = load %struct.Token*, %struct.Token** %7, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 1
  %18 = load %struct.Token*, %struct.Token** %17, align 8
  %19 = call zeroext i1 @equal(%struct.Token* noundef %18, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i64 0, i64 0))
  %20 = xor i1 %19, true
  br label %21

21:                                               ; preds = %15, %10
  %22 = phi i1 [ false, %10 ], [ %20, %15 ]
  br i1 %22, label %23, label %630

23:                                               ; preds = %21
  %24 = load %struct.Token*, %struct.Token** %7, align 8
  %25 = getelementptr inbounds %struct.Token, %struct.Token* %24, i32 0, i32 0
  %26 = load i32, i32* %25, align 16
  %27 = icmp eq i32 %26, 3
  br i1 %27, label %28, label %335

28:                                               ; preds = %23
  %29 = load %struct.Token*, %struct.Token** %7, align 8
  %30 = getelementptr inbounds %struct.Token, %struct.Token* %29, i32 0, i32 7
  %31 = load i8*, i8** %30, align 8
  %32 = load %struct.Token*, %struct.Token** %7, align 8
  %33 = getelementptr inbounds %struct.Token, %struct.Token* %32, i32 0, i32 5
  %34 = load i32, i32* %33, align 8
  %35 = sext i32 %34 to i64
  %36 = call i32 @strncmp(i8* noundef %31, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.15, i64 0, i64 0), i64 noundef %35) #8
  %37 = icmp ne i32 %36, 0
  br i1 %37, label %38, label %48

38:                                               ; preds = %28
  %39 = load %struct.Token*, %struct.Token** %7, align 8
  %40 = getelementptr inbounds %struct.Token, %struct.Token* %39, i32 0, i32 7
  %41 = load i8*, i8** %40, align 8
  %42 = load %struct.Token*, %struct.Token** %7, align 8
  %43 = getelementptr inbounds %struct.Token, %struct.Token* %42, i32 0, i32 5
  %44 = load i32, i32* %43, align 8
  %45 = sext i32 %44 to i64
  %46 = call i32 @strncmp(i8* noundef %41, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.16, i64 0, i64 0), i64 noundef %45) #8
  %47 = icmp ne i32 %46, 0
  br i1 %47, label %96, label %48

48:                                               ; preds = %38, %28
  %49 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %50 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %49, i32 0, i32 1
  %51 = load i32, i32* @nbOutput, align 4
  %52 = sext i32 %51 to i64
  %53 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %50, i64 0, i64 %52
  %54 = load %struct.AsmOutput*, %struct.AsmOutput** %53, align 8
  %55 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %54, i32 0, i32 7
  store i8 1, i8* %55, align 4
  %56 = load %struct.Token*, %struct.Token** %7, align 8
  %57 = getelementptr inbounds %struct.Token, %struct.Token* %56, i32 0, i32 7
  %58 = load i8*, i8** %57, align 8
  %59 = load %struct.Token*, %struct.Token** %7, align 8
  %60 = getelementptr inbounds %struct.Token, %struct.Token* %59, i32 0, i32 5
  %61 = load i32, i32* %60, align 8
  %62 = sext i32 %61 to i64
  %63 = call i32 @strncmp(i8* noundef %58, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.15, i64 0, i64 0), i64 noundef %62) #8
  %64 = icmp ne i32 %63, 0
  br i1 %64, label %73, label %65

65:                                               ; preds = %48
  %66 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %67 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %66, i32 0, i32 1
  %68 = load i32, i32* @nbOutput, align 4
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %67, i64 0, i64 %69
  %71 = load %struct.AsmOutput*, %struct.AsmOutput** %70, align 8
  %72 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %71, i32 0, i32 2
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.17, i64 0, i64 0), i8** %72, align 8
  br label %81

73:                                               ; preds = %48
  %74 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %75 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %74, i32 0, i32 1
  %76 = load i32, i32* @nbOutput, align 4
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %75, i64 0, i64 %77
  %79 = load %struct.AsmOutput*, %struct.AsmOutput** %78, align 8
  %80 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %79, i32 0, i32 2
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i64 0, i64 0), i8** %80, align 8
  br label %81

81:                                               ; preds = %73, %65
  %82 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %83 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %82, i32 0, i32 1
  %84 = load i32, i32* @nbOutput, align 4
  %85 = sext i32 %84 to i64
  %86 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %83, i64 0, i64 %85
  %87 = load %struct.AsmOutput*, %struct.AsmOutput** %86, align 8
  %88 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %87, i32 0, i32 3
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.19, i64 0, i64 0), i8** %88, align 8
  %89 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %90 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %89, i32 0, i32 1
  %91 = load i32, i32* @nbOutput, align 4
  %92 = sext i32 %91 to i64
  %93 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %90, i64 0, i64 %92
  %94 = load %struct.AsmOutput*, %struct.AsmOutput** %93, align 8
  %95 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %94, i32 0, i32 4
  store i8 114, i8* %95, align 8
  br label %326

96:                                               ; preds = %38
  %97 = load %struct.Token*, %struct.Token** %7, align 8
  %98 = getelementptr inbounds %struct.Token, %struct.Token* %97, i32 0, i32 7
  %99 = load i8*, i8** %98, align 8
  %100 = load %struct.Token*, %struct.Token** %7, align 8
  %101 = getelementptr inbounds %struct.Token, %struct.Token* %100, i32 0, i32 5
  %102 = load i32, i32* %101, align 8
  %103 = sext i32 %102 to i64
  %104 = call i32 @strncmp(i8* noundef %99, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.20, i64 0, i64 0), i64 noundef %103) #8
  %105 = icmp ne i32 %104, 0
  br i1 %105, label %106, label %116

106:                                              ; preds = %96
  %107 = load %struct.Token*, %struct.Token** %7, align 8
  %108 = getelementptr inbounds %struct.Token, %struct.Token* %107, i32 0, i32 7
  %109 = load i8*, i8** %108, align 8
  %110 = load %struct.Token*, %struct.Token** %7, align 8
  %111 = getelementptr inbounds %struct.Token, %struct.Token* %110, i32 0, i32 5
  %112 = load i32, i32* %111, align 8
  %113 = sext i32 %112 to i64
  %114 = call i32 @strncmp(i8* noundef %109, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.21, i64 0, i64 0), i64 noundef %113) #8
  %115 = icmp ne i32 %114, 0
  br i1 %115, label %164, label %116

116:                                              ; preds = %106, %96
  %117 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %118 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %117, i32 0, i32 1
  %119 = load i32, i32* @nbOutput, align 4
  %120 = sext i32 %119 to i64
  %121 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %118, i64 0, i64 %120
  %122 = load %struct.AsmOutput*, %struct.AsmOutput** %121, align 8
  %123 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %122, i32 0, i32 8
  store i8 1, i8* %123, align 1
  %124 = load %struct.Token*, %struct.Token** %7, align 8
  %125 = getelementptr inbounds %struct.Token, %struct.Token* %124, i32 0, i32 7
  %126 = load i8*, i8** %125, align 8
  %127 = load %struct.Token*, %struct.Token** %7, align 8
  %128 = getelementptr inbounds %struct.Token, %struct.Token* %127, i32 0, i32 5
  %129 = load i32, i32* %128, align 8
  %130 = sext i32 %129 to i64
  %131 = call i32 @strncmp(i8* noundef %126, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.20, i64 0, i64 0), i64 noundef %130) #8
  %132 = icmp ne i32 %131, 0
  br i1 %132, label %141, label %133

133:                                              ; preds = %116
  %134 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %135 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %134, i32 0, i32 1
  %136 = load i32, i32* @nbOutput, align 4
  %137 = sext i32 %136 to i64
  %138 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %135, i64 0, i64 %137
  %139 = load %struct.AsmOutput*, %struct.AsmOutput** %138, align 8
  %140 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %139, i32 0, i32 2
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.17, i64 0, i64 0), i8** %140, align 8
  br label %149

141:                                              ; preds = %116
  %142 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %143 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %142, i32 0, i32 1
  %144 = load i32, i32* @nbOutput, align 4
  %145 = sext i32 %144 to i64
  %146 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %143, i64 0, i64 %145
  %147 = load %struct.AsmOutput*, %struct.AsmOutput** %146, align 8
  %148 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %147, i32 0, i32 2
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i64 0, i64 0), i8** %148, align 8
  br label %149

149:                                              ; preds = %141, %133
  %150 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %151 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %150, i32 0, i32 1
  %152 = load i32, i32* @nbOutput, align 4
  %153 = sext i32 %152 to i64
  %154 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %151, i64 0, i64 %153
  %155 = load %struct.AsmOutput*, %struct.AsmOutput** %154, align 8
  %156 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %155, i32 0, i32 3
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.19, i64 0, i64 0), i8** %156, align 8
  %157 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %158 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %157, i32 0, i32 1
  %159 = load i32, i32* @nbOutput, align 4
  %160 = sext i32 %159 to i64
  %161 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %158, i64 0, i64 %160
  %162 = load %struct.AsmOutput*, %struct.AsmOutput** %161, align 8
  %163 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %162, i32 0, i32 4
  store i8 109, i8* %163, align 8
  br label %325

164:                                              ; preds = %106
  %165 = load %struct.Token*, %struct.Token** %7, align 8
  %166 = getelementptr inbounds %struct.Token, %struct.Token* %165, i32 0, i32 7
  %167 = load i8*, i8** %166, align 8
  %168 = load %struct.Token*, %struct.Token** %7, align 8
  %169 = getelementptr inbounds %struct.Token, %struct.Token* %168, i32 0, i32 5
  %170 = load i32, i32* %169, align 8
  %171 = sext i32 %170 to i64
  %172 = call i32 @strncmp(i8* noundef %167, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.22, i64 0, i64 0), i64 noundef %171) #8
  %173 = icmp ne i32 %172, 0
  br i1 %173, label %174, label %204

174:                                              ; preds = %164
  %175 = load %struct.Token*, %struct.Token** %7, align 8
  %176 = getelementptr inbounds %struct.Token, %struct.Token* %175, i32 0, i32 7
  %177 = load i8*, i8** %176, align 8
  %178 = load %struct.Token*, %struct.Token** %7, align 8
  %179 = getelementptr inbounds %struct.Token, %struct.Token* %178, i32 0, i32 5
  %180 = load i32, i32* %179, align 8
  %181 = sext i32 %180 to i64
  %182 = call i32 @strncmp(i8* noundef %177, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.23, i64 0, i64 0), i64 noundef %181) #8
  %183 = icmp ne i32 %182, 0
  br i1 %183, label %184, label %204

184:                                              ; preds = %174
  %185 = load %struct.Token*, %struct.Token** %7, align 8
  %186 = getelementptr inbounds %struct.Token, %struct.Token* %185, i32 0, i32 7
  %187 = load i8*, i8** %186, align 8
  %188 = load %struct.Token*, %struct.Token** %7, align 8
  %189 = getelementptr inbounds %struct.Token, %struct.Token* %188, i32 0, i32 5
  %190 = load i32, i32* %189, align 8
  %191 = sext i32 %190 to i64
  %192 = call i32 @strncmp(i8* noundef %187, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.24, i64 0, i64 0), i64 noundef %191) #8
  %193 = icmp ne i32 %192, 0
  br i1 %193, label %194, label %204

194:                                              ; preds = %184
  %195 = load %struct.Token*, %struct.Token** %7, align 8
  %196 = getelementptr inbounds %struct.Token, %struct.Token* %195, i32 0, i32 7
  %197 = load i8*, i8** %196, align 8
  %198 = load %struct.Token*, %struct.Token** %7, align 8
  %199 = getelementptr inbounds %struct.Token, %struct.Token* %198, i32 0, i32 5
  %200 = load i32, i32* %199, align 8
  %201 = sext i32 %200 to i64
  %202 = call i32 @strncmp(i8* noundef %197, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.25, i64 0, i64 0), i64 noundef %201) #8
  %203 = icmp ne i32 %202, 0
  br i1 %203, label %324, label %204

204:                                              ; preds = %194, %184, %174, %164
  %205 = load %struct.Token*, %struct.Token** %7, align 8
  %206 = getelementptr inbounds %struct.Token, %struct.Token* %205, i32 0, i32 7
  %207 = load i8*, i8** %206, align 8
  %208 = load %struct.Token*, %struct.Token** %7, align 8
  %209 = getelementptr inbounds %struct.Token, %struct.Token* %208, i32 0, i32 5
  %210 = load i32, i32* %209, align 8
  %211 = sext i32 %210 to i64
  %212 = call i32 @strncmp(i8* noundef %207, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.22, i64 0, i64 0), i64 noundef %211) #8
  %213 = icmp ne i32 %212, 0
  br i1 %213, label %229, label %214

214:                                              ; preds = %204
  %215 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %216 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %215, i32 0, i32 1
  %217 = load i32, i32* @nbOutput, align 4
  %218 = sext i32 %217 to i64
  %219 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %216, i64 0, i64 %218
  %220 = load %struct.AsmOutput*, %struct.AsmOutput** %219, align 8
  %221 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %220, i32 0, i32 3
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.19, i64 0, i64 0), i8** %221, align 8
  %222 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %223 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %222, i32 0, i32 1
  %224 = load i32, i32* @nbOutput, align 4
  %225 = sext i32 %224 to i64
  %226 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %223, i64 0, i64 %225
  %227 = load %struct.AsmOutput*, %struct.AsmOutput** %226, align 8
  %228 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %227, i32 0, i32 4
  store i8 97, i8* %228, align 8
  br label %309

229:                                              ; preds = %204
  %230 = load %struct.Token*, %struct.Token** %7, align 8
  %231 = getelementptr inbounds %struct.Token, %struct.Token* %230, i32 0, i32 7
  %232 = load i8*, i8** %231, align 8
  %233 = load %struct.Token*, %struct.Token** %7, align 8
  %234 = getelementptr inbounds %struct.Token, %struct.Token* %233, i32 0, i32 5
  %235 = load i32, i32* %234, align 8
  %236 = sext i32 %235 to i64
  %237 = call i32 @strncmp(i8* noundef %232, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.23, i64 0, i64 0), i64 noundef %236) #8
  %238 = icmp ne i32 %237, 0
  br i1 %238, label %254, label %239

239:                                              ; preds = %229
  %240 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %241 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %240, i32 0, i32 1
  %242 = load i32, i32* @nbOutput, align 4
  %243 = sext i32 %242 to i64
  %244 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %241, i64 0, i64 %243
  %245 = load %struct.AsmOutput*, %struct.AsmOutput** %244, align 8
  %246 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %245, i32 0, i32 3
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.26, i64 0, i64 0), i8** %246, align 8
  %247 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %248 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %247, i32 0, i32 1
  %249 = load i32, i32* @nbOutput, align 4
  %250 = sext i32 %249 to i64
  %251 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %248, i64 0, i64 %250
  %252 = load %struct.AsmOutput*, %struct.AsmOutput** %251, align 8
  %253 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %252, i32 0, i32 4
  store i8 98, i8* %253, align 8
  br label %308

254:                                              ; preds = %229
  %255 = load %struct.Token*, %struct.Token** %7, align 8
  %256 = getelementptr inbounds %struct.Token, %struct.Token* %255, i32 0, i32 7
  %257 = load i8*, i8** %256, align 8
  %258 = load %struct.Token*, %struct.Token** %7, align 8
  %259 = getelementptr inbounds %struct.Token, %struct.Token* %258, i32 0, i32 5
  %260 = load i32, i32* %259, align 8
  %261 = sext i32 %260 to i64
  %262 = call i32 @strncmp(i8* noundef %257, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.24, i64 0, i64 0), i64 noundef %261) #8
  %263 = icmp ne i32 %262, 0
  br i1 %263, label %279, label %264

264:                                              ; preds = %254
  %265 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %266 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %265, i32 0, i32 1
  %267 = load i32, i32* @nbOutput, align 4
  %268 = sext i32 %267 to i64
  %269 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %266, i64 0, i64 %268
  %270 = load %struct.AsmOutput*, %struct.AsmOutput** %269, align 8
  %271 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %270, i32 0, i32 3
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.27, i64 0, i64 0), i8** %271, align 8
  %272 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %273 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %272, i32 0, i32 1
  %274 = load i32, i32* @nbOutput, align 4
  %275 = sext i32 %274 to i64
  %276 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %273, i64 0, i64 %275
  %277 = load %struct.AsmOutput*, %struct.AsmOutput** %276, align 8
  %278 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %277, i32 0, i32 4
  store i8 99, i8* %278, align 8
  br label %307

279:                                              ; preds = %254
  %280 = load %struct.Token*, %struct.Token** %7, align 8
  %281 = getelementptr inbounds %struct.Token, %struct.Token* %280, i32 0, i32 7
  %282 = load i8*, i8** %281, align 8
  %283 = load %struct.Token*, %struct.Token** %7, align 8
  %284 = getelementptr inbounds %struct.Token, %struct.Token* %283, i32 0, i32 5
  %285 = load i32, i32* %284, align 8
  %286 = sext i32 %285 to i64
  %287 = call i32 @strncmp(i8* noundef %282, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.25, i64 0, i64 0), i64 noundef %286) #8
  %288 = icmp ne i32 %287, 0
  br i1 %288, label %304, label %289

289:                                              ; preds = %279
  %290 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %291 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %290, i32 0, i32 1
  %292 = load i32, i32* @nbOutput, align 4
  %293 = sext i32 %292 to i64
  %294 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %291, i64 0, i64 %293
  %295 = load %struct.AsmOutput*, %struct.AsmOutput** %294, align 8
  %296 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %295, i32 0, i32 3
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.28, i64 0, i64 0), i8** %296, align 8
  %297 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %298 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %297, i32 0, i32 1
  %299 = load i32, i32* @nbOutput, align 4
  %300 = sext i32 %299 to i64
  %301 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %298, i64 0, i64 %300
  %302 = load %struct.AsmOutput*, %struct.AsmOutput** %301, align 8
  %303 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %302, i32 0, i32 4
  store i8 100, i8* %303, align 8
  br label %306

304:                                              ; preds = %279
  %305 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %305, i8* noundef getelementptr inbounds ([51 x i8], [51 x i8]* @.str.29, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

306:                                              ; preds = %289
  br label %307

307:                                              ; preds = %306, %264
  br label %308

308:                                              ; preds = %307, %239
  br label %309

309:                                              ; preds = %308, %214
  %310 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %311 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %310, i32 0, i32 1
  %312 = load i32, i32* @nbOutput, align 4
  %313 = sext i32 %312 to i64
  %314 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %311, i64 0, i64 %313
  %315 = load %struct.AsmOutput*, %struct.AsmOutput** %314, align 8
  %316 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %315, i32 0, i32 9
  store i8 1, i8* %316, align 2
  %317 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %318 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %317, i32 0, i32 1
  %319 = load i32, i32* @nbOutput, align 4
  %320 = sext i32 %319 to i64
  %321 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %318, i64 0, i64 %320
  %322 = load %struct.AsmOutput*, %struct.AsmOutput** %321, align 8
  %323 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %322, i32 0, i32 2
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.17, i64 0, i64 0), i8** %323, align 8
  br label %324

324:                                              ; preds = %309, %194
  br label %325

325:                                              ; preds = %324, %149
  br label %326

326:                                              ; preds = %325, %81
  %327 = load i32, i32* @nbOutput, align 4
  %328 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %329 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %328, i32 0, i32 1
  %330 = load i32, i32* @nbOutput, align 4
  %331 = sext i32 %330 to i64
  %332 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %329, i64 0, i64 %331
  %333 = load %struct.AsmOutput*, %struct.AsmOutput** %332, align 8
  %334 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %333, i32 0, i32 5
  store i32 %327, i32* %334, align 4
  br label %626

335:                                              ; preds = %23
  %336 = load %struct.Token*, %struct.Token** %7, align 8
  %337 = call zeroext i1 @equal(%struct.Token* noundef %336, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.30, i64 0, i64 0))
  br i1 %337, label %338, label %341

338:                                              ; preds = %335
  %339 = load %struct.Token*, %struct.Token** %7, align 8
  %340 = call %struct.Token* @skip(%struct.Token* noundef %339, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.30, i64 0, i64 0))
  store %struct.Token* %340, %struct.Token** %7, align 8
  br label %625

341:                                              ; preds = %335
  %342 = load %struct.Token*, %struct.Token** %7, align 8
  %343 = call zeroext i1 @equal(%struct.Token* noundef %342, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.31, i64 0, i64 0))
  br i1 %343, label %344, label %622

344:                                              ; preds = %341
  %345 = load %struct.Token*, %struct.Token** %7, align 8
  %346 = call %struct.Token* @skip(%struct.Token* noundef %345, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.31, i64 0, i64 0))
  store %struct.Token* %346, %struct.Token** %7, align 8
  %347 = load %struct.Token*, %struct.Token** %7, align 8
  %348 = getelementptr inbounds %struct.Token, %struct.Token* %347, i32 0, i32 0
  %349 = load i32, i32* %348, align 16
  %350 = icmp eq i32 %349, 0
  br i1 %350, label %351, label %490

351:                                              ; preds = %344
  %352 = load %struct.Token*, %struct.Token** %7, align 8
  %353 = call %struct.VarScope* @find_var(%struct.Token* noundef %352)
  store %struct.VarScope* %353, %struct.VarScope** %9, align 8
  %354 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %355 = icmp ne %struct.VarScope* %354, null
  br i1 %355, label %358, label %356

356:                                              ; preds = %351
  %357 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %357, i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.32, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

358:                                              ; preds = %351
  %359 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %360 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %359, i32 0, i32 0
  %361 = load %struct.Obj*, %struct.Obj** %360, align 8
  %362 = getelementptr inbounds %struct.Obj, %struct.Obj* %361, i32 0, i32 3
  %363 = load %struct.Type*, %struct.Type** %362, align 8
  %364 = icmp ne %struct.Type* %363, null
  br i1 %364, label %367, label %365

365:                                              ; preds = %358
  %366 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %366, i8* noundef getelementptr inbounds ([52 x i8], [52 x i8]* @.str.33, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

367:                                              ; preds = %358
  %368 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %369 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %368, i32 0, i32 0
  %370 = load %struct.Obj*, %struct.Obj** %369, align 8
  %371 = getelementptr inbounds %struct.Obj, %struct.Obj* %370, i32 0, i32 3
  %372 = load %struct.Type*, %struct.Type** %371, align 8
  %373 = getelementptr inbounds %struct.Type, %struct.Type* %372, i32 0, i32 1
  %374 = load i32, i32* %373, align 4
  %375 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %376 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %375, i32 0, i32 1
  %377 = load i32, i32* @nbOutput, align 4
  %378 = sext i32 %377 to i64
  %379 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %376, i64 0, i64 %378
  %380 = load %struct.AsmOutput*, %struct.AsmOutput** %379, align 8
  %381 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %380, i32 0, i32 6
  store i32 %374, i32* %381, align 8
  %382 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %383 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %382, i32 0, i32 1
  %384 = load i32, i32* @nbOutput, align 4
  %385 = sext i32 %384 to i64
  %386 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %383, i64 0, i64 %385
  %387 = load %struct.AsmOutput*, %struct.AsmOutput** %386, align 8
  %388 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %387, i32 0, i32 11
  store i8 1, i8* %388, align 4
  %389 = load %struct.Token*, %struct.Token** %7, align 8
  %390 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %391 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %390, i32 0, i32 1
  %392 = load i32, i32* @nbOutput, align 4
  %393 = sext i32 %392 to i64
  %394 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %391, i64 0, i64 %393
  %395 = load %struct.AsmOutput*, %struct.AsmOutput** %394, align 8
  %396 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %395, i32 0, i32 0
  store %struct.Token* %389, %struct.Token** %396, align 8
  %397 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %398 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %397, i32 0, i32 0
  %399 = load %struct.Obj*, %struct.Obj** %398, align 8
  %400 = getelementptr inbounds %struct.Obj, %struct.Obj* %399, i32 0, i32 2
  %401 = load i8*, i8** %400, align 8
  %402 = icmp ne i8* %401, null
  br i1 %402, label %403, label %422

403:                                              ; preds = %367
  %404 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %405 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %404, i32 0, i32 0
  %406 = load %struct.Obj*, %struct.Obj** %405, align 8
  %407 = getelementptr inbounds %struct.Obj, %struct.Obj* %406, i32 0, i32 8
  %408 = load i32, i32* %407, align 4
  %409 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %410 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %409, i32 0, i32 0
  %411 = load %struct.Obj*, %struct.Obj** %410, align 8
  %412 = getelementptr inbounds %struct.Obj, %struct.Obj* %411, i32 0, i32 2
  %413 = load i8*, i8** %412, align 8
  %414 = call i32 @retrieve_parameter_order(i32 noundef %408, i8* noundef %413)
  %415 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %416 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %415, i32 0, i32 1
  %417 = load i32, i32* @nbOutput, align 4
  %418 = sext i32 %417 to i64
  %419 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %416, i64 0, i64 %418
  %420 = load %struct.AsmOutput*, %struct.AsmOutput** %419, align 8
  %421 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %420, i32 0, i32 10
  store i32 %414, i32* %421, align 8
  br label %430

422:                                              ; preds = %367
  %423 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %424 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %423, i32 0, i32 1
  %425 = load i32, i32* @nbOutput, align 4
  %426 = sext i32 %425 to i64
  %427 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %424, i64 0, i64 %426
  %428 = load %struct.AsmOutput*, %struct.AsmOutput** %427, align 8
  %429 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %428, i32 0, i32 10
  store i32 0, i32* %429, align 8
  br label %430

430:                                              ; preds = %422, %403
  %431 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %432 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %431, i32 0, i32 1
  %433 = load i32, i32* @nbOutput, align 4
  %434 = sext i32 %433 to i64
  %435 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %432, i64 0, i64 %434
  %436 = load %struct.AsmOutput*, %struct.AsmOutput** %435, align 8
  %437 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %436, i32 0, i32 3
  %438 = load i8*, i8** %437, align 8
  %439 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %440 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %439, i32 0, i32 1
  %441 = load i32, i32* @nbOutput, align 4
  %442 = sext i32 %441 to i64
  %443 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %440, i64 0, i64 %442
  %444 = load %struct.AsmOutput*, %struct.AsmOutput** %443, align 8
  %445 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %444, i32 0, i32 6
  %446 = load i32, i32* %445, align 8
  %447 = call i8* @update_register_size(i8* noundef %438, i32 noundef %446)
  %448 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %449 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %448, i32 0, i32 1
  %450 = load i32, i32* @nbOutput, align 4
  %451 = sext i32 %450 to i64
  %452 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %449, i64 0, i64 %451
  %453 = load %struct.AsmOutput*, %struct.AsmOutput** %452, align 8
  %454 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %453, i32 0, i32 3
  store i8* %447, i8** %454, align 8
  %455 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %456 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %455, i32 0, i32 1
  %457 = load i32, i32* @nbOutput, align 4
  %458 = sext i32 %457 to i64
  %459 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %456, i64 0, i64 %458
  %460 = load %struct.AsmOutput*, %struct.AsmOutput** %459, align 8
  %461 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %460, i32 0, i32 3
  %462 = load i8*, i8** %461, align 8
  %463 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %464 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %463, i32 0, i32 1
  %465 = load i32, i32* @nbOutput, align 4
  %466 = sext i32 %465 to i64
  %467 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %464, i64 0, i64 %466
  %468 = load %struct.AsmOutput*, %struct.AsmOutput** %467, align 8
  %469 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %468, i32 0, i32 1
  store i8* %462, i8** %469, align 8
  %470 = load %struct.Token*, %struct.Token** %7, align 8
  %471 = getelementptr inbounds %struct.Token, %struct.Token* %470, i32 0, i32 1
  %472 = load %struct.Token*, %struct.Token** %471, align 8
  store %struct.Token* %472, %struct.Token** %7, align 8
  %473 = load %struct.Token*, %struct.Token** %7, align 8
  %474 = call %struct.Token* @skip(%struct.Token* noundef %473, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.34, i64 0, i64 0))
  %475 = load %struct.Token**, %struct.Token*** %6, align 8
  store %struct.Token* %474, %struct.Token** %475, align 8
  %476 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %477 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %476, i32 0, i32 1
  %478 = load i32, i32* @nbOutput, align 4
  %479 = sext i32 %478 to i64
  %480 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %477, i64 0, i64 %479
  %481 = load %struct.AsmOutput*, %struct.AsmOutput** %480, align 8
  %482 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %481, i32 0, i32 1
  %483 = load i8*, i8** %482, align 8
  store i8* %483, i8** %8, align 8
  %484 = load i8*, i8** %8, align 8
  %485 = icmp ne i8* %484, null
  br i1 %485, label %488, label %486

486:                                              ; preds = %430
  %487 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %487, i8* noundef getelementptr inbounds ([50 x i8], [50 x i8]* @.str.35, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

488:                                              ; preds = %430
  %489 = load i8*, i8** %8, align 8
  store i8* %489, i8** %4, align 8
  br label %631

490:                                              ; preds = %344
  %491 = load %struct.Token*, %struct.Token** %7, align 8
  %492 = call zeroext i1 @equal(%struct.Token* noundef %491, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.36, i64 0, i64 0))
  br i1 %492, label %493, label %618

493:                                              ; preds = %490
  %494 = load %struct.Token*, %struct.Token** %7, align 8
  %495 = call zeroext i1 @consume(%struct.Token** noundef %7, %struct.Token* noundef %494, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.36, i64 0, i64 0))
  %496 = load %struct.Token*, %struct.Token** %7, align 8
  %497 = getelementptr inbounds %struct.Token, %struct.Token* %496, i32 0, i32 0
  %498 = load i32, i32* %497, align 16
  %499 = icmp eq i32 %498, 0
  br i1 %499, label %500, label %617

500:                                              ; preds = %493
  %501 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %502 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %501, i32 0, i32 1
  %503 = load i32, i32* @nbOutput, align 4
  %504 = sext i32 %503 to i64
  %505 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %502, i64 0, i64 %504
  %506 = load %struct.AsmOutput*, %struct.AsmOutput** %505, align 8
  %507 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %506, i32 0, i32 12
  store i8 1, i8* %507, align 1
  %508 = load %struct.Token*, %struct.Token** %7, align 8
  %509 = call %struct.VarScope* @find_var(%struct.Token* noundef %508)
  store %struct.VarScope* %509, %struct.VarScope** %9, align 8
  %510 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %511 = icmp ne %struct.VarScope* %510, null
  br i1 %511, label %514, label %512

512:                                              ; preds = %500
  %513 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %513, i8* noundef getelementptr inbounds ([50 x i8], [50 x i8]* @.str.37, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

514:                                              ; preds = %500
  %515 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %516 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %515, i32 0, i32 0
  %517 = load %struct.Obj*, %struct.Obj** %516, align 8
  %518 = getelementptr inbounds %struct.Obj, %struct.Obj* %517, i32 0, i32 3
  %519 = load %struct.Type*, %struct.Type** %518, align 8
  %520 = icmp ne %struct.Type* %519, null
  br i1 %520, label %523, label %521

521:                                              ; preds = %514
  %522 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %522, i8* noundef getelementptr inbounds ([53 x i8], [53 x i8]* @.str.38, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

523:                                              ; preds = %514
  %524 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %525 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %524, i32 0, i32 0
  %526 = load %struct.Obj*, %struct.Obj** %525, align 8
  %527 = getelementptr inbounds %struct.Obj, %struct.Obj* %526, i32 0, i32 3
  %528 = load %struct.Type*, %struct.Type** %527, align 8
  %529 = getelementptr inbounds %struct.Type, %struct.Type* %528, i32 0, i32 6
  %530 = load %struct.Type*, %struct.Type** %529, align 8
  %531 = getelementptr inbounds %struct.Type, %struct.Type* %530, i32 0, i32 1
  %532 = load i32, i32* %531, align 4
  %533 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %534 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %533, i32 0, i32 1
  %535 = load i32, i32* @nbOutput, align 4
  %536 = sext i32 %535 to i64
  %537 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %534, i64 0, i64 %536
  %538 = load %struct.AsmOutput*, %struct.AsmOutput** %537, align 8
  %539 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %538, i32 0, i32 6
  store i32 %532, i32* %539, align 8
  %540 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %541 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %540, i32 0, i32 0
  %542 = load %struct.Obj*, %struct.Obj** %541, align 8
  %543 = getelementptr inbounds %struct.Obj, %struct.Obj* %542, i32 0, i32 8
  %544 = load i32, i32* %543, align 4
  %545 = load %struct.VarScope*, %struct.VarScope** %9, align 8
  %546 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %545, i32 0, i32 0
  %547 = load %struct.Obj*, %struct.Obj** %546, align 8
  %548 = getelementptr inbounds %struct.Obj, %struct.Obj* %547, i32 0, i32 2
  %549 = load i8*, i8** %548, align 8
  %550 = call i32 @retrieve_parameter_order(i32 noundef %544, i8* noundef %549)
  %551 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %552 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %551, i32 0, i32 1
  %553 = load i32, i32* @nbOutput, align 4
  %554 = sext i32 %553 to i64
  %555 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %552, i64 0, i64 %554
  %556 = load %struct.AsmOutput*, %struct.AsmOutput** %555, align 8
  %557 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %556, i32 0, i32 10
  store i32 %550, i32* %557, align 8
  %558 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %559 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %558, i32 0, i32 1
  %560 = load i32, i32* @nbOutput, align 4
  %561 = sext i32 %560 to i64
  %562 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %559, i64 0, i64 %561
  %563 = load %struct.AsmOutput*, %struct.AsmOutput** %562, align 8
  %564 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %563, i32 0, i32 3
  %565 = load i8*, i8** %564, align 8
  %566 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %567 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %566, i32 0, i32 1
  %568 = load i32, i32* @nbOutput, align 4
  %569 = sext i32 %568 to i64
  %570 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %567, i64 0, i64 %569
  %571 = load %struct.AsmOutput*, %struct.AsmOutput** %570, align 8
  %572 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %571, i32 0, i32 6
  %573 = load i32, i32* %572, align 8
  %574 = call i8* @update_register_size(i8* noundef %565, i32 noundef %573)
  %575 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %576 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %575, i32 0, i32 1
  %577 = load i32, i32* @nbOutput, align 4
  %578 = sext i32 %577 to i64
  %579 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %576, i64 0, i64 %578
  %580 = load %struct.AsmOutput*, %struct.AsmOutput** %579, align 8
  %581 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %580, i32 0, i32 3
  store i8* %574, i8** %581, align 8
  %582 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %583 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %582, i32 0, i32 1
  %584 = load i32, i32* @nbOutput, align 4
  %585 = sext i32 %584 to i64
  %586 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %583, i64 0, i64 %585
  %587 = load %struct.AsmOutput*, %struct.AsmOutput** %586, align 8
  %588 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %587, i32 0, i32 3
  %589 = load i8*, i8** %588, align 8
  %590 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %591 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %590, i32 0, i32 1
  %592 = load i32, i32* @nbOutput, align 4
  %593 = sext i32 %592 to i64
  %594 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %591, i64 0, i64 %593
  %595 = load %struct.AsmOutput*, %struct.AsmOutput** %594, align 8
  %596 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %595, i32 0, i32 1
  store i8* %589, i8** %596, align 8
  %597 = load %struct.Token*, %struct.Token** %7, align 8
  %598 = getelementptr inbounds %struct.Token, %struct.Token* %597, i32 0, i32 1
  %599 = load %struct.Token*, %struct.Token** %598, align 8
  store %struct.Token* %599, %struct.Token** %7, align 8
  %600 = load %struct.Token*, %struct.Token** %7, align 8
  %601 = call %struct.Token* @skip(%struct.Token* noundef %600, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.34, i64 0, i64 0))
  %602 = load %struct.Token**, %struct.Token*** %6, align 8
  store %struct.Token* %601, %struct.Token** %602, align 8
  %603 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %604 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %603, i32 0, i32 1
  %605 = load i32, i32* @nbOutput, align 4
  %606 = sext i32 %605 to i64
  %607 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %604, i64 0, i64 %606
  %608 = load %struct.AsmOutput*, %struct.AsmOutput** %607, align 8
  %609 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %608, i32 0, i32 1
  %610 = load i8*, i8** %609, align 8
  store i8* %610, i8** %8, align 8
  %611 = load i8*, i8** %8, align 8
  %612 = icmp ne i8* %611, null
  br i1 %612, label %615, label %613

613:                                              ; preds = %523
  %614 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %614, i8* noundef getelementptr inbounds ([51 x i8], [51 x i8]* @.str.39, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

615:                                              ; preds = %523
  %616 = load i8*, i8** %8, align 8
  store i8* %616, i8** %4, align 8
  br label %631

617:                                              ; preds = %493
  br label %620

618:                                              ; preds = %490
  %619 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %619, i8* noundef getelementptr inbounds ([51 x i8], [51 x i8]* @.str.40, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

620:                                              ; preds = %617
  br label %621

621:                                              ; preds = %620
  br label %624

622:                                              ; preds = %341
  %623 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %623, i8* noundef getelementptr inbounds ([65 x i8], [65 x i8]* @.str.41, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

624:                                              ; preds = %621
  br label %625

625:                                              ; preds = %624, %338
  br label %626

626:                                              ; preds = %625, %326
  %627 = load %struct.Token*, %struct.Token** %7, align 8
  %628 = getelementptr inbounds %struct.Token, %struct.Token* %627, i32 0, i32 1
  %629 = load %struct.Token*, %struct.Token** %628, align 8
  store %struct.Token* %629, %struct.Token** %7, align 8
  br label %10, !llvm.loop !14

630:                                              ; preds = %21
  store i8* null, i8** %4, align 8
  br label %631

631:                                              ; preds = %630, %615, %488
  %632 = load i8*, i8** %4, align 8
  ret i8* %632
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @generate_output_asm(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  %5 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 300) #7
  store i8* %5, i8** %4, align 8
  %6 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %7 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %6, i32 0, i32 1
  %8 = load i32, i32* @nbOutput, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %7, i64 0, i64 %9
  %11 = load %struct.AsmOutput*, %struct.AsmOutput** %10, align 8
  %12 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %11, i32 0, i32 11
  %13 = load i8, i8* %12, align 4
  %14 = trunc i8 %13 to i1
  br i1 %14, label %15, label %92

15:                                               ; preds = %1
  %16 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %17 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %16, i32 0, i32 1
  %18 = load i32, i32* @nbOutput, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %17, i64 0, i64 %19
  %21 = load %struct.AsmOutput*, %struct.AsmOutput** %20, align 8
  %22 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %21, i32 0, i32 12
  %23 = load i8, i8* %22, align 1
  %24 = trunc i8 %23 to i1
  br i1 %24, label %92, label %25

25:                                               ; preds = %15
  %26 = load i8*, i8** %4, align 8
  %27 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %28 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %27, i32 0, i32 1
  %29 = load i32, i32* @nbOutput, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %28, i64 0, i64 %30
  %32 = load %struct.AsmOutput*, %struct.AsmOutput** %31, align 8
  %33 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %32, i32 0, i32 6
  %34 = load i32, i32* %33, align 8
  %35 = call i8* @opcode(i32 noundef %34)
  %36 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %37 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %36, i32 0, i32 1
  %38 = load i32, i32* @nbOutput, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %37, i64 0, i64 %39
  %41 = load %struct.AsmOutput*, %struct.AsmOutput** %40, align 8
  %42 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %41, i32 0, i32 6
  %43 = load i32, i32* %42, align 8
  %44 = call i8* @opcode(i32 noundef %43)
  %45 = call i64 @strlen(i8* noundef %44) #8
  %46 = call i8* @strncat(i8* noundef %26, i8* noundef %35, i64 noundef %45) #7
  %47 = load i8*, i8** %4, align 8
  %48 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %49 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %48, i32 0, i32 1
  %50 = load i32, i32* @nbOutput, align 4
  %51 = sext i32 %50 to i64
  %52 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %49, i64 0, i64 %51
  %53 = load %struct.AsmOutput*, %struct.AsmOutput** %52, align 8
  %54 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %53, i32 0, i32 1
  %55 = load i8*, i8** %54, align 8
  %56 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %57 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %56, i32 0, i32 1
  %58 = load i32, i32* @nbOutput, align 4
  %59 = sext i32 %58 to i64
  %60 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %57, i64 0, i64 %59
  %61 = load %struct.AsmOutput*, %struct.AsmOutput** %60, align 8
  %62 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %61, i32 0, i32 1
  %63 = load i8*, i8** %62, align 8
  %64 = call i64 @strlen(i8* noundef %63) #8
  %65 = call i8* @strncat(i8* noundef %47, i8* noundef %55, i64 noundef %64) #7
  %66 = load i8*, i8** %4, align 8
  %67 = call i8* @strncat(i8* noundef %66, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.61, i64 0, i64 0), i64 noundef 3) #7
  %68 = load i8*, i8** %4, align 8
  %69 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %70 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %69, i32 0, i32 1
  %71 = load i32, i32* @nbOutput, align 4
  %72 = sext i32 %71 to i64
  %73 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %70, i64 0, i64 %72
  %74 = load %struct.AsmOutput*, %struct.AsmOutput** %73, align 8
  %75 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %74, i32 0, i32 10
  %76 = load i32, i32* %75, align 8
  %77 = call i8* @load_variable(i32 noundef %76)
  %78 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %79 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %78, i32 0, i32 1
  %80 = load i32, i32* @nbOutput, align 4
  %81 = sext i32 %80 to i64
  %82 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %79, i64 0, i64 %81
  %83 = load %struct.AsmOutput*, %struct.AsmOutput** %82, align 8
  %84 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %83, i32 0, i32 10
  %85 = load i32, i32* %84, align 8
  %86 = call i8* @load_variable(i32 noundef %85)
  %87 = call i64 @strlen(i8* noundef %86) #8
  %88 = call i8* @strncat(i8* noundef %68, i8* noundef %77, i64 noundef %87) #7
  %89 = load i8*, i8** %4, align 8
  %90 = call i8* @strncat(i8* noundef %89, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.62, i64 0, i64 0), i64 noundef 3) #7
  %91 = load i8*, i8** %4, align 8
  store i8* %91, i8** %2, align 8
  br label %240

92:                                               ; preds = %15, %1
  %93 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %94 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %93, i32 0, i32 1
  %95 = load i32, i32* @nbOutput, align 4
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %94, i64 0, i64 %96
  %98 = load %struct.AsmOutput*, %struct.AsmOutput** %97, align 8
  %99 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %98, i32 0, i32 12
  %100 = load i8, i8* %99, align 1
  %101 = trunc i8 %100 to i1
  br i1 %101, label %169, label %102

102:                                              ; preds = %92
  %103 = load i8*, i8** %4, align 8
  %104 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %105 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %104, i32 0, i32 1
  %106 = load i32, i32* @nbOutput, align 4
  %107 = sext i32 %106 to i64
  %108 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %105, i64 0, i64 %107
  %109 = load %struct.AsmOutput*, %struct.AsmOutput** %108, align 8
  %110 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %109, i32 0, i32 6
  %111 = load i32, i32* %110, align 8
  %112 = call i8* @opcode(i32 noundef %111)
  %113 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %114 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %113, i32 0, i32 1
  %115 = load i32, i32* @nbOutput, align 4
  %116 = sext i32 %115 to i64
  %117 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %114, i64 0, i64 %116
  %118 = load %struct.AsmOutput*, %struct.AsmOutput** %117, align 8
  %119 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %118, i32 0, i32 6
  %120 = load i32, i32* %119, align 8
  %121 = call i8* @opcode(i32 noundef %120)
  %122 = call i64 @strlen(i8* noundef %121) #8
  %123 = call i8* @strncat(i8* noundef %103, i8* noundef %112, i64 noundef %122) #7
  %124 = load i8*, i8** %4, align 8
  %125 = call i8* @strncat(i8* noundef %124, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.63, i64 0, i64 0), i64 noundef 3) #7
  %126 = load i8*, i8** %4, align 8
  %127 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %128 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %127, i32 0, i32 2
  %129 = load i32, i32* @nbInput, align 4
  %130 = sext i32 %129 to i64
  %131 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %128, i64 0, i64 %130
  %132 = load %struct.AsmInput*, %struct.AsmInput** %131, align 8
  %133 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %132, i32 0, i32 2
  %134 = load i8*, i8** %133, align 8
  %135 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %136 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %135, i32 0, i32 2
  %137 = load i32, i32* @nbInput, align 4
  %138 = sext i32 %137 to i64
  %139 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %136, i64 0, i64 %138
  %140 = load %struct.AsmInput*, %struct.AsmInput** %139, align 8
  %141 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %140, i32 0, i32 2
  %142 = load i8*, i8** %141, align 8
  %143 = call i64 @strlen(i8* noundef %142) #8
  %144 = call i8* @strncat(i8* noundef %126, i8* noundef %134, i64 noundef %143) #7
  %145 = load i8*, i8** %4, align 8
  %146 = call i8* @strncat(i8* noundef %145, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.61, i64 0, i64 0), i64 noundef 3) #7
  %147 = load i8*, i8** %4, align 8
  %148 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %149 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %148, i32 0, i32 2
  %150 = load i32, i32* @nbInput, align 4
  %151 = sext i32 %150 to i64
  %152 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %149, i64 0, i64 %151
  %153 = load %struct.AsmInput*, %struct.AsmInput** %152, align 8
  %154 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %153, i32 0, i32 1
  %155 = load i8*, i8** %154, align 8
  %156 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %157 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %156, i32 0, i32 2
  %158 = load i32, i32* @nbInput, align 4
  %159 = sext i32 %158 to i64
  %160 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %157, i64 0, i64 %159
  %161 = load %struct.AsmInput*, %struct.AsmInput** %160, align 8
  %162 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %161, i32 0, i32 1
  %163 = load i8*, i8** %162, align 8
  %164 = call i64 @strlen(i8* noundef %163) #8
  %165 = call i8* @strncat(i8* noundef %147, i8* noundef %155, i64 noundef %164) #7
  %166 = load i8*, i8** %4, align 8
  %167 = call i8* @strncat(i8* noundef %166, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.62, i64 0, i64 0), i64 noundef 3) #7
  %168 = load i8*, i8** %4, align 8
  store i8* %168, i8** %2, align 8
  br label %240

169:                                              ; preds = %92
  %170 = load i8*, i8** %4, align 8
  %171 = call i8* @strncat(i8* noundef %170, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.64, i64 0, i64 0), i64 noundef 2) #7
  %172 = load i8*, i8** %4, align 8
  %173 = call i8* @strncat(i8* noundef %172, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.65, i64 0, i64 0), i64 noundef 8) #7
  %174 = load i8*, i8** %4, align 8
  %175 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %176 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %175, i32 0, i32 1
  %177 = load i32, i32* @nbOutput, align 4
  %178 = sext i32 %177 to i64
  %179 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %176, i64 0, i64 %178
  %180 = load %struct.AsmOutput*, %struct.AsmOutput** %179, align 8
  %181 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %180, i32 0, i32 10
  %182 = load i32, i32* %181, align 8
  %183 = call i8* @load_variable(i32 noundef %182)
  %184 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %185 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %184, i32 0, i32 1
  %186 = load i32, i32* @nbOutput, align 4
  %187 = sext i32 %186 to i64
  %188 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %185, i64 0, i64 %187
  %189 = load %struct.AsmOutput*, %struct.AsmOutput** %188, align 8
  %190 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %189, i32 0, i32 10
  %191 = load i32, i32* %190, align 8
  %192 = call i8* @load_variable(i32 noundef %191)
  %193 = call i64 @strlen(i8* noundef %192) #8
  %194 = call i8* @strncat(i8* noundef %174, i8* noundef %183, i64 noundef %193) #7
  %195 = load i8*, i8** %4, align 8
  %196 = call i8* @strncat(i8* noundef %195, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.66, i64 0, i64 0), i64 noundef 8) #7
  %197 = load i8*, i8** %4, align 8
  %198 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %199 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %198, i32 0, i32 1
  %200 = load i32, i32* @nbOutput, align 4
  %201 = sext i32 %200 to i64
  %202 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %199, i64 0, i64 %201
  %203 = load %struct.AsmOutput*, %struct.AsmOutput** %202, align 8
  %204 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %203, i32 0, i32 6
  %205 = load i32, i32* %204, align 8
  %206 = call i8* @opcode(i32 noundef %205)
  %207 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %208 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %207, i32 0, i32 1
  %209 = load i32, i32* @nbOutput, align 4
  %210 = sext i32 %209 to i64
  %211 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %208, i64 0, i64 %210
  %212 = load %struct.AsmOutput*, %struct.AsmOutput** %211, align 8
  %213 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %212, i32 0, i32 6
  %214 = load i32, i32* %213, align 8
  %215 = call i8* @opcode(i32 noundef %214)
  %216 = call i64 @strlen(i8* noundef %215) #8
  %217 = call i8* @strncat(i8* noundef %197, i8* noundef %206, i64 noundef %216) #7
  %218 = load i8*, i8** %4, align 8
  %219 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %220 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %219, i32 0, i32 1
  %221 = load i32, i32* @nbOutput, align 4
  %222 = sext i32 %221 to i64
  %223 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %220, i64 0, i64 %222
  %224 = load %struct.AsmOutput*, %struct.AsmOutput** %223, align 8
  %225 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %224, i32 0, i32 1
  %226 = load i8*, i8** %225, align 8
  %227 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %228 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %227, i32 0, i32 1
  %229 = load i32, i32* @nbOutput, align 4
  %230 = sext i32 %229 to i64
  %231 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %228, i64 0, i64 %230
  %232 = load %struct.AsmOutput*, %struct.AsmOutput** %231, align 8
  %233 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %232, i32 0, i32 1
  %234 = load i8*, i8** %233, align 8
  %235 = call i64 @strlen(i8* noundef %234) #8
  %236 = call i8* @strncat(i8* noundef %218, i8* noundef %226, i64 noundef %235) #7
  %237 = load i8*, i8** %4, align 8
  %238 = call i8* @strncat(i8* noundef %237, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.67, i64 0, i64 0), i64 noundef 10) #7
  %239 = load i8*, i8** %4, align 8
  store i8* %239, i8** %2, align 8
  br label %240

240:                                              ; preds = %169, %102, %25
  %241 = load i8*, i8** %2, align 8
  ret i8* %241
}

; Function Attrs: nounwind
declare i8* @strncat(i8* noundef, i8* noundef, i64 noundef) #1

; Function Attrs: nounwind readonly willreturn
declare i64 @strlen(i8* noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @input_asm(%struct.Node* noundef %0, %struct.Token** noundef %1, %struct.Token* noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token**, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca %struct.VarScope*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i32, align 4
  store %struct.Node* %0, %struct.Node** %5, align 8
  store %struct.Token** %1, %struct.Token*** %6, align 8
  store %struct.Token* %2, %struct.Token** %7, align 8
  %12 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 20) #7
  store i8* %12, i8** %9, align 8
  %13 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 20) #7
  store i8* %13, i8** %10, align 8
  br label %14

14:                                               ; preds = %554, %3
  %15 = load %struct.Token*, %struct.Token** %7, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call zeroext i1 @equal(%struct.Token* noundef %17, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i64 0, i64 0))
  br i1 %18, label %25, label %19

19:                                               ; preds = %14
  %20 = load %struct.Token*, %struct.Token** %7, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 1
  %22 = load %struct.Token*, %struct.Token** %21, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i64 0, i64 0))
  %24 = xor i1 %23, true
  br label %25

25:                                               ; preds = %19, %14
  %26 = phi i1 [ false, %14 ], [ %24, %19 ]
  br i1 %26, label %27, label %558

27:                                               ; preds = %25
  %28 = load %struct.Token*, %struct.Token** %7, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 0
  %30 = load i32, i32* %29, align 16
  %31 = icmp eq i32 %30, 3
  br i1 %31, label %32, label %50

32:                                               ; preds = %27
  %33 = load %struct.Token*, %struct.Token** %7, align 8
  %34 = getelementptr inbounds %struct.Token, %struct.Token* %33, i32 0, i32 7
  %35 = load i8*, i8** %34, align 8
  %36 = load %struct.Token*, %struct.Token** %7, align 8
  %37 = getelementptr inbounds %struct.Token, %struct.Token* %36, i32 0, i32 5
  %38 = load i32, i32* %37, align 8
  %39 = sext i32 %38 to i64
  %40 = call i32 @strncmp(i8* noundef %35, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.42, i64 0, i64 0), i64 noundef %39) #8
  %41 = icmp ne i32 %40, 0
  br i1 %41, label %50, label %42

42:                                               ; preds = %32
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.43, i64 0, i64 0), i8** %9, align 8
  %43 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %44 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %43, i32 0, i32 2
  %45 = load i32, i32* @nbInput, align 4
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %44, i64 0, i64 %46
  %48 = load %struct.AsmInput*, %struct.AsmInput** %47, align 8
  %49 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %48, i32 0, i32 3
  store i32 0, i32* %49, align 8
  br label %554

50:                                               ; preds = %32, %27
  %51 = load %struct.Token*, %struct.Token** %7, align 8
  %52 = getelementptr inbounds %struct.Token, %struct.Token* %51, i32 0, i32 0
  %53 = load i32, i32* %52, align 16
  %54 = icmp eq i32 %53, 3
  br i1 %54, label %55, label %73

55:                                               ; preds = %50
  %56 = load %struct.Token*, %struct.Token** %7, align 8
  %57 = getelementptr inbounds %struct.Token, %struct.Token* %56, i32 0, i32 7
  %58 = load i8*, i8** %57, align 8
  %59 = load %struct.Token*, %struct.Token** %7, align 8
  %60 = getelementptr inbounds %struct.Token, %struct.Token* %59, i32 0, i32 5
  %61 = load i32, i32* %60, align 8
  %62 = sext i32 %61 to i64
  %63 = call i32 @strncmp(i8* noundef %58, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.44, i64 0, i64 0), i64 noundef %62) #8
  %64 = icmp ne i32 %63, 0
  br i1 %64, label %73, label %65

65:                                               ; preds = %55
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.45, i64 0, i64 0), i8** %9, align 8
  %66 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %67 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %66, i32 0, i32 2
  %68 = load i32, i32* @nbInput, align 4
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %67, i64 0, i64 %69
  %71 = load %struct.AsmInput*, %struct.AsmInput** %70, align 8
  %72 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %71, i32 0, i32 3
  store i32 1, i32* %72, align 8
  br label %553

73:                                               ; preds = %55, %50
  %74 = load %struct.Token*, %struct.Token** %7, align 8
  %75 = getelementptr inbounds %struct.Token, %struct.Token* %74, i32 0, i32 0
  %76 = load i32, i32* %75, align 16
  %77 = icmp eq i32 %76, 3
  br i1 %77, label %78, label %96

78:                                               ; preds = %73
  %79 = load %struct.Token*, %struct.Token** %7, align 8
  %80 = getelementptr inbounds %struct.Token, %struct.Token* %79, i32 0, i32 7
  %81 = load i8*, i8** %80, align 8
  %82 = load %struct.Token*, %struct.Token** %7, align 8
  %83 = getelementptr inbounds %struct.Token, %struct.Token* %82, i32 0, i32 5
  %84 = load i32, i32* %83, align 8
  %85 = sext i32 %84 to i64
  %86 = call i32 @strncmp(i8* noundef %81, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.46, i64 0, i64 0), i64 noundef %85) #8
  %87 = icmp ne i32 %86, 0
  br i1 %87, label %96, label %88

88:                                               ; preds = %78
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.47, i64 0, i64 0), i8** %9, align 8
  %89 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %90 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %89, i32 0, i32 2
  %91 = load i32, i32* @nbInput, align 4
  %92 = sext i32 %91 to i64
  %93 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %90, i64 0, i64 %92
  %94 = load %struct.AsmInput*, %struct.AsmInput** %93, align 8
  %95 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %94, i32 0, i32 3
  store i32 2, i32* %95, align 8
  br label %552

96:                                               ; preds = %78, %73
  %97 = load %struct.Token*, %struct.Token** %7, align 8
  %98 = getelementptr inbounds %struct.Token, %struct.Token* %97, i32 0, i32 0
  %99 = load i32, i32* %98, align 16
  %100 = icmp eq i32 %99, 3
  br i1 %100, label %101, label %119

101:                                              ; preds = %96
  %102 = load %struct.Token*, %struct.Token** %7, align 8
  %103 = getelementptr inbounds %struct.Token, %struct.Token* %102, i32 0, i32 7
  %104 = load i8*, i8** %103, align 8
  %105 = load %struct.Token*, %struct.Token** %7, align 8
  %106 = getelementptr inbounds %struct.Token, %struct.Token* %105, i32 0, i32 5
  %107 = load i32, i32* %106, align 8
  %108 = sext i32 %107 to i64
  %109 = call i32 @strncmp(i8* noundef %104, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.48, i64 0, i64 0), i64 noundef %108) #8
  %110 = icmp ne i32 %109, 0
  br i1 %110, label %119, label %111

111:                                              ; preds = %101
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.49, i64 0, i64 0), i8** %9, align 8
  %112 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %113 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %112, i32 0, i32 2
  %114 = load i32, i32* @nbInput, align 4
  %115 = sext i32 %114 to i64
  %116 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %113, i64 0, i64 %115
  %117 = load %struct.AsmInput*, %struct.AsmInput** %116, align 8
  %118 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %117, i32 0, i32 3
  store i32 3, i32* %118, align 8
  br label %551

119:                                              ; preds = %101, %96
  %120 = load %struct.Token*, %struct.Token** %7, align 8
  %121 = getelementptr inbounds %struct.Token, %struct.Token* %120, i32 0, i32 0
  %122 = load i32, i32* %121, align 16
  %123 = icmp eq i32 %122, 3
  br i1 %123, label %124, label %153

124:                                              ; preds = %119
  %125 = load %struct.Token*, %struct.Token** %7, align 8
  %126 = getelementptr inbounds %struct.Token, %struct.Token* %125, i32 0, i32 7
  %127 = load i8*, i8** %126, align 8
  %128 = load %struct.Token*, %struct.Token** %7, align 8
  %129 = getelementptr inbounds %struct.Token, %struct.Token* %128, i32 0, i32 5
  %130 = load i32, i32* %129, align 8
  %131 = sext i32 %130 to i64
  %132 = call i32 @strncmp(i8* noundef %127, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.50, i64 0, i64 0), i64 noundef %131) #8
  %133 = icmp ne i32 %132, 0
  br i1 %133, label %153, label %134

134:                                              ; preds = %124
  %135 = call i8* @retrieve_output_index_str(i8 noundef signext 97)
  store i8* %135, i8** %9, align 8
  %136 = load i32, i32* @nbOutput, align 4
  %137 = load i32, i32* @nbInput, align 4
  %138 = add nsw i32 %136, %137
  %139 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %140 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %139, i32 0, i32 2
  %141 = load i32, i32* @nbInput, align 4
  %142 = sext i32 %141 to i64
  %143 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %140, i64 0, i64 %142
  %144 = load %struct.AsmInput*, %struct.AsmInput** %143, align 8
  %145 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %144, i32 0, i32 3
  store i32 %138, i32* %145, align 8
  %146 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %147 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %146, i32 0, i32 2
  %148 = load i32, i32* @nbInput, align 4
  %149 = sext i32 %148 to i64
  %150 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %147, i64 0, i64 %149
  %151 = load %struct.AsmInput*, %struct.AsmInput** %150, align 8
  %152 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %151, i32 0, i32 4
  store i8 97, i8* %152, align 4
  br label %550

153:                                              ; preds = %124, %119
  %154 = load %struct.Token*, %struct.Token** %7, align 8
  %155 = getelementptr inbounds %struct.Token, %struct.Token* %154, i32 0, i32 0
  %156 = load i32, i32* %155, align 16
  %157 = icmp eq i32 %156, 3
  br i1 %157, label %158, label %187

158:                                              ; preds = %153
  %159 = load %struct.Token*, %struct.Token** %7, align 8
  %160 = getelementptr inbounds %struct.Token, %struct.Token* %159, i32 0, i32 7
  %161 = load i8*, i8** %160, align 8
  %162 = load %struct.Token*, %struct.Token** %7, align 8
  %163 = getelementptr inbounds %struct.Token, %struct.Token* %162, i32 0, i32 5
  %164 = load i32, i32* %163, align 8
  %165 = sext i32 %164 to i64
  %166 = call i32 @strncmp(i8* noundef %161, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.51, i64 0, i64 0), i64 noundef %165) #8
  %167 = icmp ne i32 %166, 0
  br i1 %167, label %187, label %168

168:                                              ; preds = %158
  %169 = call i8* @retrieve_output_index_str(i8 noundef signext 98)
  store i8* %169, i8** %9, align 8
  %170 = load i32, i32* @nbOutput, align 4
  %171 = load i32, i32* @nbInput, align 4
  %172 = add nsw i32 %170, %171
  %173 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %174 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %173, i32 0, i32 2
  %175 = load i32, i32* @nbInput, align 4
  %176 = sext i32 %175 to i64
  %177 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %174, i64 0, i64 %176
  %178 = load %struct.AsmInput*, %struct.AsmInput** %177, align 8
  %179 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %178, i32 0, i32 3
  store i32 %172, i32* %179, align 8
  %180 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %181 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %180, i32 0, i32 2
  %182 = load i32, i32* @nbInput, align 4
  %183 = sext i32 %182 to i64
  %184 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %181, i64 0, i64 %183
  %185 = load %struct.AsmInput*, %struct.AsmInput** %184, align 8
  %186 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %185, i32 0, i32 4
  store i8 98, i8* %186, align 4
  br label %549

187:                                              ; preds = %158, %153
  %188 = load %struct.Token*, %struct.Token** %7, align 8
  %189 = getelementptr inbounds %struct.Token, %struct.Token* %188, i32 0, i32 0
  %190 = load i32, i32* %189, align 16
  %191 = icmp eq i32 %190, 3
  br i1 %191, label %192, label %221

192:                                              ; preds = %187
  %193 = load %struct.Token*, %struct.Token** %7, align 8
  %194 = getelementptr inbounds %struct.Token, %struct.Token* %193, i32 0, i32 7
  %195 = load i8*, i8** %194, align 8
  %196 = load %struct.Token*, %struct.Token** %7, align 8
  %197 = getelementptr inbounds %struct.Token, %struct.Token* %196, i32 0, i32 5
  %198 = load i32, i32* %197, align 8
  %199 = sext i32 %198 to i64
  %200 = call i32 @strncmp(i8* noundef %195, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.52, i64 0, i64 0), i64 noundef %199) #8
  %201 = icmp ne i32 %200, 0
  br i1 %201, label %221, label %202

202:                                              ; preds = %192
  %203 = call i8* @retrieve_output_index_str(i8 noundef signext 99)
  store i8* %203, i8** %9, align 8
  %204 = load i32, i32* @nbOutput, align 4
  %205 = load i32, i32* @nbInput, align 4
  %206 = add nsw i32 %204, %205
  %207 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %208 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %207, i32 0, i32 2
  %209 = load i32, i32* @nbInput, align 4
  %210 = sext i32 %209 to i64
  %211 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %208, i64 0, i64 %210
  %212 = load %struct.AsmInput*, %struct.AsmInput** %211, align 8
  %213 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %212, i32 0, i32 3
  store i32 %206, i32* %213, align 8
  %214 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %215 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %214, i32 0, i32 2
  %216 = load i32, i32* @nbInput, align 4
  %217 = sext i32 %216 to i64
  %218 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %215, i64 0, i64 %217
  %219 = load %struct.AsmInput*, %struct.AsmInput** %218, align 8
  %220 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %219, i32 0, i32 4
  store i8 99, i8* %220, align 4
  br label %548

221:                                              ; preds = %192, %187
  %222 = load %struct.Token*, %struct.Token** %7, align 8
  %223 = getelementptr inbounds %struct.Token, %struct.Token* %222, i32 0, i32 0
  %224 = load i32, i32* %223, align 16
  %225 = icmp eq i32 %224, 3
  br i1 %225, label %226, label %255

226:                                              ; preds = %221
  %227 = load %struct.Token*, %struct.Token** %7, align 8
  %228 = getelementptr inbounds %struct.Token, %struct.Token* %227, i32 0, i32 7
  %229 = load i8*, i8** %228, align 8
  %230 = load %struct.Token*, %struct.Token** %7, align 8
  %231 = getelementptr inbounds %struct.Token, %struct.Token* %230, i32 0, i32 5
  %232 = load i32, i32* %231, align 8
  %233 = sext i32 %232 to i64
  %234 = call i32 @strncmp(i8* noundef %229, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.53, i64 0, i64 0), i64 noundef %233) #8
  %235 = icmp ne i32 %234, 0
  br i1 %235, label %255, label %236

236:                                              ; preds = %226
  %237 = call i8* @retrieve_output_index_str(i8 noundef signext 100)
  store i8* %237, i8** %9, align 8
  %238 = load i32, i32* @nbOutput, align 4
  %239 = load i32, i32* @nbInput, align 4
  %240 = add nsw i32 %238, %239
  %241 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %242 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %241, i32 0, i32 2
  %243 = load i32, i32* @nbInput, align 4
  %244 = sext i32 %243 to i64
  %245 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %242, i64 0, i64 %244
  %246 = load %struct.AsmInput*, %struct.AsmInput** %245, align 8
  %247 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %246, i32 0, i32 3
  store i32 %240, i32* %247, align 8
  %248 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %249 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %248, i32 0, i32 2
  %250 = load i32, i32* @nbInput, align 4
  %251 = sext i32 %250 to i64
  %252 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %249, i64 0, i64 %251
  %253 = load %struct.AsmInput*, %struct.AsmInput** %252, align 8
  %254 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %253, i32 0, i32 4
  store i8 100, i8* %254, align 4
  br label %547

255:                                              ; preds = %226, %221
  %256 = load %struct.Token*, %struct.Token** %7, align 8
  %257 = getelementptr inbounds %struct.Token, %struct.Token* %256, i32 0, i32 0
  %258 = load i32, i32* %257, align 16
  %259 = icmp eq i32 %258, 3
  br i1 %259, label %260, label %289

260:                                              ; preds = %255
  %261 = load %struct.Token*, %struct.Token** %7, align 8
  %262 = getelementptr inbounds %struct.Token, %struct.Token* %261, i32 0, i32 7
  %263 = load i8*, i8** %262, align 8
  %264 = load %struct.Token*, %struct.Token** %7, align 8
  %265 = getelementptr inbounds %struct.Token, %struct.Token* %264, i32 0, i32 5
  %266 = load i32, i32* %265, align 8
  %267 = sext i32 %266 to i64
  %268 = call i32 @strncmp(i8* noundef %263, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.54, i64 0, i64 0), i64 noundef %267) #8
  %269 = icmp ne i32 %268, 0
  br i1 %269, label %289, label %270

270:                                              ; preds = %260
  %271 = call i8* @retrieve_output_index_str(i8 noundef signext 109)
  store i8* %271, i8** %9, align 8
  %272 = load i32, i32* @nbOutput, align 4
  %273 = load i32, i32* @nbInput, align 4
  %274 = add nsw i32 %272, %273
  %275 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %276 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %275, i32 0, i32 2
  %277 = load i32, i32* @nbInput, align 4
  %278 = sext i32 %277 to i64
  %279 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %276, i64 0, i64 %278
  %280 = load %struct.AsmInput*, %struct.AsmInput** %279, align 8
  %281 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %280, i32 0, i32 3
  store i32 %274, i32* %281, align 8
  %282 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %283 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %282, i32 0, i32 2
  %284 = load i32, i32* @nbInput, align 4
  %285 = sext i32 %284 to i64
  %286 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %283, i64 0, i64 %285
  %287 = load %struct.AsmInput*, %struct.AsmInput** %286, align 8
  %288 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %287, i32 0, i32 4
  store i8 109, i8* %288, align 4
  br label %546

289:                                              ; preds = %260, %255
  %290 = load %struct.Token*, %struct.Token** %7, align 8
  %291 = getelementptr inbounds %struct.Token, %struct.Token* %290, i32 0, i32 0
  %292 = load i32, i32* %291, align 16
  %293 = icmp eq i32 %292, 3
  br i1 %293, label %294, label %323

294:                                              ; preds = %289
  %295 = load %struct.Token*, %struct.Token** %7, align 8
  %296 = getelementptr inbounds %struct.Token, %struct.Token* %295, i32 0, i32 7
  %297 = load i8*, i8** %296, align 8
  %298 = load %struct.Token*, %struct.Token** %7, align 8
  %299 = getelementptr inbounds %struct.Token, %struct.Token* %298, i32 0, i32 5
  %300 = load i32, i32* %299, align 8
  %301 = sext i32 %300 to i64
  %302 = call i32 @strncmp(i8* noundef %297, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.55, i64 0, i64 0), i64 noundef %301) #8
  %303 = icmp ne i32 %302, 0
  br i1 %303, label %323, label %304

304:                                              ; preds = %294
  %305 = call i8* @retrieve_output_index_str(i8 noundef signext 114)
  store i8* %305, i8** %9, align 8
  %306 = load i32, i32* @nbOutput, align 4
  %307 = load i32, i32* @nbInput, align 4
  %308 = add nsw i32 %306, %307
  %309 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %310 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %309, i32 0, i32 2
  %311 = load i32, i32* @nbInput, align 4
  %312 = sext i32 %311 to i64
  %313 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %310, i64 0, i64 %312
  %314 = load %struct.AsmInput*, %struct.AsmInput** %313, align 8
  %315 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %314, i32 0, i32 3
  store i32 %308, i32* %315, align 8
  %316 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %317 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %316, i32 0, i32 2
  %318 = load i32, i32* @nbInput, align 4
  %319 = sext i32 %318 to i64
  %320 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %317, i64 0, i64 %319
  %321 = load %struct.AsmInput*, %struct.AsmInput** %320, align 8
  %322 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %321, i32 0, i32 4
  store i8 114, i8* %322, align 4
  br label %545

323:                                              ; preds = %294, %289
  %324 = load %struct.Token*, %struct.Token** %7, align 8
  %325 = call zeroext i1 @equal(%struct.Token* noundef %324, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.31, i64 0, i64 0))
  br i1 %325, label %326, label %535

326:                                              ; preds = %323
  %327 = load %struct.Token*, %struct.Token** %7, align 8
  %328 = call %struct.Token* @skip(%struct.Token* noundef %327, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.31, i64 0, i64 0))
  store %struct.Token* %328, %struct.Token** %7, align 8
  %329 = load %struct.Token*, %struct.Token** %7, align 8
  %330 = getelementptr inbounds %struct.Token, %struct.Token* %329, i32 0, i32 0
  %331 = load i32, i32* %330, align 16
  %332 = icmp eq i32 %331, 0
  br i1 %332, label %333, label %385

333:                                              ; preds = %326
  %334 = load %struct.Token*, %struct.Token** %7, align 8
  %335 = call %struct.VarScope* @find_var(%struct.Token* noundef %334)
  store %struct.VarScope* %335, %struct.VarScope** %8, align 8
  %336 = load %struct.VarScope*, %struct.VarScope** %8, align 8
  %337 = icmp ne %struct.VarScope* %336, null
  br i1 %337, label %340, label %338

338:                                              ; preds = %333
  %339 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %339, i8* noundef getelementptr inbounds ([48 x i8], [48 x i8]* @.str.56, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

340:                                              ; preds = %333
  %341 = load %struct.Token*, %struct.Token** %7, align 8
  %342 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %343 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %342, i32 0, i32 2
  %344 = load i32, i32* @nbInput, align 4
  %345 = sext i32 %344 to i64
  %346 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %343, i64 0, i64 %345
  %347 = load %struct.AsmInput*, %struct.AsmInput** %346, align 8
  %348 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %347, i32 0, i32 0
  store %struct.Token* %341, %struct.Token** %348, align 8
  %349 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %350 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %349, i32 0, i32 2
  %351 = load i32, i32* @nbInput, align 4
  %352 = sext i32 %351 to i64
  %353 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %350, i64 0, i64 %352
  %354 = load %struct.AsmInput*, %struct.AsmInput** %353, align 8
  %355 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %354, i32 0, i32 7
  store i8 1, i8* %355, align 8
  %356 = load i8*, i8** %9, align 8
  %357 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %358 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %357, i32 0, i32 2
  %359 = load i32, i32* @nbInput, align 4
  %360 = sext i32 %359 to i64
  %361 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %358, i64 0, i64 %360
  %362 = load %struct.AsmInput*, %struct.AsmInput** %361, align 8
  %363 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %362, i32 0, i32 1
  store i8* %356, i8** %363, align 8
  %364 = load %struct.VarScope*, %struct.VarScope** %8, align 8
  %365 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %364, i32 0, i32 0
  %366 = load %struct.Obj*, %struct.Obj** %365, align 8
  %367 = getelementptr inbounds %struct.Obj, %struct.Obj* %366, i32 0, i32 3
  %368 = load %struct.Type*, %struct.Type** %367, align 8
  %369 = getelementptr inbounds %struct.Type, %struct.Type* %368, i32 0, i32 1
  %370 = load i32, i32* %369, align 4
  %371 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %372 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %371, i32 0, i32 2
  %373 = load i32, i32* @nbInput, align 4
  %374 = sext i32 %373 to i64
  %375 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %372, i64 0, i64 %374
  %376 = load %struct.AsmInput*, %struct.AsmInput** %375, align 8
  %377 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %376, i32 0, i32 6
  store i32 %370, i32* %377, align 4
  %378 = load %struct.Token*, %struct.Token** %7, align 8
  %379 = getelementptr inbounds %struct.Token, %struct.Token* %378, i32 0, i32 1
  %380 = load %struct.Token*, %struct.Token** %379, align 8
  store %struct.Token* %380, %struct.Token** %7, align 8
  %381 = load %struct.Token*, %struct.Token** %7, align 8
  %382 = call %struct.Token* @skip(%struct.Token* noundef %381, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.34, i64 0, i64 0))
  %383 = load %struct.Token**, %struct.Token*** %6, align 8
  store %struct.Token* %382, %struct.Token** %383, align 8
  %384 = load i8*, i8** %9, align 8
  store i8* %384, i8** %4, align 8
  br label %559

385:                                              ; preds = %326
  %386 = load %struct.Token*, %struct.Token** %7, align 8
  %387 = getelementptr inbounds %struct.Token, %struct.Token* %386, i32 0, i32 0
  %388 = load i32, i32* %387, align 16
  %389 = icmp eq i32 %388, 4
  br i1 %389, label %390, label %462

390:                                              ; preds = %385
  %391 = load %struct.Token*, %struct.Token** %7, align 8
  %392 = getelementptr inbounds %struct.Token, %struct.Token* %391, i32 0, i32 2
  %393 = load i64, i64* %392, align 16
  %394 = call i32 (i8*, i64, i8*, ...) @snprintf(i8* noundef null, i64 noundef 0, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.57, i64 0, i64 0), i64 noundef %393) #7
  store i32 %394, i32* %11, align 4
  %395 = load %struct.Token*, %struct.Token** %7, align 8
  %396 = getelementptr inbounds %struct.Token, %struct.Token* %395, i32 0, i32 2
  %397 = load i64, i64* %396, align 16
  %398 = icmp eq i64 %397, 0
  br i1 %398, label %399, label %402

399:                                              ; preds = %390
  %400 = load i8*, i8** %10, align 8
  %401 = call i8* @strncat(i8* noundef %400, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.58, i64 0, i64 0), i64 noundef 3) #7
  br label %411

402:                                              ; preds = %390
  %403 = load i8*, i8** %10, align 8
  %404 = load i32, i32* %11, align 4
  %405 = add nsw i32 %404, 1
  %406 = sext i32 %405 to i64
  %407 = load %struct.Token*, %struct.Token** %7, align 8
  %408 = getelementptr inbounds %struct.Token, %struct.Token* %407, i32 0, i32 2
  %409 = load i64, i64* %408, align 16
  %410 = call i32 (i8*, i64, i8*, ...) @snprintf(i8* noundef %403, i64 noundef %406, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.57, i64 0, i64 0), i64 noundef %409) #7
  br label %411

411:                                              ; preds = %402, %399
  %412 = load %struct.Token*, %struct.Token** %7, align 8
  %413 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %414 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %413, i32 0, i32 2
  %415 = load i32, i32* @nbInput, align 4
  %416 = sext i32 %415 to i64
  %417 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %414, i64 0, i64 %416
  %418 = load %struct.AsmInput*, %struct.AsmInput** %417, align 8
  %419 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %418, i32 0, i32 0
  store %struct.Token* %412, %struct.Token** %419, align 8
  %420 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %421 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %420, i32 0, i32 2
  %422 = load i32, i32* @nbInput, align 4
  %423 = sext i32 %422 to i64
  %424 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %421, i64 0, i64 %423
  %425 = load %struct.AsmInput*, %struct.AsmInput** %424, align 8
  %426 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %425, i32 0, i32 7
  store i8 0, i8* %426, align 8
  %427 = load i8*, i8** %9, align 8
  %428 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %429 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %428, i32 0, i32 2
  %430 = load i32, i32* @nbInput, align 4
  %431 = sext i32 %430 to i64
  %432 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %429, i64 0, i64 %431
  %433 = load %struct.AsmInput*, %struct.AsmInput** %432, align 8
  %434 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %433, i32 0, i32 1
  store i8* %427, i8** %434, align 8
  %435 = load i8*, i8** %10, align 8
  %436 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %437 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %436, i32 0, i32 2
  %438 = load i32, i32* @nbInput, align 4
  %439 = sext i32 %438 to i64
  %440 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %437, i64 0, i64 %439
  %441 = load %struct.AsmInput*, %struct.AsmInput** %440, align 8
  %442 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %441, i32 0, i32 2
  store i8* %435, i8** %442, align 8
  %443 = load %struct.Token*, %struct.Token** %7, align 8
  %444 = getelementptr inbounds %struct.Token, %struct.Token* %443, i32 0, i32 6
  %445 = load %struct.Type*, %struct.Type** %444, align 16
  %446 = getelementptr inbounds %struct.Type, %struct.Type* %445, i32 0, i32 1
  %447 = load i32, i32* %446, align 4
  %448 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %449 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %448, i32 0, i32 2
  %450 = load i32, i32* @nbInput, align 4
  %451 = sext i32 %450 to i64
  %452 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %449, i64 0, i64 %451
  %453 = load %struct.AsmInput*, %struct.AsmInput** %452, align 8
  %454 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %453, i32 0, i32 6
  store i32 %447, i32* %454, align 4
  %455 = load %struct.Token*, %struct.Token** %7, align 8
  %456 = getelementptr inbounds %struct.Token, %struct.Token* %455, i32 0, i32 1
  %457 = load %struct.Token*, %struct.Token** %456, align 8
  store %struct.Token* %457, %struct.Token** %7, align 8
  %458 = load %struct.Token*, %struct.Token** %7, align 8
  %459 = call %struct.Token* @skip(%struct.Token* noundef %458, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.34, i64 0, i64 0))
  %460 = load %struct.Token**, %struct.Token*** %6, align 8
  store %struct.Token* %459, %struct.Token** %460, align 8
  %461 = load i8*, i8** %9, align 8
  store i8* %461, i8** %4, align 8
  br label %559

462:                                              ; preds = %385
  %463 = load %struct.Token*, %struct.Token** %7, align 8
  %464 = call zeroext i1 @equal(%struct.Token* noundef %463, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.36, i64 0, i64 0))
  br i1 %464, label %465, label %532

465:                                              ; preds = %462
  %466 = load %struct.Token*, %struct.Token** %7, align 8
  %467 = call zeroext i1 @consume(%struct.Token** noundef %7, %struct.Token* noundef %466, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.36, i64 0, i64 0))
  %468 = load %struct.Token*, %struct.Token** %7, align 8
  %469 = getelementptr inbounds %struct.Token, %struct.Token* %468, i32 0, i32 0
  %470 = load i32, i32* %469, align 16
  %471 = icmp eq i32 %470, 0
  br i1 %471, label %472, label %531

472:                                              ; preds = %465
  %473 = load %struct.Token*, %struct.Token** %7, align 8
  %474 = call %struct.VarScope* @find_var(%struct.Token* noundef %473)
  store %struct.VarScope* %474, %struct.VarScope** %8, align 8
  %475 = load %struct.VarScope*, %struct.VarScope** %8, align 8
  %476 = icmp ne %struct.VarScope* %475, null
  br i1 %476, label %479, label %477

477:                                              ; preds = %472
  %478 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %478, i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.59, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

479:                                              ; preds = %472
  %480 = load %struct.Token*, %struct.Token** %7, align 8
  %481 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %482 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %481, i32 0, i32 2
  %483 = load i32, i32* @nbInput, align 4
  %484 = sext i32 %483 to i64
  %485 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %482, i64 0, i64 %484
  %486 = load %struct.AsmInput*, %struct.AsmInput** %485, align 8
  %487 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %486, i32 0, i32 0
  store %struct.Token* %480, %struct.Token** %487, align 8
  %488 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %489 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %488, i32 0, i32 2
  %490 = load i32, i32* @nbInput, align 4
  %491 = sext i32 %490 to i64
  %492 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %489, i64 0, i64 %491
  %493 = load %struct.AsmInput*, %struct.AsmInput** %492, align 8
  %494 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %493, i32 0, i32 7
  store i8 1, i8* %494, align 8
  %495 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %496 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %495, i32 0, i32 2
  %497 = load i32, i32* @nbInput, align 4
  %498 = sext i32 %497 to i64
  %499 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %496, i64 0, i64 %498
  %500 = load %struct.AsmInput*, %struct.AsmInput** %499, align 8
  %501 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %500, i32 0, i32 8
  store i8 1, i8* %501, align 1
  %502 = load i8*, i8** %9, align 8
  %503 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %504 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %503, i32 0, i32 2
  %505 = load i32, i32* @nbInput, align 4
  %506 = sext i32 %505 to i64
  %507 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %504, i64 0, i64 %506
  %508 = load %struct.AsmInput*, %struct.AsmInput** %507, align 8
  %509 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %508, i32 0, i32 1
  store i8* %502, i8** %509, align 8
  %510 = load %struct.VarScope*, %struct.VarScope** %8, align 8
  %511 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %510, i32 0, i32 0
  %512 = load %struct.Obj*, %struct.Obj** %511, align 8
  %513 = getelementptr inbounds %struct.Obj, %struct.Obj* %512, i32 0, i32 3
  %514 = load %struct.Type*, %struct.Type** %513, align 8
  %515 = getelementptr inbounds %struct.Type, %struct.Type* %514, i32 0, i32 1
  %516 = load i32, i32* %515, align 4
  %517 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %518 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %517, i32 0, i32 2
  %519 = load i32, i32* @nbInput, align 4
  %520 = sext i32 %519 to i64
  %521 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %518, i64 0, i64 %520
  %522 = load %struct.AsmInput*, %struct.AsmInput** %521, align 8
  %523 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %522, i32 0, i32 6
  store i32 %516, i32* %523, align 4
  %524 = load %struct.Token*, %struct.Token** %7, align 8
  %525 = getelementptr inbounds %struct.Token, %struct.Token* %524, i32 0, i32 1
  %526 = load %struct.Token*, %struct.Token** %525, align 8
  store %struct.Token* %526, %struct.Token** %7, align 8
  %527 = load %struct.Token*, %struct.Token** %7, align 8
  %528 = call %struct.Token* @skip(%struct.Token* noundef %527, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.34, i64 0, i64 0))
  %529 = load %struct.Token**, %struct.Token*** %6, align 8
  store %struct.Token* %528, %struct.Token** %529, align 8
  %530 = load i8*, i8** %9, align 8
  store i8* %530, i8** %4, align 8
  br label %559

531:                                              ; preds = %465
  br label %532

532:                                              ; preds = %531, %462
  br label %533

533:                                              ; preds = %532
  br label %534

534:                                              ; preds = %533
  br label %544

535:                                              ; preds = %323
  %536 = load %struct.Token*, %struct.Token** %7, align 8
  %537 = call zeroext i1 @equal(%struct.Token* noundef %536, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.30, i64 0, i64 0))
  br i1 %537, label %538, label %541

538:                                              ; preds = %535
  %539 = load %struct.Token*, %struct.Token** %7, align 8
  %540 = call %struct.Token* @skip(%struct.Token* noundef %539, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.30, i64 0, i64 0))
  store %struct.Token* %540, %struct.Token** %7, align 8
  br label %543

541:                                              ; preds = %535
  %542 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %542, i8* noundef getelementptr inbounds ([71 x i8], [71 x i8]* @.str.60, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

543:                                              ; preds = %538
  br label %544

544:                                              ; preds = %543, %534
  br label %545

545:                                              ; preds = %544, %304
  br label %546

546:                                              ; preds = %545, %270
  br label %547

547:                                              ; preds = %546, %236
  br label %548

548:                                              ; preds = %547, %202
  br label %549

549:                                              ; preds = %548, %168
  br label %550

550:                                              ; preds = %549, %134
  br label %551

551:                                              ; preds = %550, %111
  br label %552

552:                                              ; preds = %551, %88
  br label %553

553:                                              ; preds = %552, %65
  br label %554

554:                                              ; preds = %553, %42
  %555 = load %struct.Token*, %struct.Token** %7, align 8
  %556 = getelementptr inbounds %struct.Token, %struct.Token* %555, i32 0, i32 1
  %557 = load %struct.Token*, %struct.Token** %556, align 8
  store %struct.Token* %557, %struct.Token** %7, align 8
  br label %14, !llvm.loop !15

558:                                              ; preds = %25
  store i8* null, i8** %4, align 8
  br label %559

559:                                              ; preds = %558, %479, %411, %340
  %560 = load i8*, i8** %4, align 8
  ret i8* %560
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @generate_input_asm(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  %5 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 100) #7
  store i8* %5, i8** %4, align 8
  %6 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %7 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %6, i32 0, i32 2
  %8 = load i32, i32* @nbInput, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %7, i64 0, i64 %9
  %11 = load %struct.AsmInput*, %struct.AsmInput** %10, align 8
  %12 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %11, i32 0, i32 7
  %13 = load i8, i8* %12, align 8
  %14 = trunc i8 %13 to i1
  br i1 %14, label %15, label %82

15:                                               ; preds = %1
  %16 = load i8*, i8** %4, align 8
  %17 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %18 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %17, i32 0, i32 2
  %19 = load i32, i32* @nbInput, align 4
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %18, i64 0, i64 %20
  %22 = load %struct.AsmInput*, %struct.AsmInput** %21, align 8
  %23 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %22, i32 0, i32 6
  %24 = load i32, i32* %23, align 4
  %25 = call i8* @opcode(i32 noundef %24)
  %26 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %27 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %26, i32 0, i32 2
  %28 = load i32, i32* @nbInput, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %27, i64 0, i64 %29
  %31 = load %struct.AsmInput*, %struct.AsmInput** %30, align 8
  %32 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %31, i32 0, i32 6
  %33 = load i32, i32* %32, align 4
  %34 = call i8* @opcode(i32 noundef %33)
  %35 = call i64 @strlen(i8* noundef %34) #8
  %36 = call i8* @strncat(i8* noundef %16, i8* noundef %25, i64 noundef %35) #7
  %37 = load i8*, i8** %4, align 8
  %38 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %39 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %38, i32 0, i32 2
  %40 = load i32, i32* @nbInput, align 4
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %39, i64 0, i64 %41
  %43 = load %struct.AsmInput*, %struct.AsmInput** %42, align 8
  %44 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %43, i32 0, i32 5
  %45 = load i32, i32* %44, align 8
  %46 = call i8* @load_variable(i32 noundef %45)
  %47 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %48 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %47, i32 0, i32 2
  %49 = load i32, i32* @nbInput, align 4
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %48, i64 0, i64 %50
  %52 = load %struct.AsmInput*, %struct.AsmInput** %51, align 8
  %53 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %52, i32 0, i32 5
  %54 = load i32, i32* %53, align 8
  %55 = call i8* @load_variable(i32 noundef %54)
  %56 = call i64 @strlen(i8* noundef %55) #8
  %57 = call i8* @strncat(i8* noundef %37, i8* noundef %46, i64 noundef %56) #7
  %58 = load i8*, i8** %4, align 8
  %59 = call i8* @strncat(i8* noundef %58, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.61, i64 0, i64 0), i64 noundef 3) #7
  %60 = load i8*, i8** %4, align 8
  %61 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %62 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %61, i32 0, i32 2
  %63 = load i32, i32* @nbInput, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %62, i64 0, i64 %64
  %66 = load %struct.AsmInput*, %struct.AsmInput** %65, align 8
  %67 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %66, i32 0, i32 1
  %68 = load i8*, i8** %67, align 8
  %69 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %70 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %69, i32 0, i32 2
  %71 = load i32, i32* @nbInput, align 4
  %72 = sext i32 %71 to i64
  %73 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %70, i64 0, i64 %72
  %74 = load %struct.AsmInput*, %struct.AsmInput** %73, align 8
  %75 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %74, i32 0, i32 1
  %76 = load i8*, i8** %75, align 8
  %77 = call i64 @strlen(i8* noundef %76) #8
  %78 = call i8* @strncat(i8* noundef %60, i8* noundef %68, i64 noundef %77) #7
  %79 = load i8*, i8** %4, align 8
  %80 = call i8* @strncat(i8* noundef %79, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.62, i64 0, i64 0), i64 noundef 3) #7
  %81 = load i8*, i8** %4, align 8
  store i8* %81, i8** %2, align 8
  br label %149

82:                                               ; preds = %1
  %83 = load i8*, i8** %4, align 8
  %84 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %85 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %84, i32 0, i32 2
  %86 = load i32, i32* @nbInput, align 4
  %87 = sext i32 %86 to i64
  %88 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %85, i64 0, i64 %87
  %89 = load %struct.AsmInput*, %struct.AsmInput** %88, align 8
  %90 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %89, i32 0, i32 6
  %91 = load i32, i32* %90, align 4
  %92 = call i8* @opcode(i32 noundef %91)
  %93 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %94 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %93, i32 0, i32 2
  %95 = load i32, i32* @nbInput, align 4
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %94, i64 0, i64 %96
  %98 = load %struct.AsmInput*, %struct.AsmInput** %97, align 8
  %99 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %98, i32 0, i32 6
  %100 = load i32, i32* %99, align 4
  %101 = call i8* @opcode(i32 noundef %100)
  %102 = call i64 @strlen(i8* noundef %101) #8
  %103 = call i8* @strncat(i8* noundef %83, i8* noundef %92, i64 noundef %102) #7
  %104 = load i8*, i8** %4, align 8
  %105 = call i8* @strncat(i8* noundef %104, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.63, i64 0, i64 0), i64 noundef 3) #7
  %106 = load i8*, i8** %4, align 8
  %107 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %108 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %107, i32 0, i32 2
  %109 = load i32, i32* @nbInput, align 4
  %110 = sext i32 %109 to i64
  %111 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %108, i64 0, i64 %110
  %112 = load %struct.AsmInput*, %struct.AsmInput** %111, align 8
  %113 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %112, i32 0, i32 2
  %114 = load i8*, i8** %113, align 8
  %115 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %116 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %115, i32 0, i32 2
  %117 = load i32, i32* @nbInput, align 4
  %118 = sext i32 %117 to i64
  %119 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %116, i64 0, i64 %118
  %120 = load %struct.AsmInput*, %struct.AsmInput** %119, align 8
  %121 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %120, i32 0, i32 2
  %122 = load i8*, i8** %121, align 8
  %123 = call i64 @strlen(i8* noundef %122) #8
  %124 = call i8* @strncat(i8* noundef %106, i8* noundef %114, i64 noundef %123) #7
  %125 = load i8*, i8** %4, align 8
  %126 = call i8* @strncat(i8* noundef %125, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.61, i64 0, i64 0), i64 noundef 3) #7
  %127 = load i8*, i8** %4, align 8
  %128 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %129 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %128, i32 0, i32 2
  %130 = load i32, i32* @nbInput, align 4
  %131 = sext i32 %130 to i64
  %132 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %129, i64 0, i64 %131
  %133 = load %struct.AsmInput*, %struct.AsmInput** %132, align 8
  %134 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %133, i32 0, i32 1
  %135 = load i8*, i8** %134, align 8
  %136 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %137 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %136, i32 0, i32 2
  %138 = load i32, i32* @nbInput, align 4
  %139 = sext i32 %138 to i64
  %140 = getelementptr inbounds [10 x %struct.AsmInput*], [10 x %struct.AsmInput*]* %137, i64 0, i64 %139
  %141 = load %struct.AsmInput*, %struct.AsmInput** %140, align 8
  %142 = getelementptr inbounds %struct.AsmInput, %struct.AsmInput* %141, i32 0, i32 1
  %143 = load i8*, i8** %142, align 8
  %144 = call i64 @strlen(i8* noundef %143) #8
  %145 = call i8* @strncat(i8* noundef %127, i8* noundef %135, i64 noundef %144) #7
  %146 = load i8*, i8** %4, align 8
  %147 = call i8* @strncat(i8* noundef %146, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.62, i64 0, i64 0), i64 noundef 3) #7
  %148 = load i8*, i8** %4, align 8
  store i8* %148, i8** %2, align 8
  br label %149

149:                                              ; preds = %82, %15
  %150 = load i8*, i8** %2, align 8
  ret i8* %150
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @retrieve_output_index(i8 noundef signext %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i8, align 1
  %4 = alloca i32, align 4
  store i8 %0, i8* %3, align 1
  store i32 0, i32* %4, align 4
  br label %5

5:                                                ; preds = %32, %1
  %6 = load i32, i32* %4, align 4
  %7 = load i32, i32* @nbOutput, align 4
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %9, label %35

9:                                                ; preds = %5
  %10 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %11 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %10, i32 0, i32 1
  %12 = load i32, i32* %4, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %11, i64 0, i64 %13
  %15 = load %struct.AsmOutput*, %struct.AsmOutput** %14, align 8
  %16 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %15, i32 0, i32 4
  %17 = load i8, i8* %16, align 8
  %18 = sext i8 %17 to i32
  %19 = load i8, i8* %3, align 1
  %20 = sext i8 %19 to i32
  %21 = icmp eq i32 %18, %20
  br i1 %21, label %22, label %31

22:                                               ; preds = %9
  %23 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %24 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %23, i32 0, i32 1
  %25 = load i32, i32* %4, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %24, i64 0, i64 %26
  %28 = load %struct.AsmOutput*, %struct.AsmOutput** %27, align 8
  %29 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %28, i32 0, i32 5
  %30 = load i32, i32* %29, align 4
  store i32 %30, i32* %2, align 4
  br label %36

31:                                               ; preds = %9
  br label %32

32:                                               ; preds = %31
  %33 = load i32, i32* %4, align 4
  %34 = add nsw i32 %33, 1
  store i32 %34, i32* %4, align 4
  br label %5, !llvm.loop !16

35:                                               ; preds = %5
  store i32 -1, i32* %2, align 4
  br label %36

36:                                               ; preds = %35, %22
  %37 = load i32, i32* %2, align 4
  ret i32 %37
}

; Function Attrs: noreturn
declare void @error_tok(%struct.Token* noundef, i8* noundef, ...) #4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @subst_asm(i8* noundef %0, i8* noundef %1, i8* noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  store i8* %0, i8** %4, align 8
  store i8* %1, i8** %5, align 8
  store i8* %2, i8** %6, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = load i8*, i8** %6, align 8
  %9 = load i8*, i8** %5, align 8
  %10 = call i8* @string_replace(i8* noundef %7, i8* noundef %8, i8* noundef %9)
  ret i8* %10
}

; Function Attrs: nounwind
declare void @free(i8* noundef) #1

; Function Attrs: nounwind readonly willreturn
declare i32 @strncmp(i8* noundef, i8* noundef, i64 noundef) #3

declare %struct.Token* @skip(%struct.Token* noundef, i8* noundef) #2

declare %struct.VarScope* @find_var(%struct.Token* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @retrieve_parameter_order(i32 noundef %0, i8* noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca %struct.Obj*, align 8
  store i32 %0, i32* %4, align 4
  store i8* %1, i8** %5, align 8
  %7 = load i8*, i8** %5, align 8
  %8 = call %struct.Obj* @find_func(i8* noundef %7)
  store %struct.Obj* %8, %struct.Obj** %6, align 8
  %9 = load %struct.Obj*, %struct.Obj** %6, align 8
  %10 = icmp ne %struct.Obj* %9, null
  br i1 %10, label %11, label %18

11:                                               ; preds = %2
  %12 = load %struct.Obj*, %struct.Obj** %6, align 8
  %13 = getelementptr inbounds %struct.Obj, %struct.Obj* %12, i32 0, i32 9
  %14 = load i32, i32* %13, align 8
  %15 = sub nsw i32 %14, 1
  %16 = load i32, i32* %4, align 4
  %17 = sub nsw i32 %15, %16
  store i32 %17, i32* %3, align 4
  br label %19

18:                                               ; preds = %2
  store i32 0, i32* %3, align 4
  br label %19

19:                                               ; preds = %18, %11
  %20 = load i32, i32* %3, align 4
  ret i32 %20
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @update_register_size(i8* noundef %0, i32 noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  store i32 %1, i32* %5, align 4
  %6 = load i8*, i8** %4, align 8
  %7 = call i32 @strncmp(i8* noundef %6, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.19, i64 0, i64 0), i64 noundef 5) #8
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %12, label %9

9:                                                ; preds = %2
  %10 = load i32, i32* %5, align 4
  %11 = call i8* @reg_ax(i32 noundef %10)
  store i8* %11, i8** %3, align 8
  br label %35

12:                                               ; preds = %2
  %13 = load i8*, i8** %4, align 8
  %14 = call i32 @strncmp(i8* noundef %13, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.26, i64 0, i64 0), i64 noundef 5) #8
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %19, label %16

16:                                               ; preds = %12
  %17 = load i32, i32* %5, align 4
  %18 = call i8* @reg_bx(i32 noundef %17)
  store i8* %18, i8** %3, align 8
  br label %35

19:                                               ; preds = %12
  %20 = load i8*, i8** %4, align 8
  %21 = call i32 @strncmp(i8* noundef %20, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.27, i64 0, i64 0), i64 noundef 5) #8
  %22 = icmp ne i32 %21, 0
  br i1 %22, label %26, label %23

23:                                               ; preds = %19
  %24 = load i32, i32* %5, align 4
  %25 = call i8* @reg_cx(i32 noundef %24)
  store i8* %25, i8** %3, align 8
  br label %35

26:                                               ; preds = %19
  %27 = load i8*, i8** %4, align 8
  %28 = call i32 @strncmp(i8* noundef %27, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.28, i64 0, i64 0), i64 noundef 5) #8
  %29 = icmp ne i32 %28, 0
  br i1 %29, label %33, label %30

30:                                               ; preds = %26
  %31 = load i32, i32* %5, align 4
  %32 = call i8* @reg_dx(i32 noundef %31)
  store i8* %32, i8** %3, align 8
  br label %35

33:                                               ; preds = %26
  %34 = load i8*, i8** %4, align 8
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.79, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0), i8* noundef %34) #9
  unreachable

35:                                               ; preds = %30, %23, %16, %9
  %36 = load i8*, i8** %3, align 8
  ret i8* %36
}

declare zeroext i1 @consume(%struct.Token** noundef, %struct.Token* noundef, i8* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @retrieve_output_index_str(i8 noundef signext %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8, align 1
  %4 = alloca i32, align 4
  store i8 %0, i8* %3, align 1
  store i32 0, i32* %4, align 4
  br label %5

5:                                                ; preds = %39, %1
  %6 = load i32, i32* %4, align 4
  %7 = load i32, i32* @nbOutput, align 4
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %9, label %42

9:                                                ; preds = %5
  %10 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %11 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %10, i32 0, i32 1
  %12 = load i32, i32* %4, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %11, i64 0, i64 %13
  %15 = load %struct.AsmOutput*, %struct.AsmOutput** %14, align 8
  %16 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %15, i32 0, i32 4
  %17 = load i8, i8* %16, align 8
  %18 = sext i8 %17 to i32
  %19 = load i8, i8* %3, align 1
  %20 = sext i8 %19 to i32
  %21 = icmp eq i32 %18, %20
  br i1 %21, label %22, label %38

22:                                               ; preds = %9
  %23 = load %struct.AsmExtended*, %struct.AsmExtended** @asmExt, align 8
  %24 = getelementptr inbounds %struct.AsmExtended, %struct.AsmExtended* %23, i32 0, i32 1
  %25 = load i32, i32* %4, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [10 x %struct.AsmOutput*], [10 x %struct.AsmOutput*]* %24, i64 0, i64 %26
  %28 = load %struct.AsmOutput*, %struct.AsmOutput** %27, align 8
  %29 = getelementptr inbounds %struct.AsmOutput, %struct.AsmOutput* %28, i32 0, i32 5
  %30 = load i32, i32* %29, align 4
  switch i32 %30, label %37 [
    i32 0, label %31
    i32 1, label %32
    i32 2, label %33
    i32 3, label %34
    i32 4, label %35
    i32 5, label %36
  ]

31:                                               ; preds = %22
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.43, i64 0, i64 0), i8** %2, align 8
  br label %43

32:                                               ; preds = %22
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.45, i64 0, i64 0), i8** %2, align 8
  br label %43

33:                                               ; preds = %22
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.47, i64 0, i64 0), i8** %2, align 8
  br label %43

34:                                               ; preds = %22
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.49, i64 0, i64 0), i8** %2, align 8
  br label %43

35:                                               ; preds = %22
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.80, i64 0, i64 0), i8** %2, align 8
  br label %43

36:                                               ; preds = %22
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.81, i64 0, i64 0), i8** %2, align 8
  br label %43

37:                                               ; preds = %22
  br label %38

38:                                               ; preds = %37, %9
  br label %39

39:                                               ; preds = %38
  %40 = load i32, i32* %4, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* %4, align 4
  br label %5, !llvm.loop !17

42:                                               ; preds = %5
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.43, i64 0, i64 0), i8** %2, align 8
  br label %43

43:                                               ; preds = %42, %36, %35, %34, %33, %32, %31
  %44 = load i8*, i8** %2, align 8
  ret i8* %44
}

; Function Attrs: nounwind
declare i32 @snprintf(i8* noundef, i64 noundef, i8* noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @string_replace(i8* noundef %0, i8* noundef %1, i8* noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i64, align 8
  %9 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  store i8* %1, i8** %5, align 8
  store i8* %2, i8** %6, align 8
  %10 = load i8*, i8** %4, align 8
  %11 = call i64 @strlen(i8* noundef %10) #8
  %12 = call i8* @llvm.stacksave()
  store i8* %12, i8** %7, align 8
  %13 = alloca i8, i64 %11, align 16
  store i64 %11, i64* %8, align 8
  call void @llvm.memset.p0i8.i64(i8* align 16 %13, i8 0, i64 %11, i1 false)
  store i32 0, i32* %9, align 4
  br label %14

14:                                               ; preds = %47, %3
  %15 = load i32, i32* %9, align 4
  %16 = sext i32 %15 to i64
  %17 = load i8*, i8** %4, align 8
  %18 = call i64 @strlen(i8* noundef %17) #8
  %19 = icmp ult i64 %16, %18
  br i1 %19, label %20, label %50

20:                                               ; preds = %14
  %21 = load i8*, i8** %4, align 8
  %22 = load i32, i32* %9, align 4
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds i8, i8* %21, i64 %23
  %25 = load i8*, i8** %5, align 8
  %26 = load i8*, i8** %5, align 8
  %27 = call i64 @strlen(i8* noundef %26) #8
  %28 = call i32 @strncmp(i8* noundef %24, i8* noundef %25, i64 noundef %27) #8
  %29 = icmp ne i32 %28, 0
  br i1 %29, label %40, label %30

30:                                               ; preds = %20
  %31 = load i8*, i8** %6, align 8
  %32 = call i8* @strcat(i8* noundef %13, i8* noundef %31) #7
  %33 = load i8*, i8** %5, align 8
  %34 = call i64 @strlen(i8* noundef %33) #8
  %35 = sub i64 %34, 1
  %36 = load i32, i32* %9, align 4
  %37 = sext i32 %36 to i64
  %38 = add i64 %37, %35
  %39 = trunc i64 %38 to i32
  store i32 %39, i32* %9, align 4
  br label %46

40:                                               ; preds = %20
  %41 = load i8*, i8** %4, align 8
  %42 = load i32, i32* %9, align 4
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds i8, i8* %41, i64 %43
  %45 = call i8* @strncat(i8* noundef %13, i8* noundef %44, i64 noundef 1) #7
  br label %46

46:                                               ; preds = %40, %30
  br label %47

47:                                               ; preds = %46
  %48 = load i32, i32* %9, align 4
  %49 = add nsw i32 %48, 1
  store i32 %49, i32* %9, align 4
  br label %14, !llvm.loop !18

50:                                               ; preds = %14
  %51 = load i8*, i8** %4, align 8
  %52 = call i64 @strlen(i8* noundef %13) #8
  %53 = call i8* @strncpy(i8* noundef %51, i8* noundef %13, i64 noundef %52) #7
  %54 = load i8*, i8** %4, align 8
  %55 = load i8*, i8** %7, align 8
  call void @llvm.stackrestore(i8* %55)
  ret i8* %54
}

; Function Attrs: nofree nosync nounwind willreturn
declare i8* @llvm.stacksave() #5

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #6

; Function Attrs: nounwind
declare i8* @strcat(i8* noundef, i8* noundef) #1

; Function Attrs: nounwind
declare i8* @strncpy(i8* noundef, i8* noundef, i64 noundef) #1

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.stackrestore(i8*) #5

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @opcode(i32 noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  switch i32 %4, label %9 [
    i32 1, label %5
    i32 2, label %6
    i32 4, label %7
    i32 8, label %8
  ]

5:                                                ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.74, i64 0, i64 0), i8** %2, align 8
  br label %11

6:                                                ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.75, i64 0, i64 0), i8** %2, align 8
  br label %11

7:                                                ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.76, i64 0, i64 0), i8** %2, align 8
  br label %11

8:                                                ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.77, i64 0, i64 0), i8** %2, align 8
  br label %11

9:                                                ; preds = %1
  %10 = load i32, i32* %3, align 4
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.78, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0), i32 noundef %10) #9
  unreachable

11:                                               ; preds = %8, %7, %6, %5
  %12 = load i8*, i8** %2, align 8
  ret i8* %12
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @load_variable(i32 noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  switch i32 %4, label %10 [
    i32 0, label %5
    i32 1, label %6
    i32 2, label %7
    i32 3, label %8
    i32 4, label %9
  ]

5:                                                ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.68, i64 0, i64 0), i8** %2, align 8
  br label %11

6:                                                ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.69, i64 0, i64 0), i8** %2, align 8
  br label %11

7:                                                ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.70, i64 0, i64 0), i8** %2, align 8
  br label %11

8:                                                ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.71, i64 0, i64 0), i8** %2, align 8
  br label %11

9:                                                ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.72, i64 0, i64 0), i8** %2, align 8
  br label %11

10:                                               ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([61 x i8], [61 x i8]* @.str.73, i64 0, i64 0), i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

11:                                               ; preds = %9, %8, %7, %6, %5
  %12 = load i8*, i8** %2, align 8
  ret i8* %12
}

; Function Attrs: nounwind readonly willreturn
declare i8* @strchr(i8* noundef, i32 noundef) #3

; Function Attrs: noreturn
declare void @error(i8* noundef, ...) #4

declare %struct.Obj* @find_func(i8* noundef) #2

declare i8* @reg_ax(i32 noundef) #2

declare i8* @reg_bx(i32 noundef) #2

declare i8* @reg_cx(i32 noundef) #2

declare i8* @reg_dx(i32 noundef) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind readonly willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nofree nosync nounwind willreturn }
attributes #6 = { argmemonly nofree nounwind willreturn writeonly }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly willreturn }
attributes #9 = { noreturn }

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
