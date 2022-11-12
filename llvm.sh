rm *.ll
clang -S -emit-llvm *.c
llvm-link -S -v -o chibicc.ll *.ll
clang chibicc.ll -o chibicc
