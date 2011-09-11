
CC = gcc

SOURCES = boot.o main.o monitor.o common.o printf.o
CFLAGS  = -Wall -O3 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS = -Tlink.ld -s
ASFLAGS = -felf

all: $(SOURCES) kernel
clean:
	rm -f *.o
	rm -f kernel

kernel: $(SOURCES)
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

