
all: kernel floppy.img
clean:
	@echo -e "\e[1;33mcleaning up...\e[m"
	@make clean -C src
	@rm -f log
	@rm -f floppy.img
	@[ -d "mnt" ] && rmdir mnt || true
rebuild: clean all
debug: all
	@echo -e "\e[1;33mrunning bochs...\e[m"
	@bochs -q || true
qemu: all
	@echo -e "\e[1;33mrunning qemu...\e[m"
	@qemu -boot a -fda floppy.img

kernel:
	@echo -e "\e[1;33mcompiling kernel...\e[m"
	@make -C src
floppy.img: src/kernel grub.img
	@echo -e "\e[1;33mupdating image...\e[m"
	@[ -d "mnt" ] || mkdir mnt
	@cp grub.img floppy.img
	@sudo mount floppy.img -o loop mnt
	@sudo cp src/kernel mnt/
	@sudo umount mnt
	@touch $@
