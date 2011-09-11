lanos - Lanos' AN OS
======================================================================
The Lanos Project<br>
by eXerigumo Clanjor

This project is licensed under GPLv2.<br>
*ABSOLUTELY NO WARRANTY!*

Introduction
------------------------------------------------------------
This project is a sub project of cjsp (Clanjor Selfaction Project) -
the OS part.<br>
It uses GRUB to load the kernel written in C.<br>
It's, eh, just kind of hacking for myself (my bad English...)

Have a try
------------------------------------------------------------
You need _qemu_/_bochs_(either is ok), _gcc_, _ld_, _nasm_, _make_

After having them installed, you type following command
if you are using bochs:

	make debug

Or for qemu users:

	make qemu

Then, the source codes will be compiled and linked, and a floppy
image called _floppy.img_ will be created with the kernel compiled
copied in (*this will need the root's permission*). Finally, the
virtual machine will run. As this OS is in the very alpha stage,
you can only see the output for testing.

You can try to modify it. The main code is src/main.c

