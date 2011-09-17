lanos - Lanos' AN OS
======================================================================
The Lanos Project<br>
by eXerigumo Clanjor

<h2>中文文档见 doc 目录(see doc/ for Chinese document)</h2>

All the codes are licensed under GPLv2,<br>
and all the artworks/documents are licensed under CC-BY-SA 3.0,<br>
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

You can try to modify it. The main code is src/main.c. *Before you do it,
set your editor's tab width to 4 spaces!*

Issues
------------------------------------------------------------
("\*" means have been solved)

 * 2011/9/11 * Add timer, but does not work.

