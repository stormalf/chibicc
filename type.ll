; ModuleID = 'type.c'
source_filename = "type.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.Type = type { i32, i32, i32, i8, i8, i8, %struct.Type*, %struct.Type*, %struct.Type*, %struct.Token*, %struct.Token*, i32, %struct.Node*, %struct.Obj*, %struct.Member*, i8, i8, %struct.Type*, %struct.Type*, i8, %struct.Type* }
%struct.Token = type { i32, %struct.Token*, i64, x86_fp80, i8*, i32, %struct.Type*, i8*, %struct.File*, i8*, i32, i32, i8, i8, %struct.Hideset*, %struct.Token* }
%struct.File = type { i8*, i32, i8*, i8*, i32 }
%struct.Hideset = type opaque
%struct.Node = type { i32, %struct.Node*, %struct.Type*, %struct.Token*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, i8*, i8*, %struct.Node*, %struct.Member*, %struct.Type*, %struct.Node*, i8, %struct.Obj*, i8*, i8*, %struct.Node*, %struct.Node*, %struct.Node*, i64, i64, i8*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Obj*, %struct.Node*, i8, %struct.Obj*, i64, x86_fp80, i32, [12 x i8] }
%struct.Obj = type { %struct.Obj*, i8*, i8*, %struct.Type*, %struct.Token*, i8, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8*, %struct.Relocation*, i8, %struct.Obj*, %struct.Node*, %struct.Obj*, %struct.Obj*, %struct.Obj*, i32, i8, i8, %struct.StringArray }
%struct.Relocation = type { %struct.Relocation*, i32, i8**, i64 }
%struct.StringArray = type { i8**, i32, i32 }
%struct.Member = type { %struct.Member*, %struct.Type*, %struct.Token*, %struct.Token*, i32, i32, i32, i8, i32, i32 }

@.compoundliteral = internal global %struct.Type { i32 0, i32 1, i32 1, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_void = dso_local global %struct.Type* @.compoundliteral, align 8
@.compoundliteral.1 = internal global %struct.Type { i32 1, i32 1, i32 1, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_bool = dso_local global %struct.Type* @.compoundliteral.1, align 8
@.compoundliteral.2 = internal global %struct.Type { i32 2, i32 1, i32 1, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_char = dso_local global %struct.Type* @.compoundliteral.2, align 8
@.compoundliteral.3 = internal global %struct.Type { i32 3, i32 2, i32 2, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_short = dso_local global %struct.Type* @.compoundliteral.3, align 8
@.compoundliteral.4 = internal global %struct.Type { i32 4, i32 4, i32 4, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_int = dso_local global %struct.Type* @.compoundliteral.4, align 8
@.compoundliteral.5 = internal global %struct.Type { i32 5, i32 8, i32 8, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_long = dso_local global %struct.Type* @.compoundliteral.5, align 8
@.compoundliteral.6 = internal global %struct.Type { i32 2, i32 1, i32 1, i8 1, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_uchar = dso_local global %struct.Type* @.compoundliteral.6, align 8
@.compoundliteral.7 = internal global %struct.Type { i32 3, i32 2, i32 2, i8 1, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_ushort = dso_local global %struct.Type* @.compoundliteral.7, align 8
@.compoundliteral.8 = internal global %struct.Type { i32 4, i32 4, i32 4, i8 1, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_uint = dso_local global %struct.Type* @.compoundliteral.8, align 8
@.compoundliteral.9 = internal global %struct.Type { i32 5, i32 8, i32 8, i8 1, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_ulong = dso_local global %struct.Type* @.compoundliteral.9, align 8
@.compoundliteral.10 = internal global %struct.Type { i32 6, i32 4, i32 4, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_float = dso_local global %struct.Type* @.compoundliteral.10, align 8
@.compoundliteral.11 = internal global %struct.Type { i32 7, i32 8, i32 8, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_double = dso_local global %struct.Type* @.compoundliteral.11, align 8
@.compoundliteral.12 = internal global %struct.Type { i32 8, i32 16, i32 16, i8 0, i8 0, i8 0, %struct.Type* null, %struct.Type* null, %struct.Type* null, %struct.Token* null, %struct.Token* null, i32 0, %struct.Node* null, %struct.Obj* null, %struct.Member* null, i8 0, i8 0, %struct.Type* null, %struct.Type* null, i8 0, %struct.Type* null }, align 8
@ty_ldouble = dso_local global %struct.Type* @.compoundliteral.12, align 8
@.str = private unnamed_addr constant [30 x i8] c"%s: in copy_type ret is null!\00", align 1
@.str.13 = private unnamed_addr constant [7 x i8] c"type.c\00", align 1
@.str.14 = private unnamed_addr constant [17 x i8] c"%s not an lvalue\00", align 1
@.str.15 = private unnamed_addr constant [31 x i8] c"%s invalid pointer dereference\00", align 1
@.str.16 = private unnamed_addr constant [32 x i8] c"%s dereferencing a void pointer\00", align 1
@.str.17 = private unnamed_addr constant [56 x i8] c"%s statement expression returning void is not supported\00", align 1
@.str.18 = private unnamed_addr constant [20 x i8] c"%s pointer expected\00", align 1
@.str.19 = private unnamed_addr constant [28 x i8] c"%s: in new_type ty is null!\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @is_integer(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca i32, align 4
  store %struct.Type* %0, %struct.Type** %2, align 8
  %4 = load %struct.Type*, %struct.Type** %2, align 8
  %5 = getelementptr inbounds %struct.Type, %struct.Type* %4, i32 0, i32 0
  %6 = load i32, i32* %5, align 8
  store i32 %6, i32* %3, align 4
  %7 = load i32, i32* %3, align 4
  %8 = icmp eq i32 %7, 1
  br i1 %8, label %24, label %9

9:                                                ; preds = %1
  %10 = load i32, i32* %3, align 4
  %11 = icmp eq i32 %10, 2
  br i1 %11, label %24, label %12

12:                                               ; preds = %9
  %13 = load i32, i32* %3, align 4
  %14 = icmp eq i32 %13, 3
  br i1 %14, label %24, label %15

15:                                               ; preds = %12
  %16 = load i32, i32* %3, align 4
  %17 = icmp eq i32 %16, 4
  br i1 %17, label %24, label %18

18:                                               ; preds = %15
  %19 = load i32, i32* %3, align 4
  %20 = icmp eq i32 %19, 5
  br i1 %20, label %24, label %21

21:                                               ; preds = %18
  %22 = load i32, i32* %3, align 4
  %23 = icmp eq i32 %22, 9
  br label %24

24:                                               ; preds = %21, %18, %15, %12, %9, %1
  %25 = phi i1 [ true, %18 ], [ true, %15 ], [ true, %12 ], [ true, %9 ], [ true, %1 ], [ %23, %21 ]
  ret i1 %25
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @is_flonum(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %3 = load %struct.Type*, %struct.Type** %2, align 8
  %4 = getelementptr inbounds %struct.Type, %struct.Type* %3, i32 0, i32 0
  %5 = load i32, i32* %4, align 8
  %6 = icmp eq i32 %5, 6
  br i1 %6, label %17, label %7

7:                                                ; preds = %1
  %8 = load %struct.Type*, %struct.Type** %2, align 8
  %9 = getelementptr inbounds %struct.Type, %struct.Type* %8, i32 0, i32 0
  %10 = load i32, i32* %9, align 8
  %11 = icmp eq i32 %10, 7
  br i1 %11, label %17, label %12

12:                                               ; preds = %7
  %13 = load %struct.Type*, %struct.Type** %2, align 8
  %14 = getelementptr inbounds %struct.Type, %struct.Type* %13, i32 0, i32 0
  %15 = load i32, i32* %14, align 8
  %16 = icmp eq i32 %15, 8
  br label %17

17:                                               ; preds = %12, %7, %1
  %18 = phi i1 [ true, %7 ], [ true, %1 ], [ %16, %12 ]
  ret i1 %18
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @is_numeric(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %3 = load %struct.Type*, %struct.Type** %2, align 8
  %4 = call zeroext i1 @is_integer(%struct.Type* noundef %3)
  br i1 %4, label %8, label %5

5:                                                ; preds = %1
  %6 = load %struct.Type*, %struct.Type** %2, align 8
  %7 = call zeroext i1 @is_flonum(%struct.Type* noundef %6)
  br label %8

8:                                                ; preds = %5, %1
  %9 = phi i1 [ true, %1 ], [ %7, %5 ]
  ret i1 %9
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @is_compatible(%struct.Type* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca i1, align 1
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Type*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %4, align 8
  store %struct.Type* %1, %struct.Type** %5, align 8
  %8 = load %struct.Type*, %struct.Type** %4, align 8
  %9 = load %struct.Type*, %struct.Type** %5, align 8
  %10 = icmp eq %struct.Type* %8, %9
  br i1 %10, label %11, label %12

11:                                               ; preds = %2
  store i1 true, i1* %3, align 1
  br label %156

12:                                               ; preds = %2
  %13 = load %struct.Type*, %struct.Type** %4, align 8
  %14 = getelementptr inbounds %struct.Type, %struct.Type* %13, i32 0, i32 7
  %15 = load %struct.Type*, %struct.Type** %14, align 8
  %16 = icmp ne %struct.Type* %15, null
  br i1 %16, label %17, label %23

17:                                               ; preds = %12
  %18 = load %struct.Type*, %struct.Type** %4, align 8
  %19 = getelementptr inbounds %struct.Type, %struct.Type* %18, i32 0, i32 7
  %20 = load %struct.Type*, %struct.Type** %19, align 8
  %21 = load %struct.Type*, %struct.Type** %5, align 8
  %22 = call zeroext i1 @is_compatible(%struct.Type* noundef %20, %struct.Type* noundef %21)
  store i1 %22, i1* %3, align 1
  br label %156

23:                                               ; preds = %12
  %24 = load %struct.Type*, %struct.Type** %5, align 8
  %25 = getelementptr inbounds %struct.Type, %struct.Type* %24, i32 0, i32 7
  %26 = load %struct.Type*, %struct.Type** %25, align 8
  %27 = icmp ne %struct.Type* %26, null
  br i1 %27, label %28, label %34

28:                                               ; preds = %23
  %29 = load %struct.Type*, %struct.Type** %4, align 8
  %30 = load %struct.Type*, %struct.Type** %5, align 8
  %31 = getelementptr inbounds %struct.Type, %struct.Type* %30, i32 0, i32 7
  %32 = load %struct.Type*, %struct.Type** %31, align 8
  %33 = call zeroext i1 @is_compatible(%struct.Type* noundef %29, %struct.Type* noundef %32)
  store i1 %33, i1* %3, align 1
  br label %156

34:                                               ; preds = %23
  %35 = load %struct.Type*, %struct.Type** %4, align 8
  %36 = getelementptr inbounds %struct.Type, %struct.Type* %35, i32 0, i32 0
  %37 = load i32, i32* %36, align 8
  %38 = load %struct.Type*, %struct.Type** %5, align 8
  %39 = getelementptr inbounds %struct.Type, %struct.Type* %38, i32 0, i32 0
  %40 = load i32, i32* %39, align 8
  %41 = icmp ne i32 %37, %40
  br i1 %41, label %42, label %43

42:                                               ; preds = %34
  store i1 false, i1* %3, align 1
  br label %156

43:                                               ; preds = %34
  %44 = load %struct.Type*, %struct.Type** %4, align 8
  %45 = getelementptr inbounds %struct.Type, %struct.Type* %44, i32 0, i32 0
  %46 = load i32, i32* %45, align 8
  switch i32 %46, label %155 [
    i32 2, label %47
    i32 3, label %47
    i32 4, label %47
    i32 5, label %47
    i32 6, label %59
    i32 7, label %59
    i32 8, label %59
    i32 10, label %60
    i32 11, label %68
    i32 12, label %126
  ]

47:                                               ; preds = %43, %43, %43, %43
  %48 = load %struct.Type*, %struct.Type** %4, align 8
  %49 = getelementptr inbounds %struct.Type, %struct.Type* %48, i32 0, i32 3
  %50 = load i8, i8* %49, align 4
  %51 = trunc i8 %50 to i1
  %52 = zext i1 %51 to i32
  %53 = load %struct.Type*, %struct.Type** %5, align 8
  %54 = getelementptr inbounds %struct.Type, %struct.Type* %53, i32 0, i32 3
  %55 = load i8, i8* %54, align 4
  %56 = trunc i8 %55 to i1
  %57 = zext i1 %56 to i32
  %58 = icmp eq i32 %52, %57
  store i1 %58, i1* %3, align 1
  br label %156

59:                                               ; preds = %43, %43, %43
  store i1 true, i1* %3, align 1
  br label %156

60:                                               ; preds = %43
  %61 = load %struct.Type*, %struct.Type** %4, align 8
  %62 = getelementptr inbounds %struct.Type, %struct.Type* %61, i32 0, i32 8
  %63 = load %struct.Type*, %struct.Type** %62, align 8
  %64 = load %struct.Type*, %struct.Type** %5, align 8
  %65 = getelementptr inbounds %struct.Type, %struct.Type* %64, i32 0, i32 8
  %66 = load %struct.Type*, %struct.Type** %65, align 8
  %67 = call zeroext i1 @is_compatible(%struct.Type* noundef %63, %struct.Type* noundef %66)
  store i1 %67, i1* %3, align 1
  br label %156

68:                                               ; preds = %43
  %69 = load %struct.Type*, %struct.Type** %4, align 8
  %70 = getelementptr inbounds %struct.Type, %struct.Type* %69, i32 0, i32 17
  %71 = load %struct.Type*, %struct.Type** %70, align 8
  %72 = load %struct.Type*, %struct.Type** %5, align 8
  %73 = getelementptr inbounds %struct.Type, %struct.Type* %72, i32 0, i32 17
  %74 = load %struct.Type*, %struct.Type** %73, align 8
  %75 = call zeroext i1 @is_compatible(%struct.Type* noundef %71, %struct.Type* noundef %74)
  br i1 %75, label %77, label %76

76:                                               ; preds = %68
  store i1 false, i1* %3, align 1
  br label %156

77:                                               ; preds = %68
  %78 = load %struct.Type*, %struct.Type** %4, align 8
  %79 = getelementptr inbounds %struct.Type, %struct.Type* %78, i32 0, i32 19
  %80 = load i8, i8* %79, align 8
  %81 = trunc i8 %80 to i1
  %82 = zext i1 %81 to i32
  %83 = load %struct.Type*, %struct.Type** %5, align 8
  %84 = getelementptr inbounds %struct.Type, %struct.Type* %83, i32 0, i32 19
  %85 = load i8, i8* %84, align 8
  %86 = trunc i8 %85 to i1
  %87 = zext i1 %86 to i32
  %88 = icmp ne i32 %82, %87
  br i1 %88, label %89, label %90

89:                                               ; preds = %77
  store i1 false, i1* %3, align 1
  br label %156

90:                                               ; preds = %77
  %91 = load %struct.Type*, %struct.Type** %4, align 8
  %92 = getelementptr inbounds %struct.Type, %struct.Type* %91, i32 0, i32 18
  %93 = load %struct.Type*, %struct.Type** %92, align 8
  store %struct.Type* %93, %struct.Type** %6, align 8
  %94 = load %struct.Type*, %struct.Type** %5, align 8
  %95 = getelementptr inbounds %struct.Type, %struct.Type* %94, i32 0, i32 18
  %96 = load %struct.Type*, %struct.Type** %95, align 8
  store %struct.Type* %96, %struct.Type** %7, align 8
  br label %97

97:                                               ; preds = %111, %90
  %98 = load %struct.Type*, %struct.Type** %6, align 8
  %99 = icmp ne %struct.Type* %98, null
  br i1 %99, label %100, label %103

100:                                              ; preds = %97
  %101 = load %struct.Type*, %struct.Type** %7, align 8
  %102 = icmp ne %struct.Type* %101, null
  br label %103

103:                                              ; preds = %100, %97
  %104 = phi i1 [ false, %97 ], [ %102, %100 ]
  br i1 %104, label %105, label %118

105:                                              ; preds = %103
  %106 = load %struct.Type*, %struct.Type** %6, align 8
  %107 = load %struct.Type*, %struct.Type** %7, align 8
  %108 = call zeroext i1 @is_compatible(%struct.Type* noundef %106, %struct.Type* noundef %107)
  br i1 %108, label %110, label %109

109:                                              ; preds = %105
  store i1 false, i1* %3, align 1
  br label %156

110:                                              ; preds = %105
  br label %111

111:                                              ; preds = %110
  %112 = load %struct.Type*, %struct.Type** %6, align 8
  %113 = getelementptr inbounds %struct.Type, %struct.Type* %112, i32 0, i32 20
  %114 = load %struct.Type*, %struct.Type** %113, align 8
  store %struct.Type* %114, %struct.Type** %6, align 8
  %115 = load %struct.Type*, %struct.Type** %7, align 8
  %116 = getelementptr inbounds %struct.Type, %struct.Type* %115, i32 0, i32 20
  %117 = load %struct.Type*, %struct.Type** %116, align 8
  store %struct.Type* %117, %struct.Type** %7, align 8
  br label %97, !llvm.loop !6

118:                                              ; preds = %103
  %119 = load %struct.Type*, %struct.Type** %6, align 8
  %120 = icmp eq %struct.Type* %119, null
  br i1 %120, label %121, label %124

121:                                              ; preds = %118
  %122 = load %struct.Type*, %struct.Type** %7, align 8
  %123 = icmp eq %struct.Type* %122, null
  br label %124

124:                                              ; preds = %121, %118
  %125 = phi i1 [ false, %118 ], [ %123, %121 ]
  store i1 %125, i1* %3, align 1
  br label %156

126:                                              ; preds = %43
  %127 = load %struct.Type*, %struct.Type** %4, align 8
  %128 = getelementptr inbounds %struct.Type, %struct.Type* %127, i32 0, i32 8
  %129 = load %struct.Type*, %struct.Type** %128, align 8
  %130 = load %struct.Type*, %struct.Type** %5, align 8
  %131 = getelementptr inbounds %struct.Type, %struct.Type* %130, i32 0, i32 8
  %132 = load %struct.Type*, %struct.Type** %131, align 8
  %133 = call zeroext i1 @is_compatible(%struct.Type* noundef %129, %struct.Type* noundef %132)
  br i1 %133, label %135, label %134

134:                                              ; preds = %126
  store i1 false, i1* %3, align 1
  br label %156

135:                                              ; preds = %126
  %136 = load %struct.Type*, %struct.Type** %4, align 8
  %137 = getelementptr inbounds %struct.Type, %struct.Type* %136, i32 0, i32 11
  %138 = load i32, i32* %137, align 8
  %139 = icmp slt i32 %138, 0
  br i1 %139, label %140, label %153

140:                                              ; preds = %135
  %141 = load %struct.Type*, %struct.Type** %5, align 8
  %142 = getelementptr inbounds %struct.Type, %struct.Type* %141, i32 0, i32 11
  %143 = load i32, i32* %142, align 8
  %144 = icmp slt i32 %143, 0
  br i1 %144, label %145, label %153

145:                                              ; preds = %140
  %146 = load %struct.Type*, %struct.Type** %4, align 8
  %147 = getelementptr inbounds %struct.Type, %struct.Type* %146, i32 0, i32 11
  %148 = load i32, i32* %147, align 8
  %149 = load %struct.Type*, %struct.Type** %5, align 8
  %150 = getelementptr inbounds %struct.Type, %struct.Type* %149, i32 0, i32 11
  %151 = load i32, i32* %150, align 8
  %152 = icmp eq i32 %148, %151
  br label %153

153:                                              ; preds = %145, %140, %135
  %154 = phi i1 [ false, %140 ], [ false, %135 ], [ %152, %145 ]
  store i1 %154, i1* %3, align 1
  br label %156

155:                                              ; preds = %43
  store i1 false, i1* %3, align 1
  br label %156

156:                                              ; preds = %155, %153, %134, %124, %109, %89, %76, %60, %59, %47, %42, %28, %17, %11
  %157 = load i1, i1* %3, align 1
  ret i1 %157
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Type* @copy_type(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %4 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 128) #5
  %5 = bitcast i8* %4 to %struct.Type*
  store %struct.Type* %5, %struct.Type** %3, align 8
  %6 = load %struct.Type*, %struct.Type** %3, align 8
  %7 = icmp eq %struct.Type* %6, null
  br i1 %7, label %8, label %9

8:                                                ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

9:                                                ; preds = %1
  %10 = load %struct.Type*, %struct.Type** %3, align 8
  %11 = load %struct.Type*, %struct.Type** %2, align 8
  %12 = bitcast %struct.Type* %10 to i8*
  %13 = bitcast %struct.Type* %11 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %12, i8* align 8 %13, i64 128, i1 false)
  %14 = load %struct.Type*, %struct.Type** %2, align 8
  %15 = load %struct.Type*, %struct.Type** %3, align 8
  %16 = getelementptr inbounds %struct.Type, %struct.Type* %15, i32 0, i32 7
  store %struct.Type* %14, %struct.Type** %16, align 8
  %17 = load %struct.Type*, %struct.Type** %3, align 8
  ret %struct.Type* %17
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64 noundef, i64 noundef) #1

; Function Attrs: noreturn
declare void @error(i8* noundef, ...) #2

; Function Attrs: argmemonly nofree nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Type* @pointer_to(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %4 = call %struct.Type* @new_type(i32 noundef 10, i32 noundef 8, i32 noundef 8)
  store %struct.Type* %4, %struct.Type** %3, align 8
  %5 = load %struct.Type*, %struct.Type** %2, align 8
  %6 = load %struct.Type*, %struct.Type** %3, align 8
  %7 = getelementptr inbounds %struct.Type, %struct.Type* %6, i32 0, i32 8
  store %struct.Type* %5, %struct.Type** %7, align 8
  %8 = load %struct.Type*, %struct.Type** %3, align 8
  %9 = getelementptr inbounds %struct.Type, %struct.Type* %8, i32 0, i32 3
  store i8 1, i8* %9, align 4
  %10 = load %struct.Type*, %struct.Type** %3, align 8
  ret %struct.Type* %10
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @new_type(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca %struct.Type*, align 8
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  %8 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 128) #5
  %9 = bitcast i8* %8 to %struct.Type*
  store %struct.Type* %9, %struct.Type** %7, align 8
  %10 = load %struct.Type*, %struct.Type** %7, align 8
  %11 = icmp eq %struct.Type* %10, null
  br i1 %11, label %12, label %13

12:                                               ; preds = %3
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @.str.19, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

13:                                               ; preds = %3
  %14 = load i32, i32* %4, align 4
  %15 = load %struct.Type*, %struct.Type** %7, align 8
  %16 = getelementptr inbounds %struct.Type, %struct.Type* %15, i32 0, i32 0
  store i32 %14, i32* %16, align 8
  %17 = load i32, i32* %5, align 4
  %18 = load %struct.Type*, %struct.Type** %7, align 8
  %19 = getelementptr inbounds %struct.Type, %struct.Type* %18, i32 0, i32 1
  store i32 %17, i32* %19, align 4
  %20 = load i32, i32* %6, align 4
  %21 = load %struct.Type*, %struct.Type** %7, align 8
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 2
  store i32 %20, i32* %22, align 8
  %23 = load %struct.Type*, %struct.Type** %7, align 8
  ret %struct.Type* %23
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Type* @func_type(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %4 = call %struct.Type* @new_type(i32 noundef 11, i32 noundef 1, i32 noundef 1)
  store %struct.Type* %4, %struct.Type** %3, align 8
  %5 = load %struct.Type*, %struct.Type** %2, align 8
  %6 = load %struct.Type*, %struct.Type** %3, align 8
  %7 = getelementptr inbounds %struct.Type, %struct.Type* %6, i32 0, i32 17
  store %struct.Type* %5, %struct.Type** %7, align 8
  %8 = load %struct.Type*, %struct.Type** %3, align 8
  ret %struct.Type* %8
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Type* @array_of(%struct.Type* noundef %0, i32 noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca i32, align 4
  %5 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %3, align 8
  store i32 %1, i32* %4, align 4
  %6 = load %struct.Type*, %struct.Type** %3, align 8
  %7 = getelementptr inbounds %struct.Type, %struct.Type* %6, i32 0, i32 1
  %8 = load i32, i32* %7, align 4
  %9 = load i32, i32* %4, align 4
  %10 = mul nsw i32 %8, %9
  %11 = load %struct.Type*, %struct.Type** %3, align 8
  %12 = getelementptr inbounds %struct.Type, %struct.Type* %11, i32 0, i32 2
  %13 = load i32, i32* %12, align 8
  %14 = call %struct.Type* @new_type(i32 noundef 12, i32 noundef %10, i32 noundef %13)
  store %struct.Type* %14, %struct.Type** %5, align 8
  %15 = load %struct.Type*, %struct.Type** %3, align 8
  %16 = load %struct.Type*, %struct.Type** %5, align 8
  %17 = getelementptr inbounds %struct.Type, %struct.Type* %16, i32 0, i32 8
  store %struct.Type* %15, %struct.Type** %17, align 8
  %18 = load i32, i32* %4, align 4
  %19 = load %struct.Type*, %struct.Type** %5, align 8
  %20 = getelementptr inbounds %struct.Type, %struct.Type* %19, i32 0, i32 11
  store i32 %18, i32* %20, align 8
  %21 = load %struct.Type*, %struct.Type** %5, align 8
  ret %struct.Type* %21
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Type* @vla_of(%struct.Type* noundef %0, %struct.Node* noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca %struct.Node*, align 8
  %5 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %3, align 8
  store %struct.Node* %1, %struct.Node** %4, align 8
  %6 = call %struct.Type* @new_type(i32 noundef 13, i32 noundef 8, i32 noundef 8)
  store %struct.Type* %6, %struct.Type** %5, align 8
  %7 = load %struct.Type*, %struct.Type** %3, align 8
  %8 = load %struct.Type*, %struct.Type** %5, align 8
  %9 = getelementptr inbounds %struct.Type, %struct.Type* %8, i32 0, i32 8
  store %struct.Type* %7, %struct.Type** %9, align 8
  %10 = load %struct.Node*, %struct.Node** %4, align 8
  %11 = load %struct.Type*, %struct.Type** %5, align 8
  %12 = getelementptr inbounds %struct.Type, %struct.Type* %11, i32 0, i32 12
  store %struct.Node* %10, %struct.Node** %12, align 8
  %13 = load %struct.Type*, %struct.Type** %5, align 8
  ret %struct.Type* %13
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Type* @enum_type() #0 {
  %1 = call %struct.Type* @new_type(i32 noundef 9, i32 noundef 4, i32 noundef 4)
  ret %struct.Type* %1
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Type* @struct_type() #0 {
  %1 = call %struct.Type* @new_type(i32 noundef 14, i32 noundef 0, i32 noundef 1)
  ret %struct.Type* %1
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @add_type(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Node*, align 8
  %5 = alloca %struct.Type*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %2, align 8
  %8 = load %struct.Node*, %struct.Node** %2, align 8
  %9 = icmp ne %struct.Node* %8, null
  br i1 %9, label %10, label %15

10:                                               ; preds = %1
  %11 = load %struct.Node*, %struct.Node** %2, align 8
  %12 = getelementptr inbounds %struct.Node, %struct.Node* %11, i32 0, i32 2
  %13 = load %struct.Type*, %struct.Type** %12, align 16
  %14 = icmp ne %struct.Type* %13, null
  br i1 %14, label %15, label %16

15:                                               ; preds = %10, %1
  br label %412

16:                                               ; preds = %10
  %17 = load %struct.Node*, %struct.Node** %2, align 8
  %18 = getelementptr inbounds %struct.Node, %struct.Node* %17, i32 0, i32 4
  %19 = load %struct.Node*, %struct.Node** %18, align 16
  call void @add_type(%struct.Node* noundef %19)
  %20 = load %struct.Node*, %struct.Node** %2, align 8
  %21 = getelementptr inbounds %struct.Node, %struct.Node* %20, i32 0, i32 5
  %22 = load %struct.Node*, %struct.Node** %21, align 8
  call void @add_type(%struct.Node* noundef %22)
  %23 = load %struct.Node*, %struct.Node** %2, align 8
  %24 = getelementptr inbounds %struct.Node, %struct.Node* %23, i32 0, i32 6
  %25 = load %struct.Node*, %struct.Node** %24, align 16
  call void @add_type(%struct.Node* noundef %25)
  %26 = load %struct.Node*, %struct.Node** %2, align 8
  %27 = getelementptr inbounds %struct.Node, %struct.Node* %26, i32 0, i32 7
  %28 = load %struct.Node*, %struct.Node** %27, align 8
  call void @add_type(%struct.Node* noundef %28)
  %29 = load %struct.Node*, %struct.Node** %2, align 8
  %30 = getelementptr inbounds %struct.Node, %struct.Node* %29, i32 0, i32 8
  %31 = load %struct.Node*, %struct.Node** %30, align 16
  call void @add_type(%struct.Node* noundef %31)
  %32 = load %struct.Node*, %struct.Node** %2, align 8
  %33 = getelementptr inbounds %struct.Node, %struct.Node* %32, i32 0, i32 9
  %34 = load %struct.Node*, %struct.Node** %33, align 8
  call void @add_type(%struct.Node* noundef %34)
  %35 = load %struct.Node*, %struct.Node** %2, align 8
  %36 = getelementptr inbounds %struct.Node, %struct.Node* %35, i32 0, i32 10
  %37 = load %struct.Node*, %struct.Node** %36, align 16
  call void @add_type(%struct.Node* noundef %37)
  %38 = load %struct.Node*, %struct.Node** %2, align 8
  %39 = getelementptr inbounds %struct.Node, %struct.Node* %38, i32 0, i32 13
  %40 = load %struct.Node*, %struct.Node** %39, align 8
  store %struct.Node* %40, %struct.Node** %3, align 8
  br label %41

41:                                               ; preds = %46, %16
  %42 = load %struct.Node*, %struct.Node** %3, align 8
  %43 = icmp ne %struct.Node* %42, null
  br i1 %43, label %44, label %50

44:                                               ; preds = %41
  %45 = load %struct.Node*, %struct.Node** %3, align 8
  call void @add_type(%struct.Node* noundef %45)
  br label %46

46:                                               ; preds = %44
  %47 = load %struct.Node*, %struct.Node** %3, align 8
  %48 = getelementptr inbounds %struct.Node, %struct.Node* %47, i32 0, i32 1
  %49 = load %struct.Node*, %struct.Node** %48, align 8
  store %struct.Node* %49, %struct.Node** %3, align 8
  br label %41, !llvm.loop !8

50:                                               ; preds = %41
  %51 = load %struct.Node*, %struct.Node** %2, align 8
  %52 = getelementptr inbounds %struct.Node, %struct.Node* %51, i32 0, i32 16
  %53 = load %struct.Node*, %struct.Node** %52, align 16
  store %struct.Node* %53, %struct.Node** %4, align 8
  br label %54

54:                                               ; preds = %59, %50
  %55 = load %struct.Node*, %struct.Node** %4, align 8
  %56 = icmp ne %struct.Node* %55, null
  br i1 %56, label %57, label %63

57:                                               ; preds = %54
  %58 = load %struct.Node*, %struct.Node** %4, align 8
  call void @add_type(%struct.Node* noundef %58)
  br label %59

59:                                               ; preds = %57
  %60 = load %struct.Node*, %struct.Node** %4, align 8
  %61 = getelementptr inbounds %struct.Node, %struct.Node* %60, i32 0, i32 1
  %62 = load %struct.Node*, %struct.Node** %61, align 8
  store %struct.Node* %62, %struct.Node** %4, align 8
  br label %54, !llvm.loop !9

63:                                               ; preds = %54
  %64 = load %struct.Node*, %struct.Node** %2, align 8
  %65 = getelementptr inbounds %struct.Node, %struct.Node* %64, i32 0, i32 0
  %66 = load i32, i32* %65, align 16
  switch i32 %66, label %412 [
    i32 42, label %67
    i32 1, label %71
    i32 2, label %71
    i32 3, label %71
    i32 4, label %71
    i32 6, label %71
    i32 7, label %71
    i32 8, label %71
    i32 9, label %71
    i32 5, label %83
    i32 16, label %101
    i32 12, label %145
    i32 13, label %145
    i32 14, label %145
    i32 15, label %145
    i32 37, label %153
    i32 22, label %161
    i32 25, label %161
    i32 24, label %161
    i32 23, label %165
    i32 10, label %165
    i32 11, label %165
    i32 40, label %173
    i32 41, label %173
    i32 17, label %181
    i32 18, label %216
    i32 19, label %224
    i32 20, label %232
    i32 21, label %255
    i32 39, label %293
    i32 36, label %339
    i32 46, label %344
    i32 47, label %387
  ]

67:                                               ; preds = %63
  %68 = load %struct.Type*, %struct.Type** @ty_int, align 8
  %69 = load %struct.Node*, %struct.Node** %2, align 8
  %70 = getelementptr inbounds %struct.Node, %struct.Node* %69, i32 0, i32 2
  store %struct.Type* %68, %struct.Type** %70, align 16
  br label %412

71:                                               ; preds = %63, %63, %63, %63, %63, %63, %63, %63
  %72 = load %struct.Node*, %struct.Node** %2, align 8
  %73 = getelementptr inbounds %struct.Node, %struct.Node* %72, i32 0, i32 4
  %74 = load %struct.Node*, %struct.Node** %2, align 8
  %75 = getelementptr inbounds %struct.Node, %struct.Node* %74, i32 0, i32 5
  call void @usual_arith_conv(%struct.Node** noundef %73, %struct.Node** noundef %75)
  %76 = load %struct.Node*, %struct.Node** %2, align 8
  %77 = getelementptr inbounds %struct.Node, %struct.Node* %76, i32 0, i32 4
  %78 = load %struct.Node*, %struct.Node** %77, align 16
  %79 = getelementptr inbounds %struct.Node, %struct.Node* %78, i32 0, i32 2
  %80 = load %struct.Type*, %struct.Type** %79, align 16
  %81 = load %struct.Node*, %struct.Node** %2, align 8
  %82 = getelementptr inbounds %struct.Node, %struct.Node* %81, i32 0, i32 2
  store %struct.Type* %80, %struct.Type** %82, align 16
  br label %412

83:                                               ; preds = %63
  %84 = load %struct.Type*, %struct.Type** @ty_int, align 8
  %85 = load %struct.Node*, %struct.Node** %2, align 8
  %86 = getelementptr inbounds %struct.Node, %struct.Node* %85, i32 0, i32 4
  %87 = load %struct.Node*, %struct.Node** %86, align 16
  %88 = getelementptr inbounds %struct.Node, %struct.Node* %87, i32 0, i32 2
  %89 = load %struct.Type*, %struct.Type** %88, align 16
  %90 = call %struct.Type* @get_common_type(%struct.Type* noundef %84, %struct.Type* noundef %89)
  store %struct.Type* %90, %struct.Type** %5, align 8
  %91 = load %struct.Node*, %struct.Node** %2, align 8
  %92 = getelementptr inbounds %struct.Node, %struct.Node* %91, i32 0, i32 4
  %93 = load %struct.Node*, %struct.Node** %92, align 16
  %94 = load %struct.Type*, %struct.Type** %5, align 8
  %95 = call %struct.Node* @new_cast(%struct.Node* noundef %93, %struct.Type* noundef %94)
  %96 = load %struct.Node*, %struct.Node** %2, align 8
  %97 = getelementptr inbounds %struct.Node, %struct.Node* %96, i32 0, i32 4
  store %struct.Node* %95, %struct.Node** %97, align 16
  %98 = load %struct.Type*, %struct.Type** %5, align 8
  %99 = load %struct.Node*, %struct.Node** %2, align 8
  %100 = getelementptr inbounds %struct.Node, %struct.Node* %99, i32 0, i32 2
  store %struct.Type* %98, %struct.Type** %100, align 16
  br label %412

101:                                              ; preds = %63
  %102 = load %struct.Node*, %struct.Node** %2, align 8
  %103 = getelementptr inbounds %struct.Node, %struct.Node* %102, i32 0, i32 4
  %104 = load %struct.Node*, %struct.Node** %103, align 16
  %105 = getelementptr inbounds %struct.Node, %struct.Node* %104, i32 0, i32 2
  %106 = load %struct.Type*, %struct.Type** %105, align 16
  %107 = getelementptr inbounds %struct.Type, %struct.Type* %106, i32 0, i32 0
  %108 = load i32, i32* %107, align 8
  %109 = icmp eq i32 %108, 12
  br i1 %109, label %110, label %116

110:                                              ; preds = %101
  %111 = load %struct.Node*, %struct.Node** %2, align 8
  %112 = getelementptr inbounds %struct.Node, %struct.Node* %111, i32 0, i32 4
  %113 = load %struct.Node*, %struct.Node** %112, align 16
  %114 = getelementptr inbounds %struct.Node, %struct.Node* %113, i32 0, i32 3
  %115 = load %struct.Token*, %struct.Token** %114, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %115, i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.14, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

116:                                              ; preds = %101
  %117 = load %struct.Node*, %struct.Node** %2, align 8
  %118 = getelementptr inbounds %struct.Node, %struct.Node* %117, i32 0, i32 4
  %119 = load %struct.Node*, %struct.Node** %118, align 16
  %120 = getelementptr inbounds %struct.Node, %struct.Node* %119, i32 0, i32 2
  %121 = load %struct.Type*, %struct.Type** %120, align 16
  %122 = getelementptr inbounds %struct.Type, %struct.Type* %121, i32 0, i32 0
  %123 = load i32, i32* %122, align 8
  %124 = icmp ne i32 %123, 14
  br i1 %124, label %125, label %137

125:                                              ; preds = %116
  %126 = load %struct.Node*, %struct.Node** %2, align 8
  %127 = getelementptr inbounds %struct.Node, %struct.Node* %126, i32 0, i32 5
  %128 = load %struct.Node*, %struct.Node** %127, align 8
  %129 = load %struct.Node*, %struct.Node** %2, align 8
  %130 = getelementptr inbounds %struct.Node, %struct.Node* %129, i32 0, i32 4
  %131 = load %struct.Node*, %struct.Node** %130, align 16
  %132 = getelementptr inbounds %struct.Node, %struct.Node* %131, i32 0, i32 2
  %133 = load %struct.Type*, %struct.Type** %132, align 16
  %134 = call %struct.Node* @new_cast(%struct.Node* noundef %128, %struct.Type* noundef %133)
  %135 = load %struct.Node*, %struct.Node** %2, align 8
  %136 = getelementptr inbounds %struct.Node, %struct.Node* %135, i32 0, i32 5
  store %struct.Node* %134, %struct.Node** %136, align 8
  br label %137

137:                                              ; preds = %125, %116
  %138 = load %struct.Node*, %struct.Node** %2, align 8
  %139 = getelementptr inbounds %struct.Node, %struct.Node* %138, i32 0, i32 4
  %140 = load %struct.Node*, %struct.Node** %139, align 16
  %141 = getelementptr inbounds %struct.Node, %struct.Node* %140, i32 0, i32 2
  %142 = load %struct.Type*, %struct.Type** %141, align 16
  %143 = load %struct.Node*, %struct.Node** %2, align 8
  %144 = getelementptr inbounds %struct.Node, %struct.Node* %143, i32 0, i32 2
  store %struct.Type* %142, %struct.Type** %144, align 16
  br label %412

145:                                              ; preds = %63, %63, %63, %63
  %146 = load %struct.Node*, %struct.Node** %2, align 8
  %147 = getelementptr inbounds %struct.Node, %struct.Node* %146, i32 0, i32 4
  %148 = load %struct.Node*, %struct.Node** %2, align 8
  %149 = getelementptr inbounds %struct.Node, %struct.Node* %148, i32 0, i32 5
  call void @usual_arith_conv(%struct.Node** noundef %147, %struct.Node** noundef %149)
  %150 = load %struct.Type*, %struct.Type** @ty_int, align 8
  %151 = load %struct.Node*, %struct.Node** %2, align 8
  %152 = getelementptr inbounds %struct.Node, %struct.Node* %151, i32 0, i32 2
  store %struct.Type* %150, %struct.Type** %152, align 16
  br label %412

153:                                              ; preds = %63
  %154 = load %struct.Node*, %struct.Node** %2, align 8
  %155 = getelementptr inbounds %struct.Node, %struct.Node* %154, i32 0, i32 15
  %156 = load %struct.Type*, %struct.Type** %155, align 8
  %157 = getelementptr inbounds %struct.Type, %struct.Type* %156, i32 0, i32 17
  %158 = load %struct.Type*, %struct.Type** %157, align 8
  %159 = load %struct.Node*, %struct.Node** %2, align 8
  %160 = getelementptr inbounds %struct.Node, %struct.Node* %159, i32 0, i32 2
  store %struct.Type* %158, %struct.Type** %160, align 16
  br label %412

161:                                              ; preds = %63, %63, %63
  %162 = load %struct.Type*, %struct.Type** @ty_int, align 8
  %163 = load %struct.Node*, %struct.Node** %2, align 8
  %164 = getelementptr inbounds %struct.Node, %struct.Node* %163, i32 0, i32 2
  store %struct.Type* %162, %struct.Type** %164, align 16
  br label %412

165:                                              ; preds = %63, %63, %63
  %166 = load %struct.Node*, %struct.Node** %2, align 8
  %167 = getelementptr inbounds %struct.Node, %struct.Node* %166, i32 0, i32 4
  %168 = load %struct.Node*, %struct.Node** %167, align 16
  %169 = getelementptr inbounds %struct.Node, %struct.Node* %168, i32 0, i32 2
  %170 = load %struct.Type*, %struct.Type** %169, align 16
  %171 = load %struct.Node*, %struct.Node** %2, align 8
  %172 = getelementptr inbounds %struct.Node, %struct.Node* %171, i32 0, i32 2
  store %struct.Type* %170, %struct.Type** %172, align 16
  br label %412

173:                                              ; preds = %63, %63
  %174 = load %struct.Node*, %struct.Node** %2, align 8
  %175 = getelementptr inbounds %struct.Node, %struct.Node* %174, i32 0, i32 33
  %176 = load %struct.Obj*, %struct.Obj** %175, align 8
  %177 = getelementptr inbounds %struct.Obj, %struct.Obj* %176, i32 0, i32 3
  %178 = load %struct.Type*, %struct.Type** %177, align 8
  %179 = load %struct.Node*, %struct.Node** %2, align 8
  %180 = getelementptr inbounds %struct.Node, %struct.Node* %179, i32 0, i32 2
  store %struct.Type* %178, %struct.Type** %180, align 16
  br label %412

181:                                              ; preds = %63
  %182 = load %struct.Node*, %struct.Node** %2, align 8
  %183 = getelementptr inbounds %struct.Node, %struct.Node* %182, i32 0, i32 7
  %184 = load %struct.Node*, %struct.Node** %183, align 8
  %185 = getelementptr inbounds %struct.Node, %struct.Node* %184, i32 0, i32 2
  %186 = load %struct.Type*, %struct.Type** %185, align 16
  %187 = getelementptr inbounds %struct.Type, %struct.Type* %186, i32 0, i32 0
  %188 = load i32, i32* %187, align 8
  %189 = icmp eq i32 %188, 0
  br i1 %189, label %199, label %190

190:                                              ; preds = %181
  %191 = load %struct.Node*, %struct.Node** %2, align 8
  %192 = getelementptr inbounds %struct.Node, %struct.Node* %191, i32 0, i32 8
  %193 = load %struct.Node*, %struct.Node** %192, align 16
  %194 = getelementptr inbounds %struct.Node, %struct.Node* %193, i32 0, i32 2
  %195 = load %struct.Type*, %struct.Type** %194, align 16
  %196 = getelementptr inbounds %struct.Type, %struct.Type* %195, i32 0, i32 0
  %197 = load i32, i32* %196, align 8
  %198 = icmp eq i32 %197, 0
  br i1 %198, label %199, label %203

199:                                              ; preds = %190, %181
  %200 = load %struct.Type*, %struct.Type** @ty_void, align 8
  %201 = load %struct.Node*, %struct.Node** %2, align 8
  %202 = getelementptr inbounds %struct.Node, %struct.Node* %201, i32 0, i32 2
  store %struct.Type* %200, %struct.Type** %202, align 16
  br label %215

203:                                              ; preds = %190
  %204 = load %struct.Node*, %struct.Node** %2, align 8
  %205 = getelementptr inbounds %struct.Node, %struct.Node* %204, i32 0, i32 7
  %206 = load %struct.Node*, %struct.Node** %2, align 8
  %207 = getelementptr inbounds %struct.Node, %struct.Node* %206, i32 0, i32 8
  call void @usual_arith_conv(%struct.Node** noundef %205, %struct.Node** noundef %207)
  %208 = load %struct.Node*, %struct.Node** %2, align 8
  %209 = getelementptr inbounds %struct.Node, %struct.Node* %208, i32 0, i32 7
  %210 = load %struct.Node*, %struct.Node** %209, align 8
  %211 = getelementptr inbounds %struct.Node, %struct.Node* %210, i32 0, i32 2
  %212 = load %struct.Type*, %struct.Type** %211, align 16
  %213 = load %struct.Node*, %struct.Node** %2, align 8
  %214 = getelementptr inbounds %struct.Node, %struct.Node* %213, i32 0, i32 2
  store %struct.Type* %212, %struct.Type** %214, align 16
  br label %215

215:                                              ; preds = %203, %199
  br label %412

216:                                              ; preds = %63
  %217 = load %struct.Node*, %struct.Node** %2, align 8
  %218 = getelementptr inbounds %struct.Node, %struct.Node* %217, i32 0, i32 5
  %219 = load %struct.Node*, %struct.Node** %218, align 8
  %220 = getelementptr inbounds %struct.Node, %struct.Node* %219, i32 0, i32 2
  %221 = load %struct.Type*, %struct.Type** %220, align 16
  %222 = load %struct.Node*, %struct.Node** %2, align 8
  %223 = getelementptr inbounds %struct.Node, %struct.Node* %222, i32 0, i32 2
  store %struct.Type* %221, %struct.Type** %223, align 16
  br label %412

224:                                              ; preds = %63
  %225 = load %struct.Node*, %struct.Node** %2, align 8
  %226 = getelementptr inbounds %struct.Node, %struct.Node* %225, i32 0, i32 14
  %227 = load %struct.Member*, %struct.Member** %226, align 16
  %228 = getelementptr inbounds %struct.Member, %struct.Member* %227, i32 0, i32 1
  %229 = load %struct.Type*, %struct.Type** %228, align 8
  %230 = load %struct.Node*, %struct.Node** %2, align 8
  %231 = getelementptr inbounds %struct.Node, %struct.Node* %230, i32 0, i32 2
  store %struct.Type* %229, %struct.Type** %231, align 16
  br label %412

232:                                              ; preds = %63
  %233 = load %struct.Node*, %struct.Node** %2, align 8
  %234 = getelementptr inbounds %struct.Node, %struct.Node* %233, i32 0, i32 4
  %235 = load %struct.Node*, %struct.Node** %234, align 16
  %236 = getelementptr inbounds %struct.Node, %struct.Node* %235, i32 0, i32 2
  %237 = load %struct.Type*, %struct.Type** %236, align 16
  store %struct.Type* %237, %struct.Type** %6, align 8
  %238 = load %struct.Type*, %struct.Type** %6, align 8
  %239 = getelementptr inbounds %struct.Type, %struct.Type* %238, i32 0, i32 0
  %240 = load i32, i32* %239, align 8
  %241 = icmp eq i32 %240, 12
  br i1 %241, label %242, label %249

242:                                              ; preds = %232
  %243 = load %struct.Type*, %struct.Type** %6, align 8
  %244 = getelementptr inbounds %struct.Type, %struct.Type* %243, i32 0, i32 8
  %245 = load %struct.Type*, %struct.Type** %244, align 8
  %246 = call %struct.Type* @pointer_to(%struct.Type* noundef %245)
  %247 = load %struct.Node*, %struct.Node** %2, align 8
  %248 = getelementptr inbounds %struct.Node, %struct.Node* %247, i32 0, i32 2
  store %struct.Type* %246, %struct.Type** %248, align 16
  br label %254

249:                                              ; preds = %232
  %250 = load %struct.Type*, %struct.Type** %6, align 8
  %251 = call %struct.Type* @pointer_to(%struct.Type* noundef %250)
  %252 = load %struct.Node*, %struct.Node** %2, align 8
  %253 = getelementptr inbounds %struct.Node, %struct.Node* %252, i32 0, i32 2
  store %struct.Type* %251, %struct.Type** %253, align 16
  br label %254

254:                                              ; preds = %249, %242
  br label %412

255:                                              ; preds = %63
  %256 = load %struct.Node*, %struct.Node** %2, align 8
  %257 = getelementptr inbounds %struct.Node, %struct.Node* %256, i32 0, i32 4
  %258 = load %struct.Node*, %struct.Node** %257, align 16
  %259 = getelementptr inbounds %struct.Node, %struct.Node* %258, i32 0, i32 2
  %260 = load %struct.Type*, %struct.Type** %259, align 16
  %261 = getelementptr inbounds %struct.Type, %struct.Type* %260, i32 0, i32 8
  %262 = load %struct.Type*, %struct.Type** %261, align 8
  %263 = icmp ne %struct.Type* %262, null
  br i1 %263, label %268, label %264

264:                                              ; preds = %255
  %265 = load %struct.Node*, %struct.Node** %2, align 8
  %266 = getelementptr inbounds %struct.Node, %struct.Node* %265, i32 0, i32 3
  %267 = load %struct.Token*, %struct.Token** %266, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %267, i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.15, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

268:                                              ; preds = %255
  %269 = load %struct.Node*, %struct.Node** %2, align 8
  %270 = getelementptr inbounds %struct.Node, %struct.Node* %269, i32 0, i32 4
  %271 = load %struct.Node*, %struct.Node** %270, align 16
  %272 = getelementptr inbounds %struct.Node, %struct.Node* %271, i32 0, i32 2
  %273 = load %struct.Type*, %struct.Type** %272, align 16
  %274 = getelementptr inbounds %struct.Type, %struct.Type* %273, i32 0, i32 8
  %275 = load %struct.Type*, %struct.Type** %274, align 8
  %276 = getelementptr inbounds %struct.Type, %struct.Type* %275, i32 0, i32 0
  %277 = load i32, i32* %276, align 8
  %278 = icmp eq i32 %277, 0
  br i1 %278, label %279, label %283

279:                                              ; preds = %268
  %280 = load %struct.Node*, %struct.Node** %2, align 8
  %281 = getelementptr inbounds %struct.Node, %struct.Node* %280, i32 0, i32 3
  %282 = load %struct.Token*, %struct.Token** %281, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %282, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @.str.16, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

283:                                              ; preds = %268
  %284 = load %struct.Node*, %struct.Node** %2, align 8
  %285 = getelementptr inbounds %struct.Node, %struct.Node* %284, i32 0, i32 4
  %286 = load %struct.Node*, %struct.Node** %285, align 16
  %287 = getelementptr inbounds %struct.Node, %struct.Node* %286, i32 0, i32 2
  %288 = load %struct.Type*, %struct.Type** %287, align 16
  %289 = getelementptr inbounds %struct.Type, %struct.Type* %288, i32 0, i32 8
  %290 = load %struct.Type*, %struct.Type** %289, align 8
  %291 = load %struct.Node*, %struct.Node** %2, align 8
  %292 = getelementptr inbounds %struct.Node, %struct.Node* %291, i32 0, i32 2
  store %struct.Type* %290, %struct.Type** %292, align 16
  br label %412

293:                                              ; preds = %63
  %294 = load %struct.Node*, %struct.Node** %2, align 8
  %295 = getelementptr inbounds %struct.Node, %struct.Node* %294, i32 0, i32 13
  %296 = load %struct.Node*, %struct.Node** %295, align 8
  %297 = icmp ne %struct.Node* %296, null
  br i1 %297, label %298, label %335

298:                                              ; preds = %293
  %299 = load %struct.Node*, %struct.Node** %2, align 8
  %300 = getelementptr inbounds %struct.Node, %struct.Node* %299, i32 0, i32 13
  %301 = load %struct.Node*, %struct.Node** %300, align 8
  store %struct.Node* %301, %struct.Node** %7, align 8
  br label %302

302:                                              ; preds = %307, %298
  %303 = load %struct.Node*, %struct.Node** %7, align 8
  %304 = getelementptr inbounds %struct.Node, %struct.Node* %303, i32 0, i32 1
  %305 = load %struct.Node*, %struct.Node** %304, align 8
  %306 = icmp ne %struct.Node* %305, null
  br i1 %306, label %307, label %311

307:                                              ; preds = %302
  %308 = load %struct.Node*, %struct.Node** %7, align 8
  %309 = getelementptr inbounds %struct.Node, %struct.Node* %308, i32 0, i32 1
  %310 = load %struct.Node*, %struct.Node** %309, align 8
  store %struct.Node* %310, %struct.Node** %7, align 8
  br label %302, !llvm.loop !10

311:                                              ; preds = %302
  br label %312

312:                                              ; preds = %317, %311
  %313 = load %struct.Node*, %struct.Node** %7, align 8
  %314 = getelementptr inbounds %struct.Node, %struct.Node* %313, i32 0, i32 0
  %315 = load i32, i32* %314, align 16
  %316 = icmp eq i32 %315, 35
  br i1 %316, label %317, label %321

317:                                              ; preds = %312
  %318 = load %struct.Node*, %struct.Node** %7, align 8
  %319 = getelementptr inbounds %struct.Node, %struct.Node* %318, i32 0, i32 4
  %320 = load %struct.Node*, %struct.Node** %319, align 16
  store %struct.Node* %320, %struct.Node** %7, align 8
  br label %312, !llvm.loop !11

321:                                              ; preds = %312
  %322 = load %struct.Node*, %struct.Node** %7, align 8
  %323 = getelementptr inbounds %struct.Node, %struct.Node* %322, i32 0, i32 0
  %324 = load i32, i32* %323, align 16
  %325 = icmp eq i32 %324, 38
  br i1 %325, label %326, label %334

326:                                              ; preds = %321
  %327 = load %struct.Node*, %struct.Node** %7, align 8
  %328 = getelementptr inbounds %struct.Node, %struct.Node* %327, i32 0, i32 4
  %329 = load %struct.Node*, %struct.Node** %328, align 16
  %330 = getelementptr inbounds %struct.Node, %struct.Node* %329, i32 0, i32 2
  %331 = load %struct.Type*, %struct.Type** %330, align 16
  %332 = load %struct.Node*, %struct.Node** %2, align 8
  %333 = getelementptr inbounds %struct.Node, %struct.Node* %332, i32 0, i32 2
  store %struct.Type* %331, %struct.Type** %333, align 16
  br label %412

334:                                              ; preds = %321
  br label %335

335:                                              ; preds = %334, %293
  %336 = load %struct.Node*, %struct.Node** %2, align 8
  %337 = getelementptr inbounds %struct.Node, %struct.Node* %336, i32 0, i32 3
  %338 = load %struct.Token*, %struct.Token** %337, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %338, i8* noundef getelementptr inbounds ([56 x i8], [56 x i8]* @.str.17, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

339:                                              ; preds = %63
  %340 = load %struct.Type*, %struct.Type** @ty_void, align 8
  %341 = call %struct.Type* @pointer_to(%struct.Type* noundef %340)
  %342 = load %struct.Node*, %struct.Node** %2, align 8
  %343 = getelementptr inbounds %struct.Node, %struct.Node* %342, i32 0, i32 2
  store %struct.Type* %341, %struct.Type** %343, align 16
  br label %412

344:                                              ; preds = %63
  %345 = load %struct.Node*, %struct.Node** %2, align 8
  %346 = getelementptr inbounds %struct.Node, %struct.Node* %345, i32 0, i32 27
  %347 = load %struct.Node*, %struct.Node** %346, align 8
  call void @add_type(%struct.Node* noundef %347)
  %348 = load %struct.Node*, %struct.Node** %2, align 8
  %349 = getelementptr inbounds %struct.Node, %struct.Node* %348, i32 0, i32 28
  %350 = load %struct.Node*, %struct.Node** %349, align 16
  call void @add_type(%struct.Node* noundef %350)
  %351 = load %struct.Node*, %struct.Node** %2, align 8
  %352 = getelementptr inbounds %struct.Node, %struct.Node* %351, i32 0, i32 29
  %353 = load %struct.Node*, %struct.Node** %352, align 8
  call void @add_type(%struct.Node* noundef %353)
  %354 = load %struct.Type*, %struct.Type** @ty_bool, align 8
  %355 = load %struct.Node*, %struct.Node** %2, align 8
  %356 = getelementptr inbounds %struct.Node, %struct.Node* %355, i32 0, i32 2
  store %struct.Type* %354, %struct.Type** %356, align 16
  %357 = load %struct.Node*, %struct.Node** %2, align 8
  %358 = getelementptr inbounds %struct.Node, %struct.Node* %357, i32 0, i32 27
  %359 = load %struct.Node*, %struct.Node** %358, align 8
  %360 = getelementptr inbounds %struct.Node, %struct.Node* %359, i32 0, i32 2
  %361 = load %struct.Type*, %struct.Type** %360, align 16
  %362 = getelementptr inbounds %struct.Type, %struct.Type* %361, i32 0, i32 0
  %363 = load i32, i32* %362, align 8
  %364 = icmp ne i32 %363, 10
  br i1 %364, label %365, label %371

365:                                              ; preds = %344
  %366 = load %struct.Node*, %struct.Node** %2, align 8
  %367 = getelementptr inbounds %struct.Node, %struct.Node* %366, i32 0, i32 27
  %368 = load %struct.Node*, %struct.Node** %367, align 8
  %369 = getelementptr inbounds %struct.Node, %struct.Node* %368, i32 0, i32 3
  %370 = load %struct.Token*, %struct.Token** %369, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %370, i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.18, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

371:                                              ; preds = %344
  %372 = load %struct.Node*, %struct.Node** %2, align 8
  %373 = getelementptr inbounds %struct.Node, %struct.Node* %372, i32 0, i32 28
  %374 = load %struct.Node*, %struct.Node** %373, align 16
  %375 = getelementptr inbounds %struct.Node, %struct.Node* %374, i32 0, i32 2
  %376 = load %struct.Type*, %struct.Type** %375, align 16
  %377 = getelementptr inbounds %struct.Type, %struct.Type* %376, i32 0, i32 0
  %378 = load i32, i32* %377, align 8
  %379 = icmp ne i32 %378, 10
  br i1 %379, label %380, label %386

380:                                              ; preds = %371
  %381 = load %struct.Node*, %struct.Node** %2, align 8
  %382 = getelementptr inbounds %struct.Node, %struct.Node* %381, i32 0, i32 28
  %383 = load %struct.Node*, %struct.Node** %382, align 16
  %384 = getelementptr inbounds %struct.Node, %struct.Node* %383, i32 0, i32 3
  %385 = load %struct.Token*, %struct.Token** %384, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %385, i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.18, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

386:                                              ; preds = %371
  br label %412

387:                                              ; preds = %63
  %388 = load %struct.Node*, %struct.Node** %2, align 8
  %389 = getelementptr inbounds %struct.Node, %struct.Node* %388, i32 0, i32 4
  %390 = load %struct.Node*, %struct.Node** %389, align 16
  %391 = getelementptr inbounds %struct.Node, %struct.Node* %390, i32 0, i32 2
  %392 = load %struct.Type*, %struct.Type** %391, align 16
  %393 = getelementptr inbounds %struct.Type, %struct.Type* %392, i32 0, i32 0
  %394 = load i32, i32* %393, align 8
  %395 = icmp ne i32 %394, 10
  br i1 %395, label %396, label %402

396:                                              ; preds = %387
  %397 = load %struct.Node*, %struct.Node** %2, align 8
  %398 = getelementptr inbounds %struct.Node, %struct.Node* %397, i32 0, i32 27
  %399 = load %struct.Node*, %struct.Node** %398, align 8
  %400 = getelementptr inbounds %struct.Node, %struct.Node* %399, i32 0, i32 3
  %401 = load %struct.Token*, %struct.Token** %400, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %401, i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.18, i64 0, i64 0), i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.13, i64 0, i64 0)) #6
  unreachable

402:                                              ; preds = %387
  %403 = load %struct.Node*, %struct.Node** %2, align 8
  %404 = getelementptr inbounds %struct.Node, %struct.Node* %403, i32 0, i32 4
  %405 = load %struct.Node*, %struct.Node** %404, align 16
  %406 = getelementptr inbounds %struct.Node, %struct.Node* %405, i32 0, i32 2
  %407 = load %struct.Type*, %struct.Type** %406, align 16
  %408 = getelementptr inbounds %struct.Type, %struct.Type* %407, i32 0, i32 8
  %409 = load %struct.Type*, %struct.Type** %408, align 8
  %410 = load %struct.Node*, %struct.Node** %2, align 8
  %411 = getelementptr inbounds %struct.Node, %struct.Node* %410, i32 0, i32 2
  store %struct.Type* %409, %struct.Type** %411, align 16
  br label %412

412:                                              ; preds = %15, %67, %71, %83, %137, %145, %153, %161, %165, %173, %215, %216, %224, %254, %283, %326, %339, %386, %402, %63
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @usual_arith_conv(%struct.Node** noundef %0, %struct.Node** noundef %1) #0 {
  %3 = alloca %struct.Node**, align 8
  %4 = alloca %struct.Node**, align 8
  %5 = alloca %struct.Type*, align 8
  store %struct.Node** %0, %struct.Node*** %3, align 8
  store %struct.Node** %1, %struct.Node*** %4, align 8
  %6 = load %struct.Node**, %struct.Node*** %3, align 8
  %7 = load %struct.Node*, %struct.Node** %6, align 8
  %8 = getelementptr inbounds %struct.Node, %struct.Node* %7, i32 0, i32 2
  %9 = load %struct.Type*, %struct.Type** %8, align 16
  %10 = load %struct.Node**, %struct.Node*** %4, align 8
  %11 = load %struct.Node*, %struct.Node** %10, align 8
  %12 = getelementptr inbounds %struct.Node, %struct.Node* %11, i32 0, i32 2
  %13 = load %struct.Type*, %struct.Type** %12, align 16
  %14 = call %struct.Type* @get_common_type(%struct.Type* noundef %9, %struct.Type* noundef %13)
  store %struct.Type* %14, %struct.Type** %5, align 8
  %15 = load %struct.Node**, %struct.Node*** %3, align 8
  %16 = load %struct.Node*, %struct.Node** %15, align 8
  %17 = load %struct.Type*, %struct.Type** %5, align 8
  %18 = call %struct.Node* @new_cast(%struct.Node* noundef %16, %struct.Type* noundef %17)
  %19 = load %struct.Node**, %struct.Node*** %3, align 8
  store %struct.Node* %18, %struct.Node** %19, align 8
  %20 = load %struct.Node**, %struct.Node*** %4, align 8
  %21 = load %struct.Node*, %struct.Node** %20, align 8
  %22 = load %struct.Type*, %struct.Type** %5, align 8
  %23 = call %struct.Node* @new_cast(%struct.Node* noundef %21, %struct.Type* noundef %22)
  %24 = load %struct.Node**, %struct.Node*** %4, align 8
  store %struct.Node* %23, %struct.Node** %24, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @get_common_type(%struct.Type* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %4, align 8
  store %struct.Type* %1, %struct.Type** %5, align 8
  %6 = load %struct.Type*, %struct.Type** %4, align 8
  %7 = getelementptr inbounds %struct.Type, %struct.Type* %6, i32 0, i32 8
  %8 = load %struct.Type*, %struct.Type** %7, align 8
  %9 = icmp ne %struct.Type* %8, null
  br i1 %9, label %10, label %15

10:                                               ; preds = %2
  %11 = load %struct.Type*, %struct.Type** %4, align 8
  %12 = getelementptr inbounds %struct.Type, %struct.Type* %11, i32 0, i32 8
  %13 = load %struct.Type*, %struct.Type** %12, align 8
  %14 = call %struct.Type* @pointer_to(%struct.Type* noundef %13)
  store %struct.Type* %14, %struct.Type** %3, align 8
  br label %112

15:                                               ; preds = %2
  %16 = load %struct.Type*, %struct.Type** %4, align 8
  %17 = getelementptr inbounds %struct.Type, %struct.Type* %16, i32 0, i32 0
  %18 = load i32, i32* %17, align 8
  %19 = icmp eq i32 %18, 11
  br i1 %19, label %20, label %23

20:                                               ; preds = %15
  %21 = load %struct.Type*, %struct.Type** %4, align 8
  %22 = call %struct.Type* @pointer_to(%struct.Type* noundef %21)
  store %struct.Type* %22, %struct.Type** %3, align 8
  br label %112

23:                                               ; preds = %15
  %24 = load %struct.Type*, %struct.Type** %5, align 8
  %25 = getelementptr inbounds %struct.Type, %struct.Type* %24, i32 0, i32 0
  %26 = load i32, i32* %25, align 8
  %27 = icmp eq i32 %26, 11
  br i1 %27, label %28, label %31

28:                                               ; preds = %23
  %29 = load %struct.Type*, %struct.Type** %5, align 8
  %30 = call %struct.Type* @pointer_to(%struct.Type* noundef %29)
  store %struct.Type* %30, %struct.Type** %3, align 8
  br label %112

31:                                               ; preds = %23
  %32 = load %struct.Type*, %struct.Type** %4, align 8
  %33 = getelementptr inbounds %struct.Type, %struct.Type* %32, i32 0, i32 0
  %34 = load i32, i32* %33, align 8
  %35 = icmp eq i32 %34, 8
  br i1 %35, label %41, label %36

36:                                               ; preds = %31
  %37 = load %struct.Type*, %struct.Type** %5, align 8
  %38 = getelementptr inbounds %struct.Type, %struct.Type* %37, i32 0, i32 0
  %39 = load i32, i32* %38, align 8
  %40 = icmp eq i32 %39, 8
  br i1 %40, label %41, label %43

41:                                               ; preds = %36, %31
  %42 = load %struct.Type*, %struct.Type** @ty_ldouble, align 8
  store %struct.Type* %42, %struct.Type** %3, align 8
  br label %112

43:                                               ; preds = %36
  %44 = load %struct.Type*, %struct.Type** %4, align 8
  %45 = getelementptr inbounds %struct.Type, %struct.Type* %44, i32 0, i32 0
  %46 = load i32, i32* %45, align 8
  %47 = icmp eq i32 %46, 7
  br i1 %47, label %53, label %48

48:                                               ; preds = %43
  %49 = load %struct.Type*, %struct.Type** %5, align 8
  %50 = getelementptr inbounds %struct.Type, %struct.Type* %49, i32 0, i32 0
  %51 = load i32, i32* %50, align 8
  %52 = icmp eq i32 %51, 7
  br i1 %52, label %53, label %55

53:                                               ; preds = %48, %43
  %54 = load %struct.Type*, %struct.Type** @ty_double, align 8
  store %struct.Type* %54, %struct.Type** %3, align 8
  br label %112

55:                                               ; preds = %48
  %56 = load %struct.Type*, %struct.Type** %4, align 8
  %57 = getelementptr inbounds %struct.Type, %struct.Type* %56, i32 0, i32 0
  %58 = load i32, i32* %57, align 8
  %59 = icmp eq i32 %58, 6
  br i1 %59, label %65, label %60

60:                                               ; preds = %55
  %61 = load %struct.Type*, %struct.Type** %5, align 8
  %62 = getelementptr inbounds %struct.Type, %struct.Type* %61, i32 0, i32 0
  %63 = load i32, i32* %62, align 8
  %64 = icmp eq i32 %63, 6
  br i1 %64, label %65, label %67

65:                                               ; preds = %60, %55
  %66 = load %struct.Type*, %struct.Type** @ty_float, align 8
  store %struct.Type* %66, %struct.Type** %3, align 8
  br label %112

67:                                               ; preds = %60
  %68 = load %struct.Type*, %struct.Type** %4, align 8
  %69 = getelementptr inbounds %struct.Type, %struct.Type* %68, i32 0, i32 1
  %70 = load i32, i32* %69, align 4
  %71 = icmp slt i32 %70, 4
  br i1 %71, label %72, label %74

72:                                               ; preds = %67
  %73 = load %struct.Type*, %struct.Type** @ty_int, align 8
  store %struct.Type* %73, %struct.Type** %4, align 8
  br label %74

74:                                               ; preds = %72, %67
  %75 = load %struct.Type*, %struct.Type** %5, align 8
  %76 = getelementptr inbounds %struct.Type, %struct.Type* %75, i32 0, i32 1
  %77 = load i32, i32* %76, align 4
  %78 = icmp slt i32 %77, 4
  br i1 %78, label %79, label %81

79:                                               ; preds = %74
  %80 = load %struct.Type*, %struct.Type** @ty_int, align 8
  store %struct.Type* %80, %struct.Type** %5, align 8
  br label %81

81:                                               ; preds = %79, %74
  %82 = load %struct.Type*, %struct.Type** %4, align 8
  %83 = getelementptr inbounds %struct.Type, %struct.Type* %82, i32 0, i32 1
  %84 = load i32, i32* %83, align 4
  %85 = load %struct.Type*, %struct.Type** %5, align 8
  %86 = getelementptr inbounds %struct.Type, %struct.Type* %85, i32 0, i32 1
  %87 = load i32, i32* %86, align 4
  %88 = icmp ne i32 %84, %87
  br i1 %88, label %89, label %103

89:                                               ; preds = %81
  %90 = load %struct.Type*, %struct.Type** %4, align 8
  %91 = getelementptr inbounds %struct.Type, %struct.Type* %90, i32 0, i32 1
  %92 = load i32, i32* %91, align 4
  %93 = load %struct.Type*, %struct.Type** %5, align 8
  %94 = getelementptr inbounds %struct.Type, %struct.Type* %93, i32 0, i32 1
  %95 = load i32, i32* %94, align 4
  %96 = icmp slt i32 %92, %95
  br i1 %96, label %97, label %99

97:                                               ; preds = %89
  %98 = load %struct.Type*, %struct.Type** %5, align 8
  br label %101

99:                                               ; preds = %89
  %100 = load %struct.Type*, %struct.Type** %4, align 8
  br label %101

101:                                              ; preds = %99, %97
  %102 = phi %struct.Type* [ %98, %97 ], [ %100, %99 ]
  store %struct.Type* %102, %struct.Type** %3, align 8
  br label %112

103:                                              ; preds = %81
  %104 = load %struct.Type*, %struct.Type** %5, align 8
  %105 = getelementptr inbounds %struct.Type, %struct.Type* %104, i32 0, i32 3
  %106 = load i8, i8* %105, align 4
  %107 = trunc i8 %106 to i1
  br i1 %107, label %108, label %110

108:                                              ; preds = %103
  %109 = load %struct.Type*, %struct.Type** %5, align 8
  store %struct.Type* %109, %struct.Type** %3, align 8
  br label %112

110:                                              ; preds = %103
  %111 = load %struct.Type*, %struct.Type** %4, align 8
  store %struct.Type* %111, %struct.Type** %3, align 8
  br label %112

112:                                              ; preds = %110, %108, %101, %65, %53, %41, %28, %20, %10
  %113 = load %struct.Type*, %struct.Type** %3, align 8
  ret %struct.Type* %113
}

declare %struct.Node* @new_cast(%struct.Node* noundef, %struct.Type* noundef) #4

; Function Attrs: noreturn
declare void @error_tok(%struct.Token* noundef, i8* noundef, ...) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { argmemonly nofree nounwind willreturn }
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
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
