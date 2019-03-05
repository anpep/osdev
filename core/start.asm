;;
;;  multiboot stub
;;  
;;  SPDX-License-Identifier: GPL-2.0-only
;;  Copyright (C) 2018, angel
;;

;;
;;  multiboot constants
;;
MB2_HEADER_MAGIC     equ 0xe85250d6  ; magic field should contain this
MB_ARCHITECTURE_I386 equ 0           ; Intel 32-bit Protected Mode
MB_HEADER_TAG_END    equ 0           ; required end tag

;;
;;  multiboot header
;;
section .boot
  align 4

  hdr:
    magic:        dd MB2_HEADER_MAGIC
    architecture: dd MB_ARCHITECTURE_I386
    size:         dd hdr_fin - hdr
    checksum:     dd -(MB2_HEADER_MAGIC + MB_ARCHITECTURE_I386 + hdr_fin - hdr)

  tag_end:
    dw MB_HEADER_TAG_END
    dw 0
    dd tag_end_fin - tag_end

    tag_end_fin:

  hdr_fin:

;;
;;  kernel stub
;;
section .text
  bits    32
  global  start:function (start.end - start)
  extern  main

  start:  cli
          
          mov   esp, stack_end   ; setup kernel stack
          push  0                ; reset EFLAGS
          popf

          push  ebx              ; bootloader data struct
          push  eax              ; bootloader magic value
          call  main

  .loop:  hlt
          jmp   .loop
  .end:

;;
;;  stack layout
;;
section .bss
  align 16
  stack_start: resb 0x4000
  stack_end:
