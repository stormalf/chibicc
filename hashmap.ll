; ModuleID = 'hashmap.c'
source_filename = "hashmap.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.HashMap = type { %struct.HashEntry*, i32, i32 }
%struct.HashEntry = type { i8*, i32, i8* }

@.str = private unnamed_addr constant [7 x i8] c"key %d\00", align 1
@.str.1 = private unnamed_addr constant [51 x i8] c"(size_t)hashmap_get(map, format(\22key %d\22, i)) == i\00", align 1
@.str.2 = private unnamed_addr constant [10 x i8] c"hashmap.c\00", align 1
@__PRETTY_FUNCTION__.hashmap_test = private unnamed_addr constant [24 x i8] c"void hashmap_test(void)\00", align 1
@.str.3 = private unnamed_addr constant [12 x i8] c"no such key\00", align 1
@.str.4 = private unnamed_addr constant [40 x i8] c"hashmap_get(map, \22no such key\22) == NULL\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@.str.6 = private unnamed_addr constant [24 x i8] c"internal error at %s:%d\00", align 1
@.str.7 = private unnamed_addr constant [49 x i8] c"%s: in get_or_insert_entry map->buckets is null!\00", align 1
@.str.8 = private unnamed_addr constant [8 x i8] c"cap > 0\00", align 1
@__PRETTY_FUNCTION__.rehash = private unnamed_addr constant [23 x i8] c"void rehash(HashMap *)\00", align 1
@.str.9 = private unnamed_addr constant [36 x i8] c"%s: in rehash map2.buckets is null!\00", align 1
@.str.10 = private unnamed_addr constant [19 x i8] c"map2.used == nkeys\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @hashmap_get(%struct.HashMap* noundef %0, i8* noundef %1) #0 {
  %3 = alloca %struct.HashMap*, align 8
  %4 = alloca i8*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %struct.HashMap*, %struct.HashMap** %3, align 8
  %6 = load i8*, i8** %4, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = call i64 @strlen(i8* noundef %7) #8
  %9 = trunc i64 %8 to i32
  %10 = call i8* @hashmap_get2(%struct.HashMap* noundef %5, i8* noundef %6, i32 noundef %9)
  ret i8* %10
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @hashmap_get2(%struct.HashMap* noundef %0, i8* noundef %1, i32 noundef %2) #0 {
  %4 = alloca %struct.HashMap*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  %7 = alloca %struct.HashEntry*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %4, align 8
  store i8* %1, i8** %5, align 8
  store i32 %2, i32* %6, align 4
  %8 = load %struct.HashMap*, %struct.HashMap** %4, align 8
  %9 = load i8*, i8** %5, align 8
  %10 = load i32, i32* %6, align 4
  %11 = call %struct.HashEntry* @get_entry(%struct.HashMap* noundef %8, i8* noundef %9, i32 noundef %10)
  store %struct.HashEntry* %11, %struct.HashEntry** %7, align 8
  %12 = load %struct.HashEntry*, %struct.HashEntry** %7, align 8
  %13 = icmp ne %struct.HashEntry* %12, null
  br i1 %13, label %14, label %18

14:                                               ; preds = %3
  %15 = load %struct.HashEntry*, %struct.HashEntry** %7, align 8
  %16 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %15, i32 0, i32 2
  %17 = load i8*, i8** %16, align 8
  br label %19

18:                                               ; preds = %3
  br label %19

19:                                               ; preds = %18, %14
  %20 = phi i8* [ %17, %14 ], [ null, %18 ]
  ret i8* %20
}

