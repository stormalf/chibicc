; ModuleID = 'codegen.c'
source_filename = "codegen.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

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
%struct.__va_list_tag = type { i32, i32, i8*, i8* }
%union.anon = type { float }
%union.anon.0 = type { double }
%union.anon.1 = type { x86_fp80 }

@.str = private unnamed_addr constant [4 x i8] c"%dl\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%dx\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"%edx\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"%rdx\00", align 1
@.str.4 = private unnamed_addr constant [24 x i8] c"internal error at %s:%d\00", align 1
@.str.5 = private unnamed_addr constant [10 x i8] c"codegen.c\00", align 1
@.str.6 = private unnamed_addr constant [4 x i8] c"%bl\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"%bx\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"%ebx\00", align 1
@.str.9 = private unnamed_addr constant [5 x i8] c"%rbx\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"%cl\00", align 1
@.str.11 = private unnamed_addr constant [4 x i8] c"%cx\00", align 1
@.str.12 = private unnamed_addr constant [5 x i8] c"%ecx\00", align 1
@.str.13 = private unnamed_addr constant [5 x i8] c"%rcx\00", align 1
@.str.14 = private unnamed_addr constant [4 x i8] c"%al\00", align 1
@.str.15 = private unnamed_addr constant [4 x i8] c"%ax\00", align 1
@.str.16 = private unnamed_addr constant [5 x i8] c"%eax\00", align 1
@.str.17 = private unnamed_addr constant [5 x i8] c"%rax\00", align 1
@output_file = internal global %struct._IO_FILE* null, align 8
@.str.18 = private unnamed_addr constant [16 x i8] c"  .file %d \22%s\22\00", align 1
@.str.19 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.20 = private unnamed_addr constant [12 x i8] c"  .local %s\00", align 1
@.str.21 = private unnamed_addr constant [12 x i8] c"  .globl %s\00", align 1
@opt_fcommon = external global i8, align 1
@.str.22 = private unnamed_addr constant [19 x i8] c"  .comm %s, %d, %d\00", align 1
@.str.23 = private unnamed_addr constant [34 x i8] c"  .section .tdata,\22awT\22,@progbits\00", align 1
@.str.24 = private unnamed_addr constant [8 x i8] c"  .data\00", align 1
@.str.25 = private unnamed_addr constant [20 x i8] c"  .type %s, @object\00", align 1
@.str.26 = private unnamed_addr constant [15 x i8] c"  .size %s, %d\00", align 1
@.str.27 = private unnamed_addr constant [12 x i8] c"  .align %d\00", align 1
@.str.28 = private unnamed_addr constant [4 x i8] c"%s:\00", align 1
@.str.29 = private unnamed_addr constant [15 x i8] c"  .quad %s%+ld\00", align 1
@.str.30 = private unnamed_addr constant [11 x i8] c"  .byte %d\00", align 1
@.str.31 = private unnamed_addr constant [31 x i8] c"  .section .tbss,\22awT\22,@nobits\00", align 1
@.str.32 = private unnamed_addr constant [7 x i8] c"  .bss\00", align 1
@.str.33 = private unnamed_addr constant [11 x i8] c"  .zero %d\00", align 1
@.str.34 = private unnamed_addr constant [8 x i8] c"  .text\00", align 1
@.str.35 = private unnamed_addr constant [22 x i8] c"  .type %s, @function\00", align 1
@current_fn = internal global %struct.Obj* null, align 8
@.str.36 = private unnamed_addr constant [13 x i8] c"  push %%rbp\00", align 1
@.str.37 = private unnamed_addr constant [19 x i8] c"  mov %%rsp, %%rbp\00", align 1
@.str.38 = private unnamed_addr constant [17 x i8] c"  sub $%d, %%rsp\00", align 1
@.str.39 = private unnamed_addr constant [23 x i8] c"  mov %%rsp, %d(%%rbp)\00", align 1
@.str.40 = private unnamed_addr constant [22 x i8] c"  movl $%d, %d(%%rbp)\00", align 1
@.str.41 = private unnamed_addr constant [24 x i8] c"  movq %%rbp, %d(%%rbp)\00", align 1
@.str.42 = private unnamed_addr constant [22 x i8] c"  addq $16, %d(%%rbp)\00", align 1
@.str.43 = private unnamed_addr constant [22 x i8] c"  addq $%d, %d(%%rbp)\00", align 1
@.str.44 = private unnamed_addr constant [24 x i8] c"  movq %%rdi, %d(%%rbp)\00", align 1
@.str.45 = private unnamed_addr constant [24 x i8] c"  movq %%rsi, %d(%%rbp)\00", align 1
@.str.46 = private unnamed_addr constant [24 x i8] c"  movq %%rdx, %d(%%rbp)\00", align 1
@.str.47 = private unnamed_addr constant [24 x i8] c"  movq %%rcx, %d(%%rbp)\00", align 1
@.str.48 = private unnamed_addr constant [23 x i8] c"  movq %%r8, %d(%%rbp)\00", align 1
@.str.49 = private unnamed_addr constant [23 x i8] c"  movq %%r9, %d(%%rbp)\00", align 1
@.str.50 = private unnamed_addr constant [26 x i8] c"  movsd %%xmm0, %d(%%rbp)\00", align 1
@.str.51 = private unnamed_addr constant [26 x i8] c"  movsd %%xmm1, %d(%%rbp)\00", align 1
@.str.52 = private unnamed_addr constant [26 x i8] c"  movsd %%xmm2, %d(%%rbp)\00", align 1
@.str.53 = private unnamed_addr constant [26 x i8] c"  movsd %%xmm3, %d(%%rbp)\00", align 1
@.str.54 = private unnamed_addr constant [26 x i8] c"  movsd %%xmm4, %d(%%rbp)\00", align 1
@.str.55 = private unnamed_addr constant [26 x i8] c"  movsd %%xmm5, %d(%%rbp)\00", align 1
@.str.56 = private unnamed_addr constant [26 x i8] c"  movsd %%xmm6, %d(%%rbp)\00", align 1
@.str.57 = private unnamed_addr constant [26 x i8] c"  movsd %%xmm7, %d(%%rbp)\00", align 1
@.str.58 = private unnamed_addr constant [15 x i8] c"ty->size <= 16\00", align 1
@__PRETTY_FUNCTION__.emit_text = private unnamed_addr constant [22 x i8] c"void emit_text(Obj *)\00", align 1
@depth = internal global i32 0, align 4
@.str.59 = private unnamed_addr constant [11 x i8] c"depth == 0\00", align 1
@.str.60 = private unnamed_addr constant [5 x i8] c"main\00", align 1
@.str.61 = private unnamed_addr constant [16 x i8] c"  mov $0, %%rax\00", align 1
@.str.62 = private unnamed_addr constant [14 x i8] c".L.return.%s:\00", align 1
@.str.63 = private unnamed_addr constant [19 x i8] c"  mov %%rbp, %%rsp\00", align 1
@.str.64 = private unnamed_addr constant [12 x i8] c"  pop %%rbp\00", align 1
@.str.65 = private unnamed_addr constant [6 x i8] c"  ret\00", align 1
@.str.66 = private unnamed_addr constant [27 x i8] c"  movss %%xmm%d, %d(%%rbp)\00", align 1
@.str.67 = private unnamed_addr constant [27 x i8] c"  movsd %%xmm%d, %d(%%rbp)\00", align 1
@.str.68 = private unnamed_addr constant [20 x i8] c"  mov %s, %d(%%rbp)\00", align 1
@argreg8 = internal global [6 x i8*] [i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.70, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.71, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.72, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.73, i32 0, i32 0)], align 16
@argreg16 = internal global [6 x i8*] [i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.74, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.76, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.77, i32 0, i32 0)], align 16
@argreg32 = internal global [6 x i8*] [i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.78, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.79, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.80, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.81, i32 0, i32 0)], align 16
@argreg64 = internal global [6 x i8*] [i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.83, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.84, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.85, i32 0, i32 0)], align 16
@.str.69 = private unnamed_addr constant [13 x i8] c"  shr $8, %s\00", align 1
@.str.70 = private unnamed_addr constant [5 x i8] c"%dil\00", align 1
@.str.71 = private unnamed_addr constant [5 x i8] c"%sil\00", align 1
@.str.72 = private unnamed_addr constant [5 x i8] c"%r8b\00", align 1
@.str.73 = private unnamed_addr constant [5 x i8] c"%r9b\00", align 1
@.str.74 = private unnamed_addr constant [4 x i8] c"%di\00", align 1
@.str.75 = private unnamed_addr constant [4 x i8] c"%si\00", align 1
@.str.76 = private unnamed_addr constant [5 x i8] c"%r8w\00", align 1
@.str.77 = private unnamed_addr constant [5 x i8] c"%r9w\00", align 1
@.str.78 = private unnamed_addr constant [5 x i8] c"%edi\00", align 1
@.str.79 = private unnamed_addr constant [5 x i8] c"%esi\00", align 1
@.str.80 = private unnamed_addr constant [5 x i8] c"%r8d\00", align 1
@.str.81 = private unnamed_addr constant [5 x i8] c"%r9d\00", align 1
@.str.82 = private unnamed_addr constant [5 x i8] c"%rdi\00", align 1
@.str.83 = private unnamed_addr constant [5 x i8] c"%rsi\00", align 1
@.str.84 = private unnamed_addr constant [4 x i8] c"%r8\00", align 1
@.str.85 = private unnamed_addr constant [4 x i8] c"%r9\00", align 1
@.str.86 = private unnamed_addr constant [13 x i8] c"  .loc %d %d\00", align 1
@.str.87 = private unnamed_addr constant [17 x i8] c"  je  .L.else.%d\00", align 1
@.str.88 = private unnamed_addr constant [16 x i8] c"  jmp .L.end.%d\00", align 1
@.str.89 = private unnamed_addr constant [12 x i8] c".L.else.%d:\00", align 1
@.str.90 = private unnamed_addr constant [11 x i8] c".L.end.%d:\00", align 1
@.str.91 = private unnamed_addr constant [13 x i8] c".L.begin.%d:\00", align 1
@.str.92 = private unnamed_addr constant [8 x i8] c"  je %s\00", align 1
@.str.93 = private unnamed_addr constant [18 x i8] c"  jmp .L.begin.%d\00", align 1
@.str.94 = private unnamed_addr constant [18 x i8] c"  jne .L.begin.%d\00", align 1
@.str.95 = private unnamed_addr constant [15 x i8] c"  cmp $%ld, %s\00", align 1
@.str.96 = private unnamed_addr constant [13 x i8] c"  mov %s, %s\00", align 1
@.str.97 = private unnamed_addr constant [15 x i8] c"  sub $%ld, %s\00", align 1
@.str.98 = private unnamed_addr constant [9 x i8] c"  jbe %s\00", align 1
@.str.99 = private unnamed_addr constant [9 x i8] c"  jmp %s\00", align 1
@.str.100 = private unnamed_addr constant [13 x i8] c"  jmp *%%rax\00", align 1
@.str.101 = private unnamed_addr constant [19 x i8] c"  jmp .L.return.%s\00", align 1
@.str.102 = private unnamed_addr constant [5 x i8] c"  %s\00", align 1
@.str.103 = private unnamed_addr constant [21 x i8] c"%s invalid statement\00", align 1
@count.i = internal global i32 1, align 4
@.str.104 = private unnamed_addr constant [30 x i8] c"  mov $%u, %%eax  # float %Lf\00", align 1
@.str.105 = private unnamed_addr constant [21 x i8] c"  movq %%rax, %%xmm0\00", align 1
@.str.106 = private unnamed_addr constant [32 x i8] c"  mov $%lu, %%rax  # double %Lf\00", align 1
@.str.107 = private unnamed_addr constant [37 x i8] c"  mov $%lu, %%rax  # long double %Lf\00", align 1
@.str.108 = private unnamed_addr constant [24 x i8] c"  mov %%rax, -16(%%rsp)\00", align 1
@.str.109 = private unnamed_addr constant [18 x i8] c"  mov $%lu, %%rax\00", align 1
@.str.110 = private unnamed_addr constant [23 x i8] c"  mov %%rax, -8(%%rsp)\00", align 1
@.str.111 = private unnamed_addr constant [18 x i8] c"  fldt -16(%%rsp)\00", align 1
@.str.112 = private unnamed_addr constant [18 x i8] c"  mov $%ld, %%rax\00", align 1
@.str.113 = private unnamed_addr constant [16 x i8] c"  mov $1, %%rax\00", align 1
@.str.114 = private unnamed_addr constant [17 x i8] c"  shl $31, %%rax\00", align 1
@.str.115 = private unnamed_addr constant [21 x i8] c"  movq %%rax, %%xmm1\00", align 1
@.str.116 = private unnamed_addr constant [23 x i8] c"  xorps %%xmm1, %%xmm0\00", align 1
@.str.117 = private unnamed_addr constant [17 x i8] c"  shl $63, %%rax\00", align 1
@.str.118 = private unnamed_addr constant [23 x i8] c"  xorpd %%xmm1, %%xmm0\00", align 1
@.str.119 = private unnamed_addr constant [7 x i8] c"  fchs\00", align 1
@.str.120 = private unnamed_addr constant [12 x i8] c"  neg %%rax\00", align 1
@.str.121 = private unnamed_addr constant [17 x i8] c"  shl $%d, %%rax\00", align 1
@.str.122 = private unnamed_addr constant [17 x i8] c"  shr $%d, %%rax\00", align 1
@.str.123 = private unnamed_addr constant [17 x i8] c"  sar $%d, %%rax\00", align 1
@.str.124 = private unnamed_addr constant [18 x i8] c"  mov %%rax, %%r8\00", align 1
@.str.125 = private unnamed_addr constant [19 x i8] c"  mov %%rax, %%rdi\00", align 1
@.str.126 = private unnamed_addr constant [19 x i8] c"  and %%rax, %%rdi\00", align 1
@.str.127 = private unnamed_addr constant [18 x i8] c"  and $%ld, %%rdi\00", align 1
@.str.128 = private unnamed_addr constant [17 x i8] c"  shl $%d, %%rdi\00", align 1
@.str.129 = private unnamed_addr constant [21 x i8] c"  mov (%%rsp), %%rax\00", align 1
@.str.130 = private unnamed_addr constant [17 x i8] c"  mov $%ld, %%r9\00", align 1
@.str.131 = private unnamed_addr constant [18 x i8] c"  and %%r9, %%rax\00", align 1
@.str.132 = private unnamed_addr constant [18 x i8] c"  or %%rdi, %%rax\00", align 1
@.str.133 = private unnamed_addr constant [18 x i8] c"  mov %%r8, %%rax\00", align 1
@.str.134 = private unnamed_addr constant [17 x i8] c"  mov $%d, %%rcx\00", align 1
@.str.135 = private unnamed_addr constant [23 x i8] c"  lea %d(%%rbp), %%rdi\00", align 1
@.str.136 = private unnamed_addr constant [15 x i8] c"  mov $0, %%al\00", align 1
@.str.137 = private unnamed_addr constant [12 x i8] c"  rep stosb\00", align 1
@.str.138 = private unnamed_addr constant [16 x i8] c"  je .L.else.%d\00", align 1
@.str.139 = private unnamed_addr constant [12 x i8] c"  sete %%al\00", align 1
@.str.140 = private unnamed_addr constant [20 x i8] c"  movzx %%al, %%rax\00", align 1
@.str.141 = private unnamed_addr constant [12 x i8] c"  not %%rax\00", align 1
@.str.142 = private unnamed_addr constant [17 x i8] c"  je .L.false.%d\00", align 1
@.str.143 = private unnamed_addr constant [13 x i8] c".L.false.%d:\00", align 1
@.str.144 = private unnamed_addr constant [17 x i8] c"  jne .L.true.%d\00", align 1
@.str.145 = private unnamed_addr constant [12 x i8] c".L.true.%d:\00", align 1
@.str.146 = private unnamed_addr constant [7 x i8] c"alloca\00", align 1
@.str.147 = private unnamed_addr constant [19 x i8] c"  mov %%rax, %%r10\00", align 1
@.str.148 = private unnamed_addr constant [17 x i8] c"  mov $%d, %%rax\00", align 1
@.str.149 = private unnamed_addr constant [14 x i8] c"  call *%%r10\00", align 1
@.str.150 = private unnamed_addr constant [17 x i8] c"  add $%d, %%rsp\00", align 1
@.str.151 = private unnamed_addr constant [20 x i8] c"  movzx %%al, %%eax\00", align 1
@.str.152 = private unnamed_addr constant [21 x i8] c"  movzbl %%al, %%eax\00", align 1
@.str.153 = private unnamed_addr constant [21 x i8] c"  movsbl %%al, %%eax\00", align 1
@.str.154 = private unnamed_addr constant [21 x i8] c"  movzwl %%ax, %%eax\00", align 1
@.str.155 = private unnamed_addr constant [21 x i8] c"  movswl %%ax, %%eax\00", align 1
@.str.156 = private unnamed_addr constant [23 x i8] c"  lea %d(%%rbp), %%rax\00", align 1
@.str.157 = private unnamed_addr constant [23 x i8] c"  lea %s(%%rip), %%rax\00", align 1
@.str.158 = private unnamed_addr constant [27 x i8] c"  lock cmpxchg %s, (%%rdi)\00", align 1
@.str.159 = private unnamed_addr constant [12 x i8] c"  sete %%cl\00", align 1
@.str.160 = private unnamed_addr constant [8 x i8] c"  je 1f\00", align 1
@.str.161 = private unnamed_addr constant [17 x i8] c"  mov %s, (%%r8)\00", align 1
@.str.162 = private unnamed_addr constant [3 x i8] c"1:\00", align 1
@.str.163 = private unnamed_addr constant [21 x i8] c"  movzbl %%cl, %%eax\00", align 1
@.str.164 = private unnamed_addr constant [19 x i8] c"  xchg %s, (%%rdi)\00", align 1
@.str.165 = private unnamed_addr constant [3 x i8] c"ss\00", align 1
@.str.166 = private unnamed_addr constant [3 x i8] c"sd\00", align 1
@.str.167 = private unnamed_addr constant [23 x i8] c"  add%s %%xmm1, %%xmm0\00", align 1
@.str.168 = private unnamed_addr constant [23 x i8] c"  sub%s %%xmm1, %%xmm0\00", align 1
@.str.169 = private unnamed_addr constant [23 x i8] c"  mul%s %%xmm1, %%xmm0\00", align 1
@.str.170 = private unnamed_addr constant [23 x i8] c"  div%s %%xmm1, %%xmm0\00", align 1
@.str.171 = private unnamed_addr constant [25 x i8] c"  ucomi%s %%xmm0, %%xmm1\00", align 1
@.str.172 = private unnamed_addr constant [13 x i8] c"  setnp %%dl\00", align 1
@.str.173 = private unnamed_addr constant [17 x i8] c"  and %%dl, %%al\00", align 1
@.str.174 = private unnamed_addr constant [13 x i8] c"  setne %%al\00", align 1
@.str.175 = private unnamed_addr constant [12 x i8] c"  setp %%dl\00", align 1
@.str.176 = private unnamed_addr constant [16 x i8] c"  or %%dl, %%al\00", align 1
@.str.177 = private unnamed_addr constant [12 x i8] c"  seta %%al\00", align 1
@.str.178 = private unnamed_addr constant [13 x i8] c"  setae %%al\00", align 1
@.str.179 = private unnamed_addr constant [15 x i8] c"  and $1, %%al\00", align 1
@.str.180 = private unnamed_addr constant [20 x i8] c"  movzb %%al, %%rax\00", align 1
@.str.181 = private unnamed_addr constant [22 x i8] c"%s invalid expression\00", align 1
@.str.182 = private unnamed_addr constant [8 x i8] c"  faddp\00", align 1
@.str.183 = private unnamed_addr constant [9 x i8] c"  fsubrp\00", align 1
@.str.184 = private unnamed_addr constant [8 x i8] c"  fmulp\00", align 1
@.str.185 = private unnamed_addr constant [9 x i8] c"  fdivrp\00", align 1
@.str.186 = private unnamed_addr constant [9 x i8] c"  fcomip\00", align 1
@.str.187 = private unnamed_addr constant [15 x i8] c"  fstp %%st(0)\00", align 1
@.str.188 = private unnamed_addr constant [13 x i8] c"  add %s, %s\00", align 1
@.str.189 = private unnamed_addr constant [13 x i8] c"  sub %s, %s\00", align 1
@.str.190 = private unnamed_addr constant [14 x i8] c"  imul %s, %s\00", align 1
@.str.191 = private unnamed_addr constant [13 x i8] c"  mov $0, %s\00", align 1
@.str.192 = private unnamed_addr constant [9 x i8] c"  div %s\00", align 1
@.str.193 = private unnamed_addr constant [6 x i8] c"  cqo\00", align 1
@.str.194 = private unnamed_addr constant [6 x i8] c"  cdq\00", align 1
@.str.195 = private unnamed_addr constant [10 x i8] c"  idiv %s\00", align 1
@.str.196 = private unnamed_addr constant [19 x i8] c"  mov %%rdx, %%rax\00", align 1
@.str.197 = private unnamed_addr constant [13 x i8] c"  and %s, %s\00", align 1
@.str.198 = private unnamed_addr constant [12 x i8] c"  or %s, %s\00", align 1
@.str.199 = private unnamed_addr constant [13 x i8] c"  xor %s, %s\00", align 1
@.str.200 = private unnamed_addr constant [13 x i8] c"  cmp %s, %s\00", align 1
@.str.201 = private unnamed_addr constant [12 x i8] c"  setb %%al\00", align 1
@.str.202 = private unnamed_addr constant [12 x i8] c"  setl %%al\00", align 1
@.str.203 = private unnamed_addr constant [13 x i8] c"  setbe %%al\00", align 1
@.str.204 = private unnamed_addr constant [13 x i8] c"  setle %%al\00", align 1
@.str.205 = private unnamed_addr constant [19 x i8] c"  mov %%rdi, %%rcx\00", align 1
@.str.206 = private unnamed_addr constant [15 x i8] c"  shl %%cl, %s\00", align 1
@.str.207 = private unnamed_addr constant [15 x i8] c"  shr %%cl, %s\00", align 1
@.str.208 = private unnamed_addr constant [15 x i8] c"  sar %%cl, %s\00", align 1
@.str.209 = private unnamed_addr constant [23 x i8] c"  mov %d(%%rbp), %%rax\00", align 1
@opt_fpic = external global i8, align 1
@.str.210 = private unnamed_addr constant [36 x i8] c"  data16 lea %s@tlsgd(%%rip), %%rdi\00", align 1
@.str.211 = private unnamed_addr constant [16 x i8] c"  .value 0x6666\00", align 1
@.str.212 = private unnamed_addr constant [8 x i8] c"  rex64\00", align 1
@.str.213 = private unnamed_addr constant [26 x i8] c"  call __tls_get_addr@PLT\00", align 1
@.str.214 = private unnamed_addr constant [32 x i8] c"  mov %s@GOTPCREL(%%rip), %%rax\00", align 1
@.str.215 = private unnamed_addr constant [20 x i8] c"  mov %%fs:0, %%rax\00", align 1
@.str.216 = private unnamed_addr constant [23 x i8] c"  add $%s@tpoff, %%rax\00", align 1
@.str.217 = private unnamed_addr constant [17 x i8] c"  add $%d, %%rax\00", align 1
@.str.218 = private unnamed_addr constant [17 x i8] c"%s not an lvalue\00", align 1
@.str.219 = private unnamed_addr constant [24 x i8] c"  movss (%%rax), %%xmm0\00", align 1
@.str.220 = private unnamed_addr constant [24 x i8] c"  movsd (%%rax), %%xmm0\00", align 1
@.str.221 = private unnamed_addr constant [15 x i8] c"  fldt (%%rax)\00", align 1
@.str.222 = private unnamed_addr constant [5 x i8] c"movz\00", align 1
@.str.223 = private unnamed_addr constant [5 x i8] c"movs\00", align 1
@.str.224 = private unnamed_addr constant [22 x i8] c"  %sbl (%%rax), %%eax\00", align 1
@.str.225 = private unnamed_addr constant [22 x i8] c"  %swl (%%rax), %%eax\00", align 1
@.str.226 = private unnamed_addr constant [24 x i8] c"  movsxd (%%rax), %%rax\00", align 1
@.str.227 = private unnamed_addr constant [21 x i8] c"  mov (%%rax), %%rax\00", align 1
@.str.228 = private unnamed_addr constant [13 x i8] c"  push %%rax\00", align 1
@.str.229 = private unnamed_addr constant [23 x i8] c"  mov %d(%%rax), %%r8b\00", align 1
@.str.230 = private unnamed_addr constant [23 x i8] c"  mov %%r8b, %d(%%rdi)\00", align 1
@.str.231 = private unnamed_addr constant [24 x i8] c"  movss %%xmm0, (%%rdi)\00", align 1
@.str.232 = private unnamed_addr constant [24 x i8] c"  movsd %%xmm0, (%%rdi)\00", align 1
@.str.233 = private unnamed_addr constant [16 x i8] c"  fstpt (%%rdi)\00", align 1
@.str.234 = private unnamed_addr constant [20 x i8] c"  mov %%al, (%%rdi)\00", align 1
@.str.235 = private unnamed_addr constant [20 x i8] c"  mov %%ax, (%%rdi)\00", align 1
@.str.236 = private unnamed_addr constant [21 x i8] c"  mov %%eax, (%%rdi)\00", align 1
@.str.237 = private unnamed_addr constant [21 x i8] c"  mov %%rax, (%%rdi)\00", align 1
@cast_table = internal global [11 x [11 x i8*]] [[11 x i8*] [i8* null, i8* null, i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u16, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f32, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f64, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @i32f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i8, i32 0, i32 0), i8* null, i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u16, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f32, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f64, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @i32f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i16, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u16, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f32, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f64, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @i32f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i16, i32 0, i32 0), i8* null, i8* null, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u16, i32 0, i32 0), i8* null, i8* null, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i64f32, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i64f64, i32 0, i32 0), i8* getelementptr inbounds ([37 x i8], [37 x i8]* @i64f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i8, i32 0, i32 0), i8* null, i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* null, i8* null, i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f32, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f64, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @i32f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i16, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u8, i32 0, i32 0), i8* null, i8* null, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @i32i64, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f32, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @i32f64, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @i32f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i16, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @u32i64, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u16, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @u32i64, i32 0, i32 0), i8* getelementptr inbounds ([38 x i8], [38 x i8]* @u32f32, i32 0, i32 0), i8* getelementptr inbounds ([38 x i8], [38 x i8]* @u32f64, i32 0, i32 0), i8* getelementptr inbounds ([52 x i8], [52 x i8]* @u32f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32i16, i32 0, i32 0), i8* null, i8* null, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u8, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @i32u16, i32 0, i32 0), i8* null, i8* null, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @u64f32, i32 0, i32 0), i8* getelementptr inbounds ([186 x i8], [186 x i8]* @u64f64, i32 0, i32 0), i8* getelementptr inbounds ([122 x i8], [122 x i8]* @u64f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([41 x i8], [41 x i8]* @f32i8, i32 0, i32 0), i8* getelementptr inbounds ([41 x i8], [41 x i8]* @f32i16, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @f32i32, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @f32i64, i32 0, i32 0), i8* getelementptr inbounds ([41 x i8], [41 x i8]* @f32u8, i32 0, i32 0), i8* getelementptr inbounds ([41 x i8], [41 x i8]* @f32u16, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @f32u32, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @f32u64, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @f32f64, i32 0, i32 0), i8* getelementptr inbounds ([37 x i8], [37 x i8]* @f32f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([41 x i8], [41 x i8]* @f64i8, i32 0, i32 0), i8* getelementptr inbounds ([41 x i8], [41 x i8]* @f64i16, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @f64i32, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @f64i64, i32 0, i32 0), i8* getelementptr inbounds ([41 x i8], [41 x i8]* @f64u8, i32 0, i32 0), i8* getelementptr inbounds ([41 x i8], [41 x i8]* @f64u16, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @f64u32, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @f64u64, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @f64f32, i32 0, i32 0), i8* null, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @f64f80, i32 0, i32 0)], [11 x i8*] [i8* getelementptr inbounds ([150 x i8], [150 x i8]* @f80i8, i32 0, i32 0), i8* getelementptr inbounds ([150 x i8], [150 x i8]* @f80i16, i32 0, i32 0), i8* getelementptr inbounds ([147 x i8], [147 x i8]* @f80i32, i32 0, i32 0), i8* getelementptr inbounds ([147 x i8], [147 x i8]* @f80i64, i32 0, i32 0), i8* getelementptr inbounds ([150 x i8], [150 x i8]* @f80u8, i32 0, i32 0), i8* getelementptr inbounds ([150 x i8], [150 x i8]* @f80u16, i32 0, i32 0), i8* getelementptr inbounds ([147 x i8], [147 x i8]* @f80u32, i32 0, i32 0), i8* getelementptr inbounds ([147 x i8], [147 x i8]* @f80u64, i32 0, i32 0), i8* getelementptr inbounds ([38 x i8], [38 x i8]* @f80f32, i32 0, i32 0), i8* getelementptr inbounds ([38 x i8], [38 x i8]* @f80f64, i32 0, i32 0), i8* null]], align 16
@i32i64 = internal global [18 x i8] c"movsxd %eax, %rax\00", align 16
@i32u8 = internal global [17 x i8] c"movzbl %al, %eax\00", align 16
@i32u16 = internal global [17 x i8] c"movzwl %ax, %eax\00", align 16
@i32f32 = internal global [22 x i8] c"cvtsi2ssl %eax, %xmm0\00", align 16
@i32f64 = internal global [22 x i8] c"cvtsi2sdl %eax, %xmm0\00", align 16
@i32f80 = internal global [35 x i8] c"mov %eax, -4(%rsp); fildl -4(%rsp)\00", align 16
@i32i8 = internal global [17 x i8] c"movsbl %al, %eax\00", align 16
@i32i16 = internal global [17 x i8] c"movswl %ax, %eax\00", align 16
@i64f32 = internal global [22 x i8] c"cvtsi2ssq %rax, %xmm0\00", align 16
@i64f64 = internal global [22 x i8] c"cvtsi2sdq %rax, %xmm0\00", align 16
@i64f80 = internal global [37 x i8] c"movq %rax, -8(%rsp); fildll -8(%rsp)\00", align 16
@u32i64 = internal global [15 x i8] c"mov %eax, %eax\00", align 1
@u32f32 = internal global [38 x i8] c"mov %eax, %eax; cvtsi2ssq %rax, %xmm0\00", align 16
@u32f64 = internal global [38 x i8] c"mov %eax, %eax; cvtsi2sdq %rax, %xmm0\00", align 16
@u32f80 = internal global [52 x i8] c"mov %eax, %eax; mov %rax, -8(%rsp); fildll -8(%rsp)\00", align 16
@u64f32 = internal global [22 x i8] c"cvtsi2ssq %rax, %xmm0\00", align 16
@u64f64 = internal global [186 x i8] c"test %rax,%rax; js 1f; pxor %xmm0,%xmm0; cvtsi2sd %rax,%xmm0; jmp 2f; 1: mov %rax,%rdi; and $1,%eax; pxor %xmm0,%xmm0; shr %rdi; or %rax,%rdi; cvtsi2sd %rdi,%xmm0; addsd %xmm0,%xmm0; 2:\00", align 16
@u64f80 = internal global [122 x i8] c"mov %rax, -8(%rsp); fildq -8(%rsp); test %rax, %rax; jns 1f;mov $1602224128, %eax; mov %eax, -4(%rsp); fadds -4(%rsp); 1:\00", align 16
@f32i8 = internal global [41 x i8] c"cvttss2sil %xmm0, %eax; movsbl %al, %eax\00", align 16
@f32i16 = internal global [41 x i8] c"cvttss2sil %xmm0, %eax; movswl %ax, %eax\00", align 16
@f32i32 = internal global [23 x i8] c"cvttss2sil %xmm0, %eax\00", align 16
@f32i64 = internal global [23 x i8] c"cvttss2siq %xmm0, %rax\00", align 16
@f32u8 = internal global [41 x i8] c"cvttss2sil %xmm0, %eax; movzbl %al, %eax\00", align 16
@f32u16 = internal global [41 x i8] c"cvttss2sil %xmm0, %eax; movzwl %ax, %eax\00", align 16
@f32u32 = internal global [23 x i8] c"cvttss2siq %xmm0, %rax\00", align 16
@f32u64 = internal global [23 x i8] c"cvttss2siq %xmm0, %rax\00", align 16
@f32f64 = internal global [22 x i8] c"cvtss2sd %xmm0, %xmm0\00", align 16
@f32f80 = internal global [37 x i8] c"movss %xmm0, -4(%rsp); flds -4(%rsp)\00", align 16
@f64i8 = internal global [41 x i8] c"cvttsd2sil %xmm0, %eax; movsbl %al, %eax\00", align 16
@f64i16 = internal global [41 x i8] c"cvttsd2sil %xmm0, %eax; movswl %ax, %eax\00", align 16
@f64i32 = internal global [23 x i8] c"cvttsd2sil %xmm0, %eax\00", align 16
@f64i64 = internal global [23 x i8] c"cvttsd2siq %xmm0, %rax\00", align 16
@f64u8 = internal global [41 x i8] c"cvttsd2sil %xmm0, %eax; movzbl %al, %eax\00", align 16
@f64u16 = internal global [41 x i8] c"cvttsd2sil %xmm0, %eax; movzwl %ax, %eax\00", align 16
@f64u32 = internal global [23 x i8] c"cvttsd2siq %xmm0, %rax\00", align 16
@f64u64 = internal global [23 x i8] c"cvttsd2siq %xmm0, %rax\00", align 16
@f64f32 = internal global [22 x i8] c"cvtsd2ss %xmm0, %xmm0\00", align 16
@f64f80 = internal global [37 x i8] c"movsd %xmm0, -8(%rsp); fldl -8(%rsp)\00", align 16
@f80i8 = internal global [150 x i8] c"fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; mov %ax, -12(%rsp); fldcw -12(%rsp); fistps -24(%rsp); fldcw -10(%rsp); movsbl -24(%rsp), %eax\00", align 16
@f80i16 = internal global [150 x i8] c"fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; mov %ax, -12(%rsp); fldcw -12(%rsp); fistps -24(%rsp); fldcw -10(%rsp); movzbl -24(%rsp), %eax\00", align 16
@f80i32 = internal global [147 x i8] c"fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; mov %ax, -12(%rsp); fldcw -12(%rsp); fistpl -24(%rsp); fldcw -10(%rsp); mov -24(%rsp), %eax\00", align 16
@f80i64 = internal global [147 x i8] c"fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; mov %ax, -12(%rsp); fldcw -12(%rsp); fistpq -24(%rsp); fldcw -10(%rsp); mov -24(%rsp), %rax\00", align 16
@f80u8 = internal global [150 x i8] c"fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; mov %ax, -12(%rsp); fldcw -12(%rsp); fistps -24(%rsp); fldcw -10(%rsp); movzbl -24(%rsp), %eax\00", align 16
@f80u16 = internal global [150 x i8] c"fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; mov %ax, -12(%rsp); fldcw -12(%rsp); fistpl -24(%rsp); fldcw -10(%rsp); movswl -24(%rsp), %eax\00", align 16
@f80u32 = internal global [147 x i8] c"fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; mov %ax, -12(%rsp); fldcw -12(%rsp); fistpl -24(%rsp); fldcw -10(%rsp); mov -24(%rsp), %eax\00", align 16
@f80u64 = internal global [147 x i8] c"fnstcw -10(%rsp); movzwl -10(%rsp), %eax; or $12, %ah; mov %ax, -12(%rsp); fldcw -12(%rsp); fistpq -24(%rsp); fldcw -10(%rsp); mov -24(%rsp), %rax\00", align 16
@f80f32 = internal global [38 x i8] c"fstps -8(%rsp); movss -8(%rsp), %xmm0\00", align 16
@f80f64 = internal global [38 x i8] c"fstpl -8(%rsp); movsd -8(%rsp), %xmm0\00", align 16
@.str.238 = private unnamed_addr constant [17 x i8] c"  add $15, %%rdi\00", align 1
@.str.239 = private unnamed_addr constant [25 x i8] c"  and $0xfffffff0, %%edi\00", align 1
@.str.240 = private unnamed_addr constant [23 x i8] c"  mov %d(%%rbp), %%rcx\00", align 1
@.str.241 = private unnamed_addr constant [19 x i8] c"  sub %%rsp, %%rcx\00", align 1
@.str.242 = private unnamed_addr constant [19 x i8] c"  mov %%rsp, %%rax\00", align 1
@.str.243 = private unnamed_addr constant [19 x i8] c"  sub %%rdi, %%rsp\00", align 1
@.str.244 = private unnamed_addr constant [19 x i8] c"  mov %%rsp, %%rdx\00", align 1
@.str.245 = private unnamed_addr constant [16 x i8] c"  cmp $0, %%rcx\00", align 1
@.str.246 = private unnamed_addr constant [8 x i8] c"  je 2f\00", align 1
@.str.247 = private unnamed_addr constant [21 x i8] c"  mov (%%rax), %%r8b\00", align 1
@.str.248 = private unnamed_addr constant [21 x i8] c"  mov %%r8b, (%%rdx)\00", align 1
@.str.249 = private unnamed_addr constant [12 x i8] c"  inc %%rdx\00", align 1
@.str.250 = private unnamed_addr constant [12 x i8] c"  inc %%rax\00", align 1
@.str.251 = private unnamed_addr constant [12 x i8] c"  dec %%rcx\00", align 1
@.str.252 = private unnamed_addr constant [9 x i8] c"  jmp 1b\00", align 1
@.str.253 = private unnamed_addr constant [3 x i8] c"2:\00", align 1
@.str.254 = private unnamed_addr constant [19 x i8] c"  sub %%rdi, %%rax\00", align 1
@.str.255 = private unnamed_addr constant [23 x i8] c"  mov %%rax, %d(%%rbp)\00", align 1
@.str.256 = private unnamed_addr constant [16 x i8] c"  sub $8, %%rsp\00", align 1
@.str.257 = private unnamed_addr constant [17 x i8] c"  sub $16, %%rsp\00", align 1
@.str.258 = private unnamed_addr constant [16 x i8] c"  fstpt (%%rsp)\00", align 1
@.str.259 = private unnamed_addr constant [24 x i8] c"  mov %d(%%rax), %%r10b\00", align 1
@.str.260 = private unnamed_addr constant [24 x i8] c"  mov %%r10b, %d(%%rsp)\00", align 1
@.str.261 = private unnamed_addr constant [9 x i8] c"  pop %s\00", align 1
@.str.262 = private unnamed_addr constant [25 x i8] c"  movsd (%%rsp), %%xmm%d\00", align 1
@.str.263 = private unnamed_addr constant [16 x i8] c"  add $8, %%rsp\00", align 1
@.str.264 = private unnamed_addr constant [31 x i8] c"ty->size == 4 || 8 <= ty->size\00", align 1
@__PRETTY_FUNCTION__.copy_ret_buffer = private unnamed_addr constant [28 x i8] c"void copy_ret_buffer(Obj *)\00", align 1
@.str.265 = private unnamed_addr constant [26 x i8] c"  movss %%xmm0, %d(%%rbp)\00", align 1
@.str.266 = private unnamed_addr constant [22 x i8] c"  mov %%al, %d(%%rbp)\00", align 1
@.str.267 = private unnamed_addr constant [16 x i8] c"  shr $8, %%rax\00", align 1
@.str.268 = private unnamed_addr constant [33 x i8] c"ty->size == 12 || ty->size == 16\00", align 1
@.str.269 = private unnamed_addr constant [24 x i8] c"  movsd %%xmm0, (%%rsp)\00", align 1
@.str.270 = private unnamed_addr constant [23 x i8] c"  xorps %%xmm1, %%xmm1\00", align 1
@.str.271 = private unnamed_addr constant [25 x i8] c"  ucomiss %%xmm1, %%xmm0\00", align 1
@.str.272 = private unnamed_addr constant [23 x i8] c"  xorpd %%xmm1, %%xmm1\00", align 1
@.str.273 = private unnamed_addr constant [25 x i8] c"  ucomisd %%xmm1, %%xmm0\00", align 1
@.str.274 = private unnamed_addr constant [7 x i8] c"  fldz\00", align 1
@.str.275 = private unnamed_addr constant [10 x i8] c"  fucomip\00", align 1
@.str.276 = private unnamed_addr constant [16 x i8] c"  cmp $0, %%eax\00", align 1
@.str.277 = private unnamed_addr constant [16 x i8] c"  cmp $0, %%rax\00", align 1
@__PRETTY_FUNCTION__.copy_struct_reg = private unnamed_addr constant [27 x i8] c"void copy_struct_reg(void)\00", align 1
@.str.278 = private unnamed_addr constant [24 x i8] c"  movss (%%rdi), %%xmm0\00", align 1
@.str.279 = private unnamed_addr constant [24 x i8] c"  movsd (%%rdi), %%xmm0\00", align 1
@.str.280 = private unnamed_addr constant [16 x i8] c"  shl $8, %%rax\00", align 1
@.str.281 = private unnamed_addr constant [22 x i8] c"  mov %d(%%rdi), %%al\00", align 1
@.str.282 = private unnamed_addr constant [26 x i8] c"  movss 8(%%rdi), %%xmm%d\00", align 1
@.str.283 = private unnamed_addr constant [26 x i8] c"  movsd 8(%%rdi), %%xmm%d\00", align 1
@.str.284 = private unnamed_addr constant [13 x i8] c"  shl $8, %s\00", align 1
@.str.285 = private unnamed_addr constant [20 x i8] c"  mov %d(%%rdi), %s\00", align 1
@.str.286 = private unnamed_addr constant [23 x i8] c"  mov %d(%%rbp), %%rdi\00", align 1
@.str.287 = private unnamed_addr constant [22 x i8] c"  mov %d(%%rax), %%dl\00", align 1
@.str.288 = private unnamed_addr constant [22 x i8] c"  mov %%dl, %d(%%rdi)\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @align_to(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = add nsw i32 %5, %6
  %8 = sub nsw i32 %7, 1
  %9 = load i32, i32* %4, align 4
  %10 = sdiv i32 %8, %9
  %11 = load i32, i32* %4, align 4
  %12 = mul nsw i32 %10, %11
  ret i32 %12
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @reg_dx(i32 noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  switch i32 %4, label %10 [
    i32 1, label %5
    i32 2, label %6
    i32 4, label %7
    i32 8, label %8
    i32 16, label %9
  ]

5:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i8** %2, align 8
  br label %11

6:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i8** %2, align 8
  br label %11

7:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0), i8** %2, align 8
  br label %11

8:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0), i8** %2, align 8
  br label %11

9:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0), i8** %2, align 8
  br label %11

10:                                               ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 81) #7
  unreachable

11:                                               ; preds = %9, %8, %7, %6, %5
  %12 = load i8*, i8** %2, align 8
  ret i8* %12
}

; Function Attrs: noreturn
declare void @error(i8* noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @reg_bx(i32 noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  switch i32 %4, label %10 [
    i32 1, label %5
    i32 2, label %6
    i32 4, label %7
    i32 8, label %8
    i32 16, label %9
  ]

5:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i64 0, i64 0), i8** %2, align 8
  br label %11

6:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i64 0, i64 0), i8** %2, align 8
  br label %11

7:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i64 0, i64 0), i8** %2, align 8
  br label %11

8:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i64 0, i64 0), i8** %2, align 8
  br label %11

9:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i64 0, i64 0), i8** %2, align 8
  br label %11

10:                                               ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 99) #7
  unreachable

11:                                               ; preds = %9, %8, %7, %6, %5
  %12 = load i8*, i8** %2, align 8
  ret i8* %12
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @reg_cx(i32 noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  switch i32 %4, label %10 [
    i32 1, label %5
    i32 2, label %6
    i32 4, label %7
    i32 8, label %8
    i32 16, label %9
  ]

5:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i64 0, i64 0), i8** %2, align 8
  br label %11

6:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.11, i64 0, i64 0), i8** %2, align 8
  br label %11

7:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.12, i64 0, i64 0), i8** %2, align 8
  br label %11

8:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i64 0, i64 0), i8** %2, align 8
  br label %11

9:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i64 0, i64 0), i8** %2, align 8
  br label %11

10:                                               ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 117) #7
  unreachable

11:                                               ; preds = %9, %8, %7, %6, %5
  %12 = load i8*, i8** %2, align 8
  ret i8* %12
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @reg_ax(i32 noundef %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  switch i32 %4, label %10 [
    i32 1, label %5
    i32 2, label %6
    i32 4, label %7
    i32 8, label %8
    i32 16, label %9
  ]

5:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.14, i64 0, i64 0), i8** %2, align 8
  br label %11

6:                                                ; preds = %1
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.15, i64 0, i64 0), i8** %2, align 8
  br label %11

7:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.16, i64 0, i64 0), i8** %2, align 8
  br label %11

8:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i64 0, i64 0), i8** %2, align 8
  br label %11

9:                                                ; preds = %1
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0), i8** %2, align 8
  br label %11

10:                                               ; preds = %1
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 135) #7
  unreachable

11:                                               ; preds = %9, %8, %7, %6, %5
  %12 = load i8*, i8** %2, align 8
  ret i8* %12
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @codegen(%struct.Obj* noundef %0, %struct._IO_FILE* noundef %1) #0 {
  %3 = alloca %struct.Obj*, align 8
  %4 = alloca %struct._IO_FILE*, align 8
  %5 = alloca %struct.File**, align 8
  %6 = alloca i32, align 4
  store %struct.Obj* %0, %struct.Obj** %3, align 8
  store %struct._IO_FILE* %1, %struct._IO_FILE** %4, align 8
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8
  store %struct._IO_FILE* %7, %struct._IO_FILE** @output_file, align 8
  %8 = call %struct.File** @get_input_files()
  store %struct.File** %8, %struct.File*** %5, align 8
  store i32 0, i32* %6, align 4
  br label %9

9:                                                ; preds = %31, %2
  %10 = load %struct.File**, %struct.File*** %5, align 8
  %11 = load i32, i32* %6, align 4
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds %struct.File*, %struct.File** %10, i64 %12
  %14 = load %struct.File*, %struct.File** %13, align 8
  %15 = icmp ne %struct.File* %14, null
  br i1 %15, label %16, label %34

16:                                               ; preds = %9
  %17 = load %struct.File**, %struct.File*** %5, align 8
  %18 = load i32, i32* %6, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds %struct.File*, %struct.File** %17, i64 %19
  %21 = load %struct.File*, %struct.File** %20, align 8
  %22 = getelementptr inbounds %struct.File, %struct.File* %21, i32 0, i32 1
  %23 = load i32, i32* %22, align 8
  %24 = load %struct.File**, %struct.File*** %5, align 8
  %25 = load i32, i32* %6, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds %struct.File*, %struct.File** %24, i64 %26
  %28 = load %struct.File*, %struct.File** %27, align 8
  %29 = getelementptr inbounds %struct.File, %struct.File* %28, i32 0, i32 0
  %30 = load i8*, i8** %29, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.18, i64 0, i64 0), i32 noundef %23, i8* noundef %30)
  br label %31

31:                                               ; preds = %16
  %32 = load i32, i32* %6, align 4
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %6, align 4
  br label %9, !llvm.loop !6

34:                                               ; preds = %9
  %35 = load %struct.Obj*, %struct.Obj** %3, align 8
  call void @assign_lvar_offsets(%struct.Obj* noundef %35)
  %36 = load %struct.Obj*, %struct.Obj** %3, align 8
  call void @emit_data(%struct.Obj* noundef %36)
  %37 = load %struct.Obj*, %struct.Obj** %3, align 8
  call void @emit_text(%struct.Obj* noundef %37)
  ret void
}

declare %struct.File** @get_input_files() #2

; Function Attrs: noinline nounwind optnone uwtable
define internal void @println(i8* noundef %0, ...) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca [1 x %struct.__va_list_tag], align 16
  store i8* %0, i8** %2, align 8
  %4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %5 = bitcast %struct.__va_list_tag* %4 to i8*
  call void @llvm.va_start(i8* %5)
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @output_file, align 8
  %7 = load i8*, i8** %2, align 8
  %8 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %9 = call i32 @vfprintf(%struct._IO_FILE* noundef %6, i8* noundef %7, %struct.__va_list_tag* noundef %8)
  %10 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %11 = bitcast %struct.__va_list_tag* %10 to i8*
  call void @llvm.va_end(i8* %11)
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** @output_file, align 8
  %13 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* noundef %12, i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0))
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @assign_lvar_offsets(%struct.Obj* noundef %0) #0 {
  %2 = alloca %struct.Obj*, align 8
  %3 = alloca %struct.Obj*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca %struct.Obj*, align 8
  %9 = alloca %struct.Type*, align 8
  %10 = alloca i8, align 1
  %11 = alloca i8, align 1
  %12 = alloca %struct.Obj*, align 8
  %13 = alloca i32, align 4
  store %struct.Obj* %0, %struct.Obj** %2, align 8
  %14 = load %struct.Obj*, %struct.Obj** %2, align 8
  store %struct.Obj* %14, %struct.Obj** %3, align 8
  br label %15

15:                                               ; preds = %194, %1
  %16 = load %struct.Obj*, %struct.Obj** %3, align 8
  %17 = icmp ne %struct.Obj* %16, null
  br i1 %17, label %18, label %198

18:                                               ; preds = %15
  %19 = load %struct.Obj*, %struct.Obj** %3, align 8
  %20 = getelementptr inbounds %struct.Obj, %struct.Obj* %19, i32 0, i32 10
  %21 = load i8, i8* %20, align 4
  %22 = trunc i8 %21 to i1
  br i1 %22, label %24, label %23

23:                                               ; preds = %18
  br label %194

24:                                               ; preds = %18
  store i32 16, i32* %4, align 4
  store i32 0, i32* %5, align 4
  store i32 0, i32* %6, align 4
  store i32 0, i32* %7, align 4
  %25 = load %struct.Obj*, %struct.Obj** %3, align 8
  %26 = getelementptr inbounds %struct.Obj, %struct.Obj* %25, i32 0, i32 18
  %27 = load %struct.Obj*, %struct.Obj** %26, align 8
  store %struct.Obj* %27, %struct.Obj** %8, align 8
  br label %28

28:                                               ; preds = %122, %24
  %29 = load %struct.Obj*, %struct.Obj** %8, align 8
  %30 = icmp ne %struct.Obj* %29, null
  br i1 %30, label %31, label %126

31:                                               ; preds = %28
  %32 = load %struct.Obj*, %struct.Obj** %8, align 8
  %33 = getelementptr inbounds %struct.Obj, %struct.Obj* %32, i32 0, i32 3
  %34 = load %struct.Type*, %struct.Type** %33, align 8
  store %struct.Type* %34, %struct.Type** %9, align 8
  %35 = load %struct.Type*, %struct.Type** %9, align 8
  %36 = getelementptr inbounds %struct.Type, %struct.Type* %35, i32 0, i32 0
  %37 = load i32, i32* %36, align 8
  switch i32 %37, label %103 [
    i32 14, label %38
    i32 15, label %38
    i32 6, label %96
    i32 7, label %96
    i32 8, label %102
  ]

38:                                               ; preds = %31, %31
  %39 = load %struct.Type*, %struct.Type** %9, align 8
  %40 = getelementptr inbounds %struct.Type, %struct.Type* %39, i32 0, i32 1
  %41 = load i32, i32* %40, align 4
  %42 = icmp sle i32 %41, 16
  br i1 %42, label %43, label %95

43:                                               ; preds = %38
  %44 = load %struct.Type*, %struct.Type** %9, align 8
  %45 = call zeroext i1 @has_flonum(%struct.Type* noundef %44, i32 noundef 0, i32 noundef 8, i32 noundef 0)
  %46 = zext i1 %45 to i8
  store i8 %46, i8* %10, align 1
  %47 = load %struct.Type*, %struct.Type** %9, align 8
  %48 = call zeroext i1 @has_flonum(%struct.Type* noundef %47, i32 noundef 8, i32 noundef 16, i32 noundef 8)
  %49 = zext i1 %48 to i8
  store i8 %49, i8* %11, align 1
  %50 = load i32, i32* %7, align 4
  %51 = load i8, i8* %10, align 1
  %52 = trunc i8 %51 to i1
  %53 = zext i1 %52 to i32
  %54 = add nsw i32 %50, %53
  %55 = load i8, i8* %11, align 1
  %56 = trunc i8 %55 to i1
  %57 = zext i1 %56 to i32
  %58 = add nsw i32 %54, %57
  %59 = icmp slt i32 %58, 8
  br i1 %59, label %60, label %94

60:                                               ; preds = %43
  %61 = load i32, i32* %6, align 4
  %62 = load i8, i8* %10, align 1
  %63 = trunc i8 %62 to i1
  %64 = xor i1 %63, true
  %65 = zext i1 %64 to i32
  %66 = add nsw i32 %61, %65
  %67 = load i8, i8* %11, align 1
  %68 = trunc i8 %67 to i1
  %69 = xor i1 %68, true
  %70 = zext i1 %69 to i32
  %71 = add nsw i32 %66, %70
  %72 = icmp slt i32 %71, 6
  br i1 %72, label %73, label %94

73:                                               ; preds = %60
  %74 = load i32, i32* %7, align 4
  %75 = load i8, i8* %10, align 1
  %76 = trunc i8 %75 to i1
  %77 = zext i1 %76 to i32
  %78 = add nsw i32 %74, %77
  %79 = load i8, i8* %11, align 1
  %80 = trunc i8 %79 to i1
  %81 = zext i1 %80 to i32
  %82 = add nsw i32 %78, %81
  store i32 %82, i32* %7, align 4
  %83 = load i32, i32* %6, align 4
  %84 = load i8, i8* %10, align 1
  %85 = trunc i8 %84 to i1
  %86 = xor i1 %85, true
  %87 = zext i1 %86 to i32
  %88 = add nsw i32 %83, %87
  %89 = load i8, i8* %11, align 1
  %90 = trunc i8 %89 to i1
  %91 = xor i1 %90, true
  %92 = zext i1 %91 to i32
  %93 = add nsw i32 %88, %92
  store i32 %93, i32* %6, align 4
  br label %122

94:                                               ; preds = %60, %43
  br label %95

95:                                               ; preds = %94, %38
  br label %109

96:                                               ; preds = %31, %31
  %97 = load i32, i32* %7, align 4
  %98 = add nsw i32 %97, 1
  store i32 %98, i32* %7, align 4
  %99 = icmp slt i32 %97, 8
  br i1 %99, label %100, label %101

100:                                              ; preds = %96
  br label %122

101:                                              ; preds = %96
  br label %109

102:                                              ; preds = %31
  br label %109

103:                                              ; preds = %31
  %104 = load i32, i32* %6, align 4
  %105 = add nsw i32 %104, 1
  store i32 %105, i32* %6, align 4
  %106 = icmp slt i32 %104, 6
  br i1 %106, label %107, label %108

107:                                              ; preds = %103
  br label %122

108:                                              ; preds = %103
  br label %109

109:                                              ; preds = %108, %102, %101, %95
  %110 = load i32, i32* %4, align 4
  %111 = call i32 @align_to(i32 noundef %110, i32 noundef 8)
  store i32 %111, i32* %4, align 4
  %112 = load i32, i32* %4, align 4
  %113 = load %struct.Obj*, %struct.Obj** %8, align 8
  %114 = getelementptr inbounds %struct.Obj, %struct.Obj* %113, i32 0, i32 7
  store i32 %112, i32* %114, align 8
  %115 = load %struct.Obj*, %struct.Obj** %8, align 8
  %116 = getelementptr inbounds %struct.Obj, %struct.Obj* %115, i32 0, i32 3
  %117 = load %struct.Type*, %struct.Type** %116, align 8
  %118 = getelementptr inbounds %struct.Type, %struct.Type* %117, i32 0, i32 1
  %119 = load i32, i32* %118, align 4
  %120 = load i32, i32* %4, align 4
  %121 = add nsw i32 %120, %119
  store i32 %121, i32* %4, align 4
  br label %122

122:                                              ; preds = %109, %107, %100, %73
  %123 = load %struct.Obj*, %struct.Obj** %8, align 8
  %124 = getelementptr inbounds %struct.Obj, %struct.Obj* %123, i32 0, i32 0
  %125 = load %struct.Obj*, %struct.Obj** %124, align 8
  store %struct.Obj* %125, %struct.Obj** %8, align 8
  br label %28, !llvm.loop !8

126:                                              ; preds = %28
  %127 = load %struct.Obj*, %struct.Obj** %3, align 8
  %128 = getelementptr inbounds %struct.Obj, %struct.Obj* %127, i32 0, i32 20
  %129 = load %struct.Obj*, %struct.Obj** %128, align 8
  store %struct.Obj* %129, %struct.Obj** %12, align 8
  br label %130

130:                                              ; preds = %185, %126
  %131 = load %struct.Obj*, %struct.Obj** %12, align 8
  %132 = icmp ne %struct.Obj* %131, null
  br i1 %132, label %133, label %189

133:                                              ; preds = %130
  %134 = load %struct.Obj*, %struct.Obj** %12, align 8
  %135 = getelementptr inbounds %struct.Obj, %struct.Obj* %134, i32 0, i32 7
  %136 = load i32, i32* %135, align 8
  %137 = icmp ne i32 %136, 0
  br i1 %137, label %138, label %139

138:                                              ; preds = %133
  br label %185

139:                                              ; preds = %133
  %140 = load %struct.Obj*, %struct.Obj** %12, align 8
  %141 = getelementptr inbounds %struct.Obj, %struct.Obj* %140, i32 0, i32 3
  %142 = load %struct.Type*, %struct.Type** %141, align 8
  %143 = getelementptr inbounds %struct.Type, %struct.Type* %142, i32 0, i32 0
  %144 = load i32, i32* %143, align 8
  %145 = icmp eq i32 %144, 12
  br i1 %145, label %146, label %165

146:                                              ; preds = %139
  %147 = load %struct.Obj*, %struct.Obj** %12, align 8
  %148 = getelementptr inbounds %struct.Obj, %struct.Obj* %147, i32 0, i32 3
  %149 = load %struct.Type*, %struct.Type** %148, align 8
  %150 = getelementptr inbounds %struct.Type, %struct.Type* %149, i32 0, i32 1
  %151 = load i32, i32* %150, align 4
  %152 = icmp sge i32 %151, 16
  br i1 %152, label %153, label %165

153:                                              ; preds = %146
  %154 = load %struct.Obj*, %struct.Obj** %12, align 8
  %155 = getelementptr inbounds %struct.Obj, %struct.Obj* %154, i32 0, i32 6
  %156 = load i32, i32* %155, align 4
  %157 = icmp slt i32 16, %156
  br i1 %157, label %158, label %162

158:                                              ; preds = %153
  %159 = load %struct.Obj*, %struct.Obj** %12, align 8
  %160 = getelementptr inbounds %struct.Obj, %struct.Obj* %159, i32 0, i32 6
  %161 = load i32, i32* %160, align 4
  br label %163

162:                                              ; preds = %153
  br label %163

163:                                              ; preds = %162, %158
  %164 = phi i32 [ %161, %158 ], [ 16, %162 ]
  br label %169

165:                                              ; preds = %146, %139
  %166 = load %struct.Obj*, %struct.Obj** %12, align 8
  %167 = getelementptr inbounds %struct.Obj, %struct.Obj* %166, i32 0, i32 6
  %168 = load i32, i32* %167, align 4
  br label %169

169:                                              ; preds = %165, %163
  %170 = phi i32 [ %164, %163 ], [ %168, %165 ]
  store i32 %170, i32* %13, align 4
  %171 = load %struct.Obj*, %struct.Obj** %12, align 8
  %172 = getelementptr inbounds %struct.Obj, %struct.Obj* %171, i32 0, i32 3
  %173 = load %struct.Type*, %struct.Type** %172, align 8
  %174 = getelementptr inbounds %struct.Type, %struct.Type* %173, i32 0, i32 1
  %175 = load i32, i32* %174, align 4
  %176 = load i32, i32* %5, align 4
  %177 = add nsw i32 %176, %175
  store i32 %177, i32* %5, align 4
  %178 = load i32, i32* %5, align 4
  %179 = load i32, i32* %13, align 4
  %180 = call i32 @align_to(i32 noundef %178, i32 noundef %179)
  store i32 %180, i32* %5, align 4
  %181 = load i32, i32* %5, align 4
  %182 = sub nsw i32 0, %181
  %183 = load %struct.Obj*, %struct.Obj** %12, align 8
  %184 = getelementptr inbounds %struct.Obj, %struct.Obj* %183, i32 0, i32 7
  store i32 %182, i32* %184, align 8
  br label %185

185:                                              ; preds = %169, %138
  %186 = load %struct.Obj*, %struct.Obj** %12, align 8
  %187 = getelementptr inbounds %struct.Obj, %struct.Obj* %186, i32 0, i32 0
  %188 = load %struct.Obj*, %struct.Obj** %187, align 8
  store %struct.Obj* %188, %struct.Obj** %12, align 8
  br label %130, !llvm.loop !9

189:                                              ; preds = %130
  %190 = load i32, i32* %5, align 4
  %191 = call i32 @align_to(i32 noundef %190, i32 noundef 16)
  %192 = load %struct.Obj*, %struct.Obj** %3, align 8
  %193 = getelementptr inbounds %struct.Obj, %struct.Obj* %192, i32 0, i32 23
  store i32 %191, i32* %193, align 8
  br label %194

194:                                              ; preds = %189, %23
  %195 = load %struct.Obj*, %struct.Obj** %3, align 8
  %196 = getelementptr inbounds %struct.Obj, %struct.Obj* %195, i32 0, i32 0
  %197 = load %struct.Obj*, %struct.Obj** %196, align 8
  store %struct.Obj* %197, %struct.Obj** %3, align 8
  br label %15, !llvm.loop !10

198:                                              ; preds = %15
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @emit_data(%struct.Obj* noundef %0) #0 {
  %2 = alloca %struct.Obj*, align 8
  %3 = alloca %struct.Obj*, align 8
  %4 = alloca i32, align 4
  %5 = alloca %struct.Relocation*, align 8
  %6 = alloca i32, align 4
  store %struct.Obj* %0, %struct.Obj** %2, align 8
  %7 = load %struct.Obj*, %struct.Obj** %2, align 8
  store %struct.Obj* %7, %struct.Obj** %3, align 8
  br label %8

8:                                                ; preds = %174, %1
  %9 = load %struct.Obj*, %struct.Obj** %3, align 8
  %10 = icmp ne %struct.Obj* %9, null
  br i1 %10, label %11, label %178

11:                                               ; preds = %8
  %12 = load %struct.Obj*, %struct.Obj** %3, align 8
  %13 = getelementptr inbounds %struct.Obj, %struct.Obj* %12, i32 0, i32 10
  %14 = load i8, i8* %13, align 4
  %15 = trunc i8 %14 to i1
  br i1 %15, label %21, label %16

16:                                               ; preds = %11
  %17 = load %struct.Obj*, %struct.Obj** %3, align 8
  %18 = getelementptr inbounds %struct.Obj, %struct.Obj* %17, i32 0, i32 11
  %19 = load i8, i8* %18, align 1
  %20 = trunc i8 %19 to i1
  br i1 %20, label %22, label %21

21:                                               ; preds = %16, %11
  br label %174

22:                                               ; preds = %16
  %23 = load %struct.Obj*, %struct.Obj** %3, align 8
  %24 = getelementptr inbounds %struct.Obj, %struct.Obj* %23, i32 0, i32 12
  %25 = load i8, i8* %24, align 2
  %26 = trunc i8 %25 to i1
  br i1 %26, label %27, label %31

27:                                               ; preds = %22
  %28 = load %struct.Obj*, %struct.Obj** %3, align 8
  %29 = getelementptr inbounds %struct.Obj, %struct.Obj* %28, i32 0, i32 1
  %30 = load i8*, i8** %29, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.20, i64 0, i64 0), i8* noundef %30)
  br label %35

31:                                               ; preds = %22
  %32 = load %struct.Obj*, %struct.Obj** %3, align 8
  %33 = getelementptr inbounds %struct.Obj, %struct.Obj* %32, i32 0, i32 1
  %34 = load i8*, i8** %33, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.21, i64 0, i64 0), i8* noundef %34)
  br label %35

35:                                               ; preds = %31, %27
  %36 = load %struct.Obj*, %struct.Obj** %3, align 8
  %37 = getelementptr inbounds %struct.Obj, %struct.Obj* %36, i32 0, i32 3
  %38 = load %struct.Type*, %struct.Type** %37, align 8
  %39 = getelementptr inbounds %struct.Type, %struct.Type* %38, i32 0, i32 0
  %40 = load i32, i32* %39, align 8
  %41 = icmp eq i32 %40, 12
  br i1 %41, label %42, label %61

42:                                               ; preds = %35
  %43 = load %struct.Obj*, %struct.Obj** %3, align 8
  %44 = getelementptr inbounds %struct.Obj, %struct.Obj* %43, i32 0, i32 3
  %45 = load %struct.Type*, %struct.Type** %44, align 8
  %46 = getelementptr inbounds %struct.Type, %struct.Type* %45, i32 0, i32 1
  %47 = load i32, i32* %46, align 4
  %48 = icmp sge i32 %47, 16
  br i1 %48, label %49, label %61

49:                                               ; preds = %42
  %50 = load %struct.Obj*, %struct.Obj** %3, align 8
  %51 = getelementptr inbounds %struct.Obj, %struct.Obj* %50, i32 0, i32 6
  %52 = load i32, i32* %51, align 4
  %53 = icmp slt i32 16, %52
  br i1 %53, label %54, label %58

54:                                               ; preds = %49
  %55 = load %struct.Obj*, %struct.Obj** %3, align 8
  %56 = getelementptr inbounds %struct.Obj, %struct.Obj* %55, i32 0, i32 6
  %57 = load i32, i32* %56, align 4
  br label %59

58:                                               ; preds = %49
  br label %59

59:                                               ; preds = %58, %54
  %60 = phi i32 [ %57, %54 ], [ 16, %58 ]
  br label %65

