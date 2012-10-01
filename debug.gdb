set disassembly-flavor intel
set architecture i8086
layout asm
tui reg general

target remote tcp::1234
b *0x7c00
c
