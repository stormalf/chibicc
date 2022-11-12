; ModuleID = 'unicode.c'
source_filename = "unicode.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [26 x i8] c"%s invalid UTF-8 sequence\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"unicode.c\00", align 1
@is_ident1.range = internal global [107 x i32] [i32 95, i32 95, i32 97, i32 122, i32 65, i32 90, i32 36, i32 36, i32 168, i32 168, i32 170, i32 170, i32 173, i32 173, i32 175, i32 175, i32 178, i32 181, i32 183, i32 186, i32 188, i32 190, i32 192, i32 214, i32 216, i32 246, i32 248, i32 255, i32 256, i32 767, i32 880, i32 5759, i32 5761, i32 6157, i32 6159, i32 7615, i32 7680, i32 8191, i32 8203, i32 8205, i32 8234, i32 8238, i32 8255, i32 8256, i32 8276, i32 8276, i32 8288, i32 8303, i32 8304, i32 8399, i32 8448, i32 8591, i32 9312, i32 9471, i32 10102, i32 10131, i32 11264, i32 11775, i32 11904, i32 12287, i32 12292, i32 12295, i32 12321, i32 12335, i32 12337, i32 12351, i32 12352, i32 55295, i32 63744, i32 64829, i32 64832, i32 64975, i32 65008, i32 65055, i32 65072, i32 65092, i32 65095, i32 65533, i32 65536, i32 131069, i32 131072, i32 196605, i32 196608, i32 262141, i32 262144, i32 327677, i32 327680, i32 393213, i32 393216, i32 458749, i32 458752, i32 524285, i32 524288, i32 589821, i32 589824, i32 655357, i32 655360, i32 720893, i32 720896, i32 786429, i32 786432, i32 851965, i32 851968, i32 917501, i32 917504, i32 983037, i32 -1], align 16
@is_ident2.range = internal global [19 x i32] [i32 95, i32 95, i32 97, i32 122, i32 65, i32 90, i32 48, i32 57, i32 36, i32 36, i32 768, i32 879, i32 7616, i32 7679, i32 8400, i32 8447, i32 65056, i32 65071, i32 -1], align 16
@is_ident3.range = internal global [109 x i32] [i32 95, i32 95, i32 97, i32 122, i32 65, i32 90, i32 48, i32 57, i32 36, i32 36, i32 168, i32 168, i32 170, i32 170, i32 173, i32 173, i32 175, i32 175, i32 178, i32 181, i32 183, i32 186, i32 188, i32 190, i32 192, i32 214, i32 216, i32 246, i32 248, i32 255, i32 256, i32 767, i32 880, i32 5759, i32 5761, i32 6157, i32 6159, i32 7615, i32 7680, i32 8191, i32 8203, i32 8205, i32 8234, i32 8238, i32 8255, i32 8256, i32 8276, i32 8276, i32 8288, i32 8303, i32 8304, i32 8399, i32 8448, i32 8591, i32 9312, i32 9471, i32 10102, i32 10131, i32 11264, i32 11775, i32 11904, i32 12287, i32 12292, i32 12295, i32 12321, i32 12335, i32 12337, i32 12351, i32 12352, i32 55295, i32 63744, i32 64829, i32 64832, i32 64975, i32 65008, i32 65055, i32 65072, i32 65092, i32 65095, i32 65533, i32 65536, i32 131069, i32 131072, i32 196605, i32 196608, i32 262141, i32 262144, i32 327677, i32 327680, i32 393213, i32 393216, i32 458749, i32 458752, i32 524285, i32 524288, i32 589821, i32 589824, i32 655357, i32 655360, i32 720893, i32 720896, i32 786429, i32 786432, i32 851965, i32 851968, i32 917501, i32 917504, i32 983037, i32 -1], align 16
@char_width.range1 = internal global [289 x i32] [i32 0, i32 31, i32 127, i32 160, i32 768, i32 879, i32 1155, i32 1158, i32 1160, i32 1161, i32 1425, i32 1469, i32 1471, i32 1471, i32 1473, i32 1474, i32 1476, i32 1477, i32 1479, i32 1479, i32 1536, i32 1539, i32 1552, i32 1557, i32 1611, i32 1630, i32 1648, i32 1648, i32 1750, i32 1764, i32 1767, i32 1768, i32 1770, i32 1773, i32 1807, i32 1807, i32 1809, i32 1809, i32 1840, i32 1866, i32 1958, i32 1968, i32 2027, i32 2035, i32 2305, i32 2306, i32 2364, i32 2364, i32 2369, i32 2376, i32 2381, i32 2381, i32 2385, i32 2388, i32 2402, i32 2403, i32 2433, i32 2433, i32 2492, i32 2492, i32 2497, i32 2500, i32 2509, i32 2509, i32 2530, i32 2531, i32 2561, i32 2562, i32 2620, i32 2620, i32 2625, i32 2626, i32 2631, i32 2632, i32 2635, i32 2637, i32 2672, i32 2673, i32 2689, i32 2690, i32 2748, i32 2748, i32 2753, i32 2757, i32 2759, i32 2760, i32 2765, i32 2765, i32 2786, i32 2787, i32 2817, i32 2817, i32 2876, i32 2876, i32 2879, i32 2879, i32 2881, i32 2883, i32 2893, i32 2893, i32 2902, i32 2902, i32 2946, i32 2946, i32 3008, i32 3008, i32 3021, i32 3021, i32 3134, i32 3136, i32 3142, i32 3144, i32 3146, i32 3149, i32 3157, i32 3158, i32 3260, i32 3260, i32 3263, i32 3263, i32 3270, i32 3270, i32 3276, i32 3277, i32 3298, i32 3299, i32 3393, i32 3395, i32 3405, i32 3405, i32 3530, i32 3530, i32 3538, i32 3540, i32 3542, i32 3542, i32 3633, i32 3633, i32 3636, i32 3642, i32 3655, i32 3662, i32 3761, i32 3761, i32 3764, i32 3769, i32 3771, i32 3772, i32 3784, i32 3789, i32 3864, i32 3865, i32 3893, i32 3893, i32 3895, i32 3895, i32 3897, i32 3897, i32 3953, i32 3966, i32 3968, i32 3972, i32 3974, i32 3975, i32 3984, i32 3991, i32 3993, i32 4028, i32 4038, i32 4038, i32 4141, i32 4144, i32 4146, i32 4146, i32 4150, i32 4151, i32 4153, i32 4153, i32 4184, i32 4185, i32 4448, i32 4607, i32 4959, i32 4959, i32 5906, i32 5908, i32 5938, i32 5940, i32 5970, i32 5971, i32 6002, i32 6003, i32 6068, i32 6069, i32 6071, i32 6077, i32 6086, i32 6086, i32 6089, i32 6099, i32 6109, i32 6109, i32 6155, i32 6157, i32 6313, i32 6313, i32 6432, i32 6434, i32 6439, i32 6440, i32 6450, i32 6450, i32 6457, i32 6459, i32 6679, i32 6680, i32 6912, i32 6915, i32 6964, i32 6964, i32 6966, i32 6970, i32 6972, i32 6972, i32 6978, i32 6978, i32 7019, i32 7027, i32 7616, i32 7626, i32 7678, i32 7679, i32 8203, i32 8207, i32 8234, i32 8238, i32 8288, i32 8291, i32 8298, i32 8303, i32 8400, i32 8431, i32 12330, i32 12335, i32 12441, i32 12442, i32 43014, i32 43014, i32 43019, i32 43019, i32 43045, i32 43046, i32 64286, i32 64286, i32 65024, i32 65039, i32 65056, i32 65059, i32 65279, i32 65279, i32 65529, i32 65531, i32 68097, i32 68099, i32 68101, i32 68102, i32 68108, i32 68111, i32 68152, i32 68154, i32 68159, i32 68159, i32 119143, i32 119145, i32 119155, i32 119170, i32 119173, i32 119179, i32 119210, i32 119213, i32 119362, i32 119364, i32 917505, i32 917505, i32 917536, i32 917631, i32 917760, i32 917999, i32 -1], align 16
@char_width.range2 = internal global [29 x i32] [i32 4352, i32 4447, i32 9001, i32 9001, i32 9002, i32 9002, i32 11904, i32 12350, i32 12352, i32 42191, i32 44032, i32 55203, i32 63744, i32 64255, i32 65040, i32 65049, i32 65072, i32 65135, i32 65280, i32 65376, i32 65504, i32 65510, i32 126976, i32 128580, i32 131072, i32 196605, i32 196608, i32 262141, i32 -1], align 16

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @encode_utf8(i8* noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  store i32 %1, i32* %5, align 4
  %6 = load i32, i32* %5, align 4
  %7 = icmp ule i32 %6, 127
  br i1 %7, label %8, label %13

8:                                                ; preds = %2
  %9 = load i32, i32* %5, align 4
  %10 = trunc i32 %9 to i8
  %11 = load i8*, i8** %4, align 8
  %12 = getelementptr inbounds i8, i8* %11, i64 0
  store i8 %10, i8* %12, align 1
  store i32 1, i32* %3, align 4
  br label %79

13:                                               ; preds = %2
  %14 = load i32, i32* %5, align 4
  %15 = icmp ule i32 %14, 2047
  br i1 %15, label %16, label %29

16:                                               ; preds = %13
  %17 = load i32, i32* %5, align 4
  %18 = lshr i32 %17, 6
  %19 = or i32 192, %18
  %20 = trunc i32 %19 to i8
  %21 = load i8*, i8** %4, align 8
  %22 = getelementptr inbounds i8, i8* %21, i64 0
  store i8 %20, i8* %22, align 1
  %23 = load i32, i32* %5, align 4
  %24 = and i32 %23, 63
  %25 = or i32 128, %24
  %26 = trunc i32 %25 to i8
  %27 = load i8*, i8** %4, align 8
  %28 = getelementptr inbounds i8, i8* %27, i64 1
  store i8 %26, i8* %28, align 1
  store i32 2, i32* %3, align 4
  br label %79

29:                                               ; preds = %13
  %30 = load i32, i32* %5, align 4
  %31 = icmp ule i32 %30, 65535
  br i1 %31, label %32, label %52

32:                                               ; preds = %29
  %33 = load i32, i32* %5, align 4
  %34 = lshr i32 %33, 12
  %35 = or i32 224, %34
  %36 = trunc i32 %35 to i8
  %37 = load i8*, i8** %4, align 8
  %38 = getelementptr inbounds i8, i8* %37, i64 0
  store i8 %36, i8* %38, align 1
  %39 = load i32, i32* %5, align 4
  %40 = lshr i32 %39, 6
  %41 = and i32 %40, 63
  %42 = or i32 128, %41
  %43 = trunc i32 %42 to i8
  %44 = load i8*, i8** %4, align 8
  %45 = getelementptr inbounds i8, i8* %44, i64 1
  store i8 %43, i8* %45, align 1
  %46 = load i32, i32* %5, align 4
  %47 = and i32 %46, 63
  %48 = or i32 128, %47
  %49 = trunc i32 %48 to i8
  %50 = load i8*, i8** %4, align 8
  %51 = getelementptr inbounds i8, i8* %50, i64 2
  store i8 %49, i8* %51, align 1
  store i32 3, i32* %3, align 4
  br label %79

52:                                               ; preds = %29
  %53 = load i32, i32* %5, align 4
  %54 = lshr i32 %53, 18
  %55 = or i32 240, %54
  %56 = trunc i32 %55 to i8
  %57 = load i8*, i8** %4, align 8
  %58 = getelementptr inbounds i8, i8* %57, i64 0
  store i8 %56, i8* %58, align 1
  %59 = load i32, i32* %5, align 4
  %60 = lshr i32 %59, 12
  %61 = and i32 %60, 63
  %62 = or i32 128, %61
  %63 = trunc i32 %62 to i8
  %64 = load i8*, i8** %4, align 8
  %65 = getelementptr inbounds i8, i8* %64, i64 1
  store i8 %63, i8* %65, align 1
  %66 = load i32, i32* %5, align 4
  %67 = lshr i32 %66, 6
  %68 = and i32 %67, 63
  %69 = or i32 128, %68
  %70 = trunc i32 %69 to i8
  %71 = load i8*, i8** %4, align 8
  %72 = getelementptr inbounds i8, i8* %71, i64 2
  store i8 %70, i8* %72, align 1
  %73 = load i32, i32* %5, align 4
  %74 = and i32 %73, 63
  %75 = or i32 128, %74
  %76 = trunc i32 %75 to i8
  %77 = load i8*, i8** %4, align 8
  %78 = getelementptr inbounds i8, i8* %77, i64 3
  store i8 %76, i8* %78, align 1
  store i32 4, i32* %3, align 4
  br label %79

79:                                               ; preds = %52, %32, %16, %8
  %80 = load i32, i32* %3, align 4
  ret i32 %80
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @decode_utf8(i8** noundef %0, i8* noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i8**, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i8** %0, i8*** %4, align 8
  store i8* %1, i8** %5, align 8
  %10 = load i8*, i8** %5, align 8
  %11 = load i8, i8* %10, align 1
  %12 = zext i8 %11 to i32
  %13 = icmp slt i32 %12, 128
  br i1 %13, label %14, label %21

14:                                               ; preds = %2
  %15 = load i8*, i8** %5, align 8
  %16 = getelementptr inbounds i8, i8* %15, i64 1
  %17 = load i8**, i8*** %4, align 8
  store i8* %16, i8** %17, align 8
  %18 = load i8*, i8** %5, align 8
  %19 = load i8, i8* %18, align 1
  %20 = sext i8 %19 to i32
  store i32 %20, i32* %3, align 4
  br label %93

21:                                               ; preds = %2
  %22 = load i8*, i8** %5, align 8
  store i8* %22, i8** %6, align 8
  %23 = load i8*, i8** %5, align 8
  %24 = load i8, i8* %23, align 1
  %25 = zext i8 %24 to i32
  %26 = icmp sge i32 %25, 240
  br i1 %26, label %27, label %32

27:                                               ; preds = %21
  store i32 4, i32* %7, align 4
  %28 = load i8*, i8** %5, align 8
  %29 = load i8, i8* %28, align 1
  %30 = sext i8 %29 to i32
  %31 = and i32 %30, 7
  store i32 %31, i32* %8, align 4
  br label %56

32:                                               ; preds = %21
  %33 = load i8*, i8** %5, align 8
  %34 = load i8, i8* %33, align 1
  %35 = zext i8 %34 to i32
  %36 = icmp sge i32 %35, 224
  br i1 %36, label %37, label %42

37:                                               ; preds = %32
  store i32 3, i32* %7, align 4
  %38 = load i8*, i8** %5, align 8
  %39 = load i8, i8* %38, align 1
  %40 = sext i8 %39 to i32
  %41 = and i32 %40, 15
  store i32 %41, i32* %8, align 4
  br label %55

42:                                               ; preds = %32
  %43 = load i8*, i8** %5, align 8
  %44 = load i8, i8* %43, align 1
  %45 = zext i8 %44 to i32
  %46 = icmp sge i32 %45, 192
  br i1 %46, label %47, label %52

47:                                               ; preds = %42
  store i32 2, i32* %7, align 4
  %48 = load i8*, i8** %5, align 8
  %49 = load i8, i8* %48, align 1
  %50 = sext i8 %49 to i32
  %51 = and i32 %50, 31
  store i32 %51, i32* %8, align 4
  br label %54

52:                                               ; preds = %42
  %53 = load i8*, i8** %6, align 8
  call void (i8*, i8*, ...) @error_at(i8* noundef %53, i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i64 0, i64 0)) #2
  unreachable

54:                                               ; preds = %47
  br label %55

55:                                               ; preds = %54, %37
  br label %56

56:                                               ; preds = %55, %27
  store i32 1, i32* %9, align 4
  br label %57

57:                                               ; preds = %83, %56
  %58 = load i32, i32* %9, align 4
  %59 = load i32, i32* %7, align 4
  %60 = icmp slt i32 %58, %59
  br i1 %60, label %61, label %86

61:                                               ; preds = %57
  %62 = load i8*, i8** %5, align 8
  %63 = load i32, i32* %9, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds i8, i8* %62, i64 %64
  %66 = load i8, i8* %65, align 1
  %67 = zext i8 %66 to i32
  %68 = ashr i32 %67, 6
  %69 = icmp ne i32 %68, 2
  br i1 %69, label %70, label %72

70:                                               ; preds = %61
  %71 = load i8*, i8** %6, align 8
  call void (i8*, i8*, ...) @error_at(i8* noundef %71, i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i64 0, i64 0)) #2
  unreachable