61:                                               ; preds = %42, %35
  %62 = load %struct.Obj*, %struct.Obj** %3, align 8
  %63 = getelementptr inbounds %struct.Obj, %struct.Obj* %62, i32 0, i32 6
  %64 = load i32, i32* %63, align 4
  br label %65

65:                                               ; preds = %61, %59
  %66 = phi i32 [ %60, %59 ], [ %64, %61 ]
  store i32 %66, i32* %4, align 4
  %67 = load i8, i8* @opt_fcommon, align 1
  %68 = trunc i8 %67 to i1
  br i1 %68, label %69, label %84

69:                                               ; preds = %65
  %70 = load %struct.Obj*, %struct.Obj** %3, align 8
  %71 = getelementptr inbounds %struct.Obj, %struct.Obj* %70, i32 0, i32 13
  %72 = load i8, i8* %71, align 1
  %73 = trunc i8 %72 to i1
  br i1 %73, label %74, label %84

74:                                               ; preds = %69
  %75 = load %struct.Obj*, %struct.Obj** %3, align 8
  %76 = getelementptr inbounds %struct.Obj, %struct.Obj* %75, i32 0, i32 1
  %77 = load i8*, i8** %76, align 8
  %78 = load %struct.Obj*, %struct.Obj** %3, align 8
  %79 = getelementptr inbounds %struct.Obj, %struct.Obj* %78, i32 0, i32 3
  %80 = load %struct.Type*, %struct.Type** %79, align 8
  %81 = getelementptr inbounds %struct.Type, %struct.Type* %80, i32 0, i32 1
  %82 = load i32, i32* %81, align 4
  %83 = load i32, i32* %4, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.22, i64 0, i64 0), i8* noundef %77, i32 noundef %82, i32 noundef %83)
  br label %174

84:                                               ; preds = %69, %65
  %85 = load %struct.Obj*, %struct.Obj** %3, align 8
  %86 = getelementptr inbounds %struct.Obj, %struct.Obj* %85, i32 0, i32 15
  %87 = load i8*, i8** %86, align 8
  %88 = icmp ne i8* %87, null
  br i1 %88, label %89, label %157

89:                                               ; preds = %84
  %90 = load %struct.Obj*, %struct.Obj** %3, align 8
  %91 = getelementptr inbounds %struct.Obj, %struct.Obj* %90, i32 0, i32 14
  %92 = load i8, i8* %91, align 8
  %93 = trunc i8 %92 to i1
  br i1 %93, label %94, label %95

94:                                               ; preds = %89
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([34 x i8], [34 x i8]* @.str.23, i64 0, i64 0))
  br label %96

95:                                               ; preds = %89
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.24, i64 0, i64 0))
  br label %96

96:                                               ; preds = %95, %94
  %97 = load %struct.Obj*, %struct.Obj** %3, align 8
  %98 = getelementptr inbounds %struct.Obj, %struct.Obj* %97, i32 0, i32 1
  %99 = load i8*, i8** %98, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.25, i64 0, i64 0), i8* noundef %99)
  %100 = load %struct.Obj*, %struct.Obj** %3, align 8
  %101 = getelementptr inbounds %struct.Obj, %struct.Obj* %100, i32 0, i32 1
  %102 = load i8*, i8** %101, align 8
  %103 = load %struct.Obj*, %struct.Obj** %3, align 8
  %104 = getelementptr inbounds %struct.Obj, %struct.Obj* %103, i32 0, i32 3
  %105 = load %struct.Type*, %struct.Type** %104, align 8
  %106 = getelementptr inbounds %struct.Type, %struct.Type* %105, i32 0, i32 1
  %107 = load i32, i32* %106, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.26, i64 0, i64 0), i8* noundef %102, i32 noundef %107)
  %108 = load i32, i32* %4, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.27, i64 0, i64 0), i32 noundef %108)
  %109 = load %struct.Obj*, %struct.Obj** %3, align 8
  %110 = getelementptr inbounds %struct.Obj, %struct.Obj* %109, i32 0, i32 1
  %111 = load i8*, i8** %110, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %111)
  %112 = load %struct.Obj*, %struct.Obj** %3, align 8
  %113 = getelementptr inbounds %struct.Obj, %struct.Obj* %112, i32 0, i32 16
  %114 = load %struct.Relocation*, %struct.Relocation** %113, align 8
  store %struct.Relocation* %114, %struct.Relocation** %5, align 8
  store i32 0, i32* %6, align 4
  br label %115

115:                                              ; preds = %155, %96
  %116 = load i32, i32* %6, align 4
  %117 = load %struct.Obj*, %struct.Obj** %3, align 8
  %118 = getelementptr inbounds %struct.Obj, %struct.Obj* %117, i32 0, i32 3
  %119 = load %struct.Type*, %struct.Type** %118, align 8
  %120 = getelementptr inbounds %struct.Type, %struct.Type* %119, i32 0, i32 1
  %121 = load i32, i32* %120, align 4
  %122 = icmp slt i32 %116, %121
  br i1 %122, label %123, label %156

123:                                              ; preds = %115
  %124 = load %struct.Relocation*, %struct.Relocation** %5, align 8
  %125 = icmp ne %struct.Relocation* %124, null
  br i1 %125, label %126, label %145

126:                                              ; preds = %123
  %127 = load %struct.Relocation*, %struct.Relocation** %5, align 8
  %128 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %127, i32 0, i32 1
  %129 = load i32, i32* %128, align 8
  %130 = load i32, i32* %6, align 4
  %131 = icmp eq i32 %129, %130
  br i1 %131, label %132, label %145

132:                                              ; preds = %126
  %133 = load %struct.Relocation*, %struct.Relocation** %5, align 8
  %134 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %133, i32 0, i32 2
  %135 = load i8**, i8*** %134, align 8
  %136 = load i8*, i8** %135, align 8
  %137 = load %struct.Relocation*, %struct.Relocation** %5, align 8
  %138 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %137, i32 0, i32 3
  %139 = load i64, i64* %138, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.29, i64 0, i64 0), i8* noundef %136, i64 noundef %139)
  %140 = load %struct.Relocation*, %struct.Relocation** %5, align 8
  %141 = getelementptr inbounds %struct.Relocation, %struct.Relocation* %140, i32 0, i32 0
  %142 = load %struct.Relocation*, %struct.Relocation** %141, align 8
  store %struct.Relocation* %142, %struct.Relocation** %5, align 8
  %143 = load i32, i32* %6, align 4
  %144 = add nsw i32 %143, 8
  store i32 %144, i32* %6, align 4
  br label %155

145:                                              ; preds = %126, %123
  %146 = load %struct.Obj*, %struct.Obj** %3, align 8
  %147 = getelementptr inbounds %struct.Obj, %struct.Obj* %146, i32 0, i32 15
  %148 = load i8*, i8** %147, align 8
  %149 = load i32, i32* %6, align 4
  %150 = add nsw i32 %149, 1
  store i32 %150, i32* %6, align 4
  %151 = sext i32 %149 to i64
  %152 = getelementptr inbounds i8, i8* %148, i64 %151
  %153 = load i8, i8* %152, align 1
  %154 = sext i8 %153 to i32
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.30, i64 0, i64 0), i32 noundef %154)
  br label %155

155:                                              ; preds = %145, %132
  br label %115, !llvm.loop !11

156:                                              ; preds = %115
  br label %174

157:                                              ; preds = %84
  %158 = load %struct.Obj*, %struct.Obj** %3, align 8
  %159 = getelementptr inbounds %struct.Obj, %struct.Obj* %158, i32 0, i32 14
  %160 = load i8, i8* %159, align 8
  %161 = trunc i8 %160 to i1
  br i1 %161, label %162, label %163

162:                                              ; preds = %157
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.31, i64 0, i64 0))
  br label %164

163:                                              ; preds = %157
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.32, i64 0, i64 0))
  br label %164

164:                                              ; preds = %163, %162
  %165 = load i32, i32* %4, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.27, i64 0, i64 0), i32 noundef %165)
  %166 = load %struct.Obj*, %struct.Obj** %3, align 8
  %167 = getelementptr inbounds %struct.Obj, %struct.Obj* %166, i32 0, i32 1
  %168 = load i8*, i8** %167, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %168)
  %169 = load %struct.Obj*, %struct.Obj** %3, align 8
  %170 = getelementptr inbounds %struct.Obj, %struct.Obj* %169, i32 0, i32 3
  %171 = load %struct.Type*, %struct.Type** %170, align 8
  %172 = getelementptr inbounds %struct.Type, %struct.Type* %171, i32 0, i32 1
  %173 = load i32, i32* %172, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.33, i64 0, i64 0), i32 noundef %173)
  br label %174

174:                                              ; preds = %164, %156, %74, %21
  %175 = load %struct.Obj*, %struct.Obj** %3, align 8
  %176 = getelementptr inbounds %struct.Obj, %struct.Obj* %175, i32 0, i32 0
  %177 = load %struct.Obj*, %struct.Obj** %176, align 8
  store %struct.Obj* %177, %struct.Obj** %3, align 8
  br label %8, !llvm.loop !12

178:                                              ; preds = %8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @emit_text(%struct.Obj* noundef %0) #0 {
  %2 = alloca %struct.Obj*, align 8
  %3 = alloca %struct.Obj*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca %struct.Obj*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca %struct.Obj*, align 8
  %11 = alloca %struct.Type*, align 8
  store %struct.Obj* %0, %struct.Obj** %2, align 8
  %12 = load %struct.Obj*, %struct.Obj** %2, align 8
  store %struct.Obj* %12, %struct.Obj** %3, align 8
  br label %13

13:                                               ; preds = %279, %1
  %14 = load %struct.Obj*, %struct.Obj** %3, align 8
  %15 = icmp ne %struct.Obj* %14, null
  br i1 %15, label %16, label %283

16:                                               ; preds = %13
  %17 = load %struct.Obj*, %struct.Obj** %3, align 8
  %18 = getelementptr inbounds %struct.Obj, %struct.Obj* %17, i32 0, i32 10
  %19 = load i8, i8* %18, align 4
  %20 = trunc i8 %19 to i1
  br i1 %20, label %21, label %26

21:                                               ; preds = %16
  %22 = load %struct.Obj*, %struct.Obj** %3, align 8
  %23 = getelementptr inbounds %struct.Obj, %struct.Obj* %22, i32 0, i32 11
  %24 = load i8, i8* %23, align 1
  %25 = trunc i8 %24 to i1
  br i1 %25, label %27, label %26

26:                                               ; preds = %21, %16
  br label %279

27:                                               ; preds = %21
  %28 = load %struct.Obj*, %struct.Obj** %3, align 8
  %29 = getelementptr inbounds %struct.Obj, %struct.Obj* %28, i32 0, i32 24
  %30 = load i8, i8* %29, align 4
  %31 = trunc i8 %30 to i1
  br i1 %31, label %33, label %32

32:                                               ; preds = %27
  br label %279

33:                                               ; preds = %27
  %34 = load %struct.Obj*, %struct.Obj** %3, align 8
  %35 = getelementptr inbounds %struct.Obj, %struct.Obj* %34, i32 0, i32 12
  %36 = load i8, i8* %35, align 2
  %37 = trunc i8 %36 to i1
  br i1 %37, label %38, label %42

38:                                               ; preds = %33
  %39 = load %struct.Obj*, %struct.Obj** %3, align 8
  %40 = getelementptr inbounds %struct.Obj, %struct.Obj* %39, i32 0, i32 1
  %41 = load i8*, i8** %40, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.20, i64 0, i64 0), i8* noundef %41)
  br label %46

42:                                               ; preds = %33
  %43 = load %struct.Obj*, %struct.Obj** %3, align 8
  %44 = getelementptr inbounds %struct.Obj, %struct.Obj* %43, i32 0, i32 1
  %45 = load i8*, i8** %44, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.21, i64 0, i64 0), i8* noundef %45)
  br label %46

46:                                               ; preds = %42, %38
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.34, i64 0, i64 0))
  %47 = load %struct.Obj*, %struct.Obj** %3, align 8
  %48 = getelementptr inbounds %struct.Obj, %struct.Obj* %47, i32 0, i32 1
  %49 = load i8*, i8** %48, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.35, i64 0, i64 0), i8* noundef %49)
  %50 = load %struct.Obj*, %struct.Obj** %3, align 8
  %51 = getelementptr inbounds %struct.Obj, %struct.Obj* %50, i32 0, i32 1
  %52 = load i8*, i8** %51, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %52)
  %53 = load %struct.Obj*, %struct.Obj** %3, align 8
  store %struct.Obj* %53, %struct.Obj** @current_fn, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.36, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.37, i64 0, i64 0))
  %54 = load %struct.Obj*, %struct.Obj** %3, align 8
  %55 = getelementptr inbounds %struct.Obj, %struct.Obj* %54, i32 0, i32 23
  %56 = load i32, i32* %55, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.38, i64 0, i64 0), i32 noundef %56)
  %57 = load %struct.Obj*, %struct.Obj** %3, align 8
  %58 = getelementptr inbounds %struct.Obj, %struct.Obj* %57, i32 0, i32 22
  %59 = load %struct.Obj*, %struct.Obj** %58, align 8
  %60 = getelementptr inbounds %struct.Obj, %struct.Obj* %59, i32 0, i32 7
  %61 = load i32, i32* %60, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.39, i64 0, i64 0), i32 noundef %61)
  %62 = load %struct.Obj*, %struct.Obj** %3, align 8
  %63 = getelementptr inbounds %struct.Obj, %struct.Obj* %62, i32 0, i32 21
  %64 = load %struct.Obj*, %struct.Obj** %63, align 8
  %65 = icmp ne %struct.Obj* %64, null
  br i1 %65, label %66, label %141

66:                                               ; preds = %46
  store i32 0, i32* %4, align 4
  store i32 0, i32* %5, align 4
  %67 = load %struct.Obj*, %struct.Obj** %3, align 8
  %68 = getelementptr inbounds %struct.Obj, %struct.Obj* %67, i32 0, i32 18
  %69 = load %struct.Obj*, %struct.Obj** %68, align 8
  store %struct.Obj* %69, %struct.Obj** %6, align 8
  br label %70

70:                                               ; preds = %85, %66
  %71 = load %struct.Obj*, %struct.Obj** %6, align 8
  %72 = icmp ne %struct.Obj* %71, null
  br i1 %72, label %73, label %89

73:                                               ; preds = %70
  %74 = load %struct.Obj*, %struct.Obj** %6, align 8
  %75 = getelementptr inbounds %struct.Obj, %struct.Obj* %74, i32 0, i32 3
  %76 = load %struct.Type*, %struct.Type** %75, align 8
  %77 = call zeroext i1 @is_flonum(%struct.Type* noundef %76)
  br i1 %77, label %78, label %81

78:                                               ; preds = %73
  %79 = load i32, i32* %5, align 4
  %80 = add nsw i32 %79, 1
  store i32 %80, i32* %5, align 4
  br label %84

81:                                               ; preds = %73
  %82 = load i32, i32* %4, align 4
  %83 = add nsw i32 %82, 1
  store i32 %83, i32* %4, align 4
  br label %84

84:                                               ; preds = %81, %78
  br label %85

85:                                               ; preds = %84
  %86 = load %struct.Obj*, %struct.Obj** %6, align 8
  %87 = getelementptr inbounds %struct.Obj, %struct.Obj* %86, i32 0, i32 0
  %88 = load %struct.Obj*, %struct.Obj** %87, align 8
  store %struct.Obj* %88, %struct.Obj** %6, align 8
  br label %70, !llvm.loop !13

89:                                               ; preds = %70
  %90 = load %struct.Obj*, %struct.Obj** %3, align 8
  %91 = getelementptr inbounds %struct.Obj, %struct.Obj* %90, i32 0, i32 21
  %92 = load %struct.Obj*, %struct.Obj** %91, align 8
  %93 = getelementptr inbounds %struct.Obj, %struct.Obj* %92, i32 0, i32 7
  %94 = load i32, i32* %93, align 8
  store i32 %94, i32* %7, align 4
  %95 = load i32, i32* %4, align 4
  %96 = mul nsw i32 %95, 8
  %97 = load i32, i32* %7, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.40, i64 0, i64 0), i32 noundef %96, i32 noundef %97)
  %98 = load i32, i32* %5, align 4
  %99 = mul nsw i32 %98, 8
  %100 = add nsw i32 %99, 48
  %101 = load i32, i32* %7, align 4
  %102 = add nsw i32 %101, 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.40, i64 0, i64 0), i32 noundef %100, i32 noundef %102)
  %103 = load i32, i32* %7, align 4
  %104 = add nsw i32 %103, 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.41, i64 0, i64 0), i32 noundef %104)
  %105 = load i32, i32* %7, align 4
  %106 = add nsw i32 %105, 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.42, i64 0, i64 0), i32 noundef %106)
  %107 = load i32, i32* %7, align 4
  %108 = add nsw i32 %107, 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.41, i64 0, i64 0), i32 noundef %108)
  %109 = load i32, i32* %7, align 4
  %110 = add nsw i32 %109, 24
  %111 = load i32, i32* %7, align 4
  %112 = add nsw i32 %111, 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.43, i64 0, i64 0), i32 noundef %110, i32 noundef %112)
  %113 = load i32, i32* %7, align 4
  %114 = add nsw i32 %113, 24
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.44, i64 0, i64 0), i32 noundef %114)
  %115 = load i32, i32* %7, align 4
  %116 = add nsw i32 %115, 32
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.45, i64 0, i64 0), i32 noundef %116)
  %117 = load i32, i32* %7, align 4
  %118 = add nsw i32 %117, 40
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.46, i64 0, i64 0), i32 noundef %118)
  %119 = load i32, i32* %7, align 4
  %120 = add nsw i32 %119, 48
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.47, i64 0, i64 0), i32 noundef %120)
  %121 = load i32, i32* %7, align 4
  %122 = add nsw i32 %121, 56
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.48, i64 0, i64 0), i32 noundef %122)
  %123 = load i32, i32* %7, align 4
  %124 = add nsw i32 %123, 64
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.49, i64 0, i64 0), i32 noundef %124)
  %125 = load i32, i32* %7, align 4
  %126 = add nsw i32 %125, 72
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.50, i64 0, i64 0), i32 noundef %126)
  %127 = load i32, i32* %7, align 4
  %128 = add nsw i32 %127, 80
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.51, i64 0, i64 0), i32 noundef %128)
  %129 = load i32, i32* %7, align 4
  %130 = add nsw i32 %129, 88
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.52, i64 0, i64 0), i32 noundef %130)
  %131 = load i32, i32* %7, align 4
  %132 = add nsw i32 %131, 96
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.53, i64 0, i64 0), i32 noundef %132)
  %133 = load i32, i32* %7, align 4
  %134 = add nsw i32 %133, 104
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.54, i64 0, i64 0), i32 noundef %134)
  %135 = load i32, i32* %7, align 4
  %136 = add nsw i32 %135, 112
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.55, i64 0, i64 0), i32 noundef %136)
  %137 = load i32, i32* %7, align 4
  %138 = add nsw i32 %137, 120
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.56, i64 0, i64 0), i32 noundef %138)
  %139 = load i32, i32* %7, align 4
  %140 = add nsw i32 %139, 128
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.57, i64 0, i64 0), i32 noundef %140)
  br label %141

141:                                              ; preds = %89, %46
  store i32 0, i32* %8, align 4
  store i32 0, i32* %9, align 4
  %142 = load %struct.Obj*, %struct.Obj** %3, align 8
  %143 = getelementptr inbounds %struct.Obj, %struct.Obj* %142, i32 0, i32 18
  %144 = load %struct.Obj*, %struct.Obj** %143, align 8
  store %struct.Obj* %144, %struct.Obj** %10, align 8
  br label %145

145:                                              ; preds = %256, %141
  %146 = load %struct.Obj*, %struct.Obj** %10, align 8
  %147 = icmp ne %struct.Obj* %146, null
  br i1 %147, label %148, label %260

148:                                              ; preds = %145
  %149 = load %struct.Obj*, %struct.Obj** %10, align 8
  %150 = getelementptr inbounds %struct.Obj, %struct.Obj* %149, i32 0, i32 7
  %151 = load i32, i32* %150, align 8
  %152 = icmp sgt i32 %151, 0
  br i1 %152, label %153, label %154

153:                                              ; preds = %148
  br label %256

154:                                              ; preds = %148
  %155 = load %struct.Obj*, %struct.Obj** %10, align 8
  %156 = getelementptr inbounds %struct.Obj, %struct.Obj* %155, i32 0, i32 3
  %157 = load %struct.Type*, %struct.Type** %156, align 8
  store %struct.Type* %157, %struct.Type** %11, align 8
  %158 = load %struct.Type*, %struct.Type** %11, align 8
  %159 = getelementptr inbounds %struct.Type, %struct.Type* %158, i32 0, i32 0
  %160 = load i32, i32* %159, align 8
  switch i32 %160, label %246 [
    i32 14, label %161
    i32 15, label %161
    i32 6, label %237
    i32 7, label %237
  ]

161:                                              ; preds = %154, %154
  %162 = load %struct.Type*, %struct.Type** %11, align 8
  %163 = getelementptr inbounds %struct.Type, %struct.Type* %162, i32 0, i32 1
  %164 = load i32, i32* %163, align 4
  %165 = icmp sle i32 %164, 16
  br i1 %165, label %166, label %167

166:                                              ; preds = %161
  br label %168

167:                                              ; preds = %161
  call void @__assert_fail(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.58, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 1792, i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @__PRETTY_FUNCTION__.emit_text, i64 0, i64 0)) #8
  unreachable

168:                                              ; preds = %166
  %169 = load %struct.Type*, %struct.Type** %11, align 8
  %170 = call zeroext i1 @has_flonum(%struct.Type* noundef %169, i32 noundef 0, i32 noundef 8, i32 noundef 0)
  br i1 %170, label %171, label %188

171:                                              ; preds = %168
  %172 = load i32, i32* %9, align 4
  %173 = add nsw i32 %172, 1
  store i32 %173, i32* %9, align 4
  %174 = load %struct.Obj*, %struct.Obj** %10, align 8
  %175 = getelementptr inbounds %struct.Obj, %struct.Obj* %174, i32 0, i32 7
  %176 = load i32, i32* %175, align 8
  %177 = load %struct.Type*, %struct.Type** %11, align 8
  %178 = getelementptr inbounds %struct.Type, %struct.Type* %177, i32 0, i32 1
  %179 = load i32, i32* %178, align 4
  %180 = icmp slt i32 8, %179
  br i1 %180, label %181, label %182

181:                                              ; preds = %171
  br label %186

182:                                              ; preds = %171
  %183 = load %struct.Type*, %struct.Type** %11, align 8
  %184 = getelementptr inbounds %struct.Type, %struct.Type* %183, i32 0, i32 1
  %185 = load i32, i32* %184, align 4
  br label %186

186:                                              ; preds = %182, %181
  %187 = phi i32 [ 8, %181 ], [ %185, %182 ]
  call void @store_fp(i32 noundef %172, i32 noundef %176, i32 noundef %187)
  br label %205

188:                                              ; preds = %168
  %189 = load i32, i32* %8, align 4
  %190 = add nsw i32 %189, 1
  store i32 %190, i32* %8, align 4
  %191 = load %struct.Obj*, %struct.Obj** %10, align 8
  %192 = getelementptr inbounds %struct.Obj, %struct.Obj* %191, i32 0, i32 7
  %193 = load i32, i32* %192, align 8
  %194 = load %struct.Type*, %struct.Type** %11, align 8
  %195 = getelementptr inbounds %struct.Type, %struct.Type* %194, i32 0, i32 1
  %196 = load i32, i32* %195, align 4
  %197 = icmp slt i32 8, %196
  br i1 %197, label %198, label %199

198:                                              ; preds = %188
  br label %203

199:                                              ; preds = %188
  %200 = load %struct.Type*, %struct.Type** %11, align 8
  %201 = getelementptr inbounds %struct.Type, %struct.Type* %200, i32 0, i32 1
  %202 = load i32, i32* %201, align 4
  br label %203

203:                                              ; preds = %199, %198
  %204 = phi i32 [ 8, %198 ], [ %202, %199 ]
  call void @store_gp(i32 noundef %189, i32 noundef %193, i32 noundef %204)
  br label %205

205:                                              ; preds = %203, %186
  %206 = load %struct.Type*, %struct.Type** %11, align 8
  %207 = getelementptr inbounds %struct.Type, %struct.Type* %206, i32 0, i32 1
  %208 = load i32, i32* %207, align 4
  %209 = icmp sgt i32 %208, 8
  br i1 %209, label %210, label %236

210:                                              ; preds = %205
  %211 = load %struct.Type*, %struct.Type** %11, align 8
  %212 = call zeroext i1 @has_flonum(%struct.Type* noundef %211, i32 noundef 8, i32 noundef 16, i32 noundef 0)
  br i1 %212, label %213, label %224

213:                                              ; preds = %210
  %214 = load i32, i32* %9, align 4
  %215 = add nsw i32 %214, 1
  store i32 %215, i32* %9, align 4
  %216 = load %struct.Obj*, %struct.Obj** %10, align 8
  %217 = getelementptr inbounds %struct.Obj, %struct.Obj* %216, i32 0, i32 7
  %218 = load i32, i32* %217, align 8
  %219 = add nsw i32 %218, 8
  %220 = load %struct.Type*, %struct.Type** %11, align 8
  %221 = getelementptr inbounds %struct.Type, %struct.Type* %220, i32 0, i32 1
  %222 = load i32, i32* %221, align 4
  %223 = sub nsw i32 %222, 8
  call void @store_fp(i32 noundef %214, i32 noundef %219, i32 noundef %223)
  br label %235

224:                                              ; preds = %210
  %225 = load i32, i32* %8, align 4
  %226 = add nsw i32 %225, 1
  store i32 %226, i32* %8, align 4
  %227 = load %struct.Obj*, %struct.Obj** %10, align 8
  %228 = getelementptr inbounds %struct.Obj, %struct.Obj* %227, i32 0, i32 7
  %229 = load i32, i32* %228, align 8
  %230 = add nsw i32 %229, 8
  %231 = load %struct.Type*, %struct.Type** %11, align 8
  %232 = getelementptr inbounds %struct.Type, %struct.Type* %231, i32 0, i32 1
  %233 = load i32, i32* %232, align 4
  %234 = sub nsw i32 %233, 8
  call void @store_gp(i32 noundef %225, i32 noundef %230, i32 noundef %234)
  br label %235

235:                                              ; preds = %224, %213
  br label %236

236:                                              ; preds = %235, %205
  br label %255

237:                                              ; preds = %154, %154
  %238 = load i32, i32* %9, align 4
  %239 = add nsw i32 %238, 1
  store i32 %239, i32* %9, align 4
  %240 = load %struct.Obj*, %struct.Obj** %10, align 8
  %241 = getelementptr inbounds %struct.Obj, %struct.Obj* %240, i32 0, i32 7
  %242 = load i32, i32* %241, align 8
  %243 = load %struct.Type*, %struct.Type** %11, align 8
  %244 = getelementptr inbounds %struct.Type, %struct.Type* %243, i32 0, i32 1
  %245 = load i32, i32* %244, align 4
  call void @store_fp(i32 noundef %238, i32 noundef %242, i32 noundef %245)
  br label %255

246:                                              ; preds = %154
  %247 = load i32, i32* %8, align 4
  %248 = add nsw i32 %247, 1
  store i32 %248, i32* %8, align 4
  %249 = load %struct.Obj*, %struct.Obj** %10, align 8
  %250 = getelementptr inbounds %struct.Obj, %struct.Obj* %249, i32 0, i32 7
  %251 = load i32, i32* %250, align 8
  %252 = load %struct.Type*, %struct.Type** %11, align 8
  %253 = getelementptr inbounds %struct.Type, %struct.Type* %252, i32 0, i32 1
  %254 = load i32, i32* %253, align 4
  call void @store_gp(i32 noundef %247, i32 noundef %251, i32 noundef %254)
  br label %255

255:                                              ; preds = %246, %237, %236
  br label %256

256:                                              ; preds = %255, %153
  %257 = load %struct.Obj*, %struct.Obj** %10, align 8
  %258 = getelementptr inbounds %struct.Obj, %struct.Obj* %257, i32 0, i32 0
  %259 = load %struct.Obj*, %struct.Obj** %258, align 8
  store %struct.Obj* %259, %struct.Obj** %10, align 8
  br label %145, !llvm.loop !14

260:                                              ; preds = %145
  %261 = load %struct.Obj*, %struct.Obj** %3, align 8
  %262 = getelementptr inbounds %struct.Obj, %struct.Obj* %261, i32 0, i32 19
  %263 = load %struct.Node*, %struct.Node** %262, align 8
  call void @gen_stmt(%struct.Node* noundef %263)
  %264 = load i32, i32* @depth, align 4
  %265 = icmp eq i32 %264, 0
  br i1 %265, label %266, label %267

266:                                              ; preds = %260
  br label %268

267:                                              ; preds = %260
  call void @__assert_fail(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.59, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 1817, i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @__PRETTY_FUNCTION__.emit_text, i64 0, i64 0)) #8
  unreachable

268:                                              ; preds = %266
  %269 = load %struct.Obj*, %struct.Obj** %3, align 8
  %270 = getelementptr inbounds %struct.Obj, %struct.Obj* %269, i32 0, i32 1
  %271 = load i8*, i8** %270, align 8
  %272 = call i32 @strcmp(i8* noundef %271, i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.60, i64 0, i64 0)) #9
  %273 = icmp eq i32 %272, 0
  br i1 %273, label %274, label %275

274:                                              ; preds = %268
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.61, i64 0, i64 0))
  br label %275

275:                                              ; preds = %274, %268
  %276 = load %struct.Obj*, %struct.Obj** %3, align 8
  %277 = getelementptr inbounds %struct.Obj, %struct.Obj* %276, i32 0, i32 1
  %278 = load i8*, i8** %277, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.62, i64 0, i64 0), i8* noundef %278)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.63, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.64, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.65, i64 0, i64 0))
  br label %279

279:                                              ; preds = %275, %32, %26
  %280 = load %struct.Obj*, %struct.Obj** %3, align 8
  %281 = getelementptr inbounds %struct.Obj, %struct.Obj* %280, i32 0, i32 0
  %282 = load %struct.Obj*, %struct.Obj** %281, align 8
  store %struct.Obj* %282, %struct.Obj** %3, align 8
  br label %13, !llvm.loop !15

283:                                              ; preds = %13
  ret void
}

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.va_start(i8*) #3

declare i32 @vfprintf(%struct._IO_FILE* noundef, i8* noundef, %struct.__va_list_tag* noundef) #2

; Function Attrs: nofree nosync nounwind willreturn
declare void @llvm.va_end(i8*) #3

