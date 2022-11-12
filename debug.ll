; ModuleID = 'debug.c'
source_filename = "debug.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, %struct._IO_codecvt*, %struct._IO_wide_data*, %struct._IO_FILE*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type opaque
%struct._IO_codecvt = type opaque
%struct._IO_wide_data = type opaque
%struct.Token = type { i32, %struct.Token*, i64, x86_fp80, i8*, i32, %struct.Type*, i8*, %struct.File*, i8*, i32, i32, i8, i8, %struct.Hideset*, %struct.Token* }
%struct.Type = type { i32, i32, i32, i8, i8, i8, %struct.Type*, %struct.Type*, %struct.Type*, %struct.Token*, %struct.Token*, i32, %struct.Node*, %struct.Obj*, %struct.Member*, i8, i8, %struct.Type*, %struct.Type*, i8, %struct.Type* }
%struct.Node = type { i32, %struct.Node*, %struct.Type*, %struct.Token*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, i8*, i8*, %struct.Node*, %struct.Member*, %struct.Type*, %struct.Node*, i8, %struct.Obj*, i8*, i8*, %struct.Node*, %struct.Node*, %struct.Node*, i64, i64, i8*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Obj*, %struct.Node*, i8, %struct.Obj*, i64, x86_fp80, i32, [12 x i8] }
%struct.Obj = type { %struct.Obj*, i8*, i8*, %struct.Type*, %struct.Token*, i8, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8*, %struct.Relocation*, i8, %struct.Obj*, %struct.Node*, %struct.Obj*, %struct.Obj*, %struct.Obj*, i32, i8, i8, %struct.StringArray }
%struct.Relocation = type { %struct.Relocation*, i32, i8**, i64 }
%struct.StringArray = type { i8**, i32, i32 }
%struct.Member = type { %struct.Member*, %struct.Type*, %struct.Token*, %struct.Token*, i32, i32, i32, i8, i32, i32 }
%struct.File = type { i8*, i32, i8*, i8*, i32 }
%struct.Hideset = type opaque

@.str = private unnamed_addr constant [9 x i8] c"TK_IDENT\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"TK_PUNCT\00", align 1
@.str.2 = private unnamed_addr constant [11 x i8] c"TK_KEYWORD\00", align 1
@.str.3 = private unnamed_addr constant [7 x i8] c"TK_STR\00", align 1
@.str.4 = private unnamed_addr constant [7 x i8] c"TK_NUM\00", align 1
@.str.5 = private unnamed_addr constant [10 x i8] c"TK_PP_NUM\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"TK_EOF\00", align 1
@.str.7 = private unnamed_addr constant [12 x i8] c"UNREACHABLE\00", align 1
@f = external global %struct._IO_FILE*, align 8
@.str.8 = private unnamed_addr constant [46 x i8] c"=====================file : %s, function: %s\0A\00", align 1
@.str.9 = private unnamed_addr constant [68 x i8] c"token->kind: %s, token->len: %d, token->val: %ld, token->fval:%Lf \0A\00", align 1
@.str.10 = private unnamed_addr constant [81 x i8] c"     token->str: %s, token->filename: %s, token->line_no: %d, token->at_bol:%d \0A\00", align 1
@.str.11 = private unnamed_addr constant [22 x i8] c"     token->loc: %s \0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @tokenkind2str(i32 noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  switch i32 %4, label %12 [
    i32 0, label %5
    i32 1, label %6
    i32 2, label %7
    i32 3, label %8
    i32 4, label %9
    i32 5, label %10
    i32 6, label %11
  ]

5:                                                ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i64 0, i64 0), i8** %2, align 8
  br label %13

6:                                                ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.1, i64 0, i64 0), i8** %2, align 8
  br label %13

7:                                                ; preds = %1
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0), i8** %2, align 8
  br label %13

8:                                                ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i64 0, i64 0), i8** %2, align 8
  br label %13

9:                                                ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.4, i64 0, i64 0), i8** %2, align 8
  br label %13

10:                                               ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i8** %2, align 8
  br label %13

11:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0), i8** %2, align 8
  br label %13

12:                                               ; preds = %1
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.7, i64 0, i64 0), i8** %2, align 8
  br label %13

13:                                               ; preds = %12, %11, %10, %9, %8, %7, %6, %5
  %14 = load i8*, i8** %2, align 8
  ret i8* %14
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @print_debug_tokens(i8* noundef %0, i8* noundef %1, %struct.Token* noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i64, align 8
  %10 = alloca i8*, align 8
  store i8* %0, i8** %4, align 8
  store i8* %1, i8** %5, align 8
  store %struct.Token* %2, %struct.Token** %6, align 8
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %12 = load i8*, i8** %4, align 8
  %13 = load i8*, i8** %5, align 8
  %14 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %11, i8* noundef getelementptr inbounds ([46 x i8], [46 x i8]* @.str.8, i64 0, i64 0), i8* noundef %12, i8* noundef %13)
  %15 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %15, %struct.Token** %7, align 8
  br label %16

16:                                               ; preds = %79, %3
  %17 = load %struct.Token*, %struct.Token** %7, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 0
  %19 = load i32, i32* %18, align 16
  %20 = icmp ne i32 %19, 6
  br i1 %20, label %21, label %83

