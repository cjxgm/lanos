
[bits 32]

; load kernel and modules on a page boundary
MBOOT_PAGE_ALIGN	equ 1<<0
; provide the kernel with memory info
MBOOT_MEM_INFO		equ 1<<1

MBOOT_HEADER_MAGIC	equ 0x1BADB002
MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[extern code]
[extern bss]
[extern end]
[global mboot]

mboot:
	dd MBOOT_HEADER_MAGIC
	dd MBOOT_HEADER_FLAGS
	dd MBOOT_CHECKSUM

	dd mboot
	dd code
	dd bss
	dd end
	dd start

[global start]				; kernel entry point.
[global boot_fail]
[extern init]				; in init.c

start:
	cli

	; init fpu the correct way
	finit

	; reconfigure the stack pointer
	mov		esp, start		; there's about 1mb stack space

	; execute init code
	push	end				; kernel kernel end address
	push	start			; kernel start address
	push	ebx				; multiboot header
	call	init

	jmp		$				; loop forever

; When booting failed at the very beginning of the boot process,
; call this routine. (That means, it crashes!)
boot_fail:
	cli

	; show a red screen
	mov		al, ' '
	mov		ah, 11000000b
	mov		edi, 0b8000h
	mov		ecx, 80*25
	rep		stosw

	jmp		$

