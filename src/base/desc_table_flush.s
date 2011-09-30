
[bits 32]

[global idt_flush]
[global gdt_flush]

idt_flush:
	; Get the pointer to the IDT, passed as a parameter. 
	mov		eax, [esp+4]
	lidt	[eax]			; Load the IDT pointer.
	sti
	ret

gdt_flush:
	; Get the pointer to the GDT, passed as a parameter.
	mov		eax, [esp+4]
	lgdt	[eax]		; Load the new GDT pointer

	mov		ax, 0x10	; 0x10 is the offset in the GDT to our data segment
	mov		ds, ax		; Load all data segment selectors
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		ss, ax
	jmp		0x08:.flush	; 0x08 is the offset to our code segment: Far jump!
.flush:
	ret

