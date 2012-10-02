
;vim: ft=nasm ts=4 sw=4 sts=0 noet

[org 0]

[bits 32]


main:
	mov		[0A0000h], byte 15

	jmp		$

