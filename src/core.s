
;vim: ft=nasm ts=4 sw=4 sts=0 noet

[org 200h]

[bits 16]




init:
	mov		ax, cs
	mov		ds, ax

	; init stack
	mov		ax, 800h
	mov		es, ax
	mov		sp, 0ffffh

	; init video memory
	mov		ax, 0b800h
	mov		gs, ax


main:
	mov		al, 'X'
	mov		ah, 01110000b
	mov		[gs:160*2+0], ax
	call	test2
	jmp		$




times 800h db 0		; test with bigger file




test2:
	mov		al, 'T'
	mov		ah, 01110000b
	mov		[gs:160*2+2], ax
	ret

