  .file 1 "issues/apprentice.c"
  .file 2 "issues/file.h"
  .file 3 "./include/stddef.h"
  .zero 8
  .hidden	file_nnames
  .section .data,"aw",@progbits
  .type file_nnames, @object
  .size file_nnames, 8
  .align 8
file_nnames:
  .quad 3  # 0x3
  .size file_nnames, 8
  .zero 2
  .local	.L..5
  .section .data,"aw",@progbits
  .type .L..5, @object
  .size .L..5, 2
.L..5:
  .byte 99  # 0x63
  .byte 0  # 0
  .size .L..5, 2
  .zero 2
  .local	.L..4
  .section .data,"aw",@progbits
  .type .L..4, @object
  .size .L..4, 2
.L..4:
  .byte 98  # 0x62
  .byte 0  # 0
  .size .L..4, 2
  .zero 2
  .local	.L..3
  .section .data,"aw",@progbits
  .type .L..3, @object
  .size .L..3, 2
.L..3:
  .byte 97  # 0x61
  .byte 0  # 0
  .size .L..3, 2
  .zero 2
  .local	.L..2
  .section .data,"aw",@progbits
  .type .L..2, @object
  .size .L..2, 2
.L..2:
  .byte 99  # 0x63
  .byte 0  # 0
  .size .L..2, 2
  .zero 2
  .local	.L..1
  .section .data,"aw",@progbits
  .type .L..1, @object
  .size .L..1, 2
.L..1:
  .byte 98  # 0x62
  .byte 0  # 0
  .size .L..1, 2
  .zero 2
  .local	.L..0
  .section .data,"aw",@progbits
  .type .L..0, @object
  .size .L..0, 2
.L..0:
  .byte 97  # 0x61
  .byte 0  # 0
  .size .L..0, 2
  .zero 24
  .globl	file_names
  .section .data,"aw",@progbits
  .type file_names, @object
  .size file_names, 24
  .align 16
file_names:
  .quad .L..3+0
  .quad .L..4+0
  .quad .L..5+0
  .size file_names, 24
  .zero 8
  .zero 8
  .section  .note.GNU-stack,"",@progbits
