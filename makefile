
.PHONY: all clean rebuild run debug bin floppy

all: floppy
clean:
	@make clean -C src
	rm -f log
	rm -f floppy.img
rebuild: clean all
run: all
	@echo -e "\e[1;33mrunning qemu...\e[m"
	@qemu -boot a -fda floppy.img
debug:
	@echo -e "\e[1;33mrunning gdb with qemu...\e[m"
	@qemu -s -S -boot a -fda floppy.img &
	@gdb -x debug.gdb

floppy: bin
	@./src/mkfloppy floppy.img src/boot src/core

bin:
	@make -C src