; Function Attrs: nounwind readonly willreturn
declare i64 @strlen(i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.HashEntry* @get_entry(%struct.HashMap* noundef %0, i8* noundef %1, i32 noundef %2) #0 {
  %4 = alloca %struct.HashEntry*, align 8
  %5 = alloca %struct.HashMap*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i64, align 8
  %9 = alloca i32, align 4
  %10 = alloca %struct.HashEntry*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %5, align 8
  store i8* %1, i8** %6, align 8
  store i32 %2, i32* %7, align 4
  %11 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %12 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %11, i32 0, i32 0
  %13 = load %struct.HashEntry*, %struct.HashEntry** %12, align 8
  %14 = icmp ne %struct.HashEntry* %13, null
  br i1 %14, label %16, label %15

15:                                               ; preds = %3
  store %struct.HashEntry* null, %struct.HashEntry** %4, align 8
  br label %57

16:                                               ; preds = %3
  %17 = load i8*, i8** %6, align 8
  %18 = load i32, i32* %7, align 4
  %19 = call i64 @fnv_hash(i8* noundef %17, i32 noundef %18)
  store i64 %19, i64* %8, align 8
  store i32 0, i32* %9, align 4
  br label %20

20:                                               ; preds = %53, %16
  %21 = load i32, i32* %9, align 4
  %22 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %23 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %22, i32 0, i32 1
  %24 = load i32, i32* %23, align 8
  %25 = icmp slt i32 %21, %24
  br i1 %25, label %26, label %56

26:                                               ; preds = %20
  %27 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %28 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %27, i32 0, i32 0
  %29 = load %struct.HashEntry*, %struct.HashEntry** %28, align 8
  %30 = load i64, i64* %8, align 8
  %31 = load i32, i32* %9, align 4
  %32 = sext i32 %31 to i64
  %33 = add i64 %30, %32
  %34 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %35 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %34, i32 0, i32 1
  %36 = load i32, i32* %35, align 8
  %37 = sext i32 %36 to i64
  %38 = urem i64 %33, %37
  %39 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %29, i64 %38
  store %struct.HashEntry* %39, %struct.HashEntry** %10, align 8
  %40 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  %41 = load i8*, i8** %6, align 8
  %42 = load i32, i32* %7, align 4
  %43 = call zeroext i1 @match(%struct.HashEntry* noundef %40, i8* noundef %41, i32 noundef %42)
  br i1 %43, label %44, label %46

44:                                               ; preds = %26
  %45 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  store %struct.HashEntry* %45, %struct.HashEntry** %4, align 8
  br label %57

46:                                               ; preds = %26
  %47 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  %48 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %47, i32 0, i32 0
  %49 = load i8*, i8** %48, align 8
  %50 = icmp eq i8* %49, null
  br i1 %50, label %51, label %52

51:                                               ; preds = %46
  store %struct.HashEntry* null, %struct.HashEntry** %4, align 8
  br label %57

52:                                               ; preds = %46
  br label %53

53:                                               ; preds = %52
  %54 = load i32, i32* %9, align 4
  %55 = add nsw i32 %54, 1
  store i32 %55, i32* %9, align 4
  br label %20, !llvm.loop !6

56:                                               ; preds = %20
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.6, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 83) #9
  unreachable

57:                                               ; preds = %51, %44, %15
  %58 = load %struct.HashEntry*, %struct.HashEntry** %4, align 8
  ret %struct.HashEntry* %58
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @hashmap_put(%struct.HashMap* noundef %0, i8* noundef %1, i8* noundef %2) #0 {
  %4 = alloca %struct.HashMap*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %4, align 8
  store i8* %1, i8** %5, align 8
  store i8* %2, i8** %6, align 8
  %7 = load %struct.HashMap*, %struct.HashMap** %4, align 8
  %8 = load i8*, i8** %5, align 8
  %9 = load i8*, i8** %5, align 8
  %10 = call i64 @strlen(i8* noundef %9) #8
  %11 = trunc i64 %10 to i32
  %12 = load i8*, i8** %6, align 8
  call void @hashmap_put2(%struct.HashMap* noundef %7, i8* noundef %8, i32 noundef %11, i8* noundef %12)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @hashmap_put2(%struct.HashMap* noundef %0, i8* noundef %1, i32 noundef %2, i8* noundef %3) #0 {
  %5 = alloca %struct.HashMap*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca %struct.HashEntry*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %5, align 8
  store i8* %1, i8** %6, align 8
  store i32 %2, i32* %7, align 4
  store i8* %3, i8** %8, align 8
  %10 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %11 = load i8*, i8** %6, align 8
  %12 = load i32, i32* %7, align 4
  %13 = call %struct.HashEntry* @get_or_insert_entry(%struct.HashMap* noundef %10, i8* noundef %11, i32 noundef %12)
  store %struct.HashEntry* %13, %struct.HashEntry** %9, align 8
  %14 = load i8*, i8** %8, align 8
  %15 = load %struct.HashEntry*, %struct.HashEntry** %9, align 8
  %16 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %15, i32 0, i32 2
  store i8* %14, i8** %16, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.HashEntry* @get_or_insert_entry(%struct.HashMap* noundef %0, i8* noundef %1, i32 noundef %2) #0 {
  %4 = alloca %struct.HashEntry*, align 8
  %5 = alloca %struct.HashMap*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i64, align 8
  %9 = alloca i32, align 4
  %10 = alloca %struct.HashEntry*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %5, align 8
  store i8* %1, i8** %6, align 8
  store i32 %2, i32* %7, align 4
  %11 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %12 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %11, i32 0, i32 0
  %13 = load %struct.HashEntry*, %struct.HashEntry** %12, align 8
  %14 = icmp ne %struct.HashEntry* %13, null
  br i1 %14, label %28, label %15

15:                                               ; preds = %3
  %16 = call noalias i8* @calloc(i64 noundef 16, i64 noundef 24) #10
  %17 = bitcast i8* %16 to %struct.HashEntry*
  %18 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %19 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %18, i32 0, i32 0
  store %struct.HashEntry* %17, %struct.HashEntry** %19, align 8
  %20 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %21 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %20, i32 0, i32 0
  %22 = load %struct.HashEntry*, %struct.HashEntry** %21, align 8
  %23 = icmp eq %struct.HashEntry* %22, null
  br i1 %23, label %24, label %25

