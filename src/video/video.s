[bits 32]
[global init_video]
init_video:
	cli
	push	cs
	push	ds
	push	es
	push	fs
	push	ss

;	mov		eax, cr0
;	xor		eax, 1
;	mov		cr0, eax

;	mov		eax, cr0
;	or		eax, 1
;	mov		cr0, eax

	pop		ss
	pop		fs
	pop		es
	pop		ds
	pop		cs
	sti
	ret
