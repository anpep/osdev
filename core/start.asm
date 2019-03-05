;;
;;  multiboot stub
;;  
;;  SPDX-License-Identifier: GPL-2.0-only
;;  Copyright (C) 2018, angel
;;

;;
;;  multiboot constants
;;
%define MB2_HEADER_MAGIC      0xe85250d6  ; magic field should contain this
%define MB_ARCHITECTURE_I386  0           ; Intel 32-bit Protected Mode
%define MB_HEADER_TAG_END     0           ; requried end tag

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
;;  common kernel constants
;;
%define KERNEL_VIRT           0xc0000000  ; kernel virtual address

;;
;;  kernel stub
;;
section .text
  bits    32

  extern  __kernel_start
  extern  __kernel_end

  extern  __data_start

  global  start
  global  entry

  extern  main

  start:  ;; kernel pre-entry point
  .mini:  ;; early page table setup: maps kernel memory to KERNEL_VIRT address
          ; physical address of first page table
          mov   edi, early_ptab1 - KERNEL_VIRT
          mov   esi, 0           ; source physical address
          mov   ecx, 1024        ; map 1K pages

  .mcmp:  ;; loop condition
          cmp   esi, __kernel_start - KERNEL_VIRT
          jl    .mmap
          cmp   esi, __kernel_end - KERNEL_VIRT
          jge   .mend
        
          mov  edx, esi          ; map this physical address as
          or   edx, 0x003        ; present, writable
          mov  [edi], edx

  .mmap:  ;; map a single page
          add  esi, 0x1000       ; increment source address (4KiB for each page)
          add  edi, 4            ; size of page table entries is 4 bytes

          loop .mcmp             ; loop again

  .mend:  ;; finish early page table setup
          ; physical address of the page table entry
          %define PTAB_ADDR     early_ptab1 - KERNEL_VIRT + 0x003
          %define PTAB_ENTRY(s) early_pdir - KERNEL_VIRT + (s / (0x400 * 0x400))

          ; identity-map the page, as EIP currently points to physical addresses
          ; and the processor does not know about the change until TLB flushes
          ; [0x00000000..0x003FFFFF]
          mov   dword [PTAB_ENTRY(0)], PTAB_ADDR

          ; map the page to kernel virtual address at the page dir entry for the
          ; new kernel virtual address (see PTAB_ENTRY macro)
          ; [0xC0000000..0xC03FFFFF]
          mov   dword [PTAB_ENTRY(KERNEL_VIRT)], PTAB_ADDR
          
          ; set page directory address
          mov   ecx, early_pdir - KERNEL_VIRT
          mov   cr3, ecx

          ; enable paging and the write-protect bit
          mov   ecx, cr0
          or    ecx, 0x80010000
          mov   cr0, ecx

          ; jump to the new kernel address using a long jump
          lea   ecx, [entry]
          jmp   ecx
   .end:

  entry:  ;; from this point we're on KERNEL_VIRT
          ; unmap identity pages we required before
          mov   dword [early_pdir], 0
          mov   ecx, cr3         ; set page directory address again to force a
          mov   cr3, ecx         ; TLB flush
          
          mov   esp, stack_end   ; setup kernel stack
          push  0                ; reset EFLAGS
          popf

          call  main

          cli
  .loop:  hlt
          jmp   .loop
   .end:

;;
;;  stack layout
;;
section .bss
  align 4096

  global early_pdir
  global early_ptab1

  stack_start:          resb  0x4000
  stack_end:

  early_pdir:           resb  0x1000
  early_ptab1:          resb  0x1000