24:                                               ; preds = %15
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([49 x i8], [49 x i8]* @.str.7, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

25:                                               ; preds = %15
  %26 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %27 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %26, i32 0, i32 1
  store i32 16, i32* %27, align 8
  br label %41

28:                                               ; preds = %3
  %29 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %30 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %29, i32 0, i32 2
  %31 = load i32, i32* %30, align 4
  %32 = mul nsw i32 %31, 100
  %33 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %34 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %33, i32 0, i32 1
  %35 = load i32, i32* %34, align 8
  %36 = sdiv i32 %32, %35
  %37 = icmp sge i32 %36, 70
  br i1 %37, label %38, label %40

38:                                               ; preds = %28
  %39 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  call void @rehash(%struct.HashMap* noundef %39)
  br label %40

40:                                               ; preds = %38, %28
  br label %41

41:                                               ; preds = %40, %25
  %42 = load i8*, i8** %6, align 8
  %43 = load i32, i32* %7, align 4
  %44 = call i64 @fnv_hash(i8* noundef %42, i32 noundef %43)
  store i64 %44, i64* %8, align 8
  store i32 0, i32* %9, align 4
  br label %45

45:                                               ; preds = %89, %41
  %46 = load i32, i32* %9, align 4
  %47 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %48 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %47, i32 0, i32 1
  %49 = load i32, i32* %48, align 8
  %50 = icmp slt i32 %46, %49
  br i1 %50, label %51, label %92

51:                                               ; preds = %45
  %52 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %53 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %52, i32 0, i32 0
  %54 = load %struct.HashEntry*, %struct.HashEntry** %53, align 8
  %55 = load i64, i64* %8, align 8
  %56 = load i32, i32* %9, align 4
  %57 = sext i32 %56 to i64
  %58 = add i64 %55, %57
  %59 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %60 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %59, i32 0, i32 1
  %61 = load i32, i32* %60, align 8
  %62 = sext i32 %61 to i64
  %63 = urem i64 %58, %62
  %64 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %54, i64 %63
  store %struct.HashEntry* %64, %struct.HashEntry** %10, align 8
  %65 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  %66 = load i8*, i8** %6, align 8
  %67 = load i32, i32* %7, align 4
  %68 = call zeroext i1 @match(%struct.HashEntry* noundef %65, i8* noundef %66, i32 noundef %67)
  br i1 %68, label %69, label %71

69:                                               ; preds = %51
  %70 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  store %struct.HashEntry* %70, %struct.HashEntry** %4, align 8
  br label %93

71:                                               ; preds = %51
  %72 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  %73 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %72, i32 0, i32 0
  %74 = load i8*, i8** %73, align 8
  %75 = icmp eq i8* %74, null
  br i1 %75, label %76, label %88

76:                                               ; preds = %71
  %77 = load i8*, i8** %6, align 8
  %78 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  %79 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %78, i32 0, i32 0
  store i8* %77, i8** %79, align 8
  %80 = load i32, i32* %7, align 4
  %81 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  %82 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %81, i32 0, i32 1
  store i32 %80, i32* %82, align 8
  %83 = load %struct.HashMap*, %struct.HashMap** %5, align 8
  %84 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %83, i32 0, i32 2
  %85 = load i32, i32* %84, align 4
  %86 = add nsw i32 %85, 1
  store i32 %86, i32* %84, align 4
  %87 = load %struct.HashEntry*, %struct.HashEntry** %10, align 8
  store %struct.HashEntry* %87, %struct.HashEntry** %4, align 8
  br label %93

88:                                               ; preds = %71
  br label %89

89:                                               ; preds = %88
  %90 = load i32, i32* %9, align 4
  %91 = add nsw i32 %90, 1
  store i32 %91, i32* %9, align 4
  br label %45, !llvm.loop !8

92:                                               ; preds = %45
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.6, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 124) #9
  unreachable

93:                                               ; preds = %76, %69
  %94 = load %struct.HashEntry*, %struct.HashEntry** %4, align 8
  ret %struct.HashEntry* %94
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @hashmap_delete(%struct.HashMap* noundef %0, i8* noundef %1) #0 {
  %3 = alloca %struct.HashMap*, align 8
  %4 = alloca i8*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %struct.HashMap*, %struct.HashMap** %3, align 8
  %6 = load i8*, i8** %4, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = call i64 @strlen(i8* noundef %7) #8
  %9 = trunc i64 %8 to i32
  call void @hashmap_delete2(%struct.HashMap* noundef %5, i8* noundef %6, i32 noundef %9)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @hashmap_delete2(%struct.HashMap* noundef %0, i8* noundef %1, i32 noundef %2) #0 {
  %4 = alloca %struct.HashMap*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  %7 = alloca %struct.HashEntry*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %4, align 8
  store i8* %1, i8** %5, align 8
  store i32 %2, i32* %6, align 4
  %8 = load %struct.HashMap*, %struct.HashMap** %4, align 8
  %9 = load i8*, i8** %5, align 8
  %10 = load i32, i32* %6, align 4
  %11 = call %struct.HashEntry* @get_entry(%struct.HashMap* noundef %8, i8* noundef %9, i32 noundef %10)
  store %struct.HashEntry* %11, %struct.HashEntry** %7, align 8
  %12 = load %struct.HashEntry*, %struct.HashEntry** %7, align 8
  %13 = icmp ne %struct.HashEntry* %12, null
  br i1 %13, label %14, label %17

14:                                               ; preds = %3
  %15 = load %struct.HashEntry*, %struct.HashEntry** %7, align 8
  %16 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %15, i32 0, i32 0
  store i8* inttoptr (i64 -1 to i8*), i8** %16, align 8
  br label %17

17:                                               ; preds = %14, %3
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @hashmap_test() #0 {
  %1 = alloca %struct.HashMap*, align 8
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 16) #10
  %14 = bitcast i8* %13 to %struct.HashMap*
  store %struct.HashMap* %14, %struct.HashMap** %1, align 8
  store i32 0, i32* %2, align 4
  br label %15

15:                                               ; preds = %25, %0
  %16 = load i32, i32* %2, align 4
  %17 = icmp slt i32 %16, 5000
  br i1 %17, label %18, label %28

18:                                               ; preds = %15
  %19 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %20 = load i32, i32* %2, align 4
  %21 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), i32 noundef %20)
  %22 = load i32, i32* %2, align 4
  %23 = sext i32 %22 to i64
  %24 = inttoptr i64 %23 to i8*
  call void @hashmap_put(%struct.HashMap* noundef %19, i8* noundef %21, i8* noundef %24)
  br label %25

25:                                               ; preds = %18
  %26 = load i32, i32* %2, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, i32* %2, align 4
  br label %15, !llvm.loop !9

28:                                               ; preds = %15
  store i32 1000, i32* %3, align 4
  br label %29

29:                                               ; preds = %36, %28
  %30 = load i32, i32* %3, align 4
  %31 = icmp slt i32 %30, 2000
  br i1 %31, label %32, label %39

32:                                               ; preds = %29
  %33 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %34 = load i32, i32* %3, align 4
  %35 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), i32 noundef %34)
  call void @hashmap_delete(%struct.HashMap* noundef %33, i8* noundef %35)
  br label %36

36:                                               ; preds = %32
  %37 = load i32, i32* %3, align 4
  %38 = add nsw i32 %37, 1
  store i32 %38, i32* %3, align 4
  br label %29, !llvm.loop !10

39:                                               ; preds = %29
  store i32 1500, i32* %4, align 4
  br label %40

40:                                               ; preds = %50, %39
  %41 = load i32, i32* %4, align 4
  %42 = icmp slt i32 %41, 1600
  br i1 %42, label %43, label %53

43:                                               ; preds = %40
  %44 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %45 = load i32, i32* %4, align 4
  %46 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), i32 noundef %45)
  %47 = load i32, i32* %4, align 4
  %48 = sext i32 %47 to i64
  %49 = inttoptr i64 %48 to i8*
  call void @hashmap_put(%struct.HashMap* noundef %44, i8* noundef %46, i8* noundef %49)
  br label %50

50:                                               ; preds = %43
  %51 = load i32, i32* %4, align 4
  %52 = add nsw i32 %51, 1
  store i32 %52, i32* %4, align 4
  br label %40, !llvm.loop !11

53:                                               ; preds = %40
  store i32 6000, i32* %5, align 4
  br label %54

54:                                               ; preds = %64, %53
  %55 = load i32, i32* %5, align 4
  %56 = icmp slt i32 %55, 7000
  br i1 %56, label %57, label %67

57:                                               ; preds = %54
  %58 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %59 = load i32, i32* %5, align 4
  %60 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), i32 noundef %59)
  %61 = load i32, i32* %5, align 4
  %62 = sext i32 %61 to i64
  %63 = inttoptr i64 %62 to i8*
  call void @hashmap_put(%struct.HashMap* noundef %58, i8* noundef %60, i8* noundef %63)
  br label %64

64:                                               ; preds = %57
  %65 = load i32, i32* %5, align 4
  %66 = add nsw i32 %65, 1
  store i32 %66, i32* %5, align 4
  br label %54, !llvm.loop !12

67:                                               ; preds = %54
  store i32 0, i32* %6, align 4
  br label %68

68:                                               ; preds = %83, %67
  %69 = load i32, i32* %6, align 4
  %70 = icmp slt i32 %69, 1000
  br i1 %70, label %71, label %86

