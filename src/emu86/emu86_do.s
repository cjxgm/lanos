
[bits 32]

[global emu86_do_cmp]

emu86_do_cmp:
	mov		eax, [esp+4]
	mov		ebx, [esp+8]
	cmp		eax, ebx
	pushf
	pop		eax
	ret

