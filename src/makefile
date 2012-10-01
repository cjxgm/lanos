
CC = gcc
CFLAGS = -Wall -Werror -O3

all: boot core utils
utils: mkfloppy
clean:
	@echo -e "\e[1;35m[ ] \e[34mcleaning \e[33m\e[m..."
	rm -f boot
	rm -f core
	rm -f mkfloppy
rebuild: clean all
debug: all
	@echo -e "\e[1;35m[ ] \e[34mmaking \e[33mfloppy.img\e[m..."
	@./mkfloppy floppy.img boot core

# implicit rules
%: %.s
	@echo -e "\e[1;35m[s] \e[34mcompiling \e[33m$@\e[m..."
	@nasm -o $@ $<
	@chmod +x $@
%: %.c
	@echo -e "\e[1;35m[c] \e[34mcompiling \e[33m$@\e[m..."
	@$(CC) $(CFLAGS) -o $@ $<