declare i32 @fprintf(%struct._IO_FILE* noundef, i8* noundef, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @has_flonum(%struct.Type* noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = alloca i1, align 1
  %6 = alloca %struct.Type*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca %struct.Member*, align 8
  %11 = alloca i32, align 4
  store %struct.Type* %0, %struct.Type** %6, align 8
  store i32 %1, i32* %7, align 4
  store i32 %2, i32* %8, align 4
  store i32 %3, i32* %9, align 4
  %12 = load %struct.Type*, %struct.Type** %6, align 8
  %13 = getelementptr inbounds %struct.Type, %struct.Type* %12, i32 0, i32 0
  %14 = load i32, i32* %13, align 8
  %15 = icmp eq i32 %14, 14
  br i1 %15, label %21, label %16

16:                                               ; preds = %4
  %17 = load %struct.Type*, %struct.Type** %6, align 8
  %18 = getelementptr inbounds %struct.Type, %struct.Type* %17, i32 0, i32 0
  %19 = load i32, i32* %18, align 8
  %20 = icmp eq i32 %19, 15
  br i1 %20, label %21, label %47

21:                                               ; preds = %16, %4
  %22 = load %struct.Type*, %struct.Type** %6, align 8
  %23 = getelementptr inbounds %struct.Type, %struct.Type* %22, i32 0, i32 14
  %24 = load %struct.Member*, %struct.Member** %23, align 8
  store %struct.Member* %24, %struct.Member** %10, align 8
  br label %25

25:                                               ; preds = %42, %21
  %26 = load %struct.Member*, %struct.Member** %10, align 8
  %27 = icmp ne %struct.Member* %26, null
  br i1 %27, label %28, label %46

28:                                               ; preds = %25
  %29 = load %struct.Member*, %struct.Member** %10, align 8
  %30 = getelementptr inbounds %struct.Member, %struct.Member* %29, i32 0, i32 1
  %31 = load %struct.Type*, %struct.Type** %30, align 8
  %32 = load i32, i32* %7, align 4
  %33 = load i32, i32* %8, align 4
  %34 = load i32, i32* %9, align 4
  %35 = load %struct.Member*, %struct.Member** %10, align 8
  %36 = getelementptr inbounds %struct.Member, %struct.Member* %35, i32 0, i32 6
  %37 = load i32, i32* %36, align 8
  %38 = add nsw i32 %34, %37
  %39 = call zeroext i1 @has_flonum(%struct.Type* noundef %31, i32 noundef %32, i32 noundef %33, i32 noundef %38)
  br i1 %39, label %41, label %40

40:                                               ; preds = %28
  store i1 false, i1* %5, align 1
  br label %101

41:                                               ; preds = %28
  br label %42

42:                                               ; preds = %41
  %43 = load %struct.Member*, %struct.Member** %10, align 8
  %44 = getelementptr inbounds %struct.Member, %struct.Member* %43, i32 0, i32 0
  %45 = load %struct.Member*, %struct.Member** %44, align 8
  store %struct.Member* %45, %struct.Member** %10, align 8
  br label %25, !llvm.loop !16

46:                                               ; preds = %25
  store i1 true, i1* %5, align 1
  br label %101

47:                                               ; preds = %16
  %48 = load %struct.Type*, %struct.Type** %6, align 8
  %49 = getelementptr inbounds %struct.Type, %struct.Type* %48, i32 0, i32 0
  %50 = load i32, i32* %49, align 8
  %51 = icmp eq i32 %50, 12
  br i1 %51, label %52, label %81

52:                                               ; preds = %47
  store i32 0, i32* %11, align 4
  br label %53

53:                                               ; preds = %77, %52
  %54 = load i32, i32* %11, align 4
  %55 = load %struct.Type*, %struct.Type** %6, align 8
  %56 = getelementptr inbounds %struct.Type, %struct.Type* %55, i32 0, i32 11
  %57 = load i32, i32* %56, align 8
  %58 = icmp slt i32 %54, %57
  br i1 %58, label %59, label %80

59:                                               ; preds = %53
  %60 = load %struct.Type*, %struct.Type** %6, align 8
  %61 = getelementptr inbounds %struct.Type, %struct.Type* %60, i32 0, i32 8
  %62 = load %struct.Type*, %struct.Type** %61, align 8
  %63 = load i32, i32* %7, align 4
  %64 = load i32, i32* %8, align 4
  %65 = load i32, i32* %9, align 4
  %66 = load %struct.Type*, %struct.Type** %6, align 8
  %67 = getelementptr inbounds %struct.Type, %struct.Type* %66, i32 0, i32 8
  %68 = load %struct.Type*, %struct.Type** %67, align 8
  %69 = getelementptr inbounds %struct.Type, %struct.Type* %68, i32 0, i32 1
  %70 = load i32, i32* %69, align 4
  %71 = load i32, i32* %11, align 4
  %72 = mul nsw i32 %70, %71
  %73 = add nsw i32 %65, %72
  %74 = call zeroext i1 @has_flonum(%struct.Type* noundef %62, i32 noundef %63, i32 noundef %64, i32 noundef %73)
  br i1 %74, label %76, label %75

75:                                               ; preds = %59
  store i1 false, i1* %5, align 1
  br label %101

76:                                               ; preds = %59
  br label %77

77:                                               ; preds = %76
  %78 = load i32, i32* %11, align 4
  %79 = add nsw i32 %78, 1
  store i32 %79, i32* %11, align 4
  br label %53, !llvm.loop !17

80:                                               ; preds = %53
  store i1 true, i1* %5, align 1
  br label %101

81:                                               ; preds = %47
  %82 = load i32, i32* %9, align 4
  %83 = load i32, i32* %7, align 4
  %84 = icmp slt i32 %82, %83
  br i1 %84, label %99, label %85

85:                                               ; preds = %81
  %86 = load i32, i32* %8, align 4
  %87 = load i32, i32* %9, align 4
  %88 = icmp sle i32 %86, %87
  br i1 %88, label %99, label %89

89:                                               ; preds = %85
  %90 = load %struct.Type*, %struct.Type** %6, align 8
  %91 = getelementptr inbounds %struct.Type, %struct.Type* %90, i32 0, i32 0
  %92 = load i32, i32* %91, align 8
  %93 = icmp eq i32 %92, 6
  br i1 %93, label %99, label %94

94:                                               ; preds = %89
  %95 = load %struct.Type*, %struct.Type** %6, align 8
  %96 = getelementptr inbounds %struct.Type, %struct.Type* %95, i32 0, i32 0
  %97 = load i32, i32* %96, align 8
  %98 = icmp eq i32 %97, 7
  br label %99

99:                                               ; preds = %94, %89, %85, %81
  %100 = phi i1 [ true, %89 ], [ true, %85 ], [ true, %81 ], [ %98, %94 ]
  store i1 %100, i1* %5, align 1
  br label %101

101:                                              ; preds = %99, %80, %75, %46, %40
  %102 = load i1, i1* %5, align 1
  ret i1 %102
}

declare zeroext i1 @is_flonum(%struct.Type* noundef) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8* noundef, i8* noundef, i32 noundef, i8* noundef) #4

; Function Attrs: noinline nounwind optnone uwtable
define internal void @store_fp(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  %7 = load i32, i32* %6, align 4
  switch i32 %7, label %14 [
    i32 4, label %8
    i32 8, label %11
  ]

8:                                                ; preds = %3
  %9 = load i32, i32* %4, align 4
  %10 = load i32, i32* %5, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @.str.66, i64 0, i64 0), i32 noundef %9, i32 noundef %10)
  br label %15

11:                                               ; preds = %3
  %12 = load i32, i32* %4, align 4
  %13 = load i32, i32* %5, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @.str.67, i64 0, i64 0), i32 noundef %12, i32 noundef %13)
  br label %15

14:                                               ; preds = %3
  call void (i8*, ...) @error(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 1683) #7
  unreachable

15:                                               ; preds = %11, %8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @store_gp(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  %8 = load i32, i32* %6, align 4
  switch i32 %8, label %33 [
    i32 1, label %9
    i32 2, label %15
    i32 4, label %21
    i32 8, label %27
  ]

9:                                                ; preds = %3
  %10 = load i32, i32* %4, align 4
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg8, i64 0, i64 %11
  %13 = load i8*, i8** %12, align 8
  %14 = load i32, i32* %5, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.68, i64 0, i64 0), i8* noundef %13, i32 noundef %14)
  br label %54

15:                                               ; preds = %3
  %16 = load i32, i32* %4, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg16, i64 0, i64 %17
  %19 = load i8*, i8** %18, align 8
  %20 = load i32, i32* %5, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.68, i64 0, i64 0), i8* noundef %19, i32 noundef %20)
  br label %54

21:                                               ; preds = %3
  %22 = load i32, i32* %4, align 4
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg32, i64 0, i64 %23
  %25 = load i8*, i8** %24, align 8
  %26 = load i32, i32* %5, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.68, i64 0, i64 0), i8* noundef %25, i32 noundef %26)
  br label %54

27:                                               ; preds = %3
  %28 = load i32, i32* %4, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg64, i64 0, i64 %29
  %31 = load i8*, i8** %30, align 8
  %32 = load i32, i32* %5, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.68, i64 0, i64 0), i8* noundef %31, i32 noundef %32)
  br label %54

33:                                               ; preds = %3
  store i32 0, i32* %7, align 4
  br label %34

34:                                               ; preds = %50, %33
  %35 = load i32, i32* %7, align 4
  %36 = load i32, i32* %6, align 4
  %37 = icmp slt i32 %35, %36
  br i1 %37, label %38, label %53

38:                                               ; preds = %34
  %39 = load i32, i32* %4, align 4
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg8, i64 0, i64 %40
  %42 = load i8*, i8** %41, align 8
  %43 = load i32, i32* %5, align 4
  %44 = load i32, i32* %7, align 4
  %45 = add nsw i32 %43, %44
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.68, i64 0, i64 0), i8* noundef %42, i32 noundef %45)
  %46 = load i32, i32* %4, align 4
  %47 = sext i32 %46 to i64
  %48 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg64, i64 0, i64 %47
  %49 = load i8*, i8** %48, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.69, i64 0, i64 0), i8* noundef %49)
  br label %50

50:                                               ; preds = %38
  %51 = load i32, i32* %7, align 4
  %52 = add nsw i32 %51, 1
  store i32 %52, i32* %7, align 4
  br label %34, !llvm.loop !18

53:                                               ; preds = %34
  br label %54

54:                                               ; preds = %53, %27, %21, %15, %9
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @gen_stmt(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca %struct.Node*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca %struct.Node*, align 8
  %10 = alloca %struct.Type*, align 8
  store %struct.Node* %0, %struct.Node** %2, align 8
  %11 = load %struct.Node*, %struct.Node** %2, align 8
  %12 = getelementptr inbounds %struct.Node, %struct.Node* %11, i32 0, i32 3
  %13 = load %struct.Token*, %struct.Token** %12, align 8
  %14 = getelementptr inbounds %struct.Token, %struct.Token* %13, i32 0, i32 8
  %15 = load %struct.File*, %struct.File** %14, align 16
  %16 = getelementptr inbounds %struct.File, %struct.File* %15, i32 0, i32 1
  %17 = load i32, i32* %16, align 8
  %18 = load %struct.Node*, %struct.Node** %2, align 8
  %19 = getelementptr inbounds %struct.Node, %struct.Node* %18, i32 0, i32 3
  %20 = load %struct.Token*, %struct.Token** %19, align 8
  %21 = getelementptr inbounds %struct.Token, %struct.Token* %20, i32 0, i32 10
  %22 = load i32, i32* %21, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.86, i64 0, i64 0), i32 noundef %17, i32 noundef %22)
  %23 = load %struct.Node*, %struct.Node** %2, align 8
  %24 = getelementptr inbounds %struct.Node, %struct.Node* %23, i32 0, i32 0
  %25 = load i32, i32* %24, align 16
  switch i32 %25, label %284 [
    i32 27, label %26
    i32 28, label %52
    i32 29, label %100
    i32 30, label %121
    i32 31, label %210
    i32 32, label %217
    i32 33, label %231
    i32 34, label %235
    i32 35, label %239
    i32 26, label %246
    i32 38, label %276
    i32 45, label %280
  ]

26:                                               ; preds = %1
  %27 = call i32 @count()
  store i32 %27, i32* %3, align 4
  %28 = load %struct.Node*, %struct.Node** %2, align 8
  %29 = getelementptr inbounds %struct.Node, %struct.Node* %28, i32 0, i32 6
  %30 = load %struct.Node*, %struct.Node** %29, align 16
  call void @gen_expr(%struct.Node* noundef %30)
  %31 = load %struct.Node*, %struct.Node** %2, align 8
  %32 = getelementptr inbounds %struct.Node, %struct.Node* %31, i32 0, i32 6
  %33 = load %struct.Node*, %struct.Node** %32, align 16
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 2
  %35 = load %struct.Type*, %struct.Type** %34, align 16
  call void @cmp_zero(%struct.Type* noundef %35)
  %36 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.87, i64 0, i64 0), i32 noundef %36)
  %37 = load %struct.Node*, %struct.Node** %2, align 8
  %38 = getelementptr inbounds %struct.Node, %struct.Node* %37, i32 0, i32 7
  %39 = load %struct.Node*, %struct.Node** %38, align 8
  call void @gen_stmt(%struct.Node* noundef %39)
  %40 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.88, i64 0, i64 0), i32 noundef %40)
  %41 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.89, i64 0, i64 0), i32 noundef %41)
  %42 = load %struct.Node*, %struct.Node** %2, align 8
  %43 = getelementptr inbounds %struct.Node, %struct.Node* %42, i32 0, i32 8
  %44 = load %struct.Node*, %struct.Node** %43, align 16
  %45 = icmp ne %struct.Node* %44, null
  br i1 %45, label %46, label %50

46:                                               ; preds = %26
  %47 = load %struct.Node*, %struct.Node** %2, align 8
  %48 = getelementptr inbounds %struct.Node, %struct.Node* %47, i32 0, i32 8
  %49 = load %struct.Node*, %struct.Node** %48, align 16
  call void @gen_stmt(%struct.Node* noundef %49)
  br label %50

50:                                               ; preds = %46, %26
  %51 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.90, i64 0, i64 0), i32 noundef %51)
  br label %288

52:                                               ; preds = %1
  %53 = call i32 @count()
  store i32 %53, i32* %4, align 4
  %54 = load %struct.Node*, %struct.Node** %2, align 8
  %55 = getelementptr inbounds %struct.Node, %struct.Node* %54, i32 0, i32 9
  %56 = load %struct.Node*, %struct.Node** %55, align 8
  %57 = icmp ne %struct.Node* %56, null
  br i1 %57, label %58, label %62

58:                                               ; preds = %52
  %59 = load %struct.Node*, %struct.Node** %2, align 8
  %60 = getelementptr inbounds %struct.Node, %struct.Node* %59, i32 0, i32 9
  %61 = load %struct.Node*, %struct.Node** %60, align 8
  call void @gen_stmt(%struct.Node* noundef %61)
  br label %62

62:                                               ; preds = %58, %52
  %63 = load i32, i32* %4, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.91, i64 0, i64 0), i32 noundef %63)
  %64 = load %struct.Node*, %struct.Node** %2, align 8
  %65 = getelementptr inbounds %struct.Node, %struct.Node* %64, i32 0, i32 6
  %66 = load %struct.Node*, %struct.Node** %65, align 16
  %67 = icmp ne %struct.Node* %66, null
  br i1 %67, label %68, label %80

68:                                               ; preds = %62
  %69 = load %struct.Node*, %struct.Node** %2, align 8
  %70 = getelementptr inbounds %struct.Node, %struct.Node* %69, i32 0, i32 6
  %71 = load %struct.Node*, %struct.Node** %70, align 16
  call void @gen_expr(%struct.Node* noundef %71)
  %72 = load %struct.Node*, %struct.Node** %2, align 8
  %73 = getelementptr inbounds %struct.Node, %struct.Node* %72, i32 0, i32 6
  %74 = load %struct.Node*, %struct.Node** %73, align 16
  %75 = getelementptr inbounds %struct.Node, %struct.Node* %74, i32 0, i32 2
  %76 = load %struct.Type*, %struct.Type** %75, align 16
  call void @cmp_zero(%struct.Type* noundef %76)
  %77 = load %struct.Node*, %struct.Node** %2, align 8
  %78 = getelementptr inbounds %struct.Node, %struct.Node* %77, i32 0, i32 11
  %79 = load i8*, i8** %78, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.92, i64 0, i64 0), i8* noundef %79)
  br label %80

80:                                               ; preds = %68, %62
  %81 = load %struct.Node*, %struct.Node** %2, align 8
  %82 = getelementptr inbounds %struct.Node, %struct.Node* %81, i32 0, i32 7
  %83 = load %struct.Node*, %struct.Node** %82, align 8
  call void @gen_stmt(%struct.Node* noundef %83)
  %84 = load %struct.Node*, %struct.Node** %2, align 8
  %85 = getelementptr inbounds %struct.Node, %struct.Node* %84, i32 0, i32 12
  %86 = load i8*, i8** %85, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %86)
  %87 = load %struct.Node*, %struct.Node** %2, align 8
  %88 = getelementptr inbounds %struct.Node, %struct.Node* %87, i32 0, i32 10
  %89 = load %struct.Node*, %struct.Node** %88, align 16
  %90 = icmp ne %struct.Node* %89, null
  br i1 %90, label %91, label %95

91:                                               ; preds = %80
  %92 = load %struct.Node*, %struct.Node** %2, align 8
  %93 = getelementptr inbounds %struct.Node, %struct.Node* %92, i32 0, i32 10
  %94 = load %struct.Node*, %struct.Node** %93, align 16
  call void @gen_expr(%struct.Node* noundef %94)
  br label %95

95:                                               ; preds = %91, %80
  %96 = load i32, i32* %4, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.93, i64 0, i64 0), i32 noundef %96)
  %97 = load %struct.Node*, %struct.Node** %2, align 8
  %98 = getelementptr inbounds %struct.Node, %struct.Node* %97, i32 0, i32 11
  %99 = load i8*, i8** %98, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %99)
  br label %288

100:                                              ; preds = %1
  %101 = call i32 @count()
  store i32 %101, i32* %5, align 4
  %102 = load i32, i32* %5, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.91, i64 0, i64 0), i32 noundef %102)
  %103 = load %struct.Node*, %struct.Node** %2, align 8
  %104 = getelementptr inbounds %struct.Node, %struct.Node* %103, i32 0, i32 7
  %105 = load %struct.Node*, %struct.Node** %104, align 8
  call void @gen_stmt(%struct.Node* noundef %105)
  %106 = load %struct.Node*, %struct.Node** %2, align 8
  %107 = getelementptr inbounds %struct.Node, %struct.Node* %106, i32 0, i32 12
  %108 = load i8*, i8** %107, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %108)
  %109 = load %struct.Node*, %struct.Node** %2, align 8
  %110 = getelementptr inbounds %struct.Node, %struct.Node* %109, i32 0, i32 6
  %111 = load %struct.Node*, %struct.Node** %110, align 16
  call void @gen_expr(%struct.Node* noundef %111)
  %112 = load %struct.Node*, %struct.Node** %2, align 8
  %113 = getelementptr inbounds %struct.Node, %struct.Node* %112, i32 0, i32 6
  %114 = load %struct.Node*, %struct.Node** %113, align 16
  %115 = getelementptr inbounds %struct.Node, %struct.Node* %114, i32 0, i32 2
  %116 = load %struct.Type*, %struct.Type** %115, align 16
  call void @cmp_zero(%struct.Type* noundef %116)
  %117 = load i32, i32* %5, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.94, i64 0, i64 0), i32 noundef %117)
  %118 = load %struct.Node*, %struct.Node** %2, align 8
  %119 = getelementptr inbounds %struct.Node, %struct.Node* %118, i32 0, i32 11
  %120 = load i8*, i8** %119, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %120)
  br label %288

121:                                              ; preds = %1
  %122 = load %struct.Node*, %struct.Node** %2, align 8
  %123 = getelementptr inbounds %struct.Node, %struct.Node* %122, i32 0, i32 6
  %124 = load %struct.Node*, %struct.Node** %123, align 16
  call void @gen_expr(%struct.Node* noundef %124)
  %125 = load %struct.Node*, %struct.Node** %2, align 8
  %126 = getelementptr inbounds %struct.Node, %struct.Node* %125, i32 0, i32 22
  %127 = load %struct.Node*, %struct.Node** %126, align 16
  store %struct.Node* %127, %struct.Node** %6, align 8
  br label %128

128:                                              ; preds = %185, %121
  %129 = load %struct.Node*, %struct.Node** %6, align 8
  %130 = icmp ne %struct.Node* %129, null
  br i1 %130, label %131, label %189

131:                                              ; preds = %128
  %132 = load %struct.Node*, %struct.Node** %2, align 8
  %133 = getelementptr inbounds %struct.Node, %struct.Node* %132, i32 0, i32 6
  %134 = load %struct.Node*, %struct.Node** %133, align 16
  %135 = getelementptr inbounds %struct.Node, %struct.Node* %134, i32 0, i32 2
  %136 = load %struct.Type*, %struct.Type** %135, align 16
  %137 = getelementptr inbounds %struct.Type, %struct.Type* %136, i32 0, i32 1
  %138 = load i32, i32* %137, align 4
  %139 = icmp eq i32 %138, 8
  %140 = zext i1 %139 to i64
  %141 = select i1 %139, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.16, i64 0, i64 0)
  store i8* %141, i8** %7, align 8
  %142 = load %struct.Node*, %struct.Node** %2, align 8
  %143 = getelementptr inbounds %struct.Node, %struct.Node* %142, i32 0, i32 6
  %144 = load %struct.Node*, %struct.Node** %143, align 16
  %145 = getelementptr inbounds %struct.Node, %struct.Node* %144, i32 0, i32 2
  %146 = load %struct.Type*, %struct.Type** %145, align 16
  %147 = getelementptr inbounds %struct.Type, %struct.Type* %146, i32 0, i32 1
  %148 = load i32, i32* %147, align 4
  %149 = icmp eq i32 %148, 8
  %150 = zext i1 %149 to i64
  %151 = select i1 %149, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.78, i64 0, i64 0)
  store i8* %151, i8** %8, align 8
  %152 = load %struct.Node*, %struct.Node** %6, align 8
  %153 = getelementptr inbounds %struct.Node, %struct.Node* %152, i32 0, i32 24
  %154 = load i64, i64* %153, align 16
  %155 = load %struct.Node*, %struct.Node** %6, align 8
  %156 = getelementptr inbounds %struct.Node, %struct.Node* %155, i32 0, i32 25
  %157 = load i64, i64* %156, align 8
  %158 = icmp eq i64 %154, %157
  br i1 %158, label %159, label %167

159:                                              ; preds = %131
  %160 = load %struct.Node*, %struct.Node** %6, align 8
  %161 = getelementptr inbounds %struct.Node, %struct.Node* %160, i32 0, i32 24
  %162 = load i64, i64* %161, align 16
  %163 = load i8*, i8** %7, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.95, i64 0, i64 0), i64 noundef %162, i8* noundef %163)
  %164 = load %struct.Node*, %struct.Node** %6, align 8
  %165 = getelementptr inbounds %struct.Node, %struct.Node* %164, i32 0, i32 19
  %166 = load i8*, i8** %165, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.92, i64 0, i64 0), i8* noundef %166)
  br label %185

167:                                              ; preds = %131
  %168 = load i8*, i8** %7, align 8
  %169 = load i8*, i8** %8, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.96, i64 0, i64 0), i8* noundef %168, i8* noundef %169)
  %170 = load %struct.Node*, %struct.Node** %6, align 8
  %171 = getelementptr inbounds %struct.Node, %struct.Node* %170, i32 0, i32 24
  %172 = load i64, i64* %171, align 16
  %173 = load i8*, i8** %8, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.97, i64 0, i64 0), i64 noundef %172, i8* noundef %173)
  %174 = load %struct.Node*, %struct.Node** %6, align 8
  %175 = getelementptr inbounds %struct.Node, %struct.Node* %174, i32 0, i32 25
  %176 = load i64, i64* %175, align 8
  %177 = load %struct.Node*, %struct.Node** %6, align 8
  %178 = getelementptr inbounds %struct.Node, %struct.Node* %177, i32 0, i32 24
  %179 = load i64, i64* %178, align 16
  %180 = sub nsw i64 %176, %179
  %181 = load i8*, i8** %8, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.95, i64 0, i64 0), i64 noundef %180, i8* noundef %181)
  %182 = load %struct.Node*, %struct.Node** %6, align 8
  %183 = getelementptr inbounds %struct.Node, %struct.Node* %182, i32 0, i32 19
  %184 = load i8*, i8** %183, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.98, i64 0, i64 0), i8* noundef %184)
  br label %185

185:                                              ; preds = %167, %159
  %186 = load %struct.Node*, %struct.Node** %6, align 8
  %187 = getelementptr inbounds %struct.Node, %struct.Node* %186, i32 0, i32 22
  %188 = load %struct.Node*, %struct.Node** %187, align 16
  store %struct.Node* %188, %struct.Node** %6, align 8
  br label %128, !llvm.loop !19

189:                                              ; preds = %128
  %190 = load %struct.Node*, %struct.Node** %2, align 8
  %191 = getelementptr inbounds %struct.Node, %struct.Node* %190, i32 0, i32 23
  %192 = load %struct.Node*, %struct.Node** %191, align 8
  %193 = icmp ne %struct.Node* %192, null
  br i1 %193, label %194, label %200

194:                                              ; preds = %189
  %195 = load %struct.Node*, %struct.Node** %2, align 8
  %196 = getelementptr inbounds %struct.Node, %struct.Node* %195, i32 0, i32 23
  %197 = load %struct.Node*, %struct.Node** %196, align 8
  %198 = getelementptr inbounds %struct.Node, %struct.Node* %197, i32 0, i32 19
  %199 = load i8*, i8** %198, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.99, i64 0, i64 0), i8* noundef %199)
  br label %200

200:                                              ; preds = %194, %189
  %201 = load %struct.Node*, %struct.Node** %2, align 8
  %202 = getelementptr inbounds %struct.Node, %struct.Node* %201, i32 0, i32 11
  %203 = load i8*, i8** %202, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.99, i64 0, i64 0), i8* noundef %203)
  %204 = load %struct.Node*, %struct.Node** %2, align 8
  %205 = getelementptr inbounds %struct.Node, %struct.Node* %204, i32 0, i32 7
  %206 = load %struct.Node*, %struct.Node** %205, align 8
  call void @gen_stmt(%struct.Node* noundef %206)
  %207 = load %struct.Node*, %struct.Node** %2, align 8
  %208 = getelementptr inbounds %struct.Node, %struct.Node* %207, i32 0, i32 11
  %209 = load i8*, i8** %208, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %209)
  br label %288

210:                                              ; preds = %1
  %211 = load %struct.Node*, %struct.Node** %2, align 8
  %212 = getelementptr inbounds %struct.Node, %struct.Node* %211, i32 0, i32 19
  %213 = load i8*, i8** %212, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %213)
  %214 = load %struct.Node*, %struct.Node** %2, align 8
  %215 = getelementptr inbounds %struct.Node, %struct.Node* %214, i32 0, i32 4
  %216 = load %struct.Node*, %struct.Node** %215, align 16
  call void @gen_stmt(%struct.Node* noundef %216)
  br label %288

217:                                              ; preds = %1
  %218 = load %struct.Node*, %struct.Node** %2, align 8
  %219 = getelementptr inbounds %struct.Node, %struct.Node* %218, i32 0, i32 13
  %220 = load %struct.Node*, %struct.Node** %219, align 8
  store %struct.Node* %220, %struct.Node** %9, align 8
  br label %221

221:                                              ; preds = %226, %217
  %222 = load %struct.Node*, %struct.Node** %9, align 8
  %223 = icmp ne %struct.Node* %222, null
  br i1 %223, label %224, label %230

224:                                              ; preds = %221
  %225 = load %struct.Node*, %struct.Node** %9, align 8
  call void @gen_stmt(%struct.Node* noundef %225)
  br label %226

226:                                              ; preds = %224
  %227 = load %struct.Node*, %struct.Node** %9, align 8
  %228 = getelementptr inbounds %struct.Node, %struct.Node* %227, i32 0, i32 1
  %229 = load %struct.Node*, %struct.Node** %228, align 8
  store %struct.Node* %229, %struct.Node** %9, align 8
  br label %221, !llvm.loop !20

230:                                              ; preds = %221
  br label %288

231:                                              ; preds = %1
  %232 = load %struct.Node*, %struct.Node** %2, align 8
  %233 = getelementptr inbounds %struct.Node, %struct.Node* %232, i32 0, i32 20
  %234 = load i8*, i8** %233, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.99, i64 0, i64 0), i8* noundef %234)
  br label %288

235:                                              ; preds = %1
  %236 = load %struct.Node*, %struct.Node** %2, align 8
  %237 = getelementptr inbounds %struct.Node, %struct.Node* %236, i32 0, i32 4
  %238 = load %struct.Node*, %struct.Node** %237, align 16
  call void @gen_expr(%struct.Node* noundef %238)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.100, i64 0, i64 0))
  br label %288

239:                                              ; preds = %1
  %240 = load %struct.Node*, %struct.Node** %2, align 8
  %241 = getelementptr inbounds %struct.Node, %struct.Node* %240, i32 0, i32 20
  %242 = load i8*, i8** %241, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.28, i64 0, i64 0), i8* noundef %242)
  %243 = load %struct.Node*, %struct.Node** %2, align 8
  %244 = getelementptr inbounds %struct.Node, %struct.Node* %243, i32 0, i32 4
  %245 = load %struct.Node*, %struct.Node** %244, align 16
  call void @gen_stmt(%struct.Node* noundef %245)
  br label %288

246:                                              ; preds = %1
  %247 = load %struct.Node*, %struct.Node** %2, align 8
  %248 = getelementptr inbounds %struct.Node, %struct.Node* %247, i32 0, i32 4
  %249 = load %struct.Node*, %struct.Node** %248, align 16
  %250 = icmp ne %struct.Node* %249, null
  br i1 %250, label %251, label %272

251:                                              ; preds = %246
  %252 = load %struct.Node*, %struct.Node** %2, align 8
  %253 = getelementptr inbounds %struct.Node, %struct.Node* %252, i32 0, i32 4
  %254 = load %struct.Node*, %struct.Node** %253, align 16
  call void @gen_expr(%struct.Node* noundef %254)
  %255 = load %struct.Node*, %struct.Node** %2, align 8
  %256 = getelementptr inbounds %struct.Node, %struct.Node* %255, i32 0, i32 4
  %257 = load %struct.Node*, %struct.Node** %256, align 16
  %258 = getelementptr inbounds %struct.Node, %struct.Node* %257, i32 0, i32 2
  %259 = load %struct.Type*, %struct.Type** %258, align 16
  store %struct.Type* %259, %struct.Type** %10, align 8
  %260 = load %struct.Type*, %struct.Type** %10, align 8
  %261 = getelementptr inbounds %struct.Type, %struct.Type* %260, i32 0, i32 0
  %262 = load i32, i32* %261, align 8
  switch i32 %262, label %271 [
    i32 14, label %263
    i32 15, label %263
  ]

263:                                              ; preds = %251, %251
  %264 = load %struct.Type*, %struct.Type** %10, align 8
  %265 = getelementptr inbounds %struct.Type, %struct.Type* %264, i32 0, i32 1
  %266 = load i32, i32* %265, align 4
  %267 = icmp sle i32 %266, 16
  br i1 %267, label %268, label %269

268:                                              ; preds = %263
  call void @copy_struct_reg()
  br label %270

269:                                              ; preds = %263
  call void @copy_struct_mem()
  br label %270

270:                                              ; preds = %269, %268
  br label %271

271:                                              ; preds = %251, %270
  br label %272

272:                                              ; preds = %271, %246
  %273 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %274 = getelementptr inbounds %struct.Obj, %struct.Obj* %273, i32 0, i32 1
  %275 = load i8*, i8** %274, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.101, i64 0, i64 0), i8* noundef %275)
  br label %288

276:                                              ; preds = %1
  %277 = load %struct.Node*, %struct.Node** %2, align 8
  %278 = getelementptr inbounds %struct.Node, %struct.Node* %277, i32 0, i32 4
  %279 = load %struct.Node*, %struct.Node** %278, align 16
  call void @gen_expr(%struct.Node* noundef %279)
  br label %288

280:                                              ; preds = %1
  %281 = load %struct.Node*, %struct.Node** %2, align 8
  %282 = getelementptr inbounds %struct.Node, %struct.Node* %281, i32 0, i32 26
  %283 = load i8*, i8** %282, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.102, i64 0, i64 0), i8* noundef %283)
  br label %288

284:                                              ; preds = %1
  %285 = load %struct.Node*, %struct.Node** %2, align 8
  %286 = getelementptr inbounds %struct.Node, %struct.Node* %285, i32 0, i32 3
  %287 = load %struct.Token*, %struct.Token** %286, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %287, i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.103, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0)) #7
  unreachable

288:                                              ; preds = %280, %276, %272, %239, %235, %231, %230, %210, %200, %100, %95, %50
  ret void
}

; Function Attrs: nounwind readonly willreturn
declare i32 @strcmp(i8* noundef, i8* noundef) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @count() #0 {
  %1 = load i32, i32* @count.i, align 4
  %2 = add nsw i32 %1, 1
  store i32 %2, i32* @count.i, align 4
  ret i32 %1
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @gen_expr(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  %3 = alloca %union.anon, align 4
  %4 = alloca %union.anon.0, align 8
  %5 = alloca %union.anon.1, align 16
  %6 = alloca %struct.Member*, align 8
  %7 = alloca %struct.Member*, align 8
  %8 = alloca i64, align 8
  %9 = alloca %struct.Node*, align 8
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca %struct.Node*, align 8
  %17 = alloca %struct.Type*, align 8
  %18 = alloca i8, align 1
  %19 = alloca i8, align 1
  %20 = alloca i32, align 4
  %21 = alloca i32, align 4
  %22 = alloca i8*, align 8
  %23 = alloca i8*, align 8
  %24 = alloca i8*, align 8
  %25 = alloca i8*, align 8
  store %struct.Node* %0, %struct.Node** %2, align 8
  %26 = load %struct.Node*, %struct.Node** %2, align 8
  %27 = getelementptr inbounds %struct.Node, %struct.Node* %26, i32 0, i32 3
  %28 = load %struct.Token*, %struct.Token** %27, align 8
  %29 = getelementptr inbounds %struct.Token, %struct.Token* %28, i32 0, i32 8
  %30 = load %struct.File*, %struct.File** %29, align 16
  %31 = getelementptr inbounds %struct.File, %struct.File* %30, i32 0, i32 1
  %32 = load i32, i32* %31, align 8
  %33 = load %struct.Node*, %struct.Node** %2, align 8
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 3
  %35 = load %struct.Token*, %struct.Token** %34, align 8
  %36 = getelementptr inbounds %struct.Token, %struct.Token* %35, i32 0, i32 10
  %37 = load i32, i32* %36, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.86, i64 0, i64 0), i32 noundef %32, i32 noundef %37)
  %38 = load %struct.Node*, %struct.Node** %2, align 8
  %39 = getelementptr inbounds %struct.Node, %struct.Node* %38, i32 0, i32 0
  %40 = load i32, i32* %39, align 16
  switch i32 %40, label %611 [
    i32 0, label %41
    i32 42, label %42
    i32 5, label %89
    i32 40, label %102
    i32 19, label %107
    i32 21, label %146
    i32 20, label %153
    i32 16, label %157
    i32 39, label %230
    i32 18, label %244
    i32 43, label %251
    i32 44, label %263
    i32 17, label %276
    i32 22, label %296
    i32 23, label %305
    i32 24, label %309
    i32 25, label %332
    i32 37, label %355
    i32 36, label %559
    i32 46, label %563
    i32 47, label %593
  ]

