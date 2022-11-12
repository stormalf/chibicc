; ModuleID = 'strings.c'
source_filename = "strings.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.StringArray = type { i8**, i32, i32 }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, %struct._IO_codecvt*, %struct._IO_wide_data*, %struct._IO_FILE*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type opaque
%struct._IO_codecvt = type opaque
%struct._IO_wide_data = type opaque
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [55 x i8] c"%s: in strarray_push reallocation of arr->data failed!\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"strings.c\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @strarray_push(%struct.StringArray* noundef %0, i8* noundef %1) #0 {
  %3 = alloca %struct.StringArray*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  store %struct.StringArray* %0, %struct.StringArray** %3, align 8
  store i8* %1, i8** %4, align 8
  %7 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %8 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %7, i32 0, i32 0
  %9 = load i8**, i8*** %8, align 8
  %10 = icmp ne i8** %9, null
  br i1 %10, label %18, label %11

11:                                               ; preds = %2
  %12 = call noalias i8* @calloc(i64 noundef 8, i64 noundef 8) #5
  %13 = bitcast i8* %12 to i8**
  %14 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %15 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %14, i32 0, i32 0
  store i8** %13, i8*** %15, align 8
  %16 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %17 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %16, i32 0, i32 1
  store i32 8, i32* %17, align 8
  br label %18

18:                                               ; preds = %11, %2
  %19 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %20 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %19, i32 0, i32 1
  %21 = load i32, i32* %20, align 8
  %22 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %23 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %22, i32 0, i32 2
  %24 = load i32, i32* %23, align 4
  %25 = icmp eq i32 %21, %24
  br i1 %25, label %26, label %70

26:                                               ; preds = %18
  %27 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %28 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %27, i32 0, i32 0
  %29 = load i8**, i8*** %28, align 8
  %30 = bitcast i8** %29 to i8*
  %31 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %32 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %31, i32 0, i32 1
  %33 = load i32, i32* %32, align 8
  %34 = sext i32 %33 to i64
  %35 = mul i64 8, %34
  %36 = mul i64 %35, 2
  %37 = call i8* @realloc(i8* noundef %30, i64 noundef %36) #5
  %38 = bitcast i8* %37 to i8**
  store i8** %38, i8*** %5, align 8
  %39 = load i8**, i8*** %5, align 8
  %40 = icmp eq i8** %39, null
  br i1 %40, label %41, label %42

41:                                               ; preds = %26
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([55 x i8], [55 x i8]* @.str, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i64 0, i64 0)) #6
  unreachable

42:                                               ; preds = %26
  %43 = load i8**, i8*** %5, align 8
  %44 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %45 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %44, i32 0, i32 0
  store i8** %43, i8*** %45, align 8
  %46 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %47 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %46, i32 0, i32 1
  %48 = load i32, i32* %47, align 8
  %49 = mul nsw i32 %48, 2
  store i32 %49, i32* %47, align 8
  %50 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %51 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %50, i32 0, i32 2
  %52 = load i32, i32* %51, align 4
  store i32 %52, i32* %6, align 4
  br label %53

53:                                               ; preds = %66, %42
  %54 = load i32, i32* %6, align 4
  %55 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %56 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %55, i32 0, i32 1
  %57 = load i32, i32* %56, align 8
  %58 = icmp slt i32 %54, %57
  br i1 %58, label %59, label %69

59:                                               ; preds = %53
  %60 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %61 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %60, i32 0, i32 0
  %62 = load i8**, i8*** %61, align 8
  %63 = load i32, i32* %6, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds i8*, i8** %62, i64 %64
  store i8* null, i8** %65, align 8
  br label %66

66:                                               ; preds = %59
  %67 = load i32, i32* %6, align 4
  %68 = add nsw i32 %67, 1
  store i32 %68, i32* %6, align 4
  br label %53, !llvm.loop !6

69:                                               ; preds = %53
  br label %70

70:                                               ; preds = %69, %18
  %71 = load i8*, i8** %4, align 8
  %72 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %73 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %72, i32 0, i32 0
  %74 = load i8**, i8*** %73, align 8
  %75 = load %struct.StringArray*, %struct.StringArray** %3, align 8
  %76 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %75, i32 0, i32 2
  %77 = load i32, i32* %76, align 4
  %78 = add nsw i32 %77, 1
  store i32 %78, i32* %76, align 4
  %79 = sext i32 %77 to i64
  %80 = getelementptr inbounds i8*, i8** %74, i64 %79
  store i8* %71, i8** %80, align 8
  ret void
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64 noundef, i64 noundef) #1

; Function Attrs: nounwind
declare i8* @realloc(i8* noundef, i64 noundef) #1

; Function Attrs: noreturn
declare void @error(i8* noundef, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @format(i8* noundef %0, ...) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i64, align 8
  %5 = alloca %struct._IO_FILE*, align 8
  %6 = alloca [1 x %struct.__va_list_tag], align 16
  store i8* %0, i8** %2, align 8
  %7 = call noalias %struct._IO_FILE* @open_memstream(i8** noundef %3, i64* noundef %4) #5
  store %struct._IO_FILE* %7, %struct._IO_FILE** %5, align 8
  %8 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %6, i64 0, i64 0
  %9 = bitcast %struct.__va_list_tag* %8 to i8*
  call void @llvm.va_start(i8* %9)
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8
  %11 = load i8*, i8** %2, align 8
  %12 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %6, i64 0, i64 0
  %13 = call i32 @vfprintf(%struct._IO_FILE* noundef %10, i8* noundef %11, %struct.__va_list_tag* noundef %12)
  %14 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %6, i64 0, i64 0
  %15 = bitcast %struct.__va_list_tag* %14 to i8*
  call void @llvm.va_end(i8* %15)
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8
  %17 = call i32 @fclose(%struct._IO_FILE* noundef %16)
  %18 = load i8*, i8** %3, align 8
  ret i8* %18
}

; Function Attrs: nounwind
declare noalias %struct._IO_FILE* @open_memstream(i8** noundef, i64* noundef) #1

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.va_start(i8*) #3

declare i32 @vfprintf(%struct._IO_FILE* noundef, i8* noundef, %struct.__va_list_tag* noundef) #4

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.va_end(i8*) #3

declare i32 @fclose(%struct._IO_FILE* noundef) #4

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nofree nosync nounwind willreturn }
attributes #4 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind }
attributes #6 = { noreturn }

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
