
all:
	make -C src
clean:
	make clean -C src
	rm -f log
	rm -f floppy.img
	[ -d "mnt" ] && rmdir mnt || true
rebuild: clean all
debug: all floppy.img
	@echo running bochs...
	@bochs -q
qemu: all floppy.img
	@echo running qemu...
	@qemu -boot a -fda floppy.img

floppy.img: src/kernel grub.img
	@echo updating image...
	@[ -d "mnt" ] || mkdir mnt
	@cp grub.img floppy.img
	@sudo mount floppy.img -o loop mnt
	@sudo cp src/kernel mnt/
	@sudo umount mnt
	@touch $@