41:                                               ; preds = %1
  br label %864

42:                                               ; preds = %1
  %43 = load %struct.Node*, %struct.Node** %2, align 8
  %44 = getelementptr inbounds %struct.Node, %struct.Node* %43, i32 0, i32 2
  %45 = load %struct.Type*, %struct.Type** %44, align 16
  %46 = getelementptr inbounds %struct.Type, %struct.Type* %45, i32 0, i32 0
  %47 = load i32, i32* %46, align 8
  switch i32 %47, label %85 [
    i32 6, label %48
    i32 7, label %59
    i32 8, label %70
  ]

48:                                               ; preds = %42
  %49 = bitcast %union.anon* %3 to float*
  %50 = load %struct.Node*, %struct.Node** %2, align 8
  %51 = getelementptr inbounds %struct.Node, %struct.Node* %50, i32 0, i32 35
  %52 = load x86_fp80, x86_fp80* %51, align 16
  %53 = fptrunc x86_fp80 %52 to float
  store float %53, float* %49, align 4
  %54 = bitcast %union.anon* %3 to i32*
  %55 = load i32, i32* %54, align 4
  %56 = load %struct.Node*, %struct.Node** %2, align 8
  %57 = getelementptr inbounds %struct.Node, %struct.Node* %56, i32 0, i32 35
  %58 = load x86_fp80, x86_fp80* %57, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([30 x i8], [30 x i8]* @.str.104, i64 0, i64 0), i32 noundef %55, x86_fp80 noundef %58)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.105, i64 0, i64 0))
  br label %864

59:                                               ; preds = %42
  %60 = bitcast %union.anon.0* %4 to double*
  %61 = load %struct.Node*, %struct.Node** %2, align 8
  %62 = getelementptr inbounds %struct.Node, %struct.Node* %61, i32 0, i32 35
  %63 = load x86_fp80, x86_fp80* %62, align 16
  %64 = fptrunc x86_fp80 %63 to double
  store double %64, double* %60, align 8
  %65 = bitcast %union.anon.0* %4 to i64*
  %66 = load i64, i64* %65, align 8
  %67 = load %struct.Node*, %struct.Node** %2, align 8
  %68 = getelementptr inbounds %struct.Node, %struct.Node* %67, i32 0, i32 35
  %69 = load x86_fp80, x86_fp80* %68, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @.str.106, i64 0, i64 0), i64 noundef %66, x86_fp80 noundef %69)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.105, i64 0, i64 0))
  br label %864

70:                                               ; preds = %42
  %71 = bitcast %union.anon.1* %5 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %71, i8 0, i64 16, i1 false)
  %72 = load %struct.Node*, %struct.Node** %2, align 8
  %73 = getelementptr inbounds %struct.Node, %struct.Node* %72, i32 0, i32 35
  %74 = load x86_fp80, x86_fp80* %73, align 16
  %75 = bitcast %union.anon.1* %5 to x86_fp80*
  store x86_fp80 %74, x86_fp80* %75, align 16
  %76 = bitcast %union.anon.1* %5 to [2 x i64]*
  %77 = getelementptr inbounds [2 x i64], [2 x i64]* %76, i64 0, i64 0
  %78 = load i64, i64* %77, align 16
  %79 = load %struct.Node*, %struct.Node** %2, align 8
  %80 = getelementptr inbounds %struct.Node, %struct.Node* %79, i32 0, i32 35
  %81 = load x86_fp80, x86_fp80* %80, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([37 x i8], [37 x i8]* @.str.107, i64 0, i64 0), i64 noundef %78, x86_fp80 noundef %81)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.108, i64 0, i64 0))
  %82 = bitcast %union.anon.1* %5 to [2 x i64]*
  %83 = getelementptr inbounds [2 x i64], [2 x i64]* %82, i64 0, i64 1
  %84 = load i64, i64* %83, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.109, i64 0, i64 0), i64 noundef %84)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.110, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.111, i64 0, i64 0))
  br label %864

85:                                               ; preds = %42
  %86 = load %struct.Node*, %struct.Node** %2, align 8
  %87 = getelementptr inbounds %struct.Node, %struct.Node* %86, i32 0, i32 34
  %88 = load i64, i64* %87, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.112, i64 0, i64 0), i64 noundef %88)
  br label %864

89:                                               ; preds = %1
  %90 = load %struct.Node*, %struct.Node** %2, align 8
  %91 = getelementptr inbounds %struct.Node, %struct.Node* %90, i32 0, i32 4
  %92 = load %struct.Node*, %struct.Node** %91, align 16
  call void @gen_expr(%struct.Node* noundef %92)
  %93 = load %struct.Node*, %struct.Node** %2, align 8
  %94 = getelementptr inbounds %struct.Node, %struct.Node* %93, i32 0, i32 2
  %95 = load %struct.Type*, %struct.Type** %94, align 16
  %96 = getelementptr inbounds %struct.Type, %struct.Type* %95, i32 0, i32 0
  %97 = load i32, i32* %96, align 8
  switch i32 %97, label %101 [
    i32 6, label %98
    i32 7, label %99
    i32 8, label %100
  ]

98:                                               ; preds = %89
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.113, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.114, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.115, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.116, i64 0, i64 0))
  br label %864

99:                                               ; preds = %89
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.113, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.117, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.115, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.118, i64 0, i64 0))
  br label %864

100:                                              ; preds = %89
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.119, i64 0, i64 0))
  br label %864

101:                                              ; preds = %89
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.120, i64 0, i64 0))
  br label %864

102:                                              ; preds = %1
  %103 = load %struct.Node*, %struct.Node** %2, align 8
  call void @gen_addr(%struct.Node* noundef %103)
  %104 = load %struct.Node*, %struct.Node** %2, align 8
  %105 = getelementptr inbounds %struct.Node, %struct.Node* %104, i32 0, i32 2
  %106 = load %struct.Type*, %struct.Type** %105, align 16
  call void @load(%struct.Type* noundef %106)
  br label %864

107:                                              ; preds = %1
  %108 = load %struct.Node*, %struct.Node** %2, align 8
  call void @gen_addr(%struct.Node* noundef %108)
  %109 = load %struct.Node*, %struct.Node** %2, align 8
  %110 = getelementptr inbounds %struct.Node, %struct.Node* %109, i32 0, i32 2
  %111 = load %struct.Type*, %struct.Type** %110, align 16
  call void @load(%struct.Type* noundef %111)
  %112 = load %struct.Node*, %struct.Node** %2, align 8
  %113 = getelementptr inbounds %struct.Node, %struct.Node* %112, i32 0, i32 14
  %114 = load %struct.Member*, %struct.Member** %113, align 16
  store %struct.Member* %114, %struct.Member** %6, align 8
  %115 = load %struct.Member*, %struct.Member** %6, align 8
  %116 = getelementptr inbounds %struct.Member, %struct.Member* %115, i32 0, i32 7
  %117 = load i8, i8* %116, align 4
  %118 = trunc i8 %117 to i1
  br i1 %118, label %119, label %145

119:                                              ; preds = %107
  %120 = load %struct.Member*, %struct.Member** %6, align 8
  %121 = getelementptr inbounds %struct.Member, %struct.Member* %120, i32 0, i32 9
  %122 = load i32, i32* %121, align 4
  %123 = sub nsw i32 64, %122
  %124 = load %struct.Member*, %struct.Member** %6, align 8
  %125 = getelementptr inbounds %struct.Member, %struct.Member* %124, i32 0, i32 8
  %126 = load i32, i32* %125, align 8
  %127 = sub nsw i32 %123, %126
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.121, i64 0, i64 0), i32 noundef %127)
  %128 = load %struct.Member*, %struct.Member** %6, align 8
  %129 = getelementptr inbounds %struct.Member, %struct.Member* %128, i32 0, i32 1
  %130 = load %struct.Type*, %struct.Type** %129, align 8
  %131 = getelementptr inbounds %struct.Type, %struct.Type* %130, i32 0, i32 3
  %132 = load i8, i8* %131, align 4
  %133 = trunc i8 %132 to i1
  br i1 %133, label %134, label %139

134:                                              ; preds = %119
  %135 = load %struct.Member*, %struct.Member** %6, align 8
  %136 = getelementptr inbounds %struct.Member, %struct.Member* %135, i32 0, i32 9
  %137 = load i32, i32* %136, align 4
  %138 = sub nsw i32 64, %137
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.122, i64 0, i64 0), i32 noundef %138)
  br label %144

139:                                              ; preds = %119
  %140 = load %struct.Member*, %struct.Member** %6, align 8
  %141 = getelementptr inbounds %struct.Member, %struct.Member* %140, i32 0, i32 9
  %142 = load i32, i32* %141, align 4
  %143 = sub nsw i32 64, %142
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.123, i64 0, i64 0), i32 noundef %143)
  br label %144

144:                                              ; preds = %139, %134
  br label %145

145:                                              ; preds = %144, %107
  br label %864

146:                                              ; preds = %1
  %147 = load %struct.Node*, %struct.Node** %2, align 8
  %148 = getelementptr inbounds %struct.Node, %struct.Node* %147, i32 0, i32 4
  %149 = load %struct.Node*, %struct.Node** %148, align 16
  call void @gen_expr(%struct.Node* noundef %149)
  %150 = load %struct.Node*, %struct.Node** %2, align 8
  %151 = getelementptr inbounds %struct.Node, %struct.Node* %150, i32 0, i32 2
  %152 = load %struct.Type*, %struct.Type** %151, align 16
  call void @load(%struct.Type* noundef %152)
  br label %864

153:                                              ; preds = %1
  %154 = load %struct.Node*, %struct.Node** %2, align 8
  %155 = getelementptr inbounds %struct.Node, %struct.Node* %154, i32 0, i32 4
  %156 = load %struct.Node*, %struct.Node** %155, align 16
  call void @gen_addr(%struct.Node* noundef %156)
  br label %864

157:                                              ; preds = %1
  %158 = load %struct.Node*, %struct.Node** %2, align 8
  %159 = getelementptr inbounds %struct.Node, %struct.Node* %158, i32 0, i32 4
  %160 = load %struct.Node*, %struct.Node** %159, align 16
  call void @gen_addr(%struct.Node* noundef %160)
  call void @push()
  %161 = load %struct.Node*, %struct.Node** %2, align 8
  %162 = getelementptr inbounds %struct.Node, %struct.Node* %161, i32 0, i32 5
  %163 = load %struct.Node*, %struct.Node** %162, align 8
  call void @gen_expr(%struct.Node* noundef %163)
  %164 = load %struct.Node*, %struct.Node** %2, align 8
  %165 = getelementptr inbounds %struct.Node, %struct.Node* %164, i32 0, i32 4
  %166 = load %struct.Node*, %struct.Node** %165, align 16
  %167 = getelementptr inbounds %struct.Node, %struct.Node* %166, i32 0, i32 0
  %168 = load i32, i32* %167, align 16
  %169 = icmp eq i32 %168, 19
  br i1 %169, label %170, label %226

170:                                              ; preds = %157
  %171 = load %struct.Node*, %struct.Node** %2, align 8
  %172 = getelementptr inbounds %struct.Node, %struct.Node* %171, i32 0, i32 4
  %173 = load %struct.Node*, %struct.Node** %172, align 16
  %174 = getelementptr inbounds %struct.Node, %struct.Node* %173, i32 0, i32 14
  %175 = load %struct.Member*, %struct.Member** %174, align 16
  %176 = getelementptr inbounds %struct.Member, %struct.Member* %175, i32 0, i32 7
  %177 = load i8, i8* %176, align 4
  %178 = trunc i8 %177 to i1
  br i1 %178, label %179, label %226

179:                                              ; preds = %170
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.124, i64 0, i64 0))
  %180 = load %struct.Node*, %struct.Node** %2, align 8
  %181 = getelementptr inbounds %struct.Node, %struct.Node* %180, i32 0, i32 4
  %182 = load %struct.Node*, %struct.Node** %181, align 16
  %183 = getelementptr inbounds %struct.Node, %struct.Node* %182, i32 0, i32 14
  %184 = load %struct.Member*, %struct.Member** %183, align 16
  store %struct.Member* %184, %struct.Member** %7, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.125, i64 0, i64 0))
  %185 = load %struct.Member*, %struct.Member** %7, align 8
  %186 = getelementptr inbounds %struct.Member, %struct.Member* %185, i32 0, i32 9
  %187 = load i32, i32* %186, align 4
  %188 = icmp sge i32 %187, 32
  br i1 %188, label %189, label %196

189:                                              ; preds = %179
  %190 = load %struct.Member*, %struct.Member** %7, align 8
  %191 = getelementptr inbounds %struct.Member, %struct.Member* %190, i32 0, i32 9
  %192 = load i32, i32* %191, align 4
  %193 = zext i32 %192 to i64
  %194 = shl i64 1, %193
  %195 = sub nsw i64 %194, 1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.112, i64 0, i64 0), i64 noundef %195)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.126, i64 0, i64 0))
  br label %203

196:                                              ; preds = %179
  %197 = load %struct.Member*, %struct.Member** %7, align 8
  %198 = getelementptr inbounds %struct.Member, %struct.Member* %197, i32 0, i32 9
  %199 = load i32, i32* %198, align 4
  %200 = zext i32 %199 to i64
  %201 = shl i64 1, %200
  %202 = sub nsw i64 %201, 1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.127, i64 0, i64 0), i64 noundef %202)
  br label %203

203:                                              ; preds = %196, %189
  %204 = load %struct.Member*, %struct.Member** %7, align 8
  %205 = getelementptr inbounds %struct.Member, %struct.Member* %204, i32 0, i32 8
  %206 = load i32, i32* %205, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.128, i64 0, i64 0), i32 noundef %206)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.129, i64 0, i64 0))
  %207 = load %struct.Member*, %struct.Member** %7, align 8
  %208 = getelementptr inbounds %struct.Member, %struct.Member* %207, i32 0, i32 1
  %209 = load %struct.Type*, %struct.Type** %208, align 8
  call void @load(%struct.Type* noundef %209)
  %210 = load %struct.Member*, %struct.Member** %7, align 8
  %211 = getelementptr inbounds %struct.Member, %struct.Member* %210, i32 0, i32 9
  %212 = load i32, i32* %211, align 4
  %213 = zext i32 %212 to i64
  %214 = shl i64 1, %213
  %215 = sub nsw i64 %214, 1
  %216 = load %struct.Member*, %struct.Member** %7, align 8
  %217 = getelementptr inbounds %struct.Member, %struct.Member* %216, i32 0, i32 8
  %218 = load i32, i32* %217, align 8
  %219 = zext i32 %218 to i64
  %220 = shl i64 %215, %219
  store i64 %220, i64* %8, align 8
  %221 = load i64, i64* %8, align 8
  %222 = xor i64 %221, -1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.130, i64 0, i64 0), i64 noundef %222)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.131, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.132, i64 0, i64 0))
  %223 = load %struct.Node*, %struct.Node** %2, align 8
  %224 = getelementptr inbounds %struct.Node, %struct.Node* %223, i32 0, i32 2
  %225 = load %struct.Type*, %struct.Type** %224, align 16
  call void @store(%struct.Type* noundef %225)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.133, i64 0, i64 0))
  br label %864

226:                                              ; preds = %170, %157
  %227 = load %struct.Node*, %struct.Node** %2, align 8
  %228 = getelementptr inbounds %struct.Node, %struct.Node* %227, i32 0, i32 2
  %229 = load %struct.Type*, %struct.Type** %228, align 16
  call void @store(%struct.Type* noundef %229)
  br label %864

230:                                              ; preds = %1
  %231 = load %struct.Node*, %struct.Node** %2, align 8
  %232 = getelementptr inbounds %struct.Node, %struct.Node* %231, i32 0, i32 13
  %233 = load %struct.Node*, %struct.Node** %232, align 8
  store %struct.Node* %233, %struct.Node** %9, align 8
  br label %234

234:                                              ; preds = %239, %230
  %235 = load %struct.Node*, %struct.Node** %9, align 8
  %236 = icmp ne %struct.Node* %235, null
  br i1 %236, label %237, label %243

237:                                              ; preds = %234
  %238 = load %struct.Node*, %struct.Node** %9, align 8
  call void @gen_stmt(%struct.Node* noundef %238)
  br label %239

239:                                              ; preds = %237
  %240 = load %struct.Node*, %struct.Node** %9, align 8
  %241 = getelementptr inbounds %struct.Node, %struct.Node* %240, i32 0, i32 1
  %242 = load %struct.Node*, %struct.Node** %241, align 8
  store %struct.Node* %242, %struct.Node** %9, align 8
  br label %234, !llvm.loop !21

243:                                              ; preds = %234
  br label %864

244:                                              ; preds = %1
  %245 = load %struct.Node*, %struct.Node** %2, align 8
  %246 = getelementptr inbounds %struct.Node, %struct.Node* %245, i32 0, i32 4
  %247 = load %struct.Node*, %struct.Node** %246, align 16
  call void @gen_expr(%struct.Node* noundef %247)
  %248 = load %struct.Node*, %struct.Node** %2, align 8
  %249 = getelementptr inbounds %struct.Node, %struct.Node* %248, i32 0, i32 5
  %250 = load %struct.Node*, %struct.Node** %249, align 8
  call void @gen_expr(%struct.Node* noundef %250)
  br label %864

251:                                              ; preds = %1
  %252 = load %struct.Node*, %struct.Node** %2, align 8
  %253 = getelementptr inbounds %struct.Node, %struct.Node* %252, i32 0, i32 4
  %254 = load %struct.Node*, %struct.Node** %253, align 16
  call void @gen_expr(%struct.Node* noundef %254)
  %255 = load %struct.Node*, %struct.Node** %2, align 8
  %256 = getelementptr inbounds %struct.Node, %struct.Node* %255, i32 0, i32 4
  %257 = load %struct.Node*, %struct.Node** %256, align 16
  %258 = getelementptr inbounds %struct.Node, %struct.Node* %257, i32 0, i32 2
  %259 = load %struct.Type*, %struct.Type** %258, align 16
  %260 = load %struct.Node*, %struct.Node** %2, align 8
  %261 = getelementptr inbounds %struct.Node, %struct.Node* %260, i32 0, i32 2
  %262 = load %struct.Type*, %struct.Type** %261, align 16
  call void @cast(%struct.Type* noundef %259, %struct.Type* noundef %262)
  br label %864

263:                                              ; preds = %1
  %264 = load %struct.Node*, %struct.Node** %2, align 8
  %265 = getelementptr inbounds %struct.Node, %struct.Node* %264, i32 0, i32 33
  %266 = load %struct.Obj*, %struct.Obj** %265, align 8
  %267 = getelementptr inbounds %struct.Obj, %struct.Obj* %266, i32 0, i32 3
  %268 = load %struct.Type*, %struct.Type** %267, align 8
  %269 = getelementptr inbounds %struct.Type, %struct.Type* %268, i32 0, i32 1
  %270 = load i32, i32* %269, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.134, i64 0, i64 0), i32 noundef %270)
  %271 = load %struct.Node*, %struct.Node** %2, align 8
  %272 = getelementptr inbounds %struct.Node, %struct.Node* %271, i32 0, i32 33
  %273 = load %struct.Obj*, %struct.Obj** %272, align 8
  %274 = getelementptr inbounds %struct.Obj, %struct.Obj* %273, i32 0, i32 7
  %275 = load i32, i32* %274, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.135, i64 0, i64 0), i32 noundef %275)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.136, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.137, i64 0, i64 0))
  br label %864

276:                                              ; preds = %1
  %277 = call i32 @count()
  store i32 %277, i32* %10, align 4
  %278 = load %struct.Node*, %struct.Node** %2, align 8
  %279 = getelementptr inbounds %struct.Node, %struct.Node* %278, i32 0, i32 6
  %280 = load %struct.Node*, %struct.Node** %279, align 16
  call void @gen_expr(%struct.Node* noundef %280)
  %281 = load %struct.Node*, %struct.Node** %2, align 8
  %282 = getelementptr inbounds %struct.Node, %struct.Node* %281, i32 0, i32 6
  %283 = load %struct.Node*, %struct.Node** %282, align 16
  %284 = getelementptr inbounds %struct.Node, %struct.Node* %283, i32 0, i32 2
  %285 = load %struct.Type*, %struct.Type** %284, align 16
  call void @cmp_zero(%struct.Type* noundef %285)
  %286 = load i32, i32* %10, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.138, i64 0, i64 0), i32 noundef %286)
  %287 = load %struct.Node*, %struct.Node** %2, align 8
  %288 = getelementptr inbounds %struct.Node, %struct.Node* %287, i32 0, i32 7
  %289 = load %struct.Node*, %struct.Node** %288, align 8
  call void @gen_expr(%struct.Node* noundef %289)
  %290 = load i32, i32* %10, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.88, i64 0, i64 0), i32 noundef %290)
  %291 = load i32, i32* %10, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.89, i64 0, i64 0), i32 noundef %291)
  %292 = load %struct.Node*, %struct.Node** %2, align 8
  %293 = getelementptr inbounds %struct.Node, %struct.Node* %292, i32 0, i32 8
  %294 = load %struct.Node*, %struct.Node** %293, align 16
  call void @gen_expr(%struct.Node* noundef %294)
  %295 = load i32, i32* %10, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.90, i64 0, i64 0), i32 noundef %295)
  br label %864

296:                                              ; preds = %1
  %297 = load %struct.Node*, %struct.Node** %2, align 8
  %298 = getelementptr inbounds %struct.Node, %struct.Node* %297, i32 0, i32 4
  %299 = load %struct.Node*, %struct.Node** %298, align 16
  call void @gen_expr(%struct.Node* noundef %299)
  %300 = load %struct.Node*, %struct.Node** %2, align 8
  %301 = getelementptr inbounds %struct.Node, %struct.Node* %300, i32 0, i32 4
  %302 = load %struct.Node*, %struct.Node** %301, align 16
  %303 = getelementptr inbounds %struct.Node, %struct.Node* %302, i32 0, i32 2
  %304 = load %struct.Type*, %struct.Type** %303, align 16
  call void @cmp_zero(%struct.Type* noundef %304)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.139, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.140, i64 0, i64 0))
  br label %864

305:                                              ; preds = %1
  %306 = load %struct.Node*, %struct.Node** %2, align 8
  %307 = getelementptr inbounds %struct.Node, %struct.Node* %306, i32 0, i32 4
  %308 = load %struct.Node*, %struct.Node** %307, align 16
  call void @gen_expr(%struct.Node* noundef %308)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.141, i64 0, i64 0))
  br label %864

309:                                              ; preds = %1
  %310 = call i32 @count()
  store i32 %310, i32* %11, align 4
  %311 = load %struct.Node*, %struct.Node** %2, align 8
  %312 = getelementptr inbounds %struct.Node, %struct.Node* %311, i32 0, i32 4
  %313 = load %struct.Node*, %struct.Node** %312, align 16
  call void @gen_expr(%struct.Node* noundef %313)
  %314 = load %struct.Node*, %struct.Node** %2, align 8
  %315 = getelementptr inbounds %struct.Node, %struct.Node* %314, i32 0, i32 4
  %316 = load %struct.Node*, %struct.Node** %315, align 16
  %317 = getelementptr inbounds %struct.Node, %struct.Node* %316, i32 0, i32 2
  %318 = load %struct.Type*, %struct.Type** %317, align 16
  call void @cmp_zero(%struct.Type* noundef %318)
  %319 = load i32, i32* %11, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.142, i64 0, i64 0), i32 noundef %319)
  %320 = load %struct.Node*, %struct.Node** %2, align 8
  %321 = getelementptr inbounds %struct.Node, %struct.Node* %320, i32 0, i32 5
  %322 = load %struct.Node*, %struct.Node** %321, align 8
  call void @gen_expr(%struct.Node* noundef %322)
  %323 = load %struct.Node*, %struct.Node** %2, align 8
  %324 = getelementptr inbounds %struct.Node, %struct.Node* %323, i32 0, i32 5
  %325 = load %struct.Node*, %struct.Node** %324, align 8
  %326 = getelementptr inbounds %struct.Node, %struct.Node* %325, i32 0, i32 2
  %327 = load %struct.Type*, %struct.Type** %326, align 16
  call void @cmp_zero(%struct.Type* noundef %327)
  %328 = load i32, i32* %11, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.142, i64 0, i64 0), i32 noundef %328)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.113, i64 0, i64 0))
  %329 = load i32, i32* %11, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.88, i64 0, i64 0), i32 noundef %329)
  %330 = load i32, i32* %11, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.143, i64 0, i64 0), i32 noundef %330)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.61, i64 0, i64 0))
  %331 = load i32, i32* %11, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.90, i64 0, i64 0), i32 noundef %331)
  br label %864

332:                                              ; preds = %1
  %333 = call i32 @count()
  store i32 %333, i32* %12, align 4
  %334 = load %struct.Node*, %struct.Node** %2, align 8
  %335 = getelementptr inbounds %struct.Node, %struct.Node* %334, i32 0, i32 4
  %336 = load %struct.Node*, %struct.Node** %335, align 16
  call void @gen_expr(%struct.Node* noundef %336)
  %337 = load %struct.Node*, %struct.Node** %2, align 8
  %338 = getelementptr inbounds %struct.Node, %struct.Node* %337, i32 0, i32 4
  %339 = load %struct.Node*, %struct.Node** %338, align 16
  %340 = getelementptr inbounds %struct.Node, %struct.Node* %339, i32 0, i32 2
  %341 = load %struct.Type*, %struct.Type** %340, align 16
  call void @cmp_zero(%struct.Type* noundef %341)
  %342 = load i32, i32* %12, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.144, i64 0, i64 0), i32 noundef %342)
  %343 = load %struct.Node*, %struct.Node** %2, align 8
  %344 = getelementptr inbounds %struct.Node, %struct.Node* %343, i32 0, i32 5
  %345 = load %struct.Node*, %struct.Node** %344, align 8
  call void @gen_expr(%struct.Node* noundef %345)
  %346 = load %struct.Node*, %struct.Node** %2, align 8
  %347 = getelementptr inbounds %struct.Node, %struct.Node* %346, i32 0, i32 5
  %348 = load %struct.Node*, %struct.Node** %347, align 8
  %349 = getelementptr inbounds %struct.Node, %struct.Node* %348, i32 0, i32 2
  %350 = load %struct.Type*, %struct.Type** %349, align 16
  call void @cmp_zero(%struct.Type* noundef %350)
  %351 = load i32, i32* %12, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.144, i64 0, i64 0), i32 noundef %351)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.61, i64 0, i64 0))
  %352 = load i32, i32* %12, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.88, i64 0, i64 0), i32 noundef %352)
  %353 = load i32, i32* %12, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.145, i64 0, i64 0), i32 noundef %353)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.113, i64 0, i64 0))
  %354 = load i32, i32* %12, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([11 x i8], [11 x i8]* @.str.90, i64 0, i64 0), i32 noundef %354)
  br label %864

355:                                              ; preds = %1
  %356 = load %struct.Node*, %struct.Node** %2, align 8
  %357 = getelementptr inbounds %struct.Node, %struct.Node* %356, i32 0, i32 4
  %358 = load %struct.Node*, %struct.Node** %357, align 16
  %359 = getelementptr inbounds %struct.Node, %struct.Node* %358, i32 0, i32 0
  %360 = load i32, i32* %359, align 16
  %361 = icmp eq i32 %360, 40
  br i1 %361, label %362, label %376

362:                                              ; preds = %355
  %363 = load %struct.Node*, %struct.Node** %2, align 8
  %364 = getelementptr inbounds %struct.Node, %struct.Node* %363, i32 0, i32 4
  %365 = load %struct.Node*, %struct.Node** %364, align 16
  %366 = getelementptr inbounds %struct.Node, %struct.Node* %365, i32 0, i32 33
  %367 = load %struct.Obj*, %struct.Obj** %366, align 8
  %368 = getelementptr inbounds %struct.Obj, %struct.Obj* %367, i32 0, i32 1
  %369 = load i8*, i8** %368, align 8
  %370 = call i32 @strcmp(i8* noundef %369, i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.146, i64 0, i64 0)) #9
  %371 = icmp ne i32 %370, 0
  br i1 %371, label %376, label %372

372:                                              ; preds = %362
  %373 = load %struct.Node*, %struct.Node** %2, align 8
  %374 = getelementptr inbounds %struct.Node, %struct.Node* %373, i32 0, i32 16
  %375 = load %struct.Node*, %struct.Node** %374, align 16
  call void @gen_expr(%struct.Node* noundef %375)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.125, i64 0, i64 0))
  call void @builtin_alloca()
  br label %864

376:                                              ; preds = %362, %355
  %377 = load %struct.Node*, %struct.Node** %2, align 8
  %378 = call i32 @push_args(%struct.Node* noundef %377)
  store i32 %378, i32* %13, align 4
  %379 = load %struct.Node*, %struct.Node** %2, align 8
  %380 = getelementptr inbounds %struct.Node, %struct.Node* %379, i32 0, i32 4
  %381 = load %struct.Node*, %struct.Node** %380, align 16
  call void @gen_expr(%struct.Node* noundef %381)
  store i32 0, i32* %14, align 4
  store i32 0, i32* %15, align 4
  %382 = load %struct.Node*, %struct.Node** %2, align 8
  %383 = getelementptr inbounds %struct.Node, %struct.Node* %382, i32 0, i32 18
  %384 = load %struct.Obj*, %struct.Obj** %383, align 16
  %385 = icmp ne %struct.Obj* %384, null
  br i1 %385, label %386, label %399

386:                                              ; preds = %376
  %387 = load %struct.Node*, %struct.Node** %2, align 8
  %388 = getelementptr inbounds %struct.Node, %struct.Node* %387, i32 0, i32 2
  %389 = load %struct.Type*, %struct.Type** %388, align 16
  %390 = getelementptr inbounds %struct.Type, %struct.Type* %389, i32 0, i32 1
  %391 = load i32, i32* %390, align 4
  %392 = icmp sgt i32 %391, 16
  br i1 %392, label %393, label %399

393:                                              ; preds = %386
  %394 = load i32, i32* %14, align 4
  %395 = add nsw i32 %394, 1
  store i32 %395, i32* %14, align 4
  %396 = sext i32 %394 to i64
  %397 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg64, i64 0, i64 %396
  %398 = load i8*, i8** %397, align 8
  call void @pop(i8* noundef %398)
  br label %399

399:                                              ; preds = %393, %386, %376
  %400 = load %struct.Node*, %struct.Node** %2, align 8
  %401 = getelementptr inbounds %struct.Node, %struct.Node* %400, i32 0, i32 16
  %402 = load %struct.Node*, %struct.Node** %401, align 16
  store %struct.Node* %402, %struct.Node** %16, align 8
  br label %403

403:                                              ; preds = %500, %399
  %404 = load %struct.Node*, %struct.Node** %16, align 8
  %405 = icmp ne %struct.Node* %404, null
  br i1 %405, label %406, label %504

406:                                              ; preds = %403
  %407 = load %struct.Node*, %struct.Node** %16, align 8
  %408 = getelementptr inbounds %struct.Node, %struct.Node* %407, i32 0, i32 2
  %409 = load %struct.Type*, %struct.Type** %408, align 16
  store %struct.Type* %409, %struct.Type** %17, align 8
  %410 = load %struct.Type*, %struct.Type** %17, align 8
  %411 = getelementptr inbounds %struct.Type, %struct.Type* %410, i32 0, i32 0
  %412 = load i32, i32* %411, align 8
  switch i32 %412, label %489 [
    i32 14, label %413
    i32 15, label %413
    i32 6, label %481
    i32 7, label %481
    i32 8, label %488
  ]

413:                                              ; preds = %406, %406
  %414 = load %struct.Type*, %struct.Type** %17, align 8
  %415 = getelementptr inbounds %struct.Type, %struct.Type* %414, i32 0, i32 1
  %416 = load i32, i32* %415, align 4
  %417 = icmp sgt i32 %416, 16
  br i1 %417, label %418, label %419

418:                                              ; preds = %413
  br label %500

419:                                              ; preds = %413
  %420 = load %struct.Type*, %struct.Type** %17, align 8
  %421 = call zeroext i1 @has_flonum1(%struct.Type* noundef %420)
  %422 = zext i1 %421 to i8
  store i8 %422, i8* %18, align 1
  %423 = load %struct.Type*, %struct.Type** %17, align 8
  %424 = call zeroext i1 @has_flonum2(%struct.Type* noundef %423)
  %425 = zext i1 %424 to i8
  store i8 %425, i8* %19, align 1
  %426 = load i32, i32* %15, align 4
  %427 = load i8, i8* %18, align 1
  %428 = trunc i8 %427 to i1
  %429 = zext i1 %428 to i32
  %430 = add nsw i32 %426, %429
  %431 = load i8, i8* %19, align 1
  %432 = trunc i8 %431 to i1
  %433 = zext i1 %432 to i32
  %434 = add nsw i32 %430, %433
  %435 = icmp slt i32 %434, 8
  br i1 %435, label %436, label %480

