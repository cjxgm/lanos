
;vim: ft=nasm ts=4 sw=4 sts=0 noet

; lander - the LANos loaDER, stage 1
; for loading the stage 2

[org 7c00h]

[bits 16]




init:
	mov		ax, cs
	mov		ds, ax
	; video memory
	mov		ax, 0b800h
	mov		es, ax

main:
	call	clear_screen

	mov		si, msg_loading
	xor		di, di
	mov		ah, 00000010b
	call	write_string

	call	load_lander

	mov		si, msg_done
	mov		di, 80
	mov		ah, 00000010b
	call	write_string

	xor		ah, ah
	int		16h
	; al <-- key pressed

	jmp		1000h:0200h


; void clear_screen()
clear_screen:
	xor		ax, ax
	xor		di, di
	mov		cx, 80*25
	repnz	stosw
	ret


; void write_string(ds:si str, di to_where, ah color)
write_string:
	shl		di, 1			; each char takes 2 bytes

.write:
	lodsb
	cmp		al, 0
	je		.end
	stosw
	jmp		.write

.end:
	ret

; void load_lander()
load_lander:
	push	es

	mov		bx, 1000h
	mov		es, bx
	mov		bx, 0200h
	mov		ax, 1

.0:
	cmp		ax, 127
	jg		.end
	call	load_sector
	jc		.failed
	inc		ax
	add		bx, 200h
	jmp		.0

.end:
	pop		es
	ret

.failed:
	pop		es

	mov		si, msg_fail
	mov		di, 80
	mov		ah, 00001100b
	call	write_string

	jmp		$

; CF load_sector(ax sector)
load_sector:
	push	ax
	push	ax

.reset:
	xor		ah, ah
	xor		dl, dl
	int		13h
	jc		.reset

	pop		ax
	call	lba_to_chs
	mov		ah, 2				; read floppy sector function
	mov		al, 1				; read 1 sector
	mov		dl, 0				; drive 0 (floppy)
	int		13h

	pop		ax
	ret

; cx,dh lba_to_chs(ax lba)
lba_to_chs:
	push	ax
	push	bx

	mov		bl, 18
	div		bl
	inc		ah
	mov		cl, ah				; sector

	mov		dh, al
	shr		al, 1
	mov		ch, al				; track / cylinder

	and		dh, 1				; head
	pop		bx
	pop		ax
	ret




;;;;;;;;;;;;;;;;;; data ;;;;;;;;;;;;;;;;;;
msg_loading:	db "Loading lander...", 0
msg_done:		db "Done. Press any key to jump into lander...", 0
msg_fail:		db "Failed to load lander.", 0

