; Initializes the multiboot magic we need for the kernel.
; (See 'LICENSE' in root directory for licensing terms of this file.
; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;

; What we'll do is be actually an ELF64 kernel, but use objcopy to pass off as ELF32.
; Dirty magic, but necessary to use QEMU for testing.

MB_ALIGN    equ 1<<0
MB_MEM_INFO equ 1<<1
MB_FLAGS    equ MB_ALIGN | MB_MEM_INFO
MB_MAGIC    equ 0x1BADB002

MB_CHECKSUM    equ -(MB_MAGIC + MB_FLAGS)

[SECTION .multiboot]
ALIGN 4
dd MB_MAGIC
dd MB_FLAGS
dd MB_CHECKSUM

[SECTION .bss]
ALIGN 4

stack_bottom:
	resb 8196	;8KiB for kernel stack...

stack_top:
			; on x86/x86-64, stack grows downward.

[SECTION .text]
global _kinit:function (_kinit.end - _kinit)
_kinit:
	mov esp, stack_top		; Setup stack. C cannot work without stack.
	extern Kernel_Main		; Kernel_Main defined in main.c...
	call   Kernel_Main		; Jump to kernel's main code...
	cli
	hlt
.hang:
	jmp $

.end:























;OLD!!!



;
; Created by Brian Schnepp
; >> Multiboot 2 <<
; Contributors:
	; 

;[BITS 64]

;extern Kernel_Main

;MAGIC_NUM 	equ 0xE85250D6
;ARCHITECTURE 	equ 1


;Will probably replace this with a stub to switch to 64-bit mode... and multiboot 1.

;hdr_start:
;	dd MAGIC_NUM						; Magic number for multiboot 2...
;	dd ARCHITECTURE						; This is a guess. Trying to get x86_64...
;	dd hdr_end - hdr_start					; Size of the header total...
;	;dd -(MAGIC_NUM + ARCHITECTURE + (hdr_end - hdr_start))	; Checksum...??

;hdr_end:
	