436:                                              ; preds = %419
  %437 = load i32, i32* %14, align 4
  %438 = load i8, i8* %18, align 1
  %439 = trunc i8 %438 to i1
  %440 = xor i1 %439, true
  %441 = zext i1 %440 to i32
  %442 = add nsw i32 %437, %441
  %443 = load i8, i8* %19, align 1
  %444 = trunc i8 %443 to i1
  %445 = xor i1 %444, true
  %446 = zext i1 %445 to i32
  %447 = add nsw i32 %442, %446
  %448 = icmp slt i32 %447, 6
  br i1 %448, label %449, label %480

449:                                              ; preds = %436
  %450 = load i8, i8* %18, align 1
  %451 = trunc i8 %450 to i1
  br i1 %451, label %452, label %455

452:                                              ; preds = %449
  %453 = load i32, i32* %15, align 4
  %454 = add nsw i32 %453, 1
  store i32 %454, i32* %15, align 4
  call void @popf(i32 noundef %453)
  br label %461

455:                                              ; preds = %449
  %456 = load i32, i32* %14, align 4
  %457 = add nsw i32 %456, 1
  store i32 %457, i32* %14, align 4
  %458 = sext i32 %456 to i64
  %459 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg64, i64 0, i64 %458
  %460 = load i8*, i8** %459, align 8
  call void @pop(i8* noundef %460)
  br label %461

461:                                              ; preds = %455, %452
  %462 = load %struct.Type*, %struct.Type** %17, align 8
  %463 = getelementptr inbounds %struct.Type, %struct.Type* %462, i32 0, i32 1
  %464 = load i32, i32* %463, align 4
  %465 = icmp sgt i32 %464, 8
  br i1 %465, label %466, label %479

466:                                              ; preds = %461
  %467 = load i8, i8* %19, align 1
  %468 = trunc i8 %467 to i1
  br i1 %468, label %469, label %472

469:                                              ; preds = %466
  %470 = load i32, i32* %15, align 4
  %471 = add nsw i32 %470, 1
  store i32 %471, i32* %15, align 4
  call void @popf(i32 noundef %470)
  br label %478

472:                                              ; preds = %466
  %473 = load i32, i32* %14, align 4
  %474 = add nsw i32 %473, 1
  store i32 %474, i32* %14, align 4
  %475 = sext i32 %473 to i64
  %476 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg64, i64 0, i64 %475
  %477 = load i8*, i8** %476, align 8
  call void @pop(i8* noundef %477)
  br label %478

478:                                              ; preds = %472, %469
  br label %479

479:                                              ; preds = %478, %461
  br label %480

480:                                              ; preds = %479, %436, %419
  br label %499

481:                                              ; preds = %406, %406
  %482 = load i32, i32* %15, align 4
  %483 = icmp slt i32 %482, 8
  br i1 %483, label %484, label %487

484:                                              ; preds = %481
  %485 = load i32, i32* %15, align 4
  %486 = add nsw i32 %485, 1
  store i32 %486, i32* %15, align 4
  call void @popf(i32 noundef %485)
  br label %487

487:                                              ; preds = %484, %481
  br label %499

488:                                              ; preds = %406
  br label %499

489:                                              ; preds = %406
  %490 = load i32, i32* %14, align 4
  %491 = icmp slt i32 %490, 6
  br i1 %491, label %492, label %498

492:                                              ; preds = %489
  %493 = load i32, i32* %14, align 4
  %494 = add nsw i32 %493, 1
  store i32 %494, i32* %14, align 4
  %495 = sext i32 %493 to i64
  %496 = getelementptr inbounds [6 x i8*], [6 x i8*]* @argreg64, i64 0, i64 %495
  %497 = load i8*, i8** %496, align 8
  call void @pop(i8* noundef %497)
  br label %498

498:                                              ; preds = %492, %489
  br label %499

499:                                              ; preds = %498, %488, %487, %480
  br label %500

500:                                              ; preds = %499, %418
  %501 = load %struct.Node*, %struct.Node** %16, align 8
  %502 = getelementptr inbounds %struct.Node, %struct.Node* %501, i32 0, i32 1
  %503 = load %struct.Node*, %struct.Node** %502, align 8
  store %struct.Node* %503, %struct.Node** %16, align 8
  br label %403, !llvm.loop !22

504:                                              ; preds = %403
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.147, i64 0, i64 0))
  %505 = load i32, i32* %15, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.148, i64 0, i64 0), i32 noundef %505)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.149, i64 0, i64 0))
  %506 = load i32, i32* %13, align 4
  %507 = mul nsw i32 %506, 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.150, i64 0, i64 0), i32 noundef %507)
  %508 = load i32, i32* %13, align 4
  %509 = load i32, i32* @depth, align 4
  %510 = sub nsw i32 %509, %508
  store i32 %510, i32* @depth, align 4
  %511 = load %struct.Node*, %struct.Node** %2, align 8
  %512 = getelementptr inbounds %struct.Node, %struct.Node* %511, i32 0, i32 2
  %513 = load %struct.Type*, %struct.Type** %512, align 16
  %514 = getelementptr inbounds %struct.Type, %struct.Type* %513, i32 0, i32 0
  %515 = load i32, i32* %514, align 8
  switch i32 %515, label %537 [
    i32 1, label %516
    i32 2, label %517
    i32 3, label %527
  ]

516:                                              ; preds = %504
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.151, i64 0, i64 0))
  br label %864

517:                                              ; preds = %504
  %518 = load %struct.Node*, %struct.Node** %2, align 8
  %519 = getelementptr inbounds %struct.Node, %struct.Node* %518, i32 0, i32 2
  %520 = load %struct.Type*, %struct.Type** %519, align 16
  %521 = getelementptr inbounds %struct.Type, %struct.Type* %520, i32 0, i32 3
  %522 = load i8, i8* %521, align 4
  %523 = trunc i8 %522 to i1
  br i1 %523, label %524, label %525

524:                                              ; preds = %517
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.152, i64 0, i64 0))
  br label %526

525:                                              ; preds = %517
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.153, i64 0, i64 0))
  br label %526

526:                                              ; preds = %525, %524
  br label %864

527:                                              ; preds = %504
  %528 = load %struct.Node*, %struct.Node** %2, align 8
  %529 = getelementptr inbounds %struct.Node, %struct.Node* %528, i32 0, i32 2
  %530 = load %struct.Type*, %struct.Type** %529, align 16
  %531 = getelementptr inbounds %struct.Type, %struct.Type* %530, i32 0, i32 3
  %532 = load i8, i8* %531, align 4
  %533 = trunc i8 %532 to i1
  br i1 %533, label %534, label %535

534:                                              ; preds = %527
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.154, i64 0, i64 0))
  br label %536

535:                                              ; preds = %527
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.155, i64 0, i64 0))
  br label %536

536:                                              ; preds = %535, %534
  br label %864

537:                                              ; preds = %504
  %538 = load %struct.Node*, %struct.Node** %2, align 8
  %539 = getelementptr inbounds %struct.Node, %struct.Node* %538, i32 0, i32 18
  %540 = load %struct.Obj*, %struct.Obj** %539, align 16
  %541 = icmp ne %struct.Obj* %540, null
  br i1 %541, label %542, label %558

542:                                              ; preds = %537
  %543 = load %struct.Node*, %struct.Node** %2, align 8
  %544 = getelementptr inbounds %struct.Node, %struct.Node* %543, i32 0, i32 2
  %545 = load %struct.Type*, %struct.Type** %544, align 16
  %546 = getelementptr inbounds %struct.Type, %struct.Type* %545, i32 0, i32 1
  %547 = load i32, i32* %546, align 4
  %548 = icmp sle i32 %547, 16
  br i1 %548, label %549, label %558

549:                                              ; preds = %542
  %550 = load %struct.Node*, %struct.Node** %2, align 8
  %551 = getelementptr inbounds %struct.Node, %struct.Node* %550, i32 0, i32 18
  %552 = load %struct.Obj*, %struct.Obj** %551, align 16
  call void @copy_ret_buffer(%struct.Obj* noundef %552)
  %553 = load %struct.Node*, %struct.Node** %2, align 8
  %554 = getelementptr inbounds %struct.Node, %struct.Node* %553, i32 0, i32 18
  %555 = load %struct.Obj*, %struct.Obj** %554, align 16
  %556 = getelementptr inbounds %struct.Obj, %struct.Obj* %555, i32 0, i32 7
  %557 = load i32, i32* %556, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.156, i64 0, i64 0), i32 noundef %557)
  br label %558

558:                                              ; preds = %549, %542, %537
  br label %864

559:                                              ; preds = %1
  %560 = load %struct.Node*, %struct.Node** %2, align 8
  %561 = getelementptr inbounds %struct.Node, %struct.Node* %560, i32 0, i32 20
  %562 = load i8*, i8** %561, align 16
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.157, i64 0, i64 0), i8* noundef %562)
  br label %864

563:                                              ; preds = %1
  %564 = load %struct.Node*, %struct.Node** %2, align 8
  %565 = getelementptr inbounds %struct.Node, %struct.Node* %564, i32 0, i32 27
  %566 = load %struct.Node*, %struct.Node** %565, align 8
  call void @gen_expr(%struct.Node* noundef %566)
  call void @push()
  %567 = load %struct.Node*, %struct.Node** %2, align 8
  %568 = getelementptr inbounds %struct.Node, %struct.Node* %567, i32 0, i32 29
  %569 = load %struct.Node*, %struct.Node** %568, align 8
  call void @gen_expr(%struct.Node* noundef %569)
  call void @push()
  %570 = load %struct.Node*, %struct.Node** %2, align 8
  %571 = getelementptr inbounds %struct.Node, %struct.Node* %570, i32 0, i32 28
  %572 = load %struct.Node*, %struct.Node** %571, align 16
  call void @gen_expr(%struct.Node* noundef %572)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([18 x i8], [18 x i8]* @.str.124, i64 0, i64 0))
  %573 = load %struct.Node*, %struct.Node** %2, align 8
  %574 = getelementptr inbounds %struct.Node, %struct.Node* %573, i32 0, i32 28
  %575 = load %struct.Node*, %struct.Node** %574, align 16
  %576 = getelementptr inbounds %struct.Node, %struct.Node* %575, i32 0, i32 2
  %577 = load %struct.Type*, %struct.Type** %576, align 16
  %578 = getelementptr inbounds %struct.Type, %struct.Type* %577, i32 0, i32 8
  %579 = load %struct.Type*, %struct.Type** %578, align 8
  call void @load(%struct.Type* noundef %579)
  call void @pop(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0))
  call void @pop(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i64 0, i64 0))
  %580 = load %struct.Node*, %struct.Node** %2, align 8
  %581 = getelementptr inbounds %struct.Node, %struct.Node* %580, i32 0, i32 27
  %582 = load %struct.Node*, %struct.Node** %581, align 8
  %583 = getelementptr inbounds %struct.Node, %struct.Node* %582, i32 0, i32 2
  %584 = load %struct.Type*, %struct.Type** %583, align 16
  %585 = getelementptr inbounds %struct.Type, %struct.Type* %584, i32 0, i32 8
  %586 = load %struct.Type*, %struct.Type** %585, align 8
  %587 = getelementptr inbounds %struct.Type, %struct.Type* %586, i32 0, i32 1
  %588 = load i32, i32* %587, align 4
  store i32 %588, i32* %20, align 4
  %589 = load i32, i32* %20, align 4
  %590 = call i8* @reg_dx(i32 noundef %589)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @.str.158, i64 0, i64 0), i8* noundef %590)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.159, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.160, i64 0, i64 0))
  %591 = load i32, i32* %20, align 4
  %592 = call i8* @reg_ax(i32 noundef %591)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.161, i64 0, i64 0), i8* noundef %592)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.162, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.163, i64 0, i64 0))
  br label %864

593:                                              ; preds = %1
  %594 = load %struct.Node*, %struct.Node** %2, align 8
  %595 = getelementptr inbounds %struct.Node, %struct.Node* %594, i32 0, i32 4
  %596 = load %struct.Node*, %struct.Node** %595, align 16
  call void @gen_expr(%struct.Node* noundef %596)
  call void @push()
  %597 = load %struct.Node*, %struct.Node** %2, align 8
  %598 = getelementptr inbounds %struct.Node, %struct.Node* %597, i32 0, i32 5
  %599 = load %struct.Node*, %struct.Node** %598, align 8
  call void @gen_expr(%struct.Node* noundef %599)
  call void @pop(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i64 0, i64 0))
  %600 = load %struct.Node*, %struct.Node** %2, align 8
  %601 = getelementptr inbounds %struct.Node, %struct.Node* %600, i32 0, i32 4
  %602 = load %struct.Node*, %struct.Node** %601, align 16
  %603 = getelementptr inbounds %struct.Node, %struct.Node* %602, i32 0, i32 2
  %604 = load %struct.Type*, %struct.Type** %603, align 16
  %605 = getelementptr inbounds %struct.Type, %struct.Type* %604, i32 0, i32 8
  %606 = load %struct.Type*, %struct.Type** %605, align 8
  %607 = getelementptr inbounds %struct.Type, %struct.Type* %606, i32 0, i32 1
  %608 = load i32, i32* %607, align 4
  store i32 %608, i32* %21, align 4
  %609 = load i32, i32* %21, align 4
  %610 = call i8* @reg_ax(i32 noundef %609)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.164, i64 0, i64 0), i8* noundef %610)
  br label %864

611:                                              ; preds = %1
  %612 = load %struct.Node*, %struct.Node** %2, align 8
  %613 = getelementptr inbounds %struct.Node, %struct.Node* %612, i32 0, i32 4
  %614 = load %struct.Node*, %struct.Node** %613, align 16
  %615 = getelementptr inbounds %struct.Node, %struct.Node* %614, i32 0, i32 2
  %616 = load %struct.Type*, %struct.Type** %615, align 16
  %617 = getelementptr inbounds %struct.Type, %struct.Type* %616, i32 0, i32 0
  %618 = load i32, i32* %617, align 8
  switch i32 %618, label %714 [
    i32 6, label %619
    i32 7, label %619
    i32 8, label %674
  ]

619:                                              ; preds = %611, %611
  %620 = load %struct.Node*, %struct.Node** %2, align 8
  %621 = getelementptr inbounds %struct.Node, %struct.Node* %620, i32 0, i32 5
  %622 = load %struct.Node*, %struct.Node** %621, align 8
  call void @gen_expr(%struct.Node* noundef %622)
  call void @pushf()
  %623 = load %struct.Node*, %struct.Node** %2, align 8
  %624 = getelementptr inbounds %struct.Node, %struct.Node* %623, i32 0, i32 4
  %625 = load %struct.Node*, %struct.Node** %624, align 16
  call void @gen_expr(%struct.Node* noundef %625)
  call void @popf(i32 noundef 1)
  %626 = load %struct.Node*, %struct.Node** %2, align 8
  %627 = getelementptr inbounds %struct.Node, %struct.Node* %626, i32 0, i32 4
  %628 = load %struct.Node*, %struct.Node** %627, align 16
  %629 = getelementptr inbounds %struct.Node, %struct.Node* %628, i32 0, i32 2
  %630 = load %struct.Type*, %struct.Type** %629, align 16
  %631 = getelementptr inbounds %struct.Type, %struct.Type* %630, i32 0, i32 0
  %632 = load i32, i32* %631, align 8
  %633 = icmp eq i32 %632, 6
  %634 = zext i1 %633 to i64
  %635 = select i1 %633, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.165, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.166, i64 0, i64 0)
  store i8* %635, i8** %22, align 8
  %636 = load %struct.Node*, %struct.Node** %2, align 8
  %637 = getelementptr inbounds %struct.Node, %struct.Node* %636, i32 0, i32 0
  %638 = load i32, i32* %637, align 16
  switch i32 %638, label %670 [
    i32 1, label %639
    i32 2, label %641
    i32 3, label %643
    i32 4, label %645
    i32 12, label %647
    i32 13, label %647
    i32 14, label %647
    i32 15, label %647
  ]

639:                                              ; preds = %619
  %640 = load i8*, i8** %22, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.167, i64 0, i64 0), i8* noundef %640)
  br label %864

641:                                              ; preds = %619
  %642 = load i8*, i8** %22, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.168, i64 0, i64 0), i8* noundef %642)
  br label %864

643:                                              ; preds = %619
  %644 = load i8*, i8** %22, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.169, i64 0, i64 0), i8* noundef %644)
  br label %864

645:                                              ; preds = %619
  %646 = load i8*, i8** %22, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.170, i64 0, i64 0), i8* noundef %646)
  br label %864

647:                                              ; preds = %619, %619, %619, %619
  %648 = load i8*, i8** %22, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.171, i64 0, i64 0), i8* noundef %648)
  %649 = load %struct.Node*, %struct.Node** %2, align 8
  %650 = getelementptr inbounds %struct.Node, %struct.Node* %649, i32 0, i32 0
  %651 = load i32, i32* %650, align 16
  %652 = icmp eq i32 %651, 12
  br i1 %652, label %653, label %654

653:                                              ; preds = %647
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.139, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.172, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.173, i64 0, i64 0))
  br label %669

654:                                              ; preds = %647
  %655 = load %struct.Node*, %struct.Node** %2, align 8
  %656 = getelementptr inbounds %struct.Node, %struct.Node* %655, i32 0, i32 0
  %657 = load i32, i32* %656, align 16
  %658 = icmp eq i32 %657, 13
  br i1 %658, label %659, label %660

659:                                              ; preds = %654
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.174, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.175, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.176, i64 0, i64 0))
  br label %668

660:                                              ; preds = %654
  %661 = load %struct.Node*, %struct.Node** %2, align 8
  %662 = getelementptr inbounds %struct.Node, %struct.Node* %661, i32 0, i32 0
  %663 = load i32, i32* %662, align 16
  %664 = icmp eq i32 %663, 14
  br i1 %664, label %665, label %666

665:                                              ; preds = %660
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.177, i64 0, i64 0))
  br label %667

666:                                              ; preds = %660
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.178, i64 0, i64 0))
  br label %667

667:                                              ; preds = %666, %665
  br label %668

668:                                              ; preds = %667, %659
  br label %669

669:                                              ; preds = %668, %653
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.179, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.180, i64 0, i64 0))
  br label %864

670:                                              ; preds = %619
  %671 = load %struct.Node*, %struct.Node** %2, align 8
  %672 = getelementptr inbounds %struct.Node, %struct.Node* %671, i32 0, i32 3
  %673 = load %struct.Token*, %struct.Token** %672, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %673, i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.181, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0)) #7
  unreachable

674:                                              ; preds = %611
  %675 = load %struct.Node*, %struct.Node** %2, align 8
  %676 = getelementptr inbounds %struct.Node, %struct.Node* %675, i32 0, i32 4
  %677 = load %struct.Node*, %struct.Node** %676, align 16
  call void @gen_expr(%struct.Node* noundef %677)
  %678 = load %struct.Node*, %struct.Node** %2, align 8
  %679 = getelementptr inbounds %struct.Node, %struct.Node* %678, i32 0, i32 5
  %680 = load %struct.Node*, %struct.Node** %679, align 8
  call void @gen_expr(%struct.Node* noundef %680)
  %681 = load %struct.Node*, %struct.Node** %2, align 8
  %682 = getelementptr inbounds %struct.Node, %struct.Node* %681, i32 0, i32 0
  %683 = load i32, i32* %682, align 16
  switch i32 %683, label %710 [
    i32 1, label %684
    i32 2, label %685
    i32 3, label %686
    i32 4, label %687
    i32 12, label %688
    i32 13, label %688
    i32 14, label %688
    i32 15, label %688
  ]

684:                                              ; preds = %674
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.182, i64 0, i64 0))
  br label %864

685:                                              ; preds = %674
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.183, i64 0, i64 0))
  br label %864

686:                                              ; preds = %674
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.184, i64 0, i64 0))
  br label %864

687:                                              ; preds = %674
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.185, i64 0, i64 0))
  br label %864

688:                                              ; preds = %674, %674, %674, %674
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.186, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.187, i64 0, i64 0))
  %689 = load %struct.Node*, %struct.Node** %2, align 8
  %690 = getelementptr inbounds %struct.Node, %struct.Node* %689, i32 0, i32 0
  %691 = load i32, i32* %690, align 16
  %692 = icmp eq i32 %691, 12
  br i1 %692, label %693, label %694

693:                                              ; preds = %688
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.139, i64 0, i64 0))
  br label %709

694:                                              ; preds = %688
  %695 = load %struct.Node*, %struct.Node** %2, align 8
  %696 = getelementptr inbounds %struct.Node, %struct.Node* %695, i32 0, i32 0
  %697 = load i32, i32* %696, align 16
  %698 = icmp eq i32 %697, 13
  br i1 %698, label %699, label %700

699:                                              ; preds = %694
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.174, i64 0, i64 0))
  br label %708

700:                                              ; preds = %694
  %701 = load %struct.Node*, %struct.Node** %2, align 8
  %702 = getelementptr inbounds %struct.Node, %struct.Node* %701, i32 0, i32 0
  %703 = load i32, i32* %702, align 16
  %704 = icmp eq i32 %703, 14
  br i1 %704, label %705, label %706

705:                                              ; preds = %700
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.177, i64 0, i64 0))
  br label %707

706:                                              ; preds = %700
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.178, i64 0, i64 0))
  br label %707

707:                                              ; preds = %706, %705
  br label %708

708:                                              ; preds = %707, %699
  br label %709

709:                                              ; preds = %708, %693
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.180, i64 0, i64 0))
  br label %864

710:                                              ; preds = %674
  %711 = load %struct.Node*, %struct.Node** %2, align 8
  %712 = getelementptr inbounds %struct.Node, %struct.Node* %711, i32 0, i32 3
  %713 = load %struct.Token*, %struct.Token** %712, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %713, i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.181, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0)) #7
  unreachable

714:                                              ; preds = %611
  %715 = load %struct.Node*, %struct.Node** %2, align 8
  %716 = getelementptr inbounds %struct.Node, %struct.Node* %715, i32 0, i32 5
  %717 = load %struct.Node*, %struct.Node** %716, align 8
  call void @gen_expr(%struct.Node* noundef %717)
  call void @push()
  %718 = load %struct.Node*, %struct.Node** %2, align 8
  %719 = getelementptr inbounds %struct.Node, %struct.Node* %718, i32 0, i32 4
  %720 = load %struct.Node*, %struct.Node** %719, align 16
  call void @gen_expr(%struct.Node* noundef %720)
  call void @pop(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i64 0, i64 0))
  %721 = load %struct.Node*, %struct.Node** %2, align 8
  %722 = getelementptr inbounds %struct.Node, %struct.Node* %721, i32 0, i32 4
  %723 = load %struct.Node*, %struct.Node** %722, align 16
  %724 = getelementptr inbounds %struct.Node, %struct.Node* %723, i32 0, i32 2
  %725 = load %struct.Type*, %struct.Type** %724, align 16
  %726 = getelementptr inbounds %struct.Type, %struct.Type* %725, i32 0, i32 0
  %727 = load i32, i32* %726, align 8
  %728 = icmp eq i32 %727, 5
  br i1 %728, label %738, label %729

729:                                              ; preds = %714
  %730 = load %struct.Node*, %struct.Node** %2, align 8
  %731 = getelementptr inbounds %struct.Node, %struct.Node* %730, i32 0, i32 4
  %732 = load %struct.Node*, %struct.Node** %731, align 16
  %733 = getelementptr inbounds %struct.Node, %struct.Node* %732, i32 0, i32 2
  %734 = load %struct.Type*, %struct.Type** %733, align 16
  %735 = getelementptr inbounds %struct.Type, %struct.Type* %734, i32 0, i32 8
  %736 = load %struct.Type*, %struct.Type** %735, align 8
  %737 = icmp ne %struct.Type* %736, null
  br i1 %737, label %738, label %739

738:                                              ; preds = %729, %714
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i64 0, i64 0), i8** %23, align 8
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i64 0, i64 0), i8** %24, align 8
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0), i8** %25, align 8
  br label %740

739:                                              ; preds = %729
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.16, i64 0, i64 0), i8** %23, align 8
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.78, i64 0, i64 0), i8** %24, align 8
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0), i8** %25, align 8
  br label %740

740:                                              ; preds = %739, %738
  %741 = load %struct.Node*, %struct.Node** %2, align 8
  %742 = getelementptr inbounds %struct.Node, %struct.Node* %741, i32 0, i32 0
  %743 = load i32, i32* %742, align 16
  switch i32 %743, label %860 [
    i32 1, label %744
    i32 2, label %747
    i32 3, label %750
    i32 4, label %753
    i32 6, label %753
    i32 7, label %783
    i32 8, label %786
    i32 9, label %789
    i32 12, label %792
    i32 13, label %792
    i32 14, label %792
    i32 15, label %792
    i32 10, label %844
    i32 11, label %846
  ]

744:                                              ; preds = %740
  %745 = load i8*, i8** %24, align 8
  %746 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.188, i64 0, i64 0), i8* noundef %745, i8* noundef %746)
  br label %864

747:                                              ; preds = %740
  %748 = load i8*, i8** %24, align 8
  %749 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.189, i64 0, i64 0), i8* noundef %748, i8* noundef %749)
  br label %864

750:                                              ; preds = %740
  %751 = load i8*, i8** %24, align 8
  %752 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([14 x i8], [14 x i8]* @.str.190, i64 0, i64 0), i8* noundef %751, i8* noundef %752)
  br label %864

753:                                              ; preds = %740, %740
  %754 = load %struct.Node*, %struct.Node** %2, align 8
  %755 = getelementptr inbounds %struct.Node, %struct.Node* %754, i32 0, i32 2
  %756 = load %struct.Type*, %struct.Type** %755, align 16
  %757 = getelementptr inbounds %struct.Type, %struct.Type* %756, i32 0, i32 3
  %758 = load i8, i8* %757, align 4
  %759 = trunc i8 %758 to i1
  br i1 %759, label %760, label %763

760:                                              ; preds = %753
  %761 = load i8*, i8** %25, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.191, i64 0, i64 0), i8* noundef %761)
  %762 = load i8*, i8** %24, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.192, i64 0, i64 0), i8* noundef %762)
  br label %776

763:                                              ; preds = %753
  %764 = load %struct.Node*, %struct.Node** %2, align 8
  %765 = getelementptr inbounds %struct.Node, %struct.Node* %764, i32 0, i32 4
  %766 = load %struct.Node*, %struct.Node** %765, align 16
  %767 = getelementptr inbounds %struct.Node, %struct.Node* %766, i32 0, i32 2
  %768 = load %struct.Type*, %struct.Type** %767, align 16
  %769 = getelementptr inbounds %struct.Type, %struct.Type* %768, i32 0, i32 1
  %770 = load i32, i32* %769, align 4
  %771 = icmp eq i32 %770, 8
  br i1 %771, label %772, label %773

772:                                              ; preds = %763
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.193, i64 0, i64 0))
  br label %774

773:                                              ; preds = %763
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.194, i64 0, i64 0))
  br label %774

774:                                              ; preds = %773, %772
  %775 = load i8*, i8** %24, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.195, i64 0, i64 0), i8* noundef %775)
  br label %776

776:                                              ; preds = %774, %760
  %777 = load %struct.Node*, %struct.Node** %2, align 8
  %778 = getelementptr inbounds %struct.Node, %struct.Node* %777, i32 0, i32 0
  %779 = load i32, i32* %778, align 16
  %780 = icmp eq i32 %779, 6
  br i1 %780, label %781, label %782

781:                                              ; preds = %776
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.196, i64 0, i64 0))
  br label %782

782:                                              ; preds = %781, %776
  br label %864

783:                                              ; preds = %740
  %784 = load i8*, i8** %24, align 8
  %785 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.197, i64 0, i64 0), i8* noundef %784, i8* noundef %785)
  br label %864

786:                                              ; preds = %740
  %787 = load i8*, i8** %24, align 8
  %788 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.198, i64 0, i64 0), i8* noundef %787, i8* noundef %788)
  br label %864

789:                                              ; preds = %740
  %790 = load i8*, i8** %24, align 8
  %791 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.199, i64 0, i64 0), i8* noundef %790, i8* noundef %791)
  br label %864

792:                                              ; preds = %740, %740, %740, %740
  %793 = load i8*, i8** %24, align 8
  %794 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.200, i64 0, i64 0), i8* noundef %793, i8* noundef %794)
  %795 = load %struct.Node*, %struct.Node** %2, align 8
  %796 = getelementptr inbounds %struct.Node, %struct.Node* %795, i32 0, i32 0
  %797 = load i32, i32* %796, align 16
  %798 = icmp eq i32 %797, 12
  br i1 %798, label %799, label %800

799:                                              ; preds = %792
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.139, i64 0, i64 0))
  br label %843

800:                                              ; preds = %792
  %801 = load %struct.Node*, %struct.Node** %2, align 8
  %802 = getelementptr inbounds %struct.Node, %struct.Node* %801, i32 0, i32 0
  %803 = load i32, i32* %802, align 16
  %804 = icmp eq i32 %803, 13
  br i1 %804, label %805, label %806

805:                                              ; preds = %800
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.174, i64 0, i64 0))
  br label %842

806:                                              ; preds = %800
  %807 = load %struct.Node*, %struct.Node** %2, align 8
  %808 = getelementptr inbounds %struct.Node, %struct.Node* %807, i32 0, i32 0
  %809 = load i32, i32* %808, align 16
  %810 = icmp eq i32 %809, 14
  br i1 %810, label %811, label %823

811:                                              ; preds = %806
  %812 = load %struct.Node*, %struct.Node** %2, align 8
  %813 = getelementptr inbounds %struct.Node, %struct.Node* %812, i32 0, i32 4
  %814 = load %struct.Node*, %struct.Node** %813, align 16
  %815 = getelementptr inbounds %struct.Node, %struct.Node* %814, i32 0, i32 2
  %816 = load %struct.Type*, %struct.Type** %815, align 16
  %817 = getelementptr inbounds %struct.Type, %struct.Type* %816, i32 0, i32 3
  %818 = load i8, i8* %817, align 4
  %819 = trunc i8 %818 to i1
  br i1 %819, label %820, label %821

820:                                              ; preds = %811
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.201, i64 0, i64 0))
  br label %822

821:                                              ; preds = %811
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.202, i64 0, i64 0))
  br label %822

822:                                              ; preds = %821, %820
  br label %841

823:                                              ; preds = %806
  %824 = load %struct.Node*, %struct.Node** %2, align 8
  %825 = getelementptr inbounds %struct.Node, %struct.Node* %824, i32 0, i32 0
  %826 = load i32, i32* %825, align 16
  %827 = icmp eq i32 %826, 15
  br i1 %827, label %828, label %840

828:                                              ; preds = %823
  %829 = load %struct.Node*, %struct.Node** %2, align 8
  %830 = getelementptr inbounds %struct.Node, %struct.Node* %829, i32 0, i32 4
  %831 = load %struct.Node*, %struct.Node** %830, align 16
  %832 = getelementptr inbounds %struct.Node, %struct.Node* %831, i32 0, i32 2
  %833 = load %struct.Type*, %struct.Type** %832, align 16
  %834 = getelementptr inbounds %struct.Type, %struct.Type* %833, i32 0, i32 3
  %835 = load i8, i8* %834, align 4
  %836 = trunc i8 %835 to i1
  br i1 %836, label %837, label %838

837:                                              ; preds = %828
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.203, i64 0, i64 0))
  br label %839

838:                                              ; preds = %828
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.204, i64 0, i64 0))
  br label %839

839:                                              ; preds = %838, %837
  br label %840

840:                                              ; preds = %839, %823
  br label %841

841:                                              ; preds = %840, %822
  br label %842

842:                                              ; preds = %841, %805
  br label %843

843:                                              ; preds = %842, %799
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.180, i64 0, i64 0))
  br label %864

844:                                              ; preds = %740
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.205, i64 0, i64 0))
  %845 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.206, i64 0, i64 0), i8* noundef %845)
  br label %864

846:                                              ; preds = %740
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.205, i64 0, i64 0))
  %847 = load %struct.Node*, %struct.Node** %2, align 8
  %848 = getelementptr inbounds %struct.Node, %struct.Node* %847, i32 0, i32 4
  %849 = load %struct.Node*, %struct.Node** %848, align 16
  %850 = getelementptr inbounds %struct.Node, %struct.Node* %849, i32 0, i32 2
  %851 = load %struct.Type*, %struct.Type** %850, align 16
  %852 = getelementptr inbounds %struct.Type, %struct.Type* %851, i32 0, i32 3
  %853 = load i8, i8* %852, align 4
  %854 = trunc i8 %853 to i1
  br i1 %854, label %855, label %857

855:                                              ; preds = %846
  %856 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.207, i64 0, i64 0), i8* noundef %856)
  br label %859

857:                                              ; preds = %846
  %858 = load i8*, i8** %23, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.208, i64 0, i64 0), i8* noundef %858)
  br label %859

859:                                              ; preds = %857, %855
  br label %864