72:                                               ; preds = %61
  %73 = load i32, i32* %8, align 4
  %74 = shl i32 %73, 6
  %75 = load i8*, i8** %5, align 8
  %76 = load i32, i32* %9, align 4
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds i8, i8* %75, i64 %77
  %79 = load i8, i8* %78, align 1
  %80 = sext i8 %79 to i32
  %81 = and i32 %80, 63
  %82 = or i32 %74, %81
  store i32 %82, i32* %8, align 4
  br label %83

83:                                               ; preds = %72
  %84 = load i32, i32* %9, align 4
  %85 = add nsw i32 %84, 1
  store i32 %85, i32* %9, align 4
  br label %57, !llvm.loop !6

86:                                               ; preds = %57
  %87 = load i8*, i8** %5, align 8
  %88 = load i32, i32* %7, align 4
  %89 = sext i32 %88 to i64
  %90 = getelementptr inbounds i8, i8* %87, i64 %89
  %91 = load i8**, i8*** %4, align 8
  store i8* %90, i8** %91, align 8
  %92 = load i32, i32* %8, align 4
  store i32 %92, i32* %3, align 4
  br label %93

93:                                               ; preds = %86, %14
  %94 = load i32, i32* %3, align 4
  ret i32 %94
}

; Function Attrs: noreturn
declare void @error_at(i8* noundef, i8* noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @is_ident1(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = call zeroext i1 @in_range(i32* noundef getelementptr inbounds ([107 x i32], [107 x i32]* @is_ident1.range, i64 0, i64 0), i32 noundef %3)
  ret i1 %4
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @in_range(i32* noundef %0, i32 noundef %1) #0 {
  %3 = alloca i1, align 1
  %4 = alloca i32*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32* %0, i32** %4, align 8
  store i32 %1, i32* %5, align 4
  store i32 0, i32* %6, align 4
  br label %7

7:                                                ; preds = %33, %2
  %8 = load i32*, i32** %4, align 8
  %9 = load i32, i32* %6, align 4
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds i32, i32* %8, i64 %10
  %12 = load i32, i32* %11, align 4
  %13 = icmp ne i32 %12, -1
  br i1 %13, label %14, label %36

14:                                               ; preds = %7
  %15 = load i32*, i32** %4, align 8
  %16 = load i32, i32* %6, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds i32, i32* %15, i64 %17
  %19 = load i32, i32* %18, align 4
  %20 = load i32, i32* %5, align 4
  %21 = icmp ule i32 %19, %20
  br i1 %21, label %22, label %32

22:                                               ; preds = %14
  %23 = load i32, i32* %5, align 4
  %24 = load i32*, i32** %4, align 8
  %25 = load i32, i32* %6, align 4
  %26 = add nsw i32 %25, 1
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds i32, i32* %24, i64 %27
  %29 = load i32, i32* %28, align 4
  %30 = icmp ule i32 %23, %29
  br i1 %30, label %31, label %32

31:                                               ; preds = %22
  store i1 true, i1* %3, align 1
  br label %37

32:                                               ; preds = %22, %14
  br label %33

33:                                               ; preds = %32
  %34 = load i32, i32* %6, align 4
  %35 = add nsw i32 %34, 2
  store i32 %35, i32* %6, align 4
  br label %7, !llvm.loop !8

36:                                               ; preds = %7
  store i1 false, i1* %3, align 1
  br label %37

37:                                               ; preds = %36, %31
  %38 = load i1, i1* %3, align 1
  ret i1 %38
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @is_ident2(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = call zeroext i1 @is_ident1(i32 noundef %3)
  br i1 %4, label %8, label %5

5:                                                ; preds = %1
  %6 = load i32, i32* %2, align 4
  %7 = call zeroext i1 @in_range(i32* noundef getelementptr inbounds ([19 x i32], [19 x i32]* @is_ident2.range, i64 0, i64 0), i32 noundef %6)
  br label %8

8:                                                ; preds = %5, %1
  %9 = phi i1 [ true, %1 ], [ %7, %5 ]
  ret i1 %9
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @is_ident3(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = call zeroext i1 @in_range(i32* noundef getelementptr inbounds ([109 x i32], [109 x i32]* @is_ident3.range, i64 0, i64 0), i32 noundef %3)
  ret i1 %4
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @display_width(i8* noundef %0, i32 noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i32 %1, i32* %4, align 4
  %8 = load i8*, i8** %3, align 8
  store i8* %8, i8** %5, align 8
  store i32 0, i32* %6, align 4
  br label %9

9:                                                ; preds = %18, %2
  %10 = load i8*, i8** %3, align 8
  %11 = load i8*, i8** %5, align 8
  %12 = ptrtoint i8* %10 to i64
  %13 = ptrtoint i8* %11 to i64
  %14 = sub i64 %12, %13
  %15 = load i32, i32* %4, align 4
  %16 = sext i32 %15 to i64
  %17 = icmp slt i64 %14, %16
  br i1 %17, label %18, label %25

18:                                               ; preds = %9
  %19 = load i8*, i8** %3, align 8
  %20 = call i32 @decode_utf8(i8** noundef %3, i8* noundef %19)
  store i32 %20, i32* %7, align 4
  %21 = load i32, i32* %7, align 4
  %22 = call i32 @char_width(i32 noundef %21)
  %23 = load i32, i32* %6, align 4
  %24 = add nsw i32 %23, %22
  store i32 %24, i32* %6, align 4
  br label %9, !llvm.loop !9

25:                                               ; preds = %9
  %26 = load i32, i32* %6, align 4
  ret i32 %26
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @char_width(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  %5 = call zeroext i1 @in_range(i32* noundef getelementptr inbounds ([289 x i32], [289 x i32]* @char_width.range1, i64 0, i64 0), i32 noundef %4)
  br i1 %5, label %6, label %7

6:                                                ; preds = %1
  store i32 0, i32* %2, align 4
  br label %12

7:                                                ; preds = %1
  %8 = load i32, i32* %3, align 4
  %9 = call zeroext i1 @in_range(i32* noundef getelementptr inbounds ([29 x i32], [29 x i32]* @char_width.range2, i64 0, i64 0), i32 noundef %8)
  br i1 %9, label %10, label %11

10:                                               ; preds = %7
  store i32 2, i32* %2, align 4
  br label %12

11:                                               ; preds = %7
  store i32 1, i32* %2, align 4
  br label %12

12:                                               ; preds = %11, %10, %6
  %13 = load i32, i32* %2, align 4
  ret i32 %13
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { noreturn }

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
