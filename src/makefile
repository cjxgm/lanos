
CC = gcc

OBJ_BASE = base/boot.o \
		   base/interrupt.o  base/isr.o base/timer.o \
		   base/desc_table.o base/desc_table_flush.o

OBJ_VIDEO = video/monitor.o video/video.o

OBJ_MISC = misc/common.o misc/stdio.o misc/assert.o misc/string.o

OBJ_KEYBOARD = keyboard/keyboard.o keyboard/kb_queue.o

OBJ_APP = app/lush.o

SOURCES = $(OBJ_BASE)		\
		  $(OBJ_VIDEO)		\
		  $(OBJ_MISC)		\
		  $(OBJ_KEYBOARD)	\
		  $(OBJ_APP)		\
		  main.o
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
	ld $(LDFLAGS) -o $@ $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

