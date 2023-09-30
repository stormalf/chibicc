rm *.ll
clang-15 -S -emit-llvm *.c
llvm-link-15 -S -v -o chibicc.ll *.ll
clang-15 chibicc.ll -o chibicc