71:                                               ; preds = %68
  %72 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %73 = load i32, i32* %6, align 4
  %74 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), i32 noundef %73)
  %75 = call i8* @hashmap_get(%struct.HashMap* noundef %72, i8* noundef %74)
  %76 = ptrtoint i8* %75 to i64
  %77 = load i32, i32* %6, align 4
  %78 = sext i32 %77 to i64
  %79 = icmp eq i64 %76, %78
  br i1 %79, label %80, label %81

80:                                               ; preds = %71
  br label %82

81:                                               ; preds = %71
  call void @__assert_fail(i8* noundef getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 175, i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.hashmap_test, i64 0, i64 0)) #11
  unreachable

82:                                               ; preds = %80
  br label %83

83:                                               ; preds = %82
  %84 = load i32, i32* %6, align 4
  %85 = add nsw i32 %84, 1
  store i32 %85, i32* %6, align 4
  br label %68, !llvm.loop !13

86:                                               ; preds = %68
  store i32 1000, i32* %7, align 4
  br label %87

87:                                               ; preds = %97, %86
  %88 = load i32, i32* %7, align 4
  %89 = icmp slt i32 %88, 1500
  br i1 %89, label %90, label %100

90:                                               ; preds = %87
  %91 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %92 = call i8* @hashmap_get(%struct.HashMap* noundef %91, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.3, i64 0, i64 0))
  %93 = icmp eq i8* %92, null
  br i1 %93, label %94, label %95

94:                                               ; preds = %90
  br label %96

95:                                               ; preds = %90
  call void @__assert_fail(i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 177, i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.hashmap_test, i64 0, i64 0)) #11
  unreachable

96:                                               ; preds = %94
  br label %97

97:                                               ; preds = %96
  %98 = load i32, i32* %7, align 4
  %99 = add nsw i32 %98, 1
  store i32 %99, i32* %7, align 4
  br label %87, !llvm.loop !14

100:                                              ; preds = %87
  store i32 1500, i32* %8, align 4
  br label %101

101:                                              ; preds = %116, %100
  %102 = load i32, i32* %8, align 4
  %103 = icmp slt i32 %102, 1600
  br i1 %103, label %104, label %119

104:                                              ; preds = %101
  %105 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %106 = load i32, i32* %8, align 4
  %107 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), i32 noundef %106)
  %108 = call i8* @hashmap_get(%struct.HashMap* noundef %105, i8* noundef %107)
  %109 = ptrtoint i8* %108 to i64
  %110 = load i32, i32* %8, align 4
  %111 = sext i32 %110 to i64
  %112 = icmp eq i64 %109, %111
  br i1 %112, label %113, label %114

113:                                              ; preds = %104
  br label %115

114:                                              ; preds = %104
  call void @__assert_fail(i8* noundef getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 179, i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.hashmap_test, i64 0, i64 0)) #11
  unreachable

115:                                              ; preds = %113
  br label %116

116:                                              ; preds = %115
  %117 = load i32, i32* %8, align 4
  %118 = add nsw i32 %117, 1
  store i32 %118, i32* %8, align 4
  br label %101, !llvm.loop !15

119:                                              ; preds = %101
  store i32 1600, i32* %9, align 4
  br label %120

120:                                              ; preds = %130, %119
  %121 = load i32, i32* %9, align 4
  %122 = icmp slt i32 %121, 2000
  br i1 %122, label %123, label %133

123:                                              ; preds = %120
  %124 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %125 = call i8* @hashmap_get(%struct.HashMap* noundef %124, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.3, i64 0, i64 0))
  %126 = icmp eq i8* %125, null
  br i1 %126, label %127, label %128

127:                                              ; preds = %123
  br label %129

128:                                              ; preds = %123
  call void @__assert_fail(i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 181, i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.hashmap_test, i64 0, i64 0)) #11
  unreachable

129:                                              ; preds = %127
  br label %130

130:                                              ; preds = %129
  %131 = load i32, i32* %9, align 4
  %132 = add nsw i32 %131, 1
  store i32 %132, i32* %9, align 4
  br label %120, !llvm.loop !16

133:                                              ; preds = %120
  store i32 2000, i32* %10, align 4
  br label %134

134:                                              ; preds = %149, %133
  %135 = load i32, i32* %10, align 4
  %136 = icmp slt i32 %135, 5000
  br i1 %136, label %137, label %152

137:                                              ; preds = %134
  %138 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %139 = load i32, i32* %10, align 4
  %140 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), i32 noundef %139)
  %141 = call i8* @hashmap_get(%struct.HashMap* noundef %138, i8* noundef %140)
  %142 = ptrtoint i8* %141 to i64
  %143 = load i32, i32* %10, align 4
  %144 = sext i32 %143 to i64
  %145 = icmp eq i64 %142, %144
  br i1 %145, label %146, label %147

146:                                              ; preds = %137
  br label %148

147:                                              ; preds = %137
  call void @__assert_fail(i8* noundef getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 183, i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.hashmap_test, i64 0, i64 0)) #11
  unreachable

148:                                              ; preds = %146
  br label %149