860:                                              ; preds = %740
  %861 = load %struct.Node*, %struct.Node** %2, align 8
  %862 = getelementptr inbounds %struct.Node, %struct.Node* %861, i32 0, i32 3
  %863 = load %struct.Token*, %struct.Token** %862, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %863, i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.181, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0)) #7
  unreachable

864:                                              ; preds = %859, %844, %843, %789, %786, %783, %782, %750, %747, %744, %709, %687, %686, %685, %684, %669, %645, %643, %641, %639, %593, %563, %559, %558, %536, %526, %516, %372, %332, %309, %305, %296, %276, %263, %251, %244, %243, %226, %203, %153, %146, %145, %102, %101, %100, %99, %98, %85, %70, %59, %48, %41
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @cmp_zero(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %3 = load %struct.Type*, %struct.Type** %2, align 8
  %4 = getelementptr inbounds %struct.Type, %struct.Type* %3, i32 0, i32 0
  %5 = load i32, i32* %4, align 8
  switch i32 %5, label %9 [
    i32 6, label %6
    i32 7, label %7
    i32 8, label %8
  ]

6:                                                ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.270, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.271, i64 0, i64 0))
  br label %19

7:                                                ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.272, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.273, i64 0, i64 0))
  br label %19

8:                                                ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([7 x i8], [7 x i8]* @.str.274, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.275, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.187, i64 0, i64 0))
  br label %19

9:                                                ; preds = %1
  %10 = load %struct.Type*, %struct.Type** %2, align 8
  %11 = call zeroext i1 @is_integer(%struct.Type* noundef %10)
  br i1 %11, label %12, label %18

12:                                               ; preds = %9
  %13 = load %struct.Type*, %struct.Type** %2, align 8
  %14 = getelementptr inbounds %struct.Type, %struct.Type* %13, i32 0, i32 1
  %15 = load i32, i32* %14, align 4
  %16 = icmp sle i32 %15, 4
  br i1 %16, label %17, label %18

17:                                               ; preds = %12
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.276, i64 0, i64 0))
  br label %19

18:                                               ; preds = %12, %9
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.277, i64 0, i64 0))
  br label %19

19:                                               ; preds = %6, %7, %8, %18, %17
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @copy_struct_reg() #0 {
  %1 = alloca %struct.Type*, align 8
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %9 = getelementptr inbounds %struct.Obj, %struct.Obj* %8, i32 0, i32 3
  %10 = load %struct.Type*, %struct.Type** %9, align 8
  %11 = getelementptr inbounds %struct.Type, %struct.Type* %10, i32 0, i32 17
  %12 = load %struct.Type*, %struct.Type** %11, align 8
  store %struct.Type* %12, %struct.Type** %1, align 8
  store i32 0, i32* %2, align 4
  store i32 0, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.125, i64 0, i64 0))
  %13 = load %struct.Type*, %struct.Type** %1, align 8
  %14 = call zeroext i1 @has_flonum(%struct.Type* noundef %13, i32 noundef 0, i32 noundef 8, i32 noundef 0)
  br i1 %14, label %15, label %37

15:                                               ; preds = %0
  %16 = load %struct.Type*, %struct.Type** %1, align 8
  %17 = getelementptr inbounds %struct.Type, %struct.Type* %16, i32 0, i32 1
  %18 = load i32, i32* %17, align 4
  %19 = icmp eq i32 %18, 4
  br i1 %19, label %25, label %20

20:                                               ; preds = %15
  %21 = load %struct.Type*, %struct.Type** %1, align 8
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 1
  %23 = load i32, i32* %22, align 4
  %24 = icmp sle i32 8, %23
  br i1 %24, label %25, label %26

25:                                               ; preds = %20, %15
  br label %27

26:                                               ; preds = %20
  call void @__assert_fail(i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.264, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 745, i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @__PRETTY_FUNCTION__.copy_struct_reg, i64 0, i64 0)) #8
  unreachable

27:                                               ; preds = %25
  %28 = load %struct.Type*, %struct.Type** %1, align 8
  %29 = getelementptr inbounds %struct.Type, %struct.Type* %28, i32 0, i32 1
  %30 = load i32, i32* %29, align 4
  %31 = icmp eq i32 %30, 4
  br i1 %31, label %32, label %33

32:                                               ; preds = %27
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.278, i64 0, i64 0))
  br label %34

33:                                               ; preds = %27
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.279, i64 0, i64 0))
  br label %34

34:                                               ; preds = %33, %32
  %35 = load i32, i32* %3, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %3, align 4
  br label %61

37:                                               ; preds = %0
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.61, i64 0, i64 0))
  %38 = load %struct.Type*, %struct.Type** %1, align 8
  %39 = getelementptr inbounds %struct.Type, %struct.Type* %38, i32 0, i32 1
  %40 = load i32, i32* %39, align 4
  %41 = icmp slt i32 8, %40
  br i1 %41, label %42, label %43

42:                                               ; preds = %37
  br label %47

43:                                               ; preds = %37
  %44 = load %struct.Type*, %struct.Type** %1, align 8
  %45 = getelementptr inbounds %struct.Type, %struct.Type* %44, i32 0, i32 1
  %46 = load i32, i32* %45, align 4
  br label %47

47:                                               ; preds = %43, %42
  %48 = phi i32 [ 8, %42 ], [ %46, %43 ]
  %49 = sub nsw i32 %48, 1
  store i32 %49, i32* %4, align 4
  br label %50

50:                                               ; preds = %55, %47
  %51 = load i32, i32* %4, align 4
  %52 = icmp sge i32 %51, 0
  br i1 %52, label %53, label %58

53:                                               ; preds = %50
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.280, i64 0, i64 0))
  %54 = load i32, i32* %4, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.281, i64 0, i64 0), i32 noundef %54)
  br label %55

55:                                               ; preds = %53
  %56 = load i32, i32* %4, align 4
  %57 = add nsw i32 %56, -1
  store i32 %57, i32* %4, align 4
  br label %50, !llvm.loop !23

58:                                               ; preds = %50
  %59 = load i32, i32* %2, align 4
  %60 = add nsw i32 %59, 1
  store i32 %60, i32* %2, align 4
  br label %61

61:                                               ; preds = %58, %34
  %62 = load %struct.Type*, %struct.Type** %1, align 8
  %63 = getelementptr inbounds %struct.Type, %struct.Type* %62, i32 0, i32 1
  %64 = load i32, i32* %63, align 4
  %65 = icmp sgt i32 %64, 8
  br i1 %65, label %66, label %125

66:                                               ; preds = %61
  %67 = load %struct.Type*, %struct.Type** %1, align 8
  %68 = call zeroext i1 @has_flonum(%struct.Type* noundef %67, i32 noundef 8, i32 noundef 16, i32 noundef 0)
  br i1 %68, label %69, label %91

69:                                               ; preds = %66
  %70 = load %struct.Type*, %struct.Type** %1, align 8
  %71 = getelementptr inbounds %struct.Type, %struct.Type* %70, i32 0, i32 1
  %72 = load i32, i32* %71, align 4
  %73 = icmp eq i32 %72, 12
  br i1 %73, label %79, label %74

74:                                               ; preds = %69
  %75 = load %struct.Type*, %struct.Type** %1, align 8
  %76 = getelementptr inbounds %struct.Type, %struct.Type* %75, i32 0, i32 1
  %77 = load i32, i32* %76, align 4
  %78 = icmp eq i32 %77, 16
  br i1 %78, label %79, label %80

79:                                               ; preds = %74, %69
  br label %81

80:                                               ; preds = %74
  call void @__assert_fail(i8* noundef getelementptr inbounds ([33 x i8], [33 x i8]* @.str.268, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 767, i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @__PRETTY_FUNCTION__.copy_struct_reg, i64 0, i64 0)) #8
  unreachable

81:                                               ; preds = %79
  %82 = load %struct.Type*, %struct.Type** %1, align 8
  %83 = getelementptr inbounds %struct.Type, %struct.Type* %82, i32 0, i32 1
  %84 = load i32, i32* %83, align 4
  %85 = icmp eq i32 %84, 12
  br i1 %85, label %86, label %88

86:                                               ; preds = %81
  %87 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.282, i64 0, i64 0), i32 noundef %87)
  br label %90

88:                                               ; preds = %81
  %89 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.283, i64 0, i64 0), i32 noundef %89)
  br label %90

90:                                               ; preds = %88, %86
  br label %124

91:                                               ; preds = %66
  %92 = load i32, i32* %2, align 4
  %93 = icmp eq i32 %92, 0
  %94 = zext i1 %93 to i64
  %95 = select i1 %93, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.14, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0)
  store i8* %95, i8** %5, align 8
  %96 = load i32, i32* %2, align 4
  %97 = icmp eq i32 %96, 0
  %98 = zext i1 %97 to i64
  %99 = select i1 %97, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0)
  store i8* %99, i8** %6, align 8
  %100 = load i8*, i8** %6, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.191, i64 0, i64 0), i8* noundef %100)
  %101 = load %struct.Type*, %struct.Type** %1, align 8
  %102 = getelementptr inbounds %struct.Type, %struct.Type* %101, i32 0, i32 1
  %103 = load i32, i32* %102, align 4
  %104 = icmp slt i32 16, %103
  br i1 %104, label %105, label %106

105:                                              ; preds = %91
  br label %110

106:                                              ; preds = %91
  %107 = load %struct.Type*, %struct.Type** %1, align 8
  %108 = getelementptr inbounds %struct.Type, %struct.Type* %107, i32 0, i32 1
  %109 = load i32, i32* %108, align 4
  br label %110

110:                                              ; preds = %106, %105
  %111 = phi i32 [ 16, %105 ], [ %109, %106 ]
  %112 = sub nsw i32 %111, 1
  store i32 %112, i32* %7, align 4
  br label %113

113:                                              ; preds = %120, %110
  %114 = load i32, i32* %7, align 4
  %115 = icmp sge i32 %114, 8
  br i1 %115, label %116, label %123

116:                                              ; preds = %113
  %117 = load i8*, i8** %6, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.284, i64 0, i64 0), i8* noundef %117)
  %118 = load i32, i32* %7, align 4
  %119 = load i8*, i8** %5, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.285, i64 0, i64 0), i32 noundef %118, i8* noundef %119)
  br label %120

120:                                              ; preds = %116
  %121 = load i32, i32* %7, align 4
  %122 = add nsw i32 %121, -1
  store i32 %122, i32* %7, align 4
  br label %113, !llvm.loop !24

123:                                              ; preds = %113
  br label %124

124:                                              ; preds = %123, %90
  br label %125

125:                                              ; preds = %124, %61
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @copy_struct_mem() #0 {
  %1 = alloca %struct.Type*, align 8
  %2 = alloca %struct.Obj*, align 8
  %3 = alloca i32, align 4
  %4 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %5 = getelementptr inbounds %struct.Obj, %struct.Obj* %4, i32 0, i32 3
  %6 = load %struct.Type*, %struct.Type** %5, align 8
  %7 = getelementptr inbounds %struct.Type, %struct.Type* %6, i32 0, i32 17
  %8 = load %struct.Type*, %struct.Type** %7, align 8
  store %struct.Type* %8, %struct.Type** %1, align 8
  %9 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %10 = getelementptr inbounds %struct.Obj, %struct.Obj* %9, i32 0, i32 18
  %11 = load %struct.Obj*, %struct.Obj** %10, align 8
  store %struct.Obj* %11, %struct.Obj** %2, align 8
  %12 = load %struct.Obj*, %struct.Obj** %2, align 8
  %13 = getelementptr inbounds %struct.Obj, %struct.Obj* %12, i32 0, i32 7
  %14 = load i32, i32* %13, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.286, i64 0, i64 0), i32 noundef %14)
  store i32 0, i32* %3, align 4
  br label %15

15:                                               ; preds = %24, %0
  %16 = load i32, i32* %3, align 4
  %17 = load %struct.Type*, %struct.Type** %1, align 8
  %18 = getelementptr inbounds %struct.Type, %struct.Type* %17, i32 0, i32 1
  %19 = load i32, i32* %18, align 4
  %20 = icmp slt i32 %16, %19
  br i1 %20, label %21, label %27

21:                                               ; preds = %15
  %22 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.287, i64 0, i64 0), i32 noundef %22)
  %23 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.288, i64 0, i64 0), i32 noundef %23)
  br label %24

24:                                               ; preds = %21
  %25 = load i32, i32* %3, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, i32* %3, align 4
  br label %15, !llvm.loop !25

27:                                               ; preds = %15
  ret void
}

; Function Attrs: noreturn
declare void @error_tok(%struct.Token* noundef, i8* noundef, ...) #1

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #6

; Function Attrs: noinline nounwind optnone uwtable
define internal void @gen_addr(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %2, align 8
  %3 = load %struct.Node*, %struct.Node** %2, align 8
  %4 = getelementptr inbounds %struct.Node, %struct.Node* %3, i32 0, i32 0
  %5 = load i32, i32* %4, align 16
  switch i32 %5, label %153 [
    i32 40, label %6
    i32 21, label %102
    i32 18, label %106
    i32 19, label %113
    i32 37, label %122
    i32 16, label %130
    i32 17, label %130
    i32 41, label %147
  ]

6:                                                ; preds = %1
  %7 = load %struct.Node*, %struct.Node** %2, align 8
  %8 = getelementptr inbounds %struct.Node, %struct.Node* %7, i32 0, i32 33
  %9 = load %struct.Obj*, %struct.Obj** %8, align 8
  %10 = getelementptr inbounds %struct.Obj, %struct.Obj* %9, i32 0, i32 3
  %11 = load %struct.Type*, %struct.Type** %10, align 8
  %12 = getelementptr inbounds %struct.Type, %struct.Type* %11, i32 0, i32 0
  %13 = load i32, i32* %12, align 8
  %14 = icmp eq i32 %13, 13
  br i1 %14, label %15, label %21

15:                                               ; preds = %6
  %16 = load %struct.Node*, %struct.Node** %2, align 8
  %17 = getelementptr inbounds %struct.Node, %struct.Node* %16, i32 0, i32 33
  %18 = load %struct.Obj*, %struct.Obj** %17, align 8
  %19 = getelementptr inbounds %struct.Obj, %struct.Obj* %18, i32 0, i32 7
  %20 = load i32, i32* %19, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.209, i64 0, i64 0), i32 noundef %20)
  br label %157

21:                                               ; preds = %6
  %22 = load %struct.Node*, %struct.Node** %2, align 8
  %23 = getelementptr inbounds %struct.Node, %struct.Node* %22, i32 0, i32 33
  %24 = load %struct.Obj*, %struct.Obj** %23, align 8
  %25 = getelementptr inbounds %struct.Obj, %struct.Obj* %24, i32 0, i32 5
  %26 = load i8, i8* %25, align 8
  %27 = trunc i8 %26 to i1
  br i1 %27, label %28, label %34

28:                                               ; preds = %21
  %29 = load %struct.Node*, %struct.Node** %2, align 8
  %30 = getelementptr inbounds %struct.Node, %struct.Node* %29, i32 0, i32 33
  %31 = load %struct.Obj*, %struct.Obj** %30, align 8
  %32 = getelementptr inbounds %struct.Obj, %struct.Obj* %31, i32 0, i32 7
  %33 = load i32, i32* %32, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.156, i64 0, i64 0), i32 noundef %33)
  br label %157

34:                                               ; preds = %21
  %35 = load i8, i8* @opt_fpic, align 1
  %36 = trunc i8 %35 to i1
  br i1 %36, label %37, label %56

37:                                               ; preds = %34
  %38 = load %struct.Node*, %struct.Node** %2, align 8
  %39 = getelementptr inbounds %struct.Node, %struct.Node* %38, i32 0, i32 33
  %40 = load %struct.Obj*, %struct.Obj** %39, align 8
  %41 = getelementptr inbounds %struct.Obj, %struct.Obj* %40, i32 0, i32 14
  %42 = load i8, i8* %41, align 8
  %43 = trunc i8 %42 to i1
  br i1 %43, label %44, label %50

44:                                               ; preds = %37
  %45 = load %struct.Node*, %struct.Node** %2, align 8
  %46 = getelementptr inbounds %struct.Node, %struct.Node* %45, i32 0, i32 33
  %47 = load %struct.Obj*, %struct.Obj** %46, align 8
  %48 = getelementptr inbounds %struct.Obj, %struct.Obj* %47, i32 0, i32 1
  %49 = load i8*, i8** %48, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([36 x i8], [36 x i8]* @.str.210, i64 0, i64 0), i8* noundef %49)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.211, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.212, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.213, i64 0, i64 0))
  br label %157

50:                                               ; preds = %37
  %51 = load %struct.Node*, %struct.Node** %2, align 8
  %52 = getelementptr inbounds %struct.Node, %struct.Node* %51, i32 0, i32 33
  %53 = load %struct.Obj*, %struct.Obj** %52, align 8
  %54 = getelementptr inbounds %struct.Obj, %struct.Obj* %53, i32 0, i32 1
  %55 = load i8*, i8** %54, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @.str.214, i64 0, i64 0), i8* noundef %55)
  br label %157

56:                                               ; preds = %34
  %57 = load %struct.Node*, %struct.Node** %2, align 8
  %58 = getelementptr inbounds %struct.Node, %struct.Node* %57, i32 0, i32 33
  %59 = load %struct.Obj*, %struct.Obj** %58, align 8
  %60 = getelementptr inbounds %struct.Obj, %struct.Obj* %59, i32 0, i32 14
  %61 = load i8, i8* %60, align 8
  %62 = trunc i8 %61 to i1
  br i1 %62, label %63, label %69

63:                                               ; preds = %56
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.215, i64 0, i64 0))
  %64 = load %struct.Node*, %struct.Node** %2, align 8
  %65 = getelementptr inbounds %struct.Node, %struct.Node* %64, i32 0, i32 33
  %66 = load %struct.Obj*, %struct.Obj** %65, align 8
  %67 = getelementptr inbounds %struct.Obj, %struct.Obj* %66, i32 0, i32 1
  %68 = load i8*, i8** %67, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.216, i64 0, i64 0), i8* noundef %68)
  br label %157

69:                                               ; preds = %56
  %70 = load %struct.Node*, %struct.Node** %2, align 8
  %71 = getelementptr inbounds %struct.Node, %struct.Node* %70, i32 0, i32 2
  %72 = load %struct.Type*, %struct.Type** %71, align 16
  %73 = getelementptr inbounds %struct.Type, %struct.Type* %72, i32 0, i32 0
  %74 = load i32, i32* %73, align 8
  %75 = icmp eq i32 %74, 11
  br i1 %75, label %76, label %96

76:                                               ; preds = %69
  %77 = load %struct.Node*, %struct.Node** %2, align 8
  %78 = getelementptr inbounds %struct.Node, %struct.Node* %77, i32 0, i32 33
  %79 = load %struct.Obj*, %struct.Obj** %78, align 8
  %80 = getelementptr inbounds %struct.Obj, %struct.Obj* %79, i32 0, i32 11
  %81 = load i8, i8* %80, align 1
  %82 = trunc i8 %81 to i1
  br i1 %82, label %83, label %89

83:                                               ; preds = %76
  %84 = load %struct.Node*, %struct.Node** %2, align 8
  %85 = getelementptr inbounds %struct.Node, %struct.Node* %84, i32 0, i32 33
  %86 = load %struct.Obj*, %struct.Obj** %85, align 8
  %87 = getelementptr inbounds %struct.Obj, %struct.Obj* %86, i32 0, i32 1
  %88 = load i8*, i8** %87, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.157, i64 0, i64 0), i8* noundef %88)
  br label %95

89:                                               ; preds = %76
  %90 = load %struct.Node*, %struct.Node** %2, align 8
  %91 = getelementptr inbounds %struct.Node, %struct.Node* %90, i32 0, i32 33
  %92 = load %struct.Obj*, %struct.Obj** %91, align 8
  %93 = getelementptr inbounds %struct.Obj, %struct.Obj* %92, i32 0, i32 1
  %94 = load i8*, i8** %93, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @.str.214, i64 0, i64 0), i8* noundef %94)
  br label %95

95:                                               ; preds = %89, %83
  br label %157

96:                                               ; preds = %69
  %97 = load %struct.Node*, %struct.Node** %2, align 8
  %98 = getelementptr inbounds %struct.Node, %struct.Node* %97, i32 0, i32 33
  %99 = load %struct.Obj*, %struct.Obj** %98, align 8
  %100 = getelementptr inbounds %struct.Obj, %struct.Obj* %99, i32 0, i32 1
  %101 = load i8*, i8** %100, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.157, i64 0, i64 0), i8* noundef %101)
  br label %157

102:                                              ; preds = %1
  %103 = load %struct.Node*, %struct.Node** %2, align 8
  %104 = getelementptr inbounds %struct.Node, %struct.Node* %103, i32 0, i32 4
  %105 = load %struct.Node*, %struct.Node** %104, align 16
  call void @gen_expr(%struct.Node* noundef %105)
  br label %157

106:                                              ; preds = %1
  %107 = load %struct.Node*, %struct.Node** %2, align 8
  %108 = getelementptr inbounds %struct.Node, %struct.Node* %107, i32 0, i32 4
  %109 = load %struct.Node*, %struct.Node** %108, align 16
  call void @gen_expr(%struct.Node* noundef %109)
  %110 = load %struct.Node*, %struct.Node** %2, align 8
  %111 = getelementptr inbounds %struct.Node, %struct.Node* %110, i32 0, i32 5
  %112 = load %struct.Node*, %struct.Node** %111, align 8
  call void @gen_addr(%struct.Node* noundef %112)
  br label %157

113:                                              ; preds = %1
  %114 = load %struct.Node*, %struct.Node** %2, align 8
  %115 = getelementptr inbounds %struct.Node, %struct.Node* %114, i32 0, i32 4
  %116 = load %struct.Node*, %struct.Node** %115, align 16
  call void @gen_addr(%struct.Node* noundef %116)
  %117 = load %struct.Node*, %struct.Node** %2, align 8
  %118 = getelementptr inbounds %struct.Node, %struct.Node* %117, i32 0, i32 14
  %119 = load %struct.Member*, %struct.Member** %118, align 16
  %120 = getelementptr inbounds %struct.Member, %struct.Member* %119, i32 0, i32 6
  %121 = load i32, i32* %120, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.217, i64 0, i64 0), i32 noundef %121)
  br label %157

122:                                              ; preds = %1
  %123 = load %struct.Node*, %struct.Node** %2, align 8
  %124 = getelementptr inbounds %struct.Node, %struct.Node* %123, i32 0, i32 18
  %125 = load %struct.Obj*, %struct.Obj** %124, align 16
  %126 = icmp ne %struct.Obj* %125, null
  br i1 %126, label %127, label %129

127:                                              ; preds = %122
  %128 = load %struct.Node*, %struct.Node** %2, align 8
  call void @gen_expr(%struct.Node* noundef %128)
  br label %157

129:                                              ; preds = %122
  br label %153

130:                                              ; preds = %1, %1
  %131 = load %struct.Node*, %struct.Node** %2, align 8
  %132 = getelementptr inbounds %struct.Node, %struct.Node* %131, i32 0, i32 2
  %133 = load %struct.Type*, %struct.Type** %132, align 16
  %134 = getelementptr inbounds %struct.Type, %struct.Type* %133, i32 0, i32 0
  %135 = load i32, i32* %134, align 8
  %136 = icmp eq i32 %135, 14
  br i1 %136, label %144, label %137

137:                                              ; preds = %130
  %138 = load %struct.Node*, %struct.Node** %2, align 8
  %139 = getelementptr inbounds %struct.Node, %struct.Node* %138, i32 0, i32 2
  %140 = load %struct.Type*, %struct.Type** %139, align 16
  %141 = getelementptr inbounds %struct.Type, %struct.Type* %140, i32 0, i32 0
  %142 = load i32, i32* %141, align 8
  %143 = icmp eq i32 %142, 15
  br i1 %143, label %144, label %146

144:                                              ; preds = %137, %130
  %145 = load %struct.Node*, %struct.Node** %2, align 8
  call void @gen_expr(%struct.Node* noundef %145)
  br label %157

146:                                              ; preds = %137
  br label %153

147:                                              ; preds = %1
  %148 = load %struct.Node*, %struct.Node** %2, align 8
  %149 = getelementptr inbounds %struct.Node, %struct.Node* %148, i32 0, i32 33
  %150 = load %struct.Obj*, %struct.Obj** %149, align 8
  %151 = getelementptr inbounds %struct.Obj, %struct.Obj* %150, i32 0, i32 7
  %152 = load i32, i32* %151, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.156, i64 0, i64 0), i32 noundef %152)
  br label %157

153:                                              ; preds = %1, %146, %129
  %154 = load %struct.Node*, %struct.Node** %2, align 8
  %155 = getelementptr inbounds %struct.Node, %struct.Node* %154, i32 0, i32 3
  %156 = load %struct.Token*, %struct.Token** %155, align 8
  call void (%struct.Token*, i8*, ...) @error_tok(%struct.Token* noundef %156, i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.218, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0)) #7
  unreachable

157:                                              ; preds = %147, %144, %127, %113, %106, %102, %96, %95, %63, %50, %44, %28, %15
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @load(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca i8*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %4 = load %struct.Type*, %struct.Type** %2, align 8
  %5 = getelementptr inbounds %struct.Type, %struct.Type* %4, i32 0, i32 0
  %6 = load i32, i32* %5, align 8
  switch i32 %6, label %11 [
    i32 12, label %7
    i32 14, label %7
    i32 15, label %7
    i32 11, label %7
    i32 13, label %7
    i32 6, label %8
    i32 7, label %9
    i32 8, label %10
  ]

7:                                                ; preds = %1, %1, %1, %1, %1
  br label %40

8:                                                ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.219, i64 0, i64 0))
  br label %40

9:                                                ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.220, i64 0, i64 0))
  br label %40

10:                                               ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([15 x i8], [15 x i8]* @.str.221, i64 0, i64 0))
  br label %40

11:                                               ; preds = %1
  %12 = load %struct.Type*, %struct.Type** %2, align 8
  %13 = getelementptr inbounds %struct.Type, %struct.Type* %12, i32 0, i32 3
  %14 = load i8, i8* %13, align 4
  %15 = trunc i8 %14 to i1
  %16 = zext i1 %15 to i64
  %17 = select i1 %15, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.222, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.223, i64 0, i64 0)
  store i8* %17, i8** %3, align 8
  %18 = load %struct.Type*, %struct.Type** %2, align 8
  %19 = getelementptr inbounds %struct.Type, %struct.Type* %18, i32 0, i32 1
  %20 = load i32, i32* %19, align 4
  %21 = icmp eq i32 %20, 1
  br i1 %21, label %22, label %24

22:                                               ; preds = %11
  %23 = load i8*, i8** %3, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.224, i64 0, i64 0), i8* noundef %23)
  br label %40

24:                                               ; preds = %11
  %25 = load %struct.Type*, %struct.Type** %2, align 8
  %26 = getelementptr inbounds %struct.Type, %struct.Type* %25, i32 0, i32 1
  %27 = load i32, i32* %26, align 4
  %28 = icmp eq i32 %27, 2
  br i1 %28, label %29, label %31

29:                                               ; preds = %24
  %30 = load i8*, i8** %3, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.225, i64 0, i64 0), i8* noundef %30)
  br label %39

31:                                               ; preds = %24
  %32 = load %struct.Type*, %struct.Type** %2, align 8
  %33 = getelementptr inbounds %struct.Type, %struct.Type* %32, i32 0, i32 1
  %34 = load i32, i32* %33, align 4
  %35 = icmp eq i32 %34, 4
  br i1 %35, label %36, label %37

36:                                               ; preds = %31
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.226, i64 0, i64 0))
  br label %38

37:                                               ; preds = %31
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.227, i64 0, i64 0))
  br label %38

38:                                               ; preds = %37, %36
  br label %39

39:                                               ; preds = %38, %29
  br label %40

40:                                               ; preds = %7, %8, %9, %10, %39, %22
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @push() #0 {
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.228, i64 0, i64 0))
  %1 = load i32, i32* @depth, align 4
  %2 = add nsw i32 %1, 1
  store i32 %2, i32* @depth, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @store(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca i32, align 4
  store %struct.Type* %0, %struct.Type** %2, align 8
  call void @pop(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i64 0, i64 0))
  %4 = load %struct.Type*, %struct.Type** %2, align 8
  %5 = getelementptr inbounds %struct.Type, %struct.Type* %4, i32 0, i32 0
  %6 = load i32, i32* %5, align 8
  switch i32 %6, label %24 [
    i32 14, label %7
    i32 15, label %7
    i32 6, label %21
    i32 7, label %22
    i32 8, label %23
  ]

7:                                                ; preds = %1, %1
  store i32 0, i32* %3, align 4
  br label %8

8:                                                ; preds = %17, %7
  %9 = load i32, i32* %3, align 4
  %10 = load %struct.Type*, %struct.Type** %2, align 8
  %11 = getelementptr inbounds %struct.Type, %struct.Type* %10, i32 0, i32 1
  %12 = load i32, i32* %11, align 4
  %13 = icmp slt i32 %9, %12
  br i1 %13, label %14, label %20

14:                                               ; preds = %8
  %15 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.229, i64 0, i64 0), i32 noundef %15)
  %16 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.230, i64 0, i64 0), i32 noundef %16)
  br label %17

17:                                               ; preds = %14
  %18 = load i32, i32* %3, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, i32* %3, align 4
  br label %8, !llvm.loop !26

20:                                               ; preds = %8
  br label %45

21:                                               ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.231, i64 0, i64 0))
  br label %45

22:                                               ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.232, i64 0, i64 0))
  br label %45

23:                                               ; preds = %1
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.233, i64 0, i64 0))
  br label %45

24:                                               ; preds = %1
  %25 = load %struct.Type*, %struct.Type** %2, align 8
  %26 = getelementptr inbounds %struct.Type, %struct.Type* %25, i32 0, i32 1
  %27 = load i32, i32* %26, align 4
  %28 = icmp eq i32 %27, 1
  br i1 %28, label %29, label %30

29:                                               ; preds = %24
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.234, i64 0, i64 0))
  br label %45

30:                                               ; preds = %24
  %31 = load %struct.Type*, %struct.Type** %2, align 8
  %32 = getelementptr inbounds %struct.Type, %struct.Type* %31, i32 0, i32 1
  %33 = load i32, i32* %32, align 4
  %34 = icmp eq i32 %33, 2
  br i1 %34, label %35, label %36

35:                                               ; preds = %30
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.235, i64 0, i64 0))
  br label %44

36:                                               ; preds = %30
  %37 = load %struct.Type*, %struct.Type** %2, align 8
  %38 = getelementptr inbounds %struct.Type, %struct.Type* %37, i32 0, i32 1
  %39 = load i32, i32* %38, align 4
  %40 = icmp eq i32 %39, 4
  br i1 %40, label %41, label %42

41:                                               ; preds = %36
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.236, i64 0, i64 0))
  br label %43

42:                                               ; preds = %36
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.237, i64 0, i64 0))
  br label %43

43:                                               ; preds = %42, %41
  br label %44

44:                                               ; preds = %43, %35
  br label %45

45:                                               ; preds = %20, %21, %22, %23, %44, %29
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @cast(%struct.Type* noundef %0, %struct.Type* noundef %1) #0 {
  %3 = alloca %struct.Type*, align 8
  %4 = alloca %struct.Type*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store %struct.Type* %0, %struct.Type** %3, align 8
  store %struct.Type* %1, %struct.Type** %4, align 8
  %7 = load %struct.Type*, %struct.Type** %4, align 8
  %8 = getelementptr inbounds %struct.Type, %struct.Type* %7, i32 0, i32 0
  %9 = load i32, i32* %8, align 8
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %11, label %12

11:                                               ; preds = %2
  br label %40

12:                                               ; preds = %2
  %13 = load %struct.Type*, %struct.Type** %4, align 8
  %14 = getelementptr inbounds %struct.Type, %struct.Type* %13, i32 0, i32 0
  %15 = load i32, i32* %14, align 8
  %16 = icmp eq i32 %15, 1
  br i1 %16, label %17, label %19

17:                                               ; preds = %12
  %18 = load %struct.Type*, %struct.Type** %3, align 8
  call void @cmp_zero(%struct.Type* noundef %18)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.174, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.151, i64 0, i64 0))
  br label %40

19:                                               ; preds = %12
  %20 = load %struct.Type*, %struct.Type** %3, align 8
  %21 = call i32 @getTypeId(%struct.Type* noundef %20)
  store i32 %21, i32* %5, align 4
  %22 = load %struct.Type*, %struct.Type** %4, align 8
  %23 = call i32 @getTypeId(%struct.Type* noundef %22)
  store i32 %23, i32* %6, align 4
  %24 = load i32, i32* %5, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds [11 x [11 x i8*]], [11 x [11 x i8*]]* @cast_table, i64 0, i64 %25
  %27 = load i32, i32* %6, align 4
  %28 = sext i32 %27 to i64
  %29 = getelementptr inbounds [11 x i8*], [11 x i8*]* %26, i64 0, i64 %28
  %30 = load i8*, i8** %29, align 8
  %31 = icmp ne i8* %30, null
  br i1 %31, label %32, label %40

