
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
	; enter 320x200x256 mode
	xor		ah, ah
	mov		al, 13h
	int		10h
	mov		ax, 0A000h
	mov		gs, ax

	call	draw

	; wait a key
	xor		ah, ah
	int		16h
	; al <-- key pressed

	; back to text mode
	xor		ah, ah
	mov		al, 3h
	int		10h

.end:
	xor		ah, ah
	int		16h
	jmp		.end


; void draw()
draw:
	mov		cx, 199
.1:
	mov		bx, cx
	mov		cx, 319
.0:
	mov		ax, cx
	mov		dl, al
	add		dl, bl
	call	plot
	dec		cx
	jnz		.0

	mov		cx, bx
	dec		cx
	jnz		.1

	ret

; void plot(ax x, bx y, dl color)
plot:
	push bx
	push cx

	; offset = (y<<8) + (y<<6) + x
	mov		cx, bx
	shl		bx, 8
	shl		cx, 6
	add		bx, cx
	add		bx, ax

	mov		[gs:bx], dl

	pop		cx
	pop		bx
	ret