149:                                              ; preds = %148
  %150 = load i32, i32* %10, align 4
  %151 = add nsw i32 %150, 1
  store i32 %151, i32* %10, align 4
  br label %134, !llvm.loop !17

152:                                              ; preds = %134
  store i32 5000, i32* %11, align 4
  br label %153

153:                                              ; preds = %163, %152
  %154 = load i32, i32* %11, align 4
  %155 = icmp slt i32 %154, 6000
  br i1 %155, label %156, label %166

156:                                              ; preds = %153
  %157 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %158 = call i8* @hashmap_get(%struct.HashMap* noundef %157, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.3, i64 0, i64 0))
  %159 = icmp eq i8* %158, null
  br i1 %159, label %160, label %161

160:                                              ; preds = %156
  br label %162

161:                                              ; preds = %156
  call void @__assert_fail(i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 185, i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.hashmap_test, i64 0, i64 0)) #11
  unreachable

162:                                              ; preds = %160
  br label %163

163:                                              ; preds = %162
  %164 = load i32, i32* %11, align 4
  %165 = add nsw i32 %164, 1
  store i32 %165, i32* %11, align 4
  br label %153, !llvm.loop !18

166:                                              ; preds = %153
  store i32 6000, i32* %12, align 4
  br label %167

167:                                              ; preds = %177, %166
  %168 = load i32, i32* %12, align 4
  %169 = icmp slt i32 %168, 7000
  br i1 %169, label %170, label %180

170:                                              ; preds = %167
  %171 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %172 = load i32, i32* %12, align 4
  %173 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), i32 noundef %172)
  %174 = load i32, i32* %12, align 4
  %175 = sext i32 %174 to i64
  %176 = inttoptr i64 %175 to i8*
  call void @hashmap_put(%struct.HashMap* noundef %171, i8* noundef %173, i8* noundef %176)
  br label %177

177:                                              ; preds = %170
  %178 = load i32, i32* %12, align 4
  %179 = add nsw i32 %178, 1
  store i32 %179, i32* %12, align 4
  br label %167, !llvm.loop !19

180:                                              ; preds = %167
  %181 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %182 = call i8* @hashmap_get(%struct.HashMap* noundef %181, i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.3, i64 0, i64 0))
  %183 = icmp eq i8* %182, null
  br i1 %183, label %184, label %185

184:                                              ; preds = %180
  br label %186

185:                                              ; preds = %180
  call void @__assert_fail(i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 189, i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.hashmap_test, i64 0, i64 0)) #11
  unreachable

186:                                              ; preds = %184
  %187 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0))
  %188 = load %struct.HashMap*, %struct.HashMap** %1, align 8
  %189 = bitcast %struct.HashMap* %188 to i8*
  call void @free(i8* noundef %189) #10
  ret void
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64 noundef, i64 noundef) #2

declare i8* @format(i8* noundef, ...) #3

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8* noundef, i8* noundef, i32 noundef, i8* noundef) #4

declare i32 @printf(i8* noundef, ...) #3