32:                                               ; preds = %19
  %33 = load i32, i32* %5, align 4
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds [11 x [11 x i8*]], [11 x [11 x i8*]]* @cast_table, i64 0, i64 %34
  %36 = load i32, i32* %6, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds [11 x i8*], [11 x i8*]* %35, i64 0, i64 %37
  %39 = load i8*, i8** %38, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([5 x i8], [5 x i8]* @.str.102, i64 0, i64 0), i8* noundef %39)
  br label %40

40:                                               ; preds = %11, %17, %32, %19
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @builtin_alloca() #0 {
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.238, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.239, i64 0, i64 0))
  %1 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %2 = getelementptr inbounds %struct.Obj, %struct.Obj* %1, i32 0, i32 22
  %3 = load %struct.Obj*, %struct.Obj** %2, align 8
  %4 = getelementptr inbounds %struct.Obj, %struct.Obj* %3, i32 0, i32 7
  %5 = load i32, i32* %4, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.240, i64 0, i64 0), i32 noundef %5)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.241, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.242, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.243, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.244, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.162, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.245, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([8 x i8], [8 x i8]* @.str.246, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.247, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.248, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.249, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.250, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([12 x i8], [12 x i8]* @.str.251, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.252, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.253, i64 0, i64 0))
  %6 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %7 = getelementptr inbounds %struct.Obj, %struct.Obj* %6, i32 0, i32 22
  %8 = load %struct.Obj*, %struct.Obj** %7, align 8
  %9 = getelementptr inbounds %struct.Obj, %struct.Obj* %8, i32 0, i32 7
  %10 = load i32, i32* %9, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.209, i64 0, i64 0), i32 noundef %10)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str.254, i64 0, i64 0))
  %11 = load %struct.Obj*, %struct.Obj** @current_fn, align 8
  %12 = getelementptr inbounds %struct.Obj, %struct.Obj* %11, i32 0, i32 22
  %13 = load %struct.Obj*, %struct.Obj** %12, align 8
  %14 = getelementptr inbounds %struct.Obj, %struct.Obj* %13, i32 0, i32 7
  %15 = load i32, i32* %14, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.255, i64 0, i64 0), i32 noundef %15)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @push_args(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Type*, align 8
  %8 = alloca i8, align 1
  %9 = alloca i8, align 1
  store %struct.Node* %0, %struct.Node** %2, align 8
  store i32 0, i32* %3, align 4
  store i32 0, i32* %4, align 4
  store i32 0, i32* %5, align 4
  %10 = load %struct.Node*, %struct.Node** %2, align 8
  %11 = getelementptr inbounds %struct.Node, %struct.Node* %10, i32 0, i32 18
  %12 = load %struct.Obj*, %struct.Obj** %11, align 16
  %13 = icmp ne %struct.Obj* %12, null
  br i1 %13, label %14, label %24

14:                                               ; preds = %1
  %15 = load %struct.Node*, %struct.Node** %2, align 8
  %16 = getelementptr inbounds %struct.Node, %struct.Node* %15, i32 0, i32 2
  %17 = load %struct.Type*, %struct.Type** %16, align 16
  %18 = getelementptr inbounds %struct.Type, %struct.Type* %17, i32 0, i32 1
  %19 = load i32, i32* %18, align 4
  %20 = icmp sgt i32 %19, 16
  br i1 %20, label %21, label %24

21:                                               ; preds = %14
  %22 = load i32, i32* %4, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* %4, align 4
  br label %24

24:                                               ; preds = %21, %14, %1
  %25 = load %struct.Node*, %struct.Node** %2, align 8
  %26 = getelementptr inbounds %struct.Node, %struct.Node* %25, i32 0, i32 16
  %27 = load %struct.Node*, %struct.Node** %26, align 16
  store %struct.Node* %27, %struct.Node** %6, align 8
  br label %28

28:                                               ; preds = %142, %24
  %29 = load %struct.Node*, %struct.Node** %6, align 8
  %30 = icmp ne %struct.Node* %29, null
  br i1 %30, label %31, label %146

31:                                               ; preds = %28
  %32 = load %struct.Node*, %struct.Node** %6, align 8
  %33 = getelementptr inbounds %struct.Node, %struct.Node* %32, i32 0, i32 2
  %34 = load %struct.Type*, %struct.Type** %33, align 16
  store %struct.Type* %34, %struct.Type** %7, align 8
  %35 = load %struct.Type*, %struct.Type** %7, align 8
  %36 = getelementptr inbounds %struct.Type, %struct.Type* %35, i32 0, i32 0
  %37 = load i32, i32* %36, align 8
  switch i32 %37, label %131 [
    i32 14, label %38
    i32 15, label %38
    i32 6, label %116
    i32 7, label %116
    i32 8, label %126
  ]

38:                                               ; preds = %31, %31
  %39 = load %struct.Type*, %struct.Type** %7, align 8
  %40 = getelementptr inbounds %struct.Type, %struct.Type* %39, i32 0, i32 1
  %41 = load i32, i32* %40, align 4
  %42 = icmp sgt i32 %41, 16
  br i1 %42, label %43, label %53

43:                                               ; preds = %38
  %44 = load %struct.Node*, %struct.Node** %6, align 8
  %45 = getelementptr inbounds %struct.Node, %struct.Node* %44, i32 0, i32 17
  store i8 1, i8* %45, align 8
  %46 = load %struct.Type*, %struct.Type** %7, align 8
  %47 = getelementptr inbounds %struct.Type, %struct.Type* %46, i32 0, i32 1
  %48 = load i32, i32* %47, align 4
  %49 = call i32 @align_to(i32 noundef %48, i32 noundef 8)
  %50 = sdiv i32 %49, 8
  %51 = load i32, i32* %3, align 4
  %52 = add nsw i32 %51, %50
  store i32 %52, i32* %3, align 4
  br label %115

53:                                               ; preds = %38
  %54 = load %struct.Type*, %struct.Type** %7, align 8
  %55 = call zeroext i1 @has_flonum1(%struct.Type* noundef %54)
  %56 = zext i1 %55 to i8
  store i8 %56, i8* %8, align 1
  %57 = load %struct.Type*, %struct.Type** %7, align 8
  %58 = call zeroext i1 @has_flonum2(%struct.Type* noundef %57)
  %59 = zext i1 %58 to i8
  store i8 %59, i8* %9, align 1
  %60 = load i32, i32* %5, align 4
  %61 = load i8, i8* %8, align 1
  %62 = trunc i8 %61 to i1
  %63 = zext i1 %62 to i32
  %64 = add nsw i32 %60, %63
  %65 = load i8, i8* %9, align 1
  %66 = trunc i8 %65 to i1
  %67 = zext i1 %66 to i32
  %68 = add nsw i32 %64, %67
  %69 = icmp slt i32 %68, 8
  br i1 %69, label %70, label %104

70:                                               ; preds = %53
  %71 = load i32, i32* %4, align 4
  %72 = load i8, i8* %8, align 1
  %73 = trunc i8 %72 to i1
  %74 = xor i1 %73, true
  %75 = zext i1 %74 to i32
  %76 = add nsw i32 %71, %75
  %77 = load i8, i8* %9, align 1
  %78 = trunc i8 %77 to i1
  %79 = xor i1 %78, true
  %80 = zext i1 %79 to i32
  %81 = add nsw i32 %76, %80
  %82 = icmp slt i32 %81, 6
  br i1 %82, label %83, label %104

83:                                               ; preds = %70
  %84 = load i32, i32* %5, align 4
  %85 = load i8, i8* %8, align 1
  %86 = trunc i8 %85 to i1
  %87 = zext i1 %86 to i32
  %88 = add nsw i32 %84, %87
  %89 = load i8, i8* %9, align 1
  %90 = trunc i8 %89 to i1
  %91 = zext i1 %90 to i32
  %92 = add nsw i32 %88, %91
  store i32 %92, i32* %5, align 4
  %93 = load i32, i32* %4, align 4
  %94 = load i8, i8* %8, align 1
  %95 = trunc i8 %94 to i1
  %96 = xor i1 %95, true
  %97 = zext i1 %96 to i32
  %98 = add nsw i32 %93, %97
  %99 = load i8, i8* %9, align 1
  %100 = trunc i8 %99 to i1
  %101 = xor i1 %100, true
  %102 = zext i1 %101 to i32
  %103 = add nsw i32 %98, %102
  store i32 %103, i32* %4, align 4
  br label %114

104:                                              ; preds = %70, %53
  %105 = load %struct.Node*, %struct.Node** %6, align 8
  %106 = getelementptr inbounds %struct.Node, %struct.Node* %105, i32 0, i32 17
  store i8 1, i8* %106, align 8
  %107 = load %struct.Type*, %struct.Type** %7, align 8
  %108 = getelementptr inbounds %struct.Type, %struct.Type* %107, i32 0, i32 1
  %109 = load i32, i32* %108, align 4
  %110 = call i32 @align_to(i32 noundef %109, i32 noundef 8)
  %111 = sdiv i32 %110, 8
  %112 = load i32, i32* %3, align 4
  %113 = add nsw i32 %112, %111
  store i32 %113, i32* %3, align 4
  br label %114

114:                                              ; preds = %104, %83
  br label %115

115:                                              ; preds = %114, %43
  br label %141

116:                                              ; preds = %31, %31
  %117 = load i32, i32* %5, align 4
  %118 = add nsw i32 %117, 1
  store i32 %118, i32* %5, align 4
  %119 = icmp sge i32 %117, 8
  br i1 %119, label %120, label %125

120:                                              ; preds = %116
  %121 = load %struct.Node*, %struct.Node** %6, align 8
  %122 = getelementptr inbounds %struct.Node, %struct.Node* %121, i32 0, i32 17
  store i8 1, i8* %122, align 8
  %123 = load i32, i32* %3, align 4
  %124 = add nsw i32 %123, 1
  store i32 %124, i32* %3, align 4
  br label %125

125:                                              ; preds = %120, %116
  br label %141

126:                                              ; preds = %31
  %127 = load %struct.Node*, %struct.Node** %6, align 8
  %128 = getelementptr inbounds %struct.Node, %struct.Node* %127, i32 0, i32 17
  store i8 1, i8* %128, align 8
  %129 = load i32, i32* %3, align 4
  %130 = add nsw i32 %129, 2
  store i32 %130, i32* %3, align 4
  br label %141

131:                                              ; preds = %31
  %132 = load i32, i32* %4, align 4
  %133 = add nsw i32 %132, 1
  store i32 %133, i32* %4, align 4
  %134 = icmp sge i32 %132, 6
  br i1 %134, label %135, label %140

135:                                              ; preds = %131
  %136 = load %struct.Node*, %struct.Node** %6, align 8
  %137 = getelementptr inbounds %struct.Node, %struct.Node* %136, i32 0, i32 17
  store i8 1, i8* %137, align 8
  %138 = load i32, i32* %3, align 4
  %139 = add nsw i32 %138, 1
  store i32 %139, i32* %3, align 4
  br label %140

140:                                              ; preds = %135, %131
  br label %141

141:                                              ; preds = %140, %126, %125, %115
  br label %142

142:                                              ; preds = %141
  %143 = load %struct.Node*, %struct.Node** %6, align 8
  %144 = getelementptr inbounds %struct.Node, %struct.Node* %143, i32 0, i32 1
  %145 = load %struct.Node*, %struct.Node** %144, align 8
  store %struct.Node* %145, %struct.Node** %6, align 8
  br label %28, !llvm.loop !27

146:                                              ; preds = %28
  %147 = load i32, i32* @depth, align 4
  %148 = load i32, i32* %3, align 4
  %149 = add nsw i32 %147, %148
  %150 = srem i32 %149, 2
  %151 = icmp eq i32 %150, 1
  br i1 %151, label %152, label %157

152:                                              ; preds = %146
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.256, i64 0, i64 0))
  %153 = load i32, i32* @depth, align 4
  %154 = add nsw i32 %153, 1
  store i32 %154, i32* @depth, align 4
  %155 = load i32, i32* %3, align 4
  %156 = add nsw i32 %155, 1
  store i32 %156, i32* %3, align 4
  br label %157

157:                                              ; preds = %152, %146
  %158 = load %struct.Node*, %struct.Node** %2, align 8
  %159 = getelementptr inbounds %struct.Node, %struct.Node* %158, i32 0, i32 16
  %160 = load %struct.Node*, %struct.Node** %159, align 16
  call void @push_args2(%struct.Node* noundef %160, i1 noundef zeroext true)
  %161 = load %struct.Node*, %struct.Node** %2, align 8
  %162 = getelementptr inbounds %struct.Node, %struct.Node* %161, i32 0, i32 16
  %163 = load %struct.Node*, %struct.Node** %162, align 16
  call void @push_args2(%struct.Node* noundef %163, i1 noundef zeroext false)
  %164 = load %struct.Node*, %struct.Node** %2, align 8
  %165 = getelementptr inbounds %struct.Node, %struct.Node* %164, i32 0, i32 18
  %166 = load %struct.Obj*, %struct.Obj** %165, align 16
  %167 = icmp ne %struct.Obj* %166, null
  br i1 %167, label %168, label %181

168:                                              ; preds = %157
  %169 = load %struct.Node*, %struct.Node** %2, align 8
  %170 = getelementptr inbounds %struct.Node, %struct.Node* %169, i32 0, i32 2
  %171 = load %struct.Type*, %struct.Type** %170, align 16
  %172 = getelementptr inbounds %struct.Type, %struct.Type* %171, i32 0, i32 1
  %173 = load i32, i32* %172, align 4
  %174 = icmp sgt i32 %173, 16
  br i1 %174, label %175, label %181

175:                                              ; preds = %168
  %176 = load %struct.Node*, %struct.Node** %2, align 8
  %177 = getelementptr inbounds %struct.Node, %struct.Node* %176, i32 0, i32 18
  %178 = load %struct.Obj*, %struct.Obj** %177, align 16
  %179 = getelementptr inbounds %struct.Obj, %struct.Obj* %178, i32 0, i32 7
  %180 = load i32, i32* %179, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.156, i64 0, i64 0), i32 noundef %180)
  call void @push()
  br label %181

181:                                              ; preds = %175, %168, %157
  %182 = load i32, i32* %3, align 4
  ret i32 %182
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @pop(i8* noundef %0) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str.261, i64 0, i64 0), i8* noundef %3)
  %4 = load i32, i32* @depth, align 4
  %5 = add nsw i32 %4, -1
  store i32 %5, i32* @depth, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @has_flonum1(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %3 = load %struct.Type*, %struct.Type** %2, align 8
  %4 = call zeroext i1 @has_flonum(%struct.Type* noundef %3, i32 noundef 0, i32 noundef 8, i32 noundef 0)
  ret i1 %4
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i1 @has_flonum2(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %2, align 8
  %3 = load %struct.Type*, %struct.Type** %2, align 8
  %4 = call zeroext i1 @has_flonum(%struct.Type* noundef %3, i32 noundef 8, i32 noundef 16, i32 noundef 0)
  ret i1 %4
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @popf(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([25 x i8], [25 x i8]* @.str.262, i64 0, i64 0), i32 noundef %3)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.263, i64 0, i64 0))
  %4 = load i32, i32* @depth, align 4
  %5 = add nsw i32 %4, -1
  store i32 %5, i32* @depth, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @copy_ret_buffer(%struct.Obj* noundef %0) #0 {
  %2 = alloca %struct.Obj*, align 8
  %3 = alloca %struct.Type*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  store %struct.Obj* %0, %struct.Obj** %2, align 8
  %10 = load %struct.Obj*, %struct.Obj** %2, align 8
  %11 = getelementptr inbounds %struct.Obj, %struct.Obj* %10, i32 0, i32 3
  %12 = load %struct.Type*, %struct.Type** %11, align 8
  store %struct.Type* %12, %struct.Type** %3, align 8
  store i32 0, i32* %4, align 4
  store i32 0, i32* %5, align 4
  %13 = load %struct.Type*, %struct.Type** %3, align 8
  %14 = call zeroext i1 @has_flonum1(%struct.Type* noundef %13)
  br i1 %14, label %15, label %43

15:                                               ; preds = %1
  %16 = load %struct.Type*, %struct.Type** %3, align 8
  %17 = getelementptr inbounds %struct.Type, %struct.Type* %16, i32 0, i32 1
  %18 = load i32, i32* %17, align 4
  %19 = icmp eq i32 %18, 4
  br i1 %19, label %25, label %20

20:                                               ; preds = %15
  %21 = load %struct.Type*, %struct.Type** %3, align 8
  %22 = getelementptr inbounds %struct.Type, %struct.Type* %21, i32 0, i32 1
  %23 = load i32, i32* %22, align 4
  %24 = icmp sle i32 8, %23
  br i1 %24, label %25, label %26

25:                                               ; preds = %20, %15
  br label %27

26:                                               ; preds = %20
  call void @__assert_fail(i8* noundef getelementptr inbounds ([31 x i8], [31 x i8]* @.str.264, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 696, i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @__PRETTY_FUNCTION__.copy_ret_buffer, i64 0, i64 0)) #8
  unreachable

27:                                               ; preds = %25
  %28 = load %struct.Type*, %struct.Type** %3, align 8
  %29 = getelementptr inbounds %struct.Type, %struct.Type* %28, i32 0, i32 1
  %30 = load i32, i32* %29, align 4
  %31 = icmp eq i32 %30, 4
  br i1 %31, label %32, label %36

32:                                               ; preds = %27
  %33 = load %struct.Obj*, %struct.Obj** %2, align 8
  %34 = getelementptr inbounds %struct.Obj, %struct.Obj* %33, i32 0, i32 7
  %35 = load i32, i32* %34, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.265, i64 0, i64 0), i32 noundef %35)
  br label %40

36:                                               ; preds = %27
  %37 = load %struct.Obj*, %struct.Obj** %2, align 8
  %38 = getelementptr inbounds %struct.Obj, %struct.Obj* %37, i32 0, i32 7
  %39 = load i32, i32* %38, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str.50, i64 0, i64 0), i32 noundef %39)
  br label %40

40:                                               ; preds = %36, %32
  %41 = load i32, i32* %5, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, i32* %5, align 4
  br label %70

43:                                               ; preds = %1
  store i32 0, i32* %6, align 4
  br label %44

44:                                               ; preds = %64, %43
  %45 = load i32, i32* %6, align 4
  %46 = load %struct.Type*, %struct.Type** %3, align 8
  %47 = getelementptr inbounds %struct.Type, %struct.Type* %46, i32 0, i32 1
  %48 = load i32, i32* %47, align 4
  %49 = icmp slt i32 8, %48
  br i1 %49, label %50, label %51

50:                                               ; preds = %44
  br label %55

51:                                               ; preds = %44
  %52 = load %struct.Type*, %struct.Type** %3, align 8
  %53 = getelementptr inbounds %struct.Type, %struct.Type* %52, i32 0, i32 1
  %54 = load i32, i32* %53, align 4
  br label %55

55:                                               ; preds = %51, %50
  %56 = phi i32 [ 8, %50 ], [ %54, %51 ]
  %57 = icmp slt i32 %45, %56
  br i1 %57, label %58, label %67

58:                                               ; preds = %55
  %59 = load %struct.Obj*, %struct.Obj** %2, align 8
  %60 = getelementptr inbounds %struct.Obj, %struct.Obj* %59, i32 0, i32 7
  %61 = load i32, i32* %60, align 8
  %62 = load i32, i32* %6, align 4
  %63 = add nsw i32 %61, %62
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.266, i64 0, i64 0), i32 noundef %63)
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.267, i64 0, i64 0))
  br label %64

64:                                               ; preds = %58
  %65 = load i32, i32* %6, align 4
  %66 = add nsw i32 %65, 1
  store i32 %66, i32* %6, align 4
  br label %44, !llvm.loop !28

67:                                               ; preds = %55
  %68 = load i32, i32* %4, align 4
  %69 = add nsw i32 %68, 1
  store i32 %69, i32* %4, align 4
  br label %70

70:                                               ; preds = %67, %40
  %71 = load %struct.Type*, %struct.Type** %3, align 8
  %72 = getelementptr inbounds %struct.Type, %struct.Type* %71, i32 0, i32 1
  %73 = load i32, i32* %72, align 4
  %74 = icmp sgt i32 %73, 8
  br i1 %74, label %75, label %144

75:                                               ; preds = %70
  %76 = load %struct.Type*, %struct.Type** %3, align 8
  %77 = call zeroext i1 @has_flonum2(%struct.Type* noundef %76)
  br i1 %77, label %78, label %108

78:                                               ; preds = %75
  %79 = load %struct.Type*, %struct.Type** %3, align 8
  %80 = getelementptr inbounds %struct.Type, %struct.Type* %79, i32 0, i32 1
  %81 = load i32, i32* %80, align 4
  %82 = icmp eq i32 %81, 12
  br i1 %82, label %88, label %83

83:                                               ; preds = %78
  %84 = load %struct.Type*, %struct.Type** %3, align 8
  %85 = getelementptr inbounds %struct.Type, %struct.Type* %84, i32 0, i32 1
  %86 = load i32, i32* %85, align 4
  %87 = icmp eq i32 %86, 16
  br i1 %87, label %88, label %89

88:                                               ; preds = %83, %78
  br label %90

89:                                               ; preds = %83
  call void @__assert_fail(i8* noundef getelementptr inbounds ([33 x i8], [33 x i8]* @.str.268, i64 0, i64 0), i8* noundef getelementptr inbounds ([10 x i8], [10 x i8]* @.str.5, i64 0, i64 0), i32 noundef 717, i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @__PRETTY_FUNCTION__.copy_ret_buffer, i64 0, i64 0)) #8
  unreachable

90:                                               ; preds = %88
  %91 = load %struct.Type*, %struct.Type** %3, align 8
  %92 = getelementptr inbounds %struct.Type, %struct.Type* %91, i32 0, i32 1
  %93 = load i32, i32* %92, align 4
  %94 = icmp eq i32 %93, 12
  br i1 %94, label %95, label %101

95:                                               ; preds = %90
  %96 = load i32, i32* %5, align 4
  %97 = load %struct.Obj*, %struct.Obj** %2, align 8
  %98 = getelementptr inbounds %struct.Obj, %struct.Obj* %97, i32 0, i32 7
  %99 = load i32, i32* %98, align 8
  %100 = add nsw i32 %99, 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @.str.66, i64 0, i64 0), i32 noundef %96, i32 noundef %100)
  br label %107

101:                                              ; preds = %90
  %102 = load i32, i32* %5, align 4
  %103 = load %struct.Obj*, %struct.Obj** %2, align 8
  %104 = getelementptr inbounds %struct.Obj, %struct.Obj* %103, i32 0, i32 7
  %105 = load i32, i32* %104, align 8
  %106 = add nsw i32 %105, 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([27 x i8], [27 x i8]* @.str.67, i64 0, i64 0), i32 noundef %102, i32 noundef %106)
  br label %107

107:                                              ; preds = %101, %95
  br label %143

108:                                              ; preds = %75
  %109 = load i32, i32* %4, align 4
  %110 = icmp eq i32 %109, 0
  %111 = zext i1 %110 to i64
  %112 = select i1 %110, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.14, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0)
  store i8* %112, i8** %7, align 8
  %113 = load i32, i32* %4, align 4
  %114 = icmp eq i32 %113, 0
  %115 = zext i1 %114 to i64
  %116 = select i1 %114, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0)
  store i8* %116, i8** %8, align 8
  store i32 8, i32* %9, align 4
  br label %117

117:                                              ; preds = %139, %108
  %118 = load i32, i32* %9, align 4
  %119 = load %struct.Type*, %struct.Type** %3, align 8
  %120 = getelementptr inbounds %struct.Type, %struct.Type* %119, i32 0, i32 1
  %121 = load i32, i32* %120, align 4
  %122 = icmp slt i32 16, %121
  br i1 %122, label %123, label %124

123:                                              ; preds = %117
  br label %128

124:                                              ; preds = %117
  %125 = load %struct.Type*, %struct.Type** %3, align 8
  %126 = getelementptr inbounds %struct.Type, %struct.Type* %125, i32 0, i32 1
  %127 = load i32, i32* %126, align 4
  br label %128

128:                                              ; preds = %124, %123
  %129 = phi i32 [ 16, %123 ], [ %127, %124 ]
  %130 = icmp slt i32 %118, %129
  br i1 %130, label %131, label %142

131:                                              ; preds = %128
  %132 = load i8*, i8** %7, align 8
  %133 = load %struct.Obj*, %struct.Obj** %2, align 8
  %134 = getelementptr inbounds %struct.Obj, %struct.Obj* %133, i32 0, i32 7
  %135 = load i32, i32* %134, align 8
  %136 = load i32, i32* %9, align 4
  %137 = add nsw i32 %135, %136
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.68, i64 0, i64 0), i8* noundef %132, i32 noundef %137)
  %138 = load i8*, i8** %8, align 8
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.69, i64 0, i64 0), i8* noundef %138)
  br label %139

139:                                              ; preds = %131
  %140 = load i32, i32* %9, align 4
  %141 = add nsw i32 %140, 1
  store i32 %141, i32* %9, align 4
  br label %117, !llvm.loop !29

142:                                              ; preds = %128
  br label %143

143:                                              ; preds = %142, %107
  br label %144

144:                                              ; preds = %143, %70
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @pushf() #0 {
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.256, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.269, i64 0, i64 0))
  %1 = load i32, i32* @depth, align 4
  %2 = add nsw i32 %1, 1
  store i32 %2, i32* @depth, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @getTypeId(%struct.Type* noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.Type*, align 8
  store %struct.Type* %0, %struct.Type** %3, align 8
  %4 = load %struct.Type*, %struct.Type** %3, align 8
  %5 = getelementptr inbounds %struct.Type, %struct.Type* %4, i32 0, i32 0
  %6 = load i32, i32* %5, align 8
  switch i32 %6, label %38 [
    i32 2, label %7
    i32 3, label %14
    i32 4, label %21
    i32 5, label %28
    i32 6, label %35
    i32 7, label %36
    i32 8, label %37
  ]

7:                                                ; preds = %1
  %8 = load %struct.Type*, %struct.Type** %3, align 8
  %9 = getelementptr inbounds %struct.Type, %struct.Type* %8, i32 0, i32 3
  %10 = load i8, i8* %9, align 4
  %11 = trunc i8 %10 to i1
  %12 = zext i1 %11 to i64
  %13 = select i1 %11, i32 4, i32 0
  store i32 %13, i32* %2, align 4
  br label %39

14:                                               ; preds = %1
  %15 = load %struct.Type*, %struct.Type** %3, align 8
  %16 = getelementptr inbounds %struct.Type, %struct.Type* %15, i32 0, i32 3
  %17 = load i8, i8* %16, align 4
  %18 = trunc i8 %17 to i1
  %19 = zext i1 %18 to i64
  %20 = select i1 %18, i32 5, i32 1
  store i32 %20, i32* %2, align 4
  br label %39

21:                                               ; preds = %1
  %22 = load %struct.Type*, %struct.Type** %3, align 8
  %23 = getelementptr inbounds %struct.Type, %struct.Type* %22, i32 0, i32 3
  %24 = load i8, i8* %23, align 4
  %25 = trunc i8 %24 to i1
  %26 = zext i1 %25 to i64
  %27 = select i1 %25, i32 6, i32 2
  store i32 %27, i32* %2, align 4
  br label %39

28:                                               ; preds = %1
  %29 = load %struct.Type*, %struct.Type** %3, align 8
  %30 = getelementptr inbounds %struct.Type, %struct.Type* %29, i32 0, i32 3
  %31 = load i8, i8* %30, align 4
  %32 = trunc i8 %31 to i1
  %33 = zext i1 %32 to i64
  %34 = select i1 %32, i32 7, i32 3
  store i32 %34, i32* %2, align 4
  br label %39

35:                                               ; preds = %1
  store i32 8, i32* %2, align 4
  br label %39

36:                                               ; preds = %1
  store i32 9, i32* %2, align 4
  br label %39

37:                                               ; preds = %1
  store i32 10, i32* %2, align 4
  br label %39

38:                                               ; preds = %1
  store i32 7, i32* %2, align 4
  br label %39

39:                                               ; preds = %38, %37, %36, %35, %28, %21, %14, %7
  %40 = load i32, i32* %2, align 4
  ret i32 %40
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @push_args2(%struct.Node* noundef %0, i1 noundef zeroext %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca i8, align 1
  store %struct.Node* %0, %struct.Node** %3, align 8
  %5 = zext i1 %1 to i8
  store i8 %5, i8* %4, align 1
  %6 = load %struct.Node*, %struct.Node** %3, align 8
  %7 = icmp ne %struct.Node* %6, null
  br i1 %7, label %9, label %8

8:                                                ; preds = %2
  br label %41

9:                                                ; preds = %2
  %10 = load %struct.Node*, %struct.Node** %3, align 8
  %11 = getelementptr inbounds %struct.Node, %struct.Node* %10, i32 0, i32 1
  %12 = load %struct.Node*, %struct.Node** %11, align 8
  %13 = load i8, i8* %4, align 1
  %14 = trunc i8 %13 to i1
  call void @push_args2(%struct.Node* noundef %12, i1 noundef zeroext %14)
  %15 = load i8, i8* %4, align 1
  %16 = trunc i8 %15 to i1
  %17 = zext i1 %16 to i32
  %18 = load %struct.Node*, %struct.Node** %3, align 8
  %19 = getelementptr inbounds %struct.Node, %struct.Node* %18, i32 0, i32 17
  %20 = load i8, i8* %19, align 8
  %21 = trunc i8 %20 to i1
  %22 = zext i1 %21 to i32
  %23 = icmp ne i32 %17, %22
  br i1 %23, label %24, label %25

24:                                               ; preds = %9
  br label %41

25:                                               ; preds = %9
  %26 = load %struct.Node*, %struct.Node** %3, align 8
  call void @gen_expr(%struct.Node* noundef %26)
  %27 = load %struct.Node*, %struct.Node** %3, align 8
  %28 = getelementptr inbounds %struct.Node, %struct.Node* %27, i32 0, i32 2
  %29 = load %struct.Type*, %struct.Type** %28, align 16
  %30 = getelementptr inbounds %struct.Type, %struct.Type* %29, i32 0, i32 0
  %31 = load i32, i32* %30, align 8
  switch i32 %31, label %40 [
    i32 14, label %32
    i32 15, label %32
    i32 6, label %36
    i32 7, label %36
    i32 8, label %37
  ]

32:                                               ; preds = %25, %25
  %33 = load %struct.Node*, %struct.Node** %3, align 8
  %34 = getelementptr inbounds %struct.Node, %struct.Node* %33, i32 0, i32 2
  %35 = load %struct.Type*, %struct.Type** %34, align 16
  call void @push_struct(%struct.Type* noundef %35)
  br label %41

36:                                               ; preds = %25, %25
  call void @pushf()
  br label %41

37:                                               ; preds = %25
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.257, i64 0, i64 0))
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @.str.258, i64 0, i64 0))
  %38 = load i32, i32* @depth, align 4
  %39 = add nsw i32 %38, 2
  store i32 %39, i32* @depth, align 4
  br label %41

40:                                               ; preds = %25
  call void @push()
  br label %41

41:                                               ; preds = %8, %24, %40, %37, %36, %32
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @push_struct(%struct.Type* noundef %0) #0 {
  %2 = alloca %struct.Type*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store %struct.Type* %0, %struct.Type** %2, align 8
  %5 = load %struct.Type*, %struct.Type** %2, align 8
  %6 = getelementptr inbounds %struct.Type, %struct.Type* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 4
  %8 = call i32 @align_to(i32 noundef %7, i32 noundef 8)
  store i32 %8, i32* %3, align 4
  %9 = load i32, i32* %3, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([17 x i8], [17 x i8]* @.str.38, i64 0, i64 0), i32 noundef %9)
  %10 = load i32, i32* %3, align 4
  %11 = sdiv i32 %10, 8
  %12 = load i32, i32* @depth, align 4
  %13 = add nsw i32 %12, %11
  store i32 %13, i32* @depth, align 4
  store i32 0, i32* %4, align 4
  br label %14

14:                                               ; preds = %23, %1
  %15 = load i32, i32* %4, align 4
  %16 = load %struct.Type*, %struct.Type** %2, align 8
  %17 = getelementptr inbounds %struct.Type, %struct.Type* %16, i32 0, i32 1
  %18 = load i32, i32* %17, align 4
  %19 = icmp slt i32 %15, %18
  br i1 %19, label %20, label %26

20:                                               ; preds = %14
  %21 = load i32, i32* %4, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.259, i64 0, i64 0), i32 noundef %21)
  %22 = load i32, i32* %4, align 4
  call void (i8*, ...) @println(i8* noundef getelementptr inbounds ([24 x i8], [24 x i8]* @.str.260, i64 0, i64 0), i32 noundef %22)
  br label %23

23:                                               ; preds = %20
  %24 = load i32, i32* %4, align 4
  %25 = add nsw i32 %24, 1
  store i32 %25, i32* %4, align 4
  br label %14, !llvm.loop !30

26:                                               ; preds = %14
  ret void
}

declare zeroext i1 @is_integer(%struct.Type* noundef) #2

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { noreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nofree nosync nounwind willreturn }
attributes #4 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind readonly willreturn "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { argmemonly nofree nounwind willreturn writeonly }
attributes #7 = { noreturn }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind readonly willreturn }

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
