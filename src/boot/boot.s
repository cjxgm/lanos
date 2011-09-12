
; load kernel and modules on a page boundary
MBOOT_PAGE_ALIGN    equ 1<<0
; provide the kernel with memory info
MBOOT_MEM_INFO      equ 1<<1
; multiboot magic value
MBOOT_HEADER_MAGIC  equ 0x1BADB002
; NOTE: I do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass me a symbol table.
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[bits 32]

[global mboot]
; start of the .text/.bss section.
[extern code]
[extern bss]
; end of the last loadable section.
[extern end]

mboot:
	dd MBOOT_HEADER_MAGIC	; GRUB will search for this value on each
							; 4-byte boundary in your kernel file
	dd MBOOT_HEADER_FLAGS	; How GRUB should load your file / settings
	dd MBOOT_CHECKSUM		; To ensure that the above values are correct

	dd mboot				; Location of this descriptor
	dd code					; Start of kernel '.text' (code) section.
	dd bss					; end of kernel '.data' section.
	dd end					; end of kernel.
	dd start				; kernel entry point (initial EIP).

[global start]				; kernel entry point.
[extern main]				; this is the entry point of the C code

start:
	cli						; close interrupts

	; execute the kernel:
	push	ebx				; multiboot header
	call	main

	jmp		$				; loop forever

