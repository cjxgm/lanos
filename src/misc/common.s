
[bits 32]

[global outb]
[global outw]
[global inb]
[global inw]

outb:
	mov		edx, [esp+4]
	mov		eax, [esp+8]
	out		dx, al
	ret

outw:
	mov		edx, [esp+4]
	mov		eax, [esp+8]
	out		dx, ax
	ret

inb:
	mov		edx, [esp+4]
	in		al, dx
	ret

inw:
	mov		edx, [esp+4]
	in		ax, dx
	ret

