; ModuleID = 'parse.c'
source_filename = "parse.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.Scope = type { %struct.Scope*, %struct.HashMap, %struct.HashMap }
%struct.HashMap = type { %struct.HashEntry*, i32, i32 }
%struct.HashEntry = type { i8*, i32, i8* }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, %struct._IO_codecvt*, %struct._IO_wide_data*, %struct._IO_FILE*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type opaque
%struct._IO_codecvt = type opaque
%struct._IO_wide_data = type opaque
%struct.Obj = type { %struct.Obj*, i8*, i8*, %struct.Type*, %struct.Token*, i8, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8*, %struct.Relocation*, i8, %struct.Obj*, %struct.Node*, %struct.Obj*, %struct.Obj*, %struct.Obj*, i32, i8, i8, %struct.StringArray }
%struct.Type = type { i32, i32, i32, i8, i8, i8, %struct.Type*, %struct.Type*, %struct.Type*, %struct.Token*, %struct.Token*, i32, %struct.Node*, %struct.Obj*, %struct.Member*, i8, i8, %struct.Type*, %struct.Type*, i8, %struct.Type* }
%struct.Member = type { %struct.Member*, %struct.Type*, %struct.Token*, %struct.Token*, i32, i32, i32, i8, i32, i32 }
%struct.Token = type { i32, %struct.Token*, i64, x86_fp80, i8*, i32, %struct.Type*, i8*, %struct.File*, i8*, i32, i32, i8, i8, %struct.Hideset*, %struct.Token* }
%struct.File = type { i8*, i32, i8*, i8*, i32 }
%struct.Hideset = type opaque
%struct.Relocation = type { %struct.Relocation*, i32, i8**, i64 }
%struct.Node = type { i32, %struct.Node*, %struct.Type*, %struct.Token*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Node*, i8*, i8*, %struct.Node*, %struct.Member*, %struct.Type*, %struct.Node*, i8, %struct.Obj*, i8*, i8*, %struct.Node*, %struct.Node*, %struct.Node*, i64, i64, i8*, %struct.Node*, %struct.Node*, %struct.Node*, %struct.Obj*, %struct.Node*, i8, %struct.Obj*, i64, x86_fp80, i32, [12 x i8] }
%struct.StringArray = type { i8**, i32, i32 }
%struct.VarScope = type { %struct.Obj*, %struct.Type*, %struct.Type*, i32 }
%struct.VarAttr = type { i8, i8, i8, i8, i8, i32 }
%struct.Initializer = type { %struct.Initializer*, %struct.Type*, %struct.Token*, i8, %struct.Node*, %struct.Initializer**, %struct.Member* }
%struct.InitDesg = type { %struct.InitDesg*, i32, %struct.Member*, %struct.Obj* }

@scope = internal global %struct.Scope* @.compoundliteral, align 8
@.str = private unnamed_addr constant [31 x i8] c"%s: in new_cast : node is null\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c"parse.c\00", align 1
@isDotfile = external global i8, align 1
@dotf = external global %struct._IO_FILE*, align 8
@base_file = external global i8*, align 8
@opt_o = external global i8*, align 8
@stderr = external global %struct._IO_FILE*, align 8
@.str.2 = private unnamed_addr constant [44 x i8] c"%s: in parse base_file and opt_o are null!\0A\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c".dot\00", align 1
@.str.4 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str.5 = private unnamed_addr constant [39 x i8] c"%s: in parse dot file cannot be opend\0A\00", align 1
@.str.6 = private unnamed_addr constant [13 x i8] c"digraph A {\0A\00", align 1
@opt_fbuiltin = external global i8, align 1
@globals = internal global %struct.Obj* null, align 8
@.str.7 = private unnamed_addr constant [10 x i8] c"NULL_EXPR\00", align 1
@.str.8 = private unnamed_addr constant [4 x i8] c"ADD\00", align 1
@.str.9 = private unnamed_addr constant [4 x i8] c"SUB\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"MUL\00", align 1
@.str.11 = private unnamed_addr constant [4 x i8] c"DIV\00", align 1
@.str.12 = private unnamed_addr constant [4 x i8] c"NEG\00", align 1
@.str.13 = private unnamed_addr constant [4 x i8] c"MOD\00", align 1
@.str.14 = private unnamed_addr constant [7 x i8] c"BITAND\00", align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"BITOR\00", align 1
@.str.16 = private unnamed_addr constant [7 x i8] c"BITXOR\00", align 1
@.str.17 = private unnamed_addr constant [4 x i8] c"SHL\00", align 1
@.str.18 = private unnamed_addr constant [4 x i8] c"SHR\00", align 1
@.str.19 = private unnamed_addr constant [3 x i8] c"EQ\00", align 1
@.str.20 = private unnamed_addr constant [3 x i8] c"NE\00", align 1
@.str.21 = private unnamed_addr constant [3 x i8] c"LT\00", align 1
@.str.22 = private unnamed_addr constant [3 x i8] c"LE\00", align 1
@.str.23 = private unnamed_addr constant [7 x i8] c"ASSIGN\00", align 1
@.str.24 = private unnamed_addr constant [5 x i8] c"COND\00", align 1
@.str.25 = private unnamed_addr constant [6 x i8] c"COMMA\00", align 1
@.str.26 = private unnamed_addr constant [7 x i8] c"MEMBER\00", align 1
@.str.27 = private unnamed_addr constant [5 x i8] c"ADDR\00", align 1
@.str.28 = private unnamed_addr constant [6 x i8] c"DEREF\00", align 1
@.str.29 = private unnamed_addr constant [4 x i8] c"NOT\00", align 1
@.str.30 = private unnamed_addr constant [7 x i8] c"BITNOT\00", align 1
@.str.31 = private unnamed_addr constant [7 x i8] c"LOGAND\00", align 1
@.str.32 = private unnamed_addr constant [6 x i8] c"LOGOR\00", align 1
@.str.33 = private unnamed_addr constant [7 x i8] c"RETURN\00", align 1
@.str.34 = private unnamed_addr constant [3 x i8] c"IF\00", align 1
@.str.35 = private unnamed_addr constant [4 x i8] c"FOR\00", align 1
@.str.36 = private unnamed_addr constant [3 x i8] c"DO\00", align 1
@.str.37 = private unnamed_addr constant [7 x i8] c"SWITCH\00", align 1
@.str.38 = private unnamed_addr constant [5 x i8] c"CASE\00", align 1
@.str.39 = private unnamed_addr constant [6 x i8] c"BLOCK\00", align 1
@.str.40 = private unnamed_addr constant [5 x i8] c"GOTO\00", align 1
@.str.41 = private unnamed_addr constant [10 x i8] c"GOTO_EXPR\00", align 1
@.str.42 = private unnamed_addr constant [6 x i8] c"LABLE\00", align 1
@.str.43 = private unnamed_addr constant [10 x i8] c"LABEL_VAL\00", align 1
@.str.44 = private unnamed_addr constant [9 x i8] c"FUNCCALL\00", align 1
@.str.45 = private unnamed_addr constant [9 x i8] c"EXPRSTMR\00", align 1
@.str.46 = private unnamed_addr constant [9 x i8] c"STMTEXPR\00", align 1
@.str.47 = private unnamed_addr constant [4 x i8] c"VAR\00", align 1
@.str.48 = private unnamed_addr constant [7 x i8] c"VLAPTR\00", align 1
@.str.49 = private unnamed_addr constant [4 x i8] c"NUM\00", align 1
@.str.50 = private unnamed_addr constant [5 x i8] c"CAST\00", align 1
@.str.51 = private unnamed_addr constant [8 x i8] c"MEMZERO\00", align 1
@.str.52 = private unnamed_addr constant [4 x i8] c"ASM\00", align 1
@.str.53 = private unnamed_addr constant [4 x i8] c"CAS\00", align 1
@.str.54 = private unnamed_addr constant [5 x i8] c"EXCH\00", align 1
@.str.55 = private unnamed_addr constant [12 x i8] c"UNREACHABLE\00", align 1
@.compoundliteral = internal global %struct.Scope zeroinitializer, align 8
@.str.56 = private unnamed_addr constant [43 x i8] c"%s: in eval2 : not a compile-time constant\00", align 1
@.str.57 = private unnamed_addr constant [35 x i8] c"%s: in eval2 : invalid initializer\00", align 1
@.str.58 = private unnamed_addr constant [44 x i8] c"%s: in eval2 : not a compile-time constant2\00", align 1
@.str.59 = private unnamed_addr constant [36 x i8] c"%s: in eval2 : invalid initializer2\00", align 1
@.str.60 = private unnamed_addr constant [44 x i8] c"%s: in eval2 : not a compile-time constant3\00", align 1
@.str.61 = private unnamed_addr constant [50 x i8] c"%s : in eval_double : not a compile-time constant\00", align 1
@.str.62 = private unnamed_addr constant [44 x i8] c"%s: in eval2 : not a compile-time constant4\00", align 1
@.str.63 = private unnamed_addr constant [36 x i8] c"%s: in eval2 : invalid initializer3\00", align 1
@.str.64 = private unnamed_addr constant [2 x i8] c"?\00", align 1
@.str.65 = private unnamed_addr constant [2 x i8] c":\00", align 1
@.str.66 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.67 = private unnamed_addr constant [3 x i8] c"||\00", align 1
@.str.68 = private unnamed_addr constant [3 x i8] c"&&\00", align 1
@.str.69 = private unnamed_addr constant [2 x i8] c"|\00", align 1
@.str.70 = private unnamed_addr constant [2 x i8] c"^\00", align 1
@.str.71 = private unnamed_addr constant [2 x i8] c"&\00", align 1
@.str.72 = private unnamed_addr constant [3 x i8] c"==\00", align 1
@.str.73 = private unnamed_addr constant [3 x i8] c"!=\00", align 1
@.str.74 = private unnamed_addr constant [2 x i8] c"<\00", align 1
@.str.75 = private unnamed_addr constant [3 x i8] c"<=\00", align 1
@.str.76 = private unnamed_addr constant [2 x i8] c">\00", align 1
@.str.77 = private unnamed_addr constant [3 x i8] c">=\00", align 1
@.str.78 = private unnamed_addr constant [3 x i8] c"<<\00", align 1
@.str.79 = private unnamed_addr constant [3 x i8] c">>\00", align 1
@.str.80 = private unnamed_addr constant [2 x i8] c"+\00", align 1
@.str.81 = private unnamed_addr constant [2 x i8] c"-\00", align 1
@.str.82 = private unnamed_addr constant [2 x i8] c"*\00", align 1
@.str.83 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.84 = private unnamed_addr constant [2 x i8] c"%\00", align 1
@.str.85 = private unnamed_addr constant [2 x i8] c"(\00", align 1
@.str.86 = private unnamed_addr constant [2 x i8] c")\00", align 1
@.str.87 = private unnamed_addr constant [2 x i8] c"{\00", align 1
@is_typename.map = internal global %struct.HashMap zeroinitializer, align 8
@is_typename.kw = internal global [31 x i8*] [i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.88, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.89, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.90, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.91, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.93, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.94, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.95, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.96, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.97, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.98, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.100, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.101, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.102, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.103, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.104, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.105, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.106, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.107, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.108, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.109, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.110, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.111, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.112, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.113, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.114, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.115, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.116, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.117, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.118, i32 0, i32 0)], align 16
@.str.88 = private unnamed_addr constant [5 x i8] c"void\00", align 1
@.str.89 = private unnamed_addr constant [6 x i8] c"_Bool\00", align 1
@.str.90 = private unnamed_addr constant [5 x i8] c"char\00", align 1
@.str.91 = private unnamed_addr constant [6 x i8] c"short\00", align 1
@.str.92 = private unnamed_addr constant [4 x i8] c"int\00", align 1
@.str.93 = private unnamed_addr constant [5 x i8] c"long\00", align 1
@.str.94 = private unnamed_addr constant [7 x i8] c"struct\00", align 1
@.str.95 = private unnamed_addr constant [6 x i8] c"union\00", align 1
@.str.96 = private unnamed_addr constant [8 x i8] c"typedef\00", align 1
@.str.97 = private unnamed_addr constant [5 x i8] c"enum\00", align 1
@.str.98 = private unnamed_addr constant [7 x i8] c"static\00", align 1
@.str.99 = private unnamed_addr constant [7 x i8] c"extern\00", align 1
@.str.100 = private unnamed_addr constant [9 x i8] c"_Alignas\00", align 1
@.str.101 = private unnamed_addr constant [7 x i8] c"signed\00", align 1
@.str.102 = private unnamed_addr constant [9 x i8] c"unsigned\00", align 1
@.str.103 = private unnamed_addr constant [6 x i8] c"const\00", align 1
@.str.104 = private unnamed_addr constant [9 x i8] c"volatile\00", align 1
@.str.105 = private unnamed_addr constant [5 x i8] c"auto\00", align 1
@.str.106 = private unnamed_addr constant [9 x i8] c"register\00", align 1
@.str.107 = private unnamed_addr constant [9 x i8] c"restrict\00", align 1
@.str.108 = private unnamed_addr constant [11 x i8] c"__restrict\00", align 1
@.str.109 = private unnamed_addr constant [13 x i8] c"__restrict__\00", align 1
@.str.110 = private unnamed_addr constant [10 x i8] c"_Noreturn\00", align 1
@.str.111 = private unnamed_addr constant [6 x i8] c"float\00", align 1
@.str.112 = private unnamed_addr constant [7 x i8] c"double\00", align 1
@.str.113 = private unnamed_addr constant [7 x i8] c"typeof\00", align 1
@.str.114 = private unnamed_addr constant [7 x i8] c"inline\00", align 1
@.str.115 = private unnamed_addr constant [14 x i8] c"_Thread_local\00", align 1
@.str.116 = private unnamed_addr constant [9 x i8] c"__thread\00", align 1
@.str.117 = private unnamed_addr constant [8 x i8] c"_Atomic\00", align 1
@.str.118 = private unnamed_addr constant [9 x i8] c"_Complex\00", align 1
@.str.119 = private unnamed_addr constant [2 x i8] c"[\00", align 1
@.str.120 = private unnamed_addr constant [4 x i8] c"...\00", align 1
@.str.121 = private unnamed_addr constant [2 x i8] c";\00", align 1
@.str.122 = private unnamed_addr constant [2 x i8] c",\00", align 1
@.str.123 = private unnamed_addr constant [7 x i8] c"sizeof\00", align 1
@.str.124 = private unnamed_addr constant [9 x i8] c"_Alignof\00", align 1
@.str.125 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@.str.126 = private unnamed_addr constant [47 x i8] c"%s: in unary : cannot take address of bitfield\00", align 1
@.str.127 = private unnamed_addr constant [2 x i8] c"!\00", align 1
@.str.128 = private unnamed_addr constant [2 x i8] c"~\00", align 1
@.str.129 = private unnamed_addr constant [3 x i8] c"++\00", align 1
@.str.130 = private unnamed_addr constant [3 x i8] c"--\00", align 1
@gotos = internal global %struct.Node* null, align 8
@.str.131 = private unnamed_addr constant [14 x i8] c"%s%d -> %s%d\0A\00", align 1
@new_unique_name.id = internal global i32 0, align 4
@.str.132 = private unnamed_addr constant [7 x i8] c".L..%d\00", align 1
@.str.133 = private unnamed_addr constant [42 x i8] c"%s: in get_ident : expected an identifier\00", align 1
@.str.134 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.135 = private unnamed_addr constant [3 x i8] c"->\00", align 1
@.str.136 = private unnamed_addr constant [29 x i8] c"%s: in new_var : var is null\00", align 1
@.str.137 = private unnamed_addr constant [32 x i8] c"%s: in push_scope : sc is null!\00", align 1
@.str.138 = private unnamed_addr constant [39 x i8] c"%s: in gvar_initializer : buf is null!\00", align 1
@.str.139 = private unnamed_addr constant [38 x i8] c"%s: in new_initializer : init is null\00", align 1
@.str.140 = private unnamed_addr constant [48 x i8] c"%s: in new_initializer : init->children is null\00", align 1
@.str.141 = private unnamed_addr constant [54 x i8] c"%s: in new_initializer : init->children is null (bis)\00", align 1
@.str.142 = private unnamed_addr constant [39 x i8] c"%s: in new_initializer : child is null\00", align 1
@.str.143 = private unnamed_addr constant [2 x i8] c"}\00", align 1
@.str.144 = private unnamed_addr constant [89 x i8] c"%s: in string_initializer : array of inappropriate type initialized from string constant\00", align 1
@.str.145 = private unnamed_addr constant [70 x i8] c"%s: in array_designator : array designator index exceeds array bounds\00", align 1
@.str.146 = private unnamed_addr constant [53 x i8] c"%s: in array designator : index exceeds array bounds\00", align 1
@.str.147 = private unnamed_addr constant [50 x i8] c"%s: in array designator : range [%d, %d] is empty\00", align 1
@.str.148 = private unnamed_addr constant [58 x i8] c"%s: in designation : array index in non-array initializer\00", align 1
@.str.149 = private unnamed_addr constant [66 x i8] c"%s: in designation: field name not in struct or union initializer\00", align 1
@.str.150 = private unnamed_addr constant [2 x i8] c"=\00", align 1
@.str.151 = private unnamed_addr constant [55 x i8] c"%s: in struct_designator : expected a field designator\00", align 1
@.str.152 = private unnamed_addr constant [53 x i8] c"%s: in struct_designator : struct has no such member\00", align 1
@.str.153 = private unnamed_addr constant [3 x i8] c"+=\00", align 1
@.str.154 = private unnamed_addr constant [3 x i8] c"-=\00", align 1
@.str.155 = private unnamed_addr constant [3 x i8] c"*=\00", align 1
@.str.156 = private unnamed_addr constant [3 x i8] c"/=\00", align 1
@.str.157 = private unnamed_addr constant [3 x i8] c"%=\00", align 1
@.str.158 = private unnamed_addr constant [3 x i8] c"&=\00", align 1
@.str.159 = private unnamed_addr constant [3 x i8] c"|=\00", align 1
@.str.160 = private unnamed_addr constant [3 x i8] c"^=\00", align 1
@.str.161 = private unnamed_addr constant [4 x i8] c"<<=\00", align 1
@.str.162 = private unnamed_addr constant [4 x i8] c">>=\00", align 1
@.str.163 = private unnamed_addr constant [37 x i8] c"%s: in copy_struct_type :  m is null\00", align 1
@.str.164 = private unnamed_addr constant [37 x i8] c"%s: in write_gvar_data : rel is null\00", align 1
@.str.165 = private unnamed_addr constant [24 x i8] c"internal error at %s:%d\00", align 1
@.str.166 = private unnamed_addr constant [9 x i8] c"_Generic\00", align 1
@.str.167 = private unnamed_addr constant [29 x i8] c"__builtin_types_compatible_p\00", align 1
@.str.168 = private unnamed_addr constant [20 x i8] c"__builtin_reg_class\00", align 1
@.str.169 = private unnamed_addr constant [27 x i8] c"__builtin_compare_and_swap\00", align 1
@.str.170 = private unnamed_addr constant [26 x i8] c"__builtin_atomic_exchange\00", align 1
@.str.171 = private unnamed_addr constant [26 x i8] c"__builtin_atomic_fetch_op\00", align 1
@.str.172 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.173 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@.str.174 = private unnamed_addr constant [2 x i8] c"2\00", align 1
@.str.175 = private unnamed_addr constant [2 x i8] c"3\00", align 1
@.str.176 = private unnamed_addr constant [2 x i8] c"4\00", align 1
@.str.177 = private unnamed_addr constant [40 x i8] c"%s: in primary : invalid fetch operator\00", align 1
@current_fn = internal global %struct.Obj* null, align 8
@.str.178 = private unnamed_addr constant [43 x i8] c"%s: in primary : error: undefined variable\00", align 1
@.str.179 = private unnamed_addr constant [40 x i8] c"%s: in primary : expected an expression\00", align 1
@.str.180 = private unnamed_addr constant [41 x i8] c"%s: in enter_scope : sc pointer is null!\00", align 1
@.str.181 = private unnamed_addr constant [44 x i8] c"%s: in declaration : variable declared void\00", align 1
@.str.182 = private unnamed_addr constant [44 x i8] c"%s: in declaration : variable name omitted1\00", align 1
@.str.183 = private unnamed_addr constant [65 x i8] c"%s: in declaration: variable-sized object may not be initialized\00", align 1
@.str.184 = private unnamed_addr constant [50 x i8] c"%s: in declaration : variable has incomplete type\00", align 1
@builtin_alloca = internal global %struct.Obj* null, align 8
@.str.185 = private unnamed_addr constant [7 x i8] c"return\00", align 1
@.str.186 = private unnamed_addr constant [54 x i8] c"%s: in stmt : Non-void function must return something\00", align 1
@.str.187 = private unnamed_addr constant [61 x i8] c"%s: in stmt : Void function must return void type expression\00", align 1
@.str.188 = private unnamed_addr constant [67 x i8] c"%s: in stmt : Non-void function cannot return void type expression\00", align 1
@.str.189 = private unnamed_addr constant [3 x i8] c"if\00", align 1
@.str.190 = private unnamed_addr constant [5 x i8] c"else\00", align 1
@.str.191 = private unnamed_addr constant [7 x i8] c"switch\00", align 1
@current_switch = internal global %struct.Node* null, align 8
@brk_label = internal global i8* null, align 8
@.str.192 = private unnamed_addr constant [5 x i8] c"case\00", align 1
@.str.193 = private unnamed_addr constant [25 x i8] c"%s: in stmt : stray case\00", align 1
@.str.194 = private unnamed_addr constant [41 x i8] c"%s: in stmt : empty case range specified\00", align 1
@.str.195 = private unnamed_addr constant [8 x i8] c"default\00", align 1
@.str.196 = private unnamed_addr constant [28 x i8] c"%s: in stmt : stray default\00", align 1
@.str.197 = private unnamed_addr constant [4 x i8] c"for\00", align 1
@cont_label = internal global i8* null, align 8
@.str.198 = private unnamed_addr constant [6 x i8] c"while\00", align 1
@.str.199 = private unnamed_addr constant [3 x i8] c"do\00", align 1
@.str.200 = private unnamed_addr constant [4 x i8] c"asm\00", align 1
@.str.201 = private unnamed_addr constant [8 x i8] c"__asm__\00", align 1
@.str.202 = private unnamed_addr constant [5 x i8] c"goto\00", align 1
@.str.203 = private unnamed_addr constant [6 x i8] c"break\00", align 1
@.str.204 = private unnamed_addr constant [26 x i8] c"%s: in stmt : stray break\00", align 1
@.str.205 = private unnamed_addr constant [9 x i8] c"continue\00", align 1
@.str.206 = private unnamed_addr constant [29 x i8] c"%s: in stmt : stray continue\00", align 1
@labels = internal global %struct.Node* null, align 8
@.str.207 = private unnamed_addr constant [42 x i8] c"%s: in asm_stmt : expected string literal\00", align 1
@.str.208 = private unnamed_addr constant [68 x i8] c"%s: in asm_stmt : error during extended_asm function null returned!\00", align 1
@ty_ulong = external global %struct.Type*, align 8
@.str.209 = private unnamed_addr constant [32 x i8] c"%s: in funcall : not a function\00", align 1
@.str.210 = private unnamed_addr constant [36 x i8] c"%s: in funcall : too many arguments\00", align 1
@ty_double = external global %struct.Type*, align 8
@.str.211 = private unnamed_addr constant [35 x i8] c"%s: in funcall : too few arguments\00", align 1
@.str.212 = private unnamed_addr constant [45 x i8] c"%s: in struct_ref : not a struct nor a union\00", align 1
@.str.213 = private unnamed_addr constant [35 x i8] c"%s: in struct_ref : no such member\00", align 1
@.str.214 = private unnamed_addr constant [34 x i8] c"%s: in new_add : invalid operands\00", align 1
@ty_long = external global %struct.Type*, align 8
@.str.215 = private unnamed_addr constant [34 x i8] c"%s: in new_sub : invalid operands\00", align 1
@locals = internal global %struct.Obj* null, align 8
@order = internal global i32 0, align 4
@.str.216 = private unnamed_addr constant [55 x i8] c"%s: in new_binary : Cannot assign void type expression\00", align 1
@new_node.count = internal global i32 0, align 4
@.str.217 = private unnamed_addr constant [31 x i8] c"%s: in new_node : node is null\00", align 1
@ty_void = external global %struct.Type*, align 8
@ty_int = external global %struct.Type*, align 8
@.str.218 = private unnamed_addr constant [7 x i8] c"alloca\00", align 1
@.str.219 = private unnamed_addr constant [74 x i8] c"%s : in declspec : storage class specifier is not allowed in this context\00", align 1
@.str.220 = private unnamed_addr constant [106 x i8] c"%s: in declspec : typedef may not be used together with static, extern, inline, __thread or _Thread_local\00", align 1
@.str.221 = private unnamed_addr constant [58 x i8] c"%s: in declspec : _Alignas is not allowed in this context\00", align 1
@ty_bool = external global %struct.Type*, align 8
@ty_char = external global %struct.Type*, align 8
@ty_uchar = external global %struct.Type*, align 8
@ty_short = external global %struct.Type*, align 8
@ty_ushort = external global %struct.Type*, align 8
@ty_uint = external global %struct.Type*, align 8
@ty_float = external global %struct.Type*, align 8
@ty_ldouble = external global %struct.Type*, align 8
@.str.222 = private unnamed_addr constant [31 x i8] c"%s: in declspec : invalid type\00", align 1
@.str.223 = private unnamed_addr constant [14 x i8] c"__attribute__\00", align 1
@.str.224 = private unnamed_addr constant [7 x i8] c"packed\00", align 1
@.str.225 = private unnamed_addr constant [8 x i8] c"aligned\00", align 1
@.str.226 = private unnamed_addr constant [42 x i8] c"%s: in attribute_list : unknown attribute\00", align 1
@.str.227 = private unnamed_addr constant [36 x i8] c"%s: in struct_members : mem is null\00", align 1
@.str.228 = private unnamed_addr constant [42 x i8] c"%s: in struct_members : mem is null (bis)\00", align 1
@.str.229 = private unnamed_addr constant [55 x i8] c"%s: in struct_members : only integers can be bitfields\00", align 1
@.str.230 = private unnamed_addr constant [42 x i8] c"%s: in enum_specifier : unknown enum type\00", align 1
@.str.231 = private unnamed_addr constant [40 x i8] c"%s: in enum_specifier : not an enum tag\00", align 1
@.str.232 = private unnamed_addr constant [44 x i8] c"%s: in parse_typedef : typedef name omitted\00", align 1
@.str.233 = private unnamed_addr constant [40 x i8] c"%s: in function : function name omitted\00", align 1
@.str.234 = private unnamed_addr constant [59 x i8] c"%s: in function : redeclared as a different kind of symbol\00", align 1
@.str.235 = private unnamed_addr constant [37 x i8] c"%s: in function : redefinition of %s\00", align 1
@.str.236 = private unnamed_addr constant [70 x i8] c"%s: in function : static declaration follows a non-static declaration\00", align 1
@.str.237 = private unnamed_addr constant [12 x i8] c"__va_area__\00", align 1
@.str.238 = private unnamed_addr constant [16 x i8] c"__alloca_size__\00", align 1
@.str.239 = private unnamed_addr constant [9 x i8] c"__func__\00", align 1
@.str.240 = private unnamed_addr constant [13 x i8] c"__FUNCTION__\00", align 1
@.str.241 = private unnamed_addr constant [53 x i8] c"%s: in resolve_goto_labels : use of undeclared label\00", align 1
@.str.242 = private unnamed_addr constant [47 x i8] c"%s: in global_variable : variable name omitted\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.VarScope* @find_var(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.VarScope*, align 8
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Scope*, align 8
  %5 = alloca %struct.VarScope*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %6 = load %struct.Scope*, %struct.Scope** @scope, align 8
  store %struct.Scope* %6, %struct.Scope** %4, align 8
  br label %7

7:                                                ; preds = %26, %1
  %8 = load %struct.Scope*, %struct.Scope** %4, align 8
  %9 = icmp ne %struct.Scope* %8, null
  br i1 %9, label %10, label %30

10:                                               ; preds = %7
  %11 = load %struct.Scope*, %struct.Scope** %4, align 8
  %12 = getelementptr inbounds %struct.Scope, %struct.Scope* %11, i32 0, i32 1
  %13 = load %struct.Token*, %struct.Token** %3, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 4
  %15 = load i8*, i8** %14, align 16
  %16 = load %struct.Token*, %struct.Token** %3, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 5
  %18 = load i32, i32* %17, align 8
  %19 = call i8* @hashmap_get2(%struct.HashMap* noundef %12, i8* noundef %15, i32 noundef %18)
  %20 = bitcast i8* %19 to %struct.VarScope*
  store %struct.VarScope* %20, %struct.VarScope** %5, align 8
  %21 = load %struct.VarScope*, %struct.VarScope** %5, align 8
  %22 = icmp ne %struct.VarScope* %21, null
  br i1 %22, label %23, label %25

23:                                               ; preds = %10
  %24 = load %struct.VarScope*, %struct.VarScope** %5, align 8
  store %struct.VarScope* %24, %struct.VarScope** %2, align 8
  br label %31

25:                                               ; preds = %10
  br label %26

26:                                               ; preds = %25
  %27 = load %struct.Scope*, %struct.Scope** %4, align 8
  %28 = getelementptr inbounds %struct.Scope, %struct.Scope* %27, i32 0, i32 0
  %29 = load %struct.Scope*, %struct.Scope** %28, align 8
  store %struct.Scope* %29, %struct.Scope** %4, align 8
  br label %7, !llvm.loop !6

30:                                               ; preds = %7
  store %struct.VarScope* null, %struct.VarScope** %2, align 8
  br label %31

31:                                               ; preds = %30, %23
  %32 = load %struct.VarScope*, %struct.VarScope** %2, align 8
  ret %struct.VarScope* %32
}

declare i8* @hashmap_get2(%struct.HashMap* noundef, i8* noundef, i32 noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Node* @new_cast(%struct.Node* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  %6 = load %struct.Node*, %struct.Node** %3, align 8
  call void @add_type(%struct.Node* noundef %6)
  %7 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 320) #8
  %8 = bitcast i8* %7 to %struct.Node*
  store %struct.Node* %8, %struct.Node** %5, align 8
  %9 = load %struct.Node*, %struct.Node** %5, align 8
  %10 = icmp eq %struct.Node* %9, null
  br i1 %10, label %11, label %12

11:                                               ; preds = %2
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

12:                                               ; preds = %2
  %13 = load %struct.Node*, %struct.Node** %5, align 8
  %14 = getelementptr inbounds %struct.Node, %struct.Node* %13, i32 0, i32 0
  store i32 43, i32* %14, align 16
  %15 = load %struct.Node*, %struct.Node** %3, align 8
  %16 = getelementptr inbounds %struct.Node, %struct.Node* %15, i32 0, i32 3
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = load %struct.Node*, %struct.Node** %5, align 8
  %19 = getelementptr inbounds %struct.Node, %struct.Node* %18, i32 0, i32 3
  store %struct.Token* %17, %struct.Token** %19, align 8
  %20 = load %struct.Node*, %struct.Node** %3, align 8
  %21 = load %struct.Node*, %struct.Node** %5, align 8
  %22 = getelementptr inbounds %struct.Node, %struct.Node* %21, i32 0, i32 4
  store %struct.Node* %20, %struct.Node** %22, align 16
  %23 = load %struct.Type*, %struct.Type** %4, align 8
  %24 = call %struct.Type* @copy_type(%struct.Type* noundef %23)
  %25 = load %struct.Node*, %struct.Node** %5, align 8
  %26 = getelementptr inbounds %struct.Node, %struct.Node* %25, i32 0, i32 2
  store %struct.Type* %24, %struct.Type** %26, align 16
  %27 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %27
}

declare void @add_type(%struct.Node* noundef) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64 noundef, i64 noundef) #2

; Function Attrs: noreturn
declare void @error(i8* noundef, ...) #3

declare %struct.Type* @copy_type(%struct.Type* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i64 @const_expr(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load %struct.Token**, %struct.Token*** %3, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @conditional(%struct.Token** noundef %6, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  %9 = load %struct.Node*, %struct.Node** %5, align 8
  %10 = call i64 @eval(%struct.Node* noundef %9)
  ret i64 %10
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @conditional(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Obj*, align 8
  %8 = alloca %struct.Node*, align 8
  %9 = alloca %struct.Node*, align 8
  %10 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %11 = load %struct.Token*, %struct.Token** %5, align 8
  %12 = call %struct.Node* @logor(%struct.Token** noundef %5, %struct.Token* noundef %11)
  store %struct.Node* %12, %struct.Node** %6, align 8
  %13 = load %struct.Token*, %struct.Token** %5, align 8
  %14 = call zeroext i1 @equal(%struct.Token* noundef %13, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.64, i64 0, i64 0))
  br i1 %14, label %19, label %15

15:                                               ; preds = %2
  %16 = load %struct.Token*, %struct.Token** %5, align 8
  %17 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %16, %struct.Token** %17, align 8
  %18 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %18, %struct.Node** %3, align 8
  br label %81

19:                                               ; preds = %2
  %20 = load %struct.Token*, %struct.Token** %5, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 1
  %22 = load %struct.Token*, %struct.Token** %21, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  br i1 %23, label %24, label %61

24:                                               ; preds = %19
  %25 = load %struct.Node*, %struct.Node** %6, align 8
  call void @add_type(%struct.Node* noundef %25)
  %26 = load %struct.Node*, %struct.Node** %6, align 8
  %27 = getelementptr inbounds %struct.Node, %struct.Node* %26, i32 0, i32 2
  %28 = load %struct.Type*, %struct.Type** %27, align 16
  %29 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %28, i8* noundef null)
  store %struct.Obj* %29, %struct.Obj** %7, align 8
  %30 = load %struct.Obj*, %struct.Obj** %7, align 8
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = call %struct.Node* @new_var_node(%struct.Obj* noundef %30, %struct.Token* noundef %31)
  %33 = load %struct.Node*, %struct.Node** %6, align 8
  %34 = load %struct.Token*, %struct.Token** %5, align 8
  %35 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %32, %struct.Node* noundef %33, %struct.Token* noundef %34)
  store %struct.Node* %35, %struct.Node** %8, align 8
  %36 = load %struct.Token*, %struct.Token** %5, align 8
  %37 = call %struct.Node* @new_node(i32 noundef 17, %struct.Token* noundef %36)
  store %struct.Node* %37, %struct.Node** %9, align 8
  %38 = load %struct.Obj*, %struct.Obj** %7, align 8
  %39 = load %struct.Token*, %struct.Token** %5, align 8
  %40 = call %struct.Node* @new_var_node(%struct.Obj* noundef %38, %struct.Token* noundef %39)
  %41 = load %struct.Node*, %struct.Node** %9, align 8
  %42 = getelementptr inbounds %struct.Node, %struct.Node* %41, i32 0, i32 6
  store %struct.Node* %40, %struct.Node** %42, align 16
  %43 = load %struct.Obj*, %struct.Obj** %7, align 8
  %44 = load %struct.Token*, %struct.Token** %5, align 8
  %45 = call %struct.Node* @new_var_node(%struct.Obj* noundef %43, %struct.Token* noundef %44)
  %46 = load %struct.Node*, %struct.Node** %9, align 8
  %47 = getelementptr inbounds %struct.Node, %struct.Node* %46, i32 0, i32 7
  store %struct.Node* %45, %struct.Node** %47, align 8
  %48 = load %struct.Token**, %struct.Token*** %4, align 8
  %49 = load %struct.Token*, %struct.Token** %5, align 8
  %50 = getelementptr inbounds %struct.Token, %struct.Token* %49, i32 0, i32 1
  %51 = load %struct.Token*, %struct.Token** %50, align 8
  %52 = getelementptr inbounds %struct.Token, %struct.Token* %51, i32 0, i32 1
  %53 = load %struct.Token*, %struct.Token** %52, align 8
  %54 = call %struct.Node* @conditional(%struct.Token** noundef %48, %struct.Token* noundef %53)
  %55 = load %struct.Node*, %struct.Node** %9, align 8
  %56 = getelementptr inbounds %struct.Node, %struct.Node* %55, i32 0, i32 8
  store %struct.Node* %54, %struct.Node** %56, align 16
  %57 = load %struct.Node*, %struct.Node** %8, align 8
  %58 = load %struct.Node*, %struct.Node** %9, align 8
  %59 = load %struct.Token*, %struct.Token** %5, align 8
  %60 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %57, %struct.Node* noundef %58, %struct.Token* noundef %59)
  store %struct.Node* %60, %struct.Node** %3, align 8
  br label %81

61:                                               ; preds = %19
  %62 = load %struct.Token*, %struct.Token** %5, align 8
  %63 = call %struct.Node* @new_node(i32 noundef 17, %struct.Token* noundef %62)
  store %struct.Node* %63, %struct.Node** %10, align 8
  %64 = load %struct.Node*, %struct.Node** %6, align 8
  %65 = load %struct.Node*, %struct.Node** %10, align 8
  %66 = getelementptr inbounds %struct.Node, %struct.Node* %65, i32 0, i32 6
  store %struct.Node* %64, %struct.Node** %66, align 16
  %67 = load %struct.Token*, %struct.Token** %5, align 8
  %68 = getelementptr inbounds %struct.Token, %struct.Token* %67, i32 0, i32 1
  %69 = load %struct.Token*, %struct.Token** %68, align 8
  %70 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %69)
  %71 = load %struct.Node*, %struct.Node** %10, align 8
  %72 = getelementptr inbounds %struct.Node, %struct.Node* %71, i32 0, i32 7
  store %struct.Node* %70, %struct.Node** %72, align 8
  %73 = load %struct.Token*, %struct.Token** %5, align 8
  %74 = call %struct.Token* @skip(%struct.Token* noundef %73, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  store %struct.Token* %74, %struct.Token** %5, align 8
  %75 = load %struct.Token**, %struct.Token*** %4, align 8
  %76 = load %struct.Token*, %struct.Token** %5, align 8
  %77 = call %struct.Node* @conditional(%struct.Token** noundef %75, %struct.Token* noundef %76)
  %78 = load %struct.Node*, %struct.Node** %10, align 8
  %79 = getelementptr inbounds %struct.Node, %struct.Node* %78, i32 0, i32 8
  store %struct.Node* %77, %struct.Node** %79, align 16
  %80 = load %struct.Node*, %struct.Node** %10, align 8
  store %struct.Node* %80, %struct.Node** %3, align 8
  br label %81

81:                                               ; preds = %61, %24, %15
  %82 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %82
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i64 @eval(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %2, align 8
  %3 = load %struct.Node*, %struct.Node** %2, align 8
  %4 = call i64 @eval2(%struct.Node* noundef %3, i8*** noundef null)
  ret i64 %4
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Obj* @find_func(i8* noundef %0) #0 {
  %2 = alloca %struct.Obj*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct.Scope*, align 8
  %5 = alloca %struct.VarScope*, align 8
  store i8* %0, i8** %3, align 8
  %6 = load %struct.Scope*, %struct.Scope** @scope, align 8
  store %struct.Scope* %6, %struct.Scope** %4, align 8
  br label %7

7:                                                ; preds = %12, %1
  %8 = load %struct.Scope*, %struct.Scope** %4, align 8
  %9 = getelementptr inbounds %struct.Scope, %struct.Scope* %8, i32 0, i32 0
  %10 = load %struct.Scope*, %struct.Scope** %9, align 8
  %11 = icmp ne %struct.Scope* %10, null
  br i1 %11, label %12, label %16

12:                                               ; preds = %7
  %13 = load %struct.Scope*, %struct.Scope** %4, align 8
  %14 = getelementptr inbounds %struct.Scope, %struct.Scope* %13, i32 0, i32 0
  %15 = load %struct.Scope*, %struct.Scope** %14, align 8
  store %struct.Scope* %15, %struct.Scope** %4, align 8
  br label %7, !llvm.loop !8

16:                                               ; preds = %7
  %17 = load %struct.Scope*, %struct.Scope** %4, align 8
  %18 = getelementptr inbounds %struct.Scope, %struct.Scope* %17, i32 0, i32 1
  %19 = load i8*, i8** %3, align 8
  %20 = call i8* @hashmap_get(%struct.HashMap* noundef %18, i8* noundef %19)
  %21 = bitcast i8* %20 to %struct.VarScope*
  store %struct.VarScope* %21, %struct.VarScope** %5, align 8
  %22 = load %struct.VarScope*, %struct.VarScope** %5, align 8
  %23 = icmp ne %struct.VarScope* %22, null
  br i1 %23, label %24, label %40

24:                                               ; preds = %16
  %25 = load %struct.VarScope*, %struct.VarScope** %5, align 8
  %26 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %25, i32 0, i32 0
  %27 = load %struct.Obj*, %struct.Obj** %26, align 8
  %28 = icmp ne %struct.Obj* %27, null
  br i1 %28, label %29, label %40

29:                                               ; preds = %24
  %30 = load %struct.VarScope*, %struct.VarScope** %5, align 8
  %31 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %30, i32 0, i32 0
  %32 = load %struct.Obj*, %struct.Obj** %31, align 8
  %33 = getelementptr inbounds %struct.Obj, %struct.Obj* %32, i32 0, i32 10
  %34 = load i8, i8* %33, align 4
  %35 = trunc i8 %34 to i1
  br i1 %35, label %36, label %40

36:                                               ; preds = %29
  %37 = load %struct.VarScope*, %struct.VarScope** %5, align 8
  %38 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %37, i32 0, i32 0
  %39 = load %struct.Obj*, %struct.Obj** %38, align 8
  store %struct.Obj* %39, %struct.Obj** %2, align 8
  br label %41

40:                                               ; preds = %29, %24, %16
  store %struct.Obj* null, %struct.Obj** %2, align 8
  br label %41

41:                                               ; preds = %40, %36
  %42 = load %struct.Obj*, %struct.Obj** %2, align 8
  ret %struct.Obj* %42
}

declare i8* @hashmap_get(%struct.HashMap* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Obj* @parse(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca %struct.VarAttr, align 4
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.Obj*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %9 = load i8, i8* @isDotfile, align 1
  %10 = trunc i8 %9 to i1
  br i1 %10, label %11, label %58

11:                                               ; preds = %1
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %13 = icmp eq %struct._IO_FILE* %12, null
  br i1 %13, label %14, label %58

14:                                               ; preds = %11
  %15 = load i8*, i8** @base_file, align 8
  %16 = icmp eq i8* %15, null
  br i1 %16, label %17, label %23

17:                                               ; preds = %14
  %18 = load i8*, i8** @opt_o, align 8
  %19 = icmp eq i8* %18, null
  br i1 %19, label %20, label %23

20:                                               ; preds = %17
  %21 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %22 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %21, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.2, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0))
  call void @exit(i32 noundef 5) #10
  unreachable

23:                                               ; preds = %17, %14
  %24 = load i8*, i8** @opt_o, align 8
  %25 = icmp ne i8* %24, null
  br i1 %25, label %26, label %28

26:                                               ; preds = %23
  %27 = load i8*, i8** @opt_o, align 8
  br label %30

28:                                               ; preds = %23
  %29 = load i8*, i8** @base_file, align 8
  br label %30

30:                                               ; preds = %28, %26
  %31 = phi i8* [ %27, %26 ], [ %29, %28 ]
  %32 = call i8* @replace_extn(i8* noundef %31, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0))
  store i8* %32, i8** %3, align 8
  %33 = load i8*, i8** @opt_o, align 8
  %34 = icmp ne i8* %33, null
  br i1 %34, label %35, label %47

35:                                               ; preds = %30
  %36 = load i8*, i8** @opt_o, align 8
  %37 = call i8* @extract_filename(i8* noundef %36)
  store i8* %37, i8** %5, align 8
  %38 = load i8*, i8** @opt_o, align 8
  %39 = load i8*, i8** %5, align 8
  %40 = call i8* @extract_path(i8* noundef %38, i8* noundef %39)
  store i8* %40, i8** %4, align 8
  %41 = load i8*, i8** %4, align 8
  %42 = load i8*, i8** %3, align 8
  %43 = load i8*, i8** %3, align 8
  %44 = call i64 @strlen(i8* noundef %43) #11
  %45 = call i8* @strncat(i8* noundef %41, i8* noundef %42, i64 noundef %44) #8
  %46 = load i8*, i8** %4, align 8
  store i8* %46, i8** %3, align 8
  br label %47

47:                                               ; preds = %35, %30
  %48 = load i8*, i8** %3, align 8
  %49 = call noalias %struct._IO_FILE* @fopen(i8* noundef %48, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0))
  store %struct._IO_FILE* %49, %struct._IO_FILE** @dotf, align 8
  %50 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %51 = icmp eq %struct._IO_FILE* %50, null
  br i1 %51, label %52, label %55

52:                                               ; preds = %47
  %53 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8
  %54 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %53, i8* noundef getelementptr inbounds ([39 x i8], [39 x i8]* @.str.5, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0))
  call void @exit(i32 noundef 4) #10
  unreachable

55:                                               ; preds = %47
  %56 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %57 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %56, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.6, i64 0, i64 0))
  br label %58

58:                                               ; preds = %55, %11, %1
  %59 = load i8, i8* @opt_fbuiltin, align 1
  %60 = trunc i8 %59 to i1
  br i1 %60, label %61, label %62

61:                                               ; preds = %58
  call void @declare_builtin_functions()
  br label %62

62:                                               ; preds = %61, %58
  store %struct.Obj* null, %struct.Obj** @globals, align 8
  br label %63

63:                                               ; preds = %86, %82, %75, %62
  %64 = load %struct.Token*, %struct.Token** %2, align 8
  %65 = getelementptr inbounds %struct.Token, %struct.Token* %64, i32 0, i32 0
  %66 = load i32, i32* %65, align 16
  %67 = icmp ne i32 %66, 6
  br i1 %67, label %68, label %90

68:                                               ; preds = %63
  %69 = bitcast %struct.VarAttr* %6 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 4 %69, i8 0, i64 12, i1 false)
  %70 = load %struct.Token*, %struct.Token** %2, align 8
  %71 = call %struct.Type* @declspec(%struct.Token** noundef %2, %struct.Token* noundef %70, %struct.VarAttr* noundef %6)
  store %struct.Type* %71, %struct.Type** %7, align 8
  %72 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %6, i32 0, i32 0
  %73 = load i8, i8* %72, align 4
  %74 = trunc i8 %73 to i1
  br i1 %74, label %75, label %79

75:                                               ; preds = %68
  %76 = load %struct.Token*, %struct.Token** %2, align 8
  %77 = load %struct.Type*, %struct.Type** %7, align 8
  %78 = call %struct.Token* @parse_typedef(%struct.Token* noundef %76, %struct.Type* noundef %77)
  store %struct.Token* %78, %struct.Token** %2, align 8
  br label %63, !llvm.loop !9

79:                                               ; preds = %68
  %80 = load %struct.Token*, %struct.Token** %2, align 8
  %81 = call zeroext i1 @is_function(%struct.Token* noundef %80)
  br i1 %81, label %82, label %86

82:                                               ; preds = %79
  %83 = load %struct.Token*, %struct.Token** %2, align 8
  %84 = load %struct.Type*, %struct.Type** %7, align 8
  %85 = call %struct.Token* @function(%struct.Token* noundef %83, %struct.Type* noundef %84, %struct.VarAttr* noundef %6)
  store %struct.Token* %85, %struct.Token** %2, align 8
  br label %63, !llvm.loop !9

86:                                               ; preds = %79
  %87 = load %struct.Token*, %struct.Token** %2, align 8
  %88 = load %struct.Type*, %struct.Type** %7, align 8
  %89 = call %struct.Token* @global_variable(%struct.Token* noundef %87, %struct.Type* noundef %88, %struct.VarAttr* noundef %6)
  store %struct.Token* %89, %struct.Token** %2, align 8
  br label %63, !llvm.loop !9

90:                                               ; preds = %63
  %91 = load %struct.Obj*, %struct.Obj** @globals, align 8
  store %struct.Obj* %91, %struct.Obj** %8, align 8
  br label %92

92:                                               ; preds = %103, %90
  %93 = load %struct.Obj*, %struct.Obj** %8, align 8
  %94 = icmp ne %struct.Obj* %93, null
  br i1 %94, label %95, label %107

95:                                               ; preds = %92
  %96 = load %struct.Obj*, %struct.Obj** %8, align 8
  %97 = getelementptr inbounds %struct.Obj, %struct.Obj* %96, i32 0, i32 25
  %98 = load i8, i8* %97, align 1
  %99 = trunc i8 %98 to i1
  br i1 %99, label %100, label %102

100:                                              ; preds = %95
  %101 = load %struct.Obj*, %struct.Obj** %8, align 8
  call void @mark_live(%struct.Obj* noundef %101)
  br label %102

102:                                              ; preds = %100, %95
  br label %103

103:                                              ; preds = %102
  %104 = load %struct.Obj*, %struct.Obj** %8, align 8
  %105 = getelementptr inbounds %struct.Obj, %struct.Obj* %104, i32 0, i32 0
  %106 = load %struct.Obj*, %struct.Obj** %105, align 8
  store %struct.Obj* %106, %struct.Obj** %8, align 8
  br label %92, !llvm.loop !10

107:                                              ; preds = %92
  call void @scan_globals()
  %108 = load %struct.Obj*, %struct.Obj** @globals, align 8
  ret %struct.Obj* %108
}

declare i32 @fprintf(%struct._IO_FILE* noundef, i8* noundef, ...) #1

; Function Attrs: noreturn nounwind
declare void @exit(i32 noundef) #4

declare i8* @replace_extn(i8* noundef, i8* noundef) #1

declare i8* @extract_filename(i8* noundef) #1

declare i8* @extract_path(i8* noundef, i8* noundef) #1

; Function Attrs: nounwind
declare i8* @strncat(i8* noundef, i8* noundef, i64 noundef) #2

; Function Attrs: nounwind readonly willreturn
declare i64 @strlen(i8* noundef) #5

declare noalias %struct._IO_FILE* @fopen(i8* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal void @declare_builtin_functions() #0 {
  %1 = alloca %struct.Type*, align 8
  %2 = load %struct.Type*, %struct.Type** @ty_void, align 8
  %3 = call %struct.Type* @pointer_to(%struct.Type* noundef %2)
  %4 = call %struct.Type* @func_type(%struct.Type* noundef %3)
  store %struct.Type* %4, %struct.Type** %1, align 8
  %5 = load %struct.Type*, %struct.Type** @ty_int, align 8
  %6 = call %struct.Type* @copy_type(%struct.Type* noundef %5)
  %7 = load %struct.Type*, %struct.Type** %1, align 8
  %8 = getelementptr inbounds %struct.Type, %struct.Type* %7, i32 0, i32 18
  store %struct.Type* %6, %struct.Type** %8, align 8
  %9 = load %struct.Type*, %struct.Type** %1, align 8
  %10 = call %struct.Obj* @new_gvar(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.218, i64 0, i64 0), %struct.Type* noundef %9)
  store %struct.Obj* %10, %struct.Obj** @builtin_alloca, align 8
  %11 = load %struct.Obj*, %struct.Obj** @builtin_alloca, align 8
  %12 = getelementptr inbounds %struct.Obj, %struct.Obj* %11, i32 0, i32 11
  store i8 0, i8* %12, align 1
  ret void
}

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #6

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @declspec(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.VarAttr* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.VarAttr*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca i32, align 4
  %9 = alloca i8, align 1
  %10 = alloca %struct.Type*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.VarAttr* %2, %struct.VarAttr** %6, align 8
  %11 = load %struct.Type*, %struct.Type** @ty_int, align 8
  store %struct.Type* %11, %struct.Type** %7, align 8
  store i32 0, i32* %8, align 4
  store i8 0, i8* %9, align 1
  br label %12

12:                                               ; preds = %344, %241, %177, %148, %131, %100, %3
  %13 = load %struct.Token*, %struct.Token** %5, align 8
  %14 = call zeroext i1 @is_typename(%struct.Token* noundef %13)
  br i1 %14, label %15, label %348

15:                                               ; preds = %12
  %16 = load %struct.Token*, %struct.Token** %5, align 8
  %17 = call zeroext i1 @equal(%struct.Token* noundef %16, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.96, i64 0, i64 0))
  br i1 %17, label %33, label %18

18:                                               ; preds = %15
  %19 = load %struct.Token*, %struct.Token** %5, align 8
  %20 = call zeroext i1 @equal(%struct.Token* noundef %19, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.98, i64 0, i64 0))
  br i1 %20, label %33, label %21

21:                                               ; preds = %18
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.99, i64 0, i64 0))
  br i1 %23, label %33, label %24

24:                                               ; preds = %21
  %25 = load %struct.Token*, %struct.Token** %5, align 8
  %26 = call zeroext i1 @equal(%struct.Token* noundef %25, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.114, i64 0, i64 0))
  br i1 %26, label %33, label %27

27:                                               ; preds = %24
  %28 = load %struct.Token*, %struct.Token** %5, align 8
  %29 = call zeroext i1 @equal(%struct.Token* noundef %28, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.115, i64 0, i64 0))
  br i1 %29, label %33, label %30

30:                                               ; preds = %27
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = call zeroext i1 @equal(%struct.Token* noundef %31, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.116, i64 0, i64 0))
  br i1 %32, label %33, label %104

33:                                               ; preds = %30, %27, %24, %21, %18, %15
  %34 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %35 = icmp ne %struct.VarAttr* %34, null
  br i1 %35, label %38, label %36

36:                                               ; preds = %33
  %37 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %37, i8* noundef getelementptr inbounds ([74 x i8], [74 x i8]* @.str.219, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

38:                                               ; preds = %33
  %39 = load %struct.Token*, %struct.Token** %5, align 8
  %40 = call zeroext i1 @equal(%struct.Token* noundef %39, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.96, i64 0, i64 0))
  br i1 %40, label %41, label %44

41:                                               ; preds = %38
  %42 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %43 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %42, i32 0, i32 0
  store i8 1, i8* %43, align 4
  br label %68

44:                                               ; preds = %38
  %45 = load %struct.Token*, %struct.Token** %5, align 8
  %46 = call zeroext i1 @equal(%struct.Token* noundef %45, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.98, i64 0, i64 0))
  br i1 %46, label %47, label %50

47:                                               ; preds = %44
  %48 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %49 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %48, i32 0, i32 1
  store i8 1, i8* %49, align 1
  br label %67

50:                                               ; preds = %44
  %51 = load %struct.Token*, %struct.Token** %5, align 8
  %52 = call zeroext i1 @equal(%struct.Token* noundef %51, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.99, i64 0, i64 0))
  br i1 %52, label %53, label %56

53:                                               ; preds = %50
  %54 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %55 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %54, i32 0, i32 2
  store i8 1, i8* %55, align 2
  br label %66

56:                                               ; preds = %50
  %57 = load %struct.Token*, %struct.Token** %5, align 8
  %58 = call zeroext i1 @equal(%struct.Token* noundef %57, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.114, i64 0, i64 0))
  br i1 %58, label %59, label %62

59:                                               ; preds = %56
  %60 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %61 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %60, i32 0, i32 3
  store i8 1, i8* %61, align 1
  br label %65

62:                                               ; preds = %56
  %63 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %64 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %63, i32 0, i32 4
  store i8 1, i8* %64, align 4
  br label %65

65:                                               ; preds = %62, %59
  br label %66

66:                                               ; preds = %65, %53
  br label %67

67:                                               ; preds = %66, %47
  br label %68

68:                                               ; preds = %67, %41
  %69 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %70 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %69, i32 0, i32 0
  %71 = load i8, i8* %70, align 4
  %72 = trunc i8 %71 to i1
  br i1 %72, label %73, label %100

73:                                               ; preds = %68
  %74 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %75 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %74, i32 0, i32 1
  %76 = load i8, i8* %75, align 1
  %77 = trunc i8 %76 to i1
  %78 = zext i1 %77 to i32
  %79 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %80 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %79, i32 0, i32 2
  %81 = load i8, i8* %80, align 2
  %82 = trunc i8 %81 to i1
  %83 = zext i1 %82 to i32
  %84 = add nsw i32 %78, %83
  %85 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %86 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %85, i32 0, i32 3
  %87 = load i8, i8* %86, align 1
  %88 = trunc i8 %87 to i1
  %89 = zext i1 %88 to i32
  %90 = add nsw i32 %84, %89
  %91 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %92 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %91, i32 0, i32 4
  %93 = load i8, i8* %92, align 4
  %94 = trunc i8 %93 to i1
  %95 = zext i1 %94 to i32
  %96 = add nsw i32 %90, %95
  %97 = icmp sgt i32 %96, 1
  br i1 %97, label %98, label %100

98:                                               ; preds = %73
  %99 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %99, i8* noundef getelementptr inbounds ([106 x i8], [106 x i8]* @.str.220, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

100:                                              ; preds = %73, %68
  %101 = load %struct.Token*, %struct.Token** %5, align 8
  %102 = getelementptr inbounds %struct.Token, %struct.Token* %101, i32 0, i32 1
  %103 = load %struct.Token*, %struct.Token** %102, align 8
  store %struct.Token* %103, %struct.Token** %5, align 8
  br label %12, !llvm.loop !11

104:                                              ; preds = %30
  %105 = load %struct.Token*, %struct.Token** %5, align 8
  %106 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %105, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.103, i64 0, i64 0))
  br i1 %106, label %131, label %107

107:                                              ; preds = %104
  %108 = load %struct.Token*, %struct.Token** %5, align 8
  %109 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %108, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.104, i64 0, i64 0))
  br i1 %109, label %131, label %110

110:                                              ; preds = %107
  %111 = load %struct.Token*, %struct.Token** %5, align 8
  %112 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %111, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.105, i64 0, i64 0))
  br i1 %112, label %131, label %113

113:                                              ; preds = %110
  %114 = load %struct.Token*, %struct.Token** %5, align 8
  %115 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %114, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.106, i64 0, i64 0))
  br i1 %115, label %131, label %116

116:                                              ; preds = %113
  %117 = load %struct.Token*, %struct.Token** %5, align 8
  %118 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %117, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.118, i64 0, i64 0))
  br i1 %118, label %131, label %119

119:                                              ; preds = %116
  %120 = load %struct.Token*, %struct.Token** %5, align 8
  %121 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %120, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.107, i64 0, i64 0))
  br i1 %121, label %131, label %122

122:                                              ; preds = %119
  %123 = load %struct.Token*, %struct.Token** %5, align 8
  %124 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %123, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.108, i64 0, i64 0))
  br i1 %124, label %131, label %125

125:                                              ; preds = %122
  %126 = load %struct.Token*, %struct.Token** %5, align 8
  %127 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %126, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.109, i64 0, i64 0))
  br i1 %127, label %131, label %128

128:                                              ; preds = %125
  %129 = load %struct.Token*, %struct.Token** %5, align 8
  %130 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %129, i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.110, i64 0, i64 0))
  br i1 %130, label %131, label %132

131:                                              ; preds = %128, %125, %122, %119, %116, %113, %110, %107, %104
  br label %12, !llvm.loop !11

132:                                              ; preds = %128
  %133 = load %struct.Token*, %struct.Token** %5, align 8
  %134 = call zeroext i1 @equal(%struct.Token* noundef %133, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.117, i64 0, i64 0))
  br i1 %134, label %135, label %149

135:                                              ; preds = %132
  %136 = load %struct.Token*, %struct.Token** %5, align 8
  %137 = getelementptr inbounds %struct.Token, %struct.Token* %136, i32 0, i32 1
  %138 = load %struct.Token*, %struct.Token** %137, align 8
  store %struct.Token* %138, %struct.Token** %5, align 8
  %139 = load %struct.Token*, %struct.Token** %5, align 8
  %140 = call zeroext i1 @equal(%struct.Token* noundef %139, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %140, label %141, label %148

141:                                              ; preds = %135
  %142 = load %struct.Token*, %struct.Token** %5, align 8
  %143 = getelementptr inbounds %struct.Token, %struct.Token* %142, i32 0, i32 1
  %144 = load %struct.Token*, %struct.Token** %143, align 8
  %145 = call %struct.Type* @typename(%struct.Token** noundef %5, %struct.Token* noundef %144)
  store %struct.Type* %145, %struct.Type** %7, align 8
  %146 = load %struct.Token*, %struct.Token** %5, align 8
  %147 = call %struct.Token* @skip(%struct.Token* noundef %146, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %147, %struct.Token** %5, align 8
  br label %148

148:                                              ; preds = %141, %135
  store i8 1, i8* %9, align 1
  br label %12, !llvm.loop !11

149:                                              ; preds = %132
  %150 = load %struct.Token*, %struct.Token** %5, align 8
  %151 = call zeroext i1 @equal(%struct.Token* noundef %150, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.100, i64 0, i64 0))
  br i1 %151, label %152, label %180

152:                                              ; preds = %149
  %153 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %154 = icmp ne %struct.VarAttr* %153, null
  br i1 %154, label %157, label %155

155:                                              ; preds = %152
  %156 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %156, i8* noundef getelementptr inbounds ([58 x i8], [58 x i8]* @.str.221, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

157:                                              ; preds = %152
  %158 = load %struct.Token*, %struct.Token** %5, align 8
  %159 = getelementptr inbounds %struct.Token, %struct.Token* %158, i32 0, i32 1
  %160 = load %struct.Token*, %struct.Token** %159, align 8
  %161 = call %struct.Token* @skip(%struct.Token* noundef %160, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %161, %struct.Token** %5, align 8
  %162 = load %struct.Token*, %struct.Token** %5, align 8
  %163 = call zeroext i1 @is_typename(%struct.Token* noundef %162)
  br i1 %163, label %164, label %171

164:                                              ; preds = %157
  %165 = load %struct.Token*, %struct.Token** %5, align 8
  %166 = call %struct.Type* @typename(%struct.Token** noundef %5, %struct.Token* noundef %165)
  %167 = getelementptr inbounds %struct.Type, %struct.Type* %166, i32 0, i32 2
  %168 = load i32, i32* %167, align 8
  %169 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %170 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %169, i32 0, i32 5
  store i32 %168, i32* %170, align 4
  br label %177

171:                                              ; preds = %157
  %172 = load %struct.Token*, %struct.Token** %5, align 8
  %173 = call i64 @const_expr(%struct.Token** noundef %5, %struct.Token* noundef %172)
  %174 = trunc i64 %173 to i32
  %175 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %176 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %175, i32 0, i32 5
  store i32 %174, i32* %176, align 4
  br label %177

177:                                              ; preds = %171, %164
  %178 = load %struct.Token*, %struct.Token** %5, align 8
  %179 = call %struct.Token* @skip(%struct.Token* noundef %178, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %179, %struct.Token** %5, align 8
  br label %12, !llvm.loop !11

180:                                              ; preds = %149
  %181 = load %struct.Token*, %struct.Token** %5, align 8
  %182 = call %struct.Type* @find_typedef(%struct.Token* noundef %181)
  store %struct.Type* %182, %struct.Type** %10, align 8
  %183 = load %struct.Token*, %struct.Token** %5, align 8
  %184 = call zeroext i1 @equal(%struct.Token* noundef %183, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.94, i64 0, i64 0))
  br i1 %184, label %197, label %185

185:                                              ; preds = %180
  %186 = load %struct.Token*, %struct.Token** %5, align 8
  %187 = call zeroext i1 @equal(%struct.Token* noundef %186, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.95, i64 0, i64 0))
  br i1 %187, label %197, label %188

188:                                              ; preds = %185
  %189 = load %struct.Token*, %struct.Token** %5, align 8
  %190 = call zeroext i1 @equal(%struct.Token* noundef %189, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.97, i64 0, i64 0))
  br i1 %190, label %197, label %191

191:                                              ; preds = %188
  %192 = load %struct.Token*, %struct.Token** %5, align 8
  %193 = call zeroext i1 @equal(%struct.Token* noundef %192, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.113, i64 0, i64 0))
  br i1 %193, label %197, label %194

194:                                              ; preds = %191
  %195 = load %struct.Type*, %struct.Type** %10, align 8
  %196 = icmp ne %struct.Type* %195, null
  br i1 %196, label %197, label %244

197:                                              ; preds = %194, %191, %188, %185, %180
  %198 = load i32, i32* %8, align 4
  %199 = icmp ne i32 %198, 0
  br i1 %199, label %200, label %201

200:                                              ; preds = %197
  br label %348

201:                                              ; preds = %197
  %202 = load %struct.Token*, %struct.Token** %5, align 8
  %203 = call zeroext i1 @equal(%struct.Token* noundef %202, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.94, i64 0, i64 0))
  br i1 %203, label %204, label %209

204:                                              ; preds = %201
  %205 = load %struct.Token*, %struct.Token** %5, align 8
  %206 = getelementptr inbounds %struct.Token, %struct.Token* %205, i32 0, i32 1
  %207 = load %struct.Token*, %struct.Token** %206, align 8
  %208 = call %struct.Type* @struct_decl(%struct.Token** noundef %5, %struct.Token* noundef %207)
  store %struct.Type* %208, %struct.Type** %7, align 8
  br label %241

209:                                              ; preds = %201
  %210 = load %struct.Token*, %struct.Token** %5, align 8
  %211 = call zeroext i1 @equal(%struct.Token* noundef %210, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.95, i64 0, i64 0))
  br i1 %211, label %212, label %217

212:                                              ; preds = %209
  %213 = load %struct.Token*, %struct.Token** %5, align 8
  %214 = getelementptr inbounds %struct.Token, %struct.Token* %213, i32 0, i32 1
  %215 = load %struct.Token*, %struct.Token** %214, align 8
  %216 = call %struct.Type* @union_decl(%struct.Token** noundef %5, %struct.Token* noundef %215)
  store %struct.Type* %216, %struct.Type** %7, align 8
  br label %240

217:                                              ; preds = %209
  %218 = load %struct.Token*, %struct.Token** %5, align 8
  %219 = call zeroext i1 @equal(%struct.Token* noundef %218, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.97, i64 0, i64 0))
  br i1 %219, label %220, label %225

220:                                              ; preds = %217
  %221 = load %struct.Token*, %struct.Token** %5, align 8
  %222 = getelementptr inbounds %struct.Token, %struct.Token* %221, i32 0, i32 1
  %223 = load %struct.Token*, %struct.Token** %222, align 8
  %224 = call %struct.Type* @enum_specifier(%struct.Token** noundef %5, %struct.Token* noundef %223)
  store %struct.Type* %224, %struct.Type** %7, align 8
  br label %239

225:                                              ; preds = %217
  %226 = load %struct.Token*, %struct.Token** %5, align 8
  %227 = call zeroext i1 @equal(%struct.Token* noundef %226, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.113, i64 0, i64 0))
  br i1 %227, label %228, label %233

228:                                              ; preds = %225
  %229 = load %struct.Token*, %struct.Token** %5, align 8
  %230 = getelementptr inbounds %struct.Token, %struct.Token* %229, i32 0, i32 1
  %231 = load %struct.Token*, %struct.Token** %230, align 8
  %232 = call %struct.Type* @typeof_specifier(%struct.Token** noundef %5, %struct.Token* noundef %231)
  store %struct.Type* %232, %struct.Type** %7, align 8
  br label %238

233:                                              ; preds = %225
  %234 = load %struct.Type*, %struct.Type** %10, align 8
  store %struct.Type* %234, %struct.Type** %7, align 8
  %235 = load %struct.Token*, %struct.Token** %5, align 8
  %236 = getelementptr inbounds %struct.Token, %struct.Token* %235, i32 0, i32 1
  %237 = load %struct.Token*, %struct.Token** %236, align 8
  store %struct.Token* %237, %struct.Token** %5, align 8
  br label %238

238:                                              ; preds = %233, %228
  br label %239

239:                                              ; preds = %238, %220
  br label %240

240:                                              ; preds = %239, %212
  br label %241

241:                                              ; preds = %240, %204
  %242 = load i32, i32* %8, align 4
  %243 = add nsw i32 %242, 65536
  store i32 %243, i32* %8, align 4
  br label %12, !llvm.loop !11

244:                                              ; preds = %194
  %245 = load %struct.Token*, %struct.Token** %5, align 8
  %246 = call zeroext i1 @equal(%struct.Token* noundef %245, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.88, i64 0, i64 0))
  br i1 %246, label %247, label %250

247:                                              ; preds = %244
  %248 = load i32, i32* %8, align 4
  %249 = add nsw i32 %248, 1
  store i32 %249, i32* %8, align 4
  br label %314

250:                                              ; preds = %244
  %251 = load %struct.Token*, %struct.Token** %5, align 8
  %252 = call zeroext i1 @equal(%struct.Token* noundef %251, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.89, i64 0, i64 0))
  br i1 %252, label %253, label %256

253:                                              ; preds = %250
  %254 = load i32, i32* %8, align 4
  %255 = add nsw i32 %254, 4
  store i32 %255, i32* %8, align 4
  br label %313

256:                                              ; preds = %250
  %257 = load %struct.Token*, %struct.Token** %5, align 8
  %258 = call zeroext i1 @equal(%struct.Token* noundef %257, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.90, i64 0, i64 0))
  br i1 %258, label %259, label %262

259:                                              ; preds = %256
  %260 = load i32, i32* %8, align 4
  %261 = add nsw i32 %260, 16
  store i32 %261, i32* %8, align 4
  br label %312

262:                                              ; preds = %256
  %263 = load %struct.Token*, %struct.Token** %5, align 8
  %264 = call zeroext i1 @equal(%struct.Token* noundef %263, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.91, i64 0, i64 0))
  br i1 %264, label %265, label %268

265:                                              ; preds = %262
  %266 = load i32, i32* %8, align 4
  %267 = add nsw i32 %266, 64
  store i32 %267, i32* %8, align 4
  br label %311

268:                                              ; preds = %262
  %269 = load %struct.Token*, %struct.Token** %5, align 8
  %270 = call zeroext i1 @equal(%struct.Token* noundef %269, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.92, i64 0, i64 0))
  br i1 %270, label %271, label %274

271:                                              ; preds = %268
  %272 = load i32, i32* %8, align 4
  %273 = add nsw i32 %272, 256
  store i32 %273, i32* %8, align 4
  br label %310

274:                                              ; preds = %268
  %275 = load %struct.Token*, %struct.Token** %5, align 8
  %276 = call zeroext i1 @equal(%struct.Token* noundef %275, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.93, i64 0, i64 0))
  br i1 %276, label %277, label %280

277:                                              ; preds = %274
  %278 = load i32, i32* %8, align 4
  %279 = add nsw i32 %278, 1024
  store i32 %279, i32* %8, align 4
  br label %309

280:                                              ; preds = %274
  %281 = load %struct.Token*, %struct.Token** %5, align 8
  %282 = call zeroext i1 @equal(%struct.Token* noundef %281, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.111, i64 0, i64 0))
  br i1 %282, label %283, label %286

283:                                              ; preds = %280
  %284 = load i32, i32* %8, align 4
  %285 = add nsw i32 %284, 4096
  store i32 %285, i32* %8, align 4
  br label %308

286:                                              ; preds = %280
  %287 = load %struct.Token*, %struct.Token** %5, align 8
  %288 = call zeroext i1 @equal(%struct.Token* noundef %287, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.112, i64 0, i64 0))
  br i1 %288, label %289, label %292

289:                                              ; preds = %286
  %290 = load i32, i32* %8, align 4
  %291 = add nsw i32 %290, 16384
  store i32 %291, i32* %8, align 4
  br label %307

292:                                              ; preds = %286
  %293 = load %struct.Token*, %struct.Token** %5, align 8
  %294 = call zeroext i1 @equal(%struct.Token* noundef %293, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.101, i64 0, i64 0))
  br i1 %294, label %295, label %298

295:                                              ; preds = %292
  %296 = load i32, i32* %8, align 4
  %297 = or i32 %296, 131072
  store i32 %297, i32* %8, align 4
  br label %306

298:                                              ; preds = %292
  %299 = load %struct.Token*, %struct.Token** %5, align 8
  %300 = call zeroext i1 @equal(%struct.Token* noundef %299, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.102, i64 0, i64 0))
  br i1 %300, label %301, label %304

301:                                              ; preds = %298
  %302 = load i32, i32* %8, align 4
  %303 = or i32 %302, 262144
  store i32 %303, i32* %8, align 4
  br label %305

304:                                              ; preds = %298
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.165, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 noundef 598) #9
  unreachable

305:                                              ; preds = %301
  br label %306

306:                                              ; preds = %305, %295
  br label %307

307:                                              ; preds = %306, %289
  br label %308

308:                                              ; preds = %307, %283
  br label %309

309:                                              ; preds = %308, %277
  br label %310

310:                                              ; preds = %309, %271
  br label %311

311:                                              ; preds = %310, %265
  br label %312

312:                                              ; preds = %311, %259
  br label %313

313:                                              ; preds = %312, %253
  br label %314

314:                                              ; preds = %313, %247
  %315 = load i32, i32* %8, align 4
  switch i32 %315, label %342 [
    i32 1, label %316
    i32 4, label %318
    i32 16, label %320
    i32 131088, label %320
    i32 262160, label %322
    i32 64, label %324
    i32 320, label %324
    i32 131136, label %324
    i32 131392, label %324
    i32 262208, label %326
    i32 262464, label %326
    i32 256, label %328
    i32 131072, label %328
    i32 131328, label %328
    i32 262144, label %330
    i32 262400, label %330
    i32 1024, label %332
    i32 1280, label %332
    i32 2048, label %332
    i32 2304, label %332
    i32 132096, label %332
    i32 132352, label %332
    i32 133120, label %332
    i32 133376, label %332
    i32 263168, label %334
    i32 263424, label %334
    i32 264192, label %334
    i32 264448, label %334
    i32 4096, label %336
    i32 16384, label %338
    i32 17408, label %340
  ]

316:                                              ; preds = %314
  %317 = load %struct.Type*, %struct.Type** @ty_void, align 8
  store %struct.Type* %317, %struct.Type** %7, align 8
  br label %344

318:                                              ; preds = %314
  %319 = load %struct.Type*, %struct.Type** @ty_bool, align 8
  store %struct.Type* %319, %struct.Type** %7, align 8
  br label %344

320:                                              ; preds = %314, %314
  %321 = load %struct.Type*, %struct.Type** @ty_char, align 8
  store %struct.Type* %321, %struct.Type** %7, align 8
  br label %344

322:                                              ; preds = %314
  %323 = load %struct.Type*, %struct.Type** @ty_uchar, align 8
  store %struct.Type* %323, %struct.Type** %7, align 8
  br label %344

324:                                              ; preds = %314, %314, %314, %314
  %325 = load %struct.Type*, %struct.Type** @ty_short, align 8
  store %struct.Type* %325, %struct.Type** %7, align 8
  br label %344

326:                                              ; preds = %314, %314
  %327 = load %struct.Type*, %struct.Type** @ty_ushort, align 8
  store %struct.Type* %327, %struct.Type** %7, align 8
  br label %344

328:                                              ; preds = %314, %314, %314
  %329 = load %struct.Type*, %struct.Type** @ty_int, align 8
  store %struct.Type* %329, %struct.Type** %7, align 8
  br label %344

330:                                              ; preds = %314, %314
  %331 = load %struct.Type*, %struct.Type** @ty_uint, align 8
  store %struct.Type* %331, %struct.Type** %7, align 8
  br label %344

332:                                              ; preds = %314, %314, %314, %314, %314, %314, %314, %314
  %333 = load %struct.Type*, %struct.Type** @ty_long, align 8
  store %struct.Type* %333, %struct.Type** %7, align 8
  br label %344

334:                                              ; preds = %314, %314, %314, %314
  %335 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  store %struct.Type* %335, %struct.Type** %7, align 8
  br label %344

336:                                              ; preds = %314
  %337 = load %struct.Type*, %struct.Type** @ty_float, align 8
  store %struct.Type* %337, %struct.Type** %7, align 8
  br label %344

338:                                              ; preds = %314
  %339 = load %struct.Type*, %struct.Type** @ty_double, align 8
  store %struct.Type* %339, %struct.Type** %7, align 8
  br label %344

340:                                              ; preds = %314
  %341 = load %struct.Type*, %struct.Type** @ty_ldouble, align 8
  store %struct.Type* %341, %struct.Type** %7, align 8
  br label %344

342:                                              ; preds = %314
  %343 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %343, i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.222, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

344:                                              ; preds = %340, %338, %336, %334, %332, %330, %328, %326, %324, %322, %320, %318, %316
  %345 = load %struct.Token*, %struct.Token** %5, align 8
  %346 = getelementptr inbounds %struct.Token, %struct.Token* %345, i32 0, i32 1
  %347 = load %struct.Token*, %struct.Token** %346, align 8
  store %struct.Token* %347, %struct.Token** %5, align 8
  br label %12, !llvm.loop !11

348:                                              ; preds = %200, %12
  %349 = load i8, i8* %9, align 1
  %350 = trunc i8 %349 to i1
  br i1 %350, label %351, label %356

351:                                              ; preds = %348
  %352 = load %struct.Type*, %struct.Type** %7, align 8
  %353 = call %struct.Type* @copy_type(%struct.Type* noundef %352)
  store %struct.Type* %353, %struct.Type** %7, align 8
  %354 = load %struct.Type*, %struct.Type** %7, align 8
  %355 = getelementptr inbounds %struct.Type, %struct.Type* %354, i32 0, i32 4
  store i8 1, i8* %355, align 1
  br label %356

356:                                              ; preds = %351, %348
  %357 = load %struct.Token*, %struct.Token** %5, align 8
  %358 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %357, %struct.Token** %358, align 8
  %359 = load %struct.Type*, %struct.Type** %7, align 8
  ret %struct.Type* %359
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @parse_typedef(%struct.Token* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca i8, align 1
  %6 = alloca %struct.Type*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  store i8 1, i8* %5, align 1
  br label %7

7:                                                ; preds = %29, %2
  %8 = load %struct.Token*, %struct.Token** %3, align 8
  %9 = call zeroext i1 @consume(%struct.Token** noundef %3, %struct.Token* noundef %8, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %10 = xor i1 %9, true
  br i1 %10, label %11, label %37

11:                                               ; preds = %7
  %12 = load i8, i8* %5, align 1
  %13 = trunc i8 %12 to i1
  br i1 %13, label %17, label %14

14:                                               ; preds = %11
  %15 = load %struct.Token*, %struct.Token** %3, align 8
  %16 = call %struct.Token* @skip(%struct.Token* noundef %15, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %16, %struct.Token** %3, align 8
  br label %17

17:                                               ; preds = %14, %11
  store i8 0, i8* %5, align 1
  %18 = load %struct.Token*, %struct.Token** %3, align 8
  %19 = load %struct.Type*, %struct.Type** %4, align 8
  %20 = call %struct.Type* @declarator(%struct.Token** noundef %3, %struct.Token* noundef %18, %struct.Type* noundef %19)
  store %struct.Type* %20, %struct.Type** %6, align 8
  %21 = load %struct.Type*, %struct.Type** %6, align 8
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 9
  %23 = load %struct.Token*, %struct.Token** %22, align 8
  %24 = icmp ne %struct.Token* %23, null
  br i1 %24, label %29, label %25

25:                                               ; preds = %17
  %26 = load %struct.Type*, %struct.Type** %6, align 8
  %27 = getelementptr inbounds %struct.Type, %struct.Type* %26, i32 0, i32 10
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %28, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.232, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

29:                                               ; preds = %17
  %30 = load %struct.Type*, %struct.Type** %6, align 8
  %31 = load %struct.Type*, %struct.Type** %6, align 8
  %32 = getelementptr inbounds %struct.Type, %struct.Type* %31, i32 0, i32 9
  %33 = load %struct.Token*, %struct.Token** %32, align 8
  %34 = call i8* @get_ident(%struct.Token* noundef %33)
  %35 = call %struct.VarScope* @push_scope(i8* noundef %34)
  %36 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %35, i32 0, i32 1
  store %struct.Type* %30, %struct.Type** %36, align 8
  br label %7, !llvm.loop !12

37:                                               ; preds = %7
  %38 = load %struct.Token*, %struct.Token** %3, align 8
  ret %struct.Token* %38
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @is_function(%struct.Token* noundef %0) #0 {
  %2 = alloca i1, align 1
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Type, align 8
  %5 = alloca %struct.Type*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %6 = load %struct.Token*, %struct.Token** %3, align 8
  %7 = call zeroext i1 @equal(%struct.Token* noundef %6, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  br i1 %7, label %8, label %9

8:                                                ; preds = %1
  store i1 false, i1* %2, align 1
  br label %17

9:                                                ; preds = %1
  %10 = bitcast %struct.Type* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %10, i8 0, i64 128, i1 false)
  %11 = load %struct.Token*, %struct.Token** %3, align 8
  %12 = call %struct.Type* @declarator(%struct.Token** noundef %3, %struct.Token* noundef %11, %struct.Type* noundef %4)
  store %struct.Type* %12, %struct.Type** %5, align 8
  %13 = load %struct.Type*, %struct.Type** %5, align 8
  %14 = getelementptr inbounds %struct.Type, %struct.Type* %13, i32 0, i32 0
  %15 = load i32, i32* %14, align 8
  %16 = icmp eq i32 %15, 11
  store i1 %16, i1* %2, align 1
  br label %17

17:                                               ; preds = %9, %8
  %18 = load i1, i1* %2, align 1
  ret i1 %18
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @function(%struct.Token* noundef %0, %struct.Type* noundef %1, %struct.VarAttr* noundef %2) #0 {
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.VarAttr*, align 8
  %8 = alloca %struct.Type*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca %struct.Obj*, align 8
  %11 = alloca %struct.Type*, align 8
  store %struct.Token* %0, %struct.Token** %5, align 8
  store %struct.Type* %1, %struct.Type** %6, align 8
  store %struct.VarAttr* %2, %struct.VarAttr** %7, align 8
  %12 = load %struct.Token*, %struct.Token** %5, align 8
  %13 = load %struct.Type*, %struct.Type** %6, align 8
  %14 = call %struct.Type* @declarator(%struct.Token** noundef %5, %struct.Token* noundef %12, %struct.Type* noundef %13)
  store %struct.Type* %14, %struct.Type** %8, align 8
  %15 = load %struct.Type*, %struct.Type** %8, align 8
  %16 = getelementptr inbounds %struct.Type, %struct.Type* %15, i32 0, i32 9
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = icmp ne %struct.Token* %17, null
  br i1 %18, label %23, label %19

19:                                               ; preds = %3
  %20 = load %struct.Type*, %struct.Type** %8, align 8
  %21 = getelementptr inbounds %struct.Type, %struct.Type* %20, i32 0, i32 10
  %22 = load %struct.Token*, %struct.Token** %21, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.233, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

23:                                               ; preds = %3
  %24 = load %struct.Type*, %struct.Type** %8, align 8
  %25 = getelementptr inbounds %struct.Type, %struct.Type* %24, i32 0, i32 9
  %26 = load %struct.Token*, %struct.Token** %25, align 8
  %27 = call i8* @get_ident(%struct.Token* noundef %26)
  store i8* %27, i8** %9, align 8
  %28 = load i8*, i8** %9, align 8
  %29 = call %struct.Obj* @find_func(i8* noundef %28)
  store %struct.Obj* %29, %struct.Obj** %10, align 8
  %30 = load %struct.Obj*, %struct.Obj** %10, align 8
  %31 = icmp ne %struct.Obj* %30, null
  br i1 %31, label %32, label %75

32:                                               ; preds = %23
  %33 = load %struct.Obj*, %struct.Obj** %10, align 8
  %34 = getelementptr inbounds %struct.Obj, %struct.Obj* %33, i32 0, i32 10
  %35 = load i8, i8* %34, align 4
  %36 = trunc i8 %35 to i1
  br i1 %36, label %39, label %37

37:                                               ; preds = %32
  %38 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %38, i8* noundef getelementptr inbounds ([59 x i8], [59 x i8]* @.str.234, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

39:                                               ; preds = %32
  %40 = load %struct.Obj*, %struct.Obj** %10, align 8
  %41 = getelementptr inbounds %struct.Obj, %struct.Obj* %40, i32 0, i32 11
  %42 = load i8, i8* %41, align 1
  %43 = trunc i8 %42 to i1
  br i1 %43, label %44, label %50

44:                                               ; preds = %39
  %45 = load %struct.Token*, %struct.Token** %5, align 8
  %46 = call zeroext i1 @equal(%struct.Token* noundef %45, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %46, label %47, label %50

47:                                               ; preds = %44
  %48 = load %struct.Token*, %struct.Token** %5, align 8
  %49 = load i8*, i8** %9, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %48, i8* noundef getelementptr inbounds ([37 x i8], [37 x i8]* @.str.235, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i8* noundef %49) #9
  unreachable

50:                                               ; preds = %44, %39
  %51 = load %struct.Obj*, %struct.Obj** %10, align 8
  %52 = getelementptr inbounds %struct.Obj, %struct.Obj* %51, i32 0, i32 12
  %53 = load i8, i8* %52, align 2
  %54 = trunc i8 %53 to i1
  br i1 %54, label %62, label %55

55:                                               ; preds = %50
  %56 = load %struct.VarAttr*, %struct.VarAttr** %7, align 8
  %57 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %56, i32 0, i32 1
  %58 = load i8, i8* %57, align 1
  %59 = trunc i8 %58 to i1
  br i1 %59, label %60, label %62

60:                                               ; preds = %55
  %61 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %61, i8* noundef getelementptr inbounds ([70 x i8], [70 x i8]* @.str.236, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

62:                                               ; preds = %55, %50
  %63 = load %struct.Obj*, %struct.Obj** %10, align 8
  %64 = getelementptr inbounds %struct.Obj, %struct.Obj* %63, i32 0, i32 11
  %65 = load i8, i8* %64, align 1
  %66 = trunc i8 %65 to i1
  br i1 %66, label %70, label %67

67:                                               ; preds = %62
  %68 = load %struct.Token*, %struct.Token** %5, align 8
  %69 = call zeroext i1 @equal(%struct.Token* noundef %68, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br label %70

70:                                               ; preds = %67, %62
  %71 = phi i1 [ true, %62 ], [ %69, %67 ]
  %72 = load %struct.Obj*, %struct.Obj** %10, align 8
  %73 = getelementptr inbounds %struct.Obj, %struct.Obj* %72, i32 0, i32 11
  %74 = zext i1 %71 to i8
  store i8 %74, i8* %73, align 1
  br label %115

75:                                               ; preds = %23
  %76 = load i8*, i8** %9, align 8
  %77 = load %struct.Type*, %struct.Type** %8, align 8
  %78 = call %struct.Obj* @new_gvar(i8* noundef %76, %struct.Type* noundef %77)
  store %struct.Obj* %78, %struct.Obj** %10, align 8
  %79 = load %struct.Obj*, %struct.Obj** %10, align 8
  %80 = getelementptr inbounds %struct.Obj, %struct.Obj* %79, i32 0, i32 10
  store i8 1, i8* %80, align 4
  %81 = load %struct.Token*, %struct.Token** %5, align 8
  %82 = call zeroext i1 @equal(%struct.Token* noundef %81, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  %83 = load %struct.Obj*, %struct.Obj** %10, align 8
  %84 = getelementptr inbounds %struct.Obj, %struct.Obj* %83, i32 0, i32 11
  %85 = zext i1 %82 to i8
  store i8 %85, i8* %84, align 1
  %86 = load %struct.VarAttr*, %struct.VarAttr** %7, align 8
  %87 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %86, i32 0, i32 1
  %88 = load i8, i8* %87, align 1
  %89 = trunc i8 %88 to i1
  br i1 %89, label %103, label %90

90:                                               ; preds = %75
  %91 = load %struct.VarAttr*, %struct.VarAttr** %7, align 8
  %92 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %91, i32 0, i32 3
  %93 = load i8, i8* %92, align 1
  %94 = trunc i8 %93 to i1
  br i1 %94, label %95, label %101

95:                                               ; preds = %90
  %96 = load %struct.VarAttr*, %struct.VarAttr** %7, align 8
  %97 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %96, i32 0, i32 2
  %98 = load i8, i8* %97, align 2
  %99 = trunc i8 %98 to i1
  %100 = xor i1 %99, true
  br label %101

101:                                              ; preds = %95, %90
  %102 = phi i1 [ false, %90 ], [ %100, %95 ]
  br label %103

103:                                              ; preds = %101, %75
  %104 = phi i1 [ true, %75 ], [ %102, %101 ]
  %105 = load %struct.Obj*, %struct.Obj** %10, align 8
  %106 = getelementptr inbounds %struct.Obj, %struct.Obj* %105, i32 0, i32 12
  %107 = zext i1 %104 to i8
  store i8 %107, i8* %106, align 2
  %108 = load %struct.VarAttr*, %struct.VarAttr** %7, align 8
  %109 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %108, i32 0, i32 3
  %110 = load i8, i8* %109, align 1
  %111 = trunc i8 %110 to i1
  %112 = load %struct.Obj*, %struct.Obj** %10, align 8
  %113 = getelementptr inbounds %struct.Obj, %struct.Obj* %112, i32 0, i32 17
  %114 = zext i1 %111 to i8
  store i8 %114, i8* %113, align 8
  br label %115

115:                                              ; preds = %103, %70
  %116 = load %struct.Obj*, %struct.Obj** %10, align 8
  %117 = getelementptr inbounds %struct.Obj, %struct.Obj* %116, i32 0, i32 12
  %118 = load i8, i8* %117, align 2
  %119 = trunc i8 %118 to i1
  br i1 %119, label %120, label %125

120:                                              ; preds = %115
  %121 = load %struct.Obj*, %struct.Obj** %10, align 8
  %122 = getelementptr inbounds %struct.Obj, %struct.Obj* %121, i32 0, i32 17
  %123 = load i8, i8* %122, align 8
  %124 = trunc i8 %123 to i1
  br label %125

125:                                              ; preds = %120, %115
  %126 = phi i1 [ false, %115 ], [ %124, %120 ]
  %127 = xor i1 %126, true
  %128 = load %struct.Obj*, %struct.Obj** %10, align 8
  %129 = getelementptr inbounds %struct.Obj, %struct.Obj* %128, i32 0, i32 25
  %130 = zext i1 %127 to i8
  store i8 %130, i8* %129, align 1
  %131 = load %struct.Token*, %struct.Token** %5, align 8
  %132 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %131, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  br i1 %132, label %133, label %135

133:                                              ; preds = %125
  %134 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %134, %struct.Token** %4, align 8
  br label %234

135:                                              ; preds = %125
  %136 = load %struct.Obj*, %struct.Obj** %10, align 8
  store %struct.Obj* %136, %struct.Obj** @current_fn, align 8
  store %struct.Obj* null, %struct.Obj** @locals, align 8
  call void @enter_scope()
  %137 = load %struct.Type*, %struct.Type** %8, align 8
  %138 = getelementptr inbounds %struct.Type, %struct.Type* %137, i32 0, i32 18
  %139 = load %struct.Type*, %struct.Type** %138, align 8
  %140 = load i8*, i8** %9, align 8
  call void @create_param_lvars(%struct.Type* noundef %139, i8* noundef %140)
  %141 = load i32, i32* @order, align 4
  %142 = load %struct.Obj*, %struct.Obj** %10, align 8
  %143 = getelementptr inbounds %struct.Obj, %struct.Obj* %142, i32 0, i32 9
  store i32 %141, i32* %143, align 8
  %144 = load %struct.Type*, %struct.Type** %8, align 8
  %145 = getelementptr inbounds %struct.Type, %struct.Type* %144, i32 0, i32 17
  %146 = load %struct.Type*, %struct.Type** %145, align 8
  store %struct.Type* %146, %struct.Type** %11, align 8
  %147 = load %struct.Type*, %struct.Type** %11, align 8
  %148 = getelementptr inbounds %struct.Type, %struct.Type* %147, i32 0, i32 0
  %149 = load i32, i32* %148, align 8
  %150 = icmp eq i32 %149, 14
  br i1 %150, label %156, label %151

151:                                              ; preds = %135
  %152 = load %struct.Type*, %struct.Type** %11, align 8
  %153 = getelementptr inbounds %struct.Type, %struct.Type* %152, i32 0, i32 0
  %154 = load i32, i32* %153, align 8
  %155 = icmp eq i32 %154, 15
  br i1 %155, label %156, label %166

156:                                              ; preds = %151, %135
  %157 = load %struct.Type*, %struct.Type** %11, align 8
  %158 = getelementptr inbounds %struct.Type, %struct.Type* %157, i32 0, i32 1
  %159 = load i32, i32* %158, align 4
  %160 = icmp sgt i32 %159, 16
  br i1 %160, label %161, label %166

161:                                              ; preds = %156
  %162 = load %struct.Type*, %struct.Type** %11, align 8
  %163 = call %struct.Type* @pointer_to(%struct.Type* noundef %162)
  %164 = load i8*, i8** %9, align 8
  %165 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %163, i8* noundef %164)
  br label %166

166:                                              ; preds = %161, %156, %151
  %167 = load %struct.Obj*, %struct.Obj** @locals, align 8
  %168 = load %struct.Obj*, %struct.Obj** %10, align 8
  %169 = getelementptr inbounds %struct.Obj, %struct.Obj* %168, i32 0, i32 18
  store %struct.Obj* %167, %struct.Obj** %169, align 8
  %170 = load %struct.Type*, %struct.Type** %8, align 8
  %171 = getelementptr inbounds %struct.Type, %struct.Type* %170, i32 0, i32 19
  %172 = load i8, i8* %171, align 8
  %173 = trunc i8 %172 to i1
  br i1 %173, label %174, label %181

174:                                              ; preds = %166
  %175 = load %struct.Type*, %struct.Type** @ty_char, align 8
  %176 = call %struct.Type* @array_of(%struct.Type* noundef %175, i32 noundef 136)
  %177 = load i8*, i8** %9, align 8
  %178 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.237, i64 0, i64 0), %struct.Type* noundef %176, i8* noundef %177)
  %179 = load %struct.Obj*, %struct.Obj** %10, align 8
  %180 = getelementptr inbounds %struct.Obj, %struct.Obj* %179, i32 0, i32 21
  store %struct.Obj* %178, %struct.Obj** %180, align 8
  br label %181

181:                                              ; preds = %174, %166
  %182 = load %struct.Type*, %struct.Type** @ty_char, align 8
  %183 = call %struct.Type* @pointer_to(%struct.Type* noundef %182)
  %184 = load i8*, i8** %9, align 8
  %185 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.238, i64 0, i64 0), %struct.Type* noundef %183, i8* noundef %184)
  %186 = load %struct.Obj*, %struct.Obj** %10, align 8
  %187 = getelementptr inbounds %struct.Obj, %struct.Obj* %186, i32 0, i32 22
  store %struct.Obj* %185, %struct.Obj** %187, align 8
  br label %188

188:                                              ; preds = %192, %181
  %189 = load %struct.Token*, %struct.Token** %5, align 8
  %190 = call zeroext i1 @equal(%struct.Token* noundef %189, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  %191 = xor i1 %190, true
  br i1 %191, label %192, label %195

192:                                              ; preds = %188
  %193 = load %struct.Token*, %struct.Token** %5, align 8
  %194 = call %struct.Token* @skip_excess_element2(%struct.Token* noundef %193)
  store %struct.Token* %194, %struct.Token** %5, align 8
  br label %188, !llvm.loop !13

195:                                              ; preds = %188
  %196 = load %struct.Token*, %struct.Token** %5, align 8
  %197 = call %struct.Token* @skip(%struct.Token* noundef %196, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  store %struct.Token* %197, %struct.Token** %5, align 8
  %198 = load %struct.Obj*, %struct.Obj** %10, align 8
  %199 = getelementptr inbounds %struct.Obj, %struct.Obj* %198, i32 0, i32 1
  %200 = load i8*, i8** %199, align 8
  %201 = load %struct.Type*, %struct.Type** @ty_char, align 8
  %202 = load %struct.Obj*, %struct.Obj** %10, align 8
  %203 = getelementptr inbounds %struct.Obj, %struct.Obj* %202, i32 0, i32 1
  %204 = load i8*, i8** %203, align 8
  %205 = call i64 @strlen(i8* noundef %204) #11
  %206 = add i64 %205, 1
  %207 = trunc i64 %206 to i32
  %208 = call %struct.Type* @array_of(%struct.Type* noundef %201, i32 noundef %207)
  %209 = call %struct.Obj* @new_string_literal(i8* noundef %200, %struct.Type* noundef %208)
  %210 = call %struct.VarScope* @push_scope(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.239, i64 0, i64 0))
  %211 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %210, i32 0, i32 0
  store %struct.Obj* %209, %struct.Obj** %211, align 8
  %212 = load %struct.Obj*, %struct.Obj** %10, align 8
  %213 = getelementptr inbounds %struct.Obj, %struct.Obj* %212, i32 0, i32 1
  %214 = load i8*, i8** %213, align 8
  %215 = load %struct.Type*, %struct.Type** @ty_char, align 8
  %216 = load %struct.Obj*, %struct.Obj** %10, align 8
  %217 = getelementptr inbounds %struct.Obj, %struct.Obj* %216, i32 0, i32 1
  %218 = load i8*, i8** %217, align 8
  %219 = call i64 @strlen(i8* noundef %218) #11
  %220 = add i64 %219, 1
  %221 = trunc i64 %220 to i32
  %222 = call %struct.Type* @array_of(%struct.Type* noundef %215, i32 noundef %221)
  %223 = call %struct.Obj* @new_string_literal(i8* noundef %214, %struct.Type* noundef %222)
  %224 = call %struct.VarScope* @push_scope(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.240, i64 0, i64 0))
  %225 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %224, i32 0, i32 0
  store %struct.Obj* %223, %struct.Obj** %225, align 8
  %226 = load %struct.Token*, %struct.Token** %5, align 8
  %227 = call %struct.Node* @compound_stmt(%struct.Token** noundef %5, %struct.Token* noundef %226)
  %228 = load %struct.Obj*, %struct.Obj** %10, align 8
  %229 = getelementptr inbounds %struct.Obj, %struct.Obj* %228, i32 0, i32 19
  store %struct.Node* %227, %struct.Node** %229, align 8
  %230 = load %struct.Obj*, %struct.Obj** @locals, align 8
  %231 = load %struct.Obj*, %struct.Obj** %10, align 8
  %232 = getelementptr inbounds %struct.Obj, %struct.Obj* %231, i32 0, i32 20
  store %struct.Obj* %230, %struct.Obj** %232, align 8
  store i32 0, i32* @order, align 4
  call void @leave_scope()
  call void @resolve_goto_labels()
  %233 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %233, %struct.Token** %4, align 8
  br label %234

234:                                              ; preds = %195, %133
  %235 = load %struct.Token*, %struct.Token** %4, align 8
  ret %struct.Token* %235
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @global_variable(%struct.Token* noundef %0, %struct.Type* noundef %1, %struct.VarAttr* noundef %2) #0 {
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Type*, align 8
  %6 = alloca %struct.VarAttr*, align 8
  %7 = alloca i8, align 1
  %8 = alloca %struct.Type*, align 8
  %9 = alloca %struct.Obj*, align 8
  store %struct.Token* %0, %struct.Token** %4, align 8
  store %struct.Type* %1, %struct.Type** %5, align 8
  store %struct.VarAttr* %2, %struct.VarAttr** %6, align 8
  store i8 1, i8* %7, align 1
  br label %10

10:                                               ; preds = %93, %3
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  %12 = call zeroext i1 @consume(%struct.Token** noundef %4, %struct.Token* noundef %11, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %13 = xor i1 %12, true
  br i1 %13, label %14, label %94

14:                                               ; preds = %10
  %15 = load i8, i8* %7, align 1
  %16 = trunc i8 %15 to i1
  br i1 %16, label %20, label %17

17:                                               ; preds = %14
  %18 = load %struct.Token*, %struct.Token** %4, align 8
  %19 = call %struct.Token* @skip(%struct.Token* noundef %18, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %19, %struct.Token** %4, align 8
  br label %20

20:                                               ; preds = %17, %14
  store i8 0, i8* %7, align 1
  %21 = load %struct.Token*, %struct.Token** %4, align 8
  %22 = load %struct.Type*, %struct.Type** %5, align 8
  %23 = call %struct.Type* @declarator(%struct.Token** noundef %4, %struct.Token* noundef %21, %struct.Type* noundef %22)
  store %struct.Type* %23, %struct.Type** %8, align 8
  %24 = load %struct.Type*, %struct.Type** %8, align 8
  %25 = getelementptr inbounds %struct.Type, %struct.Type* %24, i32 0, i32 9
  %26 = load %struct.Token*, %struct.Token** %25, align 8
  %27 = icmp ne %struct.Token* %26, null
  br i1 %27, label %32, label %28

28:                                               ; preds = %20
  %29 = load %struct.Type*, %struct.Type** %8, align 8
  %30 = getelementptr inbounds %struct.Type, %struct.Type* %29, i32 0, i32 10
  %31 = load %struct.Token*, %struct.Token** %30, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %31, i8* noundef getelementptr inbounds ([47 x i8], [47 x i8]* @.str.242, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

32:                                               ; preds = %20
  %33 = load %struct.Type*, %struct.Type** %8, align 8
  %34 = getelementptr inbounds %struct.Type, %struct.Type* %33, i32 0, i32 9
  %35 = load %struct.Token*, %struct.Token** %34, align 8
  %36 = call i8* @get_ident(%struct.Token* noundef %35)
  %37 = load %struct.Type*, %struct.Type** %8, align 8
  %38 = call %struct.Obj* @new_gvar(i8* noundef %36, %struct.Type* noundef %37)
  store %struct.Obj* %38, %struct.Obj** %9, align 8
  %39 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %40 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %39, i32 0, i32 2
  %41 = load i8, i8* %40, align 2
  %42 = trunc i8 %41 to i1
  %43 = xor i1 %42, true
  %44 = load %struct.Obj*, %struct.Obj** %9, align 8
  %45 = getelementptr inbounds %struct.Obj, %struct.Obj* %44, i32 0, i32 11
  %46 = zext i1 %43 to i8
  store i8 %46, i8* %45, align 1
  %47 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %48 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %47, i32 0, i32 1
  %49 = load i8, i8* %48, align 1
  %50 = trunc i8 %49 to i1
  %51 = load %struct.Obj*, %struct.Obj** %9, align 8
  %52 = getelementptr inbounds %struct.Obj, %struct.Obj* %51, i32 0, i32 12
  %53 = zext i1 %50 to i8
  store i8 %53, i8* %52, align 2
  %54 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %55 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %54, i32 0, i32 4
  %56 = load i8, i8* %55, align 4
  %57 = trunc i8 %56 to i1
  %58 = load %struct.Obj*, %struct.Obj** %9, align 8
  %59 = getelementptr inbounds %struct.Obj, %struct.Obj* %58, i32 0, i32 14
  %60 = zext i1 %57 to i8
  store i8 %60, i8* %59, align 8
  %61 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %62 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %61, i32 0, i32 5
  %63 = load i32, i32* %62, align 4
  %64 = icmp ne i32 %63, 0
  br i1 %64, label %65, label %71

65:                                               ; preds = %32
  %66 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %67 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %66, i32 0, i32 5
  %68 = load i32, i32* %67, align 4
  %69 = load %struct.Obj*, %struct.Obj** %9, align 8
  %70 = getelementptr inbounds %struct.Obj, %struct.Obj* %69, i32 0, i32 6
  store i32 %68, i32* %70, align 4
  br label %71

71:                                               ; preds = %65, %32
  %72 = load %struct.Token*, %struct.Token** %4, align 8
  %73 = call zeroext i1 @equal(%struct.Token* noundef %72, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.150, i64 0, i64 0))
  br i1 %73, label %74, label %79

74:                                               ; preds = %71
  %75 = load %struct.Token*, %struct.Token** %4, align 8
  %76 = getelementptr inbounds %struct.Token, %struct.Token* %75, i32 0, i32 1
  %77 = load %struct.Token*, %struct.Token** %76, align 8
  %78 = load %struct.Obj*, %struct.Obj** %9, align 8
  call void @gvar_initializer(%struct.Token** noundef %4, %struct.Token* noundef %77, %struct.Obj* noundef %78)
  br label %93

79:                                               ; preds = %71
  %80 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %81 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %80, i32 0, i32 2
  %82 = load i8, i8* %81, align 2
  %83 = trunc i8 %82 to i1
  br i1 %83, label %92, label %84

84:                                               ; preds = %79
  %85 = load %struct.VarAttr*, %struct.VarAttr** %6, align 8
  %86 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %85, i32 0, i32 4
  %87 = load i8, i8* %86, align 4
  %88 = trunc i8 %87 to i1
  br i1 %88, label %92, label %89

89:                                               ; preds = %84
  %90 = load %struct.Obj*, %struct.Obj** %9, align 8
  %91 = getelementptr inbounds %struct.Obj, %struct.Obj* %90, i32 0, i32 13
  store i8 1, i8* %91, align 1
  br label %92

92:                                               ; preds = %89, %84, %79
  br label %93

93:                                               ; preds = %92, %74
  br label %10, !llvm.loop !14

94:                                               ; preds = %10
  %95 = load %struct.Token*, %struct.Token** %4, align 8
  ret %struct.Token* %95
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @mark_live(%struct.Obj* noundef %0) #0 {
  %2 = alloca %struct.Obj*, align 8
  %3 = alloca i32, align 4
  %4 = alloca %struct.Obj*, align 8
  store %struct.Obj* %0, %struct.Obj** %2, align 8
  %5 = load %struct.Obj*, %struct.Obj** %2, align 8
  %6 = getelementptr inbounds %struct.Obj, %struct.Obj* %5, i32 0, i32 10
  %7 = load i8, i8* %6, align 4
  %8 = trunc i8 %7 to i1
  br i1 %8, label %9, label %14

9:                                                ; preds = %1
  %10 = load %struct.Obj*, %struct.Obj** %2, align 8
  %11 = getelementptr inbounds %struct.Obj, %struct.Obj* %10, i32 0, i32 24
  %12 = load i8, i8* %11, align 4
  %13 = trunc i8 %12 to i1
  br i1 %13, label %14, label %15

14:                                               ; preds = %9, %1
  br label %43

15:                                               ; preds = %9
  %16 = load %struct.Obj*, %struct.Obj** %2, align 8
  %17 = getelementptr inbounds %struct.Obj, %struct.Obj* %16, i32 0, i32 24
  store i8 1, i8* %17, align 4
  store i32 0, i32* %3, align 4
  br label %18

18:                                               ; preds = %40, %15
  %19 = load i32, i32* %3, align 4
  %20 = load %struct.Obj*, %struct.Obj** %2, align 8
  %21 = getelementptr inbounds %struct.Obj, %struct.Obj* %20, i32 0, i32 26
  %22 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %21, i32 0, i32 2
  %23 = load i32, i32* %22, align 4
  %24 = icmp slt i32 %19, %23
  br i1 %24, label %25, label %43

25:                                               ; preds = %18
  %26 = load %struct.Obj*, %struct.Obj** %2, align 8
  %27 = getelementptr inbounds %struct.Obj, %struct.Obj* %26, i32 0, i32 26
  %28 = getelementptr inbounds %struct.StringArray, %struct.StringArray* %27, i32 0, i32 0
  %29 = load i8**, i8*** %28, align 8
  %30 = load i32, i32* %3, align 4
  %31 = sext i32 %30 to i64
  %32 = getelementptr inbounds i8*, i8** %29, i64 %31
  %33 = load i8*, i8** %32, align 8
  %34 = call %struct.Obj* @find_func(i8* noundef %33)
  store %struct.Obj* %34, %struct.Obj** %4, align 8
  %35 = load %struct.Obj*, %struct.Obj** %4, align 8
  %36 = icmp ne %struct.Obj* %35, null
  br i1 %36, label %37, label %39

37:                                               ; preds = %25
  %38 = load %struct.Obj*, %struct.Obj** %4, align 8
  call void @mark_live(%struct.Obj* noundef %38)
  br label %39

39:                                               ; preds = %37, %25
  br label %40

40:                                               ; preds = %39
  %41 = load i32, i32* %3, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, i32* %3, align 4
  br label %18, !llvm.loop !15

43:                                               ; preds = %14, %18
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @scan_globals() #0 {
  %1 = alloca %struct.Obj, align 8
  %2 = alloca %struct.Obj*, align 8
  %3 = alloca %struct.Obj*, align 8
  %4 = alloca %struct.Obj*, align 8
  store %struct.Obj* %1, %struct.Obj** %2, align 8
  %5 = load %struct.Obj*, %struct.Obj** @globals, align 8
  store %struct.Obj* %5, %struct.Obj** %3, align 8
  br label %6

6:                                                ; preds = %55, %0
  %7 = load %struct.Obj*, %struct.Obj** %3, align 8
  %8 = icmp ne %struct.Obj* %7, null
  br i1 %8, label %9, label %59

9:                                                ; preds = %6
  %10 = load %struct.Obj*, %struct.Obj** %3, align 8
  %11 = getelementptr inbounds %struct.Obj, %struct.Obj* %10, i32 0, i32 13
  %12 = load i8, i8* %11, align 1
  %13 = trunc i8 %12 to i1
  br i1 %13, label %18, label %14

14:                                               ; preds = %9
  %15 = load %struct.Obj*, %struct.Obj** %3, align 8
  %16 = load %struct.Obj*, %struct.Obj** %2, align 8
  %17 = getelementptr inbounds %struct.Obj, %struct.Obj* %16, i32 0, i32 0
  store %struct.Obj* %15, %struct.Obj** %17, align 8
  store %struct.Obj* %15, %struct.Obj** %2, align 8
  br label %55

18:                                               ; preds = %9
  %19 = load %struct.Obj*, %struct.Obj** @globals, align 8
  store %struct.Obj* %19, %struct.Obj** %4, align 8
  br label %20

20:                                               ; preds = %43, %18
  %21 = load %struct.Obj*, %struct.Obj** %4, align 8
  %22 = icmp ne %struct.Obj* %21, null
  br i1 %22, label %23, label %47

23:                                               ; preds = %20
  %24 = load %struct.Obj*, %struct.Obj** %3, align 8
  %25 = load %struct.Obj*, %struct.Obj** %4, align 8
  %26 = icmp ne %struct.Obj* %24, %25
  br i1 %26, label %27, label %42

27:                                               ; preds = %23
  %28 = load %struct.Obj*, %struct.Obj** %4, align 8
  %29 = getelementptr inbounds %struct.Obj, %struct.Obj* %28, i32 0, i32 11
  %30 = load i8, i8* %29, align 1
  %31 = trunc i8 %30 to i1
  br i1 %31, label %32, label %42

32:                                               ; preds = %27
  %33 = load %struct.Obj*, %struct.Obj** %3, align 8
  %34 = getelementptr inbounds %struct.Obj, %struct.Obj* %33, i32 0, i32 1
  %35 = load i8*, i8** %34, align 8
  %36 = load %struct.Obj*, %struct.Obj** %4, align 8
  %37 = getelementptr inbounds %struct.Obj, %struct.Obj* %36, i32 0, i32 1
  %38 = load i8*, i8** %37, align 8
  %39 = call i32 @strcmp(i8* noundef %35, i8* noundef %38) #11
  %40 = icmp ne i32 %39, 0
  br i1 %40, label %42, label %41

41:                                               ; preds = %32
  br label %47

42:                                               ; preds = %32, %27, %23
  br label %43

43:                                               ; preds = %42
  %44 = load %struct.Obj*, %struct.Obj** %4, align 8
  %45 = getelementptr inbounds %struct.Obj, %struct.Obj* %44, i32 0, i32 0
  %46 = load %struct.Obj*, %struct.Obj** %45, align 8
  store %struct.Obj* %46, %struct.Obj** %4, align 8
  br label %20, !llvm.loop !16

47:                                               ; preds = %41, %20
  %48 = load %struct.Obj*, %struct.Obj** %4, align 8
  %49 = icmp ne %struct.Obj* %48, null
  br i1 %49, label %54, label %50

50:                                               ; preds = %47
  %51 = load %struct.Obj*, %struct.Obj** %3, align 8
  %52 = load %struct.Obj*, %struct.Obj** %2, align 8
  %53 = getelementptr inbounds %struct.Obj, %struct.Obj* %52, i32 0, i32 0
  store %struct.Obj* %51, %struct.Obj** %53, align 8
  store %struct.Obj* %51, %struct.Obj** %2, align 8
  br label %54

54:                                               ; preds = %50, %47
  br label %55

55:                                               ; preds = %54, %14
  %56 = load %struct.Obj*, %struct.Obj** %3, align 8
  %57 = getelementptr inbounds %struct.Obj, %struct.Obj* %56, i32 0, i32 0
  %58 = load %struct.Obj*, %struct.Obj** %57, align 8
  store %struct.Obj* %58, %struct.Obj** %3, align 8
  br label %6, !llvm.loop !17

59:                                               ; preds = %6
  %60 = load %struct.Obj*, %struct.Obj** %2, align 8
  %61 = getelementptr inbounds %struct.Obj, %struct.Obj* %60, i32 0, i32 0
  store %struct.Obj* null, %struct.Obj** %61, align 8
  %62 = getelementptr inbounds %struct.Obj, %struct.Obj* %1, i32 0, i32 0
  %63 = load %struct.Obj*, %struct.Obj** %62, align 8
  store %struct.Obj* %63, %struct.Obj** @globals, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @nodekind2str(i32 noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  switch i32 %4, label %53 [
    i32 0, label %5
    i32 1, label %6
    i32 2, label %7
    i32 3, label %8
    i32 4, label %9
    i32 5, label %10
    i32 6, label %11
    i32 7, label %12
    i32 8, label %13
    i32 9, label %14
    i32 10, label %15
    i32 11, label %16
    i32 12, label %17
    i32 13, label %18
    i32 14, label %19
    i32 15, label %20
    i32 16, label %21
    i32 17, label %22
    i32 18, label %23
    i32 19, label %24
    i32 20, label %25
    i32 21, label %26
    i32 22, label %27
    i32 23, label %28
    i32 24, label %29
    i32 25, label %30
    i32 26, label %31
    i32 27, label %32
    i32 28, label %33
    i32 29, label %34
    i32 30, label %35
    i32 31, label %36
    i32 32, label %37
    i32 33, label %38
    i32 34, label %39
    i32 35, label %40
    i32 36, label %41
    i32 37, label %42
    i32 38, label %43
    i32 39, label %44
    i32 40, label %45
    i32 41, label %46
    i32 42, label %47
    i32 43, label %48
    i32 44, label %49
    i32 45, label %50
    i32 46, label %51
    i32 47, label %52
  ]

5:                                                ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i64 0, i64 0), i8** %2, align 8
  br label %54

6:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i64 0, i64 0), i8** %2, align 8
  br label %54

7:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i64 0, i64 0), i8** %2, align 8
  br label %54

8:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i64 0, i64 0), i8** %2, align 8
  br label %54

9:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i64 0, i64 0), i8** %2, align 8
  br label %54

10:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.12, i64 0, i64 0), i8** %2, align 8
  br label %54

11:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.13, i64 0, i64 0), i8** %2, align 8
  br label %54

12:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.14, i64 0, i64 0), i8** %2, align 8
  br label %54

13:                                               ; preds = %1
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i64 0, i64 0), i8** %2, align 8
  br label %54

14:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.16, i64 0, i64 0), i8** %2, align 8
  br label %54

15:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.17, i64 0, i64 0), i8** %2, align 8
  br label %54

16:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.18, i64 0, i64 0), i8** %2, align 8
  br label %54

17:                                               ; preds = %1
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.19, i64 0, i64 0), i8** %2, align 8
  br label %54

18:                                               ; preds = %1
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.20, i64 0, i64 0), i8** %2, align 8
  br label %54

19:                                               ; preds = %1
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.21, i64 0, i64 0), i8** %2, align 8
  br label %54

20:                                               ; preds = %1
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.22, i64 0, i64 0), i8** %2, align 8
  br label %54

21:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.23, i64 0, i64 0), i8** %2, align 8
  br label %54

22:                                               ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.24, i64 0, i64 0), i8** %2, align 8
  br label %54

23:                                               ; preds = %1
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.25, i64 0, i64 0), i8** %2, align 8
  br label %54

24:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.26, i64 0, i64 0), i8** %2, align 8
  br label %54

25:                                               ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.27, i64 0, i64 0), i8** %2, align 8
  br label %54

26:                                               ; preds = %1
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.28, i64 0, i64 0), i8** %2, align 8
  br label %54

27:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.29, i64 0, i64 0), i8** %2, align 8
  br label %54

28:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.30, i64 0, i64 0), i8** %2, align 8
  br label %54

29:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.31, i64 0, i64 0), i8** %2, align 8
  br label %54

30:                                               ; preds = %1
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.32, i64 0, i64 0), i8** %2, align 8
  br label %54

31:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.33, i64 0, i64 0), i8** %2, align 8
  br label %54

32:                                               ; preds = %1
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.34, i64 0, i64 0), i8** %2, align 8
  br label %54

33:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.35, i64 0, i64 0), i8** %2, align 8
  br label %54

34:                                               ; preds = %1
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.36, i64 0, i64 0), i8** %2, align 8
  br label %54

35:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.37, i64 0, i64 0), i8** %2, align 8
  br label %54

36:                                               ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.38, i64 0, i64 0), i8** %2, align 8
  br label %54

37:                                               ; preds = %1
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.39, i64 0, i64 0), i8** %2, align 8
  br label %54

38:                                               ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.40, i64 0, i64 0), i8** %2, align 8
  br label %54

39:                                               ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.41, i64 0, i64 0), i8** %2, align 8
  br label %54

40:                                               ; preds = %1
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.42, i64 0, i64 0), i8** %2, align 8
  br label %54

41:                                               ; preds = %1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.43, i64 0, i64 0), i8** %2, align 8
  br label %54

42:                                               ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.44, i64 0, i64 0), i8** %2, align 8
  br label %54

43:                                               ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.45, i64 0, i64 0), i8** %2, align 8
  br label %54

44:                                               ; preds = %1
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.46, i64 0, i64 0), i8** %2, align 8
  br label %54

45:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.47, i64 0, i64 0), i8** %2, align 8
  br label %54

46:                                               ; preds = %1
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.48, i64 0, i64 0), i8** %2, align 8
  br label %54

47:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.49, i64 0, i64 0), i8** %2, align 8
  br label %54

48:                                               ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.50, i64 0, i64 0), i8** %2, align 8
  br label %54

49:                                               ; preds = %1
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.51, i64 0, i64 0), i8** %2, align 8
  br label %54

50:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.52, i64 0, i64 0), i8** %2, align 8
  br label %54

51:                                               ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.53, i64 0, i64 0), i8** %2, align 8
  br label %54

52:                                               ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.54, i64 0, i64 0), i8** %2, align 8
  br label %54

53:                                               ; preds = %1
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.55, i64 0, i64 0), i8** %2, align 8
  br label %54

54:                                               ; preds = %53, %52, %51, %50, %49, %48, %47, %46, %45, %44, %43, %42, %41, %40, %39, %38, %37, %36, %35, %34, %33, %32, %31, %30, %29, %28, %27, %26, %25, %24, %23, %22, %21, %20, %19, %18, %17, %16, %15, %14, %13, %12, %11, %10, %9, %8, %7, %6, %5
  %55 = load i8*, i8** %2, align 8
  ret i8* %55
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i64 @eval2(%struct.Node* noundef %0, i8*** noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca %struct.Node*, align 8
  %5 = alloca i8***, align 8
  %6 = alloca i64, align 8
  store %struct.Node* %0, %struct.Node** %4, align 8
  store i8*** %1, i8**** %5, align 8
  %7 = load %struct.Node*, %struct.Node** %4, align 8
  call void @add_type(%struct.Node* noundef %7)
  %8 = load %struct.Node*, %struct.Node** %4, align 8
  %9 = getelementptr inbounds %struct.Node, %struct.Node* %8, i32 0, i32 2
  %10 = load %struct.Type*, %struct.Type** %9, align 16
  %11 = call zeroext i1 @is_flonum(%struct.Type* noundef %10)
  br i1 %11, label %12, label %16

12:                                               ; preds = %2
  %13 = load %struct.Node*, %struct.Node** %4, align 8
  %14 = call double @eval_double(%struct.Node* noundef %13)
  %15 = fptosi double %14 to i64
  store i64 %15, i64* %3, align 8
  br label %510

16:                                               ; preds = %2
  %17 = load %struct.Node*, %struct.Node** %4, align 8
  %18 = getelementptr inbounds %struct.Node, %struct.Node* %17, i32 0, i32 0
  %19 = load i32, i32* %18, align 16
  switch i32 %19, label %506 [
    i32 1, label %20
    i32 2, label %31
    i32 3, label %42
    i32 4, label %52
    i32 5, label %79
    i32 6, label %85
    i32 7, label %112
    i32 8, label %122
    i32 9, label %132
    i32 10, label %142
    i32 11, label %152
    i32 12, label %186
    i32 13, label %198
    i32 14, label %210
    i32 15, label %243
    i32 17, label %276
    i32 18, label %296
    i32 22, label %302
    i32 23, label %311
    i32 24, label %317
    i32 25, label %333
    i32 43, label %349
    i32 20, label %420
    i32 36, label %426
    i32 19, label %430
    i32 40, label %461
    i32 42, label %496
    i32 21, label %500
  ]

20:                                               ; preds = %16
  %21 = load %struct.Node*, %struct.Node** %4, align 8
  %22 = getelementptr inbounds %struct.Node, %struct.Node* %21, i32 0, i32 4
  %23 = load %struct.Node*, %struct.Node** %22, align 16
  %24 = load i8***, i8**** %5, align 8
  %25 = call i64 @eval2(%struct.Node* noundef %23, i8*** noundef %24)
  %26 = load %struct.Node*, %struct.Node** %4, align 8
  %27 = getelementptr inbounds %struct.Node, %struct.Node* %26, i32 0, i32 5
  %28 = load %struct.Node*, %struct.Node** %27, align 8
  %29 = call i64 @eval(%struct.Node* noundef %28)
  %30 = add nsw i64 %25, %29
  store i64 %30, i64* %3, align 8
  br label %510

31:                                               ; preds = %16
  %32 = load %struct.Node*, %struct.Node** %4, align 8
  %33 = getelementptr inbounds %struct.Node, %struct.Node* %32, i32 0, i32 4
  %34 = load %struct.Node*, %struct.Node** %33, align 16
  %35 = load i8***, i8**** %5, align 8
  %36 = call i64 @eval2(%struct.Node* noundef %34, i8*** noundef %35)
  %37 = load %struct.Node*, %struct.Node** %4, align 8
  %38 = getelementptr inbounds %struct.Node, %struct.Node* %37, i32 0, i32 5
  %39 = load %struct.Node*, %struct.Node** %38, align 8
  %40 = call i64 @eval(%struct.Node* noundef %39)
  %41 = sub nsw i64 %36, %40
  store i64 %41, i64* %3, align 8
  br label %510

42:                                               ; preds = %16
  %43 = load %struct.Node*, %struct.Node** %4, align 8
  %44 = getelementptr inbounds %struct.Node, %struct.Node* %43, i32 0, i32 4
  %45 = load %struct.Node*, %struct.Node** %44, align 16
  %46 = call i64 @eval(%struct.Node* noundef %45)
  %47 = load %struct.Node*, %struct.Node** %4, align 8
  %48 = getelementptr inbounds %struct.Node, %struct.Node* %47, i32 0, i32 5
  %49 = load %struct.Node*, %struct.Node** %48, align 8
  %50 = call i64 @eval(%struct.Node* noundef %49)
  %51 = mul nsw i64 %46, %50
  store i64 %51, i64* %3, align 8
  br label %510

52:                                               ; preds = %16
  %53 = load %struct.Node*, %struct.Node** %4, align 8
  %54 = getelementptr inbounds %struct.Node, %struct.Node* %53, i32 0, i32 2
  %55 = load %struct.Type*, %struct.Type** %54, align 16
  %56 = getelementptr inbounds %struct.Type, %struct.Type* %55, i32 0, i32 3
  %57 = load i8, i8* %56, align 4
  %58 = trunc i8 %57 to i1
  br i1 %58, label %59, label %69

59:                                               ; preds = %52
  %60 = load %struct.Node*, %struct.Node** %4, align 8
  %61 = getelementptr inbounds %struct.Node, %struct.Node* %60, i32 0, i32 4
  %62 = load %struct.Node*, %struct.Node** %61, align 16
  %63 = call i64 @eval(%struct.Node* noundef %62)
  %64 = load %struct.Node*, %struct.Node** %4, align 8
  %65 = getelementptr inbounds %struct.Node, %struct.Node* %64, i32 0, i32 5
  %66 = load %struct.Node*, %struct.Node** %65, align 8
  %67 = call i64 @eval(%struct.Node* noundef %66)
  %68 = udiv i64 %63, %67
  store i64 %68, i64* %3, align 8
  br label %510

69:                                               ; preds = %52
  %70 = load %struct.Node*, %struct.Node** %4, align 8
  %71 = getelementptr inbounds %struct.Node, %struct.Node* %70, i32 0, i32 4
  %72 = load %struct.Node*, %struct.Node** %71, align 16
  %73 = call i64 @eval(%struct.Node* noundef %72)
  %74 = load %struct.Node*, %struct.Node** %4, align 8
  %75 = getelementptr inbounds %struct.Node, %struct.Node* %74, i32 0, i32 5
  %76 = load %struct.Node*, %struct.Node** %75, align 8
  %77 = call i64 @eval(%struct.Node* noundef %76)
  %78 = sdiv i64 %73, %77
  store i64 %78, i64* %3, align 8
  br label %510

79:                                               ; preds = %16
  %80 = load %struct.Node*, %struct.Node** %4, align 8
  %81 = getelementptr inbounds %struct.Node, %struct.Node* %80, i32 0, i32 4
  %82 = load %struct.Node*, %struct.Node** %81, align 16
  %83 = call i64 @eval(%struct.Node* noundef %82)
  %84 = sub nsw i64 0, %83
  store i64 %84, i64* %3, align 8
  br label %510

85:                                               ; preds = %16
  %86 = load %struct.Node*, %struct.Node** %4, align 8
  %87 = getelementptr inbounds %struct.Node, %struct.Node* %86, i32 0, i32 2
  %88 = load %struct.Type*, %struct.Type** %87, align 16
  %89 = getelementptr inbounds %struct.Type, %struct.Type* %88, i32 0, i32 3
  %90 = load i8, i8* %89, align 4
  %91 = trunc i8 %90 to i1
  br i1 %91, label %92, label %102

92:                                               ; preds = %85
  %93 = load %struct.Node*, %struct.Node** %4, align 8
  %94 = getelementptr inbounds %struct.Node, %struct.Node* %93, i32 0, i32 4
  %95 = load %struct.Node*, %struct.Node** %94, align 16
  %96 = call i64 @eval(%struct.Node* noundef %95)
  %97 = load %struct.Node*, %struct.Node** %4, align 8
  %98 = getelementptr inbounds %struct.Node, %struct.Node* %97, i32 0, i32 5
  %99 = load %struct.Node*, %struct.Node** %98, align 8
  %100 = call i64 @eval(%struct.Node* noundef %99)
  %101 = urem i64 %96, %100
  store i64 %101, i64* %3, align 8
  br label %510

102:                                              ; preds = %85
  %103 = load %struct.Node*, %struct.Node** %4, align 8
  %104 = getelementptr inbounds %struct.Node, %struct.Node* %103, i32 0, i32 4
  %105 = load %struct.Node*, %struct.Node** %104, align 16
  %106 = call i64 @eval(%struct.Node* noundef %105)
  %107 = load %struct.Node*, %struct.Node** %4, align 8
  %108 = getelementptr inbounds %struct.Node, %struct.Node* %107, i32 0, i32 5
  %109 = load %struct.Node*, %struct.Node** %108, align 8
  %110 = call i64 @eval(%struct.Node* noundef %109)
  %111 = srem i64 %106, %110
  store i64 %111, i64* %3, align 8
  br label %510

112:                                              ; preds = %16
  %113 = load %struct.Node*, %struct.Node** %4, align 8
  %114 = getelementptr inbounds %struct.Node, %struct.Node* %113, i32 0, i32 4
  %115 = load %struct.Node*, %struct.Node** %114, align 16
  %116 = call i64 @eval(%struct.Node* noundef %115)
  %117 = load %struct.Node*, %struct.Node** %4, align 8
  %118 = getelementptr inbounds %struct.Node, %struct.Node* %117, i32 0, i32 5
  %119 = load %struct.Node*, %struct.Node** %118, align 8
  %120 = call i64 @eval(%struct.Node* noundef %119)
  %121 = and i64 %116, %120
  store i64 %121, i64* %3, align 8
  br label %510

122:                                              ; preds = %16
  %123 = load %struct.Node*, %struct.Node** %4, align 8
  %124 = getelementptr inbounds %struct.Node, %struct.Node* %123, i32 0, i32 4
  %125 = load %struct.Node*, %struct.Node** %124, align 16
  %126 = call i64 @eval(%struct.Node* noundef %125)
  %127 = load %struct.Node*, %struct.Node** %4, align 8
  %128 = getelementptr inbounds %struct.Node, %struct.Node* %127, i32 0, i32 5
  %129 = load %struct.Node*, %struct.Node** %128, align 8
  %130 = call i64 @eval(%struct.Node* noundef %129)
  %131 = or i64 %126, %130
  store i64 %131, i64* %3, align 8
  br label %510

132:                                              ; preds = %16
  %133 = load %struct.Node*, %struct.Node** %4, align 8
  %134 = getelementptr inbounds %struct.Node, %struct.Node* %133, i32 0, i32 4
  %135 = load %struct.Node*, %struct.Node** %134, align 16
  %136 = call i64 @eval(%struct.Node* noundef %135)
  %137 = load %struct.Node*, %struct.Node** %4, align 8
  %138 = getelementptr inbounds %struct.Node, %struct.Node* %137, i32 0, i32 5
  %139 = load %struct.Node*, %struct.Node** %138, align 8
  %140 = call i64 @eval(%struct.Node* noundef %139)
  %141 = xor i64 %136, %140
  store i64 %141, i64* %3, align 8
  br label %510

142:                                              ; preds = %16
  %143 = load %struct.Node*, %struct.Node** %4, align 8
  %144 = getelementptr inbounds %struct.Node, %struct.Node* %143, i32 0, i32 4
  %145 = load %struct.Node*, %struct.Node** %144, align 16
  %146 = call i64 @eval(%struct.Node* noundef %145)
  %147 = load %struct.Node*, %struct.Node** %4, align 8
  %148 = getelementptr inbounds %struct.Node, %struct.Node* %147, i32 0, i32 5
  %149 = load %struct.Node*, %struct.Node** %148, align 8
  %150 = call i64 @eval(%struct.Node* noundef %149)
  %151 = shl i64 %146, %150
  store i64 %151, i64* %3, align 8
  br label %510

152:                                              ; preds = %16
  %153 = load %struct.Node*, %struct.Node** %4, align 8
  %154 = getelementptr inbounds %struct.Node, %struct.Node* %153, i32 0, i32 2
  %155 = load %struct.Type*, %struct.Type** %154, align 16
  %156 = getelementptr inbounds %struct.Type, %struct.Type* %155, i32 0, i32 3
  %157 = load i8, i8* %156, align 4
  %158 = trunc i8 %157 to i1
  br i1 %158, label %159, label %176

159:                                              ; preds = %152
  %160 = load %struct.Node*, %struct.Node** %4, align 8
  %161 = getelementptr inbounds %struct.Node, %struct.Node* %160, i32 0, i32 2
  %162 = load %struct.Type*, %struct.Type** %161, align 16
  %163 = getelementptr inbounds %struct.Type, %struct.Type* %162, i32 0, i32 1
  %164 = load i32, i32* %163, align 4
  %165 = icmp eq i32 %164, 8
  br i1 %165, label %166, label %176

166:                                              ; preds = %159
  %167 = load %struct.Node*, %struct.Node** %4, align 8
  %168 = getelementptr inbounds %struct.Node, %struct.Node* %167, i32 0, i32 4
  %169 = load %struct.Node*, %struct.Node** %168, align 16
  %170 = call i64 @eval(%struct.Node* noundef %169)
  %171 = load %struct.Node*, %struct.Node** %4, align 8
  %172 = getelementptr inbounds %struct.Node, %struct.Node* %171, i32 0, i32 5
  %173 = load %struct.Node*, %struct.Node** %172, align 8
  %174 = call i64 @eval(%struct.Node* noundef %173)
  %175 = lshr i64 %170, %174
  store i64 %175, i64* %3, align 8
  br label %510

176:                                              ; preds = %159, %152
  %177 = load %struct.Node*, %struct.Node** %4, align 8
  %178 = getelementptr inbounds %struct.Node, %struct.Node* %177, i32 0, i32 4
  %179 = load %struct.Node*, %struct.Node** %178, align 16
  %180 = call i64 @eval(%struct.Node* noundef %179)
  %181 = load %struct.Node*, %struct.Node** %4, align 8
  %182 = getelementptr inbounds %struct.Node, %struct.Node* %181, i32 0, i32 5
  %183 = load %struct.Node*, %struct.Node** %182, align 8
  %184 = call i64 @eval(%struct.Node* noundef %183)
  %185 = ashr i64 %180, %184
  store i64 %185, i64* %3, align 8
  br label %510

186:                                              ; preds = %16
  %187 = load %struct.Node*, %struct.Node** %4, align 8
  %188 = getelementptr inbounds %struct.Node, %struct.Node* %187, i32 0, i32 4
  %189 = load %struct.Node*, %struct.Node** %188, align 16
  %190 = call i64 @eval(%struct.Node* noundef %189)
  %191 = load %struct.Node*, %struct.Node** %4, align 8
  %192 = getelementptr inbounds %struct.Node, %struct.Node* %191, i32 0, i32 5
  %193 = load %struct.Node*, %struct.Node** %192, align 8
  %194 = call i64 @eval(%struct.Node* noundef %193)
  %195 = icmp eq i64 %190, %194
  %196 = zext i1 %195 to i32
  %197 = sext i32 %196 to i64
  store i64 %197, i64* %3, align 8
  br label %510

198:                                              ; preds = %16
  %199 = load %struct.Node*, %struct.Node** %4, align 8
  %200 = getelementptr inbounds %struct.Node, %struct.Node* %199, i32 0, i32 4
  %201 = load %struct.Node*, %struct.Node** %200, align 16
  %202 = call i64 @eval(%struct.Node* noundef %201)
  %203 = load %struct.Node*, %struct.Node** %4, align 8
  %204 = getelementptr inbounds %struct.Node, %struct.Node* %203, i32 0, i32 5
  %205 = load %struct.Node*, %struct.Node** %204, align 8
  %206 = call i64 @eval(%struct.Node* noundef %205)
  %207 = icmp ne i64 %202, %206
  %208 = zext i1 %207 to i32
  %209 = sext i32 %208 to i64
  store i64 %209, i64* %3, align 8
  br label %510

210:                                              ; preds = %16
  %211 = load %struct.Node*, %struct.Node** %4, align 8
  %212 = getelementptr inbounds %struct.Node, %struct.Node* %211, i32 0, i32 4
  %213 = load %struct.Node*, %struct.Node** %212, align 16
  %214 = getelementptr inbounds %struct.Node, %struct.Node* %213, i32 0, i32 2
  %215 = load %struct.Type*, %struct.Type** %214, align 16
  %216 = getelementptr inbounds %struct.Type, %struct.Type* %215, i32 0, i32 3
  %217 = load i8, i8* %216, align 4
  %218 = trunc i8 %217 to i1
  br i1 %218, label %219, label %231

219:                                              ; preds = %210
  %220 = load %struct.Node*, %struct.Node** %4, align 8
  %221 = getelementptr inbounds %struct.Node, %struct.Node* %220, i32 0, i32 4
  %222 = load %struct.Node*, %struct.Node** %221, align 16
  %223 = call i64 @eval(%struct.Node* noundef %222)
  %224 = load %struct.Node*, %struct.Node** %4, align 8
  %225 = getelementptr inbounds %struct.Node, %struct.Node* %224, i32 0, i32 5
  %226 = load %struct.Node*, %struct.Node** %225, align 8
  %227 = call i64 @eval(%struct.Node* noundef %226)
  %228 = icmp ult i64 %223, %227
  %229 = zext i1 %228 to i32
  %230 = sext i32 %229 to i64
  store i64 %230, i64* %3, align 8
  br label %510

231:                                              ; preds = %210
  %232 = load %struct.Node*, %struct.Node** %4, align 8
  %233 = getelementptr inbounds %struct.Node, %struct.Node* %232, i32 0, i32 4
  %234 = load %struct.Node*, %struct.Node** %233, align 16
  %235 = call i64 @eval(%struct.Node* noundef %234)
  %236 = load %struct.Node*, %struct.Node** %4, align 8
  %237 = getelementptr inbounds %struct.Node, %struct.Node* %236, i32 0, i32 5
  %238 = load %struct.Node*, %struct.Node** %237, align 8
  %239 = call i64 @eval(%struct.Node* noundef %238)
  %240 = icmp slt i64 %235, %239
  %241 = zext i1 %240 to i32
  %242 = sext i32 %241 to i64
  store i64 %242, i64* %3, align 8
  br label %510

243:                                              ; preds = %16
  %244 = load %struct.Node*, %struct.Node** %4, align 8
  %245 = getelementptr inbounds %struct.Node, %struct.Node* %244, i32 0, i32 4
  %246 = load %struct.Node*, %struct.Node** %245, align 16
  %247 = getelementptr inbounds %struct.Node, %struct.Node* %246, i32 0, i32 2
  %248 = load %struct.Type*, %struct.Type** %247, align 16
  %249 = getelementptr inbounds %struct.Type, %struct.Type* %248, i32 0, i32 3
  %250 = load i8, i8* %249, align 4
  %251 = trunc i8 %250 to i1
  br i1 %251, label %252, label %264

252:                                              ; preds = %243
  %253 = load %struct.Node*, %struct.Node** %4, align 8
  %254 = getelementptr inbounds %struct.Node, %struct.Node* %253, i32 0, i32 4
  %255 = load %struct.Node*, %struct.Node** %254, align 16
  %256 = call i64 @eval(%struct.Node* noundef %255)
  %257 = load %struct.Node*, %struct.Node** %4, align 8
  %258 = getelementptr inbounds %struct.Node, %struct.Node* %257, i32 0, i32 5
  %259 = load %struct.Node*, %struct.Node** %258, align 8
  %260 = call i64 @eval(%struct.Node* noundef %259)
  %261 = icmp ule i64 %256, %260
  %262 = zext i1 %261 to i32
  %263 = sext i32 %262 to i64
  store i64 %263, i64* %3, align 8
  br label %510

264:                                              ; preds = %243
  %265 = load %struct.Node*, %struct.Node** %4, align 8
  %266 = getelementptr inbounds %struct.Node, %struct.Node* %265, i32 0, i32 4
  %267 = load %struct.Node*, %struct.Node** %266, align 16
  %268 = call i64 @eval(%struct.Node* noundef %267)
  %269 = load %struct.Node*, %struct.Node** %4, align 8
  %270 = getelementptr inbounds %struct.Node, %struct.Node* %269, i32 0, i32 5
  %271 = load %struct.Node*, %struct.Node** %270, align 8
  %272 = call i64 @eval(%struct.Node* noundef %271)
  %273 = icmp sle i64 %268, %272
  %274 = zext i1 %273 to i32
  %275 = sext i32 %274 to i64
  store i64 %275, i64* %3, align 8
  br label %510

276:                                              ; preds = %16
  %277 = load %struct.Node*, %struct.Node** %4, align 8
  %278 = getelementptr inbounds %struct.Node, %struct.Node* %277, i32 0, i32 6
  %279 = load %struct.Node*, %struct.Node** %278, align 16
  %280 = call i64 @eval(%struct.Node* noundef %279)
  %281 = icmp ne i64 %280, 0
  br i1 %281, label %282, label %288

282:                                              ; preds = %276
  %283 = load %struct.Node*, %struct.Node** %4, align 8
  %284 = getelementptr inbounds %struct.Node, %struct.Node* %283, i32 0, i32 7
  %285 = load %struct.Node*, %struct.Node** %284, align 8
  %286 = load i8***, i8**** %5, align 8
  %287 = call i64 @eval2(%struct.Node* noundef %285, i8*** noundef %286)
  br label %294

288:                                              ; preds = %276
  %289 = load %struct.Node*, %struct.Node** %4, align 8
  %290 = getelementptr inbounds %struct.Node, %struct.Node* %289, i32 0, i32 8
  %291 = load %struct.Node*, %struct.Node** %290, align 16
  %292 = load i8***, i8**** %5, align 8
  %293 = call i64 @eval2(%struct.Node* noundef %291, i8*** noundef %292)
  br label %294

294:                                              ; preds = %288, %282
  %295 = phi i64 [ %287, %282 ], [ %293, %288 ]
  store i64 %295, i64* %3, align 8
  br label %510

296:                                              ; preds = %16
  %297 = load %struct.Node*, %struct.Node** %4, align 8
  %298 = getelementptr inbounds %struct.Node, %struct.Node* %297, i32 0, i32 5
  %299 = load %struct.Node*, %struct.Node** %298, align 8
  %300 = load i8***, i8**** %5, align 8
  %301 = call i64 @eval2(%struct.Node* noundef %299, i8*** noundef %300)
  store i64 %301, i64* %3, align 8
  br label %510

302:                                              ; preds = %16
  %303 = load %struct.Node*, %struct.Node** %4, align 8
  %304 = getelementptr inbounds %struct.Node, %struct.Node* %303, i32 0, i32 4
  %305 = load %struct.Node*, %struct.Node** %304, align 16
  %306 = call i64 @eval(%struct.Node* noundef %305)
  %307 = icmp ne i64 %306, 0
  %308 = xor i1 %307, true
  %309 = zext i1 %308 to i32
  %310 = sext i32 %309 to i64
  store i64 %310, i64* %3, align 8
  br label %510

311:                                              ; preds = %16
  %312 = load %struct.Node*, %struct.Node** %4, align 8
  %313 = getelementptr inbounds %struct.Node, %struct.Node* %312, i32 0, i32 4
  %314 = load %struct.Node*, %struct.Node** %313, align 16
  %315 = call i64 @eval(%struct.Node* noundef %314)
  %316 = xor i64 %315, -1
  store i64 %316, i64* %3, align 8
  br label %510

317:                                              ; preds = %16
  %318 = load %struct.Node*, %struct.Node** %4, align 8
  %319 = getelementptr inbounds %struct.Node, %struct.Node* %318, i32 0, i32 4
  %320 = load %struct.Node*, %struct.Node** %319, align 16
  %321 = call i64 @eval(%struct.Node* noundef %320)
  %322 = icmp ne i64 %321, 0
  br i1 %322, label %323, label %329

323:                                              ; preds = %317
  %324 = load %struct.Node*, %struct.Node** %4, align 8
  %325 = getelementptr inbounds %struct.Node, %struct.Node* %324, i32 0, i32 5
  %326 = load %struct.Node*, %struct.Node** %325, align 8
  %327 = call i64 @eval(%struct.Node* noundef %326)
  %328 = icmp ne i64 %327, 0
  br label %329

329:                                              ; preds = %323, %317
  %330 = phi i1 [ false, %317 ], [ %328, %323 ]
  %331 = zext i1 %330 to i32
  %332 = sext i32 %331 to i64
  store i64 %332, i64* %3, align 8
  br label %510

333:                                              ; preds = %16
  %334 = load %struct.Node*, %struct.Node** %4, align 8
  %335 = getelementptr inbounds %struct.Node, %struct.Node* %334, i32 0, i32 4
  %336 = load %struct.Node*, %struct.Node** %335, align 16
  %337 = call i64 @eval(%struct.Node* noundef %336)
  %338 = icmp ne i64 %337, 0
  br i1 %338, label %345, label %339

339:                                              ; preds = %333
  %340 = load %struct.Node*, %struct.Node** %4, align 8
  %341 = getelementptr inbounds %struct.Node, %struct.Node* %340, i32 0, i32 5
  %342 = load %struct.Node*, %struct.Node** %341, align 8
  %343 = call i64 @eval(%struct.Node* noundef %342)
  %344 = icmp ne i64 %343, 0
  br label %345

345:                                              ; preds = %339, %333
  %346 = phi i1 [ true, %333 ], [ %344, %339 ]
  %347 = zext i1 %346 to i32
  %348 = sext i32 %347 to i64
  store i64 %348, i64* %3, align 8
  br label %510

349:                                              ; preds = %16
  %350 = load %struct.Node*, %struct.Node** %4, align 8
  %351 = getelementptr inbounds %struct.Node, %struct.Node* %350, i32 0, i32 4
  %352 = load %struct.Node*, %struct.Node** %351, align 16
  %353 = load i8***, i8**** %5, align 8
  %354 = call i64 @eval2(%struct.Node* noundef %352, i8*** noundef %353)
  store i64 %354, i64* %6, align 8
  %355 = load %struct.Node*, %struct.Node** %4, align 8
  %356 = getelementptr inbounds %struct.Node, %struct.Node* %355, i32 0, i32 2
  %357 = load %struct.Type*, %struct.Type** %356, align 16
  %358 = call zeroext i1 @is_integer(%struct.Type* noundef %357)
  br i1 %358, label %359, label %418

359:                                              ; preds = %349
  %360 = load %struct.Node*, %struct.Node** %4, align 8
  %361 = getelementptr inbounds %struct.Node, %struct.Node* %360, i32 0, i32 2
  %362 = load %struct.Type*, %struct.Type** %361, align 16
  %363 = getelementptr inbounds %struct.Type, %struct.Type* %362, i32 0, i32 1
  %364 = load i32, i32* %363, align 4
  switch i32 %364, label %417 [
    i32 1, label %365
    i32 2, label %383
    i32 4, label %401
  ]

365:                                              ; preds = %359
  %366 = load %struct.Node*, %struct.Node** %4, align 8
  %367 = getelementptr inbounds %struct.Node, %struct.Node* %366, i32 0, i32 2
  %368 = load %struct.Type*, %struct.Type** %367, align 16
  %369 = getelementptr inbounds %struct.Type, %struct.Type* %368, i32 0, i32 3
  %370 = load i8, i8* %369, align 4
  %371 = trunc i8 %370 to i1
  br i1 %371, label %372, label %376

372:                                              ; preds = %365
  %373 = load i64, i64* %6, align 8
  %374 = trunc i64 %373 to i8
  %375 = zext i8 %374 to i32
  br label %380

376:                                              ; preds = %365
  %377 = load i64, i64* %6, align 8
  %378 = trunc i64 %377 to i8
  %379 = sext i8 %378 to i32
  br label %380

380:                                              ; preds = %376, %372
  %381 = phi i32 [ %375, %372 ], [ %379, %376 ]
  %382 = sext i32 %381 to i64
  store i64 %382, i64* %3, align 8
  br label %510

383:                                              ; preds = %359
  %384 = load %struct.Node*, %struct.Node** %4, align 8
  %385 = getelementptr inbounds %struct.Node, %struct.Node* %384, i32 0, i32 2
  %386 = load %struct.Type*, %struct.Type** %385, align 16
  %387 = getelementptr inbounds %struct.Type, %struct.Type* %386, i32 0, i32 3
  %388 = load i8, i8* %387, align 4
  %389 = trunc i8 %388 to i1
  br i1 %389, label %390, label %394

390:                                              ; preds = %383
  %391 = load i64, i64* %6, align 8
  %392 = trunc i64 %391 to i16
  %393 = zext i16 %392 to i32
  br label %398

394:                                              ; preds = %383
  %395 = load i64, i64* %6, align 8
  %396 = trunc i64 %395 to i16
  %397 = sext i16 %396 to i32
  br label %398

398:                                              ; preds = %394, %390
  %399 = phi i32 [ %393, %390 ], [ %397, %394 ]
  %400 = sext i32 %399 to i64
  store i64 %400, i64* %3, align 8
  br label %510

401:                                              ; preds = %359
  %402 = load %struct.Node*, %struct.Node** %4, align 8
  %403 = getelementptr inbounds %struct.Node, %struct.Node* %402, i32 0, i32 2
  %404 = load %struct.Type*, %struct.Type** %403, align 16
  %405 = getelementptr inbounds %struct.Type, %struct.Type* %404, i32 0, i32 3
  %406 = load i8, i8* %405, align 4
  %407 = trunc i8 %406 to i1
  br i1 %407, label %408, label %411

408:                                              ; preds = %401
  %409 = load i64, i64* %6, align 8
  %410 = trunc i64 %409 to i32
  br label %414

411:                                              ; preds = %401
  %412 = load i64, i64* %6, align 8
  %413 = trunc i64 %412 to i32
  br label %414

414:                                              ; preds = %411, %408
  %415 = phi i32 [ %410, %408 ], [ %413, %411 ]
  %416 = zext i32 %415 to i64
  store i64 %416, i64* %3, align 8
  br label %510

417:                                              ; preds = %359
  br label %418

418:                                              ; preds = %417, %349
  %419 = load i64, i64* %6, align 8
  store i64 %419, i64* %3, align 8
  br label %510

420:                                              ; preds = %16
  %421 = load %struct.Node*, %struct.Node** %4, align 8
  %422 = getelementptr inbounds %struct.Node, %struct.Node* %421, i32 0, i32 4
  %423 = load %struct.Node*, %struct.Node** %422, align 16
  %424 = load i8***, i8**** %5, align 8
  %425 = call i64 @eval_rval(%struct.Node* noundef %423, i8*** noundef %424)
  store i64 %425, i64* %3, align 8
  br label %510

426:                                              ; preds = %16
  %427 = load %struct.Node*, %struct.Node** %4, align 8
  %428 = getelementptr inbounds %struct.Node, %struct.Node* %427, i32 0, i32 20
  %429 = load i8***, i8**** %5, align 8
  store i8** %428, i8*** %429, align 8
  store i64 0, i64* %3, align 8
  br label %510

430:                                              ; preds = %16
  %431 = load i8***, i8**** %5, align 8
  %432 = icmp ne i8*** %431, null
  br i1 %432, label %437, label %433

433:                                              ; preds = %430
  %434 = load %struct.Node*, %struct.Node** %4, align 8
  %435 = getelementptr inbounds %struct.Node, %struct.Node* %434, i32 0, i32 3
  %436 = load %struct.Token*, %struct.Token** %435, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %436, i8* noundef getelementptr inbounds ([43 x i8], [43 x i8]* @.str.56, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

437:                                              ; preds = %430
  %438 = load %struct.Node*, %struct.Node** %4, align 8
  %439 = getelementptr inbounds %struct.Node, %struct.Node* %438, i32 0, i32 2
  %440 = load %struct.Type*, %struct.Type** %439, align 16
  %441 = getelementptr inbounds %struct.Type, %struct.Type* %440, i32 0, i32 0
  %442 = load i32, i32* %441, align 8
  %443 = icmp ne i32 %442, 12
  br i1 %443, label %444, label %448

444:                                              ; preds = %437
  %445 = load %struct.Node*, %struct.Node** %4, align 8
  %446 = getelementptr inbounds %struct.Node, %struct.Node* %445, i32 0, i32 3
  %447 = load %struct.Token*, %struct.Token** %446, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %447, i8* noundef getelementptr inbounds ([35 x i8], [35 x i8]* @.str.57, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

448:                                              ; preds = %437
  %449 = load %struct.Node*, %struct.Node** %4, align 8
  %450 = getelementptr inbounds %struct.Node, %struct.Node* %449, i32 0, i32 4
  %451 = load %struct.Node*, %struct.Node** %450, align 16
  %452 = load i8***, i8**** %5, align 8
  %453 = call i64 @eval_rval(%struct.Node* noundef %451, i8*** noundef %452)
  %454 = load %struct.Node*, %struct.Node** %4, align 8
  %455 = getelementptr inbounds %struct.Node, %struct.Node* %454, i32 0, i32 14
  %456 = load %struct.Member*, %struct.Member** %455, align 16
  %457 = getelementptr inbounds %struct.Member, %struct.Member* %456, i32 0, i32 6
  %458 = load i32, i32* %457, align 8
  %459 = sext i32 %458 to i64
  %460 = add nsw i64 %453, %459
  store i64 %460, i64* %3, align 8
  br label %510

461:                                              ; preds = %16
  %462 = load i8***, i8**** %5, align 8
  %463 = icmp ne i8*** %462, null
  br i1 %463, label %468, label %464

464:                                              ; preds = %461
  %465 = load %struct.Node*, %struct.Node** %4, align 8
  %466 = getelementptr inbounds %struct.Node, %struct.Node* %465, i32 0, i32 3
  %467 = load %struct.Token*, %struct.Token** %466, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %467, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.58, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

468:                                              ; preds = %461
  %469 = load %struct.Node*, %struct.Node** %4, align 8
  %470 = getelementptr inbounds %struct.Node, %struct.Node* %469, i32 0, i32 33
  %471 = load %struct.Obj*, %struct.Obj** %470, align 8
  %472 = getelementptr inbounds %struct.Obj, %struct.Obj* %471, i32 0, i32 3
  %473 = load %struct.Type*, %struct.Type** %472, align 8
  %474 = getelementptr inbounds %struct.Type, %struct.Type* %473, i32 0, i32 0
  %475 = load i32, i32* %474, align 8
  %476 = icmp ne i32 %475, 12
  br i1 %476, label %477, label %490

477:                                              ; preds = %468
  %478 = load %struct.Node*, %struct.Node** %4, align 8
  %479 = getelementptr inbounds %struct.Node, %struct.Node* %478, i32 0, i32 33
  %480 = load %struct.Obj*, %struct.Obj** %479, align 8
  %481 = getelementptr inbounds %struct.Obj, %struct.Obj* %480, i32 0, i32 3
  %482 = load %struct.Type*, %struct.Type** %481, align 8
  %483 = getelementptr inbounds %struct.Type, %struct.Type* %482, i32 0, i32 0
  %484 = load i32, i32* %483, align 8
  %485 = icmp ne i32 %484, 11
  br i1 %485, label %486, label %490

486:                                              ; preds = %477
  %487 = load %struct.Node*, %struct.Node** %4, align 8
  %488 = getelementptr inbounds %struct.Node, %struct.Node* %487, i32 0, i32 3
  %489 = load %struct.Token*, %struct.Token** %488, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %489, i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.59, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

490:                                              ; preds = %477, %468
  %491 = load %struct.Node*, %struct.Node** %4, align 8
  %492 = getelementptr inbounds %struct.Node, %struct.Node* %491, i32 0, i32 33
  %493 = load %struct.Obj*, %struct.Obj** %492, align 8
  %494 = getelementptr inbounds %struct.Obj, %struct.Obj* %493, i32 0, i32 1
  %495 = load i8***, i8**** %5, align 8
  store i8** %494, i8*** %495, align 8
  store i64 0, i64* %3, align 8
  br label %510

496:                                              ; preds = %16
  %497 = load %struct.Node*, %struct.Node** %4, align 8
  %498 = getelementptr inbounds %struct.Node, %struct.Node* %497, i32 0, i32 34
  %499 = load i64, i64* %498, align 16
  store i64 %499, i64* %3, align 8
  br label %510

500:                                              ; preds = %16
  %501 = load %struct.Node*, %struct.Node** %4, align 8
  %502 = getelementptr inbounds %struct.Node, %struct.Node* %501, i32 0, i32 4
  %503 = load %struct.Node*, %struct.Node** %502, align 16
  %504 = load i8***, i8**** %5, align 8
  %505 = call i64 @eval2(%struct.Node* noundef %503, i8*** noundef %504)
  store i64 %505, i64* %3, align 8
  br label %510

506:                                              ; preds = %16
  %507 = load %struct.Node*, %struct.Node** %4, align 8
  %508 = getelementptr inbounds %struct.Node, %struct.Node* %507, i32 0, i32 3
  %509 = load %struct.Token*, %struct.Token** %508, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %509, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.60, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

510:                                              ; preds = %500, %496, %490, %448, %426, %420, %418, %414, %398, %380, %345, %329, %311, %302, %296, %294, %264, %252, %231, %219, %198, %186, %176, %166, %142, %132, %122, %112, %102, %92, %79, %69, %59, %42, %31, %20, %12
  %511 = load i64, i64* %3, align 8
  ret i64 %511
}

declare zeroext i1 @is_flonum(%struct.Type* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal double @eval_double(%struct.Node* noundef %0) #0 {
  %2 = alloca double, align 8
  %3 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %3, align 8
  %4 = load %struct.Node*, %struct.Node** %3, align 8
  call void @add_type(%struct.Node* noundef %4)
  %5 = load %struct.Node*, %struct.Node** %3, align 8
  %6 = getelementptr inbounds %struct.Node, %struct.Node* %5, i32 0, i32 2
  %7 = load %struct.Type*, %struct.Type** %6, align 16
  %8 = call zeroext i1 @is_integer(%struct.Type* noundef %7)
  br i1 %8, label %9, label %24

9:                                                ; preds = %1
  %10 = load %struct.Node*, %struct.Node** %3, align 8
  %11 = getelementptr inbounds %struct.Node, %struct.Node* %10, i32 0, i32 2
  %12 = load %struct.Type*, %struct.Type** %11, align 16
  %13 = getelementptr inbounds %struct.Type, %struct.Type* %12, i32 0, i32 3
  %14 = load i8, i8* %13, align 4
  %15 = trunc i8 %14 to i1
  br i1 %15, label %16, label %20

16:                                               ; preds = %9
  %17 = load %struct.Node*, %struct.Node** %3, align 8
  %18 = call i64 @eval(%struct.Node* noundef %17)
  %19 = uitofp i64 %18 to double
  store double %19, double* %2, align 8
  br label %124

20:                                               ; preds = %9
  %21 = load %struct.Node*, %struct.Node** %3, align 8
  %22 = call i64 @eval(%struct.Node* noundef %21)
  %23 = sitofp i64 %22 to double
  store double %23, double* %2, align 8
  br label %124

24:                                               ; preds = %1
  %25 = load %struct.Node*, %struct.Node** %3, align 8
  %26 = getelementptr inbounds %struct.Node, %struct.Node* %25, i32 0, i32 0
  %27 = load i32, i32* %26, align 16
  switch i32 %27, label %120 [
    i32 1, label %28
    i32 2, label %38
    i32 3, label %48
    i32 4, label %58
    i32 5, label %68
    i32 17, label %74
    i32 18, label %92
    i32 43, label %97
    i32 42, label %115
  ]

28:                                               ; preds = %24
  %29 = load %struct.Node*, %struct.Node** %3, align 8
  %30 = getelementptr inbounds %struct.Node, %struct.Node* %29, i32 0, i32 4
  %31 = load %struct.Node*, %struct.Node** %30, align 16
  %32 = call double @eval_double(%struct.Node* noundef %31)
  %33 = load %struct.Node*, %struct.Node** %3, align 8
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 5
  %35 = load %struct.Node*, %struct.Node** %34, align 8
  %36 = call double @eval_double(%struct.Node* noundef %35)
  %37 = fadd double %32, %36
  store double %37, double* %2, align 8
  br label %124

38:                                               ; preds = %24
  %39 = load %struct.Node*, %struct.Node** %3, align 8
  %40 = getelementptr inbounds %struct.Node, %struct.Node* %39, i32 0, i32 4
  %41 = load %struct.Node*, %struct.Node** %40, align 16
  %42 = call double @eval_double(%struct.Node* noundef %41)
  %43 = load %struct.Node*, %struct.Node** %3, align 8
  %44 = getelementptr inbounds %struct.Node, %struct.Node* %43, i32 0, i32 5
  %45 = load %struct.Node*, %struct.Node** %44, align 8
  %46 = call double @eval_double(%struct.Node* noundef %45)
  %47 = fsub double %42, %46
  store double %47, double* %2, align 8
  br label %124

48:                                               ; preds = %24
  %49 = load %struct.Node*, %struct.Node** %3, align 8
  %50 = getelementptr inbounds %struct.Node, %struct.Node* %49, i32 0, i32 4
  %51 = load %struct.Node*, %struct.Node** %50, align 16
  %52 = call double @eval_double(%struct.Node* noundef %51)
  %53 = load %struct.Node*, %struct.Node** %3, align 8
  %54 = getelementptr inbounds %struct.Node, %struct.Node* %53, i32 0, i32 5
  %55 = load %struct.Node*, %struct.Node** %54, align 8
  %56 = call double @eval_double(%struct.Node* noundef %55)
  %57 = fmul double %52, %56
  store double %57, double* %2, align 8
  br label %124

58:                                               ; preds = %24
  %59 = load %struct.Node*, %struct.Node** %3, align 8
  %60 = getelementptr inbounds %struct.Node, %struct.Node* %59, i32 0, i32 4
  %61 = load %struct.Node*, %struct.Node** %60, align 16
  %62 = call double @eval_double(%struct.Node* noundef %61)
  %63 = load %struct.Node*, %struct.Node** %3, align 8
  %64 = getelementptr inbounds %struct.Node, %struct.Node* %63, i32 0, i32 5
  %65 = load %struct.Node*, %struct.Node** %64, align 8
  %66 = call double @eval_double(%struct.Node* noundef %65)
  %67 = fdiv double %62, %66
  store double %67, double* %2, align 8
  br label %124

68:                                               ; preds = %24
  %69 = load %struct.Node*, %struct.Node** %3, align 8
  %70 = getelementptr inbounds %struct.Node, %struct.Node* %69, i32 0, i32 4
  %71 = load %struct.Node*, %struct.Node** %70, align 16
  %72 = call double @eval_double(%struct.Node* noundef %71)
  %73 = fneg double %72
  store double %73, double* %2, align 8
  br label %124

74:                                               ; preds = %24
  %75 = load %struct.Node*, %struct.Node** %3, align 8
  %76 = getelementptr inbounds %struct.Node, %struct.Node* %75, i32 0, i32 6
  %77 = load %struct.Node*, %struct.Node** %76, align 16
  %78 = call double @eval_double(%struct.Node* noundef %77)
  %79 = fcmp une double %78, 0.000000e+00
  br i1 %79, label %80, label %85

80:                                               ; preds = %74
  %81 = load %struct.Node*, %struct.Node** %3, align 8
  %82 = getelementptr inbounds %struct.Node, %struct.Node* %81, i32 0, i32 7
  %83 = load %struct.Node*, %struct.Node** %82, align 8
  %84 = call double @eval_double(%struct.Node* noundef %83)
  br label %90

85:                                               ; preds = %74
  %86 = load %struct.Node*, %struct.Node** %3, align 8
  %87 = getelementptr inbounds %struct.Node, %struct.Node* %86, i32 0, i32 8
  %88 = load %struct.Node*, %struct.Node** %87, align 16
  %89 = call double @eval_double(%struct.Node* noundef %88)
  br label %90

90:                                               ; preds = %85, %80
  %91 = phi double [ %84, %80 ], [ %89, %85 ]
  store double %91, double* %2, align 8
  br label %124

92:                                               ; preds = %24
  %93 = load %struct.Node*, %struct.Node** %3, align 8
  %94 = getelementptr inbounds %struct.Node, %struct.Node* %93, i32 0, i32 5
  %95 = load %struct.Node*, %struct.Node** %94, align 8
  %96 = call double @eval_double(%struct.Node* noundef %95)
  store double %96, double* %2, align 8
  br label %124

97:                                               ; preds = %24
  %98 = load %struct.Node*, %struct.Node** %3, align 8
  %99 = getelementptr inbounds %struct.Node, %struct.Node* %98, i32 0, i32 4
  %100 = load %struct.Node*, %struct.Node** %99, align 16
  %101 = getelementptr inbounds %struct.Node, %struct.Node* %100, i32 0, i32 2
  %102 = load %struct.Type*, %struct.Type** %101, align 16
  %103 = call zeroext i1 @is_flonum(%struct.Type* noundef %102)
  br i1 %103, label %104, label %109

104:                                              ; preds = %97
  %105 = load %struct.Node*, %struct.Node** %3, align 8
  %106 = getelementptr inbounds %struct.Node, %struct.Node* %105, i32 0, i32 4
  %107 = load %struct.Node*, %struct.Node** %106, align 16
  %108 = call double @eval_double(%struct.Node* noundef %107)
  store double %108, double* %2, align 8
  br label %124

109:                                              ; preds = %97
  %110 = load %struct.Node*, %struct.Node** %3, align 8
  %111 = getelementptr inbounds %struct.Node, %struct.Node* %110, i32 0, i32 4
  %112 = load %struct.Node*, %struct.Node** %111, align 16
  %113 = call i64 @eval(%struct.Node* noundef %112)
  %114 = sitofp i64 %113 to double
  store double %114, double* %2, align 8
  br label %124

115:                                              ; preds = %24
  %116 = load %struct.Node*, %struct.Node** %3, align 8
  %117 = getelementptr inbounds %struct.Node, %struct.Node* %116, i32 0, i32 35
  %118 = load x86_fp80, x86_fp80* %117, align 16
  %119 = fptrunc x86_fp80 %118 to double
  store double %119, double* %2, align 8
  br label %124

120:                                              ; preds = %24
  %121 = load %struct.Node*, %struct.Node** %3, align 8
  %122 = getelementptr inbounds %struct.Node, %struct.Node* %121, i32 0, i32 3
  %123 = load %struct.Token*, %struct.Token** %122, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %123, i8* noundef getelementptr inbounds ([50 x i8], [50 x i8]* @.str.61, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

124:                                              ; preds = %115, %109, %104, %92, %90, %68, %58, %48, %38, %28, %20, %16
  %125 = load double, double* %2, align 8
  ret double %125
}

declare zeroext i1 @is_integer(%struct.Type* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal i64 @eval_rval(%struct.Node* noundef %0, i8*** noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca %struct.Node*, align 8
  %5 = alloca i8***, align 8
  store %struct.Node* %0, %struct.Node** %4, align 8
  store i8*** %1, i8**** %5, align 8
  %6 = load %struct.Node*, %struct.Node** %4, align 8
  %7 = getelementptr inbounds %struct.Node, %struct.Node* %6, i32 0, i32 0
  %8 = load i32, i32* %7, align 16
  switch i32 %8, label %45 [
    i32 40, label %9
    i32 21, label %26
    i32 19, label %32
  ]

9:                                                ; preds = %2
  %10 = load %struct.Node*, %struct.Node** %4, align 8
  %11 = getelementptr inbounds %struct.Node, %struct.Node* %10, i32 0, i32 33
  %12 = load %struct.Obj*, %struct.Obj** %11, align 8
  %13 = getelementptr inbounds %struct.Obj, %struct.Obj* %12, i32 0, i32 5
  %14 = load i8, i8* %13, align 8
  %15 = trunc i8 %14 to i1
  br i1 %15, label %16, label %20

16:                                               ; preds = %9
  %17 = load %struct.Node*, %struct.Node** %4, align 8
  %18 = getelementptr inbounds %struct.Node, %struct.Node* %17, i32 0, i32 3
  %19 = load %struct.Token*, %struct.Token** %18, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %19, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.62, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

20:                                               ; preds = %9
  %21 = load %struct.Node*, %struct.Node** %4, align 8
  %22 = getelementptr inbounds %struct.Node, %struct.Node* %21, i32 0, i32 33
  %23 = load %struct.Obj*, %struct.Obj** %22, align 8
  %24 = getelementptr inbounds %struct.Obj, %struct.Obj* %23, i32 0, i32 1
  %25 = load i8***, i8**** %5, align 8
  store i8** %24, i8*** %25, align 8
  store i64 0, i64* %3, align 8
  br label %49

26:                                               ; preds = %2
  %27 = load %struct.Node*, %struct.Node** %4, align 8
  %28 = getelementptr inbounds %struct.Node, %struct.Node* %27, i32 0, i32 4
  %29 = load %struct.Node*, %struct.Node** %28, align 16
  %30 = load i8***, i8**** %5, align 8
  %31 = call i64 @eval2(%struct.Node* noundef %29, i8*** noundef %30)
  store i64 %31, i64* %3, align 8
  br label %49

32:                                               ; preds = %2
  %33 = load %struct.Node*, %struct.Node** %4, align 8
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 4
  %35 = load %struct.Node*, %struct.Node** %34, align 16
  %36 = load i8***, i8**** %5, align 8
  %37 = call i64 @eval_rval(%struct.Node* noundef %35, i8*** noundef %36)
  %38 = load %struct.Node*, %struct.Node** %4, align 8
  %39 = getelementptr inbounds %struct.Node, %struct.Node* %38, i32 0, i32 14
  %40 = load %struct.Member*, %struct.Member** %39, align 16
  %41 = getelementptr inbounds %struct.Member, %struct.Member* %40, i32 0, i32 6
  %42 = load i32, i32* %41, align 8
  %43 = sext i32 %42 to i64
  %44 = add nsw i64 %37, %43
  store i64 %44, i64* %3, align 8
  br label %49

45:                                               ; preds = %2
  %46 = load %struct.Node*, %struct.Node** %4, align 8
  %47 = getelementptr inbounds %struct.Node, %struct.Node* %46, i32 0, i32 3
  %48 = load %struct.Token*, %struct.Token** %47, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %48, i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.63, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

49:                                               ; preds = %32, %26, %20
  %50 = load i64, i64* %3, align 8
  ret i64 %50
}

; Function Attrs: noreturn
declare void @error_tok(%struct.Token* noundef, i8* noundef, ...) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @logor(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @logand(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %12, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  %11 = call zeroext i1 @equal(%struct.Token* noundef %10, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.67, i64 0, i64 0))
  br i1 %11, label %12, label %21

12:                                               ; preds = %9
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %13, %struct.Token** %6, align 8
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @logand(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 25, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9, !llvm.loop !18

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %22, %struct.Token** %23, align 8
  %24 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %24
}

declare zeroext i1 @equal(%struct.Token* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Obj* @new_lvar(i8* noundef %0, %struct.Type* noundef %1, i8* noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca %struct.Type*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca %struct.Obj*, align 8
  store i8* %0, i8** %4, align 8
  store %struct.Type* %1, %struct.Type** %5, align 8
  store i8* %2, i8** %6, align 8
  %8 = load i8*, i8** %4, align 8
  %9 = load %struct.Type*, %struct.Type** %5, align 8
  %10 = call %struct.Obj* @new_var(i8* noundef %8, %struct.Type* noundef %9)
  store %struct.Obj* %10, %struct.Obj** %7, align 8
  %11 = load %struct.Obj*, %struct.Obj** %7, align 8
  %12 = getelementptr inbounds %struct.Obj, %struct.Obj* %11, i32 0, i32 5
  store i8 1, i8* %12, align 8
  %13 = load %struct.Obj*, %struct.Obj** @locals, align 8
  %14 = load %struct.Obj*, %struct.Obj** %7, align 8
  %15 = getelementptr inbounds %struct.Obj, %struct.Obj* %14, i32 0, i32 0
  store %struct.Obj* %13, %struct.Obj** %15, align 8
  %16 = load i32, i32* @order, align 4
  %17 = load %struct.Obj*, %struct.Obj** %7, align 8
  %18 = getelementptr inbounds %struct.Obj, %struct.Obj* %17, i32 0, i32 8
  store i32 %16, i32* %18, align 4
  %19 = load i8*, i8** %6, align 8
  %20 = load %struct.Obj*, %struct.Obj** %7, align 8
  %21 = getelementptr inbounds %struct.Obj, %struct.Obj* %20, i32 0, i32 2
  store i8* %19, i8** %21, align 8
  %22 = load %struct.Obj*, %struct.Obj** %7, align 8
  store %struct.Obj* %22, %struct.Obj** @locals, align 8
  %23 = load %struct.Obj*, %struct.Obj** %7, align 8
  ret %struct.Obj* %23
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_binary(i32 noundef %0, %struct.Node* noundef %1, %struct.Node* noundef %2, %struct.Token* noundef %3) #0 {
  %5 = alloca i32, align 4
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Token*, align 8
  %9 = alloca %struct.Node*, align 8
  store i32 %0, i32* %5, align 4
  store %struct.Node* %1, %struct.Node** %6, align 8
  store %struct.Node* %2, %struct.Node** %7, align 8
  store %struct.Token* %3, %struct.Token** %8, align 8
  %10 = load i32, i32* %5, align 4
  %11 = load %struct.Token*, %struct.Token** %8, align 8
  %12 = call %struct.Node* @new_node(i32 noundef %10, %struct.Token* noundef %11)
  store %struct.Node* %12, %struct.Node** %9, align 8
  %13 = load i8, i8* @isDotfile, align 1
  %14 = trunc i8 %13 to i1
  br i1 %14, label %15, label %51

15:                                               ; preds = %4
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %17 = icmp ne %struct._IO_FILE* %16, null
  br i1 %17, label %18, label %51

18:                                               ; preds = %15
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %20 = load %struct.Node*, %struct.Node** %9, align 8
  %21 = getelementptr inbounds %struct.Node, %struct.Node* %20, i32 0, i32 0
  %22 = load i32, i32* %21, align 16
  %23 = call i8* @nodekind2str(i32 noundef %22)
  %24 = load %struct.Node*, %struct.Node** %9, align 8
  %25 = getelementptr inbounds %struct.Node, %struct.Node* %24, i32 0, i32 36
  %26 = load i32, i32* %25, align 16
  %27 = load %struct.Node*, %struct.Node** %7, align 8
  %28 = getelementptr inbounds %struct.Node, %struct.Node* %27, i32 0, i32 0
  %29 = load i32, i32* %28, align 16
  %30 = call i8* @nodekind2str(i32 noundef %29)
  %31 = load %struct.Node*, %struct.Node** %7, align 8
  %32 = getelementptr inbounds %struct.Node, %struct.Node* %31, i32 0, i32 36
  %33 = load i32, i32* %32, align 16
  %34 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %19, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %23, i32 noundef %26, i8* noundef %30, i32 noundef %33)
  %35 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %36 = load %struct.Node*, %struct.Node** %9, align 8
  %37 = getelementptr inbounds %struct.Node, %struct.Node* %36, i32 0, i32 0
  %38 = load i32, i32* %37, align 16
  %39 = call i8* @nodekind2str(i32 noundef %38)
  %40 = load %struct.Node*, %struct.Node** %9, align 8
  %41 = getelementptr inbounds %struct.Node, %struct.Node* %40, i32 0, i32 36
  %42 = load i32, i32* %41, align 16
  %43 = load %struct.Node*, %struct.Node** %6, align 8
  %44 = getelementptr inbounds %struct.Node, %struct.Node* %43, i32 0, i32 0
  %45 = load i32, i32* %44, align 16
  %46 = call i8* @nodekind2str(i32 noundef %45)
  %47 = load %struct.Node*, %struct.Node** %6, align 8
  %48 = getelementptr inbounds %struct.Node, %struct.Node* %47, i32 0, i32 36
  %49 = load i32, i32* %48, align 16
  %50 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %35, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %39, i32 noundef %42, i8* noundef %46, i32 noundef %49)
  br label %51

51:                                               ; preds = %18, %15, %4
  %52 = load %struct.Node*, %struct.Node** %6, align 8
  %53 = load %struct.Node*, %struct.Node** %9, align 8
  %54 = getelementptr inbounds %struct.Node, %struct.Node* %53, i32 0, i32 4
  store %struct.Node* %52, %struct.Node** %54, align 16
  %55 = load %struct.Node*, %struct.Node** %7, align 8
  %56 = load %struct.Node*, %struct.Node** %9, align 8
  %57 = getelementptr inbounds %struct.Node, %struct.Node* %56, i32 0, i32 5
  store %struct.Node* %55, %struct.Node** %57, align 8
  %58 = load %struct.Node*, %struct.Node** %9, align 8
  %59 = getelementptr inbounds %struct.Node, %struct.Node* %58, i32 0, i32 5
  %60 = load %struct.Node*, %struct.Node** %59, align 8
  call void @add_type(%struct.Node* noundef %60)
  %61 = load i32, i32* %5, align 4
  %62 = icmp eq i32 %61, 16
  br i1 %62, label %63, label %78

63:                                               ; preds = %51
  %64 = load %struct.Node*, %struct.Node** %9, align 8
  %65 = getelementptr inbounds %struct.Node, %struct.Node* %64, i32 0, i32 5
  %66 = load %struct.Node*, %struct.Node** %65, align 8
  %67 = getelementptr inbounds %struct.Node, %struct.Node* %66, i32 0, i32 2
  %68 = load %struct.Type*, %struct.Type** %67, align 16
  %69 = getelementptr inbounds %struct.Type, %struct.Type* %68, i32 0, i32 0
  %70 = load i32, i32* %69, align 8
  %71 = icmp eq i32 %70, 0
  br i1 %71, label %72, label %78

72:                                               ; preds = %63
  %73 = load %struct.Node*, %struct.Node** %9, align 8
  %74 = getelementptr inbounds %struct.Node, %struct.Node* %73, i32 0, i32 5
  %75 = load %struct.Node*, %struct.Node** %74, align 8
  %76 = getelementptr inbounds %struct.Node, %struct.Node* %75, i32 0, i32 3
  %77 = load %struct.Token*, %struct.Token** %76, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %77, i8* noundef getelementptr inbounds ([55 x i8], [55 x i8]* @.str.216, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

78:                                               ; preds = %63, %51
  %79 = load %struct.Node*, %struct.Node** %9, align 8
  ret %struct.Node* %79
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_var_node(%struct.Obj* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Obj*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  store %struct.Obj* %0, %struct.Obj** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load %struct.Token*, %struct.Token** %4, align 8
  %7 = call %struct.Node* @new_node(i32 noundef 40, %struct.Token* noundef %6)
  store %struct.Node* %7, %struct.Node** %5, align 8
  %8 = load %struct.Obj*, %struct.Obj** %3, align 8
  %9 = load %struct.Node*, %struct.Node** %5, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 33
  store %struct.Obj* %8, %struct.Obj** %10, align 8
  %11 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %11
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_node(i32 noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  store i32 %0, i32* %3, align 4
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 320) #8
  %7 = bitcast i8* %6 to %struct.Node*
  store %struct.Node* %7, %struct.Node** %5, align 8
  %8 = load %struct.Node*, %struct.Node** %5, align 8
  %9 = icmp eq %struct.Node* %8, null
  br i1 %9, label %10, label %11

10:                                               ; preds = %2
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.217, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

11:                                               ; preds = %2
  %12 = load i32, i32* %3, align 4
  %13 = load %struct.Node*, %struct.Node** %5, align 8
  %14 = getelementptr inbounds %struct.Node, %struct.Node* %13, i32 0, i32 0
  store i32 %12, i32* %14, align 16
  %15 = load i32, i32* @new_node.count, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, i32* @new_node.count, align 4
  %17 = load %struct.Node*, %struct.Node** %5, align 8
  %18 = getelementptr inbounds %struct.Node, %struct.Node* %17, i32 0, i32 36
  store i32 %15, i32* %18, align 16
  %19 = load %struct.Token*, %struct.Token** %4, align 8
  %20 = load %struct.Node*, %struct.Node** %5, align 8
  %21 = getelementptr inbounds %struct.Node, %struct.Node* %20, i32 0, i32 3
  store %struct.Token* %19, %struct.Token** %21, align 8
  %22 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %22
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @expr(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %7 = load %struct.Token*, %struct.Token** %5, align 8
  %8 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %6, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = call zeroext i1 @equal(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %10, label %11, label %20

11:                                               ; preds = %2
  %12 = load %struct.Node*, %struct.Node** %6, align 8
  %13 = load %struct.Token**, %struct.Token*** %4, align 8
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 1
  %16 = load %struct.Token*, %struct.Token** %15, align 8
  %17 = call %struct.Node* @expr(%struct.Token** noundef %13, %struct.Token* noundef %16)
  %18 = load %struct.Token*, %struct.Token** %5, align 8
  %19 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %12, %struct.Node* noundef %17, %struct.Token* noundef %18)
  store %struct.Node* %19, %struct.Node** %3, align 8
  br label %24

20:                                               ; preds = %2
  %21 = load %struct.Token*, %struct.Token** %5, align 8
  %22 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %21, %struct.Token** %22, align 8
  %23 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %23, %struct.Node** %3, align 8
  br label %24

24:                                               ; preds = %20, %11
  %25 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %25
}

declare %struct.Token* @skip(%struct.Token* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @logand(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @bitor(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %12, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  %11 = call zeroext i1 @equal(%struct.Token* noundef %10, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0))
  br i1 %11, label %12, label %21

12:                                               ; preds = %9
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %13, %struct.Token** %6, align 8
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @bitor(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 24, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9, !llvm.loop !19

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %22, %struct.Token** %23, align 8
  %24 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %24
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @bitor(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @bitxor(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %12, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  %11 = call zeroext i1 @equal(%struct.Token* noundef %10, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.69, i64 0, i64 0))
  br i1 %11, label %12, label %21

12:                                               ; preds = %9
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %13, %struct.Token** %6, align 8
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @bitxor(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 8, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9, !llvm.loop !20

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %22, %struct.Token** %23, align 8
  %24 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %24
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @bitxor(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @bitand(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %12, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  %11 = call zeroext i1 @equal(%struct.Token* noundef %10, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.70, i64 0, i64 0))
  br i1 %11, label %12, label %21

12:                                               ; preds = %9
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %13, %struct.Token** %6, align 8
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @bitand(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 9, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9, !llvm.loop !21

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %22, %struct.Token** %23, align 8
  %24 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %24
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @bitand(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @equality(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %12, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  %11 = call zeroext i1 @equal(%struct.Token* noundef %10, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.71, i64 0, i64 0))
  br i1 %11, label %12, label %21

12:                                               ; preds = %9
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %13, %struct.Token** %6, align 8
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @equality(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 7, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9, !llvm.loop !22

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %22, %struct.Token** %23, align 8
  %24 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %24
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @equality(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @relational(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %24, %13, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %10, %struct.Token** %6, align 8
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  %12 = call zeroext i1 @equal(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.72, i64 0, i64 0))
  br i1 %12, label %13, label %21

13:                                               ; preds = %9
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @relational(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 12, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.73, i64 0, i64 0))
  br i1 %23, label %24, label %32

24:                                               ; preds = %21
  %25 = load %struct.Node*, %struct.Node** %5, align 8
  %26 = load %struct.Token*, %struct.Token** %4, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  %29 = call %struct.Node* @relational(%struct.Token** noundef %4, %struct.Token* noundef %28)
  %30 = load %struct.Token*, %struct.Token** %6, align 8
  %31 = call %struct.Node* @new_binary(i32 noundef 13, %struct.Node* noundef %25, %struct.Node* noundef %29, %struct.Token* noundef %30)
  store %struct.Node* %31, %struct.Node** %5, align 8
  br label %9

32:                                               ; preds = %21
  %33 = load %struct.Token*, %struct.Token** %4, align 8
  %34 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %33, %struct.Token** %34, align 8
  %35 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %35
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @relational(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @shift(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %46, %35, %24, %13, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %10, %struct.Token** %6, align 8
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  %12 = call zeroext i1 @equal(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.74, i64 0, i64 0))
  br i1 %12, label %13, label %21

13:                                               ; preds = %9
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @shift(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 14, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.75, i64 0, i64 0))
  br i1 %23, label %24, label %32

24:                                               ; preds = %21
  %25 = load %struct.Node*, %struct.Node** %5, align 8
  %26 = load %struct.Token*, %struct.Token** %4, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  %29 = call %struct.Node* @shift(%struct.Token** noundef %4, %struct.Token* noundef %28)
  %30 = load %struct.Token*, %struct.Token** %6, align 8
  %31 = call %struct.Node* @new_binary(i32 noundef 15, %struct.Node* noundef %25, %struct.Node* noundef %29, %struct.Token* noundef %30)
  store %struct.Node* %31, %struct.Node** %5, align 8
  br label %9

32:                                               ; preds = %21
  %33 = load %struct.Token*, %struct.Token** %4, align 8
  %34 = call zeroext i1 @equal(%struct.Token* noundef %33, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.76, i64 0, i64 0))
  br i1 %34, label %35, label %43

35:                                               ; preds = %32
  %36 = load %struct.Token*, %struct.Token** %4, align 8
  %37 = getelementptr inbounds %struct.Token, %struct.Token* %36, i32 0, i32 1
  %38 = load %struct.Token*, %struct.Token** %37, align 8
  %39 = call %struct.Node* @shift(%struct.Token** noundef %4, %struct.Token* noundef %38)
  %40 = load %struct.Node*, %struct.Node** %5, align 8
  %41 = load %struct.Token*, %struct.Token** %6, align 8
  %42 = call %struct.Node* @new_binary(i32 noundef 14, %struct.Node* noundef %39, %struct.Node* noundef %40, %struct.Token* noundef %41)
  store %struct.Node* %42, %struct.Node** %5, align 8
  br label %9

43:                                               ; preds = %32
  %44 = load %struct.Token*, %struct.Token** %4, align 8
  %45 = call zeroext i1 @equal(%struct.Token* noundef %44, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.77, i64 0, i64 0))
  br i1 %45, label %46, label %54

46:                                               ; preds = %43
  %47 = load %struct.Token*, %struct.Token** %4, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 1
  %49 = load %struct.Token*, %struct.Token** %48, align 8
  %50 = call %struct.Node* @shift(%struct.Token** noundef %4, %struct.Token* noundef %49)
  %51 = load %struct.Node*, %struct.Node** %5, align 8
  %52 = load %struct.Token*, %struct.Token** %6, align 8
  %53 = call %struct.Node* @new_binary(i32 noundef 15, %struct.Node* noundef %50, %struct.Node* noundef %51, %struct.Token* noundef %52)
  store %struct.Node* %53, %struct.Node** %5, align 8
  br label %9

54:                                               ; preds = %43
  %55 = load %struct.Token*, %struct.Token** %4, align 8
  %56 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %55, %struct.Token** %56, align 8
  %57 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %57
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @shift(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @add(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %24, %13, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %10, %struct.Token** %6, align 8
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  %12 = call zeroext i1 @equal(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.78, i64 0, i64 0))
  br i1 %12, label %13, label %21

13:                                               ; preds = %9
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @add(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 10, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.79, i64 0, i64 0))
  br i1 %23, label %24, label %32

24:                                               ; preds = %21
  %25 = load %struct.Node*, %struct.Node** %5, align 8
  %26 = load %struct.Token*, %struct.Token** %4, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  %29 = call %struct.Node* @add(%struct.Token** noundef %4, %struct.Token* noundef %28)
  %30 = load %struct.Token*, %struct.Token** %6, align 8
  %31 = call %struct.Node* @new_binary(i32 noundef 11, %struct.Node* noundef %25, %struct.Node* noundef %29, %struct.Token* noundef %30)
  store %struct.Node* %31, %struct.Node** %5, align 8
  br label %9

32:                                               ; preds = %21
  %33 = load %struct.Token*, %struct.Token** %4, align 8
  %34 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %33, %struct.Token** %34, align 8
  %35 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %35
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @add(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @mul(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %24, %13, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %10, %struct.Token** %6, align 8
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  %12 = call zeroext i1 @equal(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.80, i64 0, i64 0))
  br i1 %12, label %13, label %21

13:                                               ; preds = %9
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @mul(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_add(%struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.81, i64 0, i64 0))
  br i1 %23, label %24, label %32

24:                                               ; preds = %21
  %25 = load %struct.Node*, %struct.Node** %5, align 8
  %26 = load %struct.Token*, %struct.Token** %4, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  %29 = call %struct.Node* @mul(%struct.Token** noundef %4, %struct.Token* noundef %28)
  %30 = load %struct.Token*, %struct.Token** %6, align 8
  %31 = call %struct.Node* @new_sub(%struct.Node* noundef %25, %struct.Node* noundef %29, %struct.Token* noundef %30)
  store %struct.Node* %31, %struct.Node** %5, align 8
  br label %9

32:                                               ; preds = %21
  %33 = load %struct.Token*, %struct.Token** %4, align 8
  %34 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %33, %struct.Token** %34, align 8
  %35 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %35
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @mul(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Node* @cast(%struct.Token** noundef %4, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %5, align 8
  br label %9

9:                                                ; preds = %35, %24, %13, %2
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %10, %struct.Token** %6, align 8
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  %12 = call zeroext i1 @equal(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.82, i64 0, i64 0))
  br i1 %12, label %13, label %21

13:                                               ; preds = %9
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = getelementptr inbounds %struct.Token, %struct.Token* %15, i32 0, i32 1
  %17 = load %struct.Token*, %struct.Token** %16, align 8
  %18 = call %struct.Node* @cast(%struct.Token** noundef %4, %struct.Token* noundef %17)
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call %struct.Node* @new_binary(i32 noundef 3, %struct.Node* noundef %14, %struct.Node* noundef %18, %struct.Token* noundef %19)
  store %struct.Node* %20, %struct.Node** %5, align 8
  br label %9

21:                                               ; preds = %9
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.83, i64 0, i64 0))
  br i1 %23, label %24, label %32

24:                                               ; preds = %21
  %25 = load %struct.Node*, %struct.Node** %5, align 8
  %26 = load %struct.Token*, %struct.Token** %4, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  %29 = call %struct.Node* @cast(%struct.Token** noundef %4, %struct.Token* noundef %28)
  %30 = load %struct.Token*, %struct.Token** %6, align 8
  %31 = call %struct.Node* @new_binary(i32 noundef 4, %struct.Node* noundef %25, %struct.Node* noundef %29, %struct.Token* noundef %30)
  store %struct.Node* %31, %struct.Node** %5, align 8
  br label %9

32:                                               ; preds = %21
  %33 = load %struct.Token*, %struct.Token** %4, align 8
  %34 = call zeroext i1 @equal(%struct.Token* noundef %33, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.84, i64 0, i64 0))
  br i1 %34, label %35, label %43

35:                                               ; preds = %32
  %36 = load %struct.Node*, %struct.Node** %5, align 8
  %37 = load %struct.Token*, %struct.Token** %4, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 1
  %39 = load %struct.Token*, %struct.Token** %38, align 8
  %40 = call %struct.Node* @cast(%struct.Token** noundef %4, %struct.Token* noundef %39)
  %41 = load %struct.Token*, %struct.Token** %6, align 8
  %42 = call %struct.Node* @new_binary(i32 noundef 6, %struct.Node* noundef %36, %struct.Node* noundef %40, %struct.Token* noundef %41)
  store %struct.Node* %42, %struct.Node** %5, align 8
  br label %9

43:                                               ; preds = %32
  %44 = load %struct.Token*, %struct.Token** %4, align 8
  %45 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %44, %struct.Token** %45, align 8
  %46 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %46
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_add(%struct.Node* noundef %0, %struct.Node* noundef %1, %struct.Token* noundef %2) #0 {
  %4 = alloca %struct.Node*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %5, align 8
  store %struct.Node* %1, %struct.Node** %6, align 8
  store %struct.Token* %2, %struct.Token** %7, align 8
  %9 = load %struct.Node*, %struct.Node** %5, align 8
  call void @add_type(%struct.Node* noundef %9)
  %10 = load %struct.Node*, %struct.Node** %6, align 8
  call void @add_type(%struct.Node* noundef %10)
  %11 = load %struct.Node*, %struct.Node** %5, align 8
  %12 = getelementptr inbounds %struct.Node, %struct.Node* %11, i32 0, i32 2
  %13 = load %struct.Type*, %struct.Type** %12, align 16
  %14 = call zeroext i1 @is_numeric(%struct.Type* noundef %13)
  br i1 %14, label %15, label %25

15:                                               ; preds = %3
  %16 = load %struct.Node*, %struct.Node** %6, align 8
  %17 = getelementptr inbounds %struct.Node, %struct.Node* %16, i32 0, i32 2
  %18 = load %struct.Type*, %struct.Type** %17, align 16
  %19 = call zeroext i1 @is_numeric(%struct.Type* noundef %18)
  br i1 %19, label %20, label %25

20:                                               ; preds = %15
  %21 = load %struct.Node*, %struct.Node** %5, align 8
  %22 = load %struct.Node*, %struct.Node** %6, align 8
  %23 = load %struct.Token*, %struct.Token** %7, align 8
  %24 = call %struct.Node* @new_binary(i32 noundef 1, %struct.Node* noundef %21, %struct.Node* noundef %22, %struct.Token* noundef %23)
  store %struct.Node* %24, %struct.Node** %4, align 8
  br label %117

25:                                               ; preds = %15, %3
  %26 = load %struct.Node*, %struct.Node** %5, align 8
  %27 = getelementptr inbounds %struct.Node, %struct.Node* %26, i32 0, i32 2
  %28 = load %struct.Type*, %struct.Type** %27, align 16
  %29 = getelementptr inbounds %struct.Type, %struct.Type* %28, i32 0, i32 8
  %30 = load %struct.Type*, %struct.Type** %29, align 8
  %31 = icmp eq %struct.Type* %30, null
  br i1 %31, label %32, label %39

32:                                               ; preds = %25
  %33 = load %struct.Node*, %struct.Node** %6, align 8
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 2
  %35 = load %struct.Type*, %struct.Type** %34, align 16
  %36 = getelementptr inbounds %struct.Type, %struct.Type* %35, i32 0, i32 8
  %37 = load %struct.Type*, %struct.Type** %36, align 8
  %38 = icmp eq %struct.Type* %37, null
  br i1 %38, label %53, label %39

39:                                               ; preds = %32, %25
  %40 = load %struct.Node*, %struct.Node** %5, align 8
  %41 = getelementptr inbounds %struct.Node, %struct.Node* %40, i32 0, i32 2
  %42 = load %struct.Type*, %struct.Type** %41, align 16
  %43 = getelementptr inbounds %struct.Type, %struct.Type* %42, i32 0, i32 8
  %44 = load %struct.Type*, %struct.Type** %43, align 8
  %45 = icmp ne %struct.Type* %44, null
  br i1 %45, label %46, label %55

46:                                               ; preds = %39
  %47 = load %struct.Node*, %struct.Node** %6, align 8
  %48 = getelementptr inbounds %struct.Node, %struct.Node* %47, i32 0, i32 2
  %49 = load %struct.Type*, %struct.Type** %48, align 16
  %50 = getelementptr inbounds %struct.Type, %struct.Type* %49, i32 0, i32 8
  %51 = load %struct.Type*, %struct.Type** %50, align 8
  %52 = icmp ne %struct.Type* %51, null
  br i1 %52, label %53, label %55

53:                                               ; preds = %46, %32
  %54 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %54, i8* noundef getelementptr inbounds ([34 x i8], [34 x i8]* @.str.214, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

55:                                               ; preds = %46, %39
  %56 = load %struct.Node*, %struct.Node** %5, align 8
  %57 = getelementptr inbounds %struct.Node, %struct.Node* %56, i32 0, i32 2
  %58 = load %struct.Type*, %struct.Type** %57, align 16
  %59 = getelementptr inbounds %struct.Type, %struct.Type* %58, i32 0, i32 8
  %60 = load %struct.Type*, %struct.Type** %59, align 8
  %61 = icmp ne %struct.Type* %60, null
  br i1 %61, label %73, label %62

62:                                               ; preds = %55
  %63 = load %struct.Node*, %struct.Node** %6, align 8
  %64 = getelementptr inbounds %struct.Node, %struct.Node* %63, i32 0, i32 2
  %65 = load %struct.Type*, %struct.Type** %64, align 16
  %66 = getelementptr inbounds %struct.Type, %struct.Type* %65, i32 0, i32 8
  %67 = load %struct.Type*, %struct.Type** %66, align 8
  %68 = icmp ne %struct.Type* %67, null
  br i1 %68, label %69, label %73

69:                                               ; preds = %62
  %70 = load %struct.Node*, %struct.Node** %5, align 8
  store %struct.Node* %70, %struct.Node** %8, align 8
  %71 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %71, %struct.Node** %5, align 8
  %72 = load %struct.Node*, %struct.Node** %8, align 8
  store %struct.Node* %72, %struct.Node** %6, align 8
  br label %73

73:                                               ; preds = %69, %62, %55
  %74 = load %struct.Node*, %struct.Node** %5, align 8
  %75 = getelementptr inbounds %struct.Node, %struct.Node* %74, i32 0, i32 2
  %76 = load %struct.Type*, %struct.Type** %75, align 16
  %77 = getelementptr inbounds %struct.Type, %struct.Type* %76, i32 0, i32 8
  %78 = load %struct.Type*, %struct.Type** %77, align 8
  %79 = getelementptr inbounds %struct.Type, %struct.Type* %78, i32 0, i32 0
  %80 = load i32, i32* %79, align 8
  %81 = icmp eq i32 %80, 13
  br i1 %81, label %82, label %99

82:                                               ; preds = %73
  %83 = load %struct.Node*, %struct.Node** %6, align 8
  %84 = load %struct.Node*, %struct.Node** %5, align 8
  %85 = getelementptr inbounds %struct.Node, %struct.Node* %84, i32 0, i32 2
  %86 = load %struct.Type*, %struct.Type** %85, align 16
  %87 = getelementptr inbounds %struct.Type, %struct.Type* %86, i32 0, i32 8
  %88 = load %struct.Type*, %struct.Type** %87, align 8
  %89 = getelementptr inbounds %struct.Type, %struct.Type* %88, i32 0, i32 13
  %90 = load %struct.Obj*, %struct.Obj** %89, align 8
  %91 = load %struct.Token*, %struct.Token** %7, align 8
  %92 = call %struct.Node* @new_var_node(%struct.Obj* noundef %90, %struct.Token* noundef %91)
  %93 = load %struct.Token*, %struct.Token** %7, align 8
  %94 = call %struct.Node* @new_binary(i32 noundef 3, %struct.Node* noundef %83, %struct.Node* noundef %92, %struct.Token* noundef %93)
  store %struct.Node* %94, %struct.Node** %6, align 8
  %95 = load %struct.Node*, %struct.Node** %5, align 8
  %96 = load %struct.Node*, %struct.Node** %6, align 8
  %97 = load %struct.Token*, %struct.Token** %7, align 8
  %98 = call %struct.Node* @new_binary(i32 noundef 1, %struct.Node* noundef %95, %struct.Node* noundef %96, %struct.Token* noundef %97)
  store %struct.Node* %98, %struct.Node** %4, align 8
  br label %117

99:                                               ; preds = %73
  %100 = load %struct.Node*, %struct.Node** %6, align 8
  %101 = load %struct.Node*, %struct.Node** %5, align 8
  %102 = getelementptr inbounds %struct.Node, %struct.Node* %101, i32 0, i32 2
  %103 = load %struct.Type*, %struct.Type** %102, align 16
  %104 = getelementptr inbounds %struct.Type, %struct.Type* %103, i32 0, i32 8
  %105 = load %struct.Type*, %struct.Type** %104, align 8
  %106 = getelementptr inbounds %struct.Type, %struct.Type* %105, i32 0, i32 1
  %107 = load i32, i32* %106, align 4
  %108 = sext i32 %107 to i64
  %109 = load %struct.Token*, %struct.Token** %7, align 8
  %110 = call %struct.Node* @new_long(i64 noundef %108, %struct.Token* noundef %109)
  %111 = load %struct.Token*, %struct.Token** %7, align 8
  %112 = call %struct.Node* @new_binary(i32 noundef 3, %struct.Node* noundef %100, %struct.Node* noundef %110, %struct.Token* noundef %111)
  store %struct.Node* %112, %struct.Node** %6, align 8
  %113 = load %struct.Node*, %struct.Node** %5, align 8
  %114 = load %struct.Node*, %struct.Node** %6, align 8
  %115 = load %struct.Token*, %struct.Token** %7, align 8
  %116 = call %struct.Node* @new_binary(i32 noundef 1, %struct.Node* noundef %113, %struct.Node* noundef %114, %struct.Token* noundef %115)
  store %struct.Node* %116, %struct.Node** %4, align 8
  br label %117

117:                                              ; preds = %99, %82, %20
  %118 = load %struct.Node*, %struct.Node** %4, align 8
  ret %struct.Node* %118
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_sub(%struct.Node* noundef %0, %struct.Node* noundef %1, %struct.Token* noundef %2) #0 {
  %4 = alloca %struct.Node*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca %struct.Node*, align 8
  %9 = alloca %struct.Node*, align 8
  %10 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %5, align 8
  store %struct.Node* %1, %struct.Node** %6, align 8
  store %struct.Token* %2, %struct.Token** %7, align 8
  %11 = load %struct.Node*, %struct.Node** %5, align 8
  call void @add_type(%struct.Node* noundef %11)
  %12 = load %struct.Node*, %struct.Node** %6, align 8
  call void @add_type(%struct.Node* noundef %12)
  %13 = load %struct.Node*, %struct.Node** %5, align 8
  %14 = getelementptr inbounds %struct.Node, %struct.Node* %13, i32 0, i32 2
  %15 = load %struct.Type*, %struct.Type** %14, align 16
  %16 = call zeroext i1 @is_numeric(%struct.Type* noundef %15)
  br i1 %16, label %17, label %27

17:                                               ; preds = %3
  %18 = load %struct.Node*, %struct.Node** %6, align 8
  %19 = getelementptr inbounds %struct.Node, %struct.Node* %18, i32 0, i32 2
  %20 = load %struct.Type*, %struct.Type** %19, align 16
  %21 = call zeroext i1 @is_numeric(%struct.Type* noundef %20)
  br i1 %21, label %22, label %27

22:                                               ; preds = %17
  %23 = load %struct.Node*, %struct.Node** %5, align 8
  %24 = load %struct.Node*, %struct.Node** %6, align 8
  %25 = load %struct.Token*, %struct.Token** %7, align 8
  %26 = call %struct.Node* @new_binary(i32 noundef 2, %struct.Node* noundef %23, %struct.Node* noundef %24, %struct.Token* noundef %25)
  store %struct.Node* %26, %struct.Node** %4, align 8
  br label %134

27:                                               ; preds = %17, %3
  %28 = load %struct.Node*, %struct.Node** %5, align 8
  %29 = getelementptr inbounds %struct.Node, %struct.Node* %28, i32 0, i32 2
  %30 = load %struct.Type*, %struct.Type** %29, align 16
  %31 = getelementptr inbounds %struct.Type, %struct.Type* %30, i32 0, i32 8
  %32 = load %struct.Type*, %struct.Type** %31, align 8
  %33 = getelementptr inbounds %struct.Type, %struct.Type* %32, i32 0, i32 0
  %34 = load i32, i32* %33, align 8
  %35 = icmp eq i32 %34, 13
  br i1 %35, label %36, label %60

36:                                               ; preds = %27
  %37 = load %struct.Node*, %struct.Node** %6, align 8
  %38 = load %struct.Node*, %struct.Node** %5, align 8
  %39 = getelementptr inbounds %struct.Node, %struct.Node* %38, i32 0, i32 2
  %40 = load %struct.Type*, %struct.Type** %39, align 16
  %41 = getelementptr inbounds %struct.Type, %struct.Type* %40, i32 0, i32 8
  %42 = load %struct.Type*, %struct.Type** %41, align 8
  %43 = getelementptr inbounds %struct.Type, %struct.Type* %42, i32 0, i32 13
  %44 = load %struct.Obj*, %struct.Obj** %43, align 8
  %45 = load %struct.Token*, %struct.Token** %7, align 8
  %46 = call %struct.Node* @new_var_node(%struct.Obj* noundef %44, %struct.Token* noundef %45)
  %47 = load %struct.Token*, %struct.Token** %7, align 8
  %48 = call %struct.Node* @new_binary(i32 noundef 3, %struct.Node* noundef %37, %struct.Node* noundef %46, %struct.Token* noundef %47)
  store %struct.Node* %48, %struct.Node** %6, align 8
  %49 = load %struct.Node*, %struct.Node** %6, align 8
  call void @add_type(%struct.Node* noundef %49)
  %50 = load %struct.Node*, %struct.Node** %5, align 8
  %51 = load %struct.Node*, %struct.Node** %6, align 8
  %52 = load %struct.Token*, %struct.Token** %7, align 8
  %53 = call %struct.Node* @new_binary(i32 noundef 2, %struct.Node* noundef %50, %struct.Node* noundef %51, %struct.Token* noundef %52)
  store %struct.Node* %53, %struct.Node** %8, align 8
  %54 = load %struct.Node*, %struct.Node** %5, align 8
  %55 = getelementptr inbounds %struct.Node, %struct.Node* %54, i32 0, i32 2
  %56 = load %struct.Type*, %struct.Type** %55, align 16
  %57 = load %struct.Node*, %struct.Node** %8, align 8
  %58 = getelementptr inbounds %struct.Node, %struct.Node* %57, i32 0, i32 2
  store %struct.Type* %56, %struct.Type** %58, align 16
  %59 = load %struct.Node*, %struct.Node** %8, align 8
  store %struct.Node* %59, %struct.Node** %4, align 8
  br label %134

60:                                               ; preds = %27
  %61 = load %struct.Node*, %struct.Node** %5, align 8
  %62 = getelementptr inbounds %struct.Node, %struct.Node* %61, i32 0, i32 2
  %63 = load %struct.Type*, %struct.Type** %62, align 16
  %64 = getelementptr inbounds %struct.Type, %struct.Type* %63, i32 0, i32 8
  %65 = load %struct.Type*, %struct.Type** %64, align 8
  %66 = icmp ne %struct.Type* %65, null
  br i1 %66, label %67, label %97

67:                                               ; preds = %60
  %68 = load %struct.Node*, %struct.Node** %6, align 8
  %69 = getelementptr inbounds %struct.Node, %struct.Node* %68, i32 0, i32 2
  %70 = load %struct.Type*, %struct.Type** %69, align 16
  %71 = call zeroext i1 @is_integer(%struct.Type* noundef %70)
  br i1 %71, label %72, label %97

72:                                               ; preds = %67
  %73 = load %struct.Node*, %struct.Node** %6, align 8
  %74 = load %struct.Node*, %struct.Node** %5, align 8
  %75 = getelementptr inbounds %struct.Node, %struct.Node* %74, i32 0, i32 2
  %76 = load %struct.Type*, %struct.Type** %75, align 16
  %77 = getelementptr inbounds %struct.Type, %struct.Type* %76, i32 0, i32 8
  %78 = load %struct.Type*, %struct.Type** %77, align 8
  %79 = getelementptr inbounds %struct.Type, %struct.Type* %78, i32 0, i32 1
  %80 = load i32, i32* %79, align 4
  %81 = sext i32 %80 to i64
  %82 = load %struct.Token*, %struct.Token** %7, align 8
  %83 = call %struct.Node* @new_long(i64 noundef %81, %struct.Token* noundef %82)
  %84 = load %struct.Token*, %struct.Token** %7, align 8
  %85 = call %struct.Node* @new_binary(i32 noundef 3, %struct.Node* noundef %73, %struct.Node* noundef %83, %struct.Token* noundef %84)
  store %struct.Node* %85, %struct.Node** %6, align 8
  %86 = load %struct.Node*, %struct.Node** %6, align 8
  call void @add_type(%struct.Node* noundef %86)
  %87 = load %struct.Node*, %struct.Node** %5, align 8
  %88 = load %struct.Node*, %struct.Node** %6, align 8
  %89 = load %struct.Token*, %struct.Token** %7, align 8
  %90 = call %struct.Node* @new_binary(i32 noundef 2, %struct.Node* noundef %87, %struct.Node* noundef %88, %struct.Token* noundef %89)
  store %struct.Node* %90, %struct.Node** %9, align 8
  %91 = load %struct.Node*, %struct.Node** %5, align 8
  %92 = getelementptr inbounds %struct.Node, %struct.Node* %91, i32 0, i32 2
  %93 = load %struct.Type*, %struct.Type** %92, align 16
  %94 = load %struct.Node*, %struct.Node** %9, align 8
  %95 = getelementptr inbounds %struct.Node, %struct.Node* %94, i32 0, i32 2
  store %struct.Type* %93, %struct.Type** %95, align 16
  %96 = load %struct.Node*, %struct.Node** %9, align 8
  store %struct.Node* %96, %struct.Node** %4, align 8
  br label %134

97:                                               ; preds = %67, %60
  %98 = load %struct.Node*, %struct.Node** %5, align 8
  %99 = getelementptr inbounds %struct.Node, %struct.Node* %98, i32 0, i32 2
  %100 = load %struct.Type*, %struct.Type** %99, align 16
  %101 = getelementptr inbounds %struct.Type, %struct.Type* %100, i32 0, i32 8
  %102 = load %struct.Type*, %struct.Type** %101, align 8
  %103 = icmp ne %struct.Type* %102, null
  br i1 %103, label %104, label %132

104:                                              ; preds = %97
  %105 = load %struct.Node*, %struct.Node** %6, align 8
  %106 = getelementptr inbounds %struct.Node, %struct.Node* %105, i32 0, i32 2
  %107 = load %struct.Type*, %struct.Type** %106, align 16
  %108 = getelementptr inbounds %struct.Type, %struct.Type* %107, i32 0, i32 8
  %109 = load %struct.Type*, %struct.Type** %108, align 8
  %110 = icmp ne %struct.Type* %109, null
  br i1 %110, label %111, label %132

111:                                              ; preds = %104
  %112 = load %struct.Node*, %struct.Node** %5, align 8
  %113 = load %struct.Node*, %struct.Node** %6, align 8
  %114 = load %struct.Token*, %struct.Token** %7, align 8
  %115 = call %struct.Node* @new_binary(i32 noundef 2, %struct.Node* noundef %112, %struct.Node* noundef %113, %struct.Token* noundef %114)
  store %struct.Node* %115, %struct.Node** %10, align 8
  %116 = load %struct.Type*, %struct.Type** @ty_long, align 8
  %117 = load %struct.Node*, %struct.Node** %10, align 8
  %118 = getelementptr inbounds %struct.Node, %struct.Node* %117, i32 0, i32 2
  store %struct.Type* %116, %struct.Type** %118, align 16
  %119 = load %struct.Node*, %struct.Node** %10, align 8
  %120 = load %struct.Node*, %struct.Node** %5, align 8
  %121 = getelementptr inbounds %struct.Node, %struct.Node* %120, i32 0, i32 2
  %122 = load %struct.Type*, %struct.Type** %121, align 16
  %123 = getelementptr inbounds %struct.Type, %struct.Type* %122, i32 0, i32 8
  %124 = load %struct.Type*, %struct.Type** %123, align 8
  %125 = getelementptr inbounds %struct.Type, %struct.Type* %124, i32 0, i32 1
  %126 = load i32, i32* %125, align 4
  %127 = sext i32 %126 to i64
  %128 = load %struct.Token*, %struct.Token** %7, align 8
  %129 = call %struct.Node* @new_num(i64 noundef %127, %struct.Token* noundef %128)
  %130 = load %struct.Token*, %struct.Token** %7, align 8
  %131 = call %struct.Node* @new_binary(i32 noundef 4, %struct.Node* noundef %119, %struct.Node* noundef %129, %struct.Token* noundef %130)
  store %struct.Node* %131, %struct.Node** %4, align 8
  br label %134

132:                                              ; preds = %104, %97
  %133 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %133, i8* noundef getelementptr inbounds ([34 x i8], [34 x i8]* @.str.215, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

134:                                              ; preds = %111, %72, %36, %22
  %135 = load %struct.Node*, %struct.Node** %4, align 8
  ret %struct.Node* %135
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @cast(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = call zeroext i1 @equal(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %10, label %11, label %40

11:                                               ; preds = %2
  %12 = load %struct.Token*, %struct.Token** %5, align 8
  %13 = getelementptr inbounds %struct.Token, %struct.Token* %12, i32 0, i32 1
  %14 = load %struct.Token*, %struct.Token** %13, align 8
  %15 = call zeroext i1 @is_typename(%struct.Token* noundef %14)
  br i1 %15, label %16, label %40

16:                                               ; preds = %11
  %17 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %17, %struct.Token** %6, align 8
  %18 = load %struct.Token*, %struct.Token** %5, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 1
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  %21 = call %struct.Type* @typename(%struct.Token** noundef %5, %struct.Token* noundef %20)
  store %struct.Type* %21, %struct.Type** %7, align 8
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = call %struct.Token* @skip(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %23, %struct.Token** %5, align 8
  %24 = load %struct.Token*, %struct.Token** %5, align 8
  %25 = call zeroext i1 @equal(%struct.Token* noundef %24, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %25, label %26, label %30

26:                                               ; preds = %16
  %27 = load %struct.Token**, %struct.Token*** %4, align 8
  %28 = load %struct.Token*, %struct.Token** %6, align 8
  %29 = call %struct.Node* @unary(%struct.Token** noundef %27, %struct.Token* noundef %28)
  store %struct.Node* %29, %struct.Node** %3, align 8
  br label %44

30:                                               ; preds = %16
  %31 = load %struct.Token**, %struct.Token*** %4, align 8
  %32 = load %struct.Token*, %struct.Token** %5, align 8
  %33 = call %struct.Node* @cast(%struct.Token** noundef %31, %struct.Token* noundef %32)
  %34 = load %struct.Type*, %struct.Type** %7, align 8
  %35 = call %struct.Node* @new_cast(%struct.Node* noundef %33, %struct.Type* noundef %34)
  store %struct.Node* %35, %struct.Node** %8, align 8
  %36 = load %struct.Token*, %struct.Token** %6, align 8
  %37 = load %struct.Node*, %struct.Node** %8, align 8
  %38 = getelementptr inbounds %struct.Node, %struct.Node* %37, i32 0, i32 3
  store %struct.Token* %36, %struct.Token** %38, align 8
  %39 = load %struct.Node*, %struct.Node** %8, align 8
  store %struct.Node* %39, %struct.Node** %3, align 8
  br label %44

40:                                               ; preds = %11, %2
  %41 = load %struct.Token**, %struct.Token*** %4, align 8
  %42 = load %struct.Token*, %struct.Token** %5, align 8
  %43 = call %struct.Node* @unary(%struct.Token** noundef %41, %struct.Token* noundef %42)
  store %struct.Node* %43, %struct.Node** %3, align 8
  br label %44

44:                                               ; preds = %40, %30, %26
  %45 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %45
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @is_typename(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca i32, align 4
  store %struct.Token* %0, %struct.Token** %2, align 8
  %4 = load i32, i32* getelementptr inbounds (%struct.HashMap, %struct.HashMap* @is_typename.map, i32 0, i32 1), align 8
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %6, label %20

6:                                                ; preds = %1
  store i32 0, i32* %3, align 4
  br label %7

7:                                                ; preds = %16, %6
  %8 = load i32, i32* %3, align 4
  %9 = sext i32 %8 to i64
  %10 = icmp ult i64 %9, 31
  br i1 %10, label %11, label %19

11:                                               ; preds = %7
  %12 = load i32, i32* %3, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [31 x i8*], [31 x i8*]* @is_typename.kw, i64 0, i64 %13
  %15 = load i8*, i8** %14, align 8
  call void @hashmap_put(%struct.HashMap* noundef @is_typename.map, i8* noundef %15, i8* noundef inttoptr (i64 1 to i8*))
  br label %16

16:                                               ; preds = %11
  %17 = load i32, i32* %3, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, i32* %3, align 4
  br label %7, !llvm.loop !23

19:                                               ; preds = %7
  br label %20

20:                                               ; preds = %19, %1
  %21 = load %struct.Token*, %struct.Token** %2, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 4
  %23 = load i8*, i8** %22, align 16
  %24 = load %struct.Token*, %struct.Token** %2, align 8
  %25 = getelementptr inbounds %struct.Token, %struct.Token* %24, i32 0, i32 5
  %26 = load i32, i32* %25, align 8
  %27 = call i8* @hashmap_get2(%struct.HashMap* noundef @is_typename.map, i8* noundef %23, i32 noundef %26)
  %28 = icmp ne i8* %27, null
  br i1 %28, label %33, label %29

29:                                               ; preds = %20
  %30 = load %struct.Token*, %struct.Token** %2, align 8
  %31 = call %struct.Type* @find_typedef(%struct.Token* noundef %30)
  %32 = icmp ne %struct.Type* %31, null
  br label %33

33:                                               ; preds = %29, %20
  %34 = phi i1 [ true, %20 ], [ %32, %29 ]
  ret i1 %34
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @typename(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Type*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load %struct.Token*, %struct.Token** %4, align 8
  %7 = call %struct.Type* @declspec(%struct.Token** noundef %4, %struct.Token* noundef %6, %struct.VarAttr* noundef null)
  store %struct.Type* %7, %struct.Type** %5, align 8
  %8 = load %struct.Token**, %struct.Token*** %3, align 8
  %9 = load %struct.Token*, %struct.Token** %4, align 8
  %10 = load %struct.Type*, %struct.Type** %5, align 8
  %11 = call %struct.Type* @abstract_declarator(%struct.Token** noundef %8, %struct.Token* noundef %9, %struct.Type* noundef %10)
  ret %struct.Type* %11
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @unary(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = call zeroext i1 @equal(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.80, i64 0, i64 0))
  br i1 %10, label %11, label %17

11:                                               ; preds = %2
  %12 = load %struct.Token**, %struct.Token*** %4, align 8
  %13 = load %struct.Token*, %struct.Token** %5, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 1
  %15 = load %struct.Token*, %struct.Token** %14, align 8
  %16 = call %struct.Node* @cast(%struct.Token** noundef %12, %struct.Token* noundef %15)
  store %struct.Node* %16, %struct.Node** %3, align 8
  br label %154

17:                                               ; preds = %2
  %18 = load %struct.Token*, %struct.Token** %5, align 8
  %19 = call zeroext i1 @equal(%struct.Token* noundef %18, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.81, i64 0, i64 0))
  br i1 %19, label %20, label %28

20:                                               ; preds = %17
  %21 = load %struct.Token**, %struct.Token*** %4, align 8
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = getelementptr inbounds %struct.Token, %struct.Token* %22, i32 0, i32 1
  %24 = load %struct.Token*, %struct.Token** %23, align 8
  %25 = call %struct.Node* @cast(%struct.Token** noundef %21, %struct.Token* noundef %24)
  %26 = load %struct.Token*, %struct.Token** %5, align 8
  %27 = call %struct.Node* @new_unary(i32 noundef 5, %struct.Node* noundef %25, %struct.Token* noundef %26)
  store %struct.Node* %27, %struct.Node** %3, align 8
  br label %154

28:                                               ; preds = %17
  %29 = load %struct.Token*, %struct.Token** %5, align 8
  %30 = call zeroext i1 @equal(%struct.Token* noundef %29, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.71, i64 0, i64 0))
  br i1 %30, label %31, label %55

31:                                               ; preds = %28
  %32 = load %struct.Token**, %struct.Token*** %4, align 8
  %33 = load %struct.Token*, %struct.Token** %5, align 8
  %34 = getelementptr inbounds %struct.Token, %struct.Token* %33, i32 0, i32 1
  %35 = load %struct.Token*, %struct.Token** %34, align 8
  %36 = call %struct.Node* @cast(%struct.Token** noundef %32, %struct.Token* noundef %35)
  store %struct.Node* %36, %struct.Node** %6, align 8
  %37 = load %struct.Node*, %struct.Node** %6, align 8
  call void @add_type(%struct.Node* noundef %37)
  %38 = load %struct.Node*, %struct.Node** %6, align 8
  %39 = getelementptr inbounds %struct.Node, %struct.Node* %38, i32 0, i32 0
  %40 = load i32, i32* %39, align 16
  %41 = icmp eq i32 %40, 19
  br i1 %41, label %42, label %51

42:                                               ; preds = %31
  %43 = load %struct.Node*, %struct.Node** %6, align 8
  %44 = getelementptr inbounds %struct.Node, %struct.Node* %43, i32 0, i32 14
  %45 = load %struct.Member*, %struct.Member** %44, align 16
  %46 = getelementptr inbounds %struct.Member, %struct.Member* %45, i32 0, i32 7
  %47 = load i8, i8* %46, align 4
  %48 = trunc i8 %47 to i1
  br i1 %48, label %49, label %51

49:                                               ; preds = %42
  %50 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %50, i8* noundef getelementptr inbounds ([47 x i8], [47 x i8]* @.str.126, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

51:                                               ; preds = %42, %31
  %52 = load %struct.Node*, %struct.Node** %6, align 8
  %53 = load %struct.Token*, %struct.Token** %5, align 8
  %54 = call %struct.Node* @new_unary(i32 noundef 20, %struct.Node* noundef %52, %struct.Token* noundef %53)
  store %struct.Node* %54, %struct.Node** %3, align 8
  br label %154

55:                                               ; preds = %28
  %56 = load %struct.Token*, %struct.Token** %5, align 8
  %57 = call zeroext i1 @equal(%struct.Token* noundef %56, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.82, i64 0, i64 0))
  br i1 %57, label %58, label %77

58:                                               ; preds = %55
  %59 = load %struct.Token**, %struct.Token*** %4, align 8
  %60 = load %struct.Token*, %struct.Token** %5, align 8
  %61 = getelementptr inbounds %struct.Token, %struct.Token* %60, i32 0, i32 1
  %62 = load %struct.Token*, %struct.Token** %61, align 8
  %63 = call %struct.Node* @cast(%struct.Token** noundef %59, %struct.Token* noundef %62)
  store %struct.Node* %63, %struct.Node** %7, align 8
  %64 = load %struct.Node*, %struct.Node** %7, align 8
  call void @add_type(%struct.Node* noundef %64)
  %65 = load %struct.Node*, %struct.Node** %7, align 8
  %66 = getelementptr inbounds %struct.Node, %struct.Node* %65, i32 0, i32 2
  %67 = load %struct.Type*, %struct.Type** %66, align 16
  %68 = getelementptr inbounds %struct.Type, %struct.Type* %67, i32 0, i32 0
  %69 = load i32, i32* %68, align 8
  %70 = icmp eq i32 %69, 11
  br i1 %70, label %71, label %73

71:                                               ; preds = %58
  %72 = load %struct.Node*, %struct.Node** %7, align 8
  store %struct.Node* %72, %struct.Node** %3, align 8
  br label %154

73:                                               ; preds = %58
  %74 = load %struct.Node*, %struct.Node** %7, align 8
  %75 = load %struct.Token*, %struct.Token** %5, align 8
  %76 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %74, %struct.Token* noundef %75)
  store %struct.Node* %76, %struct.Node** %3, align 8
  br label %154

77:                                               ; preds = %55
  %78 = load %struct.Token*, %struct.Token** %5, align 8
  %79 = call zeroext i1 @equal(%struct.Token* noundef %78, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.127, i64 0, i64 0))
  br i1 %79, label %80, label %88

80:                                               ; preds = %77
  %81 = load %struct.Token**, %struct.Token*** %4, align 8
  %82 = load %struct.Token*, %struct.Token** %5, align 8
  %83 = getelementptr inbounds %struct.Token, %struct.Token* %82, i32 0, i32 1
  %84 = load %struct.Token*, %struct.Token** %83, align 8
  %85 = call %struct.Node* @cast(%struct.Token** noundef %81, %struct.Token* noundef %84)
  %86 = load %struct.Token*, %struct.Token** %5, align 8
  %87 = call %struct.Node* @new_unary(i32 noundef 22, %struct.Node* noundef %85, %struct.Token* noundef %86)
  store %struct.Node* %87, %struct.Node** %3, align 8
  br label %154

88:                                               ; preds = %77
  %89 = load %struct.Token*, %struct.Token** %5, align 8
  %90 = call zeroext i1 @equal(%struct.Token* noundef %89, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.128, i64 0, i64 0))
  br i1 %90, label %91, label %99

91:                                               ; preds = %88
  %92 = load %struct.Token**, %struct.Token*** %4, align 8
  %93 = load %struct.Token*, %struct.Token** %5, align 8
  %94 = getelementptr inbounds %struct.Token, %struct.Token* %93, i32 0, i32 1
  %95 = load %struct.Token*, %struct.Token** %94, align 8
  %96 = call %struct.Node* @cast(%struct.Token** noundef %92, %struct.Token* noundef %95)
  %97 = load %struct.Token*, %struct.Token** %5, align 8
  %98 = call %struct.Node* @new_unary(i32 noundef 23, %struct.Node* noundef %96, %struct.Token* noundef %97)
  store %struct.Node* %98, %struct.Node** %3, align 8
  br label %154

99:                                               ; preds = %88
  %100 = load %struct.Token*, %struct.Token** %5, align 8
  %101 = call zeroext i1 @equal(%struct.Token* noundef %100, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.129, i64 0, i64 0))
  br i1 %101, label %102, label %113

102:                                              ; preds = %99
  %103 = load %struct.Token**, %struct.Token*** %4, align 8
  %104 = load %struct.Token*, %struct.Token** %5, align 8
  %105 = getelementptr inbounds %struct.Token, %struct.Token* %104, i32 0, i32 1
  %106 = load %struct.Token*, %struct.Token** %105, align 8
  %107 = call %struct.Node* @unary(%struct.Token** noundef %103, %struct.Token* noundef %106)
  %108 = load %struct.Token*, %struct.Token** %5, align 8
  %109 = call %struct.Node* @new_num(i64 noundef 1, %struct.Token* noundef %108)
  %110 = load %struct.Token*, %struct.Token** %5, align 8
  %111 = call %struct.Node* @new_add(%struct.Node* noundef %107, %struct.Node* noundef %109, %struct.Token* noundef %110)
  %112 = call %struct.Node* @to_assign(%struct.Node* noundef %111)
  store %struct.Node* %112, %struct.Node** %3, align 8
  br label %154

113:                                              ; preds = %99
  %114 = load %struct.Token*, %struct.Token** %5, align 8
  %115 = call zeroext i1 @equal(%struct.Token* noundef %114, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.130, i64 0, i64 0))
  br i1 %115, label %116, label %127

116:                                              ; preds = %113
  %117 = load %struct.Token**, %struct.Token*** %4, align 8
  %118 = load %struct.Token*, %struct.Token** %5, align 8
  %119 = getelementptr inbounds %struct.Token, %struct.Token* %118, i32 0, i32 1
  %120 = load %struct.Token*, %struct.Token** %119, align 8
  %121 = call %struct.Node* @unary(%struct.Token** noundef %117, %struct.Token* noundef %120)
  %122 = load %struct.Token*, %struct.Token** %5, align 8
  %123 = call %struct.Node* @new_num(i64 noundef 1, %struct.Token* noundef %122)
  %124 = load %struct.Token*, %struct.Token** %5, align 8
  %125 = call %struct.Node* @new_sub(%struct.Node* noundef %121, %struct.Node* noundef %123, %struct.Token* noundef %124)
  %126 = call %struct.Node* @to_assign(%struct.Node* noundef %125)
  store %struct.Node* %126, %struct.Node** %3, align 8
  br label %154

127:                                              ; preds = %113
  %128 = load %struct.Token*, %struct.Token** %5, align 8
  %129 = call zeroext i1 @equal(%struct.Token* noundef %128, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0))
  br i1 %129, label %130, label %150

130:                                              ; preds = %127
  %131 = load %struct.Token*, %struct.Token** %5, align 8
  %132 = call %struct.Node* @new_node(i32 noundef 36, %struct.Token* noundef %131)
  store %struct.Node* %132, %struct.Node** %8, align 8
  %133 = load %struct.Token*, %struct.Token** %5, align 8
  %134 = getelementptr inbounds %struct.Token, %struct.Token* %133, i32 0, i32 1
  %135 = load %struct.Token*, %struct.Token** %134, align 8
  %136 = call i8* @get_ident(%struct.Token* noundef %135)
  %137 = load %struct.Node*, %struct.Node** %8, align 8
  %138 = getelementptr inbounds %struct.Node, %struct.Node* %137, i32 0, i32 19
  store i8* %136, i8** %138, align 8
  %139 = load %struct.Node*, %struct.Node** @gotos, align 8
  %140 = load %struct.Node*, %struct.Node** %8, align 8
  %141 = getelementptr inbounds %struct.Node, %struct.Node* %140, i32 0, i32 21
  store %struct.Node* %139, %struct.Node** %141, align 8
  %142 = load %struct.Node*, %struct.Node** %8, align 8
  store %struct.Node* %142, %struct.Node** @gotos, align 8
  %143 = load %struct.Token*, %struct.Token** %5, align 8
  %144 = getelementptr inbounds %struct.Token, %struct.Token* %143, i32 0, i32 1
  %145 = load %struct.Token*, %struct.Token** %144, align 8
  %146 = getelementptr inbounds %struct.Token, %struct.Token* %145, i32 0, i32 1
  %147 = load %struct.Token*, %struct.Token** %146, align 8
  %148 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %147, %struct.Token** %148, align 8
  %149 = load %struct.Node*, %struct.Node** %8, align 8
  store %struct.Node* %149, %struct.Node** %3, align 8
  br label %154

150:                                              ; preds = %127
  %151 = load %struct.Token**, %struct.Token*** %4, align 8
  %152 = load %struct.Token*, %struct.Token** %5, align 8
  %153 = call %struct.Node* @postfix(%struct.Token** noundef %151, %struct.Token* noundef %152)
  store %struct.Node* %153, %struct.Node** %3, align 8
  br label %154

154:                                              ; preds = %150, %130, %116, %102, %91, %80, %73, %71, %51, %20, %11
  %155 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %155
}

declare void @hashmap_put(%struct.HashMap* noundef, i8* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @find_typedef(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.VarScope*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %5 = load %struct.Token*, %struct.Token** %3, align 8
  %6 = getelementptr inbounds %struct.Token, %struct.Token* %5, i32 0, i32 0
  %7 = load i32, i32* %6, align 16
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %9, label %19

9:                                                ; preds = %1
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = call %struct.VarScope* @find_var(%struct.Token* noundef %10)
  store %struct.VarScope* %11, %struct.VarScope** %4, align 8
  %12 = load %struct.VarScope*, %struct.VarScope** %4, align 8
  %13 = icmp ne %struct.VarScope* %12, null
  br i1 %13, label %14, label %18

14:                                               ; preds = %9
  %15 = load %struct.VarScope*, %struct.VarScope** %4, align 8
  %16 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %15, i32 0, i32 1
  %17 = load %struct.Type*, %struct.Type** %16, align 8
  store %struct.Type* %17, %struct.Type** %2, align 8
  br label %20

18:                                               ; preds = %9
  br label %19

19:                                               ; preds = %18, %1
  store %struct.Type* null, %struct.Type** %2, align 8
  br label %20

20:                                               ; preds = %19, %14
  %21 = load %struct.Type*, %struct.Type** %2, align 8
  ret %struct.Type* %21
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @abstract_declarator(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.Token*, align 8
  %9 = alloca %struct.Type, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  %10 = load %struct.Token*, %struct.Token** %6, align 8
  %11 = load %struct.Type*, %struct.Type** %7, align 8
  %12 = call %struct.Type* @pointers(%struct.Token** noundef %6, %struct.Token* noundef %10, %struct.Type* noundef %11)
  store %struct.Type* %12, %struct.Type** %7, align 8
  %13 = load %struct.Token*, %struct.Token** %6, align 8
  %14 = call zeroext i1 @equal(%struct.Token* noundef %13, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %14, label %15, label %33

15:                                               ; preds = %3
  %16 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %16, %struct.Token** %8, align 8
  %17 = bitcast %struct.Type* %9 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %17, i8 0, i64 128, i1 false)
  %18 = load %struct.Token*, %struct.Token** %8, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 1
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  %21 = call %struct.Type* @abstract_declarator(%struct.Token** noundef %6, %struct.Token* noundef %20, %struct.Type* noundef %9)
  %22 = load %struct.Token*, %struct.Token** %6, align 8
  %23 = call %struct.Token* @skip(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %23, %struct.Token** %6, align 8
  %24 = load %struct.Token**, %struct.Token*** %5, align 8
  %25 = load %struct.Token*, %struct.Token** %6, align 8
  %26 = load %struct.Type*, %struct.Type** %7, align 8
  %27 = call %struct.Type* @type_suffix(%struct.Token** noundef %24, %struct.Token* noundef %25, %struct.Type* noundef %26)
  store %struct.Type* %27, %struct.Type** %7, align 8
  %28 = load %struct.Token*, %struct.Token** %8, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 1
  %30 = load %struct.Token*, %struct.Token** %29, align 8
  %31 = load %struct.Type*, %struct.Type** %7, align 8
  %32 = call %struct.Type* @abstract_declarator(%struct.Token** noundef %6, %struct.Token* noundef %30, %struct.Type* noundef %31)
  store %struct.Type* %32, %struct.Type** %4, align 8
  br label %38

33:                                               ; preds = %3
  %34 = load %struct.Token**, %struct.Token*** %5, align 8
  %35 = load %struct.Token*, %struct.Token** %6, align 8
  %36 = load %struct.Type*, %struct.Type** %7, align 8
  %37 = call %struct.Type* @type_suffix(%struct.Token** noundef %34, %struct.Token* noundef %35, %struct.Type* noundef %36)
  store %struct.Type* %37, %struct.Type** %4, align 8
  br label %38

38:                                               ; preds = %33, %15
  %39 = load %struct.Type*, %struct.Type** %4, align 8
  ret %struct.Type* %39
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @pointers(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Type* %2, %struct.Type** %6, align 8
  br label %7

7:                                                ; preds = %40, %3
  %8 = load %struct.Token*, %struct.Token** %5, align 8
  %9 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %8, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.82, i64 0, i64 0))
  br i1 %9, label %10, label %41

10:                                               ; preds = %7
  %11 = load %struct.Type*, %struct.Type** %6, align 8
  %12 = call %struct.Type* @pointer_to(%struct.Type* noundef %11)
  store %struct.Type* %12, %struct.Type** %6, align 8
  br label %13

13:                                               ; preds = %36, %10
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  %15 = call zeroext i1 @equal(%struct.Token* noundef %14, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.103, i64 0, i64 0))
  br i1 %15, label %34, label %16

16:                                               ; preds = %13
  %17 = load %struct.Token*, %struct.Token** %5, align 8
  %18 = call zeroext i1 @equal(%struct.Token* noundef %17, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.104, i64 0, i64 0))
  br i1 %18, label %34, label %19

19:                                               ; preds = %16
  %20 = load %struct.Token*, %struct.Token** %5, align 8
  %21 = call zeroext i1 @equal(%struct.Token* noundef %20, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.107, i64 0, i64 0))
  br i1 %21, label %34, label %22

22:                                               ; preds = %19
  %23 = load %struct.Token*, %struct.Token** %5, align 8
  %24 = call zeroext i1 @equal(%struct.Token* noundef %23, i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.108, i64 0, i64 0))
  br i1 %24, label %34, label %25

25:                                               ; preds = %22
  %26 = load %struct.Token*, %struct.Token** %5, align 8
  %27 = call zeroext i1 @equal(%struct.Token* noundef %26, i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.109, i64 0, i64 0))
  br i1 %27, label %34, label %28

28:                                               ; preds = %25
  %29 = load %struct.Token*, %struct.Token** %5, align 8
  %30 = call zeroext i1 @equal(%struct.Token* noundef %29, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.117, i64 0, i64 0))
  br i1 %30, label %34, label %31

31:                                               ; preds = %28
  %32 = load %struct.Token*, %struct.Token** %5, align 8
  %33 = call zeroext i1 @equal(%struct.Token* noundef %32, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.118, i64 0, i64 0))
  br label %34

34:                                               ; preds = %31, %28, %25, %22, %19, %16, %13
  %35 = phi i1 [ true, %28 ], [ true, %25 ], [ true, %22 ], [ true, %19 ], [ true, %16 ], [ true, %13 ], [ %33, %31 ]
  br i1 %35, label %36, label %40

36:                                               ; preds = %34
  %37 = load %struct.Token*, %struct.Token** %5, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 1
  %39 = load %struct.Token*, %struct.Token** %38, align 8
  store %struct.Token* %39, %struct.Token** %5, align 8
  br label %13, !llvm.loop !24

40:                                               ; preds = %34
  br label %7, !llvm.loop !25

41:                                               ; preds = %7
  %42 = load %struct.Token*, %struct.Token** %5, align 8
  %43 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %42, %struct.Token** %43, align 8
  %44 = load %struct.Type*, %struct.Type** %6, align 8
  ret %struct.Type* %44
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @type_suffix(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca i8, align 1
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  store i8 0, i8* %8, align 1
  %9 = load %struct.Token*, %struct.Token** %6, align 8
  %10 = call zeroext i1 @equal(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %10, label %11, label %32

11:                                               ; preds = %3
  %12 = load %struct.Token*, %struct.Token** %6, align 8
  %13 = getelementptr inbounds %struct.Token, %struct.Token* %12, i32 0, i32 1
  %14 = load %struct.Token*, %struct.Token** %13, align 8
  %15 = call zeroext i1 @is_typename(%struct.Token* noundef %14)
  br i1 %15, label %32, label %16

16:                                               ; preds = %11
  %17 = load %struct.Token**, %struct.Token*** %5, align 8
  %18 = load %struct.Token*, %struct.Token** %6, align 8
  %19 = load %struct.Type*, %struct.Type** %7, align 8
  %20 = call zeroext i1 @check_old_style(%struct.Token** noundef %17, %struct.Token* noundef %18, %struct.Type* noundef %19)
  %21 = zext i1 %20 to i8
  store i8 %21, i8* %8, align 1
  %22 = load i8, i8* %8, align 1
  %23 = trunc i8 %22 to i1
  br i1 %23, label %24, label %31

24:                                               ; preds = %16
  %25 = load %struct.Token**, %struct.Token*** %5, align 8
  %26 = load %struct.Token*, %struct.Token** %6, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  %29 = load %struct.Type*, %struct.Type** %7, align 8
  %30 = call %struct.Type* @func_params2(%struct.Token** noundef %25, %struct.Token* noundef %28, %struct.Type* noundef %29)
  store %struct.Type* %30, %struct.Type** %4, align 8
  br label %56

31:                                               ; preds = %16
  br label %32

32:                                               ; preds = %31, %11, %3
  %33 = load %struct.Token*, %struct.Token** %6, align 8
  %34 = call zeroext i1 @equal(%struct.Token* noundef %33, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %34, label %35, label %42

35:                                               ; preds = %32
  %36 = load %struct.Token**, %struct.Token*** %5, align 8
  %37 = load %struct.Token*, %struct.Token** %6, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 1
  %39 = load %struct.Token*, %struct.Token** %38, align 8
  %40 = load %struct.Type*, %struct.Type** %7, align 8
  %41 = call %struct.Type* @func_params(%struct.Token** noundef %36, %struct.Token* noundef %39, %struct.Type* noundef %40)
  store %struct.Type* %41, %struct.Type** %4, align 8
  br label %56

42:                                               ; preds = %32
  %43 = load %struct.Token*, %struct.Token** %6, align 8
  %44 = call zeroext i1 @equal(%struct.Token* noundef %43, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.119, i64 0, i64 0))
  br i1 %44, label %45, label %52

45:                                               ; preds = %42
  %46 = load %struct.Token**, %struct.Token*** %5, align 8
  %47 = load %struct.Token*, %struct.Token** %6, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 1
  %49 = load %struct.Token*, %struct.Token** %48, align 8
  %50 = load %struct.Type*, %struct.Type** %7, align 8
  %51 = call %struct.Type* @array_dimensions(%struct.Token** noundef %46, %struct.Token* noundef %49, %struct.Type* noundef %50)
  store %struct.Type* %51, %struct.Type** %4, align 8
  br label %56

52:                                               ; preds = %42
  %53 = load %struct.Token*, %struct.Token** %6, align 8
  %54 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %53, %struct.Token** %54, align 8
  %55 = load %struct.Type*, %struct.Type** %7, align 8
  store %struct.Type* %55, %struct.Type** %4, align 8
  br label %56

56:                                               ; preds = %52, %45, %35, %24
  %57 = load %struct.Type*, %struct.Type** %4, align 8
  ret %struct.Type* %57
}

declare zeroext i1 @consume(%struct.Token** noundef, %struct.Token* noundef, i8* noundef) #1

declare %struct.Type* @pointer_to(%struct.Type* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @check_old_style(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  %8 = load %struct.Token*, %struct.Token** %6, align 8
  %9 = getelementptr inbounds %struct.Token, %struct.Token* %8, i32 0, i32 1
  %10 = load %struct.Token*, %struct.Token** %9, align 8
  %11 = call zeroext i1 @equal(%struct.Token* noundef %10, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  br i1 %11, label %12, label %13

12:                                               ; preds = %3
  store i1 false, i1* %4, align 1
  br label %41

13:                                               ; preds = %3
  br label %14

14:                                               ; preds = %36, %13
  %15 = load %struct.Token*, %struct.Token** %6, align 8
  %16 = call zeroext i1 @equal(%struct.Token* noundef %15, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  %17 = xor i1 %16, true
  br i1 %17, label %18, label %40

18:                                               ; preds = %14
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = call zeroext i1 @equal(%struct.Token* noundef %19, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.120, i64 0, i64 0))
  br i1 %20, label %21, label %22

21:                                               ; preds = %18
  br label %40

22:                                               ; preds = %18
  %23 = load %struct.Token*, %struct.Token** %6, align 8
  %24 = call zeroext i1 @is_typename(%struct.Token* noundef %23)
  br i1 %24, label %25, label %26

25:                                               ; preds = %22
  br label %40

26:                                               ; preds = %22
  %27 = load %struct.Token*, %struct.Token** %6, align 8
  %28 = call zeroext i1 @equal(%struct.Token* noundef %27, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  br i1 %28, label %29, label %36

29:                                               ; preds = %26
  %30 = load %struct.Token*, %struct.Token** %6, align 8
  %31 = getelementptr inbounds %struct.Token, %struct.Token* %30, i32 0, i32 1
  %32 = load %struct.Token*, %struct.Token** %31, align 8
  %33 = call zeroext i1 @equal(%struct.Token* noundef %32, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %33, label %35, label %34

34:                                               ; preds = %29
  store i1 true, i1* %4, align 1
  br label %41

35:                                               ; preds = %29
  br label %36

36:                                               ; preds = %35, %26
  %37 = load %struct.Token*, %struct.Token** %6, align 8
  %38 = getelementptr inbounds %struct.Token, %struct.Token* %37, i32 0, i32 1
  %39 = load %struct.Token*, %struct.Token** %38, align 8
  store %struct.Token* %39, %struct.Token** %6, align 8
  br label %14, !llvm.loop !26

40:                                               ; preds = %25, %21, %14
  store i1 false, i1* %4, align 1
  br label %41

41:                                               ; preds = %40, %34, %12
  %42 = load i1, i1* %4, align 1
  ret i1 %42
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @func_params2(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Type, align 8
  %8 = alloca %struct.Type*, align 8
  %9 = alloca i8, align 1
  %10 = alloca %struct.Token*, align 8
  %11 = alloca %struct.Node*, align 8
  %12 = alloca %struct.Type*, align 8
  %13 = alloca %struct.Type*, align 8
  %14 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Type* %2, %struct.Type** %6, align 8
  %15 = bitcast %struct.Type* %7 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %15, i8 0, i64 128, i1 false)
  store %struct.Type* %7, %struct.Type** %8, align 8
  store i8 0, i8* %9, align 1
  %16 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %16, %struct.Token** %10, align 8
  br label %17

17:                                               ; preds = %23, %3
  %18 = load %struct.Token*, %struct.Token** %5, align 8
  %19 = call zeroext i1 @equal(%struct.Token* noundef %18, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %20 = xor i1 %19, true
  br i1 %20, label %21, label %27

21:                                               ; preds = %17
  %22 = load %struct.Token*, %struct.Token** %10, align 8
  store %struct.Token* %22, %struct.Token** %5, align 8
  br label %23

23:                                               ; preds = %21
  %24 = load %struct.Token*, %struct.Token** %10, align 8
  %25 = getelementptr inbounds %struct.Token, %struct.Token* %24, i32 0, i32 1
  %26 = load %struct.Token*, %struct.Token** %25, align 8
  store %struct.Token* %26, %struct.Token** %10, align 8
  br label %17, !llvm.loop !27

27:                                               ; preds = %17
  %28 = load %struct.Token*, %struct.Token** %5, align 8
  %29 = call zeroext i1 @equal(%struct.Token* noundef %28, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  br i1 %29, label %30, label %34

30:                                               ; preds = %27
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = getelementptr inbounds %struct.Token, %struct.Token* %31, i32 0, i32 1
  %33 = load %struct.Token*, %struct.Token** %32, align 8
  store %struct.Token* %33, %struct.Token** %5, align 8
  br label %34

34:                                               ; preds = %30, %27
  br label %35

35:                                               ; preds = %134, %34
  %36 = load %struct.Token*, %struct.Token** %5, align 8
  %37 = call zeroext i1 @equal(%struct.Token* noundef %36, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  %38 = xor i1 %37, true
  br i1 %38, label %39, label %142

39:                                               ; preds = %35
  %40 = load %struct.Type*, %struct.Type** %8, align 8
  %41 = icmp ne %struct.Type* %40, %7
  br i1 %41, label %42, label %56

42:                                               ; preds = %39
  %43 = load %struct.Token*, %struct.Token** %5, align 8
  %44 = call zeroext i1 @equal(%struct.Token* noundef %43, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  br i1 %44, label %45, label %48

45:                                               ; preds = %42
  %46 = load %struct.Token*, %struct.Token** %5, align 8
  %47 = call %struct.Token* @skip(%struct.Token* noundef %46, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  store %struct.Token* %47, %struct.Token** %5, align 8
  br label %55

48:                                               ; preds = %42
  %49 = load %struct.Token*, %struct.Token** %5, align 8
  %50 = call zeroext i1 @equal(%struct.Token* noundef %49, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %50, label %51, label %54

51:                                               ; preds = %48
  %52 = load %struct.Token*, %struct.Token** %5, align 8
  %53 = call %struct.Token* @skip(%struct.Token* noundef %52, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %53, %struct.Token** %5, align 8
  br label %54

54:                                               ; preds = %51, %48
  br label %55

55:                                               ; preds = %54, %45
  br label %56

56:                                               ; preds = %55, %39
  %57 = load %struct.Token*, %struct.Token** %5, align 8
  %58 = call zeroext i1 @equal(%struct.Token* noundef %57, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.120, i64 0, i64 0))
  br i1 %58, label %59, label %65

59:                                               ; preds = %56
  store i8 1, i8* %9, align 1
  %60 = load %struct.Token*, %struct.Token** %5, align 8
  %61 = getelementptr inbounds %struct.Token, %struct.Token* %60, i32 0, i32 1
  %62 = load %struct.Token*, %struct.Token** %61, align 8
  store %struct.Token* %62, %struct.Token** %5, align 8
  %63 = load %struct.Token*, %struct.Token** %5, align 8
  %64 = call %struct.Token* @skip(%struct.Token* noundef %63, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  br label %142

65:                                               ; preds = %56
  %66 = load %struct.Token*, %struct.Token** %5, align 8
  %67 = getelementptr inbounds %struct.Token, %struct.Token* %66, i32 0, i32 1
  %68 = load %struct.Token*, %struct.Token** %67, align 8
  %69 = call zeroext i1 @equal(%struct.Token* noundef %68, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.72, i64 0, i64 0))
  br i1 %69, label %84, label %70

70:                                               ; preds = %65
  %71 = load %struct.Token*, %struct.Token** %5, align 8
  %72 = call zeroext i1 @equal(%struct.Token* noundef %71, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %72, label %73, label %78

73:                                               ; preds = %70
  %74 = load %struct.Token**, %struct.Token*** %4, align 8
  %75 = load %struct.Token*, %struct.Token** %5, align 8
  %76 = load %struct.Type*, %struct.Type** %6, align 8
  %77 = call zeroext i1 @is_expression(%struct.Token** noundef %74, %struct.Token* noundef %75, %struct.Type* noundef %76)
  br i1 %77, label %84, label %78

78:                                               ; preds = %73, %70
  %79 = load %struct.Token*, %struct.Token** %5, align 8
  %80 = call zeroext i1 @equal(%struct.Token* noundef %79, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.123, i64 0, i64 0))
  br i1 %80, label %84, label %81

81:                                               ; preds = %78
  %82 = load %struct.Token*, %struct.Token** %5, align 8
  %83 = call zeroext i1 @equal(%struct.Token* noundef %82, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.124, i64 0, i64 0))
  br i1 %83, label %84, label %89

84:                                               ; preds = %81, %78, %73, %65
  %85 = load %struct.Token*, %struct.Token** %5, align 8
  %86 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %85)
  store %struct.Node* %86, %struct.Node** %11, align 8
  %87 = load %struct.Token*, %struct.Token** %5, align 8
  %88 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %87, %struct.Token** %88, align 8
  br label %142

89:                                               ; preds = %81
  %90 = load %struct.Token*, %struct.Token** %5, align 8
  %91 = call %struct.Type* @declspec(%struct.Token** noundef %5, %struct.Token* noundef %90, %struct.VarAttr* noundef null)
  store %struct.Type* %91, %struct.Type** %12, align 8
  %92 = load %struct.Type*, %struct.Type** %12, align 8
  store %struct.Type* %92, %struct.Type** %13, align 8
  %93 = load %struct.Token*, %struct.Token** %5, align 8
  %94 = load %struct.Type*, %struct.Type** %12, align 8
  %95 = call %struct.Type* @declarator(%struct.Token** noundef %5, %struct.Token* noundef %93, %struct.Type* noundef %94)
  store %struct.Type* %95, %struct.Type** %12, align 8
  %96 = load %struct.Type*, %struct.Type** %12, align 8
  %97 = getelementptr inbounds %struct.Type, %struct.Type* %96, i32 0, i32 0
  %98 = load i32, i32* %97, align 8
  %99 = icmp eq i32 %98, 10
  br i1 %99, label %100, label %106

100:                                              ; preds = %89
  %101 = load %struct.Type*, %struct.Type** %12, align 8
  %102 = getelementptr inbounds %struct.Type, %struct.Type* %101, i32 0, i32 5
  store i8 1, i8* %102, align 2
  %103 = load %struct.Type*, %struct.Type** %13, align 8
  %104 = load %struct.Type*, %struct.Type** %12, align 8
  %105 = getelementptr inbounds %struct.Type, %struct.Type* %104, i32 0, i32 6
  store %struct.Type* %103, %struct.Type** %105, align 8
  br label %106

106:                                              ; preds = %100, %89
  %107 = load %struct.Type*, %struct.Type** %12, align 8
  %108 = getelementptr inbounds %struct.Type, %struct.Type* %107, i32 0, i32 9
  %109 = load %struct.Token*, %struct.Token** %108, align 8
  store %struct.Token* %109, %struct.Token** %14, align 8
  %110 = load %struct.Type*, %struct.Type** %12, align 8
  %111 = getelementptr inbounds %struct.Type, %struct.Type* %110, i32 0, i32 0
  %112 = load i32, i32* %111, align 8
  %113 = icmp eq i32 %112, 12
  br i1 %113, label %114, label %122

114:                                              ; preds = %106
  %115 = load %struct.Type*, %struct.Type** %12, align 8
  %116 = getelementptr inbounds %struct.Type, %struct.Type* %115, i32 0, i32 8
  %117 = load %struct.Type*, %struct.Type** %116, align 8
  %118 = call %struct.Type* @pointer_to(%struct.Type* noundef %117)
  store %struct.Type* %118, %struct.Type** %12, align 8
  %119 = load %struct.Token*, %struct.Token** %14, align 8
  %120 = load %struct.Type*, %struct.Type** %12, align 8
  %121 = getelementptr inbounds %struct.Type, %struct.Type* %120, i32 0, i32 9
  store %struct.Token* %119, %struct.Token** %121, align 8
  br label %134

122:                                              ; preds = %106
  %123 = load %struct.Type*, %struct.Type** %12, align 8
  %124 = getelementptr inbounds %struct.Type, %struct.Type* %123, i32 0, i32 0
  %125 = load i32, i32* %124, align 8
  %126 = icmp eq i32 %125, 11
  br i1 %126, label %127, label %133

127:                                              ; preds = %122
  %128 = load %struct.Type*, %struct.Type** %12, align 8
  %129 = call %struct.Type* @pointer_to(%struct.Type* noundef %128)
  store %struct.Type* %129, %struct.Type** %12, align 8
  %130 = load %struct.Token*, %struct.Token** %14, align 8
  %131 = load %struct.Type*, %struct.Type** %12, align 8
  %132 = getelementptr inbounds %struct.Type, %struct.Type* %131, i32 0, i32 9
  store %struct.Token* %130, %struct.Token** %132, align 8
  br label %133

133:                                              ; preds = %127, %122
  br label %134

134:                                              ; preds = %133, %114
  %135 = load %struct.Type*, %struct.Type** %12, align 8
  %136 = call %struct.Type* @copy_type(%struct.Type* noundef %135)
  %137 = load %struct.Type*, %struct.Type** %8, align 8
  %138 = getelementptr inbounds %struct.Type, %struct.Type* %137, i32 0, i32 20
  store %struct.Type* %136, %struct.Type** %138, align 8
  store %struct.Type* %136, %struct.Type** %8, align 8
  %139 = load %struct.Token*, %struct.Token** %5, align 8
  %140 = getelementptr inbounds %struct.Token, %struct.Token* %139, i32 0, i32 1
  %141 = load %struct.Token*, %struct.Token** %140, align 8
  store %struct.Token* %141, %struct.Token** %5, align 8
  br label %35, !llvm.loop !28

142:                                              ; preds = %84, %59, %35
  %143 = load %struct.Type*, %struct.Type** %8, align 8
  %144 = icmp eq %struct.Type* %143, %7
  br i1 %144, label %145, label %146

145:                                              ; preds = %142
  store i8 1, i8* %9, align 1
  br label %146

146:                                              ; preds = %145, %142
  %147 = load %struct.Type*, %struct.Type** %6, align 8
  %148 = call %struct.Type* @func_type(%struct.Type* noundef %147)
  store %struct.Type* %148, %struct.Type** %6, align 8
  %149 = getelementptr inbounds %struct.Type, %struct.Type* %7, i32 0, i32 20
  %150 = load %struct.Type*, %struct.Type** %149, align 8
  %151 = load %struct.Type*, %struct.Type** %6, align 8
  %152 = getelementptr inbounds %struct.Type, %struct.Type* %151, i32 0, i32 18
  store %struct.Type* %150, %struct.Type** %152, align 8
  %153 = load i8, i8* %9, align 1
  %154 = trunc i8 %153 to i1
  %155 = load %struct.Type*, %struct.Type** %6, align 8
  %156 = getelementptr inbounds %struct.Type, %struct.Type* %155, i32 0, i32 19
  %157 = zext i1 %154 to i8
  store i8 %157, i8* %156, align 8
  %158 = load %struct.Token*, %struct.Token** %5, align 8
  %159 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %158, %struct.Token** %159, align 8
  %160 = load %struct.Type*, %struct.Type** %6, align 8
  ret %struct.Type* %160
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @func_params(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.Type, align 8
  %9 = alloca %struct.Type*, align 8
  %10 = alloca i8, align 1
  %11 = alloca %struct.Node*, align 8
  %12 = alloca %struct.Type*, align 8
  %13 = alloca %struct.Type*, align 8
  %14 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  %15 = load %struct.Token*, %struct.Token** %6, align 8
  %16 = call zeroext i1 @equal(%struct.Token* noundef %15, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.88, i64 0, i64 0))
  br i1 %16, label %17, label %31

17:                                               ; preds = %3
  %18 = load %struct.Token*, %struct.Token** %6, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 1
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  %21 = call zeroext i1 @equal(%struct.Token* noundef %20, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  br i1 %21, label %22, label %31

22:                                               ; preds = %17
  %23 = load %struct.Token*, %struct.Token** %6, align 8
  %24 = getelementptr inbounds %struct.Token, %struct.Token* %23, i32 0, i32 1
  %25 = load %struct.Token*, %struct.Token** %24, align 8
  %26 = getelementptr inbounds %struct.Token, %struct.Token* %25, i32 0, i32 1
  %27 = load %struct.Token*, %struct.Token** %26, align 8
  %28 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %27, %struct.Token** %28, align 8
  %29 = load %struct.Type*, %struct.Type** %7, align 8
  %30 = call %struct.Type* @func_type(%struct.Type* noundef %29)
  store %struct.Type* %30, %struct.Type** %4, align 8
  br label %147

31:                                               ; preds = %17, %3
  %32 = bitcast %struct.Type* %8 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %32, i8 0, i64 128, i1 false)
  store %struct.Type* %8, %struct.Type** %9, align 8
  store i8 0, i8* %10, align 1
  br label %33

33:                                               ; preds = %121, %31
  %34 = load %struct.Token*, %struct.Token** %6, align 8
  %35 = call zeroext i1 @equal(%struct.Token* noundef %34, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %36 = xor i1 %35, true
  br i1 %36, label %37, label %126

37:                                               ; preds = %33
  %38 = load %struct.Type*, %struct.Type** %9, align 8
  %39 = icmp ne %struct.Type* %38, %8
  br i1 %39, label %40, label %43

40:                                               ; preds = %37
  %41 = load %struct.Token*, %struct.Token** %6, align 8
  %42 = call %struct.Token* @skip(%struct.Token* noundef %41, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %42, %struct.Token** %6, align 8
  br label %43

43:                                               ; preds = %40, %37
  %44 = load %struct.Token*, %struct.Token** %6, align 8
  %45 = call zeroext i1 @equal(%struct.Token* noundef %44, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.120, i64 0, i64 0))
  br i1 %45, label %46, label %52

46:                                               ; preds = %43
  store i8 1, i8* %10, align 1
  %47 = load %struct.Token*, %struct.Token** %6, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 1
  %49 = load %struct.Token*, %struct.Token** %48, align 8
  store %struct.Token* %49, %struct.Token** %6, align 8
  %50 = load %struct.Token*, %struct.Token** %6, align 8
  %51 = call %struct.Token* @skip(%struct.Token* noundef %50, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  br label %126

52:                                               ; preds = %43
  %53 = load %struct.Token*, %struct.Token** %6, align 8
  %54 = getelementptr inbounds %struct.Token, %struct.Token* %53, i32 0, i32 1
  %55 = load %struct.Token*, %struct.Token** %54, align 8
  %56 = call zeroext i1 @equal(%struct.Token* noundef %55, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.72, i64 0, i64 0))
  br i1 %56, label %71, label %57

57:                                               ; preds = %52
  %58 = load %struct.Token*, %struct.Token** %6, align 8
  %59 = call zeroext i1 @equal(%struct.Token* noundef %58, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %59, label %60, label %65

60:                                               ; preds = %57
  %61 = load %struct.Token**, %struct.Token*** %5, align 8
  %62 = load %struct.Token*, %struct.Token** %6, align 8
  %63 = load %struct.Type*, %struct.Type** %7, align 8
  %64 = call zeroext i1 @is_expression(%struct.Token** noundef %61, %struct.Token* noundef %62, %struct.Type* noundef %63)
  br i1 %64, label %71, label %65

65:                                               ; preds = %60, %57
  %66 = load %struct.Token*, %struct.Token** %6, align 8
  %67 = call zeroext i1 @equal(%struct.Token* noundef %66, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.123, i64 0, i64 0))
  br i1 %67, label %71, label %68

68:                                               ; preds = %65
  %69 = load %struct.Token*, %struct.Token** %6, align 8
  %70 = call zeroext i1 @equal(%struct.Token* noundef %69, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.124, i64 0, i64 0))
  br i1 %70, label %71, label %76

71:                                               ; preds = %68, %65, %60, %52
  %72 = load %struct.Token*, %struct.Token** %6, align 8
  %73 = call %struct.Node* @expr(%struct.Token** noundef %6, %struct.Token* noundef %72)
  store %struct.Node* %73, %struct.Node** %11, align 8
  %74 = load %struct.Token*, %struct.Token** %6, align 8
  %75 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %74, %struct.Token** %75, align 8
  br label %126

76:                                               ; preds = %68
  %77 = load %struct.Token*, %struct.Token** %6, align 8
  %78 = call %struct.Type* @declspec(%struct.Token** noundef %6, %struct.Token* noundef %77, %struct.VarAttr* noundef null)
  store %struct.Type* %78, %struct.Type** %12, align 8
  %79 = load %struct.Type*, %struct.Type** %12, align 8
  store %struct.Type* %79, %struct.Type** %13, align 8
  %80 = load %struct.Token*, %struct.Token** %6, align 8
  %81 = load %struct.Type*, %struct.Type** %12, align 8
  %82 = call %struct.Type* @declarator(%struct.Token** noundef %6, %struct.Token* noundef %80, %struct.Type* noundef %81)
  store %struct.Type* %82, %struct.Type** %12, align 8
  %83 = load %struct.Type*, %struct.Type** %12, align 8
  %84 = getelementptr inbounds %struct.Type, %struct.Type* %83, i32 0, i32 0
  %85 = load i32, i32* %84, align 8
  %86 = icmp eq i32 %85, 10
  br i1 %86, label %87, label %93

87:                                               ; preds = %76
  %88 = load %struct.Type*, %struct.Type** %12, align 8
  %89 = getelementptr inbounds %struct.Type, %struct.Type* %88, i32 0, i32 5
  store i8 1, i8* %89, align 2
  %90 = load %struct.Type*, %struct.Type** %13, align 8
  %91 = load %struct.Type*, %struct.Type** %12, align 8
  %92 = getelementptr inbounds %struct.Type, %struct.Type* %91, i32 0, i32 6
  store %struct.Type* %90, %struct.Type** %92, align 8
  br label %93

93:                                               ; preds = %87, %76
  %94 = load %struct.Type*, %struct.Type** %12, align 8
  %95 = getelementptr inbounds %struct.Type, %struct.Type* %94, i32 0, i32 9
  %96 = load %struct.Token*, %struct.Token** %95, align 8
  store %struct.Token* %96, %struct.Token** %14, align 8
  %97 = load %struct.Type*, %struct.Type** %12, align 8
  %98 = getelementptr inbounds %struct.Type, %struct.Type* %97, i32 0, i32 0
  %99 = load i32, i32* %98, align 8
  %100 = icmp eq i32 %99, 12
  br i1 %100, label %101, label %109

101:                                              ; preds = %93
  %102 = load %struct.Type*, %struct.Type** %12, align 8
  %103 = getelementptr inbounds %struct.Type, %struct.Type* %102, i32 0, i32 8
  %104 = load %struct.Type*, %struct.Type** %103, align 8
  %105 = call %struct.Type* @pointer_to(%struct.Type* noundef %104)
  store %struct.Type* %105, %struct.Type** %12, align 8
  %106 = load %struct.Token*, %struct.Token** %14, align 8
  %107 = load %struct.Type*, %struct.Type** %12, align 8
  %108 = getelementptr inbounds %struct.Type, %struct.Type* %107, i32 0, i32 9
  store %struct.Token* %106, %struct.Token** %108, align 8
  br label %121

109:                                              ; preds = %93
  %110 = load %struct.Type*, %struct.Type** %12, align 8
  %111 = getelementptr inbounds %struct.Type, %struct.Type* %110, i32 0, i32 0
  %112 = load i32, i32* %111, align 8
  %113 = icmp eq i32 %112, 11
  br i1 %113, label %114, label %120

114:                                              ; preds = %109
  %115 = load %struct.Type*, %struct.Type** %12, align 8
  %116 = call %struct.Type* @pointer_to(%struct.Type* noundef %115)
  store %struct.Type* %116, %struct.Type** %12, align 8
  %117 = load %struct.Token*, %struct.Token** %14, align 8
  %118 = load %struct.Type*, %struct.Type** %12, align 8
  %119 = getelementptr inbounds %struct.Type, %struct.Type* %118, i32 0, i32 9
  store %struct.Token* %117, %struct.Token** %119, align 8
  br label %120

120:                                              ; preds = %114, %109
  br label %121

121:                                              ; preds = %120, %101
  %122 = load %struct.Type*, %struct.Type** %12, align 8
  %123 = call %struct.Type* @copy_type(%struct.Type* noundef %122)
  %124 = load %struct.Type*, %struct.Type** %9, align 8
  %125 = getelementptr inbounds %struct.Type, %struct.Type* %124, i32 0, i32 20
  store %struct.Type* %123, %struct.Type** %125, align 8
  store %struct.Type* %123, %struct.Type** %9, align 8
  br label %33, !llvm.loop !29

126:                                              ; preds = %71, %46, %33
  %127 = load %struct.Type*, %struct.Type** %9, align 8
  %128 = icmp eq %struct.Type* %127, %8
  br i1 %128, label %129, label %130

129:                                              ; preds = %126
  store i8 1, i8* %10, align 1
  br label %130

130:                                              ; preds = %129, %126
  %131 = load %struct.Type*, %struct.Type** %7, align 8
  %132 = call %struct.Type* @func_type(%struct.Type* noundef %131)
  store %struct.Type* %132, %struct.Type** %7, align 8
  %133 = getelementptr inbounds %struct.Type, %struct.Type* %8, i32 0, i32 20
  %134 = load %struct.Type*, %struct.Type** %133, align 8
  %135 = load %struct.Type*, %struct.Type** %7, align 8
  %136 = getelementptr inbounds %struct.Type, %struct.Type* %135, i32 0, i32 18
  store %struct.Type* %134, %struct.Type** %136, align 8
  %137 = load i8, i8* %10, align 1
  %138 = trunc i8 %137 to i1
  %139 = load %struct.Type*, %struct.Type** %7, align 8
  %140 = getelementptr inbounds %struct.Type, %struct.Type* %139, i32 0, i32 19
  %141 = zext i1 %138 to i8
  store i8 %141, i8* %140, align 8
  %142 = load %struct.Token*, %struct.Token** %6, align 8
  %143 = getelementptr inbounds %struct.Token, %struct.Token* %142, i32 0, i32 1
  %144 = load %struct.Token*, %struct.Token** %143, align 8
  %145 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %144, %struct.Token** %145, align 8
  %146 = load %struct.Type*, %struct.Type** %7, align 8
  store %struct.Type* %146, %struct.Type** %4, align 8
  br label %147

147:                                              ; preds = %130, %22
  %148 = load %struct.Type*, %struct.Type** %4, align 8
  ret %struct.Type* %148
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @array_dimensions(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.VarScope*, align 8
  %9 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  br label %10

10:                                               ; preds = %18, %3
  %11 = load %struct.Token*, %struct.Token** %6, align 8
  %12 = call zeroext i1 @equal(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.98, i64 0, i64 0))
  br i1 %12, label %16, label %13

13:                                               ; preds = %10
  %14 = load %struct.Token*, %struct.Token** %6, align 8
  %15 = call zeroext i1 @equal(%struct.Token* noundef %14, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.107, i64 0, i64 0))
  br label %16

16:                                               ; preds = %13, %10
  %17 = phi i1 [ true, %10 ], [ %15, %13 ]
  br i1 %17, label %18, label %22

18:                                               ; preds = %16
  %19 = load %struct.Token*, %struct.Token** %6, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 1
  %21 = load %struct.Token*, %struct.Token** %20, align 8
  store %struct.Token* %21, %struct.Token** %6, align 8
  br label %10, !llvm.loop !30

22:                                               ; preds = %16
  %23 = load %struct.Token*, %struct.Token** %6, align 8
  %24 = getelementptr inbounds %struct.Token, %struct.Token* %23, i32 0, i32 0
  %25 = load i32, i32* %24, align 16
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %27, label %37

27:                                               ; preds = %22
  %28 = load %struct.Token*, %struct.Token** %6, align 8
  %29 = call %struct.VarScope* @find_var(%struct.Token* noundef %28)
  store %struct.VarScope* %29, %struct.VarScope** %8, align 8
  %30 = load %struct.VarScope*, %struct.VarScope** %8, align 8
  %31 = icmp eq %struct.VarScope* %30, null
  br i1 %31, label %32, label %36

32:                                               ; preds = %27
  %33 = load %struct.Token*, %struct.Token** %6, align 8
  %34 = getelementptr inbounds %struct.Token, %struct.Token* %33, i32 0, i32 1
  %35 = load %struct.Token*, %struct.Token** %34, align 8
  store %struct.Token* %35, %struct.Token** %6, align 8
  br label %36

36:                                               ; preds = %32, %27
  br label %37

37:                                               ; preds = %36, %22
  %38 = load %struct.Token*, %struct.Token** %6, align 8
  %39 = call zeroext i1 @equal(%struct.Token* noundef %38, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.125, i64 0, i64 0))
  br i1 %39, label %40, label %49

40:                                               ; preds = %37
  %41 = load %struct.Token**, %struct.Token*** %5, align 8
  %42 = load %struct.Token*, %struct.Token** %6, align 8
  %43 = getelementptr inbounds %struct.Token, %struct.Token* %42, i32 0, i32 1
  %44 = load %struct.Token*, %struct.Token** %43, align 8
  %45 = load %struct.Type*, %struct.Type** %7, align 8
  %46 = call %struct.Type* @type_suffix(%struct.Token** noundef %41, %struct.Token* noundef %44, %struct.Type* noundef %45)
  store %struct.Type* %46, %struct.Type** %7, align 8
  %47 = load %struct.Type*, %struct.Type** %7, align 8
  %48 = call %struct.Type* @array_of(%struct.Type* noundef %47, i32 noundef -1)
  store %struct.Type* %48, %struct.Type** %4, align 8
  br label %75

49:                                               ; preds = %37
  %50 = load %struct.Token*, %struct.Token** %6, align 8
  %51 = call %struct.Node* @conditional(%struct.Token** noundef %6, %struct.Token* noundef %50)
  store %struct.Node* %51, %struct.Node** %9, align 8
  %52 = load %struct.Token*, %struct.Token** %6, align 8
  %53 = call %struct.Token* @skip(%struct.Token* noundef %52, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.125, i64 0, i64 0))
  store %struct.Token* %53, %struct.Token** %6, align 8
  %54 = load %struct.Token**, %struct.Token*** %5, align 8
  %55 = load %struct.Token*, %struct.Token** %6, align 8
  %56 = load %struct.Type*, %struct.Type** %7, align 8
  %57 = call %struct.Type* @type_suffix(%struct.Token** noundef %54, %struct.Token* noundef %55, %struct.Type* noundef %56)
  store %struct.Type* %57, %struct.Type** %7, align 8
  %58 = load %struct.Type*, %struct.Type** %7, align 8
  %59 = getelementptr inbounds %struct.Type, %struct.Type* %58, i32 0, i32 0
  %60 = load i32, i32* %59, align 8
  %61 = icmp eq i32 %60, 13
  br i1 %61, label %65, label %62

62:                                               ; preds = %49
  %63 = load %struct.Node*, %struct.Node** %9, align 8
  %64 = call zeroext i1 @is_const_expr(%struct.Node* noundef %63)
  br i1 %64, label %69, label %65

65:                                               ; preds = %62, %49
  %66 = load %struct.Type*, %struct.Type** %7, align 8
  %67 = load %struct.Node*, %struct.Node** %9, align 8
  %68 = call %struct.Type* @vla_of(%struct.Type* noundef %66, %struct.Node* noundef %67)
  store %struct.Type* %68, %struct.Type** %4, align 8
  br label %75

69:                                               ; preds = %62
  %70 = load %struct.Type*, %struct.Type** %7, align 8
  %71 = load %struct.Node*, %struct.Node** %9, align 8
  %72 = call i64 @eval(%struct.Node* noundef %71)
  %73 = trunc i64 %72 to i32
  %74 = call %struct.Type* @array_of(%struct.Type* noundef %70, i32 noundef %73)
  store %struct.Type* %74, %struct.Type** %4, align 8
  br label %75

75:                                               ; preds = %69, %65, %40
  %76 = load %struct.Type*, %struct.Type** %4, align 8
  ret %struct.Type* %76
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @is_expression(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  br label %8

8:                                                ; preds = %20, %3
  %9 = load %struct.Token*, %struct.Token** %6, align 8
  %10 = call zeroext i1 @equal(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  %11 = xor i1 %10, true
  br i1 %11, label %12, label %24

12:                                               ; preds = %8
  %13 = load %struct.Token*, %struct.Token** %6, align 8
  %14 = call zeroext i1 @equal(%struct.Token* noundef %13, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.71, i64 0, i64 0))
  br i1 %14, label %15, label %16

15:                                               ; preds = %12
  store i1 true, i1* %4, align 1
  br label %25

16:                                               ; preds = %12
  %17 = load %struct.Token*, %struct.Token** %6, align 8
  %18 = call zeroext i1 @equal(%struct.Token* noundef %17, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.70, i64 0, i64 0))
  br i1 %18, label %19, label %20

19:                                               ; preds = %16
  store i1 true, i1* %4, align 1
  br label %25

20:                                               ; preds = %16
  %21 = load %struct.Token*, %struct.Token** %6, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 1
  %23 = load %struct.Token*, %struct.Token** %22, align 8
  store %struct.Token* %23, %struct.Token** %6, align 8
  br label %8, !llvm.loop !31

24:                                               ; preds = %8
  store i1 false, i1* %4, align 1
  br label %25

25:                                               ; preds = %24, %19, %15
  %26 = load i1, i1* %4, align 1
  ret i1 %26
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @declarator(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.Token*, align 8
  %9 = alloca %struct.Type, align 8
  %10 = alloca %struct.Token*, align 8
  %11 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  %12 = load %struct.Token*, %struct.Token** %6, align 8
  %13 = load %struct.Type*, %struct.Type** %7, align 8
  %14 = call %struct.Type* @pointers(%struct.Token** noundef %6, %struct.Token* noundef %12, %struct.Type* noundef %13)
  store %struct.Type* %14, %struct.Type** %7, align 8
  %15 = load %struct.Token*, %struct.Token** %6, align 8
  %16 = call zeroext i1 @equal(%struct.Token* noundef %15, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %16, label %17, label %45

17:                                               ; preds = %3
  %18 = load %struct.Token*, %struct.Token** %6, align 8
  %19 = getelementptr inbounds %struct.Token, %struct.Token* %18, i32 0, i32 1
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  %21 = call zeroext i1 @is_typename(%struct.Token* noundef %20)
  br i1 %21, label %45, label %22

22:                                               ; preds = %17
  %23 = load %struct.Token*, %struct.Token** %6, align 8
  %24 = getelementptr inbounds %struct.Token, %struct.Token* %23, i32 0, i32 1
  %25 = load %struct.Token*, %struct.Token** %24, align 8
  %26 = call zeroext i1 @equal(%struct.Token* noundef %25, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  br i1 %26, label %45, label %27

27:                                               ; preds = %22
  %28 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %28, %struct.Token** %8, align 8
  %29 = bitcast %struct.Type* %9 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %29, i8 0, i64 128, i1 false)
  %30 = load %struct.Token*, %struct.Token** %8, align 8
  %31 = getelementptr inbounds %struct.Token, %struct.Token* %30, i32 0, i32 1
  %32 = load %struct.Token*, %struct.Token** %31, align 8
  %33 = call %struct.Type* @declarator(%struct.Token** noundef %6, %struct.Token* noundef %32, %struct.Type* noundef %9)
  %34 = load %struct.Token*, %struct.Token** %6, align 8
  %35 = call %struct.Token* @skip(%struct.Token* noundef %34, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %35, %struct.Token** %6, align 8
  %36 = load %struct.Token**, %struct.Token*** %5, align 8
  %37 = load %struct.Token*, %struct.Token** %6, align 8
  %38 = load %struct.Type*, %struct.Type** %7, align 8
  %39 = call %struct.Type* @type_suffix(%struct.Token** noundef %36, %struct.Token* noundef %37, %struct.Type* noundef %38)
  store %struct.Type* %39, %struct.Type** %7, align 8
  %40 = load %struct.Token*, %struct.Token** %8, align 8
  %41 = getelementptr inbounds %struct.Token, %struct.Token* %40, i32 0, i32 1
  %42 = load %struct.Token*, %struct.Token** %41, align 8
  %43 = load %struct.Type*, %struct.Type** %7, align 8
  %44 = call %struct.Type* @declarator(%struct.Token** noundef %6, %struct.Token* noundef %42, %struct.Type* noundef %43)
  store %struct.Type* %44, %struct.Type** %4, align 8
  br label %68

45:                                               ; preds = %22, %17, %3
  store %struct.Token* null, %struct.Token** %10, align 8
  %46 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %46, %struct.Token** %11, align 8
  %47 = load %struct.Token*, %struct.Token** %6, align 8
  %48 = getelementptr inbounds %struct.Token, %struct.Token* %47, i32 0, i32 0
  %49 = load i32, i32* %48, align 16
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %51, label %56

51:                                               ; preds = %45
  %52 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %52, %struct.Token** %10, align 8
  %53 = load %struct.Token*, %struct.Token** %6, align 8
  %54 = getelementptr inbounds %struct.Token, %struct.Token* %53, i32 0, i32 1
  %55 = load %struct.Token*, %struct.Token** %54, align 8
  store %struct.Token* %55, %struct.Token** %6, align 8
  br label %56

56:                                               ; preds = %51, %45
  %57 = load %struct.Token**, %struct.Token*** %5, align 8
  %58 = load %struct.Token*, %struct.Token** %6, align 8
  %59 = load %struct.Type*, %struct.Type** %7, align 8
  %60 = call %struct.Type* @type_suffix(%struct.Token** noundef %57, %struct.Token* noundef %58, %struct.Type* noundef %59)
  store %struct.Type* %60, %struct.Type** %7, align 8
  %61 = load %struct.Token*, %struct.Token** %10, align 8
  %62 = load %struct.Type*, %struct.Type** %7, align 8
  %63 = getelementptr inbounds %struct.Type, %struct.Type* %62, i32 0, i32 9
  store %struct.Token* %61, %struct.Token** %63, align 8
  %64 = load %struct.Token*, %struct.Token** %11, align 8
  %65 = load %struct.Type*, %struct.Type** %7, align 8
  %66 = getelementptr inbounds %struct.Type, %struct.Type* %65, i32 0, i32 10
  store %struct.Token* %64, %struct.Token** %66, align 8
  %67 = load %struct.Type*, %struct.Type** %7, align 8
  store %struct.Type* %67, %struct.Type** %4, align 8
  br label %68

68:                                               ; preds = %56, %27
  %69 = load %struct.Type*, %struct.Type** %4, align 8
  ret %struct.Type* %69
}

declare %struct.Type* @func_type(%struct.Type* noundef) #1

declare %struct.Type* @array_of(%struct.Type* noundef, i32 noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @is_const_expr(%struct.Node* noundef %0) #0 {
  %2 = alloca i1, align 1
  %3 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %3, align 8
  %4 = load %struct.Node*, %struct.Node** %3, align 8
  call void @add_type(%struct.Node* noundef %4)
  %5 = load %struct.Node*, %struct.Node** %3, align 8
  %6 = getelementptr inbounds %struct.Node, %struct.Node* %5, i32 0, i32 0
  %7 = load i32, i32* %6, align 16
  switch i32 %7, label %54 [
    i32 1, label %8
    i32 2, label %8
    i32 3, label %8
    i32 4, label %8
    i32 7, label %8
    i32 8, label %8
    i32 9, label %8
    i32 10, label %8
    i32 11, label %8
    i32 12, label %8
    i32 13, label %8
    i32 14, label %8
    i32 15, label %8
    i32 24, label %8
    i32 25, label %8
    i32 17, label %20
    i32 18, label %43
    i32 5, label %48
    i32 22, label %48
    i32 23, label %48
    i32 43, label %48
    i32 42, label %53
  ]

8:                                                ; preds = %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1, %1
  %9 = load %struct.Node*, %struct.Node** %3, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 4
  %11 = load %struct.Node*, %struct.Node** %10, align 16
  %12 = call zeroext i1 @is_const_expr(%struct.Node* noundef %11)
  br i1 %12, label %13, label %18

13:                                               ; preds = %8
  %14 = load %struct.Node*, %struct.Node** %3, align 8
  %15 = getelementptr inbounds %struct.Node, %struct.Node* %14, i32 0, i32 5
  %16 = load %struct.Node*, %struct.Node** %15, align 8
  %17 = call zeroext i1 @is_const_expr(%struct.Node* noundef %16)
  br label %18

18:                                               ; preds = %13, %8
  %19 = phi i1 [ false, %8 ], [ %17, %13 ]
  store i1 %19, i1* %2, align 1
  br label %55

20:                                               ; preds = %1
  %21 = load %struct.Node*, %struct.Node** %3, align 8
  %22 = getelementptr inbounds %struct.Node, %struct.Node* %21, i32 0, i32 6
  %23 = load %struct.Node*, %struct.Node** %22, align 16
  %24 = call zeroext i1 @is_const_expr(%struct.Node* noundef %23)
  br i1 %24, label %26, label %25

25:                                               ; preds = %20
  store i1 false, i1* %2, align 1
  br label %55

26:                                               ; preds = %20
  %27 = load %struct.Node*, %struct.Node** %3, align 8
  %28 = getelementptr inbounds %struct.Node, %struct.Node* %27, i32 0, i32 6
  %29 = load %struct.Node*, %struct.Node** %28, align 16
  %30 = call i64 @eval(%struct.Node* noundef %29)
  %31 = icmp ne i64 %30, 0
  br i1 %31, label %32, label %36

32:                                               ; preds = %26
  %33 = load %struct.Node*, %struct.Node** %3, align 8
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 7
  %35 = load %struct.Node*, %struct.Node** %34, align 8
  br label %40

36:                                               ; preds = %26
  %37 = load %struct.Node*, %struct.Node** %3, align 8
  %38 = getelementptr inbounds %struct.Node, %struct.Node* %37, i32 0, i32 8
  %39 = load %struct.Node*, %struct.Node** %38, align 16
  br label %40

40:                                               ; preds = %36, %32
  %41 = phi %struct.Node* [ %35, %32 ], [ %39, %36 ]
  %42 = call zeroext i1 @is_const_expr(%struct.Node* noundef %41)
  store i1 %42, i1* %2, align 1
  br label %55

43:                                               ; preds = %1
  %44 = load %struct.Node*, %struct.Node** %3, align 8
  %45 = getelementptr inbounds %struct.Node, %struct.Node* %44, i32 0, i32 5
  %46 = load %struct.Node*, %struct.Node** %45, align 8
  %47 = call zeroext i1 @is_const_expr(%struct.Node* noundef %46)
  store i1 %47, i1* %2, align 1
  br label %55

48:                                               ; preds = %1, %1, %1, %1
  %49 = load %struct.Node*, %struct.Node** %3, align 8
  %50 = getelementptr inbounds %struct.Node, %struct.Node* %49, i32 0, i32 4
  %51 = load %struct.Node*, %struct.Node** %50, align 16
  %52 = call zeroext i1 @is_const_expr(%struct.Node* noundef %51)
  store i1 %52, i1* %2, align 1
  br label %55

53:                                               ; preds = %1
  store i1 true, i1* %2, align 1
  br label %55

54:                                               ; preds = %1
  store i1 false, i1* %2, align 1
  br label %55

55:                                               ; preds = %54, %53, %48, %43, %40, %25, %18
  %56 = load i1, i1* %2, align 1
  ret i1 %56
}

declare %struct.Type* @vla_of(%struct.Type* noundef, %struct.Node* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_unary(i32 noundef %0, %struct.Node* noundef %1, %struct.Token* noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Node*, align 8
  store i32 %0, i32* %4, align 4
  store %struct.Node* %1, %struct.Node** %5, align 8
  store %struct.Token* %2, %struct.Token** %6, align 8
  %8 = load i32, i32* %4, align 4
  %9 = load %struct.Token*, %struct.Token** %6, align 8
  %10 = call %struct.Node* @new_node(i32 noundef %8, %struct.Token* noundef %9)
  store %struct.Node* %10, %struct.Node** %7, align 8
  %11 = load i8, i8* @isDotfile, align 1
  %12 = trunc i8 %11 to i1
  br i1 %12, label %13, label %33

13:                                               ; preds = %3
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %15 = icmp ne %struct._IO_FILE* %14, null
  br i1 %15, label %16, label %33

16:                                               ; preds = %13
  %17 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %18 = load %struct.Node*, %struct.Node** %7, align 8
  %19 = getelementptr inbounds %struct.Node, %struct.Node* %18, i32 0, i32 0
  %20 = load i32, i32* %19, align 16
  %21 = call i8* @nodekind2str(i32 noundef %20)
  %22 = load %struct.Node*, %struct.Node** %7, align 8
  %23 = getelementptr inbounds %struct.Node, %struct.Node* %22, i32 0, i32 36
  %24 = load i32, i32* %23, align 16
  %25 = load %struct.Node*, %struct.Node** %5, align 8
  %26 = getelementptr inbounds %struct.Node, %struct.Node* %25, i32 0, i32 0
  %27 = load i32, i32* %26, align 16
  %28 = call i8* @nodekind2str(i32 noundef %27)
  %29 = load %struct.Node*, %struct.Node** %5, align 8
  %30 = getelementptr inbounds %struct.Node, %struct.Node* %29, i32 0, i32 36
  %31 = load i32, i32* %30, align 16
  %32 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %17, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %21, i32 noundef %24, i8* noundef %28, i32 noundef %31)
  br label %33

33:                                               ; preds = %16, %13, %3
  %34 = load %struct.Node*, %struct.Node** %5, align 8
  %35 = load %struct.Node*, %struct.Node** %7, align 8
  %36 = getelementptr inbounds %struct.Node, %struct.Node* %35, i32 0, i32 4
  store %struct.Node* %34, %struct.Node** %36, align 16
  %37 = load %struct.Node*, %struct.Node** %7, align 8
  ret %struct.Node* %37
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @to_assign(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Obj*, align 8
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Node*, align 8
  %9 = alloca %struct.Node*, align 8
  %10 = alloca %struct.Node, align 16
  %11 = alloca %struct.Node*, align 8
  %12 = alloca %struct.Obj*, align 8
  %13 = alloca %struct.Obj*, align 8
  %14 = alloca %struct.Obj*, align 8
  %15 = alloca %struct.Obj*, align 8
  %16 = alloca %struct.Obj*, align 8
  %17 = alloca %struct.Node*, align 8
  %18 = alloca %struct.Node*, align 8
  %19 = alloca %struct.Node*, align 8
  %20 = alloca %struct.Node*, align 8
  %21 = alloca %struct.Obj*, align 8
  %22 = alloca %struct.Node*, align 8
  %23 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %3, align 8
  %24 = load %struct.Node*, %struct.Node** %3, align 8
  %25 = getelementptr inbounds %struct.Node, %struct.Node* %24, i32 0, i32 4
  %26 = load %struct.Node*, %struct.Node** %25, align 16
  call void @add_type(%struct.Node* noundef %26)
  %27 = load %struct.Node*, %struct.Node** %3, align 8
  %28 = getelementptr inbounds %struct.Node, %struct.Node* %27, i32 0, i32 5
  %29 = load %struct.Node*, %struct.Node** %28, align 8
  call void @add_type(%struct.Node* noundef %29)
  %30 = load %struct.Node*, %struct.Node** %3, align 8
  %31 = getelementptr inbounds %struct.Node, %struct.Node* %30, i32 0, i32 3
  %32 = load %struct.Token*, %struct.Token** %31, align 8
  store %struct.Token* %32, %struct.Token** %4, align 8
  %33 = load %struct.Node*, %struct.Node** %3, align 8
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 4
  %35 = load %struct.Node*, %struct.Node** %34, align 16
  %36 = getelementptr inbounds %struct.Node, %struct.Node* %35, i32 0, i32 0
  %37 = load i32, i32* %36, align 16
  %38 = icmp eq i32 %37, 19
  br i1 %38, label %39, label %105

39:                                               ; preds = %1
  %40 = load %struct.Node*, %struct.Node** %3, align 8
  %41 = getelementptr inbounds %struct.Node, %struct.Node* %40, i32 0, i32 4
  %42 = load %struct.Node*, %struct.Node** %41, align 16
  %43 = getelementptr inbounds %struct.Node, %struct.Node* %42, i32 0, i32 4
  %44 = load %struct.Node*, %struct.Node** %43, align 16
  %45 = getelementptr inbounds %struct.Node, %struct.Node* %44, i32 0, i32 2
  %46 = load %struct.Type*, %struct.Type** %45, align 16
  %47 = call %struct.Type* @pointer_to(%struct.Type* noundef %46)
  %48 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %47, i8* noundef null)
  store %struct.Obj* %48, %struct.Obj** %5, align 8
  %49 = load %struct.Obj*, %struct.Obj** %5, align 8
  %50 = load %struct.Token*, %struct.Token** %4, align 8
  %51 = call %struct.Node* @new_var_node(%struct.Obj* noundef %49, %struct.Token* noundef %50)
  %52 = load %struct.Node*, %struct.Node** %3, align 8
  %53 = getelementptr inbounds %struct.Node, %struct.Node* %52, i32 0, i32 4
  %54 = load %struct.Node*, %struct.Node** %53, align 16
  %55 = getelementptr inbounds %struct.Node, %struct.Node* %54, i32 0, i32 4
  %56 = load %struct.Node*, %struct.Node** %55, align 16
  %57 = load %struct.Token*, %struct.Token** %4, align 8
  %58 = call %struct.Node* @new_unary(i32 noundef 20, %struct.Node* noundef %56, %struct.Token* noundef %57)
  %59 = load %struct.Token*, %struct.Token** %4, align 8
  %60 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %51, %struct.Node* noundef %58, %struct.Token* noundef %59)
  store %struct.Node* %60, %struct.Node** %6, align 8
  %61 = load %struct.Obj*, %struct.Obj** %5, align 8
  %62 = load %struct.Token*, %struct.Token** %4, align 8
  %63 = call %struct.Node* @new_var_node(%struct.Obj* noundef %61, %struct.Token* noundef %62)
  %64 = load %struct.Token*, %struct.Token** %4, align 8
  %65 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %63, %struct.Token* noundef %64)
  %66 = load %struct.Token*, %struct.Token** %4, align 8
  %67 = call %struct.Node* @new_unary(i32 noundef 19, %struct.Node* noundef %65, %struct.Token* noundef %66)
  store %struct.Node* %67, %struct.Node** %7, align 8
  %68 = load %struct.Node*, %struct.Node** %3, align 8
  %69 = getelementptr inbounds %struct.Node, %struct.Node* %68, i32 0, i32 4
  %70 = load %struct.Node*, %struct.Node** %69, align 16
  %71 = getelementptr inbounds %struct.Node, %struct.Node* %70, i32 0, i32 14
  %72 = load %struct.Member*, %struct.Member** %71, align 16
  %73 = load %struct.Node*, %struct.Node** %7, align 8
  %74 = getelementptr inbounds %struct.Node, %struct.Node* %73, i32 0, i32 14
  store %struct.Member* %72, %struct.Member** %74, align 16
  %75 = load %struct.Obj*, %struct.Obj** %5, align 8
  %76 = load %struct.Token*, %struct.Token** %4, align 8
  %77 = call %struct.Node* @new_var_node(%struct.Obj* noundef %75, %struct.Token* noundef %76)
  %78 = load %struct.Token*, %struct.Token** %4, align 8
  %79 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %77, %struct.Token* noundef %78)
  %80 = load %struct.Token*, %struct.Token** %4, align 8
  %81 = call %struct.Node* @new_unary(i32 noundef 19, %struct.Node* noundef %79, %struct.Token* noundef %80)
  store %struct.Node* %81, %struct.Node** %8, align 8
  %82 = load %struct.Node*, %struct.Node** %3, align 8
  %83 = getelementptr inbounds %struct.Node, %struct.Node* %82, i32 0, i32 4
  %84 = load %struct.Node*, %struct.Node** %83, align 16
  %85 = getelementptr inbounds %struct.Node, %struct.Node* %84, i32 0, i32 14
  %86 = load %struct.Member*, %struct.Member** %85, align 16
  %87 = load %struct.Node*, %struct.Node** %8, align 8
  %88 = getelementptr inbounds %struct.Node, %struct.Node* %87, i32 0, i32 14
  store %struct.Member* %86, %struct.Member** %88, align 16
  %89 = load %struct.Node*, %struct.Node** %7, align 8
  %90 = load %struct.Node*, %struct.Node** %3, align 8
  %91 = getelementptr inbounds %struct.Node, %struct.Node* %90, i32 0, i32 0
  %92 = load i32, i32* %91, align 16
  %93 = load %struct.Node*, %struct.Node** %8, align 8
  %94 = load %struct.Node*, %struct.Node** %3, align 8
  %95 = getelementptr inbounds %struct.Node, %struct.Node* %94, i32 0, i32 5
  %96 = load %struct.Node*, %struct.Node** %95, align 8
  %97 = load %struct.Token*, %struct.Token** %4, align 8
  %98 = call %struct.Node* @new_binary(i32 noundef %92, %struct.Node* noundef %93, %struct.Node* noundef %96, %struct.Token* noundef %97)
  %99 = load %struct.Token*, %struct.Token** %4, align 8
  %100 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %89, %struct.Node* noundef %98, %struct.Token* noundef %99)
  store %struct.Node* %100, %struct.Node** %9, align 8
  %101 = load %struct.Node*, %struct.Node** %6, align 8
  %102 = load %struct.Node*, %struct.Node** %9, align 8
  %103 = load %struct.Token*, %struct.Token** %4, align 8
  %104 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %101, %struct.Node* noundef %102, %struct.Token* noundef %103)
  store %struct.Node* %104, %struct.Node** %2, align 8
  br label %314

105:                                              ; preds = %1
  %106 = load %struct.Node*, %struct.Node** %3, align 8
  %107 = getelementptr inbounds %struct.Node, %struct.Node* %106, i32 0, i32 4
  %108 = load %struct.Node*, %struct.Node** %107, align 16
  %109 = getelementptr inbounds %struct.Node, %struct.Node* %108, i32 0, i32 2
  %110 = load %struct.Type*, %struct.Type** %109, align 16
  %111 = getelementptr inbounds %struct.Type, %struct.Type* %110, i32 0, i32 4
  %112 = load i8, i8* %111, align 1
  %113 = trunc i8 %112 to i1
  br i1 %113, label %119, label %114

114:                                              ; preds = %105
  %115 = load %struct.Node*, %struct.Node** %3, align 8
  %116 = getelementptr inbounds %struct.Node, %struct.Node* %115, i32 0, i32 32
  %117 = load i8, i8* %116, align 16
  %118 = trunc i8 %117 to i1
  br i1 %118, label %119, label %272

119:                                              ; preds = %114, %105
  %120 = bitcast %struct.Node* %10 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %120, i8 0, i64 320, i1 false)
  store %struct.Node* %10, %struct.Node** %11, align 8
  %121 = load %struct.Node*, %struct.Node** %3, align 8
  %122 = getelementptr inbounds %struct.Node, %struct.Node* %121, i32 0, i32 4
  %123 = load %struct.Node*, %struct.Node** %122, align 16
  %124 = getelementptr inbounds %struct.Node, %struct.Node* %123, i32 0, i32 2
  %125 = load %struct.Type*, %struct.Type** %124, align 16
  %126 = call %struct.Type* @pointer_to(%struct.Type* noundef %125)
  %127 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %126, i8* noundef null)
  store %struct.Obj* %127, %struct.Obj** %12, align 8
  %128 = load %struct.Node*, %struct.Node** %3, align 8
  %129 = getelementptr inbounds %struct.Node, %struct.Node* %128, i32 0, i32 5
  %130 = load %struct.Node*, %struct.Node** %129, align 8
  %131 = getelementptr inbounds %struct.Node, %struct.Node* %130, i32 0, i32 2
  %132 = load %struct.Type*, %struct.Type** %131, align 16
  %133 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %132, i8* noundef null)
  store %struct.Obj* %133, %struct.Obj** %13, align 8
  %134 = load %struct.Node*, %struct.Node** %3, align 8
  %135 = getelementptr inbounds %struct.Node, %struct.Node* %134, i32 0, i32 4
  %136 = load %struct.Node*, %struct.Node** %135, align 16
  %137 = getelementptr inbounds %struct.Node, %struct.Node* %136, i32 0, i32 2
  %138 = load %struct.Type*, %struct.Type** %137, align 16
  %139 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %138, i8* noundef null)
  store %struct.Obj* %139, %struct.Obj** %14, align 8
  %140 = load %struct.Node*, %struct.Node** %3, align 8
  %141 = getelementptr inbounds %struct.Node, %struct.Node* %140, i32 0, i32 4
  %142 = load %struct.Node*, %struct.Node** %141, align 16
  %143 = getelementptr inbounds %struct.Node, %struct.Node* %142, i32 0, i32 2
  %144 = load %struct.Type*, %struct.Type** %143, align 16
  %145 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %144, i8* noundef null)
  store %struct.Obj* %145, %struct.Obj** %15, align 8
  %146 = load %struct.Node*, %struct.Node** %3, align 8
  %147 = getelementptr inbounds %struct.Node, %struct.Node* %146, i32 0, i32 32
  %148 = load i8, i8* %147, align 16
  %149 = trunc i8 %148 to i1
  br i1 %149, label %150, label %152

150:                                              ; preds = %119
  %151 = load %struct.Obj*, %struct.Obj** %14, align 8
  br label %154

152:                                              ; preds = %119
  %153 = load %struct.Obj*, %struct.Obj** %15, align 8
  br label %154

154:                                              ; preds = %152, %150
  %155 = phi %struct.Obj* [ %151, %150 ], [ %153, %152 ]
  store %struct.Obj* %155, %struct.Obj** %16, align 8
  %156 = load %struct.Obj*, %struct.Obj** %12, align 8
  %157 = load %struct.Token*, %struct.Token** %4, align 8
  %158 = call %struct.Node* @new_var_node(%struct.Obj* noundef %156, %struct.Token* noundef %157)
  %159 = load %struct.Node*, %struct.Node** %3, align 8
  %160 = getelementptr inbounds %struct.Node, %struct.Node* %159, i32 0, i32 4
  %161 = load %struct.Node*, %struct.Node** %160, align 16
  %162 = load %struct.Token*, %struct.Token** %4, align 8
  %163 = call %struct.Node* @new_unary(i32 noundef 20, %struct.Node* noundef %161, %struct.Token* noundef %162)
  %164 = load %struct.Token*, %struct.Token** %4, align 8
  %165 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %158, %struct.Node* noundef %163, %struct.Token* noundef %164)
  %166 = load %struct.Token*, %struct.Token** %4, align 8
  %167 = call %struct.Node* @new_unary(i32 noundef 38, %struct.Node* noundef %165, %struct.Token* noundef %166)
  %168 = load %struct.Node*, %struct.Node** %11, align 8
  %169 = getelementptr inbounds %struct.Node, %struct.Node* %168, i32 0, i32 1
  store %struct.Node* %167, %struct.Node** %169, align 8
  store %struct.Node* %167, %struct.Node** %11, align 8
  %170 = load %struct.Obj*, %struct.Obj** %13, align 8
  %171 = load %struct.Token*, %struct.Token** %4, align 8
  %172 = call %struct.Node* @new_var_node(%struct.Obj* noundef %170, %struct.Token* noundef %171)
  %173 = load %struct.Node*, %struct.Node** %3, align 8
  %174 = getelementptr inbounds %struct.Node, %struct.Node* %173, i32 0, i32 5
  %175 = load %struct.Node*, %struct.Node** %174, align 8
  %176 = load %struct.Token*, %struct.Token** %4, align 8
  %177 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %172, %struct.Node* noundef %175, %struct.Token* noundef %176)
  %178 = load %struct.Token*, %struct.Token** %4, align 8
  %179 = call %struct.Node* @new_unary(i32 noundef 38, %struct.Node* noundef %177, %struct.Token* noundef %178)
  %180 = load %struct.Node*, %struct.Node** %11, align 8
  %181 = getelementptr inbounds %struct.Node, %struct.Node* %180, i32 0, i32 1
  store %struct.Node* %179, %struct.Node** %181, align 8
  store %struct.Node* %179, %struct.Node** %11, align 8
  %182 = load %struct.Obj*, %struct.Obj** %14, align 8
  %183 = load %struct.Token*, %struct.Token** %4, align 8
  %184 = call %struct.Node* @new_var_node(%struct.Obj* noundef %182, %struct.Token* noundef %183)
  %185 = load %struct.Obj*, %struct.Obj** %12, align 8
  %186 = load %struct.Token*, %struct.Token** %4, align 8
  %187 = call %struct.Node* @new_var_node(%struct.Obj* noundef %185, %struct.Token* noundef %186)
  %188 = load %struct.Token*, %struct.Token** %4, align 8
  %189 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %187, %struct.Token* noundef %188)
  %190 = load %struct.Token*, %struct.Token** %4, align 8
  %191 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %184, %struct.Node* noundef %189, %struct.Token* noundef %190)
  %192 = load %struct.Token*, %struct.Token** %4, align 8
  %193 = call %struct.Node* @new_unary(i32 noundef 38, %struct.Node* noundef %191, %struct.Token* noundef %192)
  %194 = load %struct.Node*, %struct.Node** %11, align 8
  %195 = getelementptr inbounds %struct.Node, %struct.Node* %194, i32 0, i32 1
  store %struct.Node* %193, %struct.Node** %195, align 8
  store %struct.Node* %193, %struct.Node** %11, align 8
  %196 = load %struct.Token*, %struct.Token** %4, align 8
  %197 = call %struct.Node* @new_node(i32 noundef 29, %struct.Token* noundef %196)
  store %struct.Node* %197, %struct.Node** %17, align 8
  %198 = call i8* @new_unique_name()
  %199 = load %struct.Node*, %struct.Node** %17, align 8
  %200 = getelementptr inbounds %struct.Node, %struct.Node* %199, i32 0, i32 11
  store i8* %198, i8** %200, align 8
  %201 = call i8* @new_unique_name()
  %202 = load %struct.Node*, %struct.Node** %17, align 8
  %203 = getelementptr inbounds %struct.Node, %struct.Node* %202, i32 0, i32 12
  store i8* %201, i8** %203, align 16
  %204 = load %struct.Obj*, %struct.Obj** %15, align 8
  %205 = load %struct.Token*, %struct.Token** %4, align 8
  %206 = call %struct.Node* @new_var_node(%struct.Obj* noundef %204, %struct.Token* noundef %205)
  %207 = load %struct.Node*, %struct.Node** %3, align 8
  %208 = getelementptr inbounds %struct.Node, %struct.Node* %207, i32 0, i32 0
  %209 = load i32, i32* %208, align 16
  %210 = load %struct.Obj*, %struct.Obj** %14, align 8
  %211 = load %struct.Token*, %struct.Token** %4, align 8
  %212 = call %struct.Node* @new_var_node(%struct.Obj* noundef %210, %struct.Token* noundef %211)
  %213 = load %struct.Obj*, %struct.Obj** %13, align 8
  %214 = load %struct.Token*, %struct.Token** %4, align 8
  %215 = call %struct.Node* @new_var_node(%struct.Obj* noundef %213, %struct.Token* noundef %214)
  %216 = load %struct.Token*, %struct.Token** %4, align 8
  %217 = call %struct.Node* @new_binary(i32 noundef %209, %struct.Node* noundef %212, %struct.Node* noundef %215, %struct.Token* noundef %216)
  %218 = load %struct.Token*, %struct.Token** %4, align 8
  %219 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %206, %struct.Node* noundef %217, %struct.Token* noundef %218)
  store %struct.Node* %219, %struct.Node** %18, align 8
  %220 = load %struct.Token*, %struct.Token** %4, align 8
  %221 = call %struct.Node* @new_node(i32 noundef 32, %struct.Token* noundef %220)
  %222 = load %struct.Node*, %struct.Node** %17, align 8
  %223 = getelementptr inbounds %struct.Node, %struct.Node* %222, i32 0, i32 7
  store %struct.Node* %221, %struct.Node** %223, align 8
  %224 = load %struct.Node*, %struct.Node** %18, align 8
  %225 = load %struct.Token*, %struct.Token** %4, align 8
  %226 = call %struct.Node* @new_unary(i32 noundef 38, %struct.Node* noundef %224, %struct.Token* noundef %225)
  %227 = load %struct.Node*, %struct.Node** %17, align 8
  %228 = getelementptr inbounds %struct.Node, %struct.Node* %227, i32 0, i32 7
  %229 = load %struct.Node*, %struct.Node** %228, align 8
  %230 = getelementptr inbounds %struct.Node, %struct.Node* %229, i32 0, i32 13
  store %struct.Node* %226, %struct.Node** %230, align 8
  %231 = load %struct.Token*, %struct.Token** %4, align 8
  %232 = call %struct.Node* @new_node(i32 noundef 46, %struct.Token* noundef %231)
  store %struct.Node* %232, %struct.Node** %19, align 8
  %233 = load %struct.Obj*, %struct.Obj** %12, align 8
  %234 = load %struct.Token*, %struct.Token** %4, align 8
  %235 = call %struct.Node* @new_var_node(%struct.Obj* noundef %233, %struct.Token* noundef %234)
  %236 = load %struct.Node*, %struct.Node** %19, align 8
  %237 = getelementptr inbounds %struct.Node, %struct.Node* %236, i32 0, i32 27
  store %struct.Node* %235, %struct.Node** %237, align 8
  %238 = load %struct.Obj*, %struct.Obj** %14, align 8
  %239 = load %struct.Token*, %struct.Token** %4, align 8
  %240 = call %struct.Node* @new_var_node(%struct.Obj* noundef %238, %struct.Token* noundef %239)
  %241 = load %struct.Token*, %struct.Token** %4, align 8
  %242 = call %struct.Node* @new_unary(i32 noundef 20, %struct.Node* noundef %240, %struct.Token* noundef %241)
  %243 = load %struct.Node*, %struct.Node** %19, align 8
  %244 = getelementptr inbounds %struct.Node, %struct.Node* %243, i32 0, i32 28
  store %struct.Node* %242, %struct.Node** %244, align 16
  %245 = load %struct.Obj*, %struct.Obj** %15, align 8
  %246 = load %struct.Token*, %struct.Token** %4, align 8
  %247 = call %struct.Node* @new_var_node(%struct.Obj* noundef %245, %struct.Token* noundef %246)
  %248 = load %struct.Node*, %struct.Node** %19, align 8
  %249 = getelementptr inbounds %struct.Node, %struct.Node* %248, i32 0, i32 29
  store %struct.Node* %247, %struct.Node** %249, align 8
  %250 = load %struct.Node*, %struct.Node** %19, align 8
  %251 = load %struct.Token*, %struct.Token** %4, align 8
  %252 = call %struct.Node* @new_unary(i32 noundef 22, %struct.Node* noundef %250, %struct.Token* noundef %251)
  %253 = load %struct.Node*, %struct.Node** %17, align 8
  %254 = getelementptr inbounds %struct.Node, %struct.Node* %253, i32 0, i32 6
  store %struct.Node* %252, %struct.Node** %254, align 16
  %255 = load %struct.Node*, %struct.Node** %17, align 8
  %256 = load %struct.Node*, %struct.Node** %11, align 8
  %257 = getelementptr inbounds %struct.Node, %struct.Node* %256, i32 0, i32 1
  store %struct.Node* %255, %struct.Node** %257, align 8
  store %struct.Node* %255, %struct.Node** %11, align 8
  %258 = load %struct.Obj*, %struct.Obj** %16, align 8
  %259 = load %struct.Token*, %struct.Token** %4, align 8
  %260 = call %struct.Node* @new_var_node(%struct.Obj* noundef %258, %struct.Token* noundef %259)
  %261 = load %struct.Token*, %struct.Token** %4, align 8
  %262 = call %struct.Node* @new_unary(i32 noundef 38, %struct.Node* noundef %260, %struct.Token* noundef %261)
  %263 = load %struct.Node*, %struct.Node** %11, align 8
  %264 = getelementptr inbounds %struct.Node, %struct.Node* %263, i32 0, i32 1
  store %struct.Node* %262, %struct.Node** %264, align 8
  store %struct.Node* %262, %struct.Node** %11, align 8
  %265 = load %struct.Token*, %struct.Token** %4, align 8
  %266 = call %struct.Node* @new_node(i32 noundef 39, %struct.Token* noundef %265)
  store %struct.Node* %266, %struct.Node** %20, align 8
  %267 = getelementptr inbounds %struct.Node, %struct.Node* %10, i32 0, i32 1
  %268 = load %struct.Node*, %struct.Node** %267, align 8
  %269 = load %struct.Node*, %struct.Node** %20, align 8
  %270 = getelementptr inbounds %struct.Node, %struct.Node* %269, i32 0, i32 13
  store %struct.Node* %268, %struct.Node** %270, align 8
  %271 = load %struct.Node*, %struct.Node** %20, align 8
  store %struct.Node* %271, %struct.Node** %2, align 8
  br label %314

272:                                              ; preds = %114
  %273 = load %struct.Node*, %struct.Node** %3, align 8
  %274 = getelementptr inbounds %struct.Node, %struct.Node* %273, i32 0, i32 4
  %275 = load %struct.Node*, %struct.Node** %274, align 16
  %276 = getelementptr inbounds %struct.Node, %struct.Node* %275, i32 0, i32 2
  %277 = load %struct.Type*, %struct.Type** %276, align 16
  %278 = call %struct.Type* @pointer_to(%struct.Type* noundef %277)
  %279 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %278, i8* noundef null)
  store %struct.Obj* %279, %struct.Obj** %21, align 8
  %280 = load %struct.Obj*, %struct.Obj** %21, align 8
  %281 = load %struct.Token*, %struct.Token** %4, align 8
  %282 = call %struct.Node* @new_var_node(%struct.Obj* noundef %280, %struct.Token* noundef %281)
  %283 = load %struct.Node*, %struct.Node** %3, align 8
  %284 = getelementptr inbounds %struct.Node, %struct.Node* %283, i32 0, i32 4
  %285 = load %struct.Node*, %struct.Node** %284, align 16
  %286 = load %struct.Token*, %struct.Token** %4, align 8
  %287 = call %struct.Node* @new_unary(i32 noundef 20, %struct.Node* noundef %285, %struct.Token* noundef %286)
  %288 = load %struct.Token*, %struct.Token** %4, align 8
  %289 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %282, %struct.Node* noundef %287, %struct.Token* noundef %288)
  store %struct.Node* %289, %struct.Node** %22, align 8
  %290 = load %struct.Obj*, %struct.Obj** %21, align 8
  %291 = load %struct.Token*, %struct.Token** %4, align 8
  %292 = call %struct.Node* @new_var_node(%struct.Obj* noundef %290, %struct.Token* noundef %291)
  %293 = load %struct.Token*, %struct.Token** %4, align 8
  %294 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %292, %struct.Token* noundef %293)
  %295 = load %struct.Node*, %struct.Node** %3, align 8
  %296 = getelementptr inbounds %struct.Node, %struct.Node* %295, i32 0, i32 0
  %297 = load i32, i32* %296, align 16
  %298 = load %struct.Obj*, %struct.Obj** %21, align 8
  %299 = load %struct.Token*, %struct.Token** %4, align 8
  %300 = call %struct.Node* @new_var_node(%struct.Obj* noundef %298, %struct.Token* noundef %299)
  %301 = load %struct.Token*, %struct.Token** %4, align 8
  %302 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %300, %struct.Token* noundef %301)
  %303 = load %struct.Node*, %struct.Node** %3, align 8
  %304 = getelementptr inbounds %struct.Node, %struct.Node* %303, i32 0, i32 5
  %305 = load %struct.Node*, %struct.Node** %304, align 8
  %306 = load %struct.Token*, %struct.Token** %4, align 8
  %307 = call %struct.Node* @new_binary(i32 noundef %297, %struct.Node* noundef %302, %struct.Node* noundef %305, %struct.Token* noundef %306)
  %308 = load %struct.Token*, %struct.Token** %4, align 8
  %309 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %294, %struct.Node* noundef %307, %struct.Token* noundef %308)
  store %struct.Node* %309, %struct.Node** %23, align 8
  %310 = load %struct.Node*, %struct.Node** %22, align 8
  %311 = load %struct.Node*, %struct.Node** %23, align 8
  %312 = load %struct.Token*, %struct.Token** %4, align 8
  %313 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %310, %struct.Node* noundef %311, %struct.Token* noundef %312)
  store %struct.Node* %313, %struct.Node** %2, align 8
  br label %314

314:                                              ; preds = %272, %154, %39
  %315 = load %struct.Node*, %struct.Node** %2, align 8
  ret %struct.Node* %315
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_num(i64 noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  store i64 %0, i64* %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load %struct.Token*, %struct.Token** %4, align 8
  %7 = call %struct.Node* @new_node(i32 noundef 42, %struct.Token* noundef %6)
  store %struct.Node* %7, %struct.Node** %5, align 8
  %8 = load i64, i64* %3, align 8
  %9 = load %struct.Node*, %struct.Node** %5, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 34
  store i64 %8, i64* %10, align 16
  %11 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %11
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @get_ident(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %3 = load %struct.Token*, %struct.Token** %2, align 8
  %4 = getelementptr inbounds %struct.Token, %struct.Token* %3, i32 0, i32 0
  %5 = load i32, i32* %4, align 16
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %7, label %9

7:                                                ; preds = %1
  %8 = load %struct.Token*, %struct.Token** %2, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %8, i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str.133, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

9:                                                ; preds = %1
  %10 = load %struct.Token*, %struct.Token** %2, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 4
  %12 = load i8*, i8** %11, align 16
  %13 = load %struct.Token*, %struct.Token** %2, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 5
  %15 = load i32, i32* %14, align 8
  %16 = sext i32 %15 to i64
  %17 = call noalias i8* @strndup(i8* noundef %12, i64 noundef %16) #8
  ret i8* %17
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @postfix(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.Obj*, align 8
  %9 = alloca %struct.Obj*, align 8
  %10 = alloca %struct.Node*, align 8
  %11 = alloca %struct.Node*, align 8
  %12 = alloca %struct.Token*, align 8
  %13 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %14 = load %struct.Token*, %struct.Token** %4, align 8
  %15 = call zeroext i1 @equal(%struct.Token* noundef %14, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %15, label %16, label %55

16:                                               ; preds = %2
  %17 = load %struct.Token*, %struct.Token** %4, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 1
  %19 = load %struct.Token*, %struct.Token** %18, align 8
  %20 = call zeroext i1 @is_typename(%struct.Token* noundef %19)
  br i1 %20, label %21, label %55

21:                                               ; preds = %16
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %22, %struct.Token** %6, align 8
  %23 = load %struct.Token*, %struct.Token** %4, align 8
  %24 = getelementptr inbounds %struct.Token, %struct.Token* %23, i32 0, i32 1
  %25 = load %struct.Token*, %struct.Token** %24, align 8
  %26 = call %struct.Type* @typename(%struct.Token** noundef %4, %struct.Token* noundef %25)
  store %struct.Type* %26, %struct.Type** %7, align 8
  %27 = load %struct.Token*, %struct.Token** %4, align 8
  %28 = call %struct.Token* @skip(%struct.Token* noundef %27, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %28, %struct.Token** %4, align 8
  %29 = load %struct.Scope*, %struct.Scope** @scope, align 8
  %30 = getelementptr inbounds %struct.Scope, %struct.Scope* %29, i32 0, i32 0
  %31 = load %struct.Scope*, %struct.Scope** %30, align 8
  %32 = icmp eq %struct.Scope* %31, null
  br i1 %32, label %33, label %41

33:                                               ; preds = %21
  %34 = load %struct.Type*, %struct.Type** %7, align 8
  %35 = call %struct.Obj* @new_anon_gvar(%struct.Type* noundef %34)
  store %struct.Obj* %35, %struct.Obj** %8, align 8
  %36 = load %struct.Token*, %struct.Token** %4, align 8
  %37 = load %struct.Obj*, %struct.Obj** %8, align 8
  call void @gvar_initializer(%struct.Token** noundef %4, %struct.Token* noundef %36, %struct.Obj* noundef %37)
  %38 = load %struct.Obj*, %struct.Obj** %8, align 8
  %39 = load %struct.Token*, %struct.Token** %6, align 8
  %40 = call %struct.Node* @new_var_node(%struct.Obj* noundef %38, %struct.Token* noundef %39)
  store %struct.Node* %40, %struct.Node** %5, align 8
  br label %54

41:                                               ; preds = %21
  %42 = load %struct.Type*, %struct.Type** %7, align 8
  %43 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %42, i8* noundef null)
  store %struct.Obj* %43, %struct.Obj** %9, align 8
  %44 = load %struct.Token*, %struct.Token** %4, align 8
  %45 = load %struct.Obj*, %struct.Obj** %9, align 8
  %46 = call %struct.Node* @lvar_initializer(%struct.Token** noundef %4, %struct.Token* noundef %44, %struct.Obj* noundef %45)
  store %struct.Node* %46, %struct.Node** %10, align 8
  %47 = load %struct.Obj*, %struct.Obj** %9, align 8
  %48 = load %struct.Token*, %struct.Token** %4, align 8
  %49 = call %struct.Node* @new_var_node(%struct.Obj* noundef %47, %struct.Token* noundef %48)
  store %struct.Node* %49, %struct.Node** %11, align 8
  %50 = load %struct.Node*, %struct.Node** %10, align 8
  %51 = load %struct.Node*, %struct.Node** %11, align 8
  %52 = load %struct.Token*, %struct.Token** %6, align 8
  %53 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %50, %struct.Node* noundef %51, %struct.Token* noundef %52)
  store %struct.Node* %53, %struct.Node** %5, align 8
  br label %54

54:                                               ; preds = %41, %33
  br label %58

55:                                               ; preds = %16, %2
  %56 = load %struct.Token*, %struct.Token** %4, align 8
  %57 = call %struct.Node* @primary(%struct.Token** noundef %4, %struct.Token* noundef %56)
  store %struct.Node* %57, %struct.Node** %5, align 8
  br label %58

58:                                               ; preds = %55, %54
  br label %59

59:                                               ; preds = %129, %119, %102, %88, %71, %62, %58
  %60 = load %struct.Token*, %struct.Token** %4, align 8
  %61 = call zeroext i1 @equal(%struct.Token* noundef %60, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %61, label %62, label %68

62:                                               ; preds = %59
  %63 = load %struct.Token*, %struct.Token** %4, align 8
  %64 = getelementptr inbounds %struct.Token, %struct.Token* %63, i32 0, i32 1
  %65 = load %struct.Token*, %struct.Token** %64, align 8
  %66 = load %struct.Node*, %struct.Node** %5, align 8
  %67 = call %struct.Node* @funcall(%struct.Token** noundef %4, %struct.Token* noundef %65, %struct.Node* noundef %66)
  store %struct.Node* %67, %struct.Node** %5, align 8
  br label %59

68:                                               ; preds = %59
  %69 = load %struct.Token*, %struct.Token** %4, align 8
  %70 = call zeroext i1 @equal(%struct.Token* noundef %69, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.119, i64 0, i64 0))
  br i1 %70, label %71, label %85

71:                                               ; preds = %68
  %72 = load %struct.Token*, %struct.Token** %4, align 8
  store %struct.Token* %72, %struct.Token** %12, align 8
  %73 = load %struct.Token*, %struct.Token** %4, align 8
  %74 = getelementptr inbounds %struct.Token, %struct.Token* %73, i32 0, i32 1
  %75 = load %struct.Token*, %struct.Token** %74, align 8
  %76 = call %struct.Node* @expr(%struct.Token** noundef %4, %struct.Token* noundef %75)
  store %struct.Node* %76, %struct.Node** %13, align 8
  %77 = load %struct.Token*, %struct.Token** %4, align 8
  %78 = call %struct.Token* @skip(%struct.Token* noundef %77, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.125, i64 0, i64 0))
  store %struct.Token* %78, %struct.Token** %4, align 8
  %79 = load %struct.Node*, %struct.Node** %5, align 8
  %80 = load %struct.Node*, %struct.Node** %13, align 8
  %81 = load %struct.Token*, %struct.Token** %12, align 8
  %82 = call %struct.Node* @new_add(%struct.Node* noundef %79, %struct.Node* noundef %80, %struct.Token* noundef %81)
  %83 = load %struct.Token*, %struct.Token** %12, align 8
  %84 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %82, %struct.Token* noundef %83)
  store %struct.Node* %84, %struct.Node** %5, align 8
  br label %59

85:                                               ; preds = %68
  %86 = load %struct.Token*, %struct.Token** %4, align 8
  %87 = call zeroext i1 @equal(%struct.Token* noundef %86, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  br i1 %87, label %88, label %99

88:                                               ; preds = %85
  %89 = load %struct.Node*, %struct.Node** %5, align 8
  %90 = load %struct.Token*, %struct.Token** %4, align 8
  %91 = getelementptr inbounds %struct.Token, %struct.Token* %90, i32 0, i32 1
  %92 = load %struct.Token*, %struct.Token** %91, align 8
  %93 = call %struct.Node* @struct_ref(%struct.Node* noundef %89, %struct.Token* noundef %92)
  store %struct.Node* %93, %struct.Node** %5, align 8
  %94 = load %struct.Token*, %struct.Token** %4, align 8
  %95 = getelementptr inbounds %struct.Token, %struct.Token* %94, i32 0, i32 1
  %96 = load %struct.Token*, %struct.Token** %95, align 8
  %97 = getelementptr inbounds %struct.Token, %struct.Token* %96, i32 0, i32 1
  %98 = load %struct.Token*, %struct.Token** %97, align 8
  store %struct.Token* %98, %struct.Token** %4, align 8
  br label %59

99:                                               ; preds = %85
  %100 = load %struct.Token*, %struct.Token** %4, align 8
  %101 = call zeroext i1 @equal(%struct.Token* noundef %100, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.135, i64 0, i64 0))
  br i1 %101, label %102, label %116

102:                                              ; preds = %99
  %103 = load %struct.Node*, %struct.Node** %5, align 8
  %104 = load %struct.Token*, %struct.Token** %4, align 8
  %105 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %103, %struct.Token* noundef %104)
  store %struct.Node* %105, %struct.Node** %5, align 8
  %106 = load %struct.Node*, %struct.Node** %5, align 8
  %107 = load %struct.Token*, %struct.Token** %4, align 8
  %108 = getelementptr inbounds %struct.Token, %struct.Token* %107, i32 0, i32 1
  %109 = load %struct.Token*, %struct.Token** %108, align 8
  %110 = call %struct.Node* @struct_ref(%struct.Node* noundef %106, %struct.Token* noundef %109)
  store %struct.Node* %110, %struct.Node** %5, align 8
  %111 = load %struct.Token*, %struct.Token** %4, align 8
  %112 = getelementptr inbounds %struct.Token, %struct.Token* %111, i32 0, i32 1
  %113 = load %struct.Token*, %struct.Token** %112, align 8
  %114 = getelementptr inbounds %struct.Token, %struct.Token* %113, i32 0, i32 1
  %115 = load %struct.Token*, %struct.Token** %114, align 8
  store %struct.Token* %115, %struct.Token** %4, align 8
  br label %59

116:                                              ; preds = %99
  %117 = load %struct.Token*, %struct.Token** %4, align 8
  %118 = call zeroext i1 @equal(%struct.Token* noundef %117, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.129, i64 0, i64 0))
  br i1 %118, label %119, label %126

119:                                              ; preds = %116
  %120 = load %struct.Node*, %struct.Node** %5, align 8
  %121 = load %struct.Token*, %struct.Token** %4, align 8
  %122 = call %struct.Node* @new_inc_dec(%struct.Node* noundef %120, %struct.Token* noundef %121, i32 noundef 1)
  store %struct.Node* %122, %struct.Node** %5, align 8
  %123 = load %struct.Token*, %struct.Token** %4, align 8
  %124 = getelementptr inbounds %struct.Token, %struct.Token* %123, i32 0, i32 1
  %125 = load %struct.Token*, %struct.Token** %124, align 8
  store %struct.Token* %125, %struct.Token** %4, align 8
  br label %59

126:                                              ; preds = %116
  %127 = load %struct.Token*, %struct.Token** %4, align 8
  %128 = call zeroext i1 @equal(%struct.Token* noundef %127, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.130, i64 0, i64 0))
  br i1 %128, label %129, label %136

129:                                              ; preds = %126
  %130 = load %struct.Node*, %struct.Node** %5, align 8
  %131 = load %struct.Token*, %struct.Token** %4, align 8
  %132 = call %struct.Node* @new_inc_dec(%struct.Node* noundef %130, %struct.Token* noundef %131, i32 noundef -1)
  store %struct.Node* %132, %struct.Node** %5, align 8
  %133 = load %struct.Token*, %struct.Token** %4, align 8
  %134 = getelementptr inbounds %struct.Token, %struct.Token* %133, i32 0, i32 1
  %135 = load %struct.Token*, %struct.Token** %134, align 8
  store %struct.Token* %135, %struct.Token** %4, align 8
  br label %59

136:                                              ; preds = %126
  %137 = load %struct.Token*, %struct.Token** %4, align 8
  %138 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %137, %struct.Token** %138, align 8
  %139 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %139
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @new_unique_name() #0 {
  %1 = load i32, i32* @new_unique_name.id, align 4
  %2 = add nsw i32 %1, 1
  store i32 %2, i32* @new_unique_name.id, align 4
  %3 = call i8* (i8*, ...) @format(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.132, i64 0, i64 0), i32 noundef %1)
  ret i8* %3
}

declare i8* @format(i8* noundef, ...) #1

; Function Attrs: nounwind
declare noalias i8* @strndup(i8* noundef, i64 noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Obj* @new_anon_gvar(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %3 = call i8* @new_unique_name()
  %4 = load %struct.Type*, %struct.Type** %2, align 8
  %5 = call %struct.Obj* @new_gvar(i8* noundef %3, %struct.Type* noundef %4)
  ret %struct.Obj* %5
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @gvar_initializer(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Obj* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Obj*, align 8
  %7 = alloca %struct.Initializer*, align 8
  %8 = alloca %struct.Relocation, align 8
  %9 = alloca i8*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Obj* %2, %struct.Obj** %6, align 8
  %10 = load %struct.Token**, %struct.Token*** %4, align 8
  %11 = load %struct.Token*, %struct.Token** %5, align 8
  %12 = load %struct.Obj*, %struct.Obj** %6, align 8
  %13 = getelementptr inbounds %struct.Obj, %struct.Obj* %12, i32 0, i32 3
  %14 = load %struct.Type*, %struct.Type** %13, align 8
  %15 = load %struct.Obj*, %struct.Obj** %6, align 8
  %16 = getelementptr inbounds %struct.Obj, %struct.Obj* %15, i32 0, i32 3
  %17 = call %struct.Initializer* @initializer(%struct.Token** noundef %10, %struct.Token* noundef %11, %struct.Type* noundef %14, %struct.Type** noundef %16)
  store %struct.Initializer* %17, %struct.Initializer** %7, align 8
  %18 = bitcast %struct.Relocation* %8 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %18, i8 0, i64 32, i1 false)
  %19 = load %struct.Obj*, %struct.Obj** %6, align 8
  %20 = getelementptr inbounds %struct.Obj, %struct.Obj* %19, i32 0, i32 3
  %21 = load %struct.Type*, %struct.Type** %20, align 8
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 1
  %23 = load i32, i32* %22, align 4
  %24 = sext i32 %23 to i64
  %25 = call noalias i8* @calloc(i64 noundef 1, i64 noundef %24) #8
  store i8* %25, i8** %9, align 8
  %26 = load i8*, i8** %9, align 8
  %27 = icmp eq i8* %26, null
  br i1 %27, label %28, label %29

28:                                               ; preds = %3
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([39 x i8], [39 x i8]* @.str.138, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

29:                                               ; preds = %3
  %30 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %31 = load %struct.Obj*, %struct.Obj** %6, align 8
  %32 = getelementptr inbounds %struct.Obj, %struct.Obj* %31, i32 0, i32 3
  %33 = load %struct.Type*, %struct.Type** %32, align 8
  %34 = load i8*, i8** %9, align 8
  %35 = call %struct.Relocation* @write_gvar_data(%struct.Relocation* noundef %8, %struct.Initializer* noundef %30, %struct.Type* noundef %33, i8* noundef %34, i32 noundef 0)
  %36 = load i8*, i8** %9, align 8
  %37 = load %struct.Obj*, %struct.Obj** %6, align 8
  %38 = getelementptr inbounds %struct.Obj, %struct.Obj* %37, i32 0, i32 15
  store i8* %36, i8** %38, align 8
  %39 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %8, i32 0, i32 0
  %40 = load %struct.Relocation*, %struct.Relocation** %39, align 8
  %41 = load %struct.Obj*, %struct.Obj** %6, align 8
  %42 = getelementptr inbounds %struct.Obj, %struct.Obj* %41, i32 0, i32 16
  store %struct.Relocation* %40, %struct.Relocation** %42, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @lvar_initializer(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Obj* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Obj*, align 8
  %7 = alloca %struct.Initializer*, align 8
  %8 = alloca %struct.InitDesg, align 8
  %9 = alloca %struct.Node*, align 8
  %10 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Obj* %2, %struct.Obj** %6, align 8
  %11 = load %struct.Token**, %struct.Token*** %4, align 8
  %12 = load %struct.Token*, %struct.Token** %5, align 8
  %13 = load %struct.Obj*, %struct.Obj** %6, align 8
  %14 = getelementptr inbounds %struct.Obj, %struct.Obj* %13, i32 0, i32 3
  %15 = load %struct.Type*, %struct.Type** %14, align 8
  %16 = load %struct.Obj*, %struct.Obj** %6, align 8
  %17 = getelementptr inbounds %struct.Obj, %struct.Obj* %16, i32 0, i32 3
  %18 = call %struct.Initializer* @initializer(%struct.Token** noundef %11, %struct.Token* noundef %12, %struct.Type* noundef %15, %struct.Type** noundef %17)
  store %struct.Initializer* %18, %struct.Initializer** %7, align 8
  %19 = bitcast %struct.InitDesg* %8 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %19, i8 0, i64 32, i1 false)
  %20 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %8, i32 0, i32 3
  %21 = load %struct.Obj*, %struct.Obj** %6, align 8
  store %struct.Obj* %21, %struct.Obj** %20, align 8
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = call %struct.Node* @new_node(i32 noundef 44, %struct.Token* noundef %22)
  store %struct.Node* %23, %struct.Node** %9, align 8
  %24 = load %struct.Obj*, %struct.Obj** %6, align 8
  %25 = load %struct.Node*, %struct.Node** %9, align 8
  %26 = getelementptr inbounds %struct.Node, %struct.Node* %25, i32 0, i32 33
  store %struct.Obj* %24, %struct.Obj** %26, align 8
  %27 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %28 = load %struct.Obj*, %struct.Obj** %6, align 8
  %29 = getelementptr inbounds %struct.Obj, %struct.Obj* %28, i32 0, i32 3
  %30 = load %struct.Type*, %struct.Type** %29, align 8
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = call %struct.Node* @create_lvar_init(%struct.Initializer* noundef %27, %struct.Type* noundef %30, %struct.InitDesg* noundef %8, %struct.Token* noundef %31)
  store %struct.Node* %32, %struct.Node** %10, align 8
  %33 = load %struct.Node*, %struct.Node** %9, align 8
  %34 = load %struct.Node*, %struct.Node** %10, align 8
  %35 = load %struct.Token*, %struct.Token** %5, align 8
  %36 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %33, %struct.Node* noundef %34, %struct.Token* noundef %35)
  ret %struct.Node* %36
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @primary(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Node*, align 8
  %9 = alloca %struct.Type*, align 8
  %10 = alloca %struct.Node*, align 8
  %11 = alloca %struct.Node*, align 8
  %12 = alloca %struct.Node*, align 8
  %13 = alloca %struct.Type*, align 8
  %14 = alloca %struct.Node*, align 8
  %15 = alloca %struct.Type*, align 8
  %16 = alloca %struct.Type*, align 8
  %17 = alloca %struct.Type*, align 8
  %18 = alloca %struct.Node*, align 8
  %19 = alloca %struct.Node*, align 8
  %20 = alloca %struct.Node*, align 8
  %21 = alloca %struct.Node*, align 8
  %22 = alloca %struct.Node*, align 8
  %23 = alloca %struct.VarScope*, align 8
  %24 = alloca %struct.Node*, align 8
  %25 = alloca %struct.Obj*, align 8
  %26 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %27 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %27, %struct.Token** %6, align 8
  %28 = load %struct.Token*, %struct.Token** %5, align 8
  %29 = call zeroext i1 @equal(%struct.Token* noundef %28, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %29, label %30, label %52

30:                                               ; preds = %2
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = getelementptr inbounds %struct.Token, %struct.Token* %31, i32 0, i32 1
  %33 = load %struct.Token*, %struct.Token** %32, align 8
  %34 = call zeroext i1 @equal(%struct.Token* noundef %33, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %34, label %35, label %52

35:                                               ; preds = %30
  %36 = load %struct.Token*, %struct.Token** %5, align 8
  %37 = call %struct.Node* @new_node(i32 noundef 39, %struct.Token* noundef %36)
  store %struct.Node* %37, %struct.Node** %7, align 8
  %38 = load %struct.Token*, %struct.Token** %5, align 8
  %39 = getelementptr inbounds %struct.Token, %struct.Token* %38, i32 0, i32 1
  %40 = load %struct.Token*, %struct.Token** %39, align 8
  %41 = getelementptr inbounds %struct.Token, %struct.Token* %40, i32 0, i32 1
  %42 = load %struct.Token*, %struct.Token** %41, align 8
  %43 = call %struct.Node* @compound_stmt(%struct.Token** noundef %5, %struct.Token* noundef %42)
  %44 = getelementptr inbounds %struct.Node, %struct.Node* %43, i32 0, i32 13
  %45 = load %struct.Node*, %struct.Node** %44, align 8
  %46 = load %struct.Node*, %struct.Node** %7, align 8
  %47 = getelementptr inbounds %struct.Node, %struct.Node* %46, i32 0, i32 13
  store %struct.Node* %45, %struct.Node** %47, align 8
  %48 = load %struct.Token*, %struct.Token** %5, align 8
  %49 = call %struct.Token* @skip(%struct.Token* noundef %48, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %50 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %49, %struct.Token** %50, align 8
  %51 = load %struct.Node*, %struct.Node** %7, align 8
  store %struct.Node* %51, %struct.Node** %3, align 8
  br label %542

52:                                               ; preds = %30, %2
  %53 = load %struct.Token*, %struct.Token** %5, align 8
  %54 = call zeroext i1 @equal(%struct.Token* noundef %53, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %54, label %55, label %64

55:                                               ; preds = %52
  %56 = load %struct.Token*, %struct.Token** %5, align 8
  %57 = getelementptr inbounds %struct.Token, %struct.Token* %56, i32 0, i32 1
  %58 = load %struct.Token*, %struct.Token** %57, align 8
  %59 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %58)
  store %struct.Node* %59, %struct.Node** %8, align 8
  %60 = load %struct.Token*, %struct.Token** %5, align 8
  %61 = call %struct.Token* @skip(%struct.Token* noundef %60, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %62 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %61, %struct.Token** %62, align 8
  %63 = load %struct.Node*, %struct.Node** %8, align 8
  store %struct.Node* %63, %struct.Node** %3, align 8
  br label %542

64:                                               ; preds = %52
  %65 = load %struct.Token*, %struct.Token** %5, align 8
  %66 = call zeroext i1 @equal(%struct.Token* noundef %65, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.123, i64 0, i64 0))
  br i1 %66, label %67, label %124

67:                                               ; preds = %64
  %68 = load %struct.Token*, %struct.Token** %5, align 8
  %69 = getelementptr inbounds %struct.Token, %struct.Token* %68, i32 0, i32 1
  %70 = load %struct.Token*, %struct.Token** %69, align 8
  %71 = call zeroext i1 @equal(%struct.Token* noundef %70, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %71, label %72, label %124

72:                                               ; preds = %67
  %73 = load %struct.Token*, %struct.Token** %5, align 8
  %74 = getelementptr inbounds %struct.Token, %struct.Token* %73, i32 0, i32 1
  %75 = load %struct.Token*, %struct.Token** %74, align 8
  %76 = getelementptr inbounds %struct.Token, %struct.Token* %75, i32 0, i32 1
  %77 = load %struct.Token*, %struct.Token** %76, align 8
  %78 = call zeroext i1 @is_typename(%struct.Token* noundef %77)
  br i1 %78, label %79, label %124

79:                                               ; preds = %72
  %80 = load %struct.Token*, %struct.Token** %5, align 8
  %81 = getelementptr inbounds %struct.Token, %struct.Token* %80, i32 0, i32 1
  %82 = load %struct.Token*, %struct.Token** %81, align 8
  %83 = getelementptr inbounds %struct.Token, %struct.Token* %82, i32 0, i32 1
  %84 = load %struct.Token*, %struct.Token** %83, align 8
  %85 = call %struct.Type* @typename(%struct.Token** noundef %5, %struct.Token* noundef %84)
  store %struct.Type* %85, %struct.Type** %9, align 8
  %86 = load %struct.Token*, %struct.Token** %5, align 8
  %87 = call %struct.Token* @skip(%struct.Token* noundef %86, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %88 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %87, %struct.Token** %88, align 8
  %89 = load %struct.Type*, %struct.Type** %9, align 8
  %90 = getelementptr inbounds %struct.Type, %struct.Type* %89, i32 0, i32 0
  %91 = load i32, i32* %90, align 8
  %92 = icmp eq i32 %91, 13
  br i1 %92, label %93, label %117

93:                                               ; preds = %79
  %94 = load %struct.Type*, %struct.Type** %9, align 8
  %95 = getelementptr inbounds %struct.Type, %struct.Type* %94, i32 0, i32 13
  %96 = load %struct.Obj*, %struct.Obj** %95, align 8
  %97 = icmp ne %struct.Obj* %96, null
  br i1 %97, label %98, label %104

98:                                               ; preds = %93
  %99 = load %struct.Type*, %struct.Type** %9, align 8
  %100 = getelementptr inbounds %struct.Type, %struct.Type* %99, i32 0, i32 13
  %101 = load %struct.Obj*, %struct.Obj** %100, align 8
  %102 = load %struct.Token*, %struct.Token** %5, align 8
  %103 = call %struct.Node* @new_var_node(%struct.Obj* noundef %101, %struct.Token* noundef %102)
  store %struct.Node* %103, %struct.Node** %3, align 8
  br label %542

104:                                              ; preds = %93
  %105 = load %struct.Type*, %struct.Type** %9, align 8
  %106 = load %struct.Token*, %struct.Token** %5, align 8
  %107 = call %struct.Node* @compute_vla_size(%struct.Type* noundef %105, %struct.Token* noundef %106)
  store %struct.Node* %107, %struct.Node** %10, align 8
  %108 = load %struct.Type*, %struct.Type** %9, align 8
  %109 = getelementptr inbounds %struct.Type, %struct.Type* %108, i32 0, i32 13
  %110 = load %struct.Obj*, %struct.Obj** %109, align 8
  %111 = load %struct.Token*, %struct.Token** %5, align 8
  %112 = call %struct.Node* @new_var_node(%struct.Obj* noundef %110, %struct.Token* noundef %111)
  store %struct.Node* %112, %struct.Node** %11, align 8
  %113 = load %struct.Node*, %struct.Node** %10, align 8
  %114 = load %struct.Node*, %struct.Node** %11, align 8
  %115 = load %struct.Token*, %struct.Token** %5, align 8
  %116 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %113, %struct.Node* noundef %114, %struct.Token* noundef %115)
  store %struct.Node* %116, %struct.Node** %3, align 8
  br label %542

117:                                              ; preds = %79
  %118 = load %struct.Type*, %struct.Type** %9, align 8
  %119 = getelementptr inbounds %struct.Type, %struct.Type* %118, i32 0, i32 1
  %120 = load i32, i32* %119, align 4
  %121 = sext i32 %120 to i64
  %122 = load %struct.Token*, %struct.Token** %6, align 8
  %123 = call %struct.Node* @new_ulong(i64 noundef %121, %struct.Token* noundef %122)
  store %struct.Node* %123, %struct.Node** %3, align 8
  br label %542

124:                                              ; preds = %72, %67, %64
  %125 = load %struct.Token*, %struct.Token** %5, align 8
  %126 = call zeroext i1 @equal(%struct.Token* noundef %125, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.123, i64 0, i64 0))
  br i1 %126, label %127, label %157

127:                                              ; preds = %124
  %128 = load %struct.Token**, %struct.Token*** %4, align 8
  %129 = load %struct.Token*, %struct.Token** %5, align 8
  %130 = getelementptr inbounds %struct.Token, %struct.Token* %129, i32 0, i32 1
  %131 = load %struct.Token*, %struct.Token** %130, align 8
  %132 = call %struct.Node* @unary(%struct.Token** noundef %128, %struct.Token* noundef %131)
  store %struct.Node* %132, %struct.Node** %12, align 8
  %133 = load %struct.Node*, %struct.Node** %12, align 8
  call void @add_type(%struct.Node* noundef %133)
  %134 = load %struct.Node*, %struct.Node** %12, align 8
  %135 = getelementptr inbounds %struct.Node, %struct.Node* %134, i32 0, i32 2
  %136 = load %struct.Type*, %struct.Type** %135, align 16
  %137 = getelementptr inbounds %struct.Type, %struct.Type* %136, i32 0, i32 0
  %138 = load i32, i32* %137, align 8
  %139 = icmp eq i32 %138, 13
  br i1 %139, label %140, label %148

140:                                              ; preds = %127
  %141 = load %struct.Node*, %struct.Node** %12, align 8
  %142 = getelementptr inbounds %struct.Node, %struct.Node* %141, i32 0, i32 2
  %143 = load %struct.Type*, %struct.Type** %142, align 16
  %144 = getelementptr inbounds %struct.Type, %struct.Type* %143, i32 0, i32 13
  %145 = load %struct.Obj*, %struct.Obj** %144, align 8
  %146 = load %struct.Token*, %struct.Token** %5, align 8
  %147 = call %struct.Node* @new_var_node(%struct.Obj* noundef %145, %struct.Token* noundef %146)
  store %struct.Node* %147, %struct.Node** %3, align 8
  br label %542

148:                                              ; preds = %127
  %149 = load %struct.Node*, %struct.Node** %12, align 8
  %150 = getelementptr inbounds %struct.Node, %struct.Node* %149, i32 0, i32 2
  %151 = load %struct.Type*, %struct.Type** %150, align 16
  %152 = getelementptr inbounds %struct.Type, %struct.Type* %151, i32 0, i32 1
  %153 = load i32, i32* %152, align 4
  %154 = sext i32 %153 to i64
  %155 = load %struct.Token*, %struct.Token** %5, align 8
  %156 = call %struct.Node* @new_ulong(i64 noundef %154, %struct.Token* noundef %155)
  store %struct.Node* %156, %struct.Node** %3, align 8
  br label %542

157:                                              ; preds = %124
  %158 = load %struct.Token*, %struct.Token** %5, align 8
  %159 = call zeroext i1 @equal(%struct.Token* noundef %158, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.124, i64 0, i64 0))
  br i1 %159, label %160, label %188

160:                                              ; preds = %157
  %161 = load %struct.Token*, %struct.Token** %5, align 8
  %162 = getelementptr inbounds %struct.Token, %struct.Token* %161, i32 0, i32 1
  %163 = load %struct.Token*, %struct.Token** %162, align 8
  %164 = call zeroext i1 @equal(%struct.Token* noundef %163, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %164, label %165, label %188

165:                                              ; preds = %160
  %166 = load %struct.Token*, %struct.Token** %5, align 8
  %167 = getelementptr inbounds %struct.Token, %struct.Token* %166, i32 0, i32 1
  %168 = load %struct.Token*, %struct.Token** %167, align 8
  %169 = getelementptr inbounds %struct.Token, %struct.Token* %168, i32 0, i32 1
  %170 = load %struct.Token*, %struct.Token** %169, align 8
  %171 = call zeroext i1 @is_typename(%struct.Token* noundef %170)
  br i1 %171, label %172, label %188

172:                                              ; preds = %165
  %173 = load %struct.Token*, %struct.Token** %5, align 8
  %174 = getelementptr inbounds %struct.Token, %struct.Token* %173, i32 0, i32 1
  %175 = load %struct.Token*, %struct.Token** %174, align 8
  %176 = getelementptr inbounds %struct.Token, %struct.Token* %175, i32 0, i32 1
  %177 = load %struct.Token*, %struct.Token** %176, align 8
  %178 = call %struct.Type* @typename(%struct.Token** noundef %5, %struct.Token* noundef %177)
  store %struct.Type* %178, %struct.Type** %13, align 8
  %179 = load %struct.Token*, %struct.Token** %5, align 8
  %180 = call %struct.Token* @skip(%struct.Token* noundef %179, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %181 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %180, %struct.Token** %181, align 8
  %182 = load %struct.Type*, %struct.Type** %13, align 8
  %183 = getelementptr inbounds %struct.Type, %struct.Type* %182, i32 0, i32 2
  %184 = load i32, i32* %183, align 8
  %185 = sext i32 %184 to i64
  %186 = load %struct.Token*, %struct.Token** %5, align 8
  %187 = call %struct.Node* @new_ulong(i64 noundef %185, %struct.Token* noundef %186)
  store %struct.Node* %187, %struct.Node** %3, align 8
  br label %542

188:                                              ; preds = %165, %160, %157
  %189 = load %struct.Token*, %struct.Token** %5, align 8
  %190 = call zeroext i1 @equal(%struct.Token* noundef %189, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.124, i64 0, i64 0))
  br i1 %190, label %191, label %206

191:                                              ; preds = %188
  %192 = load %struct.Token**, %struct.Token*** %4, align 8
  %193 = load %struct.Token*, %struct.Token** %5, align 8
  %194 = getelementptr inbounds %struct.Token, %struct.Token* %193, i32 0, i32 1
  %195 = load %struct.Token*, %struct.Token** %194, align 8
  %196 = call %struct.Node* @unary(%struct.Token** noundef %192, %struct.Token* noundef %195)
  store %struct.Node* %196, %struct.Node** %14, align 8
  %197 = load %struct.Node*, %struct.Node** %14, align 8
  call void @add_type(%struct.Node* noundef %197)
  %198 = load %struct.Node*, %struct.Node** %14, align 8
  %199 = getelementptr inbounds %struct.Node, %struct.Node* %198, i32 0, i32 2
  %200 = load %struct.Type*, %struct.Type** %199, align 16
  %201 = getelementptr inbounds %struct.Type, %struct.Type* %200, i32 0, i32 2
  %202 = load i32, i32* %201, align 8
  %203 = sext i32 %202 to i64
  %204 = load %struct.Token*, %struct.Token** %5, align 8
  %205 = call %struct.Node* @new_ulong(i64 noundef %203, %struct.Token* noundef %204)
  store %struct.Node* %205, %struct.Node** %3, align 8
  br label %542

206:                                              ; preds = %188
  %207 = load %struct.Token*, %struct.Token** %5, align 8
  %208 = call zeroext i1 @equal(%struct.Token* noundef %207, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.166, i64 0, i64 0))
  br i1 %208, label %209, label %215

209:                                              ; preds = %206
  %210 = load %struct.Token**, %struct.Token*** %4, align 8
  %211 = load %struct.Token*, %struct.Token** %5, align 8
  %212 = getelementptr inbounds %struct.Token, %struct.Token* %211, i32 0, i32 1
  %213 = load %struct.Token*, %struct.Token** %212, align 8
  %214 = call %struct.Node* @generic_selection(%struct.Token** noundef %210, %struct.Token* noundef %213)
  store %struct.Node* %214, %struct.Node** %3, align 8
  br label %542

215:                                              ; preds = %206
  %216 = load %struct.Token*, %struct.Token** %5, align 8
  %217 = call zeroext i1 @equal(%struct.Token* noundef %216, i8* noundef getelementptr inbounds ([29 x i8], [29 x i8]* @.str.167, i64 0, i64 0))
  br i1 %217, label %218, label %242

218:                                              ; preds = %215
  %219 = load %struct.Token*, %struct.Token** %5, align 8
  %220 = getelementptr inbounds %struct.Token, %struct.Token* %219, i32 0, i32 1
  %221 = load %struct.Token*, %struct.Token** %220, align 8
  %222 = call %struct.Token* @skip(%struct.Token* noundef %221, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %222, %struct.Token** %5, align 8
  %223 = load %struct.Token*, %struct.Token** %5, align 8
  %224 = call %struct.Type* @typename(%struct.Token** noundef %5, %struct.Token* noundef %223)
  store %struct.Type* %224, %struct.Type** %15, align 8
  %225 = load %struct.Token*, %struct.Token** %5, align 8
  %226 = call zeroext i1 @equal(%struct.Token* noundef %225, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %226, label %227, label %230

227:                                              ; preds = %218
  %228 = load %struct.Token*, %struct.Token** %5, align 8
  %229 = call %struct.Token* @skip(%struct.Token* noundef %228, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %229, %struct.Token** %5, align 8
  br label %230

230:                                              ; preds = %227, %218
  %231 = load %struct.Token*, %struct.Token** %5, align 8
  %232 = call %struct.Type* @typename(%struct.Token** noundef %5, %struct.Token* noundef %231)
  store %struct.Type* %232, %struct.Type** %16, align 8
  %233 = load %struct.Token*, %struct.Token** %5, align 8
  %234 = call %struct.Token* @skip(%struct.Token* noundef %233, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %235 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %234, %struct.Token** %235, align 8
  %236 = load %struct.Type*, %struct.Type** %15, align 8
  %237 = load %struct.Type*, %struct.Type** %16, align 8
  %238 = call zeroext i1 @is_compatible(%struct.Type* noundef %236, %struct.Type* noundef %237)
  %239 = zext i1 %238 to i64
  %240 = load %struct.Token*, %struct.Token** %6, align 8
  %241 = call %struct.Node* @new_num(i64 noundef %239, %struct.Token* noundef %240)
  store %struct.Node* %241, %struct.Node** %3, align 8
  br label %542

242:                                              ; preds = %215
  %243 = load %struct.Token*, %struct.Token** %5, align 8
  %244 = call zeroext i1 @equal(%struct.Token* noundef %243, i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.168, i64 0, i64 0))
  br i1 %244, label %245, label %274

245:                                              ; preds = %242
  %246 = load %struct.Token*, %struct.Token** %5, align 8
  %247 = getelementptr inbounds %struct.Token, %struct.Token* %246, i32 0, i32 1
  %248 = load %struct.Token*, %struct.Token** %247, align 8
  %249 = call %struct.Token* @skip(%struct.Token* noundef %248, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %249, %struct.Token** %5, align 8
  %250 = load %struct.Token*, %struct.Token** %5, align 8
  %251 = call %struct.Type* @typename(%struct.Token** noundef %5, %struct.Token* noundef %250)
  store %struct.Type* %251, %struct.Type** %17, align 8
  %252 = load %struct.Token*, %struct.Token** %5, align 8
  %253 = call %struct.Token* @skip(%struct.Token* noundef %252, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %254 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %253, %struct.Token** %254, align 8
  %255 = load %struct.Type*, %struct.Type** %17, align 8
  %256 = call zeroext i1 @is_integer(%struct.Type* noundef %255)
  br i1 %256, label %262, label %257

257:                                              ; preds = %245
  %258 = load %struct.Type*, %struct.Type** %17, align 8
  %259 = getelementptr inbounds %struct.Type, %struct.Type* %258, i32 0, i32 0
  %260 = load i32, i32* %259, align 8
  %261 = icmp eq i32 %260, 10
  br i1 %261, label %262, label %265

262:                                              ; preds = %257, %245
  %263 = load %struct.Token*, %struct.Token** %6, align 8
  %264 = call %struct.Node* @new_num(i64 noundef 0, %struct.Token* noundef %263)
  store %struct.Node* %264, %struct.Node** %3, align 8
  br label %542

265:                                              ; preds = %257
  %266 = load %struct.Type*, %struct.Type** %17, align 8
  %267 = call zeroext i1 @is_flonum(%struct.Type* noundef %266)
  br i1 %267, label %268, label %271

268:                                              ; preds = %265
  %269 = load %struct.Token*, %struct.Token** %6, align 8
  %270 = call %struct.Node* @new_num(i64 noundef 1, %struct.Token* noundef %269)
  store %struct.Node* %270, %struct.Node** %3, align 8
  br label %542

271:                                              ; preds = %265
  %272 = load %struct.Token*, %struct.Token** %6, align 8
  %273 = call %struct.Node* @new_num(i64 noundef 2, %struct.Token* noundef %272)
  store %struct.Node* %273, %struct.Node** %3, align 8
  br label %542

274:                                              ; preds = %242
  %275 = load %struct.Token*, %struct.Token** %5, align 8
  %276 = call zeroext i1 @equal(%struct.Token* noundef %275, i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @.str.169, i64 0, i64 0))
  br i1 %276, label %277, label %304

277:                                              ; preds = %274
  %278 = load %struct.Token*, %struct.Token** %5, align 8
  %279 = call %struct.Node* @new_node(i32 noundef 46, %struct.Token* noundef %278)
  store %struct.Node* %279, %struct.Node** %18, align 8
  %280 = load %struct.Token*, %struct.Token** %5, align 8
  %281 = getelementptr inbounds %struct.Token, %struct.Token* %280, i32 0, i32 1
  %282 = load %struct.Token*, %struct.Token** %281, align 8
  %283 = call %struct.Token* @skip(%struct.Token* noundef %282, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %283, %struct.Token** %5, align 8
  %284 = load %struct.Token*, %struct.Token** %5, align 8
  %285 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %284)
  %286 = load %struct.Node*, %struct.Node** %18, align 8
  %287 = getelementptr inbounds %struct.Node, %struct.Node* %286, i32 0, i32 27
  store %struct.Node* %285, %struct.Node** %287, align 8
  %288 = load %struct.Token*, %struct.Token** %5, align 8
  %289 = call %struct.Token* @skip(%struct.Token* noundef %288, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %289, %struct.Token** %5, align 8
  %290 = load %struct.Token*, %struct.Token** %5, align 8
  %291 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %290)
  %292 = load %struct.Node*, %struct.Node** %18, align 8
  %293 = getelementptr inbounds %struct.Node, %struct.Node* %292, i32 0, i32 28
  store %struct.Node* %291, %struct.Node** %293, align 16
  %294 = load %struct.Token*, %struct.Token** %5, align 8
  %295 = call %struct.Token* @skip(%struct.Token* noundef %294, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %295, %struct.Token** %5, align 8
  %296 = load %struct.Token*, %struct.Token** %5, align 8
  %297 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %296)
  %298 = load %struct.Node*, %struct.Node** %18, align 8
  %299 = getelementptr inbounds %struct.Node, %struct.Node* %298, i32 0, i32 29
  store %struct.Node* %297, %struct.Node** %299, align 8
  %300 = load %struct.Token*, %struct.Token** %5, align 8
  %301 = call %struct.Token* @skip(%struct.Token* noundef %300, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %302 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %301, %struct.Token** %302, align 8
  %303 = load %struct.Node*, %struct.Node** %18, align 8
  store %struct.Node* %303, %struct.Node** %3, align 8
  br label %542

304:                                              ; preds = %274
  %305 = load %struct.Token*, %struct.Token** %5, align 8
  %306 = call zeroext i1 @equal(%struct.Token* noundef %305, i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.170, i64 0, i64 0))
  br i1 %306, label %307, label %328

307:                                              ; preds = %304
  %308 = load %struct.Token*, %struct.Token** %5, align 8
  %309 = call %struct.Node* @new_node(i32 noundef 47, %struct.Token* noundef %308)
  store %struct.Node* %309, %struct.Node** %19, align 8
  %310 = load %struct.Token*, %struct.Token** %5, align 8
  %311 = getelementptr inbounds %struct.Token, %struct.Token* %310, i32 0, i32 1
  %312 = load %struct.Token*, %struct.Token** %311, align 8
  %313 = call %struct.Token* @skip(%struct.Token* noundef %312, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %313, %struct.Token** %5, align 8
  %314 = load %struct.Token*, %struct.Token** %5, align 8
  %315 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %314)
  %316 = load %struct.Node*, %struct.Node** %19, align 8
  %317 = getelementptr inbounds %struct.Node, %struct.Node* %316, i32 0, i32 4
  store %struct.Node* %315, %struct.Node** %317, align 16
  %318 = load %struct.Token*, %struct.Token** %5, align 8
  %319 = call %struct.Token* @skip(%struct.Token* noundef %318, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %319, %struct.Token** %5, align 8
  %320 = load %struct.Token*, %struct.Token** %5, align 8
  %321 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %320)
  %322 = load %struct.Node*, %struct.Node** %19, align 8
  %323 = getelementptr inbounds %struct.Node, %struct.Node* %322, i32 0, i32 5
  store %struct.Node* %321, %struct.Node** %323, align 8
  %324 = load %struct.Token*, %struct.Token** %5, align 8
  %325 = call %struct.Token* @skip(%struct.Token* noundef %324, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %326 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %325, %struct.Token** %326, align 8
  %327 = load %struct.Node*, %struct.Node** %19, align 8
  store %struct.Node* %327, %struct.Node** %3, align 8
  br label %542

328:                                              ; preds = %304
  %329 = load %struct.Token*, %struct.Token** %5, align 8
  %330 = call zeroext i1 @equal(%struct.Token* noundef %329, i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.171, i64 0, i64 0))
  br i1 %330, label %331, label %401

331:                                              ; preds = %328
  %332 = load %struct.Token*, %struct.Token** %5, align 8
  %333 = getelementptr inbounds %struct.Token, %struct.Token* %332, i32 0, i32 1
  %334 = load %struct.Token*, %struct.Token** %333, align 8
  %335 = call %struct.Token* @skip(%struct.Token* noundef %334, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %335, %struct.Token** %5, align 8
  %336 = load %struct.Token*, %struct.Token** %5, align 8
  %337 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %336)
  %338 = load %struct.Token*, %struct.Token** %5, align 8
  %339 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %337, %struct.Token* noundef %338)
  store %struct.Node* %339, %struct.Node** %20, align 8
  %340 = load %struct.Token*, %struct.Token** %5, align 8
  %341 = call %struct.Token* @skip(%struct.Token* noundef %340, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %341, %struct.Token** %5, align 8
  %342 = load %struct.Token*, %struct.Token** %5, align 8
  %343 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %342)
  store %struct.Node* %343, %struct.Node** %21, align 8
  %344 = load %struct.Token*, %struct.Token** %5, align 8
  %345 = call %struct.Token* @skip(%struct.Token* noundef %344, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %345, %struct.Token** %5, align 8
  %346 = load %struct.Token*, %struct.Token** %5, align 8
  %347 = call zeroext i1 @equal(%struct.Token* noundef %346, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.172, i64 0, i64 0))
  br i1 %347, label %348, label %353

348:                                              ; preds = %331
  %349 = load %struct.Node*, %struct.Node** %20, align 8
  %350 = load %struct.Node*, %struct.Node** %21, align 8
  %351 = load %struct.Token*, %struct.Token** %5, align 8
  %352 = call %struct.Node* @new_add(%struct.Node* noundef %349, %struct.Node* noundef %350, %struct.Token* noundef %351)
  store %struct.Node* %352, %struct.Node** %22, align 8
  br label %391

353:                                              ; preds = %331
  %354 = load %struct.Token*, %struct.Token** %5, align 8
  %355 = call zeroext i1 @equal(%struct.Token* noundef %354, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.173, i64 0, i64 0))
  br i1 %355, label %356, label %361

356:                                              ; preds = %353
  %357 = load %struct.Node*, %struct.Node** %20, align 8
  %358 = load %struct.Node*, %struct.Node** %21, align 8
  %359 = load %struct.Token*, %struct.Token** %5, align 8
  %360 = call %struct.Node* @new_sub(%struct.Node* noundef %357, %struct.Node* noundef %358, %struct.Token* noundef %359)
  store %struct.Node* %360, %struct.Node** %22, align 8
  br label %390

361:                                              ; preds = %353
  %362 = load %struct.Token*, %struct.Token** %5, align 8
  %363 = call zeroext i1 @equal(%struct.Token* noundef %362, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.174, i64 0, i64 0))
  br i1 %363, label %364, label %369

364:                                              ; preds = %361
  %365 = load %struct.Node*, %struct.Node** %20, align 8
  %366 = load %struct.Node*, %struct.Node** %21, align 8
  %367 = load %struct.Token*, %struct.Token** %5, align 8
  %368 = call %struct.Node* @new_binary(i32 noundef 8, %struct.Node* noundef %365, %struct.Node* noundef %366, %struct.Token* noundef %367)
  store %struct.Node* %368, %struct.Node** %22, align 8
  br label %389

369:                                              ; preds = %361
  %370 = load %struct.Token*, %struct.Token** %5, align 8
  %371 = call zeroext i1 @equal(%struct.Token* noundef %370, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.175, i64 0, i64 0))
  br i1 %371, label %372, label %377

372:                                              ; preds = %369
  %373 = load %struct.Node*, %struct.Node** %20, align 8
  %374 = load %struct.Node*, %struct.Node** %21, align 8
  %375 = load %struct.Token*, %struct.Token** %5, align 8
  %376 = call %struct.Node* @new_binary(i32 noundef 9, %struct.Node* noundef %373, %struct.Node* noundef %374, %struct.Token* noundef %375)
  store %struct.Node* %376, %struct.Node** %22, align 8
  br label %388

377:                                              ; preds = %369
  %378 = load %struct.Token*, %struct.Token** %5, align 8
  %379 = call zeroext i1 @equal(%struct.Token* noundef %378, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.176, i64 0, i64 0))
  br i1 %379, label %380, label %385

380:                                              ; preds = %377
  %381 = load %struct.Node*, %struct.Node** %20, align 8
  %382 = load %struct.Node*, %struct.Node** %21, align 8
  %383 = load %struct.Token*, %struct.Token** %5, align 8
  %384 = call %struct.Node* @new_binary(i32 noundef 7, %struct.Node* noundef %381, %struct.Node* noundef %382, %struct.Token* noundef %383)
  store %struct.Node* %384, %struct.Node** %22, align 8
  br label %387

385:                                              ; preds = %377
  %386 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %386, i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.177, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

387:                                              ; preds = %380
  br label %388

388:                                              ; preds = %387, %372
  br label %389

389:                                              ; preds = %388, %364
  br label %390

390:                                              ; preds = %389, %356
  br label %391

391:                                              ; preds = %390, %348
  %392 = load %struct.Node*, %struct.Node** %22, align 8
  %393 = getelementptr inbounds %struct.Node, %struct.Node* %392, i32 0, i32 32
  store i8 1, i8* %393, align 16
  %394 = load %struct.Token*, %struct.Token** %5, align 8
  %395 = getelementptr inbounds %struct.Token, %struct.Token* %394, i32 0, i32 1
  %396 = load %struct.Token*, %struct.Token** %395, align 8
  %397 = call %struct.Token* @skip(%struct.Token* noundef %396, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %398 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %397, %struct.Token** %398, align 8
  %399 = load %struct.Node*, %struct.Node** %22, align 8
  %400 = call %struct.Node* @to_assign(%struct.Node* noundef %399)
  store %struct.Node* %400, %struct.Node** %3, align 8
  br label %542

401:                                              ; preds = %328
  %402 = load %struct.Token*, %struct.Token** %5, align 8
  %403 = getelementptr inbounds %struct.Token, %struct.Token* %402, i32 0, i32 0
  %404 = load i32, i32* %403, align 16
  %405 = icmp eq i32 %404, 0
  br i1 %405, label %406, label %485

406:                                              ; preds = %401
  %407 = load %struct.Token*, %struct.Token** %5, align 8
  %408 = call %struct.VarScope* @find_var(%struct.Token* noundef %407)
  store %struct.VarScope* %408, %struct.VarScope** %23, align 8
  %409 = load %struct.Token*, %struct.Token** %5, align 8
  %410 = getelementptr inbounds %struct.Token, %struct.Token* %409, i32 0, i32 1
  %411 = load %struct.Token*, %struct.Token** %410, align 8
  %412 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %411, %struct.Token** %412, align 8
  %413 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %414 = icmp ne %struct.VarScope* %413, null
  br i1 %414, label %415, label %444

415:                                              ; preds = %406
  %416 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %417 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %416, i32 0, i32 0
  %418 = load %struct.Obj*, %struct.Obj** %417, align 8
  %419 = icmp ne %struct.Obj* %418, null
  br i1 %419, label %420, label %444

420:                                              ; preds = %415
  %421 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %422 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %421, i32 0, i32 0
  %423 = load %struct.Obj*, %struct.Obj** %422, align 8
  %424 = getelementptr inbounds %struct.Obj, %struct.Obj* %423, i32 0, i32 10
  %425 = load i8, i8* %424, align 4
  %426 = trunc i8 %425 to i1
  br i1 %426, label %427, label %444

427:                                              ; preds = %420
  %428 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %429 = icmp ne %struct.Obj* %428, null
  br i1 %429, label %430, label %438

430:                                              ; preds = %427
  %431 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %432 = getelementptr inbounds %struct.Obj, %struct.Obj* %431, i32 0, i32 26
  %433 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %434 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %433, i32 0, i32 0
  %435 = load %struct.Obj*, %struct.Obj** %434, align 8
  %436 = getelementptr inbounds %struct.Obj, %struct.Obj* %435, i32 0, i32 1
  %437 = load i8*, i8** %436, align 8
  call void @strarray_push(%struct.StringArray* noundef %432, i8* noundef %437)
  br label %443

438:                                              ; preds = %427
  %439 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %440 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %439, i32 0, i32 0
  %441 = load %struct.Obj*, %struct.Obj** %440, align 8
  %442 = getelementptr inbounds %struct.Obj, %struct.Obj* %441, i32 0, i32 25
  store i8 1, i8* %442, align 1
  br label %443

443:                                              ; preds = %438, %430
  br label %444

444:                                              ; preds = %443, %420, %415, %406
  %445 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %446 = icmp ne %struct.VarScope* %445, null
  br i1 %446, label %447, label %471

447:                                              ; preds = %444
  %448 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %449 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %448, i32 0, i32 0
  %450 = load %struct.Obj*, %struct.Obj** %449, align 8
  %451 = icmp ne %struct.Obj* %450, null
  br i1 %451, label %452, label %458

452:                                              ; preds = %447
  %453 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %454 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %453, i32 0, i32 0
  %455 = load %struct.Obj*, %struct.Obj** %454, align 8
  %456 = load %struct.Token*, %struct.Token** %5, align 8
  %457 = call %struct.Node* @new_var_node(%struct.Obj* noundef %455, %struct.Token* noundef %456)
  store %struct.Node* %457, %struct.Node** %3, align 8
  br label %542

458:                                              ; preds = %447
  %459 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %460 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %459, i32 0, i32 2
  %461 = load %struct.Type*, %struct.Type** %460, align 8
  %462 = icmp ne %struct.Type* %461, null
  br i1 %462, label %463, label %470

463:                                              ; preds = %458
  %464 = load %struct.VarScope*, %struct.VarScope** %23, align 8
  %465 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %464, i32 0, i32 3
  %466 = load i32, i32* %465, align 8
  %467 = sext i32 %466 to i64
  %468 = load %struct.Token*, %struct.Token** %5, align 8
  %469 = call %struct.Node* @new_num(i64 noundef %467, %struct.Token* noundef %468)
  store %struct.Node* %469, %struct.Node** %3, align 8
  br label %542

470:                                              ; preds = %458
  br label %471

471:                                              ; preds = %470, %444
  %472 = load %struct.Token*, %struct.Token** %5, align 8
  %473 = getelementptr inbounds %struct.Token, %struct.Token* %472, i32 0, i32 1
  %474 = load %struct.Token*, %struct.Token** %473, align 8
  %475 = call zeroext i1 @equal(%struct.Token* noundef %474, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %475, label %476, label %483

476:                                              ; preds = %471
  %477 = load %struct.Token**, %struct.Token*** %4, align 8
  %478 = load %struct.Token*, %struct.Token** %5, align 8
  %479 = getelementptr inbounds %struct.Token, %struct.Token* %478, i32 0, i32 1
  %480 = load %struct.Token*, %struct.Token** %479, align 8
  %481 = call %struct.Node* @unary(%struct.Token** noundef %477, %struct.Token* noundef %480)
  store %struct.Node* %481, %struct.Node** %24, align 8
  %482 = load %struct.Node*, %struct.Node** %24, align 8
  store %struct.Node* %482, %struct.Node** %3, align 8
  br label %542

483:                                              ; preds = %471
  %484 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %484, i8* noundef getelementptr inbounds ([43 x i8], [43 x i8]* @.str.178, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

485:                                              ; preds = %401
  %486 = load %struct.Token*, %struct.Token** %5, align 8
  %487 = getelementptr inbounds %struct.Token, %struct.Token* %486, i32 0, i32 0
  %488 = load i32, i32* %487, align 16
  %489 = icmp eq i32 %488, 3
  br i1 %489, label %490, label %505

490:                                              ; preds = %485
  %491 = load %struct.Token*, %struct.Token** %5, align 8
  %492 = getelementptr inbounds %struct.Token, %struct.Token* %491, i32 0, i32 7
  %493 = load i8*, i8** %492, align 8
  %494 = load %struct.Token*, %struct.Token** %5, align 8
  %495 = getelementptr inbounds %struct.Token, %struct.Token* %494, i32 0, i32 6
  %496 = load %struct.Type*, %struct.Type** %495, align 16
  %497 = call %struct.Obj* @new_string_literal(i8* noundef %493, %struct.Type* noundef %496)
  store %struct.Obj* %497, %struct.Obj** %25, align 8
  %498 = load %struct.Token*, %struct.Token** %5, align 8
  %499 = getelementptr inbounds %struct.Token, %struct.Token* %498, i32 0, i32 1
  %500 = load %struct.Token*, %struct.Token** %499, align 8
  %501 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %500, %struct.Token** %501, align 8
  %502 = load %struct.Obj*, %struct.Obj** %25, align 8
  %503 = load %struct.Token*, %struct.Token** %5, align 8
  %504 = call %struct.Node* @new_var_node(%struct.Obj* noundef %502, %struct.Token* noundef %503)
  store %struct.Node* %504, %struct.Node** %3, align 8
  br label %542

505:                                              ; preds = %485
  %506 = load %struct.Token*, %struct.Token** %5, align 8
  %507 = getelementptr inbounds %struct.Token, %struct.Token* %506, i32 0, i32 0
  %508 = load i32, i32* %507, align 16
  %509 = icmp eq i32 %508, 4
  br i1 %509, label %510, label %540

510:                                              ; preds = %505
  %511 = load %struct.Token*, %struct.Token** %5, align 8
  %512 = getelementptr inbounds %struct.Token, %struct.Token* %511, i32 0, i32 6
  %513 = load %struct.Type*, %struct.Type** %512, align 16
  %514 = call zeroext i1 @is_flonum(%struct.Type* noundef %513)
  br i1 %514, label %515, label %523

515:                                              ; preds = %510
  %516 = load %struct.Token*, %struct.Token** %5, align 8
  %517 = call %struct.Node* @new_node(i32 noundef 42, %struct.Token* noundef %516)
  store %struct.Node* %517, %struct.Node** %26, align 8
  %518 = load %struct.Token*, %struct.Token** %5, align 8
  %519 = getelementptr inbounds %struct.Token, %struct.Token* %518, i32 0, i32 3
  %520 = load x86_fp80, x86_fp80* %519, align 16
  %521 = load %struct.Node*, %struct.Node** %26, align 8
  %522 = getelementptr inbounds %struct.Node, %struct.Node* %521, i32 0, i32 35
  store x86_fp80 %520, x86_fp80* %522, align 16
  br label %529

523:                                              ; preds = %510
  %524 = load %struct.Token*, %struct.Token** %5, align 8
  %525 = getelementptr inbounds %struct.Token, %struct.Token* %524, i32 0, i32 2
  %526 = load i64, i64* %525, align 16
  %527 = load %struct.Token*, %struct.Token** %5, align 8
  %528 = call %struct.Node* @new_num(i64 noundef %526, %struct.Token* noundef %527)
  store %struct.Node* %528, %struct.Node** %26, align 8
  br label %529

529:                                              ; preds = %523, %515
  %530 = load %struct.Token*, %struct.Token** %5, align 8
  %531 = getelementptr inbounds %struct.Token, %struct.Token* %530, i32 0, i32 6
  %532 = load %struct.Type*, %struct.Type** %531, align 16
  %533 = load %struct.Node*, %struct.Node** %26, align 8
  %534 = getelementptr inbounds %struct.Node, %struct.Node* %533, i32 0, i32 2
  store %struct.Type* %532, %struct.Type** %534, align 16
  %535 = load %struct.Token*, %struct.Token** %5, align 8
  %536 = getelementptr inbounds %struct.Token, %struct.Token* %535, i32 0, i32 1
  %537 = load %struct.Token*, %struct.Token** %536, align 8
  %538 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %537, %struct.Token** %538, align 8
  %539 = load %struct.Node*, %struct.Node** %26, align 8
  store %struct.Node* %539, %struct.Node** %3, align 8
  br label %542

540:                                              ; preds = %505
  %541 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %541, i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.179, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

542:                                              ; preds = %529, %490, %476, %463, %452, %391, %307, %277, %271, %268, %262, %230, %209, %191, %172, %148, %140, %117, %104, %98, %55, %35
  %543 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %543
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @funcall(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Node* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.Type*, align 8
  %9 = alloca %struct.Node, align 16
  %10 = alloca %struct.Node*, align 8
  %11 = alloca %struct.Node*, align 8
  %12 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Node* %2, %struct.Node** %6, align 8
  %13 = load %struct.Node*, %struct.Node** %6, align 8
  call void @add_type(%struct.Node* noundef %13)
  %14 = load %struct.Node*, %struct.Node** %6, align 8
  %15 = getelementptr inbounds %struct.Node, %struct.Node* %14, i32 0, i32 2
  %16 = load %struct.Type*, %struct.Type** %15, align 16
  %17 = getelementptr inbounds %struct.Type, %struct.Type* %16, i32 0, i32 0
  %18 = load i32, i32* %17, align 8
  %19 = icmp ne i32 %18, 11
  br i1 %19, label %20, label %40

20:                                               ; preds = %3
  %21 = load %struct.Node*, %struct.Node** %6, align 8
  %22 = getelementptr inbounds %struct.Node, %struct.Node* %21, i32 0, i32 2
  %23 = load %struct.Type*, %struct.Type** %22, align 16
  %24 = getelementptr inbounds %struct.Type, %struct.Type* %23, i32 0, i32 0
  %25 = load i32, i32* %24, align 8
  %26 = icmp ne i32 %25, 10
  br i1 %26, label %36, label %27

27:                                               ; preds = %20
  %28 = load %struct.Node*, %struct.Node** %6, align 8
  %29 = getelementptr inbounds %struct.Node, %struct.Node* %28, i32 0, i32 2
  %30 = load %struct.Type*, %struct.Type** %29, align 16
  %31 = getelementptr inbounds %struct.Type, %struct.Type* %30, i32 0, i32 8
  %32 = load %struct.Type*, %struct.Type** %31, align 8
  %33 = getelementptr inbounds %struct.Type, %struct.Type* %32, i32 0, i32 0
  %34 = load i32, i32* %33, align 8
  %35 = icmp ne i32 %34, 11
  br i1 %35, label %36, label %40

36:                                               ; preds = %27, %20
  %37 = load %struct.Node*, %struct.Node** %6, align 8
  %38 = getelementptr inbounds %struct.Node, %struct.Node* %37, i32 0, i32 3
  %39 = load %struct.Token*, %struct.Token** %38, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %39, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @.str.209, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

40:                                               ; preds = %27, %3
  %41 = load %struct.Node*, %struct.Node** %6, align 8
  %42 = getelementptr inbounds %struct.Node, %struct.Node* %41, i32 0, i32 2
  %43 = load %struct.Type*, %struct.Type** %42, align 16
  %44 = getelementptr inbounds %struct.Type, %struct.Type* %43, i32 0, i32 0
  %45 = load i32, i32* %44, align 8
  %46 = icmp eq i32 %45, 11
  br i1 %46, label %47, label %51

47:                                               ; preds = %40
  %48 = load %struct.Node*, %struct.Node** %6, align 8
  %49 = getelementptr inbounds %struct.Node, %struct.Node* %48, i32 0, i32 2
  %50 = load %struct.Type*, %struct.Type** %49, align 16
  br label %57

51:                                               ; preds = %40
  %52 = load %struct.Node*, %struct.Node** %6, align 8
  %53 = getelementptr inbounds %struct.Node, %struct.Node* %52, i32 0, i32 2
  %54 = load %struct.Type*, %struct.Type** %53, align 16
  %55 = getelementptr inbounds %struct.Type, %struct.Type* %54, i32 0, i32 8
  %56 = load %struct.Type*, %struct.Type** %55, align 8
  br label %57

57:                                               ; preds = %51, %47
  %58 = phi %struct.Type* [ %50, %47 ], [ %56, %51 ]
  store %struct.Type* %58, %struct.Type** %7, align 8
  %59 = load %struct.Type*, %struct.Type** %7, align 8
  %60 = getelementptr inbounds %struct.Type, %struct.Type* %59, i32 0, i32 18
  %61 = load %struct.Type*, %struct.Type** %60, align 8
  store %struct.Type* %61, %struct.Type** %8, align 8
  %62 = bitcast %struct.Node* %9 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %62, i8 0, i64 320, i1 false)
  store %struct.Node* %9, %struct.Node** %10, align 8
  br label %63

63:                                               ; preds = %119, %57
  %64 = load %struct.Token*, %struct.Token** %5, align 8
  %65 = call zeroext i1 @equal(%struct.Token* noundef %64, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %66 = xor i1 %65, true
  br i1 %66, label %67, label %123

67:                                               ; preds = %63
  %68 = load %struct.Node*, %struct.Node** %10, align 8
  %69 = icmp ne %struct.Node* %68, %9
  br i1 %69, label %70, label %73

70:                                               ; preds = %67
  %71 = load %struct.Token*, %struct.Token** %5, align 8
  %72 = call %struct.Token* @skip(%struct.Token* noundef %71, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %72, %struct.Token** %5, align 8
  br label %73

73:                                               ; preds = %70, %67
  %74 = load %struct.Token*, %struct.Token** %5, align 8
  %75 = call %struct.Node* @assign(%struct.Token** noundef %5, %struct.Token* noundef %74)
  store %struct.Node* %75, %struct.Node** %11, align 8
  %76 = load %struct.Node*, %struct.Node** %11, align 8
  call void @add_type(%struct.Node* noundef %76)
  %77 = load %struct.Type*, %struct.Type** %8, align 8
  %78 = icmp ne %struct.Type* %77, null
  br i1 %78, label %86, label %79

79:                                               ; preds = %73
  %80 = load %struct.Type*, %struct.Type** %7, align 8
  %81 = getelementptr inbounds %struct.Type, %struct.Type* %80, i32 0, i32 19
  %82 = load i8, i8* %81, align 8
  %83 = trunc i8 %82 to i1
  br i1 %83, label %86, label %84

84:                                               ; preds = %79
  %85 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %85, i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.210, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

86:                                               ; preds = %79, %73
  %87 = load %struct.Type*, %struct.Type** %8, align 8
  %88 = icmp ne %struct.Type* %87, null
  br i1 %88, label %89, label %107

89:                                               ; preds = %86
  %90 = load %struct.Type*, %struct.Type** %8, align 8
  %91 = getelementptr inbounds %struct.Type, %struct.Type* %90, i32 0, i32 0
  %92 = load i32, i32* %91, align 8
  %93 = icmp ne i32 %92, 14
  br i1 %93, label %94, label %103

94:                                               ; preds = %89
  %95 = load %struct.Type*, %struct.Type** %8, align 8
  %96 = getelementptr inbounds %struct.Type, %struct.Type* %95, i32 0, i32 0
  %97 = load i32, i32* %96, align 8
  %98 = icmp ne i32 %97, 15
  br i1 %98, label %99, label %103

99:                                               ; preds = %94
  %100 = load %struct.Node*, %struct.Node** %11, align 8
  %101 = load %struct.Type*, %struct.Type** %8, align 8
  %102 = call %struct.Node* @new_cast(%struct.Node* noundef %100, %struct.Type* noundef %101)
  store %struct.Node* %102, %struct.Node** %11, align 8
  br label %103

103:                                              ; preds = %99, %94, %89
  %104 = load %struct.Type*, %struct.Type** %8, align 8
  %105 = getelementptr inbounds %struct.Type, %struct.Type* %104, i32 0, i32 20
  %106 = load %struct.Type*, %struct.Type** %105, align 8
  store %struct.Type* %106, %struct.Type** %8, align 8
  br label %119

107:                                              ; preds = %86
  %108 = load %struct.Node*, %struct.Node** %11, align 8
  %109 = getelementptr inbounds %struct.Node, %struct.Node* %108, i32 0, i32 2
  %110 = load %struct.Type*, %struct.Type** %109, align 16
  %111 = getelementptr inbounds %struct.Type, %struct.Type* %110, i32 0, i32 0
  %112 = load i32, i32* %111, align 8
  %113 = icmp eq i32 %112, 6
  br i1 %113, label %114, label %118

114:                                              ; preds = %107
  %115 = load %struct.Node*, %struct.Node** %11, align 8
  %116 = load %struct.Type*, %struct.Type** @ty_double, align 8
  %117 = call %struct.Node* @new_cast(%struct.Node* noundef %115, %struct.Type* noundef %116)
  store %struct.Node* %117, %struct.Node** %11, align 8
  br label %118

118:                                              ; preds = %114, %107
  br label %119

119:                                              ; preds = %118, %103
  %120 = load %struct.Node*, %struct.Node** %11, align 8
  %121 = load %struct.Node*, %struct.Node** %10, align 8
  %122 = getelementptr inbounds %struct.Node, %struct.Node* %121, i32 0, i32 1
  store %struct.Node* %120, %struct.Node** %122, align 8
  store %struct.Node* %120, %struct.Node** %10, align 8
  br label %63, !llvm.loop !32

123:                                              ; preds = %63
  %124 = load %struct.Type*, %struct.Type** %8, align 8
  %125 = icmp ne %struct.Type* %124, null
  br i1 %125, label %126, label %128

126:                                              ; preds = %123
  %127 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %127, i8* noundef getelementptr inbounds ([35 x i8], [35 x i8]* @.str.211, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

128:                                              ; preds = %123
  %129 = load %struct.Token*, %struct.Token** %5, align 8
  %130 = call %struct.Token* @skip(%struct.Token* noundef %129, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %131 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %130, %struct.Token** %131, align 8
  %132 = load %struct.Node*, %struct.Node** %6, align 8
  %133 = load %struct.Token*, %struct.Token** %5, align 8
  %134 = call %struct.Node* @new_unary(i32 noundef 37, %struct.Node* noundef %132, %struct.Token* noundef %133)
  store %struct.Node* %134, %struct.Node** %12, align 8
  %135 = load %struct.Type*, %struct.Type** %7, align 8
  %136 = load %struct.Node*, %struct.Node** %12, align 8
  %137 = getelementptr inbounds %struct.Node, %struct.Node* %136, i32 0, i32 15
  store %struct.Type* %135, %struct.Type** %137, align 8
  %138 = load %struct.Type*, %struct.Type** %7, align 8
  %139 = getelementptr inbounds %struct.Type, %struct.Type* %138, i32 0, i32 17
  %140 = load %struct.Type*, %struct.Type** %139, align 8
  %141 = load %struct.Node*, %struct.Node** %12, align 8
  %142 = getelementptr inbounds %struct.Node, %struct.Node* %141, i32 0, i32 2
  store %struct.Type* %140, %struct.Type** %142, align 16
  %143 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 1
  %144 = load %struct.Node*, %struct.Node** %143, align 8
  %145 = load %struct.Node*, %struct.Node** %12, align 8
  %146 = getelementptr inbounds %struct.Node, %struct.Node* %145, i32 0, i32 16
  store %struct.Node* %144, %struct.Node** %146, align 16
  %147 = load %struct.Node*, %struct.Node** %12, align 8
  %148 = getelementptr inbounds %struct.Node, %struct.Node* %147, i32 0, i32 2
  %149 = load %struct.Type*, %struct.Type** %148, align 16
  %150 = getelementptr inbounds %struct.Type, %struct.Type* %149, i32 0, i32 0
  %151 = load i32, i32* %150, align 8
  %152 = icmp eq i32 %151, 14
  br i1 %152, label %160, label %153

153:                                              ; preds = %128
  %154 = load %struct.Node*, %struct.Node** %12, align 8
  %155 = getelementptr inbounds %struct.Node, %struct.Node* %154, i32 0, i32 2
  %156 = load %struct.Type*, %struct.Type** %155, align 16
  %157 = getelementptr inbounds %struct.Type, %struct.Type* %156, i32 0, i32 0
  %158 = load i32, i32* %157, align 8
  %159 = icmp eq i32 %158, 15
  br i1 %159, label %160, label %167

160:                                              ; preds = %153, %128
  %161 = load %struct.Node*, %struct.Node** %12, align 8
  %162 = getelementptr inbounds %struct.Node, %struct.Node* %161, i32 0, i32 2
  %163 = load %struct.Type*, %struct.Type** %162, align 16
  %164 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %163, i8* noundef null)
  %165 = load %struct.Node*, %struct.Node** %12, align 8
  %166 = getelementptr inbounds %struct.Node, %struct.Node* %165, i32 0, i32 18
  store %struct.Obj* %164, %struct.Obj** %166, align 16
  br label %167

167:                                              ; preds = %160, %153
  %168 = load %struct.Node*, %struct.Node** %12, align 8
  ret %struct.Node* %168
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @struct_ref(%struct.Node* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Type*, align 8
  %6 = alloca %struct.Member*, align 8
  store %struct.Node* %0, %struct.Node** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Node*, %struct.Node** %3, align 8
  call void @add_type(%struct.Node* noundef %7)
  %8 = load %struct.Node*, %struct.Node** %3, align 8
  %9 = getelementptr inbounds %struct.Node, %struct.Node* %8, i32 0, i32 2
  %10 = load %struct.Type*, %struct.Type** %9, align 16
  %11 = getelementptr inbounds %struct.Type, %struct.Type* %10, i32 0, i32 0
  %12 = load i32, i32* %11, align 8
  %13 = icmp ne i32 %12, 14
  br i1 %13, label %14, label %25

14:                                               ; preds = %2
  %15 = load %struct.Node*, %struct.Node** %3, align 8
  %16 = getelementptr inbounds %struct.Node, %struct.Node* %15, i32 0, i32 2
  %17 = load %struct.Type*, %struct.Type** %16, align 16
  %18 = getelementptr inbounds %struct.Type, %struct.Type* %17, i32 0, i32 0
  %19 = load i32, i32* %18, align 8
  %20 = icmp ne i32 %19, 15
  br i1 %20, label %21, label %25

21:                                               ; preds = %14
  %22 = load %struct.Node*, %struct.Node** %3, align 8
  %23 = getelementptr inbounds %struct.Node, %struct.Node* %22, i32 0, i32 3
  %24 = load %struct.Token*, %struct.Token** %23, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %24, i8* noundef getelementptr inbounds ([45 x i8], [45 x i8]* @.str.212, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

25:                                               ; preds = %14, %2
  %26 = load %struct.Node*, %struct.Node** %3, align 8
  %27 = getelementptr inbounds %struct.Node, %struct.Node* %26, i32 0, i32 2
  %28 = load %struct.Type*, %struct.Type** %27, align 16
  store %struct.Type* %28, %struct.Type** %5, align 8
  br label %29

29:                                               ; preds = %49, %25
  %30 = load %struct.Type*, %struct.Type** %5, align 8
  %31 = load %struct.Token*, %struct.Token** %4, align 8
  %32 = call %struct.Member* @get_struct_member(%struct.Type* noundef %30, %struct.Token* noundef %31)
  store %struct.Member* %32, %struct.Member** %6, align 8
  %33 = load %struct.Member*, %struct.Member** %6, align 8
  %34 = icmp ne %struct.Member* %33, null
  br i1 %34, label %37, label %35

35:                                               ; preds = %29
  %36 = load %struct.Token*, %struct.Token** %4, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %36, i8* noundef getelementptr inbounds ([35 x i8], [35 x i8]* @.str.213, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

37:                                               ; preds = %29
  %38 = load %struct.Node*, %struct.Node** %3, align 8
  %39 = load %struct.Token*, %struct.Token** %4, align 8
  %40 = call %struct.Node* @new_unary(i32 noundef 19, %struct.Node* noundef %38, %struct.Token* noundef %39)
  store %struct.Node* %40, %struct.Node** %3, align 8
  %41 = load %struct.Member*, %struct.Member** %6, align 8
  %42 = load %struct.Node*, %struct.Node** %3, align 8
  %43 = getelementptr inbounds %struct.Node, %struct.Node* %42, i32 0, i32 14
  store %struct.Member* %41, %struct.Member** %43, align 16
  %44 = load %struct.Member*, %struct.Member** %6, align 8
  %45 = getelementptr inbounds %struct.Member, %struct.Member* %44, i32 0, i32 3
  %46 = load %struct.Token*, %struct.Token** %45, align 8
  %47 = icmp ne %struct.Token* %46, null
  br i1 %47, label %48, label %49

48:                                               ; preds = %37
  br label %53

49:                                               ; preds = %37
  %50 = load %struct.Member*, %struct.Member** %6, align 8
  %51 = getelementptr inbounds %struct.Member, %struct.Member* %50, i32 0, i32 1
  %52 = load %struct.Type*, %struct.Type** %51, align 8
  store %struct.Type* %52, %struct.Type** %5, align 8
  br label %29

53:                                               ; preds = %48
  %54 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %54
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_inc_dec(%struct.Node* noundef %0, %struct.Token* noundef %1, i32 noundef %2) #0 {
  %4 = alloca %struct.Node*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca i32, align 4
  store %struct.Node* %0, %struct.Node** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store i32 %2, i32* %6, align 4
  %7 = load %struct.Node*, %struct.Node** %4, align 8
  call void @add_type(%struct.Node* noundef %7)
  %8 = load %struct.Node*, %struct.Node** %4, align 8
  %9 = load i32, i32* %6, align 4
  %10 = sext i32 %9 to i64
  %11 = load %struct.Token*, %struct.Token** %5, align 8
  %12 = call %struct.Node* @new_num(i64 noundef %10, %struct.Token* noundef %11)
  %13 = load %struct.Token*, %struct.Token** %5, align 8
  %14 = call %struct.Node* @new_add(%struct.Node* noundef %8, %struct.Node* noundef %12, %struct.Token* noundef %13)
  %15 = call %struct.Node* @to_assign(%struct.Node* noundef %14)
  %16 = load i32, i32* %6, align 4
  %17 = sub nsw i32 0, %16
  %18 = sext i32 %17 to i64
  %19 = load %struct.Token*, %struct.Token** %5, align 8
  %20 = call %struct.Node* @new_num(i64 noundef %18, %struct.Token* noundef %19)
  %21 = load %struct.Token*, %struct.Token** %5, align 8
  %22 = call %struct.Node* @new_add(%struct.Node* noundef %15, %struct.Node* noundef %20, %struct.Token* noundef %21)
  %23 = load %struct.Node*, %struct.Node** %4, align 8
  %24 = getelementptr inbounds %struct.Node, %struct.Node* %23, i32 0, i32 2
  %25 = load %struct.Type*, %struct.Type** %24, align 16
  %26 = call %struct.Node* @new_cast(%struct.Node* noundef %22, %struct.Type* noundef %25)
  ret %struct.Node* %26
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Obj* @new_gvar(i8* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Obj*, align 8
  store i8* %0, i8** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  %6 = load i8*, i8** %3, align 8
  %7 = load %struct.Type*, %struct.Type** %4, align 8
  %8 = call %struct.Obj* @new_var(i8* noundef %6, %struct.Type* noundef %7)
  store %struct.Obj* %8, %struct.Obj** %5, align 8
  %9 = load %struct.Obj*, %struct.Obj** @globals, align 8
  %10 = load %struct.Obj*, %struct.Obj** %5, align 8
  %11 = getelementptr inbounds %struct.Obj, %struct.Obj* %10, i32 0, i32 0
  store %struct.Obj* %9, %struct.Obj** %11, align 8
  %12 = load %struct.Obj*, %struct.Obj** %5, align 8
  %13 = getelementptr inbounds %struct.Obj, %struct.Obj* %12, i32 0, i32 12
  store i8 1, i8* %13, align 2
  %14 = load %struct.Obj*, %struct.Obj** %5, align 8
  %15 = getelementptr inbounds %struct.Obj, %struct.Obj* %14, i32 0, i32 11
  store i8 1, i8* %15, align 1
  %16 = load %struct.Obj*, %struct.Obj** %5, align 8
  store %struct.Obj* %16, %struct.Obj** @globals, align 8
  %17 = load %struct.Obj*, %struct.Obj** %5, align 8
  ret %struct.Obj* %17
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Obj* @new_var(i8* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Obj*, align 8
  store i8* %0, i8** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  %6 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 160) #8
  %7 = bitcast i8* %6 to %struct.Obj*
  store %struct.Obj* %7, %struct.Obj** %5, align 8
  %8 = load %struct.Obj*, %struct.Obj** %5, align 8
  %9 = icmp eq %struct.Obj* %8, null
  br i1 %9, label %10, label %11

10:                                               ; preds = %2
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([29 x i8], [29 x i8]* @.str.136, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

11:                                               ; preds = %2
  %12 = load i8*, i8** %3, align 8
  %13 = load %struct.Obj*, %struct.Obj** %5, align 8
  %14 = getelementptr inbounds %struct.Obj, %struct.Obj* %13, i32 0, i32 1
  store i8* %12, i8** %14, align 8
  %15 = load %struct.Type*, %struct.Type** %4, align 8
  %16 = load %struct.Obj*, %struct.Obj** %5, align 8
  %17 = getelementptr inbounds %struct.Obj, %struct.Obj* %16, i32 0, i32 3
  store %struct.Type* %15, %struct.Type** %17, align 8
  %18 = load %struct.Type*, %struct.Type** %4, align 8
  %19 = getelementptr inbounds %struct.Type, %struct.Type* %18, i32 0, i32 2
  %20 = load i32, i32* %19, align 8
  %21 = load %struct.Obj*, %struct.Obj** %5, align 8
  %22 = getelementptr inbounds %struct.Obj, %struct.Obj* %21, i32 0, i32 6
  store i32 %20, i32* %22, align 4
  %23 = load %struct.Obj*, %struct.Obj** %5, align 8
  %24 = load i8*, i8** %3, align 8
  %25 = call %struct.VarScope* @push_scope(i8* noundef %24)
  %26 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %25, i32 0, i32 0
  store %struct.Obj* %23, %struct.Obj** %26, align 8
  %27 = load %struct.Obj*, %struct.Obj** %5, align 8
  ret %struct.Obj* %27
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.VarScope* @push_scope(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.VarScope*, align 8
  store i8* %0, i8** %2, align 8
  %4 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 32) #8
  %5 = bitcast i8* %4 to %struct.VarScope*
  store %struct.VarScope* %5, %struct.VarScope** %3, align 8
  %6 = load %struct.VarScope*, %struct.VarScope** %3, align 8
  %7 = icmp eq %struct.VarScope* %6, null
  br i1 %7, label %8, label %9

8:                                                ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @.str.137, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

9:                                                ; preds = %1
  %10 = load %struct.Scope*, %struct.Scope** @scope, align 8
  %11 = getelementptr inbounds %struct.Scope, %struct.Scope* %10, i32 0, i32 1
  %12 = load i8*, i8** %2, align 8
  %13 = load %struct.VarScope*, %struct.VarScope** %3, align 8
  %14 = bitcast %struct.VarScope* %13 to i8*
  call void @hashmap_put(%struct.HashMap* noundef %11, i8* noundef %12, i8* noundef %14)
  %15 = load %struct.VarScope*, %struct.VarScope** %3, align 8
  ret %struct.VarScope* %15
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Initializer* @initializer(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2, %struct.Type** noundef %3) #0 {
  %5 = alloca %struct.Initializer*, align 8
  %6 = alloca %struct.Token**, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca %struct.Type*, align 8
  %9 = alloca %struct.Type**, align 8
  %10 = alloca %struct.Initializer*, align 8
  %11 = alloca %struct.Member*, align 8
  store %struct.Token** %0, %struct.Token*** %6, align 8
  store %struct.Token* %1, %struct.Token** %7, align 8
  store %struct.Type* %2, %struct.Type** %8, align 8
  store %struct.Type** %3, %struct.Type*** %9, align 8
  %12 = load %struct.Type*, %struct.Type** %8, align 8
  %13 = call %struct.Initializer* @new_initializer(%struct.Type* noundef %12, i1 noundef zeroext true)
  store %struct.Initializer* %13, %struct.Initializer** %10, align 8
  %14 = load %struct.Token**, %struct.Token*** %6, align 8
  %15 = load %struct.Token*, %struct.Token** %7, align 8
  %16 = load %struct.Initializer*, %struct.Initializer** %10, align 8
  call void @initializer2(%struct.Token** noundef %14, %struct.Token* noundef %15, %struct.Initializer* noundef %16)
  %17 = load %struct.Type*, %struct.Type** %8, align 8
  %18 = getelementptr inbounds %struct.Type, %struct.Type* %17, i32 0, i32 0
  %19 = load i32, i32* %18, align 8
  %20 = icmp eq i32 %19, 14
  br i1 %20, label %26, label %21

21:                                               ; preds = %4
  %22 = load %struct.Type*, %struct.Type** %8, align 8
  %23 = getelementptr inbounds %struct.Type, %struct.Type* %22, i32 0, i32 0
  %24 = load i32, i32* %23, align 8
  %25 = icmp eq i32 %24, 15
  br i1 %25, label %26, label %72

26:                                               ; preds = %21, %4
  %27 = load %struct.Type*, %struct.Type** %8, align 8
  %28 = getelementptr inbounds %struct.Type, %struct.Type* %27, i32 0, i32 15
  %29 = load i8, i8* %28, align 8
  %30 = trunc i8 %29 to i1
  br i1 %30, label %31, label %72

31:                                               ; preds = %26
  %32 = load %struct.Type*, %struct.Type** %8, align 8
  %33 = call %struct.Type* @copy_struct_type(%struct.Type* noundef %32)
  store %struct.Type* %33, %struct.Type** %8, align 8
  %34 = load %struct.Type*, %struct.Type** %8, align 8
  %35 = getelementptr inbounds %struct.Type, %struct.Type* %34, i32 0, i32 14
  %36 = load %struct.Member*, %struct.Member** %35, align 8
  store %struct.Member* %36, %struct.Member** %11, align 8
  br label %37

37:                                               ; preds = %42, %31
  %38 = load %struct.Member*, %struct.Member** %11, align 8
  %39 = getelementptr inbounds %struct.Member, %struct.Member* %38, i32 0, i32 0
  %40 = load %struct.Member*, %struct.Member** %39, align 8
  %41 = icmp ne %struct.Member* %40, null
  br i1 %41, label %42, label %46

42:                                               ; preds = %37
  %43 = load %struct.Member*, %struct.Member** %11, align 8
  %44 = getelementptr inbounds %struct.Member, %struct.Member* %43, i32 0, i32 0
  %45 = load %struct.Member*, %struct.Member** %44, align 8
  store %struct.Member* %45, %struct.Member** %11, align 8
  br label %37, !llvm.loop !33

46:                                               ; preds = %37
  %47 = load %struct.Initializer*, %struct.Initializer** %10, align 8
  %48 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %47, i32 0, i32 5
  %49 = load %struct.Initializer**, %struct.Initializer*** %48, align 8
  %50 = load %struct.Member*, %struct.Member** %11, align 8
  %51 = getelementptr inbounds %struct.Member, %struct.Member* %50, i32 0, i32 4
  %52 = load i32, i32* %51, align 8
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %49, i64 %53
  %55 = load %struct.Initializer*, %struct.Initializer** %54, align 8
  %56 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %55, i32 0, i32 1
  %57 = load %struct.Type*, %struct.Type** %56, align 8
  %58 = load %struct.Member*, %struct.Member** %11, align 8
  %59 = getelementptr inbounds %struct.Member, %struct.Member* %58, i32 0, i32 1
  store %struct.Type* %57, %struct.Type** %59, align 8
  %60 = load %struct.Member*, %struct.Member** %11, align 8
  %61 = getelementptr inbounds %struct.Member, %struct.Member* %60, i32 0, i32 1
  %62 = load %struct.Type*, %struct.Type** %61, align 8
  %63 = getelementptr inbounds %struct.Type, %struct.Type* %62, i32 0, i32 1
  %64 = load i32, i32* %63, align 4
  %65 = load %struct.Type*, %struct.Type** %8, align 8
  %66 = getelementptr inbounds %struct.Type, %struct.Type* %65, i32 0, i32 1
  %67 = load i32, i32* %66, align 4
  %68 = add nsw i32 %67, %64
  store i32 %68, i32* %66, align 4
  %69 = load %struct.Type*, %struct.Type** %8, align 8
  %70 = load %struct.Type**, %struct.Type*** %9, align 8
  store %struct.Type* %69, %struct.Type** %70, align 8
  %71 = load %struct.Initializer*, %struct.Initializer** %10, align 8
  store %struct.Initializer* %71, %struct.Initializer** %5, align 8
  br label %78

72:                                               ; preds = %26, %21
  %73 = load %struct.Initializer*, %struct.Initializer** %10, align 8
  %74 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %73, i32 0, i32 1
  %75 = load %struct.Type*, %struct.Type** %74, align 8
  %76 = load %struct.Type**, %struct.Type*** %9, align 8
  store %struct.Type* %75, %struct.Type** %76, align 8
  %77 = load %struct.Initializer*, %struct.Initializer** %10, align 8
  store %struct.Initializer* %77, %struct.Initializer** %5, align 8
  br label %78

78:                                               ; preds = %72, %46
  %79 = load %struct.Initializer*, %struct.Initializer** %5, align 8
  ret %struct.Initializer* %79
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Relocation* @write_gvar_data(%struct.Relocation* noundef %0, %struct.Initializer* noundef %1, %struct.Type* noundef %2, i8* noundef %3, i32 noundef %4) #0 {
  %6 = alloca %struct.Relocation*, align 8
  %7 = alloca %struct.Relocation*, align 8
  %8 = alloca %struct.Initializer*, align 8
  %9 = alloca %struct.Type*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca %struct.Member*, align 8
  %15 = alloca %struct.Node*, align 8
  %16 = alloca i8*, align 8
  %17 = alloca i64, align 8
  %18 = alloca i64, align 8
  %19 = alloca i64, align 8
  %20 = alloca i64, align 8
  %21 = alloca i8**, align 8
  %22 = alloca i64, align 8
  %23 = alloca %struct.Relocation*, align 8
  store %struct.Relocation* %0, %struct.Relocation** %7, align 8
  store %struct.Initializer* %1, %struct.Initializer** %8, align 8
  store %struct.Type* %2, %struct.Type** %9, align 8
  store i8* %3, i8** %10, align 8
  store i32 %4, i32* %11, align 4
  %24 = load %struct.Type*, %struct.Type** %9, align 8
  %25 = getelementptr inbounds %struct.Type, %struct.Type* %24, i32 0, i32 0
  %26 = load i32, i32* %25, align 8
  %27 = icmp eq i32 %26, 12
  br i1 %27, label %28, label %64

28:                                               ; preds = %5
  %29 = load %struct.Type*, %struct.Type** %9, align 8
  %30 = getelementptr inbounds %struct.Type, %struct.Type* %29, i32 0, i32 8
  %31 = load %struct.Type*, %struct.Type** %30, align 8
  %32 = getelementptr inbounds %struct.Type, %struct.Type* %31, i32 0, i32 1
  %33 = load i32, i32* %32, align 4
  store i32 %33, i32* %12, align 4
  store i32 0, i32* %13, align 4
  br label %34

34:                                               ; preds = %59, %28
  %35 = load i32, i32* %13, align 4
  %36 = load %struct.Type*, %struct.Type** %9, align 8
  %37 = getelementptr inbounds %struct.Type, %struct.Type* %36, i32 0, i32 11
  %38 = load i32, i32* %37, align 8
  %39 = icmp slt i32 %35, %38
  br i1 %39, label %40, label %62

40:                                               ; preds = %34
  %41 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  %42 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %43 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %42, i32 0, i32 5
  %44 = load %struct.Initializer**, %struct.Initializer*** %43, align 8
  %45 = load i32, i32* %13, align 4
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %44, i64 %46
  %48 = load %struct.Initializer*, %struct.Initializer** %47, align 8
  %49 = load %struct.Type*, %struct.Type** %9, align 8
  %50 = getelementptr inbounds %struct.Type, %struct.Type* %49, i32 0, i32 8
  %51 = load %struct.Type*, %struct.Type** %50, align 8
  %52 = load i8*, i8** %10, align 8
  %53 = load i32, i32* %11, align 4
  %54 = load i32, i32* %12, align 4
  %55 = load i32, i32* %13, align 4
  %56 = mul nsw i32 %54, %55
  %57 = add nsw i32 %53, %56
  %58 = call %struct.Relocation* @write_gvar_data(%struct.Relocation* noundef %41, %struct.Initializer* noundef %48, %struct.Type* noundef %51, i8* noundef %52, i32 noundef %57)
  store %struct.Relocation* %58, %struct.Relocation** %7, align 8
  br label %59

59:                                               ; preds = %40
  %60 = load i32, i32* %13, align 4
  %61 = add nsw i32 %60, 1
  store i32 %61, i32* %13, align 4
  br label %34, !llvm.loop !34

62:                                               ; preds = %34
  %63 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  store %struct.Relocation* %63, %struct.Relocation** %6, align 8
  br label %278

64:                                               ; preds = %5
  %65 = load %struct.Type*, %struct.Type** %9, align 8
  %66 = getelementptr inbounds %struct.Type, %struct.Type* %65, i32 0, i32 0
  %67 = load i32, i32* %66, align 8
  %68 = icmp eq i32 %67, 14
  br i1 %68, label %69, label %166

69:                                               ; preds = %64
  %70 = load %struct.Type*, %struct.Type** %9, align 8
  %71 = getelementptr inbounds %struct.Type, %struct.Type* %70, i32 0, i32 14
  %72 = load %struct.Member*, %struct.Member** %71, align 8
  store %struct.Member* %72, %struct.Member** %14, align 8
  br label %73

73:                                               ; preds = %160, %69
  %74 = load %struct.Member*, %struct.Member** %14, align 8
  %75 = icmp ne %struct.Member* %74, null
  br i1 %75, label %76, label %164

76:                                               ; preds = %73
  %77 = load %struct.Member*, %struct.Member** %14, align 8
  %78 = getelementptr inbounds %struct.Member, %struct.Member* %77, i32 0, i32 7
  %79 = load i8, i8* %78, align 4
  %80 = trunc i8 %79 to i1
  br i1 %80, label %81, label %138

81:                                               ; preds = %76
  %82 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %83 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %82, i32 0, i32 5
  %84 = load %struct.Initializer**, %struct.Initializer*** %83, align 8
  %85 = load %struct.Member*, %struct.Member** %14, align 8
  %86 = getelementptr inbounds %struct.Member, %struct.Member* %85, i32 0, i32 4
  %87 = load i32, i32* %86, align 8
  %88 = sext i32 %87 to i64
  %89 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %84, i64 %88
  %90 = load %struct.Initializer*, %struct.Initializer** %89, align 8
  %91 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %90, i32 0, i32 4
  %92 = load %struct.Node*, %struct.Node** %91, align 8
  store %struct.Node* %92, %struct.Node** %15, align 8
  %93 = load %struct.Node*, %struct.Node** %15, align 8
  %94 = icmp ne %struct.Node* %93, null
  br i1 %94, label %96, label %95

95:                                               ; preds = %81
  br label %164

96:                                               ; preds = %81
  %97 = load i8*, i8** %10, align 8
  %98 = load i32, i32* %11, align 4
  %99 = sext i32 %98 to i64
  %100 = getelementptr inbounds i8, i8* %97, i64 %99
  %101 = load %struct.Member*, %struct.Member** %14, align 8
  %102 = getelementptr inbounds %struct.Member, %struct.Member* %101, i32 0, i32 6
  %103 = load i32, i32* %102, align 8
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds i8, i8* %100, i64 %104
  store i8* %105, i8** %16, align 8
  %106 = load i8*, i8** %16, align 8
  %107 = load %struct.Member*, %struct.Member** %14, align 8
  %108 = getelementptr inbounds %struct.Member, %struct.Member* %107, i32 0, i32 1
  %109 = load %struct.Type*, %struct.Type** %108, align 8
  %110 = getelementptr inbounds %struct.Type, %struct.Type* %109, i32 0, i32 1
  %111 = load i32, i32* %110, align 4
  %112 = call i64 @read_buf(i8* noundef %106, i32 noundef %111)
  store i64 %112, i64* %17, align 8
  %113 = load %struct.Node*, %struct.Node** %15, align 8
  %114 = call i64 @eval(%struct.Node* noundef %113)
  store i64 %114, i64* %18, align 8
  %115 = load %struct.Member*, %struct.Member** %14, align 8
  %116 = getelementptr inbounds %struct.Member, %struct.Member* %115, i32 0, i32 9
  %117 = load i32, i32* %116, align 4
  %118 = zext i32 %117 to i64
  %119 = shl i64 1, %118
  %120 = sub nsw i64 %119, 1
  store i64 %120, i64* %19, align 8
  %121 = load i64, i64* %17, align 8
  %122 = load i64, i64* %18, align 8
  %123 = load i64, i64* %19, align 8
  %124 = and i64 %122, %123
  %125 = load %struct.Member*, %struct.Member** %14, align 8
  %126 = getelementptr inbounds %struct.Member, %struct.Member* %125, i32 0, i32 8
  %127 = load i32, i32* %126, align 8
  %128 = zext i32 %127 to i64
  %129 = shl i64 %124, %128
  %130 = or i64 %121, %129
  store i64 %130, i64* %20, align 8
  %131 = load i8*, i8** %16, align 8
  %132 = load i64, i64* %20, align 8
  %133 = load %struct.Member*, %struct.Member** %14, align 8
  %134 = getelementptr inbounds %struct.Member, %struct.Member* %133, i32 0, i32 1
  %135 = load %struct.Type*, %struct.Type** %134, align 8
  %136 = getelementptr inbounds %struct.Type, %struct.Type* %135, i32 0, i32 1
  %137 = load i32, i32* %136, align 4
  call void @write_buf(i8* noundef %131, i64 noundef %132, i32 noundef %137)
  br label %159

138:                                              ; preds = %76
  %139 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  %140 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %141 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %140, i32 0, i32 5
  %142 = load %struct.Initializer**, %struct.Initializer*** %141, align 8
  %143 = load %struct.Member*, %struct.Member** %14, align 8
  %144 = getelementptr inbounds %struct.Member, %struct.Member* %143, i32 0, i32 4
  %145 = load i32, i32* %144, align 8
  %146 = sext i32 %145 to i64
  %147 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %142, i64 %146
  %148 = load %struct.Initializer*, %struct.Initializer** %147, align 8
  %149 = load %struct.Member*, %struct.Member** %14, align 8
  %150 = getelementptr inbounds %struct.Member, %struct.Member* %149, i32 0, i32 1
  %151 = load %struct.Type*, %struct.Type** %150, align 8
  %152 = load i8*, i8** %10, align 8
  %153 = load i32, i32* %11, align 4
  %154 = load %struct.Member*, %struct.Member** %14, align 8
  %155 = getelementptr inbounds %struct.Member, %struct.Member* %154, i32 0, i32 6
  %156 = load i32, i32* %155, align 8
  %157 = add nsw i32 %153, %156
  %158 = call %struct.Relocation* @write_gvar_data(%struct.Relocation* noundef %139, %struct.Initializer* noundef %148, %struct.Type* noundef %151, i8* noundef %152, i32 noundef %157)
  store %struct.Relocation* %158, %struct.Relocation** %7, align 8
  br label %159

159:                                              ; preds = %138, %96
  br label %160

160:                                              ; preds = %159
  %161 = load %struct.Member*, %struct.Member** %14, align 8
  %162 = getelementptr inbounds %struct.Member, %struct.Member* %161, i32 0, i32 0
  %163 = load %struct.Member*, %struct.Member** %162, align 8
  store %struct.Member* %163, %struct.Member** %14, align 8
  br label %73, !llvm.loop !35

164:                                              ; preds = %95, %73
  %165 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  store %struct.Relocation* %165, %struct.Relocation** %6, align 8
  br label %278

166:                                              ; preds = %64
  %167 = load %struct.Type*, %struct.Type** %9, align 8
  %168 = getelementptr inbounds %struct.Type, %struct.Type* %167, i32 0, i32 0
  %169 = load i32, i32* %168, align 8
  %170 = icmp eq i32 %169, 15
  br i1 %170, label %171, label %199

171:                                              ; preds = %166
  %172 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %173 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %172, i32 0, i32 6
  %174 = load %struct.Member*, %struct.Member** %173, align 8
  %175 = icmp ne %struct.Member* %174, null
  br i1 %175, label %178, label %176

176:                                              ; preds = %171
  %177 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  store %struct.Relocation* %177, %struct.Relocation** %6, align 8
  br label %278

178:                                              ; preds = %171
  %179 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  %180 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %181 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %180, i32 0, i32 5
  %182 = load %struct.Initializer**, %struct.Initializer*** %181, align 8
  %183 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %184 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %183, i32 0, i32 6
  %185 = load %struct.Member*, %struct.Member** %184, align 8
  %186 = getelementptr inbounds %struct.Member, %struct.Member* %185, i32 0, i32 4
  %187 = load i32, i32* %186, align 8
  %188 = sext i32 %187 to i64
  %189 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %182, i64 %188
  %190 = load %struct.Initializer*, %struct.Initializer** %189, align 8
  %191 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %192 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %191, i32 0, i32 6
  %193 = load %struct.Member*, %struct.Member** %192, align 8
  %194 = getelementptr inbounds %struct.Member, %struct.Member* %193, i32 0, i32 1
  %195 = load %struct.Type*, %struct.Type** %194, align 8
  %196 = load i8*, i8** %10, align 8
  %197 = load i32, i32* %11, align 4
  %198 = call %struct.Relocation* @write_gvar_data(%struct.Relocation* noundef %179, %struct.Initializer* noundef %190, %struct.Type* noundef %195, i8* noundef %196, i32 noundef %197)
  store %struct.Relocation* %198, %struct.Relocation** %6, align 8
  br label %278

199:                                              ; preds = %166
  %200 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %201 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %200, i32 0, i32 4
  %202 = load %struct.Node*, %struct.Node** %201, align 8
  %203 = icmp ne %struct.Node* %202, null
  br i1 %203, label %206, label %204

204:                                              ; preds = %199
  %205 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  store %struct.Relocation* %205, %struct.Relocation** %6, align 8
  br label %278

206:                                              ; preds = %199
  %207 = load %struct.Type*, %struct.Type** %9, align 8
  %208 = getelementptr inbounds %struct.Type, %struct.Type* %207, i32 0, i32 0
  %209 = load i32, i32* %208, align 8
  %210 = icmp eq i32 %209, 6
  br i1 %210, label %211, label %223

211:                                              ; preds = %206
  %212 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %213 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %212, i32 0, i32 4
  %214 = load %struct.Node*, %struct.Node** %213, align 8
  %215 = call double @eval_double(%struct.Node* noundef %214)
  %216 = fptrunc double %215 to float
  %217 = load i8*, i8** %10, align 8
  %218 = load i32, i32* %11, align 4
  %219 = sext i32 %218 to i64
  %220 = getelementptr inbounds i8, i8* %217, i64 %219
  %221 = bitcast i8* %220 to float*
  store float %216, float* %221, align 4
  %222 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  store %struct.Relocation* %222, %struct.Relocation** %6, align 8
  br label %278

223:                                              ; preds = %206
  %224 = load %struct.Type*, %struct.Type** %9, align 8
  %225 = getelementptr inbounds %struct.Type, %struct.Type* %224, i32 0, i32 0
  %226 = load i32, i32* %225, align 8
  %227 = icmp eq i32 %226, 7
  br i1 %227, label %228, label %239

228:                                              ; preds = %223
  %229 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %230 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %229, i32 0, i32 4
  %231 = load %struct.Node*, %struct.Node** %230, align 8
  %232 = call double @eval_double(%struct.Node* noundef %231)
  %233 = load i8*, i8** %10, align 8
  %234 = load i32, i32* %11, align 4
  %235 = sext i32 %234 to i64
  %236 = getelementptr inbounds i8, i8* %233, i64 %235
  %237 = bitcast i8* %236 to double*
  store double %232, double* %237, align 8
  %238 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  store %struct.Relocation* %238, %struct.Relocation** %6, align 8
  br label %278

239:                                              ; preds = %223
  store i8** null, i8*** %21, align 8
  %240 = load %struct.Initializer*, %struct.Initializer** %8, align 8
  %241 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %240, i32 0, i32 4
  %242 = load %struct.Node*, %struct.Node** %241, align 8
  %243 = call i64 @eval2(%struct.Node* noundef %242, i8*** noundef %21)
  store i64 %243, i64* %22, align 8
  %244 = load i8**, i8*** %21, align 8
  %245 = icmp ne i8** %244, null
  br i1 %245, label %256, label %246

246:                                              ; preds = %239
  %247 = load i8*, i8** %10, align 8
  %248 = load i32, i32* %11, align 4
  %249 = sext i32 %248 to i64
  %250 = getelementptr inbounds i8, i8* %247, i64 %249
  %251 = load i64, i64* %22, align 8
  %252 = load %struct.Type*, %struct.Type** %9, align 8
  %253 = getelementptr inbounds %struct.Type, %struct.Type* %252, i32 0, i32 1
  %254 = load i32, i32* %253, align 4
  call void @write_buf(i8* noundef %250, i64 noundef %251, i32 noundef %254)
  %255 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  store %struct.Relocation* %255, %struct.Relocation** %6, align 8
  br label %278

256:                                              ; preds = %239
  %257 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 32) #8
  %258 = bitcast i8* %257 to %struct.Relocation*
  store %struct.Relocation* %258, %struct.Relocation** %23, align 8
  %259 = load %struct.Relocation*, %struct.Relocation** %23, align 8
  %260 = icmp eq %struct.Relocation* %259, null
  br i1 %260, label %261, label %262

261:                                              ; preds = %256
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([37 x i8], [37 x i8]* @.str.164, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

262:                                              ; preds = %256
  %263 = load i32, i32* %11, align 4
  %264 = load %struct.Relocation*, %struct.Relocation** %23, align 8
  %265 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %264, i32 0, i32 1
  store i32 %263, i32* %265, align 8
  %266 = load i8**, i8*** %21, align 8
  %267 = load %struct.Relocation*, %struct.Relocation** %23, align 8
  %268 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %267, i32 0, i32 2
  store i8** %266, i8*** %268, align 8
  %269 = load i64, i64* %22, align 8
  %270 = load %struct.Relocation*, %struct.Relocation** %23, align 8
  %271 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %270, i32 0, i32 3
  store i64 %269, i64* %271, align 8
  %272 = load %struct.Relocation*, %struct.Relocation** %23, align 8
  %273 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  %274 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %273, i32 0, i32 0
  store %struct.Relocation* %272, %struct.Relocation** %274, align 8
  %275 = load %struct.Relocation*, %struct.Relocation** %7, align 8
  %276 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %275, i32 0, i32 0
  %277 = load %struct.Relocation*, %struct.Relocation** %276, align 8
  store %struct.Relocation* %277, %struct.Relocation** %6, align 8
  br label %278

278:                                              ; preds = %262, %246, %228, %211, %204, %178, %176, %164, %62
  %279 = load %struct.Relocation*, %struct.Relocation** %6, align 8
  ret %struct.Relocation* %279
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Initializer* @new_initializer(%struct.Type* noundef %0, i1 noundef zeroext %1) #0 {
  %3 = alloca %struct.Initializer*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca i8, align 1
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca %struct.Member*, align 8
  %10 = alloca %struct.Member*, align 8
  %11 = alloca %struct.Initializer*, align 8
  store %struct.Type* %0, %struct.Type** %4, align 8
  %12 = zext i1 %1 to i8
  store i8 %12, i8* %5, align 1
  %13 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 56) #8
  %14 = bitcast i8* %13 to %struct.Initializer*
  store %struct.Initializer* %14, %struct.Initializer** %6, align 8
  %15 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %16 = icmp eq %struct.Initializer* %15, null
  br i1 %16, label %17, label %18

17:                                               ; preds = %2
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([38 x i8], [38 x i8]* @.str.139, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

18:                                               ; preds = %2
  %19 = load %struct.Type*, %struct.Type** %4, align 8
  %20 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %21 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %20, i32 0, i32 1
  store %struct.Type* %19, %struct.Type** %21, align 8
  %22 = load %struct.Type*, %struct.Type** %4, align 8
  %23 = getelementptr inbounds %struct.Type, %struct.Type* %22, i32 0, i32 0
  %24 = load i32, i32* %23, align 8
  %25 = icmp eq i32 %24, 12
  br i1 %25, label %26, label %75

26:                                               ; preds = %18
  %27 = load i8, i8* %5, align 1
  %28 = trunc i8 %27 to i1
  br i1 %28, label %29, label %38

29:                                               ; preds = %26
  %30 = load %struct.Type*, %struct.Type** %4, align 8
  %31 = getelementptr inbounds %struct.Type, %struct.Type* %30, i32 0, i32 1
  %32 = load i32, i32* %31, align 4
  %33 = icmp slt i32 %32, 0
  br i1 %33, label %34, label %38

34:                                               ; preds = %29
  %35 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %36 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %35, i32 0, i32 3
  store i8 1, i8* %36, align 8
  %37 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  store %struct.Initializer* %37, %struct.Initializer** %3, align 8
  br label %176

38:                                               ; preds = %29, %26
  %39 = load %struct.Type*, %struct.Type** %4, align 8
  %40 = getelementptr inbounds %struct.Type, %struct.Type* %39, i32 0, i32 11
  %41 = load i32, i32* %40, align 8
  %42 = sext i32 %41 to i64
  %43 = call noalias i8* @calloc(i64 noundef %42, i64 noundef 8) #8
  %44 = bitcast i8* %43 to %struct.Initializer**
  %45 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %46 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %45, i32 0, i32 5
  store %struct.Initializer** %44, %struct.Initializer*** %46, align 8
  %47 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %48 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %47, i32 0, i32 5
  %49 = load %struct.Initializer**, %struct.Initializer*** %48, align 8
  %50 = icmp eq %struct.Initializer** %49, null
  br i1 %50, label %51, label %52

51:                                               ; preds = %38
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([48 x i8], [48 x i8]* @.str.140, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

52:                                               ; preds = %38
  store i32 0, i32* %7, align 4
  br label %53

53:                                               ; preds = %70, %52
  %54 = load i32, i32* %7, align 4
  %55 = load %struct.Type*, %struct.Type** %4, align 8
  %56 = getelementptr inbounds %struct.Type, %struct.Type* %55, i32 0, i32 11
  %57 = load i32, i32* %56, align 8
  %58 = icmp slt i32 %54, %57
  br i1 %58, label %59, label %73

59:                                               ; preds = %53
  %60 = load %struct.Type*, %struct.Type** %4, align 8
  %61 = getelementptr inbounds %struct.Type, %struct.Type* %60, i32 0, i32 8
  %62 = load %struct.Type*, %struct.Type** %61, align 8
  %63 = call %struct.Initializer* @new_initializer(%struct.Type* noundef %62, i1 noundef zeroext false)
  %64 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %65 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %64, i32 0, i32 5
  %66 = load %struct.Initializer**, %struct.Initializer*** %65, align 8
  %67 = load i32, i32* %7, align 4
  %68 = sext i32 %67 to i64
  %69 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %66, i64 %68
  store %struct.Initializer* %63, %struct.Initializer** %69, align 8
  br label %70

70:                                               ; preds = %59
  %71 = load i32, i32* %7, align 4
  %72 = add nsw i32 %71, 1
  store i32 %72, i32* %7, align 4
  br label %53, !llvm.loop !36

73:                                               ; preds = %53
  %74 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  store %struct.Initializer* %74, %struct.Initializer** %3, align 8
  br label %176

75:                                               ; preds = %18
  %76 = load %struct.Type*, %struct.Type** %4, align 8
  %77 = getelementptr inbounds %struct.Type, %struct.Type* %76, i32 0, i32 0
  %78 = load i32, i32* %77, align 8
  %79 = icmp eq i32 %78, 14
  br i1 %79, label %85, label %80

80:                                               ; preds = %75
  %81 = load %struct.Type*, %struct.Type** %4, align 8
  %82 = getelementptr inbounds %struct.Type, %struct.Type* %81, i32 0, i32 0
  %83 = load i32, i32* %82, align 8
  %84 = icmp eq i32 %83, 15
  br i1 %84, label %85, label %174

85:                                               ; preds = %80, %75
  store i32 0, i32* %8, align 4
  %86 = load %struct.Type*, %struct.Type** %4, align 8
  %87 = getelementptr inbounds %struct.Type, %struct.Type* %86, i32 0, i32 14
  %88 = load %struct.Member*, %struct.Member** %87, align 8
  store %struct.Member* %88, %struct.Member** %9, align 8
  br label %89

89:                                               ; preds = %95, %85
  %90 = load %struct.Member*, %struct.Member** %9, align 8
  %91 = icmp ne %struct.Member* %90, null
  br i1 %91, label %92, label %99

92:                                               ; preds = %89
  %93 = load i32, i32* %8, align 4
  %94 = add nsw i32 %93, 1
  store i32 %94, i32* %8, align 4
  br label %95

95:                                               ; preds = %92
  %96 = load %struct.Member*, %struct.Member** %9, align 8
  %97 = getelementptr inbounds %struct.Member, %struct.Member* %96, i32 0, i32 0
  %98 = load %struct.Member*, %struct.Member** %97, align 8
  store %struct.Member* %98, %struct.Member** %9, align 8
  br label %89, !llvm.loop !37

99:                                               ; preds = %89
  %100 = load i32, i32* %8, align 4
  %101 = sext i32 %100 to i64
  %102 = call noalias i8* @calloc(i64 noundef %101, i64 noundef 8) #8
  %103 = bitcast i8* %102 to %struct.Initializer**
  %104 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %105 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %104, i32 0, i32 5
  store %struct.Initializer** %103, %struct.Initializer*** %105, align 8
  %106 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %107 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %106, i32 0, i32 5
  %108 = load %struct.Initializer**, %struct.Initializer*** %107, align 8
  %109 = icmp eq %struct.Initializer** %108, null
  br i1 %109, label %110, label %111

110:                                              ; preds = %99
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([54 x i8], [54 x i8]* @.str.141, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

111:                                              ; preds = %99
  %112 = load %struct.Type*, %struct.Type** %4, align 8
  %113 = getelementptr inbounds %struct.Type, %struct.Type* %112, i32 0, i32 14
  %114 = load %struct.Member*, %struct.Member** %113, align 8
  store %struct.Member* %114, %struct.Member** %10, align 8
  br label %115

115:                                              ; preds = %168, %111
  %116 = load %struct.Member*, %struct.Member** %10, align 8
  %117 = icmp ne %struct.Member* %116, null
  br i1 %117, label %118, label %172

118:                                              ; preds = %115
  %119 = load i8, i8* %5, align 1
  %120 = trunc i8 %119 to i1
  br i1 %120, label %121, label %154

121:                                              ; preds = %118
  %122 = load %struct.Type*, %struct.Type** %4, align 8
  %123 = getelementptr inbounds %struct.Type, %struct.Type* %122, i32 0, i32 15
  %124 = load i8, i8* %123, align 8
  %125 = trunc i8 %124 to i1
  br i1 %125, label %126, label %154

126:                                              ; preds = %121
  %127 = load %struct.Member*, %struct.Member** %10, align 8
  %128 = getelementptr inbounds %struct.Member, %struct.Member* %127, i32 0, i32 0
  %129 = load %struct.Member*, %struct.Member** %128, align 8
  %130 = icmp ne %struct.Member* %129, null
  br i1 %130, label %154, label %131

131:                                              ; preds = %126
  %132 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 56) #8
  %133 = bitcast i8* %132 to %struct.Initializer*
  store %struct.Initializer* %133, %struct.Initializer** %11, align 8
  %134 = load %struct.Initializer*, %struct.Initializer** %11, align 8
  %135 = icmp eq %struct.Initializer* %134, null
  br i1 %135, label %136, label %137

136:                                              ; preds = %131
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([39 x i8], [39 x i8]* @.str.142, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

137:                                              ; preds = %131
  %138 = load %struct.Member*, %struct.Member** %10, align 8
  %139 = getelementptr inbounds %struct.Member, %struct.Member* %138, i32 0, i32 1
  %140 = load %struct.Type*, %struct.Type** %139, align 8
  %141 = load %struct.Initializer*, %struct.Initializer** %11, align 8
  %142 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %141, i32 0, i32 1
  store %struct.Type* %140, %struct.Type** %142, align 8
  %143 = load %struct.Initializer*, %struct.Initializer** %11, align 8
  %144 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %143, i32 0, i32 3
  store i8 1, i8* %144, align 8
  %145 = load %struct.Initializer*, %struct.Initializer** %11, align 8
  %146 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %147 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %146, i32 0, i32 5
  %148 = load %struct.Initializer**, %struct.Initializer*** %147, align 8
  %149 = load %struct.Member*, %struct.Member** %10, align 8
  %150 = getelementptr inbounds %struct.Member, %struct.Member* %149, i32 0, i32 4
  %151 = load i32, i32* %150, align 8
  %152 = sext i32 %151 to i64
  %153 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %148, i64 %152
  store %struct.Initializer* %145, %struct.Initializer** %153, align 8
  br label %167

154:                                              ; preds = %126, %121, %118
  %155 = load %struct.Member*, %struct.Member** %10, align 8
  %156 = getelementptr inbounds %struct.Member, %struct.Member* %155, i32 0, i32 1
  %157 = load %struct.Type*, %struct.Type** %156, align 8
  %158 = call %struct.Initializer* @new_initializer(%struct.Type* noundef %157, i1 noundef zeroext false)
  %159 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %160 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %159, i32 0, i32 5
  %161 = load %struct.Initializer**, %struct.Initializer*** %160, align 8
  %162 = load %struct.Member*, %struct.Member** %10, align 8
  %163 = getelementptr inbounds %struct.Member, %struct.Member* %162, i32 0, i32 4
  %164 = load i32, i32* %163, align 8
  %165 = sext i32 %164 to i64
  %166 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %161, i64 %165
  store %struct.Initializer* %158, %struct.Initializer** %166, align 8
  br label %167

167:                                              ; preds = %154, %137
  br label %168

168:                                              ; preds = %167
  %169 = load %struct.Member*, %struct.Member** %10, align 8
  %170 = getelementptr inbounds %struct.Member, %struct.Member* %169, i32 0, i32 0
  %171 = load %struct.Member*, %struct.Member** %170, align 8
  store %struct.Member* %171, %struct.Member** %10, align 8
  br label %115, !llvm.loop !38

172:                                              ; preds = %115
  %173 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  store %struct.Initializer* %173, %struct.Initializer** %3, align 8
  br label %176

174:                                              ; preds = %80
  %175 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  store %struct.Initializer* %175, %struct.Initializer** %3, align 8
  br label %176

176:                                              ; preds = %174, %172, %73, %34
  %177 = load %struct.Initializer*, %struct.Initializer** %3, align 8
  ret %struct.Initializer* %177
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @initializer2(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Initializer* %2, %struct.Initializer** %6, align 8
  %8 = load %struct.Token*, %struct.Token** %5, align 8
  %9 = call zeroext i1 @equal(%struct.Token* noundef %8, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %9, label %10, label %11

10:                                               ; preds = %3
  br label %174

11:                                               ; preds = %3
  %12 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %13 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %12, i32 0, i32 1
  %14 = load %struct.Type*, %struct.Type** %13, align 8
  %15 = getelementptr inbounds %struct.Type, %struct.Type* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 8
  %17 = icmp eq i32 %16, 12
  br i1 %17, label %18, label %27

18:                                               ; preds = %11
  %19 = load %struct.Token*, %struct.Token** %5, align 8
  %20 = getelementptr inbounds %struct.Token, %struct.Token* %19, i32 0, i32 0
  %21 = load i32, i32* %20, align 16
  %22 = icmp eq i32 %21, 3
  br i1 %22, label %23, label %27

23:                                               ; preds = %18
  %24 = load %struct.Token**, %struct.Token*** %4, align 8
  %25 = load %struct.Token*, %struct.Token** %5, align 8
  %26 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @string_initializer(%struct.Token** noundef %24, %struct.Token* noundef %25, %struct.Initializer* noundef %26)
  br label %174

27:                                               ; preds = %18, %11
  %28 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %29 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %28, i32 0, i32 1
  %30 = load %struct.Type*, %struct.Type** %29, align 8
  %31 = getelementptr inbounds %struct.Type, %struct.Type* %30, i32 0, i32 0
  %32 = load i32, i32* %31, align 8
  %33 = icmp eq i32 %32, 12
  br i1 %33, label %34, label %66

34:                                               ; preds = %27
  %35 = load %struct.Token*, %struct.Token** %5, align 8
  %36 = call zeroext i1 @equal(%struct.Token* noundef %35, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %36, label %37, label %66

37:                                               ; preds = %34
  %38 = load %struct.Token*, %struct.Token** %5, align 8
  %39 = call zeroext i1 @equal(%struct.Token* noundef %38, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  br i1 %39, label %40, label %65

40:                                               ; preds = %37
  %41 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %42 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %41, i32 0, i32 1
  %43 = load %struct.Type*, %struct.Type** %42, align 8
  %44 = getelementptr inbounds %struct.Type, %struct.Type* %43, i32 0, i32 8
  %45 = load %struct.Type*, %struct.Type** %44, align 8
  %46 = getelementptr inbounds %struct.Type, %struct.Type* %45, i32 0, i32 0
  %47 = load i32, i32* %46, align 8
  %48 = icmp eq i32 %47, 2
  br i1 %48, label %49, label %64

49:                                               ; preds = %40
  %50 = load %struct.Token*, %struct.Token** %5, align 8
  %51 = getelementptr inbounds %struct.Token, %struct.Token* %50, i32 0, i32 1
  %52 = load %struct.Token*, %struct.Token** %51, align 8
  %53 = getelementptr inbounds %struct.Token, %struct.Token* %52, i32 0, i32 0
  %54 = load i32, i32* %53, align 16
  %55 = icmp eq i32 %54, 3
  br i1 %55, label %56, label %64

56:                                               ; preds = %49
  %57 = load %struct.Token*, %struct.Token** %5, align 8
  %58 = call %struct.Token* @skip(%struct.Token* noundef %57, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %58, %struct.Token** %5, align 8
  %59 = load %struct.Token*, %struct.Token** %5, align 8
  %60 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @initializer2(%struct.Token** noundef %5, %struct.Token* noundef %59, %struct.Initializer* noundef %60)
  %61 = load %struct.Token*, %struct.Token** %5, align 8
  %62 = call %struct.Token* @skip(%struct.Token* noundef %61, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %63 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %62, %struct.Token** %63, align 8
  br label %174

64:                                               ; preds = %49, %40
  br label %174

65:                                               ; preds = %37
  br label %66

66:                                               ; preds = %65, %34, %27
  %67 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %68 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %67, i32 0, i32 1
  %69 = load %struct.Type*, %struct.Type** %68, align 8
  %70 = getelementptr inbounds %struct.Type, %struct.Type* %69, i32 0, i32 0
  %71 = load i32, i32* %70, align 8
  %72 = icmp eq i32 %71, 12
  br i1 %72, label %73, label %108

73:                                               ; preds = %66
  %74 = load %struct.Token*, %struct.Token** %5, align 8
  %75 = call zeroext i1 @equal(%struct.Token* noundef %74, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %75, label %76, label %104

76:                                               ; preds = %73
  %77 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %78 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %77, i32 0, i32 1
  %79 = load %struct.Type*, %struct.Type** %78, align 8
  %80 = getelementptr inbounds %struct.Type, %struct.Type* %79, i32 0, i32 8
  %81 = load %struct.Type*, %struct.Type** %80, align 8
  %82 = getelementptr inbounds %struct.Type, %struct.Type* %81, i32 0, i32 0
  %83 = load i32, i32* %82, align 8
  %84 = icmp eq i32 %83, 2
  br i1 %84, label %85, label %100

85:                                               ; preds = %76
  %86 = load %struct.Token*, %struct.Token** %5, align 8
  %87 = getelementptr inbounds %struct.Token, %struct.Token* %86, i32 0, i32 1
  %88 = load %struct.Token*, %struct.Token** %87, align 8
  %89 = getelementptr inbounds %struct.Token, %struct.Token* %88, i32 0, i32 0
  %90 = load i32, i32* %89, align 16
  %91 = icmp eq i32 %90, 3
  br i1 %91, label %92, label %100

92:                                               ; preds = %85
  %93 = load %struct.Token*, %struct.Token** %5, align 8
  %94 = call %struct.Token* @skip(%struct.Token* noundef %93, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  store %struct.Token* %94, %struct.Token** %5, align 8
  %95 = load %struct.Token*, %struct.Token** %5, align 8
  %96 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @initializer2(%struct.Token** noundef %5, %struct.Token* noundef %95, %struct.Initializer* noundef %96)
  %97 = load %struct.Token*, %struct.Token** %5, align 8
  %98 = call %struct.Token* @skip(%struct.Token* noundef %97, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  %99 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %98, %struct.Token** %99, align 8
  br label %174

100:                                              ; preds = %85, %76
  %101 = load %struct.Token**, %struct.Token*** %4, align 8
  %102 = load %struct.Token*, %struct.Token** %5, align 8
  %103 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @array_initializer1(%struct.Token** noundef %101, %struct.Token* noundef %102, %struct.Initializer* noundef %103)
  br label %174

104:                                              ; preds = %73
  %105 = load %struct.Token**, %struct.Token*** %4, align 8
  %106 = load %struct.Token*, %struct.Token** %5, align 8
  %107 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @array_initializer2(%struct.Token** noundef %105, %struct.Token* noundef %106, %struct.Initializer* noundef %107, i32 noundef 0)
  br label %174

108:                                              ; preds = %66
  %109 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %110 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %109, i32 0, i32 1
  %111 = load %struct.Type*, %struct.Type** %110, align 8
  %112 = getelementptr inbounds %struct.Type, %struct.Type* %111, i32 0, i32 0
  %113 = load i32, i32* %112, align 8
  %114 = icmp eq i32 %113, 14
  br i1 %114, label %115, label %146

115:                                              ; preds = %108
  %116 = load %struct.Token*, %struct.Token** %5, align 8
  %117 = call zeroext i1 @equal(%struct.Token* noundef %116, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %117, label %118, label %122

118:                                              ; preds = %115
  %119 = load %struct.Token**, %struct.Token*** %4, align 8
  %120 = load %struct.Token*, %struct.Token** %5, align 8
  %121 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @struct_initializer1(%struct.Token** noundef %119, %struct.Token* noundef %120, %struct.Initializer* noundef %121)
  br label %174

122:                                              ; preds = %115
  %123 = load %struct.Token**, %struct.Token*** %4, align 8
  %124 = load %struct.Token*, %struct.Token** %5, align 8
  %125 = call %struct.Node* @assign(%struct.Token** noundef %123, %struct.Token* noundef %124)
  store %struct.Node* %125, %struct.Node** %7, align 8
  %126 = load %struct.Node*, %struct.Node** %7, align 8
  call void @add_type(%struct.Node* noundef %126)
  %127 = load %struct.Node*, %struct.Node** %7, align 8
  %128 = getelementptr inbounds %struct.Node, %struct.Node* %127, i32 0, i32 2
  %129 = load %struct.Type*, %struct.Type** %128, align 16
  %130 = getelementptr inbounds %struct.Type, %struct.Type* %129, i32 0, i32 0
  %131 = load i32, i32* %130, align 8
  %132 = icmp eq i32 %131, 14
  br i1 %132, label %133, label %137

133:                                              ; preds = %122
  %134 = load %struct.Node*, %struct.Node** %7, align 8
  %135 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %136 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %135, i32 0, i32 4
  store %struct.Node* %134, %struct.Node** %136, align 8
  br label %174

137:                                              ; preds = %122
  %138 = load %struct.Token**, %struct.Token*** %4, align 8
  %139 = load %struct.Token*, %struct.Token** %5, align 8
  %140 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %141 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %142 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %141, i32 0, i32 1
  %143 = load %struct.Type*, %struct.Type** %142, align 8
  %144 = getelementptr inbounds %struct.Type, %struct.Type* %143, i32 0, i32 14
  %145 = load %struct.Member*, %struct.Member** %144, align 8
  call void @struct_initializer2(%struct.Token** noundef %138, %struct.Token* noundef %139, %struct.Initializer* noundef %140, %struct.Member* noundef %145)
  br label %174

146:                                              ; preds = %108
  %147 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %148 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %147, i32 0, i32 1
  %149 = load %struct.Type*, %struct.Type** %148, align 8
  %150 = getelementptr inbounds %struct.Type, %struct.Type* %149, i32 0, i32 0
  %151 = load i32, i32* %150, align 8
  %152 = icmp eq i32 %151, 15
  br i1 %152, label %153, label %157

153:                                              ; preds = %146
  %154 = load %struct.Token**, %struct.Token*** %4, align 8
  %155 = load %struct.Token*, %struct.Token** %5, align 8
  %156 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @union_initializer(%struct.Token** noundef %154, %struct.Token* noundef %155, %struct.Initializer* noundef %156)
  br label %174

157:                                              ; preds = %146
  %158 = load %struct.Token*, %struct.Token** %5, align 8
  %159 = call zeroext i1 @equal(%struct.Token* noundef %158, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %159, label %160, label %168

160:                                              ; preds = %157
  %161 = load %struct.Token*, %struct.Token** %5, align 8
  %162 = getelementptr inbounds %struct.Token, %struct.Token* %161, i32 0, i32 1
  %163 = load %struct.Token*, %struct.Token** %162, align 8
  %164 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @initializer2(%struct.Token** noundef %5, %struct.Token* noundef %163, %struct.Initializer* noundef %164)
  %165 = load %struct.Token*, %struct.Token** %5, align 8
  %166 = call %struct.Token* @skip(%struct.Token* noundef %165, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  %167 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %166, %struct.Token** %167, align 8
  br label %174

168:                                              ; preds = %157
  %169 = load %struct.Token**, %struct.Token*** %4, align 8
  %170 = load %struct.Token*, %struct.Token** %5, align 8
  %171 = call %struct.Node* @assign(%struct.Token** noundef %169, %struct.Token* noundef %170)
  %172 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %173 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %172, i32 0, i32 4
  store %struct.Node* %171, %struct.Node** %173, align 8
  br label %174

174:                                              ; preds = %168, %160, %153, %137, %133, %118, %104, %100, %92, %64, %56, %23, %10
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @copy_struct_type(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca %struct.Member, align 8
  %4 = alloca %struct.Member*, align 8
  %5 = alloca %struct.Member*, align 8
  %6 = alloca %struct.Member*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %7 = load %struct.Type*, %struct.Type** %2, align 8
  %8 = call %struct.Type* @copy_type(%struct.Type* noundef %7)
  store %struct.Type* %8, %struct.Type** %2, align 8
  %9 = bitcast %struct.Member* %3 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %9, i8 0, i64 56, i1 false)
  store %struct.Member* %3, %struct.Member** %4, align 8
  %10 = load %struct.Type*, %struct.Type** %2, align 8
  %11 = getelementptr inbounds %struct.Type, %struct.Type* %10, i32 0, i32 14
  %12 = load %struct.Member*, %struct.Member** %11, align 8
  store %struct.Member* %12, %struct.Member** %5, align 8
  br label %13

13:                                               ; preds = %30, %1
  %14 = load %struct.Member*, %struct.Member** %5, align 8
  %15 = icmp ne %struct.Member* %14, null
  br i1 %15, label %16, label %34

16:                                               ; preds = %13
  %17 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 56) #8
  %18 = bitcast i8* %17 to %struct.Member*
  store %struct.Member* %18, %struct.Member** %6, align 8
  %19 = load %struct.Member*, %struct.Member** %6, align 8
  %20 = icmp eq %struct.Member* %19, null
  br i1 %20, label %21, label %22

21:                                               ; preds = %16
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([37 x i8], [37 x i8]* @.str.163, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

22:                                               ; preds = %16
  %23 = load %struct.Member*, %struct.Member** %6, align 8
  %24 = load %struct.Member*, %struct.Member** %5, align 8
  %25 = bitcast %struct.Member* %23 to i8*
  %26 = bitcast %struct.Member* %24 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %25, i8* align 8 %26, i64 56, i1 false)
  %27 = load %struct.Member*, %struct.Member** %6, align 8
  %28 = load %struct.Member*, %struct.Member** %4, align 8
  %29 = getelementptr inbounds %struct.Member, %struct.Member* %28, i32 0, i32 0
  store %struct.Member* %27, %struct.Member** %29, align 8
  store %struct.Member* %27, %struct.Member** %4, align 8
  br label %30

30:                                               ; preds = %22
  %31 = load %struct.Member*, %struct.Member** %5, align 8
  %32 = getelementptr inbounds %struct.Member, %struct.Member* %31, i32 0, i32 0
  %33 = load %struct.Member*, %struct.Member** %32, align 8
  store %struct.Member* %33, %struct.Member** %5, align 8
  br label %13, !llvm.loop !39

34:                                               ; preds = %13
  %35 = getelementptr inbounds %struct.Member, %struct.Member* %3, i32 0, i32 0
  %36 = load %struct.Member*, %struct.Member** %35, align 8
  %37 = load %struct.Type*, %struct.Type** %2, align 8
  %38 = getelementptr inbounds %struct.Type, %struct.Type* %37, i32 0, i32 14
  store %struct.Member* %36, %struct.Member** %38, align 8
  %39 = load %struct.Type*, %struct.Type** %2, align 8
  ret %struct.Type* %39
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @string_initializer(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  %10 = alloca i16*, align 8
  %11 = alloca i32, align 4
  %12 = alloca i32*, align 8
  %13 = alloca i32, align 4
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Initializer* %2, %struct.Initializer** %6, align 8
  %14 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %15 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %14, i32 0, i32 3
  %16 = load i8, i8* %15, align 8
  %17 = trunc i8 %16 to i1
  br i1 %17, label %18, label %34

18:                                               ; preds = %3
  %19 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %20 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %21 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %20, i32 0, i32 1
  %22 = load %struct.Type*, %struct.Type** %21, align 8
  %23 = getelementptr inbounds %struct.Type, %struct.Type* %22, i32 0, i32 8
  %24 = load %struct.Type*, %struct.Type** %23, align 8
  %25 = load %struct.Token*, %struct.Token** %5, align 8
  %26 = getelementptr inbounds %struct.Token, %struct.Token* %25, i32 0, i32 6
  %27 = load %struct.Type*, %struct.Type** %26, align 16
  %28 = getelementptr inbounds %struct.Type, %struct.Type* %27, i32 0, i32 11
  %29 = load i32, i32* %28, align 8
  %30 = call %struct.Type* @array_of(%struct.Type* noundef %24, i32 noundef %29)
  %31 = call %struct.Initializer* @new_initializer(%struct.Type* noundef %30, i1 noundef zeroext false)
  %32 = bitcast %struct.Initializer* %19 to i8*
  %33 = bitcast %struct.Initializer* %31 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %32, i8* align 8 %33, i64 56, i1 false)
  br label %34

34:                                               ; preds = %18, %3
  %35 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %36 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %35, i32 0, i32 1
  %37 = load %struct.Type*, %struct.Type** %36, align 8
  %38 = getelementptr inbounds %struct.Type, %struct.Type* %37, i32 0, i32 11
  %39 = load i32, i32* %38, align 8
  %40 = load %struct.Token*, %struct.Token** %5, align 8
  %41 = getelementptr inbounds %struct.Token, %struct.Token* %40, i32 0, i32 6
  %42 = load %struct.Type*, %struct.Type** %41, align 16
  %43 = getelementptr inbounds %struct.Type, %struct.Type* %42, i32 0, i32 11
  %44 = load i32, i32* %43, align 8
  %45 = icmp slt i32 %39, %44
  br i1 %45, label %46, label %52

46:                                               ; preds = %34
  %47 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %48 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %47, i32 0, i32 1
  %49 = load %struct.Type*, %struct.Type** %48, align 8
  %50 = getelementptr inbounds %struct.Type, %struct.Type* %49, i32 0, i32 11
  %51 = load i32, i32* %50, align 8
  br label %58

52:                                               ; preds = %34
  %53 = load %struct.Token*, %struct.Token** %5, align 8
  %54 = getelementptr inbounds %struct.Token, %struct.Token* %53, i32 0, i32 6
  %55 = load %struct.Type*, %struct.Type** %54, align 16
  %56 = getelementptr inbounds %struct.Type, %struct.Type* %55, i32 0, i32 11
  %57 = load i32, i32* %56, align 8
  br label %58

58:                                               ; preds = %52, %46
  %59 = phi i32 [ %51, %46 ], [ %57, %52 ]
  store i32 %59, i32* %7, align 4
  %60 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %61 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %60, i32 0, i32 1
  %62 = load %struct.Type*, %struct.Type** %61, align 8
  %63 = getelementptr inbounds %struct.Type, %struct.Type* %62, i32 0, i32 8
  %64 = load %struct.Type*, %struct.Type** %63, align 8
  %65 = getelementptr inbounds %struct.Type, %struct.Type* %64, i32 0, i32 1
  %66 = load i32, i32* %65, align 4
  switch i32 %66, label %156 [
    i32 1, label %67
    i32 2, label %96
    i32 4, label %126
  ]

67:                                               ; preds = %58
  %68 = load %struct.Token*, %struct.Token** %5, align 8
  %69 = getelementptr inbounds %struct.Token, %struct.Token* %68, i32 0, i32 7
  %70 = load i8*, i8** %69, align 8
  store i8* %70, i8** %8, align 8
  store i32 0, i32* %9, align 4
  br label %71

71:                                               ; preds = %92, %67
  %72 = load i32, i32* %9, align 4
  %73 = load i32, i32* %7, align 4
  %74 = icmp slt i32 %72, %73
  br i1 %74, label %75, label %95

75:                                               ; preds = %71
  %76 = load i8*, i8** %8, align 8
  %77 = load i32, i32* %9, align 4
  %78 = sext i32 %77 to i64
  %79 = getelementptr inbounds i8, i8* %76, i64 %78
  %80 = load i8, i8* %79, align 1
  %81 = sext i8 %80 to i64
  %82 = load %struct.Token*, %struct.Token** %5, align 8
  %83 = call %struct.Node* @new_num(i64 noundef %81, %struct.Token* noundef %82)
  %84 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %85 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %84, i32 0, i32 5
  %86 = load %struct.Initializer**, %struct.Initializer*** %85, align 8
  %87 = load i32, i32* %9, align 4
  %88 = sext i32 %87 to i64
  %89 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %86, i64 %88
  %90 = load %struct.Initializer*, %struct.Initializer** %89, align 8
  %91 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %90, i32 0, i32 4
  store %struct.Node* %83, %struct.Node** %91, align 8
  br label %92

92:                                               ; preds = %75
  %93 = load i32, i32* %9, align 4
  %94 = add nsw i32 %93, 1
  store i32 %94, i32* %9, align 4
  br label %71, !llvm.loop !40

95:                                               ; preds = %71
  br label %158

96:                                               ; preds = %58
  %97 = load %struct.Token*, %struct.Token** %5, align 8
  %98 = getelementptr inbounds %struct.Token, %struct.Token* %97, i32 0, i32 7
  %99 = load i8*, i8** %98, align 8
  %100 = bitcast i8* %99 to i16*
  store i16* %100, i16** %10, align 8
  store i32 0, i32* %11, align 4
  br label %101

101:                                              ; preds = %122, %96
  %102 = load i32, i32* %11, align 4
  %103 = load i32, i32* %7, align 4
  %104 = icmp slt i32 %102, %103
  br i1 %104, label %105, label %125

105:                                              ; preds = %101
  %106 = load i16*, i16** %10, align 8
  %107 = load i32, i32* %11, align 4
  %108 = sext i32 %107 to i64
  %109 = getelementptr inbounds i16, i16* %106, i64 %108
  %110 = load i16, i16* %109, align 2
  %111 = zext i16 %110 to i64
  %112 = load %struct.Token*, %struct.Token** %5, align 8
  %113 = call %struct.Node* @new_num(i64 noundef %111, %struct.Token* noundef %112)
  %114 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %115 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %114, i32 0, i32 5
  %116 = load %struct.Initializer**, %struct.Initializer*** %115, align 8
  %117 = load i32, i32* %11, align 4
  %118 = sext i32 %117 to i64
  %119 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %116, i64 %118
  %120 = load %struct.Initializer*, %struct.Initializer** %119, align 8
  %121 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %120, i32 0, i32 4
  store %struct.Node* %113, %struct.Node** %121, align 8
  br label %122

122:                                              ; preds = %105
  %123 = load i32, i32* %11, align 4
  %124 = add nsw i32 %123, 1
  store i32 %124, i32* %11, align 4
  br label %101, !llvm.loop !41

125:                                              ; preds = %101
  br label %158

126:                                              ; preds = %58
  %127 = load %struct.Token*, %struct.Token** %5, align 8
  %128 = getelementptr inbounds %struct.Token, %struct.Token* %127, i32 0, i32 7
  %129 = load i8*, i8** %128, align 8
  %130 = bitcast i8* %129 to i32*
  store i32* %130, i32** %12, align 8
  store i32 0, i32* %13, align 4
  br label %131

131:                                              ; preds = %152, %126
  %132 = load i32, i32* %13, align 4
  %133 = load i32, i32* %7, align 4
  %134 = icmp slt i32 %132, %133
  br i1 %134, label %135, label %155

135:                                              ; preds = %131
  %136 = load i32*, i32** %12, align 8
  %137 = load i32, i32* %13, align 4
  %138 = sext i32 %137 to i64
  %139 = getelementptr inbounds i32, i32* %136, i64 %138
  %140 = load i32, i32* %139, align 4
  %141 = zext i32 %140 to i64
  %142 = load %struct.Token*, %struct.Token** %5, align 8
  %143 = call %struct.Node* @new_num(i64 noundef %141, %struct.Token* noundef %142)
  %144 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %145 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %144, i32 0, i32 5
  %146 = load %struct.Initializer**, %struct.Initializer*** %145, align 8
  %147 = load i32, i32* %13, align 4
  %148 = sext i32 %147 to i64
  %149 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %146, i64 %148
  %150 = load %struct.Initializer*, %struct.Initializer** %149, align 8
  %151 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %150, i32 0, i32 4
  store %struct.Node* %143, %struct.Node** %151, align 8
  br label %152

152:                                              ; preds = %135
  %153 = load i32, i32* %13, align 4
  %154 = add nsw i32 %153, 1
  store i32 %154, i32* %13, align 4
  br label %131, !llvm.loop !42

155:                                              ; preds = %131
  br label %158

156:                                              ; preds = %58
  %157 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %157, i8* noundef getelementptr inbounds ([89 x i8], [89 x i8]* @.str.144, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

158:                                              ; preds = %155, %125, %95
  %159 = load %struct.Token*, %struct.Token** %5, align 8
  %160 = getelementptr inbounds %struct.Token, %struct.Token* %159, i32 0, i32 1
  %161 = load %struct.Token*, %struct.Token** %160, align 8
  %162 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %161, %struct.Token** %162, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @array_initializer1(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8, align 1
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca %struct.Token*, align 8
  %14 = alloca i32, align 4
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Initializer* %2, %struct.Initializer** %6, align 8
  %15 = load %struct.Token*, %struct.Token** %5, align 8
  %16 = call %struct.Token* @skip(%struct.Token* noundef %15, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  store %struct.Token* %16, %struct.Token** %5, align 8
  %17 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %18 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %17, i32 0, i32 3
  %19 = load i8, i8* %18, align 8
  %20 = trunc i8 %19 to i1
  br i1 %20, label %21, label %38

21:                                               ; preds = %3
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %24 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %23, i32 0, i32 1
  %25 = load %struct.Type*, %struct.Type** %24, align 8
  %26 = call i32 @count_array_init_elements(%struct.Token* noundef %22, %struct.Type* noundef %25)
  store i32 %26, i32* %7, align 4
  %27 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %28 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %29 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %28, i32 0, i32 1
  %30 = load %struct.Type*, %struct.Type** %29, align 8
  %31 = getelementptr inbounds %struct.Type, %struct.Type* %30, i32 0, i32 8
  %32 = load %struct.Type*, %struct.Type** %31, align 8
  %33 = load i32, i32* %7, align 4
  %34 = call %struct.Type* @array_of(%struct.Type* noundef %32, i32 noundef %33)
  %35 = call %struct.Initializer* @new_initializer(%struct.Type* noundef %34, i1 noundef zeroext false)
  %36 = bitcast %struct.Initializer* %27 to i8*
  %37 = bitcast %struct.Initializer* %35 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %36, i8* align 8 %37, i64 56, i1 false)
  br label %38

38:                                               ; preds = %21, %3
  store i8 1, i8* %8, align 1
  %39 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %40 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %39, i32 0, i32 3
  %41 = load i8, i8* %40, align 8
  %42 = trunc i8 %41 to i1
  br i1 %42, label %43, label %60

43:                                               ; preds = %38
  %44 = load %struct.Token*, %struct.Token** %5, align 8
  %45 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %46 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %45, i32 0, i32 1
  %47 = load %struct.Type*, %struct.Type** %46, align 8
  %48 = call i32 @count_array_init_elements(%struct.Token* noundef %44, %struct.Type* noundef %47)
  store i32 %48, i32* %9, align 4
  %49 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %50 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %51 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %50, i32 0, i32 1
  %52 = load %struct.Type*, %struct.Type** %51, align 8
  %53 = getelementptr inbounds %struct.Type, %struct.Type* %52, i32 0, i32 8
  %54 = load %struct.Type*, %struct.Type** %53, align 8
  %55 = load i32, i32* %9, align 4
  %56 = call %struct.Type* @array_of(%struct.Type* noundef %54, i32 noundef %55)
  %57 = call %struct.Initializer* @new_initializer(%struct.Type* noundef %56, i1 noundef zeroext false)
  %58 = bitcast %struct.Initializer* %49 to i8*
  %59 = bitcast %struct.Initializer* %57 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %58, i8* align 8 %59, i64 56, i1 false)
  br label %60

60:                                               ; preds = %43, %38
  store i32 0, i32* %10, align 4
  br label %61

61:                                               ; preds = %121, %60
  %62 = load %struct.Token**, %struct.Token*** %4, align 8
  %63 = load %struct.Token*, %struct.Token** %5, align 8
  %64 = call zeroext i1 @consume_end(%struct.Token** noundef %62, %struct.Token* noundef %63)
  %65 = xor i1 %64, true
  br i1 %65, label %66, label %124

66:                                               ; preds = %61
  %67 = load i8, i8* %8, align 1
  %68 = trunc i8 %67 to i1
  br i1 %68, label %72, label %69

69:                                               ; preds = %66
  %70 = load %struct.Token*, %struct.Token** %5, align 8
  %71 = call %struct.Token* @skip(%struct.Token* noundef %70, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %71, %struct.Token** %5, align 8
  br label %72

72:                                               ; preds = %69, %66
  store i8 0, i8* %8, align 1
  %73 = load %struct.Token*, %struct.Token** %5, align 8
  %74 = call zeroext i1 @equal(%struct.Token* noundef %73, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.119, i64 0, i64 0))
  br i1 %74, label %75, label %100

75:                                               ; preds = %72
  %76 = load %struct.Token*, %struct.Token** %5, align 8
  %77 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %78 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %77, i32 0, i32 1
  %79 = load %struct.Type*, %struct.Type** %78, align 8
  call void @array_designator(%struct.Token** noundef %5, %struct.Token* noundef %76, %struct.Type* noundef %79, i32* noundef %11, i32* noundef %12)
  %80 = load i32, i32* %11, align 4
  store i32 %80, i32* %14, align 4
  br label %81

81:                                               ; preds = %94, %75
  %82 = load i32, i32* %14, align 4
  %83 = load i32, i32* %12, align 4
  %84 = icmp sle i32 %82, %83
  br i1 %84, label %85, label %97

85:                                               ; preds = %81
  %86 = load %struct.Token*, %struct.Token** %5, align 8
  %87 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %88 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %87, i32 0, i32 5
  %89 = load %struct.Initializer**, %struct.Initializer*** %88, align 8
  %90 = load i32, i32* %14, align 4
  %91 = sext i32 %90 to i64
  %92 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %89, i64 %91
  %93 = load %struct.Initializer*, %struct.Initializer** %92, align 8
  call void @designation(%struct.Token** noundef %13, %struct.Token* noundef %86, %struct.Initializer* noundef %93)
  br label %94

94:                                               ; preds = %85
  %95 = load i32, i32* %14, align 4
  %96 = add nsw i32 %95, 1
  store i32 %96, i32* %14, align 4
  br label %81, !llvm.loop !43

97:                                               ; preds = %81
  %98 = load %struct.Token*, %struct.Token** %13, align 8
  store %struct.Token* %98, %struct.Token** %5, align 8
  %99 = load i32, i32* %12, align 4
  store i32 %99, i32* %10, align 4
  br label %121

100:                                              ; preds = %72
  %101 = load i32, i32* %10, align 4
  %102 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %103 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %102, i32 0, i32 1
  %104 = load %struct.Type*, %struct.Type** %103, align 8
  %105 = getelementptr inbounds %struct.Type, %struct.Type* %104, i32 0, i32 11
  %106 = load i32, i32* %105, align 8
  %107 = icmp slt i32 %101, %106
  br i1 %107, label %108, label %117

108:                                              ; preds = %100
  %109 = load %struct.Token*, %struct.Token** %5, align 8
  %110 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %111 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %110, i32 0, i32 5
  %112 = load %struct.Initializer**, %struct.Initializer*** %111, align 8
  %113 = load i32, i32* %10, align 4
  %114 = sext i32 %113 to i64
  %115 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %112, i64 %114
  %116 = load %struct.Initializer*, %struct.Initializer** %115, align 8
  call void @initializer2(%struct.Token** noundef %5, %struct.Token* noundef %109, %struct.Initializer* noundef %116)
  br label %120

117:                                              ; preds = %100
  %118 = load %struct.Token*, %struct.Token** %5, align 8
  %119 = call %struct.Token* @skip_excess_element(%struct.Token* noundef %118)
  store %struct.Token* %119, %struct.Token** %5, align 8
  br label %120

120:                                              ; preds = %117, %108
  br label %121

121:                                              ; preds = %120, %97
  %122 = load i32, i32* %10, align 4
  %123 = add nsw i32 %122, 1
  store i32 %123, i32* %10, align 4
  br label %61, !llvm.loop !44

124:                                              ; preds = %61
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @array_initializer2(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2, i32 noundef %3) #0 {
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Initializer*, align 8
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Initializer* %2, %struct.Initializer** %7, align 8
  store i32 %3, i32* %8, align 4
  %11 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %12 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %11, i32 0, i32 3
  %13 = load i8, i8* %12, align 8
  %14 = trunc i8 %13 to i1
  br i1 %14, label %15, label %32

15:                                               ; preds = %4
  %16 = load %struct.Token*, %struct.Token** %6, align 8
  %17 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %18 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %17, i32 0, i32 1
  %19 = load %struct.Type*, %struct.Type** %18, align 8
  %20 = call i32 @count_array_init_elements(%struct.Token* noundef %16, %struct.Type* noundef %19)
  store i32 %20, i32* %9, align 4
  %21 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %22 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %23 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %22, i32 0, i32 1
  %24 = load %struct.Type*, %struct.Type** %23, align 8
  %25 = getelementptr inbounds %struct.Type, %struct.Type* %24, i32 0, i32 8
  %26 = load %struct.Type*, %struct.Type** %25, align 8
  %27 = load i32, i32* %9, align 4
  %28 = call %struct.Type* @array_of(%struct.Type* noundef %26, i32 noundef %27)
  %29 = call %struct.Initializer* @new_initializer(%struct.Type* noundef %28, i1 noundef zeroext false)
  %30 = bitcast %struct.Initializer* %21 to i8*
  %31 = bitcast %struct.Initializer* %29 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %30, i8* align 8 %31, i64 56, i1 false)
  br label %32

32:                                               ; preds = %15, %4
  br label %33

33:                                               ; preds = %72, %32
  %34 = load i32, i32* %8, align 4
  %35 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %36 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %35, i32 0, i32 1
  %37 = load %struct.Type*, %struct.Type** %36, align 8
  %38 = getelementptr inbounds %struct.Type, %struct.Type* %37, i32 0, i32 11
  %39 = load i32, i32* %38, align 8
  %40 = icmp slt i32 %34, %39
  br i1 %40, label %41, label %45

41:                                               ; preds = %33
  %42 = load %struct.Token*, %struct.Token** %6, align 8
  %43 = call zeroext i1 @is_end(%struct.Token* noundef %42)
  %44 = xor i1 %43, true
  br label %45

45:                                               ; preds = %41, %33
  %46 = phi i1 [ false, %33 ], [ %44, %41 ]
  br i1 %46, label %47, label %75

47:                                               ; preds = %45
  %48 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %48, %struct.Token** %10, align 8
  %49 = load i32, i32* %8, align 4
  %50 = icmp sgt i32 %49, 0
  br i1 %50, label %51, label %54

51:                                               ; preds = %47
  %52 = load %struct.Token*, %struct.Token** %6, align 8
  %53 = call %struct.Token* @skip(%struct.Token* noundef %52, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %53, %struct.Token** %6, align 8
  br label %54

54:                                               ; preds = %51, %47
  %55 = load %struct.Token*, %struct.Token** %6, align 8
  %56 = call zeroext i1 @equal(%struct.Token* noundef %55, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.119, i64 0, i64 0))
  br i1 %56, label %60, label %57

57:                                               ; preds = %54
  %58 = load %struct.Token*, %struct.Token** %6, align 8
  %59 = call zeroext i1 @equal(%struct.Token* noundef %58, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  br i1 %59, label %60, label %63

60:                                               ; preds = %57, %54
  %61 = load %struct.Token*, %struct.Token** %10, align 8
  %62 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %61, %struct.Token** %62, align 8
  br label %78

63:                                               ; preds = %57
  %64 = load %struct.Token*, %struct.Token** %6, align 8
  %65 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %66 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %65, i32 0, i32 5
  %67 = load %struct.Initializer**, %struct.Initializer*** %66, align 8
  %68 = load i32, i32* %8, align 4
  %69 = sext i32 %68 to i64
  %70 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %67, i64 %69
  %71 = load %struct.Initializer*, %struct.Initializer** %70, align 8
  call void @initializer2(%struct.Token** noundef %6, %struct.Token* noundef %64, %struct.Initializer* noundef %71)
  br label %72

72:                                               ; preds = %63
  %73 = load i32, i32* %8, align 4
  %74 = add nsw i32 %73, 1
  store i32 %74, i32* %8, align 4
  br label %33, !llvm.loop !45

75:                                               ; preds = %45
  %76 = load %struct.Token*, %struct.Token** %6, align 8
  %77 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %76, %struct.Token** %77, align 8
  br label %78

78:                                               ; preds = %75, %60
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @struct_initializer1(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca %struct.Member*, align 8
  %8 = alloca i8, align 1
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Initializer* %2, %struct.Initializer** %6, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = call %struct.Token* @skip(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  store %struct.Token* %10, %struct.Token** %5, align 8
  %11 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %12 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %11, i32 0, i32 1
  %13 = load %struct.Type*, %struct.Type** %12, align 8
  %14 = getelementptr inbounds %struct.Type, %struct.Type* %13, i32 0, i32 14
  %15 = load %struct.Member*, %struct.Member** %14, align 8
  store %struct.Member* %15, %struct.Member** %7, align 8
  store i8 1, i8* %8, align 1
  br label %16

16:                                               ; preds = %69, %30, %3
  %17 = load %struct.Token**, %struct.Token*** %4, align 8
  %18 = load %struct.Token*, %struct.Token** %5, align 8
  %19 = call zeroext i1 @consume_end(%struct.Token** noundef %17, %struct.Token* noundef %18)
  %20 = xor i1 %19, true
  br i1 %20, label %21, label %70

21:                                               ; preds = %16
  %22 = load i8, i8* %8, align 1
  %23 = trunc i8 %22 to i1
  br i1 %23, label %27, label %24

24:                                               ; preds = %21
  %25 = load %struct.Token*, %struct.Token** %5, align 8
  %26 = call %struct.Token* @skip(%struct.Token* noundef %25, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %26, %struct.Token** %5, align 8
  br label %27

27:                                               ; preds = %24, %21
  store i8 0, i8* %8, align 1
  %28 = load %struct.Token*, %struct.Token** %5, align 8
  %29 = call zeroext i1 @equal(%struct.Token* noundef %28, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  br i1 %29, label %30, label %49

30:                                               ; preds = %27
  %31 = load %struct.Token*, %struct.Token** %5, align 8
  %32 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %33 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %32, i32 0, i32 1
  %34 = load %struct.Type*, %struct.Type** %33, align 8
  %35 = call %struct.Member* @struct_designator(%struct.Token** noundef %5, %struct.Token* noundef %31, %struct.Type* noundef %34)
  store %struct.Member* %35, %struct.Member** %7, align 8
  %36 = load %struct.Token*, %struct.Token** %5, align 8
  %37 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %38 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %37, i32 0, i32 5
  %39 = load %struct.Initializer**, %struct.Initializer*** %38, align 8
  %40 = load %struct.Member*, %struct.Member** %7, align 8
  %41 = getelementptr inbounds %struct.Member, %struct.Member* %40, i32 0, i32 4
  %42 = load i32, i32* %41, align 8
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %39, i64 %43
  %45 = load %struct.Initializer*, %struct.Initializer** %44, align 8
  call void @designation(%struct.Token** noundef %5, %struct.Token* noundef %36, %struct.Initializer* noundef %45)
  %46 = load %struct.Member*, %struct.Member** %7, align 8
  %47 = getelementptr inbounds %struct.Member, %struct.Member* %46, i32 0, i32 0
  %48 = load %struct.Member*, %struct.Member** %47, align 8
  store %struct.Member* %48, %struct.Member** %7, align 8
  br label %16, !llvm.loop !46

49:                                               ; preds = %27
  %50 = load %struct.Member*, %struct.Member** %7, align 8
  %51 = icmp ne %struct.Member* %50, null
  br i1 %51, label %52, label %66

52:                                               ; preds = %49
  %53 = load %struct.Token*, %struct.Token** %5, align 8
  %54 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %55 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %54, i32 0, i32 5
  %56 = load %struct.Initializer**, %struct.Initializer*** %55, align 8
  %57 = load %struct.Member*, %struct.Member** %7, align 8
  %58 = getelementptr inbounds %struct.Member, %struct.Member* %57, i32 0, i32 4
  %59 = load i32, i32* %58, align 8
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %56, i64 %60
  %62 = load %struct.Initializer*, %struct.Initializer** %61, align 8
  call void @initializer2(%struct.Token** noundef %5, %struct.Token* noundef %53, %struct.Initializer* noundef %62)
  %63 = load %struct.Member*, %struct.Member** %7, align 8
  %64 = getelementptr inbounds %struct.Member, %struct.Member* %63, i32 0, i32 0
  %65 = load %struct.Member*, %struct.Member** %64, align 8
  store %struct.Member* %65, %struct.Member** %7, align 8
  br label %69

66:                                               ; preds = %49
  %67 = load %struct.Token*, %struct.Token** %5, align 8
  %68 = call %struct.Token* @skip_excess_element(%struct.Token* noundef %67)
  store %struct.Token* %68, %struct.Token** %5, align 8
  br label %69

69:                                               ; preds = %66, %52
  br label %16, !llvm.loop !46

70:                                               ; preds = %16
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @assign(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %7 = load %struct.Token*, %struct.Token** %5, align 8
  %8 = call %struct.Node* @conditional(%struct.Token** noundef %5, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %6, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = call zeroext i1 @equal(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.150, i64 0, i64 0))
  br i1 %10, label %11, label %20

11:                                               ; preds = %2
  %12 = load %struct.Node*, %struct.Node** %6, align 8
  %13 = load %struct.Token**, %struct.Token*** %4, align 8
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 1
  %16 = load %struct.Token*, %struct.Token** %15, align 8
  %17 = call %struct.Node* @assign(%struct.Token** noundef %13, %struct.Token* noundef %16)
  %18 = load %struct.Token*, %struct.Token** %5, align 8
  %19 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %12, %struct.Node* noundef %17, %struct.Token* noundef %18)
  store %struct.Node* %19, %struct.Node** %3, align 8
  br label %154

20:                                               ; preds = %2
  %21 = load %struct.Token*, %struct.Token** %5, align 8
  %22 = call zeroext i1 @equal(%struct.Token* noundef %21, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.153, i64 0, i64 0))
  br i1 %22, label %23, label %33

23:                                               ; preds = %20
  %24 = load %struct.Node*, %struct.Node** %6, align 8
  %25 = load %struct.Token**, %struct.Token*** %4, align 8
  %26 = load %struct.Token*, %struct.Token** %5, align 8
  %27 = getelementptr inbounds %struct.Token, %struct.Token* %26, i32 0, i32 1
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  %29 = call %struct.Node* @assign(%struct.Token** noundef %25, %struct.Token* noundef %28)
  %30 = load %struct.Token*, %struct.Token** %5, align 8
  %31 = call %struct.Node* @new_add(%struct.Node* noundef %24, %struct.Node* noundef %29, %struct.Token* noundef %30)
  %32 = call %struct.Node* @to_assign(%struct.Node* noundef %31)
  store %struct.Node* %32, %struct.Node** %3, align 8
  br label %154

33:                                               ; preds = %20
  %34 = load %struct.Token*, %struct.Token** %5, align 8
  %35 = call zeroext i1 @equal(%struct.Token* noundef %34, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.154, i64 0, i64 0))
  br i1 %35, label %36, label %46

36:                                               ; preds = %33
  %37 = load %struct.Node*, %struct.Node** %6, align 8
  %38 = load %struct.Token**, %struct.Token*** %4, align 8
  %39 = load %struct.Token*, %struct.Token** %5, align 8
  %40 = getelementptr inbounds %struct.Token, %struct.Token* %39, i32 0, i32 1
  %41 = load %struct.Token*, %struct.Token** %40, align 8
  %42 = call %struct.Node* @assign(%struct.Token** noundef %38, %struct.Token* noundef %41)
  %43 = load %struct.Token*, %struct.Token** %5, align 8
  %44 = call %struct.Node* @new_sub(%struct.Node* noundef %37, %struct.Node* noundef %42, %struct.Token* noundef %43)
  %45 = call %struct.Node* @to_assign(%struct.Node* noundef %44)
  store %struct.Node* %45, %struct.Node** %3, align 8
  br label %154

46:                                               ; preds = %33
  %47 = load %struct.Token*, %struct.Token** %5, align 8
  %48 = call zeroext i1 @equal(%struct.Token* noundef %47, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.155, i64 0, i64 0))
  br i1 %48, label %49, label %59

49:                                               ; preds = %46
  %50 = load %struct.Node*, %struct.Node** %6, align 8
  %51 = load %struct.Token**, %struct.Token*** %4, align 8
  %52 = load %struct.Token*, %struct.Token** %5, align 8
  %53 = getelementptr inbounds %struct.Token, %struct.Token* %52, i32 0, i32 1
  %54 = load %struct.Token*, %struct.Token** %53, align 8
  %55 = call %struct.Node* @assign(%struct.Token** noundef %51, %struct.Token* noundef %54)
  %56 = load %struct.Token*, %struct.Token** %5, align 8
  %57 = call %struct.Node* @new_binary(i32 noundef 3, %struct.Node* noundef %50, %struct.Node* noundef %55, %struct.Token* noundef %56)
  %58 = call %struct.Node* @to_assign(%struct.Node* noundef %57)
  store %struct.Node* %58, %struct.Node** %3, align 8
  br label %154

59:                                               ; preds = %46
  %60 = load %struct.Token*, %struct.Token** %5, align 8
  %61 = call zeroext i1 @equal(%struct.Token* noundef %60, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.156, i64 0, i64 0))
  br i1 %61, label %62, label %72

62:                                               ; preds = %59
  %63 = load %struct.Node*, %struct.Node** %6, align 8
  %64 = load %struct.Token**, %struct.Token*** %4, align 8
  %65 = load %struct.Token*, %struct.Token** %5, align 8
  %66 = getelementptr inbounds %struct.Token, %struct.Token* %65, i32 0, i32 1
  %67 = load %struct.Token*, %struct.Token** %66, align 8
  %68 = call %struct.Node* @assign(%struct.Token** noundef %64, %struct.Token* noundef %67)
  %69 = load %struct.Token*, %struct.Token** %5, align 8
  %70 = call %struct.Node* @new_binary(i32 noundef 4, %struct.Node* noundef %63, %struct.Node* noundef %68, %struct.Token* noundef %69)
  %71 = call %struct.Node* @to_assign(%struct.Node* noundef %70)
  store %struct.Node* %71, %struct.Node** %3, align 8
  br label %154

72:                                               ; preds = %59
  %73 = load %struct.Token*, %struct.Token** %5, align 8
  %74 = call zeroext i1 @equal(%struct.Token* noundef %73, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.157, i64 0, i64 0))
  br i1 %74, label %75, label %85

75:                                               ; preds = %72
  %76 = load %struct.Node*, %struct.Node** %6, align 8
  %77 = load %struct.Token**, %struct.Token*** %4, align 8
  %78 = load %struct.Token*, %struct.Token** %5, align 8
  %79 = getelementptr inbounds %struct.Token, %struct.Token* %78, i32 0, i32 1
  %80 = load %struct.Token*, %struct.Token** %79, align 8
  %81 = call %struct.Node* @assign(%struct.Token** noundef %77, %struct.Token* noundef %80)
  %82 = load %struct.Token*, %struct.Token** %5, align 8
  %83 = call %struct.Node* @new_binary(i32 noundef 6, %struct.Node* noundef %76, %struct.Node* noundef %81, %struct.Token* noundef %82)
  %84 = call %struct.Node* @to_assign(%struct.Node* noundef %83)
  store %struct.Node* %84, %struct.Node** %3, align 8
  br label %154

85:                                               ; preds = %72
  %86 = load %struct.Token*, %struct.Token** %5, align 8
  %87 = call zeroext i1 @equal(%struct.Token* noundef %86, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.158, i64 0, i64 0))
  br i1 %87, label %88, label %98

88:                                               ; preds = %85
  %89 = load %struct.Node*, %struct.Node** %6, align 8
  %90 = load %struct.Token**, %struct.Token*** %4, align 8
  %91 = load %struct.Token*, %struct.Token** %5, align 8
  %92 = getelementptr inbounds %struct.Token, %struct.Token* %91, i32 0, i32 1
  %93 = load %struct.Token*, %struct.Token** %92, align 8
  %94 = call %struct.Node* @assign(%struct.Token** noundef %90, %struct.Token* noundef %93)
  %95 = load %struct.Token*, %struct.Token** %5, align 8
  %96 = call %struct.Node* @new_binary(i32 noundef 7, %struct.Node* noundef %89, %struct.Node* noundef %94, %struct.Token* noundef %95)
  %97 = call %struct.Node* @to_assign(%struct.Node* noundef %96)
  store %struct.Node* %97, %struct.Node** %3, align 8
  br label %154

98:                                               ; preds = %85
  %99 = load %struct.Token*, %struct.Token** %5, align 8
  %100 = call zeroext i1 @equal(%struct.Token* noundef %99, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.159, i64 0, i64 0))
  br i1 %100, label %101, label %111

101:                                              ; preds = %98
  %102 = load %struct.Node*, %struct.Node** %6, align 8
  %103 = load %struct.Token**, %struct.Token*** %4, align 8
  %104 = load %struct.Token*, %struct.Token** %5, align 8
  %105 = getelementptr inbounds %struct.Token, %struct.Token* %104, i32 0, i32 1
  %106 = load %struct.Token*, %struct.Token** %105, align 8
  %107 = call %struct.Node* @assign(%struct.Token** noundef %103, %struct.Token* noundef %106)
  %108 = load %struct.Token*, %struct.Token** %5, align 8
  %109 = call %struct.Node* @new_binary(i32 noundef 8, %struct.Node* noundef %102, %struct.Node* noundef %107, %struct.Token* noundef %108)
  %110 = call %struct.Node* @to_assign(%struct.Node* noundef %109)
  store %struct.Node* %110, %struct.Node** %3, align 8
  br label %154

111:                                              ; preds = %98
  %112 = load %struct.Token*, %struct.Token** %5, align 8
  %113 = call zeroext i1 @equal(%struct.Token* noundef %112, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.160, i64 0, i64 0))
  br i1 %113, label %114, label %124

114:                                              ; preds = %111
  %115 = load %struct.Node*, %struct.Node** %6, align 8
  %116 = load %struct.Token**, %struct.Token*** %4, align 8
  %117 = load %struct.Token*, %struct.Token** %5, align 8
  %118 = getelementptr inbounds %struct.Token, %struct.Token* %117, i32 0, i32 1
  %119 = load %struct.Token*, %struct.Token** %118, align 8
  %120 = call %struct.Node* @assign(%struct.Token** noundef %116, %struct.Token* noundef %119)
  %121 = load %struct.Token*, %struct.Token** %5, align 8
  %122 = call %struct.Node* @new_binary(i32 noundef 9, %struct.Node* noundef %115, %struct.Node* noundef %120, %struct.Token* noundef %121)
  %123 = call %struct.Node* @to_assign(%struct.Node* noundef %122)
  store %struct.Node* %123, %struct.Node** %3, align 8
  br label %154

124:                                              ; preds = %111
  %125 = load %struct.Token*, %struct.Token** %5, align 8
  %126 = call zeroext i1 @equal(%struct.Token* noundef %125, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.161, i64 0, i64 0))
  br i1 %126, label %127, label %137

127:                                              ; preds = %124
  %128 = load %struct.Node*, %struct.Node** %6, align 8
  %129 = load %struct.Token**, %struct.Token*** %4, align 8
  %130 = load %struct.Token*, %struct.Token** %5, align 8
  %131 = getelementptr inbounds %struct.Token, %struct.Token* %130, i32 0, i32 1
  %132 = load %struct.Token*, %struct.Token** %131, align 8
  %133 = call %struct.Node* @assign(%struct.Token** noundef %129, %struct.Token* noundef %132)
  %134 = load %struct.Token*, %struct.Token** %5, align 8
  %135 = call %struct.Node* @new_binary(i32 noundef 10, %struct.Node* noundef %128, %struct.Node* noundef %133, %struct.Token* noundef %134)
  %136 = call %struct.Node* @to_assign(%struct.Node* noundef %135)
  store %struct.Node* %136, %struct.Node** %3, align 8
  br label %154

137:                                              ; preds = %124
  %138 = load %struct.Token*, %struct.Token** %5, align 8
  %139 = call zeroext i1 @equal(%struct.Token* noundef %138, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.162, i64 0, i64 0))
  br i1 %139, label %140, label %150

140:                                              ; preds = %137
  %141 = load %struct.Node*, %struct.Node** %6, align 8
  %142 = load %struct.Token**, %struct.Token*** %4, align 8
  %143 = load %struct.Token*, %struct.Token** %5, align 8
  %144 = getelementptr inbounds %struct.Token, %struct.Token* %143, i32 0, i32 1
  %145 = load %struct.Token*, %struct.Token** %144, align 8
  %146 = call %struct.Node* @assign(%struct.Token** noundef %142, %struct.Token* noundef %145)
  %147 = load %struct.Token*, %struct.Token** %5, align 8
  %148 = call %struct.Node* @new_binary(i32 noundef 11, %struct.Node* noundef %141, %struct.Node* noundef %146, %struct.Token* noundef %147)
  %149 = call %struct.Node* @to_assign(%struct.Node* noundef %148)
  store %struct.Node* %149, %struct.Node** %3, align 8
  br label %154

150:                                              ; preds = %137
  %151 = load %struct.Token*, %struct.Token** %5, align 8
  %152 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %151, %struct.Token** %152, align 8
  %153 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %153, %struct.Node** %3, align 8
  br label %154

154:                                              ; preds = %150, %140, %127, %114, %101, %88, %75, %62, %49, %36, %23, %11
  %155 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %155
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @struct_initializer2(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2, %struct.Member* noundef %3) #0 {
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Initializer*, align 8
  %8 = alloca %struct.Member*, align 8
  %9 = alloca i8, align 1
  %10 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Initializer* %2, %struct.Initializer** %7, align 8
  store %struct.Member* %3, %struct.Member** %8, align 8
  store i8 1, i8* %9, align 1
  br label %11

11:                                               ; preds = %47, %4
  %12 = load %struct.Member*, %struct.Member** %8, align 8
  %13 = icmp ne %struct.Member* %12, null
  br i1 %13, label %14, label %18

14:                                               ; preds = %11
  %15 = load %struct.Token*, %struct.Token** %6, align 8
  %16 = call zeroext i1 @is_end(%struct.Token* noundef %15)
  %17 = xor i1 %16, true
  br label %18

18:                                               ; preds = %14, %11
  %19 = phi i1 [ false, %11 ], [ %17, %14 ]
  br i1 %19, label %20, label %51

20:                                               ; preds = %18
  %21 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %21, %struct.Token** %10, align 8
  %22 = load i8, i8* %9, align 1
  %23 = trunc i8 %22 to i1
  br i1 %23, label %27, label %24

24:                                               ; preds = %20
  %25 = load %struct.Token*, %struct.Token** %6, align 8
  %26 = call %struct.Token* @skip(%struct.Token* noundef %25, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %26, %struct.Token** %6, align 8
  br label %27

27:                                               ; preds = %24, %20
  store i8 0, i8* %9, align 1
  %28 = load %struct.Token*, %struct.Token** %6, align 8
  %29 = call zeroext i1 @equal(%struct.Token* noundef %28, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.119, i64 0, i64 0))
  br i1 %29, label %33, label %30

30:                                               ; preds = %27
  %31 = load %struct.Token*, %struct.Token** %6, align 8
  %32 = call zeroext i1 @equal(%struct.Token* noundef %31, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  br i1 %32, label %33, label %36

33:                                               ; preds = %30, %27
  %34 = load %struct.Token*, %struct.Token** %10, align 8
  %35 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %34, %struct.Token** %35, align 8
  br label %54

36:                                               ; preds = %30
  %37 = load %struct.Token*, %struct.Token** %6, align 8
  %38 = load %struct.Initializer*, %struct.Initializer** %7, align 8
  %39 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %38, i32 0, i32 5
  %40 = load %struct.Initializer**, %struct.Initializer*** %39, align 8
  %41 = load %struct.Member*, %struct.Member** %8, align 8
  %42 = getelementptr inbounds %struct.Member, %struct.Member* %41, i32 0, i32 4
  %43 = load i32, i32* %42, align 8
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %40, i64 %44
  %46 = load %struct.Initializer*, %struct.Initializer** %45, align 8
  call void @initializer2(%struct.Token** noundef %6, %struct.Token* noundef %37, %struct.Initializer* noundef %46)
  br label %47

47:                                               ; preds = %36
  %48 = load %struct.Member*, %struct.Member** %8, align 8
  %49 = getelementptr inbounds %struct.Member, %struct.Member* %48, i32 0, i32 0
  %50 = load %struct.Member*, %struct.Member** %49, align 8
  store %struct.Member* %50, %struct.Member** %8, align 8
  br label %11, !llvm.loop !47

51:                                               ; preds = %18
  %52 = load %struct.Token*, %struct.Token** %6, align 8
  %53 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %52, %struct.Token** %53, align 8
  br label %54

54:                                               ; preds = %51, %33
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @union_initializer(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca %struct.Member*, align 8
  %8 = alloca %struct.Member*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Initializer* %2, %struct.Initializer** %6, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = call zeroext i1 @equal(%struct.Token* noundef %9, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %10, label %11, label %88

11:                                               ; preds = %3
  %12 = load %struct.Token*, %struct.Token** %5, align 8
  %13 = getelementptr inbounds %struct.Token, %struct.Token* %12, i32 0, i32 1
  %14 = load %struct.Token*, %struct.Token** %13, align 8
  %15 = call zeroext i1 @equal(%struct.Token* noundef %14, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  br i1 %15, label %16, label %88

16:                                               ; preds = %11
  %17 = load %struct.Token*, %struct.Token** %5, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 1
  %19 = load %struct.Token*, %struct.Token** %18, align 8
  %20 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %21 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %20, i32 0, i32 1
  %22 = load %struct.Type*, %struct.Type** %21, align 8
  %23 = call %struct.Member* @struct_designator(%struct.Token** noundef %5, %struct.Token* noundef %19, %struct.Type* noundef %22)
  store %struct.Member* %23, %struct.Member** %7, align 8
  %24 = load %struct.Member*, %struct.Member** %7, align 8
  %25 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %26 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %25, i32 0, i32 6
  store %struct.Member* %24, %struct.Member** %26, align 8
  %27 = load %struct.Token*, %struct.Token** %5, align 8
  %28 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %29 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %28, i32 0, i32 5
  %30 = load %struct.Initializer**, %struct.Initializer*** %29, align 8
  %31 = load %struct.Member*, %struct.Member** %7, align 8
  %32 = getelementptr inbounds %struct.Member, %struct.Member* %31, i32 0, i32 4
  %33 = load i32, i32* %32, align 8
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %30, i64 %34
  %36 = load %struct.Initializer*, %struct.Initializer** %35, align 8
  call void @designation(%struct.Token** noundef %5, %struct.Token* noundef %27, %struct.Initializer* noundef %36)
  %37 = load %struct.Token*, %struct.Token** %5, align 8
  %38 = call zeroext i1 @equal(%struct.Token* noundef %37, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %38, label %39, label %47

39:                                               ; preds = %16
  %40 = load %struct.Token*, %struct.Token** %5, align 8
  %41 = getelementptr inbounds %struct.Token, %struct.Token* %40, i32 0, i32 1
  %42 = load %struct.Token*, %struct.Token** %41, align 8
  %43 = call zeroext i1 @equal(%struct.Token* noundef %42, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  br i1 %43, label %44, label %47

44:                                               ; preds = %39
  %45 = load %struct.Token*, %struct.Token** %5, align 8
  %46 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %45, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br label %47

47:                                               ; preds = %44, %39, %16
  br label %48

48:                                               ; preds = %83, %47
  %49 = load %struct.Token*, %struct.Token** %5, align 8
  %50 = call zeroext i1 @equal(%struct.Token* noundef %49, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  %51 = xor i1 %50, true
  br i1 %51, label %52, label %84

52:                                               ; preds = %48
  %53 = load %struct.Token*, %struct.Token** %5, align 8
  %54 = getelementptr inbounds %struct.Token, %struct.Token* %53, i32 0, i32 1
  %55 = load %struct.Token*, %struct.Token** %54, align 8
  %56 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %57 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %56, i32 0, i32 1
  %58 = load %struct.Type*, %struct.Type** %57, align 8
  %59 = call %struct.Member* @struct_designator(%struct.Token** noundef %5, %struct.Token* noundef %55, %struct.Type* noundef %58)
  store %struct.Member* %59, %struct.Member** %8, align 8
  %60 = load %struct.Member*, %struct.Member** %8, align 8
  %61 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %62 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %61, i32 0, i32 6
  store %struct.Member* %60, %struct.Member** %62, align 8
  %63 = load %struct.Token*, %struct.Token** %5, align 8
  %64 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %65 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %64, i32 0, i32 5
  %66 = load %struct.Initializer**, %struct.Initializer*** %65, align 8
  %67 = load %struct.Member*, %struct.Member** %8, align 8
  %68 = getelementptr inbounds %struct.Member, %struct.Member* %67, i32 0, i32 4
  %69 = load i32, i32* %68, align 8
  %70 = sext i32 %69 to i64
  %71 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %66, i64 %70
  %72 = load %struct.Initializer*, %struct.Initializer** %71, align 8
  call void @designation(%struct.Token** noundef %5, %struct.Token* noundef %63, %struct.Initializer* noundef %72)
  %73 = load %struct.Token*, %struct.Token** %5, align 8
  %74 = call zeroext i1 @equal(%struct.Token* noundef %73, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %74, label %75, label %83

75:                                               ; preds = %52
  %76 = load %struct.Token*, %struct.Token** %5, align 8
  %77 = getelementptr inbounds %struct.Token, %struct.Token* %76, i32 0, i32 1
  %78 = load %struct.Token*, %struct.Token** %77, align 8
  %79 = call zeroext i1 @equal(%struct.Token* noundef %78, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  br i1 %79, label %80, label %83

80:                                               ; preds = %75
  %81 = load %struct.Token*, %struct.Token** %5, align 8
  %82 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %81, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br label %83

83:                                               ; preds = %80, %75, %52
  br label %48, !llvm.loop !48

84:                                               ; preds = %48
  %85 = load %struct.Token*, %struct.Token** %5, align 8
  %86 = call %struct.Token* @skip(%struct.Token* noundef %85, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  %87 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %86, %struct.Token** %87, align 8
  br label %143

88:                                               ; preds = %11, %3
  %89 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %90 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %89, i32 0, i32 1
  %91 = load %struct.Type*, %struct.Type** %90, align 8
  %92 = getelementptr inbounds %struct.Type, %struct.Type* %91, i32 0, i32 14
  %93 = load %struct.Member*, %struct.Member** %92, align 8
  %94 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %95 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %94, i32 0, i32 6
  store %struct.Member* %93, %struct.Member** %95, align 8
  %96 = load %struct.Token*, %struct.Token** %5, align 8
  %97 = call zeroext i1 @equal(%struct.Token* noundef %96, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %97, label %98, label %121

98:                                               ; preds = %88
  %99 = load %struct.Token*, %struct.Token** %5, align 8
  %100 = getelementptr inbounds %struct.Token, %struct.Token* %99, i32 0, i32 1
  %101 = load %struct.Token*, %struct.Token** %100, align 8
  %102 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %103 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %102, i32 0, i32 5
  %104 = load %struct.Initializer**, %struct.Initializer*** %103, align 8
  %105 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %104, i64 0
  %106 = load %struct.Initializer*, %struct.Initializer** %105, align 8
  call void @initializer2(%struct.Token** noundef %5, %struct.Token* noundef %101, %struct.Initializer* noundef %106)
  %107 = load %struct.Token*, %struct.Token** %5, align 8
  %108 = call zeroext i1 @equal(%struct.Token* noundef %107, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %108, label %109, label %117

109:                                              ; preds = %98
  %110 = load %struct.Token*, %struct.Token** %5, align 8
  %111 = getelementptr inbounds %struct.Token, %struct.Token* %110, i32 0, i32 1
  %112 = load %struct.Token*, %struct.Token** %111, align 8
  %113 = call zeroext i1 @equal(%struct.Token* noundef %112, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  br i1 %113, label %114, label %117

114:                                              ; preds = %109
  %115 = load %struct.Token*, %struct.Token** %5, align 8
  %116 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %115, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br label %117

117:                                              ; preds = %114, %109, %98
  %118 = load %struct.Token*, %struct.Token** %5, align 8
  %119 = call %struct.Token* @skip(%struct.Token* noundef %118, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  %120 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %119, %struct.Token** %120, align 8
  br label %143

121:                                              ; preds = %88
  %122 = load %struct.Token*, %struct.Token** %5, align 8
  %123 = getelementptr inbounds %struct.Token, %struct.Token* %122, i32 0, i32 1
  %124 = load %struct.Token*, %struct.Token** %123, align 8
  %125 = call zeroext i1 @equal(%struct.Token* noundef %124, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.135, i64 0, i64 0))
  br i1 %125, label %126, label %134

126:                                              ; preds = %121
  %127 = load %struct.Token**, %struct.Token*** %4, align 8
  %128 = load %struct.Token*, %struct.Token** %5, align 8
  %129 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %130 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %129, i32 0, i32 5
  %131 = load %struct.Initializer**, %struct.Initializer*** %130, align 8
  %132 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %131, i64 0
  %133 = load %struct.Initializer*, %struct.Initializer** %132, align 8
  call void @initializer3(%struct.Token** noundef %127, %struct.Token* noundef %128, %struct.Initializer* noundef %133)
  br label %143

134:                                              ; preds = %121
  %135 = load %struct.Token**, %struct.Token*** %4, align 8
  %136 = load %struct.Token*, %struct.Token** %5, align 8
  %137 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %138 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %137, i32 0, i32 5
  %139 = load %struct.Initializer**, %struct.Initializer*** %138, align 8
  %140 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %139, i64 0
  %141 = load %struct.Initializer*, %struct.Initializer** %140, align 8
  call void @initializer2(%struct.Token** noundef %135, %struct.Token* noundef %136, %struct.Initializer* noundef %141)
  br label %142

142:                                              ; preds = %134
  br label %143

143:                                              ; preds = %84, %126, %142, %117
  ret void
}

; Function Attrs: argmemonly nofree nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #7

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @count_array_init_elements(%struct.Token* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca i8, align 1
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  store i8 1, i8* %5, align 1
  %9 = load %struct.Type*, %struct.Type** %4, align 8
  %10 = getelementptr inbounds %struct.Type, %struct.Type* %9, i32 0, i32 8
  %11 = load %struct.Type*, %struct.Type** %10, align 8
  %12 = call %struct.Initializer* @new_initializer(%struct.Type* noundef %11, i1 noundef zeroext true)
  store %struct.Initializer* %12, %struct.Initializer** %6, align 8
  store i32 0, i32* %7, align 4
  store i32 0, i32* %8, align 4
  br label %13

13:                                               ; preds = %58, %2
  %14 = load %struct.Token*, %struct.Token** %3, align 8
  %15 = call zeroext i1 @consume_end(%struct.Token** noundef %3, %struct.Token* noundef %14)
  %16 = xor i1 %15, true
  br i1 %16, label %17, label %60

17:                                               ; preds = %13
  %18 = load i8, i8* %5, align 1
  %19 = trunc i8 %18 to i1
  br i1 %19, label %23, label %20

20:                                               ; preds = %17
  %21 = load %struct.Token*, %struct.Token** %3, align 8
  %22 = call %struct.Token* @skip(%struct.Token* noundef %21, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %22, %struct.Token** %3, align 8
  br label %23

23:                                               ; preds = %20, %17
  store i8 0, i8* %5, align 1
  %24 = load %struct.Token*, %struct.Token** %3, align 8
  %25 = call zeroext i1 @equal(%struct.Token* noundef %24, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.119, i64 0, i64 0))
  br i1 %25, label %26, label %45

26:                                               ; preds = %23
  %27 = load %struct.Token*, %struct.Token** %3, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 1
  %29 = load %struct.Token*, %struct.Token** %28, align 8
  %30 = call i64 @const_expr(%struct.Token** noundef %3, %struct.Token* noundef %29)
  %31 = trunc i64 %30 to i32
  store i32 %31, i32* %7, align 4
  %32 = load %struct.Token*, %struct.Token** %3, align 8
  %33 = call zeroext i1 @equal(%struct.Token* noundef %32, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.120, i64 0, i64 0))
  br i1 %33, label %34, label %40

34:                                               ; preds = %26
  %35 = load %struct.Token*, %struct.Token** %3, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 1
  %37 = load %struct.Token*, %struct.Token** %36, align 8
  %38 = call i64 @const_expr(%struct.Token** noundef %3, %struct.Token* noundef %37)
  %39 = trunc i64 %38 to i32
  store i32 %39, i32* %7, align 4
  br label %40

40:                                               ; preds = %34, %26
  %41 = load %struct.Token*, %struct.Token** %3, align 8
  %42 = call %struct.Token* @skip(%struct.Token* noundef %41, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.125, i64 0, i64 0))
  store %struct.Token* %42, %struct.Token** %3, align 8
  %43 = load %struct.Token*, %struct.Token** %3, align 8
  %44 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @designation(%struct.Token** noundef %3, %struct.Token* noundef %43, %struct.Initializer* noundef %44)
  br label %48

45:                                               ; preds = %23
  %46 = load %struct.Token*, %struct.Token** %3, align 8
  %47 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @initializer2(%struct.Token** noundef %3, %struct.Token* noundef %46, %struct.Initializer* noundef %47)
  br label %48

48:                                               ; preds = %45, %40
  %49 = load i32, i32* %7, align 4
  %50 = add nsw i32 %49, 1
  store i32 %50, i32* %7, align 4
  %51 = load i32, i32* %8, align 4
  %52 = load i32, i32* %7, align 4
  %53 = icmp slt i32 %51, %52
  br i1 %53, label %54, label %56

54:                                               ; preds = %48
  %55 = load i32, i32* %7, align 4
  br label %58

56:                                               ; preds = %48
  %57 = load i32, i32* %8, align 4
  br label %58

58:                                               ; preds = %56, %54
  %59 = phi i32 [ %55, %54 ], [ %57, %56 ]
  store i32 %59, i32* %8, align 4
  br label %13, !llvm.loop !49

60:                                               ; preds = %13
  %61 = load i32, i32* %8, align 4
  ret i32 %61
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @consume_end(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca i1, align 1
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %6 = load %struct.Token*, %struct.Token** %5, align 8
  %7 = call zeroext i1 @equal(%struct.Token* noundef %6, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  br i1 %7, label %8, label %13

8:                                                ; preds = %2
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = getelementptr inbounds %struct.Token, %struct.Token* %9, i32 0, i32 1
  %11 = load %struct.Token*, %struct.Token** %10, align 8
  %12 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %11, %struct.Token** %12, align 8
  store i1 true, i1* %3, align 1
  br label %29

13:                                               ; preds = %2
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  %15 = call zeroext i1 @equal(%struct.Token* noundef %14, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %15, label %16, label %28

16:                                               ; preds = %13
  %17 = load %struct.Token*, %struct.Token** %5, align 8
  %18 = getelementptr inbounds %struct.Token, %struct.Token* %17, i32 0, i32 1
  %19 = load %struct.Token*, %struct.Token** %18, align 8
  %20 = call zeroext i1 @equal(%struct.Token* noundef %19, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  br i1 %20, label %21, label %28

21:                                               ; preds = %16
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = getelementptr inbounds %struct.Token, %struct.Token* %22, i32 0, i32 1
  %24 = load %struct.Token*, %struct.Token** %23, align 8
  %25 = getelementptr inbounds %struct.Token, %struct.Token* %24, i32 0, i32 1
  %26 = load %struct.Token*, %struct.Token** %25, align 8
  %27 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %26, %struct.Token** %27, align 8
  store i1 true, i1* %3, align 1
  br label %29

28:                                               ; preds = %16, %13
  store i1 false, i1* %3, align 1
  br label %29

29:                                               ; preds = %28, %21, %8
  %30 = load i1, i1* %3, align 1
  ret i1 %30
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @array_designator(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2, i32* noundef %3, i32* noundef %4) #0 {
  %6 = alloca %struct.Token**, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca %struct.Type*, align 8
  %9 = alloca i32*, align 8
  %10 = alloca i32*, align 8
  store %struct.Token** %0, %struct.Token*** %6, align 8
  store %struct.Token* %1, %struct.Token** %7, align 8
  store %struct.Type* %2, %struct.Type** %8, align 8
  store i32* %3, i32** %9, align 8
  store i32* %4, i32** %10, align 8
  %11 = load %struct.Token*, %struct.Token** %7, align 8
  %12 = getelementptr inbounds %struct.Token, %struct.Token* %11, i32 0, i32 1
  %13 = load %struct.Token*, %struct.Token** %12, align 8
  %14 = call i64 @const_expr(%struct.Token** noundef %7, %struct.Token* noundef %13)
  %15 = trunc i64 %14 to i32
  %16 = load i32*, i32** %9, align 8
  store i32 %15, i32* %16, align 4
  %17 = load i32*, i32** %9, align 8
  %18 = load i32, i32* %17, align 4
  %19 = load %struct.Type*, %struct.Type** %8, align 8
  %20 = getelementptr inbounds %struct.Type, %struct.Type* %19, i32 0, i32 11
  %21 = load i32, i32* %20, align 8
  %22 = icmp sge i32 %18, %21
  br i1 %22, label %23, label %25

23:                                               ; preds = %5
  %24 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %24, i8* noundef getelementptr inbounds ([70 x i8], [70 x i8]* @.str.145, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

25:                                               ; preds = %5
  %26 = load %struct.Token*, %struct.Token** %7, align 8
  %27 = call zeroext i1 @equal(%struct.Token* noundef %26, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.120, i64 0, i64 0))
  br i1 %27, label %28, label %56

28:                                               ; preds = %25
  %29 = load %struct.Token*, %struct.Token** %7, align 8
  %30 = getelementptr inbounds %struct.Token, %struct.Token* %29, i32 0, i32 1
  %31 = load %struct.Token*, %struct.Token** %30, align 8
  %32 = call i64 @const_expr(%struct.Token** noundef %7, %struct.Token* noundef %31)
  %33 = trunc i64 %32 to i32
  %34 = load i32*, i32** %10, align 8
  store i32 %33, i32* %34, align 4
  %35 = load i32*, i32** %10, align 8
  %36 = load i32, i32* %35, align 4
  %37 = load %struct.Type*, %struct.Type** %8, align 8
  %38 = getelementptr inbounds %struct.Type, %struct.Type* %37, i32 0, i32 11
  %39 = load i32, i32* %38, align 8
  %40 = icmp sge i32 %36, %39
  br i1 %40, label %41, label %43

41:                                               ; preds = %28
  %42 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %42, i8* noundef getelementptr inbounds ([53 x i8], [53 x i8]* @.str.146, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

43:                                               ; preds = %28
  %44 = load i32*, i32** %10, align 8
  %45 = load i32, i32* %44, align 4
  %46 = load i32*, i32** %9, align 8
  %47 = load i32, i32* %46, align 4
  %48 = icmp slt i32 %45, %47
  br i1 %48, label %49, label %55

49:                                               ; preds = %43
  %50 = load %struct.Token*, %struct.Token** %7, align 8
  %51 = load i32*, i32** %9, align 8
  %52 = load i32, i32* %51, align 4
  %53 = load i32*, i32** %10, align 8
  %54 = load i32, i32* %53, align 4
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %50, i8* noundef getelementptr inbounds ([50 x i8], [50 x i8]* @.str.147, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 noundef %52, i32 noundef %54) #9
  unreachable

55:                                               ; preds = %43
  br label %60

56:                                               ; preds = %25
  %57 = load i32*, i32** %9, align 8
  %58 = load i32, i32* %57, align 4
  %59 = load i32*, i32** %10, align 8
  store i32 %58, i32* %59, align 4
  br label %60

60:                                               ; preds = %56, %55
  %61 = load %struct.Token*, %struct.Token** %7, align 8
  %62 = call %struct.Token* @skip(%struct.Token* noundef %61, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.125, i64 0, i64 0))
  %63 = load %struct.Token**, %struct.Token*** %6, align 8
  store %struct.Token* %62, %struct.Token** %63, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @designation(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca %struct.Token*, align 8
  %10 = alloca i32, align 4
  %11 = alloca %struct.Member*, align 8
  %12 = alloca %struct.Member*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Initializer* %2, %struct.Initializer** %6, align 8
  %13 = load %struct.Token*, %struct.Token** %5, align 8
  %14 = call zeroext i1 @equal(%struct.Token* noundef %13, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.119, i64 0, i64 0))
  br i1 %14, label %15, label %52

15:                                               ; preds = %3
  %16 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %17 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %16, i32 0, i32 1
  %18 = load %struct.Type*, %struct.Type** %17, align 8
  %19 = getelementptr inbounds %struct.Type, %struct.Type* %18, i32 0, i32 0
  %20 = load i32, i32* %19, align 8
  %21 = icmp ne i32 %20, 12
  br i1 %21, label %22, label %24

22:                                               ; preds = %15
  %23 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %23, i8* noundef getelementptr inbounds ([58 x i8], [58 x i8]* @.str.148, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

24:                                               ; preds = %15
  %25 = load %struct.Token*, %struct.Token** %5, align 8
  %26 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %27 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %26, i32 0, i32 1
  %28 = load %struct.Type*, %struct.Type** %27, align 8
  call void @array_designator(%struct.Token** noundef %5, %struct.Token* noundef %25, %struct.Type* noundef %28, i32* noundef %7, i32* noundef %8)
  %29 = load i32, i32* %7, align 4
  store i32 %29, i32* %10, align 4
  br label %30

30:                                               ; preds = %43, %24
  %31 = load i32, i32* %10, align 4
  %32 = load i32, i32* %8, align 4
  %33 = icmp sle i32 %31, %32
  br i1 %33, label %34, label %46

34:                                               ; preds = %30
  %35 = load %struct.Token*, %struct.Token** %5, align 8
  %36 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %37 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %36, i32 0, i32 5
  %38 = load %struct.Initializer**, %struct.Initializer*** %37, align 8
  %39 = load i32, i32* %10, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %38, i64 %40
  %42 = load %struct.Initializer*, %struct.Initializer** %41, align 8
  call void @designation(%struct.Token** noundef %9, %struct.Token* noundef %35, %struct.Initializer* noundef %42)
  br label %43

43:                                               ; preds = %34
  %44 = load i32, i32* %10, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, i32* %10, align 4
  br label %30, !llvm.loop !50

46:                                               ; preds = %30
  %47 = load %struct.Token**, %struct.Token*** %4, align 8
  %48 = load %struct.Token*, %struct.Token** %9, align 8
  %49 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %50 = load i32, i32* %7, align 4
  %51 = add nsw i32 %50, 1
  call void @array_initializer2(%struct.Token** noundef %47, %struct.Token* noundef %48, %struct.Initializer* noundef %49, i32 noundef %51)
  br label %131

52:                                               ; preds = %3
  %53 = load %struct.Token*, %struct.Token** %5, align 8
  %54 = call zeroext i1 @equal(%struct.Token* noundef %53, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  br i1 %54, label %55, label %86

55:                                               ; preds = %52
  %56 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %57 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %56, i32 0, i32 1
  %58 = load %struct.Type*, %struct.Type** %57, align 8
  %59 = getelementptr inbounds %struct.Type, %struct.Type* %58, i32 0, i32 0
  %60 = load i32, i32* %59, align 8
  %61 = icmp eq i32 %60, 14
  br i1 %61, label %62, label %86

62:                                               ; preds = %55
  %63 = load %struct.Token*, %struct.Token** %5, align 8
  %64 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %65 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %64, i32 0, i32 1
  %66 = load %struct.Type*, %struct.Type** %65, align 8
  %67 = call %struct.Member* @struct_designator(%struct.Token** noundef %5, %struct.Token* noundef %63, %struct.Type* noundef %66)
  store %struct.Member* %67, %struct.Member** %11, align 8
  %68 = load %struct.Token*, %struct.Token** %5, align 8
  %69 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %70 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %69, i32 0, i32 5
  %71 = load %struct.Initializer**, %struct.Initializer*** %70, align 8
  %72 = load %struct.Member*, %struct.Member** %11, align 8
  %73 = getelementptr inbounds %struct.Member, %struct.Member* %72, i32 0, i32 4
  %74 = load i32, i32* %73, align 8
  %75 = sext i32 %74 to i64
  %76 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %71, i64 %75
  %77 = load %struct.Initializer*, %struct.Initializer** %76, align 8
  call void @designation(%struct.Token** noundef %5, %struct.Token* noundef %68, %struct.Initializer* noundef %77)
  %78 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %79 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %78, i32 0, i32 4
  store %struct.Node* null, %struct.Node** %79, align 8
  %80 = load %struct.Token**, %struct.Token*** %4, align 8
  %81 = load %struct.Token*, %struct.Token** %5, align 8
  %82 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %83 = load %struct.Member*, %struct.Member** %11, align 8
  %84 = getelementptr inbounds %struct.Member, %struct.Member* %83, i32 0, i32 0
  %85 = load %struct.Member*, %struct.Member** %84, align 8
  call void @struct_initializer2(%struct.Token** noundef %80, %struct.Token* noundef %81, %struct.Initializer* noundef %82, %struct.Member* noundef %85)
  br label %131

86:                                               ; preds = %55, %52
  %87 = load %struct.Token*, %struct.Token** %5, align 8
  %88 = call zeroext i1 @equal(%struct.Token* noundef %87, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  br i1 %88, label %89, label %116

89:                                               ; preds = %86
  %90 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %91 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %90, i32 0, i32 1
  %92 = load %struct.Type*, %struct.Type** %91, align 8
  %93 = getelementptr inbounds %struct.Type, %struct.Type* %92, i32 0, i32 0
  %94 = load i32, i32* %93, align 8
  %95 = icmp eq i32 %94, 15
  br i1 %95, label %96, label %116

96:                                               ; preds = %89
  %97 = load %struct.Token*, %struct.Token** %5, align 8
  %98 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %99 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %98, i32 0, i32 1
  %100 = load %struct.Type*, %struct.Type** %99, align 8
  %101 = call %struct.Member* @struct_designator(%struct.Token** noundef %5, %struct.Token* noundef %97, %struct.Type* noundef %100)
  store %struct.Member* %101, %struct.Member** %12, align 8
  %102 = load %struct.Member*, %struct.Member** %12, align 8
  %103 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %104 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %103, i32 0, i32 6
  store %struct.Member* %102, %struct.Member** %104, align 8
  %105 = load %struct.Token**, %struct.Token*** %4, align 8
  %106 = load %struct.Token*, %struct.Token** %5, align 8
  %107 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %108 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %107, i32 0, i32 5
  %109 = load %struct.Initializer**, %struct.Initializer*** %108, align 8
  %110 = load %struct.Member*, %struct.Member** %12, align 8
  %111 = getelementptr inbounds %struct.Member, %struct.Member* %110, i32 0, i32 4
  %112 = load i32, i32* %111, align 8
  %113 = sext i32 %112 to i64
  %114 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %109, i64 %113
  %115 = load %struct.Initializer*, %struct.Initializer** %114, align 8
  call void @designation(%struct.Token** noundef %105, %struct.Token* noundef %106, %struct.Initializer* noundef %115)
  br label %131

116:                                              ; preds = %89, %86
  %117 = load %struct.Token*, %struct.Token** %5, align 8
  %118 = call zeroext i1 @equal(%struct.Token* noundef %117, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  br i1 %118, label %119, label %121

119:                                              ; preds = %116
  %120 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %120, i8* noundef getelementptr inbounds ([66 x i8], [66 x i8]* @.str.149, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

121:                                              ; preds = %116
  %122 = load %struct.Token*, %struct.Token** %5, align 8
  %123 = call zeroext i1 @equal(%struct.Token* noundef %122, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.150, i64 0, i64 0))
  br i1 %123, label %124, label %127

124:                                              ; preds = %121
  %125 = load %struct.Token*, %struct.Token** %5, align 8
  %126 = call %struct.Token* @skip(%struct.Token* noundef %125, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.150, i64 0, i64 0))
  store %struct.Token* %126, %struct.Token** %5, align 8
  br label %127

127:                                              ; preds = %124, %121
  %128 = load %struct.Token**, %struct.Token*** %4, align 8
  %129 = load %struct.Token*, %struct.Token** %5, align 8
  %130 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  call void @initializer2(%struct.Token** noundef %128, %struct.Token* noundef %129, %struct.Initializer* noundef %130)
  br label %131

131:                                              ; preds = %127, %96, %62, %46
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @skip_excess_element(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  %3 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %4 = load %struct.Token*, %struct.Token** %3, align 8
  %5 = call zeroext i1 @equal(%struct.Token* noundef %4, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %5, label %6, label %13

6:                                                ; preds = %1
  %7 = load %struct.Token*, %struct.Token** %3, align 8
  %8 = getelementptr inbounds %struct.Token, %struct.Token* %7, i32 0, i32 1
  %9 = load %struct.Token*, %struct.Token** %8, align 8
  %10 = call %struct.Token* @skip_excess_element(%struct.Token* noundef %9)
  store %struct.Token* %10, %struct.Token** %3, align 8
  %11 = load %struct.Token*, %struct.Token** %3, align 8
  %12 = call %struct.Token* @skip(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  store %struct.Token* %12, %struct.Token** %2, align 8
  br label %17

13:                                               ; preds = %1
  %14 = load %struct.Token*, %struct.Token** %3, align 8
  %15 = call %struct.Node* @assign(%struct.Token** noundef %3, %struct.Token* noundef %14)
  %16 = load %struct.Token*, %struct.Token** %3, align 8
  store %struct.Token* %16, %struct.Token** %2, align 8
  br label %17

17:                                               ; preds = %13, %6
  %18 = load %struct.Token*, %struct.Token** %2, align 8
  ret %struct.Token* %18
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Member* @struct_designator(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Member*, align 8
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.Token*, align 8
  %9 = alloca %struct.Member*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  %10 = load %struct.Token*, %struct.Token** %6, align 8
  store %struct.Token* %10, %struct.Token** %8, align 8
  %11 = load %struct.Token*, %struct.Token** %6, align 8
  %12 = call %struct.Token* @skip(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.134, i64 0, i64 0))
  store %struct.Token* %12, %struct.Token** %6, align 8
  %13 = load %struct.Token*, %struct.Token** %6, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 0
  %15 = load i32, i32* %14, align 16
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %17, label %19

17:                                               ; preds = %3
  %18 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %18, i8* noundef getelementptr inbounds ([55 x i8], [55 x i8]* @.str.151, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

19:                                               ; preds = %3
  %20 = load %struct.Type*, %struct.Type** %7, align 8
  %21 = getelementptr inbounds %struct.Type, %struct.Type* %20, i32 0, i32 14
  %22 = load %struct.Member*, %struct.Member** %21, align 8
  store %struct.Member* %22, %struct.Member** %9, align 8
  br label %23

23:                                               ; preds = %90, %19
  %24 = load %struct.Member*, %struct.Member** %9, align 8
  %25 = icmp ne %struct.Member* %24, null
  br i1 %25, label %26, label %94

26:                                               ; preds = %23
  %27 = load %struct.Member*, %struct.Member** %9, align 8
  %28 = getelementptr inbounds %struct.Member, %struct.Member* %27, i32 0, i32 3
  %29 = load %struct.Token*, %struct.Token** %28, align 8
  %30 = icmp ne %struct.Token* %29, null
  br i1 %30, label %58, label %31

31:                                               ; preds = %26
  %32 = load %struct.Member*, %struct.Member** %9, align 8
  %33 = getelementptr inbounds %struct.Member, %struct.Member* %32, i32 0, i32 1
  %34 = load %struct.Type*, %struct.Type** %33, align 8
  %35 = getelementptr inbounds %struct.Type, %struct.Type* %34, i32 0, i32 0
  %36 = load i32, i32* %35, align 8
  %37 = icmp eq i32 %36, 14
  br i1 %37, label %45, label %38

38:                                               ; preds = %31
  %39 = load %struct.Member*, %struct.Member** %9, align 8
  %40 = getelementptr inbounds %struct.Member, %struct.Member* %39, i32 0, i32 1
  %41 = load %struct.Type*, %struct.Type** %40, align 8
  %42 = getelementptr inbounds %struct.Type, %struct.Type* %41, i32 0, i32 0
  %43 = load i32, i32* %42, align 8
  %44 = icmp eq i32 %43, 15
  br i1 %44, label %45, label %57

45:                                               ; preds = %38, %31
  %46 = load %struct.Member*, %struct.Member** %9, align 8
  %47 = getelementptr inbounds %struct.Member, %struct.Member* %46, i32 0, i32 1
  %48 = load %struct.Type*, %struct.Type** %47, align 8
  %49 = load %struct.Token*, %struct.Token** %6, align 8
  %50 = call %struct.Member* @get_struct_member(%struct.Type* noundef %48, %struct.Token* noundef %49)
  %51 = icmp ne %struct.Member* %50, null
  br i1 %51, label %52, label %56

52:                                               ; preds = %45
  %53 = load %struct.Token*, %struct.Token** %8, align 8
  %54 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %53, %struct.Token** %54, align 8
  %55 = load %struct.Member*, %struct.Member** %9, align 8
  store %struct.Member* %55, %struct.Member** %4, align 8
  br label %96

56:                                               ; preds = %45
  br label %57

57:                                               ; preds = %56, %38
  br label %90

58:                                               ; preds = %26
  %59 = load %struct.Member*, %struct.Member** %9, align 8
  %60 = getelementptr inbounds %struct.Member, %struct.Member* %59, i32 0, i32 3
  %61 = load %struct.Token*, %struct.Token** %60, align 8
  %62 = getelementptr inbounds %struct.Token, %struct.Token* %61, i32 0, i32 5
  %63 = load i32, i32* %62, align 8
  %64 = load %struct.Token*, %struct.Token** %6, align 8
  %65 = getelementptr inbounds %struct.Token, %struct.Token* %64, i32 0, i32 5
  %66 = load i32, i32* %65, align 8
  %67 = icmp eq i32 %63, %66
  br i1 %67, label %68, label %89

68:                                               ; preds = %58
  %69 = load %struct.Member*, %struct.Member** %9, align 8
  %70 = getelementptr inbounds %struct.Member, %struct.Member* %69, i32 0, i32 3
  %71 = load %struct.Token*, %struct.Token** %70, align 8
  %72 = getelementptr inbounds %struct.Token, %struct.Token* %71, i32 0, i32 4
  %73 = load i8*, i8** %72, align 16
  %74 = load %struct.Token*, %struct.Token** %6, align 8
  %75 = getelementptr inbounds %struct.Token, %struct.Token* %74, i32 0, i32 4
  %76 = load i8*, i8** %75, align 16
  %77 = load %struct.Token*, %struct.Token** %6, align 8
  %78 = getelementptr inbounds %struct.Token, %struct.Token* %77, i32 0, i32 5
  %79 = load i32, i32* %78, align 8
  %80 = sext i32 %79 to i64
  %81 = call i32 @strncmp(i8* noundef %73, i8* noundef %76, i64 noundef %80) #11
  %82 = icmp ne i32 %81, 0
  br i1 %82, label %89, label %83

83:                                               ; preds = %68
  %84 = load %struct.Token*, %struct.Token** %6, align 8
  %85 = getelementptr inbounds %struct.Token, %struct.Token* %84, i32 0, i32 1
  %86 = load %struct.Token*, %struct.Token** %85, align 8
  %87 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %86, %struct.Token** %87, align 8
  %88 = load %struct.Member*, %struct.Member** %9, align 8
  store %struct.Member* %88, %struct.Member** %4, align 8
  br label %96

89:                                               ; preds = %68, %58
  br label %90

90:                                               ; preds = %89, %57
  %91 = load %struct.Member*, %struct.Member** %9, align 8
  %92 = getelementptr inbounds %struct.Member, %struct.Member* %91, i32 0, i32 0
  %93 = load %struct.Member*, %struct.Member** %92, align 8
  store %struct.Member* %93, %struct.Member** %9, align 8
  br label %23, !llvm.loop !51

94:                                               ; preds = %23
  %95 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %95, i8* noundef getelementptr inbounds ([53 x i8], [53 x i8]* @.str.152, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

96:                                               ; preds = %83, %52
  %97 = load %struct.Member*, %struct.Member** %4, align 8
  ret %struct.Member* %97
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Member* @get_struct_member(%struct.Type* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Member*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Member*, align 8
  store %struct.Type* %0, %struct.Type** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %7 = load %struct.Type*, %struct.Type** %4, align 8
  %8 = getelementptr inbounds %struct.Type, %struct.Type* %7, i32 0, i32 14
  %9 = load %struct.Member*, %struct.Member** %8, align 8
  store %struct.Member* %9, %struct.Member** %6, align 8
  br label %10

10:                                               ; preds = %71, %2
  %11 = load %struct.Member*, %struct.Member** %6, align 8
  %12 = icmp ne %struct.Member* %11, null
  br i1 %12, label %13, label %75

13:                                               ; preds = %10
  %14 = load %struct.Member*, %struct.Member** %6, align 8
  %15 = getelementptr inbounds %struct.Member, %struct.Member* %14, i32 0, i32 3
  %16 = load %struct.Token*, %struct.Token** %15, align 8
  %17 = icmp ne %struct.Token* %16, null
  br i1 %17, label %43, label %18

18:                                               ; preds = %13
  %19 = load %struct.Member*, %struct.Member** %6, align 8
  %20 = getelementptr inbounds %struct.Member, %struct.Member* %19, i32 0, i32 1
  %21 = load %struct.Type*, %struct.Type** %20, align 8
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 0
  %23 = load i32, i32* %22, align 8
  %24 = icmp eq i32 %23, 14
  br i1 %24, label %32, label %25

25:                                               ; preds = %18
  %26 = load %struct.Member*, %struct.Member** %6, align 8
  %27 = getelementptr inbounds %struct.Member, %struct.Member* %26, i32 0, i32 1
  %28 = load %struct.Type*, %struct.Type** %27, align 8
  %29 = getelementptr inbounds %struct.Type, %struct.Type* %28, i32 0, i32 0
  %30 = load i32, i32* %29, align 8
  %31 = icmp eq i32 %30, 15
  br i1 %31, label %32, label %42

32:                                               ; preds = %25, %18
  %33 = load %struct.Member*, %struct.Member** %6, align 8
  %34 = getelementptr inbounds %struct.Member, %struct.Member* %33, i32 0, i32 1
  %35 = load %struct.Type*, %struct.Type** %34, align 8
  %36 = load %struct.Token*, %struct.Token** %5, align 8
  %37 = call %struct.Member* @get_struct_member(%struct.Type* noundef %35, %struct.Token* noundef %36)
  %38 = icmp ne %struct.Member* %37, null
  br i1 %38, label %39, label %41

39:                                               ; preds = %32
  %40 = load %struct.Member*, %struct.Member** %6, align 8
  store %struct.Member* %40, %struct.Member** %3, align 8
  br label %76

41:                                               ; preds = %32
  br label %42

42:                                               ; preds = %41, %25
  br label %71

43:                                               ; preds = %13
  %44 = load %struct.Member*, %struct.Member** %6, align 8
  %45 = getelementptr inbounds %struct.Member, %struct.Member* %44, i32 0, i32 3
  %46 = load %struct.Token*, %struct.Token** %45, align 8
  %47 = getelementptr inbounds %struct.Token, %struct.Token* %46, i32 0, i32 5
  %48 = load i32, i32* %47, align 8
  %49 = load %struct.Token*, %struct.Token** %5, align 8
  %50 = getelementptr inbounds %struct.Token, %struct.Token* %49, i32 0, i32 5
  %51 = load i32, i32* %50, align 8
  %52 = icmp eq i32 %48, %51
  br i1 %52, label %53, label %70

53:                                               ; preds = %43
  %54 = load %struct.Member*, %struct.Member** %6, align 8
  %55 = getelementptr inbounds %struct.Member, %struct.Member* %54, i32 0, i32 3
  %56 = load %struct.Token*, %struct.Token** %55, align 8
  %57 = getelementptr inbounds %struct.Token, %struct.Token* %56, i32 0, i32 4
  %58 = load i8*, i8** %57, align 16
  %59 = load %struct.Token*, %struct.Token** %5, align 8
  %60 = getelementptr inbounds %struct.Token, %struct.Token* %59, i32 0, i32 4
  %61 = load i8*, i8** %60, align 16
  %62 = load %struct.Token*, %struct.Token** %5, align 8
  %63 = getelementptr inbounds %struct.Token, %struct.Token* %62, i32 0, i32 5
  %64 = load i32, i32* %63, align 8
  %65 = sext i32 %64 to i64
  %66 = call i32 @strncmp(i8* noundef %58, i8* noundef %61, i64 noundef %65) #11
  %67 = icmp ne i32 %66, 0
  br i1 %67, label %70, label %68

68:                                               ; preds = %53
  %69 = load %struct.Member*, %struct.Member** %6, align 8
  store %struct.Member* %69, %struct.Member** %3, align 8
  br label %76

70:                                               ; preds = %53, %43
  br label %71

71:                                               ; preds = %70, %42
  %72 = load %struct.Member*, %struct.Member** %6, align 8
  %73 = getelementptr inbounds %struct.Member, %struct.Member* %72, i32 0, i32 0
  %74 = load %struct.Member*, %struct.Member** %73, align 8
  store %struct.Member* %74, %struct.Member** %6, align 8
  br label %10, !llvm.loop !52

75:                                               ; preds = %10
  store %struct.Member* null, %struct.Member** %3, align 8
  br label %76

76:                                               ; preds = %75, %68, %39
  %77 = load %struct.Member*, %struct.Member** %3, align 8
  ret %struct.Member* %77
}

; Function Attrs: nounwind readonly willreturn
declare i32 @strncmp(i8* noundef, i8* noundef, i64 noundef) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @is_end(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %3 = load %struct.Token*, %struct.Token** %2, align 8
  %4 = call zeroext i1 @equal(%struct.Token* noundef %3, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  br i1 %4, label %15, label %5

5:                                                ; preds = %1
  %6 = load %struct.Token*, %struct.Token** %2, align 8
  %7 = call zeroext i1 @equal(%struct.Token* noundef %6, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  br i1 %7, label %8, label %13

8:                                                ; preds = %5
  %9 = load %struct.Token*, %struct.Token** %2, align 8
  %10 = getelementptr inbounds %struct.Token, %struct.Token* %9, i32 0, i32 1
  %11 = load %struct.Token*, %struct.Token** %10, align 8
  %12 = call zeroext i1 @equal(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  br label %13

13:                                               ; preds = %8, %5
  %14 = phi i1 [ false, %5 ], [ %12, %8 ]
  br label %15

15:                                               ; preds = %13, %1
  %16 = phi i1 [ true, %1 ], [ %14, %13 ]
  ret i1 %16
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @initializer3(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Initializer* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Initializer* %2, %struct.Initializer** %6, align 8
  %8 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %9 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %8, i32 0, i32 1
  %10 = load %struct.Type*, %struct.Type** %9, align 8
  %11 = getelementptr inbounds %struct.Type, %struct.Type* %10, i32 0, i32 0
  %12 = load i32, i32* %11, align 8
  %13 = icmp eq i32 %12, 14
  br i1 %13, label %14, label %42

14:                                               ; preds = %3
  %15 = load %struct.Token**, %struct.Token*** %4, align 8
  %16 = load %struct.Token*, %struct.Token** %5, align 8
  %17 = call %struct.Node* @assign(%struct.Token** noundef %15, %struct.Token* noundef %16)
  store %struct.Node* %17, %struct.Node** %7, align 8
  %18 = load %struct.Node*, %struct.Node** %7, align 8
  call void @add_type(%struct.Node* noundef %18)
  %19 = load %struct.Node*, %struct.Node** %7, align 8
  %20 = getelementptr inbounds %struct.Node, %struct.Node* %19, i32 0, i32 2
  %21 = load %struct.Type*, %struct.Type** %20, align 16
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 0
  %23 = load i32, i32* %22, align 8
  %24 = icmp eq i32 %23, 14
  br i1 %24, label %32, label %25

25:                                               ; preds = %14
  %26 = load %struct.Node*, %struct.Node** %7, align 8
  %27 = getelementptr inbounds %struct.Node, %struct.Node* %26, i32 0, i32 2
  %28 = load %struct.Type*, %struct.Type** %27, align 16
  %29 = getelementptr inbounds %struct.Type, %struct.Type* %28, i32 0, i32 0
  %30 = load i32, i32* %29, align 8
  %31 = icmp eq i32 %30, 15
  br i1 %31, label %32, label %36

32:                                               ; preds = %25, %14
  %33 = load %struct.Node*, %struct.Node** %7, align 8
  %34 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %35 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %34, i32 0, i32 4
  store %struct.Node* %33, %struct.Node** %35, align 8
  br label %42

36:                                               ; preds = %25
  %37 = load %struct.Token**, %struct.Token*** %4, align 8
  %38 = load %struct.Token*, %struct.Token** %5, align 8
  %39 = call %struct.Node* @assign(%struct.Token** noundef %37, %struct.Token* noundef %38)
  %40 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %41 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %40, i32 0, i32 4
  store %struct.Node* %39, %struct.Node** %41, align 8
  br label %42

42:                                               ; preds = %32, %36, %3
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i64 @read_buf(i8* noundef %0, i32 noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  store i32 %1, i32* %5, align 4
  %6 = load i32, i32* %5, align 4
  %7 = icmp eq i32 %6, 1
  br i1 %7, label %8, label %12

8:                                                ; preds = %2
  %9 = load i8*, i8** %4, align 8
  %10 = load i8, i8* %9, align 1
  %11 = sext i8 %10 to i64
  store i64 %11, i64* %3, align 8
  br label %44

12:                                               ; preds = %2
  %13 = load i32, i32* %5, align 4
  %14 = icmp eq i32 %13, 2
  br i1 %14, label %15, label %20

15:                                               ; preds = %12
  %16 = load i8*, i8** %4, align 8
  %17 = bitcast i8* %16 to i16*
  %18 = load i16, i16* %17, align 2
  %19 = zext i16 %18 to i64
  store i64 %19, i64* %3, align 8
  br label %44

20:                                               ; preds = %12
  %21 = load i32, i32* %5, align 4
  %22 = icmp eq i32 %21, 4
  br i1 %22, label %23, label %28

23:                                               ; preds = %20
  %24 = load i8*, i8** %4, align 8
  %25 = bitcast i8* %24 to i32*
  %26 = load i32, i32* %25, align 4
  %27 = zext i32 %26 to i64
  store i64 %27, i64* %3, align 8
  br label %44

28:                                               ; preds = %20
  %29 = load i32, i32* %5, align 4
  %30 = icmp eq i32 %29, 8
  br i1 %30, label %31, label %35

31:                                               ; preds = %28
  %32 = load i8*, i8** %4, align 8
  %33 = bitcast i8* %32 to i64*
  %34 = load i64, i64* %33, align 8
  store i64 %34, i64* %3, align 8
  br label %44

35:                                               ; preds = %28
  %36 = load i32, i32* %5, align 4
  %37 = icmp eq i32 %36, 16
  br i1 %37, label %38, label %43

38:                                               ; preds = %35
  %39 = load i8*, i8** %4, align 8
  %40 = bitcast i8* %39 to x86_fp80*
  %41 = load x86_fp80, x86_fp80* %40, align 16
  %42 = fptoui x86_fp80 %41 to i64
  store i64 %42, i64* %3, align 8
  br label %44

43:                                               ; preds = %35
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.165, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 noundef 1727) #9
  unreachable

44:                                               ; preds = %38, %31, %23, %15, %8
  %45 = load i64, i64* %3, align 8
  ret i64 %45
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @write_buf(i8* noundef %0, i64 noundef %1, i32 noundef %2) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  store i64 %1, i64* %5, align 8
  store i32 %2, i32* %6, align 4
  %7 = load i32, i32* %6, align 4
  %8 = icmp eq i32 %7, 1
  br i1 %8, label %9, label %13

9:                                                ; preds = %3
  %10 = load i64, i64* %5, align 8
  %11 = trunc i64 %10 to i8
  %12 = load i8*, i8** %4, align 8
  store i8 %11, i8* %12, align 1
  br label %49

13:                                               ; preds = %3
  %14 = load i32, i32* %6, align 4
  %15 = icmp eq i32 %14, 2
  br i1 %15, label %16, label %21

16:                                               ; preds = %13
  %17 = load i64, i64* %5, align 8
  %18 = trunc i64 %17 to i16
  %19 = load i8*, i8** %4, align 8
  %20 = bitcast i8* %19 to i16*
  store i16 %18, i16* %20, align 2
  br label %48

21:                                               ; preds = %13
  %22 = load i32, i32* %6, align 4
  %23 = icmp eq i32 %22, 4
  br i1 %23, label %24, label %29

24:                                               ; preds = %21
  %25 = load i64, i64* %5, align 8
  %26 = trunc i64 %25 to i32
  %27 = load i8*, i8** %4, align 8
  %28 = bitcast i8* %27 to i32*
  store i32 %26, i32* %28, align 4
  br label %47

29:                                               ; preds = %21
  %30 = load i32, i32* %6, align 4
  %31 = icmp eq i32 %30, 8
  br i1 %31, label %32, label %36

32:                                               ; preds = %29
  %33 = load i64, i64* %5, align 8
  %34 = load i8*, i8** %4, align 8
  %35 = bitcast i8* %34 to i64*
  store i64 %33, i64* %35, align 8
  br label %46

36:                                               ; preds = %29
  %37 = load i32, i32* %6, align 4
  %38 = icmp eq i32 %37, 16
  br i1 %38, label %39, label %44

39:                                               ; preds = %36
  %40 = load i64, i64* %5, align 8
  %41 = uitofp i64 %40 to x86_fp80
  %42 = load i8*, i8** %4, align 8
  %43 = bitcast i8* %42 to x86_fp80*
  store x86_fp80 %41, x86_fp80* %43, align 16
  br label %45

44:                                               ; preds = %36
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.165, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 noundef 1743) #9
  unreachable

45:                                               ; preds = %39
  br label %46

46:                                               ; preds = %45, %32
  br label %47

47:                                               ; preds = %46, %24
  br label %48

48:                                               ; preds = %47, %16
  br label %49

49:                                               ; preds = %48, %9
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @create_lvar_init(%struct.Initializer* noundef %0, %struct.Type* noundef %1, %struct.InitDesg* noundef %2, %struct.Token* noundef %3) #0 {
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Initializer*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.InitDesg*, align 8
  %9 = alloca %struct.Token*, align 8
  %10 = alloca %struct.Node*, align 8
  %11 = alloca i32, align 4
  %12 = alloca %struct.InitDesg, align 8
  %13 = alloca %struct.Node*, align 8
  %14 = alloca %struct.Node*, align 8
  %15 = alloca %struct.Member*, align 8
  %16 = alloca %struct.InitDesg, align 8
  %17 = alloca %struct.Node*, align 8
  %18 = alloca %struct.Member*, align 8
  %19 = alloca %struct.InitDesg, align 8
  %20 = alloca %struct.Node*, align 8
  store %struct.Initializer* %0, %struct.Initializer** %6, align 8
  store %struct.Type* %1, %struct.Type** %7, align 8
  store %struct.InitDesg* %2, %struct.InitDesg** %8, align 8
  store %struct.Token* %3, %struct.Token** %9, align 8
  %21 = load %struct.Type*, %struct.Type** %7, align 8
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 0
  %23 = load i32, i32* %22, align 8
  %24 = icmp eq i32 %23, 12
  br i1 %24, label %25, label %62

25:                                               ; preds = %4
  %26 = load %struct.Token*, %struct.Token** %9, align 8
  %27 = call %struct.Node* @new_node(i32 noundef 0, %struct.Token* noundef %26)
  store %struct.Node* %27, %struct.Node** %10, align 8
  store i32 0, i32* %11, align 4
  br label %28

28:                                               ; preds = %57, %25
  %29 = load i32, i32* %11, align 4
  %30 = load %struct.Type*, %struct.Type** %7, align 8
  %31 = getelementptr inbounds %struct.Type, %struct.Type* %30, i32 0, i32 11
  %32 = load i32, i32* %31, align 8
  %33 = icmp slt i32 %29, %32
  br i1 %33, label %34, label %60

34:                                               ; preds = %28
  %35 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %12, i32 0, i32 0
  %36 = load %struct.InitDesg*, %struct.InitDesg** %8, align 8
  store %struct.InitDesg* %36, %struct.InitDesg** %35, align 8
  %37 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %12, i32 0, i32 1
  %38 = load i32, i32* %11, align 4
  store i32 %38, i32* %37, align 8
  %39 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %12, i32 0, i32 2
  store %struct.Member* null, %struct.Member** %39, align 8
  %40 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %12, i32 0, i32 3
  store %struct.Obj* null, %struct.Obj** %40, align 8
  %41 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %42 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %41, i32 0, i32 5
  %43 = load %struct.Initializer**, %struct.Initializer*** %42, align 8
  %44 = load i32, i32* %11, align 4
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %43, i64 %45
  %47 = load %struct.Initializer*, %struct.Initializer** %46, align 8
  %48 = load %struct.Type*, %struct.Type** %7, align 8
  %49 = getelementptr inbounds %struct.Type, %struct.Type* %48, i32 0, i32 8
  %50 = load %struct.Type*, %struct.Type** %49, align 8
  %51 = load %struct.Token*, %struct.Token** %9, align 8
  %52 = call %struct.Node* @create_lvar_init(%struct.Initializer* noundef %47, %struct.Type* noundef %50, %struct.InitDesg* noundef %12, %struct.Token* noundef %51)
  store %struct.Node* %52, %struct.Node** %13, align 8
  %53 = load %struct.Node*, %struct.Node** %10, align 8
  %54 = load %struct.Node*, %struct.Node** %13, align 8
  %55 = load %struct.Token*, %struct.Token** %9, align 8
  %56 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %53, %struct.Node* noundef %54, %struct.Token* noundef %55)
  store %struct.Node* %56, %struct.Node** %10, align 8
  br label %57

57:                                               ; preds = %34
  %58 = load i32, i32* %11, align 4
  %59 = add nsw i32 %58, 1
  store i32 %59, i32* %11, align 4
  br label %28, !llvm.loop !53

60:                                               ; preds = %28
  %61 = load %struct.Node*, %struct.Node** %10, align 8
  store %struct.Node* %61, %struct.Node** %5, align 8
  br label %170

62:                                               ; preds = %4
  %63 = load %struct.Type*, %struct.Type** %7, align 8
  %64 = getelementptr inbounds %struct.Type, %struct.Type* %63, i32 0, i32 0
  %65 = load i32, i32* %64, align 8
  %66 = icmp eq i32 %65, 14
  br i1 %66, label %67, label %112

67:                                               ; preds = %62
  %68 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %69 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %68, i32 0, i32 4
  %70 = load %struct.Node*, %struct.Node** %69, align 8
  %71 = icmp ne %struct.Node* %70, null
  br i1 %71, label %112, label %72

72:                                               ; preds = %67
  %73 = load %struct.Token*, %struct.Token** %9, align 8
  %74 = call %struct.Node* @new_node(i32 noundef 0, %struct.Token* noundef %73)
  store %struct.Node* %74, %struct.Node** %14, align 8
  %75 = load %struct.Type*, %struct.Type** %7, align 8
  %76 = getelementptr inbounds %struct.Type, %struct.Type* %75, i32 0, i32 14
  %77 = load %struct.Member*, %struct.Member** %76, align 8
  store %struct.Member* %77, %struct.Member** %15, align 8
  br label %78

78:                                               ; preds = %106, %72
  %79 = load %struct.Member*, %struct.Member** %15, align 8
  %80 = icmp ne %struct.Member* %79, null
  br i1 %80, label %81, label %110

81:                                               ; preds = %78
  %82 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %16, i32 0, i32 0
  %83 = load %struct.InitDesg*, %struct.InitDesg** %8, align 8
  store %struct.InitDesg* %83, %struct.InitDesg** %82, align 8
  %84 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %16, i32 0, i32 1
  store i32 0, i32* %84, align 8
  %85 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %16, i32 0, i32 2
  %86 = load %struct.Member*, %struct.Member** %15, align 8
  store %struct.Member* %86, %struct.Member** %85, align 8
  %87 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %16, i32 0, i32 3
  store %struct.Obj* null, %struct.Obj** %87, align 8
  %88 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %89 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %88, i32 0, i32 5
  %90 = load %struct.Initializer**, %struct.Initializer*** %89, align 8
  %91 = load %struct.Member*, %struct.Member** %15, align 8
  %92 = getelementptr inbounds %struct.Member, %struct.Member* %91, i32 0, i32 4
  %93 = load i32, i32* %92, align 8
  %94 = sext i32 %93 to i64
  %95 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %90, i64 %94
  %96 = load %struct.Initializer*, %struct.Initializer** %95, align 8
  %97 = load %struct.Member*, %struct.Member** %15, align 8
  %98 = getelementptr inbounds %struct.Member, %struct.Member* %97, i32 0, i32 1
  %99 = load %struct.Type*, %struct.Type** %98, align 8
  %100 = load %struct.Token*, %struct.Token** %9, align 8
  %101 = call %struct.Node* @create_lvar_init(%struct.Initializer* noundef %96, %struct.Type* noundef %99, %struct.InitDesg* noundef %16, %struct.Token* noundef %100)
  store %struct.Node* %101, %struct.Node** %17, align 8
  %102 = load %struct.Node*, %struct.Node** %14, align 8
  %103 = load %struct.Node*, %struct.Node** %17, align 8
  %104 = load %struct.Token*, %struct.Token** %9, align 8
  %105 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %102, %struct.Node* noundef %103, %struct.Token* noundef %104)
  store %struct.Node* %105, %struct.Node** %14, align 8
  br label %106

106:                                              ; preds = %81
  %107 = load %struct.Member*, %struct.Member** %15, align 8
  %108 = getelementptr inbounds %struct.Member, %struct.Member* %107, i32 0, i32 0
  %109 = load %struct.Member*, %struct.Member** %108, align 8
  store %struct.Member* %109, %struct.Member** %15, align 8
  br label %78, !llvm.loop !54

110:                                              ; preds = %78
  %111 = load %struct.Node*, %struct.Node** %14, align 8
  store %struct.Node* %111, %struct.Node** %5, align 8
  br label %170

112:                                              ; preds = %67, %62
  %113 = load %struct.Type*, %struct.Type** %7, align 8
  %114 = getelementptr inbounds %struct.Type, %struct.Type* %113, i32 0, i32 0
  %115 = load i32, i32* %114, align 8
  %116 = icmp eq i32 %115, 15
  br i1 %116, label %117, label %152

117:                                              ; preds = %112
  %118 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %119 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %118, i32 0, i32 6
  %120 = load %struct.Member*, %struct.Member** %119, align 8
  %121 = icmp ne %struct.Member* %120, null
  br i1 %121, label %122, label %126

122:                                              ; preds = %117
  %123 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %124 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %123, i32 0, i32 6
  %125 = load %struct.Member*, %struct.Member** %124, align 8
  br label %130

126:                                              ; preds = %117
  %127 = load %struct.Type*, %struct.Type** %7, align 8
  %128 = getelementptr inbounds %struct.Type, %struct.Type* %127, i32 0, i32 14
  %129 = load %struct.Member*, %struct.Member** %128, align 8
  br label %130

130:                                              ; preds = %126, %122
  %131 = phi %struct.Member* [ %125, %122 ], [ %129, %126 ]
  store %struct.Member* %131, %struct.Member** %18, align 8
  %132 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %19, i32 0, i32 0
  %133 = load %struct.InitDesg*, %struct.InitDesg** %8, align 8
  store %struct.InitDesg* %133, %struct.InitDesg** %132, align 8
  %134 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %19, i32 0, i32 1
  store i32 0, i32* %134, align 8
  %135 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %19, i32 0, i32 2
  %136 = load %struct.Member*, %struct.Member** %18, align 8
  store %struct.Member* %136, %struct.Member** %135, align 8
  %137 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %19, i32 0, i32 3
  store %struct.Obj* null, %struct.Obj** %137, align 8
  %138 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %139 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %138, i32 0, i32 5
  %140 = load %struct.Initializer**, %struct.Initializer*** %139, align 8
  %141 = load %struct.Member*, %struct.Member** %18, align 8
  %142 = getelementptr inbounds %struct.Member, %struct.Member* %141, i32 0, i32 4
  %143 = load i32, i32* %142, align 8
  %144 = sext i32 %143 to i64
  %145 = getelementptr inbounds %struct.Initializer*, %struct.Initializer** %140, i64 %144
  %146 = load %struct.Initializer*, %struct.Initializer** %145, align 8
  %147 = load %struct.Member*, %struct.Member** %18, align 8
  %148 = getelementptr inbounds %struct.Member, %struct.Member* %147, i32 0, i32 1
  %149 = load %struct.Type*, %struct.Type** %148, align 8
  %150 = load %struct.Token*, %struct.Token** %9, align 8
  %151 = call %struct.Node* @create_lvar_init(%struct.Initializer* noundef %146, %struct.Type* noundef %149, %struct.InitDesg* noundef %19, %struct.Token* noundef %150)
  store %struct.Node* %151, %struct.Node** %5, align 8
  br label %170

152:                                              ; preds = %112
  %153 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %154 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %153, i32 0, i32 4
  %155 = load %struct.Node*, %struct.Node** %154, align 8
  %156 = icmp ne %struct.Node* %155, null
  br i1 %156, label %160, label %157

157:                                              ; preds = %152
  %158 = load %struct.Token*, %struct.Token** %9, align 8
  %159 = call %struct.Node* @new_node(i32 noundef 0, %struct.Token* noundef %158)
  store %struct.Node* %159, %struct.Node** %5, align 8
  br label %170

160:                                              ; preds = %152
  %161 = load %struct.InitDesg*, %struct.InitDesg** %8, align 8
  %162 = load %struct.Token*, %struct.Token** %9, align 8
  %163 = call %struct.Node* @init_desg_expr(%struct.InitDesg* noundef %161, %struct.Token* noundef %162)
  store %struct.Node* %163, %struct.Node** %20, align 8
  %164 = load %struct.Node*, %struct.Node** %20, align 8
  %165 = load %struct.Initializer*, %struct.Initializer** %6, align 8
  %166 = getelementptr inbounds %struct.Initializer, %struct.Initializer* %165, i32 0, i32 4
  %167 = load %struct.Node*, %struct.Node** %166, align 8
  %168 = load %struct.Token*, %struct.Token** %9, align 8
  %169 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %164, %struct.Node* noundef %167, %struct.Token* noundef %168)
  store %struct.Node* %169, %struct.Node** %5, align 8
  br label %170

170:                                              ; preds = %160, %157, %130, %110, %60
  %171 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %171
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @init_desg_expr(%struct.InitDesg* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.InitDesg*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Node*, align 8
  store %struct.InitDesg* %0, %struct.InitDesg** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %9 = load %struct.InitDesg*, %struct.InitDesg** %4, align 8
  %10 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %9, i32 0, i32 3
  %11 = load %struct.Obj*, %struct.Obj** %10, align 8
  %12 = icmp ne %struct.Obj* %11, null
  br i1 %12, label %13, label %19

13:                                               ; preds = %2
  %14 = load %struct.InitDesg*, %struct.InitDesg** %4, align 8
  %15 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %14, i32 0, i32 3
  %16 = load %struct.Obj*, %struct.Obj** %15, align 8
  %17 = load %struct.Token*, %struct.Token** %5, align 8
  %18 = call %struct.Node* @new_var_node(%struct.Obj* noundef %16, %struct.Token* noundef %17)
  store %struct.Node* %18, %struct.Node** %3, align 8
  br label %56

19:                                               ; preds = %2
  %20 = load %struct.InitDesg*, %struct.InitDesg** %4, align 8
  %21 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %20, i32 0, i32 2
  %22 = load %struct.Member*, %struct.Member** %21, align 8
  %23 = icmp ne %struct.Member* %22, null
  br i1 %23, label %24, label %38

24:                                               ; preds = %19
  %25 = load %struct.InitDesg*, %struct.InitDesg** %4, align 8
  %26 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %25, i32 0, i32 0
  %27 = load %struct.InitDesg*, %struct.InitDesg** %26, align 8
  %28 = load %struct.Token*, %struct.Token** %5, align 8
  %29 = call %struct.Node* @init_desg_expr(%struct.InitDesg* noundef %27, %struct.Token* noundef %28)
  %30 = load %struct.Token*, %struct.Token** %5, align 8
  %31 = call %struct.Node* @new_unary(i32 noundef 19, %struct.Node* noundef %29, %struct.Token* noundef %30)
  store %struct.Node* %31, %struct.Node** %6, align 8
  %32 = load %struct.InitDesg*, %struct.InitDesg** %4, align 8
  %33 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %32, i32 0, i32 2
  %34 = load %struct.Member*, %struct.Member** %33, align 8
  %35 = load %struct.Node*, %struct.Node** %6, align 8
  %36 = getelementptr inbounds %struct.Node, %struct.Node* %35, i32 0, i32 14
  store %struct.Member* %34, %struct.Member** %36, align 16
  %37 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %37, %struct.Node** %3, align 8
  br label %56

38:                                               ; preds = %19
  %39 = load %struct.InitDesg*, %struct.InitDesg** %4, align 8
  %40 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %39, i32 0, i32 0
  %41 = load %struct.InitDesg*, %struct.InitDesg** %40, align 8
  %42 = load %struct.Token*, %struct.Token** %5, align 8
  %43 = call %struct.Node* @init_desg_expr(%struct.InitDesg* noundef %41, %struct.Token* noundef %42)
  store %struct.Node* %43, %struct.Node** %7, align 8
  %44 = load %struct.InitDesg*, %struct.InitDesg** %4, align 8
  %45 = getelementptr inbounds %struct.InitDesg, %struct.InitDesg* %44, i32 0, i32 1
  %46 = load i32, i32* %45, align 8
  %47 = sext i32 %46 to i64
  %48 = load %struct.Token*, %struct.Token** %5, align 8
  %49 = call %struct.Node* @new_num(i64 noundef %47, %struct.Token* noundef %48)
  store %struct.Node* %49, %struct.Node** %8, align 8
  %50 = load %struct.Node*, %struct.Node** %7, align 8
  %51 = load %struct.Node*, %struct.Node** %8, align 8
  %52 = load %struct.Token*, %struct.Token** %5, align 8
  %53 = call %struct.Node* @new_add(%struct.Node* noundef %50, %struct.Node* noundef %51, %struct.Token* noundef %52)
  %54 = load %struct.Token*, %struct.Token** %5, align 8
  %55 = call %struct.Node* @new_unary(i32 noundef 21, %struct.Node* noundef %53, %struct.Token* noundef %54)
  store %struct.Node* %55, %struct.Node** %3, align 8
  br label %56

56:                                               ; preds = %38, %24, %13
  %57 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %57
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @compound_stmt(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Node, align 16
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.VarAttr, align 4
  %9 = alloca %struct.Type*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %10 = load %struct.Token*, %struct.Token** %4, align 8
  %11 = call %struct.Node* @new_node(i32 noundef 32, %struct.Token* noundef %10)
  store %struct.Node* %11, %struct.Node** %5, align 8
  %12 = bitcast %struct.Node* %6 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %12, i8 0, i64 320, i1 false)
  store %struct.Node* %6, %struct.Node** %7, align 8
  call void @enter_scope()
  br label %13

13:                                               ; preds = %62, %47, %39, %32, %2
  %14 = load %struct.Token*, %struct.Token** %4, align 8
  %15 = call zeroext i1 @equal(%struct.Token* noundef %14, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  %16 = xor i1 %15, true
  br i1 %16, label %17, label %64

17:                                               ; preds = %13
  %18 = load %struct.Token*, %struct.Token** %4, align 8
  %19 = call zeroext i1 @is_typename(%struct.Token* noundef %18)
  br i1 %19, label %20, label %57

20:                                               ; preds = %17
  %21 = load %struct.Token*, %struct.Token** %4, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 1
  %23 = load %struct.Token*, %struct.Token** %22, align 8
  %24 = call zeroext i1 @equal(%struct.Token* noundef %23, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  br i1 %24, label %57, label %25

25:                                               ; preds = %20
  %26 = bitcast %struct.VarAttr* %8 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 4 %26, i8 0, i64 12, i1 false)
  %27 = load %struct.Token*, %struct.Token** %4, align 8
  %28 = call %struct.Type* @declspec(%struct.Token** noundef %4, %struct.Token* noundef %27, %struct.VarAttr* noundef %8)
  store %struct.Type* %28, %struct.Type** %9, align 8
  %29 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %8, i32 0, i32 0
  %30 = load i8, i8* %29, align 4
  %31 = trunc i8 %30 to i1
  br i1 %31, label %32, label %36

32:                                               ; preds = %25
  %33 = load %struct.Token*, %struct.Token** %4, align 8
  %34 = load %struct.Type*, %struct.Type** %9, align 8
  %35 = call %struct.Token* @parse_typedef(%struct.Token* noundef %33, %struct.Type* noundef %34)
  store %struct.Token* %35, %struct.Token** %4, align 8
  br label %13, !llvm.loop !55

36:                                               ; preds = %25
  %37 = load %struct.Token*, %struct.Token** %4, align 8
  %38 = call zeroext i1 @is_function(%struct.Token* noundef %37)
  br i1 %38, label %39, label %43

39:                                               ; preds = %36
  %40 = load %struct.Token*, %struct.Token** %4, align 8
  %41 = load %struct.Type*, %struct.Type** %9, align 8
  %42 = call %struct.Token* @function(%struct.Token* noundef %40, %struct.Type* noundef %41, %struct.VarAttr* noundef %8)
  store %struct.Token* %42, %struct.Token** %4, align 8
  br label %13, !llvm.loop !55

43:                                               ; preds = %36
  %44 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %8, i32 0, i32 2
  %45 = load i8, i8* %44, align 2
  %46 = trunc i8 %45 to i1
  br i1 %46, label %47, label %51

47:                                               ; preds = %43
  %48 = load %struct.Token*, %struct.Token** %4, align 8
  %49 = load %struct.Type*, %struct.Type** %9, align 8
  %50 = call %struct.Token* @global_variable(%struct.Token* noundef %48, %struct.Type* noundef %49, %struct.VarAttr* noundef %8)
  store %struct.Token* %50, %struct.Token** %4, align 8
  br label %13, !llvm.loop !55

51:                                               ; preds = %43
  %52 = load %struct.Token*, %struct.Token** %4, align 8
  %53 = load %struct.Type*, %struct.Type** %9, align 8
  %54 = call %struct.Node* @declaration(%struct.Token** noundef %4, %struct.Token* noundef %52, %struct.Type* noundef %53, %struct.VarAttr* noundef %8)
  %55 = load %struct.Node*, %struct.Node** %7, align 8
  %56 = getelementptr inbounds %struct.Node, %struct.Node* %55, i32 0, i32 1
  store %struct.Node* %54, %struct.Node** %56, align 8
  store %struct.Node* %54, %struct.Node** %7, align 8
  br label %62

57:                                               ; preds = %20, %17
  %58 = load %struct.Token*, %struct.Token** %4, align 8
  %59 = call %struct.Node* @stmt(%struct.Token** noundef %4, %struct.Token* noundef %58)
  %60 = load %struct.Node*, %struct.Node** %7, align 8
  %61 = getelementptr inbounds %struct.Node, %struct.Node* %60, i32 0, i32 1
  store %struct.Node* %59, %struct.Node** %61, align 8
  store %struct.Node* %59, %struct.Node** %7, align 8
  br label %62

62:                                               ; preds = %57, %51
  %63 = load %struct.Node*, %struct.Node** %7, align 8
  call void @add_type(%struct.Node* noundef %63)
  br label %13, !llvm.loop !55

64:                                               ; preds = %13
  call void @leave_scope()
  %65 = getelementptr inbounds %struct.Node, %struct.Node* %6, i32 0, i32 1
  %66 = load %struct.Node*, %struct.Node** %65, align 8
  %67 = load %struct.Node*, %struct.Node** %5, align 8
  %68 = getelementptr inbounds %struct.Node, %struct.Node* %67, i32 0, i32 13
  store %struct.Node* %66, %struct.Node** %68, align 8
  %69 = load i8, i8* @isDotfile, align 1
  %70 = trunc i8 %69 to i1
  br i1 %70, label %71, label %101

71:                                               ; preds = %64
  %72 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %73 = icmp ne %struct._IO_FILE* %72, null
  br i1 %73, label %74, label %101

74:                                               ; preds = %71
  %75 = load %struct.Node*, %struct.Node** %5, align 8
  %76 = getelementptr inbounds %struct.Node, %struct.Node* %75, i32 0, i32 13
  %77 = load %struct.Node*, %struct.Node** %76, align 8
  %78 = icmp ne %struct.Node* %77, null
  br i1 %78, label %79, label %100

79:                                               ; preds = %74
  %80 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %81 = load %struct.Node*, %struct.Node** %5, align 8
  %82 = getelementptr inbounds %struct.Node, %struct.Node* %81, i32 0, i32 0
  %83 = load i32, i32* %82, align 16
  %84 = call i8* @nodekind2str(i32 noundef %83)
  %85 = load %struct.Node*, %struct.Node** %5, align 8
  %86 = getelementptr inbounds %struct.Node, %struct.Node* %85, i32 0, i32 36
  %87 = load i32, i32* %86, align 16
  %88 = load %struct.Node*, %struct.Node** %5, align 8
  %89 = getelementptr inbounds %struct.Node, %struct.Node* %88, i32 0, i32 13
  %90 = load %struct.Node*, %struct.Node** %89, align 8
  %91 = getelementptr inbounds %struct.Node, %struct.Node* %90, i32 0, i32 0
  %92 = load i32, i32* %91, align 16
  %93 = call i8* @nodekind2str(i32 noundef %92)
  %94 = load %struct.Node*, %struct.Node** %5, align 8
  %95 = getelementptr inbounds %struct.Node, %struct.Node* %94, i32 0, i32 13
  %96 = load %struct.Node*, %struct.Node** %95, align 8
  %97 = getelementptr inbounds %struct.Node, %struct.Node* %96, i32 0, i32 36
  %98 = load i32, i32* %97, align 16
  %99 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %80, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %84, i32 noundef %87, i8* noundef %93, i32 noundef %98)
  br label %100

100:                                              ; preds = %79, %74
  br label %101

101:                                              ; preds = %100, %71, %64
  %102 = load %struct.Token*, %struct.Token** %4, align 8
  %103 = getelementptr inbounds %struct.Token, %struct.Token* %102, i32 0, i32 1
  %104 = load %struct.Token*, %struct.Token** %103, align 8
  %105 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %104, %struct.Token** %105, align 8
  %106 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %106
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @compute_vla_size(%struct.Type* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Node*, align 8
  store %struct.Type* %0, %struct.Type** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = call %struct.Node* @new_node(i32 noundef 0, %struct.Token* noundef %9)
  store %struct.Node* %10, %struct.Node** %6, align 8
  %11 = load %struct.Type*, %struct.Type** %4, align 8
  %12 = getelementptr inbounds %struct.Type, %struct.Type* %11, i32 0, i32 8
  %13 = load %struct.Type*, %struct.Type** %12, align 8
  %14 = icmp ne %struct.Type* %13, null
  br i1 %14, label %15, label %24

15:                                               ; preds = %2
  %16 = load %struct.Node*, %struct.Node** %6, align 8
  %17 = load %struct.Type*, %struct.Type** %4, align 8
  %18 = getelementptr inbounds %struct.Type, %struct.Type* %17, i32 0, i32 8
  %19 = load %struct.Type*, %struct.Type** %18, align 8
  %20 = load %struct.Token*, %struct.Token** %5, align 8
  %21 = call %struct.Node* @compute_vla_size(%struct.Type* noundef %19, %struct.Token* noundef %20)
  %22 = load %struct.Token*, %struct.Token** %5, align 8
  %23 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %16, %struct.Node* noundef %21, %struct.Token* noundef %22)
  store %struct.Node* %23, %struct.Node** %6, align 8
  br label %24

24:                                               ; preds = %15, %2
  %25 = load %struct.Type*, %struct.Type** %4, align 8
  %26 = getelementptr inbounds %struct.Type, %struct.Type* %25, i32 0, i32 0
  %27 = load i32, i32* %26, align 8
  %28 = icmp ne i32 %27, 13
  br i1 %28, label %29, label %31

29:                                               ; preds = %24
  %30 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %30, %struct.Node** %3, align 8
  br label %77

31:                                               ; preds = %24
  %32 = load %struct.Type*, %struct.Type** %4, align 8
  %33 = getelementptr inbounds %struct.Type, %struct.Type* %32, i32 0, i32 8
  %34 = load %struct.Type*, %struct.Type** %33, align 8
  %35 = getelementptr inbounds %struct.Type, %struct.Type* %34, i32 0, i32 0
  %36 = load i32, i32* %35, align 8
  %37 = icmp eq i32 %36, 13
  br i1 %37, label %38, label %46

38:                                               ; preds = %31
  %39 = load %struct.Type*, %struct.Type** %4, align 8
  %40 = getelementptr inbounds %struct.Type, %struct.Type* %39, i32 0, i32 8
  %41 = load %struct.Type*, %struct.Type** %40, align 8
  %42 = getelementptr inbounds %struct.Type, %struct.Type* %41, i32 0, i32 13
  %43 = load %struct.Obj*, %struct.Obj** %42, align 8
  %44 = load %struct.Token*, %struct.Token** %5, align 8
  %45 = call %struct.Node* @new_var_node(%struct.Obj* noundef %43, %struct.Token* noundef %44)
  store %struct.Node* %45, %struct.Node** %7, align 8
  br label %55

46:                                               ; preds = %31
  %47 = load %struct.Type*, %struct.Type** %4, align 8
  %48 = getelementptr inbounds %struct.Type, %struct.Type* %47, i32 0, i32 8
  %49 = load %struct.Type*, %struct.Type** %48, align 8
  %50 = getelementptr inbounds %struct.Type, %struct.Type* %49, i32 0, i32 1
  %51 = load i32, i32* %50, align 4
  %52 = sext i32 %51 to i64
  %53 = load %struct.Token*, %struct.Token** %5, align 8
  %54 = call %struct.Node* @new_num(i64 noundef %52, %struct.Token* noundef %53)
  store %struct.Node* %54, %struct.Node** %7, align 8
  br label %55

55:                                               ; preds = %46, %38
  %56 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  %57 = call %struct.Obj* @new_lvar(i8* noundef getelementptr inbounds ([1 x i8], [1 x i8]* @.str.66, i64 0, i64 0), %struct.Type* noundef %56, i8* noundef null)
  %58 = load %struct.Type*, %struct.Type** %4, align 8
  %59 = getelementptr inbounds %struct.Type, %struct.Type* %58, i32 0, i32 13
  store %struct.Obj* %57, %struct.Obj** %59, align 8
  %60 = load %struct.Type*, %struct.Type** %4, align 8
  %61 = getelementptr inbounds %struct.Type, %struct.Type* %60, i32 0, i32 13
  %62 = load %struct.Obj*, %struct.Obj** %61, align 8
  %63 = load %struct.Token*, %struct.Token** %5, align 8
  %64 = call %struct.Node* @new_var_node(%struct.Obj* noundef %62, %struct.Token* noundef %63)
  %65 = load %struct.Type*, %struct.Type** %4, align 8
  %66 = getelementptr inbounds %struct.Type, %struct.Type* %65, i32 0, i32 12
  %67 = load %struct.Node*, %struct.Node** %66, align 8
  %68 = load %struct.Node*, %struct.Node** %7, align 8
  %69 = load %struct.Token*, %struct.Token** %5, align 8
  %70 = call %struct.Node* @new_binary(i32 noundef 3, %struct.Node* noundef %67, %struct.Node* noundef %68, %struct.Token* noundef %69)
  %71 = load %struct.Token*, %struct.Token** %5, align 8
  %72 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %64, %struct.Node* noundef %70, %struct.Token* noundef %71)
  store %struct.Node* %72, %struct.Node** %8, align 8
  %73 = load %struct.Node*, %struct.Node** %6, align 8
  %74 = load %struct.Node*, %struct.Node** %8, align 8
  %75 = load %struct.Token*, %struct.Token** %5, align 8
  %76 = call %struct.Node* @new_binary(i32 noundef 18, %struct.Node* noundef %73, %struct.Node* noundef %74, %struct.Token* noundef %75)
  store %struct.Node* %76, %struct.Node** %3, align 8
  br label %77

77:                                               ; preds = %55, %29
  %78 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %78
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_ulong(i64 noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  store i64 %0, i64* %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load %struct.Token*, %struct.Token** %4, align 8
  %7 = call %struct.Node* @new_node(i32 noundef 42, %struct.Token* noundef %6)
  store %struct.Node* %7, %struct.Node** %5, align 8
  %8 = load i64, i64* %3, align 8
  %9 = load %struct.Node*, %struct.Node** %5, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 34
  store i64 %8, i64* %10, align 16
  %11 = load %struct.Type*, %struct.Type** @ty_ulong, align 8
  %12 = load %struct.Node*, %struct.Node** %5, align 8
  %13 = getelementptr inbounds %struct.Node, %struct.Node* %12, i32 0, i32 2
  store %struct.Type* %11, %struct.Type** %13, align 16
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %14
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @generic_selection(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Node*, align 8
  %9 = alloca %struct.Type*, align 8
  %10 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %11 = load %struct.Token*, %struct.Token** %4, align 8
  %12 = call %struct.Token* @skip(%struct.Token* noundef %11, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %12, %struct.Token** %4, align 8
  %13 = load %struct.Token*, %struct.Token** %4, align 8
  %14 = call %struct.Node* @assign(%struct.Token** noundef %4, %struct.Token* noundef %13)
  store %struct.Node* %14, %struct.Node** %5, align 8
  %15 = load %struct.Node*, %struct.Node** %5, align 8
  call void @add_type(%struct.Node* noundef %15)
  %16 = load %struct.Node*, %struct.Node** %5, align 8
  %17 = getelementptr inbounds %struct.Node, %struct.Node* %16, i32 0, i32 2
  %18 = load %struct.Type*, %struct.Type** %17, align 16
  store %struct.Type* %18, %struct.Type** %6, align 8
  %19 = load %struct.Type*, %struct.Type** %6, align 8
  %20 = getelementptr inbounds %struct.Type, %struct.Type* %19, i32 0, i32 0
  %21 = load i32, i32* %20, align 8
  %22 = icmp eq i32 %21, 11
  br i1 %22, label %23, label %26

23:                                               ; preds = %2
  %24 = load %struct.Type*, %struct.Type** %6, align 8
  %25 = call %struct.Type* @pointer_to(%struct.Type* noundef %24)
  store %struct.Type* %25, %struct.Type** %6, align 8
  br label %37

26:                                               ; preds = %2
  %27 = load %struct.Type*, %struct.Type** %6, align 8
  %28 = getelementptr inbounds %struct.Type, %struct.Type* %27, i32 0, i32 0
  %29 = load i32, i32* %28, align 8
  %30 = icmp eq i32 %29, 12
  br i1 %30, label %31, label %36

31:                                               ; preds = %26
  %32 = load %struct.Type*, %struct.Type** %6, align 8
  %33 = getelementptr inbounds %struct.Type, %struct.Type* %32, i32 0, i32 8
  %34 = load %struct.Type*, %struct.Type** %33, align 8
  %35 = call %struct.Type* @pointer_to(%struct.Type* noundef %34)
  store %struct.Type* %35, %struct.Type** %6, align 8
  br label %36

36:                                               ; preds = %31, %26
  br label %37

37:                                               ; preds = %36, %23
  store %struct.Node* null, %struct.Node** %7, align 8
  br label %38

38:                                               ; preds = %72, %59, %37
  %39 = load %struct.Token**, %struct.Token*** %3, align 8
  %40 = load %struct.Token*, %struct.Token** %4, align 8
  %41 = call zeroext i1 @consume(%struct.Token** noundef %39, %struct.Token* noundef %40, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %42 = xor i1 %41, true
  br i1 %42, label %43, label %73

43:                                               ; preds = %38
  %44 = load %struct.Token*, %struct.Token** %4, align 8
  %45 = call %struct.Token* @skip(%struct.Token* noundef %44, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %45, %struct.Token** %4, align 8
  %46 = load %struct.Token*, %struct.Token** %4, align 8
  %47 = call zeroext i1 @equal(%struct.Token* noundef %46, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.195, i64 0, i64 0))
  br i1 %47, label %48, label %60

48:                                               ; preds = %43
  %49 = load %struct.Token*, %struct.Token** %4, align 8
  %50 = getelementptr inbounds %struct.Token, %struct.Token* %49, i32 0, i32 1
  %51 = load %struct.Token*, %struct.Token** %50, align 8
  %52 = call %struct.Token* @skip(%struct.Token* noundef %51, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  store %struct.Token* %52, %struct.Token** %4, align 8
  %53 = load %struct.Token*, %struct.Token** %4, align 8
  %54 = call %struct.Node* @assign(%struct.Token** noundef %4, %struct.Token* noundef %53)
  store %struct.Node* %54, %struct.Node** %8, align 8
  %55 = load %struct.Node*, %struct.Node** %7, align 8
  %56 = icmp ne %struct.Node* %55, null
  br i1 %56, label %59, label %57

57:                                               ; preds = %48
  %58 = load %struct.Node*, %struct.Node** %8, align 8
  store %struct.Node* %58, %struct.Node** %7, align 8
  br label %59

59:                                               ; preds = %57, %48
  br label %38, !llvm.loop !56

60:                                               ; preds = %43
  %61 = load %struct.Token*, %struct.Token** %4, align 8
  %62 = call %struct.Type* @typename(%struct.Token** noundef %4, %struct.Token* noundef %61)
  store %struct.Type* %62, %struct.Type** %9, align 8
  %63 = load %struct.Token*, %struct.Token** %4, align 8
  %64 = call %struct.Token* @skip(%struct.Token* noundef %63, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  store %struct.Token* %64, %struct.Token** %4, align 8
  %65 = load %struct.Token*, %struct.Token** %4, align 8
  %66 = call %struct.Node* @assign(%struct.Token** noundef %4, %struct.Token* noundef %65)
  store %struct.Node* %66, %struct.Node** %10, align 8
  %67 = load %struct.Type*, %struct.Type** %6, align 8
  %68 = load %struct.Type*, %struct.Type** %9, align 8
  %69 = call zeroext i1 @is_compatible(%struct.Type* noundef %67, %struct.Type* noundef %68)
  br i1 %69, label %70, label %72

70:                                               ; preds = %60
  %71 = load %struct.Node*, %struct.Node** %10, align 8
  store %struct.Node* %71, %struct.Node** %7, align 8
  br label %72

72:                                               ; preds = %70, %60
  br label %38, !llvm.loop !56

73:                                               ; preds = %38
  %74 = load %struct.Node*, %struct.Node** %7, align 8
  %75 = icmp ne %struct.Node* %74, null
  br i1 %75, label %78, label %76

76:                                               ; preds = %73
  %77 = load %struct.Node*, %struct.Node** %5, align 8
  store %struct.Node* %77, %struct.Node** %7, align 8
  br label %78

78:                                               ; preds = %76, %73
  %79 = load %struct.Node*, %struct.Node** %7, align 8
  ret %struct.Node* %79
}

declare zeroext i1 @is_compatible(%struct.Type* noundef, %struct.Type* noundef) #1

declare void @strarray_push(%struct.StringArray* noundef, i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Obj* @new_string_literal(i8* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca %struct.Obj*, align 8
  store i8* %0, i8** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  %6 = load %struct.Type*, %struct.Type** %4, align 8
  %7 = call %struct.Obj* @new_anon_gvar(%struct.Type* noundef %6)
  store %struct.Obj* %7, %struct.Obj** %5, align 8
  %8 = load i8*, i8** %3, align 8
  %9 = load %struct.Obj*, %struct.Obj** %5, align 8
  %10 = getelementptr inbounds %struct.Obj, %struct.Obj* %9, i32 0, i32 15
  store i8* %8, i8** %10, align 8
  %11 = load %struct.Obj*, %struct.Obj** %5, align 8
  ret %struct.Obj* %11
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @enter_scope() #0 {
  %1 = alloca %struct.Scope*, align 8
  %2 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 40) #8
  %3 = bitcast i8* %2 to %struct.Scope*
  store %struct.Scope* %3, %struct.Scope** %1, align 8
  %4 = load %struct.Scope*, %struct.Scope** %1, align 8
  %5 = icmp eq %struct.Scope* %4, null
  br i1 %5, label %6, label %7

6:                                                ; preds = %0
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([41 x i8], [41 x i8]* @.str.180, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

7:                                                ; preds = %0
  %8 = load %struct.Scope*, %struct.Scope** @scope, align 8
  %9 = load %struct.Scope*, %struct.Scope** %1, align 8
  %10 = getelementptr inbounds %struct.Scope, %struct.Scope* %9, i32 0, i32 0
  store %struct.Scope* %8, %struct.Scope** %10, align 8
  %11 = load %struct.Scope*, %struct.Scope** %1, align 8
  store %struct.Scope* %11, %struct.Scope** @scope, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @declaration(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2, %struct.VarAttr* noundef %3) #0 {
  %5 = alloca %struct.Token**, align 8
  %6 = alloca %struct.Token*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca %struct.VarAttr*, align 8
  %9 = alloca %struct.Node, align 16
  %10 = alloca %struct.Node*, align 8
  %11 = alloca i32, align 4
  %12 = alloca %struct.Type*, align 8
  %13 = alloca %struct.Obj*, align 8
  %14 = alloca %struct.Obj*, align 8
  %15 = alloca %struct.Token*, align 8
  %16 = alloca %struct.Node*, align 8
  %17 = alloca %struct.Obj*, align 8
  %18 = alloca %struct.Node*, align 8
  %19 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %5, align 8
  store %struct.Token* %1, %struct.Token** %6, align 8
  store %struct.Type* %2, %struct.Type** %7, align 8
  store %struct.VarAttr* %3, %struct.VarAttr** %8, align 8
  %20 = bitcast %struct.Node* %9 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %20, i8 0, i64 320, i1 false)
  store %struct.Node* %9, %struct.Node** %10, align 8
  store i32 0, i32* %11, align 4
  br label %21

21:                                               ; preds = %176, %94, %76, %4
  %22 = load %struct.Token*, %struct.Token** %6, align 8
  %23 = call zeroext i1 @equal(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %24 = xor i1 %23, true
  br i1 %24, label %25, label %177

25:                                               ; preds = %21
  %26 = load i32, i32* %11, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, i32* %11, align 4
  %28 = icmp sgt i32 %26, 0
  br i1 %28, label %29, label %32

29:                                               ; preds = %25
  %30 = load %struct.Token*, %struct.Token** %6, align 8
  %31 = call %struct.Token* @skip(%struct.Token* noundef %30, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %31, %struct.Token** %6, align 8
  br label %32

32:                                               ; preds = %29, %25
  %33 = load %struct.Token*, %struct.Token** %6, align 8
  %34 = load %struct.Type*, %struct.Type** %7, align 8
  %35 = call %struct.Type* @declarator(%struct.Token** noundef %6, %struct.Token* noundef %33, %struct.Type* noundef %34)
  store %struct.Type* %35, %struct.Type** %12, align 8
  %36 = load %struct.Type*, %struct.Type** %12, align 8
  %37 = getelementptr inbounds %struct.Type, %struct.Type* %36, i32 0, i32 0
  %38 = load i32, i32* %37, align 8
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %40, label %42

40:                                               ; preds = %32
  %41 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %41, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.181, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

42:                                               ; preds = %32
  %43 = load %struct.Type*, %struct.Type** %12, align 8
  %44 = getelementptr inbounds %struct.Type, %struct.Type* %43, i32 0, i32 9
  %45 = load %struct.Token*, %struct.Token** %44, align 8
  %46 = icmp ne %struct.Token* %45, null
  br i1 %46, label %51, label %47

47:                                               ; preds = %42
  %48 = load %struct.Type*, %struct.Type** %12, align 8
  %49 = getelementptr inbounds %struct.Type, %struct.Type* %48, i32 0, i32 10
  %50 = load %struct.Token*, %struct.Token** %49, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %50, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.182, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

51:                                               ; preds = %42
  %52 = load %struct.VarAttr*, %struct.VarAttr** %8, align 8
  %53 = icmp ne %struct.VarAttr* %52, null
  br i1 %53, label %54, label %77

54:                                               ; preds = %51
  %55 = load %struct.VarAttr*, %struct.VarAttr** %8, align 8
  %56 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %55, i32 0, i32 1
  %57 = load i8, i8* %56, align 1
  %58 = trunc i8 %57 to i1
  br i1 %58, label %59, label %77

59:                                               ; preds = %54
  %60 = load %struct.Type*, %struct.Type** %12, align 8
  %61 = call %struct.Obj* @new_anon_gvar(%struct.Type* noundef %60)
  store %struct.Obj* %61, %struct.Obj** %13, align 8
  %62 = load %struct.Obj*, %struct.Obj** %13, align 8
  %63 = load %struct.Type*, %struct.Type** %12, align 8
  %64 = getelementptr inbounds %struct.Type, %struct.Type* %63, i32 0, i32 9
  %65 = load %struct.Token*, %struct.Token** %64, align 8
  %66 = call i8* @get_ident(%struct.Token* noundef %65)
  %67 = call %struct.VarScope* @push_scope(i8* noundef %66)
  %68 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %67, i32 0, i32 0
  store %struct.Obj* %62, %struct.Obj** %68, align 8
  %69 = load %struct.Token*, %struct.Token** %6, align 8
  %70 = call zeroext i1 @equal(%struct.Token* noundef %69, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.150, i64 0, i64 0))
  br i1 %70, label %71, label %76

71:                                               ; preds = %59
  %72 = load %struct.Token*, %struct.Token** %6, align 8
  %73 = getelementptr inbounds %struct.Token, %struct.Token* %72, i32 0, i32 1
  %74 = load %struct.Token*, %struct.Token** %73, align 8
  %75 = load %struct.Obj*, %struct.Obj** %13, align 8
  call void @gvar_initializer(%struct.Token** noundef %6, %struct.Token* noundef %74, %struct.Obj* noundef %75)
  br label %76

76:                                               ; preds = %71, %59
  br label %21, !llvm.loop !57

77:                                               ; preds = %54, %51
  %78 = load %struct.Type*, %struct.Type** %12, align 8
  %79 = load %struct.Token*, %struct.Token** %6, align 8
  %80 = call %struct.Node* @compute_vla_size(%struct.Type* noundef %78, %struct.Token* noundef %79)
  %81 = load %struct.Token*, %struct.Token** %6, align 8
  %82 = call %struct.Node* @new_unary(i32 noundef 38, %struct.Node* noundef %80, %struct.Token* noundef %81)
  %83 = load %struct.Node*, %struct.Node** %10, align 8
  %84 = getelementptr inbounds %struct.Node, %struct.Node* %83, i32 0, i32 1
  store %struct.Node* %82, %struct.Node** %84, align 8
  store %struct.Node* %82, %struct.Node** %10, align 8
  %85 = load %struct.Type*, %struct.Type** %12, align 8
  %86 = getelementptr inbounds %struct.Type, %struct.Type* %85, i32 0, i32 0
  %87 = load i32, i32* %86, align 8
  %88 = icmp eq i32 %87, 13
  br i1 %88, label %89, label %120

89:                                               ; preds = %77
  %90 = load %struct.Token*, %struct.Token** %6, align 8
  %91 = call zeroext i1 @equal(%struct.Token* noundef %90, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.150, i64 0, i64 0))
  br i1 %91, label %92, label %94

92:                                               ; preds = %89
  %93 = load %struct.Token*, %struct.Token** %6, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %93, i8* noundef getelementptr inbounds ([65 x i8], [65 x i8]* @.str.183, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

94:                                               ; preds = %89
  %95 = load %struct.Type*, %struct.Type** %12, align 8
  %96 = getelementptr inbounds %struct.Type, %struct.Type* %95, i32 0, i32 9
  %97 = load %struct.Token*, %struct.Token** %96, align 8
  %98 = call i8* @get_ident(%struct.Token* noundef %97)
  %99 = load %struct.Type*, %struct.Type** %12, align 8
  %100 = call %struct.Obj* @new_lvar(i8* noundef %98, %struct.Type* noundef %99, i8* noundef null)
  store %struct.Obj* %100, %struct.Obj** %14, align 8
  %101 = load %struct.Type*, %struct.Type** %12, align 8
  %102 = getelementptr inbounds %struct.Type, %struct.Type* %101, i32 0, i32 9
  %103 = load %struct.Token*, %struct.Token** %102, align 8
  store %struct.Token* %103, %struct.Token** %15, align 8
  %104 = load %struct.Obj*, %struct.Obj** %14, align 8
  %105 = load %struct.Token*, %struct.Token** %15, align 8
  %106 = call %struct.Node* @new_vla_ptr(%struct.Obj* noundef %104, %struct.Token* noundef %105)
  %107 = load %struct.Type*, %struct.Type** %12, align 8
  %108 = getelementptr inbounds %struct.Type, %struct.Type* %107, i32 0, i32 13
  %109 = load %struct.Obj*, %struct.Obj** %108, align 8
  %110 = load %struct.Token*, %struct.Token** %15, align 8
  %111 = call %struct.Node* @new_var_node(%struct.Obj* noundef %109, %struct.Token* noundef %110)
  %112 = call %struct.Node* @new_alloca(%struct.Node* noundef %111)
  %113 = load %struct.Token*, %struct.Token** %15, align 8
  %114 = call %struct.Node* @new_binary(i32 noundef 16, %struct.Node* noundef %106, %struct.Node* noundef %112, %struct.Token* noundef %113)
  store %struct.Node* %114, %struct.Node** %16, align 8
  %115 = load %struct.Node*, %struct.Node** %16, align 8
  %116 = load %struct.Token*, %struct.Token** %15, align 8
  %117 = call %struct.Node* @new_unary(i32 noundef 38, %struct.Node* noundef %115, %struct.Token* noundef %116)
  %118 = load %struct.Node*, %struct.Node** %10, align 8
  %119 = getelementptr inbounds %struct.Node, %struct.Node* %118, i32 0, i32 1
  store %struct.Node* %117, %struct.Node** %119, align 8
  store %struct.Node* %117, %struct.Node** %10, align 8
  br label %21, !llvm.loop !57

120:                                              ; preds = %77
  %121 = load %struct.Type*, %struct.Type** %12, align 8
  %122 = getelementptr inbounds %struct.Type, %struct.Type* %121, i32 0, i32 9
  %123 = load %struct.Token*, %struct.Token** %122, align 8
  %124 = call i8* @get_ident(%struct.Token* noundef %123)
  %125 = load %struct.Type*, %struct.Type** %12, align 8
  %126 = call %struct.Obj* @new_lvar(i8* noundef %124, %struct.Type* noundef %125, i8* noundef null)
  store %struct.Obj* %126, %struct.Obj** %17, align 8
  %127 = load %struct.VarAttr*, %struct.VarAttr** %8, align 8
  %128 = icmp ne %struct.VarAttr* %127, null
  br i1 %128, label %129, label %140

129:                                              ; preds = %120
  %130 = load %struct.VarAttr*, %struct.VarAttr** %8, align 8
  %131 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %130, i32 0, i32 5
  %132 = load i32, i32* %131, align 4
  %133 = icmp ne i32 %132, 0
  br i1 %133, label %134, label %140

134:                                              ; preds = %129
  %135 = load %struct.VarAttr*, %struct.VarAttr** %8, align 8
  %136 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %135, i32 0, i32 5
  %137 = load i32, i32* %136, align 4
  %138 = load %struct.Obj*, %struct.Obj** %17, align 8
  %139 = getelementptr inbounds %struct.Obj, %struct.Obj* %138, i32 0, i32 6
  store i32 %137, i32* %139, align 4
  br label %140

140:                                              ; preds = %134, %129, %120
  %141 = load %struct.Token*, %struct.Token** %6, align 8
  %142 = call zeroext i1 @equal(%struct.Token* noundef %141, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.150, i64 0, i64 0))
  br i1 %142, label %143, label %154

143:                                              ; preds = %140
  %144 = load %struct.Token*, %struct.Token** %6, align 8
  %145 = getelementptr inbounds %struct.Token, %struct.Token* %144, i32 0, i32 1
  %146 = load %struct.Token*, %struct.Token** %145, align 8
  %147 = load %struct.Obj*, %struct.Obj** %17, align 8
  %148 = call %struct.Node* @lvar_initializer(%struct.Token** noundef %6, %struct.Token* noundef %146, %struct.Obj* noundef %147)
  store %struct.Node* %148, %struct.Node** %18, align 8
  %149 = load %struct.Node*, %struct.Node** %18, align 8
  %150 = load %struct.Token*, %struct.Token** %6, align 8
  %151 = call %struct.Node* @new_unary(i32 noundef 38, %struct.Node* noundef %149, %struct.Token* noundef %150)
  %152 = load %struct.Node*, %struct.Node** %10, align 8
  %153 = getelementptr inbounds %struct.Node, %struct.Node* %152, i32 0, i32 1
  store %struct.Node* %151, %struct.Node** %153, align 8
  store %struct.Node* %151, %struct.Node** %10, align 8
  br label %154

154:                                              ; preds = %143, %140
  %155 = load %struct.Obj*, %struct.Obj** %17, align 8
  %156 = getelementptr inbounds %struct.Obj, %struct.Obj* %155, i32 0, i32 3
  %157 = load %struct.Type*, %struct.Type** %156, align 8
  %158 = getelementptr inbounds %struct.Type, %struct.Type* %157, i32 0, i32 1
  %159 = load i32, i32* %158, align 4
  %160 = icmp slt i32 %159, 0
  br i1 %160, label %161, label %165

161:                                              ; preds = %154
  %162 = load %struct.Type*, %struct.Type** %12, align 8
  %163 = getelementptr inbounds %struct.Type, %struct.Type* %162, i32 0, i32 9
  %164 = load %struct.Token*, %struct.Token** %163, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %164, i8* noundef getelementptr inbounds ([50 x i8], [50 x i8]* @.str.184, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

165:                                              ; preds = %154
  %166 = load %struct.Obj*, %struct.Obj** %17, align 8
  %167 = getelementptr inbounds %struct.Obj, %struct.Obj* %166, i32 0, i32 3
  %168 = load %struct.Type*, %struct.Type** %167, align 8
  %169 = getelementptr inbounds %struct.Type, %struct.Type* %168, i32 0, i32 0
  %170 = load i32, i32* %169, align 8
  %171 = icmp eq i32 %170, 0
  br i1 %171, label %172, label %176

172:                                              ; preds = %165
  %173 = load %struct.Type*, %struct.Type** %12, align 8
  %174 = getelementptr inbounds %struct.Type, %struct.Type* %173, i32 0, i32 9
  %175 = load %struct.Token*, %struct.Token** %174, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %175, i8* noundef getelementptr inbounds ([44 x i8], [44 x i8]* @.str.181, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

176:                                              ; preds = %165
  br label %21, !llvm.loop !57

177:                                              ; preds = %21
  %178 = load %struct.Token*, %struct.Token** %6, align 8
  %179 = call %struct.Node* @new_node(i32 noundef 32, %struct.Token* noundef %178)
  store %struct.Node* %179, %struct.Node** %19, align 8
  %180 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 1
  %181 = load %struct.Node*, %struct.Node** %180, align 8
  %182 = load %struct.Node*, %struct.Node** %19, align 8
  %183 = getelementptr inbounds %struct.Node, %struct.Node* %182, i32 0, i32 13
  store %struct.Node* %181, %struct.Node** %183, align 8
  %184 = load %struct.Token*, %struct.Token** %6, align 8
  %185 = getelementptr inbounds %struct.Token, %struct.Token* %184, i32 0, i32 1
  %186 = load %struct.Token*, %struct.Token** %185, align 8
  %187 = load %struct.Token**, %struct.Token*** %5, align 8
  store %struct.Token* %186, %struct.Token** %187, align 8
  %188 = load %struct.Node*, %struct.Node** %19, align 8
  ret %struct.Node* %188
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @stmt(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Node*, align 8
  %9 = alloca %struct.Node*, align 8
  %10 = alloca %struct.Node*, align 8
  %11 = alloca %struct.Node*, align 8
  %12 = alloca i8*, align 8
  %13 = alloca %struct.Node*, align 8
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca %struct.Node*, align 8
  %17 = alloca %struct.Node*, align 8
  %18 = alloca i8*, align 8
  %19 = alloca i8*, align 8
  %20 = alloca %struct.Type*, align 8
  %21 = alloca %struct.Node*, align 8
  %22 = alloca i8*, align 8
  %23 = alloca i8*, align 8
  %24 = alloca %struct.Node*, align 8
  %25 = alloca i8*, align 8
  %26 = alloca i8*, align 8
  %27 = alloca %struct.Node*, align 8
  %28 = alloca %struct.Node*, align 8
  %29 = alloca %struct.Node*, align 8
  %30 = alloca %struct.Node*, align 8
  %31 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %32 = load %struct.Token*, %struct.Token** %5, align 8
  %33 = call zeroext i1 @equal(%struct.Token* noundef %32, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.185, i64 0, i64 0))
  br i1 %33, label %34, label %115

34:                                               ; preds = %2
  %35 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %36 = getelementptr inbounds %struct.Obj, %struct.Obj* %35, i32 0, i32 3
  %37 = load %struct.Type*, %struct.Type** %36, align 8
  %38 = getelementptr inbounds %struct.Type, %struct.Type* %37, i32 0, i32 17
  %39 = load %struct.Type*, %struct.Type** %38, align 8
  store %struct.Type* %39, %struct.Type** %6, align 8
  %40 = load %struct.Token*, %struct.Token** %5, align 8
  %41 = call %struct.Node* @new_node(i32 noundef 26, %struct.Token* noundef %40)
  store %struct.Node* %41, %struct.Node** %7, align 8
  %42 = load %struct.Token**, %struct.Token*** %4, align 8
  %43 = load %struct.Token*, %struct.Token** %5, align 8
  %44 = getelementptr inbounds %struct.Token, %struct.Token* %43, i32 0, i32 1
  %45 = load %struct.Token*, %struct.Token** %44, align 8
  %46 = call zeroext i1 @consume(%struct.Token** noundef %42, %struct.Token* noundef %45, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  br i1 %46, label %47, label %56

47:                                               ; preds = %34
  %48 = load %struct.Type*, %struct.Type** %6, align 8
  %49 = getelementptr inbounds %struct.Type, %struct.Type* %48, i32 0, i32 0
  %50 = load i32, i32* %49, align 8
  %51 = icmp ne i32 %50, 0
  br i1 %51, label %52, label %54

52:                                               ; preds = %47
  %53 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %53, i8* noundef getelementptr inbounds ([54 x i8], [54 x i8]* @.str.186, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

54:                                               ; preds = %47
  %55 = load %struct.Node*, %struct.Node** %7, align 8
  store %struct.Node* %55, %struct.Node** %3, align 8
  br label %704

56:                                               ; preds = %34
  %57 = load %struct.Token*, %struct.Token** %5, align 8
  %58 = getelementptr inbounds %struct.Token, %struct.Token* %57, i32 0, i32 1
  %59 = load %struct.Token*, %struct.Token** %58, align 8
  %60 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %59)
  store %struct.Node* %60, %struct.Node** %8, align 8
  %61 = load %struct.Token*, %struct.Token** %5, align 8
  %62 = call %struct.Token* @skip(%struct.Token* noundef %61, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %63 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %62, %struct.Token** %63, align 8
  %64 = load %struct.Node*, %struct.Node** %8, align 8
  call void @add_type(%struct.Node* noundef %64)
  %65 = load %struct.Type*, %struct.Type** %6, align 8
  %66 = getelementptr inbounds %struct.Type, %struct.Type* %65, i32 0, i32 0
  %67 = load i32, i32* %66, align 8
  %68 = icmp eq i32 %67, 0
  br i1 %68, label %69, label %80

69:                                               ; preds = %56
  %70 = load %struct.Node*, %struct.Node** %8, align 8
  %71 = getelementptr inbounds %struct.Node, %struct.Node* %70, i32 0, i32 2
  %72 = load %struct.Type*, %struct.Type** %71, align 16
  %73 = getelementptr inbounds %struct.Type, %struct.Type* %72, i32 0, i32 0
  %74 = load i32, i32* %73, align 8
  %75 = icmp ne i32 %74, 0
  br i1 %75, label %76, label %80

76:                                               ; preds = %69
  %77 = load %struct.Node*, %struct.Node** %8, align 8
  %78 = getelementptr inbounds %struct.Node, %struct.Node* %77, i32 0, i32 3
  %79 = load %struct.Token*, %struct.Token** %78, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %79, i8* noundef getelementptr inbounds ([61 x i8], [61 x i8]* @.str.187, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

80:                                               ; preds = %69, %56
  %81 = load %struct.Type*, %struct.Type** %6, align 8
  %82 = getelementptr inbounds %struct.Type, %struct.Type* %81, i32 0, i32 0
  %83 = load i32, i32* %82, align 8
  %84 = icmp ne i32 %83, 0
  br i1 %84, label %85, label %96

85:                                               ; preds = %80
  %86 = load %struct.Node*, %struct.Node** %8, align 8
  %87 = getelementptr inbounds %struct.Node, %struct.Node* %86, i32 0, i32 2
  %88 = load %struct.Type*, %struct.Type** %87, align 16
  %89 = getelementptr inbounds %struct.Type, %struct.Type* %88, i32 0, i32 0
  %90 = load i32, i32* %89, align 8
  %91 = icmp eq i32 %90, 0
  br i1 %91, label %92, label %96

92:                                               ; preds = %85
  %93 = load %struct.Node*, %struct.Node** %8, align 8
  %94 = getelementptr inbounds %struct.Node, %struct.Node* %93, i32 0, i32 3
  %95 = load %struct.Token*, %struct.Token** %94, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %95, i8* noundef getelementptr inbounds ([67 x i8], [67 x i8]* @.str.188, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

96:                                               ; preds = %85, %80
  %97 = load %struct.Type*, %struct.Type** %6, align 8
  %98 = getelementptr inbounds %struct.Type, %struct.Type* %97, i32 0, i32 0
  %99 = load i32, i32* %98, align 8
  %100 = icmp ne i32 %99, 14
  br i1 %100, label %101, label %110

101:                                              ; preds = %96
  %102 = load %struct.Type*, %struct.Type** %6, align 8
  %103 = getelementptr inbounds %struct.Type, %struct.Type* %102, i32 0, i32 0
  %104 = load i32, i32* %103, align 8
  %105 = icmp ne i32 %104, 15
  br i1 %105, label %106, label %110

106:                                              ; preds = %101
  %107 = load %struct.Node*, %struct.Node** %8, align 8
  %108 = load %struct.Type*, %struct.Type** %6, align 8
  %109 = call %struct.Node* @new_cast(%struct.Node* noundef %107, %struct.Type* noundef %108)
  store %struct.Node* %109, %struct.Node** %8, align 8
  br label %110

110:                                              ; preds = %106, %101, %96
  %111 = load %struct.Node*, %struct.Node** %8, align 8
  %112 = load %struct.Node*, %struct.Node** %7, align 8
  %113 = getelementptr inbounds %struct.Node, %struct.Node* %112, i32 0, i32 4
  store %struct.Node* %111, %struct.Node** %113, align 16
  %114 = load %struct.Node*, %struct.Node** %7, align 8
  store %struct.Node* %114, %struct.Node** %3, align 8
  br label %704

115:                                              ; preds = %2
  %116 = load %struct.Token*, %struct.Token** %5, align 8
  %117 = call zeroext i1 @equal(%struct.Token* noundef %116, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.189, i64 0, i64 0))
  br i1 %117, label %118, label %229

118:                                              ; preds = %115
  %119 = load %struct.Token*, %struct.Token** %5, align 8
  %120 = call %struct.Node* @new_node(i32 noundef 27, %struct.Token* noundef %119)
  store %struct.Node* %120, %struct.Node** %9, align 8
  %121 = load %struct.Token*, %struct.Token** %5, align 8
  %122 = getelementptr inbounds %struct.Token, %struct.Token* %121, i32 0, i32 1
  %123 = load %struct.Token*, %struct.Token** %122, align 8
  %124 = call %struct.Token* @skip(%struct.Token* noundef %123, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %124, %struct.Token** %5, align 8
  %125 = load %struct.Token*, %struct.Token** %5, align 8
  %126 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %125)
  %127 = load %struct.Node*, %struct.Node** %9, align 8
  %128 = getelementptr inbounds %struct.Node, %struct.Node* %127, i32 0, i32 6
  store %struct.Node* %126, %struct.Node** %128, align 16
  %129 = load i8, i8* @isDotfile, align 1
  %130 = trunc i8 %129 to i1
  br i1 %130, label %131, label %155

131:                                              ; preds = %118
  %132 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %133 = icmp ne %struct._IO_FILE* %132, null
  br i1 %133, label %134, label %155

134:                                              ; preds = %131
  %135 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %136 = load %struct.Node*, %struct.Node** %9, align 8
  %137 = getelementptr inbounds %struct.Node, %struct.Node* %136, i32 0, i32 0
  %138 = load i32, i32* %137, align 16
  %139 = call i8* @nodekind2str(i32 noundef %138)
  %140 = load %struct.Node*, %struct.Node** %9, align 8
  %141 = getelementptr inbounds %struct.Node, %struct.Node* %140, i32 0, i32 36
  %142 = load i32, i32* %141, align 16
  %143 = load %struct.Node*, %struct.Node** %9, align 8
  %144 = getelementptr inbounds %struct.Node, %struct.Node* %143, i32 0, i32 6
  %145 = load %struct.Node*, %struct.Node** %144, align 16
  %146 = getelementptr inbounds %struct.Node, %struct.Node* %145, i32 0, i32 0
  %147 = load i32, i32* %146, align 16
  %148 = call i8* @nodekind2str(i32 noundef %147)
  %149 = load %struct.Node*, %struct.Node** %9, align 8
  %150 = getelementptr inbounds %struct.Node, %struct.Node* %149, i32 0, i32 6
  %151 = load %struct.Node*, %struct.Node** %150, align 16
  %152 = getelementptr inbounds %struct.Node, %struct.Node* %151, i32 0, i32 36
  %153 = load i32, i32* %152, align 16
  %154 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %135, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %139, i32 noundef %142, i8* noundef %148, i32 noundef %153)
  br label %155

155:                                              ; preds = %134, %131, %118
  %156 = load %struct.Token*, %struct.Token** %5, align 8
  %157 = call %struct.Token* @skip(%struct.Token* noundef %156, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %157, %struct.Token** %5, align 8
  %158 = load %struct.Token*, %struct.Token** %5, align 8
  %159 = call %struct.Node* @stmt(%struct.Token** noundef %5, %struct.Token* noundef %158)
  %160 = load %struct.Node*, %struct.Node** %9, align 8
  %161 = getelementptr inbounds %struct.Node, %struct.Node* %160, i32 0, i32 7
  store %struct.Node* %159, %struct.Node** %161, align 8
  %162 = load i8, i8* @isDotfile, align 1
  %163 = trunc i8 %162 to i1
  br i1 %163, label %164, label %188

164:                                              ; preds = %155
  %165 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %166 = icmp ne %struct._IO_FILE* %165, null
  br i1 %166, label %167, label %188

167:                                              ; preds = %164
  %168 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %169 = load %struct.Node*, %struct.Node** %9, align 8
  %170 = getelementptr inbounds %struct.Node, %struct.Node* %169, i32 0, i32 0
  %171 = load i32, i32* %170, align 16
  %172 = call i8* @nodekind2str(i32 noundef %171)
  %173 = load %struct.Node*, %struct.Node** %9, align 8
  %174 = getelementptr inbounds %struct.Node, %struct.Node* %173, i32 0, i32 36
  %175 = load i32, i32* %174, align 16
  %176 = load %struct.Node*, %struct.Node** %9, align 8
  %177 = getelementptr inbounds %struct.Node, %struct.Node* %176, i32 0, i32 7
  %178 = load %struct.Node*, %struct.Node** %177, align 8
  %179 = getelementptr inbounds %struct.Node, %struct.Node* %178, i32 0, i32 0
  %180 = load i32, i32* %179, align 16
  %181 = call i8* @nodekind2str(i32 noundef %180)
  %182 = load %struct.Node*, %struct.Node** %9, align 8
  %183 = getelementptr inbounds %struct.Node, %struct.Node* %182, i32 0, i32 7
  %184 = load %struct.Node*, %struct.Node** %183, align 8
  %185 = getelementptr inbounds %struct.Node, %struct.Node* %184, i32 0, i32 36
  %186 = load i32, i32* %185, align 16
  %187 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %168, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %172, i32 noundef %175, i8* noundef %181, i32 noundef %186)
  br label %188

188:                                              ; preds = %167, %164, %155
  %189 = load %struct.Token*, %struct.Token** %5, align 8
  %190 = call zeroext i1 @equal(%struct.Token* noundef %189, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.190, i64 0, i64 0))
  br i1 %190, label %191, label %225

191:                                              ; preds = %188
  %192 = load %struct.Token*, %struct.Token** %5, align 8
  %193 = getelementptr inbounds %struct.Token, %struct.Token* %192, i32 0, i32 1
  %194 = load %struct.Token*, %struct.Token** %193, align 8
  %195 = call %struct.Node* @stmt(%struct.Token** noundef %5, %struct.Token* noundef %194)
  %196 = load %struct.Node*, %struct.Node** %9, align 8
  %197 = getelementptr inbounds %struct.Node, %struct.Node* %196, i32 0, i32 8
  store %struct.Node* %195, %struct.Node** %197, align 16
  %198 = load i8, i8* @isDotfile, align 1
  %199 = trunc i8 %198 to i1
  br i1 %199, label %200, label %224

200:                                              ; preds = %191
  %201 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %202 = icmp ne %struct._IO_FILE* %201, null
  br i1 %202, label %203, label %224

203:                                              ; preds = %200
  %204 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %205 = load %struct.Node*, %struct.Node** %9, align 8
  %206 = getelementptr inbounds %struct.Node, %struct.Node* %205, i32 0, i32 0
  %207 = load i32, i32* %206, align 16
  %208 = call i8* @nodekind2str(i32 noundef %207)
  %209 = load %struct.Node*, %struct.Node** %9, align 8
  %210 = getelementptr inbounds %struct.Node, %struct.Node* %209, i32 0, i32 36
  %211 = load i32, i32* %210, align 16
  %212 = load %struct.Node*, %struct.Node** %9, align 8
  %213 = getelementptr inbounds %struct.Node, %struct.Node* %212, i32 0, i32 8
  %214 = load %struct.Node*, %struct.Node** %213, align 16
  %215 = getelementptr inbounds %struct.Node, %struct.Node* %214, i32 0, i32 0
  %216 = load i32, i32* %215, align 16
  %217 = call i8* @nodekind2str(i32 noundef %216)
  %218 = load %struct.Node*, %struct.Node** %9, align 8
  %219 = getelementptr inbounds %struct.Node, %struct.Node* %218, i32 0, i32 8
  %220 = load %struct.Node*, %struct.Node** %219, align 16
  %221 = getelementptr inbounds %struct.Node, %struct.Node* %220, i32 0, i32 36
  %222 = load i32, i32* %221, align 16
  %223 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %204, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %208, i32 noundef %211, i8* noundef %217, i32 noundef %222)
  br label %224

224:                                              ; preds = %203, %200, %191
  br label %225

225:                                              ; preds = %224, %188
  %226 = load %struct.Token*, %struct.Token** %5, align 8
  %227 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %226, %struct.Token** %227, align 8
  %228 = load %struct.Node*, %struct.Node** %9, align 8
  store %struct.Node* %228, %struct.Node** %3, align 8
  br label %704

229:                                              ; preds = %115
  %230 = load %struct.Token*, %struct.Token** %5, align 8
  %231 = call zeroext i1 @equal(%struct.Token* noundef %230, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.191, i64 0, i64 0))
  br i1 %231, label %232, label %259

232:                                              ; preds = %229
  %233 = load %struct.Token*, %struct.Token** %5, align 8
  %234 = call %struct.Node* @new_node(i32 noundef 30, %struct.Token* noundef %233)
  store %struct.Node* %234, %struct.Node** %10, align 8
  %235 = load %struct.Token*, %struct.Token** %5, align 8
  %236 = getelementptr inbounds %struct.Token, %struct.Token* %235, i32 0, i32 1
  %237 = load %struct.Token*, %struct.Token** %236, align 8
  %238 = call %struct.Token* @skip(%struct.Token* noundef %237, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %238, %struct.Token** %5, align 8
  %239 = load %struct.Token*, %struct.Token** %5, align 8
  %240 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %239)
  %241 = load %struct.Node*, %struct.Node** %10, align 8
  %242 = getelementptr inbounds %struct.Node, %struct.Node* %241, i32 0, i32 6
  store %struct.Node* %240, %struct.Node** %242, align 16
  %243 = load %struct.Token*, %struct.Token** %5, align 8
  %244 = call %struct.Token* @skip(%struct.Token* noundef %243, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %244, %struct.Token** %5, align 8
  %245 = load %struct.Node*, %struct.Node** @current_switch, align 8
  store %struct.Node* %245, %struct.Node** %11, align 8
  %246 = load %struct.Node*, %struct.Node** %10, align 8
  store %struct.Node* %246, %struct.Node** @current_switch, align 8
  %247 = load i8*, i8** @brk_label, align 8
  store i8* %247, i8** %12, align 8
  %248 = call i8* @new_unique_name()
  %249 = load %struct.Node*, %struct.Node** %10, align 8
  %250 = getelementptr inbounds %struct.Node, %struct.Node* %249, i32 0, i32 11
  store i8* %248, i8** %250, align 8
  store i8* %248, i8** @brk_label, align 8
  %251 = load %struct.Token**, %struct.Token*** %4, align 8
  %252 = load %struct.Token*, %struct.Token** %5, align 8
  %253 = call %struct.Node* @stmt(%struct.Token** noundef %251, %struct.Token* noundef %252)
  %254 = load %struct.Node*, %struct.Node** %10, align 8
  %255 = getelementptr inbounds %struct.Node, %struct.Node* %254, i32 0, i32 7
  store %struct.Node* %253, %struct.Node** %255, align 8
  %256 = load %struct.Node*, %struct.Node** %11, align 8
  store %struct.Node* %256, %struct.Node** @current_switch, align 8
  %257 = load i8*, i8** %12, align 8
  store i8* %257, i8** @brk_label, align 8
  %258 = load %struct.Node*, %struct.Node** %10, align 8
  store %struct.Node* %258, %struct.Node** %3, align 8
  br label %704

259:                                              ; preds = %229
  %260 = load %struct.Token*, %struct.Token** %5, align 8
  %261 = call zeroext i1 @equal(%struct.Token* noundef %260, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.192, i64 0, i64 0))
  br i1 %261, label %262, label %319

262:                                              ; preds = %259
  %263 = load %struct.Node*, %struct.Node** @current_switch, align 8
  %264 = icmp ne %struct.Node* %263, null
  br i1 %264, label %267, label %265

265:                                              ; preds = %262
  %266 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %266, i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.193, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

267:                                              ; preds = %262
  %268 = load %struct.Token*, %struct.Token** %5, align 8
  %269 = call %struct.Node* @new_node(i32 noundef 31, %struct.Token* noundef %268)
  store %struct.Node* %269, %struct.Node** %13, align 8
  %270 = load %struct.Token*, %struct.Token** %5, align 8
  %271 = getelementptr inbounds %struct.Token, %struct.Token* %270, i32 0, i32 1
  %272 = load %struct.Token*, %struct.Token** %271, align 8
  %273 = call i64 @const_expr(%struct.Token** noundef %5, %struct.Token* noundef %272)
  %274 = trunc i64 %273 to i32
  store i32 %274, i32* %14, align 4
  %275 = load %struct.Token*, %struct.Token** %5, align 8
  %276 = call zeroext i1 @equal(%struct.Token* noundef %275, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.120, i64 0, i64 0))
  br i1 %276, label %277, label %289

277:                                              ; preds = %267
  %278 = load %struct.Token*, %struct.Token** %5, align 8
  %279 = getelementptr inbounds %struct.Token, %struct.Token* %278, i32 0, i32 1
  %280 = load %struct.Token*, %struct.Token** %279, align 8
  %281 = call i64 @const_expr(%struct.Token** noundef %5, %struct.Token* noundef %280)
  %282 = trunc i64 %281 to i32
  store i32 %282, i32* %15, align 4
  %283 = load i32, i32* %15, align 4
  %284 = load i32, i32* %14, align 4
  %285 = icmp slt i32 %283, %284
  br i1 %285, label %286, label %288

286:                                              ; preds = %277
  %287 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %287, i8* noundef getelementptr inbounds ([41 x i8], [41 x i8]* @.str.194, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

288:                                              ; preds = %277
  br label %291

289:                                              ; preds = %267
  %290 = load i32, i32* %14, align 4
  store i32 %290, i32* %15, align 4
  br label %291

291:                                              ; preds = %289, %288
  %292 = load %struct.Token*, %struct.Token** %5, align 8
  %293 = call %struct.Token* @skip(%struct.Token* noundef %292, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  store %struct.Token* %293, %struct.Token** %5, align 8
  %294 = call i8* @new_unique_name()
  %295 = load %struct.Node*, %struct.Node** %13, align 8
  %296 = getelementptr inbounds %struct.Node, %struct.Node* %295, i32 0, i32 19
  store i8* %294, i8** %296, align 8
  %297 = load %struct.Token**, %struct.Token*** %4, align 8
  %298 = load %struct.Token*, %struct.Token** %5, align 8
  %299 = call %struct.Node* @stmt(%struct.Token** noundef %297, %struct.Token* noundef %298)
  %300 = load %struct.Node*, %struct.Node** %13, align 8
  %301 = getelementptr inbounds %struct.Node, %struct.Node* %300, i32 0, i32 4
  store %struct.Node* %299, %struct.Node** %301, align 16
  %302 = load i32, i32* %14, align 4
  %303 = sext i32 %302 to i64
  %304 = load %struct.Node*, %struct.Node** %13, align 8
  %305 = getelementptr inbounds %struct.Node, %struct.Node* %304, i32 0, i32 24
  store i64 %303, i64* %305, align 16
  %306 = load i32, i32* %15, align 4
  %307 = sext i32 %306 to i64
  %308 = load %struct.Node*, %struct.Node** %13, align 8
  %309 = getelementptr inbounds %struct.Node, %struct.Node* %308, i32 0, i32 25
  store i64 %307, i64* %309, align 8
  %310 = load %struct.Node*, %struct.Node** @current_switch, align 8
  %311 = getelementptr inbounds %struct.Node, %struct.Node* %310, i32 0, i32 22
  %312 = load %struct.Node*, %struct.Node** %311, align 16
  %313 = load %struct.Node*, %struct.Node** %13, align 8
  %314 = getelementptr inbounds %struct.Node, %struct.Node* %313, i32 0, i32 22
  store %struct.Node* %312, %struct.Node** %314, align 16
  %315 = load %struct.Node*, %struct.Node** %13, align 8
  %316 = load %struct.Node*, %struct.Node** @current_switch, align 8
  %317 = getelementptr inbounds %struct.Node, %struct.Node* %316, i32 0, i32 22
  store %struct.Node* %315, %struct.Node** %317, align 16
  %318 = load %struct.Node*, %struct.Node** %13, align 8
  store %struct.Node* %318, %struct.Node** %3, align 8
  br label %704

319:                                              ; preds = %259
  %320 = load %struct.Token*, %struct.Token** %5, align 8
  %321 = call zeroext i1 @equal(%struct.Token* noundef %320, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.195, i64 0, i64 0))
  br i1 %321, label %322, label %346

322:                                              ; preds = %319
  %323 = load %struct.Node*, %struct.Node** @current_switch, align 8
  %324 = icmp ne %struct.Node* %323, null
  br i1 %324, label %327, label %325

325:                                              ; preds = %322
  %326 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %326, i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @.str.196, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

327:                                              ; preds = %322
  %328 = load %struct.Token*, %struct.Token** %5, align 8
  %329 = call %struct.Node* @new_node(i32 noundef 31, %struct.Token* noundef %328)
  store %struct.Node* %329, %struct.Node** %16, align 8
  %330 = load %struct.Token*, %struct.Token** %5, align 8
  %331 = getelementptr inbounds %struct.Token, %struct.Token* %330, i32 0, i32 1
  %332 = load %struct.Token*, %struct.Token** %331, align 8
  %333 = call %struct.Token* @skip(%struct.Token* noundef %332, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  store %struct.Token* %333, %struct.Token** %5, align 8
  %334 = call i8* @new_unique_name()
  %335 = load %struct.Node*, %struct.Node** %16, align 8
  %336 = getelementptr inbounds %struct.Node, %struct.Node* %335, i32 0, i32 19
  store i8* %334, i8** %336, align 8
  %337 = load %struct.Token**, %struct.Token*** %4, align 8
  %338 = load %struct.Token*, %struct.Token** %5, align 8
  %339 = call %struct.Node* @stmt(%struct.Token** noundef %337, %struct.Token* noundef %338)
  %340 = load %struct.Node*, %struct.Node** %16, align 8
  %341 = getelementptr inbounds %struct.Node, %struct.Node* %340, i32 0, i32 4
  store %struct.Node* %339, %struct.Node** %341, align 16
  %342 = load %struct.Node*, %struct.Node** %16, align 8
  %343 = load %struct.Node*, %struct.Node** @current_switch, align 8
  %344 = getelementptr inbounds %struct.Node, %struct.Node* %343, i32 0, i32 23
  store %struct.Node* %342, %struct.Node** %344, align 8
  %345 = load %struct.Node*, %struct.Node** %16, align 8
  store %struct.Node* %345, %struct.Node** %3, align 8
  br label %704

346:                                              ; preds = %319
  %347 = load %struct.Token*, %struct.Token** %5, align 8
  %348 = call zeroext i1 @equal(%struct.Token* noundef %347, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.197, i64 0, i64 0))
  br i1 %348, label %349, label %489

349:                                              ; preds = %346
  %350 = load %struct.Token*, %struct.Token** %5, align 8
  %351 = call %struct.Node* @new_node(i32 noundef 28, %struct.Token* noundef %350)
  store %struct.Node* %351, %struct.Node** %17, align 8
  %352 = load %struct.Token*, %struct.Token** %5, align 8
  %353 = getelementptr inbounds %struct.Token, %struct.Token* %352, i32 0, i32 1
  %354 = load %struct.Token*, %struct.Token** %353, align 8
  %355 = call %struct.Token* @skip(%struct.Token* noundef %354, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %355, %struct.Token** %5, align 8
  call void @enter_scope()
  %356 = load i8*, i8** @brk_label, align 8
  store i8* %356, i8** %18, align 8
  %357 = load i8*, i8** @cont_label, align 8
  store i8* %357, i8** %19, align 8
  %358 = call i8* @new_unique_name()
  %359 = load %struct.Node*, %struct.Node** %17, align 8
  %360 = getelementptr inbounds %struct.Node, %struct.Node* %359, i32 0, i32 11
  store i8* %358, i8** %360, align 8
  store i8* %358, i8** @brk_label, align 8
  %361 = call i8* @new_unique_name()
  %362 = load %struct.Node*, %struct.Node** %17, align 8
  %363 = getelementptr inbounds %struct.Node, %struct.Node* %362, i32 0, i32 12
  store i8* %361, i8** %363, align 16
  store i8* %361, i8** @cont_label, align 8
  %364 = load %struct.Token*, %struct.Token** %5, align 8
  %365 = call zeroext i1 @is_typename(%struct.Token* noundef %364)
  br i1 %365, label %366, label %374

366:                                              ; preds = %349
  %367 = load %struct.Token*, %struct.Token** %5, align 8
  %368 = call %struct.Type* @declspec(%struct.Token** noundef %5, %struct.Token* noundef %367, %struct.VarAttr* noundef null)
  store %struct.Type* %368, %struct.Type** %20, align 8
  %369 = load %struct.Token*, %struct.Token** %5, align 8
  %370 = load %struct.Type*, %struct.Type** %20, align 8
  %371 = call %struct.Node* @declaration(%struct.Token** noundef %5, %struct.Token* noundef %369, %struct.Type* noundef %370, %struct.VarAttr* noundef null)
  %372 = load %struct.Node*, %struct.Node** %17, align 8
  %373 = getelementptr inbounds %struct.Node, %struct.Node* %372, i32 0, i32 9
  store %struct.Node* %371, %struct.Node** %373, align 8
  br label %379

374:                                              ; preds = %349
  %375 = load %struct.Token*, %struct.Token** %5, align 8
  %376 = call %struct.Node* @expr_stmt(%struct.Token** noundef %5, %struct.Token* noundef %375)
  %377 = load %struct.Node*, %struct.Node** %17, align 8
  %378 = getelementptr inbounds %struct.Node, %struct.Node* %377, i32 0, i32 9
  store %struct.Node* %376, %struct.Node** %378, align 8
  br label %379

379:                                              ; preds = %374, %366
  %380 = load %struct.Token*, %struct.Token** %5, align 8
  %381 = call zeroext i1 @equal(%struct.Token* noundef %380, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  br i1 %381, label %414, label %382

382:                                              ; preds = %379
  %383 = load %struct.Token*, %struct.Token** %5, align 8
  %384 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %383)
  %385 = load %struct.Node*, %struct.Node** %17, align 8
  %386 = getelementptr inbounds %struct.Node, %struct.Node* %385, i32 0, i32 6
  store %struct.Node* %384, %struct.Node** %386, align 16
  %387 = load i8, i8* @isDotfile, align 1
  %388 = trunc i8 %387 to i1
  br i1 %388, label %389, label %413

389:                                              ; preds = %382
  %390 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %391 = icmp ne %struct._IO_FILE* %390, null
  br i1 %391, label %392, label %413

392:                                              ; preds = %389
  %393 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %394 = load %struct.Node*, %struct.Node** %17, align 8
  %395 = getelementptr inbounds %struct.Node, %struct.Node* %394, i32 0, i32 0
  %396 = load i32, i32* %395, align 16
  %397 = call i8* @nodekind2str(i32 noundef %396)
  %398 = load %struct.Node*, %struct.Node** %17, align 8
  %399 = getelementptr inbounds %struct.Node, %struct.Node* %398, i32 0, i32 36
  %400 = load i32, i32* %399, align 16
  %401 = load %struct.Node*, %struct.Node** %17, align 8
  %402 = getelementptr inbounds %struct.Node, %struct.Node* %401, i32 0, i32 6
  %403 = load %struct.Node*, %struct.Node** %402, align 16
  %404 = getelementptr inbounds %struct.Node, %struct.Node* %403, i32 0, i32 0
  %405 = load i32, i32* %404, align 16
  %406 = call i8* @nodekind2str(i32 noundef %405)
  %407 = load %struct.Node*, %struct.Node** %17, align 8
  %408 = getelementptr inbounds %struct.Node, %struct.Node* %407, i32 0, i32 6
  %409 = load %struct.Node*, %struct.Node** %408, align 16
  %410 = getelementptr inbounds %struct.Node, %struct.Node* %409, i32 0, i32 36
  %411 = load i32, i32* %410, align 16
  %412 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %393, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %397, i32 noundef %400, i8* noundef %406, i32 noundef %411)
  br label %413

413:                                              ; preds = %392, %389, %382
  br label %414

414:                                              ; preds = %413, %379
  %415 = load %struct.Token*, %struct.Token** %5, align 8
  %416 = call %struct.Token* @skip(%struct.Token* noundef %415, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  store %struct.Token* %416, %struct.Token** %5, align 8
  %417 = load %struct.Token*, %struct.Token** %5, align 8
  %418 = call zeroext i1 @equal(%struct.Token* noundef %417, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  br i1 %418, label %451, label %419

419:                                              ; preds = %414
  %420 = load %struct.Token*, %struct.Token** %5, align 8
  %421 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %420)
  %422 = load %struct.Node*, %struct.Node** %17, align 8
  %423 = getelementptr inbounds %struct.Node, %struct.Node* %422, i32 0, i32 10
  store %struct.Node* %421, %struct.Node** %423, align 16
  %424 = load i8, i8* @isDotfile, align 1
  %425 = trunc i8 %424 to i1
  br i1 %425, label %426, label %450

426:                                              ; preds = %419
  %427 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %428 = icmp ne %struct._IO_FILE* %427, null
  br i1 %428, label %429, label %450

429:                                              ; preds = %426
  %430 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %431 = load %struct.Node*, %struct.Node** %17, align 8
  %432 = getelementptr inbounds %struct.Node, %struct.Node* %431, i32 0, i32 0
  %433 = load i32, i32* %432, align 16
  %434 = call i8* @nodekind2str(i32 noundef %433)
  %435 = load %struct.Node*, %struct.Node** %17, align 8
  %436 = getelementptr inbounds %struct.Node, %struct.Node* %435, i32 0, i32 36
  %437 = load i32, i32* %436, align 16
  %438 = load %struct.Node*, %struct.Node** %17, align 8
  %439 = getelementptr inbounds %struct.Node, %struct.Node* %438, i32 0, i32 10
  %440 = load %struct.Node*, %struct.Node** %439, align 16
  %441 = getelementptr inbounds %struct.Node, %struct.Node* %440, i32 0, i32 0
  %442 = load i32, i32* %441, align 16
  %443 = call i8* @nodekind2str(i32 noundef %442)
  %444 = load %struct.Node*, %struct.Node** %17, align 8
  %445 = getelementptr inbounds %struct.Node, %struct.Node* %444, i32 0, i32 10
  %446 = load %struct.Node*, %struct.Node** %445, align 16
  %447 = getelementptr inbounds %struct.Node, %struct.Node* %446, i32 0, i32 36
  %448 = load i32, i32* %447, align 16
  %449 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %430, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %434, i32 noundef %437, i8* noundef %443, i32 noundef %448)
  br label %450

450:                                              ; preds = %429, %426, %419
  br label %451

451:                                              ; preds = %450, %414
  %452 = load %struct.Token*, %struct.Token** %5, align 8
  %453 = call %struct.Token* @skip(%struct.Token* noundef %452, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %453, %struct.Token** %5, align 8
  %454 = load %struct.Token**, %struct.Token*** %4, align 8
  %455 = load %struct.Token*, %struct.Token** %5, align 8
  %456 = call %struct.Node* @stmt(%struct.Token** noundef %454, %struct.Token* noundef %455)
  %457 = load %struct.Node*, %struct.Node** %17, align 8
  %458 = getelementptr inbounds %struct.Node, %struct.Node* %457, i32 0, i32 7
  store %struct.Node* %456, %struct.Node** %458, align 8
  %459 = load i8, i8* @isDotfile, align 1
  %460 = trunc i8 %459 to i1
  br i1 %460, label %461, label %485

461:                                              ; preds = %451
  %462 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %463 = icmp ne %struct._IO_FILE* %462, null
  br i1 %463, label %464, label %485

464:                                              ; preds = %461
  %465 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %466 = load %struct.Node*, %struct.Node** %17, align 8
  %467 = getelementptr inbounds %struct.Node, %struct.Node* %466, i32 0, i32 0
  %468 = load i32, i32* %467, align 16
  %469 = call i8* @nodekind2str(i32 noundef %468)
  %470 = load %struct.Node*, %struct.Node** %17, align 8
  %471 = getelementptr inbounds %struct.Node, %struct.Node* %470, i32 0, i32 36
  %472 = load i32, i32* %471, align 16
  %473 = load %struct.Node*, %struct.Node** %17, align 8
  %474 = getelementptr inbounds %struct.Node, %struct.Node* %473, i32 0, i32 7
  %475 = load %struct.Node*, %struct.Node** %474, align 8
  %476 = getelementptr inbounds %struct.Node, %struct.Node* %475, i32 0, i32 0
  %477 = load i32, i32* %476, align 16
  %478 = call i8* @nodekind2str(i32 noundef %477)
  %479 = load %struct.Node*, %struct.Node** %17, align 8
  %480 = getelementptr inbounds %struct.Node, %struct.Node* %479, i32 0, i32 7
  %481 = load %struct.Node*, %struct.Node** %480, align 8
  %482 = getelementptr inbounds %struct.Node, %struct.Node* %481, i32 0, i32 36
  %483 = load i32, i32* %482, align 16
  %484 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %465, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %469, i32 noundef %472, i8* noundef %478, i32 noundef %483)
  br label %485

485:                                              ; preds = %464, %461, %451
  call void @leave_scope()
  %486 = load i8*, i8** %18, align 8
  store i8* %486, i8** @brk_label, align 8
  %487 = load i8*, i8** %19, align 8
  store i8* %487, i8** @cont_label, align 8
  %488 = load %struct.Node*, %struct.Node** %17, align 8
  store %struct.Node* %488, %struct.Node** %3, align 8
  br label %704

489:                                              ; preds = %346
  %490 = load %struct.Token*, %struct.Token** %5, align 8
  %491 = call zeroext i1 @equal(%struct.Token* noundef %490, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.198, i64 0, i64 0))
  br i1 %491, label %492, label %521

492:                                              ; preds = %489
  %493 = load %struct.Token*, %struct.Token** %5, align 8
  %494 = call %struct.Node* @new_node(i32 noundef 28, %struct.Token* noundef %493)
  store %struct.Node* %494, %struct.Node** %21, align 8
  %495 = load %struct.Token*, %struct.Token** %5, align 8
  %496 = getelementptr inbounds %struct.Token, %struct.Token* %495, i32 0, i32 1
  %497 = load %struct.Token*, %struct.Token** %496, align 8
  %498 = call %struct.Token* @skip(%struct.Token* noundef %497, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %498, %struct.Token** %5, align 8
  %499 = load %struct.Token*, %struct.Token** %5, align 8
  %500 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %499)
  %501 = load %struct.Node*, %struct.Node** %21, align 8
  %502 = getelementptr inbounds %struct.Node, %struct.Node* %501, i32 0, i32 6
  store %struct.Node* %500, %struct.Node** %502, align 16
  %503 = load %struct.Token*, %struct.Token** %5, align 8
  %504 = call %struct.Token* @skip(%struct.Token* noundef %503, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %504, %struct.Token** %5, align 8
  %505 = load i8*, i8** @brk_label, align 8
  store i8* %505, i8** %22, align 8
  %506 = load i8*, i8** @cont_label, align 8
  store i8* %506, i8** %23, align 8
  %507 = call i8* @new_unique_name()
  %508 = load %struct.Node*, %struct.Node** %21, align 8
  %509 = getelementptr inbounds %struct.Node, %struct.Node* %508, i32 0, i32 11
  store i8* %507, i8** %509, align 8
  store i8* %507, i8** @brk_label, align 8
  %510 = call i8* @new_unique_name()
  %511 = load %struct.Node*, %struct.Node** %21, align 8
  %512 = getelementptr inbounds %struct.Node, %struct.Node* %511, i32 0, i32 12
  store i8* %510, i8** %512, align 16
  store i8* %510, i8** @cont_label, align 8
  %513 = load %struct.Token**, %struct.Token*** %4, align 8
  %514 = load %struct.Token*, %struct.Token** %5, align 8
  %515 = call %struct.Node* @stmt(%struct.Token** noundef %513, %struct.Token* noundef %514)
  %516 = load %struct.Node*, %struct.Node** %21, align 8
  %517 = getelementptr inbounds %struct.Node, %struct.Node* %516, i32 0, i32 7
  store %struct.Node* %515, %struct.Node** %517, align 8
  %518 = load i8*, i8** %22, align 8
  store i8* %518, i8** @brk_label, align 8
  %519 = load i8*, i8** %23, align 8
  store i8* %519, i8** @cont_label, align 8
  %520 = load %struct.Node*, %struct.Node** %21, align 8
  store %struct.Node* %520, %struct.Node** %3, align 8
  br label %704

521:                                              ; preds = %489
  %522 = load %struct.Token*, %struct.Token** %5, align 8
  %523 = call zeroext i1 @equal(%struct.Token* noundef %522, i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.199, i64 0, i64 0))
  br i1 %523, label %524, label %557

524:                                              ; preds = %521
  %525 = load %struct.Token*, %struct.Token** %5, align 8
  %526 = call %struct.Node* @new_node(i32 noundef 29, %struct.Token* noundef %525)
  store %struct.Node* %526, %struct.Node** %24, align 8
  %527 = load i8*, i8** @brk_label, align 8
  store i8* %527, i8** %25, align 8
  %528 = load i8*, i8** @cont_label, align 8
  store i8* %528, i8** %26, align 8
  %529 = call i8* @new_unique_name()
  %530 = load %struct.Node*, %struct.Node** %24, align 8
  %531 = getelementptr inbounds %struct.Node, %struct.Node* %530, i32 0, i32 11
  store i8* %529, i8** %531, align 8
  store i8* %529, i8** @brk_label, align 8
  %532 = call i8* @new_unique_name()
  %533 = load %struct.Node*, %struct.Node** %24, align 8
  %534 = getelementptr inbounds %struct.Node, %struct.Node* %533, i32 0, i32 12
  store i8* %532, i8** %534, align 16
  store i8* %532, i8** @cont_label, align 8
  %535 = load %struct.Token*, %struct.Token** %5, align 8
  %536 = getelementptr inbounds %struct.Token, %struct.Token* %535, i32 0, i32 1
  %537 = load %struct.Token*, %struct.Token** %536, align 8
  %538 = call %struct.Node* @stmt(%struct.Token** noundef %5, %struct.Token* noundef %537)
  %539 = load %struct.Node*, %struct.Node** %24, align 8
  %540 = getelementptr inbounds %struct.Node, %struct.Node* %539, i32 0, i32 7
  store %struct.Node* %538, %struct.Node** %540, align 8
  %541 = load i8*, i8** %25, align 8
  store i8* %541, i8** @brk_label, align 8
  %542 = load i8*, i8** %26, align 8
  store i8* %542, i8** @cont_label, align 8
  %543 = load %struct.Token*, %struct.Token** %5, align 8
  %544 = call %struct.Token* @skip(%struct.Token* noundef %543, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.198, i64 0, i64 0))
  store %struct.Token* %544, %struct.Token** %5, align 8
  %545 = load %struct.Token*, %struct.Token** %5, align 8
  %546 = call %struct.Token* @skip(%struct.Token* noundef %545, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %546, %struct.Token** %5, align 8
  %547 = load %struct.Token*, %struct.Token** %5, align 8
  %548 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %547)
  %549 = load %struct.Node*, %struct.Node** %24, align 8
  %550 = getelementptr inbounds %struct.Node, %struct.Node* %549, i32 0, i32 6
  store %struct.Node* %548, %struct.Node** %550, align 16
  %551 = load %struct.Token*, %struct.Token** %5, align 8
  %552 = call %struct.Token* @skip(%struct.Token* noundef %551, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %552, %struct.Token** %5, align 8
  %553 = load %struct.Token*, %struct.Token** %5, align 8
  %554 = call %struct.Token* @skip(%struct.Token* noundef %553, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %555 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %554, %struct.Token** %555, align 8
  %556 = load %struct.Node*, %struct.Node** %24, align 8
  store %struct.Node* %556, %struct.Node** %3, align 8
  br label %704

557:                                              ; preds = %521
  %558 = load %struct.Token*, %struct.Token** %5, align 8
  %559 = call zeroext i1 @equal(%struct.Token* noundef %558, i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.200, i64 0, i64 0))
  br i1 %559, label %563, label %560

560:                                              ; preds = %557
  %561 = load %struct.Token*, %struct.Token** %5, align 8
  %562 = call zeroext i1 @equal(%struct.Token* noundef %561, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.201, i64 0, i64 0))
  br i1 %562, label %563, label %567

563:                                              ; preds = %560, %557
  %564 = load %struct.Token**, %struct.Token*** %4, align 8
  %565 = load %struct.Token*, %struct.Token** %5, align 8
  %566 = call %struct.Node* @asm_stmt(%struct.Token** noundef %564, %struct.Token* noundef %565)
  store %struct.Node* %566, %struct.Node** %3, align 8
  br label %704

567:                                              ; preds = %560
  %568 = load %struct.Token*, %struct.Token** %5, align 8
  %569 = call zeroext i1 @equal(%struct.Token* noundef %568, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.202, i64 0, i64 0))
  br i1 %569, label %570, label %611

570:                                              ; preds = %567
  %571 = load %struct.Token*, %struct.Token** %5, align 8
  %572 = getelementptr inbounds %struct.Token, %struct.Token* %571, i32 0, i32 1
  %573 = load %struct.Token*, %struct.Token** %572, align 8
  %574 = call zeroext i1 @equal(%struct.Token* noundef %573, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.82, i64 0, i64 0))
  br i1 %574, label %575, label %590

575:                                              ; preds = %570
  %576 = load %struct.Token*, %struct.Token** %5, align 8
  %577 = call %struct.Node* @new_node(i32 noundef 34, %struct.Token* noundef %576)
  store %struct.Node* %577, %struct.Node** %27, align 8
  %578 = load %struct.Token*, %struct.Token** %5, align 8
  %579 = getelementptr inbounds %struct.Token, %struct.Token* %578, i32 0, i32 1
  %580 = load %struct.Token*, %struct.Token** %579, align 8
  %581 = getelementptr inbounds %struct.Token, %struct.Token* %580, i32 0, i32 1
  %582 = load %struct.Token*, %struct.Token** %581, align 8
  %583 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %582)
  %584 = load %struct.Node*, %struct.Node** %27, align 8
  %585 = getelementptr inbounds %struct.Node, %struct.Node* %584, i32 0, i32 4
  store %struct.Node* %583, %struct.Node** %585, align 16
  %586 = load %struct.Token*, %struct.Token** %5, align 8
  %587 = call %struct.Token* @skip(%struct.Token* noundef %586, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %588 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %587, %struct.Token** %588, align 8
  %589 = load %struct.Node*, %struct.Node** %27, align 8
  store %struct.Node* %589, %struct.Node** %3, align 8
  br label %704

590:                                              ; preds = %570
  %591 = load %struct.Token*, %struct.Token** %5, align 8
  %592 = call %struct.Node* @new_node(i32 noundef 33, %struct.Token* noundef %591)
  store %struct.Node* %592, %struct.Node** %28, align 8
  %593 = load %struct.Token*, %struct.Token** %5, align 8
  %594 = getelementptr inbounds %struct.Token, %struct.Token* %593, i32 0, i32 1
  %595 = load %struct.Token*, %struct.Token** %594, align 8
  %596 = call i8* @get_ident(%struct.Token* noundef %595)
  %597 = load %struct.Node*, %struct.Node** %28, align 8
  %598 = getelementptr inbounds %struct.Node, %struct.Node* %597, i32 0, i32 19
  store i8* %596, i8** %598, align 8
  %599 = load %struct.Node*, %struct.Node** @gotos, align 8
  %600 = load %struct.Node*, %struct.Node** %28, align 8
  %601 = getelementptr inbounds %struct.Node, %struct.Node* %600, i32 0, i32 21
  store %struct.Node* %599, %struct.Node** %601, align 8
  %602 = load %struct.Node*, %struct.Node** %28, align 8
  store %struct.Node* %602, %struct.Node** @gotos, align 8
  %603 = load %struct.Token*, %struct.Token** %5, align 8
  %604 = getelementptr inbounds %struct.Token, %struct.Token* %603, i32 0, i32 1
  %605 = load %struct.Token*, %struct.Token** %604, align 8
  %606 = getelementptr inbounds %struct.Token, %struct.Token* %605, i32 0, i32 1
  %607 = load %struct.Token*, %struct.Token** %606, align 8
  %608 = call %struct.Token* @skip(%struct.Token* noundef %607, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %609 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %608, %struct.Token** %609, align 8
  %610 = load %struct.Node*, %struct.Node** %28, align 8
  store %struct.Node* %610, %struct.Node** %3, align 8
  br label %704

611:                                              ; preds = %567
  %612 = load %struct.Token*, %struct.Token** %5, align 8
  %613 = call zeroext i1 @equal(%struct.Token* noundef %612, i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.203, i64 0, i64 0))
  br i1 %613, label %614, label %631

614:                                              ; preds = %611
  %615 = load i8*, i8** @brk_label, align 8
  %616 = icmp ne i8* %615, null
  br i1 %616, label %619, label %617

617:                                              ; preds = %614
  %618 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %618, i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.204, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

619:                                              ; preds = %614
  %620 = load %struct.Token*, %struct.Token** %5, align 8
  %621 = call %struct.Node* @new_node(i32 noundef 33, %struct.Token* noundef %620)
  store %struct.Node* %621, %struct.Node** %29, align 8
  %622 = load i8*, i8** @brk_label, align 8
  %623 = load %struct.Node*, %struct.Node** %29, align 8
  %624 = getelementptr inbounds %struct.Node, %struct.Node* %623, i32 0, i32 20
  store i8* %622, i8** %624, align 16
  %625 = load %struct.Token*, %struct.Token** %5, align 8
  %626 = getelementptr inbounds %struct.Token, %struct.Token* %625, i32 0, i32 1
  %627 = load %struct.Token*, %struct.Token** %626, align 8
  %628 = call %struct.Token* @skip(%struct.Token* noundef %627, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %629 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %628, %struct.Token** %629, align 8
  %630 = load %struct.Node*, %struct.Node** %29, align 8
  store %struct.Node* %630, %struct.Node** %3, align 8
  br label %704

631:                                              ; preds = %611
  %632 = load %struct.Token*, %struct.Token** %5, align 8
  %633 = call zeroext i1 @equal(%struct.Token* noundef %632, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.205, i64 0, i64 0))
  br i1 %633, label %634, label %651

634:                                              ; preds = %631
  %635 = load i8*, i8** @cont_label, align 8
  %636 = icmp ne i8* %635, null
  br i1 %636, label %639, label %637

637:                                              ; preds = %634
  %638 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %638, i8* noundef getelementptr inbounds ([29 x i8], [29 x i8]* @.str.206, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

639:                                              ; preds = %634
  %640 = load %struct.Token*, %struct.Token** %5, align 8
  %641 = call %struct.Node* @new_node(i32 noundef 33, %struct.Token* noundef %640)
  store %struct.Node* %641, %struct.Node** %30, align 8
  %642 = load i8*, i8** @cont_label, align 8
  %643 = load %struct.Node*, %struct.Node** %30, align 8
  %644 = getelementptr inbounds %struct.Node, %struct.Node* %643, i32 0, i32 20
  store i8* %642, i8** %644, align 16
  %645 = load %struct.Token*, %struct.Token** %5, align 8
  %646 = getelementptr inbounds %struct.Token, %struct.Token* %645, i32 0, i32 1
  %647 = load %struct.Token*, %struct.Token** %646, align 8
  %648 = call %struct.Token* @skip(%struct.Token* noundef %647, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %649 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %648, %struct.Token** %649, align 8
  %650 = load %struct.Node*, %struct.Node** %30, align 8
  store %struct.Node* %650, %struct.Node** %3, align 8
  br label %704

651:                                              ; preds = %631
  %652 = load %struct.Token*, %struct.Token** %5, align 8
  %653 = getelementptr inbounds %struct.Token, %struct.Token* %652, i32 0, i32 0
  %654 = load i32, i32* %653, align 16
  %655 = icmp eq i32 %654, 0
  br i1 %655, label %656, label %691

656:                                              ; preds = %651
  %657 = load %struct.Token*, %struct.Token** %5, align 8
  %658 = getelementptr inbounds %struct.Token, %struct.Token* %657, i32 0, i32 1
  %659 = load %struct.Token*, %struct.Token** %658, align 8
  %660 = call zeroext i1 @equal(%struct.Token* noundef %659, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  br i1 %660, label %661, label %691

661:                                              ; preds = %656
  %662 = load %struct.Token*, %struct.Token** %5, align 8
  %663 = call %struct.Node* @new_node(i32 noundef 35, %struct.Token* noundef %662)
  store %struct.Node* %663, %struct.Node** %31, align 8
  %664 = load %struct.Token*, %struct.Token** %5, align 8
  %665 = getelementptr inbounds %struct.Token, %struct.Token* %664, i32 0, i32 4
  %666 = load i8*, i8** %665, align 16
  %667 = load %struct.Token*, %struct.Token** %5, align 8
  %668 = getelementptr inbounds %struct.Token, %struct.Token* %667, i32 0, i32 5
  %669 = load i32, i32* %668, align 8
  %670 = sext i32 %669 to i64
  %671 = call noalias i8* @strndup(i8* noundef %666, i64 noundef %670) #8
  %672 = load %struct.Node*, %struct.Node** %31, align 8
  %673 = getelementptr inbounds %struct.Node, %struct.Node* %672, i32 0, i32 19
  store i8* %671, i8** %673, align 8
  %674 = call i8* @new_unique_name()
  %675 = load %struct.Node*, %struct.Node** %31, align 8
  %676 = getelementptr inbounds %struct.Node, %struct.Node* %675, i32 0, i32 20
  store i8* %674, i8** %676, align 16
  %677 = load %struct.Token**, %struct.Token*** %4, align 8
  %678 = load %struct.Token*, %struct.Token** %5, align 8
  %679 = getelementptr inbounds %struct.Token, %struct.Token* %678, i32 0, i32 1
  %680 = load %struct.Token*, %struct.Token** %679, align 8
  %681 = getelementptr inbounds %struct.Token, %struct.Token* %680, i32 0, i32 1
  %682 = load %struct.Token*, %struct.Token** %681, align 8
  %683 = call %struct.Node* @stmt(%struct.Token** noundef %677, %struct.Token* noundef %682)
  %684 = load %struct.Node*, %struct.Node** %31, align 8
  %685 = getelementptr inbounds %struct.Node, %struct.Node* %684, i32 0, i32 4
  store %struct.Node* %683, %struct.Node** %685, align 16
  %686 = load %struct.Node*, %struct.Node** @labels, align 8
  %687 = load %struct.Node*, %struct.Node** %31, align 8
  %688 = getelementptr inbounds %struct.Node, %struct.Node* %687, i32 0, i32 21
  store %struct.Node* %686, %struct.Node** %688, align 8
  %689 = load %struct.Node*, %struct.Node** %31, align 8
  store %struct.Node* %689, %struct.Node** @labels, align 8
  %690 = load %struct.Node*, %struct.Node** %31, align 8
  store %struct.Node* %690, %struct.Node** %3, align 8
  br label %704

691:                                              ; preds = %656, %651
  %692 = load %struct.Token*, %struct.Token** %5, align 8
  %693 = call zeroext i1 @equal(%struct.Token* noundef %692, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %693, label %694, label %700

694:                                              ; preds = %691
  %695 = load %struct.Token**, %struct.Token*** %4, align 8
  %696 = load %struct.Token*, %struct.Token** %5, align 8
  %697 = getelementptr inbounds %struct.Token, %struct.Token* %696, i32 0, i32 1
  %698 = load %struct.Token*, %struct.Token** %697, align 8
  %699 = call %struct.Node* @compound_stmt(%struct.Token** noundef %695, %struct.Token* noundef %698)
  store %struct.Node* %699, %struct.Node** %3, align 8
  br label %704

700:                                              ; preds = %691
  %701 = load %struct.Token**, %struct.Token*** %4, align 8
  %702 = load %struct.Token*, %struct.Token** %5, align 8
  %703 = call %struct.Node* @expr_stmt(%struct.Token** noundef %701, %struct.Token* noundef %702)
  store %struct.Node* %703, %struct.Node** %3, align 8
  br label %704

704:                                              ; preds = %700, %694, %661, %639, %619, %590, %575, %563, %524, %492, %485, %327, %291, %232, %225, %110, %54
  %705 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %705
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @leave_scope() #0 {
  %1 = load %struct.Scope*, %struct.Scope** @scope, align 8
  %2 = getelementptr inbounds %struct.Scope, %struct.Scope* %1, i32 0, i32 0
  %3 = load %struct.Scope*, %struct.Scope** %2, align 8
  store %struct.Scope* %3, %struct.Scope** @scope, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_vla_ptr(%struct.Obj* noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Obj*, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  store %struct.Obj* %0, %struct.Obj** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load %struct.Token*, %struct.Token** %4, align 8
  %7 = call %struct.Node* @new_node(i32 noundef 41, %struct.Token* noundef %6)
  store %struct.Node* %7, %struct.Node** %5, align 8
  %8 = load %struct.Obj*, %struct.Obj** %3, align 8
  %9 = load %struct.Node*, %struct.Node** %5, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 33
  store %struct.Obj* %8, %struct.Obj** %10, align 8
  %11 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %11
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_alloca(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  %3 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %2, align 8
  %4 = load %struct.Obj*, %struct.Obj** @builtin_alloca, align 8
  %5 = load %struct.Node*, %struct.Node** %2, align 8
  %6 = getelementptr inbounds %struct.Node, %struct.Node* %5, i32 0, i32 3
  %7 = load %struct.Token*, %struct.Token** %6, align 8
  %8 = call %struct.Node* @new_var_node(%struct.Obj* noundef %4, %struct.Token* noundef %7)
  %9 = load %struct.Node*, %struct.Node** %2, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 3
  %11 = load %struct.Token*, %struct.Token** %10, align 8
  %12 = call %struct.Node* @new_unary(i32 noundef 37, %struct.Node* noundef %8, %struct.Token* noundef %11)
  store %struct.Node* %12, %struct.Node** %3, align 8
  %13 = load %struct.Obj*, %struct.Obj** @builtin_alloca, align 8
  %14 = getelementptr inbounds %struct.Obj, %struct.Obj* %13, i32 0, i32 3
  %15 = load %struct.Type*, %struct.Type** %14, align 8
  %16 = load %struct.Node*, %struct.Node** %3, align 8
  %17 = getelementptr inbounds %struct.Node, %struct.Node* %16, i32 0, i32 15
  store %struct.Type* %15, %struct.Type** %17, align 8
  %18 = load %struct.Obj*, %struct.Obj** @builtin_alloca, align 8
  %19 = getelementptr inbounds %struct.Obj, %struct.Obj* %18, i32 0, i32 3
  %20 = load %struct.Type*, %struct.Type** %19, align 8
  %21 = getelementptr inbounds %struct.Type, %struct.Type* %20, i32 0, i32 17
  %22 = load %struct.Type*, %struct.Type** %21, align 8
  %23 = load %struct.Node*, %struct.Node** %3, align 8
  %24 = getelementptr inbounds %struct.Node, %struct.Node* %23, i32 0, i32 2
  store %struct.Type* %22, %struct.Type** %24, align 16
  %25 = load %struct.Node*, %struct.Node** %2, align 8
  %26 = load %struct.Node*, %struct.Node** %3, align 8
  %27 = getelementptr inbounds %struct.Node, %struct.Node* %26, i32 0, i32 16
  store %struct.Node* %25, %struct.Node** %27, align 16
  %28 = load %struct.Node*, %struct.Node** %2, align 8
  call void @add_type(%struct.Node* noundef %28)
  %29 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %29
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @expr_stmt(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %7 = load %struct.Token*, %struct.Token** %5, align 8
  %8 = call zeroext i1 @equal(%struct.Token* noundef %7, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  br i1 %8, label %9, label %16

9:                                                ; preds = %2
  %10 = load %struct.Token*, %struct.Token** %5, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 1
  %12 = load %struct.Token*, %struct.Token** %11, align 8
  %13 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %12, %struct.Token** %13, align 8
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  %15 = call %struct.Node* @new_node(i32 noundef 32, %struct.Token* noundef %14)
  store %struct.Node* %15, %struct.Node** %3, align 8
  br label %54

16:                                               ; preds = %2
  %17 = load %struct.Token*, %struct.Token** %5, align 8
  %18 = call %struct.Node* @new_node(i32 noundef 38, %struct.Token* noundef %17)
  store %struct.Node* %18, %struct.Node** %6, align 8
  %19 = load %struct.Token*, %struct.Token** %5, align 8
  %20 = call %struct.Node* @expr(%struct.Token** noundef %5, %struct.Token* noundef %19)
  %21 = load %struct.Node*, %struct.Node** %6, align 8
  %22 = getelementptr inbounds %struct.Node, %struct.Node* %21, i32 0, i32 4
  store %struct.Node* %20, %struct.Node** %22, align 16
  %23 = load i8, i8* @isDotfile, align 1
  %24 = trunc i8 %23 to i1
  br i1 %24, label %25, label %49

25:                                               ; preds = %16
  %26 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %27 = icmp ne %struct._IO_FILE* %26, null
  br i1 %27, label %28, label %49

28:                                               ; preds = %25
  %29 = load %struct._IO_FILE*, %struct._IO_FILE** @dotf, align 8
  %30 = load %struct.Node*, %struct.Node** %6, align 8
  %31 = getelementptr inbounds %struct.Node, %struct.Node* %30, i32 0, i32 0
  %32 = load i32, i32* %31, align 16
  %33 = call i8* @nodekind2str(i32 noundef %32)
  %34 = load %struct.Node*, %struct.Node** %6, align 8
  %35 = getelementptr inbounds %struct.Node, %struct.Node* %34, i32 0, i32 36
  %36 = load i32, i32* %35, align 16
  %37 = load %struct.Node*, %struct.Node** %6, align 8
  %38 = getelementptr inbounds %struct.Node, %struct.Node* %37, i32 0, i32 4
  %39 = load %struct.Node*, %struct.Node** %38, align 16
  %40 = getelementptr inbounds %struct.Node, %struct.Node* %39, i32 0, i32 0
  %41 = load i32, i32* %40, align 16
  %42 = call i8* @nodekind2str(i32 noundef %41)
  %43 = load %struct.Node*, %struct.Node** %6, align 8
  %44 = getelementptr inbounds %struct.Node, %struct.Node* %43, i32 0, i32 4
  %45 = load %struct.Node*, %struct.Node** %44, align 16
  %46 = getelementptr inbounds %struct.Node, %struct.Node* %45, i32 0, i32 36
  %47 = load i32, i32* %46, align 16
  %48 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %29, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.131, i64 0, i64 0), i8* noundef %33, i32 noundef %36, i8* noundef %42, i32 noundef %47)
  br label %49

49:                                               ; preds = %28, %25, %16
  %50 = load %struct.Token*, %struct.Token** %5, align 8
  %51 = call %struct.Token* @skip(%struct.Token* noundef %50, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %52 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %51, %struct.Token** %52, align 8
  %53 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %53, %struct.Node** %3, align 8
  br label %54

54:                                               ; preds = %49, %9
  %55 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %55
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @asm_stmt(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %7 = load %struct.Token*, %struct.Token** %5, align 8
  %8 = call %struct.Node* @new_node(i32 noundef 45, %struct.Token* noundef %7)
  store %struct.Node* %8, %struct.Node** %6, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = getelementptr inbounds %struct.Token, %struct.Token* %9, i32 0, i32 1
  %11 = load %struct.Token*, %struct.Token** %10, align 8
  store %struct.Token* %11, %struct.Token** %5, align 8
  br label %12

12:                                               ; preds = %20, %2
  %13 = load %struct.Token*, %struct.Token** %5, align 8
  %14 = call zeroext i1 @equal(%struct.Token* noundef %13, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.104, i64 0, i64 0))
  br i1 %14, label %18, label %15

15:                                               ; preds = %12
  %16 = load %struct.Token*, %struct.Token** %5, align 8
  %17 = call zeroext i1 @equal(%struct.Token* noundef %16, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.114, i64 0, i64 0))
  br label %18

18:                                               ; preds = %15, %12
  %19 = phi i1 [ true, %12 ], [ %17, %15 ]
  br i1 %19, label %20, label %24

20:                                               ; preds = %18
  %21 = load %struct.Token*, %struct.Token** %5, align 8
  %22 = getelementptr inbounds %struct.Token, %struct.Token* %21, i32 0, i32 1
  %23 = load %struct.Token*, %struct.Token** %22, align 8
  store %struct.Token* %23, %struct.Token** %5, align 8
  br label %12, !llvm.loop !58

24:                                               ; preds = %18
  %25 = load %struct.Token*, %struct.Token** %5, align 8
  %26 = call %struct.Token* @skip(%struct.Token* noundef %25, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %26, %struct.Token** %5, align 8
  %27 = load %struct.Token*, %struct.Token** %5, align 8
  %28 = getelementptr inbounds %struct.Token, %struct.Token* %27, i32 0, i32 0
  %29 = load i32, i32* %28, align 16
  %30 = icmp ne i32 %29, 3
  br i1 %30, label %40, label %31

31:                                               ; preds = %24
  %32 = load %struct.Token*, %struct.Token** %5, align 8
  %33 = getelementptr inbounds %struct.Token, %struct.Token* %32, i32 0, i32 6
  %34 = load %struct.Type*, %struct.Type** %33, align 16
  %35 = getelementptr inbounds %struct.Type, %struct.Type* %34, i32 0, i32 8
  %36 = load %struct.Type*, %struct.Type** %35, align 8
  %37 = getelementptr inbounds %struct.Type, %struct.Type* %36, i32 0, i32 0
  %38 = load i32, i32* %37, align 8
  %39 = icmp ne i32 %38, 2
  br i1 %39, label %40, label %42

40:                                               ; preds = %31, %24
  %41 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %41, i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str.207, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

42:                                               ; preds = %31
  %43 = load %struct.Token*, %struct.Token** %5, align 8
  %44 = getelementptr inbounds %struct.Token, %struct.Token* %43, i32 0, i32 1
  %45 = load %struct.Token*, %struct.Token** %44, align 8
  %46 = call zeroext i1 @equal(%struct.Token* noundef %45, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  br i1 %46, label %47, label %62

47:                                               ; preds = %42
  %48 = load %struct.Node*, %struct.Node** %6, align 8
  %49 = load %struct.Token**, %struct.Token*** %4, align 8
  %50 = load %struct.Token*, %struct.Token** %5, align 8
  %51 = call i8* @extended_asm(%struct.Node* noundef %48, %struct.Token** noundef %49, %struct.Token* noundef %50)
  %52 = load %struct.Node*, %struct.Node** %6, align 8
  %53 = getelementptr inbounds %struct.Node, %struct.Node* %52, i32 0, i32 26
  store i8* %51, i8** %53, align 16
  %54 = load %struct.Node*, %struct.Node** %6, align 8
  %55 = getelementptr inbounds %struct.Node, %struct.Node* %54, i32 0, i32 26
  %56 = load i8*, i8** %55, align 16
  %57 = icmp ne i8* %56, null
  br i1 %57, label %60, label %58

58:                                               ; preds = %47
  %59 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %59, i8* noundef getelementptr inbounds ([68 x i8], [68 x i8]* @.str.208, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

60:                                               ; preds = %47
  %61 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %61, %struct.Node** %3, align 8
  br label %74

62:                                               ; preds = %42
  %63 = load %struct.Token*, %struct.Token** %5, align 8
  %64 = getelementptr inbounds %struct.Token, %struct.Token* %63, i32 0, i32 7
  %65 = load i8*, i8** %64, align 8
  %66 = load %struct.Node*, %struct.Node** %6, align 8
  %67 = getelementptr inbounds %struct.Node, %struct.Node* %66, i32 0, i32 26
  store i8* %65, i8** %67, align 16
  %68 = load %struct.Token*, %struct.Token** %5, align 8
  %69 = getelementptr inbounds %struct.Token, %struct.Token* %68, i32 0, i32 1
  %70 = load %struct.Token*, %struct.Token** %69, align 8
  %71 = call %struct.Token* @skip(%struct.Token* noundef %70, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %72 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %71, %struct.Token** %72, align 8
  %73 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %73, %struct.Node** %3, align 8
  br label %74

74:                                               ; preds = %62, %60
  %75 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %75
}

declare i8* @extended_asm(%struct.Node* noundef, %struct.Token** noundef, %struct.Token* noundef) #1

declare zeroext i1 @is_numeric(%struct.Type* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Node* @new_long(i64 noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Node*, align 8
  store i64 %0, i64* %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %6 = load %struct.Token*, %struct.Token** %4, align 8
  %7 = call %struct.Node* @new_node(i32 noundef 42, %struct.Token* noundef %6)
  store %struct.Node* %7, %struct.Node** %5, align 8
  %8 = load i64, i64* %3, align 8
  %9 = load %struct.Node*, %struct.Node** %5, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 34
  store i64 %8, i64* %10, align 16
  %11 = load %struct.Type*, %struct.Type** @ty_long, align 8
  %12 = load %struct.Node*, %struct.Node** %5, align 8
  %13 = getelementptr inbounds %struct.Node, %struct.Node* %12, i32 0, i32 2
  store %struct.Type* %11, %struct.Type** %13, align 16
  %14 = load %struct.Node*, %struct.Node** %5, align 8
  ret %struct.Node* %14
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @struct_decl(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca i32, align 4
  %8 = alloca %struct.Member*, align 8
  %9 = alloca i32, align 4
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %10 = load %struct.Token**, %struct.Token*** %4, align 8
  %11 = load %struct.Token*, %struct.Token** %5, align 8
  %12 = call %struct.Type* @struct_union_decl(%struct.Token** noundef %10, %struct.Token* noundef %11)
  store %struct.Type* %12, %struct.Type** %6, align 8
  %13 = load %struct.Type*, %struct.Type** %6, align 8
  %14 = getelementptr inbounds %struct.Type, %struct.Type* %13, i32 0, i32 0
  store i32 14, i32* %14, align 8
  %15 = load %struct.Type*, %struct.Type** %6, align 8
  %16 = getelementptr inbounds %struct.Type, %struct.Type* %15, i32 0, i32 1
  %17 = load i32, i32* %16, align 4
  %18 = icmp slt i32 %17, 0
  br i1 %18, label %19, label %21

19:                                               ; preds = %2
  %20 = load %struct.Type*, %struct.Type** %6, align 8
  store %struct.Type* %20, %struct.Type** %3, align 8
  br label %156

21:                                               ; preds = %2
  store i32 0, i32* %7, align 4
  %22 = load %struct.Type*, %struct.Type** %6, align 8
  %23 = getelementptr inbounds %struct.Type, %struct.Type* %22, i32 0, i32 14
  %24 = load %struct.Member*, %struct.Member** %23, align 8
  store %struct.Member* %24, %struct.Member** %8, align 8
  br label %25

25:                                               ; preds = %141, %21
  %26 = load %struct.Member*, %struct.Member** %8, align 8
  %27 = icmp ne %struct.Member* %26, null
  br i1 %27, label %28, label %145

28:                                               ; preds = %25
  %29 = load %struct.Member*, %struct.Member** %8, align 8
  %30 = getelementptr inbounds %struct.Member, %struct.Member* %29, i32 0, i32 7
  %31 = load i8, i8* %30, align 4
  %32 = trunc i8 %31 to i1
  br i1 %32, label %33, label %47

33:                                               ; preds = %28
  %34 = load %struct.Member*, %struct.Member** %8, align 8
  %35 = getelementptr inbounds %struct.Member, %struct.Member* %34, i32 0, i32 9
  %36 = load i32, i32* %35, align 4
  %37 = icmp eq i32 %36, 0
  br i1 %37, label %38, label %47

38:                                               ; preds = %33
  %39 = load i32, i32* %7, align 4
  %40 = load %struct.Member*, %struct.Member** %8, align 8
  %41 = getelementptr inbounds %struct.Member, %struct.Member* %40, i32 0, i32 1
  %42 = load %struct.Type*, %struct.Type** %41, align 8
  %43 = getelementptr inbounds %struct.Type, %struct.Type* %42, i32 0, i32 1
  %44 = load i32, i32* %43, align 4
  %45 = mul nsw i32 %44, 8
  %46 = call i32 @align_to(i32 noundef %39, i32 noundef %45)
  store i32 %46, i32* %7, align 4
  br label %121

47:                                               ; preds = %33, %28
  %48 = load %struct.Member*, %struct.Member** %8, align 8
  %49 = getelementptr inbounds %struct.Member, %struct.Member* %48, i32 0, i32 7
  %50 = load i8, i8* %49, align 4
  %51 = trunc i8 %50 to i1
  br i1 %51, label %52, label %95

52:                                               ; preds = %47
  %53 = load %struct.Member*, %struct.Member** %8, align 8
  %54 = getelementptr inbounds %struct.Member, %struct.Member* %53, i32 0, i32 1
  %55 = load %struct.Type*, %struct.Type** %54, align 8
  %56 = getelementptr inbounds %struct.Type, %struct.Type* %55, i32 0, i32 1
  %57 = load i32, i32* %56, align 4
  store i32 %57, i32* %9, align 4
  %58 = load i32, i32* %7, align 4
  %59 = load i32, i32* %9, align 4
  %60 = mul nsw i32 %59, 8
  %61 = sdiv i32 %58, %60
  %62 = load i32, i32* %7, align 4
  %63 = load %struct.Member*, %struct.Member** %8, align 8
  %64 = getelementptr inbounds %struct.Member, %struct.Member* %63, i32 0, i32 9
  %65 = load i32, i32* %64, align 4
  %66 = add nsw i32 %62, %65
  %67 = sub nsw i32 %66, 1
  %68 = load i32, i32* %9, align 4
  %69 = mul nsw i32 %68, 8
  %70 = sdiv i32 %67, %69
  %71 = icmp ne i32 %61, %70
  br i1 %71, label %72, label %77

72:                                               ; preds = %52
  %73 = load i32, i32* %7, align 4
  %74 = load i32, i32* %9, align 4
  %75 = mul nsw i32 %74, 8
  %76 = call i32 @align_to(i32 noundef %73, i32 noundef %75)
  store i32 %76, i32* %7, align 4
  br label %77

77:                                               ; preds = %72, %52
  %78 = load i32, i32* %7, align 4
  %79 = sdiv i32 %78, 8
  %80 = load i32, i32* %9, align 4
  %81 = call i32 @align_down(i32 noundef %79, i32 noundef %80)
  %82 = load %struct.Member*, %struct.Member** %8, align 8
  %83 = getelementptr inbounds %struct.Member, %struct.Member* %82, i32 0, i32 6
  store i32 %81, i32* %83, align 8
  %84 = load i32, i32* %7, align 4
  %85 = load i32, i32* %9, align 4
  %86 = mul nsw i32 %85, 8
  %87 = srem i32 %84, %86
  %88 = load %struct.Member*, %struct.Member** %8, align 8
  %89 = getelementptr inbounds %struct.Member, %struct.Member* %88, i32 0, i32 8
  store i32 %87, i32* %89, align 8
  %90 = load %struct.Member*, %struct.Member** %8, align 8
  %91 = getelementptr inbounds %struct.Member, %struct.Member* %90, i32 0, i32 9
  %92 = load i32, i32* %91, align 4
  %93 = load i32, i32* %7, align 4
  %94 = add nsw i32 %93, %92
  store i32 %94, i32* %7, align 4
  br label %120

95:                                               ; preds = %47
  %96 = load %struct.Type*, %struct.Type** %6, align 8
  %97 = getelementptr inbounds %struct.Type, %struct.Type* %96, i32 0, i32 16
  %98 = load i8, i8* %97, align 1
  %99 = trunc i8 %98 to i1
  br i1 %99, label %107, label %100

100:                                              ; preds = %95
  %101 = load i32, i32* %7, align 4
  %102 = load %struct.Member*, %struct.Member** %8, align 8
  %103 = getelementptr inbounds %struct.Member, %struct.Member* %102, i32 0, i32 5
  %104 = load i32, i32* %103, align 4
  %105 = mul nsw i32 %104, 8
  %106 = call i32 @align_to(i32 noundef %101, i32 noundef %105)
  store i32 %106, i32* %7, align 4
  br label %107

107:                                              ; preds = %100, %95
  %108 = load i32, i32* %7, align 4
  %109 = sdiv i32 %108, 8
  %110 = load %struct.Member*, %struct.Member** %8, align 8
  %111 = getelementptr inbounds %struct.Member, %struct.Member* %110, i32 0, i32 6
  store i32 %109, i32* %111, align 8
  %112 = load %struct.Member*, %struct.Member** %8, align 8
  %113 = getelementptr inbounds %struct.Member, %struct.Member* %112, i32 0, i32 1
  %114 = load %struct.Type*, %struct.Type** %113, align 8
  %115 = getelementptr inbounds %struct.Type, %struct.Type* %114, i32 0, i32 1
  %116 = load i32, i32* %115, align 4
  %117 = mul nsw i32 %116, 8
  %118 = load i32, i32* %7, align 4
  %119 = add nsw i32 %118, %117
  store i32 %119, i32* %7, align 4
  br label %120

120:                                              ; preds = %107, %77
  br label %121

121:                                              ; preds = %120, %38
  %122 = load %struct.Type*, %struct.Type** %6, align 8
  %123 = getelementptr inbounds %struct.Type, %struct.Type* %122, i32 0, i32 16
  %124 = load i8, i8* %123, align 1
  %125 = trunc i8 %124 to i1
  br i1 %125, label %140, label %126

126:                                              ; preds = %121
  %127 = load %struct.Type*, %struct.Type** %6, align 8
  %128 = getelementptr inbounds %struct.Type, %struct.Type* %127, i32 0, i32 2
  %129 = load i32, i32* %128, align 8
  %130 = load %struct.Member*, %struct.Member** %8, align 8
  %131 = getelementptr inbounds %struct.Member, %struct.Member* %130, i32 0, i32 5
  %132 = load i32, i32* %131, align 4
  %133 = icmp slt i32 %129, %132
  br i1 %133, label %134, label %140

134:                                              ; preds = %126
  %135 = load %struct.Member*, %struct.Member** %8, align 8
  %136 = getelementptr inbounds %struct.Member, %struct.Member* %135, i32 0, i32 5
  %137 = load i32, i32* %136, align 4
  %138 = load %struct.Type*, %struct.Type** %6, align 8
  %139 = getelementptr inbounds %struct.Type, %struct.Type* %138, i32 0, i32 2
  store i32 %137, i32* %139, align 8
  br label %140

140:                                              ; preds = %134, %126, %121
  br label %141

141:                                              ; preds = %140
  %142 = load %struct.Member*, %struct.Member** %8, align 8
  %143 = getelementptr inbounds %struct.Member, %struct.Member* %142, i32 0, i32 0
  %144 = load %struct.Member*, %struct.Member** %143, align 8
  store %struct.Member* %144, %struct.Member** %8, align 8
  br label %25, !llvm.loop !59

145:                                              ; preds = %25
  %146 = load i32, i32* %7, align 4
  %147 = load %struct.Type*, %struct.Type** %6, align 8
  %148 = getelementptr inbounds %struct.Type, %struct.Type* %147, i32 0, i32 2
  %149 = load i32, i32* %148, align 8
  %150 = mul nsw i32 %149, 8
  %151 = call i32 @align_to(i32 noundef %146, i32 noundef %150)
  %152 = sdiv i32 %151, 8
  %153 = load %struct.Type*, %struct.Type** %6, align 8
  %154 = getelementptr inbounds %struct.Type, %struct.Type* %153, i32 0, i32 1
  store i32 %152, i32* %154, align 4
  %155 = load %struct.Type*, %struct.Type** %6, align 8
  store %struct.Type* %155, %struct.Type** %3, align 8
  br label %156

156:                                              ; preds = %145, %19
  %157 = load %struct.Type*, %struct.Type** %3, align 8
  ret %struct.Type* %157
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @union_decl(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Member*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %8 = load %struct.Token**, %struct.Token*** %4, align 8
  %9 = load %struct.Token*, %struct.Token** %5, align 8
  %10 = call %struct.Type* @struct_union_decl(%struct.Token** noundef %8, %struct.Token* noundef %9)
  store %struct.Type* %10, %struct.Type** %6, align 8
  %11 = load %struct.Type*, %struct.Type** %6, align 8
  %12 = getelementptr inbounds %struct.Type, %struct.Type* %11, i32 0, i32 0
  store i32 15, i32* %12, align 8
  %13 = load %struct.Type*, %struct.Type** %6, align 8
  %14 = getelementptr inbounds %struct.Type, %struct.Type* %13, i32 0, i32 1
  %15 = load i32, i32* %14, align 4
  %16 = icmp slt i32 %15, 0
  br i1 %16, label %17, label %19

17:                                               ; preds = %2
  %18 = load %struct.Type*, %struct.Type** %6, align 8
  store %struct.Type* %18, %struct.Type** %3, align 8
  br label %74

19:                                               ; preds = %2
  %20 = load %struct.Type*, %struct.Type** %6, align 8
  %21 = getelementptr inbounds %struct.Type, %struct.Type* %20, i32 0, i32 14
  %22 = load %struct.Member*, %struct.Member** %21, align 8
  store %struct.Member* %22, %struct.Member** %7, align 8
  br label %23

23:                                               ; preds = %59, %19
  %24 = load %struct.Member*, %struct.Member** %7, align 8
  %25 = icmp ne %struct.Member* %24, null
  br i1 %25, label %26, label %63

26:                                               ; preds = %23
  %27 = load %struct.Type*, %struct.Type** %6, align 8
  %28 = getelementptr inbounds %struct.Type, %struct.Type* %27, i32 0, i32 2
  %29 = load i32, i32* %28, align 8
  %30 = load %struct.Member*, %struct.Member** %7, align 8
  %31 = getelementptr inbounds %struct.Member, %struct.Member* %30, i32 0, i32 5
  %32 = load i32, i32* %31, align 4
  %33 = icmp slt i32 %29, %32
  br i1 %33, label %34, label %40

34:                                               ; preds = %26
  %35 = load %struct.Member*, %struct.Member** %7, align 8
  %36 = getelementptr inbounds %struct.Member, %struct.Member* %35, i32 0, i32 5
  %37 = load i32, i32* %36, align 4
  %38 = load %struct.Type*, %struct.Type** %6, align 8
  %39 = getelementptr inbounds %struct.Type, %struct.Type* %38, i32 0, i32 2
  store i32 %37, i32* %39, align 8
  br label %40

40:                                               ; preds = %34, %26
  %41 = load %struct.Type*, %struct.Type** %6, align 8
  %42 = getelementptr inbounds %struct.Type, %struct.Type* %41, i32 0, i32 1
  %43 = load i32, i32* %42, align 4
  %44 = load %struct.Member*, %struct.Member** %7, align 8
  %45 = getelementptr inbounds %struct.Member, %struct.Member* %44, i32 0, i32 1
  %46 = load %struct.Type*, %struct.Type** %45, align 8
  %47 = getelementptr inbounds %struct.Type, %struct.Type* %46, i32 0, i32 1
  %48 = load i32, i32* %47, align 4
  %49 = icmp slt i32 %43, %48
  br i1 %49, label %50, label %58

50:                                               ; preds = %40
  %51 = load %struct.Member*, %struct.Member** %7, align 8
  %52 = getelementptr inbounds %struct.Member, %struct.Member* %51, i32 0, i32 1
  %53 = load %struct.Type*, %struct.Type** %52, align 8
  %54 = getelementptr inbounds %struct.Type, %struct.Type* %53, i32 0, i32 1
  %55 = load i32, i32* %54, align 4
  %56 = load %struct.Type*, %struct.Type** %6, align 8
  %57 = getelementptr inbounds %struct.Type, %struct.Type* %56, i32 0, i32 1
  store i32 %55, i32* %57, align 4
  br label %58

58:                                               ; preds = %50, %40
  br label %59

59:                                               ; preds = %58
  %60 = load %struct.Member*, %struct.Member** %7, align 8
  %61 = getelementptr inbounds %struct.Member, %struct.Member* %60, i32 0, i32 0
  %62 = load %struct.Member*, %struct.Member** %61, align 8
  store %struct.Member* %62, %struct.Member** %7, align 8
  br label %23, !llvm.loop !60

63:                                               ; preds = %23
  %64 = load %struct.Type*, %struct.Type** %6, align 8
  %65 = getelementptr inbounds %struct.Type, %struct.Type* %64, i32 0, i32 1
  %66 = load i32, i32* %65, align 4
  %67 = load %struct.Type*, %struct.Type** %6, align 8
  %68 = getelementptr inbounds %struct.Type, %struct.Type* %67, i32 0, i32 2
  %69 = load i32, i32* %68, align 8
  %70 = call i32 @align_to(i32 noundef %66, i32 noundef %69)
  %71 = load %struct.Type*, %struct.Type** %6, align 8
  %72 = getelementptr inbounds %struct.Type, %struct.Type* %71, i32 0, i32 1
  store i32 %70, i32* %72, align 4
  %73 = load %struct.Type*, %struct.Type** %6, align 8
  store %struct.Type* %73, %struct.Type** %3, align 8
  br label %74

74:                                               ; preds = %63, %17
  %75 = load %struct.Type*, %struct.Type** %3, align 8
  ret %struct.Type* %75
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @enum_specifier(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca %struct.Type*, align 8
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i8*, align 8
  %12 = alloca %struct.VarScope*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %13 = call %struct.Type* @enum_type()
  store %struct.Type* %13, %struct.Type** %6, align 8
  store %struct.Token* null, %struct.Token** %7, align 8
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 16
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %18, label %23

18:                                               ; preds = %2
  %19 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %19, %struct.Token** %7, align 8
  %20 = load %struct.Token*, %struct.Token** %5, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 1
  %22 = load %struct.Token*, %struct.Token** %21, align 8
  store %struct.Token* %22, %struct.Token** %5, align 8
  br label %23

23:                                               ; preds = %18, %2
  %24 = load %struct.Token*, %struct.Token** %7, align 8
  %25 = icmp ne %struct.Token* %24, null
  br i1 %25, label %26, label %47

26:                                               ; preds = %23
  %27 = load %struct.Token*, %struct.Token** %5, align 8
  %28 = call zeroext i1 @equal(%struct.Token* noundef %27, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %28, label %47, label %29

29:                                               ; preds = %26
  %30 = load %struct.Token*, %struct.Token** %7, align 8
  %31 = call %struct.Type* @find_tag(%struct.Token* noundef %30)
  store %struct.Type* %31, %struct.Type** %8, align 8
  %32 = load %struct.Type*, %struct.Type** %8, align 8
  %33 = icmp ne %struct.Type* %32, null
  br i1 %33, label %36, label %34

34:                                               ; preds = %29
  %35 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %35, i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str.230, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

36:                                               ; preds = %29
  %37 = load %struct.Type*, %struct.Type** %8, align 8
  %38 = getelementptr inbounds %struct.Type, %struct.Type* %37, i32 0, i32 0
  %39 = load i32, i32* %38, align 8
  %40 = icmp ne i32 %39, 9
  br i1 %40, label %41, label %43

41:                                               ; preds = %36
  %42 = load %struct.Token*, %struct.Token** %7, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %42, i8* noundef getelementptr inbounds ([40 x i8], [40 x i8]* @.str.231, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

43:                                               ; preds = %36
  %44 = load %struct.Token*, %struct.Token** %5, align 8
  %45 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %44, %struct.Token** %45, align 8
  %46 = load %struct.Type*, %struct.Type** %8, align 8
  store %struct.Type* %46, %struct.Type** %3, align 8
  br label %94

47:                                               ; preds = %26, %23
  %48 = load %struct.Token*, %struct.Token** %5, align 8
  %49 = call %struct.Token* @skip(%struct.Token* noundef %48, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  store %struct.Token* %49, %struct.Token** %5, align 8
  store i32 0, i32* %9, align 4
  store i32 0, i32* %10, align 4
  br label %50

50:                                               ; preds = %76, %47
  %51 = load %struct.Token**, %struct.Token*** %4, align 8
  %52 = load %struct.Token*, %struct.Token** %5, align 8
  %53 = call zeroext i1 @consume_end(%struct.Token** noundef %51, %struct.Token* noundef %52)
  %54 = xor i1 %53, true
  br i1 %54, label %55, label %86

55:                                               ; preds = %50
  %56 = load i32, i32* %9, align 4
  %57 = add nsw i32 %56, 1
  store i32 %57, i32* %9, align 4
  %58 = icmp sgt i32 %56, 0
  br i1 %58, label %59, label %62

59:                                               ; preds = %55
  %60 = load %struct.Token*, %struct.Token** %5, align 8
  %61 = call %struct.Token* @skip(%struct.Token* noundef %60, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %61, %struct.Token** %5, align 8
  br label %62

62:                                               ; preds = %59, %55
  %63 = load %struct.Token*, %struct.Token** %5, align 8
  %64 = call i8* @get_ident(%struct.Token* noundef %63)
  store i8* %64, i8** %11, align 8
  %65 = load %struct.Token*, %struct.Token** %5, align 8
  %66 = getelementptr inbounds %struct.Token, %struct.Token* %65, i32 0, i32 1
  %67 = load %struct.Token*, %struct.Token** %66, align 8
  store %struct.Token* %67, %struct.Token** %5, align 8
  %68 = load %struct.Token*, %struct.Token** %5, align 8
  %69 = call zeroext i1 @equal(%struct.Token* noundef %68, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.150, i64 0, i64 0))
  br i1 %69, label %70, label %76

70:                                               ; preds = %62
  %71 = load %struct.Token*, %struct.Token** %5, align 8
  %72 = getelementptr inbounds %struct.Token, %struct.Token* %71, i32 0, i32 1
  %73 = load %struct.Token*, %struct.Token** %72, align 8
  %74 = call i64 @const_expr(%struct.Token** noundef %5, %struct.Token* noundef %73)
  %75 = trunc i64 %74 to i32
  store i32 %75, i32* %10, align 4
  br label %76

76:                                               ; preds = %70, %62
  %77 = load i8*, i8** %11, align 8
  %78 = call %struct.VarScope* @push_scope(i8* noundef %77)
  store %struct.VarScope* %78, %struct.VarScope** %12, align 8
  %79 = load %struct.Type*, %struct.Type** %6, align 8
  %80 = load %struct.VarScope*, %struct.VarScope** %12, align 8
  %81 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %80, i32 0, i32 2
  store %struct.Type* %79, %struct.Type** %81, align 8
  %82 = load i32, i32* %10, align 4
  %83 = add nsw i32 %82, 1
  store i32 %83, i32* %10, align 4
  %84 = load %struct.VarScope*, %struct.VarScope** %12, align 8
  %85 = getelementptr inbounds %struct.VarScope, %struct.VarScope* %84, i32 0, i32 3
  store i32 %82, i32* %85, align 8
  br label %50, !llvm.loop !61

86:                                               ; preds = %50
  %87 = load %struct.Token*, %struct.Token** %7, align 8
  %88 = icmp ne %struct.Token* %87, null
  br i1 %88, label %89, label %92

89:                                               ; preds = %86
  %90 = load %struct.Token*, %struct.Token** %7, align 8
  %91 = load %struct.Type*, %struct.Type** %6, align 8
  call void @push_tag_scope(%struct.Token* noundef %90, %struct.Type* noundef %91)
  br label %92

92:                                               ; preds = %89, %86
  %93 = load %struct.Type*, %struct.Type** %6, align 8
  store %struct.Type* %93, %struct.Type** %3, align 8
  br label %94

94:                                               ; preds = %92, %43
  %95 = load %struct.Type*, %struct.Type** %3, align 8
  ret %struct.Type* %95
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @typeof_specifier(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Token**, align 8
  %4 = alloca %struct.Token*, align 8
  %5 = alloca %struct.Type*, align 8
  %6 = alloca %struct.Node*, align 8
  store %struct.Token** %0, %struct.Token*** %3, align 8
  store %struct.Token* %1, %struct.Token** %4, align 8
  %7 = load %struct.Token*, %struct.Token** %4, align 8
  %8 = call %struct.Token* @skip(%struct.Token* noundef %7, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %8, %struct.Token** %4, align 8
  %9 = load %struct.Token*, %struct.Token** %4, align 8
  %10 = call zeroext i1 @is_typename(%struct.Token* noundef %9)
  br i1 %10, label %11, label %14

11:                                               ; preds = %2
  %12 = load %struct.Token*, %struct.Token** %4, align 8
  %13 = call %struct.Type* @typename(%struct.Token** noundef %4, %struct.Token* noundef %12)
  store %struct.Type* %13, %struct.Type** %5, align 8
  br label %21

14:                                               ; preds = %2
  %15 = load %struct.Token*, %struct.Token** %4, align 8
  %16 = call %struct.Node* @expr(%struct.Token** noundef %4, %struct.Token* noundef %15)
  store %struct.Node* %16, %struct.Node** %6, align 8
  %17 = load %struct.Node*, %struct.Node** %6, align 8
  call void @add_type(%struct.Node* noundef %17)
  %18 = load %struct.Node*, %struct.Node** %6, align 8
  %19 = getelementptr inbounds %struct.Node, %struct.Node* %18, i32 0, i32 2
  %20 = load %struct.Type*, %struct.Type** %19, align 16
  store %struct.Type* %20, %struct.Type** %5, align 8
  br label %21

21:                                               ; preds = %14, %11
  %22 = load %struct.Token*, %struct.Token** %4, align 8
  %23 = call %struct.Token* @skip(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %24 = load %struct.Token**, %struct.Token*** %3, align 8
  store %struct.Token* %23, %struct.Token** %24, align 8
  %25 = load %struct.Type*, %struct.Type** %5, align 8
  ret %struct.Type* %25
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @struct_union_decl(%struct.Token** noundef %0, %struct.Token* noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Token*, align 8
  %8 = alloca %struct.Type*, align 8
  %9 = alloca %struct.Type*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  %10 = call %struct.Type* @struct_type()
  store %struct.Type* %10, %struct.Type** %6, align 8
  %11 = load %struct.Token*, %struct.Token** %5, align 8
  %12 = load %struct.Type*, %struct.Type** %6, align 8
  %13 = call %struct.Token* @attribute_list(%struct.Token* noundef %11, %struct.Type* noundef %12)
  store %struct.Token* %13, %struct.Token** %5, align 8
  store %struct.Token* null, %struct.Token** %7, align 8
  %14 = load %struct.Token*, %struct.Token** %5, align 8
  %15 = getelementptr inbounds %struct.Token, %struct.Token* %14, i32 0, i32 0
  %16 = load i32, i32* %15, align 16
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %18, label %23

18:                                               ; preds = %2
  %19 = load %struct.Token*, %struct.Token** %5, align 8
  store %struct.Token* %19, %struct.Token** %7, align 8
  %20 = load %struct.Token*, %struct.Token** %5, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 1
  %22 = load %struct.Token*, %struct.Token** %21, align 8
  store %struct.Token* %22, %struct.Token** %5, align 8
  br label %23

23:                                               ; preds = %18, %2
  %24 = load %struct.Token*, %struct.Token** %7, align 8
  %25 = icmp ne %struct.Token* %24, null
  br i1 %25, label %26, label %44

26:                                               ; preds = %23
  %27 = load %struct.Token*, %struct.Token** %5, align 8
  %28 = call zeroext i1 @equal(%struct.Token* noundef %27, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %28, label %44, label %29

29:                                               ; preds = %26
  %30 = load %struct.Token*, %struct.Token** %5, align 8
  %31 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %30, %struct.Token** %31, align 8
  %32 = load %struct.Token*, %struct.Token** %7, align 8
  %33 = call %struct.Type* @find_tag(%struct.Token* noundef %32)
  store %struct.Type* %33, %struct.Type** %8, align 8
  %34 = load %struct.Type*, %struct.Type** %8, align 8
  %35 = icmp ne %struct.Type* %34, null
  br i1 %35, label %36, label %38

36:                                               ; preds = %29
  %37 = load %struct.Type*, %struct.Type** %8, align 8
  store %struct.Type* %37, %struct.Type** %3, align 8
  br label %79

38:                                               ; preds = %29
  %39 = load %struct.Type*, %struct.Type** %6, align 8
  %40 = getelementptr inbounds %struct.Type, %struct.Type* %39, i32 0, i32 1
  store i32 -1, i32* %40, align 4
  %41 = load %struct.Token*, %struct.Token** %7, align 8
  %42 = load %struct.Type*, %struct.Type** %6, align 8
  call void @push_tag_scope(%struct.Token* noundef %41, %struct.Type* noundef %42)
  %43 = load %struct.Type*, %struct.Type** %6, align 8
  store %struct.Type* %43, %struct.Type** %3, align 8
  br label %79

44:                                               ; preds = %26, %23
  %45 = load %struct.Token*, %struct.Token** %5, align 8
  %46 = call %struct.Token* @skip(%struct.Token* noundef %45, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  store %struct.Token* %46, %struct.Token** %5, align 8
  %47 = load %struct.Token*, %struct.Token** %5, align 8
  %48 = load %struct.Type*, %struct.Type** %6, align 8
  call void @struct_members(%struct.Token** noundef %5, %struct.Token* noundef %47, %struct.Type* noundef %48)
  %49 = load %struct.Token*, %struct.Token** %5, align 8
  %50 = load %struct.Type*, %struct.Type** %6, align 8
  %51 = call %struct.Token* @attribute_list(%struct.Token* noundef %49, %struct.Type* noundef %50)
  %52 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %51, %struct.Token** %52, align 8
  %53 = load %struct.Token*, %struct.Token** %7, align 8
  %54 = icmp ne %struct.Token* %53, null
  br i1 %54, label %55, label %77

55:                                               ; preds = %44
  %56 = load %struct.Scope*, %struct.Scope** @scope, align 8
  %57 = getelementptr inbounds %struct.Scope, %struct.Scope* %56, i32 0, i32 2
  %58 = load %struct.Token*, %struct.Token** %7, align 8
  %59 = getelementptr inbounds %struct.Token, %struct.Token* %58, i32 0, i32 4
  %60 = load i8*, i8** %59, align 16
  %61 = load %struct.Token*, %struct.Token** %7, align 8
  %62 = getelementptr inbounds %struct.Token, %struct.Token* %61, i32 0, i32 5
  %63 = load i32, i32* %62, align 8
  %64 = call i8* @hashmap_get2(%struct.HashMap* noundef %57, i8* noundef %60, i32 noundef %63)
  %65 = bitcast i8* %64 to %struct.Type*
  store %struct.Type* %65, %struct.Type** %9, align 8
  %66 = load %struct.Type*, %struct.Type** %9, align 8
  %67 = icmp ne %struct.Type* %66, null
  br i1 %67, label %68, label %74

68:                                               ; preds = %55
  %69 = load %struct.Type*, %struct.Type** %9, align 8
  %70 = load %struct.Type*, %struct.Type** %6, align 8
  %71 = bitcast %struct.Type* %69 to i8*
  %72 = bitcast %struct.Type* %70 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %71, i8* align 8 %72, i64 128, i1 false)
  %73 = load %struct.Type*, %struct.Type** %9, align 8
  store %struct.Type* %73, %struct.Type** %3, align 8
  br label %79

74:                                               ; preds = %55
  %75 = load %struct.Token*, %struct.Token** %7, align 8
  %76 = load %struct.Type*, %struct.Type** %6, align 8
  call void @push_tag_scope(%struct.Token* noundef %75, %struct.Type* noundef %76)
  br label %77

77:                                               ; preds = %74, %44
  %78 = load %struct.Type*, %struct.Type** %6, align 8
  store %struct.Type* %78, %struct.Type** %3, align 8
  br label %79

79:                                               ; preds = %77, %68, %38, %36
  %80 = load %struct.Type*, %struct.Type** %3, align 8
  ret %struct.Type* %80
}

declare i32 @align_to(i32 noundef, i32 noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @align_down(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = sub nsw i32 %5, %6
  %8 = add nsw i32 %7, 1
  %9 = load i32, i32* %4, align 4
  %10 = call i32 @align_to(i32 noundef %8, i32 noundef %9)
  ret i32 %10
}

declare %struct.Type* @struct_type() #1

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @attribute_list(%struct.Token* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca i8, align 1
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  br label %6

6:                                                ; preds = %45, %2
  %7 = load %struct.Token*, %struct.Token** %3, align 8
  %8 = call zeroext i1 @consume(%struct.Token** noundef %3, %struct.Token* noundef %7, i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.223, i64 0, i64 0))
  br i1 %8, label %9, label %48

9:                                                ; preds = %6
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = call %struct.Token* @skip(%struct.Token* noundef %10, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %11, %struct.Token** %3, align 8
  %12 = load %struct.Token*, %struct.Token** %3, align 8
  %13 = call %struct.Token* @skip(%struct.Token* noundef %12, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %13, %struct.Token** %3, align 8
  store i8 1, i8* %5, align 1
  br label %14

14:                                               ; preds = %33, %27, %9
  %15 = load %struct.Token*, %struct.Token** %3, align 8
  %16 = call zeroext i1 @consume(%struct.Token** noundef %3, %struct.Token* noundef %15, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  %17 = xor i1 %16, true
  br i1 %17, label %18, label %45

18:                                               ; preds = %14
  %19 = load i8, i8* %5, align 1
  %20 = trunc i8 %19 to i1
  br i1 %20, label %24, label %21

21:                                               ; preds = %18
  %22 = load %struct.Token*, %struct.Token** %3, align 8
  %23 = call %struct.Token* @skip(%struct.Token* noundef %22, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %23, %struct.Token** %3, align 8
  br label %24

24:                                               ; preds = %21, %18
  store i8 0, i8* %5, align 1
  %25 = load %struct.Token*, %struct.Token** %3, align 8
  %26 = call zeroext i1 @consume(%struct.Token** noundef %3, %struct.Token* noundef %25, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.224, i64 0, i64 0))
  br i1 %26, label %27, label %30

27:                                               ; preds = %24
  %28 = load %struct.Type*, %struct.Type** %4, align 8
  %29 = getelementptr inbounds %struct.Type, %struct.Type* %28, i32 0, i32 16
  store i8 1, i8* %29, align 1
  br label %14, !llvm.loop !62

30:                                               ; preds = %24
  %31 = load %struct.Token*, %struct.Token** %3, align 8
  %32 = call zeroext i1 @consume(%struct.Token** noundef %3, %struct.Token* noundef %31, i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.225, i64 0, i64 0))
  br i1 %32, label %33, label %43

33:                                               ; preds = %30
  %34 = load %struct.Token*, %struct.Token** %3, align 8
  %35 = call %struct.Token* @skip(%struct.Token* noundef %34, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.85, i64 0, i64 0))
  store %struct.Token* %35, %struct.Token** %3, align 8
  %36 = load %struct.Token*, %struct.Token** %3, align 8
  %37 = call i64 @const_expr(%struct.Token** noundef %3, %struct.Token* noundef %36)
  %38 = trunc i64 %37 to i32
  %39 = load %struct.Type*, %struct.Type** %4, align 8
  %40 = getelementptr inbounds %struct.Type, %struct.Type* %39, i32 0, i32 2
  store i32 %38, i32* %40, align 8
  %41 = load %struct.Token*, %struct.Token** %3, align 8
  %42 = call %struct.Token* @skip(%struct.Token* noundef %41, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %42, %struct.Token** %3, align 8
  br label %14, !llvm.loop !62

43:                                               ; preds = %30
  %44 = load %struct.Token*, %struct.Token** %3, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %44, i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str.226, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

45:                                               ; preds = %14
  %46 = load %struct.Token*, %struct.Token** %3, align 8
  %47 = call %struct.Token* @skip(%struct.Token* noundef %46, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.86, i64 0, i64 0))
  store %struct.Token* %47, %struct.Token** %3, align 8
  br label %6, !llvm.loop !63

48:                                               ; preds = %6
  %49 = load %struct.Token*, %struct.Token** %3, align 8
  ret %struct.Token* %49
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Type* @find_tag(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Scope*, align 8
  %5 = alloca %struct.Type*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  %6 = load %struct.Scope*, %struct.Scope** @scope, align 8
  store %struct.Scope* %6, %struct.Scope** %4, align 8
  br label %7

7:                                                ; preds = %26, %1
  %8 = load %struct.Scope*, %struct.Scope** %4, align 8
  %9 = icmp ne %struct.Scope* %8, null
  br i1 %9, label %10, label %30

10:                                               ; preds = %7
  %11 = load %struct.Scope*, %struct.Scope** %4, align 8
  %12 = getelementptr inbounds %struct.Scope, %struct.Scope* %11, i32 0, i32 2
  %13 = load %struct.Token*, %struct.Token** %3, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 4
  %15 = load i8*, i8** %14, align 16
  %16 = load %struct.Token*, %struct.Token** %3, align 8
  %17 = getelementptr inbounds %struct.Token, %struct.Token* %16, i32 0, i32 5
  %18 = load i32, i32* %17, align 8
  %19 = call i8* @hashmap_get2(%struct.HashMap* noundef %12, i8* noundef %15, i32 noundef %18)
  %20 = bitcast i8* %19 to %struct.Type*
  store %struct.Type* %20, %struct.Type** %5, align 8
  %21 = load %struct.Type*, %struct.Type** %5, align 8
  %22 = icmp ne %struct.Type* %21, null
  br i1 %22, label %23, label %25

23:                                               ; preds = %10
  %24 = load %struct.Type*, %struct.Type** %5, align 8
  store %struct.Type* %24, %struct.Type** %2, align 8
  br label %31

25:                                               ; preds = %10
  br label %26

26:                                               ; preds = %25
  %27 = load %struct.Scope*, %struct.Scope** %4, align 8
  %28 = getelementptr inbounds %struct.Scope, %struct.Scope* %27, i32 0, i32 0
  %29 = load %struct.Scope*, %struct.Scope** %28, align 8
  store %struct.Scope* %29, %struct.Scope** %4, align 8
  br label %7, !llvm.loop !64

30:                                               ; preds = %7
  store %struct.Type* null, %struct.Type** %2, align 8
  br label %31

31:                                               ; preds = %30, %23
  %32 = load %struct.Type*, %struct.Type** %2, align 8
  ret %struct.Type* %32
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @push_tag_scope(%struct.Token* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca %struct.Token*, align 8
  %4 = alloca %struct.Type*, align 8
  store %struct.Token* %0, %struct.Token** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  %5 = load %struct.Scope*, %struct.Scope** @scope, align 8
  %6 = getelementptr inbounds %struct.Scope, %struct.Scope* %5, i32 0, i32 2
  %7 = load %struct.Token*, %struct.Token** %3, align 8
  %8 = getelementptr inbounds %struct.Token, %struct.Token* %7, i32 0, i32 4
  %9 = load i8*, i8** %8, align 16
  %10 = load %struct.Token*, %struct.Token** %3, align 8
  %11 = getelementptr inbounds %struct.Token, %struct.Token* %10, i32 0, i32 5
  %12 = load i32, i32* %11, align 8
  %13 = load %struct.Type*, %struct.Type** %4, align 8
  %14 = bitcast %struct.Type* %13 to i8*
  call void @hashmap_put2(%struct.HashMap* noundef %6, i8* noundef %9, i32 noundef %12, i8* noundef %14)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @struct_members(%struct.Token** noundef %0, %struct.Token* noundef %1, %struct.Type* noundef %2) #0 {
  %4 = alloca %struct.Token**, align 8
  %5 = alloca %struct.Token*, align 8
  %6 = alloca %struct.Type*, align 8
  %7 = alloca %struct.Member, align 8
  %8 = alloca %struct.Member*, align 8
  %9 = alloca i32, align 4
  %10 = alloca %struct.VarAttr, align 4
  %11 = alloca %struct.Type*, align 8
  %12 = alloca i8, align 1
  %13 = alloca %struct.Member*, align 8
  %14 = alloca %struct.Member*, align 8
  %15 = alloca %struct.Member*, align 8
  store %struct.Token** %0, %struct.Token*** %4, align 8
  store %struct.Token* %1, %struct.Token** %5, align 8
  store %struct.Type* %2, %struct.Type** %6, align 8
  %16 = bitcast %struct.Member* %7 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %16, i8 0, i64 56, i1 false)
  store %struct.Member* %7, %struct.Member** %8, align 8
  store i32 0, i32* %9, align 4
  br label %17

17:                                               ; preds = %141, %63, %3
  %18 = load %struct.Token*, %struct.Token** %5, align 8
  %19 = call zeroext i1 @equal(%struct.Token* noundef %18, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.143, i64 0, i64 0))
  %20 = xor i1 %19, true
  br i1 %20, label %21, label %142

21:                                               ; preds = %17
  %22 = bitcast %struct.VarAttr* %10 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 4 %22, i8 0, i64 12, i1 false)
  %23 = load %struct.Token*, %struct.Token** %5, align 8
  %24 = call %struct.Type* @declspec(%struct.Token** noundef %5, %struct.Token* noundef %23, %struct.VarAttr* noundef %10)
  store %struct.Type* %24, %struct.Type** %11, align 8
  store i8 1, i8* %12, align 1
  %25 = load %struct.Type*, %struct.Type** %11, align 8
  %26 = getelementptr inbounds %struct.Type, %struct.Type* %25, i32 0, i32 0
  %27 = load i32, i32* %26, align 8
  %28 = icmp eq i32 %27, 14
  br i1 %28, label %34, label %29

29:                                               ; preds = %21
  %30 = load %struct.Type*, %struct.Type** %11, align 8
  %31 = getelementptr inbounds %struct.Type, %struct.Type* %30, i32 0, i32 0
  %32 = load i32, i32* %31, align 8
  %33 = icmp eq i32 %32, 15
  br i1 %33, label %34, label %70

34:                                               ; preds = %29, %21
  %35 = load %struct.Token*, %struct.Token** %5, align 8
  %36 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %35, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  br i1 %36, label %37, label %70

37:                                               ; preds = %34
  %38 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 56) #8
  %39 = bitcast i8* %38 to %struct.Member*
  store %struct.Member* %39, %struct.Member** %13, align 8
  %40 = load %struct.Member*, %struct.Member** %13, align 8
  %41 = icmp eq %struct.Member* %40, null
  br i1 %41, label %42, label %43

42:                                               ; preds = %37
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.227, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

43:                                               ; preds = %37
  %44 = load %struct.Type*, %struct.Type** %11, align 8
  %45 = load %struct.Member*, %struct.Member** %13, align 8
  %46 = getelementptr inbounds %struct.Member, %struct.Member* %45, i32 0, i32 1
  store %struct.Type* %44, %struct.Type** %46, align 8
  %47 = load i32, i32* %9, align 4
  %48 = add nsw i32 %47, 1
  store i32 %48, i32* %9, align 4
  %49 = load %struct.Member*, %struct.Member** %13, align 8
  %50 = getelementptr inbounds %struct.Member, %struct.Member* %49, i32 0, i32 4
  store i32 %47, i32* %50, align 8
  %51 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %10, i32 0, i32 5
  %52 = load i32, i32* %51, align 4
  %53 = icmp ne i32 %52, 0
  br i1 %53, label %54, label %57

54:                                               ; preds = %43
  %55 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %10, i32 0, i32 5
  %56 = load i32, i32* %55, align 4
  br label %63

57:                                               ; preds = %43
  %58 = load %struct.Member*, %struct.Member** %13, align 8
  %59 = getelementptr inbounds %struct.Member, %struct.Member* %58, i32 0, i32 1
  %60 = load %struct.Type*, %struct.Type** %59, align 8
  %61 = getelementptr inbounds %struct.Type, %struct.Type* %60, i32 0, i32 2
  %62 = load i32, i32* %61, align 8
  br label %63

63:                                               ; preds = %57, %54
  %64 = phi i32 [ %56, %54 ], [ %62, %57 ]
  %65 = load %struct.Member*, %struct.Member** %13, align 8
  %66 = getelementptr inbounds %struct.Member, %struct.Member* %65, i32 0, i32 5
  store i32 %64, i32* %66, align 4
  %67 = load %struct.Member*, %struct.Member** %13, align 8
  %68 = load %struct.Member*, %struct.Member** %8, align 8
  %69 = getelementptr inbounds %struct.Member, %struct.Member* %68, i32 0, i32 0
  store %struct.Member* %67, %struct.Member** %69, align 8
  store %struct.Member* %67, %struct.Member** %8, align 8
  br label %17, !llvm.loop !65

70:                                               ; preds = %34, %29
  br label %71

71:                                               ; preds = %137, %70
  %72 = load %struct.Token*, %struct.Token** %5, align 8
  %73 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %72, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.121, i64 0, i64 0))
  %74 = xor i1 %73, true
  br i1 %74, label %75, label %141

75:                                               ; preds = %71
  %76 = load i8, i8* %12, align 1
  %77 = trunc i8 %76 to i1
  br i1 %77, label %81, label %78

78:                                               ; preds = %75
  %79 = load %struct.Token*, %struct.Token** %5, align 8
  %80 = call %struct.Token* @skip(%struct.Token* noundef %79, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.122, i64 0, i64 0))
  store %struct.Token* %80, %struct.Token** %5, align 8
  br label %81

81:                                               ; preds = %78, %75
  store i8 0, i8* %12, align 1
  %82 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 56) #8
  %83 = bitcast i8* %82 to %struct.Member*
  store %struct.Member* %83, %struct.Member** %14, align 8
  %84 = load %struct.Member*, %struct.Member** %14, align 8
  %85 = icmp eq %struct.Member* %84, null
  br i1 %85, label %86, label %87

86:                                               ; preds = %81
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([42 x i8], [42 x i8]* @.str.228, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

87:                                               ; preds = %81
  %88 = load %struct.Token*, %struct.Token** %5, align 8
  %89 = load %struct.Type*, %struct.Type** %11, align 8
  %90 = call %struct.Type* @declarator(%struct.Token** noundef %5, %struct.Token* noundef %88, %struct.Type* noundef %89)
  %91 = load %struct.Member*, %struct.Member** %14, align 8
  %92 = getelementptr inbounds %struct.Member, %struct.Member* %91, i32 0, i32 1
  store %struct.Type* %90, %struct.Type** %92, align 8
  %93 = load %struct.Member*, %struct.Member** %14, align 8
  %94 = getelementptr inbounds %struct.Member, %struct.Member* %93, i32 0, i32 1
  %95 = load %struct.Type*, %struct.Type** %94, align 8
  %96 = getelementptr inbounds %struct.Type, %struct.Type* %95, i32 0, i32 9
  %97 = load %struct.Token*, %struct.Token** %96, align 8
  %98 = load %struct.Member*, %struct.Member** %14, align 8
  %99 = getelementptr inbounds %struct.Member, %struct.Member* %98, i32 0, i32 3
  store %struct.Token* %97, %struct.Token** %99, align 8
  %100 = load i32, i32* %9, align 4
  %101 = add nsw i32 %100, 1
  store i32 %101, i32* %9, align 4
  %102 = load %struct.Member*, %struct.Member** %14, align 8
  %103 = getelementptr inbounds %struct.Member, %struct.Member* %102, i32 0, i32 4
  store i32 %100, i32* %103, align 8
  %104 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %10, i32 0, i32 5
  %105 = load i32, i32* %104, align 4
  %106 = icmp ne i32 %105, 0
  br i1 %106, label %107, label %110

107:                                              ; preds = %87
  %108 = getelementptr inbounds %struct.VarAttr, %struct.VarAttr* %10, i32 0, i32 5
  %109 = load i32, i32* %108, align 4
  br label %116

110:                                              ; preds = %87
  %111 = load %struct.Member*, %struct.Member** %14, align 8
  %112 = getelementptr inbounds %struct.Member, %struct.Member* %111, i32 0, i32 1
  %113 = load %struct.Type*, %struct.Type** %112, align 8
  %114 = getelementptr inbounds %struct.Type, %struct.Type* %113, i32 0, i32 2
  %115 = load i32, i32* %114, align 8
  br label %116

116:                                              ; preds = %110, %107
  %117 = phi i32 [ %109, %107 ], [ %115, %110 ]
  %118 = load %struct.Member*, %struct.Member** %14, align 8
  %119 = getelementptr inbounds %struct.Member, %struct.Member* %118, i32 0, i32 5
  store i32 %117, i32* %119, align 4
  %120 = load %struct.Token*, %struct.Token** %5, align 8
  %121 = call zeroext i1 @consume(%struct.Token** noundef %5, %struct.Token* noundef %120, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.65, i64 0, i64 0))
  br i1 %121, label %122, label %137

122:                                              ; preds = %116
  %123 = load %struct.Member*, %struct.Member** %14, align 8
  %124 = getelementptr inbounds %struct.Member, %struct.Member* %123, i32 0, i32 1
  %125 = load %struct.Type*, %struct.Type** %124, align 8
  %126 = call zeroext i1 @is_integer(%struct.Type* noundef %125)
  br i1 %126, label %129, label %127

127:                                              ; preds = %122
  %128 = load %struct.Token*, %struct.Token** %5, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %128, i8* noundef getelementptr inbounds ([55 x i8], [55 x i8]* @.str.229, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

129:                                              ; preds = %122
  %130 = load %struct.Member*, %struct.Member** %14, align 8
  %131 = getelementptr inbounds %struct.Member, %struct.Member* %130, i32 0, i32 7
  store i8 1, i8* %131, align 4
  %132 = load %struct.Token*, %struct.Token** %5, align 8
  %133 = call i64 @const_expr(%struct.Token** noundef %5, %struct.Token* noundef %132)
  %134 = trunc i64 %133 to i32
  %135 = load %struct.Member*, %struct.Member** %14, align 8
  %136 = getelementptr inbounds %struct.Member, %struct.Member* %135, i32 0, i32 9
  store i32 %134, i32* %136, align 4
  br label %137

137:                                              ; preds = %129, %116
  %138 = load %struct.Member*, %struct.Member** %14, align 8
  %139 = load %struct.Member*, %struct.Member** %8, align 8
  %140 = getelementptr inbounds %struct.Member, %struct.Member* %139, i32 0, i32 0
  store %struct.Member* %138, %struct.Member** %140, align 8
  store %struct.Member* %138, %struct.Member** %8, align 8
  br label %71, !llvm.loop !66

141:                                              ; preds = %71
  br label %17, !llvm.loop !65

142:                                              ; preds = %17
  %143 = load i32, i32* %9, align 4
  %144 = icmp eq i32 %143, 0
  br i1 %144, label %145, label %167

145:                                              ; preds = %142
  %146 = call noalias i8* @calloc(i64 noundef 1, i64 noundef 56) #8
  %147 = bitcast i8* %146 to %struct.Member*
  store %struct.Member* %147, %struct.Member** %15, align 8
  %148 = load %struct.Member*, %struct.Member** %15, align 8
  %149 = icmp eq %struct.Member* %148, null
  br i1 %149, label %150, label %151

150:                                              ; preds = %145
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.227, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

151:                                              ; preds = %145
  %152 = load %struct.Type*, %struct.Type** @ty_char, align 8
  %153 = load %struct.Member*, %struct.Member** %15, align 8
  %154 = getelementptr inbounds %struct.Member, %struct.Member* %153, i32 0, i32 1
  store %struct.Type* %152, %struct.Type** %154, align 8
  %155 = load %struct.Member*, %struct.Member** %15, align 8
  %156 = getelementptr inbounds %struct.Member, %struct.Member* %155, i32 0, i32 4
  store i32 0, i32* %156, align 8
  %157 = load %struct.Member*, %struct.Member** %15, align 8
  %158 = getelementptr inbounds %struct.Member, %struct.Member* %157, i32 0, i32 1
  %159 = load %struct.Type*, %struct.Type** %158, align 8
  %160 = getelementptr inbounds %struct.Type, %struct.Type* %159, i32 0, i32 2
  %161 = load i32, i32* %160, align 8
  %162 = load %struct.Member*, %struct.Member** %15, align 8
  %163 = getelementptr inbounds %struct.Member, %struct.Member* %162, i32 0, i32 5
  store i32 %161, i32* %163, align 4
  %164 = load %struct.Member*, %struct.Member** %15, align 8
  %165 = load %struct.Member*, %struct.Member** %8, align 8
  %166 = getelementptr inbounds %struct.Member, %struct.Member* %165, i32 0, i32 0
  store %struct.Member* %164, %struct.Member** %166, align 8
  store %struct.Member* %164, %struct.Member** %8, align 8
  br label %167

167:                                              ; preds = %151, %142
  %168 = load %struct.Member*, %struct.Member** %8, align 8
  %169 = icmp ne %struct.Member* %168, %7
  br i1 %169, label %170, label %195

170:                                              ; preds = %167
  %171 = load %struct.Member*, %struct.Member** %8, align 8
  %172 = getelementptr inbounds %struct.Member, %struct.Member* %171, i32 0, i32 1
  %173 = load %struct.Type*, %struct.Type** %172, align 8
  %174 = getelementptr inbounds %struct.Type, %struct.Type* %173, i32 0, i32 0
  %175 = load i32, i32* %174, align 8
  %176 = icmp eq i32 %175, 12
  br i1 %176, label %177, label %195

177:                                              ; preds = %170
  %178 = load %struct.Member*, %struct.Member** %8, align 8
  %179 = getelementptr inbounds %struct.Member, %struct.Member* %178, i32 0, i32 1
  %180 = load %struct.Type*, %struct.Type** %179, align 8
  %181 = getelementptr inbounds %struct.Type, %struct.Type* %180, i32 0, i32 11
  %182 = load i32, i32* %181, align 8
  %183 = icmp slt i32 %182, 0
  br i1 %183, label %184, label %195

184:                                              ; preds = %177
  %185 = load %struct.Member*, %struct.Member** %8, align 8
  %186 = getelementptr inbounds %struct.Member, %struct.Member* %185, i32 0, i32 1
  %187 = load %struct.Type*, %struct.Type** %186, align 8
  %188 = getelementptr inbounds %struct.Type, %struct.Type* %187, i32 0, i32 8
  %189 = load %struct.Type*, %struct.Type** %188, align 8
  %190 = call %struct.Type* @array_of(%struct.Type* noundef %189, i32 noundef 0)
  %191 = load %struct.Member*, %struct.Member** %8, align 8
  %192 = getelementptr inbounds %struct.Member, %struct.Member* %191, i32 0, i32 1
  store %struct.Type* %190, %struct.Type** %192, align 8
  %193 = load %struct.Type*, %struct.Type** %6, align 8
  %194 = getelementptr inbounds %struct.Type, %struct.Type* %193, i32 0, i32 15
  store i8 1, i8* %194, align 8
  br label %195

195:                                              ; preds = %184, %177, %170, %167
  %196 = load %struct.Token*, %struct.Token** %5, align 8
  %197 = getelementptr inbounds %struct.Token, %struct.Token* %196, i32 0, i32 1
  %198 = load %struct.Token*, %struct.Token** %197, align 8
  %199 = load %struct.Token**, %struct.Token*** %4, align 8
  store %struct.Token* %198, %struct.Token** %199, align 8
  %200 = getelementptr inbounds %struct.Member, %struct.Member* %7, i32 0, i32 0
  %201 = load %struct.Member*, %struct.Member** %200, align 8
  %202 = load %struct.Type*, %struct.Type** %6, align 8
  %203 = getelementptr inbounds %struct.Type, %struct.Type* %202, i32 0, i32 14
  store %struct.Member* %201, %struct.Member** %203, align 8
  ret void
}

declare void @hashmap_put2(%struct.HashMap* noundef, i8* noundef, i32 noundef, i8* noundef) #1

declare %struct.Type* @enum_type() #1

; Function Attrs: noinline nounwind optnone uwtable
define internal void @create_param_lvars(%struct.Type* noundef %0, i8* noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca i8*, align 8
  store %struct.Type* %0, %struct.Type** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %struct.Type*, %struct.Type** %3, align 8
  %6 = icmp ne %struct.Type* %5, null
  br i1 %6, label %7, label %27

7:                                                ; preds = %2
  %8 = load %struct.Type*, %struct.Type** %3, align 8
  %9 = getelementptr inbounds %struct.Type, %struct.Type* %8, i32 0, i32 20
  %10 = load %struct.Type*, %struct.Type** %9, align 8
  %11 = load i8*, i8** %4, align 8
  call void @create_param_lvars(%struct.Type* noundef %10, i8* noundef %11)
  %12 = load %struct.Type*, %struct.Type** %3, align 8
  %13 = getelementptr inbounds %struct.Type, %struct.Type* %12, i32 0, i32 9
  %14 = load %struct.Token*, %struct.Token** %13, align 8
  %15 = icmp ne %struct.Token* %14, null
  br i1 %15, label %17, label %16

16:                                               ; preds = %7
  br label %27

17:                                               ; preds = %7
  %18 = load %struct.Type*, %struct.Type** %3, align 8
  %19 = getelementptr inbounds %struct.Type, %struct.Type* %18, i32 0, i32 9
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  %21 = call i8* @get_ident(%struct.Token* noundef %20)
  %22 = load %struct.Type*, %struct.Type** %3, align 8
  %23 = load i8*, i8** %4, align 8
  %24 = call %struct.Obj* @new_lvar(i8* noundef %21, %struct.Type* noundef %22, i8* noundef %23)
  %25 = load i32, i32* @order, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, i32* @order, align 4
  br label %27

27:                                               ; preds = %16, %17, %2
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.Token* @skip_excess_element2(%struct.Token* noundef %0) #0 {
  %2 = alloca %struct.Token*, align 8
  store %struct.Token* %0, %struct.Token** %2, align 8
  %3 = load %struct.Token*, %struct.Token** %2, align 8
  %4 = call zeroext i1 @equal(%struct.Token* noundef %3, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.87, i64 0, i64 0))
  br i1 %4, label %10, label %5

5:                                                ; preds = %1
  %6 = load %struct.Token*, %struct.Token** %2, align 8
  %7 = getelementptr inbounds %struct.Token, %struct.Token* %6, i32 0, i32 1
  %8 = load %struct.Token*, %struct.Token** %7, align 8
  %9 = call %struct.Token* @skip_excess_element2(%struct.Token* noundef %8)
  store %struct.Token* %9, %struct.Token** %2, align 8
  br label %10

10:                                               ; preds = %5, %1
  %11 = load %struct.Token*, %struct.Token** %2, align 8
  ret %struct.Token* %11
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @resolve_goto_labels() #0 {
  %1 = alloca %struct.Node*, align 8
  %2 = alloca %struct.Node*, align 8
  %3 = load %struct.Node*, %struct.Node** @gotos, align 8
  store %struct.Node* %3, %struct.Node** %1, align 8
  br label %4

4:                                                ; preds = %44, %0
  %5 = load %struct.Node*, %struct.Node** %1, align 8
  %6 = icmp ne %struct.Node* %5, null
  br i1 %6, label %7, label %48

7:                                                ; preds = %4
  %8 = load %struct.Node*, %struct.Node** @labels, align 8
  store %struct.Node* %8, %struct.Node** %2, align 8
  br label %9

9:                                                ; preds = %28, %7
  %10 = load %struct.Node*, %struct.Node** %2, align 8
  %11 = icmp ne %struct.Node* %10, null
  br i1 %11, label %12, label %32

12:                                               ; preds = %9
  %13 = load %struct.Node*, %struct.Node** %1, align 8
  %14 = getelementptr inbounds %struct.Node, %struct.Node* %13, i32 0, i32 19
  %15 = load i8*, i8** %14, align 8
  %16 = load %struct.Node*, %struct.Node** %2, align 8
  %17 = getelementptr inbounds %struct.Node, %struct.Node* %16, i32 0, i32 19
  %18 = load i8*, i8** %17, align 8
  %19 = call i32 @strcmp(i8* noundef %15, i8* noundef %18) #11
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %27, label %21

21:                                               ; preds = %12
  %22 = load %struct.Node*, %struct.Node** %2, align 8
  %23 = getelementptr inbounds %struct.Node, %struct.Node* %22, i32 0, i32 20
  %24 = load i8*, i8** %23, align 16
  %25 = load %struct.Node*, %struct.Node** %1, align 8
  %26 = getelementptr inbounds %struct.Node, %struct.Node* %25, i32 0, i32 20
  store i8* %24, i8** %26, align 16
  br label %32

27:                                               ; preds = %12
  br label %28

28:                                               ; preds = %27
  %29 = load %struct.Node*, %struct.Node** %2, align 8
  %30 = getelementptr inbounds %struct.Node, %struct.Node* %29, i32 0, i32 21
  %31 = load %struct.Node*, %struct.Node** %30, align 8
  store %struct.Node* %31, %struct.Node** %2, align 8
  br label %9, !llvm.loop !67

32:                                               ; preds = %21, %9
  %33 = load %struct.Node*, %struct.Node** %1, align 8
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 20
  %35 = load i8*, i8** %34, align 16
  %36 = icmp eq i8* %35, null
  br i1 %36, label %37, label %43

37:                                               ; preds = %32
  %38 = load %struct.Node*, %struct.Node** %1, align 8
  %39 = getelementptr inbounds %struct.Node, %struct.Node* %38, i32 0, i32 3
  %40 = load %struct.Token*, %struct.Token** %39, align 8
  %41 = getelementptr inbounds %struct.Token, %struct.Token* %40, i32 0, i32 1
  %42 = load %struct.Token*, %struct.Token** %41, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %42, i8* noundef getelementptr inbounds ([53 x i8], [53 x i8]* @.str.241, i64 0, i64 0), i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #9
  unreachable

43:                                               ; preds = %32
  br label %44

44:                                               ; preds = %43
  %45 = load %struct.Node*, %struct.Node** %1, align 8
  %46 = getelementptr inbounds %struct.Node, %struct.Node* %45, i32 0, i32 21
  %47 = load %struct.Node*, %struct.Node** %46, align 8
  store %struct.Node* %47, %struct.Node** %1, align 8
  br label %4, !llvm.loop !68

48:                                               ; preds = %4
  store %struct.Node* null, %struct.Node** @labels, align 8
  store %struct.Node* null, %struct.Node** @gotos, align 8
  ret void
}

; Function Attrs: nounwind readonly willreturn
declare i32 @strcmp(i8* noundef, i8* noundef) #5

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind readonly willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { argmemonly nofree nounwind willreturn writeonly }
attributes #7 = { argmemonly nofree nounwind willreturn }
attributes #8 = { nounwind }
attributes #9 = { noreturn }
attributes #10 = { noreturn nounwind }
attributes #11 = { nounwind readonly willreturn }

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
!52 = distinct !{!52, !7}
!53 = distinct !{!53, !7}
!54 = distinct !{!54, !7}
!55 = distinct !{!55, !7}
!56 = distinct !{!56, !7}
!57 = distinct !{!57, !7}
!58 = distinct !{!58, !7}
!59 = distinct !{!59, !7}
!60 = distinct !{!60, !7}
!61 = distinct !{!61, !7}
!62 = distinct !{!62, !7}
!63 = distinct !{!63, !7}
!64 = distinct !{!64, !7}
!65 = distinct !{!65, !7}
!66 = distinct !{!66, !7}
!67 = distinct !{!67, !7}
!68 = distinct !{!68, !7}
