
CC = gcc

SOURCES = boot/boot.o main.o video/monitor.o misc/common.o \
			misc/printf.o interrupt/interrupt.o interrupt/isr.o \
			desc_table/desc_table.o desc_table/desc_table_flush.o \
			misc/assert.o interrupt/timer.o
CFLAGS  = -Wall -Iinclude -ffreestanding -nostdlib -nostdinc \
			-fno-builtin -fno-stack-protector
LDFLAGS = -Tmisc/link.ld
ASFLAGS = -felf

all: $(SOURCES) kernel
clean:
	for f in *; do [ -d "$$f" ] && rm -f $$f/*.o; done || true
	rm -f *.o
	rm -f kernel

kernel: $(SOURCES)
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