; Function Attrs: nounwind
declare void @free(i8* noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal i64 @fnv_hash(i8* noundef %0, i32 noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i64, align 8
  %6 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i32 %1, i32* %4, align 4
  store i64 -3750763034362895579, i64* %5, align 8
  store i32 0, i32* %6, align 4
  br label %7

7:                                                ; preds = %22, %2
  %8 = load i32, i32* %6, align 4
  %9 = load i32, i32* %4, align 4
  %10 = icmp slt i32 %8, %9
  br i1 %10, label %11, label %25

11:                                               ; preds = %7
  %12 = load i64, i64* %5, align 8
  %13 = mul i64 %12, 1099511628211
  store i64 %13, i64* %5, align 8
  %14 = load i8*, i8** %3, align 8
  %15 = load i32, i32* %6, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds i8, i8* %14, i64 %16
  %18 = load i8, i8* %17, align 1
  %19 = zext i8 %18 to i64
  %20 = load i64, i64* %5, align 8
  %21 = xor i64 %20, %19
  store i64 %21, i64* %5, align 8
  br label %22

22:                                               ; preds = %11
  %23 = load i32, i32* %6, align 4
  %24 = add nsw i32 %23, 1
  store i32 %24, i32* %6, align 4
  br label %7, !llvm.loop !20

25:                                               ; preds = %7
  %26 = load i64, i64* %5, align 8
  ret i64 %26
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @match(%struct.HashEntry* noundef %0, i8* noundef %1, i32 noundef %2) #0 {
  %4 = alloca %struct.HashEntry*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  store %struct.HashEntry* %0, %struct.HashEntry** %4, align 8
  store i8* %1, i8** %5, align 8
  store i32 %2, i32* %6, align 4
  %7 = load %struct.HashEntry*, %struct.HashEntry** %4, align 8
  %8 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %7, i32 0, i32 0
  %9 = load i8*, i8** %8, align 8
  %10 = icmp ne i8* %9, null
  br i1 %10, label %11, label %31

11:                                               ; preds = %3
  %12 = load %struct.HashEntry*, %struct.HashEntry** %4, align 8
  %13 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %12, i32 0, i32 0
  %14 = load i8*, i8** %13, align 8
  %15 = icmp ne i8* %14, inttoptr (i64 -1 to i8*)
  br i1 %15, label %16, label %31

16:                                               ; preds = %11
  %17 = load %struct.HashEntry*, %struct.HashEntry** %4, align 8
  %18 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %17, i32 0, i32 1
  %19 = load i32, i32* %18, align 8
  %20 = load i32, i32* %6, align 4
  %21 = icmp eq i32 %19, %20
  br i1 %21, label %22, label %31

22:                                               ; preds = %16
  %23 = load %struct.HashEntry*, %struct.HashEntry** %4, align 8
  %24 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %23, i32 0, i32 0
  %25 = load i8*, i8** %24, align 8
  %26 = load i8*, i8** %5, align 8
  %27 = load i32, i32* %6, align 4
  %28 = sext i32 %27 to i64
  %29 = call i32 @memcmp(i8* noundef %25, i8* noundef %26, i64 noundef %28) #8
  %30 = icmp eq i32 %29, 0
  br label %31

31:                                               ; preds = %22, %16, %11, %3
  %32 = phi i1 [ false, %16 ], [ false, %11 ], [ false, %3 ], [ %30, %22 ]
  ret i1 %32
}

; Function Attrs: noreturn
declare void @error(i8* noundef, ...) #5

; Function Attrs: nounwind readonly willreturn
declare i32 @memcmp(i8* noundef, i8* noundef, i64 noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal void @rehash(%struct.HashMap* noundef %0) #0 {
  %2 = alloca %struct.HashMap*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca %struct.HashMap, align 8
  %7 = alloca i32, align 4
  %8 = alloca %struct.HashEntry*, align 8
  store %struct.HashMap* %0, %struct.HashMap** %2, align 8
  store i32 0, i32* %3, align 4
  store i32 0, i32* %4, align 4
  br label %9

9:                                                ; preds = %39, %1
  %10 = load i32, i32* %4, align 4
  %11 = load %struct.HashMap*, %struct.HashMap** %2, align 8
  %12 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %11, i32 0, i32 1
  %13 = load i32, i32* %12, align 8
  %14 = icmp slt i32 %10, %13
  br i1 %14, label %15, label %42

15:                                               ; preds = %9
  %16 = load %struct.HashMap*, %struct.HashMap** %2, align 8
  %17 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %16, i32 0, i32 0
  %18 = load %struct.HashEntry*, %struct.HashEntry** %17, align 8
  %19 = load i32, i32* %4, align 4
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %18, i64 %20
  %22 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %21, i32 0, i32 0
  %23 = load i8*, i8** %22, align 8
  %24 = icmp ne i8* %23, null
  br i1 %24, label %25, label %38

25:                                               ; preds = %15
  %26 = load %struct.HashMap*, %struct.HashMap** %2, align 8
  %27 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %26, i32 0, i32 0
  %28 = load %struct.HashEntry*, %struct.HashEntry** %27, align 8
  %29 = load i32, i32* %4, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %28, i64 %30
  %32 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %31, i32 0, i32 0
  %33 = load i8*, i8** %32, align 8
  %34 = icmp ne i8* %33, inttoptr (i64 -1 to i8*)
  br i1 %34, label %35, label %38

35:                                               ; preds = %25
  %36 = load i32, i32* %3, align 4
  %37 = add nsw i32 %36, 1
  store i32 %37, i32* %3, align 4
  br label %38

38:                                               ; preds = %35, %25, %15
  br label %39

39:                                               ; preds = %38
  %40 = load i32, i32* %4, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* %4, align 4
  br label %9, !llvm.loop !21

42:                                               ; preds = %9
  %43 = load %struct.HashMap*, %struct.HashMap** %2, align 8
  %44 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %43, i32 0, i32 1
  %45 = load i32, i32* %44, align 8
  store i32 %45, i32* %5, align 4
  br label %46

46:                                               ; preds = %52, %42
  %47 = load i32, i32* %3, align 4
  %48 = mul nsw i32 %47, 100
  %49 = load i32, i32* %5, align 4
  %50 = sdiv i32 %48, %49
  %51 = icmp sge i32 %50, 50
  br i1 %51, label %52, label %55

52:                                               ; preds = %46
  %53 = load i32, i32* %5, align 4
  %54 = mul nsw i32 %53, 2
  store i32 %54, i32* %5, align 4
  br label %46, !llvm.loop !22

55:                                               ; preds = %46
  %56 = load i32, i32* %5, align 4
  %57 = icmp sgt i32 %56, 0
  br i1 %57, label %58, label %59

58:                                               ; preds = %55
  br label %60

59:                                               ; preds = %55
  call void @__assert_fail(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.8, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 42, i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @__PRETTY_FUNCTION__.rehash, i64 0, i64 0)) #11
  unreachable

60:                                               ; preds = %58
  %61 = bitcast %struct.HashMap* %6 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %61, i8 0, i64 16, i1 false)
  %62 = load i32, i32* %5, align 4
  %63 = sext i32 %62 to i64
  %64 = call noalias i8* @calloc(i64 noundef %63, i64 noundef 24) #10
  %65 = bitcast i8* %64 to %struct.HashEntry*
  %66 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %6, i32 0, i32 0
  store %struct.HashEntry* %65, %struct.HashEntry** %66, align 8
  %67 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %6, i32 0, i32 0
  %68 = load %struct.HashEntry*, %struct.HashEntry** %67, align 8
  %69 = icmp eq %struct.HashEntry* %68, null
  br i1 %69, label %70, label %71

