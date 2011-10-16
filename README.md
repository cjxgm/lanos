lanos - Lanos' AN OS
======================================================================
The Lanos Project<br>
by eXerigumo Clanjor

<h3>中文文档见 doc 目录(see doc/ for Chinese document)</h3>

Copyright (C) eXerigumo Clanjor (兰威举/哆啦比猫), 2010-2011.<br>
All the codes are licensed under GPLv2,<br>
and all the artworks/documents are licensed under CC-BY-SA 3.0.<br>
*It comes with ABSOLUTELY NO WARRANTY!*

Screenshots (0.13 old release)
------------------------------------------------------------
Lanos on a real machine!<br>
![](https://github.com/cjxgm/lanos/raw/master/screenshots/01.jpg)
![](https://github.com/cjxgm/lanos/raw/master/screenshots/02.jpg)

And video [here](http://www.tudou.com/programs/view/usYXAXhisVw/).

Introduction
------------------------------------------------------------
This project is a sub project of cjsp (Clanjor Selfaction Project) -
the OS part.<br>
It uses GRUB to load the kernel written in C.<br>

Definition and Goals
------------------------------------------------------------
Lanos is a 32-bit not-so-protected non-UNIX-clone OS. Useful functions
will be implemented as earliest as possible. Lanos will provide
LanosGL (there's OpenGL maybe), digital audio, high resolution,
single process with multi-threads, etc.
All the applications must (yet) be hard-coded into the kernel.

Lanos is a toy for hackers. Iy can be used for bootable demoscene.

Have a Try
------------------------------------------------------------
You need _gcc_, _ld_, _nasm_ and _make_ to compile the source code,
and you need _qemu_ or _bochs_ to run it (if you don't want to install it).

Having them installed, you type following command
to get the source code (Linux):

	git clone git://github.com/cjxgm/lanos.git

Then, compile the kernel (*it needs the root permission
to mount the floppy image*):

	make

Then, run it. If you are using bochs, type:

	make debug

Or for qemu users:

	make qemu

Then, the source codes will be compiled and linked, and a floppy
image called _floppy.img_ will be created with the kernel compiled
copied in (*it is this step that needs the root's permission*).
Finally, the virtual machine will run.

You can try modifying it. The init code is src/base/init.c.
But, you have to obey the Lanos Coding Style.

Lanos Coding Style
------------------------------------------------------------
The Lanos Coding Style is just as same as the Linux Kernel Coding Style,
*except that you MUST set your editor's tab width to 4 space-wide!*

Issues
------------------------------------------------------------
("\*" means "solved", "X" means "canceled")

 * 2011/09/11 * Add timer, but does not work.
 * 2011/09/18 X Add video 1024x768x24 mode, but do not work.
 * 2011/10/16&nbsp;&nbsp;&nbsp;sin/cos does not work properly, and
   printf("%g\n", PI), neither.