21:                                               ; preds = %16
  %22 = load %struct.Token*, %struct.Token** %7, align 8
  %23 = getelementptr inbounds %struct.Token, %struct.Token* %22, i32 0, i32 5
  %24 = load i32, i32* %23, align 8
  %25 = icmp sgt i32 %24, 0
  br i1 %25, label %26, label %79

26:                                               ; preds = %21
  %27 = load %struct.Token*, %struct.Token** %7, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 5
  %29 = load i32, i32* %28, align 8
  %30 = add nsw i32 %29, 1
  %31 = zext i32 %30 to i64
  %32 = call i8* @llvm.stacksave()
  store i8* %32, i8** %8, align 8
  %33 = alloca i8, i64 %31, align 16
  store i64 %31, i64* %9, align 8
  call void @llvm.memset.p0i8.i64(i8* align 16 %33, i8 0, i64 %31, i1 false)
  %34 = getelementptr inbounds i8, i8* %33, i64 0
  store i8* %34, i8** %10, align 8
  %35 = load i8*, i8** %10, align 8
  %36 = load %struct.Token*, %struct.Token** %7, align 8
  %37 = getelementptr inbounds %struct.Token, %struct.Token* %36, i32 0, i32 4
  %38 = load i8*, i8** %37, align 16
  %39 = load %struct.Token*, %struct.Token** %7, align 8
  %40 = getelementptr inbounds %struct.Token, %struct.Token* %39, i32 0, i32 5
  %41 = load i32, i32* %40, align 8
  %42 = sext i32 %41 to i64
  %43 = call i8* @strncpy(i8* noundef %35, i8* noundef %38, i64 noundef %42) #5
  %44 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %45 = load %struct.Token*, %struct.Token** %7, align 8
  %46 = getelementptr inbounds %struct.Token, %struct.Token* %45, i32 0, i32 0
  %47 = load i32, i32* %46, align 16
  %48 = call i8* @tokenkind2str(i32 noundef %47)
  %49 = load %struct.Token*, %struct.Token** %7, align 8
  %50 = getelementptr inbounds %struct.Token, %struct.Token* %49, i32 0, i32 5
  %51 = load i32, i32* %50, align 8
  %52 = load %struct.Token*, %struct.Token** %7, align 8
  %53 = getelementptr inbounds %struct.Token, %struct.Token* %52, i32 0, i32 2
  %54 = load i64, i64* %53, align 16
  %55 = load %struct.Token*, %struct.Token** %7, align 8
  %56 = getelementptr inbounds %struct.Token, %struct.Token* %55, i32 0, i32 3
  %57 = load x86_fp80, x86_fp80* %56, align 16
  %58 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %44, i8* noundef getelementptr inbounds ([68 x i8], [68 x i8]* @.str.9, i64 0, i64 0), i8* noundef %48, i32 noundef %51, i64 noundef %54, x86_fp80 noundef %57)
  %59 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %60 = load %struct.Token*, %struct.Token** %7, align 8
  %61 = getelementptr inbounds %struct.Token, %struct.Token* %60, i32 0, i32 7
  %62 = load i8*, i8** %61, align 8
  %63 = load %struct.Token*, %struct.Token** %7, align 8
  %64 = getelementptr inbounds %struct.Token, %struct.Token* %63, i32 0, i32 9
  %65 = load i8*, i8** %64, align 8
  %66 = load %struct.Token*, %struct.Token** %7, align 8
  %67 = getelementptr inbounds %struct.Token, %struct.Token* %66, i32 0, i32 10
  %68 = load i32, i32* %67, align 16
  %69 = load %struct.Token*, %struct.Token** %7, align 8
  %70 = getelementptr inbounds %struct.Token, %struct.Token* %69, i32 0, i32 12
  %71 = load i8, i8* %70, align 8
  %72 = trunc i8 %71 to i1
  %73 = zext i1 %72 to i32
  %74 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %59, i8* noundef getelementptr inbounds ([81 x i8], [81 x i8]* @.str.10, i64 0, i64 0), i8* noundef %62, i8* noundef %65, i32 noundef %68, i32 noundef %73)
  %75 = load %struct._IO_FILE*, %struct._IO_FILE** @f, align 8
  %76 = load i8*, i8** %10, align 8
  %77 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %75, i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.11, i64 0, i64 0), i8* noundef %76)
  %78 = load i8*, i8** %8, align 8
  call void @llvm.stackrestore(i8* %78)
  br label %79

79:                                               ; preds = %26, %21
  %80 = load %struct.Token*, %struct.Token** %7, align 8
  %81 = getelementptr inbounds %struct.Token, %struct.Token* %80, i32 0, i32 1
  %82 = load %struct.Token*, %struct.Token** %81, align 8
  store %struct.Token* %82, %struct.Token** %7, align 8
  br label %16, !llvm.loop !6

83:                                               ; preds = %16
  ret void
}

declare i32 @fprintf(%struct._IO_FILE* noundef, i8* noundef, ...) #1

; Function Attrs: nofree nosync nounwind willreturn
declare i8* @llvm.stacksave() #2

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #3

; Function Attrs: nounwind
declare i8* @strncpy(i8* noundef, i8* noundef, i64 noundef) #4

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.stackrestore(i8*) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nofree nosync nounwind willreturn }
attributes #3 = { argmemonly nofree nounwind willreturn writeonly }
attributes #4 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind }

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