70:                                               ; preds = %60
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.9, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0)) #9
  unreachable

71:                                               ; preds = %60
  %72 = load i32, i32* %5, align 4
  %73 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %6, i32 0, i32 1
  store i32 %72, i32* %73, align 8
  store i32 0, i32* %7, align 4
  br label %74

74:                                               ; preds = %107, %71
  %75 = load i32, i32* %7, align 4
  %76 = load %struct.HashMap*, %struct.HashMap** %2, align 8
  %77 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %76, i32 0, i32 1
  %78 = load i32, i32* %77, align 8
  %79 = icmp slt i32 %75, %78
  br i1 %79, label %80, label %110

80:                                               ; preds = %74
  %81 = load %struct.HashMap*, %struct.HashMap** %2, align 8
  %82 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %81, i32 0, i32 0
  %83 = load %struct.HashEntry*, %struct.HashEntry** %82, align 8
  %84 = load i32, i32* %7, align 4
  %85 = sext i32 %84 to i64
  %86 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %83, i64 %85
  store %struct.HashEntry* %86, %struct.HashEntry** %8, align 8
  %87 = load %struct.HashEntry*, %struct.HashEntry** %8, align 8
  %88 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %87, i32 0, i32 0
  %89 = load i8*, i8** %88, align 8
  %90 = icmp ne i8* %89, null
  br i1 %90, label %91, label %106

91:                                               ; preds = %80
  %92 = load %struct.HashEntry*, %struct.HashEntry** %8, align 8
  %93 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %92, i32 0, i32 0
  %94 = load i8*, i8** %93, align 8
  %95 = icmp ne i8* %94, inttoptr (i64 -1 to i8*)
  br i1 %95, label %96, label %106

96:                                               ; preds = %91
  %97 = load %struct.HashEntry*, %struct.HashEntry** %8, align 8
  %98 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %97, i32 0, i32 0
  %99 = load i8*, i8** %98, align 8
  %100 = load %struct.HashEntry*, %struct.HashEntry** %8, align 8
  %101 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %100, i32 0, i32 1
  %102 = load i32, i32* %101, align 8
  %103 = load %struct.HashEntry*, %struct.HashEntry** %8, align 8
  %104 = getelementptr inbounds %struct.HashEntry, %struct.HashEntry* %103, i32 0, i32 2
  %105 = load i8*, i8** %104, align 8
  call void @hashmap_put2(%struct.HashMap* noundef %6, i8* noundef %99, i32 noundef %102, i8* noundef %105)
  br label %106

106:                                              ; preds = %96, %91, %80
  br label %107

107:                                              ; preds = %106
  %108 = load i32, i32* %7, align 4
  %109 = add nsw i32 %108, 1
  store i32 %109, i32* %7, align 4
  br label %74, !llvm.loop !23

110:                                              ; preds = %74
  %111 = getelementptr inbounds %struct.HashMap, %struct.HashMap* %6, i32 0, i32 2
  %112 = load i32, i32* %111, align 4
  %113 = load i32, i32* %3, align 4
  %114 = icmp eq i32 %112, %113
  br i1 %114, label %115, label %116

115:                                              ; preds = %110
  br label %117

116:                                              ; preds = %110
  call void @__assert_fail(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.10, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 noundef 58, i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @__PRETTY_FUNCTION__.rehash, i64 0, i64 0)) #11
  unreachable

117:                                              ; preds = %115
  %118 = load %struct.HashMap*, %struct.HashMap** %2, align 8
  %119 = bitcast %struct.HashMap* %118 to i8*
  %120 = bitcast %struct.HashMap* %6 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %119, i8* align 8 %120, i64 16, i1 false)
  ret void
}

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #6

; Function Attrs: argmemonly nofree nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #7

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind readonly willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { argmemonly nofree nounwind willreturn writeonly }
attributes #7 = { argmemonly nofree nounwind willreturn }
attributes #8 = { nounwind readonly willreturn }
attributes #9 = { noreturn }
attributes #10 = { nounwind }
attributes #11 = { noreturn nounwind }

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
