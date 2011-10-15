lanos - Lanos' AN OS (Lanos 是一个操作系统)
======================================================================
Lanos 项目，由兰威举(哆啦比猫)发起。

版权所有 (C) 兰威举(哆啦比猫), 2010-2011.<br>
所有代码均采用 GNU 通用公共许可证 2.0 进行许可。<br>
所有艺术作品及文档均采用知识共享署名·相同方式共享 3.0 Unported
许可协议进行许可。<br>
<em>绝无担保！本软件造成的任何后果概不负责！<br>
任何由于中文造成的语言歧义以英语为准。</em>

截图 (0.13 旧版本)
------------------------------------------------------------
真机上的 Lanos！<br>
![](https://github.com/cjxgm/lanos/raw/master/screenshots/01.jpg)
![](https://github.com/cjxgm/lanos/raw/master/screenshots/02.jpg)

视频[在此](http://www.tudou.com/programs/view/usYXAXhisVw/)。

简介
------------------------------------------------------------
此项目是 cjsp 项目（Clanjor Selfaction Project）的一个子项目——
操作系统部分。<br>
它使用 GRUB 来载入，是一个主要用 C 语言写成的操作系统。

定义及目标
------------------------------------------------------------
Lanos 是一个 32 位不全保护模式非 UNIX 克隆的操作系统
(32-bit not-so-protected non-UNIX-clone OS)。Lanos 将
尽早实现实用功能（如，在完成屏幕管理模块后就立即实现了 printf）。
Lanos 将提供 LanosGL（可能还有 OpenGL）、数字音频(digital audio)、高分辨率、
鼠标/键盘/（可能还有）手柄驱动、多线程单进程
(single process with multi-threads)的支持。Lanos <em>可能</em>会提供
文件操作的支持，且所有应用程序（目前）必须硬编码(hard-coded)于内核。

Lanos 是一个给 hackers 的玩具。Lanos 可用于制作可引导实时（三维）动画
(bootable demoscene).

目录结构
------------------------------------------------------------
在 src/ 中（其中，带“·”的项目表示要先完成）：

 * · base/
 * · video/
 * &nbsp;&nbsp;audio/
 * · misc/
 * · keyboard/
 * &nbsp;&nbsp;mouse/
 * · include/
 * &nbsp;&nbsp;gl/
 * · app/
 * · math/

我要试一试
------------------------------------------------------------
你需要 _gcc_, _ld_, _nasm_ 和 _make_ 来编译源代码。
你还需要 _qemu_ 或 _bochs_ 来运行它（如果你不想安装它的话）。

安装完所需软件后，使用以下命令获取源代码（Linux）：

	git clone git://github.com/cjxgm/lanos.git

接着，编译内核（由于要 mount 软盘镜像，需要有 root 权限）：

	make

对于 bochs 用户，可以用

	make debug

来尝试运行，而对于 qemu 用户，可以用

	make qemu

尝试运行。

于是乎，源码会被编译链接，然后一个叫 floppy.img 的软盘镜像会被创建，
同时编译后的内核会被复制到其中（就是这一步需要 root 权限）。
最终，虚拟机运行起来了。

你可以尝试修改它，初始化代码在 src/base/init.c 中。
但是，你<em>必须</em>遵守 Lanos 代码风格。

Lanos 代码风格
------------------------------------------------------------
Lanos 代码风格与 Linux 内核代码风格几乎一样，除了一点：
你<em>必须</em>把你的编辑器的 tab 宽度设置成 4 个空格宽！

已知问题
------------------------------------------------------------
（“·”表示已解决，“×”表示放弃或取消）

 * 2011/9/11 · 计时器不工作
 * 2011/9/18 × 加入 1024x768x24 图形模式，但不工作

